/*
 * File - sub_1F4B.c Created 09.03.2019 Last Modified 21.01.2021
 */

#include "stdio.h"
#include <ctype.h>
#include "cgen.h"

/* int asdf; */
/*********************************************************
 * sub_1F4B OK+ (optim: Out of memory)	Used in: sub_2BD0
 *********************************************************/
int sub_1F4B(struct aaa * p1a, int p2, int p3, int p4, int * p5) {
    int l1, l2, l3, l4, l5, l6, l7, l8;
    register struct zzz * sz;

#ifdef DEBUG
    printf("\tsub_1F4B(%x, %d, %d, %d, %x)\n", p1a, p2, p3, p4, p5);
#endif

/**/
    if(p1a->a_c1 == 0) p1a->a_c2 = 0;
    if((l1 = sub_13D(p2, p1a->a_c0)) == 0) return (-1);
#if 1
    if(dummy1(p1a, p3, p4) == -1) return (-1);
#else
/* 
    if(p4 != 0) {
      if((p4 & 0x8000) == 0) {
        if(sub_6589(p3, p4) == (int)0) {
          if(p1a->a_c0 != USEREG) return (-1);
          if(sub_6589(array_AAE8[p1a->a_l15.ii[0]], p4) == (int)0) return (-1);
        }
      }
    }
*/
#endif

m4: if(l1 > 0) word_AFED = l5 = array_A162[l1++];
    else       word_AFED = l5 = l1;
k6: if(word_AFED < 0) word_AFED = (0 - word_AFED);	/* ok */
k7: sz = &array_80EF[word_AFED];

    if((sz->c_2 != 0) && (sub_6589(p3, sz->c_2) == 0)) goto m9;

k8: if((uchar)sz->c_3 < 'H') {
      if(sz->c_4 != 0) {
        if(sub_13D((uchar)sz->c_4, p1a->a_l15.wi[0]->a_c0) == 0) goto m9;
        if(sz->c_5 != 0) {
          if(sub_13D((uchar)sz->c_5, p1a->a_l15.wi[1]->a_c0) == 0) {
m9:         if(l5 >= 0) goto m4;			/* ok */
            return (-1);
          }
        }
      }
    }
/**/

/*
m9: if(((unsigned)l5 & 0x8000) != 0) return (-1);
    asdf = 1;
*/ 

/**/
k10:if((sz->c_0 != 0) && (sub_47B2(p1a, sz->c_0) == 0)) goto m9;
k11:l6 = sz->c_1;
    l7 = 0;
    if((p4 == 0) && (sz->c_3 == 'E')) p4 = sz->c_3;
k12:if(p4 != 0) {
      if((p4 & 0x8000) != 0) {
        if(l6 != 0) {
          if(sub_6589(p4 & (~0x8000), l6) == 0) goto m30; 	
        }
      }
k13:  if((word_AFEF = sz->p_8) != 0) {
        if((*word_AFEF == 'L') && (*(word_AFEF+1) == 0)) word_AFEF = "GL"; /* array_A94A */
k28:    while (*(word_AFEF) != 0) {
k14:      byte_AFF3 = *word_AFEF;
          if(byte_AFF3 == 'X') goto m15;
          if(byte_AFF3 == 'G') goto m15;
          if(byte_AFF3 != 'S') goto m26;
          if(p1a->a_c0 == USEREG) goto m15;
          goto m26;
m15:      if(isdigit(*(++word_AFEF)) != 0) word_AFF1 = word_AFEF;
          else			           word_AFF1 = (char *)0;
          while (*(word_AFEF) < 'A') word_AFEF++;
          if(*(word_AFEF) == 'L') goto m20;
          if(*(word_AFEF) == 'N') goto m23;
          if(*(word_AFEF) != 'R') continue;
          goto m22;

m20:      if((l6 = sub_66BC(l6, p4, p3, word_AFF1)) == 0) {
m21:        l6 = -1;
          }
          goto m30;

m22:      l7 = p4;
          goto m30;

m23:      if(byte_AFF3 != 'S') goto m25;
          if(p1a->a_c0 != USEREG) goto m30;
          if(sub_66BC(l6, p4, array_AAE8[p1a->a_l15.ii[0]], word_AFF1) == 0) {
            l6 = -1;
          }
          goto m30;

m25:      if(sub_63B8(p3, p4, sz->c_2) != 0) goto m30;
          if((p4 & 0x8000) == 0) goto m21;
          if(sub_66BC(sz->c_2, p4, p3, word_AFF1) == 0) {
            l6 = -1;
          }
          goto m30;
m26:	  word_AFEF++;
        }
      } else {
k29:    if((l6 = sub_66BC(l6, p4, p3, 0)) == 0) l6 = -1;
      }
    }
/**/
m30:if(l6 == -1) goto m9;
    l4 = 0;
    if((uchar)sz->c_3 >= 'H') {
      p1a->a_c1 = 0;
      if(sub_1F4B(p1a, (uchar)sz->c_3, p3, l6, &l2) >= 0) goto m42; /* ok */
      p1a->a_c1 = 0;
      goto m9;
    }
k31:if(sz->c_4 != 0) {
      *(p1a->a_l15.ci[0]+1) = 0;
      if(sub_1F4B(p1a->a_l15.wi[0], (uchar)sz->c_4, p3, l6, &l2) < 0) goto m9; /* ok */
      if(sz->c_5 == 0) goto m42;
      *(p1a->a_l15.ci[1]+1) = 0;
      l8 = sub_2B2A(p1a->a_l15.wi[0]);
      if(l7 == 0) {
        if(sz->c_2 != 0) l7 = array_AAE8[(uchar)sub_63B8(p3, p4, sz->c_2)];
        else		 l7 = 0;
k33:    l7 = ((l8 | l7) != 0) ? (((unsigned)(l8 | l7)) | 0x8000) : 0;
      }
k36:  if(sub_1F4B(p1a->a_l15.wi[1], (uchar)sz->c_5, p3, l6, &l3) < 0) goto m9; /* ok */
      l4 = sub_2B2A(p1a->a_l15.wi[1]);
      if((l4 | l8) != 0) {
        *(p1a->a_l15.ci[1]+1) = 0;
        if(0 >= sub_1F4B(p1a->a_l15.wi[1], (uchar)sz->c_5, (p3 & ((-1)-l8)), l7, &l3)) goto m9;
        l4 = sub_2B2A(p1a->a_l15.wi[1]);
      }
k37:  if((dopetab[p1a->a_c0] & 0x100) != 0) goto m38;		/* LOGOP & QUEST */
      if((l4 & l2) != 0) {
m38:    if((l8 & l3) != 0) { 		/* m38: */
          if((dopetab[p1a->a_c0] & 0x100) != 0) goto m9;	/* LOGOP & QUEST */
          p1a->a_c2 = 2;
          l4 = 0;
          goto m42;
        } else {
k39:      p1a->a_c2 = 1; 		/* m39: */
          goto m42;
        }
      }
k40:  p1a->a_c2 = 0;			/* m40: */
    } else {
k41:  if(l6 != 0) p4 = l6;
    }
m42:if(sz->c_2 != 0) { 
      word_AFF4 = p3;
      if((sz->c_2 & 0x40) == 0) goto m43;
      word_AFF6 = (unsigned)sub_63B8(sub_2B2A(p1a), p4, sz->c_2);
      if(word_AFF6 == 0) {
m43:    if((sz->c_2 & 0x40) == 0) word_AFF4 &= ((-1) - sub_2B2A(p1a));
k44:    word_AFF4 &= ((-1) - l4);
        word_AFF6 = (unsigned)sub_63B8(word_AFF4, p4, sz->c_2);
        if(word_AFF6 == 0) {
          word_AFF6 = (uchar)sub_6589(word_AFF4, sz->c_2);
          if(word_AFF6 == 0) goto m9;
        }
      }
k45:  *((uchar)p1a->a_c1 + (uchar*)p1a + 9) = word_AFF6;
    } else {
k46:  *((uchar)p1a->a_c1 + (uchar*)p1a + 9) = 0;
    }
k47:*((uchar)(p1a->a_c1++) + (uchar*)p1a + 3) = (sz - array_80EF);
    word_AFF6 = (uchar)sub_2B79(p1a);
    *((uchar*)p1a + (uchar)p1a->a_c1 + 0xE) = word_AFF6;
    if(word_AFF6 == 0)   {
      if(p1a->a_c0 == USEREG) {
        *((uchar*)p1a + (uchar)p1a->a_c1 + 0xE) = (word_AFF6 = p1a->a_l15.ii[0]);
      }
    }
k48:if(p4 != 0) {
      if((p4 & 0x8000) == 0) {
        if(word_AFF6 == 0) goto m58;
        if((uchar)sub_6589(((p4 & 0x8000) != 0) ? 
        ((-1) - p4) : 
        array_AAE8[p4], word_AFF6) != word_AFF6) goto m58;
      }
    }

#if 1
    if(dummy2(p4)  == -1) {
      p1a->a_c1--;
      goto m9;
    }
#else
k51:if((p4 & 0x8000) != 0) {	
      if((((p4 & 0x8000) ? (-1) - p4 : array_AAE8[p4]) & 
      ((word_AFF6 & 0x8000) ? (-1) - word_AFF6 : array_AAE8[word_AFF6])) != 
      ((word_AFF6 & 0x8000) ? (-1) - word_AFF6 : array_AAE8[word_AFF6])) {
m58:    p1a->a_c1--;
        goto m9;
      }
    }
#endif

k59:*p5 = array_AAE8[*((uchar*)p1a + (uchar)p1a->a_c1 + 8)];
    if(((uchar)sz->c_3 >= 'H') || (sz->c_4 != 0)) *p5 |= l2;
    if(sz->c_5 != 0) *p5 |= l3;
    return 1;
}

/* End of file sub_1F4B.c  */

#if 1
/*
 * dummy1
 */
int dummy1(struct aaa * p1a, int p3, int p4) {

#ifdef DEBUG
    printf("\tdummy1(%x, %d, %d)\n", p1a, p3, p4);
/*
    pr_st_a(p1a);
*/
#endif

    if(p4 != 0) {
      if((p4 & 0x8000) == 0) {
        if(sub_6589(p3, p4) == (int)0) {
          if(p1a->a_c0 != USEREG) return (-1);
          if(sub_6589(array_AAE8[p1a->a_l15.ii[0]], p4) == (int)0) return (-1);
        }
      }
    }
    return 0;
}

/*
 * dummy2
 */
int dummy2(int p4) {
#ifdef DEBUG
    printf("\tdummy2(%d)\n", p4);
#endif

    if(p4 != 0) {
      if((p4 & 0x8000) == 0) {
        if(word_AFF6 == 0) goto m58;
        if((uchar)sub_6589(((p4 & 0x8000) != 0) ? ((-1) - p4) : array_AAE8[p4], word_AFF6) != word_AFF6) goto m58;
      }
    }
    if((p4 & 0x8000) != 0) {	
      if((((p4 & 0x8000) ? (-1) - p4 : array_AAE8[p4]) & 
      ((word_AFF6 & 0x8000) ? (-1) - word_AFF6 : array_AAE8[word_AFF6])) != 
      ((word_AFF6 & 0x8000) ? (-1) - word_AFF6 : array_AAE8[word_AFF6])) {
m58:    return -1;
      }
    }
    return 0;
}
#endif

