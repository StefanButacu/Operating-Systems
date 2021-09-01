#!/bin/bash
S=0
for f in $1/*.c; do
	 N=`grep –E "[^ \t]" $f | wc -l`
	  S=`expr $S + $N`
	   done
	  echo $S
