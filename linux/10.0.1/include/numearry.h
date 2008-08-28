

/* Sccsid %Z% %M% %I% %G% */

/*
**	Sybase COMMON-LIBRARY Version 5.0
**	Confidential Property of Sybase, Inc.
**	(c) Copyright Sybase, Inc. 1991, 1992
**	All rights reserved
*/

#ifndef __NUMEARRAY_H__
#define __NUMEARRAY_H__

/* server: generic/include/numearray.h 60.1 8/17/92 */

/*
**	NUMEARRAY.H
**
**	This file defines several arrays used to hold information for
**	processing exact nuemric datatypes. These arrays are used to save 
**	computation time for frequently looked up values.
**
**	It contains the following arrays:
**	Nume_Byte_Power_Array[NUME_MAXPREC + 1][NUME_MAXLEN + 1] - 
**				used to hold the bit patterns
**			        for numbers 10e0, 10e1, 10e2 ...
**			        These are used to scale up or down
**			        an exact numeric value.
**				The first elementis used to store the
**				length and the rest used to store the
**				BYTE pattern. The size of the array is
**				(NUME_MAXPREC + 1) X (NUME_MAXLEN + 1)
**
**	Nume_Len_To_Prec[NUME_MAXLEN + 2]	-	
**				This is the length to maximum precision
**				for the length, map. It is used in several
**				places including conversions, scaling
**				math operations etc.
**
**	Nume_Prec_To_Len[NUME_MAXPREC + 1]	-	
**				This is the precision to length mapping.
**				It is also used in several places
**				including scaling, math opns, conversions
**					etc.
**
** History:
**	Jan 24 1991 (manish) - created for use with the exact numerics.
**	April 14 92 (prema)  - modified to reflect change in design.
**	02/16/94 tchilder 62418, removed Nume_Flt_Power_Array, 
**			Nume_Flt_256_Array: no longer used in numeric.c;
**			reformatted Nume_Byte_Power_Array for 80-char width
**
*/

#if NUMU_EARRY_DECLARE

unsigned char Nume_Byte_Power_Array[78][34] =
{
{0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^0 */ 
{0x02, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^1 */ 
{0x02, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^2 */ 
{0x03, 0x00, 0x03, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^3 */ 
{0x03, 0x00, 0x27, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^4 */ 
{0x04, 0x00, 0x01, 0x86, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^5 */ 
{0x04, 0x00, 0x0f, 0x42, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^6 */ 
{0x04, 0x00, 0x98, 0x96, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^7 */ 
{0x05, 0x00, 0x05, 0xf5, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^8 */ 
{0x05, 0x00, 0x3b, 0x9a, 0xca, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^9 */ 
{0x06, 0x00, 0x02, 0x54, 0x0b, 0xe4, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^10 */ 
{0x06, 0x00, 0x17, 0x48, 0x76, 0xe8, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^11 */ 
{0x06, 0x00, 0xe8, 0xd4, 0xa5, 0x10, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^12 */ 
{0x07, 0x00, 0x09, 0x18, 0x4e, 0x72, 0xa0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^13 */ 
{0x07, 0x00, 0x5a, 0xf3, 0x10, 0x7a, 0x40, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^14 */ 
{0x08, 0x00, 0x03, 0x8d, 0x7e, 0xa4, 0xc6, 0x80, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^15 */ 
{0x08, 0x00, 0x23, 0x86, 0xf2, 0x6f, 0xc1, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^16 */ 
{0x09, 0x00, 0x01, 0x63, 0x45, 0x78, 0x5d, 0x8a, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^17 */ 
{0x09, 0x00, 0x0d, 0xe0, 0xb6, 0xb3, 0xa7, 0x64, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^18 */ 
{0x09, 0x00, 0x8a, 0xc7, 0x23, 0x04, 0x89, 0xe8, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^19 */ 
{0x0a, 0x00, 0x05, 0x6b, 0xc7, 0x5e, 0x2d, 0x63, 0x10, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^20 */ 
{0x0a, 0x00, 0x36, 0x35, 0xc9, 0xad, 0xc5, 0xde, 0xa0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^21 */ 
{0x0b, 0x00, 0x02, 0x1e, 0x19, 0xe0, 0xc9, 0xba, 0xb2, 0x40,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^22 */ 
{0x0b, 0x00, 0x15, 0x2d, 0x02, 0xc7, 0xe1, 0x4a, 0xf6, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^23 */ 
{0x0b, 0x00, 0xd3, 0xc2, 0x1b, 0xce, 0xcc, 0xed, 0xa1, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^24 */ 
{0x0c, 0x00, 0x08, 0x45, 0x95, 0x16, 0x14, 0x01, 0x48, 0x4a,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^25 */ 
{0x0c, 0x00, 0x52, 0xb7, 0xd2, 0xdc, 0xc8, 0x0c, 0xd2, 0xe4,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^26 */ 
{0x0d, 0x00, 0x03, 0x3b, 0x2e, 0x3c, 0x9f, 0xd0, 0x80, 0x3c,
0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^27 */ 
{0x0d, 0x00, 0x20, 0x4f, 0xce, 0x5e, 0x3e, 0x25, 0x02, 0x61,
0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^28 */ 
{0x0e, 0x00, 0x01, 0x43, 0x1e, 0x0f, 0xae, 0x6d, 0x72, 0x17,
0xca, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^29 */ 
{0x0e, 0x00, 0x0c, 0x9f, 0x2c, 0x9c, 0xd0, 0x46, 0x74, 0xed,
0xea, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^30 */ 
{0x0e, 0x00, 0x7e, 0x37, 0xbe, 0x20, 0x22, 0xc0, 0x91, 0x4b,
0x26, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^31 */ 
{0x0f, 0x00, 0x04, 0xee, 0x2d, 0x6d, 0x41, 0x5b, 0x85, 0xac,
0xef, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^32 */ 
{0x0f, 0x00, 0x31, 0x4d, 0xc6, 0x44, 0x8d, 0x93, 0x38, 0xc1,
0x5b, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^33 */ 
{0x10, 0x00, 0x01, 0xed, 0x09, 0xbe, 0xad, 0x87, 0xc0, 0x37,
0x8d, 0x8e, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^34 */ 
{0x10, 0x00, 0x13, 0x42, 0x61, 0x72, 0xc7, 0x4d, 0x82, 0x2b,
0x87, 0x8f, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^35 */ 
{0x10, 0x00, 0xc0, 0x97, 0xce, 0x7b, 0xc9, 0x07, 0x15, 0xb3,
0x4b, 0x9f, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^36 */ 
{0x11, 0x00, 0x07, 0x85, 0xee, 0x10, 0xd5, 0xda, 0x46, 0xd9,
0x00, 0xf4, 0x36, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^37 */ 
{0x11, 0x00, 0x4b, 0x3b, 0x4c, 0xa8, 0x5a, 0x86, 0xc4, 0x7a,
0x09, 0x8a, 0x22, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^38 */ 
{0x12, 0x00, 0x02, 0xf0, 0x50, 0xfe, 0x93, 0x89, 0x43, 0xac,
0xc4, 0x5f, 0x65, 0x56, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^39 */ 
{0x12, 0x00, 0x1d, 0x63, 0x29, 0xf1, 0xc3, 0x5c, 0xa4, 0xbf,
0xab, 0xb9, 0xf5, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^40 */ 
{0x13, 0x00, 0x01, 0x25, 0xdf, 0xa3, 0x71, 0xa1, 0x9e, 0x6f,
0x7c, 0xb5, 0x43, 0x95, 0xca, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^41 */ 
{0x13, 0x00, 0x0b, 0x7a, 0xbc, 0x62, 0x70, 0x50, 0x30, 0x5a,
0xdf, 0x14, 0xa3, 0xd9, 0xe4, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^42 */ 
{0x13, 0x00, 0x72, 0xcb, 0x5b, 0xd8, 0x63, 0x21, 0xe3, 0x8c,
0xb6, 0xce, 0x66, 0x82, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^43 */ 
{0x14, 0x00, 0x04, 0x7b, 0xf1, 0x96, 0x73, 0xdf, 0x52, 0xe3,
0x7f, 0x24, 0x10, 0x01, 0x1d, 0x10, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^44 */ 
{0x14, 0x00, 0x2c, 0xd7, 0x6f, 0xe0, 0x86, 0xb9, 0x3c, 0xe2,
0xf7, 0x68, 0xa0, 0x0b, 0x22, 0xa0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^45 */ 
{0x15, 0x00, 0x01, 0xc0, 0x6a, 0x5e, 0xc5, 0x43, 0x3c, 0x60,
0xdd, 0xaa, 0x16, 0x40, 0x6f, 0x5a, 0x40, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^46 */ 
{0x15, 0x00, 0x11, 0x84, 0x27, 0xb3, 0xb4, 0xa0, 0x5b, 0xc8,
0xa8, 0xa4, 0xde, 0x84, 0x59, 0x86, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^47 */ 
{0x15, 0x00, 0xaf, 0x29, 0x8d, 0x05, 0x0e, 0x43, 0x95, 0xd6,
0x96, 0x70, 0xb1, 0x2b, 0x7f, 0x41, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^48 */ 
{0x16, 0x00, 0x06, 0xd7, 0x9f, 0x82, 0x32, 0x8e, 0xa3, 0xda,
0x61, 0xe0, 0x66, 0xeb, 0xb2, 0xf8, 0x8a, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^49 */ 
{0x16, 0x00, 0x44, 0x6c, 0x3b, 0x15, 0xf9, 0x92, 0x66, 0x87,
0xd2, 0xc4, 0x05, 0x34, 0xfd, 0xb5, 0x64, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^50 */ 
{0x17, 0x00, 0x02, 0xac, 0x3a, 0x4e, 0xdb, 0xbf, 0xb8, 0x01,
0x4e, 0x3b, 0xa8, 0x34, 0x11, 0xe9, 0x15, 0xe8, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^51 */ 
{0x17, 0x00, 0x1a, 0xba, 0x47, 0x14, 0x95, 0x7d, 0x30, 0x0d,
0x0e, 0x54, 0x92, 0x08, 0xb3, 0x1a, 0xdb, 0x10, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^52 */ 
{0x18, 0x00, 0x01, 0x0b, 0x46, 0xc6, 0xcd, 0xd6, 0xe3, 0xe0,
0x82, 0x8f, 0x4d, 0xb4, 0x56, 0xff, 0x0c, 0x8e, 0xa0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^53 */ 
{0x18, 0x00, 0x0a, 0x70, 0xc3, 0xc4, 0x0a, 0x64, 0xe6, 0xc5,
0x19, 0x99, 0x09, 0x0b, 0x65, 0xf6, 0x7d, 0x92, 0x40, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^54 */ 
{0x18, 0x00, 0x68, 0x67, 0xa5, 0xa8, 0x67, 0xf1, 0x03, 0xb2,
0xff, 0xfa, 0x5a, 0x71, 0xfb, 0xa0, 0xe7, 0xb6, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^55 */ 
{0x19, 0x00, 0x04, 0x14, 0x0c, 0x78, 0x94, 0x0f, 0x6a, 0x24,
0xfd, 0xff, 0xc7, 0x88, 0x73, 0xd4, 0x49, 0x0d, 0x21, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^56 */ 
{0x19, 0x00, 0x28, 0xc8, 0x7c, 0xb5, 0xc8, 0x9a, 0x25, 0x71,
0xeb, 0xfd, 0xcb, 0x54, 0x86, 0x4a, 0xda, 0x83, 0x4a, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^57 */ 
{0x1a, 0x00, 0x01, 0x97, 0xd4, 0xdf, 0x19, 0xd6, 0x05, 0x76,
0x73, 0x37, 0xe9, 0xf1, 0x4d, 0x3e, 0xec, 0x89, 0x20, 0xe4,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^58 */ 
{0x1a, 0x00, 0x0f, 0xee, 0x50, 0xb7, 0x02, 0x5c, 0x36, 0xa0,
0x80, 0x2f, 0x23, 0x6d, 0x04, 0x75, 0x3d, 0x5b, 0x48, 0xe8,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^59 */ 
{0x1a, 0x00, 0x9f, 0x4f, 0x27, 0x26, 0x17, 0x9a, 0x22, 0x45,
0x01, 0xd7, 0x62, 0x42, 0x2c, 0x94, 0x65, 0x90, 0xd9, 0x10,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^60 */ 
{0x1b, 0x00, 0x06, 0x39, 0x17, 0x87, 0x7c, 0xec, 0x05, 0x56,
0xb2, 0x12, 0x69, 0xd6, 0x95, 0xbd, 0xcb, 0xf7, 0xa8, 0x7a,
0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^61 */ 
{0x1b, 0x00, 0x3e, 0x3a, 0xeb, 0x4a, 0xe1, 0x38, 0x35, 0x62,
0xf4, 0xb8, 0x22, 0x61, 0xd9, 0x69, 0xf7, 0xac, 0x94, 0xca,
0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^62 */ 
{0x1c, 0x00, 0x02, 0x6e, 0x4d, 0x30, 0xec, 0xcc, 0x32, 0x15,
0xdd, 0x8f, 0x31, 0x57, 0xd2, 0x7e, 0x23, 0xac, 0xbd, 0xcf,
0xe6, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^63 */ 
{0x1c, 0x00, 0x18, 0x4f, 0x03, 0xe9, 0x3f, 0xf9, 0xf4, 0xda,
0xa7, 0x97, 0xed, 0x6e, 0x38, 0xed, 0x64, 0xbf, 0x6a, 0x1f,
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^64 */ 
{0x1c, 0x00, 0xf3, 0x16, 0x27, 0x1c, 0x7f, 0xc3, 0x90, 0x8a,
0x8b, 0xef, 0x46, 0x4e, 0x39, 0x45, 0xef, 0x7a, 0x25, 0x36,
0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^65 */ 
{0x1d, 0x00, 0x09, 0x7e, 0xdd, 0x87, 0x1c, 0xfd, 0xa3, 0xa5,
0x69, 0x77, 0x58, 0xbf, 0x0e, 0x3c, 0xbb, 0x5a, 0xc5, 0x74,
0x1c, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^66 */ 
{0x1d, 0x00, 0x5e, 0xf4, 0xa7, 0x47, 0x21, 0xe8, 0x64, 0x76,
0x1e, 0xa9, 0x77, 0x76, 0x8e, 0x5f, 0x51, 0x8b, 0xb6, 0x89,
0x1b, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^67 */ 
{0x1e, 0x00, 0x03, 0xb5, 0x8e, 0x88, 0xc7, 0x53, 0x13, 0xec,
0x9d, 0x32, 0x9e, 0xaa, 0xa1, 0x8f, 0xb9, 0x2f, 0x75, 0x21,
0x5b, 0x17, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^68 */ 
{0x1e, 0x00, 0x25, 0x17, 0x91, 0x57, 0xc9, 0x3e, 0xc7, 0x3e,
0x23, 0xfa, 0x32, 0xaa, 0x4f, 0x9d, 0x3b, 0xda, 0x93, 0x4d,
0x8e, 0xe6, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^69 */ 
{0x1f, 0x00, 0x01, 0x72, 0xeb, 0xad, 0x6d, 0xdc, 0x73, 0xc8,
0x6d, 0x67, 0xc5, 0xfa, 0xa7, 0x1c, 0x24, 0x56, 0x89, 0xc1,
0x07, 0x95, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^70 */ 
{0x1f, 0x00, 0x0e, 0x7d, 0x34, 0xc6, 0x4a, 0x9c, 0x85, 0xd4,
0x46, 0x0d, 0xbb, 0xca, 0x87, 0x19, 0x6b, 0x61, 0x61, 0x8a,
0x4b, 0xd2, 0x16, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^71 */ 
{0x1f, 0x00, 0x90, 0xe4, 0x0f, 0xbe, 0xea, 0x1d, 0x3a, 0x4a,
0xbc, 0x89, 0x55, 0xe9, 0x46, 0xfe, 0x31, 0xcd, 0xcf, 0x66,
0xf6, 0x34, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^72 */ 
{0x20, 0x00, 0x05, 0xa8, 0xe8, 0x9d, 0x75, 0x25, 0x24, 0x46,
0xeb, 0x5d, 0x5d, 0x5b, 0x1c, 0xc5, 0xed, 0xf2, 0x0a, 0x1a,
0x05, 0x9e, 0x10, 0xca, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^73 */ 
{0x20, 0x00, 0x38, 0x99, 0x16, 0x26, 0x93, 0x73, 0x6a, 0xc5,
0x31, 0xa5, 0xa5, 0x8f, 0x1f, 0xbb, 0x4b, 0x74, 0x65, 0x04,
0x38, 0x2c, 0xa7, 0xe4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^74 */ 
{0x21, 0x00, 0x02, 0x35, 0xfa, 0xdd, 0x81, 0xc2, 0x82, 0x2b,
0xb3, 0xf0, 0x78, 0x77, 0x97, 0x3d, 0x50, 0xf2, 0x8b, 0xf2,
0x2a, 0x31, 0xbe, 0x8e, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^75 */ 
{0x21, 0x00, 0x16, 0x1b, 0xcc, 0xa7, 0x11, 0x99, 0x15, 0xb5,
0x07, 0x64, 0xb4, 0xab, 0xe8, 0x65, 0x29, 0x79, 0x77, 0x75,
0xa5, 0xf1, 0x71, 0x95, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00},  /* 10^76 */ 
{0x21, 0x00, 0xdd, 0x15, 0xfe, 0x86, 0xaf, 0xfa, 0xd9, 0x12,
0x49, 0xef, 0x0e, 0xb7, 0x13, 0xf3, 0x9e, 0xbe, 0xaa, 0x98,
0x7b, 0x6e, 0x6f, 0xd2, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00}  /* 10^77 */ 
}; /* size 78 * 34 */

/*
**	Before 2/94, two arrays of floating point values were defined here for 
**	arithmetic conversion routines in numeric.c.  Different versions of the
**	arrays were defined for VMS to support their smaller max floating point
**	values. Refs to these arrays were removed from numearry.h, comname.h
**	numeric.h and numeric.c in 2/94 because: the arrays were not portable
**	to MVS, Windows or VMS, Nume_Flt_Power_Array was used to make a 
**	check that was never necessary, and the Nume_Flt_256_Array was
**	not referenced at all by Common-Lib code. 
**
**	There were also VMS-specific definitions for NUME_MAXVMS_SCALE and
**	MAXVMSFLOAT that are no longer referenced, and have been removed.
**	(tchilder, 2/16/94)
*/

/*	the two -1's at the end of the array return impossible values in case
**	we accidently access them. 
*/
unsigned char Nume_Len_To_Prec[] =
{
 2, 4, 7, 9, 12, 14, 16, 19, 21, 24, 26, 28, 31, 33, 36, 38, 40, 43, 45, 48, 
 50, 52, 55, 57, 60, 62, 65, 67, 69, 72, 74, 77,-1,-1
}; /* size 33 + 2 */

unsigned char Nume_Prec_To_Len[] =
{ 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 6, 6, 7, 7, 8, 8,
  9, 9, 9, 10, 10, 11, 11, 11, 12, 12, 13, 13, 14, 14, 14, 15, 15, 
  16, 16, 16, 17, 17, 18, 18, 19, 19, 19, 20, 20, 21, 21, 21, 22, 22,
  23, 23, 24, 24, 24, 25, 25, 26, 26, 26, 27, 27, 28, 28, 28, 29, 29,
  30, 30, 31, 31, 31, 32, 32, 33, 33, 33}; /* size 78 */

#else /* NUMU_EARRY_DECLARE */

extern unsigned char Nume_Byte_Power_Array[NUME_MAXPREC + 1][NUME_MAXLEN + 1];
extern unsigned char  Nume_Len_To_Prec[NUME_MAXLEN + 2];
extern unsigned char  Nume_Prec_To_Len[NUME_MAXPREC + 1];


#endif /* NUMU_EARRY_DECLARE */

#if VMS
#define NUME_MAXFLT_PREC		38
#else /* VMS */
#define NUME_MAXFLT_PREC	NUME_MAXPREC
#endif /* VMS */

#endif /* __NUMEARRAY_H__ */
