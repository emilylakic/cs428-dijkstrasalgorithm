CC=g++

CFLAGS=-Wall -Wextra -DDEBUG -g -std=c++14

all: main

main: main.o
	$(CC) $(CFLAGS) main.o -o main
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o
clean:
	rm main *.o
