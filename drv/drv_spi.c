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

#define DRV_SPI_IO_Read(_io)    DRV_IO_Read(_io)

#define DRV_SPI_IO_Write(_io, _state)                                   \
    do {                                                                \
        DRV_IO_Write((_io), (_state));                                  \
                                                                        \
        /* wait until the output IO state is stable */                  \
        while (DRV_SPI_IO_Read(_io) != (_state))                        \
        {}                                                              \
    } while (0)

#define DRV_SPI_FixReadDutyCycle()                                      \
    do {                                                                \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
    } while (0)

#define DRV_SPI_FixWriteDutyCycle()                                     \
    do {                                                                \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
        NOP();                                                          \
    } while (0)

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
)
{
    while (vByteLen--)
    {
        *pBuf++ = DRV_SPI_ReadByte();
    }
}


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
)
{
    while (vByteLen--)
    {
        DRV_SPI_WriteByte(*pBuf++);
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_ReadByte
 * DESCRIPTION:
 *      Read 1 Bytes data, via SPI Bus.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      The read 1 Byte data.
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.5.26        Panda.Xiong         Create/Update
 *****************************************************************************/
UINT8 DRV_SPI_ReadByte(void)
{
	UINT8   vData;
	UINT8   vBitIndex;

	vData = 0x00;
    for (vBitIndex = 8; vBitIndex != 0; vBitIndex--)
    {
        /* Generate one clock, to tell SPI Slave to send one bit data */
        DRV_SPI_IO_Write(IO_PIN(SPI_SCK), IO_SPI_SCK_ACTIVE);
        DRV_SPI_FixReadDutyCycle();
        DRV_SPI_IO_Write(IO_PIN(SPI_SCK), IO_SPI_SCK_INACTIVE);

        /* Sample data: MSB first, LSB last */
        vData <<= 1;
        vData |= DRV_SPI_IO_Read(IO_PIN(SPI_MISO));
	}

	return vData;
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SPI_WriteByte
 * DESCRIPTION:
 *      Write 1 Bytes data, via SPI Bus.
 * PARAMETERS:
 *      vData : Write data buffer.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2009.5.26        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_SPI_WriteByte(IN UINT8 vData)
{
	UINT8   vBitIndex;

    for (vBitIndex = 8; vBitIndex != 0; vBitIndex--)
    {
        /* Transmitting data, MSB first, LSB last */
        _CROL(vData, 1);
        DRV_SPI_IO_Write(IO_PIN(SPI_MOSI), (vData & 0x1));

        /* Generate one clock, to tell SPI Slave one bit data is ready */
        DRV_SPI_IO_Write(IO_PIN(SPI_SCK), IO_SPI_SCK_ACTIVE);
        DRV_SPI_FixWriteDutyCycle();
        DRV_SPI_IO_Write(IO_PIN(SPI_SCK), IO_SPI_SCK_INACTIVE);
	}
}

#endif

