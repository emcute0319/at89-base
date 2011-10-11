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
 *   cfg_protothread.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.4.7        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#include "drv.h"
#include "app.h"


#ifdef DECLARE_PROTOTHREAD

/* Protothread Definition.
 *
 *   entry     : Thread entry; (if non-exist or unused, set to NULL)
 *   init_func : Thread init function; (if non-exist or unused, set to NULL)
 *   cookie    : Thread cookie; (unsupported yet)
 *   desc      : Thread description;
 *
 *   Note      :
 *      N/A
 */

/*                    entry              init_func       cookie   desc        */
DECLARE_PROTOTHREAD(thread_Idle_Entry, thread_Idle_Init,   NA,    "Idle Thread")
DECLARE_PROTOTHREAD(thread_App_Entry,  thread_App_Init,    NA,    "App Thread")
DECLARE_PROTOTHREAD(thread_Cli_Entry,  thread_Cli_Init,    NA,    "CLI Thread")

#endif

