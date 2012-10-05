/*
 * Timer.cpp
 *
 *  Created on: Oct 1, 2012
 *      Author: dnyanesh
 */

#include <Processor/x86/Timer.hpp>
#include <Processor/x86/Idt.hpp>
#include <Processor/x86/IOPort.hpp>

namespace Generix {

UINT GTimer::m_TickCount = 0;

GTimer::GTimer() :
		m_Frequency(ZERO) {
}

GTimer::~GTimer() {
}

VOID GTimer::Initialise() {
	ULONG devisor = 1193180 / m_Frequency;
	OUTB(0x43, 0x36);

	UCHAR low = (UCHAR) (devisor & 0xff);
	UCHAR high = (UCHAR) (SHR(devisor,8) & 0xff);

	OUTB(0x40, low);
	OUTB(0x40, high);
}

VOID GTimer::SetFrequency(ULONG freq) {
	m_Frequency = freq;
}

ULONG GTimer::GetFrequency() {
	return m_Frequency;
}

VOID GTimer::TimerHandler(REG reg) {
	++m_TickCount;
}

UINT GTimer::GetTickCount() {
	return m_TickCount;
}

}
