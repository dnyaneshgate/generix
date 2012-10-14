/*
 * MemoryManager.hpp
 *
 *  Created on: Oct 1, 2012
 *      Author: dnyanesh
 */

#ifndef __GENERIX_MEMORYMANAGER_HPP__
#define __GENERIX_MEMORYMANAGER_HPP__

#include <Mem/Memory.hpp>

namespace Generix {

	class GMemoryManager {
		friend class GKernel;
	public:
	protected:
	private:
		GMemoryManager();
		~GMemoryManager();
		VOID Init();
		STATIC GMemoryManager *Instance()
		{
			return &m_Instance;
		}

		STATIC GMemoryManager m_Instance;
		GMemory *m_Mem;
	};

}

#endif //__GENERIX_MEMORYMANAGER_HPP__
