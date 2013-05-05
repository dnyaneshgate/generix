/*
 * Bitmap.hpp
 *
 *  Created on: Oct 1, 2012
 *      Author: dnyanesh
 */

#ifndef __GENERIX_BITMAP_HPP__
#define __GENERIX_BITMAP_HPP__

#include <Types.hpp>
#include <Macros.hpp>
#include <string.h>

class GBitMap {
public:

	GBitMap() :
			m_MAP(ZERO), m_SIZE(ZERO), m_FREE(ZERO) {
	}

	~GBitMap() {
	}

	VOID SetBitMap(UCHAR *map, UINT size) {
		m_MAP = map;
		m_SIZE = size;
		m_FREE = size;
	}

	VOID GetBitMap(UCHAR **map, UINT *size) {
		*map = m_MAP;
		*size = m_SIZE;
	}

	VOID Mark(UINT x) {
		if (!IsMarked(x)) {
			m_MAP[x / 8] |= (1 << (x % 8));
			--m_FREE;
		}
	}

	VOID UnMark(UINT x) {
		if (IsMarked(x)) {
			m_MAP[x / 8] &= ~(1 << (x % 8));
		}
	}

	BOOL IsMarked(UINT x) {
		return (m_MAP[x / 8] & (1 << (x % 8)));
	}

	VOID Clear() {
		INT nbytes = m_SIZE / 8;
		if (m_SIZE % 8)
			++nbytes;
		memset(m_MAP, 0, nbytes);
		m_FREE = m_SIZE;
	}

	INT firstFree() {
		INT i = 0;
		INT nbytes = m_SIZE / 8;
		if (m_SIZE % 8)
			++nbytes;
		for (i = 0; i < nbytes; i++) {
			for (INT j = 0; j < 8; j++) {
				INT bit = 1 << j;
				if (!(m_MAP[i] & bit))
					return i * 8 + j;
			}
		}
		return -1;
	}

	int getFree() {
		return m_FREE;
	}

	int getUsed() {
		return (m_SIZE - m_FREE);
	}

protected:
private:
	UCHAR *m_MAP;
	UINT m_SIZE;
	UINT m_FREE;
};

#endif //__GENERIX_BITMAP_HPP__
