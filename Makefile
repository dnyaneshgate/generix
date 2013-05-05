
.PHONY: world lib kernel drivers distclean libclean iso bochs qemu usage

all:
	$(MAKE) -C Src $@

world:
	$(MAKE) -C Src $@

lib:
	$(MAKE) -C Src $@

kernel:
	$(MAKE) -C Src $@

drivers:
	$(MAKE) -C Src $@

clean:
	$(MAKE) -C Src $@

clean-all:
	$(MAKE) -C Src $@

distclean:
	$(MAKE) -C Src $@

libclean:
	$(MAKE) -C Src $@

driverclean:
	$(MAKE) -C Src $@

iso: Src/Kernel32.elf Initrd.img
	Scripts/iso.sh $^

bochs:
	Scripts/emulate.sh bochs

qemu:
	Scripts/emulate.sh qemu

usage:
	@echo "make clean lib driver kernel"
	@echo "make clean lib world"
	@echo "make libclean driverclean distclen"
