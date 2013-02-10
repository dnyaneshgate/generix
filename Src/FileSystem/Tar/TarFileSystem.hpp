/*
 * File:   TarFileSystem.hpp
 * Author: dnyaneshg
 *
 * Created on December 2, 2012, 8:32 PM
 */

#ifndef __GENERIX_FILESYSTE_TARFILESYSTEM_HPP__
#define	__GENERIX_FILESYSTE_TARFILESYSTEM_HPP__

#include <FileSystem/FileSystem.hpp>

/* Size of `name' field.  */
#define TARNAMESIZE 100

/* Size of `linkname' field.  */
#define TARLINKNAMESIZE 100

/* Size of `prefix' field.  */
#define TARPREFIXSIZE 155

/* Size of entire tar header.  */
#define TARRECORDSIZE 512

namespace Generix {

struct TarHeader {
	CHAR Name[TARNAMESIZE];
	CHAR Mode[8];
	CHAR UID[8];
	CHAR GID[8];
	CHAR Size[12];
	CHAR ModifyTime[12];
	CHAR CheckSum[8];
	CHAR TypeFlag;
	CHAR LinkName[TARLINKNAMESIZE];
	CHAR Magic[6];
	CHAR Version[2];
	CHAR Uname[32];
	CHAR Gname[32];
	CHAR DevMajor[8];
	CHAR DevMinor[8];
	CHAR Prefix[TARPREFIXSIZE];
};

union TarRecord {
	TarHeader Header;
	CHAR Buffer[TARRECORDSIZE];
};

class GTarFileSystem: public GFileSystem {
	//member functions
public:
	GTarFileSystem(const CHAR * fsPath);
	GTarFileSystem(UINT Start, UINT End);
	~GTarFileSystem();
	INT Read(GFILE file, CHAR * buffer, UINT offset = 0,
			UINT size = BUFFSIZE);
	INT Write(GFILE file, CHAR * buffer, UINT offset = 0,
			UINT size = BUFFSIZE);
	VOID Open(GFILE file);
	VOID Close(GFILE file);
	GDirent * ReadDir(GFILE file, UINT index);
	GFILE FindDir(GFILE file, CONST CHAR *name);
	INT Mount(CONST CHAR *fsPath);
protected:
private:

	//member variables
public:
protected:
private:
};

}

#endif	/* __GENERIX_FILESYSTE_TARFILESYSTEM_HPP__ */

