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
 *   drv_temp_ds18b20.c
 * DESCRIPTION:
 *   DS18B20 Temperature Sensor driver.
 * HISTORY:
 *   2011.6.8        panda.xiong         Create/Update
 *
*****************************************************************************/

#include "drv.h"


#if DRV_TEMP_DS18B20_SUPPORT

/******************************************************************************
 *  Porting Part:
 ******************************************************************************/

#define DS18B20_SET_DQ()            DRV_IO_Write(IO_PIN(DS18B20_DQ), HIGH)
#define DS18B20_CLR_DQ()            DRV_IO_Write(IO_PIN(DS18B20_DQ), LOW)
#define DS18B20_GET_DQ()            DRV_IO_Read(IO_PIN(DS18B20_DQ))

#define DS18B20_ENTER_CRITICAL()    do { BOOL bIntState = DRV_INT_LockGlobalInterrupt()
#define DS18B20_EXIT_CRITICAL()     DRV_INT_UnlockGlobalInterrupt(bIntState); } while (0)

#define _ds18b20_Delay_1us()        NOP()
#define _ds18b20_Delay_15us()       DRV_CPU_DelayUs(15)
#define _ds18b20_Delay_30us()       DRV_CPU_DelayUs(30)
#define _ds18b20_Delay_45us()       DRV_CPU_DelayUs(45)
#define _ds18b20_Delay_60us()       DRV_CPU_DelayUs(60)
#define _ds18b20_Delay_480us()      do {                                    \
                                        DRV_CPU_DelayUs(240);               \
                                        DRV_CPU_DelayUs(240);               \
                                    } while (0)


/******************************************************************************
 *  Common Part:
 ******************************************************************************/

#define DS18B20_CMD_MatchROM            0x55
#define DS18B20_CMD_SkipROM             0xCC
#define DS18B20_CMD_ConvertTemp         0x44
#define DS18B20_CMD_ReadScratchpad      0xBE
#define DS18B20_CMD_WriteScratchpad     0x4E
#define DS18B20_CMD_CopyScratchpad      0x48
#define DS18B20_CMD_RecallEEPROM        0xB8


static BOOL _ds18b20_Reset(void)
{
    BOOL    bPresent;

    /* Dummy set DQ, to make sure the initial DQ is HIGH */
    DS18B20_SET_DQ();

    DS18B20_ENTER_CRITICAL();

    /* Pull DQ to LOW, for at least 480us, to send the reset pulse to DS18B20 */
    DS18B20_CLR_DQ();
    _ds18b20_Delay_480us();

    /* Release DQ, and wait for DQ goes to HIGH */
    DS18B20_SET_DQ();
    while (DS18B20_GET_DQ() == LOW)
    {}

    /* When DS18B20 detect the DQ goes from LOW to HIGH,
     *  it will wait 15-60us, and then transmits a present pulse
     *   by pulling the 1-Wire bus low for 60-240us.
     */
    _ds18b20_Delay_60us();
    bPresent = (DS18B20_GET_DQ() == LOW);

    DS18B20_EXIT_CRITICAL();

    if (bPresent)
    {
        /* Delay at least 480us, to finish the DS18B20 Initializing */
        _ds18b20_Delay_480us();
    }

    return bPresent;
}


static BOOL _ds18b20_TransmitBit(IN BOOL bData)
{
    DS18B20_ENTER_CRITICAL();

    /* Pull DQ to LOW, for timing between 1us and 15us */
    DS18B20_CLR_DQ();
    _ds18b20_Delay_1us();

    /* Send data to DS18B20 */
    if (bData)
    {
        /* write 1 */
        DS18B20_SET_DQ();
    }
    else
    {
        /* write 0 */
        /* do nothing here, the DQ is already be poll to LOW */
    }
    /* Send data should be done within 15us */
    _ds18b20_Delay_15us();

    /* Read data from DS18B20 */
    bData = DS18B20_GET_DQ();

    /* Delay 45us to finish this transmiting:
     *  --> For write: The DS18B20 need 15-45us to read the data;
     *  --> For read : Delay 45us to finish the read slot;
     */
    _ds18b20_Delay_45us();

    /* Force set DQ, for at least 1us, to release DQ */
    DS18B20_SET_DQ();
    _ds18b20_Delay_1us();

    DS18B20_EXIT_CRITICAL();

    return bData;
}


static UINT8 _ds18b20_TransmitByte(IN UINT8 vData)
{
    UINT8   vLoop;

    for (vLoop = 8; vLoop != 0; vLoop--)
    {
        BOOL    bData;

        bData = _ds18b20_TransmitBit(vData&0x01);
        vData = (vData>>1) | ((UINT8)bData << 7);
    }

    return vData;
}


/* DS18B20 internal API */
static BOOL bDS18B20_Ready = FALSE;
#define _ds18b20_IsReady()          (bDS18B20_Ready)
#define _ds18b20_WriteByte(_v)      _ds18b20_TransmitByte(_v)
#define _ds18b20_ReadByte()         _ds18b20_TransmitByte(0xFF)
#define _ds18b20_IsBusy()           (DS18B20_GET_DQ() == LOW)


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_Temp_DS18B20_GetTemp
 * DESCRIPTION:
 *      DS18B20 Get Temperature.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      The read temperature:
 *       Bit[15]   : =0, read temperature success;
 *                   =1, read temperature fail;
 *       Bit[14:0] : The read temperature;
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.8        panda.xiong         Create/Update
 *****************************************************************************/
UINT16 DRV_Temp_DS18B20_GetTemp(void)
{
    UINT8   vTempH, vTempL;

    if (_ds18b20_IsBusy() || !_ds18b20_IsReady())
    {
        /* DS18B20 is busy or not ready, get temperature fail */
        return 0x8000;
    }

    /* Read the last converted temperature value from DS18B20 */
    _ds18b20_Reset();
    _ds18b20_WriteByte(DS18B20_CMD_SkipROM);
    _ds18b20_WriteByte(DS18B20_CMD_ReadScratchpad);
    vTempL = _ds18b20_ReadByte();
    vTempH = _ds18b20_ReadByte();

    /* start converting, for next time get temperature usage */
    _ds18b20_Reset();
    _ds18b20_WriteByte(DS18B20_CMD_SkipROM);
    _ds18b20_WriteByte(DS18B20_CMD_ConvertTemp);

    return ((((UINT16)vTempH & 0x7F) << 8) | vTempL);
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_Temp_DS18B20_Init
 * DESCRIPTION:
 *      Init DS18B20 driver.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.6.8        panda.xiong         Create/Update
 *****************************************************************************/
void DRV_Temp_DS18B20_Init(void)
{
    /* Check DS18B20 is present or not */
    bDS18B20_Ready = _ds18b20_Reset();

    if (_ds18b20_IsReady())
    {
        UINT8   vTempGateH, vTempGateL;

        /* Copy the Alarm min/max gate from EEPROM to RAM */
        _ds18b20_Reset();
        _ds18b20_WriteByte(DS18B20_CMD_SkipROM);
        _ds18b20_WriteByte(DS18B20_CMD_RecallEEPROM);

        /* Wait DS18B20 copy finished */
        while (_ds18b20_IsBusy())
        {}

        /* Read the Alarm min/max gate from DS18B20 */
        _ds18b20_Reset();
        _ds18b20_WriteByte(DS18B20_CMD_SkipROM);
        _ds18b20_WriteByte(DS18B20_CMD_ReadScratchpad);
        vTempGateH = _ds18b20_ReadByte();
        vTempGateL = _ds18b20_ReadByte();

        /* Set precision to 12-bit */
        _ds18b20_Reset();
        _ds18b20_WriteByte(DS18B20_CMD_SkipROM);
        _ds18b20_WriteByte(DS18B20_CMD_WriteScratchpad);
        _ds18b20_WriteByte(vTempGateH);
        _ds18b20_WriteByte(vTempGateL);
        _ds18b20_WriteByte(0x7F);
        _ds18b20_Reset();

        /* start converting, for next time get temperature usage */
        _ds18b20_Reset();
        _ds18b20_WriteByte(DS18B20_CMD_SkipROM);
        _ds18b20_WriteByte(DS18B20_CMD_ConvertTemp);
    }
}

#endif

