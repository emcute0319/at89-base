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
 *   drv_vector.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.3.23        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_VECTOR_H
#define __DRV_VECTOR_H


/* Keil C51 interrupt ID definition.
 *
 * Note: for Keil C51, the ISR entry address is listed as below:
 *        ID0  : 0x0003
 *        ID1  : 0x000B
 *        ID2  : 0x0013
 *        ID3  : 0x001B
 *        ID4  : 0x0023
 *        ID5  : 0x002B
 *        ...
 */
#define VECTOR_ID_INT0      0  /* External Interrupt 0  */
#define VECTOR_ID_TIMER0    1  /* Timer 0               */
#define VECTOR_ID_INT1      2  /* External Interrupt 1  */
#define VECTOR_ID_TIMER1    3  /* Timer 1               */
#define VECTOR_ID_UART0     4  /* UART 0                */

#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
 #define VECTOR_ID_TIMER2   5  /* Timer 2               */
#endif

/* register group definition */
#define REG_GROUP_0         0           /* register group 0 */
#define REG_GROUP_1         1           /* register group 1 */
#define REG_GROUP_2         2           /* register group 2 */
#define REG_GROUP_3         3           /* register group 3 */
#define REG_GROUP_DEFAULT   REG_GROUP_0 /* register group 0 */


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_Vector_Init
 * DESCRIPTION:
 *      Vector Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.7.2        Panda.Xiong         Create/Update
 *****************************************************************************/
#define DRV_Vector_Init()       /* empty */


#endif /* __DRV_VECTOR_H */

