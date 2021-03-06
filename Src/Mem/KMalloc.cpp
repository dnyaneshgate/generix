#include <Types.hpp>
#include <Macros.hpp>
#include <Processor/Arch/CPU.hpp>
#include <Processor/Arch/Memory.hpp>
#include <Mem/KMalloc.hpp>
#include <string.h>
#include <stdlib.h>
#include <Assert.hpp>
#include <ScreenIo.hpp>

namespace Generix {
STATIC HEAP kHeap;
STATIC BOOL isHeapInit = false;
STATIC PCHUNK heapStart = 0;

STATIC VOID HeapInit(PHEAP heap) {
	heap->Start = (UINT) KERNEL_HEAP_START;
	heap->End = (UINT) KERNEL_HEAP_END;
	heap->Size = KERNEL_HEAP_END - KERNEL_HEAP_START;
	heap->Top = (UINT) KERNEL_HEAP_START;
	//memset(heap->Start, 0, heap->Size);
	isHeapInit = true;
}

STATIC INT ExpandHeap(PHEAP heap, UINT start, Size size) {
	//printk("ExpandHeap()\n");
	while ((start + size) GT heap->Top) {
		PAddress pAddr = PAddress(Memory->allocPhysical());
		Memory->mapVirtual(pAddr, VAddress(heap->Top),
				PAGE_PRESENT OR PAGE_WRITE);
		heap->Top += PAGESIZE;
		ASSERT(heap->Top < KERNEL_HEAP_END);
	}
	return SUCCESS;
}

STATIC INT ContractHeap(PHEAP heap, PCHUNK chunk) {
	//printk("ContractHeap()\n");
	ASSERT(NOT chunk->Next);

	if (chunk EQU heapStart)
		heapStart = ZERO;
	else
		chunk->Prev->Next = ZERO;

	while ((UINT(heap->Top) - PAGESIZE) GTE UINT(chunk)) {
		Memory->freePhysical(
				Memory->getPhyPage(VAddress(heap->Top)) AND PAGE_MASK);
		Memory->umapVirtual(VAddress(heap->Top));
		heap->Top -= PAGESIZE;
	}

	return SUCCESS;
}

STATIC INT MergeChunk(PHEAP heap, PCHUNK chunk) {
	PCHUNK preChunk = chunk->Prev;
	PCHUNK nxtChunk = chunk->Next;
	if (preChunk and preChunk->Used EQU FALSE) {
		preChunk->Next = chunk->Next;
		preChunk->Size += chunk->Size;
		if (nxtChunk)
			nxtChunk->Prev = preChunk;
		chunk = preChunk;
	}
	if (nxtChunk and nxtChunk->Used == FALSE) {
		chunk->Next = nxtChunk->Next;
		chunk->Size += nxtChunk->Size;
		if (nxtChunk->Next)
			nxtChunk->Next->Prev = chunk;
	}

	//if (NOT chunk->Next)
	//	ContractHeap(heap, chunk);

	return SUCCESS;
}

STATIC INT SplitChunk(PCHUNK chunk, Size sz) {
	if ((chunk->Size - sz) GT CHUNKSIZE) {
		PCHUNK newChunk = (PCHUNK) (UINT(chunk) + sz);
		newChunk->Magic = UINT(CHUNK_MAGIC);
		newChunk->Used = FALSE;
		newChunk->Size = chunk->Size - sz;
		newChunk->Prev = chunk;
		newChunk->Next = chunk->Next;

		chunk->Next = newChunk;
		chunk->Size = sz;
	}
	return SUCCESS;
}

GKMalloc::GKMalloc() {
}

GKMalloc::~GKMalloc() {
}

VOID * GKMalloc::Alloc(Size sz) {
	if (NOT isHeapInit)
		HeapInit(&kHeap);
	sz += CHUNKSIZE;

	PCHUNK curChunk = 0, preChunk = 0;
	curChunk = heapStart;

	while (curChunk) {
		if ((curChunk->Used EQU FALSE) and (curChunk->Size GTE sz)) {
			SplitChunk(curChunk, sz);
			curChunk->Used = TRUE;
			return (VOID*) (UINT(curChunk) + CHUNKSIZE);
		}
		preChunk = curChunk;
		curChunk = curChunk->Next;
	}

	if (preChunk) {
		curChunk = (PCHUNK) (UINT(preChunk) + preChunk->Size);
	} else {
		curChunk = heapStart = (PCHUNK) kHeap.Start;
	}

	ExpandHeap(&kHeap, (UINT) curChunk, sz);

	memset(curChunk, 0, sz);
	curChunk->Prev = preChunk;
	curChunk->Next = 0;
	curChunk->Size = sz;
	curChunk->Used = TRUE;
	if (preChunk)
		preChunk->Next = curChunk;
	return (VOID*) (UINT(curChunk) + CHUNKSIZE);
}

VOID GKMalloc::Free(VOID* address) {
	//printk("Free(%x)\n", (UINT)address);
	ASSERT(
			((UINT) address >= KERNEL_HEAP_START) && ((UINT) address < KERNEL_HEAP_END));
	PCHUNK chunk = (PCHUNK) ((UINT) address - CHUNKSIZE);

	//if (chunk->Magic == (UINT) CHUNK_MAGIC) {
	chunk->Used = FALSE;
	MergeChunk(&kHeap, chunk);
	//} else {
	//	printk("BOGUS MEMORY ADDRESS\n");
	//}
}

VOID * kmalloc(Size size) {
	if (size != ZERO) {
		VOID * addr = GKMalloc::Instance()->Alloc(size);
		return addr;
	}
	return 0;
}

VOID kfree(VOID * P) {
	if (P != NULL) {
		GKMalloc::Instance()->Free(P);
	}
}

}
