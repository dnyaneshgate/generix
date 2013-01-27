/* 
 * File:   FileSystem.hpp
 * Author: dnyaneshg
 *
 * Created on December 1, 2012, 6:07 PM
 */

#ifndef __GENERIX_FILESYSTEM_HPP__
#define	__GENERIX_FILESYSTEM_HPP__

#define MAX_PATH 256
#define FILE_SEPERATOR '/'
#define ROOT_DIR "/"

#include <Types.hpp>
#include <Macros.hpp>
#include <List.hpp>
#include <FileSystem/File.hpp>

namespace Generix {

	class GFileSystem {
		// member functions
	public:
		GFileSystem();
		GFileSystem(const CHAR * fsPath);
		virtual ~GFileSystem();
		BOOL IsMounted() const;
		virtual INT Read(GFile * file, CHAR * buffer, UINT offset = 0, UINT size = BUFFSIZE) = 0;
		virtual INT Write(GFile * file, CHAR * buffer, UINT offset = 0, UINT size = BUFFSIZE) = 0;
	protected:
	private:

		// member variables
	public:
	protected:
		UINT m_ui_FileCount;
		List<GFile*> m_p_ListOfFiles;
		STATIC UINT Id;
	private:
		CHAR m_c_Path[MAX_PATH];
		BOOL m_b_isMounted;
	};

}

#endif	// __GENERIX_FILESYSTEM_HPP__

