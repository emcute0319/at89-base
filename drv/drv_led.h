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
 *   drv_led.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2011.6.7        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_LED_H
#define __DRV_LED_H


#if DRV_LED_SUPPORT

/******************************************************************************
 *  Porting Part:
 ******************************************************************************/

#define DRV_LED_TOTAL_LEDs          (2)     /* Total LED Number */

/* LED Type:
 *   0 -- Common cathode;
 *   1 -- Common anode;
 */
#define DRV_LED_TYPE                (0)


/******************************************************************************
 *  Common Part:
 ******************************************************************************/

#if (DRV_LED_TOTAL_LEDs <= 8)
 typedef UINT8  DRV_LED_NUM_T;
#elif (DRV_LED_TOTAL_LEDs <= 16)
 typedef UINT16 DRV_LED_NUM_T;
#else
 typedef UINT32 DRV_LED_NUM_T;
#endif

#define _EMPTY                      (0xFF)

#if (DRV_LED_TYPE == 0)
 #define _LED_CODE(_v)              (_v)
#elif (DRV_LED_TYPE == 1)
 #define _LED_CODE(_v)              (~(_v))
#else
 #error "Unsupported LED Type!"
#endif

#define _LED_CODE_DARK              _LED_CODE(0x00)

#include "drv_led_sim.h"

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
);

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
void DRV_LED_Init(void);

#endif


#endif /* __DRV_LED_H */
