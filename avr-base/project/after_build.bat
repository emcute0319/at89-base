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
::    Genrate released firmware for Target CPU.
::
::  HISTORY:
::    2010.2.20     Panda.Xiong       Create
:: 
:: ############################################################################

:: close echo
@echo off

:: All binary tools should put into fixed directory
path %COMPILER_BASE%\bin

set HEX2BIN=hex2bin

set PROJECT_DIR=%1
set PROJECT_NAME=%2

set IMAGE_DIR=%PROJECT_DIR%\build\image
set OBJ_DIR=%PROJECT_DIR%\build\obj

set IMAGE_MAP=%OBJ_DIR%\%PROJECT_NAME%.map
set IMAGE_LSS=%OBJ_DIR%\%PROJECT_NAME%.cod
set IMAGE_HEX=%IMAGE_DIR%\%PROJECT_NAME%.hex
set IMAGE_BIN=%IMAGE_DIR%\%PROJECT_NAME%.bin
set EEPROM_HEX=%IMAGE_DIR%\%PROJECT_NAME%_eeprom.hex
set EEPROM_BIN=%IMAGE_DIR%\%PROJECT_NAME%_eeprom.bin

echo **************************************************************************

:: create image directory
if not exist %IMAGE_DIR% (
    mkdir %IMAGE_DIR%
)

:: copy Application map file to image directory
echo Creating file %PROJECT_NAME%.map ...
cp %IMAGE_MAP% %IMAGE_DIR%\%PROJECT_NAME%.map

:: create Application binary file
echo Creating file %PROJECT_NAME%.bin ...
%HEX2BIN% %IMAGE_HEX% %IMAGE_BIN%
echo.

:: create Application EEPROM file
echo Creating file %PROJECT_NAME%_eeprom.bin ...
%HEX2BIN% %EEPROM_HEX% %EEPROM_BIN%
echo.

echo **************************************************************************

