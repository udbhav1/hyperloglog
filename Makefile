CC = g++
CFLAGS = -Wall -g -O2
MEMORY = src/memory
BENCHMARKS = src/benchmarks

.PHONY: all
all: benchmark

benchmark: $(BENCHMARKS)/benchmark.o $(MEMORY)/memory.o
	$(CC) $(CFLAGS) -o benchmark $(BENCHMARKS)/benchmark.o $(MEMORY)/memory.o

memory.o: $(MEMORY)/memory.h

.PHONY: clean
clean: 
	$(RM) benchmark $(BENCHMARKS)/*.o $(MEMORY)/*.o
