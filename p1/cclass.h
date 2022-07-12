/*
 *
 * The cclass.h file is part of the restored P1.COM program
 * from the Hi-Tech CP/M Z80 C v3.09
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH Z80 C compiler V3.09
 * (HI-TECH Software) and extend its life, outside of the CP/M environment
 * for full operation in windows 32/64 and Unix-like operating systems
 *
 * The HI-TECH Z80 C cross compiler V3.09 is provided free of charge for any use,
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
 *
 * See the readme.md file for additional commentary
 *
 * Mark Ogden
 * 09-Jul-2022
 */
#ifndef _CCLASS_H
#define _CCLASS_H

extern char ccClass[129];

#define _Z          0  /* 0000 0000 */
#define _U          1  /* 0000 0001 */
#define _L          2  /* 0000 0010 */
#define _D          4  /* 0000 0100 */
#define _X          8 /* 0100 0000 */
#define _S          16  /* 0001 0000 */

#define Isalpha(c)  ((ccClass + 1)[(int16_t)(c)] & (_U | _L))      /*(and	3) */
#define Isupper(c)  ((ccClass + 1)[(int16_t)(c)] & _U)             /*(bit	0,(hl)) */
#define Islower(c)  ((ccClass + 1)[(int16_t)(c)] & _L)             /*(bit	0,(hl)) */
#define Isdigit(c)  ((ccClass + 1)[(int16_t)(c)] & _D)             /*(bit	2,(hl)) */
#define Isxdigit(c) ((ccClass + 1)[(int16_t)(c)] & _X)             /*(bit	6,(hl)) */
#define Isspace(c)  ((ccClass + 1)[(int16_t)(c)] & _S)             /*(bit	3,(hl)) */
#define Isalnum(c)  ((ccClass + 1)[(int16_t)(c)] & (_U | _L | _D)) /*(and	7) */
#define Tolower(c)  (Isupper(c) ? c + 0x20 : c)
#endif
