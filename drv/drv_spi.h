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

/* default, the SPI SCK pin is active high */
#ifdef DRV_SPI_SCK_ACTIVE_LOW
 #define IO_SPI_SCK_ACTIVE     LOW
 #define IO_SPI_SCK_INACTIVE   HIGH
#else
 #define IO_SPI_SCK_ACTIVE     HIGH
 #define IO_SPI_SCK_INACTIVE   LOW
#endif

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_Open
 * DESCRIPTION:
 *      Open SPI bus.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.5.26        Panda.Xiong         Create/Update
 *****************************************************************************/
#define DRV_SPI_Open()                                                      \
    do {                                                                    \
        if (DRV_IO_Read(IO_PIN(SPI_nCS)) == LOW)                            \
        {                                                                   \
            /* SPI has been opened, we should close it first,               \
             *  to force aborting the previous transmitting.                \
             */                                                             \
            DRV_SPI_Close();                                                \
        }                                                                   \
                                                                            \
        /* enable SPI transfer */                                           \
        DRV_IO_Write(IO_PIN(SPI_nCS), LOW);                                 \
    } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_Close
 * DESCRIPTION:
 *      Close SPI bus.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.5.26        Panda.Xiong         Create/Update
 *****************************************************************************/
#define DRV_SPI_Close()                                                     \
    do {                                                                    \
        /* Set SPI_CSB as high to deactive the transaxtion */               \
        DRV_IO_Write(IO_PIN(SPI_nCS), HIGH);                                \
    } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_IsSuccess
 * DESCRIPTION:
 *      Check this transmitting is successful or not.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      TRUE  : Success;
 *      FALSE : Fail.
 * NOTES:
 *      If SPI_nCS is not low, means this SPI transfering has been interrupted,
 *       thus, assume this SPI transfering fail.
 * HISTORY:
 *      2009.5.26        Panda.Xiong         Create/Update
 *****************************************************************************/
#define DRV_SPI_IsSuccess()    (DRV_IO_Read(IO_PIN(SPI_nCS)) == LOW)

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_ReadBytes
 * DESCRIPTION:
 *      Read n Bytes data, via SPI Bus.
 * PARAMETERS:
 *      vByteLen  : Read data byte length.
 *      pBuf      : Read data buffer.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.5.26        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_SPI_ReadBytes
(
    IN  UINT8   vByteLen,
    OUT UINT8  *pBuf
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_WriteBytes
 * DESCRIPTION:
 *      Write n Bytes data, via SPI Bus.
 * PARAMETERS:
 *      vByteLen  : Write data byte length.
 *      pBuf      : Write data buffer.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.5.26        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_SPI_WriteBytes
(
    IN       UINT8      vByteLen,
    IN const UINT8     *pBuf
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_ReadByte
 * DESCRIPTION:
 *      Read 1 Bytes data, via SPI Bus.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      return the read data
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.5.26        Panda.Xiong         Create/Update
 *****************************************************************************/
UINT8 DRV_SPI_ReadByte
(
    void
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_WriteByte
 * DESCRIPTION:
 *      Write 1 Bytes data, via SPI Bus.
 * PARAMETERS:
 *      vData      : Write data buffer.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.5.26        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_SPI_WriteByte
(
    IN       UINT8      vData
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
#define DRV_SPI_Init()                                                      \
    do {                                                                    \
        /* Close SPI Bus, to disable SPI transfer */                        \
        DRV_SPI_Close();                                                    \
                                                                            \
        /* Make sure the SCK pin is inactive state */                       \
        DRV_IO_Write(IO_PIN(SPI_SCK), IO_SPI_SCK_INACTIVE);                 \
    } while (0)

#endif


#endif /* __DRV_SPI_H */

