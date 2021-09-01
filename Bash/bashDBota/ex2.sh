#!/bin/bash

if [ ! -d $1 ]; then
	echo "Param is not a directory"
	exit 1
fi
for f in `ls $1`; do 
	if `file $1/$f | grep -E -q "text"`; then
		
		echo `cat $1/$f | head -n 3`
	fi	
done	
