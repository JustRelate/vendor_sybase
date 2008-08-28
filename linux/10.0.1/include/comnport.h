/* Sccsid %Z% %M% %I% %G% */
/*
**	Sybase COMN-LIBRARY Version 5.0
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1991, 1992
**	All rights reserved
**
**
** Use, duplication, or disclosure by the United States Government
** is subject to restrictions as set forth in subparagraph (c) (1) (ii)
** of the Rights in Technical Data and Computer Software clause
** at CFR 52.227-7013. Sybase, Inc. 6475 Christie Avenue, Emeryville,
** CA 94608.
**
*/

#ifndef __COMNPORT_H__
#define __COMNPORT_H__

/***************************************************************************
**
** Operating system
**
***************************************************************************/

#if defined(linux)
#define	LINUX	1
#endif
#define	SYSV 	1
#define	POSIX 	1

/*
** NOTE: The following indicates that bsd-ish functions exists in source code.
**
*/
#define BSD42	1
/***************************************************************************
**
** Machine
**
***************************************************************************/

/*
** NOTE: The following should be combined into ONE define
*/
#define M_I86	1
#define I86 	1

/*
**
** Byte ordering.
**
** FE_NORMSHORT -
**	Define FE_NORMSHORT to be 1 if shorts have the MSB in smallest address
**	(MSB, LSB).  Also known as "big-endian" byte ordering (byte 0
**	is at the "big" end).  "Big-endian" machines include MC 68000,
**	IBM 370.  Most networks have "big-endian" byte-ordering.
**
**	Define FE_NORMSHORT to be 0 if shorts have the MSB in the largest
**	address (LSB, MSB).  Also known as "little-endian" byte
**	ordering (byte 0 is at the "little" end).  "Little-endian"
**	machines include iAPX x86, NS 32000 and DEC VAX.
**
** FE_NORMLONG -
**	Define FE_NORMLONG to be 1 if longs have the MSB in smallest address
**	(MSB, MSB-1, MSB-2, LSB).  Also known as "big-endian" byte ordering
**	(byte 0 is at the "big" end).  "Big-endian" machines include MC
**	68000, IBM 370.  Most networks have "big-endian" byte-ordering.
**
**	Define FE_NORMLONG to be 0 if shorts have the MSB in the largest
**	address (LSB, MSB-2, MSB-1, MSB).  Also known as
**	"little-endian" byte ordering (byte 0 is at the "little" end).
**	"Little-endian" machines include iAPX x86, NS 32000 and DEC
**	VAX.
*/

#define FE_NORMSHORT	0
#define FE_NORMLONG	0

/*
** No alignment rules on the NCR platform. Define NOALIGN to 1
*/
#define COM_NOALIGN	0

/***************************************************************************
**
** Compiler
**
***************************************************************************/

/*
** NOTE: Will use the generic macros defined in comngen
*/

/*
** gcc can use ansi varargs
*/
#define ANSI_VARARGS		1
#define TRADUNIX_VARARGS	0
/***************************************************************************
**
** miscellaneous system/machine defines
**
***************************************************************************/

/*
** Platform name that will used to search locales.dat
*/
#define LOCALE_PLATFORM	"linux"

/*
** default character set (added for front ends)
*/
#define ISO_1		1

/***************************************************************************
**
** C-Lib Interfaces 
**
***************************************************************************/

/*
** need, since we reference stdout
*/
#include	<stdio.h>

/*
** Include values.h to value for HIBITL
*/
#include	<values.h>

/*
** include math interface file
*/
#include	<math.h>

/*
** How we get "errno"
*/
#include	<errno.h>

/*
** Specify include file for string functions 
*/
#include	<string.h>

/*
** specify memory functions
*/
#include	<memory.h>

/*
** specify malloc functions, atoi() etc
*/
#include	<stdlib.h>

/*
** include time.h to use time() fuinction
*/
#include	<time.h>

/*
** include unistd.h to use access system call 
*/
#include <unistd.h>

/*
** Override any macros defined in comngen.h that are different
** for this platform
*/


/* 
** define FILE_READ_ACCESS macro
*/
#define FILE_READ_ACCESS(path)	(access((char *)(path), (int) R_OK) == 0 ? \
					CS_SUCCEED : CS_FAIL)

/***************************************************************************
**
** Debug macros.
**
***************************************************************************/

/*
** NOTE: Will use the generic macros defined in comngen
*/

/***************************************************************************
**
** Product specific defines (SHOULD NOT BE HERE!)
**
***************************************************************************/

/*
** Supported networks.  (Possible choices are in dbprivate.h)
*/
#define TCPIPNET	1

/*
** Terminal driver used.  (Possible choices are in sioprivate.h)
*/
#define TERMIO		1

/*
**  set define for flagging that comnport.h was included.
*/
#define SYB_PORT_INCLUDE 0

#endif /* __COMNPORT_H__ */
