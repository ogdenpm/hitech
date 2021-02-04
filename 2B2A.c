/*
 *  File - sub_2B2A.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_2B2A OK+      Used in: sub_1F4B, sub_283E, sub_2B79
 *********************************************************/
int sub_2B2A(register struct aaa * sa) {

#ifdef DEBUG
    printf("\tsub_2B2A(%x)\n", sa);
#endif

    if((sa->a_c1) == 0) {
      if((dopetab[sa->a_c0] & 0xC) == 0) return 0;
      return sub_2B2A(sa->a_l15.wi[0]);			/* LOGOP & QUEST */
    }
    return sub_283E(sa, sa->a_c1 - 1); /* Generated code has insignificant differences */
}

/* End of file sub_2B2A.c  */


