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
 *   drv_timer.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.1.27        panda.xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_TIMER_H
#define __DRV_TIMER_H


#define DRV_TIMER_SysTimerTick          1       /* ms */

/* System Timer (Timer 0) Reload Value:
 *   -->  CTC mode
 *   -->  periodic mode, 8-bit Reload
 *   -->  prescale: 64
 *   -->  source clock: system clock
 */
#define DRV_TIMER_SYSTIMER_RELOAD_VAL   \
            (((CPU_CORE_CLOCK *10 /1000 /64 /DRV_TIMER_SysTimerTick ) +5) /10 -1)
#if ( (DRV_TIMER_SYSTIMER_RELOAD_VAL > 0xFF) || (DRV_TIMER_SYSTIMER_RELOAD_VAL <= 0) )
  #error "Unsupported System Timer Initial Value for current System Clock!"
#endif


/* Reload System Timer Init Value */
#define DRV_TIMER_SysTimerReload()      /* do nothing */

/* clear Sysem Timer timeout flag */
#define DRV_TIMER_ClearSysTimerFlag()   /* do nothing */

/* Enable/Disable System Timer */
#define DRV_TIMER_SysTimer_Enable()                                     \
    do {                                                                \
        /* load System Timer Init value */                              \
        OCR0 = DRV_TIMER_SYSTIMER_RELOAD_VAL;                           \
        DRV_TIMER_SysTimerReload();                                     \
                                                                        \
        /* Clear TC0 interrupt flag,                                    \
         * to prevent generating an un-wanted interrupt.                \
         */                                                             \
        DRV_TIMER_ClearSysTimerFlag();                                  \
                                                                        \
        /* config TC0 to expected state */                              \
        TCCR0 = 0x0B;                                                   \
                                                                        \
        /* enable TC0 interrupt */                                      \
        TIMSK_OCIE0 = 1;                                                \
    } while (0)
#define DRV_TIMER_SysTimer_Disable()                                    \
    do {                                                                \
        /* disable TC0 interrupt */                                     \
        TIMSK_OCIE0 = 0;                                                \
    } while (0)


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_TIMER_Init
 * DESCRIPTION:
 *      Timer Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      Timer 0 is always used for System Tick-Timer;
 *      Timer 1 is always used for UART baudrate generator;
 *      Timer 2 is unused, if this CPU has Timer 2.
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
#define DRV_TIMER_Init()                                                \
    do {                                                                \
        /* enable System Timer */                                       \
        DRV_TIMER_SysTimer_Enable();                                    \
    } while (0)


#endif /* __DRV_TIMER_H */

