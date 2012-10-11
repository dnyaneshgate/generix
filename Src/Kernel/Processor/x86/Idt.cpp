/*
 * Idt.cpp
 *
 *  Created on: Sep 30, 2012
 *      Author: dnyanesh
 */

#include <Processor/x86/Idt.hpp>
#include <Processor/x86/IOPort.hpp>
#include <ScreenIo.hpp>
#include <Init.hpp>
#include <string.h>

#define ISR(x)      EXTERN "C" VOID isr##x();
#define IRQ(x)      EXTERN "C" VOID irq##x();
#define FLAG        TRAP_GATE|BITS_32|PRESENT|RING_0
#define SETINT(x,func)     SetVector(x,func,FLAG)

const char *interrupt_messages[] = {
	"Division By Zero Exception",
	"Debug Exception", "Non Maskable Interrupt Exception",
	"Breakpoint Exception", "Into Detected Overflow Exception",
	"Out of Bounds Exception", "Invalid Opcode Exception",
	"No Coprocessor Exception", "Double Fault Exception",
	"Coprocessor Segment Overrun Exception", "Bad TSS Exception",
	"Segment Not Present Exception", "Stack Fault Exception",
	"General Protection Fault Exception", "Page Fault Exception",
	"Unknown Interrupt Exception", "Coprocessor Fault Exception",
	"Alignment Check Exception", "Machine Check Exception",
	"Reserved Exceptions", "Reserved Exceptions", "Reserved Exceptions",
	"Reserved Exceptions", "Reserved Exceptions", "Reserved Exceptions",
	"Reserved Exceptions", "Reserved Exceptions", "Reserved Exceptions",
	"Reserved Exceptions", "Reserved Exceptions", "Reserved Exceptions",
	"Reserved Exceptions"
};

ISR(0)
ISR(1)
ISR(2)
ISR(3)
ISR(4)
ISR(5)
ISR(6)
ISR(7)
ISR(8)
ISR(9)
ISR(10)
ISR(11)
ISR(12)
ISR(13)
ISR(14)
ISR(15)
ISR(16)
ISR(17)
ISR(18)
ISR(19)
ISR(20)
ISR(21)
ISR(22)
ISR(23)
ISR(24)
ISR(25)
ISR(26)
ISR(27)
ISR(28)
ISR(29)
ISR(30)
ISR(31)

IRQ(0)
IRQ(1)
IRQ(2)
IRQ(3)
IRQ(4)
IRQ(5)
IRQ(6)
IRQ(7)
IRQ(8)
IRQ(9)
IRQ(10)
IRQ(11)
IRQ(12)
IRQ(13)
IRQ(14)
IRQ(15)

PRIVATE VOID INITPIC() {
	/*send ICW1 to PIC1 (20h) and PIC2 (A0h)*/
	OUTB(PIC1, ICW1);
	OUTB(PIC2, ICW1);

	/*send ICW2 to 21h for the first PIC and 0A1h for the second PIC*/
	OUTB(PIC1 + 1, MASTER_VEC);
	OUTB(PIC2 + 1, SLAVE_VEC);

	/*send ICW3 to 21h for the first PIC and 0A1h for the second PIC*/
	OUTB(PIC1 + 1, 4);
	OUTB(PIC2 + 1, 2);

	/*finally, send ICW4 to 21h for the first PIC and 0A1h for the second PIC*/
	OUTB(PIC1 + 1, ICW4);
	OUTB(PIC2 + 1, ICW4);

	/* disable all IRQs */
	OUTB(PIC1 + 1, 0xFF);
	OUTB(PIC2 + 1, 0xFF);
}

namespace Generix {

	EXTERN "C" VOID _IdtFlush(ULONG);
	PRIVATE IsrHandler VectorList[256] = {ZERO};
	IDTENTRY GIdt::idt[];
	INT GIdt::SelectorCode;
	LONG GIdt::CurrentMask;

	GIdt::GIdt() {
	}

	GIdt::~GIdt() {
	}

	VOID GIdt::SetExceptions() {
		SETINT(0, (ULONG) isr0);
		SETINT(1, (ULONG) isr1);
		SETINT(2, (ULONG) isr2);
		SETINT(3, (ULONG) isr3);
		SETINT(4, (ULONG) isr4);
		SETINT(5, (ULONG) isr5);
		SETINT(6, (ULONG) isr6);
		SETINT(7, (ULONG) isr7);
		SETINT(8, (ULONG) isr8);
		SETINT(9, (ULONG) isr9);
		SETINT(10, (ULONG) isr10);
		SETINT(11, (ULONG) isr11);
		SETINT(12, (ULONG) isr12);
		SETINT(13, (ULONG) isr13);
		SETINT(14, (ULONG) isr14);
		SETINT(15, (ULONG) isr15);
		SETINT(16, (ULONG) isr16);
		SETINT(17, (ULONG) isr17);
		SETINT(18, (ULONG) isr18);
		SETINT(19, (ULONG) isr19);
		SETINT(20, (ULONG) isr20);
		SETINT(21, (ULONG) isr21);
		SETINT(22, (ULONG) isr22);
		SETINT(23, (ULONG) isr23);
		SETINT(24, (ULONG) isr24);
		SETINT(25, (ULONG) isr25);
		SETINT(26, (ULONG) isr26);
		SETINT(27, (ULONG) isr27);
		SETINT(28, (ULONG) isr28);
		SETINT(29, (ULONG) isr29);
		SETINT(30, (ULONG) isr30);
		SETINT(31, (ULONG) isr31);

		SETINT(32, (ULONG) irq0);
		SETINT(33, (ULONG) irq1);
		SETINT(34, (ULONG) irq2);
		SETINT(35, (ULONG) irq3);
		SETINT(36, (ULONG) irq4);
		SETINT(37, (ULONG) irq5);
		SETINT(38, (ULONG) irq6);
		SETINT(39, (ULONG) irq7);
		SETINT(40, (ULONG) irq8);
		SETINT(41, (ULONG) irq9);
		SETINT(42, (ULONG) irq10);
		SETINT(43, (ULONG) irq11);
		SETINT(44, (ULONG) irq12);
		SETINT(45, (ULONG) irq13);
		SETINT(46, (ULONG) irq14);
		SETINT(47, (ULONG) irq15);
	}

	VOID GIdt::SetVector(INT x, ULONG func, UCHAR control) {
		idt[x].offset_1 = func & 0xFFFF;
		idt[x].selector = SelectorCode;
		idt[x].zero = 0;
		idt[x].type_attr = control;
		idt[x].offset_2 = (func >> 16) & 0xFFFF;
	}

	VOID GIdt::SetVector(INT x, IsrHandler isr) {
		VectorList[x] = isr;
	}

	VOID GIdt::Install() {
		INITPIC();
		__ASM__ __VOLATILE__("mov %%cs,%0" : "=g"(SelectorCode));

		memset(VectorList, 0, sizeof (IsrHandler) * 256);
		SetExceptions();

		struct {
			USHORT limit;
			ULONG base;
		} __PACKED__ idtPtr;

		idtPtr.limit = sizeof (IDTENTRY) * 256 - 1;
		idtPtr.base = (ULONG) & idt;

		_IdtFlush((ULONG) & idtPtr);

		CurrentMask = 0xFFFF;
	}

	VOID GIdt::EnableIrq(INT x, IsrHandler irq) {
		VectorList[x] = irq;
		CurrentMask &= ~(1 << x);
		OUTB(PIC1 + 1, CurrentMask & 0xFF);
		OUTB(PIC2 + 1, (CurrentMask >> 8) & 0xFF);
	}

	VOID GIdt::DisableIrq(INT x) {
		VectorList[x] = 0;
		CurrentMask |= (1 << x);
		OUTB(PIC1 + 1, CurrentMask & 0xFF);
		OUTB(PIC2 + 1, (CurrentMask >> 8) & 0xFF);
	}

	PRIVATE VOID dumpRegisters(PREG r) {
		printk("\n======================:CPU STATUS:======================\n");
		printk("EAX = 0x%-10xEBX = 0x%-10xECX = 0x%-10xEDX = 0x%x\n", r->eax, r->ebx, r->ecx, r->edx);
		printk("ESP = 0x%-10xEBP = 0x%-10xESI = 0x%-10xEDI = 0x%x\n", r->esp0, r->ebp, r->esi, r->edi);
		printk("EIP = 0x%-10x CS = 0x%-10xDS  = 0x%-10xSS  = 0x%x\n", r->eip, r->cs, r->ds, r->ss0);
		printk("Interrupt# = 0x%x\n", r->vector);
		printk("Err.Code   = 0x%x\n", r->error);
		printk("e-Flags    = 0x%x\n", r->eflags);
		printk("Usr.Esp    = 0x%x\n", r->esp3);
	}

	PRIVATE VOID faultHandler(PREG reg) {
		Console::SetFontColor(Console::CYAN);
		dumpRegisters(reg);
		Console::SetFontColor(Console::YELLOW);
		printk("\n%s\n", interrupt_messages[reg->vector]);
		printk("System Halting...\n");
		Console::SetFontColor(Console::LIGHTGRAY);
		CLI();
		HLT();
	}

	EXTERN "C"
	VOID isr_handler(REG reg) {
		printk("Interrupt Received : %d\n", reg.vector);
		IsrHandler handler = VectorList[reg.vector];
		if (handler)
			handler(reg);
		if (reg.vector <= 31)
			faultHandler(&reg);
	}

	EXTERN "C"
	VOID irq_handler(REG reg) {
		if (reg.vector >= 40)
			OUTB(0xA0, 0x20);
		OUTB(0x20, 0x20);

		IsrHandler handler = VectorList[reg.vector];
		if (handler)
			handler(reg);
	}

}

//INITFUNC(Generix::PIC)
