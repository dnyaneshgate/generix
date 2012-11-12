#include <Allocator.hpp>

GAllocator * GAllocator::m_p_defaultAllocator = 0;

GAllocator::GAllocator() {
}

GAllocator::~GAllocator() {
}

VOID GAllocator::SetDefault(GAllocator* allocator) {
	m_p_defaultAllocator = allocator;
}

GAllocator* GAllocator::GetDefault() {
	return m_p_defaultAllocator;
}