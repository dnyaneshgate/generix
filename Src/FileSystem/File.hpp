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
	eDirectory = 0, eRegular
} eFileType;

namespace Generix {

class GFile {
	// member functions
public:
	GFile();
	GFile(UINT ID, CHAR * name, eFileType type = eRegular, UCHAR attributes = 0);
	~GFile();
	UINT GetFileId() const;
	CHAR * GetFileName() const;
	eFileType GetFileType() const;
	UCHAR GetFileAttributes() const;
protected:
private:

	// member variables
public:
protected:
private:
	UINT m_ui_Id;
	CHAR m_c_FileName[MAX_FILE_NAME];
	eFileType m_e_Type;
	USHORT m_uc_Attributes;
	UCHAR m_uc_TimeCreated[MAX_DATETIME_SIZE];
	UCHAR m_uc_LastModified[MAX_DATETIME_SIZE];
	
	UINT Size;
	CHAR * Data;
	GFile *Next, *Prev;
};

}

#endif	/* __GENERIX_FILESYSTEM_FILE_HPP__ */

