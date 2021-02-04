/*
 * File - sub_2CE0.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 *  sub_2CE0 OK++			Used in: sub_2D09
 *********************************************************/
void sub_2CE0(struct aaa * p1a, long p2) {

#ifdef DEBUG
    printf("\tsub_2CE0(%x, %lx)\n", p1a, p2); 
#endif

    printf("%ld", sub_2C5E(p1a, p2));
}

/* End of file sub_2CE0.c */


