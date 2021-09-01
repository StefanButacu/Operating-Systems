#!bin/bash

if [$# -eq 0]; then
	echo "Dati cel putin un nume de proces"
	exit 1
fi
while true; do
	for process in $@; do
		PIDs=""
		PIDs=$(ps -ef | awk '{print $8" "$2}' | grep -E "^$process" | awk '{print $2}') 
		if [ -n "$PIDs" ]; then
			kill -9 "$PIDs"
		fi
	done
	sleep 3
	done
