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
 *   drv_led.c
 * DESCRIPTION:
 *   LED Dynamic Display Driver.
 * HISTORY:
 *   2011.6.7        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#define _DRV_LED_INTERNAL_
#include "drv.h"

#if DRV_LED_SUPPORT

#define _EMPTY                      (0xFF)


/******************************************************************************
 *  Porting Part:
 ******************************************************************************/

#define DRV_LED_SET_DATA(_v)        do { IO_PORT_LED_DATA_OUT = (_v); } while (0)
#define DRV_LED_SEL_LED(_n)         do {                                        \
                                        if ((_n) == 0)                          \
                                        {                                       \
                                            DRV_IO_Write(IO_PIN(LED_SEL_1), 0); \
                                            DRV_IO_Write(IO_PIN(LED_SEL_0), 1); \
                                        }                                       \
                                        else if ((_n) == 1)                     \
                                        {                                       \
                                            DRV_IO_Write(IO_PIN(LED_SEL_0), 0); \
                                            DRV_IO_Write(IO_PIN(LED_SEL_1), 1); \
                                        }                                       \
                                        else                                    \
                                        {                                       \
                                            DRV_IO_Write(IO_PIN(LED_SEL_0), 0); \
                                            DRV_IO_Write(IO_PIN(LED_SEL_1), 0); \
                                        }                                       \
                                    } while (0)

#define DRV_LED_REFRESH_DELAY       (2)     /* ms */

/* LED Type:
 *   0 -- Common cathode;
 *   1 -- Common anode;
 */
#define DRV_LED_TYPE                (0)


/******************************************************************************
 *  Common Part:
 ******************************************************************************/

#if (DRV_LED_TYPE == 0)
 #define _LED_CODE(_v)              (_v)
#elif (DRV_LED_TYPE == 1)
 #define _LED_CODE(_v)              (~(_v))
#else
 #error "Unsupported LED Type!"
#endif

#define _LED_CODE_DARK              _LED_CODE(0x00)

static struct
{
    UINT8   vCh;
    UINT8   vCode;  /* sequence: abcdefgh (from bit 0-7) */
} CONST aLedCode[] =
{
    { 0x00,   _LED_CODE(0x3F) },
    { 0x01,   _LED_CODE(0x06) },
    { 0x02,   _LED_CODE(0x5B) },
    { 0x03,   _LED_CODE(0x4F) },
    { 0x04,   _LED_CODE(0x66) },
    { 0x05,   _LED_CODE(0x6D) },
    { 0x06,   _LED_CODE(0x7D) },
    { 0x07,   _LED_CODE(0x07) },
    { 0x08,   _LED_CODE(0x7F) },
    { 0x09,   _LED_CODE(0x6F) },
    { 0x0A,   _LED_CODE(0x77) },
    { 0x0B,   _LED_CODE(0x7C) },
    { 0x0C,   _LED_CODE(0x39) },
    { 0x0D,   _LED_CODE(0x5E) },
    { 0x0E,   _LED_CODE(0x79) },
    { 0x0F,   _LED_CODE(0x71) },
    { 'P',    _LED_CODE(0x73) },
    { 'H',    _LED_CODE(0x76) },
    { 'U',    _LED_CODE(0x3E) },
    { 'n',    _LED_CODE(0x54) },
    { 'r',    _LED_CODE(0x50) },
    { '-',    _LED_CODE(0x40) },
    { '_',    _LED_CODE(0x08) },
    { '.',    _LED_CODE(0x80) },
    { _EMPTY, _LED_CODE_DARK  },  /* Dark LED */
};

/* attach point display */
#if (DRV_LED_TYPE == 0)
 #define _LED_ATTACH_P(_n, _v)  ((_v) |  ((DRV_LED_NUM_T)READ_BIT(vLedPointBuf, (_n)) << 7))
#elif (DRV_LED_TYPE == 1)
 #define _LED_ATTACH_P(_n, _v)  ((_v) & ~((DRV_LED_NUM_T)READ_BIT(vLedPointBuf, (_n)) << 7))
#else
 #error "Unsupported LED Type!"
#endif


static volatile BOOL bDisplayEnabled = FALSE;

/******************************************************************************
 * FUNCTION NAME:
 *      drv_led_Refresh
 * DESCRIPTION:
 *      Refresh LED.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.7        Panda.Xiong         Create/Update
 *****************************************************************************/
static void drv_led_Refresh(void)
{
    static UINT8 vCurrentSelLed = 0;
    UINT8   vLoop;

    DRV_LED_SEL_LED(vCurrentSelLed);

    for (vLoop = 0; vLoop < COUNT_OF(aLedCode); vLoop++)
    {
        if (aLedCode[vLoop].vCh == aLedDisBuf[vCurrentSelLed])
        {
            DRV_LED_SET_DATA(_LED_ATTACH_P(vCurrentSelLed, aLedCode[vLoop].vCode));
            break;
        }
    }
    if (vLoop >= COUNT_OF(aLedCode))
    {
        /* Invalid data, dark this LED */
        DRV_LED_SET_DATA(_LED_ATTACH_P(vCurrentSelLed, _LED_CODE_DARK));
    }

    if (vCurrentSelLed++ >= DRV_LED_TOTAL_LEDs)
    {
        vCurrentSelLed = 0;
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_LED_Init
 * DESCRIPTION:
 *      LED Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.7        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_LED_Init(void)
{
    UINT8   vLoop;

    /* Select none LED at power-on */
    DRV_LED_SEL_LED(_EMPTY);

    /* Dark all LEDs at power-on */
    for (vLoop = 0; vLoop < COUNT_OF(aLedDisBuf); vLoop++)
    {
        aLedDisBuf[vLoop] = _LED_CODE_DARK;
    }
    vLedPointBuf = 0x00;

    /* Enable LED Dynamic Display */
    bDisplayEnabled = TRUE;
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_LED_ISR
 * DESCRIPTION:
 *      LED Interrupt Service Routine Entry.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.7        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_LED_ISR(void)
{
    if (bDisplayEnabled)
    {
        static UINT8    vCounter = 0;

        if (vCounter++ >= DRV_LED_REFRESH_DELAY)
        {
            vCounter = 0;

            /* Time to refresh LED */
            drv_led_Refresh();
        }
    }
}

#endif

