/*
 * File:   KHeap.hpp
 * Author: dnyanesh
 *
 * Created on November 10, 2012, 8:06 PM
 */

#ifndef __GENERIX_MEM_KHEAP_HPP__
#define	__GENERIX_MEM_KHEAP_HPP__

#include <Types.hpp>
#include <Macros.hpp>

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

#endif	/* __GENERIX_MEM_KHEAP_HPP__ */

