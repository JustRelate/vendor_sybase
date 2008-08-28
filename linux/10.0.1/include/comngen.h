/* ORIGINAL_SCCSID:  Sccsid @(#) comngen.h 87.1 12/29/93  */


/* Sccsid %Z% %M% %I% %G% */

/*
**	Sybase COMN-LIBRARY Version 10.0
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1991, 1993
**	All rights reserved
**
** Use, duplication, or disclosure by the Government
** is subject to restrictions as set forth in subparagraph (c) (1) (ii)
** of the Rights in Technical Data and Computer Software clause
** at DFARS 52.227-7013. Sybase, Inc. 6475 Christie Avenue, Emeryville,
** CA 94608.
**
** History:
**	09/13/94 tchilder 59414, lines over 80 chars shortened for portability
*/

#ifndef __COMNGEN_H__
#define __COMNGEN_H__

/*
** The comnport.h file should be included before this file. To force the
** issue, the entire file is wrapped with a define that should be enabled
** within the port file. This results in a bunch-o-undefines if comnport.h
** is not included.
*/
#ifdef SYB_PORT_INCLUDE

/***************************************************************************
**
** Operating system
**
***************************************************************************/

#ifndef SUNMLS
#define SUNMLS  	0
#endif

#ifndef BSD42
#define	BSD42		0
#endif

#ifndef VMS
#define	VMS		0
#endif

#ifndef VOS
#define VOS		0
#endif

#ifndef SYSV
#define SYSV		0
#endif

#ifndef HPUX
#define HPUX		0
#endif

#ifndef AIX
#define AIX		0
#endif

#ifndef ULTRIX
#define ULTRIX		0
#endif

#ifndef OS2
#define OS2		0
#endif

#ifndef NT
#define NT		0
#endif

#ifndef DGAOS
#define DGAOS   	0
#endif

#ifndef MSDOS
#define MSDOS   	0
#endif

#ifndef POSIX
#define POSIX		0
#endif

/***************************************************************************
**
** Machine
**
***************************************************************************/

#ifndef SUN
#define SUN		0
#endif

#ifndef M68000
#define M68000		0
#endif

#ifndef SPARC
#define SPARC		0
#endif

#ifndef PYRAMID
#define PYRAMID		0
#endif

#ifndef VAX
#define VAX		0
#endif

#ifndef DECALPHA
#define	DECALPHA	0
#endif

#ifndef STRATUS
#define STRATUS		0
#endif

#ifndef HP9000_300
#define HP9000_300	0
#endif

#ifndef HP9000_800
#define HP9000_800	0
#endif

#ifndef HP3000
#define HP3000		0
#endif

#ifndef IBM_RT
#define IBM_RT		0
#endif

#ifndef ATT6386
#define ATT6386		0
#endif

#ifndef HW_IS_NEXT
#define HW_IS_NEXT	0
#endif

#ifndef APOLLO
#define APOLLO		0
#endif

#ifndef DEC3100
#define DEC3100		0
#endif

#ifndef MULTRIX
#define MULTRIX         0
#endif

#ifndef DG_AVIION
#define DG_AVIION		0
#endif

#ifndef SEQUENT
#define SEQUENT         0
#endif

#ifndef RS6000
#define RS6000          0
#endif

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

/*
** default to big-endian
*/
#ifndef FE_NORMSHORT
#define FE_NORMSHORT	1
#endif
#ifndef FE_NORMLONG
#define FE_NORMLONG	1
#endif

/*
** COM_NOALIGN -
**	Defined if there are NO alignment rules. The Open Server bulk
**	copy routines use a macro which checks this flag (and FE_NORMSHORT),
**	to examine/process columns in formatted rows after they come in.
*/

/*
** default to use alignment rules
*/
#ifndef COM_NOALIGN
#define COM_NOALIGN	0
#endif

/***************************************************************************
**
** CPU Type
**
***************************************************************************/

#ifndef I86
#define I86		0	/* Intel 80x86 */
#endif

#ifndef MIPS_R2000_LE
#define MIPS_R2000_LE	0	/* MIPS R2000 - (L)ittle (E)ndian */
#endif

/***************************************************************************
**
** Compiler
**
***************************************************************************/

/*  
**  PROTOTYPE macro which either produces the prototype or disappears 
**
**  Usage:	
**	func_storage_class func_type func_name PROTOTYPE((param_decl));
**
**  Example:	
**	extern int printf PROTOTYPE((const char *format, ...));
*/

#ifndef PROTOTYPE
#define	PROTOTYPE(x)	()
#endif

#ifndef ANSI_C
#define ANSI_C		0
#endif

/*
** "stringizing" macro. When defining a macro which has an argument
** converted to a string, ANSI specifies the "#" operator. Some older
** preprocessors will accept (require) quotes around the argument. i.e.:
**
**    ANSI:
**	#define FOO(X)		foo(X, #X)
**
**    OLD:
**	#define FOO(X)		foo(X, "X")
**
** The following macro (default to ANSI) hides which is really used:
**
**	#define FOO(X)		foo(X, STRINGIZE(X))
*/
#ifndef STRINGIZE
#define STRINGIZE(S)		#S
#endif

/*
** USE_VARARGS is currently used in function dbfcmd() to choose
** between using varargs or the old-style argument list.
**
** Here, we default to using old-style args ie., (arg1, arg2, etc)
*/
#ifndef USE_VARARGS
#define USE_VARARGS		0
#endif

/*
** TRADUNIX varargs indicate the we use varargs.h, while ANSI_VARARGS 
** indicate stdargs.h.  This is used in sybvarg.h.
**
** Here, we default to ansi if none specified.
*/

#ifndef TRADUNIX_VARARGS
#define TRADUNIX_VARARGS		0
#endif

#ifndef ANSI_VARARGS
#define ANSI_VARARGS			1
#endif

/*
** define whether the compiler does row major ordering or column major
** ordering when calculating an offset for a 2 dimensional array. This macro
** is used in mapping a two dimensional array onto a one dimensional array.
** The default used here is row major ordering (used by the SUN compiler).
*/
#ifndef ARRAY_INDEX
#define ARRAY_INDEX(ROW, COL, DIM) (((ROW) * (DIM)) + (COL))
#endif

/*
** define null if needed
*/
#ifndef NULL
#define NULL    	0
#endif

/*
** convenience macro for casting null
*/
#ifndef NIL
#define NIL(T)          ((T) NULL)
#endif

/*
** define true and false if needed
*/
#ifndef TRUE
#define TRUE    	1
#endif
#ifndef FALSE
#define FALSE   	0
#endif

/*
** Void data type.
*/
#ifndef VOID
#define VOID    	void
#endif

/*
** Register supported by system
*/
#ifndef REGISTER
#define REGISTER    	register
#endif

/*
** System support of structure assignments.
*/
#ifndef FE_STRCT_ASSN_OK
#define FE_STRCT_ASSN_OK	1
#endif

/*
** Bits per byte
*/
#ifndef BITS_PER_BYTE
#define BITS_PER_BYTE	8
#endif

/*
** NOTE: This is used in comnlib:mnycnvt.c
** This macro is defined to avoid rounding while converting from float to int
** or float to long in some platforms like m88k - from server.h
*/
#ifndef DBLASSIGN
#define DBLASSIGN(x, y, type)	(y) = (type)(x)
#endif /* DBLASSIGN */

/***************************************************************************
**
** miscellaneous system/machine defines
**
***************************************************************************/

/*
** define the environment variable passed to getenv
*/
#ifndef ENV_SYBASE
#define ENV_SYBASE	"SYBASE"
#endif

/*
** define the name of the interfaces file
*/
#ifndef INTERFACES_FILE
#define INTERFACES_FILE	"interfaces"
#endif

/*
** define the enviroment variable name to check
** for the location of the interfaces file
*/
#ifndef INTERFACES_ENVVAR
#define INTERFACES_ENVVAR	"SYBASE_INTERFACE"
#endif

/* 
** define the maximum length of the value of an environment variable.
*/
#ifndef MAXENVNAME
#define MAXENVNAME	256
#endif

/*
** define the maximum length of sybase-defined language, charset and sortorder
*/
#ifndef MAXLANG
#define MAXLANG		256
#endif
 
#ifndef MAXCHARSET
#define MAXCHARSET	256
#endif
 
#ifndef MAXSORTORDER
#define MAXSORTORDER	256
#endif

/*
** define the default firstday. 
*/
#ifndef DEFFIRSTDAY
#define DEFFIRSTDAY	7
#endif

/*
** define the name of the us_english directory
*/
#ifndef	LOCUSENGLISH
#define	LOCUSENGLISH	"us_english"
#endif

/*
** define file system specific defines
**
** NOTE: Do not use FILENAME14, this is only present for backwards
**	 compatibility.
*/
#ifndef FILENAME_LEN
#define FILENAME_LEN	1024
#endif

#ifndef FILENAME14
#define	FILENAME14	0
#endif

/*
** The following is passed into FOPEN as the mode.
*/
#ifndef FILE_OPEN_MODE  
#define FILE_OPEN_MODE  "w"
#endif

/*
** The following specify the components that are need to construct a path
** name. The defaults specified here will work on most (probably all) unix
** systems. See the vms port file for an example of re-defines that are used
** in order to work with other systems.
*/
#ifndef DIRSEPARATOR
#define DIRSEPARATOR	"/"
#endif

#ifndef	DIRENDING
#define	DIRENDING	""
#endif

#ifndef	DIRENDSTRIP
#define	DIRENDSTRIP	0
#endif

/*
** define MAX number of file descriptors per process; used by everyone
** that doesn't have getdtablesize().
*/
#ifndef MAXFD
#define MAXFD		32
#endif

/* 
** The number of significant decimal digits in a floating-point number will
** vary, depending on the floating-point representation. Sun uses 64-bit IEEE
** floating-point numbers, which yield 17 significant decimal digits.
*/
#ifndef SIG_DEC_DIGITS
#define SIG_DEC_DIGITS	17
#endif

#ifndef DEFCHARSET
#define DEFCHARSET	"iso_1"
#endif

/*
** NOSHARE is defined for VMS platforms 
*/
#ifndef NOSHARE
#define NOSHARE
#endif

/*
** AM_POLL_REQUIRED is defined in windows for forced polling.
*/

#if  defined(AM_POLL_REQUIRED)
#define  CS__ASYNC_QUIET_STATUS()  CS_PENDING
#else
#define  CS__ASYNC_QUIET_STATUS()  CS_QUIET
#endif

/*
** AM_QUICK_POLL_REQUIRED - Macro to determine whether we need a quick
**                        poll. It returns 0/1 for generic platforms
**			  based on milli secs and 1 for windows.
*/
#ifndef AM_QUICK_POLL_REQUIRED
#define AM_QUICK_POLL_REQUIRED(milliseconds)    (((milliseconds) == 0) ? 0 : 1)
#endif

/*
** USE_SCCSID is defined for all platforms the want sccs keywords embedded
** in the source (since most do, it's the default).
*/
#ifndef USE_SCCSID
#define USE_SCCSID	1
#endif

/*
** Defining the overflow conditions for integer and float types.
**
** NOTE: These defines MUST be used within the correct context. An example
**	 of this is trying to find out if a BYTE > MAXI1. This makes no
**	 sense because a BYTE cannot hold more than MAXI1. To use it properly,
**	 intall the value in a unsigned long, and do the comparison.
**
** These values can be found in limits.h
*/

#ifndef MAXI4
#define MAXI4		((CS_INT)(2147483647L))
#endif

#ifndef MINI4
#define MINI4		((CS_INT)(-2147483648L))
#endif

/*
** Added this #define as part of the fix for BTS:70083.  Needed to compare
** against unsigned max 2-byte number.
*/

#ifndef UMAXI2
#define UMAXI2		((CS_INT)(0xFFFF))
#endif

#ifndef MAXI2
#define MAXI2		((CS_INT)(32767))
#endif

#ifndef MINI2
#define MINI2		((CS_INT)(-32768))
#endif

#ifndef MAXI1
#define MAXI1		0xFF		/* it's unsigned */
#endif

/*
** define MAXI8, MINI8  here to get rid of warings from the compiler. 
** The real value for MAXI8 and MINI8for a 64 bit (8 bytes integer) 
** machine needs to be defined in comnport.h for that specific platform.
*/
#ifndef MAXI8
#define MAXI8		MAXI4
#endif

#ifndef MINI8
#define MINI8		MINI4
#endif

#ifndef MAXI1FLT
#define MAXI1FLT	255.00
#endif

#ifndef MAXI2FLT
#define MAXI2FLT	32767.00
#endif

#ifndef MINI2FLT
#define MINI2FLT	-32768.00
#endif

/*
** Max and Min I4 values expressed as floating point values
*/
#ifndef MAXI4FLT
#define MAXI4FLT	2147483647.0
#endif

#ifndef MINI4FLT
#define MINI4FLT	-2147483648.0
#endif

#ifndef MAXI8FLT
#define MAXI8FLT	(float)MAXI8
#endif

#ifndef MINI8FLT
#define MINI8FLT	(float)MINI8
#endif

/*
** MAXDOUBLE and MAXFLOAT are defined in values.h. If values.h is not present
** (e.g. VMS), define MAXFLT8 and MAXFLT4 in comnport.h.
*/
#ifndef MAXFLT8
#define MAXFLT8		MAXDOUBLE
#endif

#ifndef MAXFLT4
#define MAXFLT4		MAXFLOAT
#endif

#ifndef MINFLT8
#define MINFLT8		-MAXFLT8
#endif

#ifndef MINFLT4
#define MINFLT4		-MAXFLT4
#endif

/***************************************************************************
**
** utility macros
**
***************************************************************************/

/*
** NOTE: These are also defined in comnlib.h. They are present here for
**	 backwards compatibility.
*/

#ifndef MAX
#define	MAX(a, b)	((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define	MIN(a, b)	((a) < (b) ? (a) : (b))
#endif

#ifndef ABS
#define	ABS(a)		((a) > 0 ? (a) : -(a))
#endif

/***************************************************************************
**
** Macros for C-Lib Interfaces
**
***************************************************************************/

/* 
** NOTE: These macros create default definitions if macros are not defined
** 	 in the appropriate comnport.h file.
**
**	 Please OVERIDE these macros if the platform defines a different 
**       functional interface via a include file, and the argument casting
**	 differs. An example of this is the use of void *alloc/free routines
**	 on some platforms.
**
**	 All macro definitions in this file adhere to the ANSI standard for
**	 C standard library routines.
*/

/*
** memory allocator/free routines
*/
#ifndef CALLOC
#define CALLOC(N, S)		calloc((size_t)(N), (size_t)(S))
#endif

#ifndef REALLOC
#define REALLOC(P, S)		realloc((void *)(P), (size_t)(S))
#endif

/*
** NOTE: The symantics for free are now ANSI based by default.
**
*/
#ifndef FREE
#define FREE(P)	 		free((void *)(P))
#endif

#ifndef MALLOC
#define MALLOC(S)	 	malloc((size_t)(S))
#endif

/*
** memory copy/compare routines
*/
#ifndef MEMCMP
#define MEMCMP(D,S,N)		memcmp((const void *)(D), (const void *)(S), \
					(size_t)(N))
#endif

#ifndef MEMCPY
#define MEMCPY(D,S,N)		memcpy((void *)(D), (const void *)(S), \
					(size_t)(N))
#endif

#ifndef MEMSET
#define MEMSET(D,V,N)		memset((void *)(D), (int)(V), (size_t)(N))
#endif

#ifndef	MEMMOVE
#define	MEMMOVE(D,S,N)		memmove((void *)(D), (const void *)(S), \
					(size_t)(N))
#endif

#ifndef MEMZERO
#define MEMZERO(D,N)		MEMSET(D, 0, N)
#endif

/*
** NOTE: The macro MEMCOPY is now OBSOLETE to reduce parameter ordering
**	 confusion. Please use MEMCPY.
*/
#ifndef MEMCOPY
#define MEMCOPY(S, D, N)	MEMCPY(D, S, N)
#endif

/*
** math routines
*/
#ifndef STRTOD
#define STRTOD(D, S)		strtod((const char *)(D), (char **)(S))
#endif

#ifndef IS_DIGIT
#define IS_DIGIT(C)		com_isdigit((C))
#endif

/*
** string manipulation routines
*/
#ifndef STRCAT
#define STRCAT(D, S)		strcat((char *)(D), (const char *)(S))
#endif

#ifndef STRCHR
#define STRCHR(S, C)		strchr((const char *)(S), (int)(C))
#endif

#ifndef STRCPY
#define STRCPY(D,S)		strcpy((char *)(D), (const char *)(S))
#endif

#ifndef STRLEN
#define STRLEN(str)	 	strlen((const char *)(str))
#endif

#ifndef STRNCAT
#define STRNCAT(D,S,N)		strncat((char *)(D), (const char *)(S), \
					(size_t)(N))
#endif

#ifndef STRNCPY
#define STRNCPY(D,S,N)		strncpy((char *)(D), (const char *)(S), \
					(size_t)(N))
#endif

#ifndef STRRCHR
#define STRRCHR(S,C)		strrchr((const char *)(S), (int)(C))
#endif

/*
** NOTE: Due to international support requiring unsigned string comparisons,
**	 the following calls a common lib routine to do the work. Do not
**	 overide these calls unless you are sure that the native system
**	 supports unsigned string compares.
*/
#ifndef STRCMP
#define STRCMP(S1,S2)		com_unsignstrcmp((unsigned char *)(S1), \
						(unsigned char *)(S2))
#endif

#ifndef STRNCMP
#define STRNCMP(S1,S2,N)	com_unsignstrncmp((unsigned char *)(S1), \
					(unsigned char *)(S2), (int)(N))
#endif

/*
** ascii to integer conversion routines
*/
#ifndef STRTOL
#define STRTOL(C, E, B)		strtol((char *)(C), (char **)(E), (int)(B))
#endif

#ifndef ATOI
#define ATOI(S)			atoi((char *)(S))
#endif

#ifndef ATOL
#define ATOL(S)			atol((char *)(S))
#endif

/*
** stdio/formating routines
*/
#ifndef SYBFOPEN
#define SYBFOPEN		fopen
#endif

#ifndef FCLOSE
#define FCLOSE			fclose
#endif

#ifndef SYBGETC
#define SYBGETC			getc
#endif

#ifndef SYBFSEEK
#define SYBFSEEK		fseek
#endif

#ifndef SYBFEOF
#define SYBFEOF			feof
#endif

#ifndef SYBFWRITE
#define SYBFWRITE		fwrite
#endif

#ifndef SYBFTELL
#define SYBFTELL		ftell
#endif

#ifndef SYBFREAD
#define	SYBFREAD		fread
#endif

#ifndef SYBFERROR
#define SYBFERROR		ferror
#endif

#ifndef FPRINTF
#define FPRINTF			fprintf
#endif

#ifndef SPRINTF
#define SPRINTF			sprintf
#endif

#ifndef VFPRINTF
#define VFPRINTF		vfprintf
#endif

#ifndef FGETS
#define FGETS			fgets
#endif

#ifndef FFLUSH
#define FFLUSH			fflush
#endif

#ifndef STDOUT
#define STDOUT			stdout
#endif

#ifndef STDERR
#define STDERR			stderr
#endif

#ifndef STDIN
#define STDIN			stdin
#endif

/*
** errno value
*/
#define COM__ERRNO		errno

/*
** system command
*/
#ifndef SYSTEM
#define SYSTEM(cmd)		system(cmd)
#endif

/*
** exit command
*/
#ifndef EXIT
#define EXIT(status)		exit(status)
#endif

/*
** main entr point for executables
*/
#ifndef MAIN
#define MAIN(A, V)		main(A, V)
#endif

/*
** sleep command (in seconds)
*/
#ifndef SLEEP
#define SLEEP(S)		sleep(S)
#endif

/*
** macro to get the pid 
*/
#ifndef GETPID
#define GETPID()		getpid()
#endif

/*
** macro to get the os error
*/
#ifndef STRERROR
#define STRERROR(N)		strerror(N)
#endif

/*
** macro to convert time to a string
*/
#ifndef CTIME
#define CTIME(P)		ctime(P)
#endif


#ifndef SPRINTF_PID
#define SPRINTF_PID(pidstr)	SPRINTF(pidstr, "%d", GETPID())
#endif

/*
** Using braces around code in C macros can cause problems when the macros are
** used in if conditional statements. e.g.:
**
**      #define MACRO()         { do something }
**
**      if (cond)
**              MACRO();        <- causes syntax error since ; before else
**      else
**              other stuff
**
** The following macro fixes this problem, and should not affect performance.
** (Unless the C compiler is real brain dead).
*/
#ifndef BRACKET
#define BRACKET(C)		do { C } while(0)
#endif

/*
** Return type of "signal()"
*/
#ifndef SIGRET
#define SIGRET		void
#endif

/*
** Signal handler function pointer prototype case -- empty here,
** assumes that the sighandler declaration we use exactly matches
** the OS's prototype for signal handlers.  add a typedef and
** a macro-definition for the cast in comnport.h if necessary
*/
#ifndef SYBSIGHANCAST
#define SYBSIGHANCAST
#endif /* SYBSIGHANCAST */

/*
** Return type of "sprintf()"
*/
#ifndef SPRINTFRET
#define SPRINTFRET	int
#endif

/***************************************************************************
**
** System bug macros
**
***************************************************************************/

/*
** NOTE: The following defines are used in defining a section of code which
**	 is enables to get around a bug on a particular platform. Most
**	 platforms will not need to define these.
*/

#ifndef SUN_STRTOD_BUG
#define SUN_STRTOD_BUG		0
#endif

/***************************************************************************
**
** Debug macros.
**
***************************************************************************/

#if defined(DEBUG_ASSERT) || defined(DEBUG)

#ifndef ASSERT
#define ASSERT(X)               BRACKET(if (!(X)) com_bomb(__FILE__,__LINE__);)
#endif

#ifndef BOMB
#define BOMB()                  com_bomb(__FILE__, __LINE__)
#endif

#ifndef COPSTR
#define COPSTR(P_D, P_S, SIZE)  com_copstr(P_D, P_S, SIZE)
#endif

#ifndef CATSTR
#define CATSTR(P_D, P_S, SIZE)  com_catstr(P_D, P_S, SIZE)
#endif

#ifndef CHECK_PTR
#define CHECK_PTR(P_P)		com_chkptr((char *)(P_P), __FILE__, __LINE__)
#endif

#ifndef CHECK_VARG
#define CHECK_VARG(P_P)         com_chkptr((char *)(P_P), __FILE__, __LINE__)
#endif

#ifndef CHECK_FUNC
#define CHECK_FUNC(P_P)		com_chkfunc((void *)(P_P),__FILE__,__LINE__)
#endif

/*
** The following print macro MUST have double parentheses when used. This
** allows the preprocessor to expand it with var args. e.g.
**
** The envocation:
**
**      COM_DBG_PRINT((arg1 = %d\n", arg1));
**
** gets expanded to:
**
**      fprintf (fp, "arg1 = %d\n", arg1);
**
** using the default macro.
**
*/

#ifndef COM_DBG_PRINT
#define COM_DBG_PRINT(X)	comn_debug_print X
#endif

#ifndef COM_DBG_VPRINT
#define COM_DBG_VPRINT(X)	comn_debug_vprint X
#endif

#ifndef ERROR_TRACE
#define ERROR_TRACE(E)		com_errtrace((E), __FILE__, __LINE__)
#endif

#else /* ! #if defined(DEBUG_ASSERT) || defined(DEBUG) */

#ifndef ASSERT
#define ASSERT(X)
#endif

#ifndef BOMB
#define BOMB()
#endif

#ifndef COPSTR
#define COPSTR(P_D, P_S, SIZE)  STRCPY(P_D, P_S)
#endif

#ifndef CATSTR
#define CATSTR(P_D, P_S, SIZE)  STRCAT(P_D, P_S)
#endif

#ifndef CHECK_PTR
#define CHECK_PTR(P_P)
#endif

#ifndef CHECK_VARG
#define CHECK_VARG(P_P)
#endif

#ifndef CHECK_FUNC
#define CHECK_FUNC(P_P)
#endif

#ifndef COM_DBG_PRINT
#define COM_DBG_PRINT(X)
#endif

#ifndef COM_DBG_VPRINT
#define COM_DBG_VPRINT(X)
#endif

#ifndef ERROR_TRACE
#define ERROR_TRACE(E)		(E)
#endif

#endif /* defined(DEBUG_ASSERT) || defined(DEBUG) */

/*
** NOTE: defining COM_USE_SYSTEM_CALL will changed the code which validates
**	 pointers to use a system call to do the validation.  This means the
**	 code will run MUCH slower, but is more reliable in detecting bad
**	 pointer values.
*/
#ifndef COM_USE_SYSTEM_CALL
#define COM_USE_SYSTEM_CALL	0
#endif

/***************************************************************************
**
** Unit test defines.
**
***************************************************************************/

#ifdef UNIT_TEST

/*
** The assertion mechanism for unit tests shoudl use the following macro
** instead of the ASSERT() macro. Assertions are redefined when compiling
** unit tests; otherwise external references to the com_dbg routines would
** need to be satisfied.
*/

#ifndef UNIT_ASSERT
#define UNIT_ASSERT(X)  BRACKET( if (!(X)) { \
        printf("Unit test failed: file %s, line %d\n", __FILE__, __LINE__); \
	        abort(); } )
#endif

#ifndef UNIT_BOMB
#define UNIT_BOMB()  \
        (printf("Unit test failed: file %s, line %d\n", __FILE__, __LINE__), \
	        abort())
#endif

/*
** redefine debug macros
*/
#if defined(DEBUG_ASSERT) || defined(DEBUG)

#undef ASSERT
#define ASSERT(X)          	UNIT_ASSERT(X)

#undef BOMB
#define BOMB()            	UNIT_BOMB()

#undef COPSTR
#define COPSTR(P_D, P_S, SIZE)  STRCPY(P_D, P_S)

#undef CATSTR
#define CATSTR(P_D, P_S, SIZE)  STRCAT(P_D, P_S)

#undef CHECK_PTR
#define CHECK_PTR(P_P)

#undef CHECK_VARG
#define CHECK_VARG(P_P)

#undef CHECK_FUNC
#define CHECK_FUNC(P_P)

#undef ERROR_TRACE
#define ERROR_TRACE(E)		(E)

#endif /* defined(DEBUG_ASSERT) || defined(DEBUG) */

/*
** The following print macro MUST have double parentheses when used. This
** allows the preprocessor to expand it with var args. e.g.
**
** The envocation:
**
** 	UNIT_PRINT(("arg1 = %d\n", arg1));
**
** gets expanded to:
**
**	printf ("arg1 = %d\n", arg1);
**
** using the default macro.
**
*/
#ifndef UNIT_PRINT
#define UNIT_PRINT(X)   printf X
#endif

#if defined(UNIT_VERBOSE)
#define UNIT_VPRINT     UNIT_PRINT
#else
#define UNIT_VPRINT
#endif

#endif /* UNIT_TEST */

/***************************************************************************
**
** Product specific defines (SHOULD NOT BE HERE!)
**
***************************************************************************/

/*
** max length of sql statement buffer
*/
#ifndef SQLMAXLEN
#define SQLMAXLEN	3072
#endif

#ifndef PERFORMANCE
#define PERFORMANCE	0
#endif

/*
** Icon height adjustment factor.
*/
#ifndef ICON_TXT_FCTR
#define ICON_TXT_FCTR	2    
#endif

/*
** sanity check for port defines
*/
#ifndef DBOSERRNO
#define DBOSERRNO	errno
#endif

/***************************************************************************
**
**      Thread synchronization
**
***************************************************************************/

#ifndef CS_THREADS_SUPPORTED
#define CS_THREADS_SUPPORTED    0
#endif

#undef SYB_PORT_INCLUDE
#endif /* SYB_PORT_INCLUDE */


#ifndef MAX_BLOCK_SIZE
#define MAX_BLOCK_SIZE(a)  (a) 
#endif

#endif /* __COMNGEN_H__ */
