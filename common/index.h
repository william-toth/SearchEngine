/*
 *William Toth
 *index loading and saving function headers for TSE project
 *CS50, 21W
 */

/*****************index_load*****************/
/*
 *User provides a file (with index) and an empty hashtable
 *Function loads the index into that hashtable
 */
void index_load (char* filename, hashtable_t* ht);



/*****************index_save*****************/
/*
 *User provides a file to be written to and a hashtable with index loaded in
 *Function saves index to the file
 */
void index_save (hashtable_t* index, FILE* file);
