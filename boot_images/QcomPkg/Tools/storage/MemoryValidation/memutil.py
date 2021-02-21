#!/usr/bin/python
#===========================================================================

#  memutil.py has common functions used by all tools

# REFERENCES

#  $Header: //components/rel/boot.xf/1.1.c1/QcomPkg/Tools/storage/MemoryValidation/memutil.py#1 $
#  $DateTime: 2016/03/17 01:14:31 $ 
#  $Author: pwbldsvc $

# when          who     what, where, why 
# --------      ---     ------------------------------------------------------- 
# 2015-06-30    ah      Bug fixes
# 2015-06-01    ah      Updated with genral functions for all scripts
# 2015-05-05    ah      First release basic functions

# Copyright (c) 2014-2015
# Qualcomm Technologies Incorporated.
# All Rights Reserved.
# Qualcomm Confidential and Proprietary
# ===========================================================================*/

import struct, os, sys, getopt
from time import strftime, localtime
import datetime
import zlib
import time
import sys
import subprocess as sub
import re
from types import *
import time
from time import sleep
from time import strftime, localtime

SHOWFAIL = 0
SHOWPASS = 1

FilesCopiedToPhone  = []
TempFilesCreated    = []
APKsInstalled       = []
PIDarray            = []
search_paths        = []
FilesCreated        = []
RunningAsRoot       = False
RetryTimeInSeconds  = 4
ADB_DeviceID        = None

GrepName    = "GrepName"
TestName    = "TestName"
csv_name    = "csv_name"
log_dmesg   = "log_dmesg"
logcatname  = "logcatname"

UserSpecified_systemis64bit = 0
SystemIs64Bit       = 0
ScreenState         = 0

CanSwitchClocks     = False
AllowClockSwitching = False
RebootBeforeScriptBegins = True
waitfordeviceattempts = 100

#adb shell rm /data/tiotest
#adb shell rm /data/lmdd
#adb shell rm /data/iozone

#adb push \\cbsp-licorice\Dropbox\tools\tiotest /data/
#adb shell chmod 777 /data/tiotest
#adb push \\cbsp-licorice\Dropbox\tools\lmdd\la\lmdd /data/
#adb shell chmod 777 /data/lmdd
#adb push \\cbsp-licorice\Dropbox\tools\iozone\la\iozone /data/
#adb shell chmod 777 /data/iozone

## WRITE
## adb shell /data/lmdd if=internal of=/data/test.txt bs=128k count=7650 sync=1

## READ
## adb shell "echo 3 > /proc/sys/vm/drop_caches"    ## you have to do this before doing read to clear the file cache
## adb shell /data/lmdd if=/data/test.txt of=internal bs=128k count=7650



LogUntilFileIsCreated = ""  ## holds all logging until --logname= is created
LogIsCreated = 0

WorkerThread = None


PhaseSetupTarget            = False
PhaseProfiling          = False
PhasePlotting           = False
PhaseInstallAPKs        = False
PhaseSkipConfig         = False
PhoneIsReady            = False
loadbootimg             = False
StartAppName            = ""
StartGrepName           = ""
AppIsBlocking           = True
AppNeedsToBeKilled      = False
profiletimeinseconds    = 4
PathForOutputDatFiles   = "c:\\temp\\"
aupath                  = ""
doblocktrace            = True

log_name = "log.txt"

KEYCODE = ["KEYCODE_UNKNOWN", "KEYCODE_MENU", "KEYCODE_SOFT_RIGHT", "KEYCODE_HOME", "KEYCODE_BACK", "KEYCODE_CALL", "KEYCODE_ENDCALL", "KEYCODE_0", "KEYCODE_1", "KEYCODE_2", "KEYCODE_3", "KEYCODE_4", 
"KEYCODE_5", "KEYCODE_6", "KEYCODE_7", "KEYCODE_8", "KEYCODE_9", "KEYCODE_STAR", "KEYCODE_POUND", "KEYCODE_DPAD_UP", "KEYCODE_DPAD_DOWN", "KEYCODE_DPAD_LEFT", "KEYCODE_DPAD_RIGHT", 
"KEYCODE_DPAD_CENTER", "KEYCODE_VOLUME_UP", "KEYCODE_VOLUME_DOWN", "KEYCODE_POWER", "KEYCODE_CAMERA", "KEYCODE_CLEAR", "KEYCODE_A", "KEYCODE_B", "KEYCODE_C", "KEYCODE_D", "KEYCODE_E", 
"KEYCODE_F", "KEYCODE_G", "KEYCODE_H", "KEYCODE_I", "KEYCODE_J", "KEYCODE_K", "KEYCODE_L", "KEYCODE_M", "KEYCODE_N", "KEYCODE_O", "KEYCODE_P", "KEYCODE_Q", "KEYCODE_R", "KEYCODE_S", 
"KEYCODE_T", "KEYCODE_U", "KEYCODE_V", "KEYCODE_W", "KEYCODE_X", "KEYCODE_Y", "KEYCODE_Z", "KEYCODE_COMMA", "KEYCODE_PERIOD", "KEYCODE_ALT_LEFT", "KEYCODE_ALT_RIGHT", "KEYCODE_SHIFT_LEFT", 
"KEYCODE_SHIFT_RIGHT", "KEYCODE_TAB", "KEYCODE_SPACE", "KEYCODE_SYM", "KEYCODE_EXPLORER", "KEYCODE_ENVELOPE", "KEYCODE_ENTER", "KEYCODE_DEL", "KEYCODE_GRAVE", "KEYCODE_MINUS", "KEYCODE_EQUALS", 
"KEYCODE_LEFT_BRACKET", "KEYCODE_RIGHT_BRACKET", "KEYCODE_BACKSLASH", "KEYCODE_SEMICOLON", "KEYCODE_APOSTROPHE", "KEYCODE_SLASH", "KEYCODE_AT", "KEYCODE_NUM", "KEYCODE_HEADSETHOOK", "KEYCODE_FOCUS", 
"KEYCODE_PLUS", "KEYCODE_MENU", "KEYCODE_NOTIFICATION", "KEYCODE_SEARCH", ",TAG_LAST_KEYCODE",]

KEYNAME = {}


def PrintUSBshouldBeUnplugged():
    device_log(" _   _ ___________       _                 _     _             ")
    device_log("| | | /  ___| ___ \\     | |               | |   | |            ")
    device_log("| | | \\ `--.| |_/ /  ___| |__   ___  _   _| | __| |            ")
    device_log("| | | |`--. \\ ___ \\ / __| '_ \\ / _ \\| | | | |/ _` |            ")
    device_log("| |_| /\\__/ / |_/ / \\__ \\ | | | (_) | |_| | | (_| |            ")
    device_log(" \\___/\\____/\\____/  |___/_| |_|\\___/ \\__,_|_|\\__,_|            ")
    device_log("                                                               ")
    device_log("                                                               ")
    device_log(" _                              _                            _ ")
    device_log("| |                            | |                          | |")
    device_log("| |__   ___   _   _ _ __  _ __ | |_   _  __ _  __ _  ___  __| |")
    device_log("| '_ \\ / _ \\ | | | | '_ \\| '_ \\| | | | |/ _` |/ _` |/ _ \\/ _` |")
    device_log("| |_) |  __/ | |_| | | | | |_) | | |_| | (_| | (_| |  __/ (_| |")
    device_log("|_.__/ \\___|  \\__,_|_| |_| .__/|_|\\__,_|\\__, |\\__, |\\___|\\__,_|")
    device_log("                         | |             __/ | __/ |           ")
    device_log("                         |_|            |___/ |___/  \n")

def PrintKillAPP():
    device_log(" ")
    device_log(" _   ___ _ _     ___  ____________ ")
    device_log("| | / (_) | |   / _ \\ | ___ \\ ___ \\")
    device_log("| |/ / _| | |  / /_\\ \\| |_/ / |_/ /")
    device_log("|    \\| | | |  |  _  ||  __/|  __/ ")
    device_log("| |\\  \\ | | |  | | | || |   | |    ")
    device_log("\\_| \\_/_|_|_|  \\_| |_/\\_|   \\_|  \n")

def PrintStartAPP():
    device_log(" ")
    device_log(" _____ _             _      ___  ____________ ")
    device_log("/  ___| |           | |    / _ \\ | ___ \\ ___ \\")
    device_log("\\ `--.| |_ __ _ _ __| |_  / /_\\ \\| |_/ / |_/ /")
    device_log(" `--. \\ __/ _` | '__| __| |  _  ||  __/|  __/ ")
    device_log("/\\__/ / || (_| | |  | |_  | | | || |   | |    ")
    device_log("\\____/ \\__\\__,_|_|   \\__| \\_| |_/\\_|   \\_| \n")

def PrintADBasRoot():
    device_log(" ")
    device_log(" _____      _      ___ ____________              ______ _____  _____ _____ ")
    device_log("/  ___|    | |    / _ \\|  _  \\ ___ \\             | ___ \\  _  ||  _  |_   _|")
    device_log("\\ `--.  ___| |_  / /_\\ \\ | | | |_/ /   __ _ ___  | |_/ / | | || | | | | | ") 
    device_log(" `--. \\/ _ \\ __| |  _  | | | | ___ \\  / _` / __| |    /| | | || | | | | |  ")
    device_log("/\\__/ /  __/ |_  | | | | |/ /| |_/ / | (_| \\__ \\ | |\\ \\\\ \\_/ /\\ \\_/ / | |  ")
    device_log("\\____/ \\___|\\__| \\_| |_/___/ \\____/   \\__,_|___/ \\_| \\_|\\___/  \\___/  \\_/ \n")

def PrintConfigurePhone():
    device_log(" ")
    device_log(" _____              __ _                       ______ _                      ")
    device_log("/  __ \\            / _(_)                      | ___ \\ |                     ")
    device_log("| /  \\/ ___  _ __ | |_ _  __ _ _   _ _ __ ___  | |_/ / |__   ___  _ __   ___ ")
    device_log("| |    / _ \\| '_ \\|  _| |/ _` | | | | '__/ _ \\ |  __/| '_ \\ / _ \\| '_ \\ / _ \\")
    device_log("| \\__/\\ (_) | | | | | | | (_| | |_| | | |  __/ | |   | | | | (_) | | | |  __/")
    device_log(" \\____/\\___/|_| |_|_| |_|\\__, |\\__,_|_|  \\___| \\_|   |_| |_|\\___/|_| |_|\\___|")
    device_log("                          __/ |                                              ")
    device_log("                         |___/                              \n")

def PrintSuccess():
    device_log(" ")
    device_log(" _____                             ")
    device_log("/  ___|                            ")
    device_log("\\ `--. _   _  ___ ___ ___  ___ ___ ")
    device_log(" `--. \\ | | |/ __/ __/ _ \\/ __/ __|")
    device_log("/\\__/ / |_| | (_| (_|  __/\\__ \\__ \\")
    device_log("\\____/ \\__,_|\\___\\___\\___||___/___/\n")

def PrintAdbReboot():
    device_log(" ")
    device_log("memutil.py version 2.0")
    device_log(" ")
    device_log("           _ _                _                 _   ")
    device_log("          | | |              | |               | |  ")
    device_log("  __ _  __| | |__    _ __ ___| |__   ___   ___ | |_ ")
    device_log(" / _` |/ _` | '_ \\  | '__/ _ \\ '_ \\ / _ \\ / _ \\| __|")
    device_log("| (_| | (_| | |_) | | | |  __/ |_) | (_) | (_) | |_ ")
    device_log(" \\__,_|\\__,_|_.__/  |_|  \\___|_.__/ \\___/ \\___/ \\__|\n")
                                                        
def PrintScreenOff():
    device_log("")
    device_log(" _____                            _____  __  __ ")
    device_log("/  ___|                          |  _  |/ _|/ _|")
    device_log("\\ `--.  ___ _ __ ___  ___ _ __   | | | | |_| |_ ")
    device_log(" `--. \\/ __| '__/ _ \\/ _ \\ '_ \\  | | | |  _|  _|")
    device_log("/\\__/ / (__| | |  __/  __/ | | | \\ \\_/ / | | |  ")
    device_log("\\____/ \\___|_|  \\___|\\___|_| |_|  \\___/|_| |_| \n")

def PrintScreenOn():
    device_log(" ")
    device_log(" _____                            _____       ")
    device_log("/  ___|                          |  _  |      ")
    device_log("\\ `--.  ___ _ __ ___  ___ _ __   | | | |_ __  ")
    device_log(" `--. \\/ __| '__/ _ \\/ _ \\ '_ \\  | | | | '_ \\ ")
    device_log("/\\__/ / (__| | |  __/  __/ | | | \\ \\_/ / | | |")
    device_log("\\____/ \\___|_|  \\___|\\___|_| |_|  \\___/|_| |_|\n")

def PrintBootImg():
    device_log("")
    device_log("______             _     _                 ")
    device_log("| ___ \\           | |   (_)                ")
    device_log("| |_/ / ___   ___ | |_   _ _ __ ___   __ _ ")
    device_log("| ___ \\/ _ \\ / _ \\| __| | | '_ ` _ \\ / _` |")
    device_log("| |_/ / (_) | (_) | |_ _| | | | | | | (_| |")
    device_log("\\____/ \\___/ \\___/ \\__(_)_|_| |_| |_|\\__, |")
    device_log("                                      __/ |")
    device_log("                                     |___/ \n")

def PrintUsingClockSwitching():
    device_log(" _   _     _               _____ _            _    ")
    device_log("| | | |   (_)             /  __ \\ |          | |   ")
    device_log("| | | |___ _ _ __   __ _  | /  \\/ | ___   ___| | __")
    device_log("| | | / __| | '_ \\ / _` | | |   | |/ _ \\ / __| |/ /")
    device_log("| |_| \\__ \\ | | | | (_| | | \\__/\\ | (_) | (__|   < ")
    device_log(" \\___/|___/_|_| |_|\\__, |  \\____/_|\\___/ \\___|_|\\_\\")
    device_log("                    __/ |                          ")
    device_log("                   |___/ ")
    device_log("    _____          _ _       _     _             ")
    device_log("   /  ___|        (_) |     | |   (_)            ")
    device_log("   \\ `--.__      ___| |_ ___| |__  _ _ __   __ _ ")
    device_log("    `--. \\ \\ /\\ / / | __/ __| '_ \\| | '_ \\ / _` |")
    device_log("   /\\__/ /\\ V  V /| | || (__| | | | | | | | (_| |")
    device_log("   \\____/  \\_/\\_/ |_|\\__\\___|_| |_|_|_| |_|\\__, |")
    device_log("                                            __/ |")
    device_log("                                           |___/\n")

def ResetLog():
    global log_name
    global LogIsCreated, LogUntilFileIsCreated

    try:
        log_fp = open(log_name, 'w')
        log_fp.close()
    except Exception, x:
        print "ERROR: could not open '%s'" % log_name
        print "REASON: %s" % x
        return

    LogIsCreated = 1
    device_log(LogUntilFileIsCreated)
    #LogUntilFileIsCreated = ""

## 03-18 12:05:44.609
## 03-20 14:34:20.111
## 12:05:24

def timestamp(now = time.time()):
   localtime = time.localtime(now)
   milliseconds = '%03d' % int((now - int(now)) * 1000)
   #return time.strftime('%Y-%m-%d %H:%M:%S.', localtime) + milliseconds
   #print "%s" % time.strftime('%H:%M:%S', localtime)
   return time.strftime('%H:%M:%S.', localtime) + milliseconds

def ReturnElapsedFrom(FromTime):
   elapsed = time.time() - FromTime
   if elapsed==0:
       return 0.00001
   else:
       return elapsed

def ReturnElapsedFromStartEnd(Start,End):
   elapsed = End - Start
   if elapsed==0 or elapsed<0:
       return 0.00001
   else:
       return elapsed


def device_log(message, display=1):
    global LogIsCreated, LogUntilFileIsCreated

    if LogIsCreated:
        try:
            log_fp = open(log_name, 'a')
        except Exception, x:
            print "ERROR: could not open '%s'" % log_name
            print "REASON: %s" % x
            return

        ##print "timestamp() = '%s'\n" % str(datetime.datetime.now())

        try:
            log_fp.write("%s %s\n" % (str(datetime.datetime.now()),message))
        except Exception, x:
            print "ERROR: could not write to '%s'" % log_name
            print "REASON: %s" % x
            return

        log_fp.flush()
        log_fp.close()
    else:
        LogUntilFileIsCreated += "%s %s\n" % (str(datetime.datetime.now()),message)

    if display==1:
        print message



def PrintBanner(sz):
    device_log("-"*78)
    device_log(sz)
    device_log("-"*78)

def SleepWithProgressIndicator(TimeInSeconds):
    device_log("\n")
    for i in range(TimeInSeconds):
        sys.stdout.write(".")
        sleep(1)
    device_log("\n")



def ExitAndShowLogName(ReturnValue=0,PassFail=None,PassFailMessage=None):
    global log_name,FilesCreated,PIDarray
    print "\n"

    CleanUpTempFilesCreated()
    CleanUpFilesCopiedToPhone() ## files to copied to /data
    CleanUpAPKsInstalled()      ## APKs installed with 'adb install'

    if AllowClockSwitching and CanSwitchClocks:
        PIDarray = []
        CallKillApp("sh",True)   ## PreciseMatch=True
        SleepWithProgressIndicator(5)

    sz = "DONE %s (%s) ReturnValue = %d" % (TestName,os.path.basename(sys.argv[0]),ReturnValue)
    WriteDMESG(sz) ## puts message into dmesg
    WriteLogcat(sz)## puts message into logcat
    device_log(sz)


    response = external_call('adb -s %s shell logcat -d -v time > %s' % (ADB_DeviceID,logcatname) )
    response = external_call('adb -s %s shell dmesg > %s' % (ADB_DeviceID,log_dmesg) )


    if len(FilesCreated)>0:
        device_log("Files created: (NOTE: use --outputdir=c:\\temp )")
        for file in FilesCreated:
            device_log(file)
        device_log("\n")

    if PassFail != None:
        if PassFail == 1:
            PrintPassed()
        else:
            PrintFailed()

        if PassFailMessage != None:
            PrintBanner(PassFailMessage)

    ##device_log("**Leaving ExitAndShowLogName()\n\nCalling sys.exit(1)\n\n\tLog is '%s'" % log_name)
    device_log("Log is '%s'" % (log_name))
    sys.exit(ReturnValue)


def ParseCommonCommandLineOptions(ThisArgumentOptions, About=""):
    global log_name,PathForOutputDatFiles,ADB_DeviceID,search_paths,RebootBeforeScriptBegins
    global UserSpecified_systemis64bit, SystemIs64Bit,waitfordeviceattempts

    device_log("SCRIPT WAS CALLED EXACTLY LIKE THIS BELOW")

    sz = "python "
    for o in sys.argv:
        sz += o + " "

    device_log("*"*70)
    device_log("%s" % sz)
    device_log("*"*70+"\nOS: %s\n" % sys.platform)

    if not KEYNAME: ## means dictionary is empty
        MapKeys()   ## loads the dictionary


    ArgumentOptions = ["outputdir=","deviceid=","search_path=", "systemis64bit=","noreboot","waitfordeviceattempts=", 
                       "logname="]+ThisArgumentOptions

    ArgumentOptions = sorted(ArgumentOptions)

    if len(sys.argv)<=1:
        PrintBanner("Possible Options")
        NumOptions      = len(ArgumentOptions)
        NumColumns      = 3
        NumLoop         = int(NumOptions/NumColumns)+1

        sz = ""

        for i in range(NumLoop):
            if i+2*NumLoop < len(ArgumentOptions):
                lastOne = ArgumentOptions[i+2*NumLoop]
            else:
                lastOne = ""
            sz += "--%-35s    --%-35s    --%-35s\n" % (ArgumentOptions[i],ArgumentOptions[i+NumLoop],lastOne)
        print sz

        ##print "\n\n"
        print "="*80
        print About
        #print "STEP 1: python blocktrace.py --setuptarget"
        #print "STEP 2: python blocktrace.py --doprofiling --profiletimeinseconds=15 --start=lmdd"
        sys.exit(0)

    ##print "sys.argv[1:]=",sys.argv[1:]

    for opt in sys.argv[1:]:
        if opt[0:2]!="--":
            PrintBanner("ERROR")
            print "This argument '%s'\n\n\tdoesn't start with two dashes, i.e. '--', please correct\n\n" % opt
            ExitAndShowLogName(1)

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

    NumCommandLineOpts          = 0
    NumCommandLineOptsMatched   = 0
    for opt in sys.argv[1:]:
        #print "NumCommandLineOpts+=1 for '%s'" % opt
        NumCommandLineOpts+=1

        if "=" in opt:
            temp=opt.split('=')
            if len(temp[1])==0:
                print "\nERROR: Looks like you didn't specify a value after the \"=\" sign?"
                ExitAndShowLogName(1)
            else:
                # opt currently is --fh_wipe_gpt=1
                opt = temp[0] + "=" ## To match ArgumentOptions, needs to look like --fh_wipe_gpt=

        if opt[2:] in ArgumentOptions:
            #i.e. user has --sahara=d13 and opt[2:] is "sahara=", which should be in ArgumentOptions
            NumCommandLineOptsMatched+=1

    if NumCommandLineOptsMatched != NumCommandLineOpts:
        print "\nERROR: Looks like you have an error in your command line options? Maybe missing an \"=\" sign?"
        ExitAndShowLogName(1)
    ## Command line will over ride anything in the XML file
    ## Therefore parse XML first

    for o, a in opts:
        ##CheckArgumentForMistake(ArgumentOptions,a)      ## This function is only needed if there are single options allowed, i.e. "-d" can be confused with "--dload_image"
        if o == "--outputdir":
            sys.argv.remove(o+"="+a)    ## get rid of this option

            PathForOutputDatFiles = a

            if not os.path.exists(PathForOutputDatFiles):
                ## Can I create this directory since it does not exist?
                os.system("mkdir %s" % PathForOutputDatFiles)
                if os.path.exists(PathForOutputDatFiles):
                    pass
                else:
                    device_log("")
                    device_log("ERROR: The directory you specified with --outputdir does not exist! And I cannot create it")
                    ExitAndShowLogName(1)

            PathForOutputDatFiles = os.path.realpath(PathForOutputDatFiles) ## this turns a relative path MyPath into c:\cwd\MyPath

            
        elif o == "--search_path":
            sys.argv.remove(o+"="+a)    ## get rid of this option
            search_paths.append(a.strip())	# These need to be first
        elif o == "--waitfordeviceattempts":
            sys.argv.remove(o+"="+a)    ## get rid of this option
            waitfordeviceattempts = int(a.strip())
        elif o == "--noreboot":
            sys.argv.remove(o)    ## get rid of this option
            RebootBeforeScriptBegins = 0
        elif o == "--deviceid":
            sys.argv.remove(o+"="+a)    ## get rid of this option
            ADB_DeviceID = a
            device_log("User set ADB_DeviceID to '%s' with --deviceid=%s" % (ADB_DeviceID,ADB_DeviceID))

        elif o == "--systemis64bit":
            UserSpecified_systemis64bit = 1
            SystemIs64Bit = int(a)
            device_log("SystemIs64Bit set to %d" % SystemIs64Bit)

        elif o == "--logname":
            sys.argv.remove(o+"="+a)    ## get rid of this option

            Templog_name = a

            PossibleDir = os.path.dirname(Templog_name)
            if len(PossibleDir)>0:
                device_log("ERROR: Don't specify a path in --logname=")
                device_log("ERROR: instead use --outputdir= So that all files to be saved in the same folder\n")
                device_log("ERROR: Do this instead '--logname=%s --outputdir=%s'" % (Templog_name[len(PossibleDir):],PossibleDir))
                ExitAndShowLogName(1)

            log_name = Templog_name
            ## to be this far, they didn't specify a path, just a filename

    log_name = os.path.join(PathForOutputDatFiles, log_name)

    if sys.platform.startswith("linux"):
        print "RUNNING ON LINUX"
        print "RUNNING ON LINUX"
        print "RUNNING ON LINUX"



def external_call(command, capture_output=True, show_output=True):
    global ProcessP
    errors = None
    output = None
    ExternalCallOutput = ""

    if show_output == True:
        device_log("\n=================================================\nCALLING==> '%s'\n=================================================\n" % command)

    try:
        if capture_output:
            if sys.platform.startswith("linux"):
                p = sub.Popen(command, stdout=sub.PIPE, stderr=sub.PIPE, shell=True)
            else:
                ProcessP = sub.Popen(command, stdout=sub.PIPE, stderr=sub.PIPE, shell=True)
            ExternalCallOutput, errors = ProcessP.communicate()
        else:
            ExternalCallOutput = ""
            if show_output == True:
                print "USING SYSTEM"

            os.system(command)
    except Exception, e:
        print("ExternalCallOutput:\t\t%s" % ExternalCallOutput)
        print("Error executing command '%s' (%s)" % (str(command), e))
        #clean_up()
        ExitAndShowLogName(1)
    finally:
        #if not ExternalCallOutput is None:
        #    device_log("Result: %s" % ExternalCallOutput)
        if (not errors is None) and (not errors == ""):
            if show_output == True:
                device_log("Process stderr: %s" % errors)

    if show_output == True:
        ##device_log("***ExternalCallOutput:\n"+ExternalCallOutput)
        szTemp = ExternalCallOutput
        device_log(szTemp)

    return ExternalCallOutput




def RunADBasRoot():
    global RunningAsRoot
    NumAttempts = 10
    Attempt = 0

    PrintADBasRoot()

    ReadyForNextStep = False

    while ReadyForNextStep == False:
        ## Restart ADB as ROOT
        Attempt +=1
        if Attempt >=NumAttempts:
            PrintError()
            device_log("I can't seem to get 'adb root' to work on your device????")
            device_log("I can't seem to get 'adb root' to work on your device????")
            device_log("I can't seem to get 'adb root' to work on your device????")
            import pdb; pdb.set_trace()
            ExitAndShowLogName(1)

        response = external_call('adb -s %s root' % (ADB_DeviceID) )
        
        if len(response)==0:
            ## Means devcie is really FULLY up, so look for it again
            WaitForDeviceWithPassFail()
            SleepWithProgressIndicator(5)
            continue

        ## else to be this far means we have SOME response from "adb root"

        m = re.search("adbd is already running as root", response.strip() )
        if type(m) is not NoneType:
            ## Good, we are already running as root
            RunningAsRoot = True
            ReadyForNextStep = True

        ## Are we in root yet?
        if RunningAsRoot==False:
            ## Not already in root, most likely it's restarting as root
            m = re.search("restarting adbd as root", response.strip() )
            if type(m) is not NoneType:
                ## Phone is rebooting into root
                RunningAsRoot = True
                ReadyForNextStep = True
                device_log("ADB is restarting as root, this can take a bit, will wait")
                SleepWithProgressIndicator(15)

        ## to be this far means we got some other response
        if RunningAsRoot==False:
            ##device_log("Device didn't respond as expected, will try again")
            SleepWithProgressIndicator(5)

    ## The above operation can take some time
    ##WaitForDeviceWithPassFail()

    ##SleepWithProgressIndicator(4)



    ## To be this far, we are running as ROOT
    ## To be this far, we are running as ROOT
    ## To be this far, we are running as ROOT
    ## To be this far, we are running as ROOT



def DisplayNoResponseMessageAndSleep(TimeInSeconds):
    device_log("No response yet, waiting %d second(s)\n" % (TimeInSeconds))
    device_log("\tAt this point you could double check USB is attached, drivers etc?")
    device_log("\tHit CTRL+C to quit")
    SleepWithProgressIndicator(RetryTimeInSeconds)

def SleepWithProgressIndicator(TimeInSeconds):
    device_log("\n")
    for i in range(TimeInSeconds):
        sys.stdout.write(".")
        sleep(1)
    device_log("\n")



def SetScreenTimeoutAndAirplaneMode(TimeInMinutes):
    TempTime = TimeInMinutes * 60 * 1000

    print "In SetScreenTimeoutAndAirplaneMode, calling TurnOnScreen()"
    TurnOnScreen()

    PrintConfigurePhone()


    ## Set the screen timeout
    #response = external_call('adb -s %s shell am start -a android.settings.DISPLAY_SETTINGS')
    #PressKey(KEYNAME['KEYCODE_BACK'],5)
    #response = external_call('adb -s %s shell am start -a android.settings.DISPLAY_SETTINGS')

    #PressKey(KEYNAME['KEYCODE_DPAD_DOWN'],3)
    #PressKey(KEYNAME['KEYCODE_DPAD_CENTER'])
    #PressKey(KEYNAME['KEYCODE_DPAD_DOWN'],5)## Gets us down to the cancel button
    #PressKey(KEYNAME['KEYCODE_DPAD_UP'],1)  ## Gets us up to MAX for this phone
    #PressKey(KEYNAME['KEYCODE_DPAD_CENTER'])
    #PressKey(KEYNAME['KEYCODE_BACK'],2)
    ## maybe go back to the top before hitting back key?

    ## http://developer.android.com/reference/android/provider/Settings.html
    response = external_call('adb -s %s shell settings get global airplane_mode_on' % ADB_DeviceID)
    m = re.search("0", response.strip() )
    if type(m) is not NoneType:
        device_log("Turning on AIRPLANE MODE")
        response = external_call('adb -s %s shell am start -a android.settings.AIRPLANE_MODE_SETTINGS' % ADB_DeviceID)

        PressKey(19)
        PressKey(23)
    else:
        device_log("Device is already in AIRPLANE MODE")

    NeedReboot = False
    device_log("Seeing if current screen timeout is %d minutes (which is %d milliseconds)" % (TimeInMinutes,TempTime))
    response = external_call('adb -s %s shell sqlite3 /data/data/com.android.providers.settings/databases/settings.db "select value from \'system\' where name = \'screen_off_timeout\';' % ADB_DeviceID)
    m = re.search("%d" % TempTime, response.strip() )
    if type(m) is NoneType:
        NeedReboot = True   ## To change a database value you must reboot
        device_log("Setting screen timeout to %d minutes, NOTE: Changing the database will REQUIRE A REBOOT" % TimeInMinutes)
        response = external_call('adb -s %s shell sqlite3 /data/data/com.android.providers.settings/databases/settings.db "update system set value=\'%d\' where name=\'screen_off_timeout\';"' % (ADB_DeviceID,TempTime))


    device_log("Here are the settings in use")
    # This below just shows settings in use
    response = external_call('adb -s %s shell sqlite3 /data/data/com.android.providers.settings/databases/settings.db "select name, value from \'system\'";' % ADB_DeviceID)


    device_log("\n\n")
    device_log("Screen timeout set to %d minutes, and airplane mode is on" % TimeInMinutes)

    NeedReboot = False       ## FORCE A REBOOT BEFORE EACH TEST

    if NeedReboot == True:
        RebootPhone()
        #PrintAdbReboot()
        #device_log("Rebooting device so changes take affect")
        #response = external_call('adb reboot')
        #SleepWithProgressIndicator(10)
        #WaitForDeviceWithPassFail()

        #device_log("After rebooting device can take time to be fully up for ADB, waiting")
        #SleepWithProgressIndicator(5)

MaxNumTurnOnScreenAttempts = 2
NumTurnOnScreenAttempts = 0


def TurnOnScreen():
    global KEYCODE, ScreenState
    if not KEYNAME: ## means dictionary is empty
        MapKeys()   ## loads the dictionary

    response = external_call('adb -s %s shell "dumpsys input_method | grep mScreenOn"' % ADB_DeviceID)
    m = re.search("mScreenOn=false", response)
    if type(m) is not NoneType:
        ScreenState = 0

    PrintScreenOn()

    if ScreenState == 0:
        ScreenState = 1 ## Means on
        PressKey(KEYNAME['KEYCODE_POWER']) ## 26
        PressKey(KEYNAME['KEYCODE_MENU'])  ## 82
        PressKey(KEYNAME['KEYCODE_HOME'])
    else:
        device_log("Screen is *already* on")

def TurnOffScreen():
    global KEYCODE, ScreenState
    PrintScreenOff()
    if not KEYNAME: ## means dictionary is empty
        MapKeys()   ## loads the dictionary


    response = external_call('adb -s %s shell "dumpsys input_method | grep mScreenOn"' % ADB_DeviceID)
    m = re.search("mScreenOn=true", response)
    if type(m) is not NoneType:
        ScreenState = 1

    if ScreenState==1:
        PressKey(KEYNAME['KEYCODE_ENDCALL'])  ## 6
    else:
        device_log("Screen is *already* off")

def MapKeys():
    global KEYCODE,KEYNAME
    KEYNAME = {}
    i = 0
    for key in KEYCODE:
        KEYNAME[ KEYCODE[i] ] = i
        i+=1

def PressKey(KeyCode, Repeat=1):
    device_log("\n")
    device_log("Pressing key %d (%s) %d time(s)" % (KeyCode,KEYCODE[KeyCode],Repeat))
    for i in range(Repeat):
        response = external_call('adb -s %s shell input keyevent %d' % (ADB_DeviceID,KeyCode))



def ReturnSizeString(size):
    if size>(1024*1024*1024):
        return "%.2f GB" % (size/(1024.0*1024.0*1024.0))
    elif size>(1024*1024):
        return "%.2f MB" % (size/(1024.0*1024.0))
    elif size>(1024):
        return "%.2f KB" % (size/(1024.0))
    else:
        return "%i B" % (size)


def find_file(filename,checkpwdfirst=False):
    tempsz = ""

    ## filename might already be a complete path
    if filename != os.path.basename(filename):
        ## user has provided a complete path already
        if os.path.exists(filename):
            return filename

    while True:
        device_log("\nLooking for '%s'  <--- LOOKING FOR THIS FILE (if it hangs, network is down or slow??)"%os.path.basename(filename))

        if checkpwdfirst==True:
            temp = os.path.join(os.getcwd(), filename)
            if os.path.exists(temp):
                device_log("**Found %s (%s)\n" % (temp,ReturnSizeString(os.path.getsize(temp))))
                return temp

        for x in search_paths:
            tempsz += "\t--> SEARCHING '%s'\n"%x
            temp = os.path.join(x, filename)
            device_log("calling os.path.exists(%s)" % temp)
            if os.path.exists(temp):
                device_log("**Found %s (%s)\n" % (temp,ReturnSizeString(os.path.getsize(temp))))
                return temp

        ## search cwd last
        tempsz += "\t--> SEARCHING CWD '%s'\n"%os.getcwd()
        if os.path.exists(filename):
            device_log("**Found %s (%s)\n" % (filename,ReturnSizeString(os.path.getsize(filename))))
            return filename

        device_log(tempsz)
        device_log("*** Couldn't find '%s' *** - Is it CASE SeNsItIvE?\n" % os.path.basename(filename))
        device_log("Try adding *more* search paths at the command line, i.e. --search_path=c:\\windows --search_path=c:\\temp\n")
        ReturnedFilename = PromptForPathAndUpdateSearchPaths()
        if len(ReturnedFilename)>0:
            ## To be here means user typed in a path
            ## and it exists, so look again
            continue

def PromptForPathAndUpdateSearchPaths():
    global search_paths

    device_log("Please provide a path for this file")
    device_log("Ex. \\\\somepath\\folder OR c:\\somepath\\folder\n")

    while True:
        temppath = raw_input("Enter PATH or Q to quit? ")
        if temppath=='Q' or temppath=='q' or temppath=='':
            device_log("EXITING - user pressed Q (quit)\n\n")
            ExitAndShowLogName(1)
        else:
            if not os.path.exists(temppath):
                device_log("The path '%s' doesn't exist\n\n" % temppath)
                continue

            ## To be this far, they provided something that exists

            if os.path.isfile(temppath):
                DirName = os.path.dirname(temppath) ## in case user did this c:\mypath\myfile.bin, I only want mypath
            else:
                DirName = temppath

            search_paths.append(DirName)
            return temppath


def ReturnDecimalTimeInMS(TimeString):
    m = re.search("(\d+):(\d+):(\d+)\.(\d+)", TimeString)
    if type(m) is not NoneType:
        H = int(m.group(1))
        M = int(m.group(2))
        S = int(m.group(3))
        MS= int(m.group(4))
        TimeInMS = H*60*60*1000 + M*60*1000 + S*1000 + MS
        return TimeInMS
    else:
        print "ERROR: Time string '%s' was not in the correct format" % TimeString
        ExitAndShowLogName(1)

def PrintAllIsWell():
    device_log("\t  ___  _ _   _                    _ _ ")
    device_log("\t / _ \\| | | (_)                  | | |")
    device_log("\t/ /_\\ \\ | |  _ ___  __      _____| | |")
    device_log("\t|  _  | | | | / __| \\ \\ /\\ / / _ \\ | |")
    device_log("\t| | | | | | | \\__ \\  \\ V  V /  __/ | |")
    device_log("\t\\_| |_/_|_| |_|___/   \\_/\\_/ \\___|_|_|\n")

def PrintFailed():
    device_log("\t _____         _    ______    _ _          _ ")
    device_log("\t|_   _|       | |   |  ___|  (_) |        | |")
    device_log("\t  | | ___  ___| |_  | |_ __ _ _| | ___  __| |")
    device_log("\t  | |/ _ \\/ __| __| |  _/ _` | | |/ _ \\/ _` |")
    device_log("\t  | |  __/\\__ \\ |_  | || (_| | | |  __/ (_| |")
    device_log("\t  \\_/\\___||___/\\__| \\_| \\__,_|_|_|\\___|\\__,_|\n")

def PrintPassed(About=""):
    if(len(About)>0):
        device_log(About)
    device_log("\t______                      _ ")
    device_log("\t| ___ \\                    | |")
    device_log("\t| |_/ /_ _ ___ ___  ___  __| |")
    device_log("\t|  __/ _` / __/ __|/ _ \\/ _` |")
    device_log("\t| | | (_| \\__ \\__ \\  __/ (_| |")
    device_log("\t\\_|  \\__,_|___/___/\\___|\\__,_|\n")

def PrintNoPassFail():
    device_log(" _   _        ______                 _______    _ _   _                                    _   ")
    device_log("| \\ | |       | ___ \\               / /  ___|  (_) | | |                                  | |  ")
    device_log("|  \\| | ___   | |_/ /_ _ ___ ___   / /| |_ __ _ _| | | |_ ___    _ __ ___ _ __   ___  _ __| |_ ")
    device_log("| . ` |/ _ \\  |  __/ _` / __/ __| / / |  _/ _` | | | | __/ _ \\  | '__/ _ \\ '_ \\ / _ \\| '__| __|")
    device_log("| |\\  | (_) | | | | (_| \\__ \\__ \\/ /  | || (_| | | | | || (_) | | | |  __/ |_) | (_) | |  | |_ ")
    device_log("\\_| \\_/\\___/  \\_|  \\__,_|___/___/_/   \\_| \\__,_|_|_|  \\__\\___/  |_|  \\___| .__/ \\___/|_|   \\__|")
    device_log("                                                                         | |                   ")
    device_log("                                                                         |_| \n")

def Print32bitSystem():
    device_log("  ____ ___    _     _ _      _____           _                 ")
    device_log(" |___ \\__ \\  | |   (_) |    / ____|         | |                ")
    device_log("   __) | ) | | |__  _| |_  | (___  _   _ ___| |_ ___ _ __ ___  ")
    device_log("  |__ < / /  | '_ \\| | __|  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ ")
    device_log("  ___) / /_  | |_) | | |_   ____) | |_| \\__ \\ ||  __/ | | | | |")
    device_log(" |____/____| |_.__/|_|\\__| |_____/ \\__, |___/\\__\\___|_| |_| |_|")
    device_log("                                    __/ |                      ")
    device_log("                                   |___/ \n")

def Print64bitSystem():
    device_log("    __ _  _     _     _ _      _____           _                 ")
    device_log("   / /| || |   | |   (_) |    / ____|         | |                ")
    device_log("  / /_| || |_  | |__  _| |_  | (___  _   _ ___| |_ ___ _ __ ___  ")
    device_log(" | '_ \\__   _| | '_ \\| | __|  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ ")
    device_log(" | (_) | | |   | |_) | | |_   ____) | |_| \\__ \\ ||  __/ | | | | |")
    device_log("  \\___/  |_|   |_.__/|_|\\__| |_____/ \\__, |___/\\__\\___|_| |_| |_|")
    device_log("                                      __/ |                      ")
    device_log("                                     |___/\n")

def PrintParseDmesg():
    device_log("______                            _                           ")
    device_log("| ___ \\                          | |                          ")
    device_log("| |_/ /_ _ _ __ ___  ___       __| |_ __ ___   ___  ___  __ _ ")
    device_log("|  __/ _` | '__/ __|/ _ \\     / _` | '_ ` _ \\ / _ \\/ __|/ _` |")
    device_log("| | | (_| | |  \\__ \\  __/    | (_| | | | | | |  __/\\__ \\ (_| |")
    device_log("\\_|  \\__,_|_|  |___/\\___|     \\__,_|_| |_| |_|\\___||___/\\__, |")
    device_log("                                                         __/ |")
    device_log("                                                        |___/\n")

def PrintParseLogcat():
    device_log("______                       _                       _   ")
    device_log("| ___ \\                     | |                     | |  ")
    device_log("| |_/ /_ _ _ __ ___  ___    | | ___   __ _  ___ __ _| |_ ")
    device_log("|  __/ _` | '__/ __|/ _ \\   | |/ _ \\ / _` |/ __/ _` | __|")
    device_log("| | | (_| | |  \\__ \\  __/   | | (_) | (_| | (_| (_| | |_ ")
    device_log("\\_|  \\__,_|_|  |___/\\___|   |_|\\___/ \\__, |\\___\\__,_|\\__|")
    device_log("                                      __/ |              ")
    device_log("                                     |___/\n")


def PrintError():
    device_log("\t _____                    ")
    device_log("\t|  ___|                   ")
    device_log("\t| |__ _ __ _ __ ___  _ __ ")
    device_log("\t|  __| '__| '__/ _ \\| '__|")
    device_log("\t| |__| |  | | | (_) | |   ")
    device_log("\t\\____/_|  |_|  \\___/|_| \n")

def PrintRemoveUSB():
    device_log("______                                _   _ ___________ ")
    device_log("| ___ \\                              | | | /  ___| ___ \\")
    device_log("| |_/ /___ _ __ ___   _____   _____  | | | \\ `--.| |_/ /")
    device_log("|    // _ \\ '_ ` _ \\ / _ \\ \\ / / _ \\ | | | |`--. \\ ___ \\")
    device_log("| |\\ \\  __/ | | | | | (_) \\ V /  __/ | |_| /\\__/ / |_/ /")
    device_log("\\_| \\_\\___|_| |_| |_|\\___/ \\_/ \\___|  \\___/\\____/\\____/\n")

def PlugInUSB():
    device_log("______ _               _         _   _ ___________ ")
    device_log("| ___ \\ |             (_)       | | | /  ___| ___ \\")
    device_log("| |_/ / |_   _  __ _   _ _ __   | | | \\ `--.| |_/ /")
    device_log("|  __/| | | | |/ _` | | | '_ \\  | | | |`--. \\ ___ \\")
    device_log("| |   | | |_| | (_| | | | | | | | |_| /\\__/ / |_/ /")
    device_log("\\_|   |_|\\__,_|\\__, | |_|_| |_|  \\___/\\____/\\____/ ")
    device_log("                __/ |                              ")
    device_log("               |___/                         \n")

def ParseDmesgLog(log_dmesg, DMesgRegEx):

    PrintParseDmesg()

    device_log("FILE: '%s'\n" % log_dmesg)

    try:
        Temp = open(log_dmesg, 'r')
    except Exception, x:
        PrintError()
        device_log("WARNING: could not open '%s'" % log_dmesg)
        device_log("REASON: %s" % x)
        ExitAndShowLogName(1,SHOWFAIL)
        
    Line = Temp.readlines()
    Temp.close()

    ReturnValue = 1 ## means all is well
    for i in range(len(Line)):
        for j in range(len(DMesgRegEx)):
            m = re.search(DMesgRegEx[j], Line[i])
            if type(m) is not NoneType:
                device_log(Line[i])
                ReturnValue = 0

    if ReturnValue == 1:
        device_log("Log looks good\n\n")

    return ReturnValue

def ParseLogcat(log_cat, LogcatRegEx):

    PrintParseLogcat()

    device_log("FILE: '%s'\n" % log_cat)

    Temp = open(log_cat, 'r')
    Line = Temp.readlines()
    Temp.close()


    ReturnValue = 1 ## means all is well
    for i in range(len(Line)):
        for j in range(len(LogcatRegEx)):
            m = re.search(LogcatRegEx[j], Line[i])
            if type(m) is not NoneType:
                device_log(Line[i])
                ReturnValue = 0

    if ReturnValue == 1:
        device_log("Log looks good\n\n")

    return ReturnValue

def CallKillApp(NameToGrepOn,PreciseMatch=False):
    global PIDarray

    for j in range(50):
        if GetPIDofRunningApp(NameToGrepOn,True,PreciseMatch)==0:   ## True means add to PIDArray
            ## to be here means no app was returned
            device_log("App is not running")
            return

        device_log("len(PIDarray)=%d" % len(PIDarray))
        for i in range(len(PIDarray)):

            ## To be this far there must be an entry in PIDarray. BUT, there could even be
            ## OLD entries in PIDarray, of apps that have already exited themselves
            ## Therefore don't want to confuse the user, only kill apps that the PID
            ## is still there

            if GetPIDofRunningApp(PIDarray[i])==0:   ## True means add to PIDArray
                ## to be here means no app was returned
                ##device_log("PID %s must have already exited" % PIDarray[i])
                continue    ## So try the next one

            PrintKillAPP()
            device_log("Attempting to kill PID %s (%s)" % (PIDarray[i],NameToGrepOn))
            response = external_call('adb -s %s shell kill %s' % (ADB_DeviceID,PIDarray[i]),True,True)
            sleep(3)

        ## Give a little time for it to die    
        SleepWithProgressIndicator(2)

        PIDarray = []   ## clear this

        if GetPIDofRunningApp(NameToGrepOn,True,PreciseMatch)==0:   ## True means add to PIDArray
            ## to be here means no app was returned
            device_log("App was killed successfully")
            return
        else:
            device_log("ERROR: App STILL LIVES (maybe it's still being closed?)")
            SleepWithProgressIndicator(5)

    ExitAndShowLogName()


def GetPIDofRunningApp(NameToGrepOn,AddToPIDarray=False,PreciseMatch=False):
    global PIDarray

    device_log("Seeing if '%s' is running" % NameToGrepOn)
    response = external_call('adb -s %s shell "ps | grep %s"' % (ADB_DeviceID,NameToGrepOn))

    ## Order is     USER     PID   PPID  VSIZE  RSS     WCHAN    PC         NAME
    ##              root      1     0     768    624   c026980c 0001a638 S /init
    ##              root      2     0     0      0     c01b2c00 00000000 S kthreadd
    ##              root      3     2     0      0     c019c00c 00000000 S ksoftirqd/0

    ReturnValue = 0     ## Means APP was *not* found, 1 means it was

    if len(response)==0:
        return 0    ## which is bogus

    NamePosition = 7

    if len(response)>0:
        temp=response.split('\n')
        for i in range(len(temp)):
            ## USER     PID   PPID  VSIZE  RSS     WCHAN    PC          NAME
            ## root     176   2     0      0       00239a94 00000000  S shm_svc'
            if len(temp[i])==0:
                break

            SplitArray = temp[i].split()    ## this naturally splits on whitespace

            if len(SplitArray)==0:
                break

            NamePosition = len(SplitArray)-1

            if PreciseMatch==True:
                ## To be here name must match exactly
                if len(SplitArray[NamePosition]) != len(NameToGrepOn):
                    continue    ## strings are not the same length, can't be an exact match
                if SplitArray[NamePosition] != NameToGrepOn:
                    continue    ## strings are not the same 

            ReturnValue = 1 ## Means app was found
            device_log("PID is %s (%s)" % (SplitArray[1],NameToGrepOn))

            NewPID = SplitArray[1]
            ## Only add this if we don't already have it
            GotIt = 0
            for ThisPID in PIDarray:
                if ThisPID == NewPID:
                    GotIt = 1
                    break
            if GotIt == 0:
                ##import pdb; pdb.set_trace()
                PIDarray.append(SplitArray[1])

    return ReturnValue

def CleanUpFilesCopiedToPhone():
    global FilesCopiedToPhone

    if len(FilesCopiedToPhone)==0:
        device_log("No files copied to the phone to be cleaned up")
    else:
        device_log("Cleaning up files copied to the phone")

    for File in FilesCopiedToPhone:
        response = external_call('adb -s %s shell rm %s' % (ADB_DeviceID,File) )

def CleanUpTempFilesCreated():
    global TempFilesCreated

    for File in TempFilesCreated:
        device_log("Removing temp file '%s'" % File)
        try:
            os.unlink(File) ## could be duplicate file names
        except:
            pass

def CopyFileToPhone(FileToCopy, PathToCopyTo="/data/"):
    global FilesCopiedToPhone

    temp = find_file(FileToCopy)

    ## make sure PathToCopyTo ends in a slash
    if PathToCopyTo[-1] != "/":
        PathToCopyTo += "/"

    response = external_call('adb -s %s push %s %s' % (ADB_DeviceID,temp,PathToCopyTo) ) ## send over the files
    FilesCopiedToPhone.append( os.path.join(PathToCopyTo, os.path.basename(temp)) )

    ## Did it copy?
    response = external_call('adb -s %s shell ls %s%s' % (ADB_DeviceID,PathToCopyTo,FileToCopy) ) ## send over the files

    CopiedSuccessfully = 1

    if len(response)==0:
        CopiedSuccessfully = 0
    else:
        m = re.search(FileToCopy, response.strip() )
        if type(m) is NoneType:
            CopiedSuccessfully = 0

    if CopiedSuccessfully==0:
        PrintError()
        device_log("ERROR: '%s' did not copy over to %s directory" % (FileToCopy,PathToCopyTo))
        ExitAndShowLogName(1,SHOWFAIL)
    else:
        device_log("Copied '%s' successfully to '%s'" % (FileToCopy,PathToCopyTo))



def InstallAPK(APKtoInstall,UninstallPackageName):
    global APKsInstalled


    temp = find_file(APKtoInstall)
    response = external_call('adb -s %s install %s' % (ADB_DeviceID,temp) ) ## send over the files

    m = re.search("INSTALL_FAILED_ALREADY_EXISTS|Success", response.strip() )
    if type(m) is NoneType:
        device_log("ERROR: Install of '%s' failed" % APKtoInstall)
        ExitAndShowLogName(1,SHOWFAIL)
    else:
        device_log("**SUCCESS: Install of '%s' succeeded or APK was already installed" % APKtoInstall)

    APKsInstalled.append(UninstallPackageName)

def CleanUpAPKsInstalled():
    global APKsInstalled

    for APK in APKsInstalled:
        response = external_call('adb -s %s uninstall %s' % (ADB_DeviceID,APK) )


def TestIfSystemIs64Bit():
    global SystemIs64Bit

    VoldFileName = "c:\\temp\\%s_vold" % ADB_DeviceID

    ## First copy to a safer directory like "Download", since on production builds you can get
    ## adb "cannot run as root in production builds" when you attempt "adb root"
    response = external_call('adb -s %s shell ls -l /system/bin/vold' % (ADB_DeviceID) )
    #response = external_call('adb -s %s shell cp /system/bin/vold /storage/sdcard0/Download/vold' % (ADB_DeviceID) )
    #response = external_call('adb -s %s shell ls -l /storage/sdcard0/Download/vold' % (ADB_DeviceID) )
    #response = external_call('adb -s %s pull /storage/sdcard0/Download/vold %s' % (ADB_DeviceID,VoldFileName) )
    response = external_call('adb -s %s pull /system/bin/vold %s' % (ADB_DeviceID,VoldFileName) )

    ## Now we have c:\temp\vold, look at the 4th byte
    try:
        vold_fp = open(VoldFileName, 'rb')
    except Exception, x:
        device_log("WARNING: could not open '%s' - You must use --systemis64bit=0|1 option" % VoldFileName)
        device_log("REASON: %s" % x)
        return  ## not a fatel error

    bytes_read = vold_fp.read(5)    ## Need 5 bytes
    Bytes = struct.unpack("%dB" % 5,bytes_read)    ## unpack returns list, so get index 0

    try:
        vold_fp.close()
    except:
        device_log("\tWARNING: Can't close '%s'?" % VoldFileName)
        pass

    if Bytes[4] == 2:
        device_log("SYSTEM IS 64bit")
        Print64bitSystem()
        SystemIs64Bit = 1
    elif Bytes[4] == 1:
        Print32bitSystem()
        device_log("SYSTEM IS 32bit")
        SystemIs64Bit = 0
    else:
        device_log("I can't tell if the SYSTEM is 32 or 64 bit. The 5th byte of the ELF was %d and I only expected a 1 or 2" % Bytes[4])


def ReturnElapsedFrom(FromTime):
    elapsed = time.time() - FromTime
    if elapsed==0:
        return 0.00001
    else:
        return elapsed

def ReturnElapsedFromStartEnd(Start,End):
    elapsed = End - Start
    if elapsed==0 or elapsed<0:
        return 0.00001
    else:
        return elapsed


def RebootPhone():
    global ADB_DeviceID

    DeviceNotFound      = 0
    NoResponse          = 0

    MaxNoResponse       = 50
    MaxDeviceNotFound   = 20

##adb shell getprop | grep "bootcomplete"
##error: device not found
##adb shell getprop | grep "bootcomplete"
##
##adb shell getprop | grep "bootcomplete"
##
##adb shell getprop | grep "bootcomplete"
##
##adb shell getprop | grep "bootcomplete"
##[dev.bootcomplete]: [1]

    PrintAdbReboot()
    device_log("Rebooting device")

    if ADB_DeviceID != None:
        response = external_call('adb -s %s reboot' % ADB_DeviceID)
    else:
        response = external_call('adb reboot')

    SleepWithProgressIndicator(25)
    WaitForDeviceWithPassFail()

    while True:
        sleep(5)
        response = external_call('adb -s %s shell "getprop | grep bootcomplete"' % ADB_DeviceID)
        if len(response)==0:
            NoResponse+=1
            device_log("NoResponse %d attempts of %d" % (NoResponse,MaxNoResponse))
            if NoResponse>=MaxNoResponse:
                ExitAndShowLogName(1,0) ## return 1, 0 means FAIL
        else:
            m = re.search("device not found", response)
            if type(m) is not NoneType:
                DeviceNotFound+=1
                device_log("DeviceNotFound %d attempts of %d" % (DeviceNotFound,MaxDeviceNotFound))

            if DeviceNotFound>=MaxDeviceNotFound:
                ExitAndShowLogName(1,0) ## return 1, 0 means FAIL

            m = re.search("bootcomplete", response)
            if type(m) is not NoneType:
                device_log("ANDROID IS UP! Giving the UI 15 more seconds")
                SleepWithProgressIndicator(15)
                break   ## SUCCESS


def WaitForDeviceWithPassFail(NumAttempts=100):
    global ADB_DeviceID
## adb devices
## List of devices attached
##  (this is empty)

## adb devices
## List of devices attached
## 684abc6b        device

    ##if ADB_DeviceID != None:
    ##    return ADB_DeviceID

    Attempt = 0
    while True:
        sleep(3)
        response = external_call('adb devices')
        if len(response)==0:
            PrintError()
            device_log("Looks like ADB is *not* installed, there was no response")
            ExitAndShowLogName(1,SHOWFAIL)
        else:
            #m = re.search("device", response)
            #if type(m) is not NoneType:
            #    break
            ##import pdb; pdb.set_trace()

            m = re.findall("([\da-f]+)\t+device", response.strip())
            if len(m)>0:
                for Temp_ADB_DeviceID in m:
                    device_log("Device attached is '%s'" % Temp_ADB_DeviceID)
                    if ADB_DeviceID is None:
                        DeviceIsInADBmode   = True
                        ADB_DeviceID = Temp_ADB_DeviceID
                        return Temp_ADB_DeviceID
                    elif Temp_ADB_DeviceID == ADB_DeviceID:
                        DeviceIsInADBmode   = True
                        return Temp_ADB_DeviceID

            elif "not recognized as an internal or external command" in response:
                device_log("Looks like ADB is *not* installed")
                ExitAndShowLogName(1)

        device_log("")
        ## to be this far, no device attached
        if ADB_DeviceID is None:
            device_log("** NO DEVICES ATTACHED (attempt %d of %d) **\n" % (Attempt,NumAttempts))
        else:
            device_log("** USER SPECIFIED --deviceid=%s IS NOT ATTACHED (attempt %d of %d) **\n" % (ADB_DeviceID,Attempt,NumAttempts))

        Attempt += 1
        device_log("Attempt %d of %d" % (Attempt,NumAttempts))

        if Attempt>=NumAttempts:
            PrintFailed()
            sys.exit(0) ## No phone attached, can't do clean up in this case. Can only bail

def CreateBinaryFile(Filename,FileSizeInMB,TakeCRC):
    global TempFilesCreated
    CreatedFileCRC = 0
    try:
        big_fp = open(Filename, 'wb')
    except Exception, x:
        print "ERROR: could not create '%s'" % Filename
        print "REASON: %s" % x
        ExitAndShowLogName(1)
    device_log("Creating %d MB size file" % FileSizeInMB)
    for j in range(FileSizeInMB):
        if j % 100:
            sys.stdout.write(".")        
        for i in range(1024):
            sz = "%s" % (i%10)
            buffer_string = sz*1024
            if TakeCRC==1:
                CreatedFileCRC = zlib.crc32(buffer_string,CreatedFileCRC)
            big_fp.write(buffer_string)
    big_fp.close()
    TempFilesCreated.append(Filename)
    device_log("Created temp file '%s" % Filename)
    return CreatedFileCRC

def CreateTempBinaryFileOnPhone(Filename,FileSizeInMB):
    response = external_call('adb -s %s shell dd if=/dev/zero of=/data/%s bs=1048576 count=%d' % (ADB_DeviceID,Filename,FileSizeInMB) )
    FilesCopiedToPhone.append( os.path.join("/data/",Filename ))

def FillDataPartitionWithTempFiles(SizeInMB):
    ## Now to fill the file system, 
    for Size in range(50,SizeInMB,50):
        #if Size<=50:
        #    CRC = CreateBinaryFile("BigFile%d.bin" % Size,Size,0)   ## 0 means don't calculate a CRC on the file
        #else:
        #    CRC = CreateBinaryFile("BigFile%d.bin" % Size,50,0)   ## 0 means don't calculate a CRC on the file
        #CopyFileToPhone("BigFile%d.bin" % Size)
        if Size<50:
            TempSize = Size
        else:
            TempSize = 50

        CreateTempBinaryFileOnPhone("BigFile%d.bin" % Size,TempSize)
        #response = external_call('adb -s %s shell dd if=/dev/zero of=/data/BigFile%d.bin bs=1024 count=%d' % (memutil.ADB_DeviceID,Size,TempSize) )
        #device_log('adb -s %s shell dd if=/dev/zero of=/data/BigFile%d.bin bs=1024 count=%d' % (memutil.ADB_DeviceID,Size,TempSize) )

def MutePhone():
    device_log("Muting the phone by pressing the VOLUME DOWN key")
    for i in range(25):
        PressKey(KEYNAME['KEYCODE_VOLUME_DOWN'])



def CanWeSwitchClocks():
    global CanSwitchClocks
## adb shell cat /d/rpm_send_msg/enable
## /system/bin/sh: cat: /d/rpm_send_msg/enable: No such file or directory
## OR
## adb shell cat /d/rpm_send_msg/enable
## 1

    CanSwitchClocks = True  ## HACK
    return True             ## HACK

    response = external_call('adb -s %s shell cat /d/rpm_send_msg/enable' % (ADB_DeviceID) )
    if len(response)==0:
        CanSwitchClocks = False
        return False

    ## To be this far there was a response

    m = re.search("No such file or directory", response.strip())
    if type(m) is not NoneType:
        CanSwitchClocks = False
        return False

    CanSwitchClocks = True
    return True

def ShowClockRate():

    if CanSwitchClocks and AllowClockSwitching:
        device_log("Querying clock rate. NOTE: On many targets *scaling* of the number below is needed")
        response = external_call('adb -s %s shell cat /d/clk/bimc_clk/measure' % (ADB_DeviceID) )


def WriteDMESG(sz):
    if len(sz)==0:
        return

    if RunningAsRoot == False:
        return  ## Below won't succeed unless we are running as root
 
    sz = "MEMUTIL: " + sz.replace('\\','\\\\')

    #if "NOTE: use --outputdir" in sz:
    #    import pdb; pdb.set_trace()

    #if "Aaron was here in tiotest" in sz:
    #    import pdb; pdb.set_trace()

    #print '********** Calling: adb -s %s shell "echo \'%s\' > /dev/kmsg"' % (ADB_DeviceID,sz)

    response = external_call('adb -s %s shell "echo \'%s\' > /dev/kmsg"' % (ADB_DeviceID,sz), False, False ) 
    
def WriteLogcat(sz):
    if len(sz)==0:
        return

    if RunningAsRoot == False:
        return  ## Below won't succeed unless we are running as root

    sz = sz.replace('\\','\\\\')

    response = external_call('adb -s %s shell log -t MEMUTIL \'%s\'' % (ADB_DeviceID,sz), False, False ) 


