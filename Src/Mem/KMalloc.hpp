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
#include <Mem/PhysicalMemory.hpp>

class GKMalloc {
public:
	STATIC VOID * Alloc(Size sz);
	STATIC VOID Free(VOID * address);
protected:
private:
	GKMalloc();
	~GKMalloc();
};

#ifdef CPP
EXTERN "C" {
#endif

	EXTERN VOID * kmalloc(Size size);
	EXTERN VOID kfree(VOID * address);

#ifdef CPP
}
#endif

#endif	//__GENERIX_MEM_KMALLOC_HPP__

