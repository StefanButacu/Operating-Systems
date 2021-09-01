#!/bin/bash
if [ $# -lt 1 ]; then
	echo "invalid nr of params"
	exit 1
fi

for file in $@; do
	if [ -f $file ]; then
		echo `sort -r $file | uniq -c | sort -nr | head -n1 | awk '{print $2}'`
	fi
	

done
read P
echo $P
