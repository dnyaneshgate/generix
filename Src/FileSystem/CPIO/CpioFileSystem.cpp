#include <FileSystem/CPIO/CpioFileSystem.hpp>


namespace Generix {
	
GCPIOFileSystem::GCPIOFileSystem()
{
	/*
	 * 
	 * 
	CPIOHeader * cpioHeader = (CPIOHeader*)multiBootInfo.Modules[0].ModuleStart;
	
	for(int j = 0; j < 20; j++)
	{
		printk("\n\nMAGIC : %o\n", cpioHeader->Magic);
		//printk("DEV : %o\n", cpioHeader->Dev);
		//printk("INO : %o\n", cpioHeader->INo);
		//printk("MODE : %o\n", cpioHeader->Mode);
		//printk("UID : %o\n", cpioHeader->UID);
		//printk("GID : %o\n", cpioHeader->GID);
		//printk("No Of Links : %o\n", cpioHeader->NoOfLinks);
		//printk("RDEV : %o\n", cpioHeader->rDev);
		//printk("MODIFY TIME : %d\n", cpioHeader->Modifytime[0]);
		//printk("MODIFY TIME : %d\n", cpioHeader->Modifytime[1]);
		printk("NAME SIZE : %o\n", cpioHeader->NameSize);
		printk("FILE SIZE : %d\n", cpioHeader->FileSize[0]);
		printk("FILE SIZE : %d\n", cpioHeader->FileSize[1]);
		//printk("FILE SIZE : %d\n", cpioHeader->fsize);

		CHAR * name = (CHAR*)cpioHeader + sizeof(CPIOHeader);

		for(int i=0;i<cpioHeader->NameSize;i++)
		{
			printk("%c", *name);name++;
		}
		
		UINT len = ((UINT)cpioHeader->FileSize[0] << 16) + (UINT)cpioHeader->FileSize[1];
		printk("\nlen= %d", len);
		if(cpioHeader->FileSize[0]) len-=1;
		if(j == 5) len-=1;
		if(j == 13) len+=1;
		if(j == 14) len+=1;
		if(j == 17) len-=1;
		if(j == 18) len-=1;
		cpioHeader = (CPIOHeader*)((UINT)cpioHeader + sizeof(CPIOHeader) + (UINT)cpioHeader->NameSize + len + 1);
	}
	 * 
	 */
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