/*
 * File - sub_6AA2.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "cgen.h"

extern FILE	   *f_out, *f_in;

/* 
 * To comply with C standard functions are replaced with similar
 * ones with a variable number of parameters
 *
 * sub_6B55 excluded because it is unnecessary
 */

/*********************************************************
 * faterror OK++     Used in: sub_6C8,  sub_17E0, sub_19C1,
 *			      sub_2BD0, sub_4192, sub_6B1D,
 * Fatal error  	      sub_6B9B,
 *********************************************************/
void faterror(char * fmt, ...) {
    va_list args;

#ifdef DEBUG
    printf("\tfaterror()\n");
#endif

    fprintf(stderr, "%s:%d:\t", progname, lineno);
    if(strlen(fmt) > 0) {
      va_start(args, fmt);
      vfprintf(stderr, fmt, args);
      va_end(args);
    }
    fputc ('\n', stderr);
    fclose(f_out);	/* sub_7855(stdout); */
    exit(2);
}

/*********************************************************
 * warning v1 OK++   Used in: sub_E43,  sub_3DC9, sub_43EF,
 * Warning message	      sub_54B6, sub_5CF5, sub_600E
 *********************************************************/
void warning(char *fmt, ...) {
    va_list args;

#ifdef DEBUG
    printf("\twarning()\n");
#endif

    if(wflag == 0) {
      fprintf(stderr, "%s:%d:\t", progname, lineno);
      if(strlen(fmt) > 0) {
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
      }
      fprintf(stderr, " (warning)\n");
    }
}

/*********************************************************
 * faterror v0 OK++  Used in: sub_6C8,  sub_17E0, sub_19C1,
 *			      sub_2BD0, sub_4192, sub_6B1D,
 *			      sub_6B9B,
 * Fatal error      main (contains more than 1 parameter!)
 *********************************************************
void faterror(char * p1, char *p2, char *p3) {

    sub_6B55(p1, p2, p3);
    fclose(f_out);	 //sub_7855(stdout);   
    exit(2);
}
*/

/*********************************************************
 * warning v0 OK++   Used in: sub_E43,  sub_3DC9, sub_43EF,
 * Warning message	      sub_54B6, sub_5CF5, sub_600E
 *********************************************************
void warning(char *p1, char *p2, char *p3) {

    if(wflag == 0) {
      fprintf(stderr, "%s:%d:\t", progname, lineno);
      fprintf(stderr, p1, p2, p3);
      fprintf(stderr, " (warning)\n");
    }
}
*/

/* End of file sub_6AA2.c */


