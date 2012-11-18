
ifeq ($(V),1)
CC                  = gcc
CXX                 = g++
AS                  = nasm
LD                  = ld
AR                  = gcc-ar
RANLIB              = gcc-ranlib
RM                  = rm -f
else
CC                  = @echo -e "\033[33m[CC]\033[32m       $<\033[0m" && gcc
CXX                 = @echo -e "\033[33m[CXX]\033[32m      $<\033[0m" && g++
AS                  = @echo -e "\033[33m[NASM]\033[32m     $<\033[0m" && nasm
LD                  = @echo -e "\033[33m[LD]\033[32m       $(KERNEL)\033[0m" && ld
AR                  = @echo -e "\033[33m[AR]\033[32m       $@\033[0m" && gcc-ar
RANLIB              = @echo -e "\033[33m[RANLIB]\033[32m   $@\033[0m" && gcc-ranlib
RM                  = @echo "Cleaning...  " && rm -f
endif

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS)    -o $@ $<

#%.o: %.asm
#	$(AS)  $(ASFLAGS)  -o $@ $<

#.s.o:
#	$(AS)  $(ASFLAGS)  -o $@ $<

%.o: %.s
	@$(AS) $(ASFLAGS) $< -o $@

%.s: %.asm
	$(CPP) $(CPPFLAGS) -o $@ -x assembler-with-cpp $<

##export CC CXX AS LD AR RANLIB RM
