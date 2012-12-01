/*
 * MemoryManager.cpp
 *
 *  Created on: Oct 1, 2012
 *      Author: dnyanesh
 */


#include <MemoryManager.hpp>
#include <Mem/KMalloc.hpp>

namespace Generix {

	GMemoryManager::GMemoryManager() {
	}

	GMemoryManager::~GMemoryManager() {
	}

	VOID GMemoryManager::Init() {
		Memory->Init();
		GKMalloc * kMalloc = GKMalloc::Instance();
		GAllocator::SetDefault(kMalloc);
	}

}
