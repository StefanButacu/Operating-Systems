#!/bin/bash
# Se dau perechi de nume fisier si cuvinte. Sa se afiseaza daca cuvantul apare de cel putin 3 ori


while [ $# -gt 0 ]; do
	Fisier=$1
	shift
	Word=$1
	shift # am scapat de 2 argumetente
	nr=0
	for cuv in $(cat $Fisier); do
	       if [ $Word = $cuv ]; then
	       	 	nr=$((nr+1))
  		fi
	done
	if [ $nr -ge 3 ]; then
		echo "Cuvantul $Word apare de cel putin 3 ori in $Fisier"
	fi
done	
	
