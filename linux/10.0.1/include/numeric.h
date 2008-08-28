


/* Sccsid %Z% %M% %I% %G% */

/*
**	Sybase COMMON-LIBRARY Version 10.0
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1985, 1993
**	All rights reserved
**
**
** Use, duplication, or disclosure by the Government
** is subject to restrictions as set forth in subparagraph (c) (1) (ii)
** of the Rights in Technical Data and Computer Software clause
** at DFARS 52.227-7013. Sybase, Inc. 6475 Christie Avenue, Emeryville,
** CA 94608.
**
*/

/*
** NOTE: This file will be obsolete! Do not use or add any defines in this
**	 file. Do not add any additional dependancies on the current defines
**	 unless they are already being used. Any new defines should be added
**	 to comnblib.h instead of this one. 
**
** History
**      02/16/94 tchilder 62418, #defines referencing Nume_Flt_Power_Array,
**                      Nume_Flt_256_Array removed (see numearry.h for details)
**                      lines also shortened to meet 80 char standard
**
*/

#ifndef __NUMERIC_H__
#define __NUMERIC_H__

/* server: generic/include/numeric.h 60.1 8/17/92 */

/*
** numeric.h
**
** The following is split into two parts, the connectivity definitions,
** and the server defines that where present in the original numeric.h.
**
** The connectivity additions are an attempt to use the server source
** unmodified to allow for code sharing.
*/
#ifndef SERVER

/**************************************************************************
**
** connectivity additions
**
**************************************************************************/

#define IS_ASCII_SPACE(C)		com_isspace(C)

#endif /* SERVER */

#ifndef CONSTANT

/*
** NOTE: This typedef cloned out of /code2/prod_50/dbms/generic/include/trees.h
**	 on odin on 23 oct 91. Since NUMERIC is defined to be CONSTANT below
**	 we need it.
*/
typedef struct constant
{
       CS_INT		len;
       BYTE            	type;
       BYTE		rsrvdpad[3];
       CS_INT		maxlen;		
       BYTE		prec;
       BYTE		scale;
       BYTE	  	newtype;
       BYTE		conspare[7];
       short	       	constat;
       void		*locale;
       BYTE            	*value;		  /* ptr to value */
} __CONSTANT;

#define CONSTANT	__CONSTANT

#else /* CONSTANT */

#define __CONSTANT	CONSTANT

#endif /* CONSTANT */

/**************************************************************************
**
** original server defines, all unused stuff was stripped out
**
**************************************************************************/

/* 
**	@(#)	generic/includenumeric.h	51.3	7/8/92
**
** This file contains all the definitions for Numeric operations and
** conversions. It contains various macros used commonly for manipulating
** exact numerics. It also contains declarations for all functions which
** operate on exact numerics.
**
** This file replaces the old file mparith.h. All the defines used from that
** file are moved here.
**
** History:
**	Jan 24 1991 (manish) - written.
**	April 14 92 (prema)  - modified to reflect change in design.
*/

#define NUMERIC		CONSTANT

#define NUME_DEFDIVSCALE      6
#define NUME_MAXLEN     33
#define NUME_MINLEN     2
#define NUME_MAXPREC    77
#define NUME_USERPREC   38
#define NUME_MAXSCALE   77
#define NUME_DEFPREC    18
#define NUME_DEFSCALE   0
#define NUME_DEFLEN     9
#define NUME_MNYPREC    19
#define NUME_MNYSCALE   4
#define NUME_MNYLEN     9
#define NUME_MNYSIGNBYTE	0x80

/*
** Scale for result of built-ins on numerics to simulate
** floating point precision.
*/
#define	NUME_TO_FLT_SCALE	18

#define NUME_ILLEGAL_PRECVALUE	255
#define NUME_ILLEGAL_PREC(p)	((p > NUME_MAXPREC) || (p == 0))
#define NUME_ILLEGAL_SCALEVALUE	255
#define NUME_ILLEGAL_SCALE(s)	(s > NUME_MAXSCALE)

/*
** Defines from mparith.h
*/

# define	MAX_POS_OF(x)		(~(MAX_NEG_OF((x))))
# define	MAX_NEG_OF(x)		(1L << ((sizeof((x)) * 8) -1))
# define	SIGNBIT(a)		(((a)) & (MAX_NEG_OF((a))))
# define	SIGN_MISMATCH(a, b)  	((SIGNBIT((a))) != (SIGNBIT((b))))

#ifndef FETCHLONG
/*
** This Macro eliminates depending on whether the platform stores its
** bytes in MSB-first order (NORMLONG) or LSB-first order, however it only
** works if its arguments are longs, and longs are 4 bytes.
*/
#if NORMLONG
#define FETCHLONG(a, b) (b) = (a)
#else
#define FETCHLONG(a, b) b = (((a << 24) & 0xff000000L) | \
                             ((a << 8) & 0xff0000L) | \
                             ((a >> 8) & 0xff00L) | ((a >> 24) & 0xff))
#endif /* NORMLONG */
#endif /* FETCHLONG */


#define DIGIT			unsigned char
#define NUME_BASEBITS		8
#define NUME_BASEMINUSONE	255
#define NUME_BASE		256

#define	NUME_SIGN(val)		((val)->value[0]) 
#define	NUME_SETUPSIGN(num, signa)  if (signa) (num)->value[0] = 1; \
					       else (num)->value[0] = 0; 

#define	NUME_DIGIT_SETUPSIGN(num, signa) if (signa) (num)[0] = 1; \
							else (num)[0] = 0; 

#define	NUME_POSITIVE(a) 	((a)[0]  & 0x01 )
#define NUME_DIGITPART(d)	((d) & NUME_BASEMINUSONE)
#define NUME_CARRY(d)        	((unsigned) (d) >> NUME_BASEBITS)
#define NUME_ZEROOUT(r)		MEMZERO((r)->value, (r)->len)
#define NUME_SWAP(a,b)		{  NUMERIC *tmp; \
				   	tmp = (b); (b) = (a); (a) = tmp; \
					}
#define	NUME_NEGATE(a) 		if (*((a)->value)) \
						*((a)->value) = 0; \
					else\
						*((a)->value) = 1;

#define	NUME_CHECKSTAT(stat)	(stat)

/* Flag used by exctnume_scale to force scaling */
#define NUME_FORCECONV		0x1

#define NUME_ZERO(val)		(com__exctnume_intcmp((val), 0))
#define NUME_ONE(val)		(com__exctnume_intcmp((val), 1))
#define	NUME_ZEROBUFFER(bufptr,buflen) (!*((bufptr)+1) && ((buflen) == \
				NUME_MINLEN))
#define NUME_SETUP(val, valbuf, vallen)	(val)->value = (valbuf); \
						(val)->len   = (vallen);
/*
** NT and OS/2 have problems exporting data from DLL's. While we
** can get away with exporting data on NT, it is not clean. So,
** until we can come up with a better generic way of handling
** this problem, we sparse it out for these two platforms
*/
#if NT || OS2

/* NOTE: NUME_10TOPOWER_FLT and NUME_256TOPOWER are no longer referenced by
**	 Common-Lib code, and have been removed. (tchilder, 2/16/94)
*/
#define NUME_10TOPOWER_SETUP(powerval, scale) \
		{ \
			(powerval)->len = 		\
				(int) comb_get_Byte_Power_val(scale,0); \
			(powerval)->value = 		\
				(BYTE *) comb_get_Byte_Power_ptr(scale,1); \
		}

#define NUME_PRECFROMLEN(len)	((int)(comb_get_Len_To_Prec((len)-NUME_MINLEN)))
#define NUME_PRECTOLEN(prec)	((int)(comb_get_Prec_To_Len(prec)))

#else

#define NUME_10TOPOWER_SETUP(powerval, scale) \
		{ \
			(powerval)->len = 		\
				(int) Nume_Byte_Power_Array[(scale)][0]; \
			(powerval)->value = 		\
				(BYTE *) &Nume_Byte_Power_Array[(scale)][1]; \
		}

#define NUME_PRECFROMLEN(len)	((int) (Nume_Len_To_Prec[((len)-NUME_MINLEN)]))
#define NUME_PRECTOLEN(prec)	((int) (Nume_Prec_To_Len[(prec)]))

#endif /* NT || OS2 */

/* defines for exctnume_cmp */
# define	NUMECMP_DEFAULT		0	/* unsigned, same scale comp */
# define 	NUMECMP_SIGN		0x01	/* do a signed comp */
# define	NUMECMP_SCALE		0x02	/* scale the operands if necc */

# define	NUMECMP_EXACT		(NUMECMP_SIGN | NUMECMP_SCALE)

#define ADD_NUME(op1, op2, resultp, oflag) \
	(oflag = exctnume_addorsub(op1, op2, resultp, 0))
#define SUB_NUME(op1, op2, resultp, oflag) \
	(oflag = exctnume_addorsub(op1, op2, resultp, 1))
#define MUL_NUME(op1, op2, resultp, oflag) \
	(oflag = exctnume_mul(op1, op2, resultp))
#define DIV_NUME(op1, op2, resultp, oflag) \
	(oflag = exctnume_div(op1, op2, resultp, (NUMERIC *) NULL))


#endif /* __NUMERIC_H__ */
