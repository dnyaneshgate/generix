#include <Processor/Processor.hpp>

namespace Generix {

GProcessor GProcessor::m_Instance;

GProcessor::GProcessor() {
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

}
