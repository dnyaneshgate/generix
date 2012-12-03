/* 
 * File:   CpioFileSystem.hpp
 * Author: dnyaneshg
 *
 * Created on December 1, 2012, 11:16 PM
 */

#ifndef __GENERIX_FILESYSTEM_CPIOFILESYSTEM_HPP__
#define	__GENERIX_FILESYSTEM_CPIOFILESYSTEM_HPP__

#include <FileSystem/FileSystem.hpp>

namespace Generix {

struct CPIOHeader
{
	unsigned short Magic;
	short Dev;
	unsigned short INo;
	unsigned short Mode;
	unsigned short UID;
	unsigned short GID;
	unsigned short NoOfLinks;
	short rDev;
	unsigned int Modifytime;
	unsigned short NameSize;
	unsigned int FileSize;
	char *FileName;
};

class GCPIOFileSystem : public GFileSystem {
	//member functions
public:
	GCPIOFileSystem();
	~GCPIOFileSystem();
	INT Read(GFile * file, CHAR * buffer , UINT offset = 0, UINT size = BUFFSIZE);
	INT Write(GFile * file, CHAR * buffer , UINT offset = 0, UINT size = BUFFSIZE);
protected:
private:
	
	//member variables
private:
protected:
public:
};

}

#endif	/* __GENERIX_FILESYSTEM_CPIOFILESYSTEM_HPP__ */

