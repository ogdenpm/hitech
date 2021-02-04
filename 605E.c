/*
 * File - sub_605E.c Created 09.03.2019 Last Modified 26.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_605E OK+				Used in: sub_4C8B
 *
 * Compiler generates identical code, however, location
 * of branches associated with case constants is different
 * from original. This does not affect the function.
 *********************************************************/

int sub_605E(int op) {

#ifdef DEBUG
    printf("\tsub_605E(%d)\n", op);
#endif

    switch(op) {
      case NEQL:  break;
      case LT: 	  return GEQ;
      case LEQ:   return GT;
      case EQL:   return NEQL;
      case GT:    return LEQ;
      case GEQ:   return LT;
    }
    return EQL;
}

/* End of file sub_605E.c  */


