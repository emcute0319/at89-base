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
 *   drv_i2cs.c
 * DESCRIPTION:
 *   1. Currently, only support MCS-51 MCU under Keil compiler environment.
 *   2. The SDA line must on the Ext. Interrupt,
 *        which is used by this I2C Slave driver.
 * HISTORY:
 *   2011.5.24        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#include "drv.h"


#if DRV_I2CS_SUPPORT


/******************************************************************************
 *  Porting Part:
 ******************************************************************************/

/**************************************
 *  Project Porting Part
 **************************************/

/* Related ID used by I2C Slave */
#define DRV_I2CS_ISR_ExtIntId       1   /* I2C Slave uses Ext. Interrupt 1 */
#define DRV_I2CS_ISR_RegBankId      2   /* I2C Slave uses Register Bank 2  */
#define DRV_I2CS_ISR_TimerId        1   /* I2C Slave uses Timer 1          */

/* I2C Slave IO Definition */
#define IO_I2C_SDA                  IO_PIN(I2CS_SDA)
#define IO_I2C_SCL                  IO_PIN(I2CS_SCL)

/* I2C Address of I2C Slave */
#define DRV_I2CS_I2C_ADDR           (0xA0)

/* Maximum write length of I2C Slave */
#define DRV_I2CS_MAX_WRITE_LEN      (4)     /* Byte(s) */

/* I2C Slave Hook API */
#define DRV_I2CS_ReadByte(o)                (o)
#define DRV_I2CS_WriteFlush(o, buf, len)    /* do nothing */


/**************************************
 *  MCU Porting Part
 **************************************/

/* I2C Slave IO Operation API */
#define DRV_I2CS_SET_SCL(v)         (IO_I2C_SCL = (v))
#define DRV_I2CS_SET_SDA(v)         (IO_I2C_SDA = (v))
#define DRV_I2CS_GET_SCL()          (IO_I2C_SCL)
#define DRV_I2CS_GET_SDA()          (IO_I2C_SDA)

/* I2C Slave ISR Related */
#define ISR_RegBankId(n)            COMBINE(REG_GROUP_, n)
#define ISR_IntId(n)                COMBINE(VECTOR_ID_INT, n)
#define ISR_ClearFlag(n)            do { COMBINE(IE,n) = 0; } while (0)
#define ISR_Disable(n)              do { COMBINE(EX,n) = 0; } while (0)
#define ISR_Enable(n)               do { ISR_ClearFlag(n); COMBINE(EX,n) = 1; } while (0)
#define DRV_I2CS_ISR_GetIntId()     ISR_IntId(DRV_I2CS_ISR_ExtIntId)
#define DRV_I2CS_ISR_GetRegBankId() ISR_RegBankId(DRV_I2CS_ISR_RegBankId)
#define DRV_I2CS_ISR_ClearFlag()    ISR_ClearFlag(DRV_I2CS_ISR_ExtIntId)
#define DRV_I2CS_ISR_Disable()      ISR_Disable(DRV_I2CS_ISR_ExtIntId)
#define DRV_I2CS_ISR_Enable()       ISR_Enable(DRV_I2CS_ISR_ExtIntId)

/* I2C Slave Timer Related */
#define _TR(n)                      COMBINE(TR, n)
#define _TH(n)                      COMBINE(TH, n)
#define _TL(n)                      COMBINE(TL, n)
#define _TF(n)                      COMBINE(TF, n)
#define TRn                         _TR(DRV_I2CS_ISR_TimerId)
#define THn                         _TR(DRV_I2CS_ISR_TimerId)
#define TLn                         _TR(DRV_I2CS_ISR_TimerId)
#define TFn                         _TR(DRV_I2CS_ISR_TimerId)


/******************************************************************************
 *  Common Part:
 ******************************************************************************/

/* I2C Slave Timeout Interval, 25ms defined in SMBus */
#define DRV_I2CS_TIMEOUT_INTERVAL   (25)    /* ms */

static SEG_BDATA UINT8  vI2cAddr;
SBIT(bMasterRead, vI2cAddr, 0);

static BOOL bI2cStart;
static BOOL bI2cStop;
static BOOL bI2cTimeout;
#define DRV_I2CS_ClearStartFlag()   do { bI2cStart   = FALSE; } while (0)
#define DRV_I2CS_ClearStopFlag()    do { bI2cStop    = FALSE; } while (0)
#define DRV_I2CS_ClearTimeoutFlag() do { bI2cTimeout = FALSE; } while (0)
#define DRV_I2CS_SetStartFlag()     do { bI2cStart   = TRUE;  } while (0)
#define DRV_I2CS_SetStopFlag()      do { bI2cStop    = TRUE;  } while (0)
#define DRV_I2CS_SetTimeoutFlag()   do { bI2cTimeout = TRUE;  } while (0)

/* Timer Relelated */
/* I2C Slave Timer Reload Value:
 *   -->  count up
 *   -->  free mode, 16-bit
 *   -->  prescale: 1
 *   -->  source clock: system clock
 */
#define DRV_I2CS_TIMER_RELOAD_VAL   \
            (65536UL - (DRV_I2CS_TIMEOUT_INTERVAL * CPU_CORE_CLOCK /1 /1000))
#if (DRV_I2CS_TIMER_RELOAD_VAL <= 0)
 #error "Unsupported Timer Initial Value for I2C Slave Driver!"
#endif
#define THn_VAL                 ((DRV_I2CS_TIMER_RELOAD_VAL >> 8) & 0xFF)
#define TLn_VAL                 ((DRV_I2CS_TIMER_RELOAD_VAL >> 0) & 0xFF)
#define TMOD_MASK               (0xF << (DRV_I2CS_ISR_TimerId*4))
#define TMOD_VAL                (0x1 << (DRV_I2CS_ISR_TimerId*4))
#define DRV_I2CS_TimerReload()  do {                                        \
                                    TLn = TLn_VAL;                          \
                                    THn = THn_VAL;                          \
                                    TFn = 0;                                \
                                } while(0)
#define DRV_I2CS_TimerInit()    do {                                        \
                                    TMOD = (TMOD & ~TMOD_MASK) | TMOD_VAL;  \
                                    TRn = 1;                                \
                                    DRV_I2CS_TimerReload();                 \
                                } while(0)
#define DRV_I2CS_IsTimeout()    (TFn)

#define WAIT_SCL_L2H(_err_code) do {                                    \
                                    DRV_I2CS_TimerReload();             \
                                    while (DRV_I2CS_GET_SCL() == LOW)   \
                                    {                                   \
                                        if (DRV_I2CS_IsTimeout())       \
                                        {                               \
                                            DRV_I2CS_SetTimeoutFlag();  \
                                            _err_code;                  \
                                        }                               \
                                    }                                   \
                                } while(0)

#define WAIT_SCL_H2L(_err_code) do {                                    \
                                    BOOL    _SDA = DRV_I2CS_GET_SDA();  \
                                                                        \
                                    DRV_I2CS_TimerReload();             \
                                    while (DRV_I2CS_GET_SCL() == HIGH)  \
                                    {                                   \
                                        if (DRV_I2CS_GET_SDA() != _SDA) \
                                        {                               \
                                            if (_SDA)                   \
                                            {                           \
                                                /* I2C Start */         \
                                                DRV_I2CS_SetStartFlag();\
                                            }                           \
                                            else                        \
                                            {                           \
                                                /* I2C Stop */          \
                                                DRV_I2CS_SetStopFlag(); \
                                            }                           \
                                                                        \
                                            _err_code;                  \
                                        }                               \
                                                                        \
                                        if (DRV_I2CS_IsTimeout())       \
                                        {                               \
                                            DRV_I2CS_SetTimeoutFlag();  \
                                            _err_code;                  \
                                        }                               \
                                    }                                   \
                                } while(0)

#define DRV_I2CS_Reset()        do {                                    \
                                    /* Release SDA Line */              \
                                    DRV_I2CS_SET_SDA(HIGH);             \
                                                                        \
                                    /* Initial Status: I2C Start */     \
                                    DRV_I2CS_SetStartFlag();            \
                                                                        \
                                    /* I2C timeout Timer init */        \
                                    DRV_I2CS_TimerInit();               \
                                                                        \
                                    /* clear un-wanted interrupt */     \
                                    DRV_I2CS_ISR_ClearFlag();           \
                                } while(0)

#define ACK()                   do {                                    \
                                    DRV_I2CS_SET_SDA(LOW);              \
                                    WAIT_SCL_L2H(break);                \
                                    DRV_I2CS_CheckStatus();             \
                                    WAIT_SCL_H2L(break);                \
                                    DRV_I2CS_CheckStatus();             \
                                    DRV_I2CS_SET_SDA(HIGH);             \
                                } while(0)


static UINT8 drv_i2cs_ReceiveByte(void)
{
    UINT8   vLoop;
    UINT8   vData = 0;

    for (vLoop = 8; vLoop != 0; vLoop--)
    {
        /* wait SCL from LOW to HIGH */
        WAIT_SCL_L2H(return FALSE);

        /* read one bit data */
        vData = (vData<<1) | DRV_I2CS_GET_SDA();

        /* wait SCL from HIGH to LOW */
        WAIT_SCL_H2L(return FALSE);
    }

    return vData;
}


static BOOL drv_i2cs_SendByte(UINT8 vData)
{
    UINT8   vLoop;
    BOOL    vAck;

    for (vLoop = 8; vLoop != 0; vLoop--)
    {
        /* Transmitting data, MSB first, LSB last */
        _CROL(vData, 1);
        DRV_I2CS_SET_SDA((BOOL)(vData & 0x1));

        WAIT_SCL_L2H(return FALSE);
        WAIT_SCL_H2L(return FALSE);
    }

    /* Check ACK from I2C Master */
    DRV_I2CS_SET_SDA(HIGH);
    WAIT_SCL_L2H(return FALSE);
    vAck = !DRV_I2CS_GET_SDA();
    WAIT_SCL_H2L(return FALSE);

    return vAck;
}


#define DRV_I2CS_IsAddressed()      ((vI2cAddr & 0xFE) == DRV_I2CS_I2C_ADDR)
#define DRV_I2CS_IsI2cStop()        (bI2cStop)
#define DRV_I2CS_IsI2cTimeout()     (bI2cTimeout)
#define DRV_I2CS_IsStart()          (bI2cStart)
#define DRV_I2CS_CheckStatus()      {                                       \
                                        if (bI2cStart                       \
                                                || bI2cStop                 \
                                                || bI2cTimeout)             \
                                            continue;                       \
                                    }
#define DRV_I2CS_ReceiveByte(v)     {                                       \
                                        (v) = drv_i2cs_ReceiveByte();       \
                                        DRV_I2CS_CheckStatus();             \
                                    }
#define DRV_I2CS_SendByte(v)        drv_i2cs_SendByte(v)
#define DRV_I2CS_WriteByte(d)       do {                                    \
                                        if (vWriteLen                       \
                                                < DRV_I2CS_MAX_WRITE_LEN)   \
                                        {                                   \
                                            aWriteBuf[vWriteLen++] = (d);   \
                                        }                                   \
                                    } while (0)
#define DRV_I2CS_SendAck()          ACK()
#define DRV_I2CS_IsMasterRead()     (bMasterRead)


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2CS_ISR
 * DESCRIPTION:
 *      I2C Slave Interrupt Service Routine.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.5.24        Panda.Xiong         Create/Update
 *****************************************************************************/
INTERRUPT_USING(DRV_I2CS_ISR, DRV_I2CS_ISR_GetIntId(), DRV_I2CS_ISR_GetRegBankId())
{
    static BOOL     bReceiveOffset = FALSE;
    static UINT8    vOffset        = 0x00;
    static UINT8    vWriteLen      = 0;
    static UINT8    aWriteBuf[DRV_I2CS_MAX_WRITE_LEN];

    /* Handle the I2C accessing */
    while (1)
    {
        /* I2C Start */
        if (DRV_I2CS_IsStart())
        {
            WAIT_SCL_H2L(break);

            /* clear start flag */
            DRV_I2CS_ClearStartFlag();

            DRV_I2CS_ReceiveByte(vI2cAddr);

            if (!DRV_I2CS_IsAddressed())
            {
                /* not addressed, do nothing */
                break;
            }

            DRV_I2CS_SendAck();

            /* Reset I2C Write Buffer Counter */
            vWriteLen = 0;

            /* force to no offset received, after I2C Start */
            bReceiveOffset = FALSE;
        }

        /* I2C Timeout */
        else if (DRV_I2CS_IsI2cTimeout())
        {
            /* clear timeout flag */
            DRV_I2CS_ClearTimeoutFlag();

            break;
        }

        /* I2C Stop */
        else if (DRV_I2CS_IsI2cStop())
        {
            if (bReceiveOffset)
            {
                DRV_I2CS_WriteFlush(vOffset, aWriteBuf, vWriteLen);
            }

            /* clear stop flag */
            DRV_I2CS_ClearStopFlag();

            break;
        }

        /* I2C Master Read */
        else if (DRV_I2CS_IsMasterRead())
        {
            BOOL    bReceiveAck;

            bReceiveAck = DRV_I2CS_SendByte(DRV_I2CS_ReadByte(vOffset));
            DRV_I2CS_CheckStatus();

            if (!bReceiveAck)
            {
                UINT8   vData;

                /* if NACK received, force to receive another Byte data,
                 *  this is used to detect I2C Start/Stop.
                 */
                DRV_I2CS_ReceiveByte(vData);

                /* should never reach here,
                 *  if reach here, assume I2C connecting is invalid.
                 */
                break;
            }

            vOffset++;
        }

        /* I2C Master Write */
        else
        {
            UINT8   vData;

            DRV_I2CS_ReceiveByte(vData);
            DRV_I2CS_SendAck();

            if (!bReceiveOffset)
            {
                vOffset = vData;
                bReceiveOffset = TRUE;
            }
            else
            {
                DRV_I2CS_WriteByte(vData);
                vOffset++;
            }
        }
    }

    /* set to no offset received */
    bReceiveOffset = FALSE;
    vWriteLen = 0;  /* Reset I2C Write Buffer Counter */

    /* Reset I2C */
    DRV_I2CS_Reset();
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2CS_Disable
 * DESCRIPTION:
 *      I2C Slave Disable.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.10.25        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_I2CS_Disable(void)
{
    DRV_I2CS_ISR_Disable();
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_I2CS_Enable
 * DESCRIPTION:
 *      I2C Slave Enable.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.10.25        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_I2CS_Enable(void)
{
    DRV_I2CS_ISR_ClearFlag();
    DRV_I2CS_ISR_Enable();
}


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
void DRV_I2CS_Init(void)
{
    /* Reset I2C Slave */
    DRV_I2CS_Reset();

    /* Enable I2C Slave Interrupt */
    DRV_I2CS_ISR_Enable();
}

#endif

