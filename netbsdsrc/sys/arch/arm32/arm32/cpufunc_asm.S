/*	$NetBSD: cpufunc_asm.S,v 1.3 1997/10/14 10:07:34 mark Exp $	*/

/*
 * StrongARM alternating virtual memory region writeback code
 * (CACHE_CLEAN_VM) Copyright 1997 Digital Equipment Corporation.
 * All rights reserved.
 *
 * This software is furnished under license and may be used and
 * copied only in accordance with the following terms and conditions.
 * Subject to these conditions, you may download, copy, install,
 * use, modify and distribute this software in source and/or binary
 * form. No title or ownership is transferred hereby.
 *
 * 1) Any source code used, modified or distributed must reproduce
 *    and retain this copyright notice and list of conditions as
 *    they appear in the source file.
 *
 * 2) No right is granted to use any trade name, trademark, or logo of
 *    Digital Equipment Corporation. Neither the "Digital Equipment
 *    Corporation" name nor any trademark or logo of Digital Equipment
 *    Corporation may be used to endorse or promote products derived
 *    from this software without the prior written permission of
 *    Digital Equipment Corporation.
 *
 * 3) This software is provided "AS-IS" and any express or implied
 *    warranties, including but not limited to, any implied warranties
 *    of merchantability, fitness for a particular purpose, or
 *    non-infringement are disclaimed. In no event shall DIGITAL be
 *    liable for any damages whatsoever, and in particular, DIGITAL
 *    shall not be liable for special, indirect, consequential, or
 *    incidental damages or damages for lost profits, loss of
 *    revenue or loss of use, whether such damages arise in contract,
 *    negligence, tort, under statute, in equity, at law or otherwise,
 *    even if advised of the possibility of such damage.
 */

/*
 * arm8 support code Copyright (c) 1997 ARM Limited
 * arm8 support code Copyright (c) 1997 Causality Limited
 * Copyright (c) 1997 Mark Brinicombe.
 * Copyright (c) 1997 Causality Limited
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
 *	This product includes software developed by Causality Limited.
 * 4. The name of Causality Limited may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY CAUSALITY LIMITED ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL CAUSALITY LIMITED BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * RiscBSD kernel project
 *
 * cpufunc.S 
 *
 * Assembly functions for CPU / MMU / TLB specific operations
 *
 * Created      : 30/01/97
 */

#include <machine/vmparam.h>
#include <machine/cpu.h>
#include <machine/asm.h>

sp	.req	r13
lr	.req	r14
pc	.req	r15

	.text
	.align	0

/* hack from StrongARM god: if you write-back the data cache using alternating
   VM regions, you don't need to invalidate the cache after the write-back */
#ifdef CACHE_CLEAN_VM
Lcache_clean_vms:
	.word	_cache_clean_vms	
#endif

ENTRY(cpufunc_nullop)
	mov	pc, lr

/*
 * Generic functions to read the internal coprocessor registers
 *
 * Currently these registers are :
 *  c0 - CPU ID
 *  c5 - Fault status
 *  c6 - Fault address
 *
 */

ENTRY(cpufunc_id)
	mrc	15, 0, r0, c0, c0, 0
	mov	pc, lr

ENTRY(cpu_get_control)
	mrc	15, 0, r0, c1, c0, 0
	mov	pc, lr

ENTRY(cpufunc_faultstatus)
	mrc	15, 0, r0, c5, c0, 0
	mov	pc, lr

ENTRY(cpufunc_faultaddress)
	mrc	15, 0, r0, c6, c0, 0
	mov	pc, lr


/*
 * Generic functions to write the internal coprocessor registers
 *
 *
 * Currently these registers are 
 *  c1 - CPU Control
 *  c3 - Domain Access Control
 *
 * All other registers are CPU architecture specific
 */
 
/*ENTRY(cpufunc_control)
	mcr	15, 0, r0, c1, c0, 0
	mov	pc, lr*/

ENTRY(cpufunc_domains)
	mcr	15, 0, r0, c3, c0, 0
	mov	pc, lr

/*
 * Generic functions to read/modify/write the internal coprocessor registers
 *
 *
 * Currently these registers are 
 *  c1 - CPU Control
 *
 * All other registers are CPU architecture specific
 */
 
ENTRY(cpufunc_control)
	mrc	15, 0, r3, c1, c0, 0	/* Read the control register */
	bic	r2, r3, r0		/* Clear bits */
	eor     r2, r2, r1		/* XOR bits */

	mcr	15, 0, r2, c1, c0, 0	/* Write new control register */
	mov	r0, r3			/* Return old value */
	mov	pc, lr

#ifdef CPU_ARM8
ENTRY(arm8_clock_config)
	mrc	15, 0, r3, c15, c0, 0	/* Read the clock register */
	bic	r2, r3, #0x11		/* turn off dynamic clocking
					   and clear L bit */
	mcr	15, 0, r2, c15, c0, 0	/* Write clock register */

	bic	r2, r3, r0		/* Clear bits */
	eor     r2, r2, r1		/* XOR bits */
	bic	r2, r2, #0x10		/* clear the L bit */

	bic	r1, r2, #0x01		/* still keep dynamic clocking off */
	mcr	15, 0, r1, c15, c0, 0	/* Write clock register */
	mov	r0, r0			/* NOP */
	mov	r0, r0			/* NOP */
	mov	r0, r0			/* NOP */
	mov	r0, r0			/* NOP */
	mcr	15, 0, r2, c15, c0, 0	/* Write clock register */
	mov	r0, r3			/* Return old value */
	mov	pc, lr
#endif	/* CPU_ARM8 */

/*
 * Functions to set the MMU Translation Table Base register
 */

#if defined(CPU_ARM6) || defined(CPU_ARM7)
ENTRY(arm67_setttb)

/* We need to flush the cache as it uses virtual addresses that are about to change */
        mcr     15, 0, r0, c7, c0, 0

/* Write the TTB */
	mcr	15, 0, r0, c2, c0, 0

/* If we have updated the TTB we must flush the TLB */
        mcr     15, 0, r0, c5, c0, 0

/* For good measure we will flush the IDC as well */
        mcr     15, 0, r0, c7, c0, 0

/* Make sure that pipeline is emptied */
        mov     r0, r0
        mov     r0, r0

	mov	pc, lr
#endif	/* CPU_ARM6 || CPU_ARM7 */

#ifdef CPU_ARM8
ENTRY(arm8_setttb)
	/* We need to clean and flush the cache as it uses virtual
	 * addresses that are about to change
	 */
	mrs	r3, cpsr_all
	orr	r1, r3, #(I32_bit | F32_bit)
	msr	cpsr_all , r1

	stmfd	sp!, {r0-r3, lr}
	bl	_arm8_cache_cleanID
	ldmfd	sp!, {r0-r3, lr}
	mcr	15, 0, r0, c7, c7, 0		/* flush I+D cache */

	/* Write the TTB */
	mcr	15, 0, r0, c2, c0, 0

	/* If we have updated the TTB we must flush the TLB */
	mcr     15, 0, r0, c8, c7, 0

	/* For good measure we will flush the IDC as well */
	mcr     15, 0, r0, c7, c7, 0

	/* Make sure that pipeline is emptied */
	mov     r0, r0
	mov     r0, r0
	msr	cpsr_all , r3

	mov	pc, lr
#endif	/* CPU_ARM8 */


#ifdef CPU_SA110
ENTRY(sa110_setttb)
/* We need to flush the cache as it uses virtual addresses that are about to change */
#ifndef CACHE_CLEAN_VM
	mrs	r3, cpsr_all
	orr	r1, r3, #(I32_bit | F32_bit)
	msr	cpsr_all , r1
#endif
	stmfd	sp!, {r0-r3, lr}
	bl	_sa110_cache_cleanID
	ldmfd	sp!, {r0-r3, lr}
#ifdef CACHE_CLEAN_VM
	mcr	15, 0, r0, c7, c5, 0
#else
	mcr	15, 0, r0, c7, c7, 0
#endif
	mcr	15, 0, r0, c7, c10, 4

/* Write the TTB */
	mcr	15, 0, r0, c2, c0, 0

/* If we have updated the TTB we must flush the TLB */
        mcr     15, 0, r0, c8, c7, 0

#ifdef CACHE_CLEAN_VM
/* For good measure we will flush the IC as well */
        mcr     15, 0, r0, c7, c5, 0
#else
/* For good measure we will flush the IDC as well */
        mcr     15, 0, r0, c7, c7, 0
#endif

/* Make sure that pipeline is emptied */
        mov     r0, r0
        mov     r0, r0
#ifndef CACHE_CLEAN_VM
	msr	cpsr_all , r3
#endif
	mov	pc, lr
#endif	/* CPU_SA110 */

/*
 * TLB functions
 */

#if defined(CPU_ARM6) || defined(CPU_ARM7)
ENTRY(arm67_tlb_flush)
	mcr	15, 0, r0, c5, c0, 0
	mov	pc, r14

ENTRY(arm67_tlb_purge)
	mcr	15, 0, r0, c6, c0, 0
	mov	pc, lr
#endif	/* CPU_ARM6 || CPU_ARM7 */

#ifdef CPU_ARM8
ENTRY(arm8_tlb_flushID)
	mcr	15, 0, r0, c8, c7, 0		/* flush I+D tlb */
	mov	pc, lr

ENTRY(arm8_tlb_flushID_SE)
	mcr	15, 0, r0, c8, c7, 1		/* flush I+D tlb single entry */
	mov	pc, lr
#endif	/* CPU_ARM8 */

#ifdef CPU_SA110
ENTRY(sa110_tlb_flushID)
	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */ /* XXX */
	mcr	15, 0, r0, c8, c7, 0		/* flush I+D tlb */
	mov	pc, lr

ENTRY(sa110_tlb_flushID_SE)
	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */ /* XXX */
	mcr	15, 0, r0, c8, c6, 1		/* flush D tlb single entry */
	mcr	15, 0, r0, c8, c5, 0		/* flush I tlb */
	mov	pc, lr

ENTRY(sa110_tlb_flushI)
	mcr	15, 0, r0, c8, c5, 0		/* flush I tlb */
	mov	pc, lr

ENTRY(sa110_tlb_flushD)
	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */ /* XXX */
	mcr	15, 0, r0, c8, c6, 0		/* flush D tlb */
	mov	pc, lr

ENTRY(sa110_tlb_flushD_SE)
	mcr	15, 0, r0, c8, c6, 1		/* flush D tlb single entry */
	mov	pc, lr
#endif	/* CPU_SA110 */

/*
 * Cache functions
 */

#if defined(CPU_ARM6) || defined(CPU_ARM7)
ENTRY(arm67_cache_flush)
	mcr	15, 0, r0, c7, c0, 0
	mov	pc, lr
#endif	/* CPU_ARM6 || CPU_ARM7 */

#ifdef CPU_ARM8
ENTRY(arm8_cache_flushID)
	mcr	15, 0, r0, c7, c7, 0		/* flush I+D cache */
	mov	pc, lr

ENTRY(arm8_cache_flushID_E)
	mcr	15, 0, r0, c7, c7, 1		/* flush I+D single entry */
	mov	pc, lr

ENTRY(arm8_cache_cleanID)
	mov	r0, #0x00000000

Larm8_cache_cleanID_loop:
	mov	r2, r0
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1

	adds	r0, r0, #0x04000000
	bne	Larm8_cache_cleanID_loop

	mov	pc, lr

ENTRY(arm8_cache_cleanID_E)
	mcr	15, 0, r0, c7, c11, 1		/* clean ID single entry */
	mov	pc, lr

ENTRY(arm8_cache_purgeID)
	/*
	 * ARM810 bug 3
	 *
	 * Clean and invalidate entry will not invalidate the entry
	 * if the line was already clean. (mcr 15, 0, rd, c7, 15, 1)
	 *
	 * Instead of using the clean and invalidate entry operation
	 * use a separate clean and invalidate entry operations.
	 * i.e.
	 * mcr 15, 0, rd, c7, 11, 1
	 * mcr 15, 0, rd, c7, 7, 1
	 */

	mov	r0, #0x00000000

	mrs	r3, cpsr_all
	orr	r2, r3, #(I32_bit | F32_bit)
	msr	cpsr_all , r2

Larm8_cache_purgeID_loop:
	mov	r2, r0
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1
	add	r2, r2, #0x10
	mcr	15, 0, r2, c7, c11, 1
	mcr	15, 0, r2, c7, c7, 1

	adds	r0, r0, #0x04000000
	bne	Larm8_cache_purgeID_loop

	msr	cpsr_all, r3
	mov	pc, lr

ENTRY(arm8_cache_purgeID_E)
	/*
	 * ARM810 bug 3
	 *
	 * Clean and invalidate entry will not invalidate the entry
	 * if the line was already clean. (mcr 15, 0, rd, c7, 15, 1)
	 *
	 * Instead of using the clean and invalidate entry operation
	 * use a separate clean and invalidate entry operations.
	 * i.e.
	 * mcr 15, 0, rd, c7, 11, 1
	 * mcr 15, 0, rd, c7, 7, 1
	 */
	mrs	r3, cpsr_all
	orr	r2, r3, #(I32_bit | F32_bit)
	msr	cpsr_all , r2
	mcr	15, 0, r0, c7, c11, 1		/* clean ID single entry */
	mcr	15, 0, r0, c7, c7, 1		/* flush ID single entry */
	msr	cpsr_all , r3
	mov	pc, lr
#endif	/* CPU_ARM8 */

#ifdef CPU_SA110
ENTRY(sa110_cache_flushID)
	mcr	15, 0, r0, c7, c7, 0		/* flush I+D cache */
	mov	pc, lr

ENTRY(sa110_cache_flushI)
	mcr	15, 0, r0, c7, c5, 0		/* flush I cache */
	mov	pc, lr

ENTRY(sa110_cache_flushD)
	mcr	15, 0, r0, c7, c6, 0		/* flush D cache */
	mov	pc, lr

ENTRY(sa110_cache_flushD_SE)
	mcr	15, 0, r0, c7, c6, 1		/* flush D cache single entry */
	mov	pc, lr

ENTRY(sa110_cache_cleanD_E)
	mcr	15, 0, r0, c7, c10, 1		/* clean D cache entry */
	mov	pc, lr

/*
 * Information for SA110 cache clean/purge functions
 *
 * The address of the blocks of memory to use
 * The size of the block of memory to use
 */

	.data
	.global	_sa110_cache_clean_addr
_sa110_cache_clean_addr:
	.word	0xf0000000
	.global	_sa110_cache_clean_size
_sa110_cache_clean_size:
	.word	0x00008000

	.text
Lsa110_cache_clean_addr:
	.word	_sa110_cache_clean_addr
Lsa110_cache_clean_size:
	.word	_sa110_cache_clean_size

ENTRY(sa110_cache_cleanID)
ENTRY(sa110_cache_cleanD)

#ifdef CACHE_CLEAN_VM
	ldr	r2, Lcache_clean_vms
	ldr	r0, [r2]              /* current cache clean address */
	ldr	r1, [r2, #4]          /* last/next cache clean address */
	str	r1, [r2]              /* swap! */
	str	r0, [r2, #4]
	cmp	r0, #0
	movne	r1, #16384
	moveq	r0, #0xf0000000
	moveq	r1, #32768
#else
	mrs	r3, cpsr_all
	orr	r0, r3, #(I32_bit | F32_bit)
	msr	cpsr_all , r0
	ldr	r2, Lsa110_cache_clean_addr
	ldmia	r2, {r0, r1}
	eor	r0, r0, r1
	str	r0, [r2]
#endif

Lsa110_cache_cleanD_loop:
	ldr	r2, [r0], #32
	subs	r1, r1, #32
	bne	Lsa110_cache_cleanD_loop

	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */
#ifndef CACHE_CLEAN_VM
	msr	cpsr_all , r3
#endif

	mov	pc, lr	

ENTRY(sa110_cache_purgeID)

#ifdef CACHE_CLEAN_VM
	ldr	r2, Lcache_clean_vms
	ldr	r0, [r2]              /* current cache clean address */
	ldr	r1, [r2, #4]          /* last/next cache clean address */
	str	r1, [r2]              /* swap! */
	str	r0, [r2, #4]
	cmp	r0, #0
	movne	r1, #16384
	moveq	r0, #0xf0000000
	moveq	r1, #32768
#else
	mrs	r3, cpsr_all
	orr	r0, r3, #(I32_bit | F32_bit)
	msr	cpsr_all , r0
	ldr	r2, Lsa110_cache_clean_addr
	ldmia	r2, {r0, r1}
	eor	r0, r0, r1
	str	r0, [r2]
#endif

Lsa110_cache_purgeID_loop:
	ldr	r2, [r0], #32
	subs	r1, r1, #32
	bne	Lsa110_cache_purgeID_loop

	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */
#ifdef CACHE_CLEAN_VM
	mcr	15, 0, r0, c7, c5, 0		/* flush I cache */
#else
	mcr	15, 0, r0, c7, c7, 0		/* flush I+D cache */
	msr	cpsr_all , r3
#endif
	mov	pc, lr	

ENTRY(sa110_cache_purgeD)
#ifdef CACHE_CLEAN_VM
	ldr	r2, Lcache_clean_vms
	ldr	r0, [r2]              /* current cache clean address */
	ldr	r1, [r2, #4]          /* last/next cache clean address */
	str	r1, [r2]              /* swap! */
	str	r0, [r2, #4]
	cmp	r0, #0
	movne	r1, #16384
	moveq	r0, #0xf0000000
	moveq	r1, #32768
#else
	mrs	r3, cpsr_all
	orr	r0, r3, #(I32_bit | F32_bit)
	msr	cpsr_all , r0
	ldr	r2, Lsa110_cache_clean_addr
	ldmia	r2, {r0, r1}
	eor	r0, r0, r1
	str	r0, [r2]
#endif

Lsa110_cache_purgeD_loop:
	ldr	r2, [r0], #32
	subs	r1, r1, #32
	bne	Lsa110_cache_purgeD_loop

	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */
#ifndef CACHE_CLEAN_VM
	mcr	15, 0, r0, c7, c6, 0		/* flush D cache */
	msr	cpsr_all , r3
#endif
	mov	pc, lr	

ENTRY(sa110_cache_purgeID_E)
	mcr	15, 0, r0, c7, c10, 1		/* clean dcache entry */
	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */	
	mcr	15, 0, r0, c7, c5, 0		/* flush I cache */
	mcr	15, 0, r0, c7, c6, 1		/* flush D cache single entry */
	mov	pc, lr

ENTRY(sa110_cache_purgeD_E)
	mcr	15, 0, r0, c7, c10, 1		/* clean dcache entry */
	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */	
	mcr	15, 0, r0, c7, c6, 1		/* flush D cache single entry */
	mov	pc, lr
#endif	/* CPU_SA110 */

/*
 * Other functions
 */

#ifdef CPU_SA110
ENTRY(sa110_drain_writebuf)
	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */
	mov	pc, lr
#endif	/* CPU_SA110 */

/*
 * Soft functions
 */

#ifdef CPU_SA110
/*
 * These functions need to be written. Until then act on the whole cache
 */

ENTRY(sa110_cache_syncI)
#ifdef CACHE_CLEAN_VM
	ldr	r2, Lcache_clean_vms
	ldr	r0, [r2]              /* current cache clean address */
	ldr	r1, [r2, #4]          /* last/next cache clean address */
	str	r1, [r2]              /* swap! */
	str	r0, [r2, #4]
	cmp	r0, #0
	movne	r1, #16384
	moveq	r0, #0xf0000000
	moveq	r1, #32768
#else
	mrs	r3, cpsr_all
	orr	r0, r3, #(I32_bit | F32_bit)
	msr	cpsr_all , r0
	ldr	r2, Lsa110_cache_clean_addr
	ldmia	r2, {r0, r1}
	eor	r0, r0, r1
	str	r0, [r2]
#endif

Lsa110_cache_syncI_loop:
	ldr	r2, [r0], #32
	subs	r1, r1, #32
	bne	Lsa110_cache_syncI_loop

	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */
	mcr	15, 0, r0, c7, c5, 0		/* flush I cache */
#ifndef CACHE_CLEAN_VM
	msr	cpsr_all , r3
#endif
	mov	pc, lr	

ENTRY(sa110_cache_cleanID_rng)
ENTRY(sa110_cache_cleanD_rng)
	cmp	r1, #0x4000
	bgt	_sa110_cache_cleanID

	and	r2, r0, #0x1f
	add	r1, r1, r2
	bic	r0, r0, #0x1f

sa110_cache_cleanD_rng_loop:
	mcr	15, 0, r0, c7, c10, 1		/* clean D cache entry */
	add	r0, r0, #32
	subs	r1, r1, #32
	bpl	sa110_cache_cleanD_rng_loop

	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */

	mov	pc, lr

ENTRY(sa110_cache_purgeID_rng)
	cmp	r1, #0x4000
	bgt	_sa110_cache_purgeID

	and	r2, r0, #0x1f
	add	r1, r1, r2
	bic	r0, r0, #0x1f

sa110_cache_purgeID_rng_loop:
	mcr	15, 0, r0, c7, c10, 1		/* clean D cache entry */
	mcr	15, 0, r0, c7, c6, 1		/* flush D cache single entry */
	add	r0, r0, #32
	subs	r1, r1, #32
	bpl	sa110_cache_purgeID_rng_loop

	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */
	mcr	15, 0, r0, c7, c5, 0		/* flush I cache */

	mov	pc, lr

ENTRY(sa110_cache_purgeD_rng)
	cmp	r1, #0x4000
	bgt	_sa110_cache_purgeD

	and	r2, r0, #0x1f
	add	r1, r1, r2
	bic	r0, r0, #0x1f

sa110_cache_purgeD_rng_loop:
	mcr	15, 0, r0, c7, c10, 1		/* clean D cache entry */
	mcr	15, 0, r0, c7, c6, 1		/* flush D cache single entry */
	add	r0, r0, #32
	subs	r1, r1, #32
	bpl	sa110_cache_purgeD_rng_loop

	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */

	mov	pc, lr

ENTRY(sa110_cache_syncI_rng)
	cmp	r1, #0x4000
	bgt	_sa110_cache_syncI

	and	r2, r0, #0x1f
	add	r1, r1, r2
	bic	r0, r0, #0x1f

sa110_cache_syncI_rng_loop:
	mcr	15, 0, r0, c7, c10, 1		/* clean D cache entry */
	add	r0, r0, #32
	subs	r1, r1, #32
	bpl	sa110_cache_syncI_rng_loop

	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */
	mcr	15, 0, r0, c7, c5, 0		/* flush I cache */

	mov	pc, lr
#endif	/* CPU_SA110 */

/*
 * *_context_switch()
 *
 * These are CPU specific parts of the context switcher cpu_switch()
 * These functions actually perform the TTB reload.
 *
 * NOTE: Special calling convention
 *       r1, r4-r13 must be preserved
 */

#if defined(CPU_ARM6) || defined(CPU_ARM7)
ENTRY(arm67_context_switch)
	/* Switch the memory to the new process */

	/* For good measure we will flush the IDC as well */
        mcr     15, 0, r0, c7, c0, 0		/* flush cache */

	/* Write the TTB */
        mcr     15, 0, r0, c2, c0, 0

	/* If we have updated the TTB we must flush the TLB */
        mcr     15, 0, r0, c5, c0, 0

	/* For good measure we will flush the IDC as well */
        mcr     15, 0, r0, c7, c0, 0

	/* Make sure that pipeline is emptied */
        mov     r0, r0
        mov     r0, r0
        mov     pc, r14
#endif

#ifdef CPU_ARM8
ENTRY(arm8_context_switch)
	/* Switch the memory to the new process */

	/* For good measure we will flush the IDC as well */
	mcr	15, 0, r0, c7, c7, 0		/* flush i+d cache */

	/* Write the TTB */
        mcr     15, 0, r0, c2, c0, 0

	/* If we have updated the TTB we must flush the TLB */
        mcr     15, 0, r0, c8, c7, 0		/* flush the i+d tlb */

	/* For good measure we will flush the IDC as well */	
        mcr     15, 0, r0, c7, c7, 0		/* flush the i+d cache */

	/* Make sure that pipeline is emptied */
        mov     r0, r0
        mov     r0, r0
        mov     pc, r14
#endif	/* CPU_ARM8 */

#ifdef CPU_SA110
ENTRY(sa110_context_switch)
	/* Switch the memory to the new process */

	/* For good measure we will flush the IDC as well */
	mcr	15, 0, r0, c7, c10, 4		/* drain write buffer */
#ifdef CACHE_CLEAN_VM
	mcr	15, 0, r0, c7, c5, 0		/* flush i cache */
#else
	mcr	15, 0, r0, c7, c7, 0		/* flush i+d cache */
#endif

	/* Write the TTB */
        mcr     15, 0, r0, c2, c0, 0

	/* If we have updated the TTB we must flush the TLB */
        mcr     15, 0, r0, c8, c7, 0		/* flush the i+d tlb */

#ifdef CACHE_CLEAN_VM
	/* For good measure we will flush the IC as well */	
        mcr     15, 0, r0, c7, c5, 0		/* flush the i cache */
#else
	/* For good measure we will flush the IDC as well */	
        mcr     15, 0, r0, c7, c7, 0		/* flush the i+d cache */
#endif

	/* Make sure that pipeline is emptied */
        mov     r0, r0
        mov     r0, r0
        mov     pc, r14
#endif

/*
 * other potentially useful software functions are:
 *  clean D cache entry and flush I cache entry
 *   for the moment use cache_purgeID_E
 */
