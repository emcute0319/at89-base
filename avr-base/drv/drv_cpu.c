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
 *      DRV_CPU_GetSysTick
 * DESCRIPTION:
 *      Get System Real-Time Tick.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.6.16        Panda.Xiong         Create/Update
 *****************************************************************************/
UINT32 DRV_CPU_GetSysTick(void)
{
    BOOL    bIntState;
    UINT32  vCurrentTick;

    bIntState = DRV_INT_LockTimerInterrupt(0);
	vCurrentTick = vSysTickCount;
    DRV_INT_UnlockTimerInterrupt(0, bIntState);

    return vCurrentTick;
}

