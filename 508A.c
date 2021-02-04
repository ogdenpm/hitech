/*
 * File - sub_508A.c Created 09.03.2019 Last Modified 31.05.2020
 */

#include "stdio.h"
#include <string.h>
#include "cgen.h"

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_508A OK++			Used in: sub_54B6
 *********************************************************/
struct aaa * sub_508A(register struct aaa * sa) {
    struct aaa * l1a;
    struct aaa * l2a;
    char	 buf[15];
    long	 l3;

#ifdef DEBUG
    printf("\tsub_508A(%x)\n", sa);
#endif

    if(sub_14F3(sa) == REG_F) {
      if(sa->a_l15.wi[0]->a_c0 == CONST) {
        l3 = sa->a_l15.wi[0]->a_l15.l;
        sub_36E0(sa->a_l15.wi[0]);
        sub_36E0(sa->a_l15.wi[1]);
        sprintf(buf, "%ld", l3);
        sa->a_l15.ci[0] = (char *)allocmem(strlen(buf)+1); /* create string */
        strcpy(sa->a_l15.ci[0], buf);
        sa->a_l15.ii[1] = sub_174C(); /* word_AE0F++ */
        sa->a_c0 = FCONST;
        return sa;						/* m1:  */
      }
    }
    if((dopetab[(l1a=sa->a_l15.wi[0])->a_c0] & 0x1000) != 0) {	/* m2:  */
      if(nodesize(l1a) >= nodesize(sa)) {
        if(sub_14F3(sa) != REG_F) {
          if(sub_14F3(l1a) != REG_F) { 
            l1a->a_i14 = sa->a_i14;
            l1a->a_i12 = sa->a_i12;
            sub_36E0(sa->a_l15.wi[1]);
            sub_36E0(sa);					/* m3:  */
            return l1a;
          }
        }
      }
    }
    if((char)sub_6246(sa, l1a) != 0) {				/* m5:  */
      sub_475C(sa->a_l15.wi[1]);
      l1a->a_i14 = sa->a_i14;
      l1a->a_i12 = sa->a_i12;
      sub_36E0(sa);
      return l1a;
    }
    if(nodesize(l1a) < nodesize(sa)) return sa;			/* m6:  */
    if(l1a->a_c0 == CONV) {
      if(nodesize(l1a->a_l15.wi[0]) >= nodesize(sa)) {
        if(sub_6246(sa, l1a->a_l15.wi[0]) != 0) goto m7;
        if(sub_14F3(sa) == sub_14F3(l1a)) {
          if(sub_14F3(sa) == sub_14F3(l1a->a_l15.wi[0])) {
m7:         sa->a_l15.wi[0] = l1a->a_l15.wi[0];
            sub_36E0(l1a->a_l15.wi[1]);
            sub_36E0(l1a);
            return sa;
          }
        }
      }
    }
    if((dopetab[l1a->a_c0] & 0xC00) == 0) return sa; 		/* m8:  */
    if(sub_14F3(l1a) == REG_F) return sa;
    if((dopetab[l1a->a_c0] & 0x400) != 0) {
      if(l1a->a_l15.wi[0]->a_c0 != CONV) return sa;
      if(nodesize(l1a->a_l15.wi[0]->a_l15.wi[0]) >= nodesize(l1a)) return sa;
    }
    l2a = sub_43EF(CONV, l1a->a_l15.wi[0], sa->a_l15.wi[1]);	/* m9:  */
    *sa = *sa->a_l15.wi[1];
    if((dopetab[l1a->a_c0] & 8) != 0) {
      sa = sub_43EF(CONV, l1a->a_l15.wi[1], sa);
    } else {
      sub_36E0(sa);						/* m10: */
      sa = 0;	  
    }
    l2a = sub_43EF((uchar)l1a->a_c0, l2a, sa);			/* m11: */
    sub_36E0(l1a);
    return l2a;
}

/*********************************************************
 * sub_53EE  OK++			Used in: sub_54B6
 *********************************************************/
struct aaa * sub_53EE(register struct aaa * sa) {
    struct aaa * l1a;

#ifdef DEBUG
    printf("\tsub_53EE(%x)\n", sa);
#endif

    if((dopetab[(l1a = sa->a_l15.wi[0])->a_l15.wi[0]->a_c0] & 0x1000) != 0) {
      l1a        = l1a->a_l15.wi[0];
      l1a->a_i14 = sa->a_i14;
      l1a->a_i12 = sa->a_i12;
      sub_36E0(sa->a_l15.wi[0]);
      sub_36E0(sa);
      return l1a;
    }
    sa->a_c0        = CONV;
    sa->a_l15.wi[1] = l1a;
    sa->a_l15.wi[0] = l1a->a_l15.wi[0];
    l1a->a_c0       = TYPEOP;
    l1a->a_i14      = sa->a_i14;
    l1a->a_i12      = sa->a_i12;
    byte_B013       = 1;
    return sa;
}

/* End of file sub_508A.c  */


