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
 *   drv_cpu.c
 * DESCRIPTION:
 *   CPU Driver.
 * HISTORY:
 *   2010.1.26        PANDA         Create/Update
 *
*****************************************************************************/

#define _DRV_CPU_INTERNAL_

#include "drv.h"


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_CPU_DelayUs
 * DESCRIPTION:
 *      CPU Delay us driver.
 * PARAMETERS:
 *      vUs : How many us to delay.
 * RETURN:
 *      N/A
 * NOTES:
 *      Currently, only support 14~255us.
 *      And, this delay may be not very accurately.
 * HISTORY:
 *      2010.1.26        PANDA         Create/Update
 *****************************************************************************/
void DRV_CPU_DelayUs(UINT8  vUs)
{
#if ( CPU_CORE_CLOCK == 1000000UL)

    /* 1us = 1 Tick */

    /* 10us for fixed instruction of this API,
     *  2us for calling "MOV R7, #xxH" instruction.
     */
    vUs -= (10+2);
    vUs /= 2;

    while (--vUs)
    {}

#elif ( CPU_CORE_CLOCK == 2000000UL)

    /* 1us = 2 Tick */

    /* 4us for fixed instruction of this API,
     * 1us for calling "MOV R7, #xxH" instruction.
     */
    vUs -= (4+1);

    while (--vUs)
    {}

#else
 #error "Unsupported CPU Core Clock yet!"
#endif
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_CPU_PreInit
 * DESCRIPTION:
 *      CPU Pre-Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.28        panda.xiong         Create/Update
 *****************************************************************************/
void DRV_CPU_PreInit(void)
{
    IE   = 0x00;
    IP   = 0x00;
    PCON = 0x00;
    TMOD = 0x00;
    TCON = 0x00;

    PSW  = 0x00;

    P1   = 0xFF;
    P3   = 0xFF;

#if ( !defined(_CPU_AT89C2051_) && !defined(_CPU_AT89C4051_) )
    P0   = 0xFF;
    P2   = 0xFF;
#endif

#if ( defined(_CPU_AT89S51_) || defined(_CPU_AT89S52_) )

    SET_BIT(AUXR, DISALE_BIT);  /* Disable ALE output               */
	CLR_BIT(AUXR, DISRTO_BIT);  /* Enable WDT reset MCU             */
	SET_BIT(AUXR, WDIDLE_BIT);  /* WDT halts counting in IDLE mode  */

    CLR_BIT(AUXR1, DPS_BIT);    /* Selects DPTR Registers DP0L,DP0H */

#endif

    /* reset CPU tick counter */
    vSysTickCount = 0;
}

