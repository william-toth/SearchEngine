/*
 *William Toth
 *Common functions for TSE project
 *CS50, 21W
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>
 #include <string.h>
 #include "../libcs50/webpage.h"

//Function to save a page. see pagedir.h for details
 void pagesave (webpage_t *currpage, int idnum, char *dirchar) {
   FILE *fp;
   char filename[10]; //10 is enough digits
   sprintf(filename, "%d", idnum); //turn file name to string
   if (dirchar[-1] != '/') { //check if final character of directory is a slash
     strcat(dirchar, "/"); //if not, add one
   }
   strcat(dirchar,filename); //concatenate directory and file name
   fp = fopen(dirchar, "w"); //create/open file with directory/file as name
   fprintf(fp, "%s\n",webpage_getURL(currpage));
   fprintf(fp, "%d\n",webpage_getDepth(currpage));
   fprintf(fp, "%s",webpage_getHTML(currpage)); //write html to page
   fclose(fp); //close file
 }
