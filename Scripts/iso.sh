#!/bin/bash

ECHO="echo -e"
CP="cp"
RM="rm"
MKDIR="mkdir"
MKISO="mkisofs"

if [[ $# != 1 ]]; then
	$ECHO "Usage $0 <kernel-path>";
	exit;
fi

PROJECTDIR=/media/SOFTWARE/Generix
BOOT=$PROJECTDIR/Boot
ISOPATH=$BOOT/Iso
ISO=$BOOT/Generix.iso
KERNEL=$1
GRUB=$BOOT/Grub

if [ ! -d $ISOPATH ]; then
	$MKDIR -p $ISOPATH/boot/grub/
fi

ret=`$CP $GRUB/* $ISOPATH/boot/grub/ && \
	 $CP $KERNEL $ISOPATH/boot/Generix-1.0 && \
	 $ECHO "default 0"                   > $ISOPATH/boot/grub/menu.lst && \
	 $ECHO "timeout 5\n\n"              >> $ISOPATH/boot/grub/menu.lst && \
	 $ECHO "title Generix-1.0"          >> $ISOPATH/boot/grub/menu.lst && \
	 $ECHO "\tkernel /boot/Generix-1.0" >> $ISOPATH/boot/grub/menu.lst`

if [[ $ret ]]; then
	$ECHO "Error: $ret"
else
	$ECHO "Generating Iso Image : $ISO"
	$MKISO -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o $ISO $BOOT/Iso/ #2> /dev/null
fi

$RM -rf $ISOPATH
