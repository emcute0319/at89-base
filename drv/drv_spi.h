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
 *   drv_spi.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.2.2        panda.xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_SPI_H
#define __DRV_SPI_H


#if DRV_SPI_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_Open
 * DESCRIPTION:
 *      Open SPI bus.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      TRUE    : Open SPI bus success.
 *      FALSE   : Open SPI bus fail.
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.5.26        Panda.Xiong         Create/Update
 *****************************************************************************/
BOOL DRV_SPI_Open
(
    void
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_ReadBytes
 * DESCRIPTION:
 *      Read SPI data.
 * PARAMETERS:
 *      vByteLen  : Read data byte length.
 *      pBuf      : Read data buffer.
 * RETURN:
 *      TRUE    : Read SPI data success.
 *      FALSE   : Read SPI data fail.
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.5.26        Panda.Xiong         Create/Update
 *****************************************************************************/
BOOL DRV_SPI_ReadBytes
(
    IN  UINT32      vByteLen,
    OUT UINT8      *pBuf
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_WriteBytes
 * DESCRIPTION:
 *      Write SPI data.
 * PARAMETERS:
 *      vByteLen  : Write data byte length.
 *      pBuf      : Write data buffer.
 * RETURN:
 *      TRUE    : Write SPI data success.
 *      FALSE   : Write SPI data fail.
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.5.26        Panda.Xiong         Create/Update
 *****************************************************************************/
BOOL DRV_SPI_WriteBytes
(
    IN       UINT32     vByteLen,
    IN const UINT8     *pBuf
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_Close
 * DESCRIPTION:
 *      Close SPI bus.
 * PARAMETERS:
 *      vSpiId  : SPI bus ID.
 * RETURN:
 *      TRUE    : Close SPI bus success.
 *      FALSE   : Close SPI bus fail.
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.5.26        Panda.Xiong         Create/Update
 *****************************************************************************/
BOOL DRV_SPI_Close
(
    void
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_Init
 * DESCRIPTION:
 *      SPI Driver Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.4.10        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_SPI_Init(void);

#endif


#endif /* __DRV_SPI_H */

