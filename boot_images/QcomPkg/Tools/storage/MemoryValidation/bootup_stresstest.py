#!/usr/bin/python
#===========================================================================

# REFERENCES

#  $Header: //components/rel/boot.xf/1.1.c1/QcomPkg/Tools/storage/MemoryValidation/bootup_stresstest.py#1 $
#  $DateTime: 2016/03/17 01:14:31 $ 
#  $Author: pwbldsvc $

# when          who     what, where, why 
# --------      ---     ------------------------------------------------------- 
# 2015-06-01    ah      Removed searh paths that are not needed
# 2015-06-01    ah      Updated the usage
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
This test will reboot your device repeatedly. This test is stressing all systems of your device,
but primarily is the DDR (DRAM). This is because during boot up all clocks, masters and power rails
are being turned on which can lead to power dips to DDR that can lead to bit flips.

To reboot your device repeatedly for 1 hour use --test_duration_in_minutes=60

USAGE:
python bootup_stresstest.py --test_duration_in_minutes=1440

"""

DMesgRegEx = ["String/Regex 1 to look for","String/Regex 2 to look for"] ## Any messages here found in the log will be treated as errors


LogCatRegEx= ["String/Regex 1 to look for","String/Regex 2 to look for"] ## Any messages here found in the log will be treated as errors

memutil.TestName    = "bootup_stresstest"
memutil.csv_name    = "%s.csv" % memutil.TestName
memutil.log_dmesg   = "dmesg_%s.txt" % memutil.TestName
memutil.logcatname  = "logcat_%s.txt" % memutil.TestName

ArgumentOptions = ["test_duration_in_minutes=", ]
    
test_duration_in_minutes= 1

def ParseOtherCommandLineOptions():
    global ArgumentOptions,MinStep,MaxStep
    global golden_csv,MemorySizeinMB
    global test_duration_in_minutes, suspendtimeinms, resumetimeinms, iterations
    global TestStress,TestPerf

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
        if o == "--test_duration_in_minutes":
            test_duration_in_minutes = int(a)
            device_log("test_duration_in_minutes set to %d" % test_duration_in_minutes)
        else:
            PrintBanner("ERROR")
            device_log("ERROR: '%s' is not a valid option" % o)
            device_log("use 'python %s' to see a list of possible options" % sys.argv[0])
            ExitAndShowLogName(1)

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

device_log("bootup_stresstest.py version 2.0")

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

t = time.localtime(time.time())
LinuxTimeString = ""
LinuxTimeString = "%.4d%.2d%.2d.%.2d%.2d%.2d" % (t.tm_year,t.tm_mon,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec)
device_log("Time is '%s'" % LinuxTimeString)
response = external_call('adb -s %s shell date -s %s' % (memutil.ADB_DeviceID,LinuxTimeString))

## MUTE THE PHONE
##MutePhone()


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


start_time = time.time()

repeat_loop = 0
while True:
    RebootPhone()
    device_log("NumReboots so far: %i" % (repeat_loop+1))
    elapsed = ReturnElapsedFrom(start_time) ## this is time in seconds
    Hours = int(elapsed / (60*60))
    Mins  = (elapsed - (Hours*60*60))
    Mins  = int( Mins/60)
    Secs  = int(elapsed - (Hours*60*60) - (Mins*60))
    device_log("TIME SINCE %s TEST STARTED: %i HOURS %i MINUTES %i SECONDS - (%d minutes total. %d mins left)" % (memutil.TestName,Hours,Mins,Secs,test_duration_in_minutes,test_duration_in_minutes-int(elapsed/60)))
    SleepWithProgressIndicator(3)
    repeat_loop += 1
    device_log("test_duration_in_minutes=%d and elapsed=%d" % (test_duration_in_minutes*60,elapsed))
    if (test_duration_in_minutes*60)<elapsed:
        ##device_log()
        break

response = external_call('adb -s %s shell logcat -d -v time > %s' % (memutil.ADB_DeviceID,memutil.logcatname) )
response = external_call('adb -s %s shell dmesg > %s' % (memutil.ADB_DeviceID,memutil.log_dmesg) )


## Parsing happens here ----------------------------------------------------------------------------
##	______                     _                 
##	| ___ \                   | |                
##	| |_/ /_ _ _ __ ___  ___  | | ___   __ _ ___ 
##	|  __/ _` | '__/ __|/ _ \ | |/ _ \ / _` / __|
##	| | | (_| | |  \__ \  __/ | | (_) | (_| \__ \
##	\_|  \__,_|_|  |___/\___| |_|\___/ \__, |___/
##	                                    __/ |    
##	                                   |___/     
## Parsing happens here ----------------------------------------------------------------------------
SleepWithProgressIndicator(4)

Pass = 1    ## Assume we're good

Pass = ParseDmesgLog(memutil.log_dmesg,DMesgRegEx)    ## will return 1 if there is a problem
if Pass==1:
    Pass = ParseLogcat(memutil.logcatname,LogCatRegEx)    ## will return 1 if there is a problem

# Compare results with golden to get pass fail
#   _____                                           _____       _     _            
#  /  __ \                                         |  __ \     | |   | |           
#  | /  \/ ___  _ __ ___  _ __   __ _ _ __ ___     | |  \/ ___ | | __| | ___ _ __  
#  | |    / _ \| '_ ` _ \| '_ \ / _` | '__/ _ \    | | __ / _ \| |/ _` |/ _ \ '_ \ 
#  | \__/\ (_) | | | | | | |_) | (_| | | |  __/    | |_\ \ (_) | | (_| |  __/ | | |
#   \____/\___/|_| |_| |_| .__/ \__,_|_|  \___|     \____/\___/|_|\__,_|\___|_| |_|
#                        | |                                                       
#                        |_|                  
#                                                             
# Compare results with golden to get pass fail

if Pass==0:
    PrintFailed()
    ##device_log("\nERROR: Test failed")
    ExitAndShowLogName(1)

else:
    PrintPassed(About)
    PrintBanner("Phone successfully rebooted %d times over the course of %d minutes" % (repeat_loop,test_duration_in_minutes))

ExitAndShowLogName(0)


