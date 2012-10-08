#include <Processor/Processor.hpp>
#include <Processor/ProcessorInfo.hpp>

#define _CPUID(EAX,EBX,ECX,EDX) __ASM__ __VOLATILE__("cpuid":"=a"(EAX),"=b"(EBX),"=c"(ECX),"=d"(EDX):"a"(EAX))
#define CPUID() _CPUID(_EAX,_EBX,_ECX,_EDX)

PRIVATE ULONG _EAX, _EBX, _ECX, _EDX;

namespace Generix {

GProcessor GProcessor::m_Instance;

GProcessor::GProcessor() {
	_EAX = CPUID_GETVENDORSTRING;
	CPUID();
	*(UINT*)(m_VendorName + 0) = (UINT) _EBX;
	*(UINT*)(m_VendorName + 4) = (UINT) _EDX;
	*(UINT*)(m_VendorName + 8) = (UINT) _ECX;
	m_VendorName[12] = ZERO;
}

GProcessor::~GProcessor() {
}

BOOL GProcessor::InstallGdt() {
	m_gdt.Install();
	return true;
}

BOOL GProcessor::InstallIdt() {
	m_idt.Install();
	return true;
}

BOOL GProcessor::InstallPit() {
	m_idt.EnableIrq(0, GTimer::TimerHandler);
	m_timer.SetFrequency(1000);
	m_timer.Initialise();
	return true;
}

BOOL GProcessor::RegInterrupt(INT x, IsrHandler isr) {
	m_idt.SetVector(x, isr);
	return true;
}

BOOL GProcessor::SetTimerFreq(UINT freq) {
	m_timer.SetFrequency((ULONG) freq);
	m_timer.Initialise();
	return true;
}

const CHAR* GProcessor::GetVendorName() const
{
	return m_VendorName;
}

}
