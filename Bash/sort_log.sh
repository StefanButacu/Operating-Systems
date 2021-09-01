#!/bin/bash
if [ ! $# -eq 1 ]; then
	echo "Invalid nr of params"
	exit 1
fi
if [ ! -d $1 ]; then
	echo "Invalid type of param"
	exit 1
fi

for F in `find "$1" -name "*.log"`; do
	CopyFile=`cat $F | sort`
        echo $CopyFile

	echo $CopyFile > "F2"
	
#	`rm $F`
#	`mv "$F2" "$F"`	
done
