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
 *   thread_app.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.4.7        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __THREAD_APP_H
#define __THREAD_APP_H


/******************************************************************************
 * FUNCTION NAME:
 *      thread_App_Entry
 * DESCRIPTION:
 *      App Thread Entry.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      PT_HANDLE
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.3.24        Panda.Xiong         Create/Update
 *****************************************************************************/
PT_HANDLE thread_App_Entry(PT_TCB *pt);

/******************************************************************************
 * FUNCTION NAME:
 *      thread_App_Init
 * DESCRIPTION:
 *      N/A
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.4.6        PANDA         Create/Update
 *****************************************************************************/
void thread_App_Init(void);


#endif /* __THREAD_APP_H */

