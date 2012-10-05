
KERNELPATH          := Kernel
OBJPATH             := Obj
DRIVERPATH          := Drivers
BOOTPATH            := Boot
LINKERPATH          := Linker
SHELL               := /bin/bash

ARCH                := x86

INCLUDE             := -I./ \
					   -I./Include \
					   -I./Include/Klib/libc \
					   -I./Include/Klib/libc++ \
					   -I./Include/Klib/liballoc \
					   -I./Include/Klib/libposix \
					   -I./Drivers

WARNINGS            := -Wall #-Wextra #-Werror

ifeq ($(ARCH),x86)

KERNEL              := Kernel32.elf
CPPFLAGS            := -D__x86__
CFLAGS              := -c -m32
ASFLAGS             := -felf32
LDFLAGS             := -T$(LINKERPATH)/Linker32.ld -melf_i386

else ifeq ($(ARCH),x86_64)

KERNEL              := Kernel64.elf
CPPFLAGS            := -D__x86_64__
CFLAGS              := -c -m64
ASFLAGS             := -felf64
LDFLAGS             := -T$(LINKERPATH)/Linker64.ld -melf_x86_64

endif

CFLAGS              += $(CPPFLAGS) $(INCLUDE) $(WARNINGS) -nostdlib -fno-builtin -nostartfiles -nodefaultlibs
CXXFLAGS            := $(CFLAGS) -DCPP -fno-stack-protector -fno-exceptions -fno-rtti -std=c++11
DFLAGS              := -g3 -O0 -D__DEBUG__
ARFLAGS             := rcs

