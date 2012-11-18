#include <Kernel.hpp>

namespace Generix {

	GKernel::GKernel() : m_MBH(ZERO), m_MBI(ZERO) {
		m_cpu = GProcessor::Instance();
		m_MemMngr = GMemoryManager::Instance();
	}

	GKernel::~GKernel() {
	}

	VOID GKernel::MemoryInit() {
		m_MemMngr->Init();
	}

	VOID GKernel::setMultiBootHeader(PMULTIBOOTHEADER mbh) {
		m_MBH = mbh;
	}

	VOID GKernel::setMultiBootInfo(PMULTIBOOTINFO mbi) {
		m_MBI = mbi;
	}

	PMULTIBOOTHEADER GKernel::getMultiBootHeader() {
		return m_MBH;
	}

	PMULTIBOOTINFO GKernel::getMultiBootInfo() {
		return m_MBI;
	}

	GProcessor* GKernel::getCpu() {
		return m_cpu;
	}

}
