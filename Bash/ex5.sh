#!/bin/bash
# un script care extrage bibliotecile din fisiere C si le salveaza in alt fisier 

for X in $@; do  # iterez prin argumente
	if [ ${X: -2} == ".c" ]; then # verifica daca ultimile 2 caractere sunt ".c"
		echo `grep -E "^(#include).*" $X | awk '{print $2}'` >> biblioteci.txt  # presupun ca e #include(spatiu)<biblioteca>
      		echo "fisier c"
	fi
done

