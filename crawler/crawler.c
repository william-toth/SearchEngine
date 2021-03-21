/*
 *William Toth
 *Crawler program for Lab 4
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
#include "../libcs50/webpage.h"
#include "../common/pagedir.h"

//Global variables
int maxDepth;
int id;
char* dir;
bool page_already_in; //variable for whether or not page is already in hashtable (had to be global for unimportant reasons)

//Hashtable and Bag argument functions
void itemprint(FILE *fp, const char *key, void *item);
void itemdelete(void *item);
void htitemdelete(void *item);
void hashfunc (void *arg, const char *key, void *item);

//Function to get URLS from a page's HTML
void pagescan (webpage_t *page, bag_t *bag1) {
  //Loop through
  int pos = 0;
  char *result;
  while ((result = webpage_getNextURL(page, &pos)) != NULL) {
    if (IsInternalURL(result)) { //Checks result URL
      webpage_t *newpage = webpage_new(result, webpage_getDepth(page)+1, NULL); //If it's good, create page
      bag_insert(bag1, newpage); //Insert into bag
    }
  }
}

void crawl (bag_t *bag, hashtable_t *ht) {
  bool empty = false; //Set bag empty boolean to false
  while (!empty) { //while bag isn't empty
    webpage_t* page = (webpage_t*) bag_extract(bag); //get page at front of bag
    if (webpage_fetch(page)) { //Get html for webpage and check if successful
      char dirchar[100]; //make string for directory name
      strcpy(dirchar,dir); //copy directory name into said string
      page_already_in = false; //Set boolean for whether page is in hashtable to false
      hashtable_iterate(ht, webpage_getURL(page), hashfunc); //Iterate through hashtable to check if it is already in
      if (!page_already_in) { //if not in
        pagesave(page, id, dirchar); //save page
      }
      id++; //increment id
      hashtable_insert(ht, webpage_getURL(page), ""); //insert page into hashtable
      if (webpage_getDepth(page) < maxDepth) { //if page's depth < max depth
        pagescan(page, bag); //Scan the page for more urls
      }
    } else { //If fetch unsuccessful
      empty = true; // set bag empty boolean to true
    }
  }
}

int
main(int argc, char *argv[]) {

  //Check if 3 args given
  if (argc != 4) {
    fprintf(stderr, "Wrong number of arguments given\n");
    return 1;
  }

  //check if arg given is int
  if (isdigit(argv[3][0]) == 0) {
    fprintf(stderr, "Max Depth not an integer\n");
    return 1;
  }

  //check if URL can be parsed and conatins html
  if (!NormalizeURL(argv[1])) {
    fprintf(stderr, "URL cannot be parsed or doesn't conatin html\n");
    return 1;
  }

  //check if URL is an internal URL
  if (!IsInternalURL(argv[1])) {
    fprintf(stderr, "Not internal URL\n");
    return 1;
  }

  //Check if directory given can be opened
  if (opendir(argv[2]) == NULL) {
    fprintf(stderr, "Not a valid directory\n");
    return 1;
  }

  //set dir to argument 2
  dir = argv[2];

  //Create variable for max depth
  sscanf (argv[3], "%d", &maxDepth);

  //check if if max depth is in range
  if (maxDepth < 0 || maxDepth > 10) {
    fprintf(stderr, "Max Depth out of range\n");
    return 1;
  }

  //initialize id;
  id = 0;

  //Make a bag of urls to explore
  bag_t *to_explore = bag_new();
  if (to_explore == NULL) {
    fprintf(stderr, "bag_new failed\n");
    return 1;
  }

  //Hashtable of seen pages
  hashtable_t *seen = hashtable_new (10);
  if (seen == NULL) {
    fprintf(stderr, "hashtable_new failed\n");
    return 1;
  }

  //create page for first page
  webpage_t *firstpage = webpage_new(argv[1], 0, NULL); //Create first page

  //insert first one to bag
  bag_insert(to_explore, firstpage);

  //call drawl
  crawl (to_explore, seen);

  //Print hashtable (to see how many urls were explored)
  hashtable_print(seen, stdout, itemprint);

  bag_delete(to_explore, itemdelete);

  hashtable_delete(seen, htitemdelete);

  return 0;
}

//Function to print item
void itemprint(FILE *fp, const char *key, void *item)
{

  char *itemchar = item;

  if (itemchar == NULL) {
    fprintf(fp, "(null)");
  }
  else {
    fprintf(fp, "%s", key);
    fprintf(fp, "%s", itemchar);
  }
}

//Function to delete item
void itemdelete(void *item)
{
  if (item != NULL) {
    free(item);
  }
}

//Function to delete item from hashtable
void htitemdelete(void *item)
{
  if (item != NULL) {
    //Do Nothing
  }
}

//Function to check if URL is equivalent to one in hashtable
void hashfunc (void *arg, const char *key, void *item) {
  if (strcmp(arg,item) == 0) { //check if strings are the same
    page_already_in = true; //set global variable for whether or not page is in hashtable to true
  }
}
