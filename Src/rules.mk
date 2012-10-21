
KERNELPATH          := Kernel
OBJPATH             := Obj
DRIVERPATH          := Drivers
BOOTPATH            := Boot
LINKERPATH          := Linker
BASH                := /bin/bash

## Kernel Version
VERSION             := "\"0.0.1\""

## Target Architecture currently supports ( x86 , x86_64 )
ARCH                := x86

## Include Directories
INCLUDE             :=  -I./ \
						-I./Include \
						-I./Include/Klib/libc \
						-I./Include/Klib/libc++ \
						-I./Include/Klib/liballoc \
						-I./Include/Klib/libposix \
						-I./Mem \
						-I./Drivers

WARNINGS            := -Wall -Wextra -Wno-unused-function -Wno-unused-parameter #-Werror -Wno-gnu -pedantic

CPPFLAGS            := -D__GENERIX__ -D__GENERIX_VERSION__=$(VERSION) ## C/C++ Preprocessor Flags
DFLAGS              := -g -O0 -D__DEBUG__ ## Debugger Flags

ifeq ($(ARCH),x86)

$(shell ln -nsf x86/ Include/Processor/Arch)    #create architecture dependant symbolic links
$(shell ln -nsf x86/ Kernel/Processor/Arch)    #create architecture dependant symbolic links

KERNEL              := Kernel32.elf
CPPFLAGS            += -D__x86__
CFLAGS              := -c -m32
ASFLAGS             := -f elf32
LDFLAGS             := -T$(LINKERPATH)/Linker32.ld -melf_i386

else ifeq ($(ARCH),x86_64)

$(shell ln -nsf x86_64/ Include/Processor/Arch)    #create architecture dependant symbolic links
$(shell ln -nsf x86_64/ Kernel/Processor/Arch)    #create architecture dependant symbolic links

KERNEL              := Kernel64.elf
CPPFLAGS            += -D__x86_64__
CFLAGS              := -c -m64
ASFLAGS             := -f elf64
LDFLAGS             := -T$(LINKERPATH)/Linker64.ld -melf_x86_64

endif

CFLAGS              += $(DFLAGS) $(CPPFLAGS) $(INCLUDE) $(WARNINGS) -nostdlib -fno-builtin -nostartfiles -nodefaultlibs ## C Compiler Flags
CXXFLAGS            := $(CFLAGS) -DCPP -fno-stack-protector -fno-exceptions -fno-rtti -std=c++11 ## C++ Compiler Flags
ARFLAGS             := rcs

##export KERNELPATH OBJPATH DRIVERPATH BOOTPATH LINKERPATH VERSION ARCH INCLUDE WARNINGS KERNEL CPPFLAGS CFLAGS CXXFLAGS ASFLAGS LDFLAGS ARFLAGS DFLAGS 
