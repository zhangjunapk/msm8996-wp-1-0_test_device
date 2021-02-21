@echo off
rem ==========================================================================
rem
rem  CBSP Buils system
rem
rem  General Description
rem     build batch file.
rem
rem Copyright (c) 2009-2009 by QUALCOMM, Incorporated.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem
rem --------------------------------------------------------------------------
rem
rem $Header: //components/rel/core.tz/1.0.3.c1/bsp/build/cbspbuild.cmd#1 $
rem $DateTime: 2016/12/02 01:46:26 $
rem $Author: pwbldsvc $
rem $Change: 11896995 $
rem                      EDIT HISTORY FOR FILE
rem
rem  This section contains comments describing changes made to the module.
rem  Notice that changes are listed in reverse chronological order.
rem
rem when       who     what, where, why
rem --------   ---     ---------------------------------------------------------
rem
rem ==========================================================================

setlocal
call \\stone\aswcrm\smart\nt\bin\RVCT221P593gnumake.cmd 

SET BUILD_ID=AABBQMAA
SET BUILD_VER=1010

REM Common
SET BUILD_ASIC=7X30A
SET MSM_ID=7x30
SET HAL_PLATFORM=7x30
SET TARGET_FAMILY=7600
SET CHIPSET=msm7x30

set BUILD_CMD=BUILD_ID=%BUILD_ID% BUILD_VER=%BUILD_VER% MSM_ID=%MSM_ID% HAL_PLATFORM=%HAL_PLATFORM% TARGET_FAMILY=%TARGET_FAMILY% BUILD_ASIC=%BUILD_ASIC% CHIPSET=%CHIPSET% %*

cd %~dp0..\..\core\bsp\build
call tools\rename-log.cmd
call tools\build.cmd %BUILD_CMD%
