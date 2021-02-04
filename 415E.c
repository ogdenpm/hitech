/*
 * File - sub_415E.c  Created 09.03.2019 Last Modified 26.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_415E OK++   Used in: sub_808,  sub_E43,  sub_4192,
 *			    sub_4DA3, sub_54B6
 *********************************************************/
struct aaa * sub_415E(long number) {
    register struct aaa * sa;

#ifdef DEBUG
    printf("\tsub_415E(%ld)\n", number);
#endif
    sa          = sub_3712();
    sa->a_c0    = CONST;
    sa->a_i14   = word_AE11;	/* "l" - long	  */
    sa->a_l15.l = number;
#ifdef DEBUG
    printf("\tsub_415E\t\tReturn %x\n", sa);
#endif
    return sa;
}

/* End of file sub_415E.c  */


