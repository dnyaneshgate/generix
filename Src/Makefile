include config.mk
include rules.mk

.PHONY: all world lib kernel driver usage

all: world link

world: kernel drivers

include Klib/libraries.mk
include Mem/Memory.mk
include Drivers/drivers.mk
include Kernel/kernel.mk

link:
	$(LD) $(LDFLAGS) -o $(KERNEL) $(KERNELOBJ) $(MEMOBJ) $(DRIVEROBJ) $(LIBPATH)$(LIBS)

driverclean:
	@rm -f $(DRIVEROBJ) && echo "[RM]       $(DRIVEROBJ)";

distclean: clean
	@rm -f $(KERNEL) && echo "[RM]       $(KERNEL)";

libclean:
	@for i in $(addprefix $(LIBPATH),$(LIBS)) $(LIBC) $(LIBCPP) $(LIBPOSIX) $(LIBALLOC); do \
		rm -f $$i && echo "[RM]       $$i"; \
	done

clean:
	@for i in $(LIBC) $(LIBCPP) $(LIBPOSIX) $(LIBALLOC) $(KERNELOBJ) $(MEMOBJ) $(DRIVEROBJ); do \
		rm -f $$i && echo "[RM]       $$i"; \
	done

cleanall: distclean libclean
	
usage:
	@echo "make clean lib driver kernel"
	@echo "make clean lib world"
	@echo "make libclean driverclean distclen"