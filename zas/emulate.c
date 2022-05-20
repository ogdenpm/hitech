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
#ifndef CPM

#include "cclass.h"
#include "zas.h"
/* functions to emulate hitech floating point operations */
static zfloat dtento(uint32_t matissa, int16_t exp);

zfloat altof(uint32_t d) { /* long to float */
    return dtento(d, 0);
}

zfloat zatof(char *s) { /* ascii to float */
    uint32_t matissa = 0;
    int16_t exp      = 0;
    int16_t n        = 0;
    bool negExp      = false;

    while (Isdigit(*s)) {
        if (matissa < UINT32_MAX / 10)
            matissa = matissa * 10 + (*s - '0');
        else
            exp++;
        s++;
    }
    if (*s == '.') {
        s++;
        while (Isdigit(*s)) {

            if (matissa < UINT32_MAX / 10) {
                matissa = matissa * 10 + (*s - '0');
                exp--;
            }
            s++;
        }
    }
    if (Tolower(*s) == 'e') {
        s++;
        if (*s == '+' || *s == '-')
            negExp = *s++ == '-';
        while (Isdigit(*s))
            n = n * 10 + (*s++ - '0');
        if (negExp)
            exp -= n;
        else
            exp += n;
    }

    return dtento(matissa, exp);
};

/* function to return a val + exp into a floating point number in hitech C format */
/* note the accuracy of the numbers should be the same or better than the hitech C internal
   code as it repeatedly does *10.0 or /10.0, which can lead to rounding errors. Here
   the extra precision means that the rounding errors should be less
*/

static zfloat dtento(uint32_t val, int16_t exp) {
    if (val == 0) // zero result quick return
        return 0;
    /* use 64bit arithmetic to avoid lots of repeated normalisation */
    uint64_t matissa = val;
    short zexp       = 96; /* bias for exponent */
    if (exp >= 0) {
        /* for +ve exponents, keep mutliplying by 10, scaling when
           the next digit would overflow
        */
        while (exp-- > 0) {
            if (matissa >= UINT64_MAX / 10) {
                matissa >>= 24; /* allow room for more x10, still leaves reasonable precision */
                zexp += 24;
            }
            matissa *= 10;
        }
    } else {
        /* for -ve exponents scale to use full 64bits and keep dividing by 10
           scaling back to 64bits when the precision is < 40 bits
        */
        matissa <<= 32;
        zexp -= 32;
        while ((matissa & (1ULL << 63)) == 0) {
            matissa <<= 1;
            zexp--;
        }
        while (exp++ < 0) {
            if (matissa < (UINT64_MAX >> 24)) {
                matissa <<= 24;
                zexp -= 24;
            }
            matissa /= 10;
        }
    }
    /* normalise to occupy 32 bits*/
    while (matissa >= (1ULL << 32)) {
        matissa >>= 1;
        zexp++;
    }
    while (matissa < (1ULL << 31)) {
        matissa <<= 1;
        zexp--;
    }
    /* rounding */
    matissa += 0x80;
    if (matissa >= (1ULL << 32)) {
        matissa >>= 1;
        zexp++;
    }
    matissa >>= 8;
    /* the ouput on underflow and overflow does not match hitech C
       officially they should both return 0 with an internal flag
       fperr set. In practice they may not depending on circumstances
       here underflow returns 0, overflow returns largest number
    */
    if (zexp < 0) /* underflow */
        return 0;
    if (zexp > 127) /* overflow */
        return 0x7fffffff;

    return (uint32_t)matissa + (zexp << 24);
}
#endif
