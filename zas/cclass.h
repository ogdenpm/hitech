/*
 *
 * The cclass.h file is part of the restored ZAS.COM program
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
#ifndef _CCLASS_H
#define _CCLASS_H

extern char ccClass[129];

#define _Z          0  /* 0000 0000 */
#define _U          1  /* 0000 0001 */
#define _L          2  /* 0000 0010 */
#define _D          4  /* 0000 0100 */
#define _H          64 /* 0100 0000 */
#define _S          8  /* 0000 1000 */

#define Isalpha(c)  ((ccClass + 1)[(int)(c)] & (_U | _L))      /*(and	3) */
#define Isupper(c)  ((ccClass + 1)[(int)(c)] & _U)             /*(bit	0,(hl)) */
#define Isdigit(c)  ((ccClass + 1)[(int)(c)] & _D)             /*(bit	2,(hl)) */
#define Isxdigit(c) ((ccClass + 1)[(int)(c)] & _H)             /*(bit	6,(hl)) */
#define Isspace(c)  ((ccClass + 1)[(int)(c)] & _S)             /*(bit	3,(hl)) */
#define Isalnum(c)  ((ccClass + 1)[(int)(c)] & (_U | _L | _D)) /*(and	7) */
#define Tolower(c)  (Isupper(c) ? c + 0x20 : c)
#endif
