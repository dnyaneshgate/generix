/*
 * Gdt.cpp
 *
 *  Created on: Sep 30, 2012
 *      Author: dnyanesh
 */

#include <Processor/x86/Gdt.hpp>
#include <Processor/x86/CPU.hpp>

namespace Generix {

	GDTENTRY gdt[6];
	EXTERN "C" VOID _GdtFlush(ULONG);

	GGdt::GGdt() {
	}

	GGdt::~GGdt() {
	}

	VOID GGdt::SetGdtEntry(INT n, ULONG base, ULONG limit, UCHAR access, UCHAR gran) {
		gdt[n].baseLow = base & 0xffff;
		gdt[n].baseMid = SHR(base, 16) & 0xff;
		gdt[n].baseHigh = SHR(base, 24) & 0xff;
		gdt[n].limitLow = limit & 0xffff;
		gdt[n].granularity = SHR(limit, 16) & 0xf;
		gdt[n].granularity |= gran & 0xf0;
		gdt[n].access = access;
	}

	VOID GGdt::Install() {
		SetGdtEntry(0, 0, 0, 0, 0);
		SetGdtEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
		SetGdtEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
		SetGdtEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
		SetGdtEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
		SetGdtEntry(5, 0, 0, 0, 0);

		struct {
			USHORT limit;
			ULONG base;
		} __PACKED__ gdtPtr;

		gdtPtr.limit = (sizeof (GDTENTRY) * 6) - 1;
		gdtPtr.base = (ULONG) & gdt;

		_GdtFlush((ULONG) & gdtPtr);
	}

}
