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
 *   drv_vector.c
 * DESCRIPTION:
 *   Interrupt Service Routine.
 * HISTORY:
 *   2010.1.27        panda.xiong         Create/Update
 *
*****************************************************************************/

#include "drv.h"


#define DRV_VECTOR_START(_int_name)    /* do nothing */
#define DRV_VECTOR_END(_int_name)      /* do nothing */


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_VECTOR_T0_Overflow
 * DESCRIPTION:
 *      Timer0 overflow ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
#pragma vector=VECTOR_ID(TIMER0_OVF)
__interrupt void DRV_VECTOR_T0_Overflow(void)
{
    DRV_VECTOR_START(TIMER0);

    /* Reload System Timer Value */
    /* TODO: DRV_TIMER_SysTimerReload(); */

    /* Clear System Timer Interrupt Flag */
    DRV_TIMER_ClearSysTimerFlag();

    /* update System Tick */
    DRV_CPU_UpdateSysTick();

  #if DRV_LED_SUPPORT
    DRV_LED_ISR();  /* LED driver ISR */
  #endif

    DRV_VECTOR_END(TIMER0);
}

