#include <FileSystem/Tar/TarFileSystem.hpp>
#include <string.h>

namespace Generix
{

PRIVATE INT ParseFilePath(const CHAR * pPath)
{
	return 0;
}

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
	while (fsPtr <= fsEnd and i < 180)
	{
		fileRecord = (TarRecord*) fsPtr;
		fileHeader = (TarHeader*) & fileRecord->Header;
		
		if(fileHeader->Name[0] == '\0')
			break;
		
		//printk("%s ", fileHeader->Name);
		INT sz = GetSize(fileHeader->Size);
		//printk("size = %d\n", sz);
		
		Id++;
		printk("Id= %d   Name = %s ", i, fileHeader->Name);
		GFile * file = new GFile(Id, fileHeader->Name, eRegular, 0);
		m_p_ListOfFiles.push_back(file);
		printk("..\n");
		fsPtr += ((sz / 512) + 1) * 512;
		
		if ((sz % 512) and (sz))
			fsPtr += 512;
		i++;
	}
	m_ui_FileCount = i;
}

GTarFileSystem::~GTarFileSystem()
{

}

INT GTarFileSystem::Read(GFile * file, CHAR * buffer, UINT offset, UINT size)
{
	List<GFile*>::iterator begin = m_p_ListOfFiles.begin();
	List<GFile*>::iterator end = m_p_ListOfFiles.end();
	
	while(begin != end)
	{
		GFile * file = *begin;
		printk("Id = %02d    Name = %s\n", file->GetFileId(), file->GetFileName());
		++begin;
	}
	
	return ZERO;
}

INT GTarFileSystem::Write(GFile * file, CHAR * buffer, UINT offset, UINT size)
{
	return ZERO;
}

}