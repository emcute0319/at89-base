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
 *   drv_timer.c
 * DESCRIPTION:
 *   Timer driver.
 * HISTORY:
 *   2013.10.16         PANDA           Create/Update
 *
 *****************************************************************************/

#define _DRV_TIMER_INTERNAL_
#include "drv.h"

#if DRV_TIMER_SUPPORT

/* timer configuration table */
#define DECLARE_VECTOR_TIMER(_name, _tick, _callback, _desc)    { (_tick), (_callback) },
typedef void (SEG_CODE *TIMER_HANDLER_FUNC)(void);
static struct
{
    DRV_TIMER_COUNTER_T vReload;
    TIMER_HANDLER_FUNC  pHandler;
} CONST aTimerCfgTable[] =
{
    #include "cfg_hw_porting.h"
};
#undef  DECLARE_VECTOR_TIMER

/* timer real-time table */
#define DECLARE_VECTOR_TIMER(_name, _tick, _callback, _desc)    { DISABLE, (_tick), },
static struct
{
    DRV_TIMER_COUNTER_T bEnable  : 1;
    DRV_TIMER_COUNTER_T vCounter : 15;
} aTimerRTTable[] =
{
    #include "cfg_hw_porting.h"
};
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
void DRV_Timer_ISR(void)
{
    UINT8   vLoop;

    for (vLoop = 0; vLoop < COUNT_OF(aTimerRTTable); vLoop++)
    {
        if (aTimerRTTable[vLoop].bEnable == ENABLE)
        {
            if (--aTimerRTTable[vLoop].vCounter == 0)
            {
                /* timer reached */

                /* reload counter value for this timer */
                aTimerRTTable[vLoop].vCounter = aTimerCfgTable[vLoop].vReload;

                /* handle this timer */
                aTimerCfgTable[vLoop].pHandler();
            }
        }
    }
}


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
)
{
    /* reload counter value for this timer */
    aTimerRTTable[vName].vCounter = aTimerCfgTable[vName].vReload;

    /* set timer state */
    aTimerRTTable[vName].bEnable  = bState;
}

#endif

