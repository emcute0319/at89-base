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


#include "compiler_defs.h"

#if defined __C51__

#include <intrins.h>
#define _CROL(v, n)     do { (v) = _crol_((v), (n)); } while (0)
#define _CROR(v, n)     do { (v) = _cror_((v), (n)); } while (0)

#define FUNC_SEG_CODE   SEG_CODE

#elif defined __ICC8051__

#define _CROL(v, n)     do { (v) = (((v) << (n)) | ((v) >> (8*sizeof(v)-(n)))); } while (0)
#define _CROR(v, n)     do { (v) = (((v) >> (n)) | ((v) << (8*sizeof(v)-(n)))); } while (0)

#define FUNC_SEG_CODE   /* empty */

#else

#error "Unsupported compiler yet!"

#endif


#define CONST	        const SEG_CODE


/* macros defined in absacc.h (Keil C51) */
#define CBYTE  ((UINT8  volatile SEG_CODE  *) 0)  /*  8-bit data in  code area */
#define DBYTE  ((UINT8  volatile SEG_DATA  *) 0)  /*  8-bit data in  data area */
#define PBYTE  ((UINT8  volatile SEG_PDATA *) 0)  /*  8-bit data in pdata area */
#define XBYTE  ((UINT8  volatile SEG_XDATA *) 0)  /*  8-bit data in xdata area */
#define CWORD  ((UINT16 volatile SEG_CODE  *) 0)  /* 16-bit data in  code area */
#define DWORD  ((UINT16 volatile SEG_DATA  *) 0)  /* 16-bit data in  data area */
#define PWORD  ((UINT16 volatile SEG_PDATA *) 0)  /* 16-bit data in pdata area */
#define XWORD  ((UINT16 volatile SEG_XDATA *) 0)  /* 16-bit data in xdata area */
#define CDWORD ((UINT32 volatile SEG_CODE  *) 0)  /* 32-bit data in  code area */
#define DDWORD ((UINT32 volatile SEG_DATA  *) 0)  /* 32-bit data in  data area */
#define PDWORD ((UINT32 volatile SEG_PDATA *) 0)  /* 32-bit data in pdata area */
#define XDWORD ((UINT32 volatile SEG_XDATA *) 0)  /* 32-bit data in xdata area */


#endif /* __COMPILER_PORTING_H */

