



/* Sccsid %Z% %M% %I% %G% */

/*
**      Sybase INTL library Version 5.0
**      Confidential Property of Sybase, Inc.
**      (c) Copyright Sybase, Inc. 1989, 1992
**      All rights reserved
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
** INTL_NLS.H
**
** <intl_nls.h> was created to hold sort order and character set specific
** typedefs, macros, and constants.
**
** Dependancies:
**	<server.h> or <sybfront.h>. ?
**
** History:
**	14 Aug 89 (gt & mgm)	- written
**	02 Jan 91 (gt)		- added new typedefs, defines, and macros for
**				  class 2 character sets.
**	1/15/93 (sara)		- changed name from syb_nls.h to intl_nls.h
**	8/18/94 tchilder 59414, ensured all lines >= 80 chars in length for MVS
*/

#ifndef __intl_nls__
#define __intl_nls__


/*
** set any default defines if not supplied from previous includes
*/
#ifndef BYTE
#define BYTE    CS_BYTE
#endif

#ifndef MAXNAME
#define MAXNAME 30
#endif

#ifndef PROTOTYPE
#define PROTOTYPE(s)	()
#endif


/*
**  LSC - Logical Sort Character
**
**  This structure defines what each element in the sort order array looks like.
**  An array of 256 of these will define the majority of the server's default
**  sort order.  Element `n' in that array represents code point `n' in the
**  default character set.
**
**  Class 1 sort order notes:
**  -------------------------
**  (Note: "pst" stands for a Primary/Secondary/Tertiary triplet.)
**  If the character whose code point is `n' is merely sorted as a single,
**  Logical Sort Character then that Logical Sort Character will be specified by
**  the three BYTEs .pst.p, .pst.s, and .pst.t.  If, however, it participates in
**  any special cases(*) then .pst.t will be set to zero, and .pst.smelist will
**  "point" to a sort-map-element list, which will be used to find the
**  appropriate Logical Sort Character(s) to use.
**
**  (*) That is, it is either a ligature (one character sorts as two Logical
**	Sort Characters), or it is the first character of at least one sort
**      double (two characters sort as a single Logical Sort Character), etc.
**
*/

typedef union lsc
{
    CS_UINT		lsclong;    /* The whole sha-bang as a single unit */
    unsigned short	ps;	    /* ONLY VALID FOR CLASS 1 SORT-ORDERS:
				    ** ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				    **     Just Prim/Sec as a single unit.
				    */

    /* The following union member is used for class 1 sort orders */
    /* ---------------------------------------------------------- */
    struct
    {
	BYTE	p;			/* Primary */
	BYTE	s;			/* Secondary */
	BYTE	t;			/* Tertiary */
	BYTE	smelist;		/* If .t is zero, this will "point" to
					** a list of SMELs in the SMEL array.
					** (Actually, this member is only used
					** in the main LSC array.  In a SMEL,
					** the next SMEL "pointer" is stored
					** elsewhere.)
					**
					** If .t is non-zero, this contains the
					** codepoint of the first character with
					** a larger primary value (used by the 
					** optimizer).
					*/
    }			pst;
     
    /* The following union member is used for class 2 sort orders */
    /* ---------------------------------------------------------- */
    struct
    {
	BYTE	p1;			/* High-order byte of Primary */
	BYTE 	p2;			/* Next highest-order byte of Primary */
	BYTE	s;			/* Secondary */
	BYTE	smelist;		/* If .s is zero, this will "point" to 
					** a list of SMELs in the SMEL array
					** for the current alphabet. (Actually,
					** this member is only used in the main
					** LSC array for each alphabet.  In a
					** SMEL, the next SMEL :pointer" is
					** stored elsewhere. )
					*/
    }  			p1p2s;

} LSC;


/*
**  -------------------------------------------------------------------------
**  The following constant and structure definitions describe the format of a
**  class `1' and class `2'  sort orders.
**  -------------------------------------------------------------------------
*/


/*
**  "Type" specific Sort-Map-Element structures are defined here.
**  -------------------------------------------------------------
*/


/* Typical:  one char --> one logical sort char */
typedef struct sm_0type
{
    LSC		lsc1;		/* Logical sort char for typical
				** one-to-one mapping
				*/
} SM_0TYPE;


/* Sort Double:  two chars --> one logical sort char */
typedef struct sm_1type
{
    BYTE	xtraw;		/* 2nd char of a sort double */
    BYTE	pad[3];		/* < NEVER USED > */
    LSC		lsc1;		/* Logical sort char this sort double
				** maps into.
				*/
} SM_1TYPE;

/*
** Ignored:  one char --> zero logical sort char ... could also represent an
**	     ignored row, plane, or cube, depending on how many extra raw chars
**	     are listed in the noextra field of the SMEL.
*/
typedef struct sm_2type
{
    int		dummy;		/* <NEVER USED> */
} SM_2TYPE;


/* Ligature:  one char --> two logical sort chars */
typedef struct sm_3type
{
    LSC		lsc1;		/* 1st logical sort char this ligature
				** maps into.
				*/
    LSC		lsc2;		/* 2nd logical sort char this ligature
				** maps into.
				*/
} SM_3TYPE;


/*
** Row:  256 (2^8) double-byte characters sharing the same 1st byte.  They sort
**	 in binary order with respect to the other characters in their half-row.
**	 The two half rows may sort in different places within the sort sequence
**	 or they may sort together.
**			(*** NOT USED BY CLASS 1 SORT ORDERS ***)
*/
typedef struct sm_4type
{
    LSC		lsc_low;		/* Holds P1/P2 for the left (or lower) half of
	  				** row.  If the 2nd byte of the character is in
					** the lower half of the row (i.e., 0x00-0x7F),
					** then this P1 and P2 are used. 
					*/
    LSC		lsc_high;		/* Holds P1/P2 for the right (or upper) half of
					** row.  If the 2nd byte of the character is in
					** the upper half of the row (i.e., 0x80-0xFF),
					** then this P1 and P2 are used. 
					*/
	
			/*
			** In either case, P3 is set to the value of the 2nd byte of
			** the character, and S is never needed but should be set to 1.
			*/
} SM_4TYPE;


/*
** Plane:  65,536 (2^16) triple-byte characters sharing the same 1st byte.
**	   They sort in binary order with respect to each other.
**			(*** NOT USED BY CLASS 1 SORT ORDERS ***)
*/
typedef struct sm_5type
{
    LSC		lsc1;		/* Holds P1/P2 for the plane.  P3 and P4 are set
				** to the values of the 2nd and 3rd bytes of the
				** character, respectively.  S is never needed
				** but should be set to 1.
				*/
} SM_5TYPE;


/*
** Cube:  16,777,216 (2^24) quad-byte characters sharing the same 1st byte.
**	   They sort in binary order with respect to each other.
**			(*** NOT USED BY CLASS 1 SORT ORDERS ***)
*/
typedef struct sm_6type
{
    LSC		lsc1;		/* Holds P1 for the plane.  P2, P3, and P4 are
				** set to the values of the 2nd, 3rd, and 4th
				** bytes of the character, respectively.  S is
				** never needed but should be set to 1.
				*/
} SM_6TYPE;


/*
** Alternate Alphabet:  Points to an alternate alphabet of double-byte
**                      characters, all sharing the same 1st byte.
**			(*** NOT USED BY CLASS 1 SORT ORDERS ***)
*/
typedef struct sm_7type
{
    CS_UINT   offset;				/* Points to top of the SO_ALPHABET structure
				** for the alternate alphabet.  ".offset" is
				** the number of bytes from the top of the
				** SO_2CLASS structure.
				*/
} SM_7TYPE;


/*
**  SMEL - "Sort-Map-Element"
**
**  Each "odd byte" in an alphabet will have a list of sort-map-elements
**  hanging off the LSC structure in the main sort table for that alphabet.
**  An "odd byte" is defined as one of the following:
**
**	(1) Any single-byte character from the default alphabet that:
**		(a) sorts as a ligature.
**		(b) participates as the first character of a sort double.
**	(2) Any byte from the default alphabet that represents:
**		(a) an alternate alphabet of double-byte characters.
**		(b) a binary row of double-byte characters.
**		(c) a binary plane of triple-byte characters.
**		(d) a binary cube of quad-byte characters.
**		(e) an ignored character, row, plane, or cube.
**	(3) Any 2nd byte of a double-byte character from some alternate
**	    alphabet that:
**		(a) sorts as a ligature.
**		(b) participates as the first character of a sort double.
**		(c) is an ignored character.
**
**  Each sort-map-element can be one of several different types, depending on
**  whether it represents a ligature, a sort double, etc.  Each list will be
**  ordered in descending order of the number of extra raw characters (largest
**  .noxtraw will come first, smallest .noxtraw will come last).
**
**  A SMEL belongs to a particular alphabet.  All SMELs for an alphabet will
**  be set up as an array of SMELs which will follow immediately after that
**  alphabet's SO_ALPHABET structure.  The .next_smel "pointer" will always
**  refer to a SMEL belonging to the same alphabet, and will do so by holding
**  the array index of the SMEL.
*/

typedef struct smel
{
    BYTE	next_smel;	/* Array index of the next
				** sort-map-element in list.  If
				** end of list, this will be equal
				** to END_SMELIST.
				*/
    BYTE	type_smel;	/* Type of sort-map-element this one is.
				** This determines what member of the
				** below union to use.
				*/
#define	    SM_ONE_TO_ONE		0	/* typical case */
#define	    SM_TWO_TO_ONE		1	/* sort double */
#define	    SM_ONE_TO_ZERO		2	/* ignored */
#define	    SM_ONE_TO_TWO		3	/* ligature */
#define	    SM_ROW			4	/* row */
#define	    SM_PLANE			5	/* plane */
#define	    SM_CUBE			6	/* cube */
#define	    SM_ALT_ALPHA		7	/* alternate alphabet */

    BYTE	noxtraw;	/* Number of extra raw bytes
				** to match for this sort-map-element.
				** This is used to sort the map elements
				** in a particular list so that the
				** longest ones come first.
				*/
    BYTE	pad;		/* < NEVER USED >
				*/
    union
    {
	SM_0TYPE    type0_smel;		    /* 1 --> 1 */
	SM_1TYPE    type1_smel;		    /* 2 --> 1 */
	SM_2TYPE    type2_smel;		    /* 1 --> 0 */
	SM_3TYPE    type3_smel;		    /* 1 --> 2 */
	SM_4TYPE    type4_smel;		    /* row */
	SM_5TYPE    type5_smel;		    /* plane */
	SM_6TYPE    type6_smel;		    /* cube */
	SM_7TYPE    type7_smel;		    /* alternate alphabet */

    }			smel_types;
} SMEL;


/*
**  SO_1CLASS - Class `1' Sort Order
**
**  This structure defines what the IMAGE field (and the in-memory
**  representation) will look like for a class `1' sort order.  It will contain
**  two bytes of status information about the sort order, followed by two bytes
**  that represent the number of SMEL structures actually needed for this sort
**  order, followed by an array of 256 LSCs (one for each code point), followed
**  by the above mentioned number of SMELs.
**
**  We also set the maximum number of SMELs for any class `1' sort order at 64
**  (this is the MAX_SMELS_PER_SO1 constant, defined below).  This should be
**  *MORE* than sufficient.  This also accomplishes the following two things:
**
**	 o  First, it allows a class `1' sort order to use a single BYTE as a
**	    SMEL "pointer".  Since the SMELs are all stored in an array, using a
**	    BYTE to represent the index into this array ([0]-[63]) gives each
**	    SMEL a unique address, while at the same time making the entire
**	    structure relocatable.  We also reserve array index [255] to mean
**	    "end of list", or, "no SMEL here" (see the END_SMELIST constant
**	    defined below).
**
**	 o  Second, it guarantees that an IMAGE field representation of a class
**	    `1' sort order will completely fit on a single IMAGE data page.
*/

#define MAX_SMELS_PER_SO1	 64	/* Max # SMELs per class 1 sort order */
#define END_SMELIST		255	/* Marks the end of a SMEL list.      */

typedef struct so_1class
{
    BYTE		stat1;		/* 1st byte of status flags */
    BYTE		stat2;		/* 2nd byte of status flags */
    BYTE		last_char;	/* Codepoint of the very last character
    					** in the collating sequence
					*/
    BYTE		nsmels;		/* # SMELs */
    LSC			lscs[256];	/* The main sort array. */
    SMEL		smels[MAX_SMELS_PER_SO1];
} SO_1CLASS;


/*
**  STRCMPFUNCS
**
**  This typedef represents one of the cells in the globally visible
**  Str_Cmp_Funcs[][] array, which is used during initialization of the
**  character string compare function pointers in RESOURCE.
*/


typedef struct strcmpfuncs
{
    int		(*strncmp)PROTOTYPE((SO_1CLASS *, char *, char *, int));
    int		(*str_hilo)PROTOTYPE((SO_1CLASS *, char *, char *, int));
    int		(*sqlstr_hilo)PROTOTYPE((SO_1CLASS *, char *, char *, int));
    int		(*str_tord)PROTOTYPE((SO_1CLASS *, char *, char *, int));
} STRCMPFUNCS;



/* Architecture flag definitions */
#define NORM_BYTE_ORDER		0x01   /* normal shorts/longs */

/* SO_2CLASS - Class 2 sort order structure */
/* $$$ This structure is not current used in connectivity. 
** It may be used in the future extension.
*/

typedef struct so_2class
{
    BYTE		stat1;		/* 1st byte of status flags */
    BYTE		stat2;		/* 2nd byte of status flags */
    BYTE		class;		/* What class of sort order have we?
					** This will always be 2 for so_2class.
					*/
    BYTE		arch_flags;	/* architecture flags describing any
					** architecture dependent aspects of
					** the sort order.  (These flags are
					** defined above.)
					*/

    BYTE		nalphas;	/* # of alphabets used by sort order.
					** This includes the "default alphabet",
					** thus it will always be at least 1.
					*/
    BYTE		pad[3];		/* <reserved space> */
    CS_UINT		totsmels;	/* The total # SMELs in all alphabets.
					** +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
					** The byte order will be consistent
					** with the arch_flags.  If
					** NORM_BYTE_ORDER is set, then this
					** feild has "normal" byte ordering with
					** the high order byte first.  By con-
					** vention, this will always be the case
					** when the sort order is stored in the
					** database.
					** +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
					*/
    CS_UINT		so_size;	/* The total size of this sort order in
					** bytes, including this SO_2CLASS
					** structure and all of the supporting
					** SO_ALPHABET structures with their
					** associated SMEL[] arrays.
					** +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
					** The byte order will be consistent
					** with the arch_flags, similar to
					** the totsmels field above.
					** +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
					*/
} SO_2CLASS;


/* $$$ This structure is not current used in connectivity. 
** It may be used in the future extension.
*/

typedef union so_class_union
{
    SO_1CLASS			so1;	/* used for class 1 sort orders */
    SO_2CLASS			so2;	/* used for class 2 sort orders */
} SO_CLASS_UNION;


/*
**  SO_ALPHABET - Definition of an "alphabet" for Class `2' Sort Orders
**
*/

#define MAX_SMELS_PER_ALPHA	255	/* Max # SMELs per alphabet (class 2)*/


/* $$$ This structure is not current used in connectivity. 
** It may be used in the future extension.
*/
typedef struct so_alphabet
{
    BYTE		nsmels;		/* # SMELs used by this alphabet.
					** There will be a SMEL array, this many
					** in number, immediately following this
					** structure.
					*/
    BYTE		pad[3];		/* <reserved space> */
    LSC			lscs[256];	/* The logical sort character array
					** for this alphabet.
					*/
} SO_ALPHABET;


/*
**  Status bits for the stat1 field ("SOS1_" series) and status bits for the
**  stat2 field ("SOS2_" series ... currently none defined).  Also, the "SO_"
**  series of #defines are to be used by the server to test these bits once
**  placed into the Resource->rnls slot.
**
**  Note: Resource->rnls gets set with these bits for the default
**	  sort order, as follows:
**
**    Resource->rnls = ( (unsigned int) stat1 << 8 )  |  (unsigned int) stat2;
*/

#define SOS1_PUNIQ	0x01	/* Primary values alone, uniquely define the
				** sort order (i.e., Secondaries and Tertiaries
				** are never needed, even if they are present).
				*/
#define SOS1_PSUNIQ	0x02	/* Combo Primary/Secondary values uniquely
				** define the sort order (i.e., Tertiaries
				** are never needed, even if they are present).
				*/
#define SOS1_PSTUNIQ	0x04	/* Combo Primary/Secondary/Tertiary values
				** uniquely define the sort order (i.e., they
				** are all present, and required.  Example:
				** case insensitive order with preference.)
				*/
#define SOS1_NOTUNIQ	0x08	/* If this bit is set, then two individual
				** characters can be the same.  This is
				** useful for determining *fast path*
				** approaches for string equivalence testing on
				** national characters.  
				** e.g 'A' can be equivalent to 'a' if
				** 	SOS1_NOTUNIQ is set
				*/
#define SOS1_SPECASE	0x10	/* Sort order has some special cases
				** (i.e., sort doubles or ligatures)
				*/
#define SOS1_LIGATURE	0x20	/* Sort order has some ligatures
				*/
#define SOS1_NOSTRLEN	0x40	/* If this bit is set, the strings of different
				** lengths may still be equal.  That is, if this
				** bit is *NOT* set, then two strings with
				** different lengths will *NEVER* be equal.
				*/


#define	SYBCHARSET_SIZE	256	/* Size of the CHAR_MAP, etc. arrays */

#ifndef MAX_CHAR_SIZE
#define	MAX_CHAR_SIZE	4	/* Max # bytes for a character */
#endif /* MAX_CHAR_SIZE */

/*
**  CHAR_MAP - Character Map
**
**  An array of 256 CHAR_MAPs (called a CS_TYPE_MAP -- see below) will be used
**  for each alphabet in the character set that requires c-type information,
**  upper- and lower-case mappings, and lexical type information.  The
**  collection of the CS_TYPE_MAPs will be a contiguous array, hanging off from
**  the CHAR_ATTRIB structure.  For strictly 8-bit character sets, there will
**  only be a single CS_TYPE_MAP in this array.
**
**  To find the correct CHAR_MAP structure to use for a character, we always
**  begin with the 1st CS_TYPE_MAP (CS_TYPE_MAP[0]), and use the first byte of
**  the character to index into its array of CHAR_MAPs.  If the P_ALPHABET bit
**  is *NOT* set in the CHAR_MAP.char_upper field, then this is the correct
**  CHAR_MAP structure to use to find the required information, regardless of
**  the number of bytes in the character.  If the P_ALPHABET bit *IS* set in the
**  CHAR_MAP.char_type field, this signals a secondary alphabet of double-byte
**  characters.  In this case, the index of the secondary CS_TYPE_MAP is held in
**  the CHAR_MAP.char_upper field.  Once that CS_TYPE_MAP is found, the CHAR_MAP
**  to use is indexed by the second byte of the character in question.
**
**  There is a default CS_TYPE_MAP (called Dflt_Type_Map) for use by the
**  server's *DEFAULT* default character set ("ascii_8").  It is READ-ONLY,
**  and is defined in parslex.c.  It exists so that the server can run even
**  without a Syscharsets table, which is where the character set definitions
**  are normally kept.
**
** 	Note: EVERY char_upper and char_lower MUST be filled in (except for the
**	      case where the P_ALPHABET bit is set in char_type).  If there
**	      is no conversion to take place, then it should be filled in
**	      with the character itself.
**	      e.g. - Char_Map['A'].char_upper = 'A';
**		     Char_Map['A'].char_lower = 'a';
**		     Char_Map['A'].char_lex = P_ALPHA;
**		     Char_Map['A'].char_type = P_UPPER | P_HEX;
**
**		     Char_Map['4'].char_upper = '4';
**		     Char_Map['4'].char_lower = '4';
**		     Char_Map['4'].char_lex = P_NUMB;
**		     Char_Map['4'].char_type = P_DIGIT | P_HEX
**
**		     Char_Map['^'].char_upper = '^';
**		     Char_Map['^'].char_lower = '^';
**		     Char_Map['^'].char_lex = P_OPER;
**		     Char_Map['^'].char_type = P_PUNCT;
*/

typedef struct char_map
{
	BYTE		char_upper;	/* Upper-case version of character */
	BYTE		char_lower;	/* Lower-case version of character */
	BYTE		char_lex;	/* Lexical information for parser */
	BYTE		char_type;	/* Data for ctype functions */
} CHAR_MAP;


/*
** The following bit masks are used by the parser (yylex()) and are valid
** values for char_lex.  Each char_lex can have only ONE value.
*/

#define P_ALPHA	0x01	/* Valid XACT SQL alphabetic characters 
				**  (alpha,#,@,_) 
				*/
#define P_NUMB		0x02	/* Numeric character */
#define P_SPEC 	0x04	/* Special character - can appear in 
				** identifers, except as first 
				** character -- currently none.
				*/
#define P_IGSPACE	0x08	/* Characters ignored in parsing, 
				** e.g. control characters and white space
				**     including undefined characters
				*/
#define P_STRNG 	0x10	/* String delimiters: ' or " */
#define P_OPER 	0x20	/* Operator - valid XACT SQL operators */
#define P_MONEE	0x40	/* Money Character 
				** - normally '$', there is no alternate 
				*/
#define P_IDCHAR	(P_ALPHA | P_SPEC | P_NUMB | P_MONEE)
				/* Valid XACT SQL identifier characters */

#define P_EOM		0x80	/* End of message */


/*
** The following bit-masks are for the ctype functions for determining
** the type of a character.  There may be more than one bit set for each 
** value.  They are the only valid settings for char_type.
*/

#define P_UPPER	0x01	/* upper case alpha letter */
#define P_LOWER	0x02	/* lower case alpha letter */
#define P_DIGIT	0x04	/* digit[0-9] */
#define P_SPACE	0x08	/* space, tab, carriage return, newline,
				** vertical tab or form feed
				*/
#define P_HEX		0x10	/* hexadecimal digit */
#define P_PUNCT	0x20	/* punctuation characters */
#define P_ALPHABET	0x80	/* First byte of a two-byte character.
				** If this bit is set, then the character
				** properties are defined in the CS_TYPE_MAP
				** indexed by the contents of char_upper.
				*/


/*
**  CHAR_ATTRIB and support structures CS_NORM_MAP, CS_TYPE_MAP, CS_SOUNDEX
**  -----------------------------------------------------------------------
*/

typedef struct cs_norm_map
{
	BYTE		norm[SYBCHARSET_SIZE];
} CS_NORM_MAP;

typedef struct cs_type_map
{
	CHAR_MAP	chmap[SYBCHARSET_SIZE];	/* Each type map holds
						** 256 character maps.
						*/
} CS_TYPE_MAP;

typedef struct cs_soundex
{
	BYTE		sound[SYBCHARSET_SIZE];
} CS_SOUNDEX;

typedef struct char_attrib
{
	short		cs_status;		/* Status flags */
	BYTE		cs_class;		/* Type of character set */
	BYTE		cs_id;			/* Character set ID */
	short		cs_namelen;		/* Length of the name */
	BYTE		cs_name[MAXNAME];	/* Name of character set */
	BYTE		cs_maxcharlen;		/* Max char length */
	BYTE		cs_ncharsize;		/* Average nchar len */
	BYTE		cs_nnorm;		/* No. of norm map */
	BYTE		cs_ntype;		/* No. of type map */
	BYTE		cs_nsoundex;		/* No. of soundex map */
	BYTE		spare[3];		/* Word boundry padding */
	BYTE		*cs_width_map;		/* Width of chars */
	CS_NORM_MAP	*cs_norm_map;		/* Normalization maps */
	CS_TYPE_MAP	*cs_type_map;		/* Type maps */
	CS_SOUNDEX	*cs_soundex;		/* Soundex maps */
} CHAR_ATTRIB;



/*
**  CHARACTER WIDTH MACROS:
**
**	CHAR_WIDTH(cp, width_map) - Evaluates to this character's data width.
**	INC_CHAR(cp, width_map)   - Moves character pointer to next character.
**	DISP_WIDTH(cp, width_map) - Evaluates to this character's display width.
**
**  These macros are the interface to the character width map for a
**  character set, dealing with both data widths and display widths.
**
**  In these definitions, the following parameters are used:
**
**	BYTE *cp        - Points to the character in question.
**                        (A "char *" could also be passed in here.)
**	BYTE *width_map - Points to the 1st element in the character
**			  set's width map (in the server this is usually
**			  Resource->rchar_attrib).  If this is NULL,
**			  then all characters will have both a
**			  data width and a display width of 1.
**
**  History:
**	Jan 1991 - (gt) Written.
*/

#define CHAR_WIDTH(cp, width_map)				\
    (								\
	(width_map)						\
	     ? (width_map)[*(BYTE *)(cp)] & 0x0F		\
	     : 1						\
    )								

#define INC_CHAR(cp, width_map)				\
{								\
    if (width_map)						\
	(cp) += ((width_map)[*(BYTE *)(cp)] & 0x0F);	\
    else							\
	(cp)++;					\
}

#define DISP_WIDTH(cp, width_map)				\
    (								\
	(width_map)						\
	    ? (width_map[*(BYTE *)cp] >> 4) & 0x0F		\
	    : 1							\
    )


/*
**  WHOLE_CHARS(start, end, wid_map, wcbytes, pc_part1, pc_part2, nchars)
**
**  This macro scans the string starting at `start' and ending at `end' using
**  the character width map `wid_map', and returns the following:
**
**	o  # of bytes in all "whole" characters in string (`wcbytes')
**	o  # bytes of partial character at end of string (`pc_part1')
**	o  # bytes missing from partial character at end of string (`pc_part2')
**	o  # of "whole" characters (`nchars')
**
**  Parameters:
**	Supplied:
**	    BYTE *start		Pointer to the start of the string.
**	    BYTE *end		Pointer to the byte *after* the end of the
**				string.  That is, the string's length can be
**				given by:  (end - start).
**	    BYTE *wid_map	Pointer to the character width map to use.
**			
**	Returned:
**	    int	 wcbytes	# bytes in all "whole" characters in string.
**	    int	 pc_part1	# bytes of partial character at end of string.
**				(If no partial character at end, then zero.)
**	    int	 pc_part2	# bytes missing from partial character at end
**				of string.  (If no partial character at end,
**				then zero.)
**	    int	 nchars		# of "whole" characters in string.
**
**  Evaluates to:
**	Nothing.
**
**  NOTE:
**	This macro *ASSUMES* that their may be multi-byte characters in the
**	string (i.e., assumes that the max char len for the character set > 1.)
**	Therefore, the macro makes no attempt at a fast-path for single-byte
**	character sets.
*/

#define WHOLE_CHARS(start, end, wid_map, wcbytes, pc_part1, pc_part2, nchars) \
	{								\
		BYTE	*sp;						\
		BYTE	*ep;						\
		BYTE	*cp;						\
		BYTE	*wmap;						\
		int	nc;						\
		int	wid;						\
									\
		sp = (BYTE *)(start);					\
		ep = (BYTE *)(end);					\
		cp = sp;						\
		wmap = (BYTE *)(wid_map);				\
		nc = 0;							\
		wid = 0;						\
		while (cp < ep)						\
		{							\
			wid = CHAR_WIDTH(cp, wmap);			\
			cp += wid;					\
			nc++;						\
		}							\
									\
		if (cp == ep)						\
		{							\
			/* No split characters */			\
			(nchars) = nc;					\
			(wcbytes) = ep - sp;				\
			(pc_part1) = 0;					\
			(pc_part2) = 0;					\
		}							\
		else							\
		{							\
			/* We did split a character */			\
			(nchars) = --nc;				\
			(wcbytes) = (cp - wid) - sp;			\
			(pc_part1) = wid - (cp - ep);			\
			(pc_part2) = cp - ep;				\
		}							\
	}


/*   ___________
**  *SINGLE-BYTE* CHARACTER TRANSFORMATION AND CLASSIFICATION MACROS:
**   ~~~~~~~~~~~
**	TOUPPER(c, tmap)  - Evaluate to upper-case equivalent of `c'.
**	TOLOWER(c, tmap)  - Evaluate to lower-case equivalent of `c'.
**
**	ISALPHA(c, tmap)  - Is this an alphabetic character?
**	ISUPPER(c, tmap)  - Is this an upper-case alphabetic character?
**	ISLOWER(c, tmap)  - Is this an lower-case alphabetic character?
**	ISDIGIT(c, tmap)  - Is this a decimal digit character?
**	ISXDIGIT(c, tmap) - Is this a hexadecimal digit character?
**	ISSPACE(c, tmap)  - Is this a white-space character?
**	ISPRINT(c)        - Is this a printable, 7-bit ASCII character?
**
**  These macros replace a set of standard 'C' library functions for
**  INTL_NLS use.
**	    ________________________________________________________
**	*** THESE MACROS ARE ONLY DEFINED FOR SINGLE-BYTE CHARACTERS ***
**	    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**  In these definitions, the following parameters are used:
**
**	BYTE	    c     - The codepoint for the character in question.
**	CS_TYPE_MAP *tmap - Points to the 1st element in the type map
**			    array (in the server this is usually
**			    Resource->rchar_attrib->cs_type_map).
**
**  History:
**	Feb 1991 - (gt) Written.
*/
 
#define TOUPPER(c, tmap)						\
	((tmap)[0].chmap[(BYTE)(c)].char_upper)

#define TOLOWER(c, tmap)						\
	((tmap)[0].chmap[(BYTE)(c)].char_lower)

#define ISALPHA(c, tmap)						\
	((tmap)[0].chmap[(BYTE)(c)].char_type & (P_UPPER | P_LOWER))

#define ISUPPER(c, tmap)						\
	((tmap)[0].chmap[(BYTE)(c)].char_type & P_UPPER)

#define ISLOWER(c, tmap)						\
	((tmap)[0].chmap[(BYTE)(c)].char_type & P_LOWER)

#define ISDIGIT(c, tmap)						\
	((tmap)[0].chmap[(BYTE)(c)].char_type & P_DIGIT)

#define ISXDIGIT(c, tmap)						\
	((tmap)[0].chmap[(BYTE)(c)].char_type & P_HEX)

#define ISSPACE(c, tmap)						\
	((tmap)[0].chmap[(BYTE)(c)].char_type & P_SPACE)

#define ISPRINT(c)							\
	/* for diagnostics -- only consider 7-bit ASCII */		\
	(((BYTE)(c) > 0x1f) && ((BYTE)(c) < 0x7f))


/*
**  CHARACTER TRANSFORMATION MACROS:
**
**	TO_M_UPPER(cp_src, cp_dest, chatr) - Find the upper-case
**					     equivalent of a character.
**	TO_M_LOWER(cp_src, cp_dest, chatr) - Find the lower-case
**					     equivalent of a character.
**
**  These macros are use for transforming single- or multi-byte characters
**  into some other characters.  E.g., the character's upper-case equivalent.
**
**  In these definitions, the following parameters are used:
**
**	BYTE	    *cp_src  - Points to the character to be transformed.
**	BYTE	    *cp_dest - Points to memory where the transformed
**			       character will be placed.
**	CHAR_ATTRIB *chatr   - Points to the character set definition
**			       structure (in the server this is usually
**			       Resource->rchar_attrib).
**
**  History:
**	Feb 1991 - (gt) Written.
*/

#define TO_M_UPPER(cp_src, cp_dest, chatr)				\
{									\
    REGISTER CS_TYPE_MAP	*tmap;					\
    REGISTER BYTE		*s;					\
    REGISTER BYTE		*d;					\
    REGISTER CHAR_MAP		*cm_ptr;				\
    int				tm_ix;					\
									\
    tmap = (chatr)->cs_type_map;					\
    s = (BYTE *)(cp_src);						\
    d = (BYTE *)(cp_dest);						\
									\
    /*									\
    ** Find the CHAR_MAP structure for the 1st byte of the		\
    ** character (which will be in type map [0]), and see if		\
    ** P_ALPHABET is set in the char_type field.			\
    */									\
    cm_ptr = &(tmap[0].chmap[*s]);					\
    if (cm_ptr->char_type & P_ALPHABET)					\
    {									\
	/*								\
	** P_ALPHABET *is* set, so now we need to find the		\
	** secondary type map, which is held in the char_upper		\
	** field.  Then use the 2nd byte of the source character to	\
	** index into this type map's CHAR_MAP array to find the	\
	** secondary CHAR_MAP.  The upper-case character is created	\
	** as follows:  1st byte = 1st byte of source character;	\
	** 2nd byte = the char_upper field of the secondary CHAR_MAP.	\
	*/								\
	tm_ix = cm_ptr->char_upper;					\
	cm_ptr = &(tmap[tm_ix].chmap[*(s + 1)]);			\
	*d++ = *s;							\
	*d = cm_ptr->char_upper;					\
    }									\
    else 								\
    {									\
	/*								\
	** P_ALPHABET is *not* set, so now we need to check the		\
	** char_upper field to see if it zero or not.			\
	*/								\
	if (cm_ptr->char_upper)						\
	{								\
	    /*								\
	    ** char_upper is non-zero, therefore the character is a	\
	    ** single-byte character, and the upper-case equivalent	\
	    ** is given by the char_upper field.			\
	    */								\
	    *d = cm_ptr->char_upper;					\
	}								\
	else								\
	{								\
	    /*								\
	    ** char_upper is zero, therefore we just copy the (possibly	\
	    ** multi-byte) character from source to destination.	\
	    */								\
	    int	wid = CHAR_WIDTH(s, (chatr)->cs_width_map);		\
	    while (wid--)						\
		*d++ = *s++;						\
	}								\
    }									\
}

#define TO_M_LOWER(cp_src, cp_dest, chatr)				\
{									\
    REGISTER CS_TYPE_MAP	*tmap;					\
    REGISTER BYTE		*s;					\
    REGISTER BYTE		*d;					\
    REGISTER CHAR_MAP		*cm_ptr;				\
    int				tm_ix;					\
									\
    tmap = (chatr)->cs_type_map;					\
    s = (BYTE *)(cp_src);						\
    d = (BYTE *)(cp_dest);						\
									\
    /*									\
    ** Find the CHAR_MAP structure for the 1st byte of the		\
    ** character (which will be in type map [0]), and see if		\
    ** P_ALPHABET is set in the char_type field.			\
    */									\
    cm_ptr = &(tmap[0].chmap[*s]);					\
    if (cm_ptr->char_type & P_ALPHABET)					\
    {									\
	/*								\
	** P_ALPHABET *is* set, so now we need to find the		\
	** secondary type map, which is held in the char_upper		\
	** field.  Then use the 2nd byte of the source character to	\
	** index into this type map's CHAR_MAP array to find the	\
	** secondary CHAR_MAP.  The lower-case character is created	\
	** as follows:  1st byte = 1st byte of source character;	\
	** 2nd byte = the char_lower field of the secondary CHAR_MAP.	\
	*/								\
	tm_ix = cm_ptr->char_upper;					\
	cm_ptr = &(tmap[tm_ix].chmap[*(s + 1)]);			\
	*d++ = *s;							\
	*d = cm_ptr->char_lower;					\
    }									\
    else 								\
    {									\
	/*								\
	** P_ALPHABET is *not* set, so now we need to check the		\
	** char_lower field to see if it zero or not.			\
	*/								\
	if (cm_ptr->char_lower)						\
	{								\
	    /*								\
	    ** char_lower is non-zero, therefore the character is a	\
	    ** single-byte character, and the lower-case equivalent	\
	    ** is given by the char_lower field.			\
	    */								\
	    *d = cm_ptr->char_lower;					\
	}								\
	else								\
	{								\
	    /*								\
	    ** char_lower is zero, therefore we just copy the (possibly	\
	    ** multi-byte) character from source to destination.	\
	    */								\
	    int	wid = CHAR_WIDTH(s, (chatr)->cs_width_map);		\
	    while (wid--)						\
		*d++ = *s++;						\
	}								\
    }									\
}


/*
**  MULTI-BYTE CHARACTER MACROS FOR USE
**		 ____
**		*ONLY*
**		 ~~~~
**  INTERNALLY WITHIN THIS INCLUDE FILE!
**
**	TYMAP_1(cp, tm)  - Evaluates to 1st type map (always [0]) for the
**			   character.
**	CHMAP_1(cp, tm)  - Evaluates to 1st character map for the character.
**	TYMAP_2(cp, tm)  - Evaluates to secondary type map for the character.
**	CHMAP_2(cp, tm)  - Evaluates to secondary character map for the
**			   character.
**
**	NRMAP_1(cp, ca)  - Evaluates to 1st norm map (always [0]) for the
**			   character.
**	NORM_1(cp, ca)   - Evaluates to 1st "normalization" BYTE for the
**			   character.
**	NRMAP_2(cp, ca)  - Evaluates to secondary norm map for the character.
**	NORM_2(cp, ca)   - Evaluates to secondary "normalization" BYTE for the
**			   character.
**
**	SNDMAP_1(cp, ca) - Evaluates to 1st soundex map (always [0]) for the
**			   character.
**	SOUND_1(cp, ca)  - Evaluates to 1st "soundex" BYTE for the character.
**	SNDMAP_2(cp, ca) - Evaluates to secondary soundex map for the character.
**	SOUND_2(cp, ca)  - Evaluates to secondary "soundex" BYTE for the
**			   character.
**
**  Notes:
**	(1) For all of these macros:  The pointer to the character in question,
**	    `cp', is passed in.
**
**	(2) For TYMAP_{1,2} and CHMAP_{1,2} macros:  The pointer `tm' is
**	    assumed.  It should point to the 1st element in the array of
**	    CS_TYPE_MAPs for the character set.
**
**	(3) For NRMAP_{1,2}, NORM_{1,2}, SNDMAP_{1,2} and SOUND_{1,2} macros:
**	    The pointer `chatr' is assumed.  It should point to the CHAR_ATTRIB
**	    structure for the character set.
**
**  History:
**	Feb 1991 - (gt) Written.
*/

#define TYMAP_1(cp, tm)	((tm)[0])
#define CHMAP_1(cp, tm)	(TYMAP_1(cp,tm).chmap[*((BYTE *)(cp))])
#define TYMAP_2(cp, tm)	((tm)[CHMAP_1(cp,tm).char_upper])
#define CHMAP_2(cp, tm)	(TYMAP_2(cp,tm).chmap[*((BYTE *)(cp) + 1)])

#define NRMAP_1(cp, ca)	((ca)->cs_norm_map[0])
#define NORM_1(cp, ca)		(NRMAP_1(cp,ca).norm[*((BYTE *)(cp))])
#define NRMAP_2(cp, ca)	((ca)->cs_norm_map[NORM_1(cp,ca)])
#define NORM_2(cp, ca)		(NRMAP_2(cp,ca).norm[*((BYTE *)(cp) + 1)])

#define SNDMAP_1(cp, ca)	((ca)->cs_soundex[0])
#define SOUND_1(cp, ca)	(SNDMAP_1(cp,ca).sound[*((BYTE *)(cp))])
#define SNDMAP_2(cp, ca)	((ca)->cs_soundex[SOUND_1(cp,ca)])
#define SOUND_2(cp, ca)	(SNDMAP_2(cp,ca).sound[*((BYTE *)(cp) + 1)])


/*
**  CHARACTER CLASSIFICATON MACROS:
**
**	IS_M_ALPHA(cp, tmap)  - Is this an alphabetic character?
**	IS_M_UPPER(cp, tmap)  - Is this an upper-case alphabetic character?
**	IS_M_LOWER(cp, tmap)  - Is this an lower-case alphabetic character?
**	IS_M_DIGIT(cp, tmap)  - Is this a decimal digit character?
**	IS_M_XDIGIT(cp, tmap) - Is this a hexadecimal digit character?
**	IS_M_SPACE(cp, tmap)  - Is this a white-space character?
**	IS_M_PUNCT(cp, tmap)  - Is this a punctuation character?
**
**  These macros are use for single- or multi-byte characters, and are
**  used to classify a particular character.  E.g., is it an upper-case
**  character?  Or, is it a legal hexidecimal digit character?  Etc.
**
**  Note:
**	The IS_M_WHAT() macro is intended solely for use
**	in this file by the rest of the IS_M_...() macros.
**
**  In these definitions, the following parameters are used:
**
**	BYTE	    *cp   - Points to the character in question.
**	CS_TYPE_MAP *tmap - Points to the 1st element in the type map
**			    array (in the server this is usually
**			    Resource->rchar_attrib->cs_type_map).
**
**  History:
**	Feb 1991 - (gt) Written.
*/

#define IS_M_WHAT(cp, tmap, p_type)					\
    (   /*								\
	** Find the CHAR_MAP structure for the 1st byte of the char-	\
	** acter and see if P_ALPHABET is set in the char_type field.	\
	*/								\
	(CHMAP_1(cp,tmap).char_type & P_ALPHABET)			\
	    ? /*							\
	      ** P_ALPHABET *is* set, so now we need to find the	\
	      ** secondary character map (in the secondary type map).	\
	      ** This CHAR_MAP will hold the character's c-type		\
	      ** information.  This is what we `and' with the type we	\
	      ** are interested in.					\
	      */							\
	      (CHMAP_2(cp,tmap).char_type & (p_type))			\
	    : /*							\
	      ** P_ALPHABET is *not* set, so the character's c-type	\
	      ** information is held right here in the first CHAR_MAP	\
	      ** we used.  This is what we `and' with the type we are	\
	      ** interested in.						\
	      */							\
	      (CHMAP_1(cp,tmap).char_type & (p_type))			\
    )

#define IS_M_ALPHA(cp, tmap)   IS_M_WHAT(cp, tmap, (P_UPPER | P_LOWER))
#define IS_M_UPPER(cp, tmap)   IS_M_WHAT(cp, tmap, P_UPPER)
#define IS_M_LOWER(cp, tmap)   IS_M_WHAT(cp, tmap, P_LOWER)
#define IS_M_DIGIT(cp, tmap)   IS_M_WHAT(cp, tmap, P_DIGIT)
#define IS_M_XDIGIT(cp, tmap)  IS_M_WHAT(cp, tmap, P_HEX)
#define IS_M_SPACE(cp, tmap)   IS_M_WHAT(cp, tmap, P_SPACE)
#define IS_M_PUNCT(cp, tmap)   IS_M_WHAT(cp, tmap, P_PUNCT)


/*    
**  LEXICAL ANALYZER MACROS
**
**	GET_LEX(cp, tmap)   - Evaluates to lexical type of this character.
**	TO_ASCII(cp, chatr) - Evaluates to the 7-bit ASCII, lower-case
**			      equivalent of this character.
**
**  These macros are used by the lexical analyzer, and other places in the
**  code that may need to find the lexical type of a character or the 7-bit
**  ASCII, lower-case equivalent of a character (via the character set's
**  "normalization maps").
**
**  In these definitions, the following parameters are used:
**
**	BYTE        *cp    - Points to the character in question.
**	CS_TYPE_MAP *tmap  - Points to the 1st element in the type map
**			     array (in the server this is usually
**			     Resource->rchar_attrib->cs_type_map).
**	CHAR_ATTRIB *chatr - Points to the character set definition
**			     structure (in the server this is usually
**			     Resource->rchar_attrib).
**
**  History:
**	Feb 1991 - (gt) Written.
*/

#define GET_LEX(cp, tmap)				\
    (							\
	(CHMAP_1(cp,tmap).char_type & P_ALPHABET)	\
	    ? (CHMAP_2(cp,tmap).char_lex)		\
	    : (CHMAP_1(cp,tmap).char_lex)		\
    )

#define TO_ASCII(cp, chatr)						\
    (	/*								\
	** Check to see if we have a CHAR_ATTRIB pointer.		\
	*/								\
	(chatr == NULL)							\
	    ? /*							\
	      ** No CHAR_ATTRIB pointer, just return the 1st byte.	\
	      */							\
	      (*(BYTE *)(cp))						\
	    : /*							\
	      ** We have a CHAR_ATTRIB pointer.				\
	      ** Now check for existence of norm map.			\
	      */							\
	      ((chatr)->cs_norm_map == NULL)				\
		? /*							\
		  ** No norm map.  Check for existence of type map.	\
		  */							\
		  ((chatr)->cs_type_map == NULL)			\
		    ? /*						\
		      ** No type map, just return the 1st byte.		\
		      */						\
		      (*(BYTE *)(cp))					\
		    : /*						\
		      ** There is a type map, which means that we can	\
		      ** assume a single-byte character, and return	\
		      ** the TOLOWER value of it.			\
		      */						\
		      (TOLOWER(*(BYTE *)(cp), (chatr)->cs_type_map))	\
		: /*							\
		  ** There *is* a norm map.  Check character width.	\
		  */							\
		  (CHAR_WIDTH(cp, (chatr)->cs_width_map) == 1)		\
	            ? /*						\
		      ** Character is 1 byte, so get the normalization	\
		      ** from the 1st norm map.				\
		      */						\
		      NORM_1(cp,chatr)					\
		    : /*						\
		      ** Character is multi-byte.  Test to see if there	\
		      ** is a secondary norm map.			\
		      */						\
		      (NORM_1(cp,chatr) == 0x00)			\
		        ? /*						\
			  ** No secondary norm map, which means that	\
			  ** there is *no* normalization for this	\
			  ** character (e.g., a Kanji character).	\
			  ** Return zero.				\
			  */						\
			  (BYTE) 0x00					\
			: /*						\
			  ** There *is* a secondary norm map, so we	\
			  ** will use it and return what we find there.	\
			  */						\
			  NORM_2(cp,chatr)				\
    )


/*
**  STR_TO_ASCII(cp_src, src_len, cp_dest, dest_len, chatr)
**
**  This macro converts a string into its "TO_ASCII" equivalent string.
**  It is guaranteed that the destination string length will be less than
**  or equal to the source string length.
**
**  Note:  Because of this, it is legal to supply the same string pointer 
**  as both the source and destination string, "cp_src" and "cp_dest".
**  The same goes for the lengths, "src_len" and "dest_len".
**
**  Parameters:
**
**	char		*cp_src		Pointer to the source string.
**	int		src_len		Length of source string in bytes.
**	char		*cp_dest	Pointer to location for the
**					destination string.  (This can point
**					to the same location as "cp_src".)
**	int		dest_len	(RETURNED)  Length of the destination
**					string.  (This can be the same variable
**					as "src_len".)
**	CHAR_ATTRIB	*chatr		Pointer to the character set atribute
**					structure representing the character
**					set to be used for this operation.
**
**  Depends on:
**
**	TO_ASCII()
**	INC_CHAR()
**	CHAR_WIDTH()
**
**  History:
**	Jan 1991 - (gt) Written.
*/

#define STR_TO_ASCII(cp_src, src_len, cp_dest, dest_len, chatr)	\
	{								\
		REGISTER char	*is;					\
		REGISTER char	*ie;					\
		REGISTER char	*os;					\
		REGISTER char	c;					\
		BYTE		*wmap;					\
		int		w;					\
									\
		is = (char *)(cp_src);					\
		ie = is + (src_len);					\
		os = (char *)(cp_dest);					\
		(dest_len) = 0;						\
		wmap = (chatr)->cs_width_map;				\
									\
		while (is < ie)						\
		{							\
			if ((c = TO_ASCII(is, chatr)))			\
			{						\
				INC_CHAR(is, wmap);			\
				*os++ = c;				\
				(dest_len)++;				\
			}						\
			else						\
			{						\
				for (w = CHAR_WIDTH(is, wmap); w; w--)	\
				{					\
					*os++ = *is++;			\
					(dest_len)++;			\
				}					\
			}						\
		}							\
	}


/*
**  CS_1CLASS - Class `1' Character Set in IMAGE Field
**
**  This structure defines what the IMAGE field will look like for a class `1'
**  character set.  It will contain an array of 256 CHAR_MAPs, followed by an
**  array of 256 chars representing the soundex information for the character
**  set. Each array is also padded with an extra element to maintain  
**  compatibility  with the size of the 4.2 CS_1CLASS structure. 
**  This extra element SHOULD NOT be used as it is not intended for
**  data storage.
*/

typedef struct cs_1class
{
    CHAR_MAP	char_map[SYBCHARSET_SIZE + 1];	/*
   						** The character set definition.
						*/

    BYTE	sounds[SYBCHARSET_SIZE + 1];/* The soundex information for each
					    ** character in the character set.
					    */
} CS_1CLASS;


/*
**  CS_2CLASS - Class `2' Character Set in IMAGE Field
**
**  This structure defines what the beginning of the IMAGE field will look like
**  for a class `2' character set.  This contains the offsets and sizes of the
**  various "maps", which will be used to determine the location and the size of
**  these maps (i.e., the actual data).
**
**  The full layout of a class `2' character set in the IMAGE field is as
**  follows:
**
**	+----------------------------------+
**	|   Character Set Header           |	CS_2CLASS
**	+----------------------------------+
**	|   Character Width Map	           |	BYTE[256]
**	|   (if it exists)                 |
**	+----------------------------------+
**	|   Character Normalization Maps   |	CS_NORM_MAP[n]
**	|   (if they exist)                |
**	+----------------------------------+
**	|   Character Type Maps	           |	CS_TYPE_MAP[t]
**	|   (if they exist)                |
**	+----------------------------------+
**	|   Character Soundex Maps	   |	CS_SOUNDEX[s]
**	|   (if they exist)                |
**	+----------------------------------+
*/

typedef struct cs_2class
{
	short 		cs_status;
	BYTE		cs_class;
	BYTE		cs_maxcharlen;
	BYTE		cs_ncharsize;
	BYTE		cs_ntype;
	BYTE		cs_nnorm;
	BYTE		cs_nsoundex;
	BYTE		machine_type;
	BYTE		padding[3];
	CS_UINT		off_width;
	CS_UINT		size_width;
	CS_UINT		off_norm;
	CS_UINT		size_norm;
	CS_UINT		off_type;
	CS_UINT		size_type;
	CS_UINT		off_soundex;
	CS_UINT		size_soundex;
} CS_2CLASS;

/*
** Type of character set - whether CS_1CLASS or CS_2CLASS
** The type field in the syscharsets table in the SQL server holds either of
** these 2 values.
*/
#define		CS_TYPE_CS1	(CS_SMALLINT)1001
#define		CS_TYPE_CS2	(CS_SMALLINT)1002


/*
**  MIN_CSSIZE
**
**  The formula for determining the size of the complete character set
**  definition, as it is laid out in the Syscharsets table, is as follows:
**
**	  sizeof(CS_2CLASS)		space for CS_2CLASS structure
**	+ (w * SYBCHARSET_SIZE)		space for the width map
**	+ (n * sizeof(CS_NORM_MAP))	space for the normalization maps
**	+ (t * sizeof(CS_TYPE_MAP))	space for the type maps
**	+ (s * sizeof(CS_SOUNDEX))	space for the soundex maps
**
**  Where:
**	`w' is the number of width maps -- either 0 (no width map, all
**					   characters are 1 byte) or 1.
**	`n' is the number of normalization maps.  (Can be 0.)
**	`t' is the number of type maps.  (Can *NOT* be 0.)
**	`s' is the number of soundex maps.  (Can *NOT* be 0.)
**  
**  Given this, the minumum size of a character set definition can be derived
**  by setting:  `w' = 0,  `n' = 0,  `t' = 1,  `s' = 1.  This gives the
**  following definition for MIN_CSSIZE:
**
**  History:
**	Feb 1991 - (gt) Written.
*/

#define	MIN_CSSIZE			\
	(  sizeof(CS_2CLASS)		\
	 + (0 * SYBCHARSET_SIZE)	\
	 + (0 * sizeof(CS_NORM_MAP))	\
	 + (1 * sizeof(CS_TYPE_MAP))	\
	 + (1 * sizeof(CS_SOUNDEX))	\
	)

   

/*
**  NORMALIZE_LONG() - Normalizes a CS_UINT
**
**  Takes a CS_UINT in the native format for the
**  machine, and converts it into a "normal" byte ordered form, where
**  the first byte is the high-order byte, the second byte is the
**  next-highest-order byte, and so on down to the last byte which is
**  the low-order byte.
**
**  NORMALIZE_LONG(x)
**	On entry, x is assumed to CS_UINIT in "native"
**	    machine form.
**	On exit, x will be in "normalized" form, with the high-order
**	    byte first, etc.
*/

#define NORMALIZE_LONG(x)			\
{						\
	CS_UINT		l;			\
	BYTE		*bp;			\
						\
	bp = (BYTE *)(&(l));			\
	*bp++ = (((x) >> 24) & 0x000000FF);	\
	*bp++ = (((x) >> 16) & 0x000000FF);	\
	*bp++ = (((x) >>  8) & 0x000000FF);	\
	*bp   = (((x)      ) & 0x000000FF);	\
	(x) = l;				\
}


/*
**  NORMALIZE_SHORT() - Normalizes a short or unsigned short.
**
**  Takes a short (or an unsigned short) in the native format for the
**  machine, and converts it into a "normal" byte ordered form, where
**  the first byte is the high-order byte, the second byte is the
**  next-highest-order byte, and so on down to the last byte which is
**  the low-order byte.
**
**  NORMALIZE_SHORT(x)
**	On entry, x is assumed to a short or unsigned short in "native"
**	    machine form.
**	On exit, x will be in "normalized" form, with the high-order
**	    byte first, etc.
*/

#define NORMALIZE_SHORT(x)			\
{						\
	unsigned short	s;			\
	BYTE		*bp;			\
						\
	bp = (BYTE *)(&(s));			\
	*bp++ = (((x) >>  8) & 0x00FF);		\
	*bp   = (((x)      ) & 0x00FF);		\
	(x) = s;				\
}


/*
**  NATURALIZE_LONG() - Naturalizes a CS_UINT.
**
**  Takes a CS_UINT in "normal" byte ordered form
**  (where the first byte is the high-order byte, the second byte is the
**  next-highest-order byte, and so on down to the last byte which is
**  the low-order byte) and converts it into the native format for the
**  machine.
**
**  NATURALIZE_LONG(x)
**	On entry, x is assumed to a CS_UINT in
**	    "normalized" form, with the high-order byte first, etc.
**	On exit, x will be in "native" machine form.
*/

#define NATURALIZE_LONG(x)				\
{							\
	CS_UINT		l;				\
	BYTE		*bp;				\
							\
	bp = (BYTE *)(&(x));				\
	l  = ((((CS_UINT)(*bp++)) << 24) & ~ (CS_UINT)0x00FFFFFF); \
	l |= ((((CS_UINT)(*bp++)) << 16) & 0x00FF0000);	\
	l |= ((((CS_UINT)(*bp++)) <<  8) & 0x0000FF00);	\
	l |= ((((CS_UINT)(*bp  ))      ) & 0x000000FF);	\
	(x) = l;					\
}


/*
**  NATURALIZE_SHORT() - Naturalizes a short or unsigned short.
**
**  Takes a short (or an unsigned short) in "normal" byte ordered form
**  (where the first byte is the high-order byte, the second byte is the
**  next-highest-order byte, and so on down to the last byte which is
**  the low-order byte) and converts it into the native format for the
**  machine.
**
**  NATURALIZE_SHORT(x)
**	On entry, x is assumed to a short or unsigned short in
**	    "normalized" form, with the high-order byte first, etc.
**	On exit, x will be in "native" machine form.
*/

#define NATURALIZE_SHORT(x)				\
{							\
	unsigned short	s;				\
	BYTE		*bp;				\
							\
	bp = (BYTE *)(&(x));				\
	s  = ((((unsigned short)(*bp++)) <<  8) & 0xFF00);	\
	s |= ((((unsigned short)(*bp  ))      ) & 0x00FF);	\
	(x) = s;						\
}


#endif  /* ifndef __intl_nls__ */
