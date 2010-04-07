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
 *   protothread.c
 * DESCRIPTION:
 *   Application Entry.
 * HISTORY:
 *   2010.2.1        panda.xiong         Create/Update
 *
*****************************************************************************/

#include "protothread.h"


/* Protothread Thread List */
#define DECLARE_PROTOTHREAD(entry, init_func, cookie, desc)   { entry, init_func },
static struct
{
    PT_FUNC         p_thread;
    PT_INIT_FUNC    p_init;
} const thread_list[] =
{
    #include "cfg_protothread.h"
};
#undef DECLARE_PROTOTHREAD


/* thread TCB heap */
#define THREAD_MAX_NO    COUNT_OF(thread_list)
static PT_TCB   thread_tcb[THREAD_MAX_NO];

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
void PT_Start(void)
{
    while (1)
    {
        UINT8   i;

        for (i=0; i<THREAD_MAX_NO; i++)
        {
            if (thread_list[i].p_thread != NULL)
            {
                thread_list[i].p_thread(&thread_tcb[i]);
            }
        }
    }
}


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
void PT_Init(void)
{
    UINT8   i;

    for (i=0; i<THREAD_MAX_NO; i++)
    {
        PT_INIT(&thread_tcb[i]);

        if (thread_list[i].p_init != NULL)
        {
            thread_list[i].p_init();
        }
    }
}

