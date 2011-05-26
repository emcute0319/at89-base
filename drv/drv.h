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
 *   drv.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.1.27        panda.xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_H
#define __DRV_H


#include "cfg_hw_def.h"
#include "typedef.h"
#include "reg_def_at89.h"

#include "version.h"
#include "drv_cpu.h"
#include "drv_io.h"
#include "drv_int.h"
#include "drv_vector.h"
#include "drv_timer.h"
#include "drv_uart.h"
#include "drv_watchdog.h"
#include "drv_spi.h"
#include "drv_i2cm.h"
#include "drv_i2cs.h"


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_PreInit
 * DESCRIPTION:
 *      Driver Pre-Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.28        panda.xiong         Create/Update
 *****************************************************************************/
#define DRV_PreInit()   DRV_CPU_PreInit()

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
void DRV_Init(void);

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
void DRV_FixupInit(void);

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
void DRV_Entry(void);


#endif /* __DRV_H */

