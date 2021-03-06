/*	$NetBSD: bzivsc.c,v 1.1 1997/10/10 04:53:32 mhitch Exp $	*/

/*
 * Copyright (c) 1997 Michael L. Hitch
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product contains software written by Michael L. Hitch for
 *	the NetBSD project.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include <sys/types.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/device.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/queue.h>

#include <dev/scsipi/scsi_all.h>
#include <dev/scsipi/scsipi_all.h>
#include <dev/scsipi/scsiconf.h>
#include <dev/scsipi/scsi_message.h>

#include <machine/cpu.h>
#include <machine/param.h>

#include <dev/ic/ncr53c9xreg.h>
#include <dev/ic/ncr53c9xvar.h>

#include <amiga/amiga/isr.h>
#include <amiga/dev/bzivscvar.h>
#include <amiga/dev/zbusvar.h>

void	bzivscattach	__P((struct device *, struct device *, void *));
int	bzivscmatch	__P((struct device *, struct cfdata *, void *));

/* Linkup to the rest of the kernel */
struct cfattach bzivsc_ca = {
	sizeof(struct bzivsc_softc), bzivscmatch, bzivscattach
};

struct cfdriver bzivsc_cd = {
	NULL, "bzivsc", DV_DULL
};

struct scsipi_adapter bzivsc_switch = {
	ncr53c9x_scsi_cmd,
	minphys,		/* no max at this level; handled by DMA code */
	NULL,
	NULL,
};

struct scsipi_device bzivsc_dev = {
	NULL,			/* Use default error handler */
	NULL,			/* have a queue, served by this */
	NULL,			/* have no async handler */
	NULL,			/* Use default 'done' routine */
};

/*
 * Functions and the switch for the MI code.
 */
u_char	bzivsc_read_reg __P((struct ncr53c9x_softc *, int));
void	bzivsc_write_reg __P((struct ncr53c9x_softc *, int, u_char));
int	bzivsc_dma_isintr __P((struct ncr53c9x_softc *));
void	bzivsc_dma_reset __P((struct ncr53c9x_softc *));
int	bzivsc_dma_intr __P((struct ncr53c9x_softc *));
int	bzivsc_dma_setup __P((struct ncr53c9x_softc *, caddr_t *,
	    size_t *, int, size_t *));
void	bzivsc_dma_go __P((struct ncr53c9x_softc *));
void	bzivsc_dma_stop __P((struct ncr53c9x_softc *));
int	bzivsc_dma_isactive __P((struct ncr53c9x_softc *));

struct ncr53c9x_glue bzivsc_glue = {
	bzivsc_read_reg,
	bzivsc_write_reg,
	bzivsc_dma_isintr,
	bzivsc_dma_reset,
	bzivsc_dma_intr,
	bzivsc_dma_setup,
	bzivsc_dma_go,
	bzivsc_dma_stop,
	bzivsc_dma_isactive,
	0,
};

/* Maximum DMA transfer length to reduce impact on high-speed serial input */
u_long bzivsc_max_dma = 1024;
extern int ser_open_speed;

u_long bzivsc_cnt_pio = 0;	/* number of PIO transfers */
u_long bzivsc_cnt_dma = 0;	/* number of DMA transfers */
u_long bzivsc_cnt_dma2 = 0;	/* number of DMA transfers broken up */
u_long bzivsc_cnt_dma3 = 0;	/* number of pages combined */

#ifdef DEBUG
struct {
	u_char hardbits;
	u_char status;
	u_char xx;
	u_char yy;
} bzivsc_trace[128];
int bzivsc_trace_ptr = 0;
int bzivsc_trace_enable = 1;
void bzivsc_dump __P((void));
#endif

/*
 * if we are a Phase5 Blizzard 12x0-IV
 */
int
bzivscmatch(parent, cf, aux)
	struct device *parent;
	struct cfdata *cf;
	void *aux;
{
	struct zbus_args *zap;
	volatile u_char *regs;

	zap = aux;
	if (zap->manid != 0x2140)
		return(0);			/* It's not Phase 5 */
	if (zap->prodid != 11 && zap->prodid != 17)
		return(0);			/* Not Blizzard 12x0 */
	if (!is_a1200())
		return(0);			/* And not A1200 */
	regs = &((volatile u_char *)zap->va)[0x8000];
	if (badaddr((caddr_t)regs))
		return(0);
	regs[NCR_CFG1 * 4] = 0;
	regs[NCR_CFG1 * 4] = NCRCFG1_PARENB | 7;
	delay(5);
	if (regs[NCR_CFG1 * 4] != (NCRCFG1_PARENB | 7))
		return(0);
	return(1);
}

/*
 * Attach this instance, and then all the sub-devices
 */
void
bzivscattach(parent, self, aux)
	struct device *parent, *self;
	void *aux;
{
	struct bzivsc_softc *bsc = (void *)self;
	struct ncr53c9x_softc *sc = &bsc->sc_ncr53c9x;
	struct zbus_args  *zap;
	extern u_long scsi_nosync;
	extern int shift_nosync;
	extern int ncr53c9x_debug;

	/*
	 * Set up the glue for MI code early; we use some of it here.
	 */
	sc->sc_glue = &bzivsc_glue;

	/*
	 * Save the regs
	 */
	zap = aux;
	bsc->sc_reg = &((volatile u_char *)zap->va)[0x8000];
	bsc->sc_dmabase = &bsc->sc_reg[0x8000];

	sc->sc_freq = 40;		/* Clocked at 40Mhz */

	printf(": address %p", bsc->sc_reg);

	sc->sc_id = 7;

	/*
	 * It is necessary to try to load the 2nd config register here,
	 * to find out what rev the FAS chip is, else the ncr53c9x_reset
	 * will not set up the defaults correctly.
	 */
	sc->sc_cfg1 = sc->sc_id | NCRCFG1_PARENB;
	sc->sc_cfg2 = NCRCFG2_SCSI2 | NCRCFG2_FE;
	sc->sc_cfg3 = 0x08 /*FCLK*/ | NCRESPCFG3_FSCSI | NCRESPCFG3_CDB;
	sc->sc_rev = NCR_VARIANT_FAS216;

	/*
	 * This is the value used to start sync negotiations
	 * Note that the NCR register "SYNCTP" is programmed
	 * in "clocks per byte", and has a minimum value of 4.
	 * The SCSI period used in negotiation is one-fourth
	 * of the time (in nanoseconds) needed to transfer one byte.
	 * Since the chip's clock is given in MHz, we have the following
	 * formula: 4 * period = (1000 / freq) * 4
	 */
	sc->sc_minsync = 1000 / sc->sc_freq;

	/*
	 * get flags from -I argument and set cf_flags.
	 * NOTE: low 8 bits are to disable disconnect, and the next
	 *       8 bits are to disable sync.
	 */
	sc->sc_dev.dv_cfdata->cf_flags |= (scsi_nosync >> shift_nosync)
	    & 0xffff;
	shift_nosync += 16;

	/* Use next 16 bits of -I argument to set ncr53c9x_debug flags */
	ncr53c9x_debug |= (scsi_nosync >> shift_nosync) & 0xffff;
	shift_nosync += 16;

#if 1
	if (((scsi_nosync >> shift_nosync) & 0xff00) == 0xff00)
		sc->sc_minsync = 0;
#endif

	/* Really no limit, but since we want to fit into the TCR... */
	sc->sc_maxxfer = 64 * 1024;

	/*
	 * Configure interrupts.
	 */
	bsc->sc_isr.isr_intr = (int (*)(void *))ncr53c9x_intr;
	bsc->sc_isr.isr_arg  = sc;
	bsc->sc_isr.isr_ipl  = 2;
	add_isr(&bsc->sc_isr);

	/*
	 * Now try to attach all the sub-devices
	 */
	ncr53c9x_attach(sc, &bzivsc_switch, &bzivsc_dev);
}

/*
 * Glue functions.
 */

u_char
bzivsc_read_reg(sc, reg)
	struct ncr53c9x_softc *sc;
	int reg;
{
	struct bzivsc_softc *bsc = (struct bzivsc_softc *)sc;

	return bsc->sc_reg[reg * 4];
}

void
bzivsc_write_reg(sc, reg, val)
	struct ncr53c9x_softc *sc;
	int reg;
	u_char val;
{
	struct bzivsc_softc *bsc = (struct bzivsc_softc *)sc;
	u_char v = val;

	bsc->sc_reg[reg * 4] = v;
#ifdef DEBUG
if (bzivsc_trace_enable/* && sc->sc_nexus && sc->sc_nexus->xs->flags & SCSI_POLL*/ &&
  reg == NCR_CMD/* && bsc->sc_active*/) {
  bzivsc_trace[(bzivsc_trace_ptr - 1) & 127].yy = v;
/*  printf(" cmd %x", v);*/
}
#endif
}

int
bzivsc_dma_isintr(sc)
	struct ncr53c9x_softc *sc;
{
	struct bzivsc_softc *bsc = (struct bzivsc_softc *)sc;

	if ((bsc->sc_reg[NCR_STAT * 4] & NCRSTAT_INT) == 0)
		return 0;

#ifdef DEBUG
if (/*sc->sc_nexus && sc->sc_nexus->xs->flags & SCSI_POLL &&*/ bzivsc_trace_enable) {
  bzivsc_trace[bzivsc_trace_ptr].status = bsc->sc_reg[NCR_STAT * 4];
  bzivsc_trace[bzivsc_trace_ptr].xx = bsc->sc_reg[NCR_CMD * 4];
  bzivsc_trace[bzivsc_trace_ptr].yy = bsc->sc_active;
  bzivsc_trace_ptr = (bzivsc_trace_ptr + 1) & 127;
}
#endif
	return 1;
}

void
bzivsc_dma_reset(sc)
	struct ncr53c9x_softc *sc;
{
	struct bzivsc_softc *bsc = (struct bzivsc_softc *)sc;

	bsc->sc_active = 0;
}

int
bzivsc_dma_intr(sc)
	struct ncr53c9x_softc *sc;
{
	register struct bzivsc_softc *bsc = (struct bzivsc_softc *)sc;
	register int	cnt;

	NCR_DMA(("bzivsc_dma_intr: cnt %d int %x stat %x fifo %d ",
	    bsc->sc_dmasize, sc->sc_espintr, sc->sc_espstat,
	    bsc->sc_reg[NCR_FFLAG * 4] & NCRFIFO_FF));
	if (bsc->sc_active == 0) {
		printf("bzivsc_intr--inactive DMA\n");
		return -1;
	}

	/* update sc_dmaaddr and sc_pdmalen */
	cnt = bsc->sc_reg[NCR_TCL * 4];
	cnt += bsc->sc_reg[NCR_TCM * 4] << 8;
	cnt += bsc->sc_reg[NCR_TCH * 4] << 16;
	if (!bsc->sc_datain) {
		cnt += bsc->sc_reg[NCR_FFLAG * 4] & NCRFIFO_FF;
		bsc->sc_reg[NCR_CMD * 4] = NCRCMD_FLUSH;
	}
	cnt = bsc->sc_dmasize - cnt;	/* number of bytes transferred */
	NCR_DMA(("DMA xferred %d\n", cnt));
	if (bsc->sc_xfr_align) {
		bcopy(bsc->sc_alignbuf, *bsc->sc_dmaaddr, cnt);
		bsc->sc_xfr_align = 0;
	}
	*bsc->sc_dmaaddr += cnt;
	*bsc->sc_pdmalen -= cnt;
	bsc->sc_active = 0;
	return 0;
}

int
bzivsc_dma_setup(sc, addr, len, datain, dmasize)
	struct ncr53c9x_softc *sc;
	caddr_t *addr;
	size_t *len;
	int datain;
	size_t *dmasize;
{
	struct bzivsc_softc *bsc = (struct bzivsc_softc *)sc;
	vm_offset_t pa;
	u_char *ptr;
	size_t xfer;

	bsc->sc_dmaaddr = addr;
	bsc->sc_pdmalen = len;
	bsc->sc_datain = datain;
	bsc->sc_dmasize = *dmasize;
	/*
	 * DMA can be nasty for high-speed serial input, so limit the
	 * size of this DMA operation if the serial port is running at
	 * a high speed (higher than 19200 for now - should be adjusted
	 * based on cpu type and speed?).
	 * XXX - add serial speed check XXX
	 */
	if (ser_open_speed > 19200 && bzivsc_max_dma != 0 &&
	    bsc->sc_dmasize > bzivsc_max_dma)
		bsc->sc_dmasize = bzivsc_max_dma;
	ptr = *addr;			/* Kernel virtual address */
	pa = kvtop(ptr);		/* Physical address of DMA */
	xfer = min(bsc->sc_dmasize, NBPG - (pa & (NBPG - 1)));
	bsc->sc_xfr_align = 0;
	/*
	 * If output and unaligned, stuff odd byte into FIFO
	 */
	if (datain == 0 && (int)ptr & 1) {
		NCR_DMA(("bzivsc_dma_setup: align byte written to fifo\n"));
		pa++;
		xfer--;			/* XXXX CHECK THIS !!!! XXXX */
		bsc->sc_reg[NCR_FIFO * 4] = *ptr++;
	}
	/*
	 * If unaligned address, read unaligned bytes into alignment buffer
	 */
	else if ((int)ptr & 1) {
		pa = kvtop((caddr_t)&bsc->sc_alignbuf);
		xfer = bsc->sc_dmasize = min(xfer, sizeof (bsc->sc_alignbuf));
		NCR_DMA(("bzivsc_dma_setup: align read by %d bytes\n", xfer));
		bsc->sc_xfr_align = 1;
	}
++bzivsc_cnt_dma;		/* number of DMA operations */

	while (xfer < bsc->sc_dmasize) {
		if ((pa + xfer) != kvtop(*addr + xfer))
			break;
		if ((bsc->sc_dmasize - xfer) < NBPG)
			xfer = bsc->sc_dmasize;
		else
			xfer += NBPG;
++bzivsc_cnt_dma3;
	}
if (xfer != *len)
  ++bzivsc_cnt_dma2;

	bsc->sc_dmasize = xfer;
	*dmasize = bsc->sc_dmasize;
	bsc->sc_pa = pa;
#if defined(M68040) || defined(M68060)
	if (mmutype == MMU_68040) {
		if (bsc->sc_xfr_align) {
			dma_cachectl(bsc->sc_alignbuf,
			    sizeof(bsc->sc_alignbuf));
		}
		else
			dma_cachectl(*bsc->sc_dmaaddr, bsc->sc_dmasize);
	}
#endif

	pa >>= 1;
	if (!bsc->sc_datain)
		pa |= 0x80000000;
	bsc->sc_dmabase[0x8000] = (u_int8_t)(pa >> 24);
	bsc->sc_dmabase[0] = (u_int8_t)(pa >> 24);
	bsc->sc_dmabase[0] = (u_int8_t)(pa >> 16);
	bsc->sc_dmabase[0] = (u_int8_t)(pa >> 8);
	bsc->sc_dmabase[0] = (u_int8_t)(pa);
	bsc->sc_active = 1;
	return 0;
}

void
bzivsc_dma_go(sc)
	struct ncr53c9x_softc *sc;
{
}

void
bzivsc_dma_stop(sc)
	struct ncr53c9x_softc *sc;
{
}

int
bzivsc_dma_isactive(sc)
	struct ncr53c9x_softc *sc;
{
	struct bzivsc_softc *bsc = (struct bzivsc_softc *)sc;

	return bsc->sc_active;
}

#ifdef DEBUG
void
bzivsc_dump()
{
	int i;

	i = bzivsc_trace_ptr;
	printf("bzivsc_trace dump: ptr %x\n", bzivsc_trace_ptr);
	do {
		if (bzivsc_trace[i].hardbits == 0) {
			i = (i + 1) & 127;
			continue;
		}
		printf("%02x%02x%02x%02x(", bzivsc_trace[i].hardbits,
		    bzivsc_trace[i].status, bzivsc_trace[i].xx, bzivsc_trace[i].yy);
		if (bzivsc_trace[i].status & NCRSTAT_INT)
			printf("NCRINT/");
		if (bzivsc_trace[i].status & NCRSTAT_TC)
			printf("NCRTC/");
		switch(bzivsc_trace[i].status & NCRSTAT_PHASE) {
		case 0:
			printf("dataout"); break;
		case 1:
			printf("datain"); break;
		case 2:
			printf("cmdout"); break;
		case 3:
			printf("status"); break;
		case 6:
			printf("msgout"); break;
		case 7:
			printf("msgin"); break;
		default:
			printf("phase%d?", bzivsc_trace[i].status & NCRSTAT_PHASE);
		}
		printf(") ");
		i = (i + 1) & 127;
	} while (i != bzivsc_trace_ptr);
	printf("\n");
}
#endif
