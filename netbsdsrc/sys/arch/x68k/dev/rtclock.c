/*	$NetBSD: rtclock.c,v 1.3 1997/10/12 12:13:52 oki Exp $	*/

/*
 * Copyright 1993, 1994 Masaru Oki
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
 *      This product includes software developed by Masaru Oki.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * X680x0 internal real time clock interface
 * alarm is not supported.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/malloc.h>
#include <sys/proc.h>
#include <sys/reboot.h>
#include <sys/file.h>
#include <sys/kernel.h>

#include <x68k/dev/rtclock_var.h>
#include <x68k/x68k/iodevice.h>

static u_long rtgettod __P((void));
static int  rtsettod __P((long));

/*
 * x68k/clock.c calls thru this vector, if it is set, to read
 * the realtime clock.
 */
u_long (*gettod) __P((void));
int (*settod) __P((long));

static volatile union rtc *rtc_addr = 0;
int rtclockinit __P((void));

int
rtclockinit()
{
	rtc_addr = &IODEVbase->io_rtc;

	if (rtgettod())	{
		gettod = rtgettod;
		settod = rtsettod;
	} else {
		return 0;
	}
	return 1;
}

static int month_days[12] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static u_long
rtgettod()
{
	register int i;
	register u_long tmp;
	int year, month, day, hour, min, sec;

	/* hold clock */
	RTC_WRITE(rtc_addr, mode, RTC_HOLD_CLOCK);

	/* read it */
	sec   = RTC_REG(sec10)  * 10 + RTC_REG(sec);
	min   = RTC_REG(min10)  * 10 + RTC_REG(min);
	hour  = RTC_REG(hour10) * 10 + RTC_REG(hour);
	day   = RTC_REG(day10)  * 10 + RTC_REG(day);
	month = RTC_REG(mon10)  * 10 + RTC_REG(mon);
	year  = RTC_REG(year10) * 10 + RTC_REG(year)  + 1980;

	/* let it run again.. */
	RTC_WRITE(rtc_addr, mode, RTC_FREE_CLOCK);

	range_test(hour, 0, 23);
	range_test(day, 1, 31);
	range_test(month, 1, 12);
	range_test(year, STARTOFTIME, 2000);
  
	tmp = 0;

	for (i = STARTOFTIME; i < year; i++)
		tmp += days_in_year(i);
	if (leapyear(year) && month > FEBRUARY)
		tmp++;
  
	for (i = 1; i < month; i++)
		tmp += days_in_month(i);
  
	tmp += (day - 1);

	tmp = ((tmp * 24 + hour) * 60 + min + rtc_offset) * 60 + sec;
  
	return tmp;
}

static int
rtsettod (tim)
	long tim;
{
	/*
	 * I don't know if setting the clock is analogous
	 * to reading it, I don't have demo-code for setting.
	 * just give it a try..
	 */
	register int i;
	register long hms, day;
	u_char sec1, sec2;
	u_char min1, min2;
	u_char hour1, hour2;
	u_char day1, day2;
	u_char mon1, mon2;
	u_char year1, year2;

	/*
	 * there seem to be problems with the bitfield addressing
	 * currently used..
	 */
	if (!rtc_addr)
		return 0;

	tim -= (rtc_offset * 60);

	/* prepare values to be written to clock */
	day = tim / SECDAY;
	hms = tim % SECDAY;

	hour2 = hms / 3600;
	hour1 = hour2 / 10;
	hour2 %= 10;

	min2 = (hms % 3600) / 60;
	min1 = min2 / 10;
	min2 %= 10;

	sec2 = (hms % 3600) % 60;
	sec1 = sec2 / 10;
	sec2 %= 10;

	/* Number of years in days */
	for (i = STARTOFTIME - 1980; day >= days_in_year(i); i++)
		day -= days_in_year(i);
	year1 = i / 10;
	year2 = i % 10;

	/* Number of months in days left */
	if (leapyear(i))
		days_in_month(FEBRUARY) = 29;
	for (i = 1; day >= days_in_month(i); i++)
		day -= days_in_month(i);
	days_in_month(FEBRUARY) = 28;

	mon1 = i / 10;
	mon2 = i % 10;
  
	/* Days are what is left over (+1) from all that. */
	day ++;
	day1 = day / 10;
	day2 = day % 10;

	RTC_WRITE(rtc_addr, mode,   RTC_HOLD_CLOCK);
	RTC_WRITE(rtc_addr, sec10,  sec1);
	RTC_WRITE(rtc_addr, sec,    sec2);
	RTC_WRITE(rtc_addr, min10,  min1);
	RTC_WRITE(rtc_addr, min,    min2);
	RTC_WRITE(rtc_addr, hour10, hour1);
	RTC_WRITE(rtc_addr, hour,   hour2);
	RTC_WRITE(rtc_addr, day10,  day1);
	RTC_WRITE(rtc_addr, day,    day2);
	RTC_WRITE(rtc_addr, mon10,  mon1);
	RTC_WRITE(rtc_addr, mon,    mon2);
	RTC_WRITE(rtc_addr, year10, year1);
	RTC_WRITE(rtc_addr, year,   year2);
	RTC_WRITE(rtc_addr, mode,   RTC_FREE_CLOCK);

	return 1;
}
