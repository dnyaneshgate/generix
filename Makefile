
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

usage:
	@echo "make clean lib driver kernel"
	@echo "make clean lib world"
	@echo "make libclean driverclean distclen"
