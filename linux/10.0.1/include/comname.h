
/* Sccsid %Z% %M% %I% %G% */

/*
**      Sybase COMMON-LIBRARY Version 5.0
**      Confidential Property of Sybase, Inc.
**      (c) Copyright Sybase, Inc. 1991, 1992
**      All rights reserved
*/

/*
** COMNAME.H
**
** Common-Lib's very private include file.  Contains a complete set of server
** functions and the common lib internal name representions for them.
**
** The purposed of this is to eliminate name clashes with user programs.
** In looking at the list below, it would be very easy to have a user create
** a function with the same name, WHICH GET LINKED IN FIRST. This file is
** included in all the server source modules to prevent this. All references
** to server functions MUST use the com__ prefix.
*/

#ifndef __COMNAME_H__
#define __COMNAME_H__


/* datetime.c */
#define datetochar		com__datetochar
#define datetolongchar		com__datetolongchar
#define leapcnt			com__leapcnt
#define datecrack		com__datecrack
#define timecrack		com__timecrack
#define cpchar			com__cpchar
#define datediff		com__datediff
#define date_add		com__date_add
#define datename		com__datename
#define datepart		com__datepart
#define timemake		com__timemake
#define datemake		com__datemake
#define itochar			com__itochar
#define chtoi1_mb		com__chtoi1_mb
#define chtoi2_mb		com__chtoi2_mb
#define chtoi4_mb		com__chtoi4_mb
#define chtoi8_mb		com__chtoi8_mb
#define datefromchar_mb		com__datefromchar_mb
#define timefromchar_mb		com__timefromchar_mb
#define amcheck			com__amcheck
#define year2digit		com__year2digit
#define datecmp			com__datecmp
#define date4fromchar_mb	com__date4fromchar_mb
#define dttodate4		com__dttodate4
#define date4todt		com__date4todt
#define date4tochar		com__date4tochar
#define dateadd_both		com__dateadd_both
#define valid_datetime		com__valid_datetime
#define cpint			com__cpint

/* mny4cnvt.c */
#define mny4tomny		com__mny4tomny
#define mnytomny4		com__mnytomny4
#define inttomny4		com__inttomny4
#define mny4toint		com__mny4toint
#define mnyminus4		com__mnyminus4
#define mnyadd4			com__mnyadd4
#define mnysub4			com__mnysub4
#define mnydiv4			com__mnydiv4
#define mnymul4			com__mnymul4
#define mnyrem4			com__mnyrem4
#define flt4tomny		com__flt4tomny
#define mnytoflt4		com__mnytoflt4
#define mny4tochar		com__mny4tochar
#define mny4toflt8		com__mny4toflt8
#define flt8tomny4		com__flt8tomny4
#define flt4tomny4		com__flt4tomny4
#define mny4fromchar_mb		com__mny4fromchar_mb
#define mny4toflt4		com__mny4toflt4

/* mnycnvt.c */
#define mnycopy			com__mnycopy
#define mnyinit			com__mnyinit
#define mnytochar		com__mnytochar
#define mnyfromchar_mb		com__mnyfromchar_mb
#define mnyndigit		com__mnyndigit
#define inttomny		com__inttomny
#define mnytoint		com__mnytoint
#define mnytoflt8		com__mnytoflt8
#define flt8tomny		com__flt8tomny
#define mnyinc			com__mnyinc
#define mnydec			com__mnydec
#define mnyminus		com__mnyminus
#define mnydown			com__mnydown
#define mnyscale		com__mnyscale
#define mnyadd			com__mnyadd
#define mnysub			com__mnysub
#define mnydiv			com__mnydiv
#define mnymul			com__mnymul
#define mnyrem			com__mnyrem
#define mnyshift		com__mnyshift
#define maxposmny		com__maxposmny
#define maxnegmny		com__maxnegmny

/* mpint.c */
#define mp_cmp			com__mp_cmp
#define mp_add			com__mp_add
#define mp_sub			com__mp_sub
#define mp_mul			com__mp_mul
#define mp_div			com__mp_div

/* mpmath.c */
#define mpadd			com__mpadd
#define mpsub			com__mpsub
#define mpmul			com__mpmul
#define mpdiv			com__mpdiv
#define mpdigcvt		com__mpdigcvt
#define mpscale			com__mpscale
#define mpgetdig		com__mpgetdig
#define mpbyteswap		com__mpbyteswap
#define mpgetswap		com__mpgetswap
#define mpput			com__mpput
#define mpnormalize		com__mpnormalize
#define mpneg			com__mpneg
#define impscale		com__impscale
#define impincr			com__impincr

/* numeaux.c */
#define exctnume_cmp		com__exctnume_cmp
#define exctnume_scale		com__exctnume_scale
#define exctnume_checkprecision	com__exctnume_checkprecision
#define exctnume_intcmp		com__exctnume_intcmp
#define exctnume_copy		com__exctnume_copy
#define exctnume_divby10	com__exctnume_divby10
#define exctnume_mulby10_add	com__exctnume_mulby10_add
#define exctnume_inc		com__exctnume_inc
#define exctnume_needsbyte	com__exctnume_needsbyte

/* numemath.c */
#define exctnume_intadd		com__exctnume_intadd
#define exctnume_intsub		com__exctnume_intsub
#define exctnume_intmul		com__exctnume_intmul
#define exctnume_intdiv		com__exctnume_intdiv
#define exctnume_addorsub	com__exctnume_addorsub
#define exctnume_mul		com__exctnume_mul
#define exctnume_div		com__exctnume_div
#define exctnume_round		com__exctnume_round
#define exctnume_ceilingfloor	com__exctnume_ceilingfloor

/* numeric.c */
#define subexctnumetoflt8	com__subexctnumetoflt8
#define doubletoexctnume	com__doubletoexctnume
#define subexctnumetoflt8	com__subexctnumetoflt8
#define doubletoexctnume	com__doubletoexctnume
#define longtoexctnume		com__longtoexctnume
#define longlongtoexctnume	com__longlongtoexctnume
#define exctnumetomny8		com__exctnumetomny8
#define mny8toexctnume		com__mny8toexctnume
#define subexctnumetochar	com__subexctnumetochar
#define subchartoexctnume	com__subchartoexctnume
#define Nume_Byte_Power_Array	Com__Nume_Byte_Power_Array
#define Nume_Len_To_Prec	Com__Nume_Len_To_Prec
#define Nume_Prec_To_Len	Com__Nume_Prec_To_Len

/* strcmp.c */
#define smel_lsc		com__smel_lsc
#define ps_dl_sqlhilo		com__ps_dl_sqlhilo
#define spec_tord		com__spec_tord

/* ennkeys.c */
#define Enc_initialized		Com__Enc_initialized
#define Enkeys			Com__Enkeys

/* fealencr. */
#define Null4			Com__Null4

/* netenc.c */
#define Netkey			Com__Netkey
#define pad			com__pad
#define trunc			com__trunc
#endif /* __COMNAME_H__ */
