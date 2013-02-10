#ifndef __GENERIX_PROCESSOR_HPP__
#define __GENERIX_PROCESSOR_HPP__

#include <Processor/Arch/Interrupt.hpp>
#include <Processor/Arch/IOPort.hpp>
#include <Processor/Arch/Memory.hpp>
#include <Processor/Arch/Timer.hpp>

namespace Generix {

typedef enum {
	eUNKNOWN = -1, eINTEL = 0, eAMD
} Processor;

class GProcessorInfo;

class GProcessor: public GSingleton<GProcessor> {
	friend class GSingleton<GProcessor> ;
	friend class GKernel;
public:
	BOOL InstallPit();
	BOOL RegInterrupt(INT No, IsrHandler isr);
	BOOL SetTimerFreq(UINT Frequency = 1000);
	BOOL GetTickCount(UINT &tick);
	BOOL GetProcessorInfo(const CHAR *info, VOID *result);
	BOOL GetProcessorFeature(const CHAR *feature);
protected:
private:
	GProcessor();
	~GProcessor();

	VOID ProcessorInfoInit();

	GProcessorInfo *m_p_ProcessorInfo;
	GTimer m_timer;
};
}

#endif //__GENERIX_PROCESSOR_HPP__
