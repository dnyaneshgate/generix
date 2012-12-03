#include <Processor/x86/Interrupt.hpp>
#include <Processor/x86/IOPort.hpp>
#include <ScreenIo.hpp>
#include <string.h>

namespace Generix {

PRIVATE IsrHandler VectorList[256] = {ZERO};
PRIVATE LONG CurrentMask = 0xffff;

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

PRIVATE VOID Init()
{
	memset(VectorList, 0, sizeof (IsrHandler) * 256);
}

VOID EnableIrq(INT x, IsrHandler irq)
{
	VectorList[x] = irq;
	CurrentMask &= ~(1 << x);
	OUTB(PIC1 + 1, CurrentMask & 0xFF);
	OUTB(PIC2 + 1, (CurrentMask >> 8) & 0xFF);
}

VOID DisableIrq(INT x)
{
	VectorList[x] = 0;
	CurrentMask |= (1 << x);
	OUTB(PIC1 + 1, CurrentMask & 0xFF);
	OUTB(PIC2 + 1, (CurrentMask >> 8) & 0xFF);
}

VOID SetVector(INT x, IsrHandler isr)
{
	VectorList[x] = isr;
}

PRIVATE VOID dumpRegisters(PREG r)
{
	printk("\n======================:CPU STATUS:======================\n");
	printk("EAX = 0x%-10xEBX = 0x%-10xECX = 0x%-10xEDX = 0x%x\n", r->eax, r->ebx, r->ecx, r->edx);
	printk("ESP = 0x%-10xEBP = 0x%-10xESI = 0x%-10xEDI = 0x%x\n", r->esp0, r->ebp, r->esi, r->edi);
	printk("EIP = 0x%-10x CS = 0x%-10xDS  = 0x%-10xSS  = 0x%x\n", r->eip, r->cs, r->ds, r->ss0);
	printk("Interrupt# = 0x%x\n", r->vector);
	printk("Err.Code   = 0x%x\n", r->error);
	printk("e-Flags    = 0x%x\n", r->eflags);
	printk("Usr.Esp    = 0x%x\n", r->esp3);
}

PRIVATE VOID faultHandler(PREG reg)
{
	printk("Interrupt Received : %d\n", reg->vector);
	Console::SetFontColor(Console::CYAN);
	dumpRegisters(reg);
	Console::SetFontColor(Console::YELLOW);
	printk("\n%s\n", interrupt_messages[reg->vector]);
	printk("System Halting...\n");
	Console::SetFontColor(Console::LIGHTGRAY);
	CLI();
	HLT();
}

EXTERN "C" VOID InterruptServiceRoutine(REG reg)
{
	IsrHandler handler = VectorList[reg.vector];
	if (handler)
		handler(reg);
	if (reg.vector <= 31)
		faultHandler(&reg);
}

STATIC UINT __interruptinit __INIT__("Interrupt") __USED__ = (UINT) Init;
}
