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
 *   drv_swi.h
 * DESCRIPTION:
 *   Enhanced Software Interrupt Handler.
 * HISTORY:
 *   2013.10.16         PANDA           Create/Update
 *
 *****************************************************************************/

#ifndef __DRV_SWI_H
#define __DRV_SWI_H


#if DRV_SWI_SUPPORT

/* SWI porting part:
 *   here, we use Timer 2 interrupt to expand the SWI interrupt,
 *   to support as much as possible SWI interrupts.
 */
#define DRV_SWI_InterruptID                 VECTOR_ID_TIMER2
#define DRV_SWI_SetGlobalInterrupt()        do { TF2 = 1; } while (0)
#define DRV_SWI_ClearGlobalInterrupt()      do { TF2 = 0; } while (0)
#define DRV_SWI_GlobalEnableInterrupt()     do { T2CON = 0x00; ET2 = 1; } while (0)
#define DRV_SWI_GlobalDisableInterrupt()    do { T2CON = 0x00; ET2 = 0; } while (0)


/* SWI name definition */
#define SWI(n)        COMBINE(SWI_, n)
#define DECLARE_VECTOR_SWI(_name, _callback, _desc)     SWI(_name),
typedef enum
{
    DRV_SWI_NAME_START = -1,
    #include "cfg_hw_porting.h"
    DRV_SWI_NAME_END
} DRV_SWI_NAME_T;
#undef  DECLARE_VECTOR_SWI

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SWI_ISR
 * DESCRIPTION:
 *      SWI Interrupt Service Rountine.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2012.3.7          PANDA           Create/Update
 *****************************************************************************/
void DRV_SWI_ISR(void);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SWI_SetInterrupt
 * DESCRIPTION:
 *      Set SWI Interrupt Flag.
 * PARAMETERS:
 *      vName  : SWI Name;
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2012.3.7          PANDA           Create/Update
 *****************************************************************************/
void DRV_SWI_SetInterrupt(IN DRV_SWI_NAME_T vName);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SWI_SetState
 * DESCRIPTION:
 *      Set SWI State.
 * PARAMETERS:
 *      vName  : SWI Name;
 *      vState : ENABLE/DISABLE.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2012.3.7          PANDA           Create/Update
 *****************************************************************************/
void DRV_SWI_SetState
(
    IN DRV_SWI_NAME_T   vName,
    IN BOOL             bState
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SWI_Init
 * DESCRIPTION:
 *      SWI Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2012.3.7          PANDA           Create/Update
 *****************************************************************************/
void DRV_SWI_Init(void);

#endif


#endif /* __DRV_SWI_H */

