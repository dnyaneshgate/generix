#include <Main.hpp>
#include <Support.hpp>
#include <Kernel.hpp>
#include <stdlib.h>
#include <string.h>
#include <ScreenIo.hpp>
#include <Mem/KMalloc.hpp>

#include "Processor/x86/CPU.hpp"

using namespace Generix;

EXTERN MULTIBOOTHEADER multiBootHeader;
EXTERN MULTIBOOTINFO multiBootInfo;
ULONG __INIT_ESP;

EXTERN "C" INT _kMain(INT argc, CHAR ** argv);

EXTERN "C" VOID __init(void) {
	EXTERN VOID(*__INIT_START__)();
	EXTERN VOID(*__INIT_END__)();

	VOID(**init)();
	for (init = &__INIT_START__; init < &__INIT_END__; init++) {
		(*init)();
	}
}

EXTERN "C" INT _kInit(UINT esp) {
	Console::Clear();
	__ctors(); //invoke constructors of static/global objects
	__init(); //invoke functions resident in .initGenerix section
	__INIT_ESP = esp; //save initial stack pointer

	GKernel *kernel = GKernel::Instance(); //get kernel instance
	kernel->SetMultiBootHeader(&multiBootHeader); //save multibootheader
	kernel->SetMultiBootInfo(&multiBootInfo); //save multibootinfo

	GProcessor *CPU = kernel->GetCpu(); //get processor instance
	CPU->InstallPit(); //setup timer

	kernel->MemoryInit();

	_kMain(0, NULL);

	__dtors(); //invoke destructors of static/global objects
	return EXIT_SUCCESS;
}

EXTERN "C" INT _kMain(INT argc, CHAR ** argv) {

	//Console::Clear();

	Console::Writeln(WELCOMELOGO);
	Console::Write("\nWelcome to ");
	Console::Color fgCol = Console::GetFontColor();
	Console::SetFontColor(Console::MAGENTA);
	Console::Writeln("Generix");
	Console::SetFontColor(fgCol);
	Console::Write("Version : ");
	Console::Writeln(__GENERIX_VERSION__);

	GKernel *kernel = GKernel::Instance(); //get kernel instance
	GProcessor *CPU = kernel->GetCpu(); //get processor instance

	CHAR vendor[13];
	CPU->GetProcessorInfo("VendorName", vendor);
	Console::Writeln("Processor : %s", vendor);

	//UINT cores;
	//CPU->GetProcessorInfo("Cores", &cores);
	//Console::Writeln("Cores : %d", cores);

	//CHAR brand[256];
	//CPU->GetProcessorInfo("Brand",brand);
	//Console::Writeln("Brand : %s",brand);

	CHAR * addr1 = (CHAR*)kmalloc(10);
	printk("addr1: %x\n",(UINT)addr1);
	strcpy(addr1, "AB");
	printk("%s\n",addr1);

	return EXIT_SUCCESS;
}
