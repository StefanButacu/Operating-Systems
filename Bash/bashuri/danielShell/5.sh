#!/bin/bash
# pentru fiecare param de la linia de comanda
# daca e fisier se afiseaza nume nr de caracterii si de linii
# daca e director se afiseaza numele si cate fisiere contine 
if [ $# -lt 1 ]; then
	echo "invalid nr of param"
	exit 1
fi
for name in $@; do
	if [ -f $name ]; then
		nrC=`du -b $name | cut -f1`
		nrL=`wc -l $name`
		echo "Fisierul $name: $nrC caractere $nrL linii"
	fi
	if [ -d $name ]; then
		i=0
		for f in `find $name`; do
			i=$(($i+1))
		done
		echo "Directorul $name are $i fisiere"
	fi
done

