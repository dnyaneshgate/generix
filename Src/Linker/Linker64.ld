

/* Generate an ELF executable */
OUTPUT_FORMAT("elf32-i386")

/* Set the entry point to 'start'. This is an assembly function, so there's
* no name mangling */
ENTRY(Start)
SECTIONS
{
	/* The executable is to be loaded by GrUB at 1 Mib */
	. = 0x00100000;
	/* Align every section on page boundaries. This'll be important later on */
	.text ALIGN(0x1000) : 
	{
		/* This marks the start of the program code */
		code = .;
		/* GrUB requires that the Multiboot header be located at the start
		* of the file */
		*(.Multiboot)
		*(.text*)
		*(.gnu.linkonce.t*)
		*(.gnu.linkonce.r*)
		codeEnd = .;
	}
	/* This section contains our local variables and constructor
	* (and destructor) lists */
	.data ALIGN(0x1000) : 
	{
		data = .;

		__CTOR_LIST__ = .; LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2) *(.ctors) LONG(0) __CTOR_END__ = .; 
		__DTOR_LIST__ = .; LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2) *(.dtors) LONG(0) __DTOR_END__ = .;

		*(.rodata*)
		*(.data*)
		*(.gnu.linkonce.d*)
		dataEnd = .;
	}
	/* There isn't really anything interesting here. It gets zeroed out by GrUB before
	* the kernel is executed */
	.bss ALIGN(0x1000) : 
	{
		bss = .;
		*(.gnu.linkonce.b*)
		*(COMMON)
		*(.bss*)
		bssEnd = .;
	}
	end = .; _end = .; __end = .;
}
