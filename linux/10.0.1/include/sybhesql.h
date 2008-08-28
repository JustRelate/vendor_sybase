/*
**
**	Sybase Precompiler System 10
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1993
**	All rights reserved
**
**	%M%    %I%    %G%    %U%
**
*/

/*
** sybhesql.h - this is the header file needed by users for the 
** 	    System 10 Precompiler
*/

#ifndef __SYBHESQL_H__
#define __SYBHESQL_H__

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctpublic.h> 

#ifndef _SQL_SCOPE
#define _SQL_SCOPE extern
#endif	/* _SQL_SCOPE */
/*
** internal error table of types, codes, states and messages
*/
#define _SQL_INTRERR_25001	(CS_INT) 0	
#define _SQL_INTRERR_25002	(CS_INT) 1	
#define _SQL_INTRERR_25003	(CS_INT) 2	
#define _SQL_INTRERR_25004	(CS_INT) 3	
#define _SQL_INTRERR_25005	(CS_INT) 4	
#define _SQL_INTRERR_25006	(CS_INT) 5	
#define _SQL_INTRERR_25007	(CS_INT) 6	
#define _SQL_INTRERR_25008	(CS_INT) 7	
#define _SQL_INTRERR_25009	(CS_INT) 8	
#define _SQL_INTRERR_25010	(CS_INT) 9
#define _SQL_INTRERR_25011	(CS_INT) 10
#define _SQL_INTRERR_25012	(CS_INT) 11
#define _SQL_INTRERR_25013	(CS_INT) 12
#define _SQL_INTRERR_25014	(CS_INT) 13
#define _SQL_INTRERR_25015	(CS_INT) 14
#define _SQL_INTRERR_25016	(CS_INT) 15
#define _SQL_INTRERR_25017	(CS_INT) 16
#define _SQL_INTRERR_25018	(CS_INT) 17

/* object types (for _sqlprolog(...,_sqlObjType,...) */
#define _SQL_CONNECT_TYPE	(CS_INT) 0
#define _SQL_CURSOR_TYPE	(CS_INT) 1
#define _SQL_DYNSTMT_TYPE	(CS_INT) 2
#define _SQL_DYNDESC_TYPE	(CS_INT) 3
#define _SQL_NOCONNECT_TYPE	(CS_INT) 4
#define _SQL_DIAG_TYPE		(CS_INT) 5
/* operation types (for _sqlprolog(...,_sqlOperation,...) */
#define _SQL_CREATE		(CS_INT) 101
#define _SQL_GET		(CS_INT) 102
#define _SQL_DESTROY		(CS_INT) 103
/*
** special 'Userdata' object-type for keeping a list of dynamic
** cursors which have been declared upon dynamic statements
*/
#define _SQL_STMT_CURSOR_TABLE 99
#define _SQL_DESCRIPTOR_NAME 98
#define _SQL_ESQL_CONTEXT 97

typedef struct { 
    CS_CONTEXT		*ctx;		/* the global context handle */
    CS_OBJNAME		connName;	/* connection name */
    CS_OBJDATA		conn; 		/* connection handles */
    CS_OBJNAME		currentName;	/* 'current' connection name */
    CS_OBJDATA		current; 	/* 'current' connection info */
    CS_OBJNAME		curName; 	/* cursor name */
    CS_OBJDATA		cur; 		/* cursor handles */
    CS_OBJNAME		stmtName; 	/* statement name */
    CS_OBJDATA		stmt; 		/* statement handles */
    CS_OBJNAME		descName; 	/* descriptor name */
    CS_OBJDATA		desc; 		/* descriptor handles */
    CS_BOOL		bind;		/* TRUE -> binds needed before fetch
    					** on current cursor */
    CS_BOOL		doDecl;		/* TRUE -> object did not exist, 
    					** it must be declared/initialized */
    /*
    ** variables used for control of flow, looping, retrieving
    ** status and results from cs/ct lib calls
    */
    CS_INT		csfalse;
    CS_INT		Level3;
    CS_INT		cstrue;
    CS_INT		descSize;
    CS_INT		found;
    CS_INT		intvar;
    CS_INT		loopvar1;
    CS_INT		outlen;
    CS_INT		resloop;
    CS_INT		restype;
    CS_INT		retcode;
    CS_INT		rowsread;
    CS_SMALLINT		shortvar;
    CS_VOID		*threadId;
    CS_INT		threadIdLen;
    /*
    ** Data Formats -- some utility ones, and a bunch of pre-initialized
    ** ones for specific datatypes
    */
    CS_DATAFMT		dfmtDFMT_NAME;
    CS_DATAFMT		dfmtUTIL;
    CS_DATAFMT		dfmtNULLCHAR;
    CS_DATAFMT		dfmtDYN;
    CS_DATAFMT		dfmtCS_LONG_TYPE;
    CS_DATAFMT		dfmtCS_CHAR_TYPE;
    CS_DATAFMT		dfmtCS_VARCHAR_TYPE;
    CS_DATAFMT		dfmtCS_BINARY_TYPE;
    CS_DATAFMT		dfmtCS_VARBINARY_TYPE;
    CS_DATAFMT		dfmtCS_TEXT_TYPE;
    CS_DATAFMT		dfmtCS_IMAGE_TYPE;
    CS_DATAFMT		dfmtCS_TINYINT_TYPE;
    CS_DATAFMT		dfmtCS_SMALLINT_TYPE;
    CS_DATAFMT		dfmtCS_INT_TYPE;
    CS_DATAFMT		dfmtCS_REAL_TYPE;
    CS_DATAFMT		dfmtCS_FLOAT_TYPE;
    CS_DATAFMT		dfmtCS_BIT_TYPE;
    CS_DATAFMT		dfmtCS_DATETIME_TYPE;
    CS_DATAFMT		dfmtCS_DATETIME4_TYPE;
    CS_DATAFMT		dfmtCS_MONEY_TYPE;
    CS_DATAFMT		dfmtCS_MONEY4_TYPE;
    CS_DATAFMT		dfmtCS_NUMERIC_TYPE;
    CS_DATAFMT		dfmtCS_DECIMAL_TYPE;
    /*
    ** Temporary variables for holding values that must be converted
    ** from 'Literal' representations
    */
    CS_CHAR		temp_char[256];
    CS_BIT		temp_bit[1];
    CS_INT		temp_int;
    CS_INT		temp_hex;
    CS_BINARY		temp_binary[256];
    CS_DATETIME		temp_datetime;
    CS_MONEY		temp_money;
    CS_NUMERIC		temp_numeric;

} _SQL_CT_HANDLES; 
/*
** table for SQL ANSI, CT-Library Descriptor type values
** the ordering of the table is based on the ANSI SQL document
** for dynamic descriptor data types
*/
typedef struct _sql_desc_types
{
    CS_INT	_sql_ctlib_type;
    CS_INT	_sql_ansi_type;
} _sqldesctype;


/*
** function prototypes
*/

/* sybtesql.h */
#if defined(__cplusplus)
extern "C" {
#endif
_SQL_SCOPE CS_VOID _sqlinitctx  PROTOTYPE((
	_SQL_CT_HANDLES **_sql,
	CS_INT	_sqlVersion,
	CS_INT	_sqlObjType,
	SQLCA *_sqlSqlca,
	long *SQLCODE,
	CS_CHAR *SQLSTATE
));
_SQL_SCOPE CS_VOID _sqlInitName  PROTOTYPE((
	CS_OBJNAME	*name,
	CS_INT		namet
));
_SQL_SCOPE CS_VOID _sqlInitData  PROTOTYPE((
	CS_OBJDATA	*data
));
_SQL_SCOPE CS_VOID _sqlInitDfmt  PROTOTYPE((
	CS_DATAFMT	*data,
	CS_INT		datat
));
_SQL_SCOPE CS_INT _sqlprolog  PROTOTYPE((
	_SQL_CT_HANDLES *_sql,
	CS_INT _sqlObjType,
	CS_INT _sqlOperation,
	SQLCA *_sqlSqlca,
	long *SQLCODE,
	CS_CHAR *SQLSTATE
));
_SQL_SCOPE CS_INT _sqlCurCName  PROTOTYPE((
	_SQL_CT_HANDLES *_sql,
	CS_OBJNAME *_sqlObjname
));
_SQL_SCOPE CS_INT _sqlCurOp  PROTOTYPE((
	CS_INT _sqlOper,
	_SQL_CT_HANDLES *_sql
));
_SQL_SCOPE CS_INT _sqlStmOp  PROTOTYPE((
	CS_INT _sqlOper,
	_SQL_CT_HANDLES *_sql,
	SQLCA *_sqlSqlca,
	long *SQLCODE,
	CS_CHAR *SQLSTATE
));
_SQL_SCOPE CS_INT _sqlDropStmtCurs  PROTOTYPE((
	_SQL_CT_HANDLES *_sql
));
_SQL_SCOPE CS_INT _sqlDynCur  PROTOTYPE((
	_SQL_CT_HANDLES *_sql
));
_SQL_SCOPE CS_INT _sqlDescOp  PROTOTYPE((
	CS_INT _sqlOper,
	_SQL_CT_HANDLES *_sql
));
_SQL_SCOPE CS_INT _sqlepilog  PROTOTYPE((
	_SQL_CT_HANDLES *_sql,
	CS_INT _sqlObjType,
	SQLCA *_sqlSqlca,
	long *SQLCODE,
	CS_CHAR *SQLSTATE
));
_SQL_SCOPE void _sqlctxerr  PROTOTYPE((
	SQLCA *_sqlSqlca,
	long *SQLCODE,
	CS_CHAR *SQLSTATE,
	CS_INT _sqlintrerr_type
));
_SQL_SCOPE void _sqlsetintrerr  PROTOTYPE((
	_SQL_CT_HANDLES *_sql,
	CS_INT _sqlintrerr_type
));
_SQL_SCOPE CS_INT _sqlcsdiag  PROTOTYPE((
	CS_CONTEXT *_sqlctx,
	CS_INT _sqlOper,
	CS_INT _sqlerrindex,
	SQLCA *_sqlSqlca,
	long *SQLCODE,
	CS_CHAR *SQLSTATE
));
_SQL_SCOPE CS_INT _sqlworst  PROTOTYPE((
	_SQL_CT_HANDLES *_sql,
	CS_BOOL		_sqlHaveConn
));
_SQL_SCOPE CS_INT _sqlctdiag  PROTOTYPE((
	_SQL_CT_HANDLES *_sql,
	CS_INT _sqlOper,
	CS_INT _sqlerrindex,
	SQLCA *_sqlSqlca,
	long *SQLCODE,
	CS_CHAR *SQLSTATE
));
_SQL_SCOPE CS_INT _sqldtcnv PROTOTYPE((
	_SQL_CT_HANDLES *_sql,
	CS_INT _sqlType,
	CS_INT _sqlOper
));
_SQL_SCOPE CS_VOID _sqlmemzero PROTOTYPE((
	CS_VOID	*_sqlBuf,
	CS_INT	_sqlSize
));
_SQL_SCOPE CS_VOID _sqlmemcpy PROTOTYPE((
	CS_VOID	*_sqlsrc,
	CS_VOID	*_sqldest,
	CS_INT	_sqlSize
));
_SQL_SCOPE CS_RETCODE _sqlInitThreadId PROTOTYPE((
	CS_CONTEXT	*_sqlctx,
	CS_VOID		**thread,
	CS_INT		*threadLen,
	CS_VOID		*buff,
	CS_INT		bufLen
));
_SQL_SCOPE CS_RETCODE _sqlTakeMutex PROTOTYPE((
	CS_CONTEXT	*_sqlctx,
	CS_THRDRES	**mutex
));
_SQL_SCOPE CS_RETCODE _sqlReleaseMutex PROTOTYPE((
	CS_CONTEXT	*_sqlctx,
	CS_THRDRES	*mutex
));
_SQL_SCOPE CS_CHAR *_sqlcheckstr PROTOTYPE((
	_SQL_CT_HANDLES *_sql,
	char	*_sqlHostString
));
#if defined(__cplusplus)
}
#endif

#define       _sql_MIN(a,b)   ((b)>(a)?(a):(b))
#define	SQLNULLSTR(s)	((*s == '\0')?(" "):(s))

/*
** Compatibility section.
*/
#define	SQLINDICATOR	CS_SMALLINT
/*
** Bogus 'length' to use when paraming/binding char *;
*/
#define _SQL_PCHAR_LEN	((CS_INT) ~0x80000000L)

#endif /* __SYBHESQL_H__ */
