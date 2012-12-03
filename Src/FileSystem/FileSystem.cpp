
#include <FileSystem/FileSystem.hpp>

namespace Generix {

UINT GFileSystem::Id = 0;

GFileSystem::GFileSystem() : m_ui_FileCount(ZERO), m_b_Mounted(false)
{
	
}

GFileSystem::~GFileSystem()
{
	m_b_Mounted = false;
	m_ui_FileCount = ZERO;
}

BOOL GFileSystem::IsMounted() const
{
	return m_b_Mounted;
}

}