#!/bin/bash

echo $0
:
if [ $# -lt 1 ]; then
	echo "invalid nr of params"
	exit 1
fi

for dir in $@; do 
	if [ -d $dir ]; then
		for file in `find -perm -755`; do
			echo "Vreti sa schimbati permisiunea Y/N?"
			read p
			if [ "$p" == "Y" ]; then
				chmod 744 $file
			fi
		done	
	
	else echo "$dir nu e director"
	
	fi
done
