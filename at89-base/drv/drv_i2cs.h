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
 *   drv_i2cs.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2011.5.24        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_I2CS_H
#define __DRV_I2CS_H


#if DRV_I2CS_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2CS_SetInterruptedFlag
 * DESCRIPTION:
 *      Set interrupted flag for I2C Slave,
  *      while there is another higher interrupt occurrerd.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 * HISTORY:
 *      2011.5.24        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_I2CS_SetInterruptedFlag(void);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2CS_Init
 * DESCRIPTION:
 *      I2C Slave Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.5.24        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_I2CS_Init(void);

#endif


#endif /* __DRV_I2CS_H */

