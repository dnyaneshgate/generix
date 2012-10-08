include config.mk
include rules.mk
include Klib/libraries.mk
include Mem/Memory.mk
include Kernel/kernel.mk
include Drivers/drivers.mk

.PHONY: world lib kernel driver usage

all: world

world: drivers kernel

driverclean:
	rm -f $(DRIVEROBJ)

distclean: clean
	rm -f $(KERNEL)

libclean:
	rm -f $(addprefix $(LIBPATH),$(LIBS))

clean:
	$(RM) $(LIBC) $(LIBCPP) $(LIBPOSIX) $(LIBALLOC) $(MEMOBJ) $(KERNELOBJ) $(DRIVEROBJ)

usage:
	@echo "make clean lib driver kernel"
	@echo "make clean lib world"
	@echo "make libclean driverclean distclen"