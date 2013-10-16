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
 *   drv_led_sim.c
 * DESCRIPTION:
 *   Simulated LED Dynamic Display Driver.
 * HISTORY:
 *   2011.6.7        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#define _DRV_LED_SIM_INTERNAL_
#include "drv.h"

#if DRV_LED_Sim_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_LED_Sim_ISR
 * DESCRIPTION:
 *      Simulated LED Interrupt Service Routine Entry.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.7        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_LED_Sim_ISR(void)
{
    static UINT8 vCurrentSelLed = 0;

    DRV_LED_SIM_SEL_LED(vCurrentSelLed);
    DRV_LED_SIM_SET_DATA(aLedDisBuf[vCurrentSelLed]);

    if (vCurrentSelLed++ >= COUNT_OF(aLedDisBuf))
    {
        vCurrentSelLed = 0;
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_LED_Sim_Init
 * DESCRIPTION:
 *      Simulated LED Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.7        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_LED_Sim_Init(void)
{
    /* Select none LED at power-on */
    DRV_LED_SIM_SEL_LED(_EMPTY);

    /* Enable LED Dynamic Display Timer */
    DRV_Timer_SetState(TIMER(Timer_LED_Sim), ENABLE);
}

#endif

