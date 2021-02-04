/*
 * File - sub_17E0.c Created 09.03.2019 Last Modified 17.06.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_17E0 OK+			Used in: sub_6D1, sub_4192
 *
 * Compiler generates identical code from restored source
 * program in C, however, location of branches associated
 * with case constants is different from original.
 * This does not affect the function.
 *********************************************************/
void sub_17E0(void) {
    struct aaa          * l1a;
    int                   l2;
    register struct bbb * sb;

#ifdef DEBUG
    printf("\tsub_17E0()\n");
#endif

    sb         = sub_1754(sub_306(), DECL9);
    sb->b_type = sub_627(sub_306(), &sb->b_refl);
    l1a        = sub_600E(sub_4192());
    if(l1a->a_c0 != CONST)
      faterror("Bad element count expr");
    sb->b_nelem = l1a->a_l15.ii[0]; /* ??? */
    sub_475C(l1a);
    l2 = *sub_306();
    sub_76F(']');

#ifdef DEBUG
    printf("\tsub_17E0\t\tl2=%c\n", l2);
#endif

    switch (l2) {
      case 'A':		/* auto		*/
      case 'a':	  
        sb->b_c13 = 1;
        break;
      case 'E':		/* extern	*/
      case 'e':
        sb->b_c13 = 3;
        break;
      case 'R':		/* register	*/
      case 'r':
        sb->b_c3 |= 8;
      case 'P':		/* pointer	*/
      case 'p':
        sb->b_c13 = 5;
        break;
      case 'S':		/* static 	*/
      case 's':
        sb->b_c13 = 4;
        break;
      case 'T':		/* typedef	*/
      case 't':
        sb->b_class = TDECL;
        if(sb->b_refl != 0) {
          sb->b_i11 = 0;
          sb->b_c13 = 2;
        } else {
          sb->b_i11 = sb->b_type->b_i11;
          sb->b_c13 = sb->b_type->b_c13;
        }
        if(sb->b_nelem != 1) {
          sb->b_c13 = 0;
        }
        break;
      default:
        faterror("Bad storage class");
    }
    sb->b_size = sub_1C8E(sb);
    if(sb->b_class != TDECL) {
      if((sb->b_refl         == 0) &&
         (sb->b_size         == 0) &&
         (sb->b_type->b_size == 0)) {
	uerror("Bad dimensions");
      }
      switch (sb->b_c13) {
	case 1:
	case 5:
	  sub_5CF5(sb, l2);
	  break;
	default:
	  sb->b_i11 = sub_174C(); /* word_AE0F++ */
      }
      if((sb->b_refl & 0x2) != 0) {
	if(sb->b_nelem != 0) {
	  if(++lvlidx == MAXFUN) {
	    faterror("Functions nested too deep");
	  }
	  array_AE57[lvlidx] = nstdpth; /* Save current nesting depth */
	  array_AE97[lvlidx] = 6;
	  array_AE13[lvlidx] = 0;
	  array_AEDB[lvlidx] = sb;
	}
      }
    }
#ifdef DEBUG
    printf("\tsub_17E0\t\t Exit\n");
#endif
}

/* End of file sub_17E0.c  */


