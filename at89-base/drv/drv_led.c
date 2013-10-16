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

#if (DRV_LED_Sim_SUPPORT && DRV_LED_MAX7219_SUPPORT)
 #error "Only one LED Driver can be enabled!"
#endif


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
    { 'L',    _LED_CODE(0x38) },
    { 'U',    _LED_CODE(0x3E) },
    { 'n',    _LED_CODE(0x54) },
    { 'r',    _LED_CODE(0x50) },
    { '-',    _LED_CODE(0x40) },
    { '_',    _LED_CODE(0x08) },
    { '.',    _LED_CODE(0x80) },
    { _EMPTY, _LED_CODE_DARK  },  /* Dark LED */
};


#if DRV_LED_Sim_SUPPORT
 #define _SET_DATA(_n, _v)          DRV_LED_Sim_SetData((_n), (_v))
#elif DRV_LED_MAX7219_SUPPORT
 #define _SET_DATA(_n, _v)          DRV_LED_MAX7219_SetData((_n), (_v))
#endif
#if DRV_LED_Blink_SUPPORT
 static volatile UINT8  aLedDataBuf[DRV_LED_TOTAL_LEDs];
 #define DRV_LED_SET_DATA(_n, _v)   do { aLedDataBuf[(_n)] = (_v); } while (0)
#else
 #define DRV_LED_SET_DATA(_n, _v)   _SET_DATA((_n), (_v))
#endif


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_LED_SetLedData
 * DESCRIPTION:
 *      Set LED Display Data.
 * PARAMETERS:
 *      _n : LED Number;
 *      _p : LED point display;
 *            =TRUE,  Light LED point;
 *            =FALSE, Dark  LED point;
 *      _v : LED Display data;
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.7        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_LED_SetLedData
(
    IN UINT8    vLedNum,
    IN BOOL     bDisPoint,
    IN UINT8    vDisData
)
{
  /* attach point display */
  #if (DRV_LED_TYPE == 0)
   #define _LED_ATTACH_P(_b, _v)    ((_v) |  ((UINT8)(_b) << 7))
  #elif (DRV_LED_TYPE == 1)
   #define _LED_ATTACH_P(_b, _v)    ((_v) & ~((UINT8)(_b) << 7))
  #endif

    UINT8   vLoop;

    /* set display data */
    for (vLoop = 0; vLoop < COUNT_OF(aLedCode); vLoop++)
    {
        if (aLedCode[vLoop].vCh == vDisData)
        {
            DRV_LED_SET_DATA(vLedNum,
                             _LED_ATTACH_P(bDisPoint, aLedCode[vLoop].vCode));
            return;
        }
    }
    if (vLoop >= COUNT_OF(aLedCode))
    {
        /* Invalid data, dark this LED */
        DRV_LED_SET_DATA(vLedNum,
                         _LED_ATTACH_P(bDisPoint, _LED_CODE_DARK));
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
    UINT8    vLoop;

  #if DRV_LED_Blink_SUPPORT
    /* No blink at power-on */
    vLedBlinkState = 0;

    /* Init LED buffer to all dark at power-on */
    for (vLoop = 0; vLoop < COUNT_OF(aLedDataBuf); vLoop++)
    {
        aLedDataBuf[vLoop] = _LED_CODE_DARK;
    }
  #endif

    /* Dark all LEDs at power-on */
    for (vLoop = 0; vLoop < DRV_LED_TOTAL_LEDs; vLoop++)
    {
        _SET_DATA(vLoop, _LED_CODE_DARK);
    }

  #if DRV_LED_Sim_SUPPORT
    DRV_LED_Sim_Init();
  #endif

  #if DRV_LED_MAX7219_SUPPORT
    DRV_LED_MAX7219_Init();
  #endif

  #if DRV_LED_Blink_SUPPORT
    /* Enable LED Blink Timer */
    DRV_Timer_SetState(TIMER(Timer_LED_Blink), ENABLE);
  #endif
}


#if DRV_LED_Blink_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_LED_Blink_ISR
 * DESCRIPTION:
 *      LED Blink Interrupt Service Routine Entry.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.7        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_LED_Blink_ISR(void)
{
    static BOOL bDark = FALSE;
    UINT8       vLoop;

    /* Time to Blink LED */
    for (vLoop = 0; vLoop < COUNT_OF(aLedDataBuf); vLoop++)
    {
        if (bDark && READ_BIT(vLedBlinkState, vLoop))
        {
            _SET_DATA(vLoop, _LED_CODE_DARK);
        }
        else
        {
            _SET_DATA(vLoop, aLedDataBuf[vLoop]);
        }
    }
    bDark = !bDark;
}

#endif

#endif

