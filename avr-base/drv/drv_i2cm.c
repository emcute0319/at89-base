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

#include "drv.h"


#if DRV_I2CM_SUPPORT

/* =1, send I2C Stop at I2C Master Bus initializing;
 * =0, do not send I2C Stop. (default)
 */
#define DRV_I2CM_INIT_STOP_SUPPORT          (0)

/* I2C Driver Porting part */
#if 1
/* Note:
 *  And, this short delay is also very useful,
 *   while Pull-Up resister on SCL/SDA is too large,
 *   in this condition, the SCL/SDA may not be pull to 1, i.e. 3.3V;
 *  Thus, the Pull-Up resister on SCL/SDA should be designed to 1K-10K ohm,
 *   recommend to choice 4K-5K ohm !!!
 */
#define DRV_I2CM_Delay_Us(_us)      DRV_CPU_DelayUs(_us)
#define DRV_I2CM_SET_SCL(_data)     do { DRV_IO_Write(IO(I2CM_SCL), (_data)); if (_data) {DRV_I2CM_Delay_Us(1);} } while (0)
#define DRV_I2CM_SET_SDA(_data)     do { DRV_IO_Write(IO(I2CM_SDA), (_data)); if (_data) {DRV_I2CM_Delay_Us(1);} } while (0)
#define DRV_I2CM_GET_SCL()          DRV_IO_Read(IO(I2CM_SCL))
#define DRV_I2CM_GET_SDA()          DRV_IO_Read(IO(I2CM_SDA))
#endif


/* low-level I2C driver */
#if 1

/* return : TRUE,  an ACK received;
 *          FALSE, no ACK received.
 */
static BOOL _drv_i2cm_SendByte(UINT8 vData)
{
    UINT8   vLoop;
    BOOL    vAck;

    /* Send Byte Data: MSB first, LSB last */
    for (vLoop = 8; vLoop != 0; vLoop--)
    {
        CROL(vData, 1);
        DRV_I2CM_SET_SDA((vData & 0x1));

        DRV_I2CM_SET_SCL(1);
        DRV_I2CM_SET_SCL(0);
    }

    /* release SDA */
    DRV_I2CM_SET_SDA(1);

    /* check ACK */
    DRV_I2CM_SET_SCL(1);
    vAck = DRV_I2CM_GET_SDA();
    DRV_I2CM_SET_SCL(0);

    return !vAck;
}

static UINT8 _drv_i2cm_ReceiveByte(void)
{
    UINT8   vLoop;
    UINT8   vData = 0;

    /* Receive Byte Data: MSB first, LSB last */
    for (vLoop = 8; vLoop != 0; vLoop--)
    {
        DRV_I2CM_SET_SCL(1);
        vData <<= 1;
        vData |= DRV_I2CM_GET_SDA();
        DRV_I2CM_SET_SCL(0);
    }

    return vData;
}

#define _drv_i2cm_SendAck(_ack)                                             \
    do {                                                                    \
        /* send ACK */                                                      \
        DRV_I2CM_SET_SDA(_ack);                                             \
                                                                            \
        /* generate one clock */                                            \
        DRV_I2CM_SET_SCL(1);                                                \
        DRV_I2CM_SET_SCL(0);                                                \
                                                                            \
        /* release SDA */                                                   \
        DRV_I2CM_SET_SDA(1);                                                \
    } while (0)

#define _drv_i2cm_Start()                                                   \
    do {                                                                    \
        /* I2C Start/ReStart:                                               \
         *   SDA changed from HIGH(1) to LOW(0), while SCL is HIGH(1).      \
         */                                                                 \
        DRV_I2CM_SET_SDA(1);                                                \
        DRV_I2CM_SET_SCL(1);                                                \
        DRV_I2CM_SET_SDA(0);                                                \
        DRV_I2CM_SET_SCL(0);                                                \
    } while (0)

#define _drv_i2cm_ReStart()     _drv_i2cm_Start()

#define _drv_i2cm_Stop()                                                    \
    do {                                                                    \
        /* Note: this is a I2C Start, if current SCL/SDA is HIGH;           \
         *       this will only happen while initializing I2C Master Bus.   \
         */                                                                 \
        DRV_I2CM_SET_SDA(0);                                                \
        DRV_I2CM_SET_SCL(0);                                                \
                                                                            \
        /* I2C Stop:                                                        \
         *   SDA changed from LOW(0) to HIGH(1), while SCL is HIGH(1).      \
         */                                                                 \
        DRV_I2CM_SET_SCL(1);                                                \
        DRV_I2CM_SET_SDA(1);                                                \
    } while (0)

#define _drv_i2cm_Init()                                                    \
    do {                                                                    \
        /* force stop all operations on I2C bus */                          \
        _drv_i2cm_Stop();                                                   \
    } while (0)

/* check I2C hardware is ready to operate or not */
static BOOL _drv_i2cm_CheckReady(void)
{
    BOOL    bResult = FALSE;

    if ((DRV_I2CM_GET_SCL() == 1)
        && (DRV_I2CM_GET_SDA() == 1))
    {
        /* The I2C only can be started, while SCL/SDA is at high level */
        bResult = TRUE;
    }
    else if ((DRV_I2CM_GET_SCL() == 1)
            && (DRV_I2CM_GET_SDA() == 0))
    {
        /* SCL line is OK, but SDA line has been stretched by I2C Slave,
         *  we should attempt to reset the I2C Bus,
         *  to recover the SDA to idle state.
         *
         * According to SFF-8431 & INF-8077 Spec,
         *  we can follow below steps to recover SDA line:
         *
         *   Memory (Management Interface) Reset:
         *    1) Clock up to 9 cycles.
         *    2) Look for SDA high in each cycle while SCL is high.
         *    3) Create a START condition as SDA is high.
         */

        UINT8   vLoop;

        for (vLoop = 9; vLoop > 0; vLoop--)
        {
            DRV_I2CM_SET_SCL(0);
            DRV_I2CM_SET_SCL(1);

            if (DRV_I2CM_GET_SDA() == 1)
            {
                /* we have successfully recover the SDA line to idle state */
                bResult = TRUE;
                break;
            }
        }
    }
    else
    {
        /* Unsupported stretching on SCL/SDA line, operation fail */
    }

    return bResult;
}

#endif


#if 1

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
)
{
    UINT8      vLoop;

    /* send I2C start */
    _drv_i2cm_Start();

    /* send I2C slave address + Write */
    CLR_BIT(vI2cAddr, 0);
    if (!_drv_i2cm_SendByte(vI2cAddr))
    {
        goto _error_exit;
    }

    /* send offset */
    if (!_drv_i2cm_SendByte(vOffset))
    {
        goto _error_exit;
    }

    /* send I2C repeat start */
    _drv_i2cm_ReStart();

    /* send I2C slave address + Read */
    SET_BIT(vI2cAddr, 0);
    if (!_drv_i2cm_SendByte(vI2cAddr))
    {
        goto _error_exit;
    }

    /* read data */
    for (vLoop = 0; vLoop < vDataLen-1; vLoop++)
    {
        aDataBuf[vLoop] = _drv_i2cm_ReceiveByte();
        _drv_i2cm_SendAck();    /* send ACK  */
    }

    /* read the last Byte data */
    aDataBuf[vLoop] = _drv_i2cm_ReceiveByte();
    _drv_i2cm_SendNoAck();      /* send NACK */

/* success exit */
    /* send I2C stop */
    _drv_i2cm_Stop();
    return TRUE;

_error_exit:
    /* we should reset the I2C, or the I2C bus will keep on fail */
    _drv_i2cm_Init();
    return FALSE;
}


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
)
{
    UINT8   vLoop;

    /* send I2C start */
    _drv_i2cm_Start();

    /* send I2C slave address + Write */
    CLR_BIT(vI2cAddr, 0);
    if (!_drv_i2cm_SendByte(vI2cAddr))
    {
        goto _error_exit;
    }

    /* send offset */
    if (!_drv_i2cm_SendByte(vOffset))
    {
        goto _error_exit;
    }

    /* send data */
    for (vLoop = 0; vLoop < vDataLen; vLoop++)
    {
        if (!_drv_i2cm_SendByte(aDataBuf[vLoop]))
        {
            goto _error_exit;
        }
    }

/* success exit */
    /* send I2C stop */
    _drv_i2cm_Stop();
    return TRUE;

_error_exit:
    /* we should reset the I2C, or the I2C bus will keep on fail */
    _drv_i2cm_Init();
    return FALSE;
}


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
BOOL DRV_I2CM_Probe(IN UINT8 vI2cAddr)
{
    /* send I2C start */
    _drv_i2cm_Start();

    /* send I2C slave address + Write */
    CLR_BIT(vI2cAddr, 0);
    if (!_drv_i2cm_SendByte(vI2cAddr))
    {
        goto _error_exit;
    }

/* success exit */
    /* send I2C stop */
    _drv_i2cm_Stop();
    return TRUE;

_error_exit:
    /* we should reset the I2C, or the I2C bus will keep on fail */
    _drv_i2cm_Init();
    return FALSE;
}


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
void DRV_I2CM_Init(void)
{
  #if DRV_I2CM_INIT_STOP_SUPPORT
    _drv_i2cm_Init();
  #endif
}

#endif

#endif

