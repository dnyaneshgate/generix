#ifndef __GENERIX_MEM_VIRTUAL_MEMORY_HPP__
#define __GENERIX_MEM_VIRTUAL_MEMORY_HPP__

#include <Types.hpp>
#include <Macros.hpp>

#define PAGESIZE 0x1000
#define PAGEMASK 0xfffff000
#define PAGE_PRESENT BIT(0)
#define PAGE_WRITE BIT(1)
#define PAGE_USER BIT(2)
#define PAGE_ACCESS BIT(5)
#define PAGE_DIRTY BIT(6)

#define PAGE_ROUND(x) AND(x,PAGEMASK)

#define PAGE_ROUND_UP(x) (AND(x,PAGEMASK)+PAGESIZE)

#define PAGE_DIR_INDEX(x) SHR(x,22)

#define PAGE_TABLE_INDEX(x) AND(SHR(x,12),0x3ff)

namespace Generix {

	class GVirtualMemory {
		friend class GMemory;
		friend class GPhysicalMemory;
	public:
		STATIC GVirtualMemory *Instance() {
			return &m_Instance;
		}
	private:
		GVirtualMemory();
		~GVirtualMemory();
		VOID Init();

		STATIC GVirtualMemory m_Instance;
	};
}

#endif //__GENERIX_MEM_VIRTUAL_MEMORY_HPP__