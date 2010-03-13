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
 *   os_rtxtiny.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.1.27        panda.xiong         Create/Update
 *
*****************************************************************************/

#ifndef __OS_RTXTINY_H
#define __OS_RTXTINY_H


#define OS_TICK_TIME                5   /* ms */


#ifndef __asm

#if OS_RtxTiny_SUPPORT

#include <rtx_tiny.h>

#define OS_TASK_Create(id)              os_create_task(id)
#define OS_TASK_Delete(id)              os_delete_task(id)
#define OS_TASK_SleepMs(ms)             os_wait(K_TMO, (ms)/OS_TICK_TIME, 0)
#define OS_TASK_SleepSec(sec)           OS_TASK_SleepMs(1000 * (sec))
#define OS_TASK_IsrSetReady(task_id)    isr_set_ready(task_id)
#define OS_TASK_SetReady(task_id)       os_set_ready(task_id)
#define OS_TASK_ForceSwitch()           os_swich_task()

#define OS_SIG_Wait()                   os_wait(K_SIG, 0, 0)
#define OS_SIG_TaskSend(task_id)        os_send_signal(task_id)
#define OS_SIG_IsrSend(task_id)         isr_send_signal(task_id)
#define OS_SIG_Clear(task_id)           os_clear_signal(task_id)

#define OS_TASK_ID(_n)                  _task_ _n

#else

#define OS_TASK_Create(id)              /* do nothing */
#define OS_TASK_Delete(id)              /* do nothing */
#define OS_TASK_SleepMs(ms)             DRV_CPU_DelayMs(ms)
#define OS_TASK_SleepSec(sec)           OS_TASK_SleepMs(1000 * (sec))
#define OS_TASK_IsrSetReady(task_id)    /* do nothing */
#define OS_TASK_SetReady(task_id)       /* do nothing */
#define OS_TASK_ForceSwitch()           /* do nothing */

#define OS_SIG_Wait()                   /* do nothing */
#define OS_SIG_TaskSend(task_id)        /* do nothing */
#define OS_SIG_IsrSend(task_id)         /* do nothing */
#define OS_SIG_Clear(task_id)           /* do nothing */

#define OS_TASK_ID(_n)                  /* empty */

#endif

#define OS_Enter_Critical()             DRV_INT_GlobalDisableInterrupt()
#define OS_Exit_Critical()              DRV_INT_GlobalEnableInterrupt()


#else


#include <cfg_hw_def.h>

/******************************************************************************
 *
 * RTX-51 TINY Hardware-Timer
 * ==========================
 *
 * With the following EQU statements the initialization of the RTX-51 TINY
 * Hardware-Timer can be defined (RTX-51 TINY uses the 8051 Timer 0 for
 * controlling RTX-51 software timers).
 */

/* Define the register bank used for the timer interrupt */
#define INT_REGBANK     1   /* Register Bank for RTX-51 Tiny */

/* Define Hardware-Timer Tick Time, in 8051 machine cycles */
#define INT_CLOCK       4608

/* Define Round-Robin Timeout in Hardware-Timer ticks.
 * =0, disables Round-Robin Task Switching.
 */
#define TIMESHARING     OS_TICK_TIME

/* Long User Interrupt Routines: set to 1 if your application contains
 *  user interrupt functions that may take longer than a hardware timer
 *  interval for execution.
 * =0, user interrupts execute fast;
 * =1, user interrupts take long execution times.
 */
#define LONG_USR_INTR   0


/******************************************************************************
 *
 * USER CODE FOR 8051 HARDWARE TIMER INTERRUPT
 * ===========================================
 *
 * The following macro defines the code executed on a hardware timer interrupt.
 *
 * Define instructions executed on a hardware timer interrupt.
 * Empty Macro by default.
 */
#if DRV_WATCHDOG_SUPPORT
 EXTRN  CODE(DRV_Watchdog_Kick)
#endif

HW_TIMER_CODE	MACRO
  #if DRV_WATCHDOG_SUPPORT
    LCALL DRV_Watchdog_Kick
  #endif

 	RETI
ENDM


/*****************************************************************************
 *
 * CODE BANKING SUPPORT
 * ====================
 *
 * The following EQU statement controls the code banking support for RTX51 TINY.
 *
 * Enable or disable code banking support:
 *   =0, application uses no code banking; (default)
 *   =1, application uses code banking.
 */
#define CODE_BANKING    0


/*****************************************************************************
 *
 * RTX-51 TINY Stack Space
 * =======================
 *
 * The following EQU statements defines the size of the internal RAM used
 * for stack area and the minimum free space on the stack.  A macro defines
 * the code executed when there is there is not enough free stack on the
 * CPU stack.
 */

/* Define the highest RAM address used for CPU stack */
#define RAMTOP      0x7F    /* default is address (256-1) */

/* default is 20 bytes free space on stack
 * the value 0 disables stack checking.
 */
#define FREE_STACK  20

STACK_ERROR	MACRO
	CLR     EA  /* disable interrupts */
	SJMP    $   /* endless loop if stack space is exhausted */
ENDM


/*****************************************************************************
 *
 * 8051 CPU IDLE CODE
 * ==================
 *
 * Many 8051 devices provide an IDLE MODE that reduces power consumption and
 *  EMC.  The following macro defines the code executed when there is no
 *  ready task in the system.  The code must set the CPU into an IDLE MODE
 *  that stops instruction execution until an 8051 hardware interrupt occurs.
 */

/* Disable or Enable CPU_IDLE CODE:
 *  =0, CPU_IDLE MACRO is not inserted;
 *  =1, CPU_IDLE MACRO is executed.
 */
#define CPU_IDLE_CODE   1

/* Power Control SFR on most 8051 devices */
#define PCON            0x87

/* Stop CPU execution until hardware interrupt;
 * executed when there is no active task in the system.
 */
CPU_IDLE	MACRO
	ORL	PCON,#1     /* set 8051 CPU to IDLE */
ENDM


#endif


#endif /* __OS_RTXTINY_H */

