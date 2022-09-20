/*
 *
 * The op.c file is part of the restored P1.COM program
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
#include "p1.h"
/* clang-format off */
op_t opTable[68] = {
{"",    6,    0,    0x200,  7}, /*  60 T_OPBOT */
{"(",   0x1e, 2,    0x200,  3}, /*  61 */
{"",    0x1f, 0,    0,      0}, /*  62 T_LPAREN */
{"",    2,    0,    0,      0}, /*  63 T_RPAREN */
{"",    0x1e, 2,    0,      0}, /*  64 T_ARRAYIDX */
{"",    0x1e, 0,    0,      0}, /*  65 T_LBRACK */
{"",    2,    0,    0,      0}, /*  66 T_RBRACK */
{".",   0x1e, 2,    0xa00,  2}, /*  67 T_DOT */
{"",    0x1e, 2,    0,      0}, /*  68 T_POINTER */
{"*U",  0x1c, 0x1c, 0x4200, 3}, /*  69 D_DEREF */
{"&U",  0x1c, 0x1c, 0x2200, 4}, /*  70 D_ADDRESSOF */
{"-U",  0x1c, 0x1c, 0x30,   1}, /*  71 D_NEG */
{"!",   0x1c, 8,    2,      6}, /*  72 T_LNOT */
{"~",   0x1c, 0x18, 0x20,   1}, /*  73 T_BNOT  */
{"",    0x1c, 8,    0,      0}, /*  74 T_PREINC */
{"",    0x1c, 8,    0,      0}, /*  75 T_POSTINC */
{"",    0x1c, 8,    0,      0}, /*  76 T_PREDEC */
{"",    0x1c, 8,    0,      0}, /*  77 T_POSTDEC */
{"#",   0x1c, 0x18, 0x300,  5}, /*  78 T_SIZEOF */
{"()",  0x1c, 0xa,  0,      0}, /*  79 T_CAST */
{"*",   0x1a, 0x16, 0x70,   1}, /*  80 T_MUL */
{"&",   0x11, 0x16, 0x60,   1}, /*  81 T_BAND */
{"-",   0x18, 0x16, 0x7c,   1}, /*  82 T_MINUS */
{"/",   0x1a, 0x12, 0x70,   1}, /*  83 T_ DIV */
{"%",   0x1a, 0x12, 0x60,   1}, /*  84 T_MOD */
{"+",   0x18, 0x12, 0x74,   1}, /*  85 T_PLUS */
{">>",  0x16, 0x12, 0x60,   1}, /*  86 T_SHR */
{"<<",  0x16, 0x12, 0x60,   1}, /*  87 T_SHL */
{"<",   0x14, 0x12, 0x10f8, 6}, /*  88 T_LT */
{">",   0x14, 0x12, 0x10f8, 6}, /*  89 T_GT */
{"<=",  0x14, 0x12, 0x10f8, 6}, /*  90 T_LE */
{">=",  0x14, 0x12, 0x10f8, 6}, /*  91 T_GE */
{"==",  0x12, 0x12, 0x90f8, 6}, /*  92 T_EQEQ */
{"!=",  0x12, 0x12, 0x90f8, 6}, /*  93 T_NE */
{"^",   0x10, 0x12, 0x60,   1}, /*  94 T_XOR*/
{"|",   0xf,  0x12, 0x60,   1}, /*  95 T_BOR */
{"&&",  0xe,  2,    3,      6}, /*  96 T_LAND */
{"||",  0xd,  2,    3,      6}, /*  97 T_LOR */
{"?",   0xc,  0x1a, 2,      2}, /*  98 T_QUEST */
{":",   0xc,  0x1a, 0x12f8, 1}, /*  99 T_COLON */
{"=",   0xa,  0xa,  0x2600, 1}, /* 100 T_EQ */
{"=+",  0xa,  0xa,  0x2434, 1}, /* 101 P1_EQPLUS */
{"++",  0,    0xa,  0x2434, 1}, /* 102 P1_POSTINC */
{"=-",  0xa,  0xa,  0x2434, 1}, /* 103 P1_EQMINUS */
{"--",  0,    0xa,  0x2434, 1}, /* 104 P1_POSTDEC */
{"=*",  0xa,  0xa,  0x2430, 1}, /* 105 P1_EQMUL */
{"=/",  0xa,  0xa,  0x2430, 1}, /* 106 P1_EQDIV */
{"=%",  0xa,  0xa,  0x2420, 1}, /* 107 P1_EQMOD */
{"=>>", 0xa,  0xa,  0x2020, 1}, /* 108 P1_EQSHR */
{"=<<", 0xa,  0xa,  0x2020, 1}, /* 109 P1_EQSHL */
{"=&",  0xa,  0xa,  0x2420, 1}, /* 110 P1_EQAND */
{"=^",  0xa,  0xa,  0x2420, 1}, /* 111 P1_EQXOR */
{"=|",  0xa,  0xa,  0x2420, 1}, /* 112 P1_EQOR */
{",",   7,    2,    0x200,  7}, /* 113 T_COMMA */
{";",   7,    2,    0x200,  2}, /* 114 T_SEMICOLON */
{"",    0,    1,    0,      0}, /* 115 T_ID */
{"",    0,    0x11, 0,      0}, /* 116 T_ICONST */
{"",    0,    0x11, 0,      0}, /* 117 T_LCONST */
{"",    0,    0x11, 0,      0}, /* 118 T_SCONST */
{"",    0,    0x11, 0,      0}, /* 119 S_TYPE */
{"..",  0,    0,    0,      0}, /* 120 */
{")",   0,    0,    0x200,  7}, /* 121 */
{"$U",  0,    0,    0x200,  7}, /* 122 P1_COND */
{"$",   0,    2,    2,      7}, /* 123 */
{"->",  0,    0x12, 0x880,  2}, /* 124 P1_CONVERT */
{"@",   0,    2,    0x480,  7}, /* 125 */
{"",    0,    1,    0,      0}, /* 126 D_MEMBERID*/
{"",    0,    0x11, 0,      0}, /* 127 T_FCONST */


}; /* 9271 */