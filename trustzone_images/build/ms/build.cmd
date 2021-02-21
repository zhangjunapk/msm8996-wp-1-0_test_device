@echo off
rem ==========================================================================
rem
rem  CBSP Buils system
rem
rem  General Description
rem     build batch file.
rem
rem Copyright (c) 2009-2015 by QUALCOMM Technologies, Incorporated.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem
rem --------------------------------------------------------------------------
rem
rem $Header: //components/rel/build.tz/1.0.6/ms/build.cmd#1 $
rem $DateTime: 2016/12/02 01:48:48 $
rem $Author: pwbldsvc $
rem $Change: 11897026 $
rem                      EDIT HISTORY FOR FILE
rem
rem  This section contains comments describing changes made to the module.
rem  Notice that changes are listed in reverse chronological order.
rem
rem when       who     what, where, why
rem --------   ---     ---------------------------------------------------------
rem
rem ==========================================================================

rem
rem PLEASE note that this script MUST be called with the target and options at
rem then end of command.
rem Syntax: build.cmd BUILD_ID=XYZ CHIPSET=ABC tz --verbose=2
rem We first parse out the chipset build options then everything else must come
rem later.
rem

setlocal

rem ============== Call the set environment batch file ===================
CALL setenv.cmd

rem ===== Setup Paths=====================================================
SET BUILD_ROOT=%~dp0..\..
SET CORE_BSP_ROOT=%BUILD_ROOT%\core\bsp
SET TOOLS_SCONS_ROOT=%BUILD_ROOT%\tools\build\scons
SET CMD_ARGS=%*

setlocal
:LOOP

IF /I "%1" equ "" GOTO CONTINUE

IF /I "%1" equ "BUILD_ID" (
 SET BUILD_ID=%2
 GOTO SHIFT2
)
IF /I "%1" equ "BUILD_VER" (
  SET BUILD_VER=%2
  GOTO SHIFT2
)
IF /I "%1" equ "MSM_ID" (
  SET MSM_ID=%2
  GOTO SHIFT2
)
IF /I "%1" equ "HAL_PLATFORM" (
  SET  HAL_PLATFORM=%2
  GOTO SHIFT2
)
IF /I "%1" equ "TARGET_FAMILY" (
  SET TARGET_FAMILY=%2
  GOTO SHIFT2
)
IF /I "%1" equ "BUILD_ASIC" (
  SET BUILD_ASIC=%2
  GOTO SHIFT2
)
IF /I "%1" equ "CHIPSET" (
  SET CHIPSET=%2
  GOTO SHIFT2
)
IF /I "%1" equ "MAPREPORT" (
  SET MAPREPORT=%2
  GOTO SHIFT2
)

SHIFT
GOTO LOOP

:SHIFT2
SHIFT
SHIFT
GOTO LOOP

:CONTINUE
IF /I "%MSM_ID%" equ "8956" (
  set _result=%CMD_ARGS:*8956=%
  goto SET_8956
)
IF /I "%CHIPSET%" equ "msm8956" (
  set _result=%CMD_ARGS:*msm8956=%
  goto SET_8956
)
IF /I "%HAL_PLATFORM%" equ "8956" (
  set _result=%CMD_ARGS:*8956=%
  goto SET_8956
)
IF /I "%MSM_ID%" equ "8952" (
  set _result=%CMD_ARGS:*8952=%
  goto SET_8952
)
IF /I "%CHIPSET%" equ "msm8952" (
  set _result=%CMD_ARGS:*msm8952=%
  goto SET_8952
)
IF /I "%HAL_PLATFORM%" equ "8952" (
  set _result=%CMD_ARGS:*8952=%
  goto SET_8952
)
IF /I "%MSM_ID%" equ "8953" (
  set _result=%CMD_ARGS:*8953=%
  goto SET_8953
)
IF /I "%CHIPSET%" equ "msm8953" (
  set _result=%CMD_ARGS:*msm8953=%
  goto SET_8953
)
IF /I "%HAL_PLATFORM%" equ "8953" (
  set _result=%CMD_ARGS:*8953=%
  goto SET_8953
)
IF /I "%MSM_ID%" equ "8996" (
  set _result=%CMD_ARGS:*8996=%
  goto SET_8996
)
IF /I "%CHIPSET%" equ "msm8996" (
  set _result=%CMD_ARGS:*msm8996=%
  goto SET_8996
)
IF /I "%HAL_PLATFORM%" equ "8996" (
  set _result=%CMD_ARGS:*8996=%
  goto SET_8996
)
IF /I "%MSM_ID%" equ "8998" (
  set _result=%CMD_ARGS:*8998=%
  goto SET_8998
)
IF /I "%CHIPSET%" equ "msm8998" (
  set _result=%CMD_ARGS:*msm8998=%
  goto SET_8998
)
IF /I "%HAL_PLATFORM%" equ "8998" (
  set _result=%CMD_ARGS:*8998=%
  goto SET_8998
)
IF /I "%MSM_ID%" equ "8937" (
  set _result=%CMD_ARGS:*8937=%
  goto SET_8937
)
IF /I "%CHIPSET%" equ "msm8937" (
  set _result=%CMD_ARGS:*msm8937=%
  goto SET_8937
)
IF /I "%HAL_PLATFORM%" equ "8937" (
  set _result=%CMD_ARGS:*8937=%
  goto SET_8937
)
IF /I "%MSM_ID%" equ "9645" (
  set _result=%CMD_ARGS:*9645=%
  goto SET_9645
)
IF /I "%CHIPSET%" equ "mdm9645" (
  set _result=%CMD_ARGS:*9645=%
  goto SET_9645
)
IF /I "%HAL_PLATFORM%" equ "9645" (
  set _result=%CMD_ARGS:*9645=%
  goto SET_9645
)
IF /I "%TARGET_FAMILY%" equ "9645" (
  set _result=%CMD_ARGS:*9645=%
  goto SET_9645
)
IF /I "%MSM_ID%" equ "stubs" (
  set _result=%CMD_ARGS:*stubs=%
  goto SET_STUBS
)
IF /I "%CHIPSET%" equ "stubs" (
  set _result=%CMD_ARGS:*stubs=%
  goto SET_STUBS
)
IF /I "%HAL_PLATFORM%" equ "stubs" (
  set _result=%CMD_ARGS:*stubs=%
  goto SET_STUBS
)

echo "Please Specify the CHIPSET to build"
EXIT /B

:SET_8956
rem Below BUILD_ID is temporary until we have full details on 8916 mem config
SET BUILD_ID=MAYAANAA
SET BUILD_VER=40000000
SET BUILD_ASIC=8956A
SET MSM_ID=8956
SET HAL_PLATFORM=8956
SET TARGET_FAMILY=bear
SET CHIPSET=msm8956
SET _tempresult=%_result:hdcpapp=%

IF NOT "%_result%" == "%_tempresult%" (
  SET _tempresult=%_result:-c=%
  IF NOT "%_result%" == "%_tempresult%" (
    DEL %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\dxhdcp2*"
  ) ELSE (
    MKDIR %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%
    COPY "%CORE_BSP_ROOT%\trustzone\qsapps\hdcpapp\build\*.*" "%BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\*.*"
  )
)

SET _result=%_result:hdcpapp=%
goto DO_BUILD

:SET_8952
rem Below BUILD_ID is temporary until we have full details on 8916 mem config
SET BUILD_ID=NAKAANAA
SET BUILD_VER=40000000
SET BUILD_ASIC=8952A
SET MSM_ID=8952
SET HAL_PLATFORM=8952
SET TARGET_FAMILY=bear
SET CHIPSET=msm8952
SET _tempresult=%_result:hdcpapp=%

IF NOT "%_result%" == "%_tempresult%" (
  SET _tempresult=%_result:-c=%
  IF NOT "%_result%" == "%_tempresult%" (
    DEL %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\dxhdcp2*"
  ) ELSE (
    MKDIR %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%
    COPY "%CORE_BSP_ROOT%\trustzone\qsapps\hdcpapp\build\*.*" "%BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\*.*"
  )
)

SET _result=%_result:hdcpapp=%
goto DO_BUILD

:SET_8953
rem Below BUILD_ID is temporary until we have full details on 8916 mem config
SET BUILD_ID=SANAANAA
SET BUILD_VER=40000000
SET BUILD_ASIC=8953A
SET MSM_ID=8953
SET HAL_PLATFORM=8953
SET TARGET_FAMILY=bear
SET CHIPSET=msm8953
SET _tempresult=%_result:hdcpapp=%

IF NOT "%_result%" == "%_tempresult%" (
  SET _tempresult=%_result:-c=%
  IF NOT "%_result%" == "%_tempresult%" (
    DEL %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\dxhdcp2*"
  ) ELSE (
    MKDIR %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%
    COPY "%CORE_BSP_ROOT%\trustzone\qsapps\hdcpapp\build\*.*" "%BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\*.*"
  )
)

SET _result=%_result:hdcpapp=%
goto DO_BUILD

:SET_8996
SET BUILD_ID=IADAANAA
SET BUILD_VER=40000000
SET BUILD_ASIC=8996
SET MSM_ID=8996
SET HAL_PLATFORM=8996
SET TARGET_FAMILY=honeybadger
SET CHIPSET=msm8996
SET _tempresult=%_result:hdcpapp=%

IF NOT "%_result%" == "%_tempresult%" (
  SET _tempresult=%_result:-c=%
  IF NOT "%_result%" == "%_tempresult%" (
    DEL %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\dxhdcp2*"
  ) ELSE (
    MKDIR %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%
    COPY "%CORE_BSP_ROOT%\trustzone\qsapps\hdcpapp\build\*.*" "%BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\*.*"
  )
)

SET _result=%_result:hdcpapp=%
goto DO_BUILD

:SET_8998
SET BUILD_ID=RAGAANAA
SET BUILD_VER=40000000
SET BUILD_ASIC=8998
SET MSM_ID=8998
SET TARGET_FAMILY=honeybadger
SET CHIPSET=msm8998
SET _tempresult=%_result:hdcpapp=%

IF "%HAL_PLATFORM%" == "VIRTIO" (
  SET BUILD_ID=RAGAANVA
)
IF "%HAL_PLATFORM%" == "RUMI" (
  SET BUILD_ID=RAGAANRA
)
IF "%HAL_PLATFORM%" == "" (
  SET HAL_PLATFORM=8998
)

IF NOT "%_result%" == "%_tempresult%" (
  SET _tempresult=%_result:-c=%
  IF NOT "%_result%" == "%_tempresult%" (
    DEL %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\dxhdcp2*"
  ) ELSE (
    MKDIR %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%
    COPY "%CORE_BSP_ROOT%\trustzone\qsapps\hdcpapp\build\*.*" "%BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\*.*"
  )
)

SET _result=%_result:hdcpapp=%
goto DO_BUILD

:SET_8937
rem Below BUILD_ID is temporary until we have full details on 8916 mem config
SET BUILD_ID=ZALAANAA
SET BUILD_VER=40000000
SET BUILD_ASIC=8937A
SET MSM_ID=8937
SET HAL_PLATFORM=8937
SET TARGET_FAMILY=bear
SET CHIPSET=msm8937
SET _tempresult=%_result:hdcpapp=%

IF NOT "%_result%" == "%_tempresult%" (
  SET _tempresult=%_result:-c=%
  IF NOT "%_result%" == "%_tempresult%" (
    DEL %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\dxhdcp2*"
  ) ELSE (
    MKDIR %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%
    COPY "%CORE_BSP_ROOT%\trustzone\qsapps\hdcpapp\build\*.*" "%BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\*.*"
  )
)

SET _result=%_result:hdcpapp=%
goto DO_BUILD

:SET_9645
rem BUILD_ID is passed in from build_9645.cmd
rem BUILD_ID for 9645 is set to TAFAANBA
IF "%BUILD_ID%"=="" SET BUILD_ID=TAFAANBA
SET BUILD_VER=40000000
SET BUILD_ASIC=9645
SET MSM_ID=9645
SET HAL_PLATFORM=9645
SET TARGET_FAMILY=badger
SET CHIPSET=mdm9645
SET _tempresult=%_result:hdcpapp=%

IF NOT "%_result%" == "%_tempresult%" (
  SET _tempresult=%_result:-c=%
  IF NOT "%_result%" == "%_tempresult%" (
    DEL %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\dxhdcp2*"
  ) ELSE (
    MKDIR %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%
    COPY "%CORE_BSP_ROOT%\trustzone\qsapps\hdcpapp\build\*.*" "%BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\*.*"
  )
)

SET _result=%_result:hdcpapp=%
goto DO_BUILD

:SET_STUBS
SET BUILD_ID=CHIPSTUBS
SET BUILD_VER=40000000
SET BUILD_ASIC=0000
SET MSM_ID=0000
SET HAL_PLATFORM=0000
SET TARGET_FAMILY=none
SET CHIPSET=msm0000
SET _tempresult=%_result:hdcpapp=%

IF NOT "%_result%" == "%_tempresult%" (
  SET _tempresult=%_result:-c=%
  IF NOT "%_result%" == "%_tempresult%" (
    DEL %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\dxhdcp2*"
  ) ELSE (
    MKDIR %BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%
    COPY "%CORE_BSP_ROOT%\trustzone\qsapps\hdcpapp\build\*.*" "%BUILD_ROOT%\build\ms\bin\PIL_IMAGES\SPLITBINS_%BUILD_ID%\*.*"
  )
)

SET _result=%_result:hdcpapp=%
goto DO_BUILD

:DO_END
EXIT /B

SET IMAGES=%1
REM SET BUILDSPEC=KLOCWORK

:DO_BUILD
SET BUILD_CMD=BUILD_ID=%BUILD_ID% BUILD_VER=%BUILD_VER% MSM_ID=%MSM_ID% HAL_PLATFORM=%HAL_PLATFORM% TARGET_FAMILY=%TARGET_FAMILY% BUILD_ASIC=%BUILD_ASIC% CHIPSET=%CHIPSET% %_result%

CALL %TOOLS_SCONS_ROOT%\build\rename-log.cmd

@echo CALL %TOOLS_SCONS_ROOT%\build\build.cmd -f target.scons %BUILD_CMD%

CALL %TOOLS_SCONS_ROOT%\build\build.cmd -f target.scons %BUILD_CMD%

IF /I "%MAPREPORT%" equ "1" (
  IF NOT "%_result%"=="%_result:tz=%" (
     python %TOOLS_SCONS_ROOT%\linker_reporter\report_generator.py %BUILD_ROOT%\core\securemsm\trustzone
     python %TOOLS_SCONS_ROOT%\linker_reporter\report_generator.py %BUILD_ROOT%\core\bsp\qsee
     python %TOOLS_SCONS_ROOT%\linker_reporter\report_generator.py %BUILD_ROOT%\core\bsp\monitor
     python %TOOLS_SCONS_ROOT%\linker_reporter\report_generator.py %BUILD_ROOT%\core\bsp\devcfg
  )
  IF NOT "%_result%"=="%_result:hyp=%" (
     python %TOOLS_SCONS_ROOT%\linker_reporter\report_generator.py %BUILD_ROOT%\core\bsp\hypervisor
  )

  IF NOT "%_result%"=="%_result:sampleapp=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:commonlib=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:gpsample=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:gptest=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:ttacapi1=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:ttacapi2=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:ttacapi3=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:ttacapi4=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:ttacapi5=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:ttacrp1=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:ttads1=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:ttatime1=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:ttatcf1=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:ttatcf2=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:ttatcf3=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:ttatcf4=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:ttatcf5=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:isdbtmm=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:uefisecapp=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:winsecapp=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:uefi_sec=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:winsecap=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:playready=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:widevine=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:fingerprint=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:fidocrypto=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:chamomile=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:sampleauth=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:sampleextauth=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:hdcp1=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:securemm=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:secure_ui_sample=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:secureindicator=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:mdtp=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:teetest=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:cppf=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:secotacl=%" goto GENERATE_APP_LINKREPORT
  IF NOT "%_result%"=="%_result:iris=%" goto GENERATE_APP_LINKREPORT

  goto DO_END
) ELSE (
  goto DO_END
)

:GENERATE_APP_LINKREPORT
python %TOOLS_SCONS_ROOT%\linker_reporter\report_generator.py %BUILD_ROOT%\core\bsp\trustzone\qsapps
goto DO_END
