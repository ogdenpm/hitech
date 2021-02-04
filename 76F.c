/*
 * File - sub_76F.c  Created 09.03.2019 Last Modified 26.05.2020
 */

#include "stdio.h"
#include <ctype.h>
#include "cgen.h"

enum psect {
  P_BSS = 1,
  P_TEXT,
  P_DATA
};

/*********************************************************
 * sub_76F OK++	      Used in: sub_6D1,  sub_B19, sub_E43,
 * 			       sub_17E0, sub_1B0C 
 ;
 * Search for expected character (closing square bracket)
 *********************************************************/
void sub_76F(int par) {
    char ch;

#ifdef DEBUG
    printf("\tsub_76F()\n");
#endif

    do {
      ch = getchar();
    } while (isspace(ch));	/* Skip white-space characters */

    if(ch != (char)par) {
      sub_6C8(); 		/* {faterror("Bad int. code");} */
    }
}

/*********************************************************
 * sub_793 OK++ 			 Used in: sub_6D1
 *********************************************************/
void sub_793(void) {
    char	  * loc1;
    char	    buf[1024];
    register char * ptr;

#ifdef DEBUG
    printf("\tsub_793()\n");
#endif

    selpsect(P_DATA);
    sub_2BD0(sub_600E(sub_43EF(COLON_U, sub_43EF(COLON_S, sub_4192(), 0), 0)));
    ptr = buf;
    for(;;) {
      loc1 = sub_306();		/* Get_token */
      if(*loc1 == ']') break;	/* If data is over go to its output */
      *ptr = atoi(loc1);	/* Convert string to int value and place it in buffer */
      ptr++;			/* Set next address  */
    }				/* and continue processing */
    sub_155D(buf, ptr-buf); 	/* Emit data "defb byte1, ..." ("ptr-buf" bytes from "buf")*/
}

/* End of file sub_76F.c  */


