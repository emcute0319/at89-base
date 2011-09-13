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
 *   version.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.2.5        panda.xiong         Create/Update
 *
*****************************************************************************/

#ifndef __VERSION_H
#define __VERSION_H


#include "cfg_hw_def.h"

/* Firmware Version, will be embedded into Firmware */
#define FW_SIG_OFFSET   0x80
#define FW_VERSION      "v0.0.0.1"


#ifdef _VERSION_INTERNAL_
 __root __flash UINT8 _fw_sig[] @ FW_SIG_OFFSET = "CPU:"CPU_TYPE" FW:"FW_VERSION;
#else
 extern UINT8 __flash _fw_sig[];
 #define GET_FW_SIG_STRING()    (_fw_sig)
#endif


#endif /* __VERSION_H */

