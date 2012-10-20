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
		KernelDirectory = PPAGEDIRECTORY(Generix::GPhysicalMemory::Instance()->Alloc());
		memset(KernelDirectory, 0, sizeof (PAGEDIRECTORY));

		UINT i = 0;
		VAddress virt = 0;
		PAddress frame = 0;

		for (i = 0, virt = 0x0, frame = 0x0;
				i LT 1024;
				i++, virt += PAGESIZE, frame += PAGESIZE) {
			MAPPAGE(frame, virt, (ZERO OR PAGE_PRESENT OR PAGE_WRITE));
		}

		for (i = 0, virt = KERNEL_OFFSET, frame = 0x100000;
				i LT 1024;
				i++, virt += PAGESIZE, frame += PAGESIZE) {
			MAPPAGE(frame, virt, (ZERO OR PAGE_PRESENT OR PAGE_WRITE));
		}

		GProcessor *CPU = GKernel::Instance()->GetCpu();
		CPU->RegInterrupt(14,PageFaultHandler);

		//SWITCHPAGEDIR(KernelDirectory);

		isPagingEnabled = true;
	}

	VOID GVirtualMemory::PageFaultHandler(REG reg) {
		ULONG faultAddress;
		GIOPort::ReadCRX(2,&faultAddress);
		printk("PAGE FAULT at 0x%x\n",faultAddress);
		CLI();
		HLT();
	}
}