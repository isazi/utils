
CC := g++
CFLAGS := -std=c++11 -Wall
ifneq ($(DEBUG), 1)
	CFLAGS += -O3 -g0
else
	CFLAGS += -O0 -g3
endif


all: ArgumentList.o Timer.o utils.o

ArgumentList.o: include/utils.hpp include/ArgumentList.hpp src/ArgumentList.cpp
	$(CC) -o bin/ArgumentList.o -c src/ArgumentList.cpp -I"include" $(CFLAGS)

Timer.o: include/Stats.hpp include/Timer.hpp src/Timer.cpp
	$(CC) -o bin/Timer.o -c src/Timer.cpp -I"include" $(CFLAGS)

utils.o: include/utils.hpp src/utils.cpp
	$(CC) -o bin/utils.o -c src/utils.cpp -I"include" $(CFLAGS)

clean:
	rm bin/*.o

