#!/bin/bash

for (( s=$1; s<=$2; s++ ))
do
	for f in /var/operation/HVSCAN/00$s/Scan00????_Run*
	do
		echo $f
		bin/reformatting $f
	done
done

