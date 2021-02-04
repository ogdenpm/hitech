/*
 * File - sub_283E.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include <ctype.h>
#include "cgen.h"

/*********************************************************
 * sub_283E OK+				 Used in: sub_2B2A
 *
 * Restored source code did not allow optimizer to reduce
 * number of sub_2B2A function calls to one.
 *
 * The switch statement, in comparison with if, more clearly
 * reflects the structure of the program, however, fragments
 * of the generated assembler code are arranged in an order
 * different from the original.
 *********************************************************/
 int sub_283E(register struct aaa * sa, int par) {
    char	* l1;
    struct zzz 	* l2z;
    struct aaa 	* l3a;
    char	* l4;
    char	  l5;
    int		  l6;
    int		  l7;

#ifdef DEBUG
    printf("\tsub_283E(%x, %x)\n", sa, par);
#endif

    l2z = &array_80EF[*(par + (uchar*)&sa->a_c3)];
    l7  = 0;
    l1  = l2z->p_8;
m1: if(*(l1) == 0) return l7 & word_B017;
    switch (l5 = *(l1++)) {
      case 'A':
      case 'B':
      case 'C':
      case 'F':
      case 'M':
      case 'O':
      case 'P':
      case 'Q':
      case 'S':
      case 'T':
      case 'V':
      case 'W':
      case 'Z':
        for(;;l1++) {						/* m23: */
          if(*l1 == 0)   goto m1;				/* m24: */
          if(*l1 == 'N') goto m1;
          if(*l1 == 'L') goto m1;
          if(*l1 == 'R') goto m1;						
        }
      case 'D':
      case 'U':
        goto  m1;
      case 'X':
      case 'G':
        if(isdigit(*l1) != 0) {					/* m4:	*/
          l4 = l1;
          while(isdigit(*l1) != 0) {l1++;};
        } else {
          l4 = 0;						/* m7:  */
        }
        switch (*(l1++)) {					/* m8:	*/
          case 'L':
            if(0 < par) {					/* m11: */
              l3a = sa;
              l6  = par-1;
              break;
            }
            l6 = *((uchar*)(l3a = sa->a_l15.wi[0])+1)-1;	/* m14: */
            break;
          case 'N':
            l6  = par;						/* m10: */
            l3a = sa;
            break;
          case '~':
            l6 = *((uchar*)(l3a = sa->a_l15.wi[1])+1)-1;	/* m15: */
            break;
        }
        if(l5 == 'S') {						/* m9: */
          if(l3a->a_c0 == USEREG) {
            l5 = l3a->a_l15.bc[0];
          } else {
            l5 = 0;						/* m16: */
          }
        } else {
          l5 = (l5 == 'G') ?					/* m17: */
          *(l6 + (uchar *)&l3a->a_i9) :
          *(l6 + (uchar *)&l3a->a_i6);
          if(l4 != 0) {
            while (isdigit(*((char *)par)) != 0) {	/* cast to "char *" from smaller integer type "int" */
              l5 = array_AB24[(uchar)l5*2 +((-48) + *(l4++))];
            }
          }
        }
        l7 |= array_AAE8[(uchar)l5];				/* m22: */
        if(l5 != 0) byte_AFFA = l5;
        goto m1;
      case 'L':
        l7 |= (0 >= par) ?					/* m27: */
        sub_2B2A(sa->a_l15.wi[0]) :
        sub_283E(sa, par-1);
        goto m1;
      case 'R':
        l7 |= sub_2B2A(sa->a_l15.wi[1]);			/* m31: */
        goto m1;
      case '~':
        for(;;l1++) {						/* m25: */
          if(*l1 == 0)   goto m1;				/* m26: */
          if(*l1 == 'L') goto m1;
          if(*l1 == 'R') goto m1;
        }
    }
    goto m1;
}

/* End of file sub_283E.c  */


