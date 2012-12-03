#include <FileSystem/CPIO/CpioFileSystem.hpp>


namespace Generix {
	
GCPIOFileSystem::GCPIOFileSystem()
{
	
}

GCPIOFileSystem::~GCPIOFileSystem()
{
	
}

INT GCPIOFileSystem::Read(GFile * file, CHAR * buffer , UINT offset, UINT size)
{
	return ZERO;
}

INT GCPIOFileSystem::Write(GFile * file, CHAR * buffer , UINT offset, UINT size)
{
	return ZERO;
}

}