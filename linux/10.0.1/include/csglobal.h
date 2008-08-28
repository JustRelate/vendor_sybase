


/* Sccsid %Z% %M% %I% %G% */

/*
**	Sybase OpenClient Version 10.0
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1991, 1993
**	All rights reserved
*/

/*
** csglobal.h - This is a common INTERNAL header file for all 10.0 libraries.
*/
#ifndef __CSGLOBAL_H__

#define __CSGLOBAL_H__

/*
** define forward reference to the async structures use in this and teh
** comasync file.
*/
typedef	struct _csamcontx	CS_AMCONTX;
typedef	struct _csasync		CS_ASYNC;
typedef	struct _csappglobal	CS_APPGLOBAL;

/*
** define pointer to functions, with prototypes
*/
typedef CS_RETCODE	(CS_PUBLIC * CS_POST_FUNC)PROTOTYPE((
					CS_ASYNC *async,
					CS_RETCODE status,
					CS_INT flag
					));
typedef CS_RETCODE	(CS_PUBLIC * CS_GETCTX_FUNC)PROTOTYPE((
					CS_AMCONTX **actx
					));
typedef CS_RETCODE	(CS_PUBLIC * CS_ASSOC_FUNC)PROTOTYPE((
					CS_ASYNC *async
					));
typedef CS_RETCODE	(CS_PUBLIC * CS_ACCESS_FUNC)PROTOTYPE((
					CS_APPGLOBAL *appg
					));
typedef CS_RETCODE	(CS_PUBLIC * CS_DBSLEEP_FUNC)PROTOTYPE((
					CS_VOID *sleepevent
					));
typedef CS_RETCODE	(CS_PUBLIC * CS_DBWAKE_FUNC)PROTOTYPE((
					CS_VOID *sleepevent
					));

/*
** Application Global Structure - Used by all Net-Library based libraries
*/
typedef struct _csasyncfuncs
{
	CS_POST_FUNC	amf_iopostfunc;	/* ptr to function to use when io or
					** and event is completed.
					*/
	CS_GETCTX_FUNC	amf_getctxfunc;	/* ptr to function to return current
					** async context. Currently used only
					** by openserver .
					*/
	CS_ASSOC_FUNC	amf_assoc;	/* ptr to function to associate async
					** manager thread with openserver
					** thread.
					*/
} CsAsyncFuncs;

/*
** Pointers to shared Net-Library structures and functions
*/
typedef struct _csnetglobal
{
	CS_VOID		*ntg_netengine;
	CS_VOID		*ntg_netstate;
	CS_DBSLEEP_FUNC	*ntg_dbsleep;
	CS_DBWAKE_FUNC	*ntg_dbwake;
} CsNetGlobal;

/*
** Shared Async manager structures 
*/
typedef struct _csasyncglobal
{
	CS_QUEUEHDR	amg_actxs;
	CsAsyncFuncs	amg_funcs;
} CsAsyncGlobal;

/* ag_subscribers flags */
#define	CS_AGSUBS_SRVLIB		(CS_INT)0
#define	CS_AGSUBS_CTLIB			(CS_INT)1
#define	CS_AGSUBS_DBLIB			(CS_INT)2
#define	CS_AGSUBS_MAXSUB		(CS_INT)3

/* ag_state flags */
#define	CS_AGSTATE_NETINITED		0x1
#define	CS_AGSTATE_FUNCSINITED		0x2

/*
** Structures shared among Context structures
**	Locales
**	Locale error cache 
**	Charset and sort order cache
*/
typedef struct _csctxglobals
{
	CS_INT		cmg_count;	/* num ctx's using cache */
	CS_VOID		*cmg_lcache;	/* ptr to localization cache
					** for context
					*/
	CS_VOID		*cmg_chardesc;	/* ptr to charset/sortorder
					** info for globally shared by
					** the locales.
					*/
	CS_LOCALE	*cmg_locale;	/* ptr to active localization
					** defined for contexts
					*/
} CsCtxGlobals;


/*
** Structure was added for bugid 72196.
*/
typedef struct _csappctxglobal
{
	CS_INT		acmg_ctxcount;	/* number of context's currently
					** allocated by this task
					*/
	CS_VOID		*acmg_curctx;	/*
					** current context being allocated.
					** this is to trap cs_ctx_alloc
					** calling cs_ctx_drop, so we don't
					** decrement our counter.
					*/
	CS_VOID		*acmg_netctx;	/* the context being used by netlib
					** for this task
					*/
} CsAppCtxGlobal;


/*
** Global area managed by comaglob.c
**
** Note that the subscriber count may not match the number of accesses
** to the structure. If you want to determine if anyone is currently "using"
** the structure, the subscribers array should be consulted. Any library or
** function(s) outside of the async manager which use or manipulates the
** internals of this structure should become a subscriber to it.
*/
typedef	struct _csappglobal
{
	CS_INT		ag_subscribers[CS_AGSUBS_MAXSUB];
					/* array of who is currently using
					** this structure. This must be
					** cleared before accesscnt goes to
					** zero.
					*/
	CS_INT		ag_state;	/* bitmask of flags indicating what
					** has done inside this structure.
					*/
	CS_INT		ag_accesscnt;	/* Number of current users of this
					** structure.
					*/
	CsNetGlobal	ag_netglobal;	/* shared netlib informatation */
	CsAsyncGlobal	ag_asyncglobal; /* shared async mgr information */ 
	CS_ACCESS_FUNC	ag_accessfunc;	/* ptr to function to control write
					** access to the CsAppGlobal structure
					*/
	CS_VOID		*ag_platformptr;	/* Unknown */
	CS_THREAD	*ag_ctxthread;	/* Points to the conext element */
	CS_THRDRES	*ag_mtx;	/* Lock for the structure */
	CsAppCtxGlobal	ag_appctxglobal;	/* Keeps track of how many
						** context's are allocated and
						** which context is being used
						** by netlib.
						*/
} CsAppGlobal;

/*
** Macro which returns true is anybody is currently subscribed
*/
#define CS_AGSUBS_INUSE(G) \
	( ((G)->ag_subscribers[CS_AGSUBS_SRVLIB] != 0) || \
	  ((G)->ag_subscribers[CS_AGSUBS_CTLIB] != 0) || \
	  ((G)->ag_subscribers[CS_AGSUBS_DBLIB] != 0) )

extern CS_RETCODE CS_PUBLIC com_appglobal_alloc PROTOTYPE((
	CsAppGlobal	**global_ptr,
	CS_THREAD	*ctxthread,
	CS_INT		flags
        ));
extern CS_RETCODE CS_PUBLIC com_appglobal_drop PROTOTYPE((
	CsAppGlobal	*appg,
	CS_INT		flags
        ));

#endif /* __CSGLOBAL_H__ */
