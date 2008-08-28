 
/* Sccsid %Z% %M% %I% %G% */

/*
**      Sybase OpenClient Version 5.0
**      Confidential Property of Sybase, Inc.
**      (c) Copyright Sybase, Inc. 1991, 1992
**      All rights reserved
*/

/*
** csintrn.h - This header file enables the internal use of "generic"
**	       data structures in OpenClient
*/
#ifndef __CSINTRN_H__
 
#define __CSINTRN_H__

#define CS__INTERNAL_STRUCTS

typedef struct _cscontext	CS_CONTEXT;
typedef struct _csconnection	CS_CONNECTION;
typedef struct _cscommand	CS_COMMAND;
typedef struct _csloginfo	CS_LOGINFO;
typedef struct _cslocale  	CS_LOCALE;
typedef struct char_attrib	CS_ATTRIB;
typedef struct cs_type_map	CS_TYPEMAP;
typedef struct so_1class	CS_SO_1CLASS;
typedef struct so_2class	CS_SO_2CLASS;
typedef struct _cs_blkdesc	CS_BLKDESC;
typedef	struct _bulkrow		CS_BLK_ROW; 

#endif /* __CSINTRN_H__ */
