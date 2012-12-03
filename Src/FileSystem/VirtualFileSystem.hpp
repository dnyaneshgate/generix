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
#include <List.hpp>
#include <Singleton.hpp>

namespace Generix {

class GVirtualFileSystem : public GSingleton<GVirtualFileSystem> {
	friend class GSingleton<GVirtualFileSystem>;
	friend class GFileSystemManager;
	//member functions
public:
	INT Mount();
	INT Umount();
protected:
private:
	GVirtualFileSystem();
	~GVirtualFileSystem();

	//member variables
public:
protected:
private:
	List<GFileSystem *> m_p_FileSystems;
};

}

#endif	/* __GENERIX_FILESYSTEM_VIRTUALFILESYSTEM_HPP__ */

