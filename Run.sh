#!/bin/bash

if [[ $1 == "debug" ]]; then
	debug='debug';
else
	debug=' ';
fi

Scripts/iso.sh Src/Kernel32.elf Initrd.img && Scripts/emulate.sh bochs $debug
