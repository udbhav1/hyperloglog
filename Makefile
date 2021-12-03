CC = g++
CFLAGS = -Wall -g

.PHONY: all
all: benchmark

benchmark: benchmark.o memory.o
	$(CC) $(CFLAGS) -o benchmark benchmark.o memory.o

memory.o: memory.h

.PHONY: clean
clean: 
	$(RM) benchmark *.o
