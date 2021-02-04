/*
 * File - sprintf.c Created 01.07.2019 Last Modified 31.01.2021
 */

#include <stdio.h>

static	FILE	spf;

#define MAXINT  32767	/* max for int (0x7fff)	*/

/*========================================================
 * sprintf OK++ From library		Used in: sub_6BF5
 * 
 * Unlike the standard library function, this one uses the 
 * _IOWRT|_IOBINARY flags instead of _IOWRT|_IOBINARY|_IOSTRG.
 *=======================================================*/
int sprintf(wh, f, a) char * wh; char * f; int a; {

    spf._cnt = MAXINT;
    spf._ptr = wh;
    spf._flag = _IOWRT|_IOBINARY;
    _doprnt(&spf, f, &a);
    *spf._ptr = 0;
    return spf._ptr - wh;
}

/* End function sprintf */

