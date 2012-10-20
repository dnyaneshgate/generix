#ifndef __GENERIX_MEM_VIRTUAL_MEMORY_HPP__
#define __GENERIX_MEM_VIRTUAL_MEMORY_HPP__

#include <Types.hpp>
#include <Macros.hpp>
#include <Mem/Paging.hpp>
#include <Processor/Arch/CPU.hpp>

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

EXTERN BOOL isPagingEnabled;

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
		STATIC VOID PageFaultHandler(REG reg);

		STATIC GVirtualMemory m_Instance;
	};
}

#endif //__GENERIX_MEM_VIRTUAL_MEMORY_HPP__