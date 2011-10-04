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
 *   2011.10.4        PANDA         Create/Update
 *
*****************************************************************************/


#ifdef DECLARE_IO_PIN

/* IO pin Definition.
 *
 *   name      : IO pin name;
 *   port      : IO port ID;
 *   bit       : IO bit ID of port;
 *   mode      : IO input/output mode;
 *   init_val  : IO initial output value;
 *   pin_no    : IO hardware pin number;
 *   desc      : IO description;
 */

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

/* PORT A */
DECLARE_IO_PORT(LED_DATA_OUT,   _PORT(A),  "LED Data Output port")
/*               name        port bit      mode     init_val pin_no  desc  */
DECLARE_IO_PIN(LED_DATA_c,  _IO(A, 0),   IO_OUTPUT,     1,     12,  "LED Data Output: c: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_p,  _IO(A, 1),   IO_OUTPUT,     1,     13,  "LED Data Output: p: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_e,  _IO(A, 2),   IO_OUTPUT,     1,     14,  "LED Data Output: e: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_d,  _IO(A, 3),   IO_OUTPUT,     1,     15,  "LED Data Output: d: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_g,  _IO(A, 4),   IO_OUTPUT,     1,     16,  "LED Data Output: g: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_b,  _IO(A, 5),   IO_OUTPUT,     1,     17,  "LED Data Output: b: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_a,  _IO(A, 6),   IO_OUTPUT,     1,     18,  "LED Data Output: a: =0, Light; =1, Dark.")
DECLARE_IO_PIN(LED_DATA_f,  _IO(A, 7),   IO_OUTPUT,     1,     19,  "LED Data Output: f: =0, Light; =1, Dark.")

/* PORT B */
/*               name        port bit      mode     init_val pin_no  desc  */
DECLARE_IO_PIN(UART_RXD,    _IO(B, 0),   IO_INPUT,      1,      2,  "UART RXD Pin")
DECLARE_IO_PIN(UART_TXD,    _IO(B, 1),   IO_OUTPUT,     1,      3,  "UART TXD Pin")
DECLARE_IO_PIN(SPI_MISO,    _IO(B, 2),   IO_INPUT,      1,      8,  "MAX187 CS Pin: =0, select MAX187; =1, deselect MAX187.")
DECLARE_IO_PIN(SPI_CS,      _IO(B, 3),   IO_OUTPUT,     1,      9,  "MAX518 Serial Data Output Pin")
DECLARE_IO_PIN(LED_SEL_1,   _IO(B, 4),   IO_OUTPUT,     1,      6,  "LED Select 1: =0, select this LED; =1, deselect this LED.")
DECLARE_IO_PIN(LED_SEL_0,   _IO(B, 5),   IO_OUTPUT,     1,      7,  "LED Select 0: =0, select this LED; =1, deselect this LED.")
DECLARE_IO_PIN(SPI_MOSI,    _IO(B, 6),   IO_OUTPUT,     1,     NA,  "Unused Pin")
DECLARE_IO_PIN(SPI_SCK,     _IO(B, 7),   IO_OUTPUT,     1,     11,  "MAX518 Serial Clock Pin")

#endif



#ifdef DECLARE_ADC_CH

/* ADC Channel Definition.
 *
 *   name      : ADC channel name;
 *   pos_ch    : ADC positive channel;
 *   neg_ch    : ADC negative channel;
 *   cookie    : ADC channel cookie;
 *   desc      : ADC channel description;
 */

/*               name       adc_mux                                                               adc_prescale      desc  */
DECLARE_ADC_CH(ADC_VCC,  ADC_Vref_Internal | ADC_Result_RightAdjust | ADC_MUX_Single_VBG,       ADC_Prescale_128,  "VCC monitor")

#endif


