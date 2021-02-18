#William Toth
#Makefile for indexer module
#Note: This makefile compiles and runs both indexer and indexertest and
#by default implements all test conditions

PROG = indexer
PROG1 = indextest
OBJS = indexer.o ../libcs50/memory.o ../libcs50/libcs50-given.a ../common/common.a
OBJS1 = indextest.o ../libcs50/memory.o ../libcs50/libcs50-given.a ../libcs50/counters.c ../common/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

#Compile indexer
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

#Compile index test
$(PROG1): $(OBJS1)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indexer.o: indexer.c
indextest.o: indextest.c

.PHONY: test valgrind clean

test: $(PROG) $(PROG1)
	@echo
	@echo Testing should print to stdout the contents of the file that indexer writes to
	@echo If you dont want to print to stdout comment out line 157 of indexer
	@echo
	@echo Please view oldIndexFile and newIndexFile to see the results of indexertest
	@echo
	@echo Test: Invalid directory of crawler Output
	@echo
	-./$(PROG) invalidDirectory oldIndexFile
	@echo
	@echo Test: Not writable file
	@echo
	-./$(PROG) invalidDirectory ../querier
	@echo
	@echo Test: Indexer works but indexertest gets unreadable file
	@echo
	-./$(PROG) ../crawler/pageDirectory oldIndexFile
	-./$(PROG1) iNvALiDoldIndexFile newIndexFile
	@echo
	@echo Test: Indexer works but indexertest gets unwriteable file
	@echo
	-./$(PROG) ../crawler/pageDirectory oldIndexFile
	-./$(PROG1) iNvALiDoldIndexFile ../querier
	@echo
	@echo Test: Both Work
	@echo
	-./$(PROG) ../crawler/pageDirectory oldIndexFile
	-./$(PROG1) oldIndexFile newIndexFile

valgrind: $(PROG)
	#valgrind ./$(PROG) ../crawler/pageDirectory oldIndexFile
	#valgrind ./$(PROG1) oldIndexFile newIndexFile

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
