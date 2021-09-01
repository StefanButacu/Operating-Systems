#!/bin/bash

if [ $# -lt 3 ]; then
	echo "Invalid nr of params"
	exit 1
fi

while [ $# -gt 0 ]; do
	name=$1
	word=$2
	k=$3
	shift 3
	echo "$name - $word - $k"
	ans=`awk -v ap="$k" -v cuv="$word" '{nr=0;for(i = 1; i <=NF; i++) {if($i==cuv) nr++};if(nr==ap) prinf $0;printf "\n"}' $name`
	echo $ans

done
