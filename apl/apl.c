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
 *   apl.c
 * DESCRIPTION:
 *   Application Entry.
 * HISTORY:
 *   2010.2.1        panda.xiong         Create/Update
 *
*****************************************************************************/

#include "plf.h"
#include "apl.h"


static THREAD_FUNC thread_list[] =
{
    _thread_Idle,    /* Idle Thread */
};


#define THREAD_MAX_NO    COUNT_OF(thread_list)

/* thread TCB heap */
static PT_TCB   thread_tcb[THREAD_MAX_NO];

/******************************************************************************
 * FUNCTION NAME:
 *      APL_Entry
 * DESCRIPTION:
 *      Application Entry.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.2.1        panda.xiong         Create/Update
 *****************************************************************************/
void APL_Entry(void)
{
    UINT8   i;

    for (i=0; i<THREAD_MAX_NO; i++)
    {
        thread_list[i](&thread_tcb[i]);
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *      APL_Init
 * DESCRIPTION:
 *      Application Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.2.1        panda.xiong         Create/Update
 *****************************************************************************/
void APL_Init(void)
{
    UINT8   i;

    for (i=0; i<THREAD_MAX_NO; i++)
    {
        PT_INIT(&thread_tcb[i]);
    }
}

