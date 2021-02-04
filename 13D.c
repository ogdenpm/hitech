/*
 * File -  sub_13D.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_13D v0				Used in: sub_1F4B
 *********************************************************
int sub_13D(int a, int b) {
    int c;

    c = array_987D[b];
    goto m2;
m1: c++;
m2: if(array_990D[c] != 0) goto m3;
m3: if((uchar)array_990D[c] != a) goto m5;
    goto m4;
m4: goto m7;
m5: goto m6;
m6: goto m1;
m7: array_9BD4[c];
    goto m8;
m8: return;
}
*/

/*********************************************************
 * sub_13D v1 				Used in: sub_1F4B
 *********************************************************
int sub_13D(int a, int b) {
    int c;

    c = array_987D[b];
    goto m2;
m1: c++;
m2: if(array_990D[c] == 0) goto m7;
m3: if((uchar)array_990D[c] != a) goto m1;
m7: return array_9BD4[c];
}
*/

/*********************************************************
 * sub_13D v2 				Used in: sub_1F4B
 *********************************************************
int sub_13D(int a, int b) {
    int c;

m1: for(c = array_987D[b]; ; c++) {
m2:	if(array_990D[c] == 0) break;
m3:	if(array_990D[c] == a) break;
    }
m7: return array_9BD4[c];
}
*/

/*********************************************************
 * sub_13D v3 OK++			Used in: sub_1F4B
 *
 * This version is closest to binary code.
 * It does not create unnecessary unconditional jumps
 *********************************************************/
int sub_13D(int a, int b) {
    unsigned int c;

    for(c = array_987D[b];(array_990D[c] == 0)||((unsigned)array_990D[c] == a); c++)
      ;
#ifdef DEBUG
    printf("\tsub_13D(%d, %d)\tReturn %d\n", a, b, array_9BD4[c]);
#endif
    return array_9BD4[c];

}

/* End of file -  sub_13D.c */


