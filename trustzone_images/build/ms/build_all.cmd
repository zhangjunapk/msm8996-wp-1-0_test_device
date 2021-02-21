@echo off
rem ==========================================================================
rem
rem  CBSP Builds system
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
rem $Header: //components/rel/build.tz/1.0.6/ms/build_all.cmd#1 $
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
rem 10/17/13   ib      Added securemm for apq8084
rem ==========================================================================

setlocal

rem ===== Setup Paths=====================================================
SET BUILD_ROOT=%~dp0..\..
SET MAPREPORT=0

IF "%1"=="CHIPSET" (
  IF "%2" == "msm8996" (
    pushd %BUILD_ROOT%\build\ms\bin\IADAANAA
    del tz.mbn hyp.mbn devcfg.mbn devcfg_noac.mbn appsbl.mbn dummy_venus.mbn dummy_hexagon.mbn tz_with_test.mbn tzbsptest.mbn tztestexec.mbn tztimage.img
>>>> ORIGINAL //components/rel/build.tz/1.0/ms/build_all.cmd#21
    del cmnlib.mbn gpsample.mbn gptest.mbn ttacapi1.mbn ttacapi2.mbn ttacapi3.mbn ttacapi4.mbn ttacapi5.mbn ttacrp1.mbn ttads1.mbn ttatime1.mbn ttatcf1.mbn ttatcf2.mbn ttatcf3.mbn ttatcf4.mbn ttatcf5.mbn ttaari1.mbn isdbtmm.mbn sampleapp.mbn assurancetest.mbn fingerprint.mbn smplserv.mbn smplcert.mbn uefi_sec.mbn winsecap.mbn hdcp2p2.mbn lksecapp.mbn keymaster.mbn hdcp1.mbn apttestapp.mbn apttestapp64.mbn aptcryptotestapp.mbn aptcryptotestapp64.mbn voiceprint.mbn dxhdcp2.mbn dxhdcp2dbg.mbn qpay.mbn qpay64.mbn
==== THEIRS //components/rel/build.tz/1.0/ms/build_all.cmd#22
    del cmnlib.mbn gpsample.mbn gptest.mbn ttacapi1.mbn ttacapi2.mbn ttacapi3.mbn ttacapi4.mbn ttacapi5.mbn ttacrp1.mbn ttads1.mbn ttatime1.mbn ttatcf1.mbn ttatcf2.mbn ttatcf3.mbn ttatcf4.mbn ttatcf5.mbn isdbtmm.mbn sampleapp.mbn assurancetest.mbn fingerprint.mbn smplserv.mbn smplcert.mbn uefi_sec.mbn winsecap.mbn hdcp2p2.mbn lksecapp.mbn keymaster.mbn hdcp1.mbn apttestapp.mbn apttestapp64.mbn aptcryptotestapp.mbn aptcryptotestapp64.mbn voiceprint.mbn dxhdcp2.mbn dxhdcp2dbg.mbn qpay.mbn qpay64.mbn
==== YOURS //kenz.build.tz.1.0.build_40_2/trustzone_images/build/ms/build_all.cmd
    del cmnlib.mbn gpsample.mbn gptest.mbn ttacapi1.mbn ttacapi2.mbn ttacapi3.mbn ttacapi4.mbn ttacapi5.mbn ttacrp1.mbn ttads1.mbn ttatime1.mbn ttatcf1.mbn ttatcf2.mbn ttatcf3.mbn ttatcf4.mbn ttatcf5.mbn ttaari1.mbn isdbtmm.mbn sampleapp.mbn assurancetest.mbn fingerprint.mbn smplserv.mbn smplcert.mbn uefi_sec.mbn winsecap.mbn hdcp2p2.mbn lksecapp.mbn keymaster.mbn hdcp1.mbn apttestapp.mbn apttestapp64.mbn aptcryptotestapp.mbn aptcryptotestapp64.mbn voiceprint.mbn dxhdcp2.mbn dxhdcp2dbg.mbn qpay.mbn qpay64.mbn iris.mbn 
<<<<
    popd
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\playread.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\widevine.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\fidocrypto.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\fidocfg.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\fidosui.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\chamomile.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\sampleauth.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\sampleextauth.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\macchiato_sample.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\securemm.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\secure_ui_sample.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\secure_ui_sample64.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\secureindicator.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\qmpsecap.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\mdtp.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\dhsecapp.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\apttestapp.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\apttestapp64.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\teetest.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\aptcryptotestapp.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\aptcryptotestapp64.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\cppf.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\secotacl.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\qpay.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\qpay64.mbn
    del %BUILD_ROOT%\build\ms\bin\IADAANAA\pr_3_0.mbn
	

    IF "%3"=="MAPREPORT" (
      IF "%4" == "1" (
        SET MAPREPORT=1
      )
    )	
	
    goto BUILD_8996_all
  )
  echo Unknown chipset...
  EXIT /B
)

IF "%1"=="MAPREPORT" (
  IF "%2" == "1" (
    SET MAPREPORT=1
    goto :BUILD_all
  )
)

IF "%1" == "" (
  goto :BUILD_all
)

IF "%1" == "-c" (
  CALL %BUILD_ROOT%\build\ms\clean_all.cmd
  endlocal
  EXIT /B
)

echo Please specify a valid chipset e.g. CHIPSET=msm8996
EXIT /B

rem TODO: doesn't build CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 tz tz_with_test tzbsptest
rem       it loses the order.?!!
:BUILD_8996_all
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% tz
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% hyp devcfg
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\tz.mbn (
  CALL :ERROR_MSG tz.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\hyp.mbn (
  CALL :ERROR_MSG hyp.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\devcfg.mbn (
  CALL :ERROR_MSG devcfg.mbn  msm8996
  EXIT /B 1
)

CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% devcfg_noac
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\devcfg_noac.mbn (
  CALL :ERROR_MSG devcfg_noac.mbn  msm8996
  EXIT /B 1
)

CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% tz_with_test tztestexec
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\tz_with_test.mbn (
  CALL :ERROR_MSG tz_with_test.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\tztestexec.mbn (
  CALL :ERROR_MSG tztestexec.mbn  msm8996
  EXIT /B 1
)

CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% tzbsptest -j 1
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\tzbsptest.mbn (
  CALL :ERROR_MSG tzbsptest.mbn  msm8996
  EXIT /B 1
)

rem CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% commonlib gpsample gptest pr_3_0 ttacapi1 ttacapi2 ttacapi3 ttacapi4 ttacapi5 ttacrp1 ttads1 ttatime1 ttatcf1 ttatcf2 ttatcf3 ttatcf4 ttatcf5 isdbtmm sampleapp smplserv smplcert uefi_sec winsecap hdcp2p2 lksecapp keymaster fingerprint USES_FLAGS=USES_NO_CP -j 1
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% commonlib USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% gpsample USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% gptest USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% ttacapi1 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% ttacapi2 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% ttacapi3 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% ttacapi4 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% ttacapi5 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% ttacrp1 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% ttads1 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% ttatime1 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% ttatcf1 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% ttatcf2 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% ttatcf3 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% ttatcf4 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% ttatcf5 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% isdbtmm USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% sampleapp USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% assurancetest USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% fingerprint USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% voiceprint USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% smplserv USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% smplcert USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% uefi_sec USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% winsecap USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% hdcp2p2 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% lksecapp USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% keymaster USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% playready USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% widevine USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% fidocrypto USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% fidocfg USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% fidosui USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% chamomile USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% sampleauth USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% sampleextauth USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% macchiato_sample USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% hdcp1 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% securemm USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% secure_ui_sample USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% secureindicator USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% qmpsecap USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% mdtp USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% dhsecapp USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% apttestapp USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% teetest USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% aptcryptotestapp USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% dxhdcp2 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% dxhdcp2dbg USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% cppf USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% secotacl USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% qpay USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% pr_3_0 USES_FLAGS=USES_NO_CP
CALL %BUILD_ROOT%\build\ms\build.cmd CHIPSET=msm8996 MAPREPORT=%MAPREPORT% iris USES_FLAGS=USES_NO_CP



IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\cmnlib.mbn (
  CALL :ERROR_MSG commonlib.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\cmnlib64.mbn (
  CALL :ERROR_MSG cmnlib64.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\gpsample.mbn (
  CALL :ERROR_MSG gpsample.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\gptest.mbn (
  CALL :ERROR_MSG gptest.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\ttacapi1.mbn (
  CALL :ERROR_MSG ttacapi1.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\ttacapi2.mbn (
  CALL :ERROR_MSG ttacapi2.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\ttacapi3.mbn (
  CALL :ERROR_MSG ttacapi3.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\ttacapi4.mbn (
  CALL :ERROR_MSG ttacapi4.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\ttacapi5.mbn (
  CALL :ERROR_MSG ttacapi5.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\ttacrp1.mbn (
  CALL :ERROR_MSG ttacrp1.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\ttads1.mbn (
  CALL :ERROR_MSG ttads1.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\ttatime1.mbn (
  CALL :ERROR_MSG ttatime1.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\ttatcf1.mbn (
  CALL :ERROR_MSG ttatcf1.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\ttatcf2.mbn (
  CALL :ERROR_MSG ttatcf2.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\ttatcf3.mbn (
  CALL :ERROR_MSG ttatcf3.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\ttatcf4.mbn (
  CALL :ERROR_MSG ttatcf4.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\ttatcf5.mbn (
  CALL :ERROR_MSG ttatcf5.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\smplap32.mbn (
  CALL :ERROR_MSG sampleapp.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\smplap64.mbn (
  CALL :ERROR_MSG sampleapp.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\assurancetest.mbn (
  CALL :ERROR_MSG assurancetest.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\assurancetest64.mbn (
  CALL :ERROR_MSG assurancetest64.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\fingerprint.mbn (
  CALL :ERROR_MSG fingerprint.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\voiceprint.mbn (
  CALL :ERROR_MSG voiceprint.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\isdbtmm.mbn (
CALL :ERROR_MSG isdbtmm.mbn  msm8996
EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\smplserv.mbn (
  CALL :ERROR_MSG smplserv.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\smplcert.mbn (
  CALL :ERROR_MSG smplcert.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\uefi_sec.mbn (
  CALL :ERROR_MSG uefi_sec.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\winsecap.mbn (
  CALL :ERROR_MSG winsecap.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\hdcp2p2.mbn (
  CALL :ERROR_MSG hdcp2p2.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\lksecapp.mbn (
  CALL :ERROR_MSG lksecapp.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\keymaster.mbn (
  CALL :ERROR_MSG keymaster.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\playread.mbn (
  CALL :ERROR_MSG playread.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\widevine.mbn (
  CALL :ERROR_MSG widevine.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\fidocrypto.mbn (
  CALL :ERROR_MSG fidocrypto.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\fidocfg.mbn (
  CALL :ERROR_MSG fidocfg.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\fidosui.mbn (
  CALL :ERROR_MSG fidosui.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\chamomile.mbn (
  CALL :ERROR_MSG chamomile.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\sampleauth.mbn (
  CALL :ERROR_MSG sampleauth.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\sampleextauth.mbn (
  CALL :ERROR_MSG sampleextauth.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\macchiato_sample.mbn (
  CALL :ERROR_MSG macchiato_sample.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\hdcp1.mbn (
  CALL :ERROR_MSG hdcp1.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\securemm.mbn (
  CALL :ERROR_MSG securemm.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\secure_ui_sample.mbn (
  CALL :ERROR_MSG secure_ui_sample.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\secure_ui_sample64.mbn (
  CALL :ERROR_MSG secure_ui_sample64.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\secureindicator.mbn (
  CALL :ERROR_MSG secureindicator.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\qmpsecap.mbn (
  CALL :ERROR_MSG qmpsecap.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\mdtp.mbn (
  CALL :ERROR_MSG mdtp.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\dhsecapp.mbn (
  CALL :ERROR_MSG dhsecapp.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\apttestapp.mbn (
  CALL :ERROR_MSG apttestapp.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\apttestapp64.mbn (
  CALL :ERROR_MSG apttestapp64.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\teetest.mbn (
  CALL :ERROR_MSG teetest.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\aptcryptotestapp.mbn (
  CALL :ERROR_MSG aptcryptotestapp.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\aptcryptotestapp64.mbn (
  CALL :ERROR_MSG aptcryptotestapp64.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\dxhdcp2.mbn (
  CALL :ERROR_MSG dxhdcp2.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\dxhdcp2dbg.mbn (
  CALL :ERROR_MSG dxhdcp2dbg.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\cppf.mbn (
  CALL :ERROR_MSG cppf.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\secotacl.mbn (
  CALL :ERROR_MSG secotacl.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\qpay.mbn (
  CALL :ERROR_MSG qpay.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\qpay64.mbn (
  CALL :ERROR_MSG qpay64.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\pr_3_0.mbn (
  CALL :ERROR_MSG pr_3_0.mbn  msm8996
  EXIT /B 1
)
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\iris.mbn (
  CALL :ERROR_MSG iris.mbn  msm8996
  EXIT /B 1
)

CALL :BUILD_CHIPSET_SUCCESS IADAANAA 8996
goto :DONE

:BUILD_CHIPSET_SUCCESS
echo ==============================================================================
echo BUILD_ALL.cmd build summary for %2
echo ==============================================================================
echo BUILD SUCCESS - The following images were generated:
echo %1\tz.mbn
echo %1\hyp.mbn
echo %1\devcfg.mbn
echo %1\devcfg_noac.mbn
echo %1\tz_with_test.mbn
echo %1\tztestexec.mbn
echo %1\tzbsptest.mbn
echo %1\tztimage.img
echo %1\cmnlib.mbn
echo %1\gpsample.mbn
echo %1\gptest.mbn
echo %1\ttacapi1.mbn
echo %1\ttacapi2.mbn
echo %1\ttacapi3.mbn
echo %1\ttacapi4.mbn
echo %1\ttacapi5.mbn
echo %1\ttacrp1.mbn
echo %1\ttads1.mbn
echo %1\ttatime1.mbn
echo %1\ttatcf1.mbn
echo %1\ttatcf2.mbn
echo %1\ttatcf3.mbn
echo %1\ttatcf4.mbn
echo %1\ttatcf5.mbn
echo %1\teetest.mbn
echo %1\sampleapp.mbn
echo %1\assurancetest.mbn
echo %1\fingerprint.mbn
echo %1\voiceprint.mbn
echo %1\isdbtmm.mbn
echo %1\smplserv.mbn
echo %1\smplcert.mbn
echo %1\uefi_sec.mbn
echo %1\winsecap.mbn
echo %1\hdcp2p2.mbn
echo %1\lksecapp.mbn
echo %1\keymaster.mbn
echo %1\playread.mbn
echo %1\widevine.mbn
echo %1\fidocrypto.mbn
echo %1\fidocfg.mbn
echo %1\fidosui.mbn
echo %1\chamomile.mbn
echo %1\sampleauth.mbn
echo %1\sampleextauth.mbn
echo %1\macchiato_sample.mbn
echo %1\hdcp1.mbn
echo %1\securemm.mbn
echo %1\secure_ui_sample.mbn
echo %1\secure_ui_sample64.mbn
echo %1\secureindicator.mbn
echo %1\qmpsecap.mbn
echo %1\mdtp.mbn
echo %1\dhsecapp.mbn
echo %1\apttestapp.mbn
echo %1\apttestapp64.mbn
echo %1\aptcryptotestapp.mbn
echo %1\aptcryptotestapp64.mbn
echo %1\dxhdcp2.mbn
echo %1\dxhdcp2dbg.mbn
echo %1\cppf.mbn
echo %1\secotacl.mbn
echo %1\qpay.mbn
echo %1\qpay64.mbn
echo %1\pr_3_0.mbn
echo %1\iris.mbn
echo. 2>BuildAllSuccess_%2.txt
EXIT /B
goto :EOF

:BUILD_all
CALL %~f0 CHIPSET=msm8996 MAPREPORT=%MAPREPORT%
IF NOT EXIST %BUILD_ROOT%\build\ms\bin\IADAANAA\tz.mbn GOTO BUILD_all_error
GOTO DONE_all

:DONE
echo ***BUILDING COMPLETE***
endlocal
EXIT /B

:DONE_all
echo ***BUILDING COMPLETE FOR ALL TARGETS***
echo. 2>BuildAllTargetsSuccess.txt
endlocal
EXIT /B

:BUILD_all_error
echo **Build errors...
echo Please refer to build log for build errors and check the image bin folder(s).
endlocal
EXIT /B

:ERROR_MSG
echo **Build errors...
echo %1 file not found for %2. Please refer to build log for build errors.
goto :EOF
