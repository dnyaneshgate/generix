#ifndef __GENERIX_MEM_VIRTUAL_MEMORY_HPP__
#define __GENERIX_MEM_VIRTUAL_MEMORY_HPP__

#include <Types.hpp>
#include <Macros.hpp>

#define USER_STACK_BOTTOM  0xB0000000
#define USER_STACK_TOP     0xC0000000
#define KERNEL_OFFSET      0xC0000000
#define KERNEL_HEAP_START  0xE0000000
#define KERNEL_HEAP_END    0xF0000000
#define PMM_PAGE_STACK     0xFE000000
#define VMM_TEMP2          0xFF7FE000
#define VMM_TEMP1          0xFF7FF000
#define VMM_EXPAGE_TABLES  0xFF800000
#define VMM_EXPAGE_DIR     0xFFBFF000
#define VMM_PAGE_TABLES    0xFFC00000
#define VMM_PAGE_DIR       0xFFFFF000

#define VMM_PAGES_PER_TABLE 1024

#define PAGESIZE      0x1000
#define PAGEMASK      0xfffff000
#define PAGE_PRESENT  BIT(0)
#define PAGE_WRITE    BIT(1)
#define PAGE_USER     BIT(2)
#define PAGE_ACCESS   BIT(5)
#define PAGE_DIRTY    BIT(6)

#define PAGE_ROUND(x)            AND(x,PAGEMASK)
#define PAGE_ROUND_UP(x)         (AND(x,PAGEMASK)+PAGESIZE)
#define PAGE_DIR_INDEX(x)        AND(SHR(x,22),0x3ff)
#define PAGE_TABLE_INDEX(x)      AND(SHR(x,12),0x3ff)
#define SETATTRIBUTE(page,flag)  OR(page,flag)

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