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
 *   Currently, only support MCS-51 MCU under Keil compiler environment.
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
#define DRV_I2CS_ReadByte(o)                (0xAA)
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
#define ISR_Enable(n)               do { ISR_ClearFlag(); COMBINE(EX,n) = 1; } while (0)
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

#define _interrupt_                 \
    __interrupt_using(DRV_I2CS_ISR_GetIntId(), DRV_I2CS_ISR_GetRegBankId())

#define DECLEAR_BIT(name, x, n)     sbit name = x ^ n



/******************************************************************************
 *  Common Part:
 ******************************************************************************/

/* I2C Slave Timeout Interval, 25ms defined in SMBus */
#define DRV_I2CS_TIMEOUT_INTERVAL   (25)    /* ms */

static SEG_BDATA volatile UINT8  vI2cAddr = 0x00;
DECLEAR_BIT(bMasterRead, vI2cAddr, 0);
DECLEAR_BIT(bA2Selected, vI2cAddr, 1);

static SEG_BDATA volatile UINT8  vI2cStatus = 0x01;
DECLEAR_BIT(bI2cStart,   vI2cStatus, 0);
DECLEAR_BIT(bI2cStop,    vI2cStatus, 1);
DECLEAR_BIT(bI2cTimeout, vI2cStatus, 2);

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
#define DRV_I2CS_TimerStart()   do { TRn = 1; } while(0)
#define DRV_I2CS_TimerStop()    do {                                    \
                                    TLn = TLn_VAL;                      \
                                    THn = THn_VAL;                      \
                                    TRn = 0;                            \
                                    TFn = 0;                            \
                                } while(0)
#define DRV_I2CS_IsTimeout()    (TFn)

#define WAIT_SCL_L2H            do {                                    \
                                    while (DRV_I2CS_GET_SCL() == LOW)   \
                                    {                                   \
                                        if (DRV_I2CS_IsTimeout())       \
                                        {                               \
                                            bI2cTimeout = TRUE;         \
                                            break;                      \
                                        }                               \
                                    }                                   \
                                } while(0)

#define WAIT_SCL_H2L            do {                                    \
                                    while (DRV_I2CS_GET_SCL() == HIGH)  \
                                    {                                   \
                                        if (DRV_I2CS_IsTimeout())       \
                                        {                               \
                                            bI2cTimeout = TRUE;         \
                                            break;                      \
                                        }                               \
                                    }                                   \
                                } while(0)

#define DRV_I2CS_Reset()        do {                                    \
                                    /* Release SDA Line */              \
                                    DRV_I2CS_SET_SDA(HIGH);             \
                                                                        \
                                    vI2cStatus = 0x01;                  \
                                    DRV_I2CS_TimerStop();               \
                                                                        \
                                    /* clear un-wanted interrupt */     \
                                    DRV_I2CS_ISR_ClearFlag();           \
                                } while(0)

#define ACK()                   do {                                    \
                                    DRV_I2CS_SET_SDA(LOW);              \
                                    WAIT_SCL_L2H;                       \
                                    WAIT_SCL_H2L;                       \
                                    DRV_I2CS_SET_SDA(HIGH);             \
                                } while(0)


static UINT8 drv_i2cs_ReceiveByte(void)
{
    BOOL    vSDA;
    UINT8   vLoop;
    UINT8   vData = 0;

    for (vLoop = 8; vLoop != 0; vLoop--)
    {
        WAIT_SCL_L2H;

        /* Monitor I2C Start/Stop */
        vSDA = DRV_I2CS_GET_SDA();
        do
        {
            if (DRV_I2CS_GET_SDA() != vSDA)
            {
                if (vSDA)
                {
                    /* I2C Start */
                    bI2cStart = TRUE;
                }
                else
                {
                    /* I2C Stop */
                    bI2cStop = TRUE;
                }

                return vData;
            }

            if (TF1)
            {
                bI2cTimeout = TRUE;
                break;
            }
        } while (DRV_I2CS_GET_SCL());

        vData = (vData<<1) | vSDA;
    }

    vI2cStatus = 0x00;
    return vData;
}


static BOOL drv_i2cs_SendByte(UINT8 vData)
{
    UINT8   vLoop;
    BOOL    vAck;

    for (vLoop = 8; vLoop != 0; vLoop--)
    {
        /* Transmitting data, MSB first, LSB last */
        vData = _crol_(vData, 1);
        DRV_I2CS_SET_SDA((BOOL)(vData & 0x1));

        WAIT_SCL_L2H;
        WAIT_SCL_H2L;

        if (bI2cTimeout)
        {
            DRV_I2CS_SET_SDA(HIGH);
            return FALSE;
        }
    }

    /* Check ACK from I2C Master */
    DRV_I2CS_SET_SDA(HIGH);
    WAIT_SCL_L2H;
    vAck = !DRV_I2CS_GET_SDA();
    WAIT_SCL_H2L;

    return vAck;
}


#define DRV_I2CS_IsAddressed()      ((vI2cAddr & 0xFC) == DRV_I2CS_I2C_ADDR)
#define DRV_I2CS_IsI2cStop()        (bI2cStop)
#define DRV_I2CS_IsI2cTimeout()     (bI2cTimeout)
#define DRV_I2CS_IsStart()          (bI2cStart)
#define DRV_I2CS_ReceiveByte(v)     {                                       \
                                        (v) = drv_i2cs_ReceiveByte();       \
                                        if (vI2cStatus)                     \
                                            continue;                       \
                                    }
#define DRV_I2CS_SendByte(v)        drv_i2cs_SendByte(v)
#define DRV_I2CS_WriteByte(d)       do {                                    \
                                        if (vWriteLen                       \
                                                < DRV_I2CS_MAX_WRITE_LEN)   \
                                        {                                   \
                                            aWriteBuf[vWriteLen++] = (d);   \
                                        }                                   \
                                    } while (0)
#define DRV_I2CS_SendAck()          {                                       \
                                        ACK();                              \
                                        if (DRV_I2CS_IsI2cTimeout())        \
                                            continue;                       \
                                    }
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
void DRV_I2CS_ISR(void) _interrupt_
{
    static BOOL     bReceiveOffset = FALSE;
    static UINT8    vOffset        = 0x00;
    static UINT8    vWriteLen      = 0;
    static UINT8    aWriteBuf[DRV_I2CS_MAX_WRITE_LEN];
    UINT8           vData;

    DRV_I2CS_TimerStart();

    /* Handle the I2C accessing */
    while (1)
    {
        /* I2C Stop/Timeout */
        if (DRV_I2CS_IsI2cStop() || DRV_I2CS_IsI2cTimeout())
        {
            if (DRV_I2CS_IsI2cStop())
            {
                if (bReceiveOffset)
                {
                    DRV_I2CS_WriteFlush(vOffset, aWriteBuf, vWriteLen);
                }
            }

            break;
        }

        /* I2C Start */
        else if (DRV_I2CS_IsStart())
        {
            WAIT_SCL_H2L;
            DRV_I2CS_ReceiveByte(vI2cAddr);

            if (DRV_I2CS_IsAddressed())
            {
                DRV_I2CS_SendAck();
                vWriteLen = 0;  /* Reset I2C Write Buffer Counter */
            }
            else
            {
                break;
            }
        }

        /* I2C Master Read */
        else if (DRV_I2CS_IsMasterRead())
        {
            vData = DRV_I2CS_ReadByte(vOffset);

            if (!DRV_I2CS_SendByte(vData))
            {
                break;
            }

            vOffset++;
        }

        /* I2C Master Write */
        else
        {
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

