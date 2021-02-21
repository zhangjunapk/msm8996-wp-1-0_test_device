#!/usr/bin/python
#===========================================================================

#  Fundamentally runs "adb shell /data/ddrBenchmark -min=0 -max=16 -s=64m -pst"

# REFERENCES

#  $Header: //components/rel/boot.xf/1.1.c1/QcomPkg/Tools/storage/MemoryValidation/ddrSuspendResume.py#1 $
#  $DateTime: 2016/03/17 01:14:31 $ 
#  $Author: pwbldsvc $

# when          who     what, where, why 
# --------      ---     ------------------------------------------------------- 
# 2015-06-30    ah      Minor tweaks
# 2015-06-26    ah      Updates, added remove USB
# 2015-06-01    ah      First release - This one works
# 2015-05-27    ah      Broken "skeleton script"

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
This test uses the DDR teams SuspendResume.APK. This APK puts the phone into a deep sleep
state also known as XO shutdown. This test ensures that DDR retains data when entering 
and exiting low power states.

It is recommended that this test is run for 24 hours. Test test passes if it is still running after 24 hours

USAGE:
python ddrSuspendResume.py --test_duration_in_minutes=1440

"""

SHOWFAIL = 0
SHOWPASS = 1

DMesgRegEx = ["String/Regex 1 to look for","String/Regex 2 to look for"] ## Any messages here found in the log will be treated as errors
LogCatRegEx= ["String/Regex 1 to look for","String/Regex 2 to look for"] ## Any messages here found in the log will be treated as errors

memutil.GrepName    = "doualarmtest"
memutil.TestName    = "ddrSuspendResume"

memutil.search_paths= ["SupportFiles\\suspend_resume\\suspend_resume"]

ArgumentOptions = ["test_duration_in_minutes=", "suspendtimeinms=", "resumetimeinms="]

suspendtimeinms = 8000 
resumetimeinms  = 8000 
iterations      = 9000000

test_duration_in_minutes= 1

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

    test_duration_in_minutes_in_ms = test_duration_in_minutes * 60 * 1000
    NumIterations = float(test_duration_in_minutes_in_ms) / float(suspendtimeinms + resumetimeinms)
    iterations = int(math.ceil(NumIterations))
    device_log("iterations calculated to be %i " % iterations)


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

device_log("ddrSuspendResume.py version 2.0")

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

if memutil.RebootBeforeScriptBegins:
    RebootPhone()

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

TestResponse = external_call('adb -s %s shell am start -n com.android.doualarmtest/.DOUAlarmTest -e suspendtime %i -e resumetime %i -e iterations %i' % ( memutil.ADB_DeviceID,suspendtimeinms,resumetimeinms,iterations))

LengthOfTestInSeconds = test_duration_in_minutes*60+10
##CheckEvery = LengthOfTestInSeconds/10
CheckEvery = 10

start_time = time.time()

PrintRemoveUSB()
##raw_input('Press Enter when USB has been removed') - This is now the same as storageSuspendResume.py

##device_log("Sleeping for %i seconds while test runs" % (LengthOfTestInSeconds))

for i in range(0,LengthOfTestInSeconds,CheckEvery):
    SleepWithProgressIndicator(CheckEvery)

    elapsed = ReturnElapsedFrom(start_time) ## this is time in seconds
    Hours = int(elapsed / (60*60))
    Mins  = (elapsed - (Hours*60*60))
    Mins  = int( Mins/60)
    Secs  = int(elapsed - (Hours*60*60) - (Mins*60))

    SecondsLeft = (test_duration_in_minutes*60)-elapsed
    if(SecondsLeft<=0):
        break

    print "SecondsLeft=%d\n" % SecondsLeft

#    if GetPIDofRunningApp(memutil.GrepName)==0:
#        ## to be here means no app was returned
#        PrintBanner("ERROR")
#        device_log("ERROR: App is not running, test has failed!!")
#        ExitAndShowLogName(1,SHOWFAIL)
#    else:
#        PrintAllIsWell()
#        device_log("You should see your phones screen TOGGLE *off* for %.2f seconds, and then *on* for %.2f seconds\n" % ((float(suspendtimeinms)/1000.0),float(resumetimeinms)/1000.0))
#        device_log("Time since SuspendResume.apk started: %i HOURS %i MINUTES %i SECONDS (%d minutes total. %d mins left)" % (Hours,Mins,Secs,test_duration_in_minutes,test_duration_in_minutes-int(elapsed/60)))
    device_log("You should see your phones screen TOGGLE *off* for %.2f seconds, and then *on* for %.2f seconds\n" % ((float(suspendtimeinms)/1000.0),float(resumetimeinms)/1000.0))
    device_log("Time since SuspendResume.apk started: %i HOURS %i MINUTES %i SECONDS (%d minutes total. %d mins left)" % (Hours,Mins,Secs,test_duration_in_minutes,test_duration_in_minutes-int(elapsed/60)))
    PrintUSBshouldBeUnplugged()

PlugInUSB()
raw_input('Press Enter when USB has been plugged back in')

SleepWithProgressIndicator(5)

WaitForDeviceWithPassFail()

## So to be here means we're done
device_log("\n\n\n")
PrintSuccess()
device_log("Your phone seems to still be alive. Let's double check by looking at the logs")
SleepWithProgressIndicator(6)

if GetPIDofRunningApp(memutil.GrepName)==0:
    ## to be here means no app was returned
    PrintBanner("ERROR")
    device_log("ERROR: App is not running, test has failed!!")
    ExitAndShowLogName(1,SHOWFAIL)

if len(memutil.GrepName)>0:
    CallKillApp(memutil.GrepName)
    CallKillApp(memutil.GrepName)  ## Calling twice to make sure it's dead, will return instantly if already gone

response = external_call('adb -s %s shell logcat -d -v time > %s' % (memutil.ADB_DeviceID,memutil.logcatname) )
response = external_call('adb -s %s shell dmesg > %s' % (memutil.ADB_DeviceID,memutil.log_dmesg) )

SleepWithProgressIndicator(4)

Pass = 1    ## Assume we're good

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
    device_log("Your phone (DDR) survived the Suspend Resume test for %i minutes\n\n" % test_duration_in_minutes)


ExitAndShowLogName(0,SHOWPASS,sz)








