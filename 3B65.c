/*
 * File - sub_3B65.c Created 09.03.2019 Last Modified 29.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_3B65 OK++			Used in: sub_3EAA
 *********************************************************/
void sub_3B65(register unsigned long * ptr, long p2, int operator) {

#ifdef DEBUG
    printf("\tsub_3B65(%x, %lx, %d)\n", ptr, p2, operator);
#endif

    switch (operator) {
      case MOD:	   *ptr /=  p2;  break;
      case DIV:    *ptr %=  p2;  break;
      case RSHIFT: *ptr >>= p2;  break;
    }
    return;
}

/* End of file sub_3B65.c  */


