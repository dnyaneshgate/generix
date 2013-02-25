#include <FileSystem/File.hpp>
#include <string.h>

namespace Generix {

GFile::GFile() :
		m_ui_magic(__FILE_MAGIC__), m_ui_id(ZERO), m_us_attributes(ZERO), m_ui_size(
				ZERO), m_pc_data(ZERO), m_p_fsDriver(ZERO) {
	m_i_type = FS_UNKNOWN;
	memset(m_c_fileName, ZERO, MAX_FILE_NAME);
}

GFile::GFile(UINT ID, CONST CHAR* name, INT type, UCHAR attributes,
		UINT fileSize, CHAR *data, PVOID fsDriver) :
		m_ui_magic(__FILE_MAGIC__), m_ui_id(ID), m_i_type(type), m_us_attributes(
				attributes), m_ui_size(fileSize), m_pc_data(data), m_p_fsDriver(
				fsDriver) {
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

INT GFile::GetFileType() const {
	return m_i_type;
}

UCHAR GFile::GetFileAttributes() const {
	return m_us_attributes;
}

UINT GFile::GetSize() const {
	return m_ui_size;
}

CHAR* GFile::GetData() const {
	return m_pc_data;
}

BOOL GFile::isValid() const {
	return (m_ui_magic == __FILE_MAGIC__);
}

}
