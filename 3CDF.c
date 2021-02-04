/*
 * File - sub_3CDF.c Created 09.03.2019 Last Modified 31.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_3CDF OK++			Used in: sub_3DC9
 *********************************************************/
struct aaa * sub_3CDF(register struct aaa * sa) {
    int loc;

#ifdef DEBUG
    printf("\tsub_3CDF(%x)\n", sa);
#endif

    if(sa->a_c0 == SCOLON) {
      sub_2BD0(sa->a_l15.wi[0]);
      sub_36E0(sa);
      sa = sa->a_l15.wi[1];
    }
    if(byte_B014 != 0xA) {
      if((dopetab[sa->a_c0] & 0x4000) != 0) return sa;
      switch(sa->a_c0) {
        case INCR:
        case DECR:
          if(sub_4C6D(sa) != 0) {
            array_AFFD[byte_B014++] = sa;
            sa->a_c0 = (sa->a_c0 == INCR) ? ASADD : ASSUB;
            sa = sub_377A(sa->a_l15.wi[0]);
          }
      }
      loc = dopetab[sa->a_c0]/*& 0xC */;
      if((loc & 0xC) != 0) sa->a_l15.wi[0] = sub_3CDF(sa->a_l15.wi[0]);
      if((loc & 0xC) == 8) sa->a_l15.wi[1] = sub_3CDF(sa->a_l15.wi[1]);
    }
    return sa;
}

/*********************************************************
 * sub_3DC9 OK++		Used in: sub_6D1, sub_D66
 *********************************************************/
void sub_3DC9(register struct aaa * sa) {
    unsigned loc;

#ifdef DEBUG
    printf("\tsub_3DC9(%x)\n", sa);
#endif

    sa = sub_600E(sa);
    if(sa->a_c0 == DOLLAR) {
      if(sa->a_l15.wi[0]->a_c0 == CONST) {
        warning("constant conditional branch");
        if(sa->a_l15.wi[0]->a_l15.l != 0) {
          sa->a_c0 = DOLLAR_U;
          sub_36E0(sa->a_l15.wi[0]);
          sa->a_l15.wi[0] = sa->a_l15.wi[1];
        } else {
          sub_475C(sa);
          return;
        }
      }
    }
    byte_B014 = 0;
    if(sa->a_c0 == INCR) {
      sa->a_c0 = ASADD;
    } else {
      if(sa->a_c0 == DECR) {
        sa->a_c0 = ASSUB;
      }
    }
    sa = sub_3CDF(sa);
    if(byte_B014 != 0) sa = sub_600E(sa);
    sub_2BD0(sa);
    loc = 0;
    while(loc < byte_B014) {
      sub_2BD0(array_AFFD[loc]);
      loc++;
    }
}

/* End of file sub_3CDF.c */


