#include <FileSystem/Tar/TarFileSystem.hpp>


namespace Generix
{

PRIVATE INT GetSize(const CHAR * in)
{
	UINT size = 0;
	UINT j;
	UINT count = 1;

	for (j = 11; j > 0; j--, count *= 8)
		size += ((in[j - 1] - '0') * count);

	return size;
}

GTarFileSystem::GTarFileSystem()
{

}

GTarFileSystem::GTarFileSystem(UINT Start, UINT End)
{
	TarRecord * fileRecord = ZERO;
	TarHeader * fileHeader = ZERO;
	UINT fsStart = Start;
	UINT fsEnd = End;
	UINT fsPtr = fsStart;
	INT i = 0;
	while (fsPtr <= fsEnd)
	{
		fileRecord = (TarRecord*) fsPtr;
		fileHeader = (TarHeader*) & fileRecord->Header;
		
		if(fileHeader->Name[0] == '\0')
			break;
		
		//printk("%s ", fileHeader->Name);
		INT sz = GetSize(fileHeader->Size);
		//printk("size = %d\n", sz);
		fsPtr += ((sz / 512) + 1) * 512;
		if ((sz % 512) and (sz))
			fsPtr += 512;
		i++;
	}
}

GTarFileSystem::~GTarFileSystem()
{

}

INT GTarFileSystem::Read(GFile * file, CHAR * buffer, UINT offset, UINT size)
{
	return ZERO;
}

INT GTarFileSystem::Write(GFile * file, CHAR * buffer, UINT offset, UINT size)
{
	return ZERO;
}

}