/*
 *
 * The kwd.h file is part of the restored ZAS.COM program
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
typedef struct _kwd {
    char *name;
    int16_t id;
    int16_t flags;
} kwd_t;

#define G_SIMPLE   1
#define G_EDSIMPLE 2
#define G_ARITH8   3
#define G_INCDEC   4
#define T_IM       5
#define G_ROTATE   6
#define G_BIT      7
#define T_JP       8
#define T_JR       9
#define T_DJNZ     10
#define T_CALL     11
#define T_RET      12
#define T_RST      13
#define T_IN       14
#define T_OUT      15
#define G_PUSHPOP  16
#define T_EX       17
#define G_ADCSBC   18
#define T_ADD      19
#define T_LD       20
#define T_UPLUS    21
#define T_UMINUS   22
#define G_NOT      23
#define T_HIGH     24
#define T_LOW      25
#define T_RES      26
#define T_MARKER   27
#define T_PLUS     28
#define T_MINUS    29
#define T_MULT     30
#define T_DIV      31
#define T_MOD      32
#define T_SHR      33
#define T_SHL      34
#define G_AND      35
#define G_OR       36
#define T_XOR      37
#define G_EQ       38
#define G_GT       39
#define G_LT       40
#define T_UGT      41
#define T_ULT      42
#define T_LPAREN   43
#define T_RPAREN   44
#define G_FWD      46
#define G_BWD      47
#define T_DOLLAR   48
#define G_SYM      49
#define G_INT      50
#define G_STR      51
#define T_PSECT    52
#define T_GLOBAL   53
#define T_COMMA    54
#define T_DEFW     55
#define T_DEFL     56
#define T_DEFB     57
#define T_DEFM     58
#define T_DEFS     59
#define T_DEFF     60
#define T_EQU      61
#define T_ORG      62
#define T_EOL      64
#define T_COLON    65
#define T_MACRO    66
#define T_ENDM     67
#define T_COND     68
#define T_ENDC     69
#define G_REG      70
#define G_CC       71
#define G_PSECT    72
#define G_FLOAT    73
#define T_END      74
#define T_MLT      75
#define T_IN0      76
#define T_TSTIO    77
#define T_TST      78
#define T_OUT0     79
#define T_INDEXED  100
#define T_MEM      101
#define T_REGIND   102
#define T_IXIY     109

enum {
    R_B = 0,
    R_C,
    R_D,
    R_E,
    R_H,
    R_L,
    R_IHL,
    R_A,
    R_I = 0x10,
    R_R,
    R_BC = 0x20,
    R_DE = 0x22,
    R_HL = 0x24,
    R_SP = 0x26,
    R_AF,
    R_AFQ,
    R_IX = 0xdd,
    R_IY = 0xfd
};

#define F_GLOBAL 020
#define F_PURE   040
#define F_OVRLD  0100
#define F_ABS    0200
#define F_BIGSET 0400
#define F_PSECT  0400
#define F_BPAGE  01000
#define F_LOCAL  04000
#define F_ARGS   0x1000
