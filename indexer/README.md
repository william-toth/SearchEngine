# Indexer

Library of Indexer modules for the Lab 5 portion of the TSE project

To run, first navigate to the `libcs50` directory and run `make`

Next, navigate to the `common` directory and run `make`

Finally, back to `indexer` and run either `testing.sh`, which you may need to get permission to run with `chmod +x testing.sh`, or `make test`

All of the testing conditions are currently in `Makefile`, so to run `indexer.c` or `indexertest.c`, with different arguments, please change the `Makefile`

*NOTE:* The makefile doesn't use an `all` target, but does functionally the same thing.

Indexer is currently set to run `indexer.c` on `pageDirectory` in `crawler`, which is produced by running crawler on http://cs50tse.cs.dartmouth.edu/tse/ until depth 1. To change this, please run crawler with different arguments (instructions in the `README.md` for crawler)

## indexer.c
Given a directory (created by crawler) to look in and a file to write to, `indexer.c` will parse through the htmls from the various documents in directory and load their urls, depths, and htmls into a website. It then places all of this information into a hashtable, in which the key is a word found in the htmls and the value is a counters. In each counters, the key is the document id, and the value is the amount of times the word appeared in that document. This index (hashtable of counters) is then saved into a file specified by the user. To run, use the `Makefile` (directions above)

*NOTE:* `indexer.c` currently writes the index to `stdout` as well as `oldIndexFile`, as it makes testing easier. If you would like it to not write to `stdout`, please comment out `line 163`.

## indexertest.c
indexertest.c tests the functions `index_load` and `index_save`. The former is given a file with an index written to it and loads that index to a hashtable. The latter is given such a hashtable and writes the index to a file. for `indexertest.c`, the user gives a file to read from and a file to write to (the contents of these two files and running `indexertest.c` should be the same). To run, use the `Makefile` (directions above).
