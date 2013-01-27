#include <FileSystem/VirtualFileSystem.hpp>
#include <ScreenIo.hpp>

namespace Generix {

	fsNode * Root = ZERO;

	PRIVATE INT ListChilds(fsNode * node);
	PRIVATE INT MkDir(fsNode * node, const CHAR * name);

	GVirtualFileSystem::GVirtualFileSystem() {

	}

	GVirtualFileSystem::~GVirtualFileSystem() {

	}

	VOID GVirtualFileSystem::Init() {
		Root = new fsNode("/", FILE_TYPE_DIRECTORY, ZERO);
		SetCWD("/");
	}

	INT GVirtualFileSystem::Mount(const CHAR* dest, const CHAR* src, const CHAR * fsType) {
		return SUCCESS;
	}

	INT GVirtualFileSystem::Umount(const CHAR* src) {
		return SUCCESS;
	}

	INT GVirtualFileSystem::SetCWD(const CHAR* path) {
		strcpy(m_c_CurrentWorkingDirectory, path);
		return SUCCESS;
	}

	INT GVirtualFileSystem::Create(const CHAR * file) {

		return SUCCESS;
	}

	INT GVirtualFileSystem::ChangeDir(const CHAR * path) {
		return SUCCESS;
	}

	INT GVirtualFileSystem::ListDir(const CHAR * path) {

		return SUCCESS;
	}

}