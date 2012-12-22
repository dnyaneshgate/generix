
AS := yasm
CC := gcc
CXX := g++
LD := ld

ASFLAGS := -f bin
CFLAGS := -fno-builtin -nostdinc -fno-stack-protector -Wall
CXXFLAGS :=
CPPFLAGS :=
LDFLAGS :=

%.img : %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.o : %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.s : %.asm
	$(CC) -E $(CFLAGS) -o $@ -x assembler-with-cpp $<
	
%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<
	
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<
