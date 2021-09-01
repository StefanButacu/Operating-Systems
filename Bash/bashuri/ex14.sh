#!/bin/bash

declare -A cuvinte  # dictionar in care salvez cuvintele 

for i in $@; do
	cuvinte[$i]=0
done
for key in ${!cuvinte[@]}; do
	echo $key "-" ${cuvinte[$key]}
done
# initializez frecventa fiecarui cuvant la 0
while true; do #citesc fisiere la nesfasrist
	read X
	if [ -f $X ]; then
		for cuv in $(cat $X); do # iau fiecare cuvant din fisierul citit
			for key in "${!cuvinte[@]}"; do # iau dictionarul cu argumentele
				if [ $key == $cuv ]; then # vad daca se gaseste key-ul printe cuvintele din fisier  
					cuvinte[$key]=1
				fi
			done
		done
		final=1
		for key in ${!cuvinte[@]}; do
			echo $key "-" ${cuvinte[$key]}
			if [ ${cuvinte[$key]} -eq 0 ]; then
			final=0
			fi
		done

		if [ $final == 1 ]; then
			break
		fi
	fi
done
