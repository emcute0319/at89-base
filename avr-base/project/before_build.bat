:: ############################################################################
::
::  (C) Copyright 2007-2010
::   This program is free software; you can redistribute it and/or
::   modify it under the terms of the GNU General Public License as
::   published by the Free Software Foundation; either version 2 of
::   the License, or (at your option) any later version.
::
::   This program is distributed in the hope that it will be useful,
::   but WITHOUT ANY WARRANTY; without even the implied warranty of
::   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
::   GNU General Public License for more details.
::
::   You should have received a copy of the GNU General Public License
::   along with this program; if not, write to the Free Software
::   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
::   MA 02111-1307 USA
::
::  DESCRIPTION:
::    Do necessary operations before building.
::
::  HISTORY:
::    2011.9.13     Panda.Xiong       Create
:: 
:: ############################################################################

:: close echo
@echo off

set PROJECT_DIR=%1
set PROJECT_NAME=%2

:: All binary tools should put into fixed directory
path %COMPILER_BASE%\bin;%PROJECT_DIR%\tools\bin

mkdir %PROJECT_DIR%\build\tmp\
converter %PROJECT_DIR%\cfg\cfg_hw_porting.h %PROJECT_DIR%\build\tmp\~cfg_io_def.h

