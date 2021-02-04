/*
 * File - sub_3564.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_3564 OK++			Used in: sub_35E6
 *********************************************************/
void sub_3564(register struct aaa * sa) {
    char         l1;
    struct zzz * l2z;

#ifdef DEBUG
    printf("\tsub_3564(%x)\n", sa);
#endif

    word_AFF8 = 0;
    l1 = 0;
    while ((unsigned)l1 != sa->a_c1) {
      if(((l2z = &array_80EF[*(&sa->a_c3 + l1)]))->p_6 != 0) {
        sub_2D09(sa, l2z->p_6, l1);
        putchar('\n');
      }
      l1++;
    }
#ifdef DEBUG
    printf("\tsub_3564\t\tReturn\n");
#endif
}

/*********************************************************
 * sub_35E6 OK+				Used in: sub_2BD0
 *
 * Minor differences in the generated code
 *********************************************************/
void sub_35E6(register struct aaa * sa) {
    int l1;

#ifdef DEBUG
    printf("\tsub_35E6(%x)\n", sa);
#endif

    if((dopetab[sa->a_c0] & 0x200) != 0) word_AFFB++;
    l1 = dopetab[sa->a_c0] & 0xC;
    if(8 == l1) { 
      if((bittst(sa->a_c2, 0)) != 0) {
        sub_35E6(sa->a_l15.wi[0]);
        sub_35E6(sa->a_l15.wi[1]);
      } else {
        sub_35E6(sa->a_l15.wi[1]);
        if((bittst(sa->a_c2, 1)) != 0) {
          /* Following statement creates code that is not
             significantly different from  original. */
          sub_143F(*(sa->a_l15.wi[1]->a_c1 + &sa->a_l15.wi[1]->a_c0 + 0xE));
        }
        sub_35E6(sa->a_l15.wi[1]);
      }
    }
    if(l1 == 4) {
      sub_35E6(sa->a_l15.wi[0]);
    }
    if((bittst(sa->a_c2, 1)) != 0) {
      /* Following statement creates code that is not
         significantly different from  original. */
      sub_1489(*(sa->a_l15.wi[1]->a_c1 + &sa->a_l15.wi[1]->a_c0 + 0xE));
    }
    sub_3564(sa);
    if((dopetab[sa->a_c0] & 0x200) != 0) word_AFFB--;
}

/*********************************************************
 * sub_36E0 OK++   Used in: sub_E43,  sub_39CA, sub_3CDF, 
 *			    sub_3DC9, sub_3EAA, sub_43EF,
 *			    sub_475C, sub_4C8B, sub_4FA8,
 *			    sub_508A, sub_53EE, sub_54B6,
 *			    sub_5DF6, sub_5F52
 *********************************************************/
void sub_36E0(register struct aaa * sa) {

#ifdef DEBUG
    printf("\tsub_36E0(%x)\n", sa);
#endif
 
    (byte_B013) = 1;
    if(sa->a_c0 == FCONST) {
      sub_7028((struct ptr *)sa->a_l15.wi[0]);
    }
    sa->a_i14 = word_B011;
    word_B011 = sa;
/*  
    --nodecnt;
*/
}

/*********************************************************
 * sub_3712 OK++    Used in: sub_E43,  sub_377A, sub_415E,
 *			     sub_4192, sub_43EF, sub_4DA3,
 *			     sub_54B6
 *********************************************************/
struct aaa * sub_3712(void) {
    register struct aaa * sa;

#ifdef DEBUG
    printf("\tsub_3712()\n");
#endif

    byte_B013 = 1;
    if(word_B011 != 0) {
      sa = word_B011;
      word_B011 = sa->a_i14;
      blkclr((char *)sa, sizeof(struct aaa));
    } else { /* create struct aaa */
      sa = (struct aaa *)allocmem(sizeof(struct aaa));
    }
/*
    if(++nodecnt > nodes) nodes = nodecnt;
*/
#ifdef DEBUG
    printf("\tsub_3712\t\tReturn %x\n", sa);
#endif
    return sa;
}

/*********************************************************
 *  sub_374C OK++			Used in: allocmem
 *********************************************************/
char sub_374C(void) {
    register struct aaa * sa;

#ifdef DEBUG
    printf("\tsub_374C()\n");
#endif

    if(word_B011 == 0) return 0;
    while((sa = word_B011) != 0) {
      word_B011 = sa->a_i14;
      sub_7028((struct ptr *)sa);
    }	
    return 1;
}

/*********************************************************
 *  sub_377A OK++			Used in: sub_3CDF
 *********************************************************/
struct aaa * sub_377A(struct aaa * p1a) {
    register struct aaa * sa;

#ifdef DEBUG
    printf("\tsub_377A(%x)\n", p1a);
#endif

    sa = sub_3712();
    *(sa) = *(p1a); 

    if((dopetab[sa->a_c0] & 0xC) != 0) {
      sa->a_l15.wi[0] = sub_377A(sa->a_l15.wi[0]);
    }
    if((dopetab[sa->a_c0] & 0xC) == 8) {
      sa->a_l15.wi[1] = sub_377A(sa->a_l15.wi[1]);
    }
    return sa;
}

/* End of file sub_3564.c  */


