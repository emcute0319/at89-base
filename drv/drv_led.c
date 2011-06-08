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

#include "drv.h"

#if DRV_LED_SUPPORT

/******************************************************************************
 *  Common Part:
 ******************************************************************************/

#if (DRV_LED_Sim_SUPPORT && DRV_LED_MAX7219_SUPPORT)
 #error "Only one LED Driver can be enabled!"
#endif

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
    IN DRV_LED_NUM_T    vLedNum,
    IN BOOL             bDisPoint,
    IN UINT8            vDisData
)
{
  #if DRV_LED_Sim_SUPPORT
   #define _SET_DATA(_n, _v)    DRV_LED_Sim_SetData(_n, _v)
  #elif DRV_LED_MAX7219_SUPPORT
   #define _SET_DATA(_n, _v)    DRV_LED_MAX7219_SetData(_n, _v)
  #endif

  /* attach point display */
  #if (DRV_LED_TYPE == 0)
   #define _LED_ATTACH_P(_n, _b, _v)  ((_v) |  ((DRV_LED_NUM_T)(_b) << 7))
  #elif (DRV_LED_TYPE == 1)
   #define _LED_ATTACH_P(_n, _b, _v)  ((_v) & ~((DRV_LED_NUM_T)(_b) << 7))
  #endif

    UINT8   vLoop;

    /* set display data */
    for (vLoop = 0; vLoop < COUNT_OF(aLedCode); vLoop++)
    {
        if (aLedCode[vLoop].vCh == vDisData)
        {
            _SET_DATA(vLedNum,
                      _LED_ATTACH_P(vLedNum, bDisPoint, aLedCode[vLoop].vCode));
            return;
        }
    }
    if (vLoop >= COUNT_OF(aLedCode))
    {
        /* Invalid data, dark this LED */
        _SET_DATA(vLedNum, _LED_ATTACH_P(vLedNum, bDisPoint, _LED_CODE_DARK));
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
  #if DRV_LED_Sim_SUPPORT
    DRV_LED_Sim_Init();
  #endif
}

#endif

