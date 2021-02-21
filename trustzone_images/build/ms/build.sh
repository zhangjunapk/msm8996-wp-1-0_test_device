#!/bin/bash
#===============================================================================
#
# CBSP Buils system
#
# General Description
#    build shell script file.
#
# Copyright (c) 2009-2015 by QUALCOMM Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
# $Header: //components/rel/build.tz/1.0.6/ms/build.sh#1 $
# $DateTime: 2016/12/02 01:48:48 $
# $Author: pwbldsvc $
# $Change: 11897026 $
#                      EDIT HISTORY FOR FILE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------
#
#===============================================================================
#===============================================================================
# Set up default paths
# Need to get working on Linux
#===============================================================================


build_dir=`dirname $0`
cd $build_dir
#export OKL4_SDK=../../core/kernel/sdk
export BUILD_ROOT=../..
export CORE_BSP_ROOT=$BUILD_ROOT/core/bsp
export TOOLS_SCONS_ROOT=$BUILD_ROOT/tools/build/scons

if [ -e setenv.sh ]; then
source $BUILD_ROOT/build/ms/setenv.sh
fi

#===============================================================================
# Set target enviroment
#===============================================================================

chipset="$1"
mapreport="$2"

if [ "$chipset" = "CHIPSET=msm8996" ]; then
  export BUILD_ID=IADAANAA
  export BUILD_VER=40000000
  export BUILDSPEC=KLOCWORK

  export BUILD_ASIC=8996
  export MSM_ID=8996
  export HAL_PLATFORM=8996
  export TARGET_FAMILY=honeybadger
  export CHIPSET=msm8996
  export IMAGES=""

elif [ "$chipset" = "CHIPSET=msm8952" ]; then
  export BUILD_ID=NAKAANAA
  export BUILD_VER=40000000
  export BUILDSPEC=KLOCWORK

  export BUILD_ASIC=8952
  export MSM_ID=8952
  export HAL_PLATFORM=8952
  export TARGET_FAMILY=bear
  export CHIPSET=msm8952
  export IMAGES=""

elif [ "$chipset" = "CHIPSET=msm8956" ]; then
  export BUILD_ID=MAYAANAA
  export BUILD_VER=40000000
  export BUILDSPEC=KLOCWORK

  export BUILD_ASIC=8956
  export MSM_ID=8956
  export HAL_PLATFORM=8956
  export TARGET_FAMILY=bear
  export CHIPSET=msm8956
  export IMAGES=""
elif [ "$chipset" = "CHIPSET=msm8953" ]; then
  export BUILD_ID=SANAANAA
  export BUILD_VER=40000000
  export BUILDSPEC=KLOCWORK

  export BUILD_ASIC=8953
  export MSM_ID=8953
  export HAL_PLATFORM=8953
  export TARGET_FAMILY=bear
  export CHIPSET=msm8953
  export IMAGES=""
elif [ "$chipset" = "CHIPSET=msm8937" ]; then
  export BUILD_ID=ZALAANAA
  export BUILD_VER=40000000
  export BUILDSPEC=KLOCWORK

  export BUILD_ASIC=8937
  export MSM_ID=8937
  export HAL_PLATFORM=8937
  export TARGET_FAMILY=bear
  export CHIPSET=msm8937
  export IMAGES=""
elif [ "$chipset" = "CHIPSET=msm8998" ]; then
  export BUILD_ID=RAGAANAA
  export BUILD_VER=40000000
  export BUILDSPEC=KLOCWORK

  export BUILD_ASIC=8998
  export MSM_ID=8998
  export HAL_PLATFORM=8998
  export TARGET_FAMILY=honeybadger
  export CHIPSET=msm8998
  export IMAGES=""
elif [ "$chipset" = "CHIPSET=msm8998virtio" ]; then
  export BUILD_ID=RAGAANVA
  export BUILD_VER=40000000
  export BUILDSPEC=KLOCWORK

  export BUILD_ASIC=8998
  export MSM_ID=8998
  export HAL_PLATFORM=VIRTIO
  export TARGET_FAMILY=honeybadger
  export CHIPSET=msm8998
  export IMAGES=""
elif [ "$chipset" = "CHIPSET=msm8998rumi" ]; then
  export BUILD_ID=RAGAANRA
  export BUILD_VER=40000000
  export BUILDSPEC=KLOCWORK

  export BUILD_ASIC=8998
  export MSM_ID=8998
  export HAL_PLATFORM=RUMI
  export TARGET_FAMILY=honeybadger
  export CHIPSET=msm8998
  export IMAGES=""
elif [ "$chipset" = "CHIPSET=mdm9645" ]; then
  export BUILD_ID=TAFFANBA
  export BUILD_VER=40000000
  export BUILDSPEC=KLOCWORK

  export BUILD_ASIC=9645
  export MSM_ID=9645
  export HAL_PLATFORM=9645
  export TARGET_FAMILY=badger
  export CHIPSET=mdm9645
  export IMAGES=""
elif [ "$chipset" = "CHIPSET=stubs" ]; then
  export BUILD_ID=CHIPSTUBS
  export BUILD_VER=40000000
  export BUILDSPEC=KLOCWORK

  export BUILD_ASIC=0000
  export MSM_ID=0000
  export HAL_PLATFORM=0000
  export TARGET_FAMILY=none
  export CHIPSET=msm0000
  export IMAGES=""
else
  echo "Please enter a valid chipset"
fi

shift

enable_mapreport=0
if [ "$mapreport" = "MAPREPORT=1" ]; then
  enable_mapreport=1
  shift
elif [ "$mapreport" = "MAPREPORT=0" ]; then
  enable_mapreport=0
  shift
fi


export BUILD_CMD="BUILD_ID=$BUILD_ID BUILD_VER=$BUILD_VER MSM_ID=$MSM_ID HAL_PLATFORM=$HAL_PLATFORM TARGET_FAMILY=$TARGET_FAMILY BUILD_ASIC=$BUILD_ASIC CHIPSET=$CHIPSET $IMAGES $*"
$TOOLS_SCONS_ROOT/build/rename-log.sh
$TOOLS_SCONS_ROOT/build/build.sh -f target.scons $BUILD_CMD

if [[ $enable_mapreport -eq 1 ]]; then
  if [[ $* == *"tz"* ]]; then
    python $TOOLS_SCONS_ROOT/linker_reporter/report_generator.py $BUILD_ROOT/core/securemsm/trustzone
    python $TOOLS_SCONS_ROOT/linker_reporter/report_generator.py $BUILD_ROOT/core/bsp/qsee
    python $TOOLS_SCONS_ROOT/linker_reporter/report_generator.py $BUILD_ROOT/core/bsp/monitor
    python $TOOLS_SCONS_ROOT/linker_reporter/report_generator.py $BUILD_ROOT/core/bsp/devcfg
  fi

  if [[ $* == *"hyp"* ]]; then
    python $TOOLS_SCONS_ROOT/linker_reporter/report_generator.py $BUILD_ROOT/core/bsp/hypervisor
  fi

  if [[ $* == *"sampleapp"* ]] || [[ $* == *"commonlib"* ]] || [[ $* ==  *"gpsample"* ]] || [[ $* ==  *"gptest"* ]] || [[ $* == *"ttacapi1"* ]] || [[ $* == *"ttacapi2"* ]] || [[  $* == *"ttacapi3"* ]] || [[ $* == *"ttacapi4"* ]] || [[ $* == *"ttacapi5"*  ]] || [[ $* == *"ttacrp1"* ]] || [[ $* == *"ttads1"* ]] || [[ $* ==  *"ttatime1"* ]] || [[ $* == *"ttatcf1"* ]] || [[ $* == *"ttatcf2"* ]] || [[ $* == *"ttatcf3"* ]] || [[ $* == *"ttatcf4"* ]] || [[ $* == *"ttatcf5"* ]] || [[ $* == *"isdbtmm"* ]] || [[ $* == *"uefisecapp"* ]] || [[ $* == *"uefi_sec"* ]] || [[ $* == *"winsecapp"* ]] || [[ $* == *"winsecap"* ]] || [[ $* == *"playready"* ]] || [[ $* == *"widevine"* ]] || [[ $* == *"fingerprint"* ]] || [[ $* == *"fidocrypto"* ]] || [[ $* == *"chamomile"* ]] || [[ $* == *"sampleauth"* ]] || [[ $* == *"sampleextauth"* ]] || [[ $* == *"hdcp1"* ]] || [[ $* == *"securemm"* ]] || [[ $* == *"secure_ui_sample"* ]] || [[ $* == *"secureindicator"* ]] || [[ $* == *"mdtp"* ]] || [[ $* == *"teetest"* ]] || [[ $* == *"cppf"* ]] || [[ $* == *"secotacl"* ]]|| [[ $* == *"iris"* ]] ; then
    python $TOOLS_SCONS_ROOT/linker_reporter/report_generator.py $BUILD_ROOT/core/bsp/trustzone/qsapps
  fi
fi
