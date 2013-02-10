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

#define MAX_FILE_NAME 128
#define MAX_DATETIME_SIZE 15

typedef enum {
	eRegularFile = 0,
	eHardLink,
	eSymbolicLink,
	eCharacterSpecial,
	eBlockSpecial,
	eDirectoryFile,
	eFIFO,
	eContiguousFile,
	eUnknownFile
} eFileType;

namespace Generix {

class GFile {
	// member functions
public:
	GFile();
	GFile(UINT ID, CHAR * name, eFileType type, UCHAR attributes, UINT fileSize,
			CHAR *data);
	~GFile();
	UINT GetFileId() const;
	CHAR * GetFileName() const;
	eFileType GetFileType() const;
	UCHAR GetFileAttributes() const;
	CHAR* GetData();
	UINT GetSize() const;
protected:
private:

	// member variables
public:
protected:
private:
	UINT m_ui_id;
	CHAR m_c_fileName[MAX_FILE_NAME];
	eFileType m_e_type;
	USHORT m_us_attributes;
	ULONG m_uc_timeCreated;
	ULONG m_uc_lastModified;
	UINT m_ui_size;
	CHAR * m_pc_data;
};

typedef VOID *GFILE;

}

#endif	/* __GENERIX_FILESYSTEM_FILE_HPP__ */

