
ADD_SUBDIRECTORY( Asm )

ADD_KERNEL_SRC( Kernel/Processor/x86 Interrupt.cpp IOPort.cpp Memory.cpp Timer.cpp )