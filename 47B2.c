/*
 * File - sub_47B2.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_47B2 OK+				Used in: sub_1F4B
 *********************************************************/
char sub_47B2(register struct aaa * sa, int p2) {
    long l1;

#ifdef DEBUG
    printf("\tsub_47B2(%x, %d)\n", sa, p2);
#endif

    switch (p2-1) {					/* m1:  */
      case MUL_U - 1:
        sa = sa->a_l15.wi[1];				/* m2:  loc_47DE */
      case T_SCOLON - 1:
        if(sa->a_l15.l >= 1) {				/* m3:  loc_47E7 */
          if(sa->a_l15.l < 3) return 1;
        }
        return 0;
      case RPAREN - 1:
        sa = sa->a_l15.wi[0];				/* m5:  loc_4821 */
      case MOD - 1:
        if(nodesize(sa) == 2) {				/* m6:  loc_482A */
m7:       if((char)sub_3968(sa) == 0) return 1;
        }
        return 0;
      case BAND - 1:
        if(sub_14F3(sa) != REG_F) goto m12;		/* m9:  loc_4846 */
        return 0;
      case MUL - 1:
        sa = sa->a_l15.wi[0];				/* m11: loc_4856 */
      case DOLLAR_U - 1:
m12:	if(nodesize(sa) == 4) return 0;			/* m12: loc_485F */
        goto m7;
      case SCOLON - 1:
        sa = sa->a_l15.wi[0];				/* m13: loc_486A */
      case DOLLAR-1:
        return sub_3968(sa);				/* m14: loc_4873 */
      case ADD - 1:
        if(sa->a_l15.bc[0] == 8) return 1;		/* m16: loc_487C */
        if(sa->a_l15.bc[0] == 9) return 1;
        return 0;
      case INCR - 1:
        l1 = sub_2C5E(sa, sa->a_l15.l);			/* m17: loc_4887 */
        if(l1 < (long)0xffffff80) return 0;
        if(l1 < 0x7d) return 1;
        return 0;
      case COLON_U - 1:
        if(sa->a_l15.l < 1) return 0;			/* m19: loc_48E0 */
        if(sa->a_l15.l < 5) return 1;
        return 0;
      case COLON_S - 1:
        l1 = sa->a_l15.l;				/* m20: loc_4910 */
        if(sub_14F3(sa) != REG_L) goto m21;
        if((l1 & 1<<(nodesize(sa)<<3)) == 0) goto m21;
        l1 |= ((-1) - (unsigned)((int)(1<<(nodesize(sa)<<3)) - 1));
m21:	if(((uchar)l1 & 0x80) == 0) return 0;
        if(l1 >= (long)0xFFFFFFFC)  return 1;
        return 0;
      case LPAREN - 1:
        sa = sa->a_l15.wi[1];				/* m22: loc_49AA */
      case HASHSIGN - 1:
        if(nodesize(sa) != 1) return 0;			/* m23: loc_49B3 */
        if((char)sub_3968(sa) != 0) return 0;
        return 1;
      case MINUS_U - 1:
        if(nodesize(sa) != 4) return 0;			/* m24: loc_49CD */
m25:	if(sub_14F3(sa) != REG_F) goto m27;
        return 0;
      case COMMA - 1:
        if(nodesize(sa) == 2) goto m25;			/* m26: loc_49EA */
        return 0;
m27:	if(sub_14F3(sa->a_l15.wi[0]) == REG_F) return 0;     /* loc_49FB */
        if(sub_14F3(sa) != REG_L) {
m28:	  if(sub_14F3(sa->a_l15.wi[0]) != REG_L) return 0;   /* loc_4A15 */
        }
        return 1;
      case LT - 1:
        if(sa->a_l15.l == 0) return 1;			/* m29: loc_4A29 */
        return 0;
      case CONV - 1:					/* m31: loc_4A3F */
        if(nodesize(sa) == 4) {
m32:	  if(sub_14F3(sa) == REG_A) {
            if(sub_14F3(sa->a_l15.wi[0]) == REG_A) return 1;
          }
        }
        return 0;
      case SUB - 1:
        if(nodesize(sa) == 2) goto m32;			/* m34: loc_4A5F */
        return 0;
      case PLUS_U - 1:
        if(1 == sa->a_l15.l) return 1;			/* m36: loc_4A7B */
        return 0;
      case NOT - 1:
        return (uchar)sub_46F7(sa->a_l15.wi[1]->a_l15.l);	/* m38: loc_4A9C */
      case NEQL - 1:
        return (uchar)sub_46F7(-1 - sa->a_l15.wi[1]->a_l15.l);	/* m40: loc_4AB7 */
      case COLON - 1:
        if(nodesize(sa) == 4) goto m45;			/* m41: loc_4ADB */
        return 0;
      case DECR - 1:
        if(nodesize(sa) == 2) goto m45;			/* m43: loc_4AEC */
        return 0;
      case GADDR - 1:
        if(nodesize(sa) != 1) return 0;			/* m44: loc_4AF7 */
m45:	if(sub_14F3(sa) != REG_A) {
          if(sub_14F3(sa) != REG_L) return 0;
        }
        if(sub_14F3(sa->a_l15.wi[0]) != REG_F) return 0; /* m46: loc_4B19 */
        return 1;
      case DIV - 1:
        if(nodesize(sa->a_l15.wi[0]) == 1) goto m51;	/* m47: loc_4B2A */
        return 0;
      case DOT_DOT - 1:
        if(nodesize(sa->a_l15.wi[0]) == 2) goto m51;	/* m49: loc_4B40 */
        return 0;
      case DOT - 1:
        if(nodesize(sa->a_l15.wi[0]) != 4) return 0;	/* m50: loc_4B50 */
m51:	if(sub_14F3(sa) != REG_F) return 0;
        if(sub_14F3(sa->a_l15.wi[0]) == REG_A) return 1;
        goto m28;
      case LAND - 1:
        if(sub_14F3(sa) == REG_F) return 1;		/* m52: loc_4B7D */
    }
    return 0;
}

/* End of file sub_47B2.c  */


