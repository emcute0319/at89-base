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
 *   drv.c
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.1.28        panda.xiong         Create/Update
 *
*****************************************************************************/

#include "drv.h"


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_Init
 * DESCRIPTION:
 *      Driver Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.28        panda.xiong         Create/Update
 *****************************************************************************/
void DRV_Init(void)
{
    /* Vector Init */
    DRV_Vector_Init();

    /* Init IO */
    DRV_IO_Init();

    /* Init Timer */
    DRV_TIMER_Init();

#if DRV_UART_SUPPORT
    /* Init UART */
    DRV_UART_Init();
#endif

#if DRV_SPI_SUPPORT
    /* Init SPI Bus */
    DRV_SPI_Init();
#endif

#if DRV_I2CM_SUPPORT
    /* Init I2C Master Bus */
    DRV_I2CM_Init();
#endif
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_FixupInit
 * DESCRIPTION:
 *      FixUp Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      This is a post init after system initialized done.
 * HISTORY:
 *      2009.9.23        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_FixupInit(void)
{
    /* Enable Watchdog */
    DRV_WATCHDOG_Enable();
}

