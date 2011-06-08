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
 *   drv_led_max7219.c
 * DESCRIPTION:
 *   MAX7219ulated LED Dynamic Display Driver.
 * HISTORY:
 *   2011.6.7        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#define _DRV_LED_MAX7219_INTERNAL_
#include "drv.h"

#if DRV_LED_MAX7219_SUPPORT

/* MAX7219 Address Definition */
#define DRV_LED_MAX7219_MASK            (0x0F)
#define _MAX7219_ADDR(_v)               ((_v) & DRV_LED_MAX7219_MASK)
#define MAX7219_ADDR_NoOp               _MAX7219_ADDR(0x00)
#define MAX7219_ADDR_Dig0               _MAX7219_ADDR(0x01)
#define MAX7219_ADDR_Dig1               _MAX7219_ADDR(0x02)
#define MAX7219_ADDR_Dig2               _MAX7219_ADDR(0x03)
#define MAX7219_ADDR_Dig3               _MAX7219_ADDR(0x04)
#define MAX7219_ADDR_Dig4               _MAX7219_ADDR(0x05)
#define MAX7219_ADDR_Dig5               _MAX7219_ADDR(0x06)
#define MAX7219_ADDR_Dig6               _MAX7219_ADDR(0x07)
#define MAX7219_ADDR_Dig7               _MAX7219_ADDR(0x08)
#define MAX7219_ADDR_DecodeMode         _MAX7219_ADDR(0x09)
#define MAX7219_ADDR_Intensity          _MAX7219_ADDR(0x0A)
#define MAX7219_ADDR_ScanLimit          _MAX7219_ADDR(0x0B)
#define MAX7219_ADDR_Shutdown           _MAX7219_ADDR(0x0C)
#define MAX7219_ADDR_Reserved           _MAX7219_ADDR(0x0D)
#define MAX7219_ADDR_DisplayTest        _MAX7219_ADDR(0x0F)

#define _Dig_Addr(_n)                   (MAX7219_ADDR_Dig0 + (_n))

/* MAX7219 Decode Mode Definition */
#define MAX7219_DecodeMode_None         0x00
#define MAX7219_DecodeMode_Bit0         0x01
#define MAX7219_DecodeMode_Bit3_0       0x0F
#define MAX7219_DecodeMode_Bit7_0       0xFF

/* MAX7219 Intensity Definition */
#define MAX7219_Intensity_1div32        0x00
#define MAX7219_Intensity_3div32        0x01
#define MAX7219_Intensity_5div32        0x02
#define MAX7219_Intensity_7div32        0x03
#define MAX7219_Intensity_9div32        0x04
#define MAX7219_Intensity_11div32       0x05
#define MAX7219_Intensity_13div32       0x06
#define MAX7219_Intensity_15div32       0x07
#define MAX7219_Intensity_17div32       0x08
#define MAX7219_Intensity_19div32       0x09
#define MAX7219_Intensity_21div32       0x0A
#define MAX7219_Intensity_23div32       0x0B
#define MAX7219_Intensity_25div32       0x0C
#define MAX7219_Intensity_27div32       0x0D
#define MAX7219_Intensity_29div32       0x0E
#define MAX7219_Intensity_31div32       0x0F

/* MAX7219 Scan-Limit Definition */
#define MAX7219_ScanLimit_Dig0          0x00
#define MAX7219_ScanLimit_Dig0_1        0x01
#define MAX7219_ScanLimit_Dig0_2        0x02
#define MAX7219_ScanLimit_Dig0_3        0x03
#define MAX7219_ScanLimit_Dig0_4        0x04
#define MAX7219_ScanLimit_Dig0_5        0x05
#define MAX7219_ScanLimit_Dig0_6        0x06
#define MAX7219_ScanLimit_Dig0_7        0x07
#define _Scanlimit_Value(_v)            ((_v) - 1)

/* MAX7219 Shut-Down Mode Definition */
#define MAX7219_ShutdownMode_Shutdown   0x00
#define MAX7219_ShutdownMode_Normal     0x01

/* MAX7219 Display-Test Mode Definition */
#define MAX7219_DisplayMode_Normal      0x00
#define MAX7219_DisplayMode_Test        0x01

/* Translate LED Display Code:
 *
 *               bit :  7 6 5 4 3 2 1 0
 *  before translate :  h g f e d c b a
 *  after  translate :  h a b c d e f g
 */
#define MAX7219_TRAN_CODE(_v)                                   \
    (  (((UINT8)(_v) << (7-7)) & (1 << 7))  /* bit 7 -> 7 */    \
     | (((UINT8)(_v) << (6-0)) & (1 << 6))  /* bit 0 -> 6 */    \
     | (((UINT8)(_v) << (5-1)) & (1 << 5))  /* bit 1 -> 5 */    \
     | (((UINT8)(_v) << (4-2)) & (1 << 4))  /* bit 2 -> 4 */    \
     | (((UINT8)(_v) >> (3-3)) & (1 << 3))  /* bit 3 -> 3 */    \
     | (((UINT8)(_v) >> (4-2)) & (1 << 2))  /* bit 4 -> 2 */    \
     | (((UINT8)(_v) >> (5-1)) & (1 << 1))  /* bit 5 -> 1 */    \
     | (((UINT8)(_v) >> (6-0)) & (1 << 0))  /* bit 6 -> 0 */    \
    )

static void drv_led_max7219_WriteReg(IN UINT8 vRegNo, IN UINT8 vData)
{
    /* write, until success */
    do
    {
        /* open SPI bus */
        DRV_SPI_Open();

        /* output the address */
        DRV_SPI_WriteByte(vRegNo);

        /* write 8-bit register value */
        DRV_SPI_WriteByte(vData);

	} while (!DRV_SPI_IsSuccess());

    /* close SPI bus */
    DRV_SPI_Close();
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_LED_MAX7219_SetData
 * DESCRIPTION:
 *      Set MAX7219 LED Display Data.
 * PARAMETERS:
 *      vLedNum  : LED Number;
 *      vDisData : LED Display data;
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.7        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_LED_MAX7219_SetData
(
    IN DRV_LED_NUM_T    vLedNum,
    IN UINT8            vDisData
)
{
    drv_led_max7219_WriteReg(_Dig_Addr(vLedNum), MAX7219_TRAN_CODE(vDisData));
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_LED_MAX7219_Init
 * DESCRIPTION:
 *      MAX7219 LED Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.7        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_LED_MAX7219_Init(void)
{
    UINT8   vLoop;

    /* Dark all LEDs at power-on */
    for (vLoop = 0; vLoop < DRV_LED_TOTAL_LEDs; vLoop++)
    {
        drv_led_max7219_WriteReg(_Dig_Addr(vLoop), _LED_CODE_DARK);
    }

    /* Set to Normal Mode */
    drv_led_max7219_WriteReg(MAX7219_ADDR_DisplayTest, MAX7219_DisplayMode_Normal);
    drv_led_max7219_WriteReg(MAX7219_ADDR_Shutdown,    MAX7219_ShutdownMode_Normal);

    /* Set Scan-Limit Value */
    drv_led_max7219_WriteReg(MAX7219_ADDR_ScanLimit,   _Scanlimit_Value(DRV_LED_TOTAL_LEDs));

    /* Set Intensity Value: 17/32 */
    drv_led_max7219_WriteReg(MAX7219_ADDR_Intensity,   MAX7219_Intensity_17div32);
}

#endif

