#ifndef __GENERIX_X86_CPU_HPP__
#define __GENERIX_X86_CPU_HPP__

#include <Types.hpp>
#include <Macros.hpp>

/** Kernel Code Segment. */
#define KERNEL_CS       1
#define KERNEL_CS_SEL   0x8

/** System Data Segment. */
#define KERNEL_DS       2
#define KERNEL_DS_SEL   0x10

/** User Code Segment. */
#define USER_CS         3
#define USER_CS_SEL     (0x18 | 3)

/** User Data Segment. */
#define USER_DS         4
#define USER_DS_SEL     (0x20 | 3)

/** User TSS. */
#define USER_TSS        5
#define USER_TSS_SEL    0x28

/*PICs*/
#define PIC1        0x20
#define PIC2        0xA0

/*ICWs*/
#define ICW1        0x11
#define ICW4        0x01

#define MASTER_VEC  0x20
#define SLAVE_VEC   0x28

#define INT_GATE    0x06
#define TRAP_GATE   0x07

#define BITS_16     0x00
#define BITS_32     0x08

#define ABSENT      0x00
#define PRESENT     0x80

#define RING_0      0x00
#define RING_1      0x20
#define RING_2      0x40
#define RING_3      0x60
#define EOI         0x20          //end of interrupt

#ifndef __ASSEMBLER__

namespace Generix {

	enum ContrilRegister {
		CR0, CR1, CR2, CR3, CR4, CR5
	};

	typedef struct strucTSS {
		UINT backlink;
		UINT esp0, ss0;
		UINT esp1, ss1;
		UINT esp2, ss2;
		UINT cr3;
		UINT eip;
		UINT eflags;
		UINT eax, ecx, edx, ebx;
		UINT esp, ebp;
		UINT esi, edi;
		UINT es, cs, ss, ds, fs, gs;
		UINT ldt;
		UINT bitmap;
	} TSS, *PTSS;

	typedef struct strucREG {
		/* Segments. */
		UINT gs, fs, es, ds, ss0;

		/* By pushad */
		UINT edi, esi, ebp, esp0, ebx, edx, ecx, eax;

		/* Vector/error arguments. */
		UINT vector, error;

		/* Pushed by processor. */
		UINT eip, cs, eflags, esp3, ss3;
	} REG, *PREG;

	typedef struct strucGDTENTRY {
		UINT limitLow : 16;
		UINT baseLow : 16;
		UINT baseMid : 8;
		UINT access : 8;
		UINT granularity : 8;
		UINT baseHigh : 8;
	} __PACKED__ GDTENTRY, *PGDTENTRY;

	typedef struct strucIDTENTRY {
		USHORT offset_1; // offset bits 0..15
		USHORT selector; // a code segment selector in GDT or LDT
		UCHAR zero; // unused, set to 0
		UCHAR type_attr; // type and attributes, see below
		USHORT offset_2; // offset bits 16..31
	} __PACKED__ IDTENTRY, *PIDTENTRY;

	EXTERN GDTENTRY gdt[];

}

#endif //__ASSEMBLER__

#endif //__GENERIX_X86_CPU_HPP__
