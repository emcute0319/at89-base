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
 *   2009.8.26        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_I2CM_H
#define __DRV_I2CM_H


#if DRV_I2CM_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2cM_ReadBytes
 * DESCRIPTION:
 *      Random read one or more bytes data.
 * PARAMETERS:
 *      vI2cAddr   : I2C slave chip address.
 *      vOffset    : Read start offset.
 *      vDataLen   : data length to be read.
 *      aDataBuf   : data buffer.
 * RETURN:
 *      TRUE   : read success.
 *      FALSE  : read fail.
 * NOTES:
 *      None
 * HISTORY:
 *      2009.1.16     Panda Xiong       Create
 ******************************************************************************/
BOOL DRV_I2CM_ReadBytes
(
    IN  UINT8   vI2cAddr,
    IN  UINT8   vOffset,
    IN  UINT8   vDataLen,
    OUT UINT8  *aDataBuf
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2cM_ReadByte
 * DESCRIPTION:
 *      Random read byte.
 * PARAMETERS:
 *      vI2cAddr : I2C slave chip address.
 *      vOffset  : Read start offset.
 *      pData    : data read buffer.
 * RETURN:
 *      TRUE   : read success.
 *      FALSE  : read fail.
 * NOTES:
 *      None
 * HISTORY:
 *      2009.1.16     Panda Xiong       Create
 ******************************************************************************/
#define DRV_I2CM_ReadByte(_vI2cAddr, _vOffset, _pData)                      \
    DRV_I2CM_ReadBytes((_vI2cAddr), (_vOffset), 1, (_pData))

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2cM_WriteBytes
 * DESCRIPTION:
 *      Random write one or more bytes data.
 * PARAMETERS:
 *      vI2cAddr    : I2C slave chip address.
 *      vOffset     : write start offset.
 *      aDataBuf    : data length to be write.
 *      data_buf    : data buffer.
 * RETURN:
 *      TRUE   : write success.
 *      FALSE  : write fail.
 * NOTES:
 *      None
 * HISTORY:
 *      2009.1.16     Panda Xiong       Create
 ******************************************************************************/
BOOL DRV_I2CM_WriteBytes
(
    IN       UINT8  vI2cAddr,
    IN       UINT8  vOffset,
    IN       UINT8  vDataLen,
    IN const UINT8 *aDataBuf
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2cM_WriteByte
 * DESCRIPTION:
 *      Random write one byte data.
 * PARAMETERS:
 *      vI2cAddr : I2C slave chip address.
 *      vOffset  : write start offset.
 *      vData    : data to be written.
 * RETURN:
 *      TRUE   : write success.
 *      FALSE  : write fail.
 * NOTES:
 *      None
 * HISTORY:
 *      2009.1.16     Panda Xiong       Create
 ******************************************************************************/
#define DRV_I2CM_WriteByte(_vI2cAddr, _vOffset, _vData)                     \
    DRV_I2CM_WriteBytes((_vI2cAddr), (_vOffset), 1, &vData)

/*******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2CM_Probe
 * DESCRIPTION:
 *      Probe I2C slave chip.
 * PARAMETERS:
 *      vI2cAddr : I2C slave chip address.
 * RETURN:
 *      None
 * NOTES:
 *      None
 * HISTORY:
 *      2009.1.16     Panda Xiong       Create
 ******************************************************************************/
BOOL DRV_I2CM_Probe(IN UINT8 vI2cAddr);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2cM_Init
 * DESCRIPTION:
 *      I2C init driver.
 * PARAMETERS:
 *      None
 * RETURN:
 *      None
 * NOTES:
 *      None
 * HISTORY:
 *      2009.8.26     Panda Xiong       Create
 ******************************************************************************/
void DRV_I2CM_Init(void);

#endif


#endif /* __DRV_I2CM_H */

