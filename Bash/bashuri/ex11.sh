#!/bin/bash
# primeste un director si sterge toate fisierle .c si afiseaza celelallte fisiere sortate

if [ ! -d $1 ]; then
	echo "Nu mi ai dat un director"
	exit 1
fi

for F in `find $1 -type f`;do
	Tip=`file $F`
#	echo $F '-' $Tip
	if [[ "$Tip" == *"C source"* ]]; then # exit codul lui grep va fi 1 daca gaseste C source 
		`rm $F` 
		echo "Am sters fisierul $F"
	else 
		echo $F >> notC.txt # appenduiesc numele fisireului in unul text dupa care il sortez si afisez
	fi
done
echo `cat notC.txt | sort | less `
`rm notC.txt` # fac curatenie dupa mine
