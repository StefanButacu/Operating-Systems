#!/bin/bash

if [ ! $# -eq 1 ]; then 
	echo "Numar gresit de parametrii"
	exit 1
fi

if [ ! -d "$1" ]; then 
	echo "Nu este un director"
	exit 1
fi
NrFiles=0
for file in `find "$1" -name "*.c"`; do
	NrLines=`wc -l $file | awk '{print $1}'`
	if [ $NrLines -gt 500 ]; then
		NrFiles=`expr $NrFiles + 1`
		echo $file
	fi
	if [ $NrFiles -eq 2 ]; then
		exit 0
	fi
done

