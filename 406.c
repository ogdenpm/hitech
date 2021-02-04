/*
 * File - sub_406.c Created 09.03.2019 Last Modified 09.12.2020
 */

#include "stdio.h"
#include <ctype.h>
#include "cgen.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern int	    empty;

/*********************************************************
 * sub_406 v3 OK++			 Used in: sub_6D1
 *
 * Note:
 *   Added "empty" parameter to sub_5CF5 function call to
 *   match number and types actual and formal parameters
 *   this function.
 *   sub_5CF5 function is called only if value sb->b_c13
 *   is 3 or 4. if this condition is met, variable "empty"
 *   in sub_5CF5 function is not used.
 *********************************************************/
void sub_406() {
  struct bbb	     ** l1b;
  int			l2;
  struct bbb	      * l3b;
  struct bbb	      * l4b;
  struct ptr	      * l5;
  int			l6;
  register struct bbb * sb;

#ifdef DEBUG
  printf("\tsub_406()\n");
#endif

  l2  = ARRAY_SIZE(hashtab);
  l1b = hashtab;
  do {
    l3b = 0;							/* m1: 	*/
    sb  = *l1b;
    while((sb != 0) && ((uchar)sb->b_ndpth == nstdpth)) {
      if(sb->b_class == DECL9) {	/* '9' */		/* m3: 	*/
	if(sb->b_c13 == 2)
	  word_B017 |= array_AAE8[(int)sb->b_memb];		/* m4: 	*/
	if((sb->b_c13 == 4) || (sb->b_c13 == 3))
	  sub_5CF5(sb, empty); /* Add parameter "empty"! */	/* m12: */
	if(0 < nstdpth) {					/* m6: 	*/
	  if(sb->b_c13 == 3) {
	    l4b        = sb->b_next;
	    sb->b_next = l3b;
	    l3b        = sb;
	    (sb->b_ndpth)--;
	    sb         = l4b;
	    continue;
	  }
	}
      }

      sub_7028(((struct ptr *)sb)->next_ptr);	 		/* m7:	*/

      if((sb->b_class == UDECL) || (sb->b_class == SDECL)) {
	l6 = *(sb->b_memb);					/* m8:  */

	l5 = (struct ptr *)(sb->b_memb + 1);

	while(l6-- != 0)					/* m10: */
	  sub_7028((l5++)->next_ptr);
	
	sub_7028((struct ptr *)sb->b_memb);
      }
      sub_7028((struct ptr *)sb);				/* m11: */
      sb = sb->b_next;
    }
    if(l3b != 0) {						/* m13: */
      *(l1b++) = l3b;
      while(l3b->b_next != 0) {					/* m15: */
        l3b = l3b->b_next;					/* m14: */
      }
      l3b->b_next = sb;
    } else {
      *(l1b++)  = sb;						/* m16: */
    }
  } while((--l2) != 0);						/* m17: */

  nstdpth--;
  if(lvlidx >= 0) {
    if(array_AE57[lvlidx] == nstdpth) {
      sb = array_AEDB[lvlidx];
      if(sb->b_type->b_class == SDECL) {
	if((sb->b_refl & 4) == 0) {
	  sub_BEE(sb->b_i11, sb->b_size);
	}
      }
      sub_BCC(sb->b_i11, array_AE13[lvlidx]);			/* m18: */
      lvlidx--;
      word_B017 = 0x17F;
    }
  }
#ifdef DEBUG
  printf("\tsub_406 Exit\n");
#endif

}

/*********************************************************
 * sub_627 OK++     Used in: sub_17E0, sub_19C1, sub_4192
 *********************************************************/
struct bbb * sub_627(register char * ch, unsigned * par) { 
    unsigned loc;

#ifdef DEBUG
    struct bbb * tmp;
    printf("\tsub_627(\"%s\", %x)\n", ch, par);
#endif

    loc = 0;
    ch++;
    do {
      loc <<= 2;
      if(*ch == '(') {
	loc |= 2;
	ch++;
      } else if(*ch == '*') {
	loc |= 1;
	ch++;
      }
    } while ((isalnum(*ch) == 0) && (*ch != '_'));
    *par = 0;
    while (loc != 0) {
      *par <<= 2;
      *par |= (loc & 3);
      loc >>= 2;
    }
#ifdef DEBUG
    tmp = sub_265(ch);
    printf("\tsub_627\t\t\tReturn %x\n", tmp);
    return tmp;
#else
    return sub_265(ch);
#endif
}	

/*********************************************************
 * sub_6C8 OK++			Used in: sub_6D1, sub_76F
 *********************************************************/
void sub_6C8(void) {

    faterror("Bad int. code");
}

/* End of file sub_406.c */


