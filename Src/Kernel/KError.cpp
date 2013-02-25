/*
 * KError.cpp
 *
 *  Created on: 25-Feb-2013
 *      Author: dnyanesh
 */

#include <Macros.hpp>
#include <Types.hpp>
#include <KError.hpp>

namespace Generix {
PRIVATE INT errno;

INT GetLastError() {
	return errno;
}

VOID SetLastError(INT errCode) {
	errno = errCode;
}

CHAR *strerr(INT errCode) {

}

}
