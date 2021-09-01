#!/bin/bash
for X in `cat /etc/passwd | awk -F: '{print $1}'`; do
	Ip=`last $X`             # varianta asta n am mai testat o 
				# am test cu fisierele .fake dar nu cred ca userii din passwd.fake se gaesc si in last.fake
	echo $Ip > $X.txt

done
