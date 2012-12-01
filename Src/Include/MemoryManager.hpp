/*
 * MemoryManager.hpp
 *
 *  Created on: Oct 1, 2012
 *      Author: dnyanesh
 */

#ifndef __GENERIX_MEMORYMANAGER_HPP__
#define __GENERIX_MEMORYMANAGER_HPP__

#include <Processor/Arch/Memory.hpp>

namespace Generix {

	class GMemoryManager : public GSingleton<GMemoryManager> {
		friend class GSingleton<GMemoryManager>;
		friend class GKernel;
	public:
	protected:
	private:
		GMemoryManager();
		~GMemoryManager();
		VOID Init();
	};

}

#endif //__GENERIX_MEMORYMANAGER_HPP__
