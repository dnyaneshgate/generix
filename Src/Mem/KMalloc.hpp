/*
 * File:   KMalloc.hpp
 * Author: dnyanesh
 *
 * Created on October 17, 2012, 7:22 PM
 */

#ifndef __GENERIX_MEM_KMALLOC_HPP__
#define	__GENERIX_MEM_KMALLOC_HPP__

#include <Types.hpp>
#include <Macros.hpp>
#include <Allocator.hpp>

namespace Generix {

	class GKMalloc : public GAllocator {
	public:
		VOID * Alloc(Size sz);
		VOID Free(VOID * address);
		STATIC GKMalloc * Instance() {
			return &m_p_Instance;
		}
	protected:
	private:
		GKMalloc();
		~GKMalloc();

		STATIC GKMalloc m_p_Instance;
	};

#ifdef CPP
	EXTERN "C"
	{
#endif

		EXTERN VOID * kmalloc(Size size);
		EXTERN VOID kfree(VOID * address);

#ifdef CPP
	}
#endif

}

#endif	//__GENERIX_MEM_KMALLOC_HPP__

