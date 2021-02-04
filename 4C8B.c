/*
 * File - sub_4C8B.c Created 09.03.2019 Last Modified 31.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_4C8B OK++			Used in: sub_54B6
 *********************************************************/
struct aaa * sub_4C8B(register struct aaa * sa) {
    struct aaa * l1;

#ifdef DEBUG
    printf("\tsub_4C8B(%x)\n", sa);
#endif

    l1 = sa->a_l15.wi[0];
    if(sa->a_l15.wi[0]->a_c0 == NOT) {
      l1 = l1->a_l15.wi[0];
      sub_36E0(sa->a_l15.wi[0]);
      sub_36E0(sa);
      return l1; 
    } 
    if((dopetab[l1->a_c0] & 0x12C) == '(') {
      sub_36E0(sa);
      l1->a_c0 = sub_605E(l1->a_c0);
      return l1; 
    } 
    if((dopetab[l1->a_c0] & 0x20) != 0) {
      l1->a_l15.wi[0] = sub_43EF(NOT, l1->a_l15.wi[0], (struct aaa *)0);
      l1->a_l15.wi[1] = sub_43EF(NOT, l1->a_l15.wi[1], (struct aaa *)0);
      sub_36E0(sa);
      l1->a_c0 = (l1->a_c0 == LAND) ? LOR : LAND;
      return l1; 
    }	
    return sa;
}

/*********************************************************
 * sub_4DA3 OK++			Used in: sub_54B6
 *********************************************************/
struct aaa * sub_4DA3(register struct aaa * sa) {
    struct aaa * l1a;

#ifdef DEBUG
    printf("\tsub_4DA3(%x)\n", sa);
#endif

    if((char)sa->a_l15.wi[0]->a_i12 == 1) {
      l1a        = sub_415E(sa->a_l15.wi[0]->a_i10);
      l1a->a_i14 = sa->a_i14;
      l1a->a_i12 = sa->a_i12;
      sub_475C(sa);
      sub_385B(l1a);
      sa          = sub_3712();
      *sa         = *l1a;
      sa->a_c0    = USEREG;
      sa->a_l15.l = 8;
      sa          = sub_43EF(ADD, sa, l1a);
      return sub_43EF(INCR, sa, 0);
    }
    if((char)sa->a_l15.wi[0]->a_i12 == 2) {
      sa->a_c0    = USEREG;
      sa->a_l15.l = (int)sa->a_l15.wi[0]->a_i11;
    }
    return sa;
}

/*********************************************************
 * sub_4E8D OK++ 			Used in: sub_54B6
 *********************************************************/
struct aaa * sub_4E8D(register struct aaa * sa) {
    struct aaa * l1a;

#ifdef DEBUG
    printf("\tsub_4E8D(%x)\n", sa);
#endif

    if((dopetab[(l1a = sa->a_l15.wi[0])->a_c0] & 0x1000) != 0) {
      l1a->a_i14      = sa->a_i14;
      l1a->a_i12      = sa->a_i12;
      sa->a_l15.wi[0] = l1a = sub_43EF(GADDR, l1a, 0);
    } else {
      l1a       = sub_3712();
      *l1a      = *sa;
      l1a->a_c0 = TYPEOP;
      sub_385B(l1a);
      sa->a_l15.wi[0] = sub_43EF(CONV, sub_43EF(GADDR, sa->a_l15.wi[0], 0), l1a);
    }
    sa->a_i14              = l1a->a_i14;
    sa->a_i12              = l1a->a_i12;
    sa->a_l15.wi[1]->a_i12 = sa->a_i12;
    sa->a_l15.wi[1]->a_i14 = sa->a_i14;
    sa->a_c0               = ADD;
    return sub_43EF(MUL_U, sa, 0);
}

/*********************************************************
 * sub_4FA8 OK++			Used in: sub_54B6
 *********************************************************/
struct aaa * sub_4FA8(register struct aaa * sa) {

#ifdef DEBUG
    printf("\tsub_4FA8(%x)\n", sa);
#endif

    sub_475C(sa->a_l15.wi[1]);
    sub_36E0(sa);
    return sa->a_l15.wi[0];
}

/* End of file sub_4C8B.c  */


