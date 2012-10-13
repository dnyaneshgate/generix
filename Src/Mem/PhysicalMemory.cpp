#include <Mem/PhysicalMemory.hpp>
#include <Kernel.hpp>
#include <ScreenIo.hpp>

namespace Generix {

	GPhysicalMemory::GPhysicalMemory() {

	}

	GPhysicalMemory::~GPhysicalMemory() {

	}

	VOID GPhysicalMemory::Init() {
		GKernel *kernel = GKernel::Instance();
		PMULTIBOOTINFO mbi = kernel->GetMultiBootInfo();
		m_TotalMemory = mbi->MemoryHigh + mbi->MemoryLow;
		ULONG mmap = mbi->MemoryMapAddress;
		ULONG mmap_len = mbi->MemoryMapLength;
		ULONG limit = mmap + mmap_len;
		ULONG i = mmap;
		printk("================================================================================");
		printk("                                MemoryMap\n");
		printk("================================================================================");
		while (i < limit) {
			PMEMORYMAP me = (PMEMORYMAP) i;
			printk("base : %04u %04u      length : %04u %04u   >> ", me->BaseAddressHigh, me->BaseAddressLow, me->LengthHigh, me->LengthLow);
			if (me->Type == MULTIBOOT_MEM_FLAG_FREE) {
				printk("Available\n");
			} else {
				printk("Reserved\n");
			}
			i += me->Size + sizeof (ULONG);
		}
	}

} /*namespace Generix*/