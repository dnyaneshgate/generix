#ifndef __GENERIX_MEM_PHYSICAL_MEMORY_HPP__
#define __GENERIX_MEM_PHYSICAL_MEMORY_HPP__

#include <Types.hpp>
#include <Macros.hpp>

#define PHY_PAGE_SIZE          0x1000
#define PHY_PAGE_MASK          0xFFFFF000
#define PHY_PAGE_F_MASK        0x00000FFF

namespace Generix {

	class GPhysicalMemory {
	public:
		VOID Init();
		GPhysicalMemory();
		~GPhysicalMemory();
	protected:
	private:
		ULONG m_TotalMemory;
		ULONG m_UsedMemory;
		ULONG m_PhyMemStack;
	};

}

#endif //__GENERIX_MEM_PHYSICAL_MEMORY_HPP__
