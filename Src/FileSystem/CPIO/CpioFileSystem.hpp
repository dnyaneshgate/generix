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

struct CPIOHeader {
	unsigned short Magic;
	unsigned short Dev;
	unsigned short INo;
	unsigned short Mode;
	unsigned short UID;
	unsigned short GID;
	unsigned short NoOfLinks;
	unsigned short rDev;
	unsigned short Modifytime[2];
	unsigned short NameSize;
	//unsigned int fsize;
	unsigned short FileSize[2];
	//char *FileName;
}__PACKED__;

struct old_cpio_header {
	unsigned short c_magic;
	unsigned short c_dev;
	unsigned short c_ino;
	unsigned short c_mode;
	unsigned short c_uid;
	unsigned short c_gid;
	unsigned short c_nlink;
	unsigned short c_rdev;
	unsigned short c_mtimes[2];
	unsigned short c_namesize;
	unsigned short c_filesizes[2];
}__PACKED__;

class GCPIOFileSystem: public GFileSystem {
	//member functions
public:
	GCPIOFileSystem();
	~GCPIOFileSystem();
	INT Read(GFile * file, CHAR * buffer, UINT offset = 0,
			UINT size = BUFFSIZE);
	INT Write(GFile * file, CHAR * buffer, UINT offset = 0,
			UINT size = BUFFSIZE);
protected:
private:

	//member variables
private:
protected:
public:
};

}

#endif	/* __GENERIX_FILESYSTEM_CPIOFILESYSTEM_HPP__ */

