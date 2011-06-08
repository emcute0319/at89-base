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
 *   drv_led_max7219.h
 * DESCRIPTION:
 *   MAX7219 LED Display Driver.
 * HISTORY:
 *   2011.6.7        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_LED_MAX7219_H
#define __DRV_LED_MAX7219_H


#if DRV_LED_MAX7219_SUPPORT

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
);

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
void DRV_LED_MAX7219_Init(void);

#endif


#endif /* __DRV_LED_MAX7219_H */

