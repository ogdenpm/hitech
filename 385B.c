/*
 * File - sub_385B.c Created 09.03.2019 Last Modified 17.06.2020
 */

#include "stdio.h"
#include <string.h>
#include "cgen.h"

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_385B OK++    Used in: sub_387A, sub_43EF, sub_4DA3,
 *			     sub_4E8D
 *********************************************************/
void sub_385B(register struct aaa * sa) {

#ifdef DEBUG
    printf("\tsub_385B(%x)\n", sa);
#endif

    sa->a_i12 = (sa->a_i12*4)|1;
}

/*********************************************************
 * sub_387A OK++			Used in: sub_2D09
 *********************************************************/
int sub_387A(register struct aaa * sa) {
    char loc;

#ifdef DEBUG
    printf("\tsub_387A(%x)\n", sa);
#endif
	
    if(sa->a_i12 != 0) goto m1;
    if(sa->a_i14->b_type != 0) goto m1;
    if(sa->a_i14->b_refl != 0)  goto m1;
    return 1;
m1: sub_37ED(sa);
    loc = nodesize(sa);
    sub_385B(sa);
    return (uchar)loc;
}

/*********************************************************
 * sub_38CA OK++	      Used in: sub_393C, sub_3952
 *********************************************************/
int sub_38CA(struct aaa * p1a, int p2) {
    register struct bbb * sb;

#ifdef DEBUG
    printf("\tsub_38CA(%x, %d)\n", p1a, p2);
#endif

    if((p1a->a_i12 & p2) != 0) return 1;
    if(p1a->a_i12 != 0) return 0;
    sb = p1a->a_i14;
    do {
      if((sb->b_refl & p2) != 0) return 1;
      if(sb->b_refl != 0) return 0;
    } while ((sb = sb->b_type) != 0);
  return 0;
}


/*********************************************************
 * sub_393C OK++			Used in: Not used
 *********************************************************/
int sub_393C(struct aaa * sa) {

#ifdef DEBUG
    printf("\tsub_393C(%x)\n", sa);
#endif

    return sub_38CA(sa, 1);
}


/*********************************************************
 * sub_3952 OK++			Used in: Not used
 *********************************************************/
int sub_3952(struct aaa * sa) {

#ifdef DEBUG
    printf("\tsub_3952(%x)\n", sa);
#endif

    return sub_38CA(sa, 2);
}


/*********************************************************
 * sub_3968 OK++			Used in: sub_47B2
 *********************************************************/
int sub_3968(register struct aaa * sa) {

#ifdef DEBUG
    printf("\tsub_3968(%x)\n", sa);
#endif

    if(sa->a_i14->b_class == SDECL) {
      if(((sa->a_i12) & 1) == 0) return 1;
    }
    return 0;
}

/*********************************************************
 * nodesize OK++    Used in: sub_808,  sub_E43,  sub_2C5E,
 *			     sub_2D09, sub_387A, sub_3A79,
 *			     sub_43EF, sub_47B2, sub_508A,
 *			     sub_54B6, sub_60A8, sub_6246,
 *			     sub_62BE
 *********************************************************/
unsigned nodesize(register struct aaa * sa) {

#ifdef DEBUG
    unsigned tmp;
    printf("\tnodesize(%x)\t", sa);
#endif

    if((sa->a_i12 & 2) != 0) {
      uerror("can\'t take sizeof func");
    }
#ifdef DEBUG
    if((sa->a_i12 & 1) != 0) tmp = 2;
    else                     tmp = sa->a_i14->b_size;
    printf("\tReturn %d\n", tmp);
    return tmp;
#else
    if((sa->a_i12 & 1) != 0) return 2;
    return sa->a_i14->b_size;
#endif
}

/*********************************************************
 * sub_39CA OK++			Used in: sub_3EAA
 *********************************************************/
struct aaa * sub_39CA(register struct aaa * sa) {
    char buf[34];

#ifdef DEBUG
    printf("\tsub_39CA(%x)\n", sa);
#endif

    sub_36E0(sa->a_l15.wi[1]);
    if(sub_14F3(sa) == REG_F) {
      sprintf(buf, "%ld.", sa->a_l15.wi[0]->a_l15.l);
      sub_36E0(sa->a_l15.wi[0]);
      sa->a_l15.ci[0] = allocmem(strlen(buf)+1); /* create string */
      strcpy(sa->a_l15.ci[0], buf);
      sa->a_l15.ii[1] = sub_174C(); /* word_AE0F++ */
      sa->a_c0        = FCONST;
      return sa;
    }
    sub_3A79(sa, sa->a_l15.wi[0]);
    sub_36E0(sa);
    return sa->a_l15.wi[0];
}

/* End of file sub_385B.c  */


