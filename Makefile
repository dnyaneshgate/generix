
all:
	$(MAKE) -C Src $@

clean:
	$(MAKE) -C Src $@

%:
	$(MAKE) -C Src $@
