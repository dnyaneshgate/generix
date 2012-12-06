#include <FileSystem/VirtualFileSystem.hpp>
#include <ScreenIo.hpp>

namespace Generix
{

fsNode * Root = ZERO;

PRIVATE INT ListChilds(fsNode * node);
PRIVATE INT MkDir(fsNode * node , const CHAR * name);

GVirtualFileSystem::GVirtualFileSystem()
{

}

GVirtualFileSystem::~GVirtualFileSystem()
{

}

VOID GVirtualFileSystem::Init()
{
	Root = new fsNode("/", FILE_TYPE_DIRECTORY, ZERO);
	MkDir(Root, "Boot");
	MkDir(Root, "Home");
	MkDir(Root, "System");
	MkDir(Root, "Temp");
}

INT GVirtualFileSystem::Mount(const CHAR* dest, const CHAR* src, const CHAR * fsType)
{
	return SUCCESS;
}

INT GVirtualFileSystem::Umount(const CHAR* src)
{
	return SUCCESS;
}

CHAR CWD[MAX_PATH] = "/";

PRIVATE INT MkDir(fsNode * node , const CHAR * name)
{
	node->Childs[node->NoOfChilds++] = new fsNode(name, FILE_TYPE_DIRECTORY, node);
	return 0;
}

PRIVATE INT ListChilds(fsNode * node)
{
	if(node != ZERO)
	{
		if(node->NoOfChilds)
		{
			for(UINT i = 0 ; i LT node->NoOfChilds ; i++)
			{
				printk("%s\n", node->Childs[i]->Name);
			}
		}
		else
		{
			printk("Empty Directory\n");
		}
	}
	printk("\n");
	return 0;
}

INT PWD()
{
	printk("%s\n", CWD);
	return 0;
}

INT Create(const CHAR * name)
{
	return 0;
}

INT ChangeDir(const CHAR * path)
{
	return 0;
}

INT MakeDir(const CHAR * dirName)
{
	return 0;
}

INT ListDir(const CHAR * path = CWD)
{
	if(path != ZERO)
	{
		printk("\nListDir\n");
		if(path[0] == '/')
		{
			//CHAR * dir = ZERO;
			ListChilds(Root);
		}
		else
		{
			
		}
	}
	return 0;
}

}