
CC := g++
CFLAGS := -std=c++11 -Wall
ifdef DEBUG
	CFLAGS += -O0 -g3
else
	CFLAGS += -O3 -g0
endif


all: bin/ArgumentList.o bin/Timer.o bin/utils.o

bin/ArgumentList.o: include/utils.hpp include/ArgumentList.hpp src/ArgumentList.cpp
	-@mkdir -p bin
	$(CC) -o bin/ArgumentList.o -c src/ArgumentList.cpp -I"include" $(CFLAGS)

bin/Timer.o: include/Stats.hpp include/Timer.hpp src/Timer.cpp
	-@mkdir -p bin
	$(CC) -o bin/Timer.o -c src/Timer.cpp -I"include" $(CFLAGS)

bin/utils.o: include/utils.hpp src/utils.cpp
	-@mkdir -p bin
	$(CC) -o bin/utils.o -c src/utils.cpp -I"include" $(CFLAGS)

clean:
	-@rm bin/*.o

