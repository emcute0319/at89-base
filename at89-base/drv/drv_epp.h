/******************************************************************************
 *
 * COPYRIGHT:
 *   Copyright (c)  2005-2010   Source Photonics Inc.    All rights reserved.
 *
 *   This is unpublished proprietary source code of Source Photonics Inc.
 *   The copyright notice above does not evidence any actual or intended
 *   publication of such source code.
 *
 * FILE NAME:
 *   drv_epp.h
 * DESCRIPTION:
 *   EPP Driver.
 * HISTORY:
 *   2012.2.10        PANDA         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_EPP_H
#define __DRV_EPP_H


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
void DRV_EPP_WriteRegister(IN UINT8 vRegNo, IN UINT8 vData);

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
UINT8 DRV_EPP_ReadRegister(IN UINT8 vRegNo);


#endif /* __DRV_EPP_H */

