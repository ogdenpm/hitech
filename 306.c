/*
 * File - sub_306.c Created 09.03.2019 Last Modified 11.05.2020
 */
 
#include "stdio.h"
#include <stdlib.h>
#include <ctype.h>
#include "cgen.h"

/*********************************************************
 * sub_306 v1 OK+    Used in: sub_6D1,  sub_793,  sub_B19,
 *			      sub_E43,  sub_17E0, sub_19C1,
 *			      sub_4192
 * get_token	     No code matching
 *********************************************************/
char * sub_306() {
    int ch, mark;
    register char * ptr;

#ifdef DEBUG
    printf("\tsub_306()");
#endif
	
    mark = 0;
    for(;;) {
      ptr = buffer;

/*    do {
	if((ch = getchar()) == EOF) break;
      } while((isspace(ch)) != 0);
      if(ch == EOF) return (-1);
*/
      do {
	if((ch = getchar()) == EOF)
	return (char *)EOF;		/* Read characters until	*/
      } while(isspace(ch) != 0);	/* detection of white-space	*/

      *(ptr++) = ch;			/* Put character in buffer	*/
      do {
	*(ptr++) = ch = getchar();
	if(ch == EOF) break;		/* Get and put in buffer 	*/
      } while(isspace(ch) == 0);	/*  white-space character	*/

      ptr += (-1); 			/* Put 0 in the place 	 	*/
      *ptr = 0;				/* of the last character 	*/
    
      if(*buffer == '"') {		/* If 1 character in buffer 	*/
	lineno = atoi(buffer+1);	/* is '"' assign lineno value  	*/
	mark=(ch != '\n') ? 1 : 0;	/* If detected newline set mark */
	continue;			/* Parse next line 		*/
      }
      if (mark != 0) {			/* If '\n' is not encountered 	*/
					/* copy program name to buffer 	*/
	strncpy(progname, buffer, sizeof(progname)-1);
	mark = 0;			/* clear mark and		*/
	continue;			/* parse next line 		*/
      }
      if(*buffer != ';' 		/* If 1 or 2 character of  	*/
      || *(buffer+1) != ';') {		/* buffer contains ';' 		*/
#ifdef DEBUG
        printf("\t\tReturn \"%s\"\n", buffer);
#endif
        return buffer;			/* return buffer addr		*/
      }
      do {
	ch = getchar();			/* Read and  			*/
	putchar(ch);			/* print characters 		*/
      } while (ch != '\n');		/* not yet detected newline 	*/
    } 					/* Parse next line 		*/
}

/* End of file sub_306.c */


