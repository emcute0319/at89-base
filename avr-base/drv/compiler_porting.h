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
 *   compiler_porting.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2011.5.26        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __COMPILER_PORTING_H
#define __COMPILER_PORTING_H


#ifndef __ICCAVR__
 #error "Only supported IAR compiler yet!"
#endif

#include <ioavr.h>
#include <inavr.h>
#include <assert.h>


/* Converts a bit number into a byte value */
#define _BV(bit)        (1 << (bit))

#define CONST	        const __flash

#define _VECTOR(x)      COMBINE(x, _vect)

#define __nop()         __no_operation()
#define __crol(v, n)    do {                                            \
                            UINT8   i = (n);                            \
                                                                        \
                            while (i--)                                 \
                            {                                           \
                                (v) = ((v) << 1) | READ_BIT((v), 7);    \
                            }                                           \
                        } while (0)
#define __cror(v, n)    do {                                            \
                            UINT8   i = (n);                            \
                                                                        \
                            while (i--)                                 \
                            {                                           \
                                (v) = ((v) >> 1) | READ_BIT((v), 0);    \
                            }                                           \
                        } while (0)


#endif /* __COMPILER_PORTING_H */

