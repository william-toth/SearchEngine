# Will Toth
## Tiny Search Engine, project for Dartmouth CS50: 21W

Coded primarily in C, this engine is comprised of:

-a crawler, which, given a URL and depth, crawls the web, saving html files

-an indexer, which reads saved files, creating an inverted index data structure of words and their number of occurences in each html file

-a querier, which, given a query, will use the inverted index data structure to search the web and subsequently return URLS matching the query

Note: To allow for URL's not in the CS50 tse domain, please change the internal url prefix in `libcs50/webpage.h` (currently, crawler only allows for websites with the cs50 tse prefix).

Instructions for each are module in their various README.md's
