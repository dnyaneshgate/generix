
#include <Processor/x86/IOPort.hpp>
#include <Processor/x86/CPU.hpp>

GIOPort::GIOPort()
{}

GIOPort::~GIOPort()
{}

BOOL
GIOPort::ReadByte(PortId port,UCHAR *result)
{
	__ASM__ __VOLATILE__("inb %1,%0;":"=a"(*result):"dN"(port));
	return true;
}

BOOL
GIOPort::ReadWord(PortId port,USHORT *result)
{
	__ASM__ __VOLATILE__("inw %1,%0;":"=a"(*result):"dN"(port));
	return true;
}

BOOL
GIOPort::ReadLong(PortId port,ULONG *result)
{
	__ASM__ __VOLATILE__("inl %1,%0;":"=a"(*result):"dN"(port));
	return true;
}

BOOL
GIOPort::WriteByte(PortId port,UCHAR value)
{
	__ASM__ __VOLATILE__("outb %1,%0;"::"dN"(port),"a"(value));
	return true;
}

BOOL
GIOPort::WriteWord(PortId port,USHORT value)
{
	__ASM__ __VOLATILE__("outw %1,%0;"::"dN"(port),"a"(value));
	return true;
}

BOOL
GIOPort::WriteLong(PortId port,ULONG value)
{
	__ASM__ __VOLATILE__("outl %1,%0;"::"dN"(port),"a"(value));
	return true;
}

BOOL
GIOPort::ReadCRX(INT X, ULONG *result)
{
	switch(X)
	{
	case Generix::CR0:
		__ASM__ __VOLATILE__("mov %%cr0,%0":"=r"(*result));
		BREAK;
	case Generix::CR1:
		__ASM__ __VOLATILE__("mov %%cr1,%0":"=r"(*result));
		BREAK;
	case Generix::CR2:
		__ASM__ __VOLATILE__("mov %%cr2,%0":"=r"(*result));
		BREAK;
	case Generix::CR3:
		__ASM__ __VOLATILE__("mov %%cr3,%0":"=r"(*result));
		BREAK;
	case Generix::CR4:
		__ASM__ __VOLATILE__("mov %%cr4,%0":"=r"(*result));
		BREAK;
	case Generix::CR5:
		__ASM__ __VOLATILE__("mov %%cr5,%0":"=r"(*result));
		BREAK;
	default:
		return false;
	}
	return true;
}

BOOL
GIOPort::WriteCRX(INT X, ULONG value)
{
	switch(X)
	{
	case Generix::CR0:
		__ASM__ __VOLATILE__("mov %0,%%cr0"::"r"(value));
		BREAK;
	case Generix::CR1:
		__ASM__ __VOLATILE__("mov %0,%%cr1"::"r"(value));
		BREAK;
	case Generix::CR2:
		__ASM__ __VOLATILE__("mov %0,%%cr2"::"r"(value));
		BREAK;
	case Generix::CR3:
		__ASM__ __VOLATILE__("mov %0,%%cr3"::"r"(value));
		BREAK;
	case Generix::CR4:
		__ASM__ __VOLATILE__("mov %0,%%cr4"::"r"(value));
		BREAK;
	case Generix::CR5:
		__ASM__ __VOLATILE__("mov %0,%%cr5"::"r"(value));
		BREAK;
	default:
		return false;
	}
	return true;
}

BOOL 
GIOPort::LoadGdtr(Type base, USHORT limit)
{
	struct
	{
		USHORT limit;
		ULONG  base;
	} PACKED Gdtr;
	
	Gdtr.limit = limit;
	Gdtr.base  = (ULONG)base;
	__ASM__ __VOLATILE__("lgdt (%0);"::"p"(&Gdtr));
	return true;
}

BOOL
GIOPort::LoadIdtr(Type base, USHORT limit)
{
	struct
	{
		USHORT limit;
		ULONG  base;
	} PACKED Idtr;
	
	Idtr.limit = limit;
	Idtr.base  = (ULONG)base;
	__ASM__ __VOLATILE__("lidt (%0);"::"p"(&Idtr));
	return true;
}

