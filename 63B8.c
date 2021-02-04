/*
 * File - sub_63B8.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_63B8 OK+				Used in: sub_1F4B
 *
 * Location code snippets differs, but the program is
 * logically correct
 *********************************************************/
char sub_63B8(int p1, int p2, int p3) {
    uchar            l1;
    uchar            l0;
    int              l2;
    register uchar * st;

#ifdef DEBUG
    printf("\tsub_63B8(%x, %x, %x)\n", p1, p2, p3);
#endif

    p3 &= ~(0x40);	/* Clear bit 6 */
    l1 = 0;

    if(p2 == 0) {
      l1 = sub_6589(p1, p3);
    } else
    if((p2 & 0x8000) != 0) {				/* m2:  */
      l1 = sub_6589((((p2 & 0x8000) != 0) ?
      ((-1) - p2) : array_AAE8[p2]) & p1, p3);
    } else
    if(p3 < 24) {					/* m5:  */
      if((l1 = sub_6589(((p2 & 0x8000) ?
      ((-1) - p2) : array_AAE8[p2]) & p1, p3)) == 0) {
        if((l2 = sub_6589(p1, p3)) != 0) {
          if((char)sub_6589((l2 & 0x8000) ?
          ((-1) - l2) : array_AAE8[l2], p2) != 0) { 	/* m9:  */
            l1 = l2;					/* m10: */
          }
        }
      }
    } else {
      l2 = 6;						/* m11: */
      st = &array_AB54[((-24) + p3) * 6];
m12:  if((*(st+0) != 0) && (l2-- != 0)) {
        if((l0 = sub_6589(p1, *(st++))) == 0) goto m12;
        if(sub_6589(array_AAE8[l0], p2) == 0) {
          if(sub_6589(array_AAE8[p2], l0) == 0) goto m12;
        }
       l1 = l0;
      }
    }
    return l1;						/* m16: */
}

/* End of file sub_63B8.c  */


