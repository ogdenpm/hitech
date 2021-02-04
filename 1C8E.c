/*
 * File - sub_1C8E.c  Created 09.03.2019 Last Modified 17.06.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_1C8E OK++   Used in: sub_B19, sub_17E0, sub_19C1
 *********************************************************/
int sub_1C8E(register struct bbb * sb) {

#ifdef DEBUG
    printf("\tsub_1C8E(%x)\n", sb);
#endif

    if((sb->b_refl & 0x1) != 0) return sb->b_nelem*2;
    return sb->b_type->b_size*(sb->b_nelem);
}

/*********************************************************
 * sub_1CC4 OK++	       Used in: sub_808, sub_1CEF
 *********************************************************/
int sub_1CC4(register struct bbb * sb) {

#ifdef DEBUG
    printf("\tsub_1CC4(%x)\n", sb);
#endif

    if(sb->b_refl != 0) return 0;
    return sb->b_type->b_i11;
}

/*********************************************************
 * sub_1CEF OK++			Used in: sub_19C1
 *********************************************************/
void sub_1CEF(register struct bbb * sb) {
    int		 l1;
    int		 l2;
    int		 l3;
    struct bbb * l4b;

#ifdef DEBUG
    printf("\tsub_1CEF(%x)\n", sb);
#endif

    l1 = 0;
    l2 = l3 = 0;
    while (l2 != *sb->b_memb) { 			/* m9: */
      l4b = *(sb->b_memb + l2 + 1);			/* m1: */ /* assigning to "struct bbb *" from "int"*/
      if(sb->b_class == UDECL) {
	l1 = sub_1659(l1, l4b->b_size);	/* return max number */
	l4b->b_i11 = 0;
	goto m8;
      }
      l1 = l4b->b_i11 = sub_1C6D(l1, sub_1CC4(l4b));	/* m2: */
      if((l4b->b_c3 & 0x10) != 0) {
	if((0x10 < (l3 + (uchar)LO_CHAR(l4b->b_i5)))
	|| (LO_CHAR(l4b->b_i5) == 0)) {
	  if(l3 != 0) {					/* m3: */
	    l4b->b_i11 = (l1 += 2);
	  }
	  l3 = 0;					/* m4: */
	}
        HI_CHAR(l4b->b_i5) = LO_CHAR(l3);		/* m5: */
        l3 += (uchar)LO_CHAR(l4b->b_i5);
        if(l3 != ' ') goto m8;
        l3 = 0;
        l1 += 2;
        goto m8;
      }
      if(l3 != 0) {					/* m6: */
	l3 = 0;
	l4b->b_i11 = (l1 += 2);
      }
      l1 += l4b->b_size;				/* m7: */
m8:   l2++;
    }
    if(l3 != 0) {
      l3 = 0;
      l1 += 2;
    }
    sb->b_size  = sub_1C6D(l1, 0);			/* m10: */
    sb->b_i11   = 0;
    sb->b_class = SDECL;
}

/*********************************************************
 * sub_1EDF OK++			Used in: sub_2BD0
 *********************************************************/
void sub_1EDF(void) {
  struct bbb   	     ** l1b;
  register struct bbb * sb;

#ifdef DEBUG
  printf("\tsub_1EDF()\n");
#endif
	
  l1b = hashtab;
  do {
    sb = *l1b;
    while ((sb != 0) && ((uchar)sb->b_ndpth == nstdpth)) {
      if(sb->b_class == DECL9) {
	if(sb->b_c13 == 2) {
	  if((sb->b_c3 & 4) != 0) sub_14D3(sb); /* Assigning register "IY" value formal parameter with type register */
	}
      }
     sb = sb->b_next;
    }
  } while (++l1b != &word_AFE9);	/* variable */
}

/* End of file sub_1C6D.c  */


