#!/bin/bash
# media id-urilor proceselor din sistem pentru fiecare utilizator
declare -A pid
declare -A frecv
for X in `ps -ef | tail -n +2 | awk '{print $1 ":" $2}'`;do # iau numele si pidul
        U=`echo $X| cut -d: -f1`
	P=`echo $X| cut -d: -f2`
        #echo $U $P
	pid[$U]=`expr ${pid[$U]} + $P`
	frecv[$U]=`expr ${frecv[$U]} + 1`
done
for key in ${!pid[@]}; do
	echo $key "-" $((pid[$key] /frecv[$key]))
done
