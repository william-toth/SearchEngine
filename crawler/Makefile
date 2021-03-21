# Makefile for crawler module

PROG = crawler
OBJS = crawler.o ../libcs50/memory.o ../libcs50/libcs50-given.a ../common/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

crawler.o: crawler.c

.PHONY: test valgrind clean

test: $(PROG)
	@echo
	@echo Testing should print out hashtable of URLs iff successful, recipe fortarget failed when not
	@echo To view downloaded pages, look at pageDirectory
	@echo
	@echo letters page with depth 0
	@echo
	#-./$(PROG) http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./pageDirectory/ 0
	@echo
	@echo letters page with depth 1
	@echo
	#-./$(PROG) http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./pageDirectory/ 1
	@echo
	@echo letters page with depth 2
	@echo
	#-./$(PROG) http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./pageDirectory/ 2
	@echo
	@echo letters page with depth 3
	@echo
	#-./$(PROG) http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./pageDirectory/ 3
	@echo
	@echo letters page with depth 4
	@echo
	#-./$(PROG) http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./pageDirectory/ 4
	@echo
	@echo Invalid URL
	@echo
	#-./$(PROG) http://cs50tse.cs.dartmouth.ed ./pageDirectory/ 0
	@echo
	@echo not a directory
	@echo
	#-./$(PROG) http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ctory/ 0
	@echo
	@echo non integer depth
	@echo
	#-./$(PROG) http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./pageDirectory/ depth
	@echo
	@echo depth out of range
	@echo
	#-./$(PROG) http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./pageDirectory/ -5
	@echo
	@echo Different website
	@echo
	#-./$(PROG) http://cs50tse.cs.dartmouth.edu/tse/ ./pageDirectory/ 1
	@echo
	@echo Same thing but missing slash at the end of directory. Should still work
	@echo
	-./$(PROG) http://cs50tse.cs.dartmouth.edu/tse/ ./pageDirectory 1



valgrind: $(PROG)
	valgrind ./$(PROG) http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./pageDirectory/ 1

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
