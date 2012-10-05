LIBS     := libc.a
LIBPATH  := Klib/
LIBC     := $(patsubst %.c,%.o,$(wildcard Klib/libc/*.c)) $(patsubst %.c,%.o,$(wildcard Klib/libc/*/*.c))
LIBCPP   := $(patsubst %.cpp,%.o,$(wildcard Klib/libc++/*.cpp)) $(patsubst %.cpp,%.o,$(wildcard Klib/libc++/*/*.cpp))
LIBPOSIX := $(patsubst %.cpp,%.o,$(wildcard Klib/libposix/*.cpp))
LIBALLOC := $(patsubst %.cpp,%.o,$(wildcard Klib/liballoc/*.cpp))

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

