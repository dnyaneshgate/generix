#!/bin/bash

ECHO="echo -e"

if [[ $# != 1 ]]; then
	$ECHO "Usage: $0 <emulator name>";
	exit;
fi

EMU=$1
PROJECTPATH=/media/SOFTWARE/Generix
BOOT=$PROJECTPATH/Boot

if [[ $EMU -eq "bochs" ]]; then
	$EMU -q "ata0-master:type=cdrom,path=$BOOT/Generix.iso,status=inserted" \
			'megs:512' \
			'boot:cdrom' \
			'cpu:count=1,ips=4000000,reset_on_triple_fault=1,ignore_bad_msrs=1' \
			'clock:sync=realtime,time0=local'
fi

