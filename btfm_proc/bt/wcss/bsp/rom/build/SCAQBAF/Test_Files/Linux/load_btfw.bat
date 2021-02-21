@echo off

adb wait-for-devices
adb root
adb wait-for-devices
adb remount 

echo ********************Loading BT Patches************************
IF EXIST rampatch_tlv_3.2.tlv (
    echo Loading ROME 3.2 BT Patches....
    
    echo Loading rampatch_tlv_3.2.tlv ....
    adb push rampatch_tlv_3.2.tlv /system/etc/firmware/ 
    
    echo Loading nvm_tlv_3.2.tlv ....
    adb push nvm_tlv_3.2.bin /system/etc/firmware/ 

    adb shell chmod 644 /system/etc/firmware/rampatch_tlv_3.2.tlv 
    adb shell chmod 644 /system/etc/firmware/nvm_tlv_3.2.bin 
    )
	
IF EXIST rampatch_tlv_3.0.tlv (
    echo Loading ROME 3.0 BT Patches....
    
    echo Loading rampatch_tlv_3.0.tlv ....
    adb push rampatch_tlv_3.0.tlv /system/etc/firmware/ 
    
    echo Loading nvm_tlv_3.0.tlv ....
    adb push nvm_tlv_3.0.bin /system/etc/firmware/ 

    adb shell chmod 644 /system/etc/firmware/rampatch_tlv_3.0.tlv 
    adb shell chmod 644 /system/etc/firmware/nvm_tlv_3.0.bin 
    )  

IF EXIST rampatch_tlv_2.1.tlv (
    echo Loading ROME 2.1 BT Patches....
    
    echo Loading rampatch_tlv_2.1.tlv ....
    adb push rampatch_tlv_2.1.tlv /system/etc/firmware/ 
    
    echo Loading nvm_tlv_2.1.tlv ....
    adb push nvm_tlv_2.1.bin /system/etc/firmware/ 

    adb shell chmod 644 /system/etc/firmware/rampatch_tlv_2.1.tlv 
    adb shell chmod 644 /system/etc/firmware/nvm_tlv_2.1.bin 
    )

echo ********************Loaded BT Patches************************
adb shell sync 
adb reboot

pause
