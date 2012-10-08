#include <Support.hpp>
#include <Kernel.hpp>
#include <stdlib.h>
#include <string.h>
#include <ScreenIo.hpp>

using namespace Generix;

EXTERN MULTIBOOTHEADER _MBOOT_HEADER;
EXTERN ULONG __KERNEL_END;
ULONG  __INIT_ESP;

EXTERN "C" VOID __init(void) {
	EXTERN VOID (*__INIT_START__)(), (*__INIT_END__)();
	VOID (**init)();
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
	__init();  //invoke functions resident in .initGenerix section

	__INIT_ESP = esp;

	GKernel *kernel = GKernel::Instance();      //get kernel instance
	kernel->SetMultiBootHeader(&_MBOOT_HEADER);
	kernel->SetMultiBootInfo(mbi);

	GProcessor *CPU = kernel->GetCpu();         //get processor instance
	CPU->InstallGdt();                          //setup gdt
	CPU->InstallIdt();                          //setup idt
	CPU->InstallPit();                          //setup timer

	Console::Writeln("Welcome to Generix");
	Console::Writeln("Version 1.0");

	Console::Write("Processor : ");
	Console::Writeln(CPU->GetVendorName());

	__dtors(); //invoke destructors of static/global objects
	return EXIT_SUCCESS;
}

