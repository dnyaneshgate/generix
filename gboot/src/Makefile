
include config.mk

all:
	@#$(MAKE) -C lib $@
	@$(MAKE) -C stage0 $@
	@#$(MAKE) -C stage1 $@

floppy:
	dd if=./build/stage0.img of=floppy.img bs=512 count=1 seek=0

qemu:
	qemu-system-i686 -fda floppy.img

clean:
	@$(MAKE) -C stage0 $@
	@#$(MAKE) -C stage1 $@
	@#$(MAKE) -C lib $@