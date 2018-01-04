
INSTALL_ROOT ?= $(HOME)
INCLUDES := -I"include"

CC := g++
CFLAGS := -std=c++11 -Wall

ifdef DEBUG
	CFLAGS += -O0 -g3
else
	CFLAGS += -O3 -g0
endif

all: bin/ArgumentList.o bin/Timer.o bin/utils.o
	-@mkdir -p lib
	$(CC) -o lib/libutils.so -shared -Wl,-soname,libutils.so bin/ArgumentList.o bin/Timer.o bin/utils.o $(CFLAGS)

bin/ArgumentList.o: include/utils.hpp include/ArgumentList.hpp src/ArgumentList.cpp
	-@mkdir -p bin
	$(CC) -o bin/ArgumentList.o -c -fpic src/ArgumentList.cpp $(INCLUDES) $(CFLAGS)

bin/Timer.o: include/Stats.hpp include/Timer.hpp src/Timer.cpp
	-@mkdir -p bin
	$(CC) -o bin/Timer.o -c -fpic src/Timer.cpp $(INCLUDES) $(CFLAGS)

bin/utils.o: include/utils.hpp src/utils.cpp
	-@mkdir -p bin
	$(CC) -o bin/utils.o -c -fpic src/utils.cpp $(INCLUDES) $(CFLAGS)

clean:
	-@rm bin/*.o
	-@rm lib/*

install: all
	-@mkdir -p $(INSTALL_ROOT)/include
	-@cp include/* $(INSTALL_ROOT)/include
	-@mkdir -p $(INSTALL_ROOT)/lib
	-@cp lib/* $(INSTALL_ROOT)/lib
