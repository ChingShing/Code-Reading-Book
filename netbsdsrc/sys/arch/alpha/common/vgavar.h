/* $NetBSD: vgavar.h,v 1.3 1997/04/06 22:55:46 cgd Exp $ */

/*
 * Copyright (c) 1995, 1996 Carnegie-Mellon University.
 * All rights reserved.
 *
 * Author: Chris G. Demetriou
 * 
 * Permission to use, copy, modify and distribute this software and
 * its documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND 
 * FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 */

struct vga_config {
	/*
	 * Filled in by front-ends.
	 */
	bus_space_tag_t	vc_iot, vc_memt;
	bus_space_handle_t vc_ioh_b, vc_ioh_c, vc_ioh_d, vc_memh;

	/*
	 * Private to back-end.
	 */
	int		vc_ncol, vc_nrow; /* screen width & height */
	int		vc_ccol, vc_crow; /* current cursor position */

	char		vc_so;		/* in standout mode? */
	char		vc_at;		/* normal attributes */
	char		vc_so_at;	/* standout attributes */
};

int	vga_common_probe __P((bus_space_tag_t, bus_space_tag_t));
void	vga_common_setup __P((bus_space_tag_t, bus_space_tag_t,
	    struct vga_config *));
void	vga_wscons_attach __P((struct device *, struct vga_config *, int));
void	vga_wscons_console __P((struct vga_config *));
