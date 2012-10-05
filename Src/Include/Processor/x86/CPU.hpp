#ifndef __GENERIX_CPU_HPP__
#define __GENERIX_CPU_HPP__

#include <Types.hpp>
#include <Macros.hpp>

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
	UINT limitLow :16;
	UINT baseLow :16;
	UINT baseMid :8;
	UINT access :8;
	UINT granularity :8;
	UINT baseHigh :8;
}PACKED GDTENTRY, *PGDTENTRY;

typedef struct strucIDTENTRY {
	USHORT offset_1;                             // offset bits 0..15
	USHORT selector;                    // a code segment selector in GDT or LDT
	UCHAR zero;                                 // unused, set to 0
	UCHAR type_attr;                           // type and attributes, see below
	USHORT offset_2;                             // offset bits 16..31
}PACKED IDTENTRY, *PIDTENTRY;

EXTERN GDTENTRY gdt[];

}

#endif //__GENERIX_CPU_HPP__
