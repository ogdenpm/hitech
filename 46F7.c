/*
 * File - sub_46F7.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_46F7 OK++     Used in: sub_2D09, sub_47B2, sub_4FCE
 *			      sub_54B6
 *********************************************************/
uchar sub_46F7(long p1) {
    uchar l1;

#ifdef DEBUG
    printf("\tsub_46F7(%lu)\n", p1);
#endif

    if(((p1 & ((-1) + p1)) != 0) || (p1 < 1)) return 0;
    l1 = 0;
    while((p1 >>= 1) != 0) l1++;
    return (l1 + 1);
}

/* End of file sub_46F7.c  */


