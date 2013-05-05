#include <Types.hpp>
#include <Macros.hpp>
#include <FileSystem/Tar/TarFileSystem.hpp>
#include <string.h>

namespace Generix {

typedef enum {
	eRegularFile = 0,
	eHardLink,
	eSymbolicLink,
	eCharacterSpecial,
	eBlockSpecial,
	eDirectoryFile,
	eFIFO,
	eContiguousFile,
	eUnknownFile
} eFileType;

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

		CHAR *fileData = ZERO;
		INT fileType;

		switch (fileHeader->TypeFlag - '0') {
		case eRegularFile:
			fileType = FS_FILE;
			fileData = (fileRecord->Buffer + TARRECORDSIZE);
			break;
		case eHardLink:
			fileType = FS_HARDLINK;
			break;
		case eSymbolicLink:
			fileType = FS_SYMLINK;
			break;
		case eCharacterSpecial:
			fileType = FS_CHARDEVICE;
			break;
		case eBlockSpecial:
			fileType = FS_BLOCKDEVICE;
			break;
		case eDirectoryFile:
			fileType = FS_DIRECTORY;
			break;
		case eFIFO:
			fileType = FS_PIPE;
			break;
		case eContiguousFile:
			fileType = FS_UNKNOWN;
			break;
		default:
			fileType = FS_UNKNOWN;
			break;
		}

		GFile * file = new GFile(GetNextId(), fileHeader->Name, fileType, 0, sz,
				fileData, this);
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
	if (ZERO == file)
		return ERROR;

	List<GFILE>::iterator begin = m_p_listOfFiles.begin();
	List<GFILE>::iterator end = m_p_listOfFiles.end();
	GFile *fp = (GFile*) file;

	if ((NOT fp->isValid()) or (FS_FILE != fp->GetFileType()))
		return ERROR;

	INT readBytes = (size > fp->GetSize()) ? fp->GetSize() : size;

	memcpy(buffer, fp->GetData(), readBytes);

	return readBytes;
}

INT GTarFileSystem::Write(GFILE file, CHAR * buffer, UINT offset, UINT size) {
	return ZERO;
}

GFILE GTarFileSystem::Open(CONST CHAR *pFile) {
	return ZERO;
}

VOID GTarFileSystem::Close(GFILE file) {
}

GDIR GTarFileSystem::OpenDir(CONST CHAR *pPath) {
	if ((NOT pPath) or (strlen(pPath)))
		return ZERO;

	GFile *dir = (GFile*) FindDir(pPath);
	if (ZERO EQU dir)
		return ZERO;

	if (FS_DIRECTORY != dir->GetFileType())
		return ZERO;

	GDir *newDir = new GDir();
	ASSERT(newDir != ZERO);
	newDir->fd = dir->GetFileId();
	strcpy(newDir->d.m_c_name, dir->GetFileName());
	newDir->d.m_i_inode = dir->GetFileId();

	return (GDIR) newDir;
}

VOID GTarFileSystem::CloseDir(GDIR dir) {
	GDir *pDir = (GDir*) dir;
	SAFE_DELETE_OBJECT(pDir);
}

GDIRENT GTarFileSystem::ReadDir(GDIR dfd) {
	return ZERO;
}

GFILE GTarFileSystem::FindDir(CONST CHAR *name) {
	if (ZERO EQU name)
		return ZERO;

	List<GFILE>::iterator begin = m_p_listOfFiles.begin();
	List<GFILE>::iterator end = m_p_listOfFiles.end();
	GFile *node = ZERO;

	while (begin != end) {
		GFile * filePtr = (GFile*) *begin;
		if (strequ(filePtr->GetFileName(), name)) {
			node = filePtr;
			break;
		}
	}
	return node;
}

INT GTarFileSystem::Mount(CONST CHAR *fsPath) {
	SetMountPath(fsPath);
	GFile *root = new GFile(GetNextId(), fsPath, eDirectoryFile, ZERO, ZERO,
			ZERO);
	m_p_listOfFiles.push_front(root);
	SetRoot(root);
	return ZERO;
}

}
