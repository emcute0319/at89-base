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


#define DRV_UART_ENTER_CRITICAL()   do { ES = 0; } while (0)
#define DRV_UART_EXIT_CRITICAL()    do { ES = 1; } while (0)

/* Global variable define */
static volatile BOOL     bTxEmpty;
static volatile UINT8    aRxFIFO[8];
static volatile UINT8    vRxFIFO_Counter;  /* Rx FIFO counter */


#if 0 /* ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) ) */
 #define UART_Baudrate_Generated_By_T2  /* UART baudrate is generated by T2 */
#else
 #define UART_Baudrate_Generated_By_T1  /* UART baudrate is generated by T1 */
#endif


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
    if (ES == 0)
    {
        /* wait for uart sent out data */
        while (TI == 0)
        {}

        TI = 0;
    }
    else
    {
        /* wait for uart sent out data */
        while (!bTxEmpty)
        {}

        bTxEmpty = FALSE;
    }

    SBUF = vByte;
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
    if (vRxFIFO_Counter != 0)
    {
        UINT8   vTmpData, i;

        /* Get the first received data in FIFO.
         *
         * Note: Within this read, the UART (RX) Interrupt should be locked.
         */
        DRV_UART_ENTER_CRITICAL();
        vTmpData = aRxFIFO[0];
        vRxFIFO_Counter--;
        for (i = 0; i < vRxFIFO_Counter; i++)
        {
            aRxFIFO[i] = aRxFIFO[i+1];
        }
        DRV_UART_EXIT_CRITICAL();

        return vTmpData;
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
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void DRV_UART_Printf(const char *format, ...)
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
            static const char SEG_CODE aHex[] = "0123456789ABCDEF";
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
                char    *p_str = va_arg(ptr, char *);

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
    /* init internal variable */
    bTxEmpty  = TRUE;

    /*
        The baudrate function using timer0 & timer1 is:

     *  In mode 1:
        baudrate  =  f(osc) / 12

     *  In mode 2:
                       2^(SMOD)
        baudrate  =  ------------  -  f(osc)
                         64

     *  In mode 1 & 3: (usually use)
                       2^(SMOD)      f(osc)          1
        baudrate  =  ------------ * -------- * ( -------------------- )
                         32            12         2^(K) - (TH1, TL1)

        In this formula:
          If T1 is in mode 0,     K = 13;
          If T1 is in mode 1 & 3, K = 16;
          If T1 is in mode 2,     K =  8(usually use).

        So:
                                 2^(SMOD) * f(osc)
        init_value  =  256  -  --------------------  (timer1 is in mode 2)
                                  384 * baudrate
    */


    /*
        The baudrate function using timer2 is:

                                    f(osc)
        baudrate  =  -----------------------------------
                       32 * (65536 - (RCAP2H, RCAP2L))

        So:
                                             f(osc)
        (RCAP2H, RCAP2L)  =  65536  -  -----------------
                                         32 * baudrate
    */


    /*
        Below are some usually used baudrate & initial values: (SCON = 0x50)

     *  Timer1: (mode 1 & 3)
            f(osc) = 12MHz
                Baudrate    SMOD    TMOD    TH1(TL1)
                  4800        1     0x20      0xF3
                  2400        0     0x20      0xF3
            f(osc) = 11.0592MHz
                Baudrate    SMOD    TMOD    TH1(TL1)
                 19200        1     0x20      0xFD
                  9600        0     0x20      0xFD
                  4800        0     0x20      0xFA
                  2400        0     0x20      0xF4

     *  Timer2: (T2CON = 0x34)
            f(osc) = 12MHz
                Baudrate    RCAP2H,RCAP2L(TH2,TL2)   T2MOD(only AT89C52/AT89S52)
                  38400       0xFF, 0xF6              0x00(error = 2.34%)
                  19200       0xFF, 0xEC              0x00(error = 2.34%)
                   9600       0xFF, 0xD9              0x00(error = 0.16%)
                   4800       0xFF, 0xB2              0x00(error = 0.16%)
            f(osc) = 11.0592MHz
                Baudrate    RCAP2H,RCAP2L(TH2,TL2)   T2MOD(only AT89C52/AT89S52)
                 115200       0xFF, 0xFD              0x00
                  57600       0xFF, 0xFA              0x00
                  38400       0xFF, 0xF7              0x00
                  19200       0xFF, 0xEE              0x00
                   9600       0xFF, 0xDC              0x00
                   4800       0xFF, 0xB8              0x00
                   2400       0xFF, 0x70              0x00
    */

#if defined(UART_Baudrate_Generated_By_T2)


    SCON   = 0x50;
    PCON   = 0x00;
    T2CON  = 0x34;
    T2MOD  = 0x00;


 #if (CPU_Crystal_Frequency == 11059200UL)


  #if (UART_BAUDRATE_VAL == 2400UL)
    RCAP2H = TH2 = 0xFF;
    RCAP2L = TL2 = 0x70;
  #elif (UART_BAUDRATE_VAL == 4800UL)
    RCAP2H = TH2 = 0xFF;
    RCAP2L = TL2 = 0xB8;
  #elif (UART_BAUDRATE_VAL == 9600UL)
    RCAP2H = TH2 = 0xFF;
    RCAP2L = TL2 = 0xDC;
  #elif (UART_BAUDRATE_VAL == 19200UL)
    RCAP2H = TH2 = 0xFF;
    RCAP2L = TL2 = 0xEE;
  #elif (UART_BAUDRATE_VAL == 38400UL)
    RCAP2H = TH2 = 0xFF;
    RCAP2L = TL2 = 0xF7;
  #elif (UART_BAUDRATE_VAL == 57600UL)
    RCAP2H = TH2 = 0xFF;
    RCAP2L = TL2 = 0xFA;
  #elif (UART_BAUDRATE_VAL == 115200UL)
    RCAP2H = TH2 = 0xFF;
    RCAP2L = TL2 = 0xFD;
  #else
    #error "Unsupported UART Baudrate!"
  #endif


 #elif (CPU_Crystal_Frequency == 12000000UL)


  #if (UART_BAUDRATE_VAL == 4800UL)
    RCAP2H = TH2 = 0xFF;
    RCAP2L = TL2 = 0xB2;
  #elif (UART_BAUDRATE_VAL == 9600UL)
    RCAP2H = TH2 = 0xFF;
    RCAP2L = TL2 = 0xD9;
  #elif (UART_BAUDRATE_VAL == 19200UL)
    RCAP2H = TH2 = 0xFF;
    RCAP2L = TL2 = 0xEC;
    #warning "The Error Rate of BaudRate is 2.34%, over maximum Error Rate 2%!"
  #elif (UART_BAUDRATE_VAL == 38400UL)
    RCAP2H = TH2 = 0xFF;
    RCAP2L = TL2 = 0xF6;
    #warning "The Error Rate of BaudRate is 2.34%, over maximum Error Rate 2%!"
  #else
    #error "Unsupported UART Baudrate!"
  #endif


 #else
    #error "Unknown/Unsupported CPU frequency!"
 #endif



#elif defined(UART_Baudrate_Generated_By_T1)



    TMOD   = 0x20;
    SCON   = 0x50;


 #if (CPU_Crystal_Frequency == 11059200UL)


  #if (UART_BAUDRATE_VAL == 300UL)
    TH1 = TL1 = 0xA0;
  #elif (UART_BAUDRATE_VAL == 600UL)
    TH1 = TL1 = 0xD0;
  #elif (UART_BAUDRATE_VAL == 1200UL)
    TH1 = TL1 = 0xE8;
  #elif (UART_BAUDRATE_VAL == 2400UL)
    TH1 = TL1 = 0xF4;
  #elif (UART_BAUDRATE_VAL == 4800UL)
    TH1 = TL1 = 0xFA;
  #elif (UART_BAUDRATE_VAL == 9600UL)
    TH1 = TL1 = 0xFD;
  #elif (UART_BAUDRATE_VAL == 19200UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFD;
  #elif (UART_BAUDRATE_VAL == 38400UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFE;
    #warning "The Error Rate of BaudRate is -33.33%, over maximum Error Rate 2%!"
  #elif (UART_BAUDRATE_VAL == 57600UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFF;
  #elif (UART_BAUDRATE_VAL == 115200UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFF;
    #warning "The Error Rate of BaudRate is -100.00%, over maximum Error Rate 2%!"
  #else
     #error "Unsupported UART Baudrate!"
  #endif


 #elif (CPU_Crystal_Frequency == 12000000UL)


  #if (UART_BAUDRATE_VAL == 300UL)
    TH1 = TL1 = 0x98;
  #elif (UART_BAUDRATE_VAL == 600UL)
    TH1 = TL1 = 0xCC;
  #elif (UART_BAUDRATE_VAL == 1200UL)
    TH1 = TL1 = 0xE6;
  #elif (UART_BAUDRATE_VAL == 2400UL)
    TH1 = TL1 = 0xF3;
  #elif (UART_BAUDRATE_VAL == 4800UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xF3;
  #elif (UART_BAUDRATE_VAL == 9600UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xF9;
    #warning "The Error Rate of BaudRate is -7.52%, over maximum Error Rate 2%!"
  #elif (UART_BAUDRATE_VAL == 19200UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFD;
    #warning "The Error Rate of BaudRate is -7.84%, over maximum Error Rate 2%!"
  #elif (UART_BAUDRATE_VAL == 38400UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFE;
    #warning "The Error Rate of BaudRate is -23.08%, over maximum Error Rate 2%!"
  #elif (UART_BAUDRATE_VAL == 57600UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFF;
    #warning "The Error Rate of BaudRate is 7.69%, over maximum Error Rate 2%!"
  #elif (UART_BAUDRATE_VAL == 115200UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFF;
    #warning "The Error Rate of BaudRate is -84.62%, over maximum Error Rate 2%!"
  #else
     #error "Unsupported UART Baudrate!"
  #endif


 #elif (CPU_Crystal_Frequency == 22118400UL)

  #if (UART_BAUDRATE_VAL == 300UL)
    TH1 = TL1 = 0x40;
  #elif (UART_BAUDRATE_VAL == 600UL)
    TH1 = TL1 = 0xA0;
  #elif (UART_BAUDRATE_VAL == 1200UL)
    TH1 = TL1 = 0xD0;
  #elif (UART_BAUDRATE_VAL == 2400UL)
    TH1 = TL1 = 0xE8;
  #elif (UART_BAUDRATE_VAL == 4800UL)
    TH1 = TL1 = 0xF4;
  #elif (UART_BAUDRATE_VAL == 9600UL)
    TH1 = TL1 = 0xFA;
  #elif (UART_BAUDRATE_VAL == 19200UL)
    TH1 = TL1 = 0xFD;
  #elif (UART_BAUDRATE_VAL == 38400UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFD;
  #elif (UART_BAUDRATE_VAL == 57600UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFE;
  #elif (UART_BAUDRATE_VAL == 115200UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFF;
  #else
     #error "Unsupported UART Baudrate!"
  #endif


 #elif (CPU_Crystal_Frequency == 24000000UL)


  #if (UART_BAUDRATE_VAL == 300UL)
    TH1 = TL1 = 0x30;
  #elif (UART_BAUDRATE_VAL == 600UL)
    TH1 = TL1 = 0x98;
  #elif (UART_BAUDRATE_VAL == 1200UL)
    TH1 = TL1 = 0xCC;
  #elif (UART_BAUDRATE_VAL == 2400UL)
    TH1 = TL1 = 0xE6;
  #elif (UART_BAUDRATE_VAL == 4800UL)
    TH1 = TL1 = 0xF3;
  #elif (UART_BAUDRATE_VAL == 9600UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xF3;
  #elif (UART_BAUDRATE_VAL == 19200UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xF9;
    #warning "The Error Rate of BaudRate is -7.52%, over maximum Error Rate 2%!"
  #elif (UART_BAUDRATE_VAL == 38400UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFD;
    #warning "The Error Rate of BaudRate is -7.84%, over maximum Error Rate 2%!"
  #elif (UART_BAUDRATE_VAL == 57600UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFE;
    #warning "The Error Rate of BaudRate is 7.69%, over maximum Error Rate 2%!"
  #elif (UART_BAUDRATE_VAL == 115200UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFF;
    #warning "The Error Rate of BaudRate is 7.69%, over maximum Error Rate 2%!"
  #else
     #error "Unsupported UART Baudrate!"
  #endif

 #elif (CPU_Crystal_Frequency == 33000000UL)

  #if (UART_BAUDRATE_VAL == 300UL)
    #error "Baudrate is too low!"
  #elif (UART_BAUDRATE_VAL == 600UL)
    TH1 = TL1 = 0x71;
  #elif (UART_BAUDRATE_VAL == 1200UL)
    TH1 = TL1 = 0xB8;
  #elif (UART_BAUDRATE_VAL == 2400UL)
    TH1 = TL1 = 0xDC;
  #elif (UART_BAUDRATE_VAL == 4800UL)
    TH1 = TL1 = 0xEE;
  #elif (UART_BAUDRATE_VAL == 9600UL)
    TH1 = TL1 = 0xF7;
  #elif (UART_BAUDRATE_VAL == 19200UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xF7;
  #elif (UART_BAUDRATE_VAL == 38400UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFC;
    #warning "The Error Rate of BaudRate is 10.59%, over maximum Error Rate 2%!"
  #elif (UART_BAUDRATE_VAL == 57600UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFD;
  #elif (UART_BAUDRATE_VAL == 115200UL)
    SET_BIT(PCON, 7);
    TH1 = TL1 = 0xFF;
    #warning "The Error Rate of BaudRate is 32.87%, over maximum Error Rate 2%!"
  #else
     #error "Unsupported UART Baudrate!"
  #endif


 #else
    #error "Unknown/Unsupported CPU frequency!"
 #endif


    TR1    = 1;



#else
 #error "Unknown UART Baudrate generator!"
#endif


    ES     = 1;
}


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
void DRV_UART_ISR(void)
{
    /* uart TX flag */
    if (TI)
    {
        TI = 0;

        /* Indicate that the UART Tx is empty */
        bTxEmpty = TRUE;
    }

    /* uart RX flag */
    if (RI)
    {
        /* Get the data from uart, and stored into FIFO buffer */
        if (vRxFIFO_Counter < COUNT_OF(aRxFIFO))
        {
            aRxFIFO[vRxFIFO_Counter] = SBUF;
            vRxFIFO_Counter++;
        }

        RI = 0;
    }
}

#endif
