
#include <FileSystem/FileSystem.hpp>
#include <string.h>

namespace Generix
{

UINT GFileSystem::Id = 0;

GFileSystem::GFileSystem() : m_ui_FileCount(ZERO), m_b_isMounted(false)
{
	bzero(m_c_Path, MAX_PATH);
}

GFileSystem::GFileSystem(const CHAR * fsPath) : m_ui_FileCount(ZERO), m_b_isMounted(false)
{
	strcpy(m_c_Path, fsPath);
}

GFileSystem::~GFileSystem()
{
	m_b_isMounted = false;
	m_ui_FileCount = ZERO;
}

BOOL GFileSystem::IsMounted() const
{
	return m_b_isMounted;
}

}