/*	$NetBSD: fpgetsticky.c,v 1.2 1996/09/16 18:10:47 jonathan Exp $	*/

/*
 * Written by J.T. Conklin, Apr 11, 1995
 * Public domain.
 */

#include <ieeefp.h>

fp_except
fpgetsticky()
{
	int x;

	__asm__("cfc1 %0,$31" : "=r" (x));
	return (x >> 2) & 0x1f;
}
