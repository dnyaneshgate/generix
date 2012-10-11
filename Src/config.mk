
ifeq ($(V),1)
CC                  = gcc
CXX                 = g++
AS                  = nasm
LD                  = ld
AR                  = gcc-ar
RANLIB              = gcc-ranlib
RM                  = rm -f
else
CC                  = @echo "[CC]       $<" && gcc
CXX                 = @echo "[CXX]      $<" && g++
AS                  = @echo "[NASM]     $<" && nasm
LD                  = @echo "[LD]       $(KERNEL)" && ld
AR                  = @echo "[AR]       $@" && gcc-ar
RANLIB              = @echo "[RANLIB]   $@" && gcc-ranlib
RM                  = @echo "Cleaning...  " && rm -f
endif

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ $<

.c.o:
	$(CXX) $(CXXFLAGS)    -o $@ $<

%.o: %.asm
	$(AS)  $(ASFLAGS)  -o $@ $<

.s.o:
	$(AS)  $(ASFLAGS)  -o $@ $<


