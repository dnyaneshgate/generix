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
	USHORT Permissions;
	UINT NoOfChilds;
	fsNode * Parent;
	fsNode ** Childs;

	fsNode(const CHAR * fName, UINT fType, fsNode * fParent) : Type(fType), NoOfChilds(ZERO), Parent(fParent), Childs(ZERO)
	{
		strcpy(Name, fName);
	}

	fsNode * CreateNewChildNode(const CHAR * fName, UINT fType)
	{
		fsNode * newNode = new fsNode(fName, fType, this);
		Childs[NoOfChilds++] = newNode;
		return fsNode;
	}

	fsNode * FindNode(const CHAR * fName, UINT fType)
	{
		fsNode * temp = ZERO;
		for (INT i = 0; i LT NoOfChilds; i++)
		{
			if (strequ(fName, Childs[i]->Name))
			{
				temp = Childs[i];
				break;
			}
		}
		return temp;
	}
};

struct MountPoint
{
	fsNode * src;
	fsNode * dest;
	USHORT flags;
	MountPoint * Next;
};

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
	INT Create(const CHAR * file);
	INT ChangeDir(const CHAR * path);
	INT ListDir(const CHAR * path);
	INT SetCWD(const CHAR * path);

	//member variables
public:
protected:
private:
	CHAR m_c_CurrentWorkingDirectory[MAX_PATH];
	fsNode * Root;
	MountPoint * mountPoints;
	List<GFileSystem*> m_p_ListOfFileSystems;
};

}

#ifdef CPP
EXTERN "C"
{
#endif

	INT Open();
	INT Create(const char * file);
	INT ChangeDir(const CHAR * path);
	INT ListDir(const CHAR * path);
	INT Read();
	INT Write();

#ifdef CPP
}
#endif

#endif	/* __GENERIX_FILESYSTEM_VIRTUALFILESYSTEM_HPP__ */

