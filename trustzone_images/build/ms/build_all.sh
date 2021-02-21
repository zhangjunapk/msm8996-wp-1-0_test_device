#!/bin/bash

cd `dirname $0`
rm -rf ./bin/

mapreport="$1"

enable_mapreport=0
if [ "$mapreport" = "MAPREPORT=1" ]; then
  enable_mapreport=1
  shift
elif [ "$mapreport" = "MAPREPORT=0" ]; then
  enable_mapreport=0
  shift
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport tz 
if [ ! -f ./bin/IADAANAA/tz.mbn ]; then
	echo "Error: tz.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport hyp
if [ ! -f ./bin/IADAANAA/hyp.mbn ]; then
	echo "Error: hyp.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport devcfg
if [ ! -f ./bin/IADAANAA/devcfg.mbn ]; then
	echo "Error: devcfg.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport devcfg_noac
if [ ! -f ./bin/IADAANAA/devcfg_noac.mbn ]; then
	echo "Error: devcfg_noac.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport tz_with_test
if [ ! -f ./bin/IADAANAA/tz_with_test.mbn ]; then
	echo "Error: tz_with_test.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport tztestexec
if [ ! -f ./bin/IADAANAA/tztestexec.mbn ]; then
	echo "Error: tztestexec.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport tzbsptest -j 1
if [ ! -f ./bin/IADAANAA/tzbsptest.mbn ]; then
	echo "Error: tzbsptest.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport commonlib USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/cmnlib.mbn ]; then
	echo "Error: cmnlib.mbn not found!"
	exit
fi
if [ ! -f ./bin/IADAANAA/cmnlib64.mbn ]; then
	echo "Error: cmnlib64.mbn not found!"
	exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport gpsample USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/gpsample.mbn ]; then
  echo "Error: gpsample.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport gptest USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/gptest.mbn ]; then
	echo "Error: gptest.mbn not found!"
	exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport ttacapi1 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/ttacapi1.mbn ]; then
	echo "Error: ttacapi1.mbn not found!"
	exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport ttacapi2 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/ttacapi2.mbn ]; then
  echo "Error: ttacapi2.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport ttacapi3 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/ttacapi3.mbn ]; then
  echo "Error: ttacapi3.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport ttacapi4 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/ttacapi4.mbn ]; then
  echo "Error: ttacapi4.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport ttacapi5 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/ttacapi5.mbn ]; then
  echo "Error: ttacapi5.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport ttacrp1 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/ttacrp1.mbn ]; then
  echo "Error: ttacrp1.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport ttads1 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/ttads1.mbn ]; then
  echo "Error: ttads1.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport ttatime1 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/ttatime1.mbn ]; then
  echo "Error: ttatime1.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport ttatcf1 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/ttatcf1.mbn ]; then
  echo "Error: ttatcf1.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport ttatcf2 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/ttatcf2.mbn ]; then
  echo "Error: ttatcf2.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport ttatcf3 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/ttatcf3.mbn ]; then
  echo "Error: ttatcf3.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport ttatcf4 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/ttatcf4.mbn ]; then
  echo "Error: ttatcf4.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport ttatcf5 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/ttatcf5.mbn ]; then
  echo "Error: ttatcf5.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport sampleapp USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/smplap32.mbn ]; then
	echo "Error: smplap32.mbn not found!"
	exit
fi
if [ ! -f ./bin/IADAANAA/smplap64.mbn ]; then
	echo "Error: smplap64.mbn not found!"
	exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport assurancetest USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/assurancetest.mbn ]; then
	echo "Error: assurancetest.mbn not found!"
	exit
fi
if [ ! -f ./bin/IADAANAA/assurancetest64.mbn ]; then
	echo "Error: assurancetest64.mbn not found!"
	exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport fingerprint USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/fingerprint.mbn ]; then
	echo "Error: fingerprint.mbn not found!"
	exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport voiceprint USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/voiceprint.mbn ]; then
	echo "Error: voiceprint.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport smplserv  USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/smplserv.mbn ]; then
  echo "Error: smplserv.mbn not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport smplcert  USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/smplcert.mbn ]; then
  echo "Error: smplcert not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport isdbtmm USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/isdbtmm.mbn ]; then
  echo "Error: isdbtmm not found!"
  exit
fi

sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport uefisecapp USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/uefi_sec.mbn ]; then
	echo "Error: uefi_sec.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport winsecapp USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/winsecap.mbn ]; then
	echo "Error: winsecap.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport hdcp2p2 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/hdcp2p2.mbn ]; then
	echo "Error: hdcp2p2.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport playready USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/playread.mbn ]; then
	echo "Error: playread.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport pr_3_0 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/pr_3_0.mbn ]; then
	echo "Error: pr_3_0.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport widevine USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/widevine.mbn ]; then
	echo "Error: widevine.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport fidocrypto USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/fidocrypto.mbn ]; then
	echo "Error: fidocrypto.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport fidocfg USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/fidocfg.mbn ]; then
	echo "Error: fidocfg.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport fidosui USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/fidosui.mbn ]; then
	echo "Error: fidosui.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport chamomile USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/chamomile.mbn ]; then
	echo "Error: chamomile.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport sampleauth USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/sampleauth.mbn ]; then
	echo "Error: sampleauth.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport sampleextauth USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/sampleextauth.mbn ]; then
	echo "Error: sampleextauth.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport lksecapp USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/lksecapp.mbn ]; then
	echo "Error: lksecapp.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport keymaster USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/keymaster.mbn ]; then
	echo "Error: keymaster.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport macchiato_sample USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/macchiato_sample.mbn ]; then
	echo "Error: macchiato_sample.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport hdcp1 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/hdcp1.mbn ]; then
	echo "Error: hdcp1.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport securemm USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/securemm.mbn ]; then
	echo "Error: securemm.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport secure_ui_sample USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/secure_ui_sample.mbn ]; then
	echo "Error: secure_ui_sample.mbn not found!"
	exit
fi
if [ ! -f ./bin/IADAANAA/secure_ui_sample64.mbn ]; then
	echo "Error: secure_ui_sample64.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport secureindicator USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/secureindicator.mbn ]; then
	echo "Error: secureindicator.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport qmpsecap USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/qmpsecap.mbn ]; then
	echo "Error: qmpsecap.mbn not found!"
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport qmpsecapp USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/qmpsecap.mbn ]; then
	echo "Error: qmpsecap.mbn not found!"
fi



sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport mdtp USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/mdtp.mbn ]; then
	echo "Error: mdtp.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport dhsecapp USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/dhsecapp.mbn ]; then
	echo "Error: dhsecapp.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport apttestapp USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/apttestapp.mbn ]; then
	echo "Error: apttestapp.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport apttestapp64 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/apttestapp64.mbn ]; then
	echo "Error: apttestapp64.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport teetest USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/teetest.mbn ]; then
	echo "Error: teetest.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport aptcryptotestapp USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/aptcryptotestapp.mbn ]; then
	echo "Error: aptcryptotestapp.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport aptcryptotestapp64 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/aptcryptotestapp64.mbn ]; then
	echo "Error: aptcryptotestapp64.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport dxhdcp2 USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/dxhdcp2.mbn ]; then
	echo "Error: dxhdcp2.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport dxhdcp2dbg USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/dxhdcp2dbg.mbn ]; then
	echo "Error: dxhdcp2dbg.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport cppf USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/cppf.mbn ]; then
	echo "Error: cppf.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport secotacl USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/secotacl.mbn ]; then
	echo "Error: secotacl.mbn not found!"
	exit
fi
sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport qpay USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/qpay.mbn ]; then
	echo "Error: qpay.mbn not found!"
	exit
fi
if [ ! -f ./bin/IADAANAA/qpay64.mbn ]; then
	echo "Error: qpay64.mbn not found!"
	exit
fi


sh build.sh CHIPSET=msm8996 MAPREPORT=$enable_mapreport iris USES_FLAGS=USES_NO_CP
if [ ! -f ./bin/IADAANAA/iris.mbn ]; then
	echo "Error: iris.mbn not found!"
	exit
fi
