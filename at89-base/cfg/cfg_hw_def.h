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
 *   cfg_hw_def.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.1.26        PANDA         Create/Update
 *
*****************************************************************************/

#ifndef __CFG_HW_DEF_H
#define __CFG_HW_DEF_H


/* Target CPU Definition, select one from below CPU lists:
 *   _CPU_AT89C2051_
 *   _CPU_AT89C4051_
 *   _CPU_AT89C51_
 *   _CPU_AT89C52_
 *   _CPU_AT89S51_
 *   _CPU_AT89S52_
 */
#define _CPU_AT89C2051_
#define CPU_TYPE                'AT89C2051'

/* CPU Driver */
#define DRV_UART_SUPPORT        1       /* UART                */
#define DRV_WATCHDOG_SUPPORT    1       /* Watchdog            */

/* Simulated/Miscellaneous Driver */
#define DRV_TIMER_SUPPORT       0       /* Simulated Timer     */
#define DRV_SWI_SUPPORT         0       /* Software Interrupt  */
#define DRV_SPI_SUPPORT         0       /* SPI                 */
#define DRV_EPP_SUPPORT         0       /* EPP                 */
#define DRV_I2CM_SUPPORT        0       /* I2C Master          */
#define DRV_I2CS_SUPPORT        0       /* I2C Slave           */
#define DRV_LED_SUPPORT         0       /* LED Driver          */
 #define DRV_LED_Blink_SUPPORT      (0 && DRV_LED_SUPPORT && DRV_TIMER_SUPPORT) /* LED Blink support    */
 #define DRV_LED_Sim_SUPPORT        (0 && DRV_LED_SUPPORT && DRV_TIMER_SUPPORT) /* Simulated LED Driver */
 #define DRV_LED_MAX7219_SUPPORT    (0 && DRV_LED_SUPPORT && DRV_SPI_SUPPORT)   /* MAX7219   LED Driver */
#define DRV_TEMP_SUPPORT        0       /* Temperature Sensor Driver */
 #define DRV_TEMP_DS18B20_SUPPORT   (0 && DRV_TEMP_SUPPORT)     /* DS18B20 Driver */


/* CPU Clock */
#define CPU_Crystal_Frequency   12000000UL    /* Hz    */
#define CPU_Prescale            12
#define CPU_CORE_CLOCK          (CPU_Crystal_Frequency / CPU_Prescale)


/* UART */
#if DRV_UART_SUPPORT
 #define UART_BAUDRATE_VAL      4800UL  /* bps */
#endif


#endif /* __CFG_HW_DEF_H */

