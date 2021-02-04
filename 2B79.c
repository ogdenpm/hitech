/*
 * File - sub_2B79.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_2B79 OK++			 Used in: sub_1F4B
 *********************************************************/
uchar sub_2B79(register struct aaa * sa) {
    uchar l1;
    int   l2;

#ifdef DEBUG
    printf("\tsub_2B79(%x)\n", sa);
#endif

    l1 = *((char*)sa + sa->a_c1 + 8);
    byte_AFFA = 0;
    l2 = sub_2B2A(sa);
    if(l1 != 0) {	
      if(sub_6589(l2, l1) == l1) return l1;
    }
    return byte_AFFA;
}

/*********************************************************
 * sub_2BD0 OK++      Used in: sub_793, sub_808, sub_3CDF
 *			       sub_3DC9
 *********************************************************/
void sub_2BD0(register struct aaa * sa) {
    int tmp;

#ifdef DEBUG
    printf("\tsub_2BD0(%x)\n", sa);
#endif

    sa->a_c1 = 0;

    if(sub_1F4B(sa, 0x48, word_B017, 0, &tmp) <= 0) {
      faterror("Expression too complicated");
    }
    sub_35E6(sa);
    if(sa->a_c0 == COLON_U) {
      if((sa->a_i12 & 2) != 0) {
        sub_B96(array_AEDB[lvlidx]->b_i11); /* emit_call_ncsv */
        sub_1EDF();
      }
      if(  sa->a_l15.wi[0]->a_c0 == IDOP) {
        sa->a_l15.wi[0]->a_l15.wi[0]->a_c3 |= 1;
      }
    }
    sub_475C(sa);
}

/* End of file sub_2B79.c  */


