/*
 * File - sub_43EF.c Created 09.03.2019 Last Modified 17.06.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_43EF OK+      Used in: sub_793,  sub_808,  sub_E43,
 *                            sub_4192, sub_4C8B, sub_4DA3,
 *                            sub_4E8D, sub_508A, sub_54B6,
 *                            sub_5DF6
 *
 * Generated code is completely identical, except for
 * location of code of branches of "switch" operator.
 *********************************************************/
struct aaa * sub_43EF(int p1, struct aaa * p2a, struct aaa * p3a) {
    struct bbb 		* l1b;
    long		  l2;
    register struct aaa * sa;

#ifdef DEBUG
    printf("\tsub_43EF(%d, %x, %x)\n", p1, p2a, p3a);
#endif

    sa              = sub_3712();
    sa->a_c0        = (char)p1;
    sa->a_l15.wi[0] = p2a;
    sa->a_l15.wi[1] = p3a;
    switch(dopetab[sa->a_c0] & 0x30) {
      case 0x10:
        sa->a_i14 = word_AE11;			/* long	  */
        break;

      case 0x20:
        sa->a_i14 = word_AF1B;			/* b	  */
        break;

      case 0x30:
        sa->a_i14 = word_AFE9;			/* variable */
        break;

      default:
        sa->a_i14 = p2a->a_i14;
        sa->a_i12 = p2a->a_i12;
    }
    switch(sa->a_c0) {
      case HASHSIGN:
        if(sa->a_l15.wi[0]->a_c0 == IDOP)
          l2 = (unsigned)sa->a_l15.wi[0]->a_l15.wi[0]->a_i6;
        else
          l2 = (unsigned)nodesize(sa->a_l15.wi[0]); /* ?? */
        if(l2 == 0) warning("Sizeof yields 0");
        sub_475C(sa->a_l15.wi[0]);
        sa->a_c0    = CONST;
        sa->a_i14   = word_AE11;		/* long	  */
        sa->a_i12   = 0;
        sa->a_l15.l = l2;
        break;

      case GADDR:
        if(sa->a_i12 == 0) {
          if(1 < (unsigned)sa->a_i14->b_nelem) {
            sa->a_i12 = sa->a_i14->b_refl;
            sa->a_i14 = sa->a_i14->b_type;
          }
        }
        sub_385B(sa);
        break;

      case LPAREN:
      case MUL_U:
        sub_37ED(sa);
        break;

      case DOT:
        if(p2a->a_c0 == TYPEOP) {	/* m9: */
          l1b = p2a->a_i14;
          sub_36E0(sa);
          sub_36E0(p2a);
          sa           = p3a;
          sa->a_i14    = l1b;
          p3a->a_l15.l = *((int)sa->a_l15.wi[0] + l1b->b_memb + 1);
          break;
        }
        l1b = *(p3a->a_l15.ii[0] + sa->a_i14->b_memb + 1);	/* assigning to "struct aaa *" from "int" */
        sa->a_i14    = l1b->b_type;
        sa->a_i12    = l1b->b_refl;
        p3a->a_l15.l = l1b->b_i11;
        p3a->a_i14   = word_AF1D;		/* x      */
        if((l1b->b_c3 & 0x10) == 0) break;
        p2a              = sub_3712();
        *p2a             = *sa;
        p2a->a_l15.wi[0] = sa;
        sa               = p2a;
        sa->a_c0         = BFIELD;
        sa->a_l15.vi[1]  = l1b;
        break;

      case COLON_S:
        sa->a_i14 = word_AED9;			/* char   */
        sa->a_i12 = 1;
        break;

      case CONV:
      case SCOLON:
      case QUEST:
        sa->a_i14 = sa->a_l15.wi[1]->a_i14;
        sa->a_i12 = sa->a_l15.wi[1]->a_i12;
        break;
    }
#ifdef DEBUG
    printf("\tsub_43EF\t\tReturn %x\n", sa);
#endif
    return sa;
}

/* End of file sub_43EF.c  */


