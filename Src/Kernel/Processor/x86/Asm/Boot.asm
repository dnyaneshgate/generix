;#include <Multiboot.hpp>

[BITS 32]

;stack size used to pass agruments in c/c++ functions
STACKSIZE                  equ            0x8000

;load kernel and module on page boundry
MULTIBOOT_PAGE_ALIGN           equ            1 << 0

;provide kernel with memory info
MULTIBOOT_MEM_INFO             equ            1 << 1

;provide kernel with graphic info
MULTIBOOT_VBE_INFO             equ            1 << 2

MULTIBOOT_AOUT_KLUDGE          equ            1 << 16

MULTIBOOT_HEADER_MAGIC         equ            0x1BADB002
MULTIBOOT_HEADER_FLAGS         equ            MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEM_INFO | MULTIBOOT_VBE_INFO ;| MULTIBOOT_AOUT_KLUDGE
MULTIBOOT_HEADER_CHECKSUM      equ            -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

GLOBAL  _Start
GLOBAL  _MBOOT_HEADER
EXTERN  _TEXT_START ,_BSS_START, _KERNEL_END
EXTERN  _kmain

SECTION .__mbHeader
ALIGN 4
_MBOOT_HEADER:
	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd MULTIBOOT_HEADER_CHECKSUM
	dd _MBOOT_HEADER
	dd _TEXT_START                          ;start of kernel '.text' code section
	dd _BSS_START                           ;start of kernel '.data' section
	dd _KERNEL_END                          ;kernel end
	dd _Start                               ;entry point of kernel

_Start:
	mov esp, StackEnd
	mov esp, StackEnd

	push esp                       ;pass stack pointer
	push eax                       ;pass mboot magic number
	push ebx                       ;pass mboot header info

	cli                            ;disable interrupts
	mov eax, _kmain
	call eax                       ;call kernel entry function

	jmp $

SECTION .bss
StackBegin:
	resb STACKSIZE
StackEnd:
