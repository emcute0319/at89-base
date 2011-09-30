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
 *   drv_adc.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2011.9.30        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_ADC_H
#define __DRV_ADC_H


#define ADC_Vref_External               (0x00 << REFS0) /* AREF, Internal Vref Disabled */
#define ADC_Vref_AVCC                   (0x01 << REFS0) /* AVCC     */
#define ADC_Vref_Reserved               (0x02 << REFS0) /* Reserved */
#define ADC_Vref_Internal               (0x03 << REFS0) /* Internal 2.56V Vref */

#define ADC_Result_LeftAdjust           (0x01 << ADLAR) /* ADC Left  Adjust Result */
#define ADC_Result_RightAdjust          (0x00 << ADLAR) /* ADC Right Adjust Result */

#define ADC_MUX_Single_ADC0             (0x00 << MUX0)  /* Single Ended Input, ADC0 */
#define ADC_MUX_Single_ADC1             (0x01 << MUX0)  /* Single Ended Input, ADC1 */
#define ADC_MUX_Single_ADC2             (0x02 << MUX0)  /* Single Ended Input, ADC2 */
#define ADC_MUX_Single_ADC3             (0x03 << MUX0)  /* Single Ended Input, ADC3 */
#define ADC_MUX_Single_ADC4             (0x04 << MUX0)  /* Single Ended Input, ADC4 */
#define ADC_MUX_Single_ADC5             (0x05 << MUX0)  /* Single Ended Input, ADC5 */
#define ADC_MUX_Single_ADC6             (0x06 << MUX0)  /* Single Ended Input, ADC6 */
#define ADC_MUX_Single_ADC7             (0x07 << MUX0)  /* Single Ended Input, ADC7 */
#define ADC_MUX_Diff_ADC0_ADC0_Gain10   (0x08 << MUX0)  /* Diff Input, Positive:ADC0; Negative:ADC0; Gain:10  */
#define ADC_MUX_Diff_ADC1_ADC0_Gain10   (0x09 << MUX0)  /* Diff Input, Positive:ADC1; Negative:ADC0; Gain:10  */
#define ADC_MUX_Diff_ADC0_ADC0_Gain200  (0x0A << MUX0)  /* Diff Input, Positive:ADC0; Negative:ADC0; Gain:200 */
#define ADC_MUX_Diff_ADC1_ADC0_Gain200  (0x0B << MUX0)  /* Diff Input, Positive:ADC1; Negative:ADC0; Gain:200 */
#define ADC_MUX_Diff_ADC2_ADC2_Gain10   (0x0C << MUX0)  /* Diff Input, Positive:ADC2; Negative:ADC2; Gain:10  */
#define ADC_MUX_Diff_ADC3_ADC2_Gain10   (0x0D << MUX0)  /* Diff Input, Positive:ADC3; Negative:ADC2; Gain:10  */
#define ADC_MUX_Diff_ADC2_ADC2_Gain200  (0x0E << MUX0)  /* Diff Input, Positive:ADC2; Negative:ADC2; Gain:200 */
#define ADC_MUX_Diff_ADC3_ADC2_Gain200  (0x0F << MUX0)  /* Diff Input, Positive:ADC3; Negative:ADC2; Gain:200 */
#define ADC_MUX_Diff_ADC0_ADC1_Gain1    (0x10 << MUX0)  /* Diff Input, Positive:ADC0; Negative:ADC1; Gain:1   */
#define ADC_MUX_Diff_ADC1_ADC1_Gain1    (0x11 << MUX0)  /* Diff Input, Positive:ADC1; Negative:ADC1; Gain:1   */
#define ADC_MUX_Diff_ADC2_ADC1_Gain1    (0x12 << MUX0)  /* Diff Input, Positive:ADC2; Negative:ADC1; Gain:1   */
#define ADC_MUX_Diff_ADC3_ADC1_Gain1    (0x13 << MUX0)  /* Diff Input, Positive:ADC3; Negative:ADC1; Gain:1   */
#define ADC_MUX_Diff_ADC4_ADC1_Gain1    (0x14 << MUX0)  /* Diff Input, Positive:ADC4; Negative:ADC1; Gain:1   */
#define ADC_MUX_Diff_ADC5_ADC1_Gain1    (0x15 << MUX0)  /* Diff Input, Positive:ADC5; Negative:ADC1; Gain:1   */
#define ADC_MUX_Diff_ADC6_ADC1_Gain1    (0x16 << MUX0)  /* Diff Input, Positive:ADC6; Negative:ADC1; Gain:1   */
#define ADC_MUX_Diff_ADC7_ADC1_Gain1    (0x17 << MUX0)  /* Diff Input, Positive:ADC7; Negative:ADC1; Gain:1   */
#define ADC_MUX_Diff_ADC0_ADC2_Gain1    (0x18 << MUX0)  /* Diff Input, Positive:ADC0; Negative:ADC2; Gain:1   */
#define ADC_MUX_Diff_ADC1_ADC2_Gain1    (0x19 << MUX0)  /* Diff Input, Positive:ADC1; Negative:ADC2; Gain:1   */
#define ADC_MUX_Diff_ADC2_ADC2_Gain1    (0x1A << MUX0)  /* Diff Input, Positive:ADC2; Negative:ADC2; Gain:1   */
#define ADC_MUX_Diff_ADC3_ADC2_Gain1    (0x1B << MUX0)  /* Diff Input, Positive:ADC3; Negative:ADC2; Gain:1   */
#define ADC_MUX_Diff_ADC4_ADC2_Gain1    (0x1C << MUX0)  /* Diff Input, Positive:ADC4; Negative:ADC2; Gain:1   */
#define ADC_MUX_Diff_ADC5_ADC2_Gain1    (0x1D << MUX0)  /* Diff Input, Positive:ADC5; Negative:ADC2; Gain:1   */
#define ADC_MUX_Single_VBG              (0x1E << MUX0)  /* Single Ended Input, V_BG, 1.22V */
#define ADC_MUX_Single_GND              (0x1F << MUX0)  /* Single Ended Input, GND */


#define ADC_Prescale_2                  (0x0 << ADPS0)  /* ADC Prescale: 2   */
#define ADC_Prescale_4                  (0x2 << ADPS0)  /* ADC Prescale: 4   */
#define ADC_Prescale_8                  (0x3 << ADPS0)  /* ADC Prescale: 4   */


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
);

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
void DRV_ADC_Init(void);


#endif /* __DRV_ADC_H */

