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
 *   cli_porting.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2011.10.19        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __CLI_PORTING_H
#define __CLI_PORTING_H


#include "typedef.h"
#include "drv.h"


#define CLI_VT_Printf(...)      DRV_UART_Printf(__VA_ARGS__)
#define CLI_VT_ReadKey()        DRV_UART_ReadByte()


#define CLI_PROMPT              ""
#define CLI_CMD_BUF_MAX         80
#define CLI_MAX_PARAM		    16


#include "cmd_about.h"

#define CLI_CMD_LIST                                                        \
{                                                                           \
    { "about", CMD_About, "about (show CLI information)" },                 \
}


#endif /* __CLI_PORTING_H */

