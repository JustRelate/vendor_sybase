
/* Sccsid %Z% %M% %I% %G% */

/*
**	Sybase COMMON-LIBRARY Version 10.0
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1991, 1993
**	All rights reserved
**
**  COMNBLIB.H
**
**	Header file for "base" Common-Lib routines. These routines will be
**	shared with the server and connectivity groups.
**
**	In deference to the server coding convention of not having include
**	file within include files, this file does not include the other needed 
**	connectivity files. To use this file, the following is (currently)
**	required:
**
**		#include <comnlib.h>
**		#include <intl_nls.h>
**		#include <csgen.h>
**		#include <numeric.h>
**
**	This header file contains:
**		a) type definitions for the Shared datatypes;
**		b) external definitions for Common-Lib routines
**
*/

#ifndef	__COMNBLIB_H__
#define __COMNBLIB_H__


/*
** NOTE NOTE NOTE NOTE NOTE
**
**   Routines defined in this files are only available to in house 
** products that are linked (not distributed in library form) or 
** are part of the OpenClient libraries.
**
*/

/*
** NOTE: Currently, external users are also including the following headers:
**
**		datetime.h
**		numeric.h
**		money.h
**
**	Eventually, the definitions within these files should be cleaned up,
**	and any externally needed defines and data structures moved here. 
*/

/***************************************************************************
**
** Structure Definitions
**
***************************************************************************/

typedef struct _castcontext
{
    CsConvertTbl ctxcvttbl;
    CS_INT	format;	       /* the format of the data (i.e. blank padded) */
    CS_INT	style;	       /* Display format style information. */
    CS_INT	flags;	       /* context descriptive flags
			       **	0x0 UNDEFINED
			       */
    CS_CHAR	**months;      /* */
    CS_CHAR	**shrtmonths;  /* */
    CS_INT	dateorder;     /* */
    CHAR_ATTRIB	*char_attrib;  /* */
    CS_CONV_FUNC cfn;	       /* */
    
} CastContext;
typedef struct _castcontext	CAST_CONTEXT;



/* size of octet/octetgroups in bytes */

#define OCTETSIZE     1
#define DOCTETSIZE    2
#define QOCTETSIZE    4
#define OOCTETSIZE    8

typedef unsigned char DOCTET[DOCTETSIZE]; /* double octets */
typedef unsigned char QOCTET[QOCTETSIZE]; /* quadruple octets */
typedef unsigned char OOCTET[OOCTETSIZE]; /* 8 octets */
typedef unsigned char OCTET;


/***************************************************************************
**
** External declarations of Common-Lib API routines
**
***************************************************************************/

CS_START_EXTERN_C

/* Routines in compriv.h added here again from the PC Server group */
extern int CS_PUBLIC com__mnyminus PROTOTYPE((
	CS_MONEY *imp,
	CS_MONEY *omp
	));
extern int CS_PUBLIC com__mnyadd PROTOTYPE((
	CS_MONEY *add1p,
	CS_MONEY *add2p,
	CS_MONEY *sump
	));
extern int CS_PUBLIC com__mnysub PROTOTYPE((
	CS_MONEY *minp,
	CS_MONEY *subp,
	CS_MONEY *difp
	));
extern int CS_PUBLIC com__mnydiv PROTOTYPE((
	CS_MONEY *m1,
	CS_MONEY *m2,
	CS_MONEY *m3
	));
extern int CS_PUBLIC com__mnymul PROTOTYPE((
	CS_MONEY *m1,
	CS_MONEY *m2,
	CS_MONEY *m3
	));
extern int CS_PUBLIC com__mnyrem PROTOTYPE((
	CS_MONEY *dvddp,
	CS_MONEY *dvsrp,
	CS_MONEY *rmp
	));
extern int  CS_PUBLIC com__mnyminus4 PROTOTYPE((
	CS_MONEY4 *imp,
	CS_MONEY4 *omp
	));
extern int  CS_PUBLIC com__mnyadd4 PROTOTYPE((
	CS_MONEY4 *add1p,
	CS_MONEY4 *add2p,
	CS_MONEY4 *sump
	));
extern int CS_PUBLIC com__mnysub4 PROTOTYPE((
	CS_MONEY4 *minp,
	CS_MONEY4 *subp,
	CS_MONEY4 *difp
	));
extern int CS_PUBLIC com__mnydiv4 PROTOTYPE((
	CS_MONEY4 *m1,
	CS_MONEY4 *m2,
	CS_MONEY4 *m3
	));
extern int CS_PUBLIC com__mnymul4 PROTOTYPE((
	CS_MONEY4 *m1,
	CS_MONEY4 *m2,
	CS_MONEY4 *m3
	));
extern int CS_PUBLIC com__mnyrem4 PROTOTYPE((
	CS_MONEY4 *dvddp,
	CS_MONEY4 *dvsrp,
	CS_MONEY4 *rmp
	));
extern char * CS_PUBLIC com__mnytochar PROTOTYPE((
	CS_MONEY *mp,
	char *cp,
	int len,
	int style
	));
extern int CS_PUBLIC com__mnyfromchar_mb PROTOTYPE((
	CS_MONEY *mp,
	char *icp,
	int ilen,
	int style,
	CS_ATTRIB *chatr
	));
extern void  CS_PUBLIC com__mny4tomny PROTOTYPE((
	CS_MONEY4 *m4p,
	CS_MONEY *mp
	));
extern char * CS_PUBLIC com__mny4tochar PROTOTYPE((
	CS_MONEY4 *m4p,
	char *cp,
	int len,
	int style
	));

/* com_glbl.c */
extern CS_CHAR ** CS_PUBLIC com__get_ampm PROTOTYPE((void));
extern CS_CHAR ** CS_PUBLIC com__get_weekdays PROTOTYPE((void));
extern CS_CHAR ** CS_PUBLIC com__get_months PROTOTYPE((void));
extern CS_CHAR ** CS_PUBLIC com__get_shortmonths PROTOTYPE((void));
extern CS_CHAR ** CS_PUBLIC com__get_days PROTOTYPE((void));
extern CS_INT CS_PUBLIC com__get_firstday PROTOTYPE((void));
extern CS_CHAR * CS_PUBLIC com__get_date_order PROTOTYPE((void));
extern int CS_PUBLIC com__get_date_order_id PROTOTYPE((void));

/* datetime.c */
extern int CS_PUBLIC com__datetochar PROTOTYPE((
	CS_DATETIME *dtp,
	char *buf,
	int len,
	int style,
	char **shortmths
	));
extern int CS_PUBLIC com__leapcnt PROTOTYPE((
	int year
	));
extern void CS_PUBLIC com__datecrack PROTOTYPE((
	CS_DATETIME *dtp,
	CS_DATEREC *pp
	));
extern void CS_PUBLIC com__timecrack PROTOTYPE((
	CS_DATETIME *dtp,
	CS_DATEREC *pp
	));
extern int CS_PUBLIC com__cpint PROTOTYPE((
	char *cp,
	int value,
	int padchar,
	int len
	));
extern int CS_PUBLIC com__cpchar PROTOTYPE((
	char *cp,
	char *str,
	int padchar,
	int maxlen
	));
extern int CS_PUBLIC com__datediff PROTOTYPE((
	int part,
	CS_DATETIME *from,
	CS_DATETIME *to,
	CS_INT *diff
	));
extern int CS_PUBLIC com__date_add PROTOTYPE((
	int part,
	CS_INT value,
	CS_DATETIME *to
	));
extern int CS_PUBLIC com__datename PROTOTYPE((
	int part,
	CS_DATETIME *dtp,
	char *cp,
	char **months,
	char **days
	));
extern int CS_PUBLIC com__datepart PROTOTYPE((
	int part,
	CS_DATETIME *to,
	int firstday
	));
extern int CS_PUBLIC com__timemake PROTOTYPE((
	CS_DATETIME *dtp,
	CS_DATEREC *pp
	));
extern int CS_PUBLIC com__datemake PROTOTYPE((
	CS_DATETIME *dtp,
	CS_DATEREC *pp
	));
extern int CS_PUBLIC com__itochar PROTOTYPE((
	CS_INT val,
	char *buf,
	int len
	));
extern int CS_PUBLIC com__chtoi1_mb PROTOTYPE((
	char *cp,
	int len,
	CS_BYTE *valp,
	CS_ATTRIB *chatr
	));
extern int CS_PUBLIC com__chtoi2_mb PROTOTYPE((
	char *cp,
	int len,
	short *valp,
	CS_ATTRIB *chatr
	));
extern int CS_PUBLIC com__chtoi4_mb PROTOTYPE((
	char *cp,
	int len,
	CS_INT *valp,
	CS_ATTRIB *chatr
	));
extern int CS_INTERNAL com__chtoi8_mb PROTOTYPE((
	char *cp,
	int len,
	long *valp,
	CS_ATTRIB *chatr
	));
extern int CS_PUBLIC com__datefromchar_mb PROTOTYPE((
	CS_DATETIME *dtp,
	char *origcp,
	int origlen,
	int style,
	int order,
	char **mths,
	char **shortmths,
	CS_ATTRIB *chatr
	));
extern int CS_PUBLIC com__timefromchar_mb PROTOTYPE((
	CS_DATETIME *dtp,
	char *origcp,
	int origlen,
	int style,
	CS_ATTRIB *chatr
	));
extern int CS_PUBLIC com__amcheck PROTOTYPE((
	CS_DATEREC *pp,
	int pmflag
	));
extern int CS_PUBLIC com__year2digit PROTOTYPE((
	int year
	));
extern int CS_PUBLIC com__datecmp PROTOTYPE((
	CS_DATETIME *date1,
	CS_DATETIME *date2
	));
extern int CS_PUBLIC com__date4fromchar_mb PROTOTYPE((
	CS_DATETIME4 *dtp4,
	char *origcp,
	int origlen,
	int style,
	int order,
	char **mths,
	char **shortmths,
	CS_ATTRIB *chatr
	));
extern int CS_PUBLIC com__dttodate4 PROTOTYPE((
	CS_DATETIME *dtp,
	CS_DATETIME4 *dtp4
	));
extern void CS_PUBLIC com__date4todt PROTOTYPE((
	CS_DATETIME4 *dtp4,
	CS_DATETIME *dtp
	));
extern int CS_PUBLIC com__date4tochar PROTOTYPE((
	CS_DATETIME4 *dtp4,
	char *buf,
	int len,
	int style,
	char **shortmths
	));
extern int CS_PUBLIC com__dateadd_both PROTOTYPE((
	int part,
	CS_INT value,
	CONSTANT *src,
	CONSTANT *result
	));
extern int CS_PUBLIC com__valid_datetime PROTOTYPE((
	CONSTANT *src,
	CS_BYTE *cast_buf
	));

/* bnewutls_bin.c */
extern CS_RETCODE CS_PUBLIC comnb__padchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb__padbin PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *dest
	));

/* bc_bin.c */
extern CS_RETCODE CS_PUBLIC comnb_anytofixed PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_anytovar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_bintobit PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_bintodate PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_bintonum PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_bit.c */
extern CS_RETCODE CS_PUBLIC comnb_bittobit PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_bittoi1 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_bittoi2 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_bittoi4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_bittoflt4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_bittoflt8 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_bittomny4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_bittomoney PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_bittonum PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_bittochar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_bittovarchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_char.c */
extern CS_RETCODE CS_PUBLIC comnb_chartobit PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_chartoi1 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_chartoi2 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_chartoi4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_chartoflt4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_chartoflt8 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_chartonum PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_chartodate4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_chartodatetime PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_chartomny4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_chartomoney PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_chartochar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_chartovarchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_dat4.c */
extern CS_RETCODE CS_PUBLIC comnb_date4todate4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_date4todate PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_date4tochar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_date4tovarchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_date4tobin PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_date4tovarbin PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_date.c */
extern CS_RETCODE CS_PUBLIC comnb_datetodate4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_datetodate PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_datetochar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_datetovarchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_flt4.c */
extern CS_RETCODE CS_PUBLIC comnb_flt4tobit PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt4toi1 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt4toi2 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt4toi4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt4toflt4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt4toflt8 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt4tonum PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt4tomny4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt4tomoney PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt4tochar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt4tovarchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt4tobin PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt4tovarbin PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_flt8.c */
extern CS_RETCODE CS_PUBLIC comnb_flt8tobit PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt8toi1 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt8toi2 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt8toi4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt8toflt4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt8toflt8 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt8tonum PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt8tomny4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt8tomoney PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt8tochar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt8tovarchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt8tobin PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_flt8tovarbin PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_hex.c */
extern CS_RETCODE CS_PUBLIC comnb_i4tohex PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_hextoi4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_i1.c */
extern CS_RETCODE CS_PUBLIC comnb_i1tobit PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i1toi1 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i1toi2 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i1toi4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i1toflt4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i1toflt8 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i1tonum PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i1tomny4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i1tomoney PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i1tochar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i1tovarchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_i2.c */
extern CS_RETCODE CS_PUBLIC comnb_i2tobit PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i2toi1 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i2toi2 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i2toi4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i2toflt4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i2toflt8 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i2tonum PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i2tomny4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i2tomoney PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i2tochar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i2tovarchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_i4.c */
extern CS_RETCODE CS_PUBLIC comnb_i4tobit PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i4toi1 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i4toi2 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i4toi4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i4toflt4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i4toflt8 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i4tonum PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i4tomny4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i4tomoney PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i4tochar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_i4tovarchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_intl.c */
extern CS_RETCODE CS_PUBLIC comb__intl_xlate PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

extern CS_INT CS_PUBLIC comnb_truncate_chars PROTOTYPE((
	CHAR_ATTRIB	*attrib,
	CS_BYTE		*source,
	CS_INT		srclen,
	CS_INT		colen
	));

/* bc_mny4.c */
extern CS_RETCODE CS_PUBLIC comnb_mny4tobit PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_mny4toi1 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_mny4toi2 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_mny4toi4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_mny4toflt4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_mny4toflt8 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_mny4tonum PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_mny4tomny4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_mny4tomoney PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_mny4tochar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_mny4tovarchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_mony.c */
extern CS_RETCODE CS_PUBLIC comnb_moneytobit PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_moneytoi1 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_moneytoi2 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_moneytoi4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_moneytoflt4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_moneytoflt8 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_moneytonum PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_moneytomny4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_moneytomoney PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_moneytochar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_moneytovarchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_num.c */
extern CS_RETCODE CS_PUBLIC comnb_numtobit PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_numtoi1 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_numtoi2 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_numtoi4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_numtoflt4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_numtoflt8 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_numtonum PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_numtomny4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_numtomoney PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_numtochar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_numtovarchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

/* bc_varc.c */
extern CS_RETCODE CS_PUBLIC comnb_varchartobit PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_varchartoi1 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_varchartoi2 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_varchartoi4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_varchartoflt4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_varchartoflt8 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_varchartonum PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_varchartodate4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_varchartodatetime PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_varchartomny4 PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_varchartomoney PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_varchartochar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));
extern CS_RETCODE CS_PUBLIC comnb_varchartovarchar PROTOTYPE((
	CAST_CONTEXT *context,
	CONSTANT *src,
	CONSTANT *dest
	));

extern int CS_PUBLIC com__subexctnumetoflt8 PROTOTYPE((
	CONSTANT *numeval,
	CS_FLOAT *flt8
	));
extern int CS_PUBLIC com__subexctnumetochar PROTOTYPE((
	CONSTANT *srcconst,
	char *dest,
	int destlen
	));
extern int CS_PUBLIC com__subchartoexctnume PROTOTYPE((
	char *cp,
	int len,
	CS_BYTE **dest,
	CS_INT *destlen,
	CS_BYTE *precision,
	CS_BYTE *scale,
	int flag
	));
/* numeric.c */
extern int CS_PUBLIC com__doubletoexctnume PROTOTYPE((
        double flt8val,
        CS_BYTE *dest,
        int destlen,
        CS_BYTE *precision,
        CS_BYTE *scale
        ));
extern int CS_PUBLIC com__longtoexctnume PROTOTYPE((
        CS_INT intval,
        CS_BYTE *dest,
        int destlen,
        CS_BYTE *precision,
        CS_BYTE *scale
        ));
extern int CS_PUBLIC com__longlongtoexctnume PROTOTYPE((
        CS_LONG longval,
        CS_BYTE *dest,
        int destlen,
        CS_BYTE *precision,
        CS_BYTE *scale
        ));
/* numemath.c */
extern int CS_PUBLIC com__exctnume_addorsub PROTOTYPE((
        CONSTANT *op1,
        CONSTANT *op2,
        CONSTANT *result,
        int opn
        ));
extern void CS_PUBLIC com__exctnume_ceilingfloor PROTOTYPE((
        CONSTANT *op,
        CONSTANT *result,
        int        type
        ));
extern int CS_PUBLIC com__exctnume_mul PROTOTYPE((
        CONSTANT *op1,
        CONSTANT *op2,
        CONSTANT *res
        ));
extern void CS_PUBLIC com__exctnume_round PROTOTYPE((
        CONSTANT *op,
        long       scale,
        CONSTANT *result
        ));

/* numeaux.c */
extern int CS_PUBLIC com__exctnume_checkprecision PROTOTYPE((
        CONSTANT *val
        ));
extern int CS_PUBLIC com__exctnume_cmp PROTOTYPE((
        CONSTANT *op1,
        CONSTANT *op2,
        int flag
        ));
extern int CS_PUBLIC com__exctnume_copy PROTOTYPE((
        CONSTANT *inval,
        CONSTANT *outval
        ));
extern int CS_PUBLIC com__exctnume_div PROTOTYPE((
        CONSTANT *op1,
        CONSTANT *op2,
        CONSTANT *quot,
        CONSTANT *remdr
        ));
extern int CS_PUBLIC com__exctnume_divby10 PROTOTYPE((
        CS_BYTE **ptrtobufptr,
        int *lenptr
        ));
extern int CS_PUBLIC com__exctnume_inc PROTOTYPE((
        CONSTANT *numeptr
        ));
extern int CS_PUBLIC com__exctnume_intcmp PROTOTYPE((
        CONSTANT *val,
        int i
        ));
extern int CS_PUBLIC com__exctnume_scale PROTOTYPE((
        CONSTANT *inval,
        CONSTANT *outval,
        int scale,
        int statflag
        ));

/* mny4cnvt.c */
extern int CS_PUBLIC com__flt8tomny PROTOTYPE((
        CS_BYTE *src,
        int srclen,
        CS_BYTE *dest,
	int destlen,
        int style
        ));
extern int CS_PUBLIC com__mnytoflt8 PROTOTYPE((
        CS_BYTE *src,
        int srclen,
        CS_BYTE *dest,
        int destlen,
        int style
        ));

/* netenc.c */
extern void CS_PUBLIC com__char_uninitialize PROTOTYPE((
        OCTET *ciphertext,
        OCTET *salt,
        OCTET *plaintext,
        int innerindex
        ));
extern void CS_PUBLIC com__char_initialize PROTOTYPE((
        OCTET *plaintext,
        OCTET *salt,
        OCTET *ciphertext,
        int innerindex
        ));

/* Functions for exporting comnlib data to other dll's */
extern unsigned char CS_PUBLIC comb_get_Byte_Power_val PROTOTYPE((
	CS_INT index_x,
	CS_INT index_y
	));

extern unsigned char * CS_PUBLIC comb_get_Byte_Power_ptr PROTOTYPE((
	CS_INT index_x,
	CS_INT index_y
	));

extern unsigned char CS_PUBLIC comb_get_Len_To_Prec PROTOTYPE((
	CS_INT index
	));

extern unsigned char CS_PUBLIC comb_get_Prec_To_Len PROTOTYPE((
	CS_INT index
	));

extern double  CS_PUBLIC comb_get_Flt_Power PROTOTYPE((
	CS_INT index
	));

extern double  CS_PUBLIC comb_get_Flt_256 PROTOTYPE((
	CS_INT index
	));

extern OCTET * CS_PUBLIC comb_get_Netkey PROTOTYPE((
	CS_INT index
	));

CS_END_EXTERN_C

#endif /* __COMNLIB_H__ */
