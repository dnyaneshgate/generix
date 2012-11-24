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
		VOID SetMultiBootHeader(PMULTIBOOTHEADER mbh);
		VOID SetMultiBootInfo(PMULTIBOOTINFO mbi);
		PMULTIBOOTHEADER GetMultiBootHeader();
		PMULTIBOOTINFO GetMultiBootInfo();
		GProcessor* GetCpu();
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
