/*
 *William Toth
 *Function headers for indexer
 */

/*****************fileGetURL*****************/
/*
 *User provides a file produced by running crawler
 *Returns a pointer to a URL string
 */
char* fileGetURL (FILE* fp);

/*****************fileGetDepth*****************/
/*
 *User provides a file produced by running crawler
 *Returns a pointer to its depth
 */
int fileGetDepth (FILE* fp);

/*****************fileGetHTML*****************/
/*
 *User provides a file produced by running crawler
 *Returns a pointer to a HTML string
 */
char* fileGetHTML (FILE* fp);

/*****************get_path*****************/
/*
 *User provides a dircetory and and integer representing a file
 *Returns path including directory/path in the form of a string
 */
char* get_path (char* pageDirectory, int filenum);

/*****************loadWordsToHT*****************/
/*
 *User provides a hashtable, webpage, and file number
 *Function gets all words from file and loads them into counters in the hashtable
 *Implements the webpage module's webpage_getNextWord() function
 */
void loadWordsToHT (hashtable_t *ht, webpage_t *page, int filenum);

/*****************build_index*****************/
/*
 *User provides a hashtable and directory of files created by crawler
 *Calls loadWordsToHT repeastedly, filling up the entire hashtable
 */
void build_index (hashtable_t *ht, char* pageDirectory);
