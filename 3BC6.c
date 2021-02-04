/*
 * File - sub_3BC6.c Created 09.03.2019 Last Modified 29.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_3BC6 v1 OK+			Used in: sub_3EAA
 *
 * Compiler generates identical code from restored source
 * program in C, however, location of branches associated
 * with case constants is different from original.
 * This does not affect the function.
 *********************************************************/
void sub_3BC6(register long * ptr, long p2, int operator) {

#ifdef DEBUG
    printf("\tsub_3BC6(%x, %lx, %d)\n", ptr, p2, operator);
#endif

    switch(operator) {
      case MOD:    *ptr %=  p2;  break;
      case BAND:   *ptr &=  p2;  break;
      case MUL:    *ptr *=  p2;  break;
      case ADD:    *ptr +=  p2;  break;
      case SUB:    *ptr -=  p2;  break;
      case DIV:    *ptr /=  p2;  break;
      case LSHIFT: *ptr <<= p2;  break;
      case RSHIFT: *ptr >>= p2;  break;
      case BXOR:   *ptr ^=  p2;  break;
      case BOR:    *ptr |=  p2;  break;
    }
    return;
}

/* End of file sub_3BC6.c  */


