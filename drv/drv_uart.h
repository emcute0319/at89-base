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
 *   drv_uart.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.1.27        panda.xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_UART_H
#define __DRV_UART_H


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_UART_Printf
 * DESCRIPTION:
 *      Print string to UART.
 * PARAMETERS:
 *      fmt : String to be written.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void DRV_UART_Printf(const char *fmt, ...);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_UART_Init
 * DESCRIPTION:
 *      Uart Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
UINT8 DRV_UART_ReadByte(void);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_UART_Init
 * DESCRIPTION:
 *      Uart Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void DRV_UART_Init(void);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_UART_ISR
 * DESCRIPTION:
 *      UART ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void DRV_UART_ISR(void);


#endif /* __DRV_UART_H */

