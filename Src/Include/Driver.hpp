#ifndef __GENERIX_DRIVER_HPP__
#define __GENERIX_DRIVER_HPP__

#include <Types.hpp>

#define _MAX_DRI_NAME_SIZE_ 128

namespace Generix {

	class GDriver {
	public:
		CHAR *getName();
		UINT getId();

		virtual INT Write(CHAR *buffer, UINT size, ULLONG offset) = 0;
		virtual INT Read(CHAR *buffer, UINT size, ULLONG offset) = 0;
	protected:
		GDriver(UINT Id, const CHAR *Name);
		virtual ~GDriver();
	private:
		CHAR m_Name[_MAX_DRI_NAME_SIZE_];
		UINT m_Id;
	};
}

#endif //__GENERIX_DRIVER_HPP__
