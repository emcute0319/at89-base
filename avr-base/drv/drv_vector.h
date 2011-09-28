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


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_VECTOR_T0_Overflow
 * DESCRIPTION:
 *      Timer0 overflow ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
INTERRUPT_PROTO(DRV_VECTOR_T0_Overflow, TIMER0_COMP);

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
#define DRV_Vector_Init()                                                   \
    do {                                                                    \
        /* remap the vector to the base address of flash */                 \
        GICR_IVSEL = 0;                                                     \
    } while (0)


#endif /* __DRV_VECTOR_H */

