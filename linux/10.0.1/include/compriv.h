


/* Sccsid %Z% %M% %I% %G% */

/*
**	Sybase COMMON-LIBRARY Version 10.0
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1991, 1993
**	All rights reserved
*/

/*
** COMPRIV.H
**
** Common-Lib's private include file.  Contains stuff that need not be
** shared with the public.
**
*/

#ifndef __COMPRIV_H__
#define __COMPRIV_H__

/*
** include server interface header file
*/
#include	<comsrv.h>

/*
** NOTE: This is used in datetime.c
*/
#ifndef	MEM_EQ
#define MEM_EQ(p1, len1, p2, len2)                                     \
        (!com_memhilo((BYTE *) p1, (CS_INT) len1, (BYTE *) p2, (CS_INT) len2))
#endif /* MEM_EQ */

#ifndef MAXNEGI4
#define MAXNEGI4	MINI4
#endif /* MAXNEGI4 */

#ifndef MAXNEGI8
#define MAXNEGI8	MINI8
#endif /* MAXNEGI4 */

/* Arithmetic result status  - from server.h */
#define O_SUCCESS       0       /* Normal completion */
#define O_OVERFLOW      1       /* Result too large */
#define O_SYNTAX        2       /* Badly-formed ASCII number string */
#define O_DIVZERO       3       /* Attempted divide-by-zero */
#define O_DOMAINE       4       /* Domain error */
#define O_UNDERFLOW     5       /* Underflow error */
#define O_TRUNCERR      6       /* Truncation error */

/*
** define a macro to map server return codes to CS_xxx return codes
*/
#define MAP_SRV_RETURN(R)	( ((R) == O_SUCCESS) \
			? CS_SUCCEED \
			: ((R) == O_OVERFLOW) \
				? CS_EOVERFLOW \
				: ((R) == O_SYNTAX) \
					? CS_ESYNTAX \
					: ((R) == O_DIVZERO) \
						? CS_EDIVZERO  \
						: ((R) == O_TRUNCERR) \
							? CS_EOVERFLOW  \
						: CS_SUCCEED )

/*
** define a macro to map CS_xxx return codes to COM_yyy return codes
*/
#define MAP_COM_RETURN(R) ( ((R) == CS_EOVERFLOW) \
		? COM_ECOFL \
		: ((R) == CS_EUNDERFLOW) \
			? COM_ECUFL \
			: ((R) == CS_EPRECISION) \
				? COM_ECPREC \
				: ((R) == CS_ESCALE) \
					? COM_ECSCALE  \
					: ((R) == CS_ESYNTAX) \
						? COM_ECSYN  \
						: ((R) == CS_EDOMAIN) \
							? COM_ECDOMAIN  \
							: (R) )

/*
** The server conversion code represents a numeric datatype in a different
** storage format than Common Lib. The following macro converts from 
** CS_NUMERIC to server NUMERIC.
*/
#define TO_SRV_NUMERIC(S, N) { \
	(N)->type = 0; \
	(N)->prec = ((CS_NUMERIC *)S)->precision; \
	(N)->scale = ((CS_NUMERIC *)S)->scale; \
	(N)->len = (comn_num_getlen((N)->prec)); \
	(N)->value = ((CS_NUMERIC *)S)->array; }

/*
** maximum number of characters that a money value needs when stored as a
** string.
*/
#define	COM_PRMONEY	24

/*
** maximum number of characters that a numeric value needs when stored as a
** string.
*/
#define	COM_PRNUMERIC	(CS_MAX_PREC + 2)

/*
** The MAX_ASCII_FLOAT define indicates the largest buffer that will hold
** the ascii character representation of a floating point number.
**
** NOTE:  When a multibyte character string is to be converted to float, it
** 	  first is converted to ascii in a temp buffer.  Since common lib
**	  does not do any memory allocations, this buffer will use the
**	  following define (hence the large value for cases with spaces in
**	  them) and exist on the stack.
*/
#define MAX_ASCII_FLOAT		1024

/*
** The MAX_ASCII_INT define indicates the largest buffer that will hold
** the ascii character representation of a four byte integer number.
** (i.e. -2147483648 plus a few for safety)
*/
#define MAX_ASCII_INT		64

/*
** defines used in bin to char routines.
**
** The BIN_TO_STRHEX() macro will take a source binary parameter (B), and
** move it into to adjacent character string locations (S). The first byte
** will contain the ascii value for the high 4 bit settings of the source.
** The second byte will contain the ascii value for the low 4 bits.
*/
#define HI_BITS(B)		((*(B) >> 4) & 0xf)
#define LOW_BITS(B)		(*(B) & 0xf)
#define TO_CHAR(H)		(((H) >= 0xa) ? (H) - 0xa + 'a' : (H) + '0')
#define BIN_TO_STRHEX(B, S)	((S)[0] = TO_CHAR(HI_BITS(B)), \
				 (S)[1] = TO_CHAR(LOW_BITS(B)))

/*
** defines used in char to bin routines.
**
** The ASCII_TO_BIN() macro will take an ascii character (C), representing a
** hex value, and return the binary equivalent. The valid characters are:
**
**	'0' - '9', 'a' - 'f', and 'A' - 'F'
**
** If the ascii character is illegal, this macro will return -1.
*/
#define ASCII_TO_BIN(C)	( ((C) >= '0' && (C) <= '9') \
				? ((C) - '0') \
				: ((C) >= 'a' && (C) <= 'f') \
					? ((C) - 'a' + 10) \
					: ((C) >= 'A' && (C) <= 'F') \
						? ((C) - 'A' + 10) \
						: -1 )

/*
** Define macros for detecting bad precision and scale values.
**
** PORT ALERT!!! Note that the scale test checks for max scale only.
** This assumes that the datatype (S) is CS_BYTE, and min scale == 0. We do
** this to shut the ANSI compilers up about "comparison is always 0"
*/
#define BAD_PRECISION(P)	((P) < CS_MIN_PREC || (P) > CS_MAX_PREC)
#define BAD_SCALE(S)		((S) > CS_MAX_SCALE)

/*
** Macros to determine if a valid type exists
*/
#define COM_IS_CHAR_TYPE(D)	((D) == CS_CHAR_TYPE || \
				 (D) == CS_TEXT_TYPE || \
				 (D) == CS_LONGCHAR_TYPE || \
				 (D) == CS_SENSITIVITY_TYPE || \
				 (D) == CS_BOUNDARY_TYPE)
#define COM_IS_BINARY_TYPE(D)	((D) == CS_BINARY_TYPE || \
				 (D) == CS_IMAGE_TYPE || \
				 (D) == CS_LONGBINARY_TYPE)

/*
** These defines used by com_mnyxdiv().
*/
#define COM_LOW     0x0000ffff
#define COM_HIGH    ~0x0000ffff
#define COM_SHIFT   16

/*
** These defines are used in the CS_ATTRIB structure.
*/
#define CSID_ISO8859_1	1   /*  iso_1 */
#define CSID_CP850	2   /*  cp850 */
#define CSID_ROMAN8	4   /*  roman8 */
#define CSID_MAC	5   /*	MacIntosh character set */

#define	COM_MONTH_PER_YEAR       12      /* number of months in a year */

/*
** padding type for the NULL value 
*/
#define COM_NULL_PADCHAR	1	/* padding of  binary */
#define COM_NULL_PADBIN		2	/* padding of  character */
#define COM_NULL_NOPAD		3	/* no padding needed */

/*
** defines used to overload "style" parameter in mnytochar function
** the upper byte is used to indicate the precision of the money when
** it is converted to a string. The lower byte is used to indicate
** whether or not to insert group separators "," in the integer part of 
** the number every third digit.
*/

#define COM_MNY_GET_GROUPSEP(S)         (((S) & 0xff) == TRUE)
#define COM_MNY_SET_GROUPSEP(S, B)      ((S) |= (0xff & B))
#define COM_MNY_GET_PRECISION(S)        ((S) >> 8)
#define COM_MNY_SET_PRECISION(S, P)     ((S) |= ((P) << 8))

/***************************************************************************
**
** External definitions for functions used internally by Common-Lib.
**
***************************************************************************/

/* com_ctbl.c */
extern CS_VOID CS_INTERNAL com__get_ctbl PROTOTYPE((
	CS_CONV_FUNC **cvt_array,
	int *cvt_dim
	));

extern CS_INT CS_INTERNAL comn_get_datetochar_fmt PROTOTYPE((
	CS_CONTEXT 	*context,
	CS_DATAFMT	*fmt
	));

/* com_glbl.c -- Moved to comnblib.h */

/* com_path.c */
extern CS_RETCODE CS_INTERNAL com__path_locfile PROTOTYPE((
	CsContext *context,
	CS_CHAR *lang,
	CS_CHAR *charset,
	CS_CHAR *locfile,
	CS_CHAR *pathname,
	CS_INT pathsize
	));
extern CS_RETCODE CS_INTERNAL com__path_charfile PROTOTYPE((
	CsContext *context,
	CS_CHAR *charset,
	CS_CHAR *filename,
	CS_CHAR *fileext,
	CS_CHAR *pathname,
	CS_INT pathsize
	));

/* com_stak.c */
extern CS_VOID CS_INTERNAL com__stackem PROTOTYPE((void));

/* cvtascii.c */
extern CS_INT CS_INTERNAL com__conv2ascii PROTOTYPE((
	CS_BYTE *src,
	CS_INT srclen,
	CS_BYTE *dest,
	CS_INT destlen,
	CS_ATTRIB *chatr
	));

/* datetime.c -- Moved to comnblib.h */

/* dbgfuncs.c */
extern CS_VOID CS_INTERNAL com__abort PROTOTYPE((void));
extern CS_VOID CS_INTERNAL com__get_stack_depth PROTOTYPE((
	int *depth
	));

/* fealencr.c */
extern void com__charbuf_clean PROTOTYPE((
	OCTET *A,
	OCTET *B,
	OCTET *fk
	));
extern void com__charbuf_alloc PROTOTYPE((
	OCTET *A,
	OCTET *B,
	OCTET *f
	));
extern void com__charbuf_activate PROTOTYPE((
	OCTET *key,
	DOCTET *feal_keysched
	));
extern void com__charbuf_initialize PROTOTYPE((
	OCTET *P,
	OCTET *C,
	DOCTET *feal_keysched
	));
extern void com__charbuf_uninitialize PROTOTYPE((
	OCTET *P,
	OCTET *C,
	DOCTET *feal_keysched
	));

/* mny4cnvt.c */
extern void CS_PUBLIC com__mny4tomny PROTOTYPE((
	CS_MONEY4 *m4p,
	CS_MONEY *mp
	));
extern int com__mnytomny4 PROTOTYPE((
	CS_MONEY *mp,
	CS_MONEY4 *m4p
	));
extern int com__inttomny4 PROTOTYPE((
	CS_MONEY4 *m4p,
	CS_INT *value
	));
extern int com__mny4toint PROTOTYPE((
	CS_MONEY4 *m4p,
	CS_INT *ip
	));
extern int CS_PUBLIC com__mnyminus4 PROTOTYPE((
	CS_MONEY4 *imp,
	CS_MONEY4 *omp
	));
extern int CS_PUBLIC com__mnyadd4 PROTOTYPE((
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
extern int com__flt4tomny PROTOTYPE((
	CS_BYTE *src,
	int srclen,
	CS_BYTE *dest,
	int destlen,
	int style
	));
extern int com__mnytoflt4 PROTOTYPE((
	CS_BYTE *src,
	int srclen,
	CS_BYTE *dest,
	int destlen,
	int style
	));
extern char * CS_PUBLIC com__mny4tochar PROTOTYPE((
	CS_MONEY4 *m4p,
	char *cp,
	int len,
	int style
	));
extern int com__mny4toflt8 PROTOTYPE((
	CS_BYTE *src,
	CS_BYTE *dest
	));
extern int com__flt8tomny4 PROTOTYPE((
	CS_BYTE *src,
	int srclen,
	CS_BYTE *dest,
	int style
	));
extern int com__flt4tomny4 PROTOTYPE((
	CS_BYTE *src,
	int srclen,
	CS_BYTE *dest,
	int style
	));
extern int com__mny4fromchar_mb PROTOTYPE((
	CS_MONEY4 *m4p,
	char *icp,
	int ilen,
	int style,
	CS_ATTRIB *chatr
	));
extern int com__mny4toflt4 PROTOTYPE((
	CS_BYTE *src,
	CS_BYTE *dest
	));

/* mnycnvt.c */
extern int com__mnycopy PROTOTYPE((
	CS_MONEY *mp1,
	CS_MONEY *mp2
	));
extern int com__mnyinit PROTOTYPE((
	CS_MONEY *mp,
	int trim
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
extern int com__mnyndigit PROTOTYPE((
	CS_MONEY *mp,
	char *value
	));
extern int com__inttomny PROTOTYPE((
	CS_MONEY *mp,
	CS_INT *value
	));
extern int com__mnytoint PROTOTYPE((
	CS_MONEY *mp,
	CS_INT *ip
	));
extern int com__mnyinc PROTOTYPE((
	CS_MONEY *mp
	));
extern int com__mnydec PROTOTYPE((
	CS_MONEY *mp
	));
extern int CS_PUBLIC com__mnyminus PROTOTYPE((
	CS_MONEY *imp,
	CS_MONEY *omp
	));
extern int CS_PUBLIC com__flt8tomny PROTOTYPE((
	BYTE *src,
	int srclen,
	BYTE *dest,
	int destlen,
	int style
	));
extern int CS_PUBLIC com__mnytoflt8 PROTOTYPE((
	BYTE *src,
	int srclen,
	BYTE *dest,
	int destlen,
	int style
	));
extern int com__mnydown PROTOTYPE((
	CS_MONEY *mp,
	int dvsr
	));
extern int com__mnyscale PROTOTYPE((
	CS_MONEY *mp,
	int mpier,
	int add
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
extern void com__mnyshift PROTOTYPE((
	CS_MONEY *m1,
	CS_INT value
	));
extern void com__maxposmny PROTOTYPE((
	CS_MONEY *mp
	));
extern void com__maxnegmny PROTOTYPE((
	CS_MONEY *mp
	));

/* netenc.c */
extern void CS_INTERNAL com__uninitialize_tds_text PROTOTYPE((
	OCTET *challenge,
	int challenge_len,
	OCTET *response,
	int *response_len
	));
extern void CS_INTERNAL com__initialize_tds_text PROTOTYPE((
	OCTET *challenge,
	int *challenge_len
	));
extern int CS_INTERNAL com__tds_initialization_check PROTOTYPE((
	OCTET *challenge,
	int challenge_len,
	OCTET *response,
	int response_len
	));
extern void CS_INTERNAL com_init_text_mem PROTOTYPE((void));

extern int CS_INTERNAL com__string_initialize PROTOTYPE((
	char *salt,
	int saltlen,
	char *plaintext,
	int length,
	char *resulttext,
	int *resultlen
	));
extern int CS_INTERNAL com__string_uninitialize PROTOTYPE((
	char *salt,
	int saltlen,
	char *ciphertext,
	int cipherlen,
	char *plaintext,
	int *ptextlen
	));
extern void CS_INTERNAL com__pad PROTOTYPE ((
	char *text,
	int textlen,
	OCTET *salt,
	OCTET *ptext
	));
extern void CS_INTERNAL com__trunc PROTOTYPE ((
	OCTET *ptext,
	int textlen,
	OCTET *salt,
	char *text
	));
extern void CS_INTERNAL com__localization_convert PROTOTYPE ((
	OCTET *plaintext,
	OCTET *salt,
	OCTET *ciphertext
	));
extern void CS_INTERNAL com__localization_reconvert PROTOTYPE ((
	OCTET *plaintext,
	OCTET *salt,
	OCTET *ciphertext
	));

/* newutils.c */
extern CS_VOID CS_INTERNAL comn__hex2binbytes PROTOTYPE((
	CS_CHAR **src,
	CS_INT *srclen
	));
extern CS_RETCODE CS_INTERNAL comn__padchar PROTOTYPE((
	CS_INT srclen,
	CS_DATAFMT *destfmt,
	CS_VOID *dest,
	CS_INT *destlen
	));
extern CS_RETCODE CS_INTERNAL comn__padbin PROTOTYPE((
	CS_INT srclen,
	CS_DATAFMT *destfmt,
	CS_VOID *dest,
	CS_INT *destlen
	));

/* numeaux.c */
extern int CS_PUBLIC com__exctnume_cmp PROTOTYPE(( 
	REGISTER NUMERIC *op1,
	REGISTER NUMERIC *op2,
	int		 flag
	));
extern int CS_PUBLIC com__exctnume_scale PROTOTYPE((
	NUMERIC *inval,
	NUMERIC *outval,
	REGISTER int scale,
	int statflag
	));
extern int CS_PUBLIC com__exctnume_checkprecision PROTOTYPE((
	NUMERIC	*val
	));
extern int CS_PUBLIC com__exctnume_intcmp PROTOTYPE((
	REGISTER NUMERIC *val,
	REGISTER int i
	));
extern int CS_PUBLIC com__exctnume_copy PROTOTYPE((
	REGISTER NUMERIC *inval,
	REGISTER NUMERIC *outval
	));
extern int CS_PUBLIC com__exctnume_divby10 PROTOTYPE((
	BYTE **ptrtobufptr,
	int *lenptr
	));
extern int CS_PUBLIC com__exctnume_inc PROTOTYPE((
	REGISTER NUMERIC *numeptr
	));
extern int com__exctnume_mulby10_add PROTOTYPE((
	CONSTANT *numeval,
	int i
	));
extern int com__exctnume_needsbyte PROTOTYPE((
	CONSTANT *numeptr
	));

/* numemath.c */
extern int CS_PUBLIC com__exctnume_addorsub PROTOTYPE((
	NUMERIC *op1,
	NUMERIC *op2,
	NUMERIC *result,
	int opn
	));
extern int CS_PUBLIC com__exctnume_mul PROTOTYPE((
	REGISTER NUMERIC *op1,
	REGISTER NUMERIC *op2,
	REGISTER NUMERIC *res
	));
extern int CS_PUBLIC com__exctnume_div PROTOTYPE((
	NUMERIC *op1,
	NUMERIC *op2,
	NUMERIC *quot,
	NUMERIC *remdr
	));
extern void CS_PUBLIC com__exctnume_round PROTOTYPE((
	NUMERIC	*op,
	CS_INT scale,
	NUMERIC	*result
	));
extern void CS_PUBLIC com__exctnume_ceilingfloor PROTOTYPE((
	REGISTER NUMERIC *op,
	REGISTER NUMERIC *result,
	int type
	));
extern int com__exctnume_intadd PROTOTYPE((
	CONSTANT *a,
	CONSTANT *b,
	CONSTANT *r
	));
extern int com__exctnume_intsub PROTOTYPE((
	CONSTANT *a,
	CONSTANT *b,
	CONSTANT *r
	));
extern int com__exctnume_intmul PROTOTYPE((
	CONSTANT *a,
	CONSTANT *b,
	CONSTANT *r
	));
extern int com__exctnume_intdiv PROTOTYPE((
	CONSTANT *a,
	CONSTANT *b,
	CONSTANT *q,
	CONSTANT *r
	));
/* numeric.c */
extern int CS_PUBLIC com__subexctnumetoflt8 PROTOTYPE((
	REGISTER NUMERIC *numeval,
	CS_FLOAT *flt8
	));
extern int CS_PUBLIC com__doubletoexctnume PROTOTYPE((
	REGISTER double	flt8val,
	REGISTER BYTE *dest,
	REGISTER int destlen,
	BYTE *precision,
	BYTE *scale
	));
extern int CS_PUBLIC com__longtoexctnume PROTOTYPE((
	REGISTER CS_INT	intval,
	BYTE *dest,
	int destlen,
	BYTE *precision,
	BYTE *scale
	));
extern int CS_PUBLIC com__longlongtoexctnume PROTOTYPE((
	REGISTER CS_LONG longval,
	BYTE *dest,
	int destlen,
	BYTE *precision,
	BYTE *scale
	));
extern int CS_PUBLIC com__subexctnumetochar PROTOTYPE((
	CONSTANT *srcconst,
	REGISTER char *dest,
	REGISTER int destlen
	));
extern int CS_PUBLIC com__subchartoexctnume PROTOTYPE((
	REGISTER char *cp,
	REGISTER int len,
	BYTE **dest,
	CS_INT *destlen,
	BYTE *precision,
	BYTE *scale,
	int flag
	));
extern int com__exctnumetomny8 PROTOTYPE((
	CONSTANT *numeval,
	CS_BYTE *dest
	));
extern int com__mny8toexctnume PROTOTYPE((
	CS_MONEY *mnyptr,
	CS_BYTE *dest,
	int destlen,
	CS_BYTE *precision,
	CS_BYTE *scale,
	int flag
	));

/* oldconv.c */
extern void com__padchar PROTOTYPE((
	char *dest,
	CS_INT destlen,
	CS_INT bytes_filled
	));
extern void com__padstring PROTOTYPE((
	char *dest,
	CS_INT destlen,
	CS_INT bytes_filled
	));
extern void com__padntbstring PROTOTYPE((
	char *dest,
	CS_INT bytes_filled
	));

/* oldutils.c */
extern int com__bin2hex PROTOTYPE((
	CS_BYTE *src,
	CS_INT srclen,
	char *dest,
	CS_INT destlen
	));
extern int com__hex2binbytes PROTOTYPE((
	char **src,
	CS_INT *srclen
	));
extern void com__shift1 PROTOTYPE((
	char *cp,
	int bytes
	));

/* strcmp.c */
extern void com__smel_lsc PROTOTYPE((
	SMEL *smels,
	int smel_1st,
	char **raw_cur,
	char *raw_end,
	LSC  *lsc,
	LSC  *hold
	));
extern int CS_INTERNAL com__ps_dl_sqlhilo PROTOTYPE((
	SO_1CLASS *so,
	CS_CHAR *str1,
	int len1,
	CS_CHAR *str2,
	int len2
	));
extern int CS_INTERNAL com__spec_tord PROTOTYPE((
	SO_1CLASS *so,
	CS_CHAR *str1,
	int len1,
	CS_CHAR *str2,
	int len2
	));

#endif /* __COMPRIV_H__ */
