/*
 * File - sub_37ED.c Created 09.03.2019 Last Modified 17.06.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_37ED v1 OK+	      Used in: sub_387A, sub_43EF
 *
 * Elegantly designed function leads to the generation of
 * less optimal code, unlike the second version
 *********************************************************
void sub_37ED(register struct aaa * sa) {
    struct bbb * l1b;

#ifdef DEBUG
    printf("\tsub_37ED(%x)\n", sa);
#endif

    l1b = sa->a_i14;
    if(sa->a_i12 != 0) {
      sa->a_i12 >>= 2;
    } else {
      while(l1b->b_refl == 0) l1b = l1b->b_type;
      sa->a_i14 = l1b->b_type;
      sa->a_i12 = (l1b->b_refl)>>2;
    }
}
*/

/*********************************************************
 * sub_37ED v2 OK++	      Used in: sub_387A, sub_43EF
 *
 * This version generates code identical to binary image
 *********************************************************/
void sub_37ED(register struct aaa * sa) {
    struct bbb * l1b;

#ifdef DEBUG
    printf("\tsub_37ED(%x)\n", sa);
#endif

    l1b = sa->a_i14;
    if(sa->a_i12 == 0) goto m2;
    sa->a_i12 >>= 2;
    return;

m1: l1b = l1b->b_type;
m2: if(l1b->b_refl == 0) goto m1;
    sa->a_i14 = l1b->b_type;
    sa->a_i12 = (l1b->b_refl)>>2;
}

/* End of file sub_37EDD.c  */


