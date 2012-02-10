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
 *   drv_epp.c
 * DESCRIPTION:
 *   EPP driver.
 * HISTORY:
 *   2012.2.10        PANDA         Create/Update
 *
*****************************************************************************/

#include "drv.h"

#if DRV_EPP_SUPPORT


#define DRV_EPP_ACTIVE              LOW
#define DRV_EPP_INACTIVE            HIGH

#define DRV_EPP_Delay_Us(vUs)       DRV_CPU_DelayUs(vUs)
#define DRV_EPP_SET_nWRITE(vData)   DRV_IO_Write(IO_PIN(EPP_nWRITE), (vData))
#define DRV_EPP_SET_nDSTRB(vData)   DRV_IO_Write(IO_PIN(EPP_nDSTRB), (vData))
#define DRV_EPP_SET_nASTRB(vData)   DRV_IO_Write(IO_PIN(EPP_nASTRB), (vData))
#define DRV_EPP_GET_nWAIT()         DRV_IO_Read(IO_PIN(EPP_nWAIT))
#define DRV_EPP_SET_DATA(vData)     do {                                                        \
                                        DRV_IO_Write(IO_PIN(EPP_DATA0), READ_BIT((vData), 0));  \
                                        DRV_IO_Write(IO_PIN(EPP_DATA1), READ_BIT((vData), 1));  \
                                        DRV_IO_Write(IO_PIN(EPP_DATA2), READ_BIT((vData), 2));  \
                                        DRV_IO_Write(IO_PIN(EPP_DATA3), READ_BIT((vData), 3));  \
                                        DRV_IO_Write(IO_PIN(EPP_DATA4), READ_BIT((vData), 4));  \
                                        DRV_IO_Write(IO_PIN(EPP_DATA5), READ_BIT((vData), 5));  \
                                        DRV_IO_Write(IO_PIN(EPP_DATA6), READ_BIT((vData), 6));  \
                                        DRV_IO_Write(IO_PIN(EPP_DATA7), READ_BIT((vData), 7));  \
                                    } while (0)
#define DRV_EPP_GET_DATA()          (                                                           \
                                          ((UINT8)DRV_IO_Read(IO_PIN(EPP_DATA0)) << 0)          \
                                        | ((UINT8)DRV_IO_Read(IO_PIN(EPP_DATA1)) << 1)          \
                                        | ((UINT8)DRV_IO_Read(IO_PIN(EPP_DATA2)) << 2)          \
                                        | ((UINT8)DRV_IO_Read(IO_PIN(EPP_DATA3)) << 3)          \
                                        | ((UINT8)DRV_IO_Read(IO_PIN(EPP_DATA4)) << 4)          \
                                        | ((UINT8)DRV_IO_Read(IO_PIN(EPP_DATA5)) << 5)          \
                                        | ((UINT8)DRV_IO_Read(IO_PIN(EPP_DATA6)) << 6)          \
                                        | ((UINT8)DRV_IO_Read(IO_PIN(EPP_DATA7)) << 7)          \
                                    )
#define DRV_EPP_SET_DATA_INPUT()    do {                                                        \
                                        DRV_IO_SetInput(IO_PIN(EPP_DATA0));                     \
                                        DRV_IO_SetInput(IO_PIN(EPP_DATA1));                     \
                                        DRV_IO_SetInput(IO_PIN(EPP_DATA2));                     \
                                        DRV_IO_SetInput(IO_PIN(EPP_DATA3));                     \
                                        DRV_IO_SetInput(IO_PIN(EPP_DATA4));                     \
                                        DRV_IO_SetInput(IO_PIN(EPP_DATA5));                     \
                                        DRV_IO_SetInput(IO_PIN(EPP_DATA6));                     \
                                        DRV_IO_SetInput(IO_PIN(EPP_DATA7));                     \
                                    } while (0)
#define DRV_EPP_SET_DATA_OUTPUT()   do {                                                        \
                                        DRV_IO_SetOutput(IO_PIN(EPP_DATA0));                    \
                                        DRV_IO_SetOutput(IO_PIN(EPP_DATA1));                    \
                                        DRV_IO_SetOutput(IO_PIN(EPP_DATA2));                    \
                                        DRV_IO_SetOutput(IO_PIN(EPP_DATA3));                    \
                                        DRV_IO_SetOutput(IO_PIN(EPP_DATA4));                    \
                                        DRV_IO_SetOutput(IO_PIN(EPP_DATA5));                    \
                                        DRV_IO_SetOutput(IO_PIN(EPP_DATA6));                    \
                                        DRV_IO_SetOutput(IO_PIN(EPP_DATA7));                    \
                                    } while (0)


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_EPP_WriteRegister
 * DESCRIPTION:
 *      Write EPP Register.
 * PARAMETERS:
 *      vRegNo    : Register Number;
 *      vData     : Register Data;
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2012.2.10        PANDA         Create/Update
 *****************************************************************************/
void DRV_EPP_WriteRegister(IN UINT8 vRegNo, IN UINT8 vData)
{
    /* send address */
    DRV_EPP_SET_DATA_OUTPUT();
    DRV_EPP_SET_nWRITE(DRV_EPP_ACTIVE);
    DRV_EPP_SET_DATA(vRegNo);
    DRV_EPP_SET_nASTRB(DRV_EPP_ACTIVE);
    while (DRV_EPP_GET_nWAIT() == LOW)
    {}
    DRV_EPP_SET_nASTRB(DRV_EPP_INACTIVE);
    DRV_EPP_SET_nWRITE(DRV_EPP_INACTIVE);

    /* send data */
    DRV_EPP_SET_DATA_OUTPUT();
    DRV_EPP_SET_nWRITE(DRV_EPP_ACTIVE);
    DRV_EPP_SET_DATA(vData);
    DRV_EPP_SET_nDSTRB(DRV_EPP_ACTIVE);
    while (DRV_EPP_GET_nWAIT() == LOW)
    {}
    DRV_EPP_SET_nDSTRB(DRV_EPP_INACTIVE);
    DRV_EPP_SET_nWRITE(DRV_EPP_INACTIVE);
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_EPP_ReadRegister
 * DESCRIPTION:
 *      Read EPP Register.
 * PARAMETERS:
 *      vRegNo    : Register Number;
 * RETURN:
 *      Register Data.
 * NOTES:
 *      N/A
 * HISTORY:
 *      2012.2.10        PANDA         Create/Update
 *****************************************************************************/
UINT8 DRV_EPP_ReadRegister(IN UINT8 vRegNo)
{
    UINT8   vData;

    /* send address */
    DRV_EPP_SET_DATA_OUTPUT();
    DRV_EPP_SET_nWRITE(DRV_EPP_ACTIVE);
    DRV_EPP_SET_DATA(vRegNo);
    DRV_EPP_SET_nASTRB(DRV_EPP_ACTIVE);
    while (DRV_EPP_GET_nWAIT() == LOW)
    {}
    DRV_EPP_SET_nASTRB(DRV_EPP_INACTIVE);
    DRV_EPP_SET_nWRITE(DRV_EPP_INACTIVE);

    /* read data */
    DRV_EPP_SET_DATA_INPUT();
    DRV_EPP_SET_nWRITE(DRV_EPP_INACTIVE);
    DRV_EPP_SET_nDSTRB(DRV_EPP_ACTIVE);
    while (DRV_EPP_GET_nWAIT() == LOW)
    {}
    vData = DRV_EPP_GET_DATA();
    DRV_EPP_SET_nDSTRB(DRV_EPP_INACTIVE);
    DRV_EPP_SET_nWRITE(DRV_EPP_INACTIVE);

    return vData;
}

#endif

