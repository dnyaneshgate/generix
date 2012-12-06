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
#include <string.h>

namespace Generix
{

#define MAX_NAME_SIZE 128
#define FILE_TYPE_REGULAR 1
#define FILE_TYPE_DIRECTORY 2

struct fsNode
{
	CHAR Name[MAX_NAME_SIZE];
	UINT Type;
	UINT NoOfChilds;
	fsNode * Parent;
	fsNode ** Childs;
	
	fsNode(const CHAR * fName, UINT fType, fsNode * fParent) : Type(fType), NoOfChilds(ZERO), Parent(fParent), Childs(ZERO) 
	{
		strcpy(Name, fName);
	}
};

EXTERN fsNode * Root;

class GVirtualFileSystem : public GSingleton<GVirtualFileSystem>
{
	friend class GSingleton<GVirtualFileSystem>;
	friend class GFileSystemManager;
	//member functions
public:
protected:
private:
	GVirtualFileSystem();
	~GVirtualFileSystem();
	VOID Init();
	INT Mount(const CHAR * dest, const CHAR * src, const CHAR * fsType);
	INT Umount(const CHAR * src);

	//member variables
public:
protected:
private:
	List<GFileSystem*> m_p_ListOfFileSystems;
};

EXTERN CHAR CWD[];

EXTERN INT PWD();
EXTERN INT Create(const CHAR * name);
EXTERN INT ChangeDir(const CHAR * path);
EXTERN INT MakeDir(const CHAR * path);
EXTERN INT ListDir(const CHAR * path);

}

#endif	/* __GENERIX_FILESYSTEM_VIRTUALFILESYSTEM_HPP__ */

