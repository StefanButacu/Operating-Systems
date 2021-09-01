#!/bin/bash

declare -A dimensiuni

for X in $@; do
	if [ -f $X ]; then
		N=`ls -l $X | awk '{print $5}' # ii iau dimensiunea fisierului`
		dimensiuni[$X]=$N
	fi
done
for key in ${!dimensiuni[@]}; do
	echo $key '-' ${dimensiuni["$key"]}
done | sort -rn -k3  #sorteaza outputul forului dupa al 3 lea camp ( dimensiunea) 

