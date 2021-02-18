/*
 *William Toth
 *CS50, 21W
 *Indexer module for TSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/webpage.h"
#include "../common/pagedir.h"
#include "../common/index.h"
#include "../common/word.h"

//Helper functions to iterate and print over data structures
void itemprint(FILE *fp, const char *key, void *item);
void htitemdelete(void *item);
static void print_index(void *arg, const char *key, void *item);
static void print_count(void *arg, const int key, const int count);

/*****************fileGetURL*****************/
char* fileGetURL (FILE* fp) {
  char *url = malloc(256);
  fscanf(fp, "%s", url); //reads first word(url) of the file to url;
  return url;
}

/*****************fileGetDepth*****************/
int fileGetDepth (FILE* fp) {
  char url[500];
  int depth;
  fscanf(fp, "%s %d", url, &depth); //reads the second one to depth
  return depth;
}

/*****************fileGetHTML*****************/
char* fileGetHTML (FILE* fp) {

  fseek(fp, 0, SEEK_END); //find where end of file is
  long fpsize = ftell(fp); //get size of file
  fseek(fp, 0, SEEK_SET);
  char *html = malloc(fpsize); //allocate space for this size
  int numNewLines = 0; //Number of newline characters hit
  char curr = fgetc(fp); //curr char
  while (!feof(fp)) { //while not at end of file
    if (curr == '\n') { //If character '\n'
      numNewLines++; //increment number of newline characters hit
    }
    if (numNewLines >= 2) { //If 2 newlines have been hit (i.e. when we're past url and depth )
      strncat(html, &curr, 1); //add each char to html string
    }
    curr = fgetc(fp); //increment current char
  }
  return html;
}


/******function to check if path to file in directory is valid******/
char* get_path (char* pageDirectory, int filenum) {

  char filestr[5];

  sprintf(filestr, "%d", filenum); //convert filenum to string

  char *pathToCheck = NULL;
  if (pageDirectory[-1] != '/') { //if final character of directory isn't a slash
    pathToCheck = malloc(strlen(pageDirectory)+strlen(filestr)+2); //allocate space for string
    strcpy(pathToCheck, pageDirectory); //make it page directory
    strcat(pathToCheck, "/"); //add slash
    strcat(pathToCheck, filestr); //add file string
  } else {
    pathToCheck = malloc(strlen(pageDirectory)+strlen(filestr)+1); //allocate space for string
    strcpy(pathToCheck, pageDirectory); //make it page directory
    strcat(pathToCheck, filestr); //add file string
  }
  return pathToCheck;

}

/*****************loadWordsToHT*****************/
void loadWordsToHT (hashtable_t *ht, webpage_t *page, int filenum) {
  int pos = 0;
  char *result;
  while ((result = webpage_getNextWord(page, &pos)) != NULL) { //while there are still words

    normalize_word(result); //lowercase

    if (hashtable_find(ht, result) == NULL) { //if word is not in hashtable
      counters_t *counters = counters_new();
      hashtable_insert(ht, result, counters); //add word to hashtable
      counters_add(counters, filenum); //increment count for that fild
    } else { //if word is in hashtable
      counters_t *counters = hashtable_find(ht, result);
      counters_add(counters, filenum); //increment count for that file
    }
  }

}

/********function to build inverted index data structure********/
void build_index (hashtable_t *ht, char* pageDirectory) {
  int filenum = 0; //start at file 0
  bool filesLeft = true; //boolean to determine whether or not there are files left in directory

  while (filesLeft) { //while there are more files in the directory
    char* pathToCheck = get_path(pageDirectory, filenum);
    FILE *fp; //FILE pointer
    if ((fp = fopen (pathToCheck, "r"))) { //Try to open
      webpage_t *page = webpage_new(fileGetURL(fp), fileGetDepth(fp), fileGetHTML(fp)); //make a page

      loadWordsToHT(ht, page, filenum); //add words for a given page/file to hashtable

      webpage_delete(page);

      fclose(fp); //close file
      free(pathToCheck);
    } else {
      free(pathToCheck);
      filesLeft = false;
    }
    filenum++; //increment file
  }
}

int
main(int argc, char *argv[]) {

  char *indexFileName = argv[2];
  FILE *indexFile;

  //Try to open index file
  if (!(indexFile = fopen (indexFileName, "w"))) {
    fprintf(stderr, "file not writeable\n");
    return 1;
  }

  //Hashtable of words
  hashtable_t *words = hashtable_new (20);
  if (words == NULL) {
    fprintf(stderr, "hashtable_new failed\n");
    return 1;
  }

  //Check if directory given can be opened
  if (opendir(argv[1]) == NULL) {
    fprintf(stderr, "Not a valid directory\n");
    return 1;
  }

  //build the index
  build_index (words, argv[1]);

  //iterate over hashtable to put index into index file
  hashtable_iterate(words, indexFile, print_index);

  //COMMENT NEXT LINE TO NOT PRINT TO STDOUT
  hashtable_iterate(words, stdout, print_index);

  hashtable_delete(words, htitemdelete);

  fclose(indexFile);


  return 0;
}

/****************HELPER FUNCTIONS****************/

//Function to delete item from hashtable
void htitemdelete(void *item)
{
  if (item != NULL) {
    counters_delete(item);
  }
}

static void print_index(void *arg, const char *key, void *item)
{
  FILE *fp = arg;

  if (fp != NULL && key != NULL &&item != NULL) {
    fprintf (fp, "%s ", key);
    counters_iterate(item, fp, print_count);
    fprintf (fp, "\n");
  }
}

static void print_count(void *arg, const int key, const int count)
{
  FILE *fp = arg;
  if (fp != NULL && key >= 0 && count >= 0) {
    fprintf(fp, "[%d %d] ", key, count);
  }
}


void itemprint(FILE *fp, const char *key, void *item)
{
  fprintf(fp, "%s", key);
  fprintf(fp, ":");
  counters_print(item, fp);
}
