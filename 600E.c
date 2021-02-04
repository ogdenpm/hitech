/*
 * File - sub_600E.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_600E OK++     Used in: sub_793,  sub_808,  sub_E43,
 *                            sub_17E0, sub_19C1, sub_1B0C,
 *			      sub_3DC9
 *********************************************************/
struct aaa * sub_600E(register struct aaa * sa) {
#if 0
    int l1; /* Not used */
#endif

#ifdef DEBUG
    struct aaa * tmp;
    printf("\tsub_600E(%x)\n", sa);
#endif

    word_B015 = 0;
    sa = sub_5DF6(sa);
#if 0
    l1 = 0; 		/* Not used, forgot to exclude */
#endif
    do {
      byte_B013 = 0;
/*
      Excluded part optimization code
      present in the DOS version (3.06)
*/
      sa = sub_3EAA(sub_54B6(sa));
    } while (byte_B013 != 0);

    if(word_B015 != 0) {
      warning(word_B015);
    }
#ifdef DEBUG
    tmp = sub_5F52(sa);
    printf("\tsub_600E\t\t Return %x\n", tmp);
    return tmp;
#else
    return sub_5F52(sa);
#endif
}

/* End of file sub_600E.c  */



