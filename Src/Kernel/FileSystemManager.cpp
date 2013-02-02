#include <FileSystemManager.hpp>

namespace Generix {

GFileSystemManager::GFileSystemManager() :
		m_p_VFS(ZERO) {

}

GFileSystemManager::~GFileSystemManager() {

}

VOID GFileSystemManager::Init() {
	m_p_VFS = GVirtualFileSystem::Instance();
	m_p_VFS->Init();
}

INT GFileSystemManager::Mount(const CHAR* dest, const CHAR* src,
		const CHAR* fsType) {
	return m_p_VFS->Mount(dest, src, fsType);
}

INT GFileSystemManager::Umount(const CHAR* src) {
	return m_p_VFS->Umount(src);
}

INT GFileSystemManager::Create(const CHAR * file) {
	return m_p_VFS->Create(file);
}

INT GFileSystemManager::ChangeDir(const CHAR * path) {
	return m_p_VFS->ChangeDir(path);
}

INT GFileSystemManager::ListDir(const CHAR * path) {
	return m_p_VFS->ListDir(path);
}

}
