#include <Types.hpp>
#include <Macros.hpp>
#include <FileSystem/FileSystem.hpp>
#include <string.h>

namespace Generix {

UINT GFileSystem::Id = 0;
UINT GFileSystem::FD = 0;

GFileSystem::GFileSystem() :
		m_ui_fileCount(ZERO), m_b_isMounted(false), m_us_fsOptions(ZERO) {
	bzero(m_c_path, MAX_PATH);
}

GFileSystem::GFileSystem(const CHAR * fsPath) :
		m_ui_fileCount(ZERO), m_b_isMounted(false), m_us_fsOptions(ZERO) {
	strcpy(m_c_path, fsPath);
}

GFileSystem::~GFileSystem() {
	m_b_isMounted = false;
	m_ui_fileCount = ZERO;
}

BOOL GFileSystem::IsMounted() const {
	return m_b_isMounted;
}

CHAR* GFileSystem::GetMountPath() const {
	return (CHAR*) m_c_path;
}

INT GFileSystem::SetMountPath(const CHAR *fsPath) {
	if (!fsPath)
		return -1;

	INT pathLen = strlen(fsPath);
	if (NOT pathLen or (pathLen >= MAX_PATH))
		return -1;

	strcpy(m_c_path, fsPath);
	return 0;
}

GFILE GFileSystem::GetRoot() const {
	return m_p_root;
}

VOID GFileSystem::SetRoot(GFILE file) {
	m_p_root = file;
}

INT GFileSystem::AddFile(GFILE file) {
	if (NOT file)
		return -1;

	m_p_listOfFiles.push_back(file);
	++m_ui_fileCount;
	return 0;
}

UINT GFileSystem::GetFileCount() const {
	return m_ui_fileCount;
}

GDirent::GDirent() :
		m_i_inode(ZERO) {
	bzero(m_c_name, MAX_FILE_NAME);
}

GDirent::~GDirent() {
}

}
