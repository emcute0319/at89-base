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
 *   drv_watchdog.h
 * DESCRIPTION:
 *   Watchdog Driver.
 * HISTORY:
 *   2010.1.27        panda.xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_WATCHDOG_H
#define __DRV_WATCHDOG_H


/* ATmega16 Watchdog Prescale Definition:
 *
 *  Prescale    VCC(3.0v)     VCC(5.0v)
 * ----------  -----------  ------------
 *    0x0         17.1ms        16.3ms
 *    0x1         34.3ms        32.5ms
 *    0x2         68.5ms        65.0ms
 *    0x3         0.14s         0.13s
 *    0x4         0.27s         0.26s
 *    0x5         0.55s         0.52s
 *    0x6         1.1s          1.0s
 *    0x7         2.2s          2.1s
 */
#define DRV_WATCHDOG_Prescale   0x7


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_WATCHDOG_Enable
 * DESCRIPTION:
 *      Enable Watchdog Timer.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        Panda.Xiong         Create/Update
 *****************************************************************************/
#define DRV_WATCHDOG_Enable()                                               \
    do {                                                                    \
        WDTCR = DRV_WATCHDOG_Prescale; /* set watchdog prescale */          \
        WDTCR_WDE = 1;                 /* enable watchdog       */          \
    } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_WATCHDOG_Disable
 * DESCRIPTION:
 *      Disable Watchdog Timer.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        Panda.Xiong         Create/Update
 *****************************************************************************/
#define DRV_WATCHDOG_Disable()                                              \
    do {                                                                    \
        BOOL bIntStatus;                                                    \
                                                                            \
        /* lock global interrupt */                                         \
        bIntStatus = DRV_INT_LockGlobalInterrupt();                         \
                                                                            \
        /* kick watchdog timer, to prevent Watchdog Timer timeout */        \
        DRV_WATCHDOG_Kick();                                                \
                                                                            \
        /* set WDE bit, to make sure watchdog can be disabled */            \
        WDTCR_WDTOE = 1;                                                    \
                                                                            \
        /* disable watchdog */                                              \
        WDTCR_WDE = 0;                                                      \
                                                                            \
        /* unlock global interrupt */                                       \
        DRV_INT_UnlockGlobalInterrupt(bIntStatus);                          \
    } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_WATCHDOG_Kick
 * DESCRIPTION:
 *      Kick Watchdog Timer, to prevent watchdog timeout.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        Panda.Xiong         Create/Update
 *****************************************************************************/
#define DRV_WATCHDOG_Kick()     __watchdog_reset()


#endif /* __DRV_WATCHDOG_H */

