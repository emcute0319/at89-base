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
 *   drv_io.h
 * DESCRIPTION:
 *   IO Driver.
 * HISTORY:
 *   2010.1.26        PANDA         Create/Update
 *
*****************************************************************************/

#ifndef __DRV_IO_H
#define __DRV_IO_H


#define IO_LOW  0
#define IO_HIGH 1


#define _IO_PORT(_name)         (P##_name)
#define _IO_BIT(_x)             (_x)
#define IO_PIN(_name)           IO_PIN_##_name

typedef UINT8   DRV_IO_PIN_T;

/* GPIO pin definition */
#define DECLARE_IO_PIN(_name,_port,_bit,_mode,_init_val,_pin_no,_desc)  \
                                            sbit IO_PIN(_name) = _port^_bit;
#include "cfg_hw_def.h"
#undef DECLARE_IO_PIN


#define DRV_IO_SetInput(_pin)               do { (_pin) = HIGH;    } while (0)
#define DRV_IO_SetOutput(_pin)              /* do nothing */
#define DRV_IO_Write(_pin, _bit)            do { (_pin) = (_bit);  } while (0)
#define DRV_IO_Read(_pin)                   (_pin)

#define DRV_IO_WritePort(_port, _val)       do { (_port) = (_val); } while (0)
#define DRV_IO_ReadPort(_port)              (_port)


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_IO_Init
 * DESCRIPTION:
 *      IO Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.26        PANDA         Create/Update
 *****************************************************************************/
void DRV_IO_Init(void);


#endif /* __DRV_IO_H */

