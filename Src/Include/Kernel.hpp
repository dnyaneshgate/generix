#ifndef __GENERIX_KERNEL_HPP__
#define __GENERIX_KERNEL_HPP__

#include <Multiboot.hpp>
#include <Processor/Processor.hpp>
#include <MemoryManager.hpp>
#include <Singleton.hpp>

namespace Generix {

	class GKernel : public GSingleton<GKernel> {
	friend class GSingleton<GKernel>;

	//member functions
	public:
		VOID MemoryInit();
		VOID setMultiBootHeader(PMULTIBOOTHEADER mbh);
		VOID setMultiBootInfo(PMULTIBOOTINFO mbi);
		PMULTIBOOTHEADER getMultiBootHeader();
		PMULTIBOOTINFO getMultiBootInfo();
		GProcessor* getCpu();
	protected:
	private:
		GKernel();
		~GKernel();

	//member variables
	public:
	protected:
	private:
		GProcessor *m_cpu;
		GMemoryManager *m_MemMngr;
		PMULTIBOOTHEADER m_MBH;
		PMULTIBOOTINFO m_MBI;
	};

}

#endif //__GENERIX_KERNEL_HPP__
