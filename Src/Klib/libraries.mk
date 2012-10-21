LIBS     := libc.a
LIBPATH  := Klib/
LIBC     := $(patsubst %.c,%.o,$(shell find Klib/libc -name "*.c"))
LIBCPP   := $(patsubst %.cpp,%.o,$(shell find Klib/libc++/ -name "*.cpp"))
LIBPOSIX := $(patsubst %.cpp,%.o,$(shell find Klib/libposix/ -name "*.cpp"))
LIBALLOC := $(patsubst %.cpp,%.o,$(shell find Klib/liballoc/ -name "*.cpp"))

lib: $(LIBS)

libc.a: $(LIBC)
		$(AR) $(ARFLAGS) $(LIBPATH)$@ $^
		$(RANLIB) $(LIBPATH)$@

libc++.a: $(LIBCPP)
		  $(AR) $(ARFLAGS) $(LIBPATH)$@ $^
		  $(RANLIB) $(LIBPATH)$@

libposix.a: $(LIBPOSIX)
			$(AR) $(ARFLAGS) $(LIBPATH)$@ $^
			$(RANLIB) $(LIBPATH)$@

liballoc.a: $(LIBALLOC)
			$(AR) $(ARFLAGS) $(LIBPATH)$@ $^
			$(RANLIB) $(LIBPATH)$@
