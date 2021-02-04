/*
 * File - sub_3EAA.c Created 09.03.2019 Last Modified 29.05.2020
 */

#include "stdio.h"
#include <stdlib.h>
#include "cgen.h"

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_3EAA OK+				Used in: sub_600E
 *********************************************************/
#if 1
/*vvvvvvvvvvvvvvvvvvvvvvvvvvv*/

struct aaa * sub_3EAA(register struct aaa * sa) {
    struct aaa * l1a;
    int		 l2;

#ifdef DEBUG
    struct aaa * tmp;
    printf("\tsub_3EAA(%x)\n", sa);
#endif

    if((l2 = dopetab[sa->a_c0] & 0xC) != 0)
      sa->a_l15.wi[0] = sub_3EAA(sa->a_l15.wi[0]);
    if(l2 == 8) sa->a_l15.wi[1] = sub_3EAA(sa->a_l15.wi[1]);
    if(sa->a_c0 == CONV) {
      if((sa->a_l15.wi[0])->a_c0 == FCONST) {
        if(sub_14F3(sa) == REG_F) {
          l1a = sa->a_l15.wi[0];
          l1a->a_i14 = sa->a_i14;
          sub_36E0(sa->a_l15.wi[1]);
          sub_36E0(sa);
#ifdef DEBUG
          tmp = l1a;
          goto d2;
#else 
          return l1a;
#endif
        }
      }
    }
    if((l2 == 0) || ((sa->a_l15.wi[0])->a_c0 != CONST)) { /* m3: */
#ifdef DEBUG
      goto d1;
#else
      return sa;
#endif
    }
    if(sa->a_c0 == CONV) {	 /* m6: */

#ifdef DEBUG
      tmp = sub_39CA(sa);
      goto d2;
#else
      return sub_39CA(sa);
#endif
    }
    if((l2 != 8) || ((sa->a_l15.wi[1])->a_c0 != CONST)) goto m8;  /* m7: */

#ifdef DEBUG
d1: tmp = sa;
d2: printf("\tsub_3EAA\t\tReturn %x\n", tmp);
    return tmp;
#else 
    return sa;
#endif
m8:   if(sub_14F3(sa) == REG_L) {		/* m8:  */
        switch(sa->a_c0) {
          case MOD:
          case DIV:
          case RSHIFT: goto m14;
          case LT:
          case LEQ:
          case GT:
          case GEQ:    goto m12;
        }
      }
      switch(sa->a_c0) {			/* m10: */
        case BNOT:    goto m23;
        case NOT:     goto m21;
        case MINUS_U: goto m19;
        case BAND:
        case LAND:
        case SUB:
        case BXOR:
        case BOR:
        case LOR:
        case ADD:
        case MUL:
        case DIV:
        case MOD:
        case RSHIFT:
        case LSHIFT:  goto m18;
        case NEQL:
        case LT:
        case LEQ:
        case EQL:
        case GT:
        case GEQ:     goto m17;
        default:   {  
#ifdef DEBUG
		      goto d1;
#else
        	      return sa;
#endif
        	   }
      }
/*    return sa; */

m12:word_B015 = "constant relational expression";	
#ifdef DEBUG
    goto d1;
#else
    return sa;
#endif

m14:sub_3B65(&sa->a_l15.wi[0]->a_l15.ul, sa->a_l15.wi[1]->a_l15.l, sa->a_c0);
m15:if(l2 == 8) {
      sub_475C(sa->a_l15.wi[1]);
    }
    sub_3A79(sa, sa->a_l15.wi[0]);	/* m16: */
    sub_36E0(sa);
#ifdef DEBUG
    tmp = sa->a_l15.wi[0];
    goto d2;
#else
    return sa->a_l15.wi[0];
#endif

/* Two identical code fragments could be intended for different messages */

m17:word_B015 = "constant relational expression";	
#ifdef DEBUG
    goto d1;
#else
    return sa;
#endif

m18:sub_3BC6(&sa->a_l15.wi[0]->a_l15.l, sa->a_l15.wi[1]->a_l15.l, sa->a_c0);
    goto m15;

m19:sa->a_l15.wi[0]->a_l15.l = (long)0 - sa->a_l15.wi[0]->a_l15.l;
    goto m15;

m21:sa->a_l15.wi[0]->a_l15.l = sa->a_l15.wi[0]->a_l15.l == 0 ?
    (long)1 : (long)0; /* minor differences in the generated code */
    goto m15;

m23:sa->a_l15.wi[0]->a_l15.l =
    (long)(-1) - sa->a_l15.wi[0]->a_l15.l; /* minor differences in the generated code */
    goto m15;
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#else
/*vvvvvvvvvvvvvvvvvvvvvvvvvvv*/
struct aaa * sub_3EAA(register struct aaa * sa) {
    struct aaa * l1a;
    int		 l2;

#ifdef DEBUG
    printf("\tsub_3EAA(%x)\n", sa);
#endif

    if((l2 = dopetab[sa->a_c0] & 0xC) != 0)
      sa->a_l15.wi[0] = sub_3EAA(sa->a_l15.wi[0]);
    if(l2 == 8) sa->a_l15.wi[1] = sub_3EAA(sa->a_l15.wi[1]);
    if(sa->a_c0 == CONV) {
      if((sa->a_l15.wi[0])->a_c0 == FCONST) {
        if(sub_14F3(sa) == REG_F) {
          l1a = sa->a_l15.wi[0];
          l1a->a_i14 = sa->a_i14;
          sub_36E0(sa->a_l15.wi[1]);
          sub_36E0(sa);
          return l1a;
        }
      }
    }
m3: if((l2 == 0) || ((sa->a_l15.wi[0])->a_c0 != CONST))  return sa;
m6: if(sa->a_c0 == CONV) return sub_39CA(sa);
m7: if((l2 != 8) || ((sa->a_l15.wi[1])->a_c0 != CONST))  goto m8; 
    return sa;

m8:   if(sub_14F3(sa) == REG_L) {		/* m8:  */
        switch(sa->a_c0) {
          case MOD:
          case DIV:
          case RSHIFT: goto m14;
          case LT:
          case LEQ:
          case GT:
          case GEQ:    goto m12;
        }
      }
m10:  switch(sa->a_c0) {			/* m10: */
        case BNOT:    goto m23;
        case NOT:     goto m21;
        case MINUS_U: goto m19;
        case BAND:
        case LAND:
        case SUB:
        case BXOR:
        case BOR:
        case LOR:
        case ADD:
        case MUL:
        case DIV:
        case MOD:
        case RSHIFT:
        case LSHIFT:  goto m18;
        case NEQL:
        case LT:
        case LEQ:
        case EQL:
        case GT:
        case GEQ:     goto m17;
        default:      return sa; 
      }
/*    return sa; */

m12:word_B015 = "constant relational expression";	
    return sa;

m14:sub_3B65(&sa->a_l15.wi[0]->a_l15.ul, sa->a_l15.wi[1]->a_l15.l, sa->a_c0);
m15:if(l2 == 8) {
      sub_475C(sa->a_l15.wi[1]);
    }
    sub_3A79(sa, sa->a_l15.wi[0]);	/* m16: */
    sub_36E0(sa);
    return sa->a_l15.wi[0];

/* Two identical code fragments could be intended for different messages */

m17:word_B015 = "constant relational expression";	
    return sa;

m18:sub_3BC6(&sa->a_l15.wi[0]->a_l15.l, sa->a_l15.wi[1]->a_l15.l, sa->a_c0);
    goto m15;

m19:sa->a_l15.wi[0]->a_l15.l = (long)0 - sa->a_l15.wi[0]->a_l15.l;
    goto m15;

m21:sa->a_l15.wi[0]->a_l15.l = sa->a_l15.wi[0]->a_l15.l == 0 ?
    (long)1 : (long)0; /* minor differences in the generated code */
    goto m15;

m23:sa->a_l15.wi[0]->a_l15.l =
    (long)(-1) - sa->a_l15.wi[0]->a_l15.l; /* minor differences in the generated code */
    goto m15;
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#endif
/* End of file sub_3EAA.c  */


