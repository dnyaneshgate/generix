#include <Mem/VirtualMemory.hpp>
#include <Mem/PhysicalMemory.hpp>
#include <string.h>

#include <Processor/Arch/IOPort.hpp>
#include <Kernel.hpp>
#include <ScreenIo.hpp>

EXTERN ULONG KEndAddress;
BOOL isPagingEnabled = false;

namespace Generix {

#ifdef __x86__
	using namespace x86Paging;
#endif

	GVirtualMemory GVirtualMemory::m_Instance;

	GVirtualMemory::GVirtualMemory() {
	}

	GVirtualMemory::~GVirtualMemory() {
	}

	VOID GVirtualMemory::Init() {

		UINT i, frame, virt;

		PPAGETABLE IdentityPageTable = ZERO;
		PPAGETABLE KernelPageTable = ZERO;

		KernelDirectory = PPAGEDIRECTORY(GPhysicalMemory::Instance()->Alloc());
		if (NOT KernelDirectory)
			return;

		memset(KernelDirectory, 0, sizeof (PAGEDIRECTORY));

		//Identity Page Mapping Start
		IdentityPageTable = PPAGETABLE(GPhysicalMemory::Instance()->Alloc());
		if (NOT IdentityPageTable)
			return;

		memset(IdentityPageTable, 0, sizeof (PAGETABLE));

		for (i = 0, frame = 0x0, virt = 0x0;
				i LT PAGES_PER_TABLE;
				i++, frame += PAGESIZE, virt += PAGESIZE) {
			PTE page = PTE(PAGE_ROUND(frame));
			SETATTRIBUTE(page, (PAGE_PRESENT OR PAGE_WRITE));
			IdentityPageTable->pages[ PAGE_TABLE_INDEX(virt) ] = page;
		}

		PPDE entry1 = PPDE(&KernelDirectory->tables[ PAGE_DIR_INDEX(0x00000000) ]);
		SETATTRIBUTE(*entry1, (PAGE_PRESENT OR PAGE_WRITE));
		SETATTRIBUTE(*entry1, UINT(IdentityPageTable));
		//Identity Page Mapping End


		//Higher Half Kernel Page Mapping Start
		KernelPageTable = PPAGETABLE(GPhysicalMemory::Instance()->Alloc());
		if (NOT KernelPageTable)
			return;

		memset(KernelPageTable, 0, sizeof (PAGETABLE));

		for (i = 0, frame = 0x100000, virt = KERNEL_OFFSET;
				i LT PAGES_PER_TABLE;
				i++, frame += PAGESIZE, virt += PAGESIZE) {
			PTE page = PTE(PAGE_ROUND(frame));
			SETATTRIBUTE(page, (PAGE_PRESENT OR PAGE_WRITE));
			KernelPageTable->pages[ PAGE_TABLE_INDEX(virt) ] = page;
		}

		PPDE entry2 = PPDE(&KernelDirectory->tables[ PAGE_DIR_INDEX(KERNEL_OFFSET) ]);
		SETATTRIBUTE(*entry2, (PAGE_PRESENT OR PAGE_WRITE));
		SETATTRIBUTE(*entry2, UINT(KernelPageTable));
		//Higher Half Kernel Page Mapping End

		//map directory to directory itself
		UINT *lastEntry = (UINT*) & KernelDirectory[1023];
		*lastEntry = UINT(&KernelDirectory[0]) OR PAGE_PRESENT OR PAGE_WRITE;

		GProcessor *CPU = GKernel::Instance()->GetCpu(); //get Processor Instance
		CPU->RegInterrupt(14, PageFaultHandler); //Install Page Fault Handler

		SWITCHPAGEDIR(KernelDirectory); //Switch To Kernel Directory

		isPagingEnabled = true;
	}

	VOID GVirtualMemory::PageFaultHandler(REG reg) {
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
}