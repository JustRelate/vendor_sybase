


/* Sccsid %Z% %M% %I% %G% */

/*
**	Sybase OpenClient Version 5.0
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1991, 1992
**	All rights reserved
*/

/*
** csgen.h - This is the common INTERNAL header file for all 5.0 libraries.
*/
#ifndef __CSGEN_H__

#define __CSGEN_H__

/*
** include the port specific file
*/
#include	<csport.h>

/*****************************************************************************
**
** port overridable defines used in client/server applications
**
*****************************************************************************/

/*
** default in-line error cache sizes
*/
#ifndef CS_CLIENT_ERR_CACHE
#define CS_CLIENT_ERR_CACHE	10
#endif

#ifndef CS_SERVER_ERR_CACHE
#define CS_SERVER_ERR_CACHE	100
#endif

#ifndef CS_ALL_ERR_CACHE
#define CS_ALL_ERR_CACHE	100
#endif

/*
** number of CsErrorCache structures to internally cache in common lib
*/
#ifndef CS_ERR_CACHE_SIZE
#define CS_ERR_CACHE_SIZE	100
#endif


/*****************************************************************************
**
** generic defines used in client/server applications
**
*****************************************************************************/

/*
** Max length of a error-number mnemonic
** the error code is used to save sqlstate. The length of sqlstate
** defined in cspublic.h is 8. So we make CS_ECODELEN as 8 too here.
*/
#define CS_ECODELEN		8

/*
** define internal error codes
*/
#define CS_INTLIB_ERR		(CS_RETCODE)(CS_INTERNAL_ERR - 1)
#define CS_BUF_OFLOW		(CS_RETCODE)(CS_INTERNAL_ERR - 2)

/*
** valid context flags
*/
#define CS__CTX_ALLOCATED	(-997)
#define CS__CTX_DROPPED		0

/*
** context status bits. These are the shift values in the bit settings, not
** the actual masks.  The macros SETBIT(), CLRBIT(), TSTBIT() make use of
** these offsets.
*/
#define CS_CTXS_INERRHANDLER	0

/*
** Tag values
*/
#define CS_CMD_TAG		(-776)
#define CS_CON_TAG		(-777)
#define CS_CTX_TAG		(-778)

/*
** Defines for CS-Lib context handle status bits (ctxstatus).  These are the
** shift values in the bit settings, not the actual masks.
*/
#define CTX_CT_CTX		1	/* ct library bit */
#define CTX_NETWORK_CTX		2	/* network layer bit */
#define CTX_OPENSERVER_CTX	3	/* Open server bit */
#define CTX_CS_CTX		4	/* CS private bit */

/* 
** the define to reset sqlstate to non error state
*/
#define CS_NOERR_SQLSTATE     "00000"

/*****************************************************************************
**
** common datatype typedefs and structures used in client/server applications
**
*****************************************************************************/

/*
** Locale tag structure.
*/
typedef struct _cslocale
{
	CS_VOID		*collateptr;	/* Cached locale with this tag's
					** collating sequence information.
					*/
	CS_VOID		*ctypeptr;	/* Cached locale with this tag's
					** character set information.
					*/
	CS_VOID		*messageptr;	/* Cached locale with this tag's
					** error message information.
					*/
	CS_VOID		*monetaryptr;	/* Cached locale with this tag's
					** money/currency information.
					*/
	CS_VOID		*numericptr;	/* Cached locale with this tag's
					** numeric format information.
					*/
	CS_VOID		*timeptr;	/* Cached locale with this tag's
					** date/time format information.
					*/
	struct _cslocale *next;		/* Next locale tag in linked list. */
} CsLocale;

/*
** default value definition
*/
typedef struct _csdefval
{
	CS_VOID		*dventity;	/* ptr to the currently defined default
					** value.
					*/
	CS_INT		dvsize;		/* number of bytes that are stored in
					** the default value
					*/
	CS_INT		dvpadtype;	/*
					** padding type: binary or char
					*/
} CsDefVal;

/*
** null table management structure
*/
typedef struct _csnulltbl
{
	CsDefVal	*nullvals;	/* ptr to current null values
					** being used.
					*/
	int		nulldim;	/* current dimension of conversion
					** table
					*/
} CsNullTbl;

/*
** null management structure for user defined data type
*/
typedef struct _csusrnull
{
	CS_INT			dttype;		/* the user defined data type */
	CS_VOID			*dventity;	/* ptr to the currently 
						** defined default value.  
						*/
	CS_INT			dvsize;		/* number of bytes that are 
						**stored in the default value 
						*/
	struct _csusrnull	*nextnull;	/*
						** next structure in the list.
						*/
} CsUsrNull;

/*
** conversion table management structure
*/
typedef struct _csconverttbl
{
	CS_CONV_FUNC	*cvttbl;	/* ptr to current conversion table
					** being used
					*/	
	int		cvtdim;		/* current dimension of conversion
					** table
					*/
} CsConvertTbl;

/*
** define the conversion table data structure for user defined data type.
*/
typedef struct _csusrcvtfunc
{
	CS_INT			srctype;	/* source data type */
	CS_INT			desttype;	/* destination data type */
	CS_CONV_FUNC		cvtfunc;	/* conversion function */
	struct _csusrcvtfunc	*nextdest;	/* a pointer to a structure of 
						** another dest type
						** for the same source data type
						*/
	struct _csusrcvtfunc	*nextsrc;	/* a pointer to next such 
						** structure for another source
						** data type.
						*/
} CsUsrCvtFunc;

/*
** Define the context handle.
*/
typedef struct _cscontext
{
	CS_INT		ctxtag;		/* Tag for context handle.  */
	CS_INT		ctxstatus;	/* context status bit */
	CS_INT		ctxversion;	/* version of context handle.  */
	CS_LOCALE	*ctxlocale;	/* ptr to a locale in the global 
					** context structure for this context
					*/
	CS_LOCALE	*ctxdeflocale;	/* ptr to the standard localization
					** for this context 
					*/
	CsCtxGlobals	*ctxglobals;	/* Global structures shared among 
					** contexts 	
					*/
	CsConvertTbl	ctxcvttbl;	/* used to manage conversion table */
	CsUsrCvtFunc	*ctxusrcvttbl;	/* used to store conversion functions
					** for user defined data type
					*/
	CsNullTbl	ctxnulls;	/* used to manage default null data
					** values
					*/
	CsUsrNull	*ctxusrnulls;	/* pointer to a list of definitions of
					** null values for user defined data
					** type.
					*/
	CS_THREAD	*ctxthread;	/* pointer to the lock/unlock thread
					** primitives installed by the user
					*/
	int		ctxintlerr;	/* Intl-Lib error code */
	CS_VOID		*ctxctctx;	/* CT-Lib context information */
	CS_VOID		*ctxnetwork;	/* Network layer context */
	CS_VOID		*ctxopenserver; /* Open Server context */
	CS_VOID		*ctxcsctx;	/* CS-Lib private information */
	CS_THRDRES	*ctxmtx;	/* To protect the context from threads */
} CsContext;


/*
** Define the loginfo structure.  This is just a copy of the old
** DBLOGINFO structure.  It needs to be updated to support 5.0
*/
typedef struct _csloginfo
{
        CS_BYTE tds_level[4];   /* TDS version                          */
        CS_INT  packet_size;    /* TDS packet size to use               */
        CS_BYTE flt8_type;      /* float type on this platform          */
        CS_BYTE flt4_type;      /* real type on this platform           */
        CS_BYTE int4_type;      /* int4 type on this platform           */
        CS_BYTE int2_type;      /* int2 type on this platform           */
        CS_BYTE date_type;      /* datetime type on this platform       */
        CS_BYTE char_type;      /* char type on this platform           */
        CS_BYTE noshort;        /* convert short values to long values? */
        CS_BYTE language[30];   /* language to use on connection        */
        CS_BYTE langlen;        /* length of language[]                 */
        CS_BYTE setlang;        /* language[] valid?                    */
        CS_BYTE charset[30];    /* charset name on connection           */
        CS_BYTE charsetlen;     /* length of charset[]                  */
        CS_BYTE setcharset;     /* charset[] valid?                     */
        CS_BYTE ldmpld;         /* Dump/load indicator.                 */
	CS_BYTE	lseclogin;	/* security login options 		*/
	CS_BYTE	lsecbulk;	/* security bulk copy options 		*/
	CS_BYTE reqcap[16];	/* request capabilities			*/
	CS_BYTE respcap[16];	/* response capabilities		*/

	/*
	** The next set of fields are not part of the passthru mechanism.
	** These fields are in this structure so that CT-Lib users can
	** pass login properties from one connection handle to another
	** connection handle using the ct_getloginfo()/ct_setloginfo()
	** APIs.
	**
	** The field setctprops indicates whether or not these fields
	** have been set.  ct_getloginfo() will set this field to 1 when
	** moving information into this structure.  Open Server and DB-Lib
	** will not.  ct_setloginfo() will then use this field to 
	** determine if these fields have valid values.
	*/
	CS_BYTE	setctprops;	/* CT-Lib login properties set		*/
	CS_BYTE	appname[30];	/* application name			*/
	CS_BYTE applen;		/* length of application name		*/
	CS_BYTE	hostname[30];	/* host name				*/
	CS_BYTE hostlen;	/* length of host name			*/
	CS_BYTE password[30];	/* password				*/
	CS_BYTE pwdlen;		/* length of password			*/
	CS_BYTE	username[30];	/* user name 				*/
	CS_BYTE userlen;	/* length of user name.			*/
	CS_LOCALE *locale;	/* Pointer to CS_LOCALE structure	*/
	
} CsLoginfo;

#endif /* __CSGEN_H__ */
