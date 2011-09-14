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
 *   drv_uart.c
 * DESCRIPTION:
 *   UART Driver.
 * HISTORY:
 *   2010.1.27        panda.xiong         Create/Update
 *
*****************************************************************************/

#include "drv.h"

#if DRV_UART_SUPPORT

#include <stdarg.h>
#include "drv_uart.h"


/******************************************************************************
 * FUNCTION NAME:
 *      drv_uart_WriteByte
 * DESCRIPTION:
 *      Write byte data to UART.
 * PARAMETERS:
 *      vByte : Byte data to be written.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
static void drv_uart_WriteByte(IN UINT8 vByte)
{
    /* waiting for send buffer empty */
    while (!UCSRA_UDRE)
    {}

    UDR = vByte;
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_UART_ReadByte
 * DESCRIPTION:
 *      Uart Read Byte.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      -1     : Rx FIFO empty;
 *      others : The received data;
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
SINT16 DRV_UART_ReadByte(void)
{
    /* return received data while RX buffer full */
    if (UCSRA_RXC)
    {
        return UDR;
    }
    else
    {
        /* Rx FIFO empty */
        return -1;
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_UART_Printf
 * DESCRIPTION:
 *      Print string to UART.
 * PARAMETERS:
 *      format : Formatted string to be written.
 * RETURN:
 *      N/A
 * NOTES:
 *      The %s may be abnormal in some formatted string,
 *       so, it's strongly recommanded to be used in a separate line.
 *      The root cause is unknown yet!!!
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void DRV_UART_Printf(char CONST *format, ...)
{
    va_list   ptr;
    char      fch;       /* get format value */

    va_start(ptr, format);

    for (;;)
    {
        /* until '%' or '\0' */
        while ((fch = *format++) != '%')
        {
            if (fch == '\0')
            {
                /* to the end of string */
                va_end(ptr);
                return;
            }

            drv_uart_WriteByte(fch);
        }

        /* skip '%' character */
        switch (fch = *format++)
        {
            static CONST char aHex[] = "0123456789ABCDEF";
            unsigned int    vDiv, vData;
            unsigned char   vRadix;

            case 'd':
            case 'u':
                vRadix = 10;
                vDiv = (sizeof(int) == 2)? 10000 : 1000000000;
                goto _print_loop;

            case 'X':
                vRadix = 16;
                vDiv = (sizeof(int) == 2)? 0x1000 : 0x10000000;

              _print_loop:
                vData = va_arg(ptr, int);

                if (fch == 'd')
                {
                    if  ((int)vData < 0)
                    {
                        vData = -vData;
                        drv_uart_WriteByte('-');
                    }
                }

                while ((vDiv > 1) && (vDiv > vData))
                {
                    vDiv /= vRadix;
                }

                while (vDiv != 0)
                {
                    drv_uart_WriteByte(aHex[vData/vDiv]);
                    vData %= vDiv;
                    vDiv  /= vRadix;
                }

                break;

            case 's':
            {
                char CONST *p_str = (char CONST *)va_arg(ptr, char CONST *);

                while ((fch = *p_str++) != '\0')
                {
                    drv_uart_WriteByte(fch);
                }
                break;
            }

            case 'c':
                fch = va_arg(ptr, int);
                /* no break here */

            default:
                drv_uart_WriteByte(fch);
                break;
        }
    }
}


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
void DRV_UART_Init(void)
{
    /*                f(osc)
     * Baudrate = ----------------
     *            16 * (UBRR + 1)
     *
     * Here, UBRR means (UBRRH, UBRRL).
     *
     *                f(osc)
     * And, UBRR = --------------- - 1
     *              16 * Baudrate
     */
    #define UBRR_VAL    ((UINT16)((CPU_CORE_CLOCK)/(16.)/UART_BAUDRATE_VAL) - 1)

    UCSRB = 0x00;       /* disable while setting baud rate */
    UCSRA = 0x00;
    UCSRC = 0x86;
    UBRRH = (UINT8)(UBRR_VAL >> 8);
    UBRRL = (UINT8)(UBRR_VAL & 0xFF);
    UCSRB = 0x98;       /* use interrupt */
}

#endif

