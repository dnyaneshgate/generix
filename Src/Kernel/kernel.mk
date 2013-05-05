
#KERNELOBJ := $(sort $(patsubst %.asm,%.o,$(wildcard Kernel/Processor/$(ARCH)/Asm/*.asm))) \
#			 $(patsubst %.cpp,%.o,$(wildcard Kernel/Processor/$(ARCH)/*.cpp)) \
#			 $(patsubst %.cpp,%.o,$(wildcard Kernel/Processor/*.cpp)) \
#			 $(patsubst %.cpp,%.o,$(wildcard Kernel/*.cpp))

KERNELOBJ := Kernel/Processor/$(ARCH)/Asm/Boot.o \
			$(patsubst %.asm, %.o, $(shell find Kernel/Processor/$(ARCH)/Asm/ -name "*.asm" | grep -v Boot.asm)) \
			$(patsubst %.cpp, %.o, $(shell find Kernel/ -name "*.cpp")) \
			$(patsubst %.c, %.o, $(shell find Kernel/ -name "*.c")) 

kernel: $(KERNELOBJ) $(MEMOBJ) $(FILESYSTEM)
