/*
 * File - sub_2C5E.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_2C5E OK+	   	      Used in: sub_2CE0, sub_47B2
 *
 * Compiler generates code that performs expected action,
 * but differs from original image
 *********************************************************/
long sub_2C5E(struct aaa * sa, long p2) {
    char loc;

#ifdef DEBUG
    printf("\tsub_2C5E(%x, %lx)\n", sa, p2); 
#endif

    if((loc = nodesize(sa) << 3) >= 0x20) return p2; 	
    if((p2 & ((long)1 << (loc - 1))) != 0) {	
      p2 |= (-1) - (((long)1<<loc) - 1);  /* No code matching */
    }
    return p2;
}

/* End of file sub_2C5E.c */


