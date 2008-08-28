
/* Sccsid %Z% %M% %I% %G% */

/*
**	Sybase COMMON-LIBRARY Version 10.0
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1985, 1993
**	All rights reserved
**
** Use, duplication, or disclosure by the Government
** is subject to restrictions as set forth in subparagraph (c) (1) (ii)
** of the Rights in Technical Data and Computer Software clause
** at DFARS 52.227-7013. Sybase, Inc. 6475 Christie Avenue, Emeryville,
** CA 94608.
*/

/*
** NOTE: This file will be obsolete! Do not use or add any defines in this
**	 file. Do not add any additional dependancies on the current defines
**	 unless they are already being used. Any new defines should be added
**	 to comnblib.h instead of this one. 
*/

/* server: generic/cinclude/datetime.h 52.1 8/13/92 */

#ifndef	__datetime__
#define __datetime__

#ifdef SERVER

/*
** NOTE: The following defines are also defined as COM_DATE_* defines. The
**	 re-definitions (currently in datetime.h) should be moved into
**	 comnblib.h and these defines removed.
*/

/*  Define the parts of a date. */
#define DPYEAR		0
#define DPQUARTER	1
#define DPMONTH		2
#define DPWEEKDAY	3
#define DPDAY		4
#define DPDAYOFYEAR	5
#define DPHOUR		6
#define	DPMINUTE	7
#define DPSECOND	8
#define DPMSECOND	9
#define DPWEEK		10

#endif /* SERVER */
/*
** The following three definitions are needed for ISO 8601 : 1988
** support. They are NOT parts of a date, they are used as case
** clause labels in datepart().
*/
#define DPCALYEAR       11
#define DPCALWEEK       12
#define DPCALDAY        13


/* commonly used constants */
# define C300TH_P_HOUR		1080000L        /*  60*60*300      */
# define C300TH_P_DAY		25920000L       /*  24*60*60*300   */
# define C300TH_P_MIN		18000L          /*  60*300         */
# define C300TH_P_SEC		300L            /*  300            */
# define MS_P_DAY		86400000L       /*  24*60*60*1000  */
# define SEC_P_HOUR		3600L           /*  60*60          */
# define SEC_P_DAY		86400L          /*  60*60*24       */
# define MIN_P_DAY		1440L           /*  60*24          */

#define TIMEMASK	0x01ffffff

# define MAXDATEPARTNAME 30	/* max chars in date part string */

/* DATETOCHAR style codes */
# define DATES_SHORT		0		/*  default	*/
# define DATES_MDY1		1		/*  mm/dd/yy	*/
# define DATES_YMD1		2		/*  yy.mm.dd	*/
# define DATES_DMY1		3		/*  dd/mm/yy	*/
# define DATES_DMY2		4		/*  dd.mm.yy	*/
# define DATES_DMY3		5		/*  dd-mm-yy	*/
# define DATES_DMY4		6		/*  dd mon yy	*/
# define DATES_MDY2		7		/*  mon dd, yy	*/
# define DATES_HMS		8		/*  hh:mm:ss	*/
# define DATES_LONG		9		/*  default with micro secs */
# define DATES_MDY3		10		/*  mm-dd-yy	*/
# define DATES_YMD2		11		/*  yy/mm/dd	*/
# define DATES_YMD3		12		/*  yymmdd	*/
# define DATES_YDM1		13		/*  yy/dd/mm	*/
# define DATES_MYD1		14		/*  mm/yy/dd	*/
# define DATES_DYM1		15		/*  dd/yy/mm	*/
# define DATES_SHORT_ALT	100		/*  default	*/
# define DATES_MDY1_YYYY	101		/*  mm/dd/yyyy	*/
# define DATES_YMD1_YYYY	102		/*  yyyy.mm.dd	*/
# define DATES_DMY1_YYYY	103		/*  dd/mm/yyyy	*/
# define DATES_DMY2_YYYY	104		/*  dd.mm.yyyy	*/
# define DATES_DMY3_YYYY	105		/*  dd-mm-yyyy  */
# define DATES_DMY4_YYYY	106		/*  dd mon yyyy	*/
# define DATES_MDY2_YYYY	107		/*  mon dd, yyyy*/
# define DATES_HMS_ALT		108		/*  hh:mm:ss	*/
# define DATES_LONG_ALT		109		/*  default with micro secs */
# define DATES_MDY3_YYYY	110		/*  mm-dd-yyyy	*/
# define DATES_YMD2_YYYY	111		/*  yyyy/mm/dd	*/
# define DATES_YMD3_YYYY	112		/*  yyyymmdd	*/
#ifdef SERVER
# define DATES_ERRLOG		200		/*  yy/mm/dd hh:mm:ss.xx*/
#endif /* SERVER */

/* Internal date order codes for all-numeric dates. */
# define	DTFMT_MDY	1	/* mm/dd/yy */
# define	DTFMT_DMY	2	/* dd/mm/yy */
# define	DTFMT_YMD	3	/* yy/mm/dd */
# define	DTFMT_YDM	4	/* yy/dd/mm */
# define	DTFMT_MYD	5	/* mm/yy/dd */
# define	DTFMT_DYM	6	/* dd/yy/mm */

/* First-day-of-week values range from 1-7, for Monday through Sunday,
** respectively.  It indicates which day of the week the user considers
** to be "first".
*/
# define	DTFIRST_MONDAY	1	/* minimum: Monday is considered
					** first day of week
					*/
# define	DTFIRST_SUNDAY	7	/* maximum, and US default:
					** Sunday is first day of week
					*/

/* Test to see if a given year is a leap year. */
#define LEAP(y) ((int) (!((y)%4)&&((y)%100)||!((y)%400)))

/*
** The following structure is used to determine
** the month and day of the month from the julian day.
*/
struct monthcnt
{
	short	daysinmonth;
	short	daysum;
};

#endif /* __datetime__ */

