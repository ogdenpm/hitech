/*
 * File - sub_60A8.c Created 09.03.2019 Last Modified 31.01.2021
 */

#include "stdio.h"
#include "cgen.h"

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_60A8 OK+				Used in: sub_54B6
 *
 * Added the r_bc variable to preserve the logical
 * behavior of the function. This function was optimized
 * manually in assembly language. In places with forced 
 * type casting in the original binary program image, the 
 * value is returned in the HL register pair.
 *
 * Generated code is different, but does not affect the
 * program logic. This function is boolean and only returns
 * 0 or 1.
 *********************************************************/
char sub_60A8(register struct aaa * sa, struct aaa * p2a) {
    long l1;
    char r_bc;	/* Original code uses BC register pair */

    if(sa->a_c0 != 'C')
	return 0;				/* m1: */
    if(nodesize(p2a) >= 4) {			/* m2: */
    	if(((uchar)sa->a_l15.bc[3] & 0x80) != 0) {
    	    if(sub_14F3(p2a) != REG_A) goto m4;
	}
	return (int)1;				/* m3: */
m4:	return (int)0;
    }
    l1 = (unsigned)1<<(int)nodesize(p2a)*8;	/* m5: */
    if(sub_14F3(p2a) != REG_L) goto m8;
    if(((uchar)sa->a_l15.bc[3] & 0x80) != 0) return 0;
m6: r_bc = 1;
    if(sa->a_l15.l >= l1) r_bc--;
m7: return r_bc;

m8: l1 /= 2;
    if(((uchar)sa->a_l15.bc[3] & 0x80) == 0) goto m6;
    r_bc = 1;
    if(sa->a_l15.l >= 0 - l1) goto m7;
    r_bc--;
    goto m7;
}

/* End function sub_60A8 */


