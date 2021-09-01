#!/bin/bash
LastEmail=""
NextEmail=""
for userName in ` cat $1 `; do
	userName+="@scs.ubbcluj.ro"
	LastEmail+=$userName
	NextEmail=$LastEmail
	LastEmail+=","
done
echo $NextEmail


