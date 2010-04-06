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
 *   pt_api.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.4.6        PANDA         Create/Update
 *
*****************************************************************************/

#ifndef __PT_API_H
#define __PT_API_H


#include "drv.h"
#include "pt-sem.h"

typedef char            PT_HANDLE;
typedef struct pt       PT_TCB;
typedef struct pt_sem   PT_SCB;

#define THREAD_VOID     PT_TCB  *tcb
#define THREAD_START    PT_BEGIN(tcb)
#define THREAD_END      PT_END(tcb)

/* sleep millisecond */
#define THREAD_SLEEP_MS(ms)                                                 \
    do {                                                                    \
        static unsigned long end_tick;                                      \
        end_tick = (DRV_CPU_GetSysTick() + (ms)/DRV_TIMER_SysTimerTick);    \
        PT_WAIT_WHILE(tcb, (DRV_CPU_GetSysTick() < end_tick));              \
    } while (0)

typedef PT_HANDLE (*THREAD_FUNC)(PT_TCB *tcb);
typedef void (*THREAD_INIT_FUNC)(void);


#endif /* __PT_API_H */

