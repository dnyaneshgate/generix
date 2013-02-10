/*
 * Timer.hpp
 *
 *  Created on: Oct 1, 2012
 *      Author: dnyanesh
 */

#ifndef __GENERIX_X86_TIMER_HPP__
#define __GENERIX_X86_TIMER_HPP__

namespace Generix {

class GTimer {
	friend class GProcessor;
private:
	GTimer();
	~GTimer();
	VOID Initialise();
	VOID SetFrequency(ULONG freq);
	ULONG GetFrequency();STATIC VOID TimerHandler(REG reg);
	UINT GetTickCount();

	STATIC UINT m_TickCount;
	ULONG m_Frequency;
};

}

#endif //__GENERIX_X86_TIMER_HPP__
