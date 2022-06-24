/*
 *
 * The cclass.c file is part of the restored ZAS.EXE program
 * from the Hi-Tech Z80 C cross compiler v4.11
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH Z80 C cross compiler V4.11 
 * (HI-TECH Software) and extend its life, outside of the MSDOS 16 bit environment
 * for full operation in windows 32/64 and Unix-like operating systems
 *
 * The HI-TECH Z80 C cross compiler V4.11 is provided free of charge for any use,
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
 * This work is an extension of earlier work on decompiling ZAS.COM from the
 * Hi-Tech CP/M based compiler v3.09
 *
 * See the readme.md file for additional commentary
 *
 * Mark Ogden
 * 06-Jun-2022
 */
#include "cclass.h"
/* clang-format off*/
char ccClass[] = { /* 016b */
                   _Z, // EOF
                   _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,  // 0
                   _S,      _S,      _Z,      _Z,      _S,      _S,      _Z,      _Z,
                   _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,   // 10
                   _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,
                   _S,      _Z,      _Z,      _Z,      _L,      _Z,      _Z,      _Z,   // 20
                   _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,
                   _D | _X, _D | _X, _D | _X, _D | _X, _D | _X, _D | _X, _D | _X, _D | _X, //30
                   _D | _X, _D | _X, _Z,      _Z,      _Z,      _Z,      _Z,      _L,
                   _Z,      _U | _X, _U | _X, _U | _X, _U | _X, _U | _X, _U | _X, _U,   //40 
                   _U,      _U,      _U,      _U,      _U,      _U,      _U,      _U,
                   _U,      _U,      _U,      _U,      _U,      _U,      _U,      _U,   // 50
                   _U,      _U,      _U,      _Z,      _Z,      _Z,      _Z,      _L,
                   _Z,      _L | _X, _L | _X, _L | _X, _L | _X, _L | _X, _L | _X, _L,   // 60
                   _L,      _L,      _L,      _L,      _L,      _L,      _L,      _L,
                   _L,      _L,      _L,      _L,      _L,      _L,      _L,      _L,   // 70
                   _L,      _L,      _L,      _Z,      _Z,      _Z,      _Z,      _Z
};
/* clang-format on*/