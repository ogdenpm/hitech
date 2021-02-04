/*
 * File - sub_1659.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_1659 OK++			Used in: sub_1CEF
 * Find maximum between two numbers
 *********************************************************/
int sub_1659(int num1, int num2) {

#ifdef DEBUG
    printf("\tsub_1659(%x, %x)\n", num1, num2);
#endif

    return (num1 > num2 ) ? num1 : num2;
}

/* End of file - sub_1659.c  */


