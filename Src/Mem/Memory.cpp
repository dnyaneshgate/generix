#include <Mem/Memory.hpp>
#include <Processor/Arch/Memory.hpp>
#include <Multiboot.hpp>
#include <string.h>
#include <ScreenIo.hpp>

EXTERN MULTIBOOTINFO multiBootInfo;
EXTERN UINT __KERNEL_END;
UINT KEndAddress = (UINT)&__KERNEL_END;

namespace Generix {

	UINT *GMemory::m_pu_memMapStart = ZERO, *GMemory::m_pu_memMapEnd = ZERO;
	UINT GMemory::m_ui_memMapLen = ZERO;
	UINT GMemory::m_ui_memTotal = ZERO;
	UINT GMemory::m_ui_memAvail = ZERO;
	UINT GMemory::m_ui_memMaxBlks = ZERO;
	UINT GMemory::m_ui_memUsedBlks = ZERO;
	UINT GMemory::m_ui_memFreeBlks = ZERO;

	VOID GMemory::MapMark(UINT bit) {
		m_pu_memMapStart[ bit / 32 ] |= (1 << (bit % 32));
	}

	VOID GMemory::MapUnmark(UINT bit) {
		m_pu_memMapStart[ bit / 32 ] &= ~(1 << (bit % 32));
	}

	BOOL GMemory::MapTest(UINT bit) {
		return (m_pu_memMapStart[ bit / 32 ] & (1 << (bit % 32)));
	}

	INT GMemory::MapFirstFree() {
		for (INT i = 0; i < (INT) (m_ui_memMaxBlks / 32); i++) {
			if (m_pu_memMapStart[i] != 0xffffffff) {
				for (INT j = 0; j < 32; j++) { //! test each bit in the dword
					INT bit = 1 << j;
					if (!(m_pu_memMapStart[i] & bit))
						return i * 4 * 8 + j;
				}
			}
		}
		return -1;
	}

	GMemory::GMemory() {
	}

	GMemory::~GMemory() {
	}

	VOID GMemory::Init() {
		PMULTIBOOTINFO mbi = (PMULTIBOOTINFO)&multiBootInfo;
		m_ui_memTotal = mbi->MemoryLow + mbi->MemoryHigh + 1024;
		m_ui_memUsedBlks = m_ui_memMaxBlks = (m_ui_memTotal * 1024) / PAGESIZE;
		m_ui_memFreeBlks = 0;
		m_pu_memMapStart = (UINT*)PAGE_ROUND_UP(KEndAddress);
		m_ui_memMapLen = m_ui_memMaxBlks / BLOCKS_PER_BYTE;
		m_pu_memMapEnd = (UINT*)(m_pu_memMapStart + m_ui_memMapLen);
		memset(m_pu_memMapStart, 0xff, m_ui_memMapLen);

		PMEMORYMAP mapAddr = (PMEMORYMAP)mbi->MemoryMapAddress;
		UINT mapLen        = mbi->MemoryMapLength;
		UINT Limit         = (UINT) mapAddr + mapLen;
		UINT i             = (UINT) mapAddr;
		//UINT region = 0;

		while( i LT Limit) {
			PMEMORYMAP me = (PMEMORYMAP) i;
			//printk("region=%-3d base=%-20x length=%-20x type=%d\n",region++,me->BaseAddressLow,me->LengthLow,me->Type);
			if(me->Type == 1)
			{
				INT align = me->BaseAddressLow / PAGESIZE;
				INT blocks = me->LengthLow / PAGESIZE;
				for(;blocks>=0;blocks--)
				{
					MapUnmark(align++);
					m_ui_memUsedBlks--;
					m_ui_memFreeBlks++;
				}
			}
			i += me->Size + sizeof(UINT);
		}

		i = 0x100000;
		KEndAddress += m_ui_memMapLen;
		Limit = PAGE_ROUND_UP(KEndAddress) / PAGESIZE;
		while (i < Limit) {
			MapMark(i);
			m_ui_memUsedBlks++;
			m_ui_memFreeBlks--;
			i++;
		}
	}

	PAddress GMemory::allocPhysical() {
		if ((INT) getFreeBlocks() < 0)
			return 0;

		INT frame = MapFirstFree();

		if (frame == -1)
			return 0;

		MapMark(frame);
		PAddress addr = PAddress( frame * PAGESIZE );
		m_ui_memUsedBlks++;
		m_ui_memFreeBlks--;

		return addr;
	}

	VOID GMemory::freePhysical(PAddress pAddr) {
		INT frame = INT( pAddr / PAGESIZE );
		MapUnmark(frame);
		m_ui_memUsedBlks--;
		m_ui_memFreeBlks++;
	}

	INT GMemory::getMaxBlocks() const {
		return m_ui_memMaxBlks;
	}

	INT GMemory::getUsedBlocks() const {
		return m_ui_memUsedBlks;
	}

	INT GMemory::getFreeBlocks() const {
		return m_ui_memFreeBlks;
	}

}

STATIC UINT __meminit __INIT__ __USED__ = (UINT) Generix::GMemory::Init;
