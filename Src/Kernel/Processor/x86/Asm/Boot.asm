[BITS 32]

;stack size used to pass agruments in c/c++ functions
STACKSIZE                  equ            0x8000

;load kernel and module on page boundry
MBOOT_PAGE_ALIGN           equ            1 << 0

;provide kernel with memory info
MBOOT_MEM_INFO             equ            1 << 1

;provide kernel with graphic info
MBOOT_VBE_INFO             equ            1 << 2

MBOOT_AOUT_KLUDGE          equ            1 << 16

MBOOT_HEADER_MAGIC         equ            0x1BADB002
MBOOT_HEADER_FLAGS         equ            MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO | MBOOT_VBE_INFO ;| MBOOT_AOUT_KLUDGE
MBOOT_HEADER_CHECKSUM      equ            -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

GLOBAL  _start
GLOBAL  _MBOOT_HEADER
EXTERN  _TEXT_START ,_BSS_START, _KERNEL_END
EXTERN  _kmain

SECTION .mboot
ALIGN 4
_MBOOT_HEADER:
	dd MBOOT_HEADER_MAGIC
	dd MBOOT_HEADER_FLAGS
	dd MBOOT_HEADER_CHECKSUM
	dd _MBOOT_HEADER
	dd _TEXT_START                          ;start of kernel '.text' code section
	dd _BSS_START                           ;start of kernel '.data' section
	dd _KERNEL_END                          ;kernel end
	dd _start                               ;entry point of kernel

_start:
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
