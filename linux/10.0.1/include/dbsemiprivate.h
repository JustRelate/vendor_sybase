/* Sccsid @(#) dbsemiprivate.h 8.1 8/10/93 */

/*
**	Sybase DB-LIBRARY Version 5.0
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1988, 1992
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
** This include file contains definitions and macros that are shared among
** various Sybase development groups, that are specific to DB-Library.
** These routines are considered semi-private because they allow programs
** to access the private parts of DB-Library, yet are not at the API level.
**
** This file should be included after sybdb.h
*/

#ifndef __dbsemiprivate__
#define	__dbsemiprivate__

/*
** The following macro returns the table from the DBPROCESS that has the
** multi-byte character set information. 
*/
#define DBGETCHARATTRIB(p)	dbgetcharattrib(p)

/* These macros return information from the internals of a dbproc.  */

#define DBGETOPTCMD(p)		dbgetoptcmd(p)
#define DBGETCUROFFSET(p)	dbgetcuroffset(p)
#define DBGETCMDBUF(p)		dbgetcmdbuf(p)

/* DBGETSTRTOTLEN() get the length of the text in a DBSTRING structure.
** p is a pointer to a DBSTRING structure.
*/
#define DBGETSTRTOTLEN(p)	dbgetstrtotlen(p)

/* DBGETCOLS() returns a pointer to the head of the list of COLINFO structures
** stored in the dbproc.  DBGETNEXTCOL() returns a pointer to the next 
** colinfo structure in the list.  The other macros get various fields
** of a COLINFO structure.
*/
#define DBGETCOLS(dbproc)		dbgetcols(dbproc)
#define DBGETNEXTCOL(colinfo)		dbgetnextcol(colinfo)
#define DBGETCOLTYPE(colinfo)		dbgetcoltype(colinfo)
#define DBGETUDTYPE(colinfo)		dbgetudtype(colinfo)
#define DBGETCOLLEN(colinfo)		dbgetcollen(colinfo)
#define DBGETCOLNAME(colinfo)		dbgetcolname(colinfo)
#define DBGETCOLCONTROL(colinfo)	dbgetcolcontrol(colinfo)

/* These macros are used by Secure Db-Lib and Secure Front-Ends */

#define DBUNSETONECOMP(a,b)     (a)[ ((b)-1)/8 ] &= ~( 0x80 >> (( (b)-1 ) % 8) )
#define DBGETONECOMP(a,b)       (a)[ ((b)-1)/8 ] & ( 0x80 >> (( (b)-1 ) % 8) )

#define DBGETLROLE(a)			dbgetlrole(a)
#define DBGETSLSTATUS(a)		dbgetslstatus(a)
#define DBGETSLCOMP(a)			dbgetslcomp(a)
/* for probe only */
#define DBSETSECURE	214
#define DBSETLSECURITY(a,b)         dbsetlbool((a), (b), DBSETSECURE)

/*
** external declaration for functions referenced in this file as macros 
** and were once macros
*/
extern VOID *		dbgetcharattrib();
extern DBSTRING *	dbgetoptcmd();
extern DBINT		dbgetcuroffset();
extern DBSTRING *	dbgetcmdbuf();
extern DBINT		dbgetstrtotlen();
extern DBCOLINFO *	dbgetcols();
extern DBCOLINFO *	dbgetnextcol();
extern BYTE		dbgetcoltype();
extern DBINT		dbgetudtype();
extern DBINT		dbgetcollen();
extern char *		dbgetcolname();
extern char *		dbgetcolcontrol();
extern BYTE		dbgetlrole();
extern short		dbgetslstatus();
extern BYTE *		dbgetslcomp();

/* dbconvert.c */
extern	void		dbfltfmt();

/* file commitlib.c */
extern	int		probe_xact();

/* file controlcmd.c */
extern	char		*dbcontrolcmd();
extern	void		dbccoff();
extern	char		*dbctrlcmd();
extern	char		*dbcolufmt();
extern	RETCODE		dbsetufmt();

/* file db__console.c */
extern	DBPROCESS	*db__console_connect();
extern	RETCODE		db__console_wait();
extern	BYTE		*db__get_request();
extern	BYTE		*db__get_response();
extern	void		db__send_response();

/* file db__head.c */
extern	RETCODE		db__head();

/* file db__line.c */
extern	RETCODE		db__line();

/* file db__prrw.c */
extern	RETCODE		db__prrow();

/* file dbgetenv.c */
extern	DBCHAR		*dbgetenv();
extern	void		*dbfree_env();

/* file dbhome.c */
extern	RETCODE		dbsethome();
extern	int		dbgethome();

/* file dbmny.c */
extern	void		dbmnyxdiv();
extern	void		maxnegmny();
extern	void		maxposmny();

/* file dbrecftos.c */
extern	void		dbrecftos();

/* file dbseclogin.c */
extern	RETCODE		db__seclogin();
extern	SECLAB		*db_os_sl();

/* file dbsqlexec.c */
extern			dbprstring();
extern			dbfprstring();

/* file getpasswd.c */
extern	char		*getpasswd();

/* file globals.c */
extern			db__getDbTime();
extern			db__getDbMsgs();
extern			db__isdbdebug();
extern	void		db__setDbDebug();
extern			db__setDbHeader();
extern			db__setDbMsgs();
extern			db__setDbTime();
extern			db__setDbOldDateStyle();
extern			db__getDbOldDateStyle();

/* file inquiry.c */
extern	DBTYPEINFO	*dbcoltypeinfo();

/* file interface.c */
extern	int		db__find_interface();
extern	int		db__read_interface();

/* file options.c */
extern	void		dbpropt();

/* file secpriv.c */
extern	void		dbsetSecComp();
extern	BYTE		*dbgetSecComp();
extern	void		dbsetSecHier();
extern	short		dbgetSecHier();
extern	void		dbsetSecEnv();
extern	BYTE		dbgetSecEnv();
extern	void		dbsetSecQa();
extern	BYTE		dbgetSecQa();
extern	void		dbsetSecRole();
extern	BYTE		dbgetSecRole();
extern	void		dbsetSysHigh();
extern	DBBOOL		dbgetSysHigh();

/* file svoff.c */
extern	void		db__proff();

/* file text_inq.c */
extern	RETCODE		dbtxplen();

/* file dbresponse.c */
extern	RETCODE		dbresponse();

#endif /*__dbsemiprivate__*/
