/*
 * File - sub_6B1D.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * uerror v1 OK++
 * Nonfatal error
 *********************************************************/
void uerror(char * msg) {

#ifdef DEBUG
    printf("\tuerror()\n");
#endif

    fprintf(stderr, msg);
    if(++errcnt >= MAXERR)
      faterror("Too many errors");
}

/*
 * Following restored functions are left as comments to
 * preserve original structure of original program.
 */

/*********************************************************
 * uerror v0 OK++		Restored by decompilation
 * Nonfatal error
 *********************************************************
void uerror(char * p1, char * p2, char * p3) {

    sub_6B55(p1, p2, p3);
    if(++errcnt >= MAXERR) {
      faterror("Too many errors");
    }
}
*/

/*********************************************************
 * sub_6B55 OK++	      	  Used in: ferror, uerror
 *
 * When changing diagnostic functions to balance number
 * parameters, this function was not required.
 *********************************************************
void sub_6B55(char *p1, char *p2, char *p3) {

    fprintf(stderr, "%s:%d:\t", progname, lineno);
    fprintf(stderr, p1, p2, p3);
    fputc ('\n', stderr);
}
*/

/* End of file sub_6B1D.c  */


