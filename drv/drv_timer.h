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


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_Timer_Init
 * DESCRIPTION:
 *      Timer Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      Timer 0 is always used for OS Tick-Timer;
 *      Timer 1 is always used for UART baudrate generator;
 *      Timer 2 is unused, if this CPU has Timer 2.
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
#define DRV_Timer_Init()        /* do nothing */


#endif /* __DRV_TIMER_H */

