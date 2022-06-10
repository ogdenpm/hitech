/*
 *
 * The kwd.h file is part of the restored ZAS.EXE program
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
#define G_END      69 // ENDC and ENDIF
#define G_REG      70
#define G_CC       71
#define G_PSECT    72
#define G_FLOAT    73
#define T_END      74 // standard END
#define T_MLT      75
#define T_IN0      76
#define T_TSTIO    77
#define T_TST      78
#define T_OUT0     79
#define T_REPT     80
#define T_IRP      81
#define T_IRPC     82
#define T_ELSE     83
#define T_LOCAL    84
#define T_LINE     85
#define T_FILE     86
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

/* PSECT flags */
#define F_ABS       0x80
#define F_GLOBAL    0x10
#define F_PURE      0x20
#define F_OVRLD     0x40
#define F_LOCAL     0x800
#define F_RELOC     0x7000
#define F_SIZE      0x6000

/* Macro flags*/

/* rtype flags */
#define RT_ABS      0
#define RT_REL      0x10
#define RT_EXT      0x20

/* symbol flags */
#define S_NONPSECT  0
#define S_GLOBAL    0x10
#define S_PURE      0x20
#define S_UNNAMED   0x40
#define S_ABS       0x80
#define S_ABSPSECT  (S_UNNAMED | S_ABS)

#define S_PSECT     0x100
#define S_UNDEF     0x200
#define S_DEFINED   0x400

#define S_IRP       1
#define S_IRPC      2
#define S_REPT      4
#define S_MACROARG  0x1000
#define S_MLOCAL    0x2000
#define S_REPMASK   7

#define S_LINENO    4
#define S_FILNAM    5
#define S_EXTERN    6
#define S_PTYPEMASK 0xf0 // global, pure, overld and abs
#define S_STYPEMASK 0x1f // global and lineno, filnam, extern or size

/* tag flags */
#define TF_EXT      0x10
#define TF_REL      0x100
