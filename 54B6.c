/*
 * File - sub_54B6.c Created 09.03.2019 Last Modified 31.05.2020
 */

#include "stdio.h"
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include "cgen.h"

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_54B6 - optim: Out of memory	Used in: sub_600E
 *********************************************************/
struct aaa * sub_54B6(register struct aaa * sa) {
    struct aaa  * l1a;
    struct aaa  * l2a;
    int		  l3;
    unsigned long l4;

#ifdef DEBUG
    printf("\tsub_54B6(%x)\n", sa);
#endif

    l3 = dopetab[sa->a_c0] & 0xC;
    if(l3 != 0) {
      sa->a_l15.wi[0] = sub_54B6(sa->a_l15.wi[0]);
    }
    if(l3 == 8) sa->a_l15.wi[1] = sub_54B6(sa->a_l15.wi[1]);		/* m1: */
    if((dopetab[sa->a_c0] & 0x40) != 0) {				/* m2: */
      if(sub_4C12(sa->a_l15.wi[0]) < sub_4C12(sa->a_l15.wi[1])) {
	byte_B013       = 1;
	l1a             = sa->a_l15.wi[0];
	sa->a_l15.wi[0] = sa->a_l15.wi[1];
	sa->a_l15.wi[1] = l1a;
      }
      if((dopetab[sa->a_c0] & 0x2000) != 0) { 				/* m3: */
	if(sa->a_c0 == sa->a_l15.wi[0]->a_c0) {
	  if(sub_4B89(sa->a_l15.wi[1]) != 0) {
	    if(sub_4B89((l1a = sa->a_l15.wi[0])->a_l15.wi[1]) != 0) {
	      byte_B013        = 1;
	      sa->a_l15.wi[0]  = l1a->a_l15.wi[1];
	      l1a->a_l15.wi[1] = sa;
	      sa               = l1a;
	      goto m5;
	    }
          }
          if(sub_4C12(sa->a_l15.wi[0]->a_l15.wi[1]) < sub_4C12(sa->a_l15.wi[1])) { /* m4: */
	    byte_B013       = 1;
	    l1a             = sa->a_l15.wi[1];
	    sa->a_l15.wi[1] = sa->a_l15.wi[0]->a_l15.wi[1];
	    sa->a_l15.wi[0]->a_l15.wi[1] = l1a;
	  }
	}
      }
    }
m5: if((dopetab[sa->a_c0] & 0xC00) == 0x800) {
      if(sa->a_l15.wi[0]->a_c0 == CONV) {
        if(nodesize(sa->a_l15.wi[0]->a_l15.wi[0]) < nodesize(sa)) {
          if(sub_60A8(sa->a_l15.wi[1], sa->a_l15.wi[0]->a_l15.wi[0]) != 0) {
            l2a                    = sa->a_l15.wi[0];
            sa->a_l15.wi[0]        = l2a->a_l15.wi[0];
            sa->a_i14              = sa->a_l15.wi[0]->a_i14;
            sa->a_i12              = sa->a_l15.wi[0]->a_i12;
            sa->a_l15.wi[1]->a_i14 = sa->a_i14;
            sa->a_l15.wi[1]->a_i12 = sa->a_i12;
            l2a->a_l15.wi[0]       = sa;
            sa = l2a;
          }
        }
      }
    }
    if((dopetab[sa->a_c0] & 0x420) == 0x420) {				/* m6: */
      l1a = sa->a_l15.wi[0];
      if(sa->a_l15.wi[0]->a_c0 == CONV) {
        if(nodesize(l1a->a_l15.wi[0]) != 0) {
          if(nodesize(l1a->a_l15.wi[0]) < nodesize(l1a)) {
            if(sa->a_l15.wi[1]->a_c0 == CONST) {
              if((sub_14F3(l1a) == REG_A) || (sub_14F3(l1a->a_l15.wi[0]) == REG_L)) {
                if(sub_62BE(sa->a_l15.wi[0], sa->a_l15.wi[1]) != 0) {	/* m7: */
                  sub_36E0(sa->a_l15.wi[0]);
                  sub_36E0(sa->a_l15.wi[0]->a_l15.wi[1]);
                  sa->a_l15.wi[0]        = sa->a_l15.wi[0]->a_l15.wi[0];
                  sa->a_l15.wi[1]->a_i14 = sa->a_l15.wi[0]->a_i14;
                  sa->a_l15.wi[1]->a_i12 = sa->a_l15.wi[0]->a_i12;
                  goto m10;
                }
                word_B015 =  "mismatched comparision";			/* m8: */
                goto m10;
              }
            }
            if(sa->a_l15.wi[1]->a_c0 == CONV) {				/* m9: */
              if(sub_6246(sa->a_l15.wi[0]->a_l15.wi[0], sa->a_l15.wi[1]->a_l15.wi[0]) != 0) {
                l1a             = sa->a_l15.wi[0];
                sa->a_l15.wi[0] = l1a->a_l15.wi[0];
                sub_36E0(l1a->a_l15.wi[1]);
                sub_36E0(l1a);
                l1a             = sa->a_l15.wi[1];
                sa->a_l15.wi[1] = l1a->a_l15.wi[0];
                sub_36E0(l1a->a_l15.wi[1]);
                sub_36E0(l1a);
              }
            }
          }
        }
      }
    }	/* Ok */
m10:switch(sa->a_c0) {
      case NOT:
	return sub_4C8B(sa); /* goto m11; */				/* m13 */
      case GADDR:
	if(sa->a_l15.wi[0]->a_c0 != MUL_U) return sa;			/* m47 */
m48:    return sub_53EE(sa); /* goto m11; */
      case MUL:
      case DIV:
      case ASMUL:
      case ASDIV:
        if(sa->a_l15.wi[1]->a_c0 == CONST) {				/* m34 */
          if(sa->a_l15.wi[1]->a_l15.l == 1) goto m30;
        }
      case MOD:
      case ASMOD:
        if(sa->a_l15.wi[1]->a_c0 == CONST) {				/* m35 */
          if(sub_46F7(sa->a_l15.wi[1]->a_l15.l) != 0) {
            return sub_4FCE(sa); /* goto m11; */
          }
        }
      case BAND:
      case ASAND:
        if(sa->a_l15.wi[1]->a_c0 != CONST) goto m41;			/* m36 */
        if(sa->a_l15.wi[1]->a_l15.l != 0)  goto m41;
        switch(sa->a_c0) {
          case MOD:
          case DIV:
          case ASMOD:
	    warning("Division by zero");
	    return sa; /* goto m18; */
          case BAND:
          case MUL:
            sub_475C(sa->a_l15.wi[0]);
            sub_475C(sa->a_l15.wi[1]);
            sa->a_c0    = CONST;
            sa->a_l15.l = 0;
            return sa; /* goto m18; */
          case ASAND:
          case ASMUL:
            sa->a_c0 = ASSIGN;
            return sa; /* goto m18; */
          case ASDIV:
m41:        l4 = (nodesize(sa) >= 4) ? (long)(-1) : ((long)1<<(nodesize(sa)*8)) + 0xffffffff;
            if(sa->a_c0 != BAND) {
              if(sa->a_c0 != ASAND) return sa;	/* goto m18; */
            }
            if(sa->a_l15.wi[1]->a_c0 != CONST) return sa;		/* m44: */
            if(l4 != (sa->a_l15.wi[1]->a_l15.l & l4)) return sa;
            goto m30;
	}
      case CONV:
        return sub_508A(sa);						/* m45 */
        /* goto m11; */
      case MUL_U:
        if(sa->a_l15.wi[0]->a_c0 != GADDR) return sa;			/* m49 */
        switch((l1a = sa->a_l15.wi[0]->a_l15.wi[0])->a_c0) {
          case LPAREN:
          case ASSIGN:
          case QUEST:
            return sa; /* goto m18; */
        }
        goto m48;
      case PLUS_U:
        sub_36E0(sa);							/* m46 */
        sa = sa->a_l15.wi[0];
        return sa; /* goto m18; */
      case DOT:
        return sub_4E8D(sa);	/* goto m11; */				/* m12 */
      case LT:
      case GEQ:
        if(sub_14F3(sa->a_l15.wi[0]) == REG_L) {			/* m14 */
          if(sub_4BE5(sa->a_l15.wi[0]) != 0) {
            word_B015 = "degenerate unsigned comparision";
            sub_475C(sa);
            sa = sub_415E((sa->a_c0 == GEQ) ? (long)1 : (long)0);
          }
        }
        return sa;	/* goto m18: */
      case LEQ:
      case GT:
        if(sub_14F3(sa->a_l15.wi[0]) == REG_L) {			/* m19: */
          if(sub_4BE5(sa->a_l15.wi[1]) != 0) {
            sa->a_c0 = (sa->a_c0 == GT) ? (char)NEQL : (char)EQL;
            return sa; /* goto m18; */
          }
        }
        if(sa->a_c0 == CONST) {						/* m23: */
          sa->a_l15.wi[1]->a_l15.l += 1;
          sa->a_c0 = (sa->a_c0 == GT) ? (char)GEQ : (char)LT;
        } else {
          l1a             = sa->a_l15.wi[0];				/* m25: */
          sa->a_l15.wi[0] = sa->a_l15.wi[1];
          sa->a_l15.wi[1] = l1a;
          sa->a_c0        = (sa->a_c0 != GT) ? (char)GEQ : (char)LT;
        }
        return sa; /* goto m18; */
      case ASEOR:
      case BOR:
        if(sa->a_l15.wi[1]->a_c0 == CONST) {				/* m27 */
          if(sa->a_l15.wi[1]->a_l15.l == (-1)) {
            sub_475C(sa->a_l15.wi[0]);
            sub_36E0(sa);
            return sa->a_l15.wi[1];
          }
        }
      case ADD:
      case SUB:
      case LSHIFT:
      case ASADD:
      case ASSUB:
      case ASLSHIFT:
      case ASRSHIFT:
      case RSHIFT:
        if(sa->a_l15.wi[1]->a_c0 == CONST) {				/* m28: */
          if(sa->a_l15.wi[1]->a_l15.l == 0) {
m30:        return sub_4FA8(sa); /* goto m11; */
          }
        }
        if((dopetab[sa->a_c0] & 0x80) != 0) {				/* m31: */
          if(nodesize(sa->a_l15.wi[1]) != 1) {
            l1a = sub_3712();
/*          asdf = 1;	*/
            *((sub_14F3(sa->a_l15.wi[1]) == REG_L) ?
            (int*)word_AE53 :		/* Pointers "int*" are not  */	/* uchar  */
            (int*)word_AED9) =		/* true, but generated code */ 	/* char   */
            &(l1a->a_i14);		/* is logically correct     */
            l1a->a_c0 = TYPEOP;
            sa->a_l15.wi[1] = sub_43EF(CONV, sa->a_l15.wi[1], l1a);
          }
        }
        return sa; /* goto m18; */
    }
    if(sa->a_c0 != IDOP) return sa; /* goto m18; */
    return sub_4DA3(sa);
}

/* End of file sub_54B6.c  */


