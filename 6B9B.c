/*
 * File - sub_6B9B.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * allocmem OK++    Used in: sub_265,  sub_1754, sub_19C1,
 *			     sub_1B0C, sub_3712, sub_39CA,
 * alloc_mem & return ptr    sub_4192, sub_508A, sub_5DF6
 *********************************************************/
void * allocmem(unsigned int size) {
    register char * ptr;

#ifdef DEBUG
    printf("\tallocmem(%u)\n", size);
#endif

    do {
      if((ptr = cmalloc(size)) != (void *)0) goto m1;
    } while (sub_374C() != 0);
    faterror("No room");
m1: blkclr(ptr, size);
    return ptr;
}	

/* End of file sub_6B9B.c  */


