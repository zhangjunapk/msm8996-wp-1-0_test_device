#!/system/bin/sh

STARTTIME=$(date +%s)

bimc_freq_switch() {
	##echo "bimc scaling freq: " ${FREQ_LIST}

	## don't turn off thermal-engine, otherwise thermal reset will be triggered easily. #stop thermal-engine
	for REQ_KHZ in ${FREQ_LIST}; do 
		echo 1 > /d/msm-bus-dbg/shell-client/mas
		echo 512 > /d/msm-bus-dbg/shell-client/slv
		echo "active clk2 0 1 max ${REQ_KHZ}" 
		echo "active clk2 0 1 max ${REQ_KHZ}" > /d/rpm_send_msg/message
		## vote for a extra large freq value
		echo $((8000*900000)) > /d/msm-bus-dbg/shell-client/ib
		echo 1 > /d/msm-bus-dbg/shell-client/update_request

#		CUR_BIMC_FREQ=$(< /d/clk/bimc_clk/rate)
#		CUR_BIMC_FREQ=$((CUR_BIMC_FREQ/1000))
		echo "BIMC req_freq: ${REQ_KHZ}"
                log -t MEMUTIL "BIMC req_freq: ${REQ_KHZ}"
 		#cat /d/clk/bimc_clk/measure
                #cat /d/clk/bimc_clk/rate
		ENDTIME=$(date +%s)
		DTIME=$(($ENDTIME - $STARTTIME))
		SECONDS=$((DTIME % 60))
		MINUTES=$(((DTIME / 60) % 60))
		HOURS=$((DTIME / 3600))
		# echo "TIME SINCE TEST STARTED: $HOURS HOURS $MINUTES MINUTES : $SECONDS : SECONDS "
		echo ""
		echo "TIME SINCE BIMC CLOCK SWITCH STARTED: $HOURS : $MINUTES : $SECONDS" # (HH:MM:SS)		
		sleep 3
	done

}

loop_bimc_freq_switch() {
	while [ 1 ] ; do
	  bimc_freq_switch
	done
}

random_bimc_freq_switch() {
   # Seed random generator
   RANDOM=$$$(date +%s)
   # randomly select the frequency from the list 
   FREQ_LIST=${bimc_scaling_freq_list[$RANDOM % ${#bimc_scaling_freq_list[@]}]}
   bimc_freq_switch
}

loop_random_bimc_freq_switch() {
	while [ 1 ] ; do
	  random_bimc_freq_switch
	done
}


## entry ###

## get the scaling frequency list from the debugfs
opt=$1

## opt: -d 	: display the scaling frequency list
if [ "$opt" = "-d" ]; then
	echo "bimc cur_freq: " $(< /d/clk/bimc_clk/measure)
	exit
fi
	
shift
bimc_scaling_freq_string="100000 150000 200000 300000 451200 547200 681600 768000 1017600 1296000 1555200 1804000"
#bimc_scaling_freq_string=$@
#shift
bimc_scaling_freq_list=(${bimc_scaling_freq_string// / })

echo 0xdeadbeef > /d/rpm_send_msg/enable

if [ "$opt" = "-h" ]; then
	echo "sh <path>/bimc_clock.sh [-h] [-d] [-r] [-l] [-f <freq_list>] "
	exit

## randomly pick one freq from  scaling_available_frequencies
elif [ "$opt" = "-r" ]; then
	random_bimc_freq_switch

elif [ "$opt" = "-l" ]; then
	loop_random_bimc_freq_switch

## switch to a specific frequency (or through frequency list) 
elif [ "$opt" = "-f" ]; then
	FREQ_LIST=$bimc_scaling_freq_string
	loop_bimc_freq_switch
fi






