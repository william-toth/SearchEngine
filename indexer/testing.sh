
#William Toth
#Testing file for indexer.c and indextest.c
#
#By default, testing is set to the files produced when Crawler
#is run on http://cs50tse.cs.dartmouth.edu/tse/
#
#NOTE: ALL OF THE TESTING CONDITIONS ARE IN Makefile
#This program simply runs Makefile
#Refer to Makefile for all tests
#
#NOTE: To change input files, run crawler with different arguments (instructions in lab 4 directory)
#
#NOTE: ./indexsort.awk is commented out, as it doesn't seem to work on my computer, but the result files oldIndexFile and newIndexFile are the same.

make

make test &> testing.out

gawk -f ./indexsort.awk oldIndexFile > oldIndexFile.sorted

gawk -f ./indexsort.awk newIndexFile > newIndexFile.sorted
