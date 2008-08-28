/* Sccsid %Z% %M% %I% %G% */

/*
**	Sybase OpenClient Version 10.0
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1991, 1993
**	All rights reserved
*/

/*
** csasync.h - This is the header file defining the public interface structure
**	       and defines for the async manager.
*/
#ifndef __CSASYNC_H__

#define __CSASYNC_H__

/*****************************************************************************
**
** interface defines and structures used 
**
*****************************************************************************/

/*
** define pointer to functions, with prototypes
*/
typedef CS_RETCODE	(CS_PUBLIC * CS_WAIT_FUNC)PROTOTYPE((
					struct _csamcontx *actx,
					struct _csasync *async,
					CS_INT sleeptime
					));
typedef CS_RETCODE	(CS_PUBLIC * CS_BLOCK_FUNC)PROTOTYPE((
					struct _csamcontx *actx,
					CS_INT flag
					));
typedef	CS_RETCODE	(CS_PUBLIC * CS_ASYNC_FUNC)PROTOTYPE((
					struct _csasync *async,
					CS_VOID *param1,
					CS_VOID *param2,
					CS_RETCODE status
					));

#ifdef DEBUG

/*
** Define the size of the debug stack which will contain function names which
** are being run
*/
#define CS_ASYNC_DBGSTACK	128

/*
** Define the maximum name to store in the stack entry. The code should make
** sure to truncate any longer names
*/
#define CS_MAX_FUNC_NAME	64

typedef struct _csamcontxdbg
{
	char	dbg_buffer[2048];
	CS_INT	dbg_tcnt;
	CS_INT	dbg_flags;
} CsAmContxDbg;

typedef struct _csasyncdbg
{
	char	dbg_name[CS_ASYNC_DBGSTACK][CS_MAX_FUNC_NAME];
} CsAsyncDbg;

#endif /* DEBUG */

/*
** Blocking macros to improve readability
*/
#define CS_ASYNC_BLOCK(A) \
	((A)->am_ctx->ac_blockfunc)((A)->am_ctx, CS_ASYNC_CB_BLOCK)
#define CS_ASYNC_UNBLOCK(A) \
	((A)->am_ctx->ac_blockfunc)((A)->am_ctx, CS_ASYNC_CB_UNBLOCK)
#define CS_ACTX_BLOCK(A) \
	((A)->ac_blockfunc)((A), CS_ASYNC_CB_BLOCK)
#define CS_ACTX_UNBLOCK(A) \
	((A)->ac_blockfunc)((A), CS_ASYNC_CB_UNBLOCK)

typedef	struct _csamcontx
{
	CS_QUEUE	ac_queue;	/* Queue Entry */
	CS_QUEUEHDR	ac_amqueue;	/* Async Handles */
	CS_VOID		*ac_blkptr;	/* Pointer available to network
					** block function */
	CS_WAIT_FUNC	ac_waitfunc;	/* Pointer to function to wait for
					** network I/O completion */
	CS_BLOCK_FUNC	ac_blockfunc;	/* Pointer to function to block
					** network I/O completion */
	CS_INT		ac_flags;	/* Context flags */
	CsAppGlobal	*ac_appglobal;	/* Application global area */
	CS_THREAD	*ac_ctxthread;	/* pointer to the thread struct */
	CS_THRDRES	*ac_mtx;	/* To protect this structure */
	CS_THRDRES	*ac_ioevent;	/* Used to signal IO on any ASYNC
					** handle in this context
					*/
#ifdef DEBUG
	CsAmContxDbg	ac_dbg;		/* Current debug information */
#endif
} CsAmContx;

/* ac_flags */
#define	CS_ASYNC_COOP		(CS_INT)0x1	/* Use the function pointers
						** and info in the global
						** structure
						*/
#define	CS_ASYNC_DONT_RUNSTACK	(CS_INT)0x2	/* Never run anything at 
						** interrupt level
						*/
#define CS_ASYNC_CTX_POLLWAIT	(CS_INT)0x0010 /* ct_poll wait on context */


typedef	struct _csasync
{
	CS_QUEUE	am_queue;	/* Next async structure on queue */
	CS_AMCONTX	*am_ctx;	/* async context for this structure */
        CS_AMCONTX      *am_ctxalloc;   /* Context used to allocate CsAsync*/

	/*
	** The following are used in managing the async stack
	*/
	CS_INT		am_stackdepth;	/* Current Postion on the stack */
	CS_INT		am_stacktop;	/* Last (first) entry in the stack */
	CS_ASYNC_FUNC	*am_stack;	/* Pointer to continuation stack */
	CS_VOID		*am_param1;	/* Param1 for continuation functions */
	CS_VOID		*am_param2;	/* Parameter 2 */
	CS_RETCODE	am_mgrstatus;	/* Input status from iopost */
	/*
	** Save stuff for completions
	*/
	CS_RETCODE	am_compstatus;	/* Completion status of last operation*/
	CS_INT		am_funcid;	/* Function id of last operation */
	/*
	** Internal info
	*/
	CS_INT		am_state;	/* Current state of this struct */
	CS_INT		am_mode;	/* Current mode of this struct */
	CS_VOID		*am_net;	/* Reserved for use by calling lib */
	CS_POST_FUNC   	am_iopostfunc;	/* User callback routine */
	/*
	** Queues to manage the checkpoint functions
	*/
	CS_INT		am_cpcount;	/* Count of checkpoint funcs */
	CS_QUEUEHDR	am_cprun;	/* runnable checkpoint funcs */
	CS_QUEUEHDR	am_cpfree;	/* free checkpoint funcs */
	CS_THRDRES	*am_mtx;	/* Protection in threads */
	CS_THRDRES	*am_ioevent;	/* Signalled when IO Completes */
#ifdef DEBUG
	CsAsyncDbg	am_dbg;		/* Current debug information */
#endif
} CsAsync;

/* States */
#define	CS_ASYNC_QUIET		(CS_INT)1
#define	CS_ASYNC_DEFERRED	(CS_INT)2
#define	CS_ASYNC_RUNABLE	(CS_INT)3
#define	CS_ASYNC_INPROGRESS	(CS_INT)4
#define	CS_ASYNC_COMPLETE	(CS_INT)5


/* Modes */
#define CS_ASYNC_DONTBLOCK	(CS_INT)0x0001
#define	CS_ASYNC_RUNDEFERRED	(CS_INT)0x0002
#define	CS_ASYNC_DONTRUN	(CS_INT)0x0004
#define CS_ASYNC_INRUNSTACK	(CS_INT)0x0008
#define CS_ASYNC_POLLWAIT	(CS_INT)0x0010	/* ct_poll wait on connection */

#define CS_ASYNC_APIMODES	(CS_ASYNC_DONTBLOCK | \
				 CS_ASYNC_INRUNSTACK | \
				 CS_ASYNC_RUNDEFERRED | CS_ASYNC_DONTRUN)


/*
** Structure to queue when managing checkpoint functions
*/
typedef struct _cscpoint
{
	CS_QUEUE	acp_queue;
	CS_INT		acp_flags;
	CS_ASYNC_FUNC	acp_cpfunc;
} CS_ASYNC_CP;

/* acp_flags */
#define CS_ASYNC_CP_EXPLICIT		(CS_INT)0x0001
#define CS_ASYNC_CP_IMMEDIATE		(CS_INT)0x0002
#define CS_ASYNC_CP_COMPLETE		(CS_INT)0x0004
#define CS_ASYNC_CP_DEFER		(CS_INT)0x0008

/* async function constants */

/* For Blocking Function */
#define	CS_ASYNC_CB_BLOCK	(CS_INT)0x1
#define	CS_ASYNC_CB_UNBLOCK	(CS_INT)0x2

/* For Shutdown Function */
#define	CS_ASYNC_FORCESHUT	(CS_INT)0x1

/* For Polling Function */
#define	CS_ASYNC_POLL_ASYNC	(CS_INT)0x1
#define	CS_ASYNC_POLL_CONTX	(CS_INT)0x2
#define	CS_ASYNC_POLL_QUIET	(CS_INT)0x4
#define	CS_ASYNC_POLL_NOTIFS	(CS_INT)0x8

#define	CS_ASYNC_POLL_MODES	(CS_ASYNC_POLL_ASYNC | CS_ASYNC_POLL_CONTX | \
				 CS_ASYNC_POLL_QUIET | CS_ASYNC_POLL_NOTIFS)

/* For Post Function */
#define	CS_ASYNC_POST_IO	(CS_INT)0x1

/* For complete Function */
#define CS_ASYNC_COMP_QUIET	(CS_INT)0x1	/* To not place thread in comp
						** queue */
#define	CS_ASYNC_COMP_FORCE	(CS_INT)0x2	/* Force this completion to
						** override current one. */
#define	CS_ASYNC_COMP_COMPLETE	(CS_INT)0x4	/* Normal */

/* Memory Allocation constants */
#define	CS_ASYNC_DEFSTACK	(CS_INT)32
#define	CS_ASYNC_CPPOOL		(CS_INT)3

/* Property Actions */
#define	CS_ASYNC_SET		(CS_INT)1
#define	CS_ASYNC_GET		(CS_INT)2

/* Properties */
#define	CS_ASYNC_PROP_POINTER1	(CS_INT)1
#define	CS_ASYNC_PROP_POINTER2	(CS_INT)2
#define	CS_ASYNC_PROP_MODE	(CS_INT)3

/* Status return flags */
#define	CS_ASYNC_STATUS_QUIET	(CS_INT)1
#define	CS_ASYNC_STATUS_BUSY	(CS_INT)2


/*
** access macros
*/
#define	COM_ASYNC_GETNET(a)		(a)->am_net
#define	COM_ASYNC_PUTNET(a, n)		(a)->am_net = (CS_VOID *)(n)
#define	COM_ASYNC_GETCTX(a)		(a)->am_ctx
#define COM_ASYNC_GETBLKPTR(ac)		(ac)->ac_blkptr
#define COM_ASYNC_PUTBLKPTR(ac, p)	(ac)->ac_blkptr = (CS_VOID *)(p)
#define COM_ASYNC_THREAD(ac)		(ac)->ac_ctxthread
#define COM_ASYNC_CTX_IOEVENT(ac)	(ac)->ac_ioevent
#define COM_ASYNC_IOEVENT(a)		(a)->am_ioevent


/*
** Debug Trace Flags
*/
#define	CS_ASYNC_DBG_REG		(CS_INT)0x0001	/* Registrations */
#define	CS_ASYNC_DBG_SNC		(CS_INT)0x0002	/* Starts & Comps */
#define	CS_ASYNC_DBG_ST			(CS_INT)0x0004	/* State transitions */
#define	CS_ASYNC_DBG_CP			(CS_INT)0x0008	/* Checkpoint runs */
#define	CS_ASYNC_DBG_CPST		(CS_INT)0x0010	/* Checkpoint trans */
#define	CS_ASYNC_DBG_MGR		(CS_INT)0x0020	/* All runmgr stuff */
#define	CS_ASYNC_DBG_IOP		(CS_INT)0x0040	/* IO Posts */
#define	CS_ASYNC_DBG_OOP		(CS_INT)0x0080	/* Other Posts */
#define	CS_ASYNC_DBG_PROPS		(CS_INT)0x0100	/* Prop Changes */
#define	CS_ASYNC_DBG_STK_EXEC		(CS_INT)0x0200	/* Stack execution */
#define	CS_ASYNC_DBG_STK_TRACE		(CS_INT)0x0400	/* Stack tracing */
#define	CS_ASYNC_DBG_VERBOSE		(CS_INT)0x1000	/* always call info */
#define	CS_ASYNC_DBG_ALL		(CS_INT)0xffff	/* turn on everything */

/*
** Debug and Trace
*/
#ifdef DEBUG

/*
** Debug macro to install function pointer and name into async struct
*/
#define	COM_ASYNC_REG_CONTINUE(a,f)				\
    { if ((a)->am_stackdepth > 0) {				\
	(a)->am_stack[--(a)->am_stackdepth] = (CS_ASYNC_FUNC)f;	\
	STRNCPY((a)->am_dbg.dbg_name[(a)->am_stackdepth],	\
		STRINGIZE(f), CS_MAX_FUNC_NAME - 1); } }

/*
** Utility function which can be used in a debugger
*/
extern CS_RETCODE CS_PUBLIC com_async_info PROTOTYPE((
	CS_ASYNC *async,
	CS_CHAR *text
	));

#else /* DEBUG */

/*
** Macro to install function pointer into async struct
*/
#define	COM_ASYNC_REG_CONTINUE(a,f)				\
	{ if ((a)->am_stackdepth > 0) {				\
		(a)->am_stack[--(a)->am_stackdepth] = (CS_ASYNC_FUNC)f; } }


#endif /* DEBUG */

/*****************************************************************************
**
** function prototypes 
**
*****************************************************************************/

/* comasync.c */
extern CS_RETCODE CS_PUBLIC com_async_init PROTOTYPE((
        CS_AMCONTX **actx,
        CS_WAIT_FUNC wait_func,
        CS_BLOCK_FUNC block_func,
	CS_INT flags,
	CS_THREAD *ctxthread
        ));
extern CS_RETCODE CS_PUBLIC com_async_assoc PROTOTYPE((
        CS_ASYNC *asyncp,
        CS_AMCONTX *newactxp
        ));
extern CS_RETCODE CS_PUBLIC com_async_exit PROTOTYPE((
        CS_AMCONTX *exitctxp
        ));
extern CS_RETCODE CS_PUBLIC com_async_shut PROTOTYPE((
        CS_AMCONTX *actx,
        CS_INT mode
        ));
extern CS_RETCODE CS_PUBLIC com_async_alloc PROTOTYPE((
        CS_AMCONTX *actx,
        CS_ASYNC **async,
        CS_INT stacksize
        ));
extern CS_RETCODE CS_PUBLIC com_async_drop PROTOTYPE((
        CS_ASYNC *async
        ));
extern CS_RETCODE CS_PUBLIC com_async_props PROTOTYPE((
        CS_ASYNC *async,
	CS_INT action,
	CS_INT property,
	CS_VOID *buffer
	));
extern CS_RETCODE CS_PUBLIC com_async_start PROTOTYPE((
	CS_ASYNC *async
        ));
extern CS_RETCODE CS_PUBLIC com_async_continue PROTOTYPE((
        CS_ASYNC *async,
        CS_RETCODE status,
	CS_INT milliseconds
        ));
extern CS_RETCODE CS_PUBLIC com_async_complete PROTOTYPE((
        CS_ASYNC *async,
	CS_INT funcid,
	CS_RETCODE final_status,
	CS_INT flags
        ));
extern CS_VOID CS_PUBLIC com_async_restart PROTOTYPE((
        CS_ASYNC *async,
        CS_RETCODE status
        ));
extern CS_VOID CS_PUBLIC com_async_abort PROTOTYPE((
        CS_ASYNC *async
        ));
extern CS_RETCODE CS_PUBLIC com_async_poll PROTOTYPE((
	CS_AMCONTX *actx,
	CS_ASYNC *async,
	CS_INT milliseconds,
	CS_INT poll_mode,
	CS_ASYNC **comp_async
        ));
extern CS_RETCODE CS_PUBLIC com_async_getcomp PROTOTYPE((
	CS_ASYNC *async,
	CS_VOID **param1,
	CS_VOID **param2,
	CS_INT *funcid,
	CS_RETCODE *final_status
        ));
extern CS_RETCODE CS_PUBLIC com_async_reg_checkfunc PROTOTYPE((
	CS_ASYNC *async,
	CS_ASYNC_FUNC funcp,
	CS_INT flags
	));
extern CS_RETCODE CS_PUBLIC com_async_iopost PROTOTYPE((
        CS_ASYNC *async,
        CS_RETCODE status
        ));
extern CS_RETCODE CS_PUBLIC com__async_iopost PROTOTYPE((
        CS_ASYNC *async,
        CS_RETCODE status,
	CS_INT flag
        ));
extern CS_RETCODE CS_PUBLIC com_async_debug PROTOTYPE((
	CS_AMCONTX *actx,
	CS_INT flags
	));
extern CS_RETCODE CS_PUBLIC com_async_status PROTOTYPE((
        CS_ASYNC *async,
	CS_INT *status
	));
extern CS_RETCODE CS_PUBLIC com_async_comp_event_wait PROTOTYPE((
        CS_ASYNC *async
        ));
extern CS_RETCODE CS_PUBLIC com_async_get_hndl_by_func PROTOTYPE((
	CS_AMCONTX	*actx,
	CS_INT		poll_mode,
	CS_ASYNC	*call_async,
	CS_ASYNC	**pasync,
	CS_INT		func_id
        ));
#endif /* __CSASYNC_H__ */
