#!/bin/bash
# gaseste recurisv in director fisere regulare care au drepturi de scriere pt toata lumea.
# sterge dretupul de scriere de la toata lumea 
RWX="??w??w??w?"
for X in `find . -type f`; do 
       Perm=`ls -l $X | awk '{print $1}'`
                     #-rwxrwxrw 
       if [[ $Perm =~ ..w..w..w. ]];then #am folosit =~ expresie regulara fiindca nu a mers cu wildcardul ??w??w??w?
	       echo $X "Are drepturi de citire pentru toti"
	       `chmod u-w,g-w,o-w $X`
       fi
done       
