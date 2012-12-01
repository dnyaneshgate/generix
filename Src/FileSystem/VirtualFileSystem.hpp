/* 
 * File:   VirtualFileSystem.hpp
 * Author: dnyaneshg
 *
 * Created on December 1, 2012, 6:47 PM
 */

#ifndef __GENERIX_FILESYSTEM_VIRTUALFILESYSTEM_HPP__
#define	__GENERIX_FILESYSTEM_VIRTUALFILESYSTEM_HPP__

#include <Types.hpp>
#include <Macros.hpp>
#include <FileSystem/FileSystem.hpp>

namespace Generix {

class GVirtualFileSystem : public GFileSystem {
	//member functions
public:
	GVirtualFileSystem();
	~GVirtualFileSystem();
protected:
private:

	//member variables
public:
protected:
private:
};

}

#endif	/* __GENERIX_FILESYSTEM_VIRTUALFILESYSTEM_HPP__ */

