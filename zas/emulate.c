/*
 *
 * The emulate.c file is part of the restored ZAS.COM program
 * from the Hi-Tech C compiler v3.09
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH C compiler V3.09
 * (HI-TECH Software) and extend its life, outside of the CP/M environment
 * (Digital Research, Inc), for full operation in a  Unix-like operating
 * system UZI-180 without using the CP/M emulator.
 *
 * The HI-TECH C compiler V3.09 is provided free of charge for any use,
 * private or commercial, strictly as-is. No warranty or product support
 * is offered or implied including merchantability, fitness for a particular
 * purpose, or non-infringement. In no event will HI-TECH Software or its
 * corporate affiliates be liable for any direct or indirect damages.
 *
 * You may use this software for whatever you like, providing you acknowledge
 * that the copyright to this software remains with HI-TECH Software and its
 * corporate affiliates.
 *
 * All copyrights to the algorithms used, binary code, trademarks, etc.
 * belong to the legal owner - Microchip Technology Inc. and its subsidiaries.
 * Commercial use and distribution of recreated source codes without permission
 * from the copyright holderis strictly prohibited.
 *
 * Early work on the decompilation was done by Andrey Nikitin
 * Completion of the work and porting to work under modern compilers done by Mark Ogden
 * 19-May-2022
 */


/* functions to emulate hitech floating point operations */

/* simple option using native IEEE floating point with sizeof(float) == 4
   this version relies on the floating point number and uint32_t being stored
   int the same byte order

*/
#ifndef CPM
#include "zas.h"
#include <math.h>
#define ZBIAS    65
#define IEEEBIAS 127

zfloat tozfloat(double f) {
    union {
        zfloat zf; /* warning relies same byte ordering cf. float */
        float f;
    } u;
    int n;
    u.f     = (float)frexp(f, &n); /* split matissa and exponent */
    int zexp = ((u.zf >> 23) & 0xff) - IEEEBIAS + n + ZBIAS;
    if ((u.zf == 0 && n == 0) || zexp < 0 || zexp > 127) /* zero or under/overflow */
        return 0;
    u.zf &= 0x807fffff; /* remove IEEE exponent */
    u.zf |= (zexp << 24) + (1 << 23); /* add in exponent and IEEE's hidden bit */
    return u.zf;

}

#endif


