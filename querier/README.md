# Querier

Currently `querier` is set to run on the `oldIndexFile`, produced by `indexer` and `pageDirectory` produced by `crawler`. If you would like to change the arguments, add input files/directories to indexer and crawler, or change their arguments and re run in with my code.

First, it is essential that `common` and `libcs50` are built before running querier. Please navigate to these directories and run `make` in both. Next, to try querier, you can:

**1)** run `make` and `make test`. You can the type queries to your heart's content (`ctrl+d` to quit). Feel free to change the arguments in `Makefile` as well.

**2)** run `testing.sh`, which is currently set to test `testquery1` and `testquery2`, which include possible queries (feel free to change these).
