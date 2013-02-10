#include <Macros.hpp>
#include <Multiboot.hpp>
#include <Processor/x86/CPU.hpp>
#include <Processor/x86/Memory.hpp>

[BITS 32]

%define STACKSIZE 0x8000

%macro REGISTER_SAVE 0
	pushad                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
	push ss
	push ds
	push es
	push fs
	push gs
	mov ax, KERNEL_DS_SEL  ; load the kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
%endmacro

%macro REGISTER_RESTORE 0
	pop gs
	pop fs
	pop es
	pop ds
	pop ss
	popad                     ; Pops edi,esi,ebp...
%endmacro

%macro interruptHandler 2
[GLOBAL ISR%1]
ISR%1:
	cli
%if !%2
	push byte 0
%endif
	push byte %1
	jmp invokeHandler
%endmacro

/**
 * Fills in IDT entries.
 */
%macro idtEntry 2
	mov eax, 8
	mov ebx, %1
	imul ebx
	add eax, idt
	mov ebx, ISR%1
	mov word [eax], bx        	/* Offset low */
	shr ebx, 16
	mov word [eax + 6], bx       	/* Offset high */
	mov word [eax + 2], KERNEL_CS_SEL    /* Kernel CS */
	mov byte [eax + 4], 0        	/* Zeroes */
	mov byte [eax + 5], %2   	/* Present, 32 bits, 01110 */
%endmacro

GLOBAL  _Start
GLOBAL  multiBootHeader, multiBootInfo, kernelDirectory, kernelTable
EXTERN  _TEXT_START ,_BSS_START, _KERNEL_END
EXTERN  _kInit

section .msection
align 4
multiBootHeader:
	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd MULTIBOOT_HEADER_CHECKSUM
	dd multiBootHeader
	dd _TEXT_START                          ;start of kernel '.text' code section
	dd _BSS_START                           ;start of kernel '.data' section
	dd _KERNEL_END                          ;kernel end
	dd _Start                               ;entry point of kernel

section .text
_Start:
	jmp _Entry

_Entry:
	cli
	mov esp, StackEnd
	mov ebp, esp

	cmp eax, MULTIBOOT_BOOTLOADER_MAGIC
	jne _Halt

	mov eax, multiBootInfo
;	%assign i 0
;	%rep MULTIBOOT_HEADER_SIZE
;		mov edx, [ebx]
;		mov [eax], edx
;		add ebx, 4
;		add eax, 4
;		%assign i i+4
;	%endrep

	mov ecx, MULTIBOOT_INFO_HEADER_SIZE
loop0:
	mov edx, [ebx]
	mov [eax], edx
	add ebx, 4
	add eax, 4
	sub ecx, 4
	jnz loop0

	mov ecx, gdtPtr
	lgdt [ecx]      ;load gdtPtr
	jmp 0x08:pic

;/*initialize pic*/
pic:
	;/*send ICW1 to PIC1 (20h) and PIC2 (A0h)*/
	mov al, ICW1
	mov dx, PIC1
	out dx, al
	mov dx, PIC2
	out dx, al

	;/*send ICW2 to 21h for the first PIC and 0A1h for the second PIC*/
	mov al, MASTER_VEC
	mov dx, PIC1
	add dx, 1
	out dx, al
	mov al , SLAVE_VEC
	mov dx, PIC2
	add dx, 1
	out dx, al

	;/*send ICW3 to 21h for the first PIC and 0A1h for the second PIC*/
	mov al, 4
	mov dx, PIC1
	add dx, 1
	out dx, al
	mov al, 2
	mov dx, PIC2
	add dx, 1
	out dx, al

	;/*finally, send ICW4 to 21h for the first PIC and 0A1h for the second PIC*/
	mov al, ICW4
	mov dx, PIC1
	add dx, 1
	out dx, al
	mov dx, PIC2
	add dx, 1
	out dx, al

	;/* disable all IRQs */
	mov al, 0xff
	mov dx, PIC1
	add dx, 1
	out dx, al
	mov dx, PIC2
	add dx, 1
	out dx, al

	;/* Fill in IDT entries 0 - 16, and 32 - 47. */
	idtEntry 0, 0x8f
	idtEntry 1, 0x8f
	idtEntry 2, 0x8f
	idtEntry 3, 0x8f
	idtEntry 4, 0x8f
	idtEntry 5, 0x8f
	idtEntry 6, 0x8f
	idtEntry 7, 0x8f
	idtEntry 8, 0x8f
	idtEntry 9, 0x8f
	idtEntry 10, 0x8f
	idtEntry 11, 0x8f
	idtEntry 12, 0x8f
	idtEntry 13, 0x8f
	idtEntry 14, 0x8f
	idtEntry 15, 0x8f
	idtEntry 16, 0x8f
	idtEntry 32, 0x8e
	idtEntry 33, 0x8e
	idtEntry 34, 0x8e
	idtEntry 35, 0x8e
	idtEntry 36, 0x8e
	idtEntry 37, 0x8e
	idtEntry 38, 0x8e
	idtEntry 39, 0x8e
	idtEntry 40, 0x8e
	idtEntry 41, 0x8e
	idtEntry 42, 0x8e
	idtEntry 43, 0x8e
	idtEntry 44, 0x8e
	idtEntry 45, 0x8e
	idtEntry 46, 0x8e
	idtEntry 47, 0x8e
	;idtEntry 0x80, 0xee

	mov ecx, idtPtr
	lidt [ecx]        ;load idtPtr

	;Setup Sengments
	mov eax, KERNEL_DS_SEL
	mov ds, eax
	mov es, eax
	mov ss, eax

	;Kernel Directory
	;mov eax, kernelDirectory
	;mov ebx, kernelTable
	;or  ebx, (PAGE_PRESENT | PAGE_WRITE)
	;mov [eax], ebx

	;identity page mapping first 4MB
;	mov eax, kernelTable
;	xor ebx, ebx
;	or ebx, (PAGE_PRESENT | PAGE_WRITE)
;	mov ecx, 1024

;loop1:
;	mov [eax], ebx
;	add ebx, PAGESIZE
;	add eax, 4
;	dec ecx
;	jnz loop1

	mov ecx, kernelDirectory
	mov cr3, ecx
	mov ecx, cr0
	or  ecx, CR0_PAGEBIT
	mov cr0, ecx

	sti
	push esp
	call _kInit

_Halt:
	cli
	hlt
	jmp _Halt

/**
 * Generated interrupt handlers.
 */
interruptHandler  0, 0
interruptHandler  1, 0
interruptHandler  2, 0
interruptHandler  3, 0
interruptHandler  4, 0
interruptHandler  5, 0
interruptHandler  6, 0
interruptHandler  7, 0
interruptHandler  8, 1
interruptHandler  9, 0
interruptHandler 10, 1
interruptHandler 11, 1
interruptHandler 12, 1
interruptHandler 13, 1
interruptHandler 14, 1
interruptHandler 15, 0
interruptHandler 16, 0
interruptHandler 32, 0
interruptHandler 33, 0
interruptHandler 34, 0
interruptHandler 35, 0
interruptHandler 36, 0
interruptHandler 37, 0
interruptHandler 38, 0
interruptHandler 39, 0
interruptHandler 40, 0
interruptHandler 41, 0
interruptHandler 42, 0
interruptHandler 43, 0
interruptHandler 44, 0
interruptHandler 45, 0
interruptHandler 46, 0
interruptHandler 47, 0
;interruptHandler 0x80, 0

[EXTERN InterruptServiceRoutine]
invokeHandler:
	REGISTER_SAVE
	mov eax, InterruptServiceRoutine
	call eax
	REGISTER_RESTORE
	add esp, 8     ; Cleans up the pushed error code and pushed ISR number
	sti
	iretd           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

section .data
/**
 * Global Descriptor Table.
 */
gdt:
	dq 0x0000000000000000 /* NULL descriptor. */
	dq 0x00cf9a000000ffff /* Kernel CS. */
	dq 0x00cf92000000ffff /* Kernel DS. */
	dq 0x00cffa000000ffff /* User CS. */
	dq 0x00cff2000000ffff /* User DS. */
	dq 0x0000000000000000 /* TSS descriptor. */
gdt_end:

gdtPtr:
	dw gdt_end - gdt
	dd gdt
	dw 0

idt:
	times 256 dq 0x0
idtPtr:
	dw 256*8-1
	dd idt

align PAGESIZE
kernelDirectory:
	dd kernelTable + (PAGE_PRESENT | PAGE_WRITE)
	times (PAGE_DIR_INDEX(KERNEL_OFFSET)-1) dd 0x0
	dd kernelTable + (PAGE_PRESENT | PAGE_WRITE)
	times(1022 - (PAGE_DIR_INDEX(KERNEL_OFFSET))) dd 0x0
	dd kernelDirectory + (PAGE_PRESENT | PAGE_WRITE)

align PAGESIZE
kernelTable:
	%assign i 0
	%rep 1024
		dd (i << 12) | PAGE_PRESENT | PAGE_WRITE
	%assign i i+1
	%endrep

section .bss
multiBootInfo:
	resb (MULTIBOOT_INFO_HEADER_SIZE)

align 4
StackBegin:
	resb STACKSIZE
StackEnd:
