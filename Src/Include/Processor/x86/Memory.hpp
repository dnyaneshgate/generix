#ifndef __GENERIX_X86_MEMORY_HPP__
#define __GENERIX_X86_MEMORY_HPP__

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

#define PAGESIZE       4096
#define PAGE_MASK      0xfffff000
#define PAGE_FLAG_MASK 0xfff
#define PAGE_PRESENT   BIT(0)
#define PAGE_WRITE     BIT(1)
#define PAGE_USER      BIT(2)
#define PAGE_ACCESS    BIT(5)
#define PAGE_DIRTY     BIT(6)
#define DIRSHIFT       22
#define TBLSHIFT       12

#define PAGE_ROUND(x)            (x AND PAGE_MASK)
#define PAGE_ROUND_UP(x)         ((x AND PAGE_MASK)+PAGESIZE)
#define PAGE_DIR_INDEX(x)        (SHR(x,DIRSHIFT) AND 0x3ff)
#define PAGE_TABLE_INDEX(x)      (SHR(x,TBLSHIFT) AND 0x3ff)
#define SETATTRIBUTE(page,flag)  (page = (page OR flag))

#define TABLES_PER_DIRECTORY     1024
#define PAGES_PER_TABLE          1024

#define CR0_PAGEBIT                  0x80000000

#ifdef __ASSEMBLER__
#define FLUSHTLB(page) invlpg[page]
#else
#define FLUSHTLB(page) \
				__ASM__ __VOLATILE__ ("invlpg (%0)" : : "a" (page & PAGE_MASK))
#endif //__ASSEMBLER__

#ifndef __ASSEMBLER__

#include <Singleton.hpp>
#include <Mem/Memory.hpp>

namespace Generix {

	class x86GMemory : public GMemory, public GSingleton<x86GMemory> {
		friend class GSingleton<x86GMemory>;
		friend class GKernel;
		/*member functions*/
	public:
		Address mapVirtual(PAddress pAddr, VAddress vAddr, UINT flag);
		VOID umapVirtual(VAddress vAddr, UINT flags = PAGE_WRITE);
		PAddress getPhyPage(VAddress vAddr);
		VOID Init();
	protected:
		x86GMemory();
		~x86GMemory();
		VAddress findFree();
	private:

		/*member variables*/
	public:
	protected:
	private:
	};

	EXTERN x86GMemory * Memory;

}
#endif //__ASSEMBLER__

#endif //__GENERIX_X86_MEMORY_HPP__
