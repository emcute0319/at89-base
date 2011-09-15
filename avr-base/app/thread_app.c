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
 *   thread_app.c
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.4.6        PANDA         Create/Update
 *
*****************************************************************************/

#include "protothread.h"


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
PT_HANDLE thread_App_Entry(PT_TCB *pt)
{
    PT_BEGIN(pt);

    for (;;)
    {
        static UINT32   vElapsedTime = 0;

      #if DRV_UART_SUPPORT
        DRV_UART_Printf("\n\r thread_App_Entry: Elapsed Time -> %d:%d:%d ...",
                        (UINT16)(vElapsedTime/3600),
                        (UINT16)(vElapsedTime/60%60),
                        (UINT16)(vElapsedTime%60));
      #endif

      #if DRV_UART_SUPPORT && DRV_TEMP_SUPPORT
      {
        SINT16  vTemp    = DRV_Temp_GetTemp();
        BOOL    bSuccess = READ_BIT(vTemp, 15);

        WRITE_BIT(vTemp, 15, bSuccess);
        if (!bSuccess)
        {
            DRV_UART_Printf("\r %s(line%d): Current Temperature: %d (degree) ...",
                            __FILE__, __LINE__,
                            vTemp);
        }
      }
      #endif

      #if DRV_LED_SUPPORT
        DRV_LED_SetLedData(0, FALSE, (vCount>>0)&0xF);
        DRV_LED_SetLedData(1, FALSE, (vCount>>8)&0xF);
      #endif

        /* delay 1000ms */
        PT_SLEEP_MS(pt, 1000);

        vElapsedTime++;
    }

    PT_END(pt);
}


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
void thread_App_Init(void)
{
    /* do nothing */
}

