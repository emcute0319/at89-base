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
 *   main.c
 * DESCRIPTION:
 *   System Startup Entry.
 * HISTORY:
 *   2010.1.29        panda.xiong         Create/Update
 *
*****************************************************************************/

#include "drv.h"
#include "apl.h"


/******************************************************************************
 * FUNCTION NAME:
 *      _system_PreInit
 * DESCRIPTION:
 *      System Pre-Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.28        panda.xiong         Create/Update
 *****************************************************************************/
#define _system_PreInit()   DRV_PreInit()


/******************************************************************************
 * FUNCTION NAME:
 *      _system_Init
 * DESCRIPTION:
 *      System init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.6.11        Panda.Xiong         Create/Update
 *****************************************************************************/
#define _system_Init()                      \
    do {                                    \
        DRV_Init();     /* Driver Init */   \
        OS_Init();      /* OS     Init */   \
        APL_Init();     /* App    Init */   \
} while (0)


/******************************************************************************
 * FUNCTION NAME:
 *      _system_Start
 * DESCRIPTION:
 *      Start System, never return.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.7.2        Panda.Xiong         Create/Update
 *****************************************************************************/
static void _system_Start(void)
{
    /* Fixup Init */
    DRV_FixupInit();

    /* Globally enable Interrupt */
    DRV_INT_GlobalEnableInterrupt();

    /* Start OS, and never return back */
    OS_Start();
}


/******************************************************************************
 * FUNCTION NAME:
 *      main
 * DESCRIPTION:
 *      System entry of C file.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.4.10        Panda.Xiong         Create/Update
 *****************************************************************************/
void main(void)
{
    /* Pre-Init system */
    _system_PreInit();

    /* init system */
	_system_Init();

    /* start system, and never return back */
    _system_Start();

    /* never reach here */
    return;
}

