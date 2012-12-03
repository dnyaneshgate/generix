#include <Kernel.hpp>

namespace Generix
{

GKernel::GKernel() : m_MBH(ZERO), m_MBI(ZERO)
{
	m_cpu = GProcessor::Instance();
	m_MemMngr = GMemoryManager::Instance();
	m_FSMngr = GFileSystemManager::Instance();
}

GKernel::~GKernel()
{
}

VOID GKernel::MemoryInit()
{
	m_MemMngr->Init();
}

VOID GKernel::FileSystemInit()
{

}

INT GKernel::FSMount(const CHAR * dest, const CHAR * src, const CHAR * fsType)
{
	return m_FSMngr->Mount(dest, src, fsType);
}
INT GKernel::FSUmount(const CHAR * src)
{
	return m_FSMngr->Umount(src);
}

VOID GKernel::SetMultiBootHeader(PMULTIBOOTHEADER mbh)
{
	m_MBH = mbh;
}

VOID GKernel::SetMultiBootInfo(PMULTIBOOTINFO mbi)
{
	m_MBI = mbi;
}

PMULTIBOOTHEADER GKernel::GetMultiBootHeader()
{
	return m_MBH;
}

PMULTIBOOTINFO GKernel::GetMultiBootInfo()
{
	return m_MBI;
}

GProcessor* GKernel::GetCpu()
{
	return m_cpu;
}

}
