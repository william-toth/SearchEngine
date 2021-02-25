#William Toth
#Makefile for querier module

PROG = querier
OBJS = querier.o ../libcs50/memory.o ../libcs50/libcs50-given.a ../common/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make


$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

quarier.o: querier.c

.PHONY: test valgrind clean

test: $(PROG)
	./$(PROG) ../crawler/pageDirectory ../indexer/oldIndexFile


valgrind: $(PROG)
	valgrind ./$(PROG) ../crawler/pageDirectory ../indexer/oldIndexFile

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
