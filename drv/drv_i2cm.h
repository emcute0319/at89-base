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
 *   drv_i2cm.h
 * DESCRIPTION:
 *   I2C Master Driver.
 * HISTORY:
 *   2010.2.2        panda.xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_I2CM_H
#define __DRV_I2CM_H


#if DRV_I2cM_SUPPORT

/*******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2cM_RandomWrite
 * DESCRIPTION:
 *      I2C Bus random write driver.
 * INPUT:
 *      vI2cAddr    : I2C chip address.
 *      vOffset     : I2C chip offset to be start to write.
 *      vDataLen    : I2C data buffer length to be written.
 *      aDataBuf    : I2C data buffer to be written.
 * OUTPUT:
 *      None
 * RETURN:
 *      TRUE        : I2C write success.
 *      FALSE       : I2C write fail.
 * NOTES:
 *      N/A
 * HISTORY:
 *      Ver1.00     2008.08.21      Panda Xiong         Create
 ******************************************************************************/
BOOL DRV_I2cM_RandomWrite
(
    IN        UINT8     vI2cAddr,
    IN        UINT8     vOffset,
    IN        UINT8     vDataLen,
    IN  const UINT8    *aDataBuf
);

/*******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2cM_RandomRead
 * DESCRIPTION:
 *      I2C Bus random read driver.
 * INPUT:
 *      vI2cAddr    : I2C chip address.
 *      vOffset     : I2C chip offset to be start to read.
 *      vDataLen    : I2C data buffer length to be read.
 * OUTPUT:
 *      aDataBuf    : I2C data buffer to be read.
 * RETURN:
 *      TRUE        : I2C read success.
 *      FALSE       : I2C read fail.
 * NOTES:
 *      N/A
 * HISTORY:
 *      Ver1.00     2008.08.21      Panda Xiong         Create
 ******************************************************************************/
BOOL DRV_I2cM_RandomRead
(
    IN  UINT8     vI2cAddr,
    IN  UINT8     vOffset,
    IN  UINT8     vDataLen,
    OUT UINT8    *aDataBuf
);

/*******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2cM_CurrentWrite
 * DESCRIPTION:
 *      I2C Bus write current driver.
 * INPUT:
 *      vI2cAddr    : I2C chip address.
 *      vDataLen    : I2C data buffer length to be write.
 * OUTPUT:
 *      aDataBuf    : I2C data buffer to be write.
 * RETURN:
 *      TRUE        : I2C write success.
 *      FALSE       : I2C write fail.
 * NOTES:
 *      N/A
 * HISTORY:
 *      Ver1.00     2008.08.21      Panda Xiong         Create
 ******************************************************************************/
BOOL DRV_I2cM_CurrentWrite
(
    IN       UINT8     vI2cAddr,
    IN       UINT8     vDataLen,
    IN const UINT8    *aDataBuf
);

/*******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2cM_CurrentRead
 * DESCRIPTION:
 *      I2C Bus read current driver.
 * INPUT:
 *      vI2cAddr    : I2C chip address.
 *      vDataLen    : I2C data buffer length to be read.
 * OUTPUT:
 *      aDataBuf    : I2C data buffer to be read.
 * RETURN:
 *      TRUE        : I2C read success.
 *      FALSE       : I2C read fail.
 * NOTES:
 *      N/A
 * HISTORY:
 *      Ver1.00     2008.08.21      Panda Xiong         Create
 ******************************************************************************/
BOOL DRV_I2cM_CurrentRead
(
    IN  UINT8     vI2cAddr,
    IN  UINT8     vDataLen,
    OUT UINT8    *aDataBuf
);

/*******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2cM_Detect
 * DESCRIPTION:
 *      I2C Bus chip detect driver.
 * INPUT:
 *      vI2cAddr    : I2C chip address.
 * OUTPUT:
 *      None
 * RETURN:
 *      GT_TRUE     : I2C chip is been detected.
 *      FALSE    : I2C chip is not been detected.
 * NOTES:
 *      N/A
 * HISTORY:
 *      Ver1.00     2008.08.21      Panda Xiong         Create
 *****************************************************************************/
BOOL DRV_I2cM_Detect
(
    IN UINT8    vI2cAddr
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2cM_Init
 * DESCRIPTION:
 *      I2C init driver.
 * PARAMETERS:
 *      None
 * RETURN:
 *      I2C Host Type.
 * NOTES:
 *      None
 * HISTORY:
 *      V1.00     2008.10.15     Panda Xiong       Create
 ******************************************************************************/
BOOL DRV_I2cM_Init
(
    void
);

#endif


#endif /* __DRV_I2CM_H */

