/*
 * Memory.hpp
 *
 *  Created on: Oct 1, 2012
 *      Author: dnyanesh
 */

#ifndef __GENERIX_MEMORY_HPP__
#define __GENERIX_MEMORY_HPP__

#include <Types.hpp>
#include <Macros.hpp>

namespace Generix {

class GMemory {
	friend class GMemoryManager;
public:
protected:
private:
	GMemory();
	~GMemory();
};

} /* namespace Generix */
#endif //__GENERIX_MEMORY_HPP__
