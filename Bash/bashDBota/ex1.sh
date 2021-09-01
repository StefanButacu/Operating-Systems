#!/bin/bash
# script care primeste ca arg un nr N si genereaa N fisier text
#numele fisierului e de forma file_X.txt, X = {1,2,..n}
# fiecare fisier va contine liniile de la X la X+5 ale fis passwd.fake

if [ ! $# -eq 1 ]; then
	echo "Invalid nr of params"
	exit 1
fi

if echo $1 | grep -E -q "^[0-9]+$"; then
	echo "Is ok"
else
		echo "not ok"
		exit 1
fi
i=1
N=$1
N=`expr $N + 1 `
while [ $i -lt $N ]; do
	numeFis="file_"
	numeFis+="$i"
	numeFis+=".txt"	
	Content=`cat passwd.fake| awk -F: '{if(NR >= "'$i'" && NR <= "'$i'" + 5) {print $0"-"NR}  }'`	
	echo $Content, "\n"  # > $numeFis 
	echo $numeFis
	i=`expr $i + 1`

done
