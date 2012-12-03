#!/bin/bash

PWD=`pwd`
ECHO="echo -e"

if [[ $# -lt 1 ]]; then
	$ECHO "Usage: $0 <emulator name>";
	exit;
fi

EMU=$1
GENERIX="GeneriXOS"
ISO=$GENERIX.iso
PROJECTPATH=$PWD
BOOT=$PROJECTPATH/Boot

if [[ $EMU == "bochs" ]]; then
	if [[ $2 == "debug" ]]; then
		DEBUG="gdbstub: enabled=1, port=1234, text_base=0, data_base=0, bss_base=0";
		EMU="bochs-gdb";
	fi

	$EMU -q "ata0-master:type=cdrom,path=$BOOT/$ISO,status=inserted" \
			'megs:512' \
			'boot:cdrom' \
			'cpu:model="core_duo_t2400_yonah" ,count=1,ips=4000000' \
			'cpuid: mmx=1, sep=1, sse=sse4_2, apic=xapic, aes=1, movbe=1, xsave=1' \
			'clock:sync=realtime,time0=local' \
			'logprefix: %t-%e-@%i-%d' \
			"$DEBUG"
elif [[ $EMU == "qemu" ]];then
	$ECHO "\033[31m Not Implemented Yet \033[0m";
else
	$ECHO "\033[31m Unsupported Emulator \033[0m";
fi
