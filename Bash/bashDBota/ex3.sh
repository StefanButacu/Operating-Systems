#!/bin/bash
if [ ! $# -eq 1 ]; then
	echo "invalid nr "
	exit 1
fi
if [ ! -d $1 ];then
	echo "invalid type"
	exit 1
fi

for f in `ls $1`; do
	echo `file $1/$f`
	if `file $1/$f | grep -E -q "text" `; then
		LiniiF=`cat $f | awk 'END {print NR}'`
	       	NrLines=`expr $NrLines + $LiniiF`
		NrFiles=`expr $NrFiles + 1`
		echo "$f -> $NrLines"
	fi
done
if [[ ! $NrFiles -eq 0 ]]; then
       	echo " $NrLines / $NrFiles"	
	echo $((NrLines/NrFiles))
else
	echo "Invalid nr of files"
fi

