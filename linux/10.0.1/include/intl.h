/* ORIGINAL_SCCSID:  Sccsid @(#) intl.h 87.7 1/2/94  */



/* Sccsid %Z% %M% %I% %G% */

/*
**      Sybase INTL-LIBRARY Version 5.0
**      Confidential Property of Sybase, Inc.
**      (c) Copyright Sybase, Inc. 1991
**      All rights reserved
**
** Use, duplication, or disclosure by the Government
** is subject to restrictions as set forth in subparagraph (c) (1) (ii)
** of the Rights in Technical Data and Computer Software clause
** at DFARS 52.227-7013. Sybase, Inc. 6475 Christie Avenue, Emeryville,
** CA 94608.
**
** History
**	03/29/94 tchilder 54179, added support for MVS port (IBM370)
**	08/30/94 tchilder 59414, shortened max line length <= 80 characters
**	12/07/94 tchilder 64194, eliminate dependency on csmvsdef.h
*/

/*
**
** History
** Chg#	Date		Description					Resp
** 001	10Oct94		Added INTE_NOMEM macro			 	soma
**
*/

#ifndef __INTL_H__
#define __INTL_H__

/*
** 	INTL.H
** 
** 	Defines the structures, types and constants needed
** 	for the Intl-Library routines
**
** 	Requires:  None
*/

/*
** set up c++ wrapper for function name mangeling
*/
#if defined(__cplusplus)
#define INTL_START_EXTERN_C	extern "C" {
#define INTL_END_EXTERN_C		}
#else
#define INTL_START_EXTERN_C		
#define INTL_END_EXTERN_C		
#endif /* defined(__cplusplus) */

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

#if defined(MAC) || defined(_MSC_VER) || defined(__BORLANDC__) || \
    defined(__STDC__) || defined(__cplusplus)
# define PROTOTYPE(s) s
#else
# define PROTOTYPE(s) ()
#endif

#endif /* PROTOTYPE */

/*
** Definition of function modifiers
*/
#if WIN3
#define INTL_PUBLIC     __export _far _pascal
#define INTL_INTERNAL   _far _pascal
#define INTL_VARARGS    __export _far _cdecl

#else /* WIN3 */

#if (_MSC_VER >= 800)

#define INTL_PUBLIC     __stdcall
#define INTL_INTERNAL   INTL_PUBLIC
#define INTL_VARARGS    INTL_PUBLIC

#else /* (_MSC_VER >= 800) */

#define INTL_PUBLIC  
#define INTL_INTERNAL
#define INTL_VARARGS

#endif /* (_MSC_VER >= 800) */
	
#endif /* WIN3 */

/*
** The range of possible values for Intl-Lib error numbers.  OC-Lib
** requires that the absolute value of all Intl-Lib error numbers
** are able to fit in a 1 byte integer.
*/
#define INTL_MAXERR	0	/* No error numbers can be greater
				 * than this value
				 */

#define INTL_MAXOSERR	-150	/* Non-OS Intl-Library errors 
				 * must be between INTL_MAXERR
				 * and INTL_MAXOSERR
				 */

#define INTL_MINERR	-255	/* Operating system errors must
				 * be between INTL_MINERR and
				 * INTL_MAXOSERR
				 */
#define INTL_MORE_DATA		1	/* this is used in intl_nextvalue to
					** return partial data when the 
					** internal buffer is full.
					*/

/* Operating system errors */

/* Unable to open file */
#define	INTE_FOPEN	(INTL_MAXOSERR - 1)

/* Unable to close file */
#define	INTE_FCLOSE	(INTL_MAXOSERR - 2)

/* Unable to read file */
#define	INTE_FREAD	(INTL_MAXOSERR - 3)

/* Unable to write to file */
#define	INTE_FWRITE	(INTL_MAXOSERR - 4)

/* Unexpected end of file */
#define	INTE_EOF	(INTL_MAXOSERR - 5)

/* Couldn't find the user 'sybase' */
#define	INTE_NOSYB	(INTL_MAXOSERR - 6)

/* Unable to access file information */
#define	INTE_FINFO	(INTL_MAXOSERR - 7)

/* Unable to allocate memory */
#define	INTE_NOMEM	(INTL_MAXOSERR - 8)


/* Non-OS Intl-Library errors */

/* General Intl-Library error */
#define	INTE_GENERR	-1

/* Syntax error:  no value found */
#define	INTE_NOVAL	-2

/* Syntax error: no entry found */
#define	INTE_NOENTRY	-3

/* Firstday value in datetime section is out of range */
#define	INTE_FDORNG	-4

/* Element of dateorder entry is invalid.  Valid elements are 'm',
 * 'd', and 'y' 
 */
#define	INTE_DOINVAL	-5

/* Time format entry in datetime section is invalid */
#define	INTE_TFINVAL	-6

/* Copying string would result in overflow of buffer */
#define	INTE_OFLOW	-7

/* Unknown version number in compiled translation file */
/* #define	INTE_XBADVER	-8 */
/* No longer needed, but don't reuse -8! */

/* Entry too long */
#define	INTE_ENTRYOF	-9

/* Value too long */
#define	INTE_VALOF	-10

/* Odd number of hex digits in localization file */
#define	INTE_ODDHEX	-11

/* Bad file pointer */
#define	INTE_BADFILE	-12

/* Bad INTL_LOCFILE pointer */
#define	INTE_BADLOC	-13

/* Syntax error:  unable to get comment character */
#define	INTE_NOCOM	-14

/* Syntax error in file format section of locfile */
#define	INTE_BADFFMT	-15

/* Bad version number */
#define INTE_BADVER	-16 

/* Unable to build string:  illegal place holder found in
 * text string
 */
#define	INTE_BADPH	-17

/* Unknown datatype token in intl_strbuild() or intl_strblist() */
#define	INTE_BADTYPE	-18

/* Unable to build string:  syntax error found in formats string */
#define	INTE_FMTSYNT	-19

/* Custom format specifier too long */
#define	INTE_SPECOF	-20

/* No custom format specifier found to match specifier in formats
 * string
 */
#define	INTE_NOCUST	-21

/* Null dateinfo structure */
#define	INTE_BADDT	-22

/* Null convert list structure */
#define	INTE_BADCVTL	-23

/* Null format string */
#define	INTE_BADFMTSTR	-24

/* Null custom format conversion routine */
#define	INTE_BADCVTR	-25

/* intl_fmtsize():  Listsize must be greater than zero */
#define	INTE_NEGLSIZE	-26

/* Null buffer */
#define	INTE_INVALBUF	-27

/* Negative buffer length */
#define	INTE_NEGBUFLEN	-28

/* Null charset directory */
#define	INTE_INVALCS	-29

/* Null translation file name */
#define	INTE_INVXLTNM	-30

/* Null translation table */
#define	INTE_INVXLT	-31

/* Null locfile name */
#define	INTE_BADLFNM	-32

/* Null text string */
#define	INTE_INVALTEXT	-33

/* intl_strblist():  Null INTL_ARGVAL structure */
#define	INTE_INVARGL	-34

/* intl_strblist():  Negative number of arguments */
#define	INTE_NEGNARGS	-35

/* intl_xlate():  Null source string */
#define	INTE_INVALSRC	-36

/* Null pointer */
#define	INTE_INVALPTR	-37 

/* intl_strblist():  Only 0, 1, or 2 stars allowed 
 * in format string 
 */
#define INTE_BADNSTARS	-38

/* Too few months in datetime section */
#define INTE_MONTHS	-39

/* Too few short months in datetime section */
#define INTE_SMONTHS	-40

/* Too few days in datetime section */
#define INTE_DAYS	-41

/* Pathname is too long */
#define INTE_PATHOF	-42

/* Line in localization file is too long */
#define INTE_LTLONG	-43

/* Duplicate dateformat value */
#define INTE_DUPDF	-44

/* Syntax error in section heading */
#define INTE_BADSECT	-45


/* SunOS 3.* won't like void *, so use a #define that can
 * be easily #if'd for the correct OS's as we port to
 * them
 */
#define INTL_VOIDPTR	void *

#define INTL_SUCCEED	1

#define INTL_TRUE	1
#define INTL_FALSE	0

/*
** Defines for file io routines.  These file descriptor values can
** be used to initialize an INTL_IOCS structure for use with stdio.
** Set the ne_fd value of the zero'ed INTL_IOCS structure to the
** appropriate value below.
*/
#define INTL_STDIN_FD	0
#define INTL_STDOUT_FD	1
#define INTL_STDERR_FD	2


/* These are used for intl_newxlate */
#define	INTL_XOK		0
#define INTL_XOF		1
#define INTL_XPAT		2


				/* Put constant values for
				 * different versions of
				 * Intl-Library here
				 */

#ifdef IBM370
#define INTL_MAXPATHLEN 44      /* Maximum allowed filename on MVS */
#else
#define INTL_MAXPATHLEN 512	/* The maximum allowed filename path length */
#endif /* IBM370 */

#define INTL_MAXLINE	512	/* The maximum length of a
				 * physical line within
				 * a localization file.  THIS
				 * INCLUDES THE NEWLINE AND
				 * THE NULL-TERMINATOR.  So
				 * the actual number of allowable
				 * "characters" is 510.
				 */

#define INTL_MAXSECT	64	/* The maximum length of a
				 * section name.
				 */

#define INTL_MAXENTRY	64	/* The maximum length of an
				 * entry name.
				 */

#define INTL_MAXVALUE	512	/* The maximum length of a
				 * value string.
				 */

#define INTL_MAXFMTLEN	20

/*
** define INTL_INT, INTL_UINT, INTL_LONG and INLT_ULONG 
*/
#if     defined(__alpha) && defined(__osf__)
typedef int		INTL_INT;
typedef unsigned int	INTL_UINT;
#else
typedef long		INTL_INT;
typedef unsigned long	INTL_UINT;
#endif

typedef	char		INTL_BYTE;
typedef long		INTL_LONG;
typedef	unsigned long	INTL_ULONG;
/*
** NOTE VAX C compiler cannot deal with typedef void so use a define
*/
#if defined(VMS) && defined(VAXC)
#define	INTL_VOID	void
#else
typedef	void		INTL_VOID;
#endif

/*
** Macintosh Think C compiler has special type for 8 byte doubles.
*/
#if defined(THINK_C) 
typedef	short double		INTL_FLOAT;
#else
typedef	double		INTL_FLOAT;
#endif

/* different type tokens for Intl-Library */
#define INTL_SHORT_TYPE		1	/* short */
#define INTL_USHORT_TYPE	2	/* unsigned short */
#define	INTL_INT_TYPE		3	/* int */
#define	INTL_UINT_TYPE		4	/* unsigned int */
#define INTL_LONG_TYPE		5	/* long */
#define INTL_ULONG_TYPE		6	/* unsigned long */
#define INTL_PTR_TYPE		7	/* (void *) */
#define INTL_DOUBLE_TYPE	8	/* double */


#define INTL_MAXMNAME	20	/* Max month-name length */
#define INTL_MAXSMNAME	9	/* Max short-month-name length */
#define INTL_MAXDNAME	30	/* Max day-name length */

#define INTL_MAXSPECLEN	20	/* The maximum length of a 
				 * conversion spec
				 */

/* definitions for the INTL_XLATE structure */
#define NUMCHARS	256	/* The number of single-
				 * byte characters in the
				 * source character set.
				 * For 8-bit character
				 * sets, this number will
				 * always be 256
				 */

#define INTL_MAXPATTERN 8	/* Source and destination
				 * patterns may contain no
				 * more than 8 characters
				 */

#if NETWARE386

#define STRTRUE		"TRUE"

/*
**	NetWare specific environment variable
*/
#define OPTIMIZE_PERFORMANCE	"OPTIMIZE_PERFORMANCE"

#endif /* NETWARE386 */

/*
** The folowing is the typedef for the user installed conversion routine
** passed to intl_fmtinstall() 
*/
typedef int (INTL_PUBLIC * INTL_CONVERT)
		PROTOTYPE((char *, INTL_VOIDPTR, char *));


/* The INTL_LOCFILE structure.
** This structure contains information about a particular 
** localization file, such as the location of a buffer, the
** current character position in the buffer, and whether
** errors or end of file have occurred.  
*/
typedef struct intl_locfile
{
	int	version;	/* This is an integer code which
				 * denotes the version-number of this
				 * localization-file's format.
				 */

	int	linenum;	/* The number of the current line in
				 * the localization file. The first
				 * line is number 1.
				 */

	int	linelen;	/* The number of characters in the
				 * current line.
				 */

	int	linepos;	/* The position of the first unread
				 * character in the current line.
				 * The first character in the line is
				 * at position 0.
				 */

	int	end_of_list;	/* 1 indicates that this entire list
				 * of values has been read.
				 */

	int	end_of_section;	/* 1 indicates that this entire
				 * section has been read.
				 */

	int	eof;		/* 1 indicates that this entire file
				 * has been read.
				 */

	char	comment_char;	/* When this character appears in a
				 * line, rest of the line is treated
				 * as a comment.
				 */

	char	leftsection;	/* When this character appears as the
				 * first character on a line, the
				 * line is treated as a section
				 * heading.
				 */

	char	rightsection;	/* This character marks the end of a
				 * section heading.
				 */

	char	list_sep;	/* This character separates the
				 * members of a list of values.
				 */

	char	escape;		/* This is the escape character, used
				 * to indicate a line-continuation.
				 */

	char	line[INTL_MAXLINE];	/* The contents of the current
					 * physical line in the 
				 	 * localization file.  
					 */

	char	section[INTL_MAXSECT];	/* The name of the current
					 * section. 
					 */

	char	entry[INTL_MAXENTRY];	/* The name of the current
			 		 * entry. 
					 */

	char	value[INTL_MAXVALUE + 1];/* The current value within a
			 		 * list. 
					 */

	void	*file;		/* On Unix, this is just a FILE
			 	 * pointer. On other operating
			 	 * systems, it may be something else.
			 	 * Hiding the actual definition
			 	 * behind this "void *" pointer
			 	 * keeps application programs
			 	 * from having to include <stdio.h>,
			 	 * which may not exist on some
			 	 * systems.
			 	 */
} INTL_LOCFILE;

typedef struct intl_fmt
{
	int		argtype;	/* One of the type tokens,
					 * of the form INTL_*_TYPE,
					 * as defined above.
					 */

	INTL_CONVERT	conversion;	/* A pointer to a
				 	 * user-supplied conversion
				 	 * routine, as described
				 	 * in the intl_fmtinstall()
				 	 * man page.
				  	 */

	char		fmt[INTL_MAXFMTLEN + 1]; /* A user-supplied custom
				 		 * format-specifier.
				 		 */
} INTL_FMT;

typedef struct intl_cvtlist
{
	int	listcount;	/* The number of custom
			 	 * format-specifiers which are
			 	 * currently stored in this list.
			 	 */

	INTL_FMT	fmtlist[1];	/* An array of format/conversion
			 		 * pairs. The actual space allocated
			 		 * for this array will usually be
			 		 * greater than that required for
			 		 * 1 member.
			 		 */
} INTL_CVTLIST;


/* the dateinfo structure */
typedef struct intl_dateinfo {
	char	months[12][INTL_MAXMNAME+1];	/* null-terminated
						 * month names 
						 */

	char	shortmonths[12][INTL_MAXSMNAME+1];  /* null-terminated
						     * month abbrevs.
						     */

	char	days[7][INTL_MAXDNAME+1];	/* null-terminated
						 * day names
						 */

	int	firstday;	/* 1 = Monday, 7 = Sunday */

	char	dateorder[4];	/* m, d, and y, NULL-terminated */

	int	is12hour;	/* 1 if 12-hour, 0 if 24-hour time */

} INTL_DATEINFO;

/* the INTL_ARGVAL structure -- this keeps track of a single
** format conversion specifier string and its various attributes
** such as the type of the argument it is specifying, and
** whether this is a custom or sprintf-type string
*/
typedef struct intl_argval
{
	int	numstars;	/* The number of asterisks in this
				 * conversion-spec.  Legal values
				 * are 0, 1, or 2.
				 */

	int	stars[2];	/* The integers which provide values
				 * for the conversion spec's asterisks
				 */

	int	value_type;	/* One of the Intl-Library type tokens,
				 * of the form, INTL_*_TYPE, as specified 
				 * above
				 */

	char	cvtspec[INTL_MAXSPECLEN + 1];	/* A complete 
				 * conversion-specification, as
				 * described on page 243 of K&R,
				 * 2nd edition.
				 */

	INTL_FMT *custom;	/* The custom format for this arg,
				 * if appropriate.
				 */

	union
	{
		unsigned short	ushort_val;
		short		short_val;
		unsigned int	uint_val;
		int		int_val;
		INTL_ULONG 	ulong_val;
		INTL_LONG	long_val;
		void		*ptr_val;
		double		doubleval;
	} value;

} INTL_ARGVAL;

/* The INTL_MAP structure */
typedef struct intl_map
{
	int	src_left;	/* The number of characters
				 * remaining in this source-
				 * pattern.  If this source-
				 * pattern contains only one
				 * byte, this number will
				 * be zero.  This is the number
				 * of characters in the 
				 * "src_pattern" array.
				 */
	
	int	dest_chars;	/* The number of characters
				 * in this destination-patter.
				 * This is the number of cha-
				 * racters in the "dest_pattern"
				 * array.
				 */
	
	unsigned char src_pattern[INTL_MAXPATTERN-1];
				/* The remaining characters in
				 * this source-pattern.  The 
				 * number of characters in this
				 * array is given by "src_left."
				 */

	unsigned char dest_pattern[INTL_MAXPATTERN];
				/* The actual characters of the
				 * destination-pattern, in the
				 * destination character set.
				 * The number of characters in
			 	 * this pattern is given by
				 * "dest_chars."
				 */
} INTL_MAP;


/* the INTL_XLIST structure */
typedef struct intl_xlist
{
	int	listsize;	/* The number of possible 
				 * translations for source
				 * strings which begin with this
				 * member of the source character
				 * set.  This is the number of
				 * elements in the array pointed
				 * to by "list". 
				 */

	INTL_MAP	*list;	/* A pointer to an array of
				 * source-to-destination mappings.
				 * The number of elements in this
				 * array is given by "listsize."
				 * This array of INTL_MAP structures
				 * is sorted by descending order of
				 * the number of characters in each
				 * source pattern, and alphabetically
				 * by source pattern (using just the
				 * binary valuese of the characters),
				 * for source patterns with the same
				 * number of characters
				 */
} INTL_XLIST;

/* the INTL_XLATE structure */
typedef struct intl_xlate
{
	INTL_XLIST	xlist[NUMCHARS];
} INTL_XLATE;

/*
** INTL_IOCS
**
**      Intl-Library implementation of the stdio library
**
**      ne_cnt          Byte count still in read buffer
**      *ne_ptr         Pointer to the current position in read buffer
**      *ne_base        Pointer to start of read buffer
**      ne_bsize        Size of the read buffer
**      ne_flag         Open flags
**      ne_fd           File descriptor returned from open()
*/
typedef struct  intl_iocs
{
        INTL_INT         ne_cnt;
        INTL_BYTE        *ne_ptr;
        INTL_BYTE        *ne_base;
        INTL_INT         ne_bsize;
        INTL_INT         ne_flag;
        INTL_INT         ne_fd;
}INTL_IOCS;

/******************************************************************************
**
** Defines for the IOCS open flags these are mapped to platform specific
** defines in intlport.h
**
******************************************************************************/
 
#define	INTL_IO_READ		1
#define	INTL_IO_READ_B		2
#define	INTL_IO_WRITE		3
#define	INTL_IO_WRITE_B		4
#define	INTL_IO_APPEND		5
#define	INTL_IO_APPEND_B	6
#define	INTL_IO_UPDATE		7
#define	INTL_IO_UPDATE_B	8
#define	INTL_IO_CR_TR		9
#define	INTL_IO_CR_TR_B		10
#define	INTL_IO_AP_CR		11
#define	INTL_IO_AP_CR_B		12

/*
** declare prototypes for user accessable functions in intl-lib
*/

INTL_START_EXTERN_C

#if NETWARE386

/*
** Global flag to indicate if certain functions need to 
** release system resources more often 
*/
extern int nw386_optimize_perf; 

#endif /* NETWARE386 */

/* intxsize.c */
extern int INTL_PUBLIC intl_xlatesize PROTOTYPE((
	char *srv_charset,
	char *xlt_name
	));
/* intxlate.c */
extern int INTL_PUBLIC intl_xlate PROTOTYPE((
	unsigned char *src,
	int srclen,
	unsigned char *dest,
	int destlen,
	INTL_XLATE *xlt,
	int *srcbytes_used,
	int srcend,
	int *status
	));
/* intxcomp.c */
/*
** These routines file contain external declarations for a set of Intl-Lib
** routines which the standalone 'xcomp' uses.  These functions provide
** a means for 'xcomp' to manipulate the internals of the INTL_XLIST
** and the INTL_MAP structures.
*/
extern int INTL_PUBLIC intl_getversion PROTOTYPE((
	INTL_LOCFILE *locfile
	));
extern INTL_XLIST * INTL_PUBLIC intl_getxlist PROTOTYPE((
	INTL_XLATE *xlate,
	int mapno
	));
extern int INTL_PUBLIC intl_getlistsize PROTOTYPE((
	INTL_XLIST *xlist
	));
extern void INTL_PUBLIC intl_inclistsize PROTOTYPE((
	INTL_XLIST *xlist
	));
extern int INTL_PUBLIC intl_map_cpsrc PROTOTYPE((
	INTL_MAP *curmap,
	char *value
	));
extern int INTL_PUBLIC intl_map_cpdest_mapping PROTOTYPE((
	INTL_MAP *curmap,
	char *value
	));
extern int INTL_PUBLIC intl_map_cpdest_range PROTOTYPE((
	INTL_MAP *curmap,
	char *value
	));
extern int INTL_PUBLIC intl_mapcompare PROTOTYPE((
	INTL_MAP *map1,
	INTL_MAP *map2
	));
/* intstrb.c */
/*
** NOTE: INTL_IGNORE_VARARGS_PROTOTYPE is just a hack until I figure out a
**	 portable way of prototyping varargs
*/
#ifndef INTL_IGNORE_VARARGS_PROTOTYPE
extern int INTL_VARARGS intl_strbuild PROTOTYPE((
	INTL_CVTLIST *cvtlist,
	char *charbuf,
	int bufsize,
	char *text,
	...
	));
extern int INTL_VARARGS intl_cstrbuild PROTOTYPE((
	INTL_CVTLIST *cvtlist,
	char *charbuf,
	int bufsize,
	char *text,
	int textlen,
	char *format,
	int formatlen,
	INTL_VOIDPTR ap
	));

extern int INTL_VARARGS intl_vstrbuild PROTOTYPE((
	INTL_CVTLIST *cvtlist,
	char *charbuf,
	int bufsize,
	char *text,
	char *format,
	...
	));
#endif
/* intslist.c */
extern int INTL_PUBLIC intl_strblist PROTOTYPE((
	char *charbuf,
	int bufsize,
	char *text,
	INTL_ARGVAL arglist[],
	int numargs
	));
/* intprx.c */
extern void INTL_PUBLIC intl__print_xlate PROTOTYPE((
	INTL_XLATE *xlt
	));
/* intopen.c */
extern int INTL_PUBLIC intl_open PROTOTYPE((
	char *filename,
	INTL_LOCFILE *locfile
	));
extern int INTL_PUBLIC intl_fopen PROTOTYPE((
	INTL_VOIDPTR file,
	INTL_LOCFILE *locfile
	));
/* intnval.c */
extern char * INTL_PUBLIC intl_nextvalue PROTOTYPE((
	INTL_LOCFILE *locfile,
	int *end_of_list
	));
/* intnsect.c */
extern char * INTL_PUBLIC intl_nextsection PROTOTYPE((
	INTL_LOCFILE *locfile,
	int *eof
	));
/* intnline.c */
extern char * INTL_PUBLIC intl_nextline PROTOTYPE((
	INTL_LOCFILE *locfile,
	int *end_of_section
	));
/* intnent.c */
extern char * INTL_PUBLIC intl_nextentry PROTOTYPE((
	INTL_LOCFILE *locfile,
	int *end_of_section
	));
/* intmem.c */
extern int INTL_PUBLIC intl_strcmp PROTOTYPE((
	register unsigned char *p1,
	register unsigned char *p2
	));
extern int INTL_PUBLIC intl_memcmp PROTOTYPE((
	register unsigned char *p1,
	register unsigned char *p2,
	register INTL_INT len
	));
extern int INTL_PUBLIC intl_memhilo PROTOTYPE((
	register unsigned char *p1,
	register INTL_INT len1,
	register unsigned char *p2,
	register INTL_INT len2
	));
/* intloadx.c */
extern int INTL_PUBLIC intl_load_xlate PROTOTYPE((
	void *buf,
	char *srv_charset,
	char *xlt_name,
	INTL_XLATE **xlt_tosrv,
	INTL_XLATE **xlt_todisp
	));
/* intlnum.c */
extern int INTL_PUBLIC intl_linenum PROTOTYPE((
	INTL_LOCFILE *locfile
	));
/* intlgenv.c */
extern int INTL_PUBLIC intlgetenv PROTOTYPE((
	char *buf,
	int buflen,
	char *envvar
	));
/* intinit.c */
extern int INTL_PUBLIC intl_init PROTOTYPE((void));
/* inthome.c */
extern int INTL_PUBLIC intl_home PROTOTYPE((
	char *buf,
	int buflen
	));
extern int INTL_PUBLIC intl_sethome PROTOTYPE((
	char *path
	));
/* intfsize.c */
extern int INTL_PUBLIC intl_fmtsize PROTOTYPE((
	int listsize
	));
/* intfinst.c */
extern int INTL_PUBLIC intl_fmtinstall PROTOTYPE((
	INTL_CVTLIST *cvtlist,
	char *fmt,
	int argtype,
	INTL_CONVERT conversion
	));
/* intexit.c */
extern int INTL_PUBLIC intl_exit PROTOTYPE((void));
/* intestr.c */
extern char * INTL_PUBLIC intl_errstr PROTOTYPE((
	int interrno
	));
/* intdtime.c */
extern int INTL_PUBLIC intl_datetime PROTOTYPE((
	INTL_LOCFILE *locfile,
	INTL_DATEINFO *dateinfo
	));
/* intclose.c */
extern int INTL_PUBLIC intl_close PROTOTYPE((
	INTL_LOCFILE *locfile
	));
/* intiocs.c */
extern INTL_IOCS * INTL_PUBLIC intl_iocsfopen PROTOTYPE((
	INTL_BYTE	*intl_name,
	INTL_INT	intl_type
	));
extern INTL_INT INTL_PUBLIC intl_iocsfread PROTOTYPE((
	INTL_BYTE	*intl_ptr,
	INTL_INT	intl_size,
	INTL_INT	intl_cnt,
	INTL_IOCS	*intl_iocs
	));
extern INTL_BYTE * INTL_PUBLIC intl_iocsfgets PROTOTYPE((
	INTL_BYTE	*intl_ptr,
	INTL_INT	intl_size,
	INTL_IOCS	*intl_iocs
	));
extern INTL_INT INTL_PUBLIC intl_iocsfwrite PROTOTYPE((
	INTL_BYTE	*intl_ptr,
	INTL_INT	intl_size,
	INTL_INT	intl_cnt,
	INTL_IOCS	*intl_iocs
	));
extern INTL_LONG INTL_PUBLIC intl_iocsfseek PROTOTYPE((
	INTL_IOCS	*intl_iocs,
	INTL_LONG	intl_offset,
	INTL_INT	intl_flag
	));
extern INTL_INT INTL_PUBLIC intl_iocsfclose PROTOTYPE((
	INTL_IOCS	*intl_iocs
	));

INTL_END_EXTERN_C

#endif /* __INTL_H__ */
