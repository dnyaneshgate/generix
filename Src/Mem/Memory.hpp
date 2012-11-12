/*
 * Memory.hpp
 *
 *  Created on: Oct 1, 2012
 *      Author: dnyanesh
 */

#ifndef __GENERIX_MEM_MEMORY_HPP__
#define __GENERIX_MEM_MEMORY_HPP__

#include <Types.hpp>
#include <Macros.hpp>

#include <Mem/PhysicalMemory.hpp>
#include <Mem/VirtualMemory.hpp>

namespace Generix {

	class GMemory {
		friend class GMemoryManager;
	private:
		GMemory();
		~GMemory();
		VOID Init();

		STATIC GMemory *Instance() {
			return &m_Instance;
		}
		STATIC GMemory m_Instance;
		GPhysicalMemory *m_PhyMem;
		GVirtualMemory *m_VirtMem;
	};

} /* namespace Generix */
#endif //__GENERIX_MEM_MEMORY_HPP__
