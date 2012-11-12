#include <Allocator.hpp>

VOID * operator new(UINT size) {
	GAllocator * allocator = GAllocator::GetDefault();
	VOID * addr = allocator->Alloc(size);
	return addr;
}

VOID * operator new[](UINT size) {
	GAllocator * allocator = GAllocator::GetDefault();
	VOID * addr = allocator->Alloc(size);
	return addr;
}

VOID operator delete(VOID *P) {
	GAllocator * allocator = GAllocator::GetDefault();
	allocator->Free(P);
}

VOID operator delete[](VOID *P) {
	GAllocator * allocator = GAllocator::GetDefault();
	allocator->Free(P);
}

