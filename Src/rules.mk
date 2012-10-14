
KERNELPATH          := Kernel
OBJPATH             := Obj
DRIVERPATH          := Drivers
BOOTPATH            := Boot
LINKERPATH          := Linker
SHELL               := /bin/bash
VERSION             := "\"0.0.1\""

ARCH                := x86

INCLUDE             :=  -I./ \
						-I./Include \
						-I./Include/Klib/libc \
						-I./Include/Klib/libc++ \
						-I./Include/Klib/liballoc \
						-I./Include/Klib/libposix \
						-I./Mem \
						-I./Drivers

WARNINGS            := -Wall -Wextra #-Werror

ifeq ($(ARCH),x86)

$(shell ln -nsf x86/ Include/Processor/Arch)    #create architecture dependant symbolic links
$(shell ln -nsf x86/ Kernel/Processor/Arch)    #create architecture dependant symbolic links

KERNEL              := Kernel32.elf
CPPFLAGS            := -D__x86__
CFLAGS              := -c -m32
ASFLAGS             := -felf32
LDFLAGS             := -T$(LINKERPATH)/Linker32.ld -melf_i386

else ifeq ($(ARCH),x86_64)

$(shell ln -nsf x86_64/ Include/Processor/Arch)    #create architecture dependant symbolic links
$(shell ln -nsf x86_64/ Kernel/Processor/Arch)    #create architecture dependant symbolic links

KERNEL              := Kernel64.elf
CPPFLAGS            := -D__x86_64__
CFLAGS              := -c -m64
ASFLAGS             := -felf64
LDFLAGS             := -T$(LINKERPATH)/Linker64.ld -melf_x86_64

endif

CPPFLAGS            += -D__GENERIX__ -D__GENERIX_VERSION__=$(VERSION)
CFLAGS              += $(CPPFLAGS) $(INCLUDE) $(WARNINGS) -nostdlib -fno-builtin -nostartfiles -nodefaultlibs
CXXFLAGS            := $(CFLAGS) -DCPP -fno-stack-protector -fno-exceptions -fno-rtti -std=c++11
DFLAGS              := -g3 -O0 -D__DEBUG__
ARFLAGS             := rcs
