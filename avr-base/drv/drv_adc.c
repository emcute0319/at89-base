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
 *   drv_adc.c
 * DESCRIPTION:
 *   ADC Driver.
 * HISTORY:
 *   2011.9.30        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#include "drv.h"


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_ADC_Get
 * DESCRIPTION:
 *      Sample ADC Value.
 * PARAMETERS:
 *      vPositive : Positive channel;
 *      vNegative : Negative channel;
 *      vAvgNum   : ADC Average Number, should be less than 62;
 * RETURN:
 *      The averaged sampled ADC Value.
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.3.16        Panda.Xiong         Update
 *****************************************************************************/
UINT16 DRV_ADC_Get
(
    IN  UINT8   vPositive,
    IN  UINT8   vNegative
)
{
    //
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_ADC_Init
 * DESCRIPTION:
 *      ADC Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.9.30        Panda.Xiong         Create/Update
 *****************************************************************************/
void DRV_ADC_Init(void)
{
    /* enable ADC */
    ADCSRA_ADEN = 1;

    //
}
