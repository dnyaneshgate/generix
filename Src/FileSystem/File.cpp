#include <FileSystem/File.hpp>
#include <string.h>

namespace Generix {

GFile::GFile() :
		m_ui_id(ZERO), m_us_attributes(ZERO), m_ui_size(ZERO), m_pc_data(ZERO) {
	m_e_type = eUnknownFile;
	memset(m_c_fileName, ZERO, MAX_FILE_NAME);
}

GFile::GFile(UINT ID, CHAR* name, eFileType type, UCHAR attributes,
		UINT fileSize, CHAR *data) :
		m_ui_id(ID), m_e_type(type), m_us_attributes(attributes), m_ui_size(
				fileSize), m_pc_data(data) {
	strcpy(m_c_fileName, name);
}

GFile::~GFile() {

}

UINT GFile::GetFileId() const {
	return m_ui_id;
}

CHAR * GFile::GetFileName() const {
	return (CHAR*) m_c_fileName;
}

eFileType GFile::GetFileType() const {
	return m_e_type;
}

UCHAR GFile::GetFileAttributes() const {
	return m_us_attributes;
}

UINT GFile::GetSize() const {
	return m_ui_size;
}

CHAR* GFile::GetData() {
	return m_pc_data;
}

}
