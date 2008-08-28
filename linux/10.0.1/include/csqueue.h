
/* Sccsid %Z% %M% %I% %G% */

/*
**	Sybase OpenClient Version 5.0
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1991
**	All rights reserved
*/

/*
** csqueue.h -	This header file defines the public queue macros and queue
**		structures.
**
** History:
**	11/16/93 tchilder 63442, COM_INSERTQ defined w/o space after label
*/
#ifndef __CSQUEUE_H__

#define __CSQUEUE_H__

/* Queue element definition						*/
typedef struct _csqueueele
{
	struct _csqueueele	*ele_next;
	struct _csqueueele	*ele_prev;
} CS_QUEUE;

/* queue header typedef */
typedef struct _csqueuehdr
{
	CS_QUEUE	*ele_first;
	CS_QUEUE	*ele_last;
} CS_QUEUEHDR;

/* 
 * Queue Manipulation Macros:
 *
 *	COM_ADDQ:	Adds a queue element as the last element in 
 *			a queue.
 *
 *	COM_ADDQ_HEAD:	Add a queue element at the head of a queue.
 *
 *	COM_INSERTQ:	Insert an element on q queue before the indicated
 *			element.
 *
 *	COM_GETQ:	Get the first element on a queue.
 *
 *	COM_REMQ:	Remove a queue element from an arbitrary location
 *			in a queue.
 */
#define COM_ADDQ(qh,qe)	{ \
					CS_QUEUEHDR	*h; \
					CS_QUEUE	*e; \
					h = (CS_QUEUEHDR *)qh; \
					e = (CS_QUEUE *)qe; \
					e->ele_next = (CS_QUEUE *)h; \
					e->ele_prev = h->ele_last; \
					h->ele_last->ele_next = e; \
					h->ele_last = e; \
				}

#define	COM_ADDQ_HEAD(qh,qe)	{ \
					CS_QUEUEHDR	*h; \
					CS_QUEUE	*e; \
					h = (CS_QUEUEHDR *)qh; \
					e = (CS_QUEUE *)qe; \
					e->ele_next = h->ele_first; \
					e->ele_prev = (CS_QUEUE *)h; \
					h->ele_first->ele_prev = e; \
					h->ele_first = e; \
				}

#define COM_GETQ(qh,qe)	{ \
					CS_QUEUEHDR 	*h; \
					CS_QUEUE	**e; \
					h = (CS_QUEUEHDR *)qh; \
					e = (CS_QUEUE **)qe; \
					if(h->ele_first == (CS_QUEUE *)h) \
					{ \
						*e = NIL(CS_QUEUE *); \
					} \
					else { \
						*e = h->ele_first; \
						h->ele_first = \
						h->ele_first->ele_next; \
						h->ele_first->ele_prev = \
							(CS_QUEUE *)h; \
						(*e)->ele_next = \
							NIL(CS_QUEUE *); \
						(*e)->ele_prev = \
							NIL(CS_QUEUE *); \
					} \
				}

#define COM_INSERTQ(qh,oqe,nqe)	{ \
					CS_QUEUEHDR 	*h; \
					CS_QUEUE 	*oe; \
					CS_QUEUE 	*ne; \
					h = (CS_QUEUEHDR *)qh; \
					oe = (CS_QUEUE *)oqe; \
					ne = (CS_QUEUE *)nqe; \
					if(oe->ele_prev == (CS_QUEUE *)h) \
					{ \
						h->ele_first = ne; \
						oe->ele_prev = ne; \
						ne->ele_next = oe; \
						ne->ele_prev = \
							(CS_QUEUE *)h; \
					} \
					else { \
						ne->ele_prev = \
						(CS_QUEUE *)oe->ele_prev; \
						oe->ele_prev->ele_next = ne;\
						ne->ele_next = oe; \
						oe->ele_prev = ne; \
					} \
				}

#define COM_REMQ(qe)		{ \
					CS_QUEUE 	*e; \
					e = (CS_QUEUE *)qe; \
					e->ele_next->ele_prev = e->ele_prev;\
					e->ele_prev->ele_next = e->ele_next;\
					e->ele_next = NIL(CS_QUEUE *); \
					e->ele_prev = NIL(CS_QUEUE *); \
				}

#endif /* __CSQUEUE_H__ */
