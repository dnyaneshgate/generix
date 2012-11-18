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
#include <Singleton.hpp>
#include <Allocator.hpp>

namespace Generix {

	#define CHUNK_MAGIC  0x123456ABCD

	typedef struct strucHEAP {
		UINT * Start;
		UINT * End;
		UINT Size;
		UINT * Top;
	} __PACKED__ HEAP, *PHEAP;

	typedef struct strucCHUNK{
		UINT Magic;
		UINT Used : 1;
		UINT Size;
		strucCHUNK * Next;
		strucCHUNK * Prev;
	} __PACKED__ CHUNK, *PCHUNK;

	#define CHUNKSIZE sizeof(CHUNK)

	class GKMalloc : public GAllocator, public GSingleton<GKMalloc> {
	friend class GSingleton<GKMalloc>;
	public:
		VOID * Alloc(Size sz);
		VOID Free(VOID * address);
	protected:
	private:
		GKMalloc();
		~GKMalloc();
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
