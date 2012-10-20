/*
 * File:   Paging.hpp
 * Author: dnyanesh
 *
 * Created on October 20, 2012, 9:05 PM
 */

#ifndef __GENERIX_MEM_PAGING_HPP__
#define	__GENERIX_MEM_PAGING_HPP__

#include <Types.hpp>
#include <Macros.hpp>

#define PAGESIZE      0x1000
#define PAGEMASK      0xfffff000
#define PAGE_PRESENT  BIT(0)
#define PAGE_WRITE    BIT(1)
#define PAGE_USER     BIT(2)
#define PAGE_ACCESS   BIT(5)
#define PAGE_DIRTY    BIT(6)

#define PAGE_ROUND(x)            (x AND PAGEMASK)
#define PAGE_ROUND_UP(x)         ((x AND PAGEMASK)+PAGESIZE)
#define PAGE_DIR_INDEX(x)        (SHR(x,22) AND 0x3ff)
#define PAGE_TABLE_INDEX(x)      (SHR(x,12) AND 0x3ff)
#define SETATTRIBUTE(page,flag)  (page OR flag)

#define PAGEBIT                  0x80000000

#ifdef __x86__

namespace x86Paging {
	typedef UINT PTE, *PPTE, **PPPTE;
	typedef UINT PDE, *PPDE, **PPPDE;

	typedef struct strucPAGETABLE {
		PTE pages[1024];
	} PAGETABLE, *PPAGETABLE;

	typedef struct strucPAGEDIRECTORY {
		PDE tables[1024];
	} PAGEDIRECTORY, *PPAGEDIRECTORY;

	EXTERN PPAGEDIRECTORY KernelDirectory;
	EXTERN PPAGEDIRECTORY CurrentDirectory;

	INT MAPPAGE(PAddress pAddr, VAddress vAddr, UINT flag);
	INT UNMAPPAGE(VAddress vAddr);
	INT SWITCHPAGEDIR(PPAGEDIRECTORY dir);
}

#endif

#endif	//__GENERIX_MEM_PAGING_HPP__

