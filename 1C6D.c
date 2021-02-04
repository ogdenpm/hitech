/*
 * File - sub_1C6D.c Created 19.03.2019 Last Modified 04.04.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_1C6D OK++			Used in: sub_1CEF
 *********************************************************/
int sub_1C6D(int p1, int p2) {

#ifdef DEBUG
    printf("\tsub_1C6D(%x, %x)\n", p1, p2);
#endif

    return (p1 + p2) & ((-1) - p2);
}

/* End of file sub_1C6D.c  */


