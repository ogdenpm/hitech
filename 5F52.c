/*
 * File - sub_5F52.c Created 09.03.2019 Last Modified 27.06.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_5F52 OK++			Used in: sub_600E
 *********************************************************/
struct aaa * sub_5F52(register struct aaa * sa) {
    char         l1;
    struct aaa * l2;

#ifdef DEBUG
    printf("\tsub_5F52(%x)\n", sa);
#endif

    l1 = dopetab[sa->a_c0] & 0xC;
    if(l1 == 8) sa->a_l15.wi[1] = sub_5F52(sa->a_l15.wi[1]);
    if(l1 != 0) sa->a_l15.wi[0] = sub_5F52(sa->a_l15.wi[0]);

    switch (sa->a_c0) {
      case ADD:
        if(sa->a_l15.wi[0]->a_c0 == MINUS_U) {	/* m4: */
          l2              = sa->a_l15.wi[0];
          sa->a_l15.wi[0] = sa->a_l15.wi[1];
          sa->a_l15.wi[1] = l2;
        }
      case ASADD:
        if(sa->a_l15.wi[1]->a_c0 == MINUS_U) {	/* m5 */
          sub_36E0(sa->a_l15.wi[1]);
          sa->a_l15.wi[1] = sa->a_l15.wi[1]->a_l15.wi[0];
          sa->a_c0 = (sa->a_c0 == ASADD) ? ASSUB : SUB;
        }
    }
#ifdef DEBUG
    printf("\tsub_5F52\t\tReturn %x\n", sa);
#endif
    return sa;
}

/* End of file sub_5F52.c  */


