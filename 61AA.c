/*
 * File - sub_61AA.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include <ctype.h>
#include "cgen.h"

#define REG_A 1
#define REG_L 2
#define REG_F 3

extern FILE	   *f_out, *f_in;

/*********************************************************
 * sub_61AA OK++			Used in: sub_5CF5
 *********************************************************/
int sub_61AA(register struct bbb * sb, int p2) {

#ifdef DEBUG
    printf("\tsub_61AA(%x, %x)\n", sb, p2);
#endif

    if(rflag == 0) {
      if(isupper(p2) != 0) {
        if(sb->b_refl == 1) {
          if(1 >= (unsigned)sb->b_nelem) {
            if(sub_6589(word_B017, 9) == 0) return 0;
            if(sb->b_c13 == 5) sb->b_c3 |= 4;
            sb->b_c13 = 2;
            sb->b_memb = (unsigned)sub_6589(word_B017, 9); /* assigning to "int *" from "unsigned int" */
            word_B017 &= ((-1) - array_AAE8[(int)sb->b_memb]);
            return 1;
          }
        }
      }
    }
    return 0;
}

/*********************************************************
 * sub_6246 OK++	      Used in: sub_508A, sub_54B6
 *********************************************************/
int sub_6246(struct aaa * p1a, struct aaa * p2a) {

#ifdef DEBUG
    printf("\tsub_6246(%x, %x)\n", p1a, p2a);
#endif

    if(nodesize(p1a) == nodesize(p2a)) {
      if(sub_14F3(p1a) == sub_14F3(p2a)) {
        return 1;
      }
    }
    return 0;
}

/*********************************************************
 * sub_628F v1 OK++ 
 *********************************************************/
char sub_628F(struct aaa * p1a, struct aaa * p2a) {

#ifdef DEBUG
    printf("\tsub_628F(%x, %x)\n", p1a, p2a);
#endif

    return ((sub_14F3(p1a) != REG_A) ||
            (sub_14F3(p2a) != REG_A)) ? (int)0 : (int)1 ;
}

/*********************************************************
 * sub_628F v2 - OK+ 
 *********************************************************
int sub_628F(struct aaa * p1a, struct aaa * p2a) {

#ifdef DEBUG
    printf("\tsub_628F(%x, %x)\n", p1a, p2a);
#endif
	
    if(sub_14F3(p1a) != REG_A) goto m1;
    if(sub_14F3(p2a) != REG_A) goto m1;
    return 1;
m1: return 0;
}
*/

/*********************************************************
 * sub_62BE OK++			Used in: sub_54B6
 *********************************************************/
char sub_62BE(register struct aaa * sa, struct aaa * p2a) {
    long l1, l2;
    char l3;

#ifdef DEBUG
    printf("\tsub_62BE(%x, %x)\n", sa, p2a);
#endif
    l3 = nodesize(sa->a_l15.wi[0])*8;
    if(l3 >= 0x20) return 1;
    l1 = (long)1<<l3;
    l2 = 0;
    if(sub_628F(sa, sa->a_l15.wi[0]) != 0) {
      l1 /= 2;
      l2 = 0 - l1;
    }
    return ((p2a->a_l15.l < l2) ||
            (p2a->a_l15.l >= l1)) ? 0 : 1;
}

/* End of file sub_61AA.c  */




