#!/bin/bash
for X in `cat ../passwd | awk -F: '{print $1}'`; do
	Ip=`cat ../last.fake | grep -E "$X"`
	echo $Ip > $X.txt

done
