CC = g++
CFLAGS = -Wall -g -O2
LIBS = src/lib
BENCHMARK = src/benchmark

.PHONY: all
all: benchmark hlltest

hlltest: $(BENCHMARK)/hlltest.o $(LIBS)/hyperloglog.o $(LIBS)/memory.o
	$(CC) $(CFLAGS) -o hlltest $(TEST)/hlltest.o $(LIBS)/hyperloglog.o $(LIBS)/memory.o

hlltest.o: $(BENCHMARK)/hlltest.cpp

benchmark: $(BENCHMARK)/benchmark.o $(LIBS)/memory.o
	$(CC) $(CFLAGS) -o benchmark $(BENCHMARK)/benchmark.o $(LIBS)/memory.o

benchmark.o: $(BENCHMARK)/benchmark.cpp

hyperloglog.o: $(LIBS)/hyperloglog.h $(LIBS)/xxhash32.h

memory.o: $(MEMORY)/memory.h

.PHONY: clean
clean: 
	$(RM) -f benchmark hlltest $(LIBS)/*.o $(BENCHMARK)/*.o
