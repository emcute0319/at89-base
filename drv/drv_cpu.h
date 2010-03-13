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


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_CPU_DelayMs
 * DESCRIPTION:
 *      CPU Delay ms driver.
 * PARAMETERS:
 *      vMs : How many ms to delay, maximum 65535 ms.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.26        PANDA         Create/Update
 *****************************************************************************/
void DRV_CPU_DelayMs(UINT16 vMs);

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
void DRV_CPU_DelayUs(UINT8  vUs);

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
void DRV_CPU_PreInit(void);


#endif /* __DRV_CPU_H */

