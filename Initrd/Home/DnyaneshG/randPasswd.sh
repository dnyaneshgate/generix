#!/bin/bash

genpasswd()
{
	echo "\$1=$1";
	len=$1;
	if [[ $len == 0 ]]; then
		len=8;
	elif [[ $len < 0 ]]; then
		len=`expr $len \* (-1)`;
	fi
	echo "len=$len";
	dd if=/dev/urandom count=1 2> /dev/null | md5sum | cut -c-$len;
}

genpasswd $1;
