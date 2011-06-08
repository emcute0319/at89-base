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

#define DRV_UART_SUPPORT        1       /* UART        */
#define DRV_WATCHDOG_SUPPORT    1       /* Watchdog    */

/* Simulated Driver */
#define DRV_SPI_SUPPORT         0       /* SPI         */
#define DRV_I2CM_SUPPORT        0       /* I2C Master  */
#define DRV_I2CS_SUPPORT        0       /* I2C Slave   */
#define DRV_LED_SUPPORT         0       /* LED Driver  */
 #define DRV_LED_Blink_SUPPORT   (0 && DRV_LED_SUPPORT)                     /* LED Blink support    */
 #define DRV_LED_Sim_SUPPORT     (0 && DRV_LED_SUPPORT)                     /* Simulated LED Driver */
 #define DRV_LED_MAX7219_SUPPORT (0 && DRV_LED_SUPPORT && DRV_SPI_SUPPORT)  /* MAX7219   LED Driver */


/* CPU Clock */
#define CPU_Crystal_Frequency   12000000UL    /* Hz    */
#define CPU_Prescale            12
#define CPU_CORE_CLOCK          (CPU_Crystal_Frequency / CPU_Prescale)


/* UART */
#if DRV_UART_SUPPORT
 #define UART_BAUDRATE_VAL      4800UL  /* bps */
#endif



#ifdef DECLARE_IO_PIN

#define NA              0

/* IO pin Definition.
 *
 *   name      : IO pin name;
 *   port      : IO port ID;
 *   bit       : IO bit ID of port;
 *   mode      : IO input/output mode;
 *   init_val  : IO initial output value;
 *   pin_no    : IO hardware pin number;
 *   desc      : IO description;
 *
 *   Note :
 *      1. Should define all GPIO pins here, at ascending order!!!
 *          else, the system may be running abnormally !!!
 */

/*             name               port       bit         mode   init_val pin_no desc  */

/* PORT 1 */
/*
 *         a
 *     ---------
 *    |         |
 *  f |         | b
 *    |    g    |
 *    |---------|
 *    |         |
 *  e |         | c
 *    |         |
 *     ---------   . p
 *         d
 */
#define IO_PORT_LED_DATA_OUT  IO_PORT(1)       /* LED Data Output port */
DECLARE_IO_PIN(LED_DATA_c,    _IO_PORT(1), _IO_BIT(0), IO_OUTPUT,  1,      12,  "LED Data Output: c: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_p,    _IO_PORT(1), _IO_BIT(1), IO_OUTPUT,  1,      13,  "LED Data Output: p: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_e,    _IO_PORT(1), _IO_BIT(2), IO_OUTPUT,  1,      14,  "LED Data Output: e: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_d,    _IO_PORT(1), _IO_BIT(3), IO_OUTPUT,  1,      15,  "LED Data Output: d: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_g,    _IO_PORT(1), _IO_BIT(4), IO_OUTPUT,  1,      16,  "LED Data Output: g: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_b,    _IO_PORT(1), _IO_BIT(5), IO_OUTPUT,  1,      17,  "LED Data Output: b: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_a,    _IO_PORT(1), _IO_BIT(6), IO_OUTPUT,  1,      18,  "LED Data Output: a: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_f,    _IO_PORT(1), _IO_BIT(7), IO_OUTPUT,  1,      19,  "LED Data Output: f: =0, Light; =1, Dark.")

/* PORT 3 */
DECLARE_IO_PIN(UART_RXD,      _IO_PORT(3), _IO_BIT(0), IO_INPUT,   1,       2,  "UART RXD Pin")
DECLARE_IO_PIN(UART_TXD,      _IO_PORT(3), _IO_BIT(1), IO_OUTPUT,  1,       3,  "UART TXD Pin")
DECLARE_IO_PIN(SPI_MISO,      _IO_PORT(3), _IO_BIT(2), IO_INPUT,   1,       8,  "MAX187 CS Pin: =0, select MAX187; =1, deselect MAX187.")
DECLARE_IO_PIN(SPI_CS,        _IO_PORT(3), _IO_BIT(3), IO_OUTPUT,  1,       9,  "MAX518 Serial Data Output Pin")
DECLARE_IO_PIN(LED_SEL_1,     _IO_PORT(3), _IO_BIT(4), IO_OUTPUT,  1,       6,  "LED Select 1: =0, select this LED; =1, deselect this LED.")
DECLARE_IO_PIN(LED_SEL_0,     _IO_PORT(3), _IO_BIT(5), IO_OUTPUT,  1,       7,  "LED Select 0: =0, select this LED; =1, deselect this LED.")
DECLARE_IO_PIN(SPI_MOSI,      _IO_PORT(3), _IO_BIT(6), IO_OUTPUT,  1,      NA,  "Unused Pin")
DECLARE_IO_PIN(SPI_SCK,       _IO_PORT(3), _IO_BIT(7), IO_OUTPUT,  1,      11,  "MAX518 Serial Clock Pin")

#endif

