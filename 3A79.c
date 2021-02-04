/*
 * File - sub_3A79.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_3A79 OK+	              Used in: sub_3EAA, sub_39CA
 *
 * Compiler generates code that performs expected action,
 * but differs from original image
 *********************************************************/
void sub_3A79(register struct aaa * sa, struct aaa * p2a) {
    int l1;

#ifdef DEBUG
    printf("\tsub_3A79(%x, %x)\n", sa, p2a);
#endif

    l1 = nodesize(sa);
    if(l1 != 0) {
      if(l1 < 4) {
        l1 <<= 3;
        p2a->a_l15.l &= ((long)1<<l1) + (-1);
        if(sub_14F3(sa) == REG_A) {
          if((p2a->a_l15.l & (1<<(l1-1))) != 0) {
            p2a->a_l15.l |= ((-1) - (((long)1<<l1) - 1)); /* no code matching */
          }
        }
      }
    }
    p2a->a_i14 = sa->a_i14;
    p2a->a_i12 = sa->a_i12; 
}

/* End of file sub_3A79.c  */


