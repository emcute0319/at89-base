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
 *   drv_int.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.4.6        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_INT_H
#define __DRV_INT_H


/* enable/disable/lock/unlock global interrupt */
#define DRV_INT_GlobalEnableInterrupt()     __enable_interrupt()
#define DRV_INT_GlobalDisableInterrupt()    __disable_interrupt()
#define DRV_INT_LockGlobalInterrupt()       ((SREG_Bit7)? (SREG_Bit7=0, TRUE) : FALSE)
#define DRV_INT_UnlockGlobalInterrupt(_s)   do { SREG_Bit7=(_s); } while (0)

/* enable/disable external interrrupt */
#define DRV_INT_EnableExtInterrupt(n)       do { COMBINE(GICR_INT,n) = 1; } while (0)
#define DRV_INT_DisableExtInterrupt(n)      do { COMBINE(GICR_INT,n) = 0; } while (0)
#define DRV_INT_LockExtInterrupt(n)         (COMBINE(GICR_INT,n)? (COMBINE(GICR_INT,n)=0, TRUE) : FALSE)
#define DRV_INT_UnlockExtInterrupt(n, _s)   do { COMBINE(GICR_INT,n) = (_s); } while (0)

/* external interrupt trigger mode:
 *
 * Note:
 *  1. Before configurating external interrupt trigger mode,
 *      the corresponding interrupt should be disabled,
 *      to prevent unwanted interrupt.
 *  2. Only support INT0/INT1 for ATmega16.
 *  3. INT2 is always edge trigger mode for ATmega16.
 */
#define DRV_INT_SetExtInterruptLowLevelTrigger(n)       do { COMBINE2(MCUCR_ICS,n,1) = 0;  COMBINE2(MCUCR_ICS,n,0) = 0; } while (0)
#define DRV_INT_SetExtInterruptLevelChangeTrigger(n)    do { COMBINE2(MCUCR_ICS,n,1) = 0;  COMBINE2(MCUCR_ICS,n,0) = 1; } while (0)
#define DRV_INT_SetExtInterruptNegativeEdgeTrigger(n)   do { if ((n) == 2) {COMBINE(MCUCSR_ISC,n)=0;} else {COMBINE2(MCUCR_ICS,n,1) = 1;  COMBINE2(MCUCR_ICS,n,0) = 0;} } while (0)
#define DRV_INT_SetExtInterruptPositiveEdgeTrigger(n)   do { if ((n) == 2) {COMBINE(MCUCSR_ISC,n)=1;} else {COMBINE2(MCUCR_ICS,n,1) = 1;  COMBINE2(MCUCR_ICS,n,0) = 1;} } while (0)
#define DRV_INT_IsExtInterruptOccurred(n)               COMBINE(GIFR_INTF,n)


#endif /* __DRV_INT_H */

