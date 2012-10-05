
KERNELOBJ := $(sort $(patsubst %.asm,%.o,$(wildcard Kernel/Processor/$(ARCH)/Asm/*.asm))) \
			 $(patsubst %.cpp,%.o,$(wildcard Kernel/Processor/$(ARCH)/*.cpp)) \
			 $(patsubst %.cpp,%.o,$(wildcard Kernel/Processor/*.cpp)) \
			 $(patsubst %.cpp,%.o,$(wildcard Kernel/*.cpp)) 

kernel: $(KERNELOBJ)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(KERNELOBJ) $(DRIVEROBJ) $(LIBPATH)$(LIBS)