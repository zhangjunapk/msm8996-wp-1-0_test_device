#!/usr/bin/python
#===========================================================================

# REFERENCES

#  $Header: //components/rel/boot.xf/1.1.c1/QcomPkg/Tools/storage/MemoryValidation/ddrMemtester.py#1 $
#  $DateTime: 2016/03/17 01:14:31 $ 
#  $Author: pwbldsvc $

# when          who     what, where, why 
# --------      ---     ------------------------------------------------------- 
# 2015-06-30    ah      tweaks and bug fixes
# 2015-06-26    ah      Updates, added clock switching
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
This test uses the DDR teams Memtester tool. This is a DDR testing tool. This is testing specific 
patterns to data address and command lines to see if anything is stuck high or low. Run this stress 
test for 24 hours as process (slow, nominal, fast) voltage and temperature variations will impact.

Ensure that --memory_size_in_mb=2 or bigger in order to miss the cache

USAGE:
python ddrMemtester.py --memory_size_in_mb=2 --test_duration_in_minutes=1440

"""

SHOWFAIL = 0
SHOWPASS = 1

DMesgRegEx = ["String/Regex 1 to look for","String/Regex 2 to look for"] ## Any messages here found in the log will be treated as errors


LogCatRegEx= ["String/Regex 1 to look for","String/Regex 2 to look for"] ## Any messages here found in the log will be treated as errors

memutil.GreName    = ""
memutil.TestName    = "ddrMemtester"
memutil.csv_name    = "%s.csv" % memutil.TestName
memutil.log_dmesg   = "dmesg_%s.txt" % memutil.TestName
memutil.logcatname  = "logcat_%s.txt" % memutil.TestName

memutil.search_paths= ["SupportFiles\\QBlizzard\\standard_stress"]

ArgumentOptions = ["test_duration_in_minutes=","memory_size_in_mb="]
    
AverageWRMBps = 0.0
AverageRDMBps = 0.0

test_duration_in_minutes= 1
MemorySizeInMB=2

def LaunchMemtester():
    device_log("Launching Memtester thread")
    device_log("Launching Memtester thread")
    device_log("Launching Memtester thread")


    start_time = time.time()

    szCommand = 'adb -s %s shell "/data/%s %dM %d > /data/memtesterResult.txt"' % (memutil.ADB_DeviceID,MemtesterFileName,MemorySizeInMB,NumIterations)
    response = external_call(szCommand)


def ParseOtherCommandLineOptions():
    global test_duration_in_minutes,ArgumentOptions
    global MemorySizeInMB

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
        elif o == "--memory_size_in_mb":
            MemorySizeInMB = int(a)
            device_log("memory_size_in_mb set to %d" % MemorySizeInMB)
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

device_log("ddrMemtester.py version 2.0")

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

t = time.localtime(time.time())
LinuxTimeString = ""
LinuxTimeString = "%.4d%.2d%.2d.%.2d%.2d%.2d" % (t.tm_year,t.tm_mon,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec)
sz = "%s started: Time is '%s' --- %s" % (os.path.basename(__file__),LinuxTimeString,strftime("%Y-%m-%d %H:%M:%S", t))
device_log(sz)
WriteDMESG(sz) ## puts message into dmesg
WriteLogcat(sz)## puts message into logcat

response = external_call('adb -s %s shell "date -s %s"' % (memutil.ADB_DeviceID,LinuxTimeString))

response = external_call('adb -s %s remount' % memutil.ADB_DeviceID)


## Make sure older version of app is gone
if len(memutil.GreName)>0:
    CallKillApp(memutil.GreName)

SetScreenTimeoutAndAirplaneMode(30)    ## this turns on screen, sets airplane mode and REBOOTS to changes take affect
TurnOnScreen()

MemtesterFileName = 'memtester'

CallKillApp(MemtesterFileName)

CopyFileToPhone(MemtesterFileName)

response = external_call('adb -s %s shell "chmod 777 /data/%s"' % (memutil.ADB_DeviceID,MemtesterFileName) ) ## change permission


response = external_call('adb -s %s shell ls /proc/sys/vm/drop_caches -l' % (memutil.ADB_DeviceID) ) ## 
response = external_call('adb -s %s shell sync"' % (memutil.ADB_DeviceID) ) ## sync
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

NumIterations = 5
device_log("Need to get a baseline of how long memtester takes on your system, testing for %d iterations" % NumIterations)


szCommand = 'adb -s %s shell "/data/%s  %dM %d "' % (memutil.ADB_DeviceID,MemtesterFileName,MemorySizeInMB,NumIterations)
start_time = time.time()
response = external_call(szCommand)

if len(response)==0:
    PrintError()
    device_log("There was no response from memtester")
    ExitAndShowLogName(1)

elapsed = ReturnElapsedFrom(start_time) ## this is time in seconds
TimePerRun = (elapsed/float(NumIterations))*.9  ## shrinking by 10% since actual runs seem faster in practice

NumIterations = int((float(test_duration_in_minutes)*60.0)/TimePerRun) + 1
device_log("TimePerRun calcualted to be %.2f seconds" % TimePerRun)
device_log("NumIterations calcualted to be %d" % NumIterations)


start_time = time.time()
##response = external_call('adb -s %s shell rm -f /data/ddr/*' % (memutil.ADB_DeviceID) )
##response = external_call('adb -s %s shell touch /data/ddr/qblog1.txt' % (memutil.ADB_DeviceID) )

device_log("SPAWNING THREAD FOR Memtester")
WorkerThread = threading.Thread(target=LaunchMemtester,args="")
WorkerThread.daemon = True  ## means thread dies if this program dies
WorkerThread.start()
device_log("Giving Memtester 5 seconds to begin")
SleepWithProgressIndicator(5)


repeat_loop = 0
while True:
    ##device_log("testing... %i" % repeat_loop)
    elapsed = ReturnElapsedFrom(start_time) ## this is time in seconds
    Hours = int(elapsed / (60*60))
    Mins  = (elapsed - (Hours*60*60))
    Mins  = int( Mins/60)
    Secs  = int(elapsed - (Hours*60*60) - (Mins*60))
    device_log("STRESS TEST - Time since Memtester started: %i HOURS %i MINUTES %i SECONDS (%d minutes total. %d mins left)" % (Hours,Mins,Secs,test_duration_in_minutes,test_duration_in_minutes-int(elapsed/60)))

    response = external_call('adb -s %s shell "ps | grep -i memtester"' % (memutil.ADB_DeviceID) )
    if len(response)==0:
        ## app is probably done. only by checking log will we know
        break

    SleepWithProgressIndicator(3)
    repeat_loop += 1
    device_log("test_duration_in_minutes=%d and elapsed=%d" % (test_duration_in_minutes*60,elapsed))
    if (test_duration_in_minutes*60)<elapsed:
        SleepWithProgressIndicator(5)
        break



## Stress test runs forever. It can only be killed
CallKillApp(MemtesterFileName)


response = external_call('adb -s %s shell logcat -d -v time > %s' % (memutil.ADB_DeviceID,memutil.logcatname) )
response = external_call('adb -s %s shell dmesg > %s' % (memutil.ADB_DeviceID,memutil.log_dmesg) )

ScriptLogName    = os.path.join(memutil.PathForOutputDatFiles, "%s_memtesterResult.txt" % memutil.ADB_DeviceID)
response = external_call('adb -s %s pull /data/memtesterResult.txt %s' % (memutil.ADB_DeviceID,ScriptLogName) )
memutil.FilesCreated.append(ScriptLogName)



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

device_log("Trying to open '%s'" % ScriptLogName)

try:
    Temp = open(ScriptLogName, 'r')
except Exception, x:
    PrintError()
    device_log("WARNING: could not open '%s'" % ScriptLogName)
    device_log("REASON: %s" % x)
    ExitAndShowLogName(1,SHOWFAIL)

response = Temp.readlines()
Temp.close()

## Build the string to search for
## NOTE: Memtester takes iterations as input, but this test needs to use TIME. So NumIterations is just an ESTIMATE
##       If Memtester is still running at the end of elapsed time, then it passed. Let's check the log to ensure at
##       least 80% of the runs completed (i.e. testing shows 98% completed, so this should be a good margin)

AtLeastNumIterations = int(0.8*NumIterations)


SearchFor = "Loop %d" % (AtLeastNumIterations)
#SearchFor = "Loop"

device_log("Trying to find the phrase '%s' in ScriptLogName='%s'" % (SearchFor,ScriptLogName))

FoundIt = 0
for i in range(len(response)):
    if SearchFor in response[i]:
        FoundIt = 1
        break

if FoundIt == 1:
    device_log("The memtester completed all runs")
else:
    PrintError()
    device_log("The memtester DID NOT COMPLETE all runs, DID NOT find '%s'" % SearchFor)
    ExitAndShowLogName(1,SHOWFAIL)

Pass = ParseDmesgLog(ScriptLogName, ["failed"])
if Pass==0:
    PrintError()
    device_log("A 'failed' was found in the memtester log '%s'" % ScriptLogName)

if Pass==1:
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
    ExitAndShowLogName(1,SHOWFAIL)

else:
    sz = About + " \n\n"
    PrintPassed(About)
    sz += "\tDDR survived the Memtester stress test"

ExitAndShowLogName(0,SHOWPASS,sz)


