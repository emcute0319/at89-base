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
 *   cfg_hw_porting.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2013.10.16         PANDA           Create/Update
 *
 *****************************************************************************/


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


/* Simulated Timer Entry Definition */
#ifdef DECLARE_VECTOR_TIMER

/* Note:
 *  1. All timer interval values should not below "DRV_TIMER_SysTimerTick";
 *     else, it will be auto limited to "DRV_TIMER_SysTimerTick".
 *  2. All timer interval values should not over
 *      (256*DRV_TIMER_SysTimerTick/1000) ms;
 *      else, the interval will be auto AND'd with 0xFF;
 *     If want to support longer timer interval,
 *      change the definition of type "DRV_TIMER_COUNTER_T".
 *  3. Default, all timers are disabled;
 *     use DRV_Timer_SetState() to enable it.
 *  4. Maximum 256 simulated timers are supported.
 */

/*
DECLARE_VECTOR_TIMER(Timer_TEST,
                     TIMER_MS(500),
                     TIMER_TEST_ISR,
                     "TEST Timer ISR")
*/

#endif


/* Simulated Software Interrupt (SWI) Entry Definition */
#ifdef DECLARE_VECTOR_SWI

/* Note:
 *  1. Default, all software interrupt are disabled;
 *      use DRV_SWI_SetState() to enable it.
 *  2. Use DRV_SWI_SetInterrupt() to trigger the software interrupt.
 *  3. Maximum 256 software interrupts are supported.
 */

/*
DECLARE_VECTOR_SWI(SWI_TEST,
                   SWI_TEST_ISR,
                   "TEST SWI ISR")
*/

#endif

