#ifndef __GENERIX_MEM_PHYSICAL_MEMORY_HPP__
#define __GENERIX_MEM_PHYSICAL_MEMORY_HPP__

#include <Types.hpp>
#include <Macros.hpp>

#define BLOCKS_PER_BYTE 8
#define PHY_PAGE_SIZE          0x1000
#define PHY_PAGE_MASK          0xFFFFF000

namespace Generix {

	class GPhysicalMemory {
		friend class GMemory;
		friend class GVirtualMemory;
	public:
		STATIC GPhysicalMemory *Instance() {
			return &m_Instance;
		}
		ULONG GetTotalMemory();
		ULONG GetMaxBlocks();
		ULONG GetUsedBlocks();
		ULONG GetFreeBlocks();

		ULONG Alloc();
		VOID Free(VOID *ddr);
	private:
		GPhysicalMemory();
		~GPhysicalMemory();
		VOID Init();

		VOID MapMark(UINT bit);
		VOID MapUnmark(UINT bit);
		BOOL MapTest(UINT bit);
		INT MapFirstFree();

		STATIC GPhysicalMemory m_Instance;
		ULONG m_TotalMemory;
		ULONG m_UsedBlocks;
		ULONG m_MaxBlocks;
		ULONG *m_PhyMemMap;
	};

}

#endif //__GENERIX_MEM_PHYSICAL_MEMORY_HPP__
