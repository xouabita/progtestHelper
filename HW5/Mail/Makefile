CC=g++
CFLAGS= -std=c++11 -Wall -g -pedantic -Wno-long-long -Werror
EXEC=build

all: $(EXEC)

builds:
	mkdir -p ./builds/

./builds/main.out: builds ./src/main.cpp
	$(CC) $(CFLAGS) -o ./builds/main.out ./src/main.cpp

build: ./builds/main.out

run: ./builds/main.out
	./builds/main.out

./builds/test.out: builds ./src/main.cpp ./test/test.cpp
	$(CC) $(CFLAGS) -D_main ./src/main.cpp ./test/test.cpp -o ./builds/test.out

test: ./builds/test.out
	./builds/test.out -d yes

clean:
	rm -rf ./builds/
