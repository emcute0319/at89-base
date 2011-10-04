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


#if DRV_ADC_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_ADC_Get
 * DESCRIPTION:
 *      Sample ADC Value.
 * PARAMETERS:
 *      vAdcPrescale : ADC prescale;
 *      vAdcMux      : ADC Mux;
 * RETURN:
 *      The averaged sampled ADC Value.
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.3.16        Panda.Xiong         Update
 *****************************************************************************/
SINT16 DRV_ADC_Get
(
    IN  UINT8   vAdcPrescale,
    IN  UINT8   vAdcMux
)
{
    SINT16  vResult;

    /* enable ADC, no interrupt */
    ADCSRA = vAdcPrescale | ADC_Enable;

    /* clear last ADC interrupt flag */
    ADCSRA_ADIF = 1;

    /* set ADC channel */
    ADMUX = vAdcMux;

    /* start ADC converting */
    ADCSRA_ADSC = 1;

    /* waiting for ADC convert done */
    while (ADCSRA_ADSC == 1)
    {}

    /* read ADC result, first ADCL, then ADCH */
    vResult  = ADCL;
    vResult |= ((SINT16)ADCH << 8);

    return vResult;
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
}

#endif

