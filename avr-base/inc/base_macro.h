/******************************************************************************
 *
 * (C) Copyright 2007-2010
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *   MA 02111-1307 USA
 *
 * FILE NAME:
 *   base_macro.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.1.26        PANDA         Create/Update
 *
*****************************************************************************/

#ifndef __BASE_MACRO_H
#define __BASE_MACRO_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#define COMBINE(a, b)   a##b

#define KB(x)           ((x)*1024)
#define MB(x)           ((x)*1024*1024)


/* Calculate the total element of an array.
 *
 * e.g:
 *   int  array[100];
 *  To get the total element of (array), just use COUNT_OF(array).
 *   acturally, the total element in this sample is 100.
 */
#define COUNT_OF(n)     (SINT32)(sizeof(n) / sizeof((n)[0]))

/* calculate the Byte Offset of member in struct.
 *
 * e.g:
 *  typedef struct
 *  {
 *      int  a;
 *      int  b;
 *      char c;
 *  } TYPE_S;
 *
 * To get the Byte Offset of (c) in TYPE_S, just use offsetof(TYPE_S, c).
 *  acturally, the offset in this sample is 8.
 */
#undef offsetof
#ifdef __compiler_offsetof
 #define offsetof(TYPE, MEMBER)  __compiler_offsetof(TYPE, MEMBER)
#else
 #define offsetof(TYPE, MEMBER)  ((size_t) &((TYPE *)0)->MEMBER)
#endif

/* remove warning */
#define NO_WARNING(x)       do { if (x) {} } while (0)

#ifndef MIN
 #define MIN(a, b)          (((a)<(b))?(a):(b))
#endif

#ifndef MAX
 #define MAX(a, b)          (((a)>(b))?(a):(b))
#endif

/* get the absolute value */
#define ABS(x)              (((x) >= 0) ? (x) : -(x))

/* bit operation */
#define SET_BIT(n, b)       do { (n) |= (0x1 << (b));  } while (0)
#define CLR_BIT(n, b)       do { (n) &= ~(0x1 << (b)); } while (0)
#define READ_BIT(n, b)      ((BOOL)(((n) >> (b)) & 0x1))
#define REVERSE_BIT(n, b)   do { (n) ^= (0x1 << (b)); } while (0)
#define WRITE_BIT(n, b, v)  do { (n) = ((n) & ~(0x1 << (b))) | ((UINT32)(v) << (b)); } while (0)


/* Get mask.
 *
 * e.g:
 *   if get 10-bit mask started from bit0, it will return 0x3FF.
 *   if get 10-bit mask started from bit5, it will return 0x7FE0.
 *
 * Note:
 *   1. the range of (start) : 0 <= start <= 31
 *      the range of (n)     : 0 <= n <= 31
 *   2. by default, this will return 32-bit mask, if only need 8-bit or 16-bit mask,
 *      you should limit the result like this:
 *         8-bit :  (UINT8)(GET_MASK(0, 5))  --- Start from bit0, occupy 5 bits;
 *        16-bit : (UINT16)(GET_MASK(3, 7))  --- Start from bit3, occupy 7 bits;
 */
#define GET_MASK(start, n)  ((~(0xFFFFFFFFUL << (UINT8)(n))) << (UINT8)(start))


/* operate memory as big-endian */
#define SET_BE_16(buf, val)                                                     \
    do {                                                                        \
        ((UINT8 *)(buf))[0] = (UINT8)(((UINT16)(val) >>  8) & 0xFF);            \
        ((UINT8 *)(buf))[1] = (UINT8)(((UINT16)(val) >>  0) & 0xFF);            \
    } while (0)

#define GET_BE_16(buf)    (UINT16)(  ((UINT16)((const UINT8 *)(buf))[0] <<  8)  \
                                   | ((UINT16)((const UINT8 *)(buf))[1] <<  0))

#define SET_BE_32(buf, val)                                                     \
    do {                                                                        \
        ((UINT8 *)(buf))[0] = (UINT8)(((UINT32)(val) >> 24) & 0xFF);            \
        ((UINT8 *)(buf))[1] = (UINT8)(((UINT32)(val) >> 16) & 0xFF);            \
        ((UINT8 *)(buf))[2] = (UINT8)(((UINT32)(val) >>  8) & 0xFF);            \
        ((UINT8 *)(buf))[3] = (UINT8)(((UINT32)(val) >>  0) & 0xFF);            \
    } while (0)

#define GET_BE_32(buf)    (  ((UINT32)((const UINT8 *)(buf))[0] << 24)          \
                           | ((UINT32)((const UINT8 *)(buf))[1] << 16)          \
                           | ((UINT32)((const UINT8 *)(buf))[2] <<  8)          \
                           | ((UINT32)((const UINT8 *)(buf))[3] <<  0))


/* operate memory as little-endian */
#define SET_LE_16(buf, val)                                                     \
    do {                                                                        \
        ((UINT8 *)(buf))[1] = (UINT8)(((UINT16)(val) >>  8) & 0xFF);            \
        ((UINT8 *)(buf))[0] = (UINT8)(((UINT16)(val) >>  0) & 0xFF);            \
    } while (0)

#define GET_LE_16(buf)    (UINT16)(  ((UINT16)((const UINT8 *)(buf))[1] <<  8)  \
                                   | ((UINT16)((const UINT8 *)(buf))[0] <<  0))

#define SET_LE_32(buf, val)                                                     \
    do {                                                                        \
        ((UINT8 *)(buf))[3] = (UINT8)(((UINT32)(val) >> 24) & 0xFF);            \
        ((UINT8 *)(buf))[2] = (UINT8)(((UINT32)(val) >> 16) & 0xFF);            \
        ((UINT8 *)(buf))[1] = (UINT8)(((UINT32)(val) >>  8) & 0xFF);            \
        ((UINT8 *)(buf))[0] = (UINT8)(((UINT32)(val) >>  0) & 0xFF);            \
    } while (0)

#define GET_LE_32(buf)    (  ((UINT32)((const UINT8 *)(buf))[3] << 24)          \
                           | ((UINT32)((const UINT8 *)(buf))[2] << 16)          \
                           | ((UINT32)((const UINT8 *)(buf))[1] <<  8)          \
                           | ((UINT32)((const UINT8 *)(buf))[0] <<  0))


/* Swap data:  Big-Endian  <-->  Little-Endian */
#define SWAP_16(x)     (UINT16)(  (((UINT16)(x) >> 8) & 0x00FF)                 \
                                | (((UINT16)(x) << 8) & 0xFF00))

#define SWAP_32(x)     (  (((UINT32)(x) >> 24) & 0x000000FFUL)                  \
                        | (((UINT32)(x) >>  8) & 0x0000FF00UL)                  \
                        | (((UINT32)(x) <<  8) & 0x00FF0000UL)                  \
                        | (((UINT32)(x) << 24) & 0xFF000000UL))


#endif /* __BASE_MACRO_H */

