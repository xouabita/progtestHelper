CC=g++
CFLAGS= -std=c++11 -Wall -pedantic -Wno-long-long -Werror
EXEC=build

all: $(EXEC)

builds:
	mkdir -p ./builds/

build: builds
	$(CC) $(CFLAGS) -o ./builds/gps.out ./src/gps.cpp

run: ./builds/gps.out
	./builds/gps.out

./builds/test.out: builds
	$(CC) $(CFLAGS) -o ./builds/test.out ./test/test.cpp ./src/gps.cpp

test: ./builds/test.out
	./build/test.out

clean:
	rm -rf ./builds/
