#include <FileSystemManager.hpp>

namespace Generix
{

GFileSystemManager::GFileSystemManager()
{

}

GFileSystemManager::~GFileSystemManager()
{

}

VOID GFileSystemManager::Init()
{
	m_p_VFS = GVirtualFileSystem::Instance();
}

INT GFileSystemManager::Mount(const CHAR* dest, const CHAR* src, const CHAR* fsType)
{
	return m_p_VFS->Mount(dest, src, fsType);
}

INT GFileSystemManager::Umount(const CHAR* src)
{
	return m_p_VFS->Umount(src);
}

}
