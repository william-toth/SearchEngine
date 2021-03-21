/*
 *William Toth
 *CS50, 21W
 *Querier for Tiny Search Engine
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

 //global
 int number_of_files; //number of files in page directory
 int total_matches; //total matched for a given query
 char* directory; //page directory
 int highest_score; //highest score
 int highest_doc; //document with highest score
 int queries; //number of queries performed

 //Helper functions
 void htitemdelete(void *item);
 static void ht_calc_num_files (void *arg, const char *key, void *item);
 static void ctrs_calc_num_files(void *arg, const int key, const int count);
 static void func1(void *arg, const int key, const int count);
 static void func2(void *arg, const int key, const int count);
 static void add_temp_to_scores(void *arg, const int key, const int count);
 static void print_result(void *arg, const int key, const int count);
 static void count_result(void *arg, const int key, const int count);
 static void add_highest(void *arg, const int key, const int count);



//Function to print invalid syntax message (to help with aesthetic of code)
 void print_invalid_syntax(){
   fprintf(stdout, "Error: Invalid Syntax\n-------------------------------------\n");
 }

//Function to rank the scores
//Returns new counters
 counters_t* rank_sites(counters_t *scores) {
   counters_t* ranked = counters_new();
   for (int i = 0; i < total_matches; i++) {
     highest_score = 0;
     counters_iterate(scores, "placeholder", add_highest);
     counters_set(ranked, highest_doc, counters_get(scores, highest_doc));
     counters_set(scores, highest_doc, 0);
   }
   return ranked;
 }

 int query (hashtable_t *index) {

   total_matches = 0;

   //Make an array of strings to hold the words entered by user
   char* query_array[50];

   FILE* readFrom;

   readFrom = stdin;

   char curr;
   if (queries != 0) {
     fprintf(stdout, "Query? "); //Prompt user
     curr = fgetc(readFrom);
   } else {
     curr = '\n';
   }

   bool typed_num = false;

   int word_num = 0; //place in input (ex. in 'I am here today', word_num for 'here' would be 2)
   int char_num = 0; //place in each word
   char currword[255]; //current word
   char last = ' ';
   while (curr != '\n') {

     if (isdigit(curr) != 0) { //If user enters a digit
       typed_num = true;
     }
     if (curr == EOF) {
       fprintf(stdout, "\n");
       return 1;
     }

     if (curr == ' ' && isalpha(last) != 0) { //when there is a space
       char* wordToAdd = malloc(sizeof(currword+1)); //make space for previous word
       strcpy(wordToAdd, currword); //copy currword to previous word
       query_array[word_num] = wordToAdd; //add previous word
       word_num++; //increment word number
       memset(currword, 0, 255); //reset currword to empty
       char_num = 0; //reset char num to 0

     } else {
       currword[char_num] = curr; //add current character to currword
       char_num++; //increment char num
     }
     last = curr;
     curr = fgetc(readFrom);
   }
   char* wordToAdd = malloc(sizeof(currword+1)); //make space for previous word
   strcpy(wordToAdd, currword); //copy currword to previous word
   query_array[word_num] = wordToAdd; //add previous word
   word_num++;
   memset(currword, 0, 255); //reset currword to empty

   if (typed_num) {
     print_invalid_syntax();
     return 2;
   }
   //set every index that isn't a word to NULL
   while (word_num < 50) {
     query_array[word_num] = NULL;
     word_num++;
   }

   //normalize every word in query
   for (int i = 0; i < 50; i++) {
     if (query_array[i] != NULL) {
       normalize_word(query_array[i]);
       //printf("%s\n", query_array[i]);
     }
   }


   //Use a counters for final scores

   counters_t *scores = counters_new();

   counters_t *temp_scores;

   //Loop through query
   for (int i = 0; query_array[i] != NULL; i++) {
     char* word = query_array[i]; //current word
     //If word is 'and' or 'or'
     if (strcmp(word, "and") == 0 || strcmp(word, "or") == 0) {
       if (i == 0 || query_array[i+1] == NULL) { //if it's the first word, error
         print_invalid_syntax();
         return 2;
       }
     } else {//if not 'and' or 'or'
        //If the word is the first word or directly after an 'or'
        if (i == 0 || strcmp(query_array[i-1], "or") == 0) {
          //printf("%s\n",query_array[i]);
          temp_scores = counters_new();
          //Get the document counts for that word
          counters_t *word_docs = hashtable_find(index, query_array[i]);
          //Add every score to scores
          counters_iterate(word_docs, temp_scores, func1);
          //Look at every word after it until end of query or an 'or' occurs
          int s = i+1;
          while (query_array[s] != NULL && strcmp(query_array[s], "or") != 0) {
            //If word is and, go to next word
            if (strcmp(query_array[s], "and") == 0 || strcmp(query_array[s], "or") == 0) {
              if (query_array[s+1] == NULL) { //if it's the last word, error
                print_invalid_syntax();
                return 2;
              } else { //if it's neither the first or last word
                //if the word before or after it is also 'or' or 'and', error
                if (strcmp(query_array[s+1], "and") == 0 || strcmp(query_array[s+1], "or") == 0) {
                  print_invalid_syntax();
                  return 2;
                }
                if (strcmp(query_array[s], "and") == 0) {
                  s++;
                  continue;
                }
              }
            }
            //Get the document counts for word
            counters_t *word_docs = hashtable_find(index, query_array[s]);
            //loop through number of files
            for (i = 0; i <= number_of_files; i++) {
              if ((counters_get(word_docs, i) == 0)) { //If file doesn't have a word
                counters_set(word_docs, i, 0); //Set count of it to 0 (helper function uses this)
              }
            }
            counters_iterate(word_docs, temp_scores, func2);
            s++; //Increment word (after or or i = 0)
          }

          counters_iterate(temp_scores, scores, add_temp_to_scores);
          counters_delete(temp_scores);
          i = s; //Jump ahead in query to end of 'and' sequence
        }
     }
   }

   for (int i = 0; query_array[i] != NULL; i++) {
     free(query_array[i]);
   }

   if (queries != 0) {

     counters_iterate(scores, "placeholder", count_result); //count the number of matches

     fprintf(stdout, "Matches %d documents (ranked):\n", total_matches);

     counters_t *ranked = rank_sites(scores); //rank scores

     counters_iterate(ranked, stdout, print_result); //print ranked scores

     counters_delete(ranked);
     counters_delete(scores);

     fprintf(stdout, "--------------------------------------\n");

   }

   return 0;
 }


 int
 main(int argc, char *argv[]) {

   if (argc != 3) { //Check for correct number of arguments
     fprintf(stderr, "Error: Please give two arguments\n");
     return 1;
   }

   //Check if directory given can be opened
   DIR* dir = opendir(argv[1]);
   if (dir == NULL) { //Check if directory is valid
     fprintf(stderr, "Error: Not a valid directory\n");
     return 1;
   }
   closedir(dir);
   directory = argv[1];


   hashtable_t *index = hashtable_new(20);

   //Try to open file
   FILE *fp;
   if ((fp = fopen(argv[2], "r"))) {
     fclose(fp);
     index_load(argv[2], index); //Load file into an index (ht of ctrs)
   } else {
     fprintf(stderr, "Error: Not a valid index file\n");
     return 1;
   }

   queries = 0; //number of queries that have happened

   //Calculate number of files
   number_of_files = 0;
   hashtable_iterate(index, "placeholder", ht_calc_num_files);

   while (query(index) != 1) { //Call query until it returns 1
     queries++;
   }

   hashtable_delete(index, htitemdelete);


   return 0;
 }


/************************HELPER FUNCTIONS************************/

//delete hashtable item
 void htitemdelete(void *item)
 {
   if (item != NULL) {
     counters_delete(item);
   }
 }

 //Helper function to calculate number of files
 static void ht_calc_num_files (void *arg, const char *key, void *item) {
   counters_t *ctrs = item;
   counters_iterate(ctrs, arg, ctrs_calc_num_files);
 }

 //Helper function to calculate number of files
 static void ctrs_calc_num_files(void *arg, const int key, const int count) {
   if (key > number_of_files) {
     number_of_files = key;
   }
 }

//If first word in the 'and' sequence
static void func1(void *arg, const int key, const int count) {
  int k = key;
  int c = count;
  counters_set(arg, k, c); //set doc in scores to count
}

//If not first word in the 'and' sequence
 static void func2(void *arg, const int key, const int count) {
   int k = key;
   int c = count;

   if (c == 0) { //If word doesn't appear
     counters_set(arg, k, 0); //set score to 0
   } else {
     if (c < counters_get(arg, k)) { //if count is less than score
       counters_set(arg, k, c); //set score to count
     }
   }
 }

//helper function to count the amount of matches
 static void count_result(void *arg, const int key, const int count) {
   if (count != 0) {
     total_matches++;
   }
 }

//helper function to print out the result
 static void print_result(void *arg, const int key, const int count) {
   if (count != 0) {
     fprintf(arg, "score %3.1d doc %2.1d: ", count, key);
     char url[255];
     int i = 0;
     char* file = get_path(directory, key);
     FILE* fp = fopen(file, "r");
     char curr = fgetc(fp);
     while (curr != '\n') {
       url[i] = curr;
       i++;
       curr = fgetc(fp);
     }
     fclose(fp);
     fprintf(arg, "%s\n", url);
   }
 }
 //helper function to add scores on either side of 'or'
 static void add_temp_to_scores(void *arg, const int key, const int count) {
   if (counters_get(arg, key) == 0) {
     counters_set(arg, key, count);
   } else {
     counters_set(arg, key, counters_get(arg, key) + count);
   }
 }

//helper function to rank scores by adding the highest one
 static void add_highest(void *arg, const int key, const int count) {
   if (count != 0) {
     if (count > highest_score) {
       highest_score = count;
       highest_doc = key;
     }
   }
 }
