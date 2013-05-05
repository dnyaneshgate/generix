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

#include <List.hpp>
#include <FileSystem/File.hpp>

namespace Generix {

class GDirent {
public:
	GDirent();
	~GDirent();
	CHAR m_c_name[MAX_FILE_NAME];
	UINT m_i_inode;
};

class GDir {
public:
	INT fd;
	GDirent d;
};

typedef GDirent *GDIRENT;
typedef VOID *GDIR;

class GFileSystem {
	// member functions
public:
	GFileSystem();
	GFileSystem(CONST CHAR * fsPath);
	virtual ~GFileSystem();
	BOOL IsMounted() const;
	CHAR *GetMountPath() const;
	INT SetMountPath(CONST CHAR *fsPath);
	GFILE GetRoot() const;
	VOID SetRoot(GFILE file);
	INT AddFile(GFILE file);
	UINT GetFileCount() const;
	virtual INT Mount(CONST CHAR *fsPath) = 0;
	virtual INT Read(GFILE file, CHAR * buffer, UINT offset = 0, UINT size =
			BUFFSIZE) = 0;
	virtual INT Write(GFILE file, CHAR * buffer, UINT offset = 0, UINT size =
			BUFFSIZE) = 0;
	virtual GFILE Open(CONST CHAR *pFile) = 0;
	virtual VOID Close(GFILE file) = 0;
	virtual GDIRENT ReadDir(GDIR dfd) = 0;
	virtual GFILE FindDir(CONST CHAR *name) = 0;
	virtual GDIR OpenDir(CONST CHAR *pPath) = 0;
	virtual VOID CloseDir(GDIR dir) = 0;

protected:
	UINT GetNextId() const {
		return ++Id;
	}
	UINT GetNextFd() const {
		return ++FD;
	}
private:

	// member variables
public:
protected:
	List<GFILE> m_p_listOfFiles;
private:
	STATIC UINT Id;STATIC UINT FD;
	UINT m_ui_fileCount;
	BOOL m_b_isMounted;
	USHORT m_us_fsOptions;
	CHAR m_c_path[MAX_PATH];
	GFILE m_p_root;
};

}

#endif	// __GENERIX_FILESYSTEM_HPP__
