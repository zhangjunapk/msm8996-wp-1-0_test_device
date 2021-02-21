#!/system/bin/sh
Iterations=$1
suspendtime=$2
resumetime=$3

if [ -z $Iterations ]; then Iterations=2 ; fi;
if [ -z $suspendtime ]; then suspendtime=4000; fi; #4sec
if [ -z $resumetime ]; then resumetime=4000; fi; #4sec


echo 'Giving phone 2 minutes before this script begins'
echo 'Sleep for 10'
sleep 10
echo 'Sleep for 10'
sleep 10
echo 'Sleep for 10'
sleep 10
echo 'Sleep for 10'
sleep 10
echo 'Sleep for 10'
sleep 10
echo 'Sleep for 10'
sleep 10

echo 'Giving phone 2 minutes before this script begins'
echo 'Sleep for 10'
sleep 10
echo 'Sleep for 10'
sleep 10
echo 'Sleep for 10'
sleep 10
echo 'Sleep for 10'
sleep 10
echo 'Sleep for 10'
sleep 10
echo 'Sleep for 10'
sleep 10


#waitAmount=$(($suspendtime+$resumetime+1000))
#waitAmount=$((waitAmount/1000))
echo "Iterations=$Iterations"
echo "suspendtime=$suspendtime"
echo "resumetime=$resumetime"

log -t MEMUTIL 'SH: **************************************'
log -t MEMUTIL 'SH: **************************************'
log -t MEMUTIL 'SH: SuspendResumeWrite.sh test is starting'

log -t MEMUTIL 'SH: 'rm /data/test/*
log -t MEMUTIL 'SH: '$(rm /data/test/*)

a='/data/' ## not /data/test since this is where I copy it to during testing, and it will be deleted each time
testfile='xlargeFile.txt'
testfileWithPath=$a$testfile
echo $testfileWithPath
mkdir -p /data/test     ## -p means if it exists

log -t MEMUTIL 'SH: Suspend Resume Test for Storage'

if [ -f $testfileWithPath ];
then
    echo "File $testfileWithPath exists."
else
    echo "File $testfileWithPath does not exist."
    echo "dd if=/dev/zero of=$testfileWithPath bs=1024 count=1024"
    dd if=/dev/zero of=$testfileWithPath bs=1024 count=1024

    if [ -f $testfileWithPath ];
    then
       echo "File $testfileWithPath exists."
    else
       echo "File $testfileWithPath does not exist. And I could not create it"
       exit 0
    fi
fi


#echo 8 > /proc/sys/kernel/printk #For capturing the complete Dump
log -t MEMUTIL 'SH: echo Y > /sys/module/printk/parameters/ignore_loglevel'
echo Y > /sys/module/printk/parameters/ignore_loglevel

#----------------------------------------------------------------------------------------------------------
# Main Section of the script
#----------------------------------------------------------------------------------------------------------
log -t MEMUTIL 'SH: Reset Suspend counter before running test'
log -t MEMUTIL 'SH: echo reset > /d/lpm_stats/suspend'
echo reset > /d/lpm_stats/suspend

num=1;
while [ $num -le $Iterations ]
do

        echo '   '
        echo '   '
	log -t MEMUTIL 'SH: =========Launching LowPowerStateTest.apk for '$num' iteraion of '$Iterations' iterations====='
        echo 'SH: =========Launching LowPowerStateTest.apk for '$num' Iteraion of '$Iterations' iterations====='
        echo 'SH: =========Launching LowPowerStateTest.apk for '$num' Iteraion of '$Iterations' iterations=====' >> /data/test/log.txt
	log -t MEMUTIL 'SH: 'cp $testfileWithPath /data/test/$testfile
        echo 'SH: cp '$testfileWithPath' /data/test/'$testfile >> /data/test/log.txt
	cp $testfileWithPath /data/test/$testfile
        #echo "BEGIN - Iterations=$Iterations suspendtime=$suspendtime resumetime=$resumetime" > /data/test/begin$num.txt
		
	input keyevent 82
        am start -n com.android.doualarmtest/.DOUAlarmTest -e suspendtime $suspendtime -e resumetime $resumetime -e iterations 1

        echo 'DOUAlarmTest started, sleep 8 - to give it time to start'
	sleep 8
        echo 'back from sleep'

        #waitAmount=$(($suspendtime+$resumetime+8000))
        #waitAmount=$((waitAmount/1000))
        #echo "Sleep for $waitAmount seconds total"

        waitAmount=$(($resumetime))
        waitAmount=$((waitAmount/1000))
        echo "Sleep for RESUME TIME: $waitAmount seconds"
        sleep $waitAmount

        waitAmount=$(($suspendtime))
        waitAmount=$((waitAmount/1000))
        echo "Sleep for SUSPEND TIME: $waitAmount seconds"
        sleep $waitAmount

        echo "Sleep for another $waitAmount seconds, just to give padding"
        sleep $waitAmount
        #echo "back from sleep"

	log -t MEMUTIL 'SH: 'sleep $waitAmount
        echo 'SH: sleep '$waitAmount >> /data/test/log.txt
	#sleep $waitAmount
        echo 'back from sleep'
        echo 'back from sleep' >> /data/test/log.txt

        sleep 1
        log -t MEMUTIL 'SH: Stop SuspendTest.apk'
        echo 'SH: Stop SuspendTest.apk'
        echo 'SH: Stop SuspendTest.apk' >> /data/test/log.txt
	am force-stop com.android.doualarmtest
        log -t MEMUTIL 'SH: 'sleep 3
        echo 'SH: sleep 3' >> /data/test/log.txt
        echo 'SH: sleep 3'
	sleep 3
        echo 'back from sleep'
        echo 'back from sleep' >> /data/test/log.txt

	#echo "Read back datafile_$num from /data/test/datafile_$num bs=1024k count=100 flush=1 sync=0" >> $DeviceLogPath
	#/data/test/lmdd if=/data/test/datafile_$num of=/data/test/fileread_$num bs=1024k flush=1 sync=0
	#ReadFileSize=`du -h datafile_$num`
	echo "read back $testfile after resume now"
	log -t MEMUTIL 'SH: read back '$testfile' after resume now'
        echo 'SH: read back '$testfile' after resume now' >> /data/test/log.txt

        log -t MEMUTIL 'SH: 'cp /data/test/$testfile /data/test/readback
        echo 'SH: cp /data/test/'$testfile' /data/test/readback' >> /data/test/log.txt
        echo 'SH: cp /data/test/'$testfile' /data/test/readback'
	cp /data/test/$testfile /data/test/readback
	echo "Compare $testfileWithPath to /data/test/readback"
        log -t MEMUTIL 'SH: 'cmp $testfileWithPath /data/test/readback
        echo 'SH: cmp $testfileWithPath /data/test/'readback >> /data/test/log.txt
        log -t MEMUTIL 'SH: '$(cmp $testfileWithPath /data/test/readback)
        echo 'COMPARE DONE HERE - SHOULD BE BLANK AFTER THIS-----> '$(cmp $testfileWithPath /data/test/readback) >> /data/test/log.txt
        echo ' '
        echo 'COMPARE DONE HERE ------> '$(cmp $testfileWithPath /data/test/readback)'    <--- Should be NOTHING between arrows'
        echo ' '
        ##echo 'SH: '$(cmp /data/test/$testfile$num /data/test/done.txt) >> /data/test/log.txt
        ##echo 'SH: '$(cmp /data/test/kitty.exe /data/test/run_qblizzard.sh) >> /data/test/log.txt
        #echo "END - Total Iterations=$Iterations suspendtime=$suspendtime resumetime=$resumetime" > /data/test/end$num.txt
        echo "END - Total Iterations=$Iterations suspendtime=$suspendtime resumetime=$resumetime"
        ##log -t MEMUTIL 'SH: '$(cmp /data/test/xlargeFile.txt1 /data/test/SuspendResumeCompare.txt)    ## for testing only that differ appears
        
        echo "Remove the files, showing contents of /data/test/"
        rm /data/test/readback
        rm /data/test/$testfile
        ls /data/test


	##num=`/data/test/busybox expr $num + 1`	
        num=$(($num+1))

done

echo '   '
echo '   '

getLPMStats=`cat /d/lpm_stats/suspend`
log -t MEMUTIL 'SH: 'cat /d/lpm_stats/suspend
log -t MEMUTIL 'SH: '$(cat /d/lpm_stats/suspend)
##log -t MEMUTIL 'SH: 'rm /data/test/*
##log -t MEMUTIL 'SH: '$(rm /data/test/*)

log -t MEMUTIL 'SH: SuspendResume test is completed'
echo "DONE - Iterations=$Iterations suspendtime=$suspendtime resumetime=$resumetime" > /data/test/DONE.txt
ls -l /data/test/

#reboot