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
 *   drv_temp.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2011.9.11        panda.xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_TEMP_H
#define __DRV_TEMP_H


#if DRV_TEMP_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_Temp_GetTemp
 * DESCRIPTION:
 *      Get Temperature.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      The read temperature:
 *       Bit[15]   : =0, read temperature success;
 *                   =1, read temperature fail;
 *       Bit[14:0] : The read temperature;
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.9.11        panda.xiong         Create/Update
 *****************************************************************************/
UINT16 DRV_Temp_GetTemp(void);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_Temp_Init
 * DESCRIPTION:
 *      Init temperature driver.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.9.11        panda.xiong         Create/Update
 *****************************************************************************/
void DRV_Temp_Init(void);

#endif


#endif /* __DRV_TEMP_H */


