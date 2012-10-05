/*
 * Idt.hpp
 *
 *  Created on: Sep 30, 2012
 *      Author: dnyanesh
 */

#ifndef __GENERIX_x86_IDT_HPP__
#define __GENERIX_x86_IDT_HPP__

#include "CPU.hpp"

/*PICs*/
#define PIC1        0x20
#define PIC2        0xA0

/*ICWs*/
#define ICW1        0x11
#define ICW4        0x01

#define MASTER_VEC  0x20
#define SLAVE_VEC   0x28

#define INT_GATE    0x06
#define TRAP_GATE   0x07

#define BITS_16     0x00
#define BITS_32     0x08

#define ABSENT      0x00
#define PRESENT     0x80

#define RING_0      0x00
#define RING_1      0x20
#define RING_2      0x40
#define RING_3      0x60
#define EOI         0x20          //end of interrupt

namespace Generix {

typedef VOID (*IsrHandler)(REG reg);

class GIdt {
	friend class GProcessor;
private:
	GIdt();
	~GIdt();
	VOID Install();
	VOID SetVector(INT x, ULONG func, UCHAR control);
	VOID SetVector(INT x, IsrHandler isr);
	VOID SetExceptions();
	VOID EnableIrq(INT x, IsrHandler irq);
	VOID DisableIrq(INT x);

	STATIC IDTENTRY idt[256];
	STATIC INT SelectorCode;
	STATIC LONG CurrentMask;
};

}

#endif //__GENERIX_x86_IDT_HPP__
