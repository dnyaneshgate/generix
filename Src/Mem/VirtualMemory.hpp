#ifndef __GENERIX_MEM_VIRTUAL_MEMORY_HPP__
#define __GENERIX_MEM_VIRTUAL_MEMORY_HPP__

#include <Types.hpp>
#include <Macros.hpp>

#define PAGESIZE 0x1000
#define PAGEMASK 0xfffff000
#define PAGE_PRESENT 0x01
#define PAGE_WRITE 0x02
#define PAGE_USER 0x03
#define PAGE_ACCESS 0x04
#define PAGE_DIRTY 0x05

#define PAGE_ROUND(x) \
		((x) & PAGEMASK)

#define PAGE_ROUND_UP(x) \
		(((x)&PAGEMASK)+PAGESIZE)

#define PAGE_DIR_INDEX(x) SHR(x,22)

#define PAGE_TABLE_INDEX(x) (SHR(x,12) & 0x3ff)



namespace Generix {

	class GVirtualMemory {
		friend class GMemory;
		friend class GPhysicalMemory;
	private:
		GVirtualMemory();
		~GVirtualMemory();
		VOID Init();
		STATIC GVirtualMemory *Instance()
		{
			return &m_Instance;
		}

		STATIC GVirtualMemory m_Instance;
	};

}

#endif //__GENERIX_MEM_VIRTUAL_MEMORY_HPP__