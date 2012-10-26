#include <Main.hpp>
#include <Support.hpp>
#include <Kernel.hpp>
#include <stdlib.h>
#include <string.h>
#include <ScreenIo.hpp>

using namespace Generix;

EXTERN MULTIBOOTHEADER _MBOOT_HEADER;
ULONG __INIT_ESP;

EXTERN "C" VOID __init(void) {
	EXTERN VOID(*__INIT_START__)(), (*__INIT_END__)();
	VOID(**init)();
	for (init = &__INIT_START__; init < &__INIT_END__; init++) {
		(*init)();
	}
}

EXTERN "C" INT _kmain(PMULTIBOOTINFO mbi, ULONG magic, ULONG esp) {

	Console::Clear();

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		printk("Invalid magic no. : %X", (UINT) magic);
		return EXIT_FAILURE;
	}
	__ctors(); //invoke constructors of static/global objects
	__init(); //invoke functions resident in .initGenerix section

	__INIT_ESP = esp; //save initial stack pointer

	GKernel *kernel = GKernel::Instance(); //get kernel instance
	kernel->SetMultiBootHeader(&_MBOOT_HEADER); //save multibootheader
	kernel->SetMultiBootInfo(mbi); //save multibootinfo

	GProcessor *CPU = kernel->GetCpu(); //get processor instance
	CPU->InstallGdt(); //setup gdt
	CPU->InstallIdt(); //setup idt

	CPU->InstallPit(); //setup timer

	kernel->MemoryInit();

	Console::Writeln(WELCOMELOGO);
	Console::Write("\nWelcome to ");
	Console::Color fgCol = Console::GetFontColor();
	Console::SetFontColor(Console::MAGENTA);
	Console::Writeln("Generix");
	Console::SetFontColor(fgCol);
	Console::Write("Version : ");
	Console::Writeln(__GENERIX_VERSION__);

	CHAR vendor[13];
	CPU->GetProcessorInfo("VendorName",vendor);
	Console::Writeln("Processor : %s",vendor);

	UINT cores;
	CPU->GetProcessorInfo("Cores",&cores);
	Console::Writeln("Cores : %d",cores);

	CHAR brand[256];
	CPU->GetProcessorInfo("Brand",brand);
	Console::Writeln("Brand : %s",brand);

	__dtors(); //invoke destructors of static/global objects
	return EXIT_SUCCESS;
}