

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
*/

/*	server: generic/include/money.h 60.1 8/17/92 */

/*
** MONEY.H
**
** Contents:
**
**	- Implementation constants and macros for money arithmetic.
**
** History:
**
**	08Sep89 (mcfong) - Written.
**	18Sep89 (mcfong) - Add "#include" guards.  Change "struct mony" to
**		"struct money" to remian compatible with backend code.
*/

#ifndef __MONEY_H__
#define __MONEY_H__

/*
** Structure assignment macros for MONY (DBMONEY).
**
** If structure assignment is not allowed, expand the macro to assign each
** field explicitly.  Because we are dealing with a small number of
** fields, this is faster than making a function call to a memory copy
** routine.  Support is harder because we have to change the macros each
** time we change the structure.  At least the macros and structure
** declarations are localized to this file.
*/

# define MNYZERO(m)	((m)->mnyhigh = 0, (m)->mnylow = 0)

# if STRCT_ASSN_OK
# define MNYSTRUCTASSIGN(a,b)	((b) = (a))
# else	/* !STRCT_ASSN_OK */
# define MNYSTRUCTASSIGN(a,b)	((b).mnyhigh = (a).mnyhigh, \
				(b).mnylow = (a).mnylow)
# endif	/* !STRCT_ASSN_OK */

# define MNY_RADIX	10	/* Money works in base 10		*/
# define MNY_SCALE	4	/* Count of internal decimal digits	*/
# define MNY_POWER	10000	/* 1e4 (money scale as an integer)	*/
# define MNY_PRECISION	2	/* Count of displayed decimal digits	*/
# define MNY_ROUND_K	(MNY_POWER / 2) /* Cutoff for rounding	*/

/*
** MONEYHIGH is placed here so we don't have to duplicate it in
** "moneycnvt.c" and "mony4cnvt.c".  "mony4cnvt.c" is found only in
** the Babel code lines but "money.h" is shared with all code lines.
*/

# define MONEYHIGH	429496.7296	/* Upper part of money base value */

/* MNY_VAL_HIGH and MNY_VAL_LOW together represent the values equal 
** to $92233720368547.7580
*/

#define MNY_VAL_HIGH ~0xf3333333

#define MNY_VAL_LOW  ~0x33333333

#ifdef	SERVER

/* Defines for money operations used in run.c 	************************/

#define ADD_MONY(op1, op2, resultp, oflag) \
        (oflag = mnyadd((MONY *) (op1), (MONY *) (op2), (MONY *) (resultp)))

#define SUB_MONY(op1, op2, resultp, oflag) \
        (oflag = mnysub((MONY *) (op1), (MONY *) (op2), (MONY *) (resultp)))
 
#define MUL_MONY(op1, op2, resultp, oflag) \
        (oflag = mnymul((MONY *) (op1), (MONY *) (op2), (MONY *) (resultp)))

#define DIV_MONY(op1, op2, resultp, oflag) \
        (oflag = mnydiv((MONY *) (op1), (MONY *) (op2), (MONY *) (resultp)))

#define MOD_MONY(op1, op2, resultp, oflag) \
        (oflag = mnyrem((MONY *) (op1), (MONY *) (op2), (MONY *) (resultp)))
 
#define NEG_MONY(op1, resultp, oflag) \
        (oflag = mnyminus((MONY *) (op1), (MONY *) (resultp)))
 
#define ADD_MONY4(op1, op2, resultp, oflag) \
        (oflag = mnyadd4((MONY4 *) (op1), (MONY4 *) (op2), (MONY4 *) (resultp)))
 
#define SUB_MONY4(op1, op2, resultp, oflag) \
        (oflag = mnysub4((MONY4 *) (op1), (MONY4 *) (op2), (MONY4 *) (resultp)))
 
#define MUL_MONY4(op1, op2, resultp, oflag) \
        (oflag = mnymul4((MONY4 *) (op1), (MONY4 *) (op2), (MONY4 *) (resultp)))
 
#define DIV_MONY4(op1, op2, resultp, oflag) \
        (oflag = mnydiv4((MONY4 *) (op1), (MONY4 *) (op2), (MONY4 *) (resultp)))
 
#define MOD_MONY4(op1, op2, resultp, oflag) \
        (oflag = mnyrem4((MONY4 *) (op1), (MONY4 *) (op2), (MONY4 *) (resultp)))
 
#define NEG_MONY4(op1, resultp, oflag) \
        (oflag = mnyminus4((MONY4 *) (op1), (MONY4 *) (resultp)))
 
/*********************************************************************/

#endif	/* SERVER */

#endif /* __MONEY_H__ */
