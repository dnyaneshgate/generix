
#include <FileSystem/FileSystem.hpp>

namespace Generix {

GFileSystem::GFileSystem() : m_b_Mounted(false), m_ui_FileCount(ZERO)
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