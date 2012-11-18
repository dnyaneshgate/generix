#ifndef __GENERIX_X86_IOPORT_HPP__
#define __GENERIX_X86_IOPORT_HPP__

#include <Types.hpp>
#include <Macros.hpp>

class GIOPort {
public:
	STATIC BOOL ReadByte(PortId port, UCHAR *result);
	STATIC BOOL ReadWord(PortId port, USHORT *result);
	STATIC BOOL ReadLong(PortId port, ULONG *result);

	STATIC BOOL WriteByte(PortId port, UCHAR value);
	STATIC BOOL WriteWord(PortId port, USHORT value);
	STATIC BOOL WriteLong(PortId port, ULONG value);

	STATIC BOOL ReadCRX(INT X, ULONG *result);
	STATIC BOOL WriteCRX(INT X, ULONG value);

	STATIC BOOL LoadIdtr(Type base, USHORT limit);
	STATIC BOOL LoadGdtr(Type base, USHORT limit);
protected:
	GIOPort();
	virtual ~GIOPort();
private:
};

#define INB(P,R)          GIOPort::ReadByte((P),(R))
#define INW(P,R)          GIOPort::ReadWord((P),(R))
#define INL(P,R)          GIOPort::ReadLong((P),(R))

#define OUTB(P,V)         GIOPort::WriteByte((P),(V))
#define OUTW(P,V)         GIOPort::WriteWord((P),(V))
#define OUTL(P,V)         GIOPort::WriteLong((P),(V))

#define LIDT(B,L)         GIOPort::LoadIdtr((B),(L))
#define LGDT(B,L)         GIOPort::LoadGdtr((B),(L))

#define CLI()             __ASM__ __VOLATILE__("cli;")  //disable interrupt
#define STI()             __ASM__ __VOLATILE__("sti;")  //enable interrupt
#define HLT()             __ASM__ __VOLATILE__("hlt;")  //halt system

#endif //__GENERIX_X86_IOPORT_HPP__
