#include <FileSystem/Tar/TarFileSystem.hpp>
#include <string.h>

namespace Generix {

PRIVATE INT ParseFilePath(const CHAR * pPath) {
	if (pPath == ZERO)
		return 0;

	CHAR * str = (CHAR*) pPath;

	while (*str != '/' && *str != '\n' && *str != 0)
		str++;

	return (str - pPath);
}

PRIVATE INT GetSize(const CHAR * in) {
	UINT size = 0;
	UINT j;
	UINT count = 1;

	for (j = 11; j > 0; j--, count *= 8)
		size += ((in[j - 1] - '0') * count);

	return size;
}

GTarFileSystem::GTarFileSystem(const CHAR * fsPath) :
		GFileSystem(fsPath) {

}

GTarFileSystem::GTarFileSystem(UINT Start, UINT End) {
	TarRecord * fileRecord = ZERO;
	TarHeader * fileHeader = ZERO;
	UINT fsStart = Start;
	UINT fsEnd = End;
	UINT fsPtr = fsStart;
	INT i = 0;
	while (fsPtr <= fsEnd) {
		fileRecord = (TarRecord*) fsPtr;
		fileHeader = (TarHeader*) &fileRecord->Header;

		if (fileHeader->Name[0] == '\0')
			break;

		INT sz = GetSize(fileHeader->Size);

		Id++;

		CHAR *fileData = ZERO;
		eFileType fileType;

		switch (fileHeader->TypeFlag - '0') {
		case eRegularFile:
			fileType = eRegularFile;
			fileData = (fileRecord->Buffer + TARRECORDSIZE);
			break;
		case eHardLink:
			fileType = eHardLink;
			break;
		case eSymbolicLink:
			fileType = eSymbolicLink;
			break;
		case eCharacterSpecial:
			fileType = eCharacterSpecial;
			break;
		case eBlockSpecial:
			fileType = eBlockSpecial;
			break;
		case eDirectoryFile:
			fileType = eDirectoryFile;
			break;
		case eFIFO:
			fileType = eFIFO;
			break;
		case eContiguousFile:
			fileType = eContiguousFile;
			break;
		}

		GFile * file = new GFile(Id, fileHeader->Name, fileType, 0, sz,
				fileData);
		AddFile(file);
		fsPtr += ((sz / TARRECORDSIZE) + 1) * TARRECORDSIZE;

		if ((sz % TARRECORDSIZE) and (sz))
			fsPtr += TARRECORDSIZE;
		i++;
	}
}

GTarFileSystem::~GTarFileSystem() {

}

INT GTarFileSystem::Read(GFILE file, CHAR * buffer, UINT offset, UINT size) {
	if(ZERO == file)
		return ERROR;

	List<GFILE>::iterator begin = m_p_listOfFiles.begin();
	List<GFILE>::iterator end = m_p_listOfFiles.end();
	GFile *fp = (GFile*)file;
	while (begin != end) {
		GFile * filePtr = (GFile*)*begin;
		if (strequ(fp->GetFileName(), filePtr->GetFileName())) {
			if(size > filePtr->GetSize()) {
				size = filePtr->GetSize();
			}
			memcpy(buffer, filePtr->GetData(), size);
			return size;
		}
		++begin;
	}

	return ERROR;
}

INT GTarFileSystem::Write(GFILE file, CHAR * buffer, UINT offset, UINT size) {
	return ZERO;
}

VOID GTarFileSystem::Open(GFILE file) {
}

VOID GTarFileSystem::Close(GFILE file) {
}

GDirent * GTarFileSystem::ReadDir(GFILE file, UINT index) {
	return ZERO;
}

GFILE GTarFileSystem::FindDir(GFILE file, CONST CHAR *name) {
	return ZERO;
}

INT GTarFileSystem::Mount(CONST CHAR *fsPath) {
	return ZERO;
}

}
