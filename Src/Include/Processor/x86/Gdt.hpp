/*
 * Gdt.hpp
 *
 *  Created on: Sep 30, 2012
 *      Author: dnyanesh
 */

#ifndef __GENERIX_x86_GDT_HPP__
#define __GENERIX_x86_GDT_HPP__

#include <Types.hpp>
#include <Macros.hpp>

namespace Generix {

	class GGdt {
		friend class GProcessor;
	private:
		GGdt();
		virtual ~GGdt();
		VOID SetGdtEntry(INT n, ULONG base, ULONG limit, UCHAR access, UCHAR gran);
		VOID Install();
	};

}

#endif //__GENERIX_x86_GDT_HPP__
