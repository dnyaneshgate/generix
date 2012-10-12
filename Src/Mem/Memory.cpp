/*
 * Memory.cpp
 *
 *  Created on: Oct 1, 2012
 *      Author: dnyanesh
 */

#include "Memory.hpp"

EXTERN ULONG __KERNEL_END;
ULONG KEndAddress = (ULONG)&__KERNEL_END;

namespace Generix {

	GMemory::GMemory() {
		// TODO Auto-generated constructor stub
	}

	GMemory::~GMemory() {
		// TODO Auto-generated destructor stub
	}

	VOID GMemory::Init() {
		m_PhyMem.Init();
	}

} /* namespace Generix */
