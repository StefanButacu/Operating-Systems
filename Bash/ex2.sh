#!/bin/bash
# Scrieti un script shell care citeste nume de fisiere pana se introduce cuvantul stop 
# pentru fiecare fisier, verificati daca acesta este un fisier text, iar daca da afisati nr de cuvinte de pe
# prima linie
while true; do
	read X
	if test "$X" == "stop"; then
		break
	fi
	if test -f $X ; then
		N=`cat $X | head -1 | awk '{print NF}'`
		echo $N
	fi
done
