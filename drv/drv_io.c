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
 *   drv_io.c
 * DESCRIPTION:
 *   IO Driver.
 * HISTORY:
 *   2010.1.26        PANDA         Create/Update
 *
*****************************************************************************/

#include <drv.h>

#define IO_INPUT         1
#define IO_OUTPUT        0


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
void DRV_IO_Init(void)
{
#define DECLARE_IO_PIN(_name,_port,_bit,_mode,_init_val,_pin_no,_desc)      \
    do                                                                      \
    {                                                                       \
        if ((_mode) == IO_INPUT)                                            \
        {                                                                   \
            DRV_IO_SetPinInput(IO_PIN(_name));                              \
        }                                                                   \
        else                                                                \
        {                                                                   \
            DRV_IO_SetPinOutput(IO_PIN(_name));                             \
            DRV_IO_WritePinData(IO_PIN(_name), (_init_val));                \
        }                                                                   \
    } while (0);

#include <cfg_hw_def.h>

#undef DECLARE_IO_PIN
}

