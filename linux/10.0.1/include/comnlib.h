/* ORIGINAL_SCCSID:  Sccsid @(#) comnlib.h 1.1 5/10/94  */



/* Sccsid @(#) comnlib.h 1.2 5/26/94 */

/*
**	Sybase COMMON-LIBRARY Version 10.0
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1991, 1994
**	All rights reserved
**
**  COMNLIB.H
**
**	Header file to be included in all files which use Common-Lib routines.
**	This header file contains:
**		a) type definitions for the Common-Lib datatypes;
**		b) useful common macros;
**		b) definitions of the conversion routines' return values
**		c) external definitions for Common-Lib routines
*/

#ifndef	__COMNLIB_H__
#define __COMNLIB_H__

/*
** include the core types file. This file contains the defines and data
** structures that are shared by all libraries.
*/
#include	<cstypes.h>
#include	<csthread.h>
#include	<csqueue.h>
#include	<csglobal.h>
#include	<csasync.h>

/***************************************************************************
**
** Commonlib utility macros and defines
**
***************************************************************************/

/*
** misc string defines
*/
#ifndef EOS
#define EOS             '\0'
#endif
#ifndef NULL_TERMINATE
#define NULL_TERMINATE(P, S)    ((P)[S - 1] = EOS)
#endif

/*
** Range and bounds checking macros
*/
#ifndef IN_BOUNDS
#define IN_BOUNDS(N, LO, HI)    ((LO) < (N) && (N) < (HI))
#endif
#ifndef IN_RANGE
#define IN_RANGE(N, LO, HI)     ((LO) <= (N) && (N) <= (HI))
#endif

/*
** Bit manipulation macros
*/
#ifndef SETBIT
#define SETBIT(B,N)     ((B) |= ((CS_INT)1 << (N)))
#endif
#ifndef CLRBIT
#define CLRBIT(B,N)     ((B) &= ~((CS_INT)1 << (N)))
#endif
#ifndef TSTBIT
#define TSTBIT(B,N)     ((B) & ((CS_INT)1 << (N)))
#endif

/*
** Predicates for odd/even tests
*/
#ifndef EVEN
#define EVEN(N)         (((N) & 1) == 0)
#endif
#ifndef ODD
#define ODD(N)          (((N) & 1) == 1)
#endif

/*
** Miscellaneous arithmetic macros
*/
#ifndef MAX
#define MAX(X,Y)        (((X) > (Y)) ? (X) : (Y))
#endif

#ifndef MIN
#define MIN(X,Y)        (((X) < (Y)) ? (X) : (Y))
#endif

#ifndef ABS
#define ABS(X)          (((X) > 0) ? (X) : - (X))
#endif

/*
** Access into a 2-D byte array.
*/
#define BYTE_TABLE_ACCESS(tbl, width, row, column) \
                (CS_BYTE) *((tbl) + ((width) * (row)) + (column))


/***************************************************************************
**
** Commonlib interface defines
**
***************************************************************************/

/*
** defines used when enabling error tracing in client products
*/
#define CS_ERR_TRACE_OFF	(CS_INT)1
#define CS_ERR_TRACE_FAIL	(CS_INT)2
#define CS_ERR_TRACE_ALL	(CS_INT)3

/*
** defines used in for state machine management
*/
#define CS_END_EVENT	(CS_EVENT) (-1)
#define CS_END_STATE	(CS_STATE) (-2)
#define CS_ST_NOTRANS   (CS_STATE) (-875)
#define CS_EVT_FAIL	(CS_EVENT) (-199)

/*
** defines used in character set translation.
*/
#define CS_FOU_NOXLT    (CS_INT) 0
#define CS_FOU_SAME     (CS_INT) 1
#define CS_FOU_7BIT     (CS_INT) 2
#define CS_FOU_OK       (CS_INT) 3

/*
** NOTE: The following are old defines (backwards compatibility)
*/

/*
** define SUCCEED and FAIL codes to map to new CS defines
*/
#define COM_SUCCEED	CS_SUCCEED
#define COM_FAIL	CS_FAIL

/* 
** These defines have equivalent defines in Db-Lib's sybdb.h.  The two sets
** of defines need to be kept in sync.
**
** These defines are used by com_datepart() and com_datename().
*/
#define COM_DATE_YY	0       /* year         1753 - 9999 */
#define COM_DATE_QQ	1       /* quarter      1 - 4 */
#define COM_DATE_MM	2       /* month        January - December */
#define COM_DATE_DW	3       /* weekday      Monday - Sunday */
#define COM_DATE_DD	4       /* day          1 - 31 */
#define COM_DATE_DY	5       /* dayofyear    1 - 366 */
#define COM_DATE_HH	6       /* hour         0 - 23 */
#define COM_DATE_MI	7       /* minute       0 - 59 */
#define COM_DATE_SS	8       /* second       0 - 59 */
#define COM_DATE_MS	9       /* millisecond  0 - 999 */
#define COM_DATE_WK	10      /* week         1 - 54 (for leap years) */
#define	COM_DATE_CY	11
#define	COM_DATE_CW	12
#define	COM_DATE_CD	13

#define COM_INTBITS	32		/* COM_INTs are 32 bits long. */
#define MONEYBITS	64		/* COM_MONEY is 64 bits long. */
#define MONEYHIGH	429496.7296	/* Upper part of money base value */

/*
** Integer equivalents for dateorder strings. These integer values are
** the same as the ones used internally by the server datetime conversion
** routines.
*/
#define COM_DTFMT_MDY	(CS_INT)1
#define COM_DTFMT_DMY	(CS_INT)2
#define COM_DTFMT_YMD	(CS_INT)3
#define COM_DTFMT_YDM	(CS_INT)4
#define COM_DTFMT_MYD	(CS_INT)5
#define COM_DTFMT_DYM	(CS_INT)6

/*
** These defines are the return values of the money routines like
** com_mnyadd(), com_mnydown(), etc.  Note that COM_MNYSUCCEED has a different
** value than COM_SUCCEED.  
**
** These constants should be consistent with analogous constants in mparith.h
*/
#define COM_MNYSUCCEED	0
#define COM_MNYOVERFLOW	1
#define COM_MNYSYNTAX	2
#define COM_MNYDIVZERO	3


/*
** These constants are the values the Common-Lib conversion routines can
** return when an error occurs.  If the conversion routine completes 
** successfully the routine will return the length of the converted data.
*/

#define	COM_ECOFL	-1	/* Data-conversion resulted in overflow.  */
#define COM_ECUFL	-2	/* Data-conversion resulted in underflow.  */
#define COM_ECSYN	-3	/* Attempt to convert data stopped by syntax
				** error in source field.
				*/
#define COM_ECLPR	-4	/* Data-conversion resulted in loss of 
				** precision.
				*/
#define COM_ECNOV	-5	/* Attempt to set variable to NULL resulted
				** in overflow.
				*/
#define COM_ECDOMAIN	-6	/* Source field value not within the domain
				** of legal values.
				*/
#define COM_ECPREC	-7	/* Illegal precision specified */
#define COM_ECSCALE	-8	/* Illegal precision specified */

/***************************************************************************
**
** Commonlib interface data structures
**
***************************************************************************/

/*
** typedefs for state machine management
*/
typedef unsigned char	CS_EVENT;
typedef unsigned char	CS_STATE;

/*
** These typedefs are for use in prototypes.  Some compilers promote
** function parameters which are unsigned chars to integers and require 
** that the prototype have declare the parameter as int, and not 
** unsigned char.  
*/
typedef int		CS_PROTO_EVENT;
typedef int		CS_PROTO_STATE;

/*
** CS_DEPEND - There may be situations where multiple state machines working
** together.  When determining whether or not a verification event is legal
** it may be necessary to check the state of another state machine.
**
** If a state machine depends on another state machine it will have a list
** of CS_DEPEND structures associated with it.  The list will contain all
** verification events that cannot be OK'd until other state machine(s)
** are checked.
*/
typedef struct _csdepend
{
	CS_EVENT	dep_event;	/* the event being verified  */
	CS_EVENT	dep_depevent;	/* the event that gets sent to the other
					** state machine(s).
					*/
} CS_DEPEND;

/*
** CS_EVENT_NS - Stores an "event"/"next state" combination.  Each state
** in a state machine will have an array of CS_EVENT_NS structures
** associated with it.  This array will define all legal events for that
** state, and defines the state transitions that can occur from this 
** state.
*/
typedef struct _cseventns
{
	unsigned char	ens_event;
	unsigned char	ens_nstate;
} CS_EVENT_NS;

/*
** CS_STRINGS - Structure of two fields, a pointer to a character string
** and a key which tells the position this structure should be in when
** part of an array of CS_STRING structures.  The key field makes it easy
** to write a unit test to verify that the CS_STRINGS structures where placed
** in the array properly.
*/
typedef struct _csstrings
{
	CS_INT	key;
	char	*string;
} CS_STRINGS;

/*
** CS_ST_TABLE - The structure an individual state table is stored in.
*/
typedef struct _cssttable
{
	char		*st_name;	/* the name of the state machine */
	CS_INT		st_version;
	int		st_numstates;	/* the number of states */
	CS_EVENT	st_init;	/* initial state */
	CS_EVENT	**st_ver;	/* pointer to the
					** verification table.
					*/
	CS_DEPEND	*st_depend;	/* pointer to the dependency list */
	CS_EVENT_NS	**st_trans;	/* pointer to the
					** transition table.
					*/
	CS_STRINGS	*st_ststrings;	/* state strings */
	CS_STRINGS	*st_verstrings;	/* verification strings */
	CS_STRINGS	*st_transtrings;	/* transition strings */
} CS_ST_TABLE;

/*
** The CS_ST_MACHINE structure is used by to store the current state
** and a pointer to the definition of the state machine.
*/
typedef struct _csstmachine
{
        CS_STATE        sm_state;     	/* The current state of the
                                        ** state machine.
                                        */
        CS_ST_TABLE     *sm_table;    	/* A pointer to the state
                                        ** machine definition.
                                        */
} CS_ST_MACHINE;

/*
** A structure used to manage state tables which are two dimensional
** arrays of bytes.
*/
typedef struct _csbytetable
{
	CS_CHAR		*btname;	/* name of state machine */
	CS_BYTE		*bttable;	/* pointer to 2-D state table */
	CS_INT		btnumevents;	/* the # of events in the table */
	CS_INT		btnumstates;	/* the # of states in the table */
	CS_STRINGS	*btevtstrs;	/* table of strings describing the
					** state events
					*/
	CS_STRINGS	*btststrs;	/* table of strings describing
					** the states
					*/
	CS_INT		btversion;	/* the version of the table */
} CS_BYTE_TABLE;



/*
** CS_NS_TABLE
**
** A structure used to manage state tables which are comprised of
** an array of pointers to CS_EVENT_NS arrays.
**
*/
typedef struct _csnstable
{
	CS_CHAR		*nsname;	/* name of state machine */
	CS_EVENT_NS	**nstable;	/* pointer to the state table */
	CS_INT		nsnumevents;	/* the # of events in the table */
	CS_INT		nsnumstates;	/* the # of states in the table */
	CS_STRINGS	*nsevtstrs;	/* table of strings describing the
					** state events
					*/
	CS_STRINGS	*nsststrs;	/* table of strings describing
					** the states
					*/
	CS_INT		nsversion;	/* the version of the table */
} CS_NS_TABLE;

/*****************************************************************************
**
** interface and generic handle defines used.
**
*****************************************************************************/

#ifndef CS__INTERNAL_STRUCTS

/*
** define generic handles
*/
#ifndef CS_TYPEMAP
#define CS_TYPEMAP	CS_VOID
#endif /* CS_CONTEXT */

#ifndef CS_ATTRIB
#define CS_ATTRIB	CS_VOID
#endif /* CS_ATTRIB */

#ifndef CS_SO_1CLASS
#define CS_SO_1CLASS	CS_VOID
#endif /* CS_SO_1CLASS */

#ifndef CS_SO_2CLASS
#define CS_SO_2CLASS	CS_VOID
#endif /* CS_SO_2CLASS */

#endif /* CS__INTERNAL_STRUCTS */

/***************************************************************************
**
** Commonlib interface macros
**
***************************************************************************/

#define COM_BMOVE(src, dest, bytes) \
	com_bmove((CS_BYTE *)(src), (CS_BYTE *)(dest), (CS_INT)(bytes))

#define COM_ZEROSPACE(dest, bytes)	com__bzero(dest, bytes)

/*
** "type" values for com_intl_getstr() and com_intl_loccmp()
*/
#define CS_CHARSET	(CS_INT)1
#define CS_LANGUAGE	(CS_INT)2
#define CS_SORTORDER	(CS_INT)3

/***************************************************************************
**
** External definitions for Common-Lib API routines
**
***************************************************************************/

#ifndef _CPROTO_

CS_START_EXTERN_C

/* charset.c */
extern CS_VOID CS_PUBLIC com_intl_chardesc_drop PROTOTYPE((
	CS_CONTEXT *context
	));
extern CS_RETCODE CS_PUBLIC com_intl_sortorder PROTOTYPE((
	CS_LOCALE *locale,
	CS_VOID **sortorder
	));

/* com_attrib.c */
extern CS_VOID * CS_PUBLIC com_alloc_char_attrib PROTOTYPE((void));
extern CS_RETCODE CS_PUBLIC com_build_char_attrib PROTOTYPE((
	CS_INT type,
	CS_INT id,
	CS_CHAR *cname,
	CS_VOID *imptr,
	CS_ATTRIB *chatr
	));
extern CS_VOID CS_PUBLIC com_free_char_attrib PROTOTYPE((
	CS_ATTRIB *chatr
	));

/* com_conv.c */
extern CS_RETCODE CS_PUBLIC com_conv_init PROTOTYPE((
	CS_CONTEXT *context
	));
extern CS_RETCODE CS_PUBLIC com_conv_free PROTOTYPE((
	CS_CONTEXT *context
	));
extern CS_CONV_FUNC CS_PUBLIC com_conv_func PROTOTYPE((
	CS_CONTEXT *context,
	CS_INT srctype,
	CS_INT desttype
	));
extern CS_RETCODE CS_PUBLIC com_conv_install PROTOTYPE((
	CS_CONTEXT *context,
	CS_INT srctype,
	CS_INT desttype,
	CS_CONV_FUNC newfunc
	));
extern CS_RETCODE CS_PUBLIC com_conv_default PROTOTYPE((
	CS_CONTEXT *context,
	CS_INT srctype,
	CS_INT desttype
	));

/* com_ctyp.c */
/*
** NOTE: ANSI requires that chars and shorts are promoted to ints when 
**	 using the K&R style of function declarations, so all following
**	 have ints instead of CS_BYTES for the prototype
*/
extern CS_BYTE CS_PUBLIC com_toupper PROTOTYPE((
	int c
	));
extern CS_BYTE CS_PUBLIC com_tolower PROTOTYPE((
	int c
	));
extern CS_BOOL CS_PUBLIC com_isalpha PROTOTYPE((
	int c
	));
extern CS_BOOL CS_PUBLIC com_isupper PROTOTYPE((
	int c
	));
extern CS_BOOL CS_PUBLIC com_islower PROTOTYPE((
	int c
	));
extern CS_BOOL CS_PUBLIC com_isdigit PROTOTYPE((
	int c
	));
extern CS_BOOL CS_PUBLIC com_isxdigit PROTOTYPE((
	int c
	));
extern CS_BOOL CS_PUBLIC com_isspace PROTOTYPE((
	int c
	));
extern CS_BOOL CS_PUBLIC com_isgraph PROTOTYPE((
	int c
	));

/* com_dbg.c */
extern CS_VOID CS_PUBLIC com_errset PROTOTYPE((
        CS_INT level
        ));
extern CS_RETCODE CS_PUBLIC com_errtrace PROTOTYPE((
        CS_RETCODE error,
        char *file,
        int line
        ));
extern CS_VOID CS_PUBLIC com_bomb PROTOTYPE((
	char *file,
	int line
	));
extern CS_VOID CS_PUBLIC com_copstr PROTOTYPE((
	char *dest,
	char *src,
	int size
	));
extern CS_VOID CS_PUBLIC com_catstr PROTOTYPE((
	char *dest,
	char *src,
	int size
	));
extern CS_VOID CS_PUBLIC com_panic PROTOTYPE((
	char *msg
	));
extern CS_RETCODE CS_PUBLIC comn_debug_setfile PROTOTYPE((
	CS_CONTEXT 	*context,
	CS_CHAR		*filename,
	CS_INT		filenlen
	));
extern CS_RETCODE CS_VARARGS comn_debug_print PROTOTYPE((
	CS_CHAR		*fmtstr
	CS_ELLIPSE
	));
extern CS_RETCODE CS_VARARGS comn_debug_vprint PROTOTYPE((
	CS_CHAR		*fmtstr,
	CS_VOID		*arglist
	));

/* com_enc.c */
extern CS_RETCODE CS_PUBLIC com_initialize_tds_strings PROTOTYPE((
	CS_VOID *handle,
	CS_BYTE *plaintext,
	CS_INT plaintext_length,
	CS_BYTE *salt,
	CS_INT saltlen,
	CS_BYTE *resulttext,
	CS_INT *resultlen
	));
extern CS_RETCODE CS_PUBLIC com_uninitialize_tds_text PROTOTYPE((
	CS_VOID *handle,
	CS_BYTE *challenge,
	CS_INT challenge_len,
	CS_BYTE *response,
	CS_INT *response_len
	));

/* com_genv.c */
extern CS_CHAR * CS_PUBLIC com_getenv PROTOTYPE((
	char *envvar
	));

/* com_intl.c */
extern CS_RETCODE CS_PUBLIC com_intl_getstr PROTOTYPE((
	CS_LOCALE *locale,
	CS_INT lctype,
	CS_INT type,
	CS_CHAR *buf,
	CS_INT buflen,
	CS_INT *outlen
	));
extern CS_INT CS_PUBLIC com_intl_loccmp PROTOTYPE((
	CS_INT lctype,
	CS_INT type,
	CS_LOCALE *loc1,
	CS_LOCALE *loc2
	));
extern CS_RETCODE CS_PUBLIC com_intl_load PROTOTYPE((
	CS_CONTEXT *context,
	CS_CHAR *name,
	CS_INT namelen,
	CS_VOID **loccache_p
	));
extern CS_RETCODE CS_PUBLIC com_intl_locname PROTOTYPE((
	CS_CONTEXT *context,
	CS_CHAR *lang_v,
	CS_INT	langlen,
	CS_CHAR *charset_v,
	CS_INT	charsetlen,
	CS_CHAR *sortorder_v,
	CS_INT	sortorderlen,
	CS_CHAR *name,
	CS_INT 	namelen,
	CS_INT	*outlen
	));
extern CS_VOID CS_PUBLIC com_intl_loccache_drop PROTOTYPE((
	CS_CONTEXT *context
	));
extern CS_CHAR * CS_PUBLIC com_intl_get_locname PROTOTYPE((
	CS_VOID *loccache
	));
extern int CS_PUBLIC com_intl_dateorder_id PROTOTYPE((
	CS_CONTEXT *context,
	CS_DATAFMT *dfmt
	));
extern CS_CHAR ** CS_PUBLIC com_intl_shortmonths PROTOTYPE((
	CS_CONTEXT *context,
	CS_DATAFMT *dfmt
	));
extern CS_CHAR ** CS_PUBLIC com_intl_months PROTOTYPE((
	CS_CONTEXT *context,
	CS_DATAFMT *dfmt
	));
extern CS_CHAR ** CS_PUBLIC com_intl_days PROTOTYPE((
	CS_CONTEXT *context,
	CS_DATAFMT *dfmt
	));
extern CS_INT CS_PUBLIC com_intl_firstday PROTOTYPE((
	CS_CONTEXT *context,
	CS_DATAFMT *dfmt
	));
extern CS_INT CS_PUBLIC com_intl_convt_firstday PROTOTYPE((
	CS_INT	orig_firstday,
	CS_INT	orig_day,
	CS_INT	dest_firstday
	));
extern CS_CHAR * CS_PUBLIC com_intl_dateorder PROTOTYPE((
	CS_CONTEXT *context,
	CS_DATAFMT *dfmt
	));
extern CS_BOOL CS_PUBLIC com_intl_is12hour PROTOTYPE((
	CS_CONTEXT *context,
	CS_DATAFMT *dfmt
	));
extern CS_INT CS_PUBLIC com_intl_get_dtfmt PROTOTYPE((
        CS_CONTEXT      *context,
        CS_DATAFMT      *dfmt
        ));
extern CS_RETCODE CS_PUBLIC com_intl_set_dtfmt PROTOTYPE((
        CS_CONTEXT      *context,
        CS_DATAFMT      *dfmt,
        CS_VOID         *buffer
        ));
extern CS_ATTRIB * CS_PUBLIC com_intl_charattr PROTOTYPE((
        CS_CONTEXT *context,
        CS_DATAFMT *dfmt
        ));
extern CS_VOID CS_PUBLIC com_intl_verify_ctxloc PROTOTYPE ((
	CS_CONTEXT      *context
	));
extern CS_RETCODE CS_PUBLIC com_intl_verify_a_msgfile PROTOTYPE ((
	CS_CONTEXT      *context,
	CS_LOCALE       *locale,
	CS_CHAR         *filename,
	CS_CHAR         *buffer,
	CS_INT          buflen
	));
extern CS_RETCODE CS_PUBLIC com_intl_verify_locfiles PROTOTYPE ((
	CS_CONTEXT      *context,
	CS_CHAR         *lang,
	CS_CHAR         *charset,
	CS_CHAR         *sortorder,
	CS_CHAR         *buffer,
	CS_INT          buflen
	));
extern CS_RETCODE CS_PUBLIC com_intl_envloc PROTOTYPE ((
	CS_CONTEXT      *context,
	CS_INT          lctype,
	CS_CHAR         *name,
	CS_INT          namelen
	));
extern CS_RETCODE CS_PUBLIC com_intl_load_lcs PROTOTYPE ((
	CS_CONTEXT      *context,
	CS_CHAR         *lang,
	CS_CHAR         *charset,
	CS_CHAR         *sortorder,
	CS_CHAR		*buf,
	CS_INT		buflen,
	CS_INT		*outlen,
	CS_VOID         **loccache_p
	));

/* comalloc.c */
extern CS_VOID * CS_PUBLIC comn_malloc PROTOTYPE((
	CS_UINT		size
	));
extern CS_VOID * CS_PUBLIC comn_realloc PROTOTYPE((
	CS_VOID		*ptr,
	CS_UINT		size
	));
extern CS_VOID * CS_PUBLIC comn_calloc PROTOTYPE((
	CS_UINT		nelem,	
	CS_UINT		size
	));
extern CS_VOID * CS_PUBLIC comn_free PROTOTYPE((
	CS_VOID		*ptr
	));


/* com_mtyp.c */
extern CS_VOID CS_PUBLIC comn_toupper PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*srcp,
	CS_BYTE		*destp
	));
extern CS_VOID CS_PUBLIC comn_tolower PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*srcp,
	CS_BYTE		*destp
	));
extern CS_BOOL CS_PUBLIC comn_isalpha PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*p
	));
extern CS_BOOL CS_PUBLIC comn_isupper PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*p
	));
extern CS_BOOL CS_PUBLIC comn_islower PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*p
	));
extern CS_BOOL CS_PUBLIC comn_isdigit PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*p
	));
extern CS_BOOL CS_PUBLIC comn_isxdigit PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*p
	));
extern CS_BOOL CS_PUBLIC comn_isspace PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*p
	));
extern CS_BOOL CS_PUBLIC comn_ispunct PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*p
	));
extern CS_BOOL CS_PUBLIC comn_isgraph PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*p
	));
extern CS_INT CS_PUBLIC comn_char_width PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*p
	));
extern CS_VOID CS_PUBLIC comn_inc_char PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		**p
	));
extern CS_INT CS_PUBLIC comn_disp_width PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*p
	));
extern CS_BYTE CS_PUBLIC comn_to_ascii PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*p
	));
extern CS_BYTE CS_PUBLIC comn_get_lex PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*p
	));
extern CS_VOID CS_PUBLIC comn_whole_char PROTOTYPE((
	CS_ATTRIB	*ca,
	CS_BYTE		*startp,
	CS_BYTE		*endp,
	CS_INT		*wcbytes,
	CS_INT		*pc_part1,
	CS_INT		*pc_part2,
	CS_INT		*nchars
	));
extern CS_BYTE * CS_PUBLIC comn_get_widthmap PROTOTYPE((
	CS_ATTRIB       *chatr
	));
extern CS_VOID CS_PUBLIC comn_str_to_ascii PROTOTYPE((
	CS_CHAR         *cp_src,
	CS_INT          src_len,
	CS_CHAR         *cp_dest,
	CS_INT          *dest_len,
	CS_ATTRIB       *chatr
	));
/* com_null.c */
extern CS_RETCODE CS_PUBLIC com_null_init PROTOTYPE((
	CS_CONTEXT *context
	));
extern CS_RETCODE CS_PUBLIC com_null_free PROTOTYPE((
	CS_CONTEXT *context
	));
extern CS_RETCODE CS_PUBLIC com_null_get PROTOTYPE((
	CS_CONTEXT *context,
	CS_DATAFMT *destfmt,
	CS_VOID *dest,
	CS_INT destlen,
	CS_INT *outlen
	));
extern CS_RETCODE CS_PUBLIC com_null_set PROTOTYPE((
	CS_CONTEXT *context,
	CS_INT nulltype,
	CS_VOID *null,
	CS_INT nulllen
	));
extern CS_RETCODE CS_PUBLIC com_null_reinstall PROTOTYPE((
	CS_CONTEXT *context,
	CS_INT nulltype
	));

/* com_path.c */
extern CS_RETCODE CS_PUBLIC com_path_ifile PROTOTYPE((
	CS_CONTEXT *context,
	CS_CHAR *pathname,
	CS_INT pathsize
	));

/* com_sort.c */
extern CS_INT CS_PUBLIC com_ps_dl_sqlhilo PROTOTYPE((
	CS_VOID *so,
	CS_CHAR *str1,
	CS_INT len1,
	CS_CHAR *str2,
	CS_INT len2
	));
extern CS_INT CS_PUBLIC com_spec_tord PROTOTYPE((
	CS_VOID *so,
	CS_CHAR *str1,
	CS_INT len1,
	CS_CHAR *str2,
	CS_INT len2
	));

/* com_st.c */
extern CS_BOOL CS_PUBLIC com_st_ver PROTOTYPE((
	CS_ST_TABLE *table,
	CS_PROTO_STATE state,
	CS_PROTO_EVENT event
	));
extern CS_BOOL CS_PUBLIC com_st_depend PROTOTYPE((
	CS_ST_TABLE *table,
	CS_PROTO_EVENT event,
	CS_EVENT *depend_event
	));
extern CS_STATE CS_PUBLIC com_st_trans PROTOTYPE((
	CS_ST_TABLE *table,
	CS_PROTO_STATE state,
	CS_PROTO_EVENT event
	));
extern CS_STATE CS_PUBLIC com_ns_trans PROTOTYPE((
	CS_NS_TABLE *table,
	CS_PROTO_STATE state,
	CS_PROTO_EVENT event
	));

/* com_str.c */
extern CS_INT CS_PUBLIC com_unsignstrcmp PROTOTYPE((
	unsigned char *str1,
	unsigned char *str2
	));
extern CS_INT CS_PUBLIC com_unsignstrncmp PROTOTYPE((
	unsigned char *str1,
	unsigned char *str2,
	int len
	));

/* com_vers.c */
extern CS_VOID CS_PUBLIC com_version PROTOTYPE((
	CS_INT *p_version,
	CS_BOOL *p_is_debug
	));

/* comutils.c */
extern CS_INT CS_PUBLIC com_memhilo PROTOTYPE((
	CS_BYTE *p1,
	CS_INT len1,
	CS_BYTE *p2,
	CS_INT len2
	));

/* cp850.c */
extern CS_TYPEMAP * CS_PUBLIC com_get_typemap PROTOTYPE((void));
extern CS_ATTRIB * CS_PUBLIC com_get_charattrib PROTOTYPE((void));

/* cvtdate.c */
extern int CS_PUBLIC com_cvtdatetochar PROTOTYPE((
	CS_DATETIME *dtp,
	char *buf,
	int len,
	int style,
	char **shortmths
	));
extern int CS_PUBLIC com_cvtdate4tochar PROTOTYPE((
	CS_DATETIME4 *dtp4,
	char *buf,
	int len,
	int style,
	char **shortmths
	));

/* cvtmny.c */
extern char * CS_PUBLIC com_cvtmnytochar PROTOTYPE((
	CS_MONEY *mp,
	char *cp,
	int len,
	int style
	));
extern char * CS_PUBLIC com_cvtmny4tochar PROTOTYPE((
	CS_MONEY4 *m4p,
	char *cp,
	int len,
	int style
	));
extern char * CS_PUBLIC com_precmnytochar PROTOTYPE((
	CS_MONEY *mp,
	char *cp,
	int len,
	int style,
	int prec
	));

/* datfuncs.c */
extern void CS_PUBLIC com_datecrack PROTOTYPE((
	CS_DATETIME *dtp,
	CS_DATEREC *pp
	));
extern void CS_PUBLIC com_timecrack PROTOTYPE((
	CS_DATETIME *dtp,
	CS_DATEREC *pp
	));
extern int CS_PUBLIC com_datepart PROTOTYPE((
	int part,
	CS_DATETIME *to,
	int firstday
	));
extern int CS_PUBLIC com_datename PROTOTYPE((
	int part,
	CS_DATETIME *dtp,
	char *cp,
	char **months,
	char **days
	));
extern int CS_PUBLIC com_datecmp PROTOTYPE((
	CS_DATETIME *d1,
	CS_DATETIME *d2
	));
extern void CS_PUBLIC com_datezero PROTOTYPE((
	CS_DATETIME *dateptr
	));
extern int CS_PUBLIC com_date4cmp PROTOTYPE((
	CS_DATETIME4 *d1,
	CS_DATETIME4 *d2
	));
extern void CS_PUBLIC com_date4zero PROTOTYPE((
	CS_DATETIME4 *dateptr
	));
extern void CS_PUBLIC com_setdatetime PROTOTYPE((
	CS_DATETIME *dateptr,
	CS_INT dtdays,
	CS_INT dttime
	));

/* dbgfuncs.c */
extern CS_VOID CS_PUBLIC com_dbginit PROTOTYPE((
	char *prog_name
	));
extern CS_VOID CS_PUBLIC com_chkfunc PROTOTYPE((
	void *p_func,
	char *file,
	int line
	));
extern CS_VOID CS_PUBLIC com_chkptr PROTOTYPE((
	char *p_ptr,
	char *file,
	int line
	));

/* iso_1.c */
extern CS_TYPEMAP * CS_PUBLIC com_get_typemap PROTOTYPE((void));
extern CS_ATTRIB * CS_PUBLIC com_get_charattrib PROTOTYPE((void));

/* mny4func.c */
extern CS_RETCODE CS_PUBLIC comn_mny4copy PROTOTYPE((
	CS_MONEY4 *mp1,
	CS_MONEY4 *mp2
	));
extern CS_RETCODE CS_PUBLIC comn_mny4minus PROTOTYPE((
	CS_MONEY4 *imp,
	CS_MONEY4 *omp
	));
extern CS_RETCODE CS_PUBLIC comn_mny4add PROTOTYPE((
	CS_MONEY4 *add1p,
	CS_MONEY4 *add2p,
	CS_MONEY4 *sump
	));
extern CS_RETCODE CS_PUBLIC comn_mny4sub PROTOTYPE((
	CS_MONEY4 *minp,
	CS_MONEY4 *subp,
	CS_MONEY4 *difp
	));
extern CS_RETCODE CS_PUBLIC comn_mny4divide PROTOTYPE((
	CS_MONEY4 *m1,
	CS_MONEY4 *m2,
	CS_MONEY4 *m3
	));
extern CS_RETCODE CS_PUBLIC comn_mny4mul PROTOTYPE((
	CS_MONEY4 *m1,
	CS_MONEY4 *m2,
	CS_MONEY4 *m3
	));
extern int CS_PUBLIC comn_mny4cmp PROTOTYPE((
	CS_MONEY4 *m1,
	CS_MONEY4 *m2
	));
extern void CS_PUBLIC comn_mny4zero PROTOTYPE((
	CS_MONEY4 *mny4ptr
	));

/* mnyfuncs.c */
extern CS_RETCODE CS_PUBLIC comn_mnycopy PROTOTYPE((
	CS_MONEY *mp1,
	CS_MONEY *mp2
	));
extern int CS_PUBLIC comn_mnyinit PROTOTYPE((
	CS_MONEY *mp,
	int trim
	));
extern int CS_PUBLIC comn_mnyndigit PROTOTYPE((
	CS_MONEY *mp,
	char *value
	));
extern CS_RETCODE CS_PUBLIC comn_mnyinc PROTOTYPE((
	CS_MONEY *mp
	));
extern CS_RETCODE CS_PUBLIC comn_mnydec PROTOTYPE((
	CS_MONEY *mp
	));
extern CS_RETCODE CS_PUBLIC comn_mnyminus PROTOTYPE((
	CS_MONEY *imp,
	CS_MONEY *omp
	));
extern int CS_PUBLIC comn_mnydown PROTOTYPE((
	CS_MONEY *mp,
	int dvsr
	));
extern CS_RETCODE CS_PUBLIC comn_mnyscale PROTOTYPE((
	CS_MONEY *mp,
	int mpier,
	int add
	));
extern CS_RETCODE CS_PUBLIC comn_mnyadd PROTOTYPE((
	CS_MONEY *add1p,
	CS_MONEY *add2p,
	CS_MONEY *sump
	));
extern CS_RETCODE CS_PUBLIC comn_mnysub PROTOTYPE((
	CS_MONEY *minp,
	CS_MONEY *subp,
	CS_MONEY *difp
	));
extern CS_RETCODE CS_PUBLIC comn_mnydivide PROTOTYPE((
	CS_MONEY *m1,
	CS_MONEY *m2,
	CS_MONEY *m3
	));
extern CS_RETCODE CS_PUBLIC comn_mnymul PROTOTYPE((
	CS_MONEY *m1,
	CS_MONEY *m2,
	CS_MONEY *m3
	));
extern void CS_PUBLIC comn_mnymaxpos PROTOTYPE((
	CS_MONEY *mp
	));
extern void CS_PUBLIC comn_mnymaxneg PROTOTYPE((
	CS_MONEY *mp
	));
extern int CS_PUBLIC comn_mnycmp PROTOTYPE((
	CS_MONEY *m1,
	CS_MONEY *m2
	));
extern void CS_PUBLIC comn_mnyzero PROTOTYPE((
	CS_MONEY *mnyptr
	));
extern void CS_PUBLIC comn_mnyxdiv PROTOTYPE((
	CS_MONEY *num,
	CS_MONEY *den,
	CS_MONEY *res
	));

/* numeaux.c */
extern CS_INT CS_PUBLIC comn_num_getlen PROTOTYPE((
	CS_INT	precision
	));
extern CS_INT CS_PUBLIC comn_num_getprec PROTOTYPE((
	CS_INT	length
	));

/* numfuncs.c */
extern CS_RETCODE CS_PUBLIC comn_numadd PROTOTYPE((
	CS_NUMERIC *add1p,
	CS_NUMERIC *add2p,
	CS_NUMERIC *sump
	));
extern CS_RETCODE CS_PUBLIC comn_numsub PROTOTYPE((
	CS_NUMERIC *minp,
	CS_NUMERIC *subp,
	CS_NUMERIC *diffp
	));
extern CS_RETCODE CS_PUBLIC comn_numdivide PROTOTYPE((
	CS_NUMERIC *dividend,
	CS_NUMERIC *divisor,
	CS_NUMERIC *quot
	));
extern CS_RETCODE CS_PUBLIC comn_nummul PROTOTYPE((
	CS_NUMERIC *m1,
	CS_NUMERIC *m2,
	CS_NUMERIC *result
	));
extern int CS_PUBLIC comn_numcmp PROTOTYPE((
	CS_NUMERIC *n1,
	CS_NUMERIC *n2
	));

/* roman8.c */
extern CS_TYPEMAP * CS_PUBLIC com_get_typemap PROTOTYPE((void));
extern CS_ATTRIB * CS_PUBLIC com_get_charattrib PROTOTYPE((void));

/* com_loca.c */
extern CS_RETCODE CS_PUBLIC comn_loc_alloc PROTOTYPE((
        CS_CONTEXT *context,
        CS_LOCALE **locptr
        ));
extern CS_RETCODE CS_PUBLIC comn_loc_drop PROTOTYPE((
        CS_CONTEXT *context,
        CS_LOCALE *locale
        ));
extern CS_RETCODE CS_PUBLIC comn_loc_drop_all PROTOTYPE((
        CS_CONTEXT *context
        ));
extern CS_BOOL CS_PUBLIC comn_loc_validate PROTOTYPE((
        CS_CONTEXT *context,
        CS_LOCALE *locale
        ));
extern CS_RETCODE CS_PUBLIC comn_loc_copy PROTOTYPE((
	CS_LOCALE *dest_locale,
	CS_LOCALE *src_locale
	));

/* com_time.c */
extern CS_INT CS_PUBLIC comn_dtloc_format PROTOTYPE((
        CS_CONTEXT *context,
        CS_LOCALE *locale
        ));
extern CS_BOOL CS_PUBLIC comn_dtloc_is12hour PROTOTYPE((
        CS_CONTEXT *context,
        CS_LOCALE *locale
        ));
extern CS_RETCODE CS_PUBLIC comn_time PROTOTYPE((
        CS_INT format,
        CS_BOOL is12hour,
        CS_CHAR *buffer,
        CS_INT buflen,
        CS_INT *outlen,
	CS_DATEREC *drec
        ));
/* comdtyp.c */
extern CS_INT CS_PUBLIC comn_typelen PROTOTYPE((
	CS_INT  type,
	CS_INT  len
	));
/* com_xlate.c */
extern CS_VOID CS_PUBLIC com_intl_will_xlate PROTOTYPE((
        CS_CONTEXT *context,
        CS_DATAFMT *srcfmt,
        CS_DATAFMT *destfmt,
        CS_INT 	*xlate_type
        ));
extern CS_RETCODE CS_PUBLIC com_intl_xlate PROTOTYPE((
        CS_CONTEXT *context,
        CS_DATAFMT *srcfmt,
        CS_VOID *src,
        CS_DATAFMT *destfmt,
        CS_VOID *dest,
	CS_INT	*srcused,
        CS_INT *destlen
        ));

/*com_perr.c */
extern CS_VOID CS_PUBLIC com_perr PROTOTYPE ((
	CS_CHAR         *err_string
	));

/* prototypes for thread routines which may be used as defaults for
** thread protection mechanism in CSLIB 
*/
extern CS_RETCODE CS_PUBLIC comn_create_mutex  PROTOTYPE((
	CS_VOID **mutex
	));
extern CS_RETCODE CS_PUBLIC comn_take_mutex  PROTOTYPE((
	CS_VOID *mutex
	));
extern CS_RETCODE CS_PUBLIC comn_release_mutex  PROTOTYPE((
	CS_VOID *mutex
	));
extern CS_RETCODE CS_PUBLIC comn_delete_mutex  PROTOTYPE((
	CS_VOID *mutex
	));

extern CS_RETCODE CS_PUBLIC comn_create_event  PROTOTYPE(( 
	CS_VOID **event
	));
extern CS_RETCODE CS_PUBLIC comn_waitfor_event  PROTOTYPE(( 
	CS_VOID *event, 
	CS_INT millisecs
	));
extern CS_RETCODE CS_PUBLIC comn_signal_event  PROTOTYPE(( 
	CS_VOID *event
	));
extern CS_RETCODE CS_PUBLIC comn_reset_event  PROTOTYPE(( 
	CS_VOID *event
	));
extern CS_RETCODE CS_PUBLIC comn_delete_event  PROTOTYPE(( 
	CS_VOID *event
	));

CS_RETCODE CS_PUBLIC comn_get_tid PROTOTYPE((
	CS_VOID *buffer,
	CS_INT buflen,
	CS_INT *outlen
	));

extern CS_RETCODE CS_PUBLIC comn_start_coroutine_mode  PROTOTYPE(( 
	CS_VOID 
	));

extern CS_RETCODE CS_PUBLIC comn_take_coroutine_control  PROTOTYPE(( 
	CS_VOID 
	));

extern CS_RETCODE CS_PUBLIC comn_release_coroutine_control  PROTOTYPE(( 
	CS_VOID 
	));

extern CS_RETCODE CS_PUBLIC comn_end_coroutine_mode  PROTOTYPE(( 
	CS_VOID 
	));

CS_END_EXTERN_C

#endif /* #ifndef _CPROTO_ */

#endif /* __COMNLIB_H__ */
