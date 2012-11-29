#!/usr/bin/perl -w

package config;

use strict;
use warnings;

use Exporter;
use base 'Exporter';    # or: our @ISA = 'Exporter';

our @EXPORT = qw( $CC $CXX $AS $AR @WARNINGS @INCLUDE @CPPFLAGS @DFLAGS @CFLAGS @CXXFLAGS @ASFLAGS @LDFLAGS $KERNEL $ARCH $VERSION $CWD $LINKERPATH  );

chomp(our $CWD = `pwd`);

our $VERSION = '0.0.1';
our $ARCH = 'X86';
our $LINKERPATH = $CWD . '/Src/Linker';

#list of build variables
our $CC = 'gcc';
our $CXX = 'g++';
our $AS = 'nasm';
our $AR = 'ar';
our $LD = 'ld';

#list of build flags
our @WARNINGS = ('-Wall ','-Wextra ','-Wno-unused-function ','-Wno-unused-parameter ');
our @INCLUDE = ('-I./ ','-I./Include ','-I./Include/Klib/libc ','-I./Include/Klib/libc++ ','-I./Include/Klib/liballoc ','-I./Include/Klib/libposix ','-I./Drivers ');
our @CPPFLAGS = ('-D__GENERIX__ ',"-D__GENERIX_VERSION__=$VERSION ",@WARNINGS,@INCLUDE,'-nostdlib ','-fno-builtin ','-nostartfiles ','-nodefaultlibs ');
our @DFLAGS = ('-g ', '-O0 ', '-D__DEBUG__ ');
our @CFLAGS = ();
our @CXXFLAGS = ();
our @ASFLAGS = ();
our @LDFLAGS = ();
our @ARFLAGS = ();

if( $ARCH eq 'X86' )
{
	`ln -nsf x86/ Src/Include/Processor/Arch`;
	`ln -nsf x86/ Src/Kernel/Processor/Arch`;
	our $KERNEL = 'Kernel32.elf';
	push(@LDFLAGS,("-T$LINKERPATH/Linker32.ld ",'-melf_i386 '));
	push(@CFLAGS, '-m32 ');
	push(@ASFLAGS,'-felf32 ');
	push(@CPPFLAGS, '-D__x86__ ');
}
elsif($ARCH eq 'X86_64')
{
	print "Intel 64-bit\n";
	print "Not Implemented Yet\n";
}

push(@CFLAGS,@CPPFLAGS);
push(@CXXFLAGS,@CFLAGS);
push(@CXXFLAGS,('-DCPP ','-fno-stack-protector ','-fno-exceptions ','-fno-rtti ','-std=c++11 '));
push(@ARFLAGS,('rcs '));
1;
