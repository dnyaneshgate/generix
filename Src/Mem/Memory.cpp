/*
 * Memory.cpp
 *
 *  Created on: Oct 1, 2012
 *      Author: dnyanesh
 */

#include "Memory.hpp"
#include "KHeap.hpp"
#include "KMalloc.hpp"

EXTERN ULONG __KERNEL_END;
ULONG KEndAddress = (ULONG) & __KERNEL_END;

namespace Generix {

	GMemory GMemory::m_Instance;

	GMemory::GMemory() {
		// TODO Auto-generated constructor stub
		m_PhyMem = GPhysicalMemory::Instance();
		m_VirtMem = GVirtualMemory::Instance();
	}

	GMemory::~GMemory() {
		// TODO Auto-generated destructor stub
	}

	VOID GMemory::Init() {
		m_PhyMem->Init();
		m_VirtMem->Init();
		GKMalloc * kMalloc = GKMalloc::Instance();
		GAllocator::SetDefault(kMalloc);
	}

} /* namespace Generix */
