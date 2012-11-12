#include <Mem/PhysicalMemory.hpp>
#include <Mem/Paging.hpp>
#include <Processor/Arch/CPU.hpp>
#include <Processor/Arch/IOPort.hpp>
#include <string.h>
#include <ScreenIo.hpp>

namespace Generix {

#ifdef __x86__
	namespace x86Paging {

		PPAGEDIRECTORY KernelDirectory = ZERO;
		PPAGEDIRECTORY CurrentDirectory = ZERO;

		INT MAPPAGE(PAddress pAddr, VAddress vAddr, UINT flag) {
			INT tbIndx = PAGE_DIR_INDEX(vAddr);
			INT pgIndx = PAGE_TABLE_INDEX(vAddr);

			if (UINT(CurrentDirectory->tables[tbIndx]) AND PAGE_PRESENT) {
				UINT *pageTable = (UINT*) (0xffc00000 + (tbIndx * PAGESIZE));
				if (!(pageTable[pgIndx] AND PAGE_PRESENT)) {
					pageTable[pgIndx] = (pAddr OR(flag AND NEG(PAGEMASK)));
				} else {
					return -1;
				}
			} else {
				PPAGETABLE newPageTable = PPAGETABLE(GPhysicalMemory::Instance()->Alloc());
				memset(newPageTable, 0, sizeof (PAGETABLE));

				PPAGETABLE pageTable = PPAGETABLE(0xffc00000 + (tbIndx * PAGESIZE));
				CurrentDirectory->tables[tbIndx] = (PAddress(newPageTable) OR 3);
				PPTE entry = (PPTE) & pageTable[pgIndx];
				*entry = (pAddr OR(flag AND NEG(PAGEMASK)));
			}
			return 0;
		}

		INT UNMAPPAGE(VAddress vAddr) {
			INT tbIndx = PAGE_DIR_INDEX(vAddr);
			INT pgIndx = PAGE_TABLE_INDEX(vAddr);

			if (CurrentDirectory->tables[tbIndx] AND PAGE_PRESENT) {
				ULONG *pageTable = (ULONG*) (0xffc00000 + (tbIndx * PAGESIZE));
				if ((pageTable[pgIndx] AND PAGE_PRESENT)) {
					pageTable[pgIndx] = 2;
				}
				INT i;
				for (i = 0; i LT 1024; i++)
					if ((pageTable[i] AND PAGE_PRESENT))
						break;

				if (i EQU 1024) {
					GPhysicalMemory::Instance()->Free((VOID*) (CurrentDirectory->tables[tbIndx] AND PAGEMASK));
					CurrentDirectory->tables[tbIndx] = 2;
				}
			}
			return 0;
		}

		INT SWITCHPAGEDIR(PPAGEDIRECTORY dir) {
			ULONG cr0;
			if (NOT dir)
				return -1;

			CurrentDirectory = dir;
			GIOPort::WriteCRX(3, ULONG(dir));
			GIOPort::ReadCRX(0, &cr0);
			cr0 = BITSET(cr0, PAGEBIT);
			GIOPort::WriteCRX(0, cr0);
			return 0;
		}
	}

#endif

}