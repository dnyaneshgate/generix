#ifndef __GENERIX_MEM_MEMORY_HPP__
#define __GENERIX_MEM_MEMORY_HPP__

#include <Types.hpp>
#include <Macros.hpp>

#define BLOCKS_PER_BYTE 8

namespace Generix {

class GMemory {
public:
	STATIC VOID Init();
	PAddress allocPhysical();
	VOID freePhysical(PAddress pAddr);
	VAddress allocVirtual(Size sz);
	VOID freeVirtual(VAddress vAddr);
	virtual Address mapVirtual(PAddress pAddr, VAddress vAddr, UINT flag) = 0;
	virtual VOID umapVirtual(VAddress vAddr, UINT flags=2) = 0;
	INT GetMaxBlocks() const;
	INT GetUsedBlocks() const;
	INT GetFreeBlocks() const;
protected:
	GMemory();
	virtual ~GMemory();
private:
	STATIC VOID MapMark(UINT bit);
	STATIC VOID MapUnmark(UINT bit);
	STATIC BOOL MapTest(UINT bit);
	STATIC INT  MapFirstFree();

public:
protected:
	STATIC UINT *m_pu_memMapStart, *m_pu_memMapEnd;
	STATIC UINT m_ui_memMapLen;
	STATIC UINT m_ui_memTotal;
	STATIC UINT m_ui_memAvail;
	STATIC UINT m_ui_memMaxBlks;
	STATIC UINT m_ui_memUsedBlks;
	STATIC UINT m_ui_memFreeBlks;
private:
};

}

#endif //__GENERIX_MEM_MEMORY_HPP__
