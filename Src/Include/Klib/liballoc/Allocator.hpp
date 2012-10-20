/*
 * File:   GAllocator.hpp
 * Author: dnyanesh
 *
 * Created on October 17, 2012, 7:27 PM
 */

#ifndef __GENERIX_KLIB_LIBALLOC_GALLOCATOR_HPP__
#define	__GENERIX_KLIB_LIBALLOC_GALLOCATOR_HPP__

#include <Types.hpp>
#include <Macros.hpp>

class GAllocator {
public:
	GAllocator();
	virtual ~GAllocator();

	STATIC GAllocator* GetDefault();
	STATIC VOID SetDefault(const GAllocator *allocator);
	virtual VOID* Alloc(Size sz) = 0;
	virtual VOID  Free(VOID *address) = 0;
protected:
private:
	STATIC GAllocator *m_p_defaultAllocator;
};

#endif	//__GENERIX_KLIB_LIBALLOC_GALLOCATOR_HPP__

