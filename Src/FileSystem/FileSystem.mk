
FILESYSTEM := $(patsubst %.cpp, %.o, $(shell find FileSystem/ -name "*.cpp"))