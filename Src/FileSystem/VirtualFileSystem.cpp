#include <FileSystem/VirtualFileSystem.hpp>

namespace Generix
{

GVirtualFileSystem::GVirtualFileSystem()
{

}

GVirtualFileSystem::~GVirtualFileSystem()
{

}

INT GVirtualFileSystem::Mount(const CHAR* dest, const CHAR* src, const CHAR * fsType)
{
	return SUCCESS;
}

INT GVirtualFileSystem::Umount(const CHAR* src)
{
	return SUCCESS;
}

}