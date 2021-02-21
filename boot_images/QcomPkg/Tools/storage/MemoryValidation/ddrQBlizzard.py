#!/usr/bin/python
#===========================================================================

# REFERENCES

#  $Header: //components/rel/boot.xf/1.1.c1/QcomPkg/Tools/storage/MemoryValidation/ddrQBlizzard.py#1 $
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
This test uses the DDR teams QBlizzard tool. This is a DDR testing tool

--testperf
This test will launch 8 threads each performing read/write accesses to 32MB (--size_in_mb=32) memory buffers.
From this the throughput is calculated and reported in MBps.
This test is performed 16 times and averaged. The amount to average is set with --numiterations=16
There is no pass/fail for this test. It is a performance test to report values.

--teststress
This runs the official QBlizzard 'stress test'. This creates 8 threads and performing read/write
operations to various sized DDR buffers until --test_duration_in_minutes=1440 elapses. This test
is known to stress DDR and expose any corner cases. This test passes *if* the test completes 
without the phone crashing (or rebooting)

USAGE:
python ddrQBlizzard.py --testperf --numiterations=16 --size_in_mb=32
python ddrQBlizzard.py --teststress --test_duration_in_minutes=1440 --use_clock_switching

"""

SHOWFAIL = 0
SHOWPASS = 1

DMesgRegEx = ["String/Regex 1 to look for","String/Regex 2 to look for"] ## Any messages here found in the log will be treated as errors


LogCatRegEx= ["String/Regex 1 to look for","String/Regex 2 to look for"] ## Any messages here found in the log will be treated as errors

memutil.GreName    = ""
memutil.TestName    = "ddrQBlizzard"
memutil.csv_name    = "%s.csv" % memutil.TestName
memutil.log_dmesg   = "dmesg_%s.txt" % memutil.TestName
memutil.logcatname  = "logcat_%s.txt" % memutil.TestName

memutil.search_paths= ["SupportFiles\\QBlizzard\\qb_v2.30_beta","SupportFiles\\QBlizzard\\standard_stress"]

ArgumentOptions = ["test_duration_in_minutes=", "numiterations=","testperf", "teststress","use_clock_switching","size_in_mb="]
    
TestPerf       = 0
TestStress      = 0

AverageWRMBps = 0.0
AverageRDMBps = 0.0

NumIterations = 16  ## number to average performance over
size_in_mb = 32
test_duration_in_minutes= 1
ClockSwitchResponse = ""
def LaunchClockSwitching():
    global ClockSwitchResponse
    device_log("Clock Switching Starting")
    device_log("Clock Switching Starting")
    device_log("Clock Switching Starting")
    szCommand = 'adb -s %s shell "sh /data/bimc_clock_fmax1804.sh -l"' % (memutil.ADB_DeviceID)
    device_log('CALLING==> '+szCommand)
    SleepWithProgressIndicator(1)
    ClockSwitchResponse = external_call(szCommand, True, False )

def LaunchQBlizzard():
    device_log("Launching QBlizzard thread")
    device_log("Launching QBlizzard thread")
    device_log("Launching QBlizzard thread")

    szCommand = 'adb -s %s shell "/data/%s  -stress_aligned -startSize 400000 -endSize 800000 -totalSize 800000 -errorCheck TRUE -repeatCount 0 -statSamples 1000000 -numThreads 8 "' % (memutil.ADB_DeviceID,QBlizzardFileName)
    device_log('CALLING==> '+szCommand)
    SleepWithProgressIndicator(1)
    response = external_call(szCommand)


def ParseOtherCommandLineOptions():
    global test_duration_in_minutes,ArgumentOptions
    global NumIterations,size_in_mb
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
        elif o == "--use_clock_switching":
            device_log("User has requested CLOCK SWITCHING if available")
            memutil.AllowClockSwitching = 1
        elif o == "--teststress":
            TestStress = 1
            device_log("TestStress requested by user with --teststress")
        elif o == "--testperf":
            TestPerf = 1
            device_log("TestPerf requested by user with --testperf")
        elif o == "--size_in_mb":
            size_in_mb = int(a)
            device_log("size_in_mb set to %d with --size_in_mb" % size_in_mb)
        elif o == "--numiterations":
            NumIterations = int(a)
            device_log("NumIterations set to %d with --numiterations" % NumIterations)
        else:
            PrintBanner("ERROR")
            device_log("ERROR: '%s' is not a valid option" % o)
            device_log("use 'python %s' to see a list of possible options" % sys.argv[0])
            ExitAndShowLogName(1)

    if TestStress == 0 and TestPerf == 0:
        TestPerf = 1   ## means user didn't pick anything, so just do a speed test

    if TestPerf == 1 and TestStress == 1:
        PrintBanner("WARNING")
        device_log("Please choose only --testperf OR --teststress")
        TestStress = 0



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

device_log("ddrQBlizzard.py version 2.0")

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


if memutil.UserSpecified_systemis64bit==0:
    TestIfSystemIs64Bit()

## Make sure older version of app is gone
if len(memutil.GreName)>0:
    CallKillApp(memutil.GreName)

SetScreenTimeoutAndAirplaneMode(30)    ## this turns on screen, sets airplane mode and REBOOTS to changes take affect
TurnOnScreen()

if memutil.SystemIs64Bit:
    QBlizzardFileName = 'QBlizzard64LnxCons.v.30_beta'
else:
    QBlizzardFileName = 'QBlizzardLnxCons.v.30_beta'



CanWeSwitchClocks() ## Sets memutil.CanSwitchClocks

if memutil.AllowClockSwitching:
    ## User wants clock switching
    if memutil.CanSwitchClocks==False:
        PrintError()
        PrintBanner("Your device cannot switch clocks. This usually means you have a PRODUCTION build. You need an Engineering Build")
        ExitAndShowLogName(1)

if memutil.CanSwitchClocks and memutil.AllowClockSwitching:
    CopyFileToPhone("bimc_clock_fmax1804.sh")

CallKillApp(QBlizzardFileName)

CopyFileToPhone(QBlizzardFileName)
##CopyFileToPhone("run_qblizzard.sh")
##CopyFileToPhone("run_qblizzard_32.sh")
CopyFileToPhone("qb_READ.parms")
CopyFileToPhone("qb_WRITE.parms")



response = external_call('adb -s %s shell "chmod 777 /data/%s"' % (memutil.ADB_DeviceID,QBlizzardFileName) ) ## change permission


response = external_call('adb -s %s shell ls /proc/sys/vm/drop_caches -l' % (memutil.ADB_DeviceID) ) ## 
response = external_call('adb -s %s shell sync' % (memutil.ADB_DeviceID) ) ## sync
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


if memutil.CanSwitchClocks and memutil.AllowClockSwitching:
    ##CallKillApp("sh",True)   ## PreciseMatch=True
    PrintUsingClockSwitching()
    device_log("SPAWNING THREAD FOR CLOCK SWITCHING")
    ClockThread = threading.Thread(target=LaunchClockSwitching,args="")
    ClockThread.daemon = True  ## means thread dies if this program dies
    ClockThread.start()
    device_log("Giving Clock Switching 5 seconds to begin")
    SleepWithProgressIndicator(5)



if TestPerf:
    BW_MEM_RD = []
    BW_MEM_WR = []
    for j in range(NumIterations):

        #response = external_call('adb -s %s shell /data/%s -perf -startSize 4MB -endSize 4MB -totalSize 4MB -statSamples 1 -numThreads 8 /data/qb.parms' % (memutil.ADB_DeviceID,QBlizzardFileName) )
        response = external_call('adb -s %s shell /data/%s -perf -startSize %dMB -endSize %dMB -totalSize %dMB -statSamples 1 -numThreads 8 /data/qb_READ.parms' % (memutil.ADB_DeviceID,QBlizzardFileName,size_in_mb,size_in_mb,size_in_mb) )

        m = re.search("not executable", response)
        if type(m) is not NoneType:
            PrintBanner("ERROR")
            device_log("Re-run this program and add the argument --systemis64bit=%d" % (memutil.SystemIs64Bit^1))
            ExitAndShowLogName(1)

        m = re.search("BW_MEM_RD\s+(\d+)", response)
        if type(m) is NoneType:
            PrintBanner("ERROR")
            device_log("Did not find output. Was looking for BW_MEM_RD string. Something failed\nShould have been present in in this %d byte string: %s" % (len(response),response))
            device_log("You will MOST LIKELY NEED TO CHANGE --size_in_mb=%d to a smaller value" % (size_in_mb))
            device_log("You will MOST LIKELY NEED TO CHANGE --size_in_mb=%d to a smaller value" % (size_in_mb))
            device_log("You will MOST LIKELY NEED TO CHANGE --size_in_mb=%d to a smaller value" % (size_in_mb))
            ExitAndShowLogName(1,SHOWFAIL)
        else:
            BW_MEM_RD.append(int(m.group(1)))

    for j in range(NumIterations):

        #response = external_call('adb -s %s shell /data/%s -perf -startSize 4MB -endSize 4MB -totalSize 4MB -statSamples 1 -numThreads 8 /data/qb.parms' % (memutil.ADB_DeviceID,QBlizzardFileName) )
        response = external_call('adb -s %s shell /data/%s -perf -startSize %dMB -endSize %dMB -totalSize %dMB -statSamples 1 -numThreads 8 /data/qb_WRITE.parms' % (memutil.ADB_DeviceID,QBlizzardFileName,size_in_mb,size_in_mb,size_in_mb) )

        m = re.search("not executable", response)
        if type(m) is not NoneType:
            PrintBanner("ERROR")
            device_log("Re-run this program and add the argument --systemis64bit=%d" % (memutil.SystemIs64Bit^1))
            ExitAndShowLogName(1)

        m = re.search("BW_MEM_WR\s+(\d+)", response)
        if type(m) is NoneType:
            PrintBanner("ERROR")
            device_log("Did not find output. Was looking for BW_MEM_WR string. Something failed\nShould have been present in in this %d byte string: %s" % (len(response),response))
            ExitAndShowLogName(1,SHOWFAIL)
        else:
            BW_MEM_WR.append(int(m.group(1)))

    SUM = 0.0
    for j in range(len(BW_MEM_RD)):
        device_log("BW_MEM_RD = %i" % BW_MEM_RD[j])
        SUM+=float(BW_MEM_RD[j])
    if SUM==0:
        PrintBanner("ERROR")
        device_log("No throughput recorded")
        ExitAndShowLogName(1,SHOWFAIL)
    else:
        AverageRDMBps = SUM/float(len(BW_MEM_RD))
        device_log("Average BW_MEM_RD = %.2fMBps" % AverageRDMBps )

    SUM = 0.0
    for j in range(len(BW_MEM_WR)):
        device_log("BW_MEM_WR = %i" % BW_MEM_WR[j])
        SUM+=float(BW_MEM_WR[j])
    if SUM==0:
        PrintBanner("ERROR")
        device_log("No throughput recorded")
        ExitAndShowLogName(1,SHOWFAIL)
    else:
        AverageWRMBps = SUM/float(len(BW_MEM_WR))
        device_log("Average BW_MEM_WR = %.2fMBps" % AverageWRMBps )

else:   ## this is TestStress -------------- this is TestStress -------------- this is TestStress --------------
    start_time = time.time()
    ##response = external_call('adb -s %s shell rm -f /data/ddr/*' % (memutil.ADB_DeviceID) )
    ##response = external_call('adb -s %s shell touch /data/ddr/qblog1.txt' % (memutil.ADB_DeviceID) )

    device_log("SPAWNING THREAD FOR QBLIZZARD")
    WorkerThread = threading.Thread(target=LaunchQBlizzard,args="")
    WorkerThread.daemon = True  ## means thread dies if this program dies
    WorkerThread.start()
    device_log("Giving QBlizzard 5 seconds to begin")
    SleepWithProgressIndicator(5)

    repeat_loop = 0
    while True:
        ##device_log("testing... %i" % repeat_loop)
        elapsed = ReturnElapsedFrom(start_time) ## this is time in seconds
        Hours = int(elapsed / (60*60))
        Mins  = (elapsed - (Hours*60*60))
        Mins  = int( Mins/60)
        Secs  = int(elapsed - (Hours*60*60) - (Mins*60))
        device_log("STRESS TEST - Time since QBLIZZARD started: %i HOURS %i MINUTES %i SECONDS (%d minutes total. %d mins left)" % (Hours,Mins,Secs,test_duration_in_minutes,test_duration_in_minutes-int(elapsed/60)))

        response = external_call('adb -s %s shell "ps | grep -i qbl"' % (memutil.ADB_DeviceID) )
        if len(response)==0:
            PrintError()
            device_log("There was no response, app is not running")
            ExitAndShowLogName(1,SHOWFAIL)
        ###response = external_call('adb -s %s shell grep -i err /data/ddr/qb*.txt' % (memutil.ADB_DeviceID),True,False )
        #####No such file or directory
        ###if len(response)!=0:
        ###    device_log("There was an error")
        ###    ExitAndShowLogName(1,SHOWFAIL)
        response = external_call('adb -s %s shell "cat /d/clk/bimc_clk/rate"' % (memutil.ADB_DeviceID) )
        response = external_call('adb -s %s shell "cat /d/clk/bimc_clk/measure"' % (memutil.ADB_DeviceID) )

        SleepWithProgressIndicator(3)
        repeat_loop += 1
        device_log("test_duration_in_minutes=%d and elapsed=%d" % (test_duration_in_minutes*60,elapsed))
        if (test_duration_in_minutes*60)<elapsed:
            ##device_log()
            break
    ## Stress test runs forever. It can only be killed
    CallKillApp(QBlizzardFileName)

#    m = re.search("not executable", response)
#    if type(m) is not NoneType:
#        PrintBanner("ERROR")
#        device_log("Re-run this program and add the argument --systemis64bit=%d" % (memutil.SystemIs64Bit^1))
#        ExitAndShowLogName(1)




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
    ExitAndShowLogName(1,SHOWFAIL)

else:
    sz = About + " \n\n"
    PrintPassed(About)
    if TestPerf:
        sz += "Average DDR Read Throughput  (BW_MEM_RD) = %.2fMBps\nAverage DDR Write Throughput (BW_MEM_WR) = %.2fMBps" % (AverageRDMBps,AverageWRMBps) 
    else:
        sz += "\tDDR survived the QBlizzard stress test"

ExitAndShowLogName(0,SHOWPASS,sz)


