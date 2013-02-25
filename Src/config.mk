ifeq ($(V),1)
CC                  = gcc
CXX                 = g++
AS                  = nasm
LD                  = ld
AR                  = ar
RANLIB              = ranlib
RM                  = rm -f
else
CC                  = @echo "[CC]       $<" && gcc
CXX                 = @echo "[CXX]      $<" && g++
AS                  = @echo "[NASM]     $<" && nasm
LD                  = @echo "[LD]       $(KERNEL)" && ld
AR                  = @echo "[AR]       $@" && ar
RANLIB              = @echo "[RANLIB]   $@" && ranlib
RM                  = @echo "Cleaning...  " && rm -f

#CC                  = @echo -e "\033[33m[CC]\033[32m       $<\033[0m" && gcc
#CXX                 = @echo -e "\033[33m[CXX]\033[32m      $<\033[0m" && g++
#AS                  = @echo -e "\033[33m[NASM]\033[32m     $<\033[0m" && nasm
#LD                  = @echo -e "\033[33m[LD]\033[32m       $(KERNEL)\033[0m" && ld
#AR                  = @echo -e "\033[33m[AR]\033[32m       $@\033[0m" && gcc-ar
#RANLIB              = @echo -e "\033[33m[RANLIB]\033[32m   $@\033[0m" && gcc-ranlib
#RM                  = @echo "Cleaning...  " && rm -f
endif

#.cpp.o:
#	$(CXX) -c $(CXXFLAGS)    -o $*.o $*.cpp
#	$(CXX) -MM $(CXXFLAGS)    $*.cpp > $*.d
#	@mv -f $*.d $*.d.tmp
#	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
#	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
#	sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
#	@rm -f $*.d.tmp

#.c.o:
#	$(CC) -c $(CFLAGS)    -o $*.o $*.c
#	@$(CC) -MM $(CFLAGS)    $*.c > $*.d
#	@mv -f $*.d $*.d.tmp
#	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
#	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
#	sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
#	@rm -f $*.d.tmp

#%.o: %.asm
#	$(AS)  $(ASFLAGS)  -o $@ $<

#.s.o:
#	$(AS)  $(ASFLAGS)  -o $@ $<

%.o: %.s
	@$(AS) $(ASFLAGS) $< -o $@

%.s: %.asm
	$(CPP) $(CPPFLAGS) -o $@ -x assembler-with-cpp $<

##export CC CXX AS LD AR RANLIB RM

.cpp.o:
	@g++ -MM $(CXXFLAGS)    $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp
	$(CXX) -c $(CXXFLAGS)    -o $*.o $*.cpp

.c.o:
	@gcc -MM $(CFLAGS)    $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp
	$(CC) -c $(CFLAGS)    -o $*.o $*.c
