
ADD_SUBDIRECTORY( Processor )

ADD_KERNEL_SRC( Kernel Device.cpp Driver.cpp FileSystemManager.cpp Fonts.cpp Kernel.cpp KError.cpp
				Main.cpp MemoryManager.cpp New.cpp ScreenIo.cpp Support.cpp Vga.cpp )