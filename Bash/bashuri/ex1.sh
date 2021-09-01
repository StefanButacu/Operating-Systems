#!/bin/bash
# Suma in octeti a tuturor fisierelor regulare dintr un director dat ca arg
S=0
if [ -d $1 ]; then
	echo "Sunt in fisier $1"
	for F in `find $1 -type f -name "*.*"`; do # for F in `ls -a "$1"`q:
		N=`ls -l $F | awk '{print $5}'`
		S=`expr $S + $N`
	done
fi
echo "Am gasit $S octeti"
