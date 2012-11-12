#include <Mem/PhysicalMemory.hpp>
#include <Mem/VirtualMemory.hpp>
#include <Kernel.hpp>
#include <ScreenIo.hpp>
#include <string.h>

EXTERN ULONG KEndAddress;

namespace Generix {

	GPhysicalMemory GPhysicalMemory::m_Instance;

	GPhysicalMemory::GPhysicalMemory() : m_PhyMemMap(ZERO) {

	}

	GPhysicalMemory::~GPhysicalMemory() {

	}

	VOID GPhysicalMemory::MapMark(UINT bit) {
		m_PhyMemMap[ bit / 32 ] |= (1 << (bit % 32));
	}

	VOID GPhysicalMemory::MapUnmark(UINT bit) {
		m_PhyMemMap[ bit / 32 ] &= ~(1 << (bit % 32));
	}

	BOOL GPhysicalMemory::MapTest(UINT bit) {
		return (m_PhyMemMap[ bit / 32 ] & (1 << (bit % 32)));
	}

	INT GPhysicalMemory::MapFirstFree() {
		for (INT i = 0; i < (INT) (GetMaxBlocks() / 32); i++) {
			if (m_PhyMemMap[i] != 0xffffffff) {
				for (INT j = 0; j < 32; j++) { //! test each bit in the dword
					INT bit = 1 << j;
					if (!(m_PhyMemMap[i] & bit))
						return i * 4 * 8 + j;
				}
			}
		}
		return -1;
	}

	ULONG GPhysicalMemory::GetTotalMemory() {
		return m_TotalMemory;
	}

	ULONG GPhysicalMemory::GetMaxBlocks() {
		return m_MaxBlocks;
	}

	ULONG GPhysicalMemory::GetUsedBlocks() {
		return m_UsedBlocks;
	}

	ULONG GPhysicalMemory::GetFreeBlocks() {
		return (GetMaxBlocks() - GetUsedBlocks());
	}

	VOID GPhysicalMemory::Init() {

		GKernel *kernel = GKernel::Instance();
		PMULTIBOOTINFO mbi = kernel->GetMultiBootInfo();
		m_TotalMemory = mbi->MemoryLow + mbi->MemoryHigh + 1024;
		m_MaxBlocks = (m_TotalMemory * 1024) / PAGESIZE;
		m_UsedBlocks = 0; //m_MaxBlocks;
		m_PhyMemMap = (ULONG*) PAGE_ROUND_UP(KEndAddress);
		memset(m_PhyMemMap, 0, m_MaxBlocks / BLOCKS_PER_BYTE);

		PMEMORYMAP map_addr = (PMEMORYMAP) mbi->MemoryMapAddress;
		UINT map_len = mbi->MemoryMapLength;
		UINT limit = (UINT) map_addr + map_len;
		UINT i = (UINT) map_addr;
		/*UINT region = 0;

		while(i < limit)
		{
			PMEMORYMAP me = (PMEMORYMAP) i;
			printk("region=%-3d base=%-20x length=%-20d type=%d\n",region++,me->BaseAddressLow,me->LengthLow,me->Type);
			if(me->Type == 1)
			{
				INT align = me->BaseAddressLow / PAGESIZE;
				INT blocks = me->LengthLow / PAGESIZE;
				for(;blocks>=0;blocks--)
				{
					MapUnmark(align++);
					m_UsedBlocks--;
				}
			}
			i += me->Size + sizeof(UINT);
		}*/

		i = 0; //0x100000;
		KEndAddress += (m_MaxBlocks / BLOCKS_PER_BYTE);
		limit = PAGE_ROUND_UP(KEndAddress) / PAGESIZE;
		while (i < limit) {
			MapMark(i);
			m_UsedBlocks++;
			i++;
		}
	}

	ULONG GPhysicalMemory::Alloc() {
		if ((INT) GetFreeBlocks() < 0)
			return 0;

		INT frame = MapFirstFree();

		if (frame == -1)
			return 0;

		MapMark(frame);
		ULONG addr = frame * PAGESIZE;
		m_UsedBlocks++;

		return addr;
	}

	VOID GPhysicalMemory::Free(VOID *p) {
		ULONG addr = (ULONG) p;
		INT frame = addr / PAGESIZE;
		MapUnmark(frame);
		m_UsedBlocks--;
	}

} /*namespace Generix*/