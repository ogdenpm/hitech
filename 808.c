/*
 * File - sub_808.c Created 09.03.2019 Last Modified 17.06.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_808 OK+				 Used in: sub_B19
 *
 * Generated code is completely identical, except for
 * incomprehensible code inside function that does not
 * affect program logic
 *********************************************************/
int sub_808(register struct bbb * sb, struct aaa * p2a) {
    int		 l1;
    int		 l2;
    struct bbb * l3b;
    struct bbb * l4b;
    int	     	 l5;
    struct aaa * l6a;

#ifdef DEBUG
    printf("\tsub_808(%x, %x)\n", sb, p2a);
#endif

    l1 = 0;
    if(p2a->a_c0 != COLON_U) goto m12;
    sub_475C(p2a);
    l5 = 0;
    if(sb->b_class == SDECL) {
      l3b = sb;
      while((p2a = sub_4192())->a_c0 != DOT_DOT) {	/* m7:  */
        /* assigning to "struct bbb *" from "int"          v	*/
        if((l2 = sub_1CC4((l4b = *(l3b->b_memb + (l5++) + 1)))) != 0) { /* m1:  */
          if(l1%(++l2) != 0) {
            l2 = l2 - l1%l2;
            l1 = l1 + l2;
            sub_CDF(l2); /* Emit "defb 0, ..." (l2 bytes) */
          }
        }
        if((l4b->b_c3 & 0x10) != 0) {			/* m2:  */
          p2a = sub_43EF(BAND, p2a, sub_415E(((long)1<<(l4b->b_i5))+(long)(-1)));
          if(HI_CHAR(l4b->b_i5) != 0) {
            /* At this point in file CGEN.COM there is a small	*/
            /* fragment directly unused code 5 bytes long	*/
            l6a = sub_43EF(BOR, l6a, sub_43EF(LSHIFT, p2a, sub_415E(0)));
          } else {
            l6a = p2a;					/* m3: */
          }
          if(l5 != *(l3b->b_memb)) {			/* m4:  */
            if((char)(((struct bbb *)*(l5 + l3b->b_memb + 1))->b_c3 & 0x10) != 0) {	/* cast to "struct bbb *" from smaller integer type "int" */
              if(((struct bbb *)*(l5 + l3b->b_memb + 1))->b_i11 == l4b->b_i11) continue;	/* cast to "struct bbb *" from smaller integer type "int" */
            }
          }
          p2a = l6a;
        }						/* m5:  */
        l1 += sub_808(l4b, p2a);			/* m6:  */
      }
m8:   sub_475C(p2a);
    } else {
      l3b = sb->b_type;					/* m9:  */
      for(;;) {
        for(;;) {
          p2a = sub_4192();				/* m10: */
          if(p2a->a_c0 != COLON_U) break;
          l1 += sub_808(l3b, p2a);
        }
        if(p2a->a_c0 == DOT_DOT) goto m8;		/* m11: */
        l1 += nodesize(p2a);
        sub_2BD0(sub_600E(sub_43EF(ATGIGN, p2a, 0)));
      }
m12:  p2a = sub_600E(sub_43EF(ATGIGN, p2a, 0));		/* m12: */
      l1  = nodesize(p2a);
      sub_2BD0(p2a);
    }
    if(l1 < sb->b_size) {				/* m13: */
      sub_CDF(sb->b_size - l1);
      l1 = sb->b_size;
    } else {
      if((sb->b_size < l1) && (sb->b_size != 0))	/* m14: */
        uerror("Too many initializers");
    }
#ifdef DEBUG
    printf("\tsub_808 Return %x\n", l1);
#endif
    return l1;						/* m15: */
}

/* End of file - sub_808.c  */


