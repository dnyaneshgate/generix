/*
 * OUTPUT FORMAT:
 * binary --This is just a flat binary with no formatting at all
 * elf32-i386 --This is just the ELF format, usually little endian too.
 * elf64-x86-64 --This is the ELF format for 64bit, usually little endian.
 * pe-i386 --The PE format
 */


/* Generate an ELF executable */
OUTPUT_FORMAT("elf32-i386")

/* Set the entry point to 'start'. This is an assembly function, so there's
* no name mangling */
ENTRY(_Start)
SECTIONS
{
	/* The executable is to be loaded by GrUB at 1 Mib */
	. = 0x00100000;
	/* Align every section on page boundaries. This'll be important later on */
	.msection : {
		*(.msection)
	}
	.text ALIGN(0x1000) :
	{
		/* This marks the start of the program code */
		_TEXT_START = .;
		/* GrUB requires that the Multiboot header be located at the start
		* of the file */
		/* *(.mboot) */
		*(.text*)
		*(.gnu.linkonce.t*)
		*(.gnu.linkonce.r*)

		_TEXT_END = .;
	}

	/* This section contains our local variables and constructor (and destructor) lists */
	.data ALIGN(0x1000) :
	{
		_DATA_START = .;

		__CTOR_LIST__ = .; LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2) *(.init_array*) LONG(0) __CTOR_END__ = .;
		__DTOR_LIST__ = .; LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2) *(.fini_array*) LONG(0) __DTOR_END__ = .;

		/*__CTOR_LIST__ = .; LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2) *(.ctor*) LONG(0) __CTOR_END__ = .;
		__DTOR_LIST__ = .; LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2) *(.dtor*) LONG(0) __DTOR_END__ = .;*/

		KEEP(*(.ctor*))
		KEEP(*(.ctor*))

		__INIT_START__ = .;
		*(.initGenerix)
		/*KEEP(*(SORT(.initGenerix)))*/
		KEEP(*(.initGenerix))
		__INIT_END__ = .;

		*(.rodata*)
		*(.data*)
		*(.gnu.linkonce.d*)

		_DATA_END = .;
	}

	/* There isn't really anything interesting here. It gets zeroed out by GrUB before
	* the kernel is executed */
	.bss ALIGN(0x1000) :
	{
		_BSS_START = .;

		*(.gnu.linkonce.b*)
		*(COMMON)
		*(.bss*)

		_BSS_END = .;
	}

	_KERNEL_END = .; __KERNEL_END = .;
}
