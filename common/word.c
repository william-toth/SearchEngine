/*
 *William Toth
 *CS50, 21W
 *Common Word Functions
 */


#include <ctype.h>
#include <string.h>

//Function to normalize (or lowercase a word)
void normalize_word (char* word) {
  for (int i = 0; i < strlen(word); i++) { //loop through word
    word[i] = tolower(word[i]); //lowercase each letter
  }
}
