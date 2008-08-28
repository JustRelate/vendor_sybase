/* Sccsid @(#) sybtypes.h 8.1 8/10/93 */

/*
**  COMTYPES.H
**
**	Header file to be included in all files which use Common-Lib routines.
**	This header file contains:
		a) definitions for NULL, FALSE, TRUE
**		b) type definitions for the Common-Lib datatypess;
*/

#ifndef	__sybtypes__
#define __sybtypes__

#include	<cstypes.h>

#ifndef NULL
#define NULL            0
#endif /* NULL */
 
#ifndef FALSE
#define FALSE   	0
#endif /* FALSE */
 
#ifndef TRUE
#define TRUE    	1
#endif /* TRUE */

/*
** NOTE: The following are for backwards compatibility. 
*/

#define	COM_MAXCHAR	CS_MAX_CHAR

/*
** Type definitions for Common-Lib datatypes.
*/
#define COM_TINYINT	CS_TINYINT
#define COM_SMALLINT	CS_SMALLINT
#define COM_INT		CS_INT
#define COM_CHAR	CS_CHAR
#define COM_BINARY	CS_BINARY
#define COM_BIT		CS_BIT

#define COM_DATETIME	CS_DATETIME
#define COM_DATETIME4	CS_DATETIME4
#define COM_MONEY	CS_MONEY
#define COM_MONEY4	CS_MONEY4

#define COM_FLT8	CS_FLOAT
#define COM_REAL	CS_REAL
#define COM_BYTE	CS_BYTE
#define COM_BOOL	CS_BOOL

#define COM_VARYCHAR	CS_VARCHAR
#define COM_VARYBIN	CS_VARBINARY

#define COM_DATEREC	CS_DATEREC

#endif /* __sybtypes__ */
