/*
 * File - sub_4BE5.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_4BE5 OK++			Used in: sub_54B6
 *********************************************************/
int sub_4BE5(register struct aaa * sa) {


#ifdef DEBUG
    printf("\tsub_4BE5(%x)\n", sa);
#endif

    if(sa->a_c0 != CONST) goto m1;
    if(sa->a_l15.l != 0)  goto m1;
    return 1;
m1: return 0;
}

/*********************************************************
 * sub_4C12 OK++			Used in: sub_54B6
 *********************************************************/
int sub_4C12(register struct aaa * sa) {

#ifdef DEBUG
    printf("\tsub_4C12(%x)\n", sa);
#endif

    if(sa->a_c0 == GADDR) {
      if(sa->a_l15.wi[0]->a_c0 == IDOP) return 1;
    }
    if((dopetab[sa->a_c0] & 0x10) != 0) return 0; /* if "#", "..", "CONST"  */
    if(sub_4B89(sa) != 0) return 1;
    return dopetab[sa->a_c0] & 0xF;
}

/* End of file sub_4BE5.c  */


