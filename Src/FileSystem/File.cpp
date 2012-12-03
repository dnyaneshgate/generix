#include <FileSystem/File.hpp>
#include <string.h>

namespace Generix
{

GFile::GFile() : m_ui_Id(ZERO), m_uc_Attributes(ZERO), Size(ZERO), Data(ZERO)
{
	m_e_Type = eRegular;
	memset(m_c_FileName, ZERO, MAX_FILE_NAME);
}

GFile::GFile(UINT ID, CHAR* name, eFileType type, UCHAR attributes) : m_ui_Id(ID), m_e_Type(type), m_uc_Attributes(attributes)
{
	strcpy(m_c_FileName, name);
}

GFile::~GFile()
{

}

UINT GFile::GetFileId() const
{
	return m_ui_Id;
}

CHAR * GFile::GetFileName() const
{
	return (CHAR*) m_c_FileName;
}

eFileType GFile::GetFileType() const
{
	return m_e_Type;
}

UCHAR GFile::GetFileAttributes() const
{
	return m_uc_Attributes;
}

}