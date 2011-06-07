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
 *      DRV_VECTOR_Timer0
 * DESCRIPTION:
 *      Timer0 ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
INTERRUPT_USING(DRV_VECTOR_Timer0, VECTOR_ID_TIMER0, REG_GROUP_1)
{
    DRV_VECTOR_START(TIMER0);

    /* Reload System Timer Value */
    DRV_TIMER_SysTimerReload();

    /* Clear System Timer Interrupt Flag */
    DRV_TIMER_ClearSysTimerFlag();

    /* update System Tick */
    DRV_CPU_UpdateSysTick();

  #if DRV_LED_SUPPORT
    DRV_LED_ISR();  /* LED dynamic display ISR */
  #endif

    DRV_VECTOR_END(TIMER0);
}


/* uart always use Timer 1 as baudrate generator */
#if !DRV_UART_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_VECTOR_Timer1
 * DESCRIPTION:
 *      Timer1 ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
INTERRUPT(DRV_VECTOR_Timer1, VECTOR_ID_TIMER1)
{
    DRV_VECTOR_START(TIMER1);
    /* Add porting code here */
    DRV_VECTOR_END(TIMER1);
}

#else

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_VECTOR_UART
 * DESCRIPTION:
 *      UART ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
INTERRUPT(DRV_VECTOR_UART, VECTOR_ID_UART0)
{
    DRV_VECTOR_START(UART0);
    DRV_UART_ISR();
    DRV_VECTOR_END(UART0);
}

#endif


#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_VECTOR_Timer2
 * DESCRIPTION:
 *      Timer2 ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
INTERRUPT(DRV_VECTOR_Timer2, VECTOR_ID_TIMER2)
{
    DRV_VECTOR_START(TIMER2);
    /* Add porting code here */
    DRV_VECTOR_END(TIMER2);
}

#endif

