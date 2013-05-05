/*
 * File:   File.hpp
 * Author: dnyaneshg
 *
 * Created on December 1, 2012, 6:11 PM
 */

#ifndef __GENERIX_FILESYSTEM_FILE_HPP__
#define	__GENERIX_FILESYSTEM_FILE_HPP__

#include <Types.hpp>
#include <Macros.hpp>

#define __FILE_MAGIC__ 0xaabbccdd
#define MAX_FILE_NAME 128
#define MAX_DATETIME_SIZE 15

#define FS_UNKNOWN     -1
#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
#define FS_HARDLINK    0x07
#define FS_MOUNTPOINT  0x08 // Is the file an active mountpoint?
namespace Generix {

class GFile {
	// member functions
public:
	GFile();
	GFile(UINT ID, CONST CHAR * name, INT type, UCHAR attributes, UINT fileSize,
			CHAR *data, PVOID fsDriver = ZERO);
	~GFile();
	UINT GetFileId() const;
	CHAR * GetFileName() const;
	INT GetFileType() const;
	UCHAR GetFileAttributes() const;
	CHAR* GetData() const;
	UINT GetSize() const;
	BOOL isValid() const;
	PVOID GetFSDriver() const {
		return m_p_fsDriver;
	}
protected:
private:

	// member variables
public:
protected:
private:
	UINT m_ui_magic;
	UINT m_ui_id;
	CHAR m_c_fileName[MAX_FILE_NAME];
	INT m_i_type;
	USHORT m_us_attributes;
	ULONG m_uc_timeCreated;
	ULONG m_uc_lastModified;
	UINT m_ui_size;
	CHAR * m_pc_data;
	ULONG64 m_ull_offset;
	PVOID m_p_fsDriver;
};

typedef VOID *GFILE;

}

#endif	/* __GENERIX_FILESYSTEM_FILE_HPP__ */

