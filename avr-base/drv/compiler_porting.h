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

#define CONST_FLASH     const __flash
#define CONST_EEPROM    const __eeprom
#define CONST           CONST_FLASH

/* interrupt definition */
#define _PPTOSTR_(x)                    #x
#define _PPARAM_(vec)                   _PPTOSTR_(vector=vec##_vect)
#define INTERRUPT(name, vector)         _Pragma(_PPARAM_(vector)) __interrupt void name(void)
#define INTERRUPT_PROTO(name, vector)   INTERRUPT(name, vector)


#define NOP()           __no_operation()
#define CROL(v, n)      do { (v) = (((v) << (n)) | ((v) >> (8*sizeof(v)-(n)))); } while (0)
#define CROR(v, n)      do { (v) = (((v) >> (n)) | ((v) << (8*sizeof(v)-(n)))); } while (0)


#endif /* __COMPILER_PORTING_H */

