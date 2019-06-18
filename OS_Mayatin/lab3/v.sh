#!/bin/bash
#-h no-filename
#-s without error
#-i ignore case

status=""
for pid in $(ps -e -o pid| tail -n +2)
do
	f="/proc/"$pid
	ppid=$(grep -E -h -s -i "ppid:\s+(.+)" $f"/status" | grep -o "[0-9]\+")
	sleepavg=$(grep -E -h -s -i "se.avg.util_sum(.+):\s+(.+)" $f/sched | grep -o "[0-9]\+")	
	if [ -z $ppid ]
	then
		ppid=0;
	fi
	if [ -z $sleepavg ]
	then
		sleepavg=0
	fi
	echo "ProcessID="$pid" : Parent_ProcessID="$ppid" : Average_sleeping_Time="$sleepavg
done |
sort -t " " -k 3 > out5.txt
