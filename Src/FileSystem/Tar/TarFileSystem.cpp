#include <FileSystem/Tar/TarFileSystem.hpp>
#include <string.h>

namespace Generix
{

PRIVATE INT ParseFilePath(const CHAR * pPath)
{
	if (pPath == ZERO)
		return 0;

	CHAR * str = (CHAR*) pPath;

	while (*str != '/' && *str != '\n' && *str != 0)
		str++;

	return (str - pPath);
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

GTarFileSystem::GTarFileSystem(const CHAR * fsPath) : GFileSystem(fsPath)
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
	while (fsPtr <= fsEnd and i < 4)
	{
		fileRecord = (TarRecord*) fsPtr;
		fileHeader = (TarHeader*) & fileRecord->Header;

		if (fileHeader->Name[0] == '\0')
			break;

		INT sz = GetSize(fileHeader->Size);
		
		Id++;
		
		/*CHAR * token = (CHAR*)fileHeader->Name;
		CHAR s[TARNAMESIZE];
		INT ret = 0;
		printk("%s: ", token);
		while((ret = ParseFilePath(token)) != 0)
		{
			memcpy(s, token, ret);
			
			//if(token[ret] != 0)
			token += ret + 1;
			
			s[ret] = 0;
			
			printk("%s ", s);
		}
		printk("\n");*/
		
		GFile * file = new GFile(Id, fileHeader->Name, eRegular, 0);
		m_p_ListOfFiles.push_back(file);
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

	while (begin != end)
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