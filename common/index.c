/*
 *William Toth
 *Common functions for TSE project
 *CS50, 21W
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

 static void print_index(void *arg, const char *key, void *item);
 static void print_count(void *arg, const int key, const int count);

//Function to load an index from a file. see index.h for details
void index_load (char* filename, hashtable_t* ht) {

  //Try to open file
  FILE *fp;
  if ((fp = fopen(filename, "r"))) {
    char currline[1000]; //Assuming each line is < 1000 chars

    //While there are lines left
    while (fgets(currline, sizeof(currline), fp)) {
      counters_t *ctrs = counters_new(); //make a new counters for each line
      char *word = malloc(sizeof(char) * 30); //allocate 30 chars worth of space for the word

      //Loop through length of line
      for (int i = 0; i < strlen(currline); i++) {
        char curr = currline[i];
        if (isalpha(curr) != 0) { //If character is alphabetical, add to word
          strncat(word, &curr, 1);
          continue;
        }
        if (curr == ' ' && isalpha(currline[i-1]) != 0) { //Add word to hashtable when it gets to a space
          char wordstr[strlen(word)];
          strcpy (wordstr,word);
          free(word);
          hashtable_insert(ht, wordstr, ctrs);
        }
        if (curr == '[') { //If there is an opening bracket
          int key = currline[i+1] - '0'; //file num
          int size = 0;
          for (int s = 3; isdigit(currline[i+s]) != 0; s++) {
            size++;
          }
          char count_str[size];
          for (int s = 3; isdigit(currline[i+s]) != 0; s++) {
            count_str[s-3] = currline[i+s];
          }
          int count = atoi(count_str);
          counters_set(ctrs, key, count); //add key and count to counters for that word
        }
      }
    }
    fclose(fp);
  } else {
    ht = NULL;
  }
}


//Function to save an index to a file. see index.h for details
void index_save (hashtable_t* index, FILE* file) {

  hashtable_iterate(index, file, print_index); //Iterate over hashtable and write to file with helper functions

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

/****************HELPER FUNCTIONS****************/

static void print_index(void *arg, const char *key, void *item)
{

  FILE *fp = arg;

  if (key != NULL && item != NULL) {

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
