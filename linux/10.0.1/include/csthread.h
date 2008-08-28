/* Sccsid %Z% %M% %I% %G% */

/*
**      Sybase OpenClient Version 5.0
**      Confidential Property of Sybase, Inc.
**      (c) Copyright Sybase, Inc. 1991, 1992
**      All rights reserved
*/

/*
** csthread.h - This is the common INTERNAL header file for the CS-Lib library.
*/
#ifndef __CSTHREAD_H__

#define __CSTHREAD_H__


/*
** Define routines that can take control of a given mutex so that only
** one thread can execute in a section of code protected by the given
** mutex
** CS__CREATE_MUTEX: Creates a synchronization object for mutual exclusion
** CS__TAKE_MUTEX:   Takes control of the object so no other threads can get it
** CS__RELEASE_MUTEX:Releases control of the object for other threads to grab it
** CS__DELETE_MUTEX: Frees up the object and the associated resource
** 
** Also define routines that create and manipulate 'event' semaphores
** Any thread can wait for an event and any
** other thread can set an event.  The thread waiting for an event to be 
** signalled will be scheduled out.  Once signalled, the event has to be
** explicitly reset.
** CS__CREATE_EVENT: Creates an event, or a conditional variable
** CS__SIGNAL_EVENT: Signals the event. Causes all the threads waiting on this
**			event to be scheduled to run again.
** CS__RESET_EVENT:  Resets an event to a non-signalled state.  
** CS__WAITFOR_EVENT: Causes a thread to wait for the said event to be signalled
** CS__DELETE_EVENT: Deletes the event from the system.
**
** All macros except the CREATE macro gets a CS_VOID * while the create 
** macro is passed CS_VOID ** for the mutex.
**
** 001	01/05/95	65013: Added a macro for retrieving thread id		nagar
*/

#ifndef CS__CREATE_MUTEX
#define CS__CREATE_MUTEX(thread, mutex)	\
		((thread == NULL) ? 	CS_SUCCEED :  \
					thread->create_mutex_fn(mutex))
#endif	/* CS__CREATE_MUTEX */

#ifndef CS__TAKE_MUTEX
#define CS__TAKE_MUTEX(thread, mutex)	\
		((thread == NULL) ? 	CS_SUCCEED :  \
					(thread)->take_mutex_fn(mutex))

#endif	/* CS__TAKE_MUTEX */

#ifndef CS__RELEASE_MUTEX
#define CS__RELEASE_MUTEX(thread, mutex)	\
		((thread == NULL) ? 	CS_SUCCEED :  \
					(thread)->release_mutex_fn(mutex))

#endif	/* CS__RELEASE_MUTEX */

#ifndef CS__DELETE_MUTEX
#define CS__DELETE_MUTEX(thread, mutex)	\
		(((thread) == NULL) ? 	CS_SUCCEED :  \
					(thread)->delete_mutex_fn(mutex))

#endif	/* CS__DELETE_MUTEX */

#ifndef CS__CREATE_EVENT
#define CS__CREATE_EVENT(thread, event)	\
		((thread == NULL) ?	CS_SUCCEED : \
					(thread)->create_event_fn(event))

#endif	/* CS__CREATE_EVENT */

#ifndef CS__SIGNAL_EVENT
#define CS__SIGNAL_EVENT(thread, event)	\
		((thread == NULL) ?	CS_SUCCEED : \
					(thread)->signal_event_fn(event))
#endif	/* CS__SIGNAL_EVENT */

#ifndef CS__RESET_EVENT
#define CS__RESET_EVENT(thread, event)	\
		((thread == NULL) ?	CS_SUCCEED : \
					(thread)->reset_event_fn(event))
#endif	/* CS__RESET_EVENT */

#ifndef CS__WAITFOR_EVENT
#define CS__WAITFOR_EVENT(thread, event, millisecs)	\
		((thread == NULL) ?	CS_SUCCEED : \
					(thread)->waitfor_event_fn(event, \
								millisecs))

#endif	/* CS__WAITFOR_EVENT */

#ifndef CS__DELETE_EVENT
#define CS__DELETE_EVENT(thread, event)	\
		((thread == NULL) ?	CS_SUCCEED : \
					(thread)->delete_event_fn(event))
#endif	/* CS__DELETE_EVENT */

#ifndef CS__THREAD_INTID
#define CS__THREAD_INTID(thread, ptid, size, out)	\
		((thread == NULL) ?	(*(CS_INT *)ptid = 0) : \
					(thread)->thread_id_fn(ptid, size, out))
#endif	/* CS__THREAD_INTID */


/*
** Macros to call any of the above thread functions, but maps to the
** appropriate return codes of the functions in which they are used.
** They are named with the type of return being the last part in the
** macro name.  
*/

#ifndef CS__THRDFUNC_RETCODE
#define CS__THRDFUNC_RETCODE(tfunc) \
		{ \
			CS_RETCODE retcode ; \
			if((retcode = (tfunc)) != CS_SUCCEED) \
				return ERROR_TRACE(CSE_THRDERR(retcode)); \
		}
#endif /* CS__THRDFUNC_RETCODE */

#ifndef CS__THRDFUNC_NULLPTR
#define CS__THRDFUNC_NULLPTR(tfunc) \
		{ \
			if((tfunc) != CS_SUCCEED) \
			{ \
				BOMB(); \
				return NIL(CS_VOID *) ; \
			} \
		}
#endif /* CS__THRDFUNC_NULLPTR */

/* This type of macro cannot catch errors in production code */
#ifndef CS__THRDFUNC_VOID
#define CS__THRDFUNC_VOID(tfunc) \
		{ \
			if((tfunc) != CS_SUCCEED) \
			{ \
				BOMB(); \
				return; \
			} \
		}
#endif /* CS__THRDFUNC_VOID */

#endif /* __CSTHREAD_H__ */

