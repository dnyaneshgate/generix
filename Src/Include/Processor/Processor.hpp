#ifndef __GENERIX_PROCESSOR_HPP__
#define __GENERIX_PROCESSOR_HPP__

#include "Arch/IOPort.hpp"
#include "Arch/CPU.hpp"
#include "Arch/Gdt.hpp"
#include "Arch/Idt.hpp"
#include "Arch/Timer.hpp"

namespace Generix {

	class GProcessor {
		friend class GKernel;
	public:
		BOOL InstallGdt();
		BOOL InstallIdt();
		BOOL InstallPit();
		BOOL RegInterrupt(INT No, IsrHandler isr);
		BOOL SetTimerFreq(UINT Frequency = 1000);
		BOOL GetTickCount(UINT &tick);
		const CHAR *GetVendorName() const;
	protected:
	private:
		GProcessor();
		~GProcessor();

		STATIC GProcessor* Instance() {
			return &m_Instance;
		}

		STATIC GProcessor m_Instance;
		GGdt m_gdt;
		GIdt m_idt;
		GTimer m_timer;

		CHAR m_VendorName[13];
	};

};

#endif //__GENERIX_PROCESSOR_HPP__
