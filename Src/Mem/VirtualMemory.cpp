#include <Mem/VirtualMemory.hpp>
#include <Mem/PhysicalMemory.hpp>

namespace x86Paging {

	typedef struct strucPAGETABLE {
		ULONG pages[1024];
	} PAGETABLE, *PPAGETABLE;

	typedef struct strucPAGEDIRECTORY {
		PPAGETABLE tables[1024];
	} PAGEDIRECTORY, *PPAGEDIRECTORY;

	PPAGEDIRECTORY KernelDirectory = ZERO;
	PPAGEDIRECTORY CurrentDirectory = ZERO;

	INT MAPPAGE(PAddress pAddr, VAddress vAddr) {
		INT table = PAGE_DIR_INDEX(vAddr);
		INT page = PAGE_TABLE_INDEX(vAddr);

		if (AND(CurrentDirectory->tables[table],PAGE_PRESENT)) {
			ULONG *pageTable = (ULONG*) (0xffc00000 + (table * PAGESIZE));
			if (!AND(pageTable[page], PAGE_PRESENT)) {
				pageTable[page] = OR(pAddr, 3);
			} else {
				return -1;
			}
		} else {
			ULONG *newPageTable = (ULONG*) (Generix::GPhysicalMemory::Instance()->Alloc());
			ULONG *pageTable = (ULONG*) (0xffc00000 + (table * PAGESIZE));
			CurrentDirectory->tables[table] = OR(newPageTable, 3);
			pageTable[page] = OR(pAddr, 3);
		}
		return 0;
	}

	INT UNMAPPAGE(VAddress vAddr) {
		INT table = PAGE_DIR_INDEX(vAddr);
		INT page = PAGE_TABLE_INDEX(vAddr);
		
		if(AND(CurrentDirectory->tables[table],PAGE_PRESENT))
		{
			ULONG *pageTable = (ULONG*)(0xffc00000 + (table*PAGESIZE));
			if(AND(pageTable[page],PAGE_PRESENT))
			{
				pageTable[page] = 2;
			}
			INT i;
			for(i=0;i<1024;i++)
				if(AND(pageTable[i],PAGE_PRESENT))
					break;
			
			if( i == 1024 )
			{
				Generix::GPhysicalMemory::Instance()->Free(AND(CurrentDirectory->tables[table],PAGEMASK));
				CurrentDirectory->tables[table] = 2;
			}
				
		}
		return 0;
	}
}

using namespace x86Paging;

namespace Generix {

	GVirtualMemory GVirtualMemory::m_Instance;

	GVirtualMemory::GVirtualMemory() {
	}

	GVirtualMemory::~GVirtualMemory() {

	}

	VOID GVirtualMemory::Init() {

	}
}