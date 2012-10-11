#include <Types.hpp>

void* operator new(UINT size) {
	return (void*) 0;
}

void* operator new[](UINT size) {
	return (void*) 0;
}

void operator delete(void *P) {

}

void operator delete[](void *P) {

}

