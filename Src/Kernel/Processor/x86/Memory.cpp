#include <Processor/x86/Memory.hpp>
#include <Processor/x86/CPU.hpp>
#include <Processor/x86/IOPort.hpp>
#include <Kernel.hpp>
#include <ScreenIo.hpp>
#include <string.h>

namespace Generix {

	VOID pageFaultHandler(REG reg);

	UINT * pageDirectory = (UINT*)VMM_PAGE_DIR;
	UINT * pageTable     = (UINT*)VMM_PAGE_TABLES;

	x86GMemory::x86GMemory() {
		GKernel * kernel = GKernel::Instance();
		GProcessor * CPU = kernel->getCpu();
		CPU->RegInterrupt(14, pageFaultHandler);
	}

	x86GMemory::~x86GMemory() {
	}

	Address x86GMemory::mapVirtual(PAddress pAddr, VAddress vAddr, UINT flags) {
		UINT page = pAddr AND PAGE_MASK;
		flags &= PAGE_FLAG_MASK;

		if( NOT (pageDirectory[PAGE_DIR_INDEX(page)] AND PAGE_PRESENT) ) {
			pageDirectory[PAGE_DIR_INDEX(page)] = allocPhysical() OR flags;
			FLUSHTLB((UINT)&pageTable[PAGE_TABLE_INDEX(page)] AND PAGE_MASK);
			memset((VOID*)((UINT)&pageTable[PAGE_TABLE_INDEX(page)] AND PAGE_MASK), 0, PAGESIZE);
		}
		pageTable[PAGE_TABLE_INDEX(page)] = pAddr OR flags;
		FLUSHTLB(page);
		return vAddr;
	}

	VOID x86GMemory::umapVirtual(VAddress vAddr) {
		if( pageDirectory[PAGE_DIR_INDEX(vAddr)] AND PAGE_PRESENT ) {
			if( pageTable[PAGE_TABLE_INDEX(vAddr)] AND PAGE_PRESENT ) {
				pageTable[PAGE_TABLE_INDEX(vAddr)] = 2;
			}

			INT i;
			for (i = 0; i LT 1024; i++)
				if ((pageTable[i] AND PAGE_PRESENT))
					break;

			if (i EQU 1024) {
				freePhysical(pageDirectory[PAGE_DIR_INDEX(vAddr)] AND PAGE_MASK);
				pageDirectory[PAGE_DIR_INDEX(vAddr)] = 2;
			}
		}
	}

	VOID pageFaultHandler(REG reg) {
		ULONG faultAddress;
		GIOPort::ReadCRX(2, &faultAddress);
		INT present = !(reg.error AND 0x1);
		INT rw = reg.error AND 0x2;
		INT us = reg.error AND 0x4;
		INT reserved = reg.error AND 0x8;

		printk("Page fault! (");
		if (present) printk(" present ");
		if (rw) printk(" readonly ");
		if (us) printk(" user-mode ");
		if (reserved) printk(" reserved ");
		printk(") at 0x%x\n", UINT(faultAddress));
		printk("eip: 0x%x\n", UINT(reg.eip));

		CLI();
		HLT();
	}

	x86GMemory * Memory = x86GMemory::Instance();

}
