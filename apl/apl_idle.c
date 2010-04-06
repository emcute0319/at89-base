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
 *   apl_idle.c
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.4.6        PANDA         Create/Update
 *
*****************************************************************************/

#include "apl.h"


/******************************************************************************
 * FUNCTION NAME:
 *      _thread_Idle
 * DESCRIPTION:
 *      Idle Thread.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      PT_HANDLE
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.3.24        Panda.Xiong         Create/Update
 *****************************************************************************/
PT_HANDLE _thread_Idle(THREAD_VOID)
{
    THREAD_START;

    while (1)
    {
        /* update device status, at every 500ms */
        THREAD_SLEEP_MS(500);
    }

    THREAD_END;
}

