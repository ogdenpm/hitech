/*
 * File - ssub_4192.c Created 09.03.2019 Last Modified 17.06.2020
 */

#include "stdio.h"
#include <ctype.h>
#include <string.h>
#include "cgen.h"
#include <stdlib.h> 

/*********************************************************
 * sub_4192 OK+     Used in: sub_6D1,  sub_793,  sub_808,
 *			     sub_B19,  sub_E43,  sub_17E0,
 *			     sub_19C1, sub_1B0C 
 *
 * Generated code is completely identical to binary image
 * executable file, with exception location some branches
 * switch statements
 *********************************************************/
struct aaa * sub_4192(void) {
    struct aaa          * l1a;
    char	        * l2;
    int 	 	  l3;
    int			  l4;
    register struct aaa * sa;

#ifdef DEBUG
    printf("\tsub_4192()\n");
#endif

m1: l2 = sub_306();
    if(isdigit(*l2) != 0) goto m2;
    if((*l2 != '-') || (isdigit(*(l2+1)) == 0)) goto m7;
m2: if(*l2 == '-') {
      l4 = 1;
      l2++;
    } else {
      l4 = 0;						/* m4:  */
    }

#ifdef DEBUG
    printf("\tsub_4192\t\tatol(\"%s\") = %ld l4 = %d\n", l2, atol(l2), l4);
#endif

    sa = sub_415E(atol(l2));
    if(l4 != 0) sa->a_l15.l = 0 - sa->a_l15.l;
m5: 
#ifdef DEBUG
    printf("\tsub_4192\t\tReturn %x\n", sa);
#endif
    return sa;

m7: if((*l2 == '_') || (isalpha(*l2) != 0)) {		/* m7:  */
      (sa = sub_3712())->a_c0 = IDOP;			/* m8:  */
      sa->a_l15.vi[0]         = sub_265(l2);
      sa->a_i14               = sa->a_l15.vi[0]->b_type;
      sa->a_i12               = sa->a_l15.vi[0]->b_refl;
      if(sa->a_l15.vi[0]->b_c13 != 3) goto m5;
      if(((sa->a_l15.vi[0]->b_c3) & 2) != 0) goto m5;
      sub_C36(sa->a_l15.vi[0]);				/* Emit "global name" */
      goto m5;
    }
    if(*l2 == '`') {					/* m9:  */
      sa        = sub_3712();			
      sa->a_i14 = sub_627(l2, &sa->a_i12);
      sa->a_c0  = TYPEOP;
      goto m5;
    }
    if(*l2 == '.') {					/* m10: */
      if(*(l2+1) != 0) {
        if(*(l2+1) != '.') {
          sa              = sub_3712();
          sa->a_i14       = word_AED7;			/* "d" - double */
          sa->a_l15.ci[0] = (char*)allocmem(strlen(l2)); /* create string */
          strcpy(sa->a_l15.ci[0], l2+1);
          sa->a_l15.ii[1] = sub_174C();			/* word_AE0F++ */
          sa->a_c0        = FCONST;
          goto m5;
        }
      }
    }
    l4 = sub_1B2(l2);	/* Token search */		/* m12: */
    l3 = dopetab[l4] & 0xC;
    switch(l3) {
      case 0xC:				/* parsing operations	    */
        switch(l4) {
          case '4':
            sub_1B0C();
            goto m1;
          case '7':
          case '8':
            sub_19C1(l4);
            goto m1;
          case '9':
            sub_17E0();
            goto m1;
        }
        faterror("Expression error");
      case 0:				/*  			    */
        return sub_43EF(l4, 0, 0);
      case 4:				/*  			    */
        return sub_43EF(l4, sub_4192(), 0);
      case 8:				/* computational operations */
        l1a = sub_4192();
        return sub_43EF(l4, l1a, sub_4192());
    }
    goto m1;
}

/* End of file sub_4192.c  */


