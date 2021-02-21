#!/usr/bin/python
#===========================================================================

# REFERENCES

#  $Header: //components/rel/boot.xf/1.1.c1/QcomPkg/Tools/storage/MemoryValidation/tiotest.py#1 $
#  $DateTime: 2016/03/17 01:14:31 $ 
#  $Author: pwbldsvc $

# when          who     what, where, why 
# --------      ---     ------------------------------------------------------- 
# 2015-06-30    ah      Bug fix to get log before attempting to parse it
# 2015-06-26    ah      Updated. Now also using Qualcomms version of TIOTEST
# 2015-06-03    ah      First release - This one works
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
tiotest (threaded IO tester) is a multi-threaded I/O benchmark. It is used to measure file 
system performance in four basic operations: sequential write, and random write, sequential 
read and random read.

USAGE:
python tiotest.py --testsequential --numiterations=16
python tiotest.py --testrandom --numiterations=16

"""

SHOWFAIL = 0
SHOWPASS = 1

DMesgRegEx = ["String/Regex 1 to look for","String/Regex 2 to look for"] ## Any messages here found in the log will be treated as errors


LogCatRegEx= ["String/Regex 1 to look for","String/Regex 2 to look for"] ## Any messages here found in the log will be treated as errors

memutil.GreName    = ""
memutil.TestName    = "tiotest"
memutil.csv_name    = "%s.csv" % memutil.TestName
memutil.log_dmesg   = "dmesg_%s.txt" % memutil.TestName
memutil.logcatname  = "logcat_%s.txt" % memutil.TestName

BW_MEM_WR = []
BW_MEM_RD = []
IOPS_WR   = []
IOPS_RD   = []

RandArgs     = "-r 12500 "
use_suspend_resume = 0
SuspendResumeWriteScript = "SuspendResumeWrite.sh"

memutil.search_paths= ["C:\\Temp\\Thundersoft\\SupportFiles\\tiotest","SupportFiles\\tiotest\\tiotest","\\\\harv-ahughes\\dropbox\\Thundersoft\\SupportFiles\\tiotest"]
##memutil.search_paths= ["\\\\lungo\\workspace2\\reddyn\\linux_filesystems\\bechmarks\\v.1"]
ArgumentOptions = ["test_duration_in_minutes=","filesizeinmb=","numiterations=","testsequential", "testrandom","numberofthreads","testread","testwrite","use_clock_switching","use_suspend_resume"]


#Usage: tiotest [options]
#  -f          Filesize per thread in MBytes (default: 10)
#  -b          Blocksize to use in bytes (default: 4096)
#  -d          Directory for test files (default: .)
#  -t          Number of concurrent test threads (default: 4)
#  -r          Random I/O operations per thread (default: 1000)
#  -o          Offset in Mb on disk between threads. Use with -R option
#  -k          Skip test number n. Could be used several times.
#  -L          Hide latency output
#  -R          Use raw devices. Set device name with -d option
#  -T          More terse output
#  -M          Use mmap for I/O
#  -W          Do writing phase sequentially
#  -S          Do writing synchronously
#  -O          Use offset from -o option for first thread. Use with -R option
#  -c          Consistency check data (will slow io and raise cpu%)
#  -D          Debug level (default: 0)
#  -h          Print this help and exit
#
#=======================================
#Additional options:
#    Option:             [Description]
#
#  --direct-io          Do direct io operations (open with O_DIRECT)
#
#=======================================

    
TestSeq      = 0
TestRnd      = 0
TestRead     = 0
TestWrite    = 0

AverageWRMBps = 0.0
AverageRDMBps = 0.0

NumIterations           = 16  ## number to average performance over
test_duration_in_minutes= 0

NumberOfThreads = 8
FileSizeInMB    = 10

TIOTESTresponse     = ""
ClockSwitchResponse = ""
def LaunchClockSwitching():
    global ClockSwitchResponse
    ClockSwitchResponse = external_call('adb -s %s shell sh /data/bimc_clock_fmax1804.sh -l' % (memutil.ADB_DeviceID), True, False )

def LaunchTIOTEST():
    global TIOTESTresponse
    ## I'm allowing SEQ or RND, but not both
    ## I'm allowing BOTH Write and Read

    szSkipString = "-L "

    if TestSeq==0 and (TestWrite==1 and TestRead==1):
        szSkipString += "-k 0 -k 2 " + RandArgs
    if TestSeq==0 and (TestWrite==1 and TestRead==0):
        szSkipString += "-k 0 -k 2 -k 3 " + RandArgs
    if TestSeq==0 and (TestWrite==0 and TestRead==1):
        szSkipString += "-k 0 -k 2 -k 1 " + RandArgs

    if TestRnd==0 and (TestWrite==1 and TestRead==1):
        szSkipString += "-k 1 -k 3 "
    if TestRnd==0 and (TestWrite==1 and TestRead==0):
        szSkipString += "-k 1 -k 3 -k 2  "
    if TestRnd==0 and (TestWrite==0 and TestRead==1):
        szSkipString += "-k 1 -k 3 -k 0 "

    start_time = time.time()

    for i in range(NumIterations):
        if test_duration_in_minutes > 0:
            elapsed = ReturnElapsedFrom(start_time) ## this is time in seconds
            Hours = int(elapsed / (60*60))
            Mins  = (elapsed - (Hours*60*60))
            Mins  = int( Mins/60)
            Secs  = int(elapsed - (Hours*60*60) - (Mins*60))
            device_log("STRESS TEST - Time since TIOTEST started: %i HOURS %i MINUTES %i SECONDS (Running for %d minutes total)" % (Hours,Mins,Secs,test_duration_in_minutes))
            if (test_duration_in_minutes*60)<elapsed:
                device_log("BREAKING since (test_duration_in_minutes*60)<elapsed")
                break

        TIOTESTresponse = external_call('adb -s %s shell /data/%s -t %d -d /data -f %d -b 4096 %s' % (memutil.ADB_DeviceID,TiotestFileName,NumberOfThreads,FileSizeInMB,szSkipString) )

        
        Lines = TIOTESTresponse.split("\n")

        if TestSeq:
            for line in Lines:
                m = re.search("(Write|Read)\s+\d+ MBs\s+\|\s+\d+\.\d+ s \|\s+(\d+\.\d+) MB/s \|\s+\|", line)
                if type(m) is NoneType:
                    continue
                else:
                    if len(m.groups()) < 2:
                        PrintBanner("ERROR")
                        device_log("Did not match all groups. Something failed")
                        TIOTESTresponse = "error" + TIOTESTresponse
                        return
                    else:
                        if m.group(1) == "Write":
                            BW_MEM_WR.append(float(m.group(2)))
                        else:
                            BW_MEM_RD.append(float(m.group(2)))
        else:
            for line in Lines:
                m = re.search("(Write|Read)\s+\d+ MBs\s+\|\s+\d+\.\d+ s \|\s+(\d+\.\d+) MB/s \|\s+(\d+)\s+\|", line)
                if type(m) is NoneType:
                    continue
                else:
                    if len(m.groups()) < 2:
                        PrintBanner("ERROR")
                        device_log("Did not match all groups. Something failed")
                        TIOTESTresponse = "error" + TIOTESTresponse
                        return
                    else:
                        if m.group(1) == "Write":
                            IOPS_WR.append(int(m.group(3)))
                        else:
                            IOPS_RD.append(int(m.group(3)))


    if TestSeq:
        for i in range(len(BW_MEM_WR)):
            device_log("BW_MEM_WR[%d] = %f" % (i,BW_MEM_WR[i]))
        for i in range(len(BW_MEM_RD)):
            device_log("BW_MEM_RD[%d] = %f" % (i,BW_MEM_RD[i]))
    else:
        for i in range(len(IOPS_WR)):
            device_log("IOPS_WR[%d] = %d" % (i,IOPS_WR[i]))
        for i in range(len(IOPS_RD)):
            device_log("IOPS_RD[%d] = %d" % (i,IOPS_RD[i]))

def ParseOtherCommandLineOptions():
    global test_duration_in_minutes,ArgumentOptions
    global NumIterations,use_suspend_resume
    global TestRnd,TestSeq,NumberOfThreads,FileSizeInMB,TestWrite,TestRead

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
        elif o == "--use_suspend_resume":
            device_log("User has requested use_suspend_resume")
            use_suspend_resume = 1
        elif o == "--testrandom":
            TestRnd = 1
            device_log("TestRnd requested by user with --testrandom")
        elif o == "--testsequential":
            TestSeq = 1
            device_log("TestSeq requested by user with --testsequential")
        elif o == "--testread":
            TestRead = 1
            device_log("TestRead requested by user with --testread")
        elif o == "--testwrite":
            TestWrite = 1
            device_log("TestWrite requested by user with --testwrite")
        elif o == "--numiterations":
            NumIterations = int(a)
            device_log("NumIterations set to %d with --numiterations" % NumIterations)
        elif o == "--numberofthreads":
            NumberOfThreads = int(a)
            device_log("NumberOfThreads set to %d with --numberofthreads" % NumberOfThreads)
        elif o == "--filesizeinmb":
            FileSizeInMB = int(a)
            device_log("FileSizeInMB set to %d with --filesizeinmb" % FileSizeInMB)
        else:
            PrintBanner("ERROR")
            device_log("ERROR: '%s' is not a valid option" % o)
            device_log("use 'python %s' to see a list of possible options" % sys.argv[0])
            ExitAndShowLogName(1)

    if TestRnd == 0 and TestSeq == 0:
        TestSeq = 1   ## means user didn't pick anything, so just do sequential

    if TestSeq == 1 and TestRnd == 1:
        PrintBanner("WARNING")
        device_log("Please choose only --testsequential OR --testrandom")
        TestRnd = 0

    if TestWrite == 0 and TestRead == 0:
        TestWrite = 1
        TestRead  = 1

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

device_log("tiotest.py version 2.0")

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

#response = external_call('adb -s 955d5021 shell dd if=/dev/zero of=/data/BigFile100.bin bs=1048576 count=50')
#sys.exit(0)

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

response = external_call('adb -s %s shell date -s %s' % (memutil.ADB_DeviceID,LinuxTimeString))

response = external_call('adb -s %s remount' % memutil.ADB_DeviceID)

##memutil.ADB_DeviceID = None
WaitForDeviceWithPassFail()


response = external_call('adb -s %s shell df' % memutil.ADB_DeviceID)

DataPartitionFreeSpaceInBytes = 0
for Line in response.split("\n"):
    Line = Line.strip() ## get rid of \r\r
    ##print Line
    
    m = re.search("/data", Line)
    if type(m) is not NoneType:
        ##                            Filesystem    Size     Used     Free   Blksize
        ## To be here means we found     /data      2.4G     1.3G     1.1G   4096
        SplitArray = Line.split(" ")   ## Will look like ['/data', '', '', '', '', '2.4G', '', '1.3G', '', '1.1G', '', '4096']
        ## Just ignore the empty ones, and we already know this is /data, and the 1.1G from above is Free space
        k = 0
        for j in range(len(SplitArray)):
            if len(SplitArray[j])>0:
                k+=1
                if k==4:
                    device_log("Found free space for /data, it is '%s'" % SplitArray[j])
                    ##DataPartitionFreeSpace
                    m = re.search("(\d+)\.(\d+)([KMG])", SplitArray[j])
                    if type(m) is NoneType:
                        device_log("Can't parse /data size")
                        ExitAndShowLogName(1)
                    else:
                        TempSize = float(m.group(1)) + float(m.group(2))/10.0
                        if m.group(3) == 'K':
                            TempSize = TempSize * 1024.0
                        elif m.group(3) == 'M':
                            TempSize = TempSize * 1024.0 * 1024.0
                        elif m.group(3) == 'G':
                            TempSize = TempSize * 1024.0 * 1024.0 * 1024.0
                        else:
                            device_log("Can't parse /data [KMG], it was '%s'" % m.group(3))
                            ExitAndShowLogName(1)
                            
                        DataPartitionFreeSpaceInBytes = TempSize
                        
                

if memutil.UserSpecified_systemis64bit==0:
    TestIfSystemIs64Bit()

## Make sure older version of app is gone
if len(memutil.GreName)>0:
    CallKillApp(memutil.GreName)

SetScreenTimeoutAndAirplaneMode(30)    ## this turns on screen, sets airplane mode and REBOOTS to changes take affect
TurnOnScreen()

if memutil.SystemIs64Bit:
    TiotestFileName = 'tiotest64'
else:
    TiotestFileName = 'tiotest32'


CallKillApp(TiotestFileName)

if use_suspend_resume:
    CopyFileToPhone(SuspendResumeWriteScript)

CanWeSwitchClocks() ## Sets memutil.CanSwitchClocks
if memutil.CanSwitchClocks and memutil.AllowClockSwitching:
    CopyFileToPhone("bimc_clock_fmax1804.sh")

CopyFileToPhone(TiotestFileName)

response = external_call('adb -s %s shell chmod 777 /data/%s' % (memutil.ADB_DeviceID,TiotestFileName) ) ## change permission


response = external_call('adb -s %s shell ls /proc/sys/vm/drop_caches -l' % (memutil.ADB_DeviceID) ) ## 
response = external_call('adb -s %s shell sync"' % (memutil.ADB_DeviceID) ) ## sync
response = external_call('adb -s %s shell \"echo 3 > /proc/sys/vm/drop_caches\"' % (memutil.ADB_DeviceID) ) ## drop caches



## Get free space on /data
device_log("DataPartitionFreeSpaceInBytes = %.2f" % DataPartitionFreeSpaceInBytes)

SizeInMB = int(DataPartitionFreeSpaceInBytes/(1024.0*1024.0))
if SizeInMB > 200:
    SizeInMB -= 190
else:
    PrintBanner("ERROR - Not enough room left in /data for the test. Please manually free up some room")
    ExitAndShowLogName(1)
    
device_log("SizeInMB = %d MB" % SizeInMB)

##FillDataPartitionWithTempFiles(SizeInMB)  


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

device_log("This will create %d files of size %dMB each. You will need at least %dMB of disk space" % (NumberOfThreads,FileSizeInMB,NumberOfThreads*FileSizeInMB))

if DataPartitionFreeSpaceInBytes/(1024*1024) < (NumberOfThreads*FileSizeInMB):
    PrintBanner("ERROR")
    device_log("You do not have enough free disk space for this test on /data. You only have %dMB available" % int(DataPartitionFreeSpaceInBytes/(1024*1024)))
    ExitAndShowLogName(1)

if memutil.CanSwitchClocks and memutil.AllowClockSwitching:
    ##CallKillApp("sh",True)   ## PreciseMatch=True
    PrintUsingClockSwitching()
    device_log("SPAWNING THREAD FOR CLOCK SWITCHING")
    ClockThread = threading.Thread(target=LaunchClockSwitching,args="")
    ClockThread.daemon = True  ## means thread dies if this program dies
    ClockThread.start()

device_log("SPAWNING THREAD FOR TIOTEST")
WorkerThread = threading.Thread(target=LaunchTIOTEST,args="")
WorkerThread.daemon = True  ## means thread dies if this program dies
WorkerThread.start()

##LaunchTIOTEST() ## uncomment this to debug, comment out the ClockThread stuff above

## This works. Spawn as a thread, grep ps to see it's still alive.

while True:
    SleepWithProgressIndicator(5)
    ShowClockRate()
    if GetPIDofRunningApp("tiotest") == 0:
        device_log("tiotest is NOT running, breaking loop")
        break

if "error" in TIOTESTresponse:
    ExitAndShowLogName(1,SHOWFAIL)


#sequential
#,---------------------------------------------------------------------------------.
#| Item                  | Time     | Rate          |  IOPS   | Usr CPU  | Sys CPU |
#+-----------------------+----------+---------------+---------+----------+---------+
#| Write          80 MBs |    3.2 s |   24.674 MB/s |         |   0.6 %  |  15.6 % |
#| Read           80 MBs |    0.7 s |  120.676 MB/s |         |   0.0 %  |  64.5 % |
#+-----------------------+----------+---------------+---------+----------+---------+
#random
#,---------------------------------------------------------------------------------.
#| Item                  | Time     | Rate          |  IOPS   | Usr CPU  | Sys CPU |
#+-----------------------+----------+---------------+---------+----------+---------+
#| Random Write  391 MBs |    4.0 s |   98.276 MB/s |   25159 |   3.4 %  |  31.9 % |
#| Random Read   391 MBs |    2.5 s |  158.619 MB/s |   40606 |   0.2 %  |  37.2 % |
#+-----------------------+----------+---------------+---------+----------+---------+

#Can also look for these as the test is running
#-rw------- root     root     260505600 2015-06-03 21:01 _21403_tiotest.0
#-rw------- root     root     268410880 2015-06-03 21:01 _21403_tiotest.1
#-rw------- root     root     268333056 2015-06-03 21:01 _21403_tiotest.2
#-rw------- root     root     266539008 2015-06-03 21:01 _21403_tiotest.3
#-rw------- root     root     262348800 2015-06-03 21:01 _21403_tiotest.4
#-rw------- root     root     268435456 2015-06-03 21:01 _21403_tiotest.5
#-rw------- root     root     267268096 2015-06-03 21:01 _21403_tiotest.6
#-rw------- root     root     262262784 2015-06-03 21:01 _21403_tiotest.7



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


if TestSeq:
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
else:
    SUM = 0.0
    for j in range(len(IOPS_RD)):
        device_log("IOPS_RD = %i" % IOPS_RD[j])
        SUM+=float(IOPS_RD[j])
    if SUM==0:
        PrintBanner("ERROR")
        device_log("No throughput recorded")
        ExitAndShowLogName(1,SHOWFAIL)
    else:
        AverageRDMBps = SUM/float(len(IOPS_RD))
        device_log("Average IOPS_RD = %.2f IOPS" % AverageRDMBps )

    SUM = 0.0
    for j in range(len(IOPS_WR)):
        device_log("IOPS_WR = %i" % IOPS_WR[j])
        SUM+=float(IOPS_WR[j])
    if SUM==0:
        PrintBanner("ERROR")
        device_log("No throughput recorded")
        ExitAndShowLogName(1,SHOWFAIL)
    else:
        AverageWRMBps = SUM/float(len(IOPS_WR))
        device_log("Average IOPS_WR = %.2f IOPS" % AverageWRMBps )



Pass = 1    ## Assume we're good

response = external_call('adb -s %s shell logcat -d -v time > %s' % (memutil.ADB_DeviceID,memutil.logcatname) )
response = external_call('adb -s %s shell dmesg > %s' % (ADB_DeviceID,memutil.log_dmesg) )

SleepWithProgressIndicator(4)

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
    if TestSeq:
        sz += "Average Sequential Read Throughput  (BW_MEM_RD) = %.2fMBps\nAverage Sequential Wrtie Throughput (BW_MEM_WR) = %.2fMBps" % (AverageRDMBps,AverageWRMBps)
    else:
        sz += "Average Random READ  IOPS (IOPS_RD) = %.2f IOPS\nAverage Random WRITE IOPS (IOPS_WR) = %.2f IOPS" % (AverageRDMBps,AverageWRMBps)

ExitAndShowLogName(0,SHOWPASS,sz)


