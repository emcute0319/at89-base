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
 *   drv_i2cm.c
 * NODULE NAME:
 *   I2C Master Driver.
 * DESCRIPTION:
 *   This I2C Master Driver has been tested/verified at 1620-00101-00,
 *    with Pull-Up Resisters on SCL/SDA are both 30K ohm.
 *
 *   Note: If the Pull-Up Resisters on SCL/SDA are too large, such as 30K ohm,
 *          and, if you want to use oscilloscope to monitor the status on
 *           SCL/SDA, please DO select 'X10' mode of probes,
 *           or use High-impedance probes to monitor;
 *          else, cause there are too large capacity of probe added on SCL/SDA,
 *           the I2C Master Bus accessing may fail !!!
 * HISTORY:
 *   2009.08.26        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#include <drv.h>


#if DRV_I2cM_SUPPORT

/* =1, send I2C Stop at I2C Master Bus initializing;
 * =0, do not send I2C Stop. (default)
 */
#define DRV_I2cM_INIT_STOP_SUPPORT          (0)

/* =1, support Clock Stretch; (default)
 * =0, do not support clock stretch.
 */
#define DRV_I2cM_CLOCK_STRETCH_SUPPORT      (0)
#define DRV_I2cM_CLOCK_STRETCH_TIMEOUT      (25)    /* ms */

/* I2C Driver Porting part */
#if 1
/* Note:
 *  Add a short delay after write SCL/SDA,
 *  to make sure the I2C Master Bus speed is ~80KHz, when CPU clock is 41.78MHz.
 *
 *  And, this short delay is also very useful,
 *   while Pull-Up resister on SCL/SDA is too large,
 *   in this condition, the SCL/SDA may not be pull to 1, i.e. 3.3V;
 *  Thus, the Pull-Up resister on SCL/SDA should be designed to 1K-10K ohm,
 *   recommend to choice 4K-5K ohm !!!
 */
#define DRV_I2cM_Delay_Ms(vMs)      DRV_CPU_DelayMs(vMs)
#define DRV_I2cM_Delay_Us(vUs)      DRV_CPU_DelayUs(vUs)
#define DRV_I2cM_SET_SCL(vData)     do { DRV_IO_WritePinData(IO_PIN(I2cM_SCL), (vData)); DRV_I2cM_Delay_Us(1); } while (0)
#define DRV_I2cM_SET_SDA(vData)     do { DRV_IO_WritePinData(IO_PIN(I2cM_SDA), (vData)); DRV_I2cM_Delay_Us(1); } while (0)
#define DRV_I2cM_GET_SCL(vData)     DRV_IO_ReadPinData(IO_PIN(I2cM_SCL))
#define DRV_I2cM_GET_SDA(vData)     DRV_IO_ReadPinData(IO_PIN(I2cM_SDA))
#endif


/* low-level I2C driver */
#if 1

/* return : TRUE,  an ACK received;
 *          FALSE, no ACK received.
 */
static BOOL _drv_i2cm_CheckAck(void)
{
    BOOL vAck;

    DRV_I2cM_SET_SCL(0);
    DRV_I2cM_SET_SDA(1);
    DRV_I2cM_SET_SCL(1);
    vAck = DRV_I2cM_GET_SDA();
    DRV_I2cM_SET_SCL(0);

    return !vAck;
}


static void _drv_i2cm_SendAck(void)
{
    DRV_I2cM_SET_SCL(0);
    DRV_I2cM_SET_SDA(0);

    DRV_I2cM_SET_SCL(1);
    DRV_I2cM_SET_SCL(0);
    DRV_I2cM_SET_SDA(1);
}


static void _drv_i2cm_SendNoAck(void)
{
    DRV_I2cM_SET_SDA(1);
    DRV_I2cM_SET_SCL(1);
    DRV_I2cM_SET_SCL(0);
}

static BOOL _drv_i2cm_ReadBit(void)
{
    BOOL vBit;

    DRV_I2cM_SET_SCL(0);

    DRV_I2cM_SET_SCL(1);
    vBit = DRV_I2cM_GET_SDA();
    DRV_I2cM_SET_SCL(0);

    return vBit;
}

static void _drv_i2cm_WriteBit(IN BOOL vBit)
{
    DRV_I2cM_SET_SCL(0);
    DRV_I2cM_SET_SDA(vBit);
    DRV_I2cM_SET_SCL(1);
}


static BOOL _drv_i2cm_SendData(IN UINT8 vData)
{
    UINT8   vLoop;

    for (vLoop = 8; vLoop > 0; vLoop--)
    {
        _drv_i2cm_WriteBit(READ_BIT(vData, vLoop-1));
    }

#if DRV_I2cM_CLOCK_STRETCH_SUPPORT
{
    UINT8   vTimeoutCount = 0;

    /* check I2C Slave is stretching the clock line */
    while (DRV_I2cM_GET_SCL() == 0)
    {
        if (vTimeoutCount++ > DRV_I2cM_CLOCK_STRETCH_TIMEOUT)
        {
            return FALSE;
        }

        DRV_I2cM_Delay_Ms(1);
    }
}
#endif

    return _drv_i2cm_CheckAck();
}


static BOOL _drv_i2cm_ReceiveData(OUT UINT8 *pData)
{
    UINT8   vLoop;
    UINT8   vData = 0;

    for (vLoop = 8; vLoop > 0; vLoop--)
    {
        vData <<= 1;
        vData  |= _drv_i2cm_ReadBit();
    }

    *pData = vData;
    _drv_i2cm_SendAck();

    return TRUE;
}


static BOOL _drv_i2cm_ReceiveLastData(OUT UINT8 *pData)
{
    UINT8   vLoop;
    UINT8   vData = 0;

    for (vLoop = 8; vLoop > 0; vLoop--)
    {
        vData <<= 1;
        vData  |= _drv_i2cm_ReadBit();
    }

    *pData = vData;
    _drv_i2cm_SendNoAck();

    return TRUE;
}


static BOOL _drv_i2cm_SendAddr_R(IN UINT8 vI2cAddr)
{
    UINT8   vData;

    vData = vI2cAddr;
    SET_BIT(vData, 0);

    return _drv_i2cm_SendData(vData);
}


static BOOL _drv_i2cm_SendAddr_W(IN UINT8 vI2cAddr)
{
    UINT8   vData;

    vData = vI2cAddr;
    CLR_BIT(vData, 0);

    return _drv_i2cm_SendData(vData);
}


static BOOL _drv_i2cm_Start(void)
{
    /* I2C Start/ReStart:
     *   SDA changed from HIGH(1) to LOW(0), while SCL is HIGH(1).
     */
    DRV_I2cM_SET_SDA(1);
    DRV_I2cM_SET_SCL(1);
    DRV_I2cM_SET_SDA(0);
    DRV_I2cM_SET_SCL(0);

    return TRUE;
}


static BOOL _drv_i2cm_ReStart(void)
{
    return _drv_i2cm_Start();
}


static void _drv_i2cm_Stop(void)
{
    /* Note: this is a I2C Start, if current SCL/SDA is HIGH;
     *       this will only happen while initializing I2C Master Bus.
     */
    DRV_I2cM_SET_SDA(0);
    DRV_I2cM_SET_SCL(0);

    /* I2C Stop:
     *   SDA changed from LOW(0) to HIGH(1), while SCL is HIGH(1).
     */
    DRV_I2cM_SET_SCL(1);
    DRV_I2cM_SET_SDA(1);
}


/* check I2C hardware is ready to operate or not */
static BOOL _drv_i2cm_CheckReady(void)
{
    BOOL    bResult;

    if ((DRV_I2cM_GET_SCL() == 1)
        && (DRV_I2cM_GET_SDA() == 1))
    {
        /* The I2C only can be started, while SCL/SDA is at high level */
        bResult = TRUE;
    }
    else
    {
        /* SCL/SDA is been stretched, operation fail */
        bResult = FALSE;
    }

    return bResult;
}


/******************************************************************************
 * FUNCTION NAME:
 *      drv_i2cm_Init
 * DESCRIPTION:
 *      Init I2C.
 * PARAMETERS:
 *      None
 * RETURN:
 *      None
 * NOTES:
 *      None
 * HISTORY:
 *      V1.00     2008.12.5     Panda Xiong       Create
 ******************************************************************************/
static BOOL _drv_i2cm_Init(void)
{
    /* force stop all operations on I2C bus */
    _drv_i2cm_Stop();

    return TRUE;
}

#endif


#if 1

static volatile BOOL b_locked = FALSE;

static BOOL drv_i2cm_Open(void)
{
    if (b_locked)
    {
        /* if I2cM bus is busy, and interrupt is occur,
         * force I2cM bus reset.
         */
        _drv_i2cm_Init();
    }
    else
    {
        /* set flag, to indicate the I2cM bus is busy */
        b_locked = TRUE;
    }

    return TRUE;
}

static BOOL drv_i2cm_Close(void)
{
    if (b_locked)
    {
        /* unlock I2cM bus */
        b_locked = FALSE;

        return TRUE;
    }
    else
    {
        /* this transferring is been interrupted,
         * assume transferring fail.
         */
        return FALSE;
    }
}

#define DRV_I2cM_OPEN_DEVICE(err_return)    \
    do {                                    \
        if (!drv_i2cm_Open())               \
            return (err_return);            \
    } while (0)

#define DRV_I2cM_CLOSE_DEVICE(err_return)   \
    do {                                    \
        if (!drv_i2cm_Close())              \
            return (err_return);            \
    } while (0)

#endif


#if 1

/******************************************************************************
 * FUNCTION NAME:
 *      drv_i2cm_ReadBytes
 * DESCRIPTION:
 *      Read one or more bytes, with/without offset.
 * PARAMETERS:
 *      vI2cAddr   : I2C slave chip address.
 *      vOffsetLen : offset buffer length to be send.
 *      aOffsetBuf : offset buffer.
 *      vDataLen   : data length to be read.
 *      aDataBuf   : data buffer.
 * RETURN:
 *      TRUE   : read success.
 *      FALSE  : read fail.
 * NOTES:
 *      None
 * HISTORY:
 *      V1.00     2008.12.5     Panda Xiong       Create
 ******************************************************************************/
static BOOL drv_i2cm_ReadBytes
(
    IN       UINT8       vI2cAddr,
    IN       UINT8       vOffsetLen,
    IN const UINT8      *aOffsetBuf,
    IN       UINT8       vDataLen,
    OUT      UINT8      *aDataBuf
)
{
    UINT8      vLoop;

    /* make sure the IIC is ready */
    if (!_drv_i2cm_CheckReady())
    {
        goto _error_exit;
    }

    /* send IIC start */
    if (!_drv_i2cm_Start())
    {
        goto _error_exit;
    }

    if (vOffsetLen > 0)
    {
        /* send IIC chip address, and check ACK */
        if (!_drv_i2cm_SendAddr_W(vI2cAddr))
        {
            goto _error_exit;
        }

        /* send offset */
        for (vLoop = 0; vLoop < vOffsetLen; vLoop++)
        {
            /* send offset, and check ACK */
            if (!_drv_i2cm_SendData(aOffsetBuf[vLoop]))
            {
                goto _error_exit;
            }
        }

        /* IIC repeat start */
        if (!_drv_i2cm_ReStart())
        {
            goto _error_exit;
        }
    }

    /* send IIC chip address, and check ACK */
    if (!_drv_i2cm_SendAddr_R(vI2cAddr))
    {
        goto _error_exit;
    }

    /* read data */
    for (vLoop = 0; vLoop < vDataLen; vLoop++)
    {
        /* if it's the last byte data, don't send ACK */
        if (vLoop == (vDataLen - 1))
        {
            if (!_drv_i2cm_ReceiveLastData(&aDataBuf[vLoop]))
            {
                goto _error_exit;
            }
        }
        else
        {
            /* normal read data */
            if (!_drv_i2cm_ReceiveData(&aDataBuf[vLoop]))
            {
                goto _error_exit;
            }
        }
    }

/* success exit */
    /* send IIC stop */
    _drv_i2cm_Stop();
    return TRUE;

_error_exit:
    /* we should reset the I2C, or the I2C bus will keep on fail */
    _drv_i2cm_Init();
    return FALSE;
}


/******************************************************************************
 * FUNCTION NAME:
 *      drv_i2cm_WriteBytes
 * DESCRIPTION:
 *      Write one or more bytes, with/without offset.
 * PARAMETERS:
 *      vI2cAddr    : I2C slave chip address.
 *      vOffsetLen  : offset buffer length to be send.
 *      aOffsetBuf  : offset buffer.
 *      aDataBuf    : data length to be write.
 *      data_buf    : data buffer.
 * RETURN:
 *      TRUE   : write success.
 *      FALSE  : write fail.
 * NOTES:
 *      None
 * HISTORY:
 *      V1.00     2008.12.5     Panda Xiong       Create
 ******************************************************************************/
static BOOL drv_i2cm_WriteBytes
(
    IN       UINT8       vI2cAddr,
    IN       UINT8       vOffsetLen,
    IN const UINT8      *aOffsetBuf,
    IN       UINT8       vDataLen,
    IN const UINT8      *aDataBuf
)
{
    UINT8   vLoop;

    /* make sure the IIC is ready */
    if (!_drv_i2cm_CheckReady())
    {
        goto _error_exit;
    }

    /* send IIC start */
    if (!_drv_i2cm_Start())
    {
        goto _error_exit;
    }

    /* send IIC chip address, and check ACK */
    if (!_drv_i2cm_SendAddr_W(vI2cAddr))
    {
        goto _error_exit;
    }

    /* send offset */
    for (vLoop = 0; vLoop < vOffsetLen; vLoop++)
    {
        /* send offset, and check ACK */
        if (!_drv_i2cm_SendData(aOffsetBuf[vLoop]))
        {
            goto _error_exit;
        }
    }

    /* send data */
    for (vLoop = 0; vLoop < vDataLen; vLoop++)
    {
        if (!_drv_i2cm_SendData(aDataBuf[vLoop]))
        {
            goto _error_exit;
        }
    }

/* success exit */
    /* send IIC stop */
    _drv_i2cm_Stop();
    return TRUE;

_error_exit:
    /* we should reset the I2C, or the I2C bus will keep on fail */
    _drv_i2cm_Init();
    return FALSE;
}


/*******************************************************************************
 * FUNCTION NAME:
 *      drv_i2cm_Detect
 * DESCRIPTION:
 *      I2C detect chip.
 * PARAMETERS:
 *      vI2cAddr : I2C chip address.
 * RETURN:
 *      None
 * NOTES:
 *      None
 * HISTORY:
 *      V1.00     2009.1.16     Panda Xiong       Create
 ******************************************************************************/
static BOOL drv_i2cm_Detect
(
    IN UINT8    vI2cAddr
)
{
    /* make sure the IIC is ready */
    if (!_drv_i2cm_CheckReady())
    {
        goto _error_exit;
    }

    /* send IIC start */
    if (!_drv_i2cm_Start())
    {
        goto _error_exit;
    }

    /* send IIC chip address, and check ACK */
    if (!_drv_i2cm_SendAddr_W(vI2cAddr))
    {
        goto _error_exit;
    }

/* success exit */
    /* send IIC stop */
    _drv_i2cm_Stop();
    return TRUE;

_error_exit:
    /* we should reset the I2C, or the I2C bus will keep on fail */
    _drv_i2cm_Init();
    return FALSE;
}

#endif


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
)
{
    BOOL    vResult;

    if ((aDataBuf == NULL) || (vDataLen == 0))
    {
        return FALSE;
    }

    DRV_I2cM_OPEN_DEVICE(FALSE);
    vResult = drv_i2cm_WriteBytes(vI2cAddr, 1, &vOffset, vDataLen, aDataBuf);
    DRV_I2cM_CLOSE_DEVICE(FALSE);

    return vResult;
}


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
)
{
    BOOL    vResult;

    if ((aDataBuf == NULL) || (vDataLen == 0))
    {
        return FALSE;
    }

    DRV_I2cM_OPEN_DEVICE(FALSE);
    vResult = drv_i2cm_ReadBytes(vI2cAddr, 1, &vOffset, vDataLen, aDataBuf);
    DRV_I2cM_CLOSE_DEVICE(FALSE);

    return vResult;
}


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
)
{
    BOOL    vResult;

    if ((aDataBuf == NULL) || (vDataLen == 0))
    {
        return FALSE;
    }

    DRV_I2cM_OPEN_DEVICE(FALSE);
    vResult = drv_i2cm_WriteBytes(vI2cAddr, 0, NULL, vDataLen, aDataBuf);
    DRV_I2cM_CLOSE_DEVICE(FALSE);

    return vResult;
}


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
)
{
    BOOL    vResult;

    if ((aDataBuf == NULL) || (vDataLen == 0))
    {
        return FALSE;
    }

    DRV_I2cM_OPEN_DEVICE(FALSE);
    vResult = drv_i2cm_ReadBytes(vI2cAddr, 0, NULL, vDataLen, aDataBuf);
    DRV_I2cM_CLOSE_DEVICE(FALSE);

    return vResult;
}


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
)
{
    BOOL    vResult;

    DRV_I2cM_OPEN_DEVICE(FALSE);
    vResult = drv_i2cm_Detect(vI2cAddr);
    DRV_I2cM_CLOSE_DEVICE(FALSE);

    return vResult;
}


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
)
{
#if DRV_I2cM_INIT_STOP_SUPPORT

    BOOL    vResult;

    DRV_I2cM_OPEN_DEVICE(FALSE);
    vResult = _drv_i2cm_Init();
    DRV_I2cM_CLOSE_DEVICE(FALSE);

    return vResult;

#else
    return TRUE;
#endif
}

#endif

