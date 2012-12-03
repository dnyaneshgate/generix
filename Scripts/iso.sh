#!/bin/bash

PWD=`pwd`
ECHO="echo -e"
CP="cp"
RM="rm"
MKDIR="mkdir"
MKISO="mkisofs"

if [[ $# != 2 ]]; then
	$ECHO "Usage $0 <path-to-kernel> <path-to-initrd>";
	exit;
fi

GENERIX="GeneriXOS"
PROJECTDIR=$PWD
BOOT=$PROJECTDIR/Boot
ISOPATH=$BOOT/Iso
ISO=$BOOT/$GENERIX.iso
KERNEL=$1
INITRD='Initrd.img'
INITRD_PATH=$2
GRUB=$BOOT/Grub

if [ ! -d $ISOPATH ]; then
	$MKDIR -p $ISOPATH/boot/grub/
fi

ret=`$CP $GRUB/* $ISOPATH/boot/grub/ && \
	 $CP $KERNEL $ISOPATH/boot/$GENERIX && \
	 $CP $INITRD_PATH $ISOPATH/boot/$INITRD && \
	 $ECHO "default 0"                   > $ISOPATH/boot/grub/menu.lst && \
	 $ECHO "timeout 5\n\n"              >> $ISOPATH/boot/grub/menu.lst && \
	 $ECHO "title $GENERIX"             >> $ISOPATH/boot/grub/menu.lst && \
	 $ECHO "\tkernel /boot/$GENERIX"    >> $ISOPATH/boot/grub/menu.lst && \
	 $ECHO "\tmodule /boot/$INITRD"     >> $ISOPATH/boot/grub/menu.lst`

if [[ $ret ]]; then
	$ECHO "Error: $ret"
else
	$ECHO "Generating Iso Image : $ISO"
	$MKISO -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o $ISO $ISOPATH #2> /dev/null
fi

$RM -rf $ISOPATH
