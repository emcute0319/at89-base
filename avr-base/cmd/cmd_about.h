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
 *   cmd_about.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2011.10.19        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#ifndef __CMD_ABOUT_H
#define __CMD_ABOUT_H


/******************************************************************************
 * FUNCTION NAME:
 *      CMD_About
 * DESCRIPTION:
 *      CLI Command: about
 * PARAMETERS:
 *      vParam    : Parameter counts;
 *      aParam[]  : Parameter lists;
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2011.10.19        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_About(IN UINT8 vParam, IN UINT8 *aParam[]);


#endif /* __CMD_ABOUT_H */

