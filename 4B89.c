/*
 * File - sub_4B89.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_4B89 OK+		      Used in: sub_4C12, sub_54B6
 *
 * Minor differences in the generated code.
 * Function is assigned the uchar type to avoid casting
 * type when it is called in other functions and generating
 * code corresponding to binary image.
 * Function is logically correct.
 *********************************************************/
uchar sub_4B89(register struct aaa * sa) {

#ifdef DEBUG
    printf("\tsub_4B89(%x)\n", sa);
#endif

    if((dopetab[sa->a_c0] & 0x10) == 0) { /* Any operator except "#", "..", "CONST" */
      if((sa->a_c0 != GADDR) || (sa->a_l15.wi[0]->a_c0 != IDOP)) {
        if(sa->a_c0 == ADD) {
          if(sa->a_l15.wi[1]->a_c0 == CONST) {
            if(sub_4B89(sa->a_l15.wi[0]) != 0) {
              return 1;
            }
          }
        }
        return 0;	/* m2: */
      }
    }
    return 1;		/* m3: */
}

/* End of file sub_4B89.c  */


