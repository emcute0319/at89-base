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
 *   startup.S
 * DESCRIPTION:
 *   System power-on start entry.
 * HISTORY:
 *   2010.3.23        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#define __asm
#include "version.h"


/******************************************************************************
 *  User-defined Power-On Initialization of Memory
 *****************************************************************************/

/* IDATA memory size definition.
 *  Note:
 *   1. The absolute start-address of IDATA memory is always 0;
 *   2. The IDATA space overlaps physically the DATA and BIT areas.
 */
#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
 #define IDATA_LEN      0x0100  /* The length of IDATA memory in Bytes */
#else
 #define IDATA_LEN      0x0080  /* The length of IDATA memory in Bytes */
#endif

/* PDATA memory size definition */
#define PDATA_START     0x0000
#define PDATA_LEN       0x0000  /* The length of PDATA memory in Bytes */

/* XDATA memory size definition */
#define XDATA_START     0x0000
#define XDATA_LEN       0x0000  /* The length of XDATA memory in Bytes */


/* Told compiler:
 *  ?STACK should be stored into idata area.
 *
 *  But, the Keil Compiler may place it into data area,
 *   from the unused data start address,
 *   to make sure the stacking always use the deepest stack depth.
 */
?STACK      SEGMENT   IDATA
RSEG    ?STACK
    DS      1


/* told compiler that this function is an external API */
EXTRN CODE (?C_START)


/******************************************************************************
 * CPU power on entry
 *****************************************************************************/
    CSEG    AT  0x0000
PUBLIC  ?C_STARTUP
?C_STARTUP:
    LJMP    _handler_reset


/* These are used for Firmware Signature,
 * do not try to remove it!
 */
    CSEG   AT  FW_SIG_OFFSET
PUBLIC __fw_sig
__fw_sig:
    DB  'CPU:', CPU_TYPE,   0x20
    DB  'FW:',  FW_VERSION, 0x00


/* Told compiler:
 *  ?C_C51STARTUP should be stored into code area,
 *   and it must be put here (Including keil library)
 *
 * TODO : This need to be checked later!!!
 */
?C_C51STARTUP   SEGMENT   CODE
RSEG    ?C_C51STARTUP


/******************************************************************************
 * system start from here
 *****************************************************************************/
_handler_reset:

/* check need to clear IDATA to 0 */
#if (IDATA_LEN != 0)

    MOV     R0, #(IDATA_LEN - 1)

  idata_loop:
    MOV     @R0, A
    DJNZ    R0,  idata_loop

#endif


/* check need to clear PDATA to 0 */
#if (PDATA_LEN != 0)

    MOV     R0, #(PDATA_START)      /* PDATA start  */
    MOV     R7, #(PDATA_LEN - 1)    /* PDATA length */

  pdata_loop:
    MOVX    @R0, A
    INC     R0
    DJNZ    R7,  pdata_loop

    /* add this, to clean the last Byte PDATA */
    MOVX    @R0, A

#endif


/* check need to clear XDATA to 0 */
#if (XDATA_LEN != 0)

    MOV     DPTR, #(XDATA_START)
    MOV     R7,   #(((XDATA_LEN - 1) >> 0) & 0xFF)
    MOV     R6,   #((((XDATA_LEN - 1) >> 8) & 0xFF) + 1)

  xdata_loop:
    MOVX    @DPTR, A
    INC     DPTR
    DJNZ    R7, xdata_loop
    DJNZ    R6, xdata_loop

    /* add this, to clean the last Byte XDATA */
    MOVX    @DPTR, A

#endif


/* Init Stack Pointer */
    MOV     SP, #(?STACK - 1)


/* Jump to main;
 *  before jump to main, the keil will call the internal library,
 *  to init static values.
 */
    LJMP    ?C_START


END

