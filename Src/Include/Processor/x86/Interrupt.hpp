/*
 * File:   Interrupt.hpp
 * Author: dnyanesh
 *
 * Created on November 17, 2012, 5:37 PM
 */

#ifndef __GENERIX_X86_INTERRUPT_HPP__
#define	__GENERIX_X86_INTERRUPT_HPP__

#include "CPU.hpp"

namespace Generix {
	typedef VOID(*IsrHandler)(REG reg);

	VOID SetVector(INT x, IsrHandler isr);
	VOID EnableIrq(INT x, IsrHandler irq);
	VOID DisableIrq(INT x);
}

#endif	//__GENERIX_X86_INTERRUPT_HPP__
