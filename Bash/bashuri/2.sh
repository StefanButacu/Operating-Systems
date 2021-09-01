#!/bin/bash
# Write a script that recives as command line arguments pairs consiting of a filename and a word. For each pair
# check if the given word appears at leas 3 times in the file and print the correspoinding message

	read File
	read Word 
	#N=`grep -E -c "^$Word$" $File`
	i=1
	N=`awk '{for $i in $0 { $i ~ /^$Word$/ {print $i} } }' $File` 
	echo $N
	if [ $N -gt 2 ]; then
	       echo "Am gasit mai mult de 3 aparitii"
	fi	
