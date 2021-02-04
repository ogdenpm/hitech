/*
 * File - sub_19C1.c Created 09.03.2019 Last Modified 17.06.2020
 */

#include "stdio.h"
#include <stdlib.h>
#include "cgen.h"

/*********************************************************
 * sub_19C1 OK++	       Used in: sub_6D1, sub_4192
 *********************************************************/
void sub_19C1(int p1) { 
    int			  l1;
    struct bbb		* l2b;
    int			* l3;
    struct aaa		* l4a;
    char		* l5;
    int			  arr[258];
    register struct bbb * sb;

#ifdef DEBUG
    printf("\tsub_19C1(%d)\n", p1);
#endif

    l2b = sub_1754(sub_306(), p1);
    l3  = arr;
    *l3 = 0;
    for(;;) {
      l5 = sub_306();
      if(*l5 == ']') break;
      sb = (struct bbb *)allocmem(sizeof(struct bbb)); /* Create struct bbb */
      sb->b_class = MEMBER;
      if(*l5 == ':') {
        LO_CHAR(sb->b_i5) = atoi(l5+1);
	bitset(sb->b_c3, 4);
	l5 = sub_306();
      }
      sb->b_type = sub_627(l5, &sb->b_refl);
      l4a	 = sub_600E(sub_4192());
      if(l4a->a_c0 != CONST) faterror("Strucdecl - bad\tnelem");
      sb->b_nelem  = l4a->a_l15.ii[0];
      sub_475C(l4a);
      sb->b_size  = sub_1C8E(sb);
      *(((++(*l3))-1) + l3 +1) = sb;	/* assigning to "int" from "struct bbb *" */
/*
      ++membcnt;
*/
    }
    l1 = (0xffff + (unsigned)*l3)*2 + 4;
    l3 = allocmem(l1);			/* create ??? */
    movmem(arr, l3, l1);
    l2b->b_memb = l3;
    sub_1CEF(l2b);
}

/*********************************************************
 * sub_1B0C OK++		Used in: sub_6D1, sub_4192
 *
 * In original executable file CGEN stack recovery code is
 * missing when returning from sub_76F function
 *********************************************************/
void sub_1B0C(void) {
    struct aaa		* l1a;
    int			* l2;
    int			  l3;
    int			  l4;			
    int			* l5;
    int			  arr[258];
    register struct bbb * sb;

#ifdef DEBUG
    printf("\tsub_1B0C()\n");
#endif

    l3  = MININT;		/* arithmetic overflow in constant expression */
    l4  = MAXINT;
    sb  = sub_1754(sub_306(), EDECL);
    l2  = arr;
    *l2 = 0;
    for(;;) {
      l1a = sub_4192();
      if(l1a->a_c0 == DOT_DOT) {
	sub_475C(l1a);
	l5 = ((*l2) - 1)*2 + 4;	/* assigning to "int *" from "int" */
	l2 = allocmem(l5);	/* passing "int *" to parameter type "int" */	/* create ??? */
	movmem(arr, l2, l5);
	sb->b_memb = l2;	/*	 In file CGEN.COM stack	recovery */
	sub_15FB(sb, l4, l3);	/*	 failed when returning from	 */
	sub_76F(']');		/* <---- function sub_76F 		 */
	return;
      }
      l1a = sub_600E(l1a);

      *(((++(*l2))-1) + l2 +1) = l1a->a_l15.ii[0];
	  
      if(    (long)l3 < l1a->a_l15.l) l3 = l1a->a_l15.ii[0];
      if(l1a->a_l15.l < (long)l4)     l4 = l1a->a_l15.ii[0];
      sub_475C(l1a);
    }
}

/* End of file sub_19C1.c  */


