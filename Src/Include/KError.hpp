/*
 * Kerror.hpp
 *
 *  Created on: 25-Feb-2013
 *      Author: dnyanesh
 */

#ifndef KERROR_HPP_
#define KERROR_HPP_

namespace Generix {

enum {
	/*Memory*/
	/*FileSystem*/
	eNoSuchFileOrDirectory = 100, eNotRegularFile = 101, eNotDirecory = 102
/*Process*/
/*Network*/
};

INT GetLastError();
VOID SetLastError(INT errCode);

}

#endif /* KERROR_HPP_ */
