/* 
 * File:   FileSystemManager.hpp
 * Author: dnyaneshg
 *
 * Created on December 1, 2012, 7:27 PM
 */

#ifndef __GENERIX_FILESYSTEMMANAGER_HPP__
#define	__GENERIX_FILESYSTEMMANAGER_HPP__

#include <FileSystem/VirtualFileSystem.hpp>

namespace Generix {

	class GFileSystemManager : public GSingleton<GFileSystemManager> {
		friend class GSingleton<GFileSystemManager>;
		friend class GKernel;
		// member functions
	public:
	protected:
	private:
		GFileSystemManager();
		~GFileSystemManager();

		VOID Init();
		INT Mount(const CHAR * dest, const CHAR * src, const CHAR * fsType);
		INT Umount(const CHAR * src);
		INT Create(const CHAR * file);
		INT ChangeDir(const CHAR * path);
		INT ListDir(const CHAR * path);

		// member variables
	public:
	protected:
	private:
		GVirtualFileSystem * m_p_VFS;
	};

}

#endif	/* __GENERIX_FILESYSTEMMANAGER_HPP__ */

