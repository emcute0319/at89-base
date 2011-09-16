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


/* the real IO definition is in this auto-generated file */
#define DECLARE_IO_PORT(...)            /* empty */
#define DECLARE_IO_PIN(...)             /* empty */
#include "cfg_io_def.h"
#undef DECLARE_IO_PORT
#undef DECLARE_IO_PIN


#define IO_PIN(_name)                   COMBINE(IO_PIN_, _name)

#define _IO_OUT(_name)                  COMBINE(_name, _PORT)
#define _IO_DDR(_name)                  COMBINE(_name, _DDR)
#define _IO_IN(_name)                   COMBINE(_name, _PIN)
#define _IO_MODE(_name)                 COMBINE(_name, _MODE)
#define _IO_INIT(_name)                 COMBINE(_name, _INIT)

#define _PORT_REG(_name, _port)         COMBINE(_name, _port)
#define _PORT_OUT(_port)                _PORT_REG(PORT, _port)
#define _PORT_DDR(_port)                _PORT_REG(DDR,  _port)
#define _PORT_IN(_port)                 _PORT_REG(PIN,  _port)

/* IO Pin operation API */
#define DRV_IO_SetInput(_pin)           do { _IO_DDR(_pin) = LOW;     } while (0)
#define DRV_IO_SetOutput(_pin)          do { _IO_DDR(_pin) = HIGH;    } while (0)
#define DRV_IO_Write(_pin, _val)        do { _IO_OUT(_pin) = (_val);  } while (0)
#define DRV_IO_Read(_pin)               _IO_IN(_pin)

/* IO Port operation API */
#define DRV_IO_WritePort(_port, _val)   do { _PORT_OUT(_port) = (_val); } while (0)
#define DRV_IO_ReadPort(_port)          _PORT_IN(_port)


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

