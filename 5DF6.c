/*
 * File - sub_5DF6.c Created 09.03.2019 Last Modified 31.05.2020
 */

#include "stdio.h"
#include <string.h>
#include "cgen.h"

/*********************************************************
 * sub_5DF6 OK++			Used in: sub_600E
 *********************************************************/
struct aaa * sub_5DF6(register struct aaa * sa) {
    char   l1;
    char * l2;

#ifdef DEBUG
    printf("\tsub_5DF6(%x)\n", sa);
#endif

    l1 = dopetab[sa->a_c0] & 0xC;
    if(l1 == 8) sa->a_l15.wi[1] = sub_5DF6(sa->a_l15.wi[1]);
    if(l1 != 0) sa->a_l15.wi[0] = sub_5DF6(sa->a_l15.wi[0]);

    switch (sa->a_c0) {
      case SUB:
      case ASSUB:
        if(sa->a_l15.wi[1]->a_c0 == CONST) {
          sa->a_l15.wi[1]->a_l15.l = 0 - sa->a_l15.wi[1]->a_l15.l;
        } else {
          sa->a_l15.wi[1] = sub_43EF(MINUS_U, sa->a_l15.wi[1], 0);
        }
        sa->a_c0 = (sa->a_c0 == SUB) ? ADD : ASADD;
        break;
      case MINUS_U:
        if(sa->a_l15.wi[0]->a_c0 == MINUS_U) {
          sub_36E0(sa);
          sa = sa->a_l15.wi[0];
          sub_36E0(sa);
          sa = sa->a_l15.wi[0];
        }
        if(sa->a_l15.wi[0]->a_c0 == FCONST) {
          sub_36E0(sa);
          sa = sa->a_l15.wi[0];
          l2 = (char *)allocmem(strlen(sa->a_l15.ci[0])+2);
          strcat(strcpy(l2, "-"), sa->a_l15.ci[0]);
          sub_7028((struct ptr *)sa->a_l15.wi[0]);
          sa->a_l15.ci[0] = l2;
        }
    }
#ifdef DEBUG
    printf("\tsub_5DF6\t\tReturn %x\n", sa);
#endif
    return sa;
}

/* End of file sub_5DF6.c  */


