#!/bin/bash

OPTIONS="Hello Quit"
: 'index=0

for opt in $OPTIONS; do
	printf "$((++index)): $opt\n"
done

while true; do
	read choice
	for opt in $OPTIONS; do
		if [ "$opt" == "$choice" ]; then
			echo "$choice"
			return
		fi
	done
	echo "Invalid Option"
done
'
select opt in $OPTIONS; do
	if [ "$opt" == "Quit" ]; then
		echo done
		return
	elif [ "$opt" == "Hello" ]; then
		echo Hello World
		return
	else
		clear
		echo bad option
	fi
done

