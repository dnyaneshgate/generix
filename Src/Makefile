include config.mk
include rules.mk

.PHONY: all world lib kernel driver usage

all: world

world: drivers kernel

include Klib/libraries.mk
include Mem/Memory.mk
include Drivers/drivers.mk
include Kernel/kernel.mk

driverclean:
	@rm -f $(DRIVEROBJ) && echo "[RM]       $(DRIVEROBJ)";

distclean: clean
	@rm -f $(KERNEL) && && echo "[RM]       $(KERNEL)";

libclean:
	@for i in $(addprefix $(LIBPATH),$(LIBS)) $(LIBC) $(LIBCPP) $(LIBPOSIX) $(LIBALLOC); do \
		rm -f $$i && echo "[RM]       $$i"; \
	done

clean:
	@for i in $(DRIVEROBJ) $(KERNELOBJ) $(MEMOBJ); do \
		rm -f $$i && echo "[RM]       $$i"; \
	done

usage:
	@echo "make clean lib driver kernel"
	@echo "make clean lib world"
	@echo "make libclean driverclean distclen"