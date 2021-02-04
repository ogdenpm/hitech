/*
 * File - sub_4C6D.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_4C6D OK+				Used in: sub_3CDF
 *********************************************************/
char sub_4C6D(struct aaa * p1a) {

#ifdef DEBUG
    printf("\tsub_4C6D(%x)\n", p1a);
#endif

    if(p1a->a_l15.wi[0]->a_c0 == USEREG) return 1;
    return 0;
}

/* End of file sub_4C6D.c  */


