/*
 * File - sub_475C.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_475C OK++    Used in: sub_808,  sub_E43,  sub_17E0,
 *			     sub_19C1, sub_1B0C, sub_2BD0,
 *			     sub_3DC9, sub_3EAA, sub_43EF,
 *			     sub_475C, sub_4DA3, sub_4FA8,
 *			     sub_508A, sub_54B6
 *********************************************************/
void sub_475C(register struct aaa * sa) {
    int loc;

#ifdef DEBUG
    printf("\tsub_475C(%x)\n", sa);
#endif

    if((loc = dopetab[sa->a_c0] & 0xC) != 0) {
      sub_475C(sa->a_l15.wi[0]);
      if(loc == 8) {
        sub_475C(sa->a_l15.wi[1]);
      }
    }
    sub_36E0(sa);
#ifdef DEBUG
    printf("\tsub_475C\t\tReturn\n");
#endif
}

/* End of file sub_475C.c  */


