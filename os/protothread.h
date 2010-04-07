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
 *   protothread.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.4.7        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __PROTOTHREAD_H
#define __PROTOTHREAD_H


#include "pt-sem.h"

typedef char            PT_HANDLE;
typedef struct pt       PT_TCB;
typedef struct pt_sem   PT_SCB;

#include "cfg_protothread.h"


/* sleep millisecond */
#define PT_SLEEP_MS(pt, ms)                                                 \
    do {                                                                    \
        static unsigned long end_tick;                                      \
        end_tick = (DRV_CPU_GetSysTick() + (ms)/DRV_TIMER_SysTimerTick);    \
        PT_WAIT_WHILE(pt, (DRV_CPU_GetSysTick() < end_tick));               \
    } while (0)

typedef PT_HANDLE (SEG_CODE *PT_FUNC)(PT_TCB *pt);
typedef void (SEG_CODE *PT_INIT_FUNC)(void);


/******************************************************************************
 * FUNCTION NAME:
 *      PT_Start
 * DESCRIPTION:
 *      Protothread Start Entry.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.2.1        panda.xiong         Create/Update
 *****************************************************************************/
void PT_Start(void);

/******************************************************************************
 * FUNCTION NAME:
 *      PT_Init
 * DESCRIPTION:
 *      Protothread Init, including Application Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.2.1        panda.xiong         Create/Update
 *****************************************************************************/
void PT_Init(void);


#endif /* __PROTOTHREAD_H */

