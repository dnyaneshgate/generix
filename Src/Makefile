include config.mk
include rules.mk

##.SILENT:
.PHONY: all world lib kernel driver usage

all: world link

world: kernel drivers


include Klib/libraries.mk
include Mem/Memory.mk
include FileSystem/FileSystem.mk
include Drivers/drivers.mk
include Kernel/kernel.mk

link:
	$(LD) $(LDFLAGS) -o $(KERNEL) $(KERNELOBJ) $(MEMOBJ) $(FILESYSTEM) $(DRIVEROBJ) $(addprefix $(LIBPATH),$(LIBS))

driverclean:
	@#rm -f $(DRIVEROBJ) && echo -e "\031[33m[RM]\033[36m       $(DRIVEROBJ)\033[0m";
	@rm -f $(DRIVEROBJ) && echo "[RM]       $(DRIVEROBJ)";

distclean:
	@#rm -f $(KERNEL) && echo -e "\033[31m[RM]\033[36m       $(KERNEL)\033[0m";
	@rm -f $(KERNEL) && echo "[RM]       $(KERNEL)";

libclean:
	@for i in $(addprefix $(LIBPATH),$(LIBS)) $(LIBC) $(LIBCPP) $(LIBPOSIX) $(LIBALLOC); do \
		rm -f $$i && echo "[RM]       $$i"; \
	done
	@#rm -f $$i && echo -e "\033[31m[RM]\033[36m       $$i\033[0m";

clean:
	@for i in $(LIBC) $(LIBCPP) $(LIBPOSIX) $(LIBALLOC) $(KERNELOBJ) $(MEMOBJ) $(FILESYSTEM) $(DRIVEROBJ); do \
		rm -f $$i && echo "[RM]       $$i"; \
	done
	@#rm -f $$i && echo -e "\033[31m[RM]\033[36m       $$i\033[0m";

clean-all: distclean libclean clean
