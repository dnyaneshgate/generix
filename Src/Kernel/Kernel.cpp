#include <Kernel.hpp>

namespace Generix {

GKernel GKernel::m_Instance;

GKernel::GKernel() : m_MBH(ZERO), m_MBI(ZERO) {
	m_cpu = GProcessor::Instance();
}

GKernel::~GKernel() {
}

VOID GKernel::SetMultiBootHeader(PMULTIBOOTHEADER mbh) {
	m_MBH = mbh;
}

VOID GKernel::SetMultiBootInfo(PMULTIBOOTINFO mbi) {
	m_MBI = mbi;
}

PMULTIBOOTHEADER GKernel::GetMultiBootHeader() {
	return m_MBH;
}

PMULTIBOOTINFO GKernel::GetMultiBootInfo() {
	return m_MBI;
}

GProcessor* GKernel::GetCpu()
{
	return m_cpu;
}

}
