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
 *   drv_spi.c
 * DESCRIPTION:
 *   SPI Driver.
 * HISTORY:
 *   2010.2.2        panda.xiong         Create/Update
 *
*****************************************************************************/

#include <drv.h>


#if DRV_SPI_SUPPORT

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
)
{
    UINT32  vLoop, vBitIndex;
    UINT8   vData;

    if (pBuf == NULL)
    {
        return FALSE;
    }

    /* enable SPI transfer */
    DRV_IO_Write(IO_PIN(SPI_nCS), LOW);

    /* add a short delay after enable SPI transferring,
     * cause some SPI slaves need some time to be ready.
     */
    DRV_CPU_DelayUs(20);

    for (vLoop = 0; vLoop < vByteLen; vLoop++)
    {
        vData = 0x00;
        for (vBitIndex = 8; vBitIndex > 0; vBitIndex--)
        {
            /* Output serial data is clocked out on the falling
             *  edge of the SPI clock.
             */
            DRV_IO_Write(IO_PIN(SPI_SCK), LOW);
            DRV_IO_Write(IO_PIN(SPI_SCK), HIGH);

            /* Read in the data on the rising edge of the clock */
            if (DRV_IO_Read(IO_PIN(SPI_MISO)))
            {
                SET_BIT(vData, vBitIndex-1);
            }
        }

        pBuf[vLoop] = vData;
    }

    /* disable SPI transfer */
    DRV_IO_Write(IO_PIN(SPI_nCS), HIGH);

    /* add a short delay after enable SPI transferring,
     * cause some SPI slaves need some time to be ready.
     */
    DRV_CPU_DelayUs(20);

    return TRUE;
}


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
)
{
    UINT32  vLoop, vBitIndex;

    if (pBuf == NULL)
    {
        return FALSE;
    }

    /* enable SPI transfer */
    DRV_IO_Write(IO_PIN(SPI_nCS), LOW);

    /* add a short delay after enable SPI transferring,
     * cause some SPI slaves need some time to be ready.
     */
    DRV_CPU_DelayUs(20);

    for (vLoop = 0; vLoop < vByteLen; vLoop++)
    {
        for (vBitIndex = 8; vBitIndex > 0; vBitIndex--)
        {
            /* Input serial data is captured on the rising edge
             *  of the SPI clock.
             */
            DRV_IO_Write(IO_PIN(SPI_SCK), LOW);

            /* Data is transmitted or received on the SPI port.
             * MSB first, LSB last.
             */
            DRV_IO_Write(IO_PIN(SPI_MISO),
                                READ_BIT(pBuf[vLoop], vBitIndex-1));

            DRV_IO_Write(IO_PIN(SPI_SCK), HIGH);
        }
    }

    /* disable SPI transfer */
    DRV_IO_Write(IO_PIN(SPI_nCS), HIGH);

    return TRUE;
}


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
void DRV_SPI_Init(void)
{
    /* Set SPI_nCS as high to deactive the transaxtion */
    DRV_IO_Write(IO_PIN(SPI_nCS), HIGH);

    /* Set MOSI and Clock to high as idle status */
    DRV_IO_Write(IO_PIN(SPI_SCK),  HIGH);
    DRV_IO_Write(IO_PIN(SPI_MOSI), HIGH);

    DRV_IO_SetInput(IO_PIN(SPI_MISO));
}

#endif

