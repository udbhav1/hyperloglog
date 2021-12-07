CC = g++
CFLAGS = -Wall -g -O2
LIBS = src/lib
BENCHMARK = src/benchmark

.PHONY: all
all: hlltest naive

hlltest: $(BENCHMARK)/hlltest.o $(LIBS)/hyperloglog.o $(LIBS)/memory.o
	$(CC) $(CFLAGS) -o hlltest $(BENCHMARK)/hlltest.o $(LIBS)/hyperloglog.o $(LIBS)/memory.o

hlltest.o: $(BENCHMARK)/hlltest.cpp

naive: $(BENCHMARK)/naive.o $(LIBS)/memory.o
	$(CC) $(CFLAGS) -o naive $(BENCHMARK)/naive.o $(LIBS)/memory.o

naive.o: $(BENCHMARK)/naive.cpp

hyperloglog.o: $(LIBS)/hyperloglog.h $(LIBS)/xxhash32.h

memory.o: $(MEMORY)/memory.h

.PHONY: clean
clean: 
	$(RM) -f naive hlltest $(LIBS)/*.o $(BENCHMARK)/*.o
