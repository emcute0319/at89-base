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
 *   drv_cpu.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.1.26        PANDA         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_CPU_H
#define __DRV_CPU_H


#ifdef _DRV_CPU_INTERNAL_
 #define _DRV_CPU_EXTERN_   /* nothing */
#else
 #define _DRV_CPU_EXTERN_   extern
#endif


_DRV_CPU_EXTERN_ volatile UINT32    vSysTickCount;

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
UINT32 DRV_CPU_GetSysTick(void);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_CPU_UpdateSysTick
 * DESCRIPTION:
 *      Update System Tick, every time update 1 tick.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.6.16        Panda.Xiong         Create/Update
 *****************************************************************************/
#define DRV_CPU_UpdateSysTick()     do { vSysTickCount++; } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_CPU_DelayUs
 * DESCRIPTION:
 *      CPU Delay us driver.
 * PARAMETERS:
 *      us : How many us to delay.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.26        PANDA         Create/Update
 *****************************************************************************/
#define DRV_CPU_DelayUs(us)     __delay_cycles((float)(us) * ((float)CPU_CORE_CLOCK / 1000000UL))

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
#define DRV_CPU_PreInit()                                                   \
    do {                                                                    \
    	/* globally disable all interrupts */                               \
    	DRV_INT_GlobalDisableInterrupt();                                   \
                                                                            \
        /* reset CPU tick counter */                                        \
        vSysTickCount = 0;                                                  \
    } while (0)


#endif /* __DRV_CPU_H */

