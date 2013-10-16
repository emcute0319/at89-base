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
 *   drv_swi.c
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2013.10.16          PANDA           Create/Update
 *
 *****************************************************************************/

#include "drv.h"


#if DRV_SWI_SUPPORT

/* SWI configuration table */
#define DECLARE_VECTOR_SWI(_name, _callback, _desc)     { (_callback) },
typedef void (SEG_CODE *SWI_HANDLER_FUNC)(void);
static struct
{
    SWI_HANDLER_FUNC    pHandler;
} CONST aSwiCfgTable[] =
{
    #include "cfg_hw_porting.h"
};
#undef  DECLARE_VECTOR_SWI

/* SWI real-time table */
#define DECLARE_VECTOR_SWI(_name, _callback, _desc)     { DISABLE, FALSE, },
static struct
{
    UINT8   bEnable  : 1;
    UINT8   bIntFlag : 1;
} aSwiRTTable[] =
{
    #include "cfg_hw_porting.h"
};
#undef  DECLARE_VECTOR_SWI


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SWI_ISR
 * DESCRIPTION:
 *      SWI Interrupt Service Rountine.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2012.3.7          PANDA           Create/Update
 *****************************************************************************/
void DRV_SWI_ISR(void)
{
    UINT8   vLoop;

    for (vLoop = 0; vLoop < COUNT_OF(aSwiRTTable); vLoop++)
    {
        if (aSwiRTTable[vLoop].bEnable == ENABLE)
        {
            if (aSwiRTTable[vLoop].bIntFlag)
            {
                /* handle this software interrupt */
                aSwiCfgTable[vLoop].pHandler();

                /* clear this software interrupt flag */
                aSwiRTTable[vLoop].bIntFlag = FALSE;
            }
        }
    }

    /* clear SWI global interrupt flag */
    DRV_SWI_ClearGlobalInterrupt();
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SWI_SetInterrupt
 * DESCRIPTION:
 *      Set SWI Interrupt Flag.
 * PARAMETERS:
 *      vName  : SWI Name;
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2012.3.7          PANDA           Create/Update
 *****************************************************************************/
void DRV_SWI_SetInterrupt(IN DRV_SWI_NAME_T vName)
{
    /* set SWI interrupt flag */
    aSwiRTTable[vName].bIntFlag = TRUE;

    /* only enable SWI global interrupt, while this SWI is enabled */
    if (aSwiRTTable[vName].bEnable == ENABLE)
    {
        DRV_SWI_SetGlobalInterrupt();
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SWI_SetState
 * DESCRIPTION:
 *      Set SWI State.
 * PARAMETERS:
 *      vName  : SWI Name;
 *      vState : ENABLE/DISABLE.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2012.3.7          PANDA           Create/Update
 *****************************************************************************/
void DRV_SWI_SetState
(
    IN DRV_SWI_NAME_T   vName,
    IN BOOL             bState
)
{
    /* clear SWI flag */
    aSwiRTTable[vName].bIntFlag = FALSE;

    /* set SWI state */
    aSwiRTTable[vName].bEnable  = bState;
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_SWI_Init
 * DESCRIPTION:
 *      SWI Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2012.3.7          PANDA           Create/Update
 *****************************************************************************/
void DRV_SWI_Init(void)
{
    DRV_SWI_ClearGlobalInterrupt();
    DRV_SWI_GlobalEnableInterrupt();
}

#endif

