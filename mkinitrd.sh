#!/bin/bash

if [[ $# != 1 ]]; then
	echo -e "Usage $0 <file-system>";
	exit;
fi

if [[ $1 == 'CPIO' ]]; then
	cd Initrd && \
	find . -depth -print | cpio -o > ../Initrd.img && \
	cd ..;
elif [[ $1 == 'TAR' ]]; then
	cd Initrd && \
	tar -cvf ../Initrd.img * && \
	cd ..;
else
	echo -e "$1 FileSystem type not supported";
fi
