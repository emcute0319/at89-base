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
 *   drv_led_sim.h
 * DESCRIPTION:
 *   Simulated LED Dynamic Display Driver.
 * HISTORY:
 *   2011.6.7        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_LED_SIM_H
#define __DRV_LED_SIM_H


#if DRV_LED_Sim_SUPPORT

/******************************************************************************
 *  Porting Part:
 ******************************************************************************/

#define DRV_LED_SIM_SET_DATA(_v)        do { IO_PORT_LED_DATA_OUT = (_v); } while (0)
#define DRV_LED_SIM_SEL_LED(_n)         do {                                        \
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

#define DRV_LED_SIM_REFRESH_INTERVAL    (2)     /* ms */


/******************************************************************************
 *  Common Part:
 ******************************************************************************/

#ifdef _DRV_LED_SIM_INTERNAL_
 #define _DRV_LED_SIM_EXTERNAL_     /* empty */
#else
 #define _DRV_LED_SIM_EXTERNAL_     extern
#endif

_DRV_LED_SIM_EXTERNAL_ volatile UINT8 aLedDisBuf[DRV_LED_TOTAL_LEDs];

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_LED_Sim_SetData
 * DESCRIPTION:
 *      Set Simulated LED Display Data.
 * PARAMETERS:
 *      _n : LED Number;
 *      _v : LED Display data;
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.7        Panda.Xiong         Create/Update
 *****************************************************************************/
#define DRV_LED_Sim_SetData(_n, _v) do { aLedDisBuf[(_n)] = (_v); } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_LED_Sim_Init
 * DESCRIPTION:
 *      Simulated LED Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.7        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_LED_Sim_Init(void);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_LED_Sim_ISR
 * DESCRIPTION:
 *      Simulated LED Interrupt Service Routine Entry.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.7        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_LED_Sim_ISR(void);

#endif


#endif /* __DRV_LED_SIM_H */

