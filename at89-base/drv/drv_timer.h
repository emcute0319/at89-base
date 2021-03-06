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
 *   -->  count up
 *   -->  periodic mode, 16-bit Reload
 *   -->  prescale: 1
 *   -->  source clock: system clock
 */
#define DRV_TIMER_SYSTIMER_RELOAD_VAL   \
            (65536L - (DRV_TIMER_SysTimerTick * CPU_CORE_CLOCK /1 /1000))
#if (DRV_TIMER_SYSTIMER_RELOAD_VAL < 0)
  #error "Unsupported System Timer Initial Value for current System Clock!"
#endif


/* Reload System Timer Init Value */
#define DRV_TIMER_SysTimerReload()                                      \
    do {                                                                \
        TL0 = (DRV_TIMER_SYSTIMER_RELOAD_VAL >> 0) & 0xFF;              \
        TH0 = (DRV_TIMER_SYSTIMER_RELOAD_VAL >> 8) & 0xFF;              \
    } while (0)

/* clear Sysem Timer timeout flag */
#define DRV_TIMER_ClearSysTimerFlag()   /* do nothing */

/* Enable/Disable System Timer */
#define DRV_TIMER_SysTimer_Enable()                                     \
    do {                                                                \
        /* 16-Bit Reload */                                             \
        TMOD &= ~0x0F;                                                  \
        TMOD |= 0x01;                                                   \
                                                                        \
        /* load System Timer Init value */                              \
        DRV_TIMER_SysTimerReload();                                     \
                                                                        \
        /* Clear Timer 0 interrupt flag,                                \
         * to prevent generating an un-wanted interrupt.                \
         */                                                             \
        DRV_TIMER_ClearSysTimerFlag();                                  \
                                                                        \
        TR0 = 1;    /* start Timer 0 */                                 \
        PT0 = 0;    /* force Timer 0 interrupt to low priority */       \
        ET0 = 1;    /* enable Timer 0 interrupt */                      \
    } while (0)
#define DRV_TIMER_SysTimer_Disable()                                    \
    do {                                                                \
        TR0 = 0;    /* stop Timer 0 */                                  \
        ET0 = 0;    /* disable Timer 0 interrupt */                     \
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


/* Simulated Timer Supporting */
#if DRV_TIMER_SUPPORT

/* timer counter format definition,
 * if want to support longer timer, change this type definition.
 */
typedef UINT16  DRV_TIMER_COUNTER_T;

#define TIMER_MS(x)     (DRV_TIMER_COUNTER_T)(((x)*1000UL+DRV_TIMER_SysTimerTick-1)/DRV_TIMER_SysTimerTick)

/* timer name definition */
#define TIMER(n)        COMBINE(TIMER_, n)
#define DECLARE_VECTOR_TIMER(_name, _tick, _callback, _desc)    TIMER(_name),
typedef enum
{
    DRV_TIMER_NAME_START = -1,
    #include "cfg_hw_porting.h"
    DRV_TIMER_NAME_END
} DRV_TIMER_NAME_T;
#undef  DECLARE_VECTOR_TIMER


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_Timer_ISR
 * DESCRIPTION:
 *      Simulated Timer Dispatcher ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2013.5.27        Panda.Xiong        Create/Update
 *****************************************************************************/
void DRV_Timer_ISR(void);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_Timer_SetState
 * DESCRIPTION:
 *      Set Simulated Timer State.
 * PARAMETERS:
 *      vName  : Timer Name;
 *      bState : ENABLE/DISABLE.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2013.5.27        Panda.Xiong        Create/Update
 *****************************************************************************/
void DRV_Timer_SetState
(
    IN DRV_TIMER_NAME_T vName,
    IN BOOL             bState
);

#endif


#endif /* __DRV_TIMER_H */

