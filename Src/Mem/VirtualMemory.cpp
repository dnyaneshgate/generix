#include <Mem/VirtualMemory.hpp>
#include <Mem/PhysicalMemory.hpp>
#include <string.h>

#include <Processor/Arch/IOPort.hpp>
#include <Kernel.hpp>
#include <ScreenIo.hpp>

#ifdef __x86__
using namespace x86Paging;
#endif

EXTERN ULONG KEndAddress;
BOOL isPagingEnabled = false;

namespace Generix {

	GVirtualMemory GVirtualMemory::m_Instance;

	GVirtualMemory::GVirtualMemory() {
	}

	GVirtualMemory::~GVirtualMemory() {

	}

	VOID GVirtualMemory::Init() {

		Console::Color col = Console::GetFontColor();
		Console::SetFontColor(Console::DARKGRAY);
		Console::Writeln("%-30s : Initializing Virtual Memory","GVirtualMemory::Init()");
		Console::SetFontColor(col);

		UINT i, frame, virt;

		PPAGETABLE IdentityPageTable = ZERO;
		PPAGETABLE KernelPageTable = ZERO;

		KernelDirectory = PPAGEDIRECTORY(GPhysicalMemory::Instance()->Alloc());
		if (NOT KernelDirectory)
			return;

		memset(KernelDirectory, 0, sizeof (PAGEDIRECTORY));

		//map directory to directory itself
		UINT *lastEntry = (UINT*)&KernelDirectory[1023];
		*lastEntry = UINT(KernelDirectory) OR PAGE_PRESENT OR PAGE_WRITE;

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

		GProcessor *CPU = GKernel::Instance()->GetCpu(); //get Processor Instance
		CPU->RegInterrupt(14, PageFaultHandler); //Install Page Fault Handler

		SWITCHPAGEDIR(KernelDirectory); //Switch To Kernel Directory

		isPagingEnabled = true;
	}

	VOID GVirtualMemory::PageFaultHandler(REG reg) {
		ULONG faultAddress;
		GIOPort::ReadCRX(2, &faultAddress);
		Console::Writeln("PAGE FAULT at 0x%x", UINT(faultAddress));
		CLI();
		HLT();
	}
}