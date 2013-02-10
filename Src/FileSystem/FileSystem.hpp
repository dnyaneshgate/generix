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

class GDirent {
public:
	GDirent();
	~GDirent();
	CHAR m_c_name[MAX_FILE_NAME];
	UINT m_i_inode;
};

class GFileSystem {
	// member functions
public:
	GFileSystem();
	GFileSystem(CONST CHAR * fsPath);
	virtual ~GFileSystem();
	BOOL IsMounted() const;
	CHAR *GetMountPath() const;
	INT  SetMountPath(CONST CHAR *fsPath);
	GFILE GetRoot() const;
	VOID SetRoot(GFILE file);
	INT AddFile(GFILE file);
	UINT GetFileCount() const;
	virtual INT Mount(CONST CHAR *fsPath) = 0;
	virtual INT Read(GFILE file, CHAR * buffer, UINT offset = 0, UINT size =
			BUFFSIZE) = 0;
	virtual INT Write(GFILE file, CHAR * buffer, UINT offset = 0, UINT size =
			BUFFSIZE) = 0;
	virtual VOID Open(GFILE file) = 0;
	virtual VOID Close(GFILE file) = 0;
	virtual GDirent * ReadDir(GFILE file, UINT index) = 0;
	virtual GFILE FindDir(CONST CHAR *name) = 0;

protected:
private:

	// member variables
public:
protected:
	STATIC UINT Id;
	List<GFILE> m_p_listOfFiles;
private:
	UINT m_ui_fileCount;
	BOOL m_b_isMounted;
	USHORT m_us_fsOptions;
	CHAR m_c_path[MAX_PATH];
	GFILE m_p_root;
};

}

#endif	// __GENERIX_FILESYSTEM_HPP__
