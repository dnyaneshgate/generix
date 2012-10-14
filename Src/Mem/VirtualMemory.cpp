#include <Mem/VirtualMemory.hpp>
#include <Mem/PhysicalMemory.hpp>

namespace x86Paging {

	typedef struct strucPAGETABLE {
		ULONG pages[1024];
	} PAGETABLE, *PPAGETABLE;

	typedef struct strucPAGEDIRECTORY {
		PAGETABLE tables[1024];
	} PAGEDIRECTORY, *PPAGEDIRECTORY;

	PPAGEDIRECTORY KernelDirectory = ZERO;
	PPAGEDIRECTORY CurrentDirectory = ZERO;
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