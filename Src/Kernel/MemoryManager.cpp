/*
 * MemoryManager.cpp
 *
 *  Created on: Oct 1, 2012
 *      Author: dnyanesh
 */


#include <MemoryManager.hpp>

namespace Generix {

	GMemoryManager::GMemoryManager() {
	}

	GMemoryManager::~GMemoryManager() {
	}

	VOID GMemoryManager::Init() {
		m_Mem.Init();
	}

}
