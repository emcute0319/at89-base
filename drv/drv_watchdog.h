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
 *   drv_watchdog.h
 * DESCRIPTION:
 *   Watchdog Driver.
 * HISTORY:
 *   2010.1.27        panda.xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_WATCHDOG_H
#define __DRV_WATCHDOG_H


#if ( defined(_CPU_AT89S51_) || defined(_CPU_AT89S52_) )
 #define DRV_Watchdog_Enable()   do { WDTRST = 0x1E; WDTRST = 0xE1; } while (0)
 #define DRV_Watchdog_Disable()  /* the Watchdog cannot be disabled, till CPU reset */
 #define DRV_Watchdog_Kick()     DRV_Watchdog_Enable()
#else
 #define DRV_Watchdog_Enable()   /* do nothing */
 #define DRV_Watchdog_Disable()  /* do nothing */
 #define DRV_Watchdog_Kick()     /* do nothing */
#endif


#endif /* __DRV_WATCHDOG_H */

