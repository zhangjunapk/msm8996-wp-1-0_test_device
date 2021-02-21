@ECHO OFF
REM Name
REM 	t32sim.cmd
REM
REM Description
REM 	Startup batch file that initializes the T32 session
REM
REM Copyright 2012 - 2014 Qualcomm Inc
REM
REM
REM 04/03/2013	AJCheriyan		Added support for newer T32start location
REM 02/06/2013	AJCheriyan		Fixed issue with multi-chipset config
REM 01/30/2013	AJCheriyan		Added support for multi-chipset configs
REM 07/19/2012	AJCheriyan		First version for MSM8974

CLS
SET SCRIPTSDIR=%~dp0..\tools\cmm
SET OSFLAVOR=
SET OSFLAVORPATH=windows


REM Find the chipset specific file. 
IF /i "%CHIPSET%"=="" (
	FOR /F "tokens=1 delims=" %%A IN ('dir /s /b /a-d %~dp0*.ts2') DO (
		SET CHIPSET=%%A
	)
)
IF /i "%CHIPSET%"=="" GOTO NOT32CONFIG

REM Detect the version of windows
WMIC OS GET OSARCHITECTURE /Format:list >> %TEMP%\%TEMPFILE%
REM Check if we are running windows64 or windows32 because t32
FOR /F "tokens=1 delims=\n" %%A IN ('%COMSPEC% /a /c type "%TEMP%\%TEMPFILE%"') DO SET OSFLAVOR=%%A

IF "%OSFLAVOR%"=="OSArchitecture=64-bit" ECHO "Running 64-bit windows" && SET OSFLAVORPATH=windows64

REM All is good now. Load T32 now.
SET T32SYS=C:\T32
IF NOT EXIST %T32SYS% SET /P T32SYS=Enter location of the T32 installation:
IF NOT EXIST %T32SYS% GOTO EXIT

:START_T32_1
IF NOT EXIST %T32SYS%\t32start.exe (
start %T32SYS%\t32start.exe -runcfgfile %CHIPSET%
GOTO EXIT
)
:START_T32_2
IF EXIST %T32SYS%\bin\%OSFLAVORPATH%\t32start.exe (
start %T32SYS%\bin\%OSFLAVORPATH%\t32start.exe -runcfgfile %CHIPSET%
GOTO EXIT
)

GOTO EXIT

:NOT32CONFIG
COLOR 0C
ECHO T32 Config file could not be found.


:EXIT

