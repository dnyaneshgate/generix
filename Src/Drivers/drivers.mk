
DRIVEROBJ := $(patsubst %.cpp,%.o,$(wildcard Drivers/*.cpp)) \
			 $(patsubst %.cpp,%.o,$(wildcard Drivers/*/*.cpp)) \
			 $(patsubst %.cpp,%.o,$(wildcard Drivers/*/*/*.cpp))

drivers: $(DRIVEROBJ)