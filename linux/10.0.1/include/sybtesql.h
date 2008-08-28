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
** sybtesql.h - this is the trailer header file needed by users for the 
** 	    System 10 Precompiler
*/

#ifndef __SYBTESQL_H__
#define __SYBTESQL_H__

/*
** Table of error messages raised by generated code
*/
static CS_CLIENTMSG _sql_intrerr[] = {
   { CS_SV_API_FAIL, (CS_MSGNUM) 25001, 
   	"Unrecoverable error occurred.",
	(CS_INT) 29, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZZ000", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25002, 
   	"Internal error occurred.",
	(CS_INT) 24, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZA000", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25003, 
   	"Unexpected CS_COMPUTE_RESULT received.",
	(CS_INT) 39, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZD000", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25004, 
   	"Unexpected CS_CURSOR_RESULT received.",
	(CS_INT) 38, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZE000", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25005, 
   	"Unexpected CS_PARAM_RESULT received.",
	(CS_INT) 37, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZF000", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25006, 
   	"Unexpected CS_ROW_RESULT received.",
	(CS_INT) 35, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZG000", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25007, 
   	"No message(s) returned for sqlca, SQLCODE or SQLSTATE.",
	(CS_INT) 54, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZB000", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25008, 
   	"Connection has not been defined yet.",
	(CS_INT) 36, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZC000", (CS_INT) 5 },
   { CS_SV_INFORM, (CS_MSGNUM) 25009, 
   	"Unexpected CS_STATUS_RESULT received.",
	(CS_INT) 38, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "00102", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25010, 
   	"Unexpected CS_DESCRIBE_RESULT received.",
	(CS_INT) 40, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZI000", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25011, 
   	"Data exception -- error in assignment of item descriptor type.",
	(CS_INT) 63, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "22005", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25012, 
   	"Memory allocation failure.",
	(CS_INT) 26, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZJ000", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25013, 
   	"SQL-Server must be version 10 or greater.",
	(CS_INT) 41, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZK000", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25014, 
   	"Data exception -- Unterminated C string.",
	(CS_INT) 40, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "22024", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25015, 
   	"Error retrieving thread identification.",
	(CS_INT) 39, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZL000", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25016, 
   	"Error Initializing Client Library.",
	(CS_INT) 34, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZM000", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25017, 
   	"Error Taking a Mutex.",
	(CS_INT) 21, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "ZN000", (CS_INT) 5 },
   { CS_SV_API_FAIL, (CS_MSGNUM) 25018, 
   	"Connection name in use.",
	(CS_INT) 23, (CS_INT) 0, "", (CS_INT) 0,
	(CS_INT) 0, "08002", (CS_INT) 5 }
};
/*
** table to convert between CS_XXX_TYPE values and Dynamic Descriptor TYPE's
*/
#define _SQL_MAX_DESC_TYPES	20
static _sqldesctype _sqldesctbl[_SQL_MAX_DESC_TYPES] = 
{
    {	CS_CHAR_TYPE,		1   },
    { 	CS_BINARY_TYPE,		-5  },
    { 	CS_LONGCHAR_TYPE,	-2  },
    { 	CS_LONGBINARY_TYPE,	-7  },
    { 	CS_TEXT_TYPE,		-3  },
    { 	CS_IMAGE_TYPE,		-4  },
    { 	CS_TINYINT_TYPE,	-8  },
    { 	CS_SMALLINT_TYPE,	5   },
    { 	CS_INT_TYPE,		4   },
    { 	CS_REAL_TYPE,		7   },
    { 	CS_FLOAT_TYPE,		8   },
    { 	CS_BIT_TYPE,		14  },
    { 	CS_DATETIME_TYPE,	9   },
    { 	CS_DATETIME4_TYPE,	-9  },
    { 	CS_MONEY_TYPE,		-10 },
    { 	CS_MONEY4_TYPE,		-11 },
    { 	CS_NUMERIC_TYPE,	2   },
    { 	CS_DECIMAL_TYPE,	3   },
    { 	CS_VARCHAR_TYPE,	12  },
    {	CS_VARBINARY_TYPE,	-6  }
};

static CS_THRDRES *_sql_mutex = (CS_THRDRES *) NULL;

_SQL_SCOPE CS_VOID
_sqlinitctx( _sql, _sqlVersion, _sqlObjType,  _sqlSqlca, SQLCODE, SQLSTATE )
  _SQL_CT_HANDLES      ** _sql; /* esql context handle */
  CS_INT	_sqlVersion; /* version of cs/ct libs to use */
  CS_INT	_sqlObjType; /* connection/cursor/... */
  SQLCA        * _sqlSqlca;
  long       * SQLCODE;
  CS_CHAR      * SQLSTATE;
{
	CS_INT	_sqlretcode = CS_SUCCEED;
	CS_CONTEXT	*_sqlctx;
	CS_OBJNAME	_sqlDesc;
	CS_OBJDATA	_sqlData;
#ifndef _SQL_THREAD_ID_SIZE
#define _SQL_THREAD_ID_SIZE	256
#endif	/* _SQL_THREAD_ID_SIZE */
	CS_BYTE		tmpTid[_SQL_THREAD_ID_SIZE];
	
	/* 
	** initialize the esql context handle for failure
	*/
	*_sql = (_SQL_CT_HANDLES *) NULL;
	/*
	** get the global context handle
	*/
	_sqlretcode = cs_ctx_global(_sqlVersion, &_sqlctx);
	if (_sqlretcode != CS_SUCCEED)
	{
		_sqlctxerr(_sqlSqlca, SQLCODE, SQLSTATE, _SQL_INTRERR_25001);
		return;
	}

	/*
	** Clear diagnostics so we start fresh for this statement
	*/
	if (_sqlretcode == CS_SUCCEED &&
		_sqlObjType != _SQL_DIAG_TYPE)
	{
		_sqlretcode = _sqlcsdiag(_sqlctx, CS_CLEAR, CS_UNUSED, 
					 _sqlSqlca, SQLCODE, SQLSTATE);
	}

	/* Retrieve the _sql state information, initialize a CS_OBJNAME
	** structure to look for this information if it already exists */
    	_sqlInitName(&_sqlDesc, _SQL_ESQL_CONTEXT);
	/* initialize this thread's id. */
	if (_sqlretcode == CS_SUCCEED)
	{
	_sqlretcode = _sqlInitThreadId(_sqlctx,
			&_sqlDesc.thread,
			&_sqlDesc.threadlen,
			(CS_VOID *) tmpTid, sizeof(tmpTid));
		if (_sqlretcode != CS_SUCCEED)
		{
			/* thread id failure */
			_sqlctxerr(_sqlSqlca, SQLCODE, SQLSTATE, 
				_SQL_INTRERR_25015);
			return;
		}
	}
    	_sqlInitData(&_sqlData);
	_sqlData.buflen = sizeof (_SQL_CT_HANDLES *);
	_sqlData.buffer = _sql;
	_sqlretcode = cs_objects(_sqlctx, CS_GET, 
			&_sqlDesc, &_sqlData);
	if (_sqlretcode != CS_SUCCEED)
	{
		/* something Really wrong */
		_sqlcsdiag(_sqlctx, CS_GET, 1, 
					 _sqlSqlca, SQLCODE, SQLSTATE);
		return;
	}
	if (_sqlData.actuallyexists == CS_TRUE)
	{
	    /* We have a esql handle, and we've just restored it, return */
		return;
	}
	/* If we get here, we need to initialize the esql-handle. */
	/* Initialize ct-lib */
	_sqlretcode = ct_init(_sqlctx, _sqlVersion);
	if (_sqlretcode != CS_SUCCEED)
	{
		/* ct_init failure */
		_sqlctxerr(_sqlSqlca, SQLCODE, SQLSTATE, _SQL_INTRERR_25016);
		return;
	}
	*_sql = (_SQL_CT_HANDLES *) malloc(sizeof (_SQL_CT_HANDLES));
	if (*_sql == (_SQL_CT_HANDLES *) NULL)
	{
		/* memory allocation failure */
		_sqlctxerr(_sqlSqlca, SQLCODE, SQLSTATE, _SQL_INTRERR_25012);
		return;
	}
	/* Initialize the _sql esql state information structure */
    	(*_sql)->ctx = _sqlctx;
	/* Save a copy of this thread's id */
	if (_sqlDesc.threadlen > 0)
	{
 		if (((*_sql)->threadId = (CS_VOID *) 
 			malloc(_sqlDesc.threadlen + 1))
			== (CS_VOID *) NULL)
		{
			/* memory allocation failure */
			_sqlctxerr(_sqlSqlca, SQLCODE, SQLSTATE, 
				_SQL_INTRERR_25012);
			free(*_sql);
			*_sql = (_SQL_CT_HANDLES *) NULL;
			return;
		}
		_sqlmemcpy( _sqlDesc.thread, (*_sql)->threadId, 
			_sqlDesc.threadlen);
	}
	(*_sql)->threadIdLen = _sqlDesc.threadlen;
    	_sqlInitName(&(*_sql)->connName, CS_CONNECTNAME);
#ifndef CONNECTIONS_ARE_SHARED_ACROSS_THREADS
	(*_sql)->connName.threadlen = (*_sql)->threadIdLen;
	(*_sql)->connName.thread = (*_sql)->threadId;
#endif /* CONNECTIONS_ARE_SHARED_ACROSS_THREADS */
    	_sqlInitData(&(*_sql)->conn);
	_sqlInitName(&(*_sql)->currentName, CS_CURRENT_CONNECTION);
	(*_sql)->currentName.threadlen = (*_sql)->threadIdLen;
	(*_sql)->currentName.thread = (*_sql)->threadId;
	_sqlInitData(&(*_sql)->current);
	_sqlInitName(&(*_sql)->curName, CS_CURSORNAME);
	(*_sql)->curName.threadlen = (*_sql)->connName.threadlen;
	(*_sql)->curName.thread = (*_sql)->threadId;
	_sqlInitData(&(*_sql)->cur);
	(*_sql)->cur.buflen = sizeof(CS_BOOL);
	_sqlInitName(&(*_sql)->stmtName, CS_STATEMENTNAME);
	(*_sql)->stmtName.threadlen = (*_sql)->connName.threadlen;
	(*_sql)->stmtName.thread = (*_sql)->threadId;
	_sqlInitData(&(*_sql)->stmt);
	_sqlInitName(&(*_sql)->descName, _SQL_DESCRIPTOR_NAME);
#ifdef DESCRIPTOR_SCOPE_IS_THREAD
	(*_sql)->descName.threadlen = (*_sql)->threadIdLen;
	(*_sql)->descName.thread = (*_sql)->threadId;
#endif /* DESCRIPTOR_SCOPE_IS_THREAD */
	_sqlInitData(&(*_sql)->desc);
	(*_sql)->bind = CS_TRUE;
	(*_sql)->descSize = (CS_INT) 1;
    	(*_sql)->doDecl = CS_TRUE;
	(*_sql)->csfalse = CS_FALSE;
	(*_sql)->Level3 = CS_OPT_LEVEL3;
	(*_sql)->cstrue = CS_TRUE;
	(*_sql)->retcode = CS_SUCCEED;
    /*
    ** Data Formats -- some utility ones, and a bunch of pre-initialized
    ** ones for specific datatypes
    */
	_sqlInitDfmt(&(*_sql)->dfmtDFMT_NAME, CS_UNUSED);
	_sqlInitDfmt(&(*_sql)->dfmtUTIL, CS_UNUSED);
	_sqlInitDfmt(&(*_sql)->dfmtNULLCHAR, CS_CHAR_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtDYN, CS_UNUSED);
	_sqlInitDfmt(&(*_sql)->dfmtCS_LONG_TYPE, CS_LONG_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_CHAR_TYPE, CS_CHAR_TYPE);
	(*_sql)->dfmtCS_CHAR_TYPE.format |= CS_FMT_PADBLANK;
	_sqlInitDfmt(&(*_sql)->dfmtCS_VARCHAR_TYPE, CS_VARCHAR_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_BINARY_TYPE, CS_BINARY_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_VARBINARY_TYPE, CS_VARBINARY_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_TEXT_TYPE, CS_TEXT_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_IMAGE_TYPE, CS_IMAGE_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_TINYINT_TYPE, CS_TINYINT_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_SMALLINT_TYPE, CS_SMALLINT_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_INT_TYPE, CS_INT_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_REAL_TYPE, CS_REAL_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_FLOAT_TYPE, CS_FLOAT_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_BIT_TYPE, CS_BIT_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_DATETIME_TYPE, CS_DATETIME_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_DATETIME4_TYPE, CS_DATETIME4_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_MONEY_TYPE, CS_MONEY_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_MONEY4_TYPE, CS_MONEY4_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_NUMERIC_TYPE, CS_NUMERIC_TYPE);
	_sqlInitDfmt(&(*_sql)->dfmtCS_DECIMAL_TYPE, CS_DECIMAL_TYPE);

	/* Initialization complete, save the esql handle for next time */
	_sqlretcode = cs_objects(_sqlctx, CS_SET, 
			&_sqlDesc, &_sqlData);

	if (_sqlretcode != CS_SUCCEED)
	{
		free(*_sql);
		*_sql = (_SQL_CT_HANDLES *) NULL;
	}
	return;
}

_SQL_SCOPE CS_VOID
_sqlInitName( name, namet )
  CS_OBJNAME	*name;
  CS_INT	namet;
{
	name->thinkexists = CS_FALSE;
	name->object_type = namet;
	name->lnlen = CS_UNUSED;
	name->fnlen = CS_UNUSED;
	name->scopelen = CS_UNUSED;
	name->threadlen = CS_UNUSED;
	return;
}
_SQL_SCOPE CS_VOID
_sqlInitData( data )
  CS_OBJDATA	*data;
{
	data->actuallyexists = CS_FALSE;
	data->connection = (CS_CONNECTION *) NULL;
	data->command = (CS_COMMAND *) NULL;
	data->buffer = (CS_VOID *) NULL;
	data->buflen = CS_UNUSED;
	return;
}
_SQL_SCOPE CS_VOID
_sqlInitDfmt( data, datat )
  CS_DATAFMT	*data;
  CS_INT	datat;
{
	data->name[0] = '\0';
	data->namelen = (CS_INT) 0;
	data->datatype = datat;
	switch (datat)
	{
		case CS_CHAR_TYPE:
		case CS_TEXT_TYPE:
			data->format = CS_FMT_NULLTERM;
			break;
		default:
			data->format = CS_FMT_UNUSED;
			break;
	}
	data->maxlength = 0;
	switch (datat)
	{
		case CS_NUMERIC_TYPE:
		case CS_DECIMAL_TYPE:
			data->scale = CS_SRC_VALUE;
			data->precision = CS_SRC_VALUE;
			break;
		default:
			data->scale = CS_DEF_SCALE;
			data->precision = CS_DEF_PREC;
	}
	data->status = (CS_INT) 0;
	data->count = (CS_INT) 1;
	data->usertype = (CS_INT) 0;
	data->locale = (CS_LOCALE *) NULL;
	return;
}

_SQL_SCOPE CS_INT 
_sqlprolog(_sql, _sqlObjType,
	 _sqlOperation, _sqlSqlca, SQLCODE, SQLSTATE)
  _SQL_CT_HANDLES      * _sql;/* ct_lib connection/command _sql */
  CS_INT	 _sqlObjType; /* connection/cursor/statement/dyndesc object */
  CS_INT 	 _sqlOperation; /* GET, CREATE, DESTROY */
  SQLCA        * _sqlSqlca;
  long       * SQLCODE;
  CS_CHAR      * SQLSTATE;
{
    CS_INT   		_sqlretcode = CS_SUCCEED;

	/* Get the connection info for specified or 'current' connection */
	if (_sqlOperation == _SQL_CREATE)
	{
		_sql->connName.thinkexists = CS_FALSE;
	}
	else
	{
		_sql->connName.thinkexists = CS_TRUE;
	}
	if (_sqlObjType != _SQL_DYNDESC_TYPE)
	{
		/* do not need a connection to use Dynamic descriptors */
		/* 
		** If the connection-name is not specified, get the
		** current connection-name
		*/
		if (_sql->connName.lnlen == CS_UNUSED)
		{
			_sqlretcode = _sqlCurCName(_sql, 
					&_sql->connName);
		}
		/* retrieve the connection data */
		if (_sqlretcode == CS_SUCCEED)
		{
			_sqlretcode = cs_objects(_sql->ctx, CS_GET, 
				&_sql->connName, &_sql->conn);
		}
		/*
		** clear out any old diagnostics on this connection and save the 
		** connection/command _sql
		*/
		if (_sqlretcode == CS_SUCCEED && 
			_sql->conn.actuallyexists == CS_TRUE &&
			_sqlObjType != _SQL_DIAG_TYPE)
		{
			_sqlretcode = _sqlctdiag(_sql,
						CS_CLEAR, CS_UNUSED, 
						_sqlSqlca, SQLCODE, SQLSTATE);
		}
	}
	/* 
	** get info for the object we are REALLY after
	*/
	if ((_sqlretcode == CS_SUCCEED) || (_sqlObjType == _SQL_DYNDESC_TYPE))
	{
	    switch(_sqlObjType)
	    {
		case _SQL_CURSOR_TYPE:		/* SQL Cursor */
			_sql->curName.lnlen = 
				_sql->connName.lnlen;
			_sqlmemcpy( _sql->connName.last_name,
				_sql->curName.last_name, 
				_sql->connName.lnlen);
			_sqlretcode = _sqlCurOp(_sqlOperation, _sql);
			break;
		case _SQL_DYNSTMT_TYPE:		/* Dynamic SQL Statement */
			_sql->stmtName.lnlen = 
				_sql->connName.lnlen;
			_sqlmemcpy( _sql->connName.last_name,
				_sql->stmtName.last_name, 
				_sql->connName.lnlen);
			_sqlretcode = _sqlStmOp(_sqlOperation, _sql,
						_sqlSqlca, SQLCODE, SQLSTATE);
			break;
		case _SQL_CONNECT_TYPE:		/* connection */
			if ((_sqlOperation == _SQL_CREATE) &&
			    (_sql->conn.actuallyexists == CS_FALSE))
			{
				_sql->doDecl = CS_TRUE;
			}
			else if ((_sqlOperation == _SQL_CREATE) &&
			    (_sql->conn.actuallyexists == CS_TRUE))
			{
				/* trying to re-open an open connection */
				_sqlsetintrerr(_sql, _SQL_INTRERR_25018);
				_sqlretcode = CS_FAIL;
			}
			break;
		case _SQL_DYNDESC_TYPE:		/* SQL Descriptor */
			_sqlretcode = _sqlDescOp(_sqlOperation, _sql);
			break;
		case _SQL_DIAG_TYPE:
			break;
		default:
			_sqlsetintrerr(_sql, _SQL_INTRERR_25008);
			break;
	    }
	}
	if (_sqlretcode == CS_FAIL)
	{ /* save _sqlretcode */
		_sqlepilog(_sql, _sqlObjType, _sqlSqlca, SQLCODE, SQLSTATE);
	}

	return(_sqlretcode);

} /* end of _sqlprolog() */

/*
** _sqlCurCName -- retrieve the 'Current' connection name, and load it
** into the _sqlObjname structure argument
*/
_SQL_SCOPE CS_INT _sqlCurCName(_sql, _sqlObjname)
_SQL_CT_HANDLES	*_sql;
CS_OBJNAME	*_sqlObjname;
{	    
	CS_INT	_sqlretcode = CS_SUCCEED;
	CS_OBJNAME	_sqlnDesc;
	CS_OBJDATA	_sqlnData;
    	_sqlInitName(&_sqlnDesc, CS_CURRENT_CONNECTION);
	_sqlnDesc.thread = _sql->threadId;
	_sqlnDesc.threadlen = _sql->threadIdLen;
	_sqlnDesc.thinkexists = CS_TRUE;
    	_sqlInitData(&_sqlnData);
	_sqlnData.buflen = CS_MAX_NAME;
	_sqlnData.buffer = _sqlObjname->last_name;
	_sqlretcode = cs_objects(_sql->ctx, CS_GET, &_sqlnDesc, &_sqlnData);
	if (_sqlretcode == CS_SUCCEED && _sqlnData.actuallyexists == CS_TRUE)
	{
		_sqlObjname->lnlen = _sqlnData.buflen;
	} else {
	    	return(CS_FAIL);
	}
	return(CS_SUCCEED);
}
/*
** _sqlCurOp - get/set information on cursors as part of sqlprolog
*/
_SQL_SCOPE CS_INT _sqlCurOp(_sqlOper, _sql)
CS_INT		_sqlOper;
_SQL_CT_HANDLES	*_sql;
{
	CS_INT	_sqlretcode = CS_SUCCEED;
	_sql->cur.buffer = &_sql->bind;
	if (_sqlOper == _SQL_CREATE)
	{
		_sql->curName.thinkexists = CS_FALSE;
	}
	else
	{
		_sql->curName.thinkexists = CS_TRUE;
	}
	_sqlretcode = cs_objects(_sql->ctx, CS_GET,
		&_sql->curName, &_sql->cur);

	if ((_sqlretcode == CS_SUCCEED) && (_sql->cur.actuallyexists == CS_TRUE))
	{
	    _sql->doDecl = CS_FALSE;
	}
	else if ((_sqlretcode == CS_SUCCEED) && (_sqlOper == _SQL_CREATE))
	{
		/* object does not exist, but that is OK */
		_sql->doDecl = CS_TRUE;
		_sqlretcode = ct_cmd_alloc(_sql->conn.connection, &_sql->cur.command);
		_sql->cur.connection = _sql->conn.connection;
	}
	return(_sqlretcode);
}
/*
** _sqlStmOp - get/set information on Dynamic statements as part of sqlprolog
*/
_SQL_SCOPE CS_INT _sqlStmOp(_sqlOper, _sql, _sqlSqlca, SQLCODE, SQLSTATE)
CS_INT		_sqlOper;
_SQL_CT_HANDLES	*_sql;
SQLCA        * _sqlSqlca;
long       * SQLCODE;
CS_CHAR      * SQLSTATE;
{
	CS_INT	_sqlretcode = CS_SUCCEED;
	if (_sqlOper == _SQL_CREATE)
	{
		_sql->stmtName.thinkexists = CS_FALSE;
	}
	else
	{
		_sql->stmtName.thinkexists = CS_TRUE;
	}
	_sqlretcode = cs_objects(_sql->ctx, CS_GET,
		&_sql->stmtName, &_sql->stmt);

	if ((_sqlretcode == CS_SUCCEED) && (_sql->stmt.actuallyexists == CS_TRUE) &&
		(_sqlOper == _SQL_CREATE))
	{
		CS_INT	_sqlRestype;
		/* 
		** We are re-preparing a Statement.  We must first close, and
		** deallocate any dynamic cursors which are open using this
		** statement
		*/
		_sqlretcode = _sqlDropStmtCurs(_sql);
		/*
		** if a cursor had been implicitly closed by the cursor, we
		** may have gotten an error trying to close an already closed
		** cursor.  This is not really an error in this circumstance,
		** so clear it.
		*/
		if (_sqlretcode == CS_SUCCEED)
		{
			_sqlretcode = _sqlctdiag(_sql,
						CS_CLEAR, CS_UNUSED, 
						_sqlSqlca, SQLCODE, SQLSTATE);
		}
		if (_sqlretcode == CS_SUCCEED)
		{
			_sqlretcode = _sqlcsdiag(_sql->ctx,
						CS_CLEAR, CS_UNUSED, 
						_sqlSqlca, SQLCODE, SQLSTATE);
		}
		/* then we deallocate the statement, and finally
		** allocate/initialize a new one
		*/
		if (_sqlretcode == CS_SUCCEED)
		{
			_sqlretcode = ct_dynamic(_sql->stmt.command, CS_DEALLOC,
				_sql->stmtName.first_name, 
				_sql->stmtName.fnlen,
				(CS_CHAR *) NULL, CS_UNUSED);
		}
		if (_sqlretcode == CS_SUCCEED)
		{
			_sqlretcode = ct_send(_sql->stmt.command);
			while ((_sqlretcode = ct_results(_sql->stmt.command,
				&_sqlRestype)) == CS_SUCCEED);
			if (_sqlRestype == CS_CMD_DONE) _sqlretcode = CS_SUCCEED;
	    		_sql->doDecl = CS_TRUE;
		}
		_sqlretcode = cs_objects(_sql->ctx, CS_CLEAR,
			&_sql->stmtName, &_sql->stmt);
		_sql->doDecl = CS_TRUE;
	}
	else if ((_sqlretcode == CS_SUCCEED) && (_sqlOper == _SQL_CREATE))
	{
		/* 
		** We are preparing a Statement for the first time, allocate
		** its command handle.
		*/
		_sql->doDecl = CS_TRUE;
		_sql->stmt.connection = _sql->conn.connection;
		_sqlretcode = ct_cmd_alloc(_sql->stmt.connection,
			&_sql->stmt.command);
	}
	else if (_sqlretcode == CS_SUCCEED)
	{
		/* Just getting a Stmt */
		_sql->doDecl = CS_FALSE;
	}
	return(_sqlretcode);
}
/*
** _sqlDropStmtCurs - Drop all dynamic cursors on a Dynamic statement
*/
_SQL_SCOPE CS_INT _sqlDropStmtCurs(_sql)
_SQL_CT_HANDLES	*_sql;
{
	/* structures to hold dynstmt/cursor table info */
	CS_OBJNAME	_sqlnDesc;
	CS_OBJDATA	_sqlnData;
	CS_CHAR	curname[CS_MAX_NAME];
	/* structures to hold cursor info */
	CS_OBJNAME	_sqlcDesc;
	CS_OBJDATA	_sqlcData;
	CS_INT	_sqlretcode = CS_SUCCEED;

	_sqlInitName(&_sqlnDesc, _SQL_STMT_CURSOR_TABLE);
	_sqlInitData(&_sqlnData);
	_sqlnDesc.fnlen = CS_WILDCARD;
	_sqlnDesc.threadlen = _sql->stmtName.threadlen;
	_sqlnDesc.thread = _sql->stmtName.thread;
	_sqlnData.buflen = CS_MAX_NAME;
	_sqlInitName(&_sqlcDesc, CS_CURSORNAME);
	_sqlcDesc.threadlen = _sql->stmtName.threadlen;
	_sqlcDesc.thread = _sql->stmtName.thread;
	_sqlInitData(&_sqlcData);
	_sqlcDesc.thinkexists = CS_TRUE;
	_sqlnDesc.lnlen = _sql->stmtName.fnlen;
	_sqlmemcpy( _sql->stmtName.first_name,
		_sqlnDesc.last_name, 
		_sql->stmtName.fnlen);
	_sqlnData.buffer = curname;
	_sqlcDesc.lnlen = _sql->connName.lnlen;
	_sqlmemcpy( _sql->connName.last_name, 
		_sqlcDesc.last_name, 
		_sql->connName.lnlen);
	_sqlretcode = cs_objects(_sql->ctx, CS_GET, &_sqlnDesc, 
		&_sqlnData);
	/* loop over all cursors */
	while ((_sqlretcode == CS_SUCCEED) && (_sqlnData.actuallyexists == CS_TRUE))
	{
		CS_INT	_sqlRestype;
		/* retrieve this dynamic cursor's info */
		_sqlcDesc.fnlen = _sqlnData.buflen;
		_sqlmemcpy( _sqlnData.buffer, 
			_sqlcDesc.first_name, 
			_sqlnData.buflen);
		_sqlretcode = cs_objects(_sql->ctx, CS_GET, 
			&_sqlcDesc, &_sqlcData);
		if ((_sqlretcode == CS_SUCCEED) && 
			(_sqlcData.actuallyexists == CS_TRUE))
		{
			/* close + deallocate the cursor */
			_sqlretcode = ct_cursor(_sqlcData.command, 
				CS_CURSOR_CLOSE,
				(CS_CHAR *) NULL, CS_UNUSED, 
				(CS_CHAR *) NULL, CS_UNUSED, 
				CS_DEALLOC);
			if (_sqlretcode != CS_SUCCEED)
			{
				/* Assume that the cursor was already
				** closed, try to deallocate it */
				_sqlretcode = ct_cursor(_sqlcData.command, 
					CS_CURSOR_DEALLOC,
					(CS_CHAR *) NULL, CS_UNUSED, 
					(CS_CHAR *) NULL, CS_UNUSED, 
					CS_UNUSED);
			}
			_sqlretcode = ct_send(_sqlcData.command);
			while ((_sqlretcode = ct_results(_sqlcData.command,
				&_sqlRestype)) == CS_SUCCEED);
			if (_sqlRestype == CS_CMD_DONE) 
				_sqlretcode = CS_SUCCEED;
			if (_sqlretcode == CS_SUCCEED)
				_sqlretcode = ct_cmd_drop(_sqlcData.command);
		}
		/* clear the cursor and the stmt/cursor relation from ctxname */
		_sqlretcode = cs_objects(_sql->ctx, CS_CLEAR, 
			&_sqlcDesc, &_sqlcData);
		_sqlnDesc.fnlen = _sqlcDesc.fnlen;
		_sqlmemcpy( _sqlcDesc.first_name, 
			_sqlnDesc.first_name, 
			_sqlcDesc.fnlen);
		_sqlretcode = cs_objects(_sql->ctx, CS_CLEAR, 
			&_sqlnDesc, &_sqlnData);
		/* get the next cursor */
		_sqlnDesc.fnlen = CS_WILDCARD;
		_sqlnData.buflen = CS_MAX_NAME;
		if (_sqlretcode == CS_SUCCEED)
		{
			_sqlretcode = cs_objects(_sql->ctx, CS_GET, 
				&_sqlnDesc, &_sqlnData);
			/* Previous CLEAR operation may have removed the last
			** dynstmt/cursor relation, in which case this GET 
			** operation failed, this is OK */
			_sqlretcode = CS_SUCCEED;
		}
	}
	return(_sqlretcode);
}
/*
** _sqldyncur - Make an association between a dynamic cursor and
** the dynamic statement it is declared with
*/
_SQL_SCOPE CS_INT _sqlDynCur(_sql)
_SQL_CT_HANDLES	*_sql;
{
	/* structures to hold dynstmt/cursor table info */
	CS_OBJNAME	_sqlnDesc;
	CS_OBJDATA	_sqlnData;
	CS_INT	_sqlretcode = CS_SUCCEED;
    	_sqlInitName(&_sqlnDesc, _SQL_STMT_CURSOR_TABLE);
    	_sqlInitData(&_sqlnData);
	_sqlnData.buflen = CS_MAX_NAME;

	/* copy the statement-name to last_name, cursor-name to first-name */
	_sqlnDesc.lnlen = _sql->stmtName.fnlen;
	_sqlnDesc.threadlen = _sql->stmtName.threadlen;
	_sqlnDesc.thread = _sql->stmtName.thread;
	_sqlmemcpy( _sql->stmtName.first_name, 
		_sqlnDesc.last_name, 
		_sql->stmtName.fnlen);
	_sqlnDesc.fnlen = _sql->curName.fnlen;
	_sqlmemcpy( _sql->curName.first_name,
		_sqlnDesc.first_name, 
		_sql->curName.fnlen);
	_sqlnData.buflen = _sql->curName.fnlen;
	_sqlnData.buffer = _sql->curName.first_name;
	_sqlretcode = cs_objects(_sql->ctx, CS_SET, &_sqlnDesc, 
		&_sqlnData);
	return(_sqlretcode);
}

/*
** _sqlDescOp - get/set information on Dynamic Descriptors as part of sqlprolog
*/
_SQL_SCOPE CS_INT _sqlDescOp(_sqlOper, _sql)
CS_INT		_sqlOper;
_SQL_CT_HANDLES	*_sql;
{
	CS_INT	_sqlretcode = CS_SUCCEED;
	if (_sqlOper == _SQL_CREATE)
	{
		/* trying to allocate a descriptor
		** so temporarily get a connection/command
		** and allocate it!
		*/
		_sqlretcode = ct_con_alloc(_sql->ctx,
			&_sql->desc.connection);
		if (_sqlretcode == CS_SUCCEED)
		{
			_sqlretcode =
				ct_cmd_alloc(_sql->desc.connection,
				&_sql->desc.command);
		}
		/*
		** initialize in-line error handling for the descriptor
		*/
		if (_sqlretcode == CS_SUCCEED)
		{
			_sqlretcode = ct_diag(_sql->desc.connection, CS_INIT,
	 			CS_UNUSED, CS_UNUSED, NULL);
		}
		if (_sqlretcode == CS_SUCCEED)
		{
			_sqlretcode = ct_dyndesc(_sql->desc.command, 
				_sql->descName.first_name,
				_sql->descName.fnlen, CS_ALLOC, 
				_sql->descSize,
				(CS_DATAFMT *) NULL, (CS_VOID *) NULL,
				CS_UNUSED, (CS_INT *) NULL,
				(CS_SMALLINT *) NULL);
#ifdef	CT_LIB_MOVES_DESCRIPTORS_IN_CTX
			/* XXX FIX -- currently a descriptor goes away
			** if you drop the connection you allocate it on */
			ct_cmd_drop(_sql->desc.command);
			ct_con_drop(_sql->desc.connection);
#endif /* CT_LIB_MOVES_DESCRIPTORS_IN_CTX */
		}
		if (_sqlretcode == CS_SUCCEED)
		{
			_sql->descName.thinkexists = CS_FALSE;
			_sqlretcode = cs_objects(_sql->ctx, CS_SET, 
				&_sql->descName, &_sql->desc);
		}
	} 
	else
	{
		if (_sqlretcode == CS_SUCCEED)
		{
			_sql->descName.thinkexists = CS_TRUE;
			_sqlretcode = cs_objects(_sql->ctx, CS_GET, 
				&_sql->descName, &_sql->desc);
		}
	}
	_sql->doDecl = CS_FALSE;
	return(_sqlretcode);
}

_SQL_SCOPE CS_INT 
_sqlepilog(_sql, _sqlObjType, _sqlSqlca, SQLCODE, SQLSTATE)
  _SQL_CT_HANDLES 	* _sql;
  CS_INT	_sqlObjType;
  SQLCA 	* _sqlSqlca;
  long	 	* SQLCODE;
  CS_CHAR 	* SQLSTATE;
{
	CS_INT   		_sqlretcode = CS_SUCCEED;
	CS_INT		_sqlWorstIndex = 0;

	switch(_sqlObjType)
	{
	    case _SQL_CURSOR_TYPE:
	    case _SQL_CONNECT_TYPE:
	    case _SQL_DYNSTMT_TYPE:
		_sqlWorstIndex = _sqlworst(_sql, CS_TRUE);
		break;
	    case _SQL_DYNDESC_TYPE:
	    case _SQL_NOCONNECT_TYPE:
	    case _SQL_DIAG_TYPE:
		_sqlWorstIndex = _sqlworst(_sql, CS_FALSE);
		break;	
	    default:
		_sqlsetintrerr(_sql, _SQL_INTRERR_25002);
		return(CS_FAIL);
	}
	if (_sqlWorstIndex > 0)
	{
	    _sqlretcode = _sqlctdiag(_sql, CS_GET, _sqlWorstIndex, 
				 _sqlSqlca, SQLCODE, SQLSTATE);
	} 
	else if (_sqlWorstIndex < 0)
	{
	    _sqlWorstIndex *= -1;
	    _sqlretcode = _sqlcsdiag(_sql->ctx, CS_GET, _sqlWorstIndex, 
				 _sqlSqlca, SQLCODE, SQLSTATE);
	}
	else
	{
	    /* No errors anywhere, make values look like success */
		if (_sqlSqlca != (SQLCA *) NULL)
		{
		    _sqlmemzero((CS_VOID *) _sqlSqlca, sizeof(SQLCA));
		}
		if (SQLSTATE != (CS_CHAR *) NULL)
		{
		    strcpy(SQLSTATE, "00000");
		}
		if (SQLCODE != (long *) NULL)
		{
		    *SQLCODE = (long) 0;
		}
	}

	return(_sqlretcode);

} /* end of _sqlepilog() */

typedef CS_RETCODE	(CS_PUBLIC * CS_CLIMSG_FUNC)PROTOTYPE((
	CS_CONTEXT	*context,
	CS_CONNECTION	*connection,
	CS_CLIENTMSG	*message
	));
_SQL_SCOPE void 
_sqlsetintrerr(_sql, _sqlintrerr_type)
  _SQL_CT_HANDLES      * _sql;
  CS_INT	  _sqlintrerr_type;
{

        CS_CLIMSG_FUNC climsg_hndlr;	/* pointer to user's client
                                        ** message handler
                                        */
        CS_RETCODE      ret;		/* return value */
	ret = ct_callback((CS_CONTEXT *) NULL, _sql->conn.connection,
		CS_GET, CS_CLIENTMSG_CB, &climsg_hndlr);
	if (ret == CS_SUCCEED)
	{
		ret = (*climsg_hndlr)(_sql->ctx,
			_sql->conn.connection,
			&_sql_intrerr[_sqlintrerr_type]);
	}
} /* end of _sqlsetintrerr() */

_SQL_SCOPE void 
_sqlctxerr(_sqlSqlca, SQLCODE, SQLSTATE, _sqlintrerr_type)
  SQLCA 	* _sqlSqlca;
  long	 	* SQLCODE;
  CS_CHAR 	* SQLSTATE;
  CS_INT	  _sqlintrerr_type;
{
    if (_sqlSqlca != (SQLCA *) NULL)
    {
	strcpy(_sqlSqlca->sqlerrm.sqlerrmc,
		(char *) _sql_intrerr[_sqlintrerr_type].msgstring);
	_sqlSqlca->sqlerrm.sqlerrml = _sql_intrerr[_sqlintrerr_type].msgstringlen;
	_sqlSqlca->sqlcode = -1 * _sql_intrerr[_sqlintrerr_type].msgnumber;
    }
    if (SQLSTATE != (CS_CHAR *) NULL)
    {
	strcpy(SQLSTATE, (char *) _sql_intrerr[_sqlintrerr_type].sqlstate); 
    }
    if (SQLCODE != (long *) NULL)
    {
	*SQLCODE = (long) -1 * _sql_intrerr[_sqlintrerr_type].msgnumber; 
    }

} /* end of _sqlctxerr() */


_SQL_SCOPE CS_INT 
_sqlcsdiag(_sqlctx, _sqlOper, _sqlerrindex, _sqlSqlca, SQLCODE, SQLSTATE)
  CS_CONTEXT	*_sqlctx;
  CS_INT 	_sqlOper;
  CS_INT 	_sqlerrindex;
  SQLCA 	* _sqlSqlca;
  long	 	* SQLCODE;
  CS_CHAR 	* SQLSTATE;
{
    CS_INT   _sqlretcode = CS_SUCCEED;

    if (_sqlOper == CS_CLEAR)
    {
	/* Don't know if we've ever initialized this context, do it now */
	_sqlretcode = cs_diag(_sqlctx, CS_INIT, 
	    CS_UNUSED, CS_UNUSED, NULL);
    }
    if ((_sqlretcode != CS_FAIL) && (_sqlSqlca != (SQLCA *) NULL))
    {
	_sqlretcode = cs_diag(_sqlctx, _sqlOper, SQLCA_TYPE, _sqlerrindex, 
			      _sqlSqlca);
	if (_sqlretcode == CS_FAIL)
	{
	    _sqlctxerr(_sqlSqlca, SQLCODE, SQLSTATE, _SQL_INTRERR_25007);
	}
    }
    if ((_sqlretcode != CS_FAIL) && (SQLSTATE != (CS_CHAR *) NULL))
    {
	CS_CHAR	tmpsqlstate[CS_SQLSTATE_SIZE];
	_sqlretcode = cs_diag(_sqlctx, _sqlOper, SQLSTATE_TYPE, _sqlerrindex, 
			      tmpsqlstate);
	if (_sqlretcode == CS_FAIL)
	{
	    _sqlctxerr(_sqlSqlca, SQLCODE, SQLSTATE, _SQL_INTRERR_25007);
	}
	_sqlmemcpy(tmpsqlstate, SQLSTATE, 6);
    }

    if ((_sqlretcode != CS_FAIL) && (SQLCODE != (long *) NULL))
    {
	CS_INT	_sqltmpsqlcode = 0;
	_sqlretcode = cs_diag(_sqlctx, _sqlOper, SQLCODE_TYPE, _sqlerrindex, 
			      &_sqltmpsqlcode);
	*SQLCODE = _sqltmpsqlcode;
	if (_sqlretcode == CS_FAIL)
	{
	    _sqlctxerr(_sqlSqlca, SQLCODE, SQLSTATE, _SQL_INTRERR_25007);
	}
    }

    if (_sqlretcode != CS_FAIL) 
	_sqlretcode = CS_SUCCEED;

    return(_sqlretcode);

} /* end of _sqlcsdiag() */


_SQL_SCOPE CS_INT 
_sqlctdiag(_sql, _sqlOper, _sqlerrindex, _sqlSqlca, SQLCODE, SQLSTATE)
  _SQL_CT_HANDLES *_sql;
  CS_INT 	_sqlOper;
  CS_INT 	_sqlerrindex;
  SQLCA 	* _sqlSqlca;
  long	 	* SQLCODE;
  CS_CHAR 	* SQLSTATE;
{
    CS_INT   _sqlretcode = CS_SUCCEED;

    if (_sqlOper == CS_CLEAR)
    {
	/* Don't know if the in-line error handling is still installed */
	_sqlretcode = ct_diag(_sql->conn.connection, CS_INIT,
	 	CS_UNUSED, CS_UNUSED, NULL);
    }
    if ((_sqlretcode != CS_FAIL) && (_sqlSqlca != (SQLCA *) NULL))
    {
	_sqlretcode = ct_diag(_sql->conn.connection,
		_sqlOper, SQLCA_TYPE, _sqlerrindex, _sqlSqlca);
	if (_sqlretcode == CS_FAIL)
	{
	    _sqlctxerr(_sqlSqlca, SQLCODE, SQLSTATE, _SQL_INTRERR_25002);
	}
    }

    if ((_sqlretcode != CS_FAIL) && (SQLSTATE != (CS_CHAR *) NULL))
    {
	CS_CHAR	tmpsqlstate[CS_SQLSTATE_SIZE];
	_sqlretcode = ct_diag(_sql->conn.connection,
		_sqlOper, SQLSTATE_TYPE, _sqlerrindex, tmpsqlstate);
	if (_sqlretcode == CS_FAIL)
	{
	    _sqlctxerr(_sqlSqlca, SQLCODE, SQLSTATE, _SQL_INTRERR_25002);
	}
	_sqlmemcpy(tmpsqlstate, SQLSTATE, 6);
    }

    if ((_sqlretcode != CS_FAIL) && (SQLCODE != (long *) NULL))
    {
	CS_INT	_sqltmpsqlcode = 0;
	_sqlretcode = ct_diag(_sql->conn.connection,
		_sqlOper, SQLCODE_TYPE, _sqlerrindex, &_sqltmpsqlcode);
	*SQLCODE = (long) _sqltmpsqlcode;
	if (_sqlretcode == CS_FAIL)
	{
	    _sqlctxerr(_sqlSqlca, SQLCODE, SQLSTATE, _SQL_INTRERR_25002);
	}
    }
    if ((_sqlOper == CS_GET) && (_sqlretcode == CS_NOMSG))
    {
	_sqlretcode = CS_SUCCEED;
    }
    return(_sqlretcode);

} /* end of _sqlctdiag() */


_SQL_SCOPE CS_INT
_sqldtcnv(_sql, _sqlType, _sqlOper)
    _SQL_CT_HANDLES	* _sql;
    CS_INT		_sqlType;
    CS_INT		_sqlOper;
{
    CS_INT	_sqlcnt = 0;

    if (_sqlOper == CS_GET)
    {
	for (; _sqlcnt < _SQL_MAX_DESC_TYPES; _sqlcnt++)
   	{
	    if (_sqldesctbl[_sqlcnt]._sql_ctlib_type == _sqlType)
		return(_sqldesctbl[_sqlcnt]._sql_ansi_type);
	}
    }
    else if (_sqlOper == CS_SET)
    {
	for (; _sqlcnt < _SQL_MAX_DESC_TYPES; _sqlcnt++)
   	{
	    if (_sqldesctbl[_sqlcnt]._sql_ansi_type == _sqlType)
		return(_sqldesctbl[_sqlcnt]._sql_ctlib_type);
	}
    }

    /* raise error if we reach this point */
    _sqlsetintrerr(_sql, _SQL_INTRERR_25011);
    return(CS_ILLEGAL_TYPE);

} /* end of _sqldtcnv() */

/*
** Function _sqlworst:
** scans through both the ct_diag and cs_diag message queues looking for
** the worst severity error message and returns the index to it.
** If the error is found in ct_diag, the message index is > 0.  If the
** error was found in cs_diag, the message index is < 0 (take the negative
** of it when calling cs_diag to get the actual message).  If there were
** no errors or warnings, return the first cs_diag message (-1) informational
** message. if there are no cs_diag messages at all, return the first ct_diag
** informational message (+1), and if there were no ct_diag messages either,
** return 0.
*/
_SQL_SCOPE CS_INT
_sqlworst ( _sql, _sqlHaveConn ) 
_SQL_CT_HANDLES *_sql;
CS_BOOL		_sqlHaveConn;
{
	CS_INT msgnum, nummsgs;
	CS_INT errindex = 0, warnindex = 0, infoindex = 0;
	CS_INT	sqlcode;
	CS_RETCODE _sqlretcode = CS_SUCCEED;
	/* look for errors in cs_diag queue */
	_sqlretcode = cs_diag(_sql->ctx, CS_STATUS,
			CS_CLIENTMSG_TYPE, CS_UNUSED, &nummsgs);
	for (msgnum = 1; ((msgnum <= nummsgs) && 
		(_sqlretcode == CS_SUCCEED)); msgnum++)
	{
		_sqlretcode = cs_diag(_sql->ctx, CS_GET,
			SQLCODE_TYPE, msgnum, &sqlcode);
		if (sqlcode < 0)
		{
			errindex = -1 * msgnum;
			break;
		}
		else if ((sqlcode > 0) && (warnindex == 0))
		{
			warnindex = -1 * msgnum;
		}
		else if (infoindex == 0)
		{
			infoindex = -1;
		}
	}
	/* if an error was found in the cs_diag queue, we are done */
	if (errindex) return(errindex);
	if (_sqlHaveConn)
	{
		/* look for the worst ct_diag message on this connecion */
		_sqlretcode = ct_diag(_sql->conn.connection, CS_STATUS,
				CS_ALLMSG_TYPE, CS_UNUSED, &nummsgs);
		for (msgnum = 1; ((msgnum <= nummsgs) && 
			(_sqlretcode == CS_SUCCEED)); msgnum++)
		{
			_sqlretcode = ct_diag(_sql->conn.connection, CS_GET,
				SQLCODE_TYPE, msgnum, &sqlcode);
			if (sqlcode < 0)
			{
				errindex = msgnum;
				break;
			}
			else if ((sqlcode > 0) && (warnindex == 0))
			{
				warnindex = msgnum;
			}
			else if (infoindex == 0)
			{
				infoindex = 1;
			}
		}
	}
	if (errindex) 
	{
		return(errindex);
	}
	else if (warnindex)
	{
		return(warnindex);
	}
	else
		return(infoindex);
}

_SQL_SCOPE CS_VOID
_sqlmemzero( _sqlBuf, _sqlSize )
CS_VOID	*_sqlBuf;
CS_INT	_sqlSize;
{
	unsigned char	*p = (unsigned char *) _sqlBuf;
	while (_sqlSize > 0)
	{
		*p++ = (unsigned char) 0;
		_sqlSize--;
	}
}

/*
** memcpy -- except we recognize (_sqlSize == CS_NULLTERM) to
** mean strcpy with null-terminated strings
*/
_SQL_SCOPE CS_VOID
_sqlmemcpy( _sqlSrc, _sqlDest, _sqlSize )
CS_VOID	*_sqlSrc;
CS_VOID	*_sqlDest;
CS_INT	_sqlSize;
{
	unsigned char	*s = (unsigned char *) _sqlSrc;
	unsigned char	*d = (unsigned char *) _sqlDest;
	if (_sqlSize == CS_NULLTERM)
	{
		while (1)
		{
			*d++ = *s++;
			if (*s == (unsigned char) '\0') break;
		}
	}
	else
	{
		while (_sqlSize > 0)
		{
			*d++ = *s++;
			_sqlSize--;
		}
	}
	/* Null-terminate the destination */
	*d = '\0';
}
/*
** Use the THREAD_RESOURCE functions -- installed in the context handle
** to determine this thread's id.  Return the thread/threadLen in 
** arguments passed in.  Arguments buff, bufLen describe memory which
** is to be used to retrieve the info, if they are not large enough,
** to accomodate the threadid, this function returns FAIL.
*/
_SQL_SCOPE CS_RETCODE 
_sqlInitThreadId( _sqlctx, thread, threadLen, buff, bufLen )
CS_CONTEXT	*_sqlctx;
CS_VOID		**thread;
CS_INT		*threadLen;
CS_VOID		*buff;
CS_INT		bufLen;
{
	CS_RETCODE _sqlretcode = CS_SUCCEED;
	CS_THREAD thread_functions;
	CS_INT	_sqloutlen;
	_sqlretcode = cs_config(_sqlctx, CS_GET, CS_THREAD_RESOURCE,
		&thread_functions, CS_UNUSED, &_sqloutlen);
	
	if (_sqlretcode == CS_SUCCEED)
	{
		_sqlretcode = (*thread_functions.thread_id_fn)(
			buff, bufLen, threadLen);
	}
	if (_sqlretcode != CS_SUCCEED)
	{
		return(_sqlretcode);
	}
	else if (*threadLen > bufLen)
	{
		/* threadid did not fit in buff! */
		return(CS_FAIL);
	}
	else
	{
		*thread = buff;
		return (_sqlretcode);
	}
}
/*
** Use the THREAD_RESOURCE functions -- installed in the context handle
** to take a mutex.  If the mutex handle passed in is NULL, this
** function will CREATE the mutex before taking it.
** NOTE:  There is no corresponding function to delete the mutex.
*/
_SQL_SCOPE CS_RETCODE 
_sqlTakeMutex( _sqlctx, mutex)
CS_CONTEXT	*_sqlctx;
CS_THRDRES	**mutex;
{
	CS_RETCODE _sqlretcode;
	CS_THREAD thread_functions;
	CS_INT	_sqloutlen;
	_sqlretcode = cs_config(_sqlctx, CS_GET, CS_THREAD_RESOURCE,
		&thread_functions, CS_UNUSED, &_sqloutlen);
	
	if (_sqlretcode != CS_SUCCEED) return(_sqlretcode);

	if (*mutex == (CS_THRDRES *) NULL)
	{
		if (thread_functions.create_mutex_fn != 
			(CS_THRDC_FUNC) NULL)
		{
			_sqlretcode = (*thread_functions.create_mutex_fn)(
				mutex);
		}
	}
	if (_sqlretcode == CS_SUCCEED)
	{
		if (thread_functions.take_mutex_fn != 
			(CS_THRDM_FUNC) NULL)
		{
			_sqlretcode = (*thread_functions.take_mutex_fn)(
				*mutex);
		}
	}
	return (_sqlretcode);
}
/*
** Use the THREAD_RESOURCE functions -- installed in the context handle
** to release a mutex.
*/
_SQL_SCOPE CS_RETCODE 
_sqlReleaseMutex( _sqlctx, mutex)
CS_CONTEXT	*_sqlctx;
CS_THRDRES	*mutex;
{
	CS_RETCODE _sqlretcode;
	CS_THREAD thread_functions;
	CS_INT	_sqloutlen;
	/* return immediately if we have not already taken the mutex */
	if (mutex == (CS_THRDRES *) NULL) return(CS_SUCCEED);
	/* get the release function */
	_sqlretcode = cs_config(_sqlctx, CS_GET, CS_THREAD_RESOURCE,
		&thread_functions, CS_UNUSED, &_sqloutlen);
	if (_sqlretcode == CS_SUCCEED)
	{
		if (thread_functions.release_mutex_fn != 
			(CS_THRDM_FUNC) NULL)
		{
			_sqlretcode = (*thread_functions.release_mutex_fn)(
				mutex);
		}
	}
	return (_sqlretcode);
}
/*
** This function checks char[] host variables to make sure:
**  1) they are null-terminated (they are passed into ct_lib
**	as CS_NULLTERM).  The data exception for unterminated
**	strings will be raised from this function if necessary.
**  2) check that the string is not 0-length.  Currently, passing
**	a zero-length character string as a parameter is
**	indistinguishable from a NULL parameter value. The behavior
**	which is desired is that SQL-Server treat the 0-length
**	string the same a single space -- we make that happen
**	by actually passing a single space, rather than an
** 	empty string here.
*/
_SQL_SCOPE CS_CHAR *
_sqlcheckstr( _sql, _sqlHostString )
_SQL_CT_HANDLES *_sql;
char	*_sqlHostString;
{
	char	*p;
	CS_INT	_sqlHostStringLen =
		_sql->dfmtCS_CHAR_TYPE.maxlength;
	for ( p = &_sqlHostString[_sqlHostStringLen - 1];
		p >= _sqlHostString; p--)
	{
		if (! *p) break;
	}
	if (p < _sqlHostString)
	{
		/* Unterminated string */
		_sqlsetintrerr(_sql, _SQL_INTRERR_25014);
		return((CS_CHAR *) NULL);
	} 
	else if (p <= _sqlHostString)
	{
		/* Zero-length string */
		strcpy(_sql->temp_char, " ");
		return(_sql->temp_char);
	}
	else
	{
		/* nothing wrong with host-string */
		return(_sqlHostString);
	}
}



#endif /* __SYBTESQL_H__ */
