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
 *   os_api.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.4.7        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __OS_API_H
#define __OS_API_H


#include "pt-sem.h"


typedef char            OS_HANDLE;
typedef struct pt       OS_TCB;
typedef struct pt_sem   OS_SCB;

#define OS_THREAD_PARAM OS_TCB  *tcb
#define OS_THREAD_START PT_BEGIN(tcb)
#define OS_THREAD_END   PT_END(tcb)

/* sleep millisecond */
#define OS_THREAD_SLEEP_MS(ms)                                              \
    do {                                                                    \
        static unsigned long end_tick;                                      \
        end_tick = (DRV_CPU_GetSysTick() + (ms)/DRV_TIMER_SysTimerTick);    \
        PT_WAIT_WHILE(tcb, (DRV_CPU_GetSysTick() < end_tick));              \
    } while (0)

typedef OS_HANDLE (*OS_THREAD_FUNC)(OS_TCB *tcb);
typedef void (*OS_THREAD_INIT_FUNC)(void);


#include "cfg_os_thread.h"

/******************************************************************************
 * FUNCTION NAME:
 *      OS_Start
 * DESCRIPTION:
 *      OS Start Entry.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.2.1        panda.xiong         Create/Update
 *****************************************************************************/
void OS_Start(void);

/******************************************************************************
 * FUNCTION NAME:
 *      OS_Init
 * DESCRIPTION:
 *      OS Init, including Application Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.2.1        panda.xiong         Create/Update
 *****************************************************************************/
void OS_Init(void);


#endif /* __OS_API_H */

