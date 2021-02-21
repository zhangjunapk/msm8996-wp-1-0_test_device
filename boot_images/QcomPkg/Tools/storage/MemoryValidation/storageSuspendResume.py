#!/usr/bin/python
#===========================================================================

# REFERENCES

#  $Header: //components/rel/boot.xf/1.1.c1/QcomPkg/Tools/storage/MemoryValidation/storageSuspendResume.py#1 $
#  $DateTime: 2016/03/17 01:14:31 $ 
#  $Author: pwbldsvc $

# when          who     what, where, why 
# --------      ---     ------------------------------------------------------- 
# 2015-06-30    ah      Not fully working. Can't get output results yet. Otherwise works
# 2015-06-26    ah      First release

# Copyright (c) 2014-2015
# Qualcomm Technologies Incorporated.
# All Rights Reserved.
# Qualcomm Confidential and Proprietary
# ===========================================================================*/

## Some useful commands
## adb shell logcat -d -v time > MyLogcat.txt
## adb shell getprop | grep "boot"   <-- looking for [dev.bootcomplete]: [1] and [init.svc.bootanim]: [stopped]
## adb shell dmesg > dmesg.txt
## 

import threading
#from threading import Thread
import thread
import memutil      ## this is Qualcomm's memutil.py which has common functions
from memutil import *
import math,traceback
import re
import codecs
from types import *
import time
from time import sleep
from time import strftime, localtime

## Turn on screen
## adb shell input keyevent KEYCODE_POWER
## OR
## adb shell input keyevent 26

About = """
TEST DESCRIPTION:
This is a STRESS TEST that ensures the storage device can correctly read back 
a file after going through XO shutdown. The SD driver team uses first creates 
a test file of size 1MB (first_file). This file is then copied (written) to 
the file system (second_file). The SD driver team then uses the SuspendTest.apk 
to force the system into XO shutdown. After the device comes back from XO 
shutdown the second_file is copied (written) to the file system (third_file). 
Then the contents of third_file is compared to the contents of both first_file 
and second_file. If either "cmp" operations show that bytes differ, then the 
test has FAILED. This demonstrates that the storage device was unable to properly 
preserve the data through XO shutdown.

NOTE: In order for a full XO shutdown to happen USB must be disconnected during 
this test. Because of this the test runs most functionality through the shell 
script SuspendResumeWrite.sh. In order for this script to be launched it is 
added to the start up script /system/etc/init.qcom.post_boot.sh. This all happens 
automatically through storageSuspendResume.py and therefore it is important to 
MANUALLY follow this script along until it TELLS THE USER to UNPLUG USB.


USAGE:
python storageSuspendResume.py --test_duration_in_minutes=1440

"""

SHOWFAIL = 0
SHOWPASS = 1

DMesgRegEx = ["String/Regex 1 to look for","String/Regex 2 to look for"] ## Any messages here found in the log will be treated as errors
LogCatRegEx= ["String/Regex 1 to look for","String/Regex 2 to look for"] ## Any messages here found in the log will be treated as errors

memutil.GrepName    = "doualarmtest"
memutil.TestName    = "storageSuspendResume"
memutil.csv_name    = "%s.csv" % memutil.TestName
memutil.log_dmesg   = "dmesg_%s.txt" % memutil.TestName
memutil.logcatname  = "logcat_%s.txt" % memutil.TestName

memutil.search_paths= ["bobby\\temp"]

ArgumentOptions = ["test_duration_in_minutes=", "suspendtimeinms=", "resumetimeinms="]

suspendtimeinms = 8000 
resumetimeinms  = 8000 
iterations      = 9000000

test_duration_in_minutes= 1


def ParseSuspendResumeWriteLog(log_name):

    LineToLookFor = "SH: If after the arrow it is BLANK, then it was a pass -->"

    device_log("PARSING FILE: '%s'\n" % log_name)

    try:
        Temp = open(log_name, 'r')
    except Exception, x:
        PrintError()
        device_log("WARNING: could not open '%s'" % log_name)
        device_log("REASON: %s" % x)
        ExitAndShowLogName(1,SHOWFAIL)

    Line = Temp.readlines()
    Temp.close()

    ReturnValue = 1 ## means all is well
    for i in range(len(Line)):
        m = re.search(LineToLookFor, Line[i])
        if type(m) is not NoneType:
            if len(LineToLookFor) != len(Line[i].strip()):
                PrintError()
                device_log("These 2 lines below should match but they do not!!")
                device_log(LineToLookFor)
                device_log(Line[i].strip())
                ReturnValue = 0

    if ReturnValue == 1:
        device_log("Log looks good\n\n")

    return ReturnValue

def ParseOtherCommandLineOptions():
    global ArgumentOptions
    global test_duration_in_minutes, suspendtimeinms, resumetimeinms, iterations

    ArgumentOptions = sorted(ArgumentOptions)

    try:
        opts, args = getopt.getopt(sys.argv[1:], "", ArgumentOptions)
    except getopt.GetoptError, err:
        # print help information and exit:
        PrintBanner("ERROR")
        print str(err) # will print something like "option -a not recognized"
        print str(err) # will print something like "option -a not recognized"
        print str(err) # will print something like "option -a not recognized"
        PrintBanner("Run 'python %s' for examples and possible options" % sys.argv[0])
        ExitAndShowLogName(1)

    for o, a in opts:
        if o == "--suspendtimeinms":
            suspendtimeinms = int(a)
            device_log("suspendtimeinms set to %d" % suspendtimeinms)
        elif o == "--resumetimeinms":
            resumetimeinms = int(a)
            device_log("resumetimeinms set to %d" % resumetimeinms)
        elif o == "--test_duration_in_minutes":
            test_duration_in_minutes = int(a)
            device_log("test_duration_in_minutes set to %d" % test_duration_in_minutes)
        else:
            PrintBanner("ERROR")
            device_log("ERROR: '%s' is not a valid option" % o)
            device_log("use 'python %s' to see a list of possible options" % sys.argv[0])
            ExitAndShowLogName(1)


    EachRunTakesInSeconds           = (float(suspendtimeinms + resumetimeinms)*3.0  + 3000.0)/1000.0

    NumIterations                   = float(test_duration_in_minutes * 60) / EachRunTakesInSeconds 
    if NumIterations < 1.0:
        NumIterations = 1.0

    iterations = int(math.ceil(NumIterations))
    PrintBanner("Iterations calculated to be %i" % iterations)

    test_duration_in_minutes  = float(iterations * EachRunTakesInSeconds)/60.0
    PrintBanner("test_duration_in_minutes updated to %.2f minutes" % test_duration_in_minutes)

##    main main main -------------------------------------------------------------
##                    (_)      
##     _ __ ___   __ _ _ _ __  
##    | '_ ` _ \ / _` | | '_ \ 
##    | | | | | | (_| | | | | |
##    |_| |_| |_|\__,_|_|_| |_|
##                            
##    main main main -------------------------------------------------------------

ParseCommonCommandLineOptions(ArgumentOptions,About)

MyProcess       = None
RunningAsRoot   = False

ParseOtherCommandLineOptions()


WaitForDeviceWithPassFail()
memutil.log_name = "%s_%s_log.txt" % (memutil.ADB_DeviceID,memutil.TestName)    ## Make this unique to each test, user can also use --porttracename=
memutil.log_name = os.path.join(memutil.PathForOutputDatFiles, memutil.log_name)
ResetLog()  ## log is created here

memutil.csv_name    = "%s_%s.csv" % (memutil.ADB_DeviceID,memutil.TestName)
memutil.log_dmesg   = "%s_dmesg_%s.txt" % (memutil.ADB_DeviceID,memutil.TestName)
memutil.logcatname  = "%s_logcat_%s.txt" % (memutil.ADB_DeviceID,memutil.TestName)

memutil.csv_name    = os.path.join(memutil.PathForOutputDatFiles, memutil.csv_name)
memutil.log_dmesg   = os.path.join(memutil.PathForOutputDatFiles, memutil.log_dmesg)
memutil.logcatname  = os.path.join(memutil.PathForOutputDatFiles, memutil.logcatname)

memutil.FilesCreated.append(memutil.log_name)
##memutil.FilesCreated.append(memutil.csv_name)
memutil.FilesCreated.append(memutil.log_dmesg)
memutil.FilesCreated.append(memutil.logcatname)

device_log("storageSuspendResume.py version 2.0")

## Setup the target ------------------------------------------------------------------------------------
##	 _____      _                 _____                    _   
##	/  ___|    | |               |_   _|                  | |  
##	\ `--.  ___| |_ _   _ _ __     | | __ _ _ __ __ _  ___| |_ 
##	 `--. \/ _ \ __| | | | '_ \    | |/ _` | '__/ _` |/ _ \ __|
##	/\__/ /  __/ |_| |_| | |_) |   | | (_| | | | (_| |  __/ |_ 
##	\____/ \___|\__|\__,_| .__/    \_/\__,_|_|  \__, |\___|\__|
##	                     | |                     __/ |         
##	                     |_|                    |___/          
## Setup the target ------------------------------------------------------------------------------------

## Clear old LOGCAT
response = external_call('adb -s %s logcat -c' % memutil.ADB_DeviceID)

##RebootPhone()

RunADBasRoot()        ## must be root to do this step below

##memutil.ADB_DeviceID = None
WaitForDeviceWithPassFail()

SleepWithProgressIndicator(5)

t = time.localtime(time.time())
LinuxTimeString = ""
LinuxTimeString = "%.4d%.2d%.2d.%.2d%.2d%.2d" % (t.tm_year,t.tm_mon,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec)

sz = "%s started: Time is '%s' --- %s" % (os.path.basename(__file__),LinuxTimeString,strftime("%Y-%m-%d %H:%M:%S", t))
device_log(sz)
WriteDMESG(sz) ## puts message into dmesg
WriteLogcat(sz)## puts message into logcat

response = external_call('adb -s %s shell date -s %s' % (memutil.ADB_DeviceID,LinuxTimeString))

response = external_call('adb -s %s remount' % memutil.ADB_DeviceID)


## NOTE: This test is made tricky since doing "adb shell command &" DOES NOT WORK
##       However we must run the shell script this way since when we unplug the USB
##       this kills ADB which then kills the script. Therefore the only way to make
##       this work is to append my shell script to the startup script /system/etc/init.qcom.post_boot.sh

InitQCOMName = "%s_init.qcom.post_boot.sh" % (memutil.ADB_DeviceID)
StartupScriptLogName    = os.path.join(memutil.PathForOutputDatFiles, InitQCOMName)
response = external_call('adb -s %s pull /system/etc/init.qcom.post_boot.sh %s' % (memutil.ADB_DeviceID,StartupScriptLogName) )
memutil.FilesCreated.append(StartupScriptLogName)
StartupScriptLogNameContent = "EMPTY"

try:
    Temp = open(StartupScriptLogName, 'rb')
    StartupScriptLogNameContent = Temp.readlines()
    Temp.close()
except getopt.GetoptError, err:
    # print help information and exit:
    PrintBanner("ERROR")
    print str(err)
    ExitAndShowLogName(1)


if len(StartupScriptLogNameContent)==0:
    device_log("The file /system/etc/init.qcom.post_boot.sh appears to have 0 bytes?? This file should have lots of startup info in it")
    ExitAndShowLogName(1,SHOWFAIL)


## Now CLEAN 
for i in range(len(StartupScriptLogNameContent)):
    if "SuspendResumeWrite.sh" in StartupScriptLogNameContent[i]:
        device_log("NOTE: Removing old \"%s\" from /system/etc/init.qcom.post_boot.sh" % StartupScriptLogNameContent[i].strip())
        StartupScriptLogNameContent[i] = " "    ## remove this line

device_log("\n\n/system/etc/init.qcom.post_boot.sh in array StartupScriptLogNameContent should now be cleaned of SuspendResumeWrite.sh lines\n\n")
##LastLine    = StartupScriptLogNameContent[-1]
NewLastLine = "su /system/bin/sh /data/test/SuspendResumeWrite.sh";  ## more is needed

NewLastLine = NewLastLine + " %i %i %i &" % (iterations,suspendtimeinms,resumetimeinms)
device_log("%s" % NewLastLine)
## to be here means we need to append this line to the end of the file
device_log("NEED TO MODIFY /system/etc/init.qcom.post_boot.sh with '%s' saved at '%s'" % (NewLastLine,StartupScriptLogName))    ## nothing to do
Temp = open(StartupScriptLogName, 'wb') ## need 'wb' to prevent newline corruption
#for i in range(len(StartupScriptLogNameContent)):
#    Temp.write(StartupScriptLogNameContent[i].strip())

Temp.writelines(StartupScriptLogNameContent)

Temp.write('\n'+NewLastLine)
Temp.close()

## Create Original *without* the modified line
Temp = open(StartupScriptLogName, 'rb')
StartupScriptLogNameContent = Temp.readlines()
Temp.close()

## Get rid of last line
StartupScriptLogNameContent = StartupScriptLogNameContent[0:-1]

## Now write it back
CleanInitQCOMName = "%s_init.qcom.post_bootCLEAN.sh" % (memutil.ADB_DeviceID)
StartupScriptLogNameClean    = os.path.join(memutil.PathForOutputDatFiles, CleanInitQCOMName)
Temp = open(StartupScriptLogNameClean, 'wb')
Temp.writelines(StartupScriptLogNameContent)
Temp.close()
memutil.FilesCreated.append(StartupScriptLogNameClean)

device_log('\n\nNOTE: *IF* this script fails, you may need to run these commands\n\n')
device_log('\tadb -s %s root' % (memutil.ADB_DeviceID) )
device_log('\tadb -s %s remount' % (memutil.ADB_DeviceID) )
device_log('\tadb -s %s push %s /system/etc/init.qcom.post_boot.sh' % (memutil.ADB_DeviceID,StartupScriptLogNameClean) )
device_log('\nIn order to restore it with the original')

## To be here means I have something like
## c:\temp\init.qcom.post_boot.sh           <-- This has my NEW last line which is su /system/bin/sh /data/test/SuspendResumeWrite.sh &
## c:\temp\init.qcom.post_bootCLEAN.sh      <-- This is identical to above, but missing that line

## Now put my modified file back
response = external_call('adb -s %s push %s /system/etc/init.qcom.post_boot.sh' % (memutil.ADB_DeviceID,StartupScriptLogName) )

device_log("Let's look and see if SuspendResumeWrite.sh is in /system/etc/init.qcom.post_boot.sh, because it SHOULD BE")
response = external_call('adb -s %s shell "cat /system/etc/init.qcom.post_boot.sh | grep SuspendResumeWrite"' % (memutil.ADB_DeviceID) )
if len(response)==0:
    PrintError()
    device_log("I was unable to modify /system/etc/init.qcom.post_boot.sh. I need to add a call to SuspendResumeWrite.sh at the end of it")
    ExitAndShowLogName(1,SHOWFAIL)
else:
    device_log("WARNING: If you see a line such as \"su /system/bin/sh /data/test/SuspendResumeWrite.sh\" appear MORE THAN ONCE above")
    device_log("WARNING: Then your /system/etc/init.qcom.post_boot.sh is NOT clean and needs to be corrected.")
    device_log("You can possibly restore by running the commands below, OR, manually by removing all lines with SuspendResumeWrite.sh and rebooting")
    device_log("\tadb -s %s root" % memutil.ADB_DeviceID)
    device_log("\tadb -s %s remount" % memutil.ADB_DeviceID)
    device_log("\tadb -s %s push c:\\temp\\%s_init.qcom.post_bootCLEAN.sh /system/etc/init.qcom.post_boot.sh" % (memutil.ADB_DeviceID,memutil.ADB_DeviceID))
    device_log("Then REBOOT")
    SleepWithProgressIndicator(5)

if memutil.UserSpecified_systemis64bit==0:
    TestIfSystemIs64Bit()

## Make sure older version of app is gone
if len(memutil.GrepName)>0:
    CallKillApp(memutil.GrepName)

SetScreenTimeoutAndAirplaneMode(30)    ## this turns on screen, sets airplane mode and REBOOTS to changes take affect
TurnOnScreen()


## To be this far, we are running as ROOT


CanWeSwitchClocks() ## Sets memutil.CanSwitchClocks
if memutil.CanSwitchClocks and memutil.AllowClockSwitching:
    CopyFileToPhone("bimc_clock_fmax1804.sh")


response = external_call('adb -s %s shell mkdir /data/test' % (memutil.ADB_DeviceID) ) ## 
response = external_call('adb -s %s shell ls -l /data/test' % (memutil.ADB_DeviceID) ) ## 
response = external_call('adb -s %s shell rm /data/test/*' % (memutil.ADB_DeviceID) ) ## 
device_log("Should be empty now, let's see")
response = external_call('adb -s %s shell ls -l /data/test' % (memutil.ADB_DeviceID) ) ## 

CopyFileToPhone("SuspendResumeWrite.sh","/data/test/")
response = external_call('adb -s %s shell ls -l /data/test' % (memutil.ADB_DeviceID) ) ## 
response = external_call('adb -s %s shell chmod 777 /data/test/SuspendResumeWrite.sh' % (memutil.ADB_DeviceID) ) ## 

## AT this point the script is there and /data/test is clean

InstallAPK('SuspendTest.apk','com.android.doualarmtest')

response = external_call('adb -s %s shell ls /proc/sys/vm/drop_caches -l' % (memutil.ADB_DeviceID) ) ## 
response = external_call('adb -s %s shell \"echo 3 > /proc/sys/vm/drop_caches\"' % (memutil.ADB_DeviceID) ) ## drop caches


##    Actual Test happens here  -------------------------------------------------------------
##	 _____         _     _                                        _                   
##	|_   _|       | |   | |                                      | |                  
##	  | | ___  ___| |_  | |__   __ _ _ __  _ __   ___ _ __  ___  | |__   ___ _ __ ___ 
##	  | |/ _ \/ __| __| | '_ \ / _` | '_ \| '_ \ / _ \ '_ \/ __| | '_ \ / _ \ '__/ _ \
##	  | |  __/\__ \ |_  | | | | (_| | |_) | |_) |  __/ | | \__ \ | | | |  __/ | |  __/
##	  \_/\___||___/\__| |_| |_|\__,_| .__/| .__/ \___|_| |_|___/ |_| |_|\___|_|  \___|
##	                                | |   | |                                         
##	                                |_|   |_|                                         
##	
##    Actual Test happens here  -------------------------------------------------------------

sz = "Your target now has all the files and is setup to do %s (%s)" % (memutil.TestName,os.path.basename(__file__))
WriteDMESG(sz) ## puts message into dmesg
WriteLogcat(sz)## puts message into logcat

device_log(sz)
device_log(sz)
device_log(sz+"\n\n")

LengthOfTestInSeconds = int(test_duration_in_minutes * 60)


## Now to 

CheckEvery = 10 ## Every 10 seconds check int(float(LengthOfTestInSeconds)/10.0)

device_log("Rebooting device")  
RebootPhone()   ## <-- THIS IS WHAT STARTS THE TEST <-- THIS IS WHAT STARTS THE TEST <-- THIS IS WHAT STARTS THE TEST
RunADBasRoot()        ## must be root to do this step below
##memutil.ADB_DeviceID = None
WaitForDeviceWithPassFail()
response = external_call('adb -s %s remount' % memutil.ADB_DeviceID)

## Want to POLL here until I see 

NumAttempts = 500
i = 0
for i in range(NumAttempts):
    response = external_call('adb -s %s shell "ps | grep -i doualarmtest"' % (memutil.ADB_DeviceID) )
    if len(response)==0:
        device_log("SuspendTest.apk is *not* running yet (%d of %d)" % (i+1,NumAttempts))
        device_log("This is *normal*")
        device_log("It will be launched by /system/etc/init.qcom.post_boot.sh automatically, roughly 2 minutes after boot up")
        device_log("Will sleep 5 seconds, and then continue to poll for it. All is well!")
        SleepWithProgressIndicator(5)
    else:
        device_log("SuspendTest.apk is NOW RUNNING. ")
        device_log("SuspendTest.apk is NOW RUNNING. ")
        device_log("SuspendTest.apk is NOW RUNNING. ")
        break

if i>=NumAttempts:
    PrintError()
    device_log("SuspendTest.apk does not seem to be running. This script modified /system/etc/init.qcom.post_boot.sh")
    device_log("It added a line like \"su /system/bin/sh /data/test/SuspendResumeWrite.sh 1695 8000 8000 &\" to the end.")
    device_log("You can put back your original /system/etc/init.qcom.post_boot.sh by running the following commands")
    device_log("\tadb -s %s root" % memutil.ADB_DeviceID)
    device_log("\tadb -s %s remount" % memutil.ADB_DeviceID)
    device_log("\tadb -s %s push c:\\temp\\%s_init.qcom.post_bootCLEAN.sh /system/etc/init.qcom.post_boot.sh" % (memutil.ADB_DeviceID,memutil.ADB_DeviceID))
    ExitAndShowLogName(1,SHOWFAIL)

PrintRemoveUSB()




##SleepWithProgressIndicator(5)


start_time = time.time()

##device_log("Sleeping for %i seconds while test runs" % (LengthOfTestInSeconds))
while True:
##for i in range(0,LengthOfTestInSeconds,CheckEvery):
    SleepWithProgressIndicator(CheckEvery)

    elapsed = ReturnElapsedFrom(start_time) ## this is time in seconds

    if elapsed > float(LengthOfTestInSeconds):
        break

    Hours = int(elapsed / (60*60))
    Mins  = (elapsed - (Hours*60*60))
    Mins  = int( Mins/60)
    Secs  = int(elapsed - (Hours*60*60) - (Mins*60))

    SecondsLeft = (test_duration_in_minutes*60)-elapsed
    if(SecondsLeft<=0):
        break

    print "SecondsLeft=%d\n" % SecondsLeft

    device_log("You should see your phones screen TOGGLE *off* for %.2f seconds, and then *on* for %.2f seconds\n" % ((float(suspendtimeinms)/1000.0),float(resumetimeinms)/1000.0))
    device_log("Time since SuspendResume.apk started: %i HOURS %i MINUTES %i SECONDS (%.2f minutes total. %.2f mins left)" % (Hours,Mins,Secs,test_duration_in_minutes,test_duration_in_minutes-int(elapsed/60)))

    PrintUSBshouldBeUnplugged()

PlugInUSB()
raw_input('Press Enter when USB has been plugged back in')

SleepWithProgressIndicator(5)

WaitForDeviceWithPassFail()

LengthOfTestInSeconds = 4.0*LengthOfTestInSeconds   ## giving 4 times the length to find "DONE.txt"

TimesLookingForDONE = 0

start_time = time.time()
while True:
##for i in range(0,LengthOfTestInSeconds,CheckEvery):
    SleepWithProgressIndicator(CheckEvery)

    elapsed = ReturnElapsedFrom(start_time) ## this is time in seconds

    if elapsed > float(LengthOfTestInSeconds):
        break

    Hours = int(elapsed / (60*60))
    Mins  = (elapsed - (Hours*60*60))
    Mins  = int( Mins/60)
    Secs  = int(elapsed - (Hours*60*60) - (Mins*60))

    SecondsLeft = (test_duration_in_minutes*60)-elapsed
    if(SecondsLeft<=0):
        break

    print "SecondsLeft=%d\n" % SecondsLeft

    device_log("Looking for DONE.txt. Time %i HOURS %i MINUTES %i SECONDS (%d minutes total. %d mins left)" % (Hours,Mins,Secs,test_duration_in_minutes,test_duration_in_minutes-int(elapsed/60)))

    ##import pdb; pdb.set_trace()
    ##response = external_call('adb -s %s shell ls -l /data/test/DONE.txt' % memutil.ADB_DeviceID)
    ##response = external_call('adb -s %s shell rm /data/test/DONE.txt' % memutil.ADB_DeviceID)

    response = external_call('adb -s %s shell ls -l /data/test/DONE.txt' % memutil.ADB_DeviceID)
    if "No such file or directory" in response:
        TimesLookingForDONE += 1
        if TimesLookingForDONE > 10:
            PrintError()
            device_log("Can't find /data/test/DONE.txt. This indicates that SuspendResumeWrite.sh did *not* complete. Test has failed, see log")
            ExitAndShowLogName(1,SHOWFAIL)
            
        device_log("Can't find /data/test/DONE.txt. Attempt %i of 10" % TimesLookingForDONE)
        continue
    else:
        device_log("Found DONE.txt")
        break


response = external_call('adb -s %s shell ls -l /data/test/' % (memutil.ADB_DeviceID) )

PrintSuccess()
device_log("Your phone seems to still be alive. Let's double check by looking at the logs")
SleepWithProgressIndicator(6)





RunADBasRoot()        ## must be root to do this step below

##memutil.ADB_DeviceID = None
WaitForDeviceWithPassFail()

response = external_call('adb -s %s remount' % memutil.ADB_DeviceID)

response = external_call('adb -s %s shell ls -l /data/test/' % (memutil.ADB_DeviceID) )

response = external_call('adb -s %s shell logcat -d -v time > %s' % (memutil.ADB_DeviceID,memutil.logcatname) )
response = external_call('adb -s %s shell dmesg > %s' % (memutil.ADB_DeviceID,memutil.log_dmesg) )

GetPIDofRunningApp("sh")

## And now remove these
response = external_call('adb -s %s shell ls -l /data/test/' % (memutil.ADB_DeviceID) )

StorageSuspendResumeLogName = "%s_StorageSuspendResumeLog.txt" % (memutil.ADB_DeviceID)

ScriptLogName    = os.path.join(memutil.PathForOutputDatFiles, StorageSuspendResumeLogName)
response = external_call('adb -s %s pull /data/test/log.txt %s' % (memutil.ADB_DeviceID,ScriptLogName) )
memutil.FilesCreated.append(ScriptLogName)

## put back original
response = external_call('adb -s %s push %s /system/etc/init.qcom.post_boot.sh' % (memutil.ADB_DeviceID,StartupScriptLogNameClean) )


device_log("Let's look and see if SuspendResumeWrite.sh is in /system/etc/init.qcom.post_boot.sh, because it should *NOT* be")
response = external_call('adb -s %s shell "cat /system/etc/init.qcom.post_boot.sh | grep SuspendResumeWrite"' % (memutil.ADB_DeviceID) )

if len(response)>0:
    device_log("WARNING: Your /system/etc/init.qcom.post_boot.sh is NOT clean. There should be no mention of SuspendResumeWrite.sh in it")
    device_log("WARNING: Your /system/etc/init.qcom.post_boot.sh is NOT clean. There should be no mention of SuspendResumeWrite.sh in it")
    device_log("WARNING: Your /system/etc/init.qcom.post_boot.sh is NOT clean. There should be no mention of SuspendResumeWrite.sh in it")
    device_log("You can possibly restore by running the commands below, OR, manually by removing all lines with SuspendResumeWrite.sh and rebooting")
    device_log("\tadb -s %s root" % memutil.ADB_DeviceID)
    device_log("\tadb -s %s remount" % memutil.ADB_DeviceID)
    device_log("\tadb -s %s push c:\\temp\\%s_init.qcom.post_bootCLEAN.sh /system/etc/init.qcom.post_boot.sh" % (memutil.ADB_DeviceID,memutil.ADB_DeviceID))
    device_log("Then REBOOT")

SleepWithProgressIndicator(4)

Pass = 1    ## Assume we're good

Pass = ParseSuspendResumeWriteLog(ScriptLogName)

Pass = ParseDmesgLog(memutil.log_dmesg,DMesgRegEx)    ## will return 1 if there is a problem
if Pass==1:
    Pass = ParseLogcat(memutil.logcatname,LogCatRegEx)    ## will return 1 if there is a problem


if Pass==0:
    PrintFailed()
    ##device_log("\nERROR: Test failed")
    ExitAndShowLogName(1,SHOWFAIL)

else:
    sz = About + " \n\n"
    PrintPassed(About)
    device_log("Your phone (DDR) survived the Suspend Resume test for %.2f minutes\n\n" % test_duration_in_minutes)


ExitAndShowLogName(0,SHOWPASS,sz)








