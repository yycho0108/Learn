#!/bin/bash

for f in $(find . -maxdepth 1 -name '*~');do
	#echo $f;
	orig=${f:0:$[${#f}-1]};
	#echo $orig;
	if [ ! -f $orig ]
	then
		#echo 'NotAFile'+$orig;
		rm -rf $f;
	else
		echo 'File :'+$orig;
	fi
	#if [ ! -f $f] then
#
#	fi
done;
