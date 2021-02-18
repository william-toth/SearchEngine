/*
 *William Toth
 *CS50, 21W
 *Program to test index_load and index_save
 *Given two arguments, loads from the first one and saves to the second
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


void htitemdelete(void *item); //Helper function

int
main(int argc, char *argv[]) {

  hashtable_t *index = hashtable_new(20); //new hashtable

  index_load(argv[1], index); //try to load
  if (index == NULL) { //if it doesn't work
    fprintf(stderr, "file not readable\n");
    return 1;
  }


  FILE* toWrite; //file to save to
  if ((toWrite = fopen (argv[2], "w"))) { //try to open
    index_save(index, toWrite); //save
    fclose(toWrite); //close
  } else { //if it doesn't open
     fprintf(stderr, "file not writeable\n");
     return 1;
  }

  hashtable_delete(index, htitemdelete); //free hashtable

  return 0;
}

/*****************HELPER FUNCTIONS *****************/

void htitemdelete(void *item)
{
  if (item != NULL) {
    //Do nothing
  }
}
