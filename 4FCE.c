/*
 * File - sub_4FCE.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_4FCE OK+				Used in: sub_54B6
 *
 * Compiler generates identical code from restored source
 * program in C, however, location of branches associated
 * with case constants is different from original.
 * This does not affect the function.
 *********************************************************/
struct aaa * sub_4FCE(register struct aaa * sa) {

#ifdef DEBUG
    printf("\tsub_4FCE(%x)\n", sa);
#endif
 
    switch (sa->a_c0) {
      case MOD:
        sa->a_c0 = BAND;
        sa->a_l15.wi[1]->a_l15.l--;
        return sa;
      case MUL:
        sa->a_c0 = LSHIFT;
        break;
      case DIV:
        if(sub_14F3(sa) != REG_L) return sa;
        sa->a_c0 = RSHIFT;
        break;
      case ASMOD:
        sa->a_c0 = ASAND;
        sa->a_l15.wi[1]->a_l15.l--;
        return sa;
      case ASMUL:
        sa->a_c0 = ASLSHIFT;
        break;
      case ASDIV:
        if(sub_14F3(sa) != REG_L) return sa;
        sa->a_c0 = ASRSHIFT;
        break;
    }
    byte_B013 = 1;
    sa->a_l15.wi[1]->a_l15.l = sub_46F7(sa->a_l15.wi[1]->a_l15.l) - 1;
    return sa;
}

/* End of file sub_4FCE.c  */


