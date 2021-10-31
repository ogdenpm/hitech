/*
 * HI-TECH Software Optimization Program.
 *
 * File optim.c created 14.08.2021, last modified 16.10.2021.
 *
 * The C source code was RESTORED by disassembling the original executable
 * file OPTIM.COM from the Hi-Tech v3.09 compiler.
 *
 * This file with some warning messages is compiled by Hi-Tech C compiler
 * v3.09 and the resulting executable file performs all the functions
 * provided. To compile, use the following command:
 *
 *    cc -o optim.c
 *
 * The created executable file almost completely matches the original image.
 *
 * The OPTIM utility tries to perform 18 types of optimizations.
 *
 * OPTIM has 5 options not described in the manual:
 *    -l - Prints additional information on each pass;
 *    -n - Prints statistics: number of iterations and number of
 *         optimization types performed;
 *    -r -
 *    -f - The action is not clear;
 *    -s - Unbuffered stdout;
 *
 * Options are unknown to ordinary users and are not used when compiling a
 * program using optimization. These options are probably intended for
 * compiler support to find errors while performing optimization.
 *
 * Not a commercial goal of this laborious work is to popularize
 * among potential fans of 8-bit computers the old HI-TECH C compiler
 * V3.09 (HI-TECH Software) and extend its life, outside of the
 * CP/M environment (Digital Research, Inc), for full operation in a
 * Unix-like operating system UZI-180 without using the CP/M emulator.
 *
 *	Andrey Nikitin 16.10.2021
 */
#include "stdio.h"
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#if defined(__STDC__) || defined(__STDC_VERSION__)
#include <stdarg.h>
#include <stdbool.h>
#endif

#ifndef INT_MAX
#define INT_MAX 32767 /* max for int */
#endif

#define P_CCF              0x3F /*   Complement Carry Flag */
#define P_CPL              0x2F /*   Complement */
#define P_DI               0xF3 /*   Disable Interrupts */
#define P_EI               0xFB /*   Enable Interrupts */
#define P_EXX              0xD9 /*   Exchange */
#define P_NEG              0x44 /*   Negates the accumulator */
#define P_NOP              0    /*   No operation */
#define P_RLA              0x17 /*   rla */
#define P_RLCA             7    /*   rlca */
#define P_RRA              0x1F /*   rra */
#define P_RRCA             0xF  /*   rrca */
#define P_SCF              0x37 /*   Set Carry Flag */

#define P_LDIR             0xB0 /*   Load, Inc., Repeat */
#define P_RLD              0x6F /*   rld */
#define P_RRD              0x67 /*   rrd */

#define P_AND              0xA0 /*   Logical AND */
#define P_CP               0xB8 /*   Compare */
#define P_OR               0xB0 /*   Logical inclusive OR */
#define P_SUB              0x90 /*   sub */
#define P_XOR              0xA8 /*   xor */

#define P_DEC              5 /*   Decrement */
#define P_INC              4 /*   Increment */

#define P_RL               0x10 /*   rl */
#define P_RLC              0    /*   rlc */
#define P_RR               0x18 /*   rr */
#define P_RRC              8    /*   rrc */
#define P_SLA              0x20 /*   sla */
#define P_SLL              0x20 /*   sll */
#define P_SRA              0x28 /*   sra */
#define P_SRL              0x38 /*   srl */

#define P_BIT              0x40 /*   Tests if the specified bit is set */
#define P_RESB             0x80 /*   Reset bit */
#define P_SETB             0xC0 /*   Set bit */

#define P_JP               0    /* */
#define P_JR               0x18 /* */
#define P_DJNZ             0x10 /* */
#define P_CALL             0    /* */
#define P_RST              0xC7 /* */
#define P_POP              0xC1 /*   pop */
#define P_PUSH             0xC5 /*   push */
#define P_EX               0    /* */
#define P_ADC              0x88 /*   Add */
#define P_SBC              0x98 /*   Subtract */
#define P_CADD             0x80 /* */
#define P_LD               0    /* */
#define P_NOT              8    /* */
#define P_HI               8    /* */
#define P_LOW              8    /* */
#define P_RES              7    /* */
#define P_ADD              5    /* */
#define P_SUB1             5    /* */
#define P_MUL              6    /* */
#define P_DIV              6    /* */
#define P_MOD              6    /* */
#define P_SHR              6    /* */
#define P_SHL              6    /* */
#define P_AND1             4    /* */
#define P_OR1              3    /* */
#define P_XOR1             3    /* */
#define P_EQU              2    /* */
#define P_LE               2    /* */
#define P_GE               2    /* */
#define P_OPAR             9    /* */
#define P_CPAR             1    /* */
#define P_PSCT             0    /* */
#define P_GLB              0    /* */
#define P_COMM             0    /* */
#define P_DEFW             0    /* */
#define P_DEFL             0    /* */
#define P_DEFB             0    /* */
#define P_DEFM             0    /* */
#define P_DEFS             0    /* */
#define P_DEFF             0    /* */
#define P_OEQU             0    /* */
#define P_COLN             0    /* */
#define P_HALT             0x76

/****************************************************************
 *	Token definitions
 *
 *	Symbol	  Code	Description
 */
#define T_ONEBYTE          1    /* one byte instruction: */
#define T_TWOBYTE          2    /* two byte instruction: */
#define T_3                3    /* Unknown: */
#define T_INCDEC           4    /* Unknown: */
#define T_5                5    /* Unknown */
#define T_6                6    /* Unknown: */
#define T_BIT              7    /* Bit operations */
#define T_JP               8    /* Absolute jumps to address */
#define T_JR               9    /* Relative jumps to address */
#define T_DJNZ             0xA  /* Dec., Jump Non-Zero */
#define T_CALL             0xB  /* Call */
#define T_RET              0xC  /* Uunknown */
#define T_RST              0xD  /* Restart Commands */
#define T_0xE              0xE  /* Unknown */
#define T_0xF              0xF  /* Unknown */
#define T_STK              0x10 /* Stack operation: */
#define T_EX               0x11 /* Exchange */
#define T_CARR             0x12 /* With Carry: */
#define T_CADD             0x13 /* Add */
#define T_LD               0x14 /* Load */

#define T_UPLUS            0x15 /* Unknown */
#define T_UMINUS           0x16 /* Unknown */

#define T_NOT              0x17 /* Bitwise complement */
#define T_HI               0x18 /* Hi byte of operand */
#define T_LOW              0x19 /* Low byte of operand */
#define T_RES              0x1A /* .res. */
#define T_MARKER           0x1B /* Unknown */
#define T_PLUS             0x1C /* Addition */
#define T_MINUS            0x1D /* Subtraction */
#define T_MUL              0x1E /* Multiplication */
#define T_DIV              0x1F /* Divison */
#define T_MOD              0x20 /* Modulus */
#define T_SHR              0x21 /* Shift right */
#define T_SHL              0x22 /* Shift left */
#define T_AND              0x23 /* Bitwise AND */
#define T_OR               0x24 /* Bitwise or */
#define T_XOR              0x25 /* Exclusive or */
#define T_EQ               0x26 /* Equality */
#define T_LE               0x27 /* Signed greater than */
#define T_GE               0x28 /* Signed less than */
#define T_ULE              0x29 /* Unigned greater than */
#define T_UGE              0x2A /* Unigned less than */
#define T_OPAR             0x2B /* Open parenthesis */
#define T_CPAR             0x2C /* Closing parenthesis */

#define T_0x2D             0x2D /* Unknown */
#define T_JBWD             0x2E /* Local jump backwards */
#define T_JFWD             0x2F /* Local jump forwards */
#define T_0x30             0x30 /* Unknown */

#define T_SYMBOL           0x31 /* Symbol		aaa */
#define T_CONST            0x32 /* Constants		123 */
#define T_STRING           0x33 /* String of characters 'aaa' */

#define T_PSCT             0x34 /* Psect */
#define T_GLB              0x35 /* Global */
#define T_COMM             0x36 /* Comma */
#define T_DEFW             0x37 /* Definition word */
#define T_DEFL             0x38 /* Definition label */
#define T_DEFB             0x39 /* Definition byte */
#define T_DEFM             0x3A /* Definition a message */
#define T_DEFS             0x3B /* Memory reservation */
#define T_DEFF             0x3C /* Definition real */
#define T_EQU              0x3D /* Set value of symbol */
#define T_0x3E             0x3E /* Unknown */
#define T_0x3F             0x3F /* Unknown */
#define T_EOL              0x40 /* end of line		';' */
#define T_COLN             0x41 /* Label separator	':' */

#define T_0x42             0x42 /* Unknown */
#define T_0x43             0x43 /* Unknown */
#define T_0x44             0x44 /* Unknown */
#define T_0x45             0x45 /* Unknown */

#define T_REG              0x46 /* Registers */
#define T_COND             0x47 /* Condition code: */

#define T_INDEXED          0x64 /* (IX / IY) */
#define T_ADDRREF          0x65 /* (addr expression) */
#define T_REGREF           0x66 /* (reg) */

/****************************************************************
 *	Used macros
 ****************************************************************/

#define bittst(var, bitno) ((var)&1 << (bitno))

/****************************************************************
 *	Assigned type abbreviations
 ****************************************************************/
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned
#endif

#ifndef ulong
#define ulong unsigned long
#endif

#ifndef bool
#define bool char /* int may be better */
#define true 1
#define false 0
#endif

/****************************************************************
 *	Definitions of structures
 *
 * Unfortunately, the members of the structures have been assigned
 * uninformative names. Perhaps there are extra structures. The
 * links between structures and are wrong.
 ****************************************************************/

typedef union {
    int *p_int;
    char *p_char;
    struct _term *pTerm;
    struct _sym *pSym;
    struct _inst *pInst;
    struct _operand *pOperand;
    int i;
    unsigned int ui;
} YYSTYPE;

typedef struct _sym {
    char *name;  /* 01	s->str */
    YYSTYPE val; /* 23	s->i_2 */
} sym_t;

typedef struct _term {
    int ival; /* 01	s->str */
    union {
        sym_t *pSym; /* 23	s->i_2 */
        struct _operand *pOperand;
    } u;
} term_t;

typedef struct {
    int type; /* 01	s->str */
    int prec; /* 23	s->i_2 */
} op_t;

typedef struct {
    char *str;
    int type;
    int aux;
} operator_t;

typedef struct _list {
    struct _list *pNext;
} list_t;

typedef struct _operand {
    uchar type;
    uchar aux;
    term_t val;
} operand_t;

typedef struct _inst {
    char *str;           /* 01	s->str */
    uchar type;          /* 2	s->i_2 */
    int aux;             /* 34	s->aux */
    struct _inst *pNext; /* 56	s->i_5 */
    struct _inst *pAlt;  /* 78	s->i_7 */
    union {
        struct {
            operand_t *lhs; /* used for operands */
            operand_t *rhs; /* */
        } o;
        struct { /* used for symbols */
            sym_t *pSym;
            int symId;
        } s;
    } u;
} inst_t;

/*
 * to avoid lots of u.o. and u.s. used some #defines to simpilfy
 */
#define iLhs      u.o.lhs /* used in inst */
#define iRhs      u.o.rhs
#define iPSym     u.s.pSym
#define iSymId    u.s.symId
#define tPSym     u.pSym /* used in term */
#define tPOperand u.pOperand
#define oPSym     val.tPSym /* used in operand */
#define oPOperand val.tPOperand
#define oIVal     val.ival

/****************************************************************
 *	Descriptions of uninitialized variables and arrays
 ****************************************************************/
char yyline[80];            /* 6f00	Working buffer */
int len_inbuf;              /* 6f50	Length string in input buffer */
char *ptr_inbuf;            /* 6f52	Pointer to input buffer */
int yytype;                 /* 6f54 */
char inp_buf[80];           /* 6f56	Input buffer */
uchar key_l;                /* 6fa6	Prints additional information on each pass */
uchar key_n;                /* 6fa7	Prints statistics */
uchar key_f;                /* 6fa8	The action is not clear */
uchar key_s;                /* 6fa9	Key_s = 1 Unbuffered stdout */
int num_warn;               /* 6faa	Number of errors */
uchar key_r;                /* 6fac */
operator_t *tableBase;      /* 6fad	Pointer to operators[] */
char *yytext;               /* 6faf	ok */
YYSTYPE yylval;             /* 6fb1	Contains different types of data */
int symbolId;               /* 6fb3	??? used only in sub_0ca2 */
sym_t *gPs;                 /* 6fb5	??? */
inst_t *gPi;                /* 6fb7 */
int word_6fb9;              /* 6fb9	??? */
bool hasChanged;            /* 6fbb */
char usesIXorIY;            /* 6fbc */
int optimiseCounters[0x12]; /* 6fbd	Array of counters types of optimizations */
/*		     6fbd //  0 Redundant labels */
/*		     6fbf //  1 Jumps to jumps */
/*		     6fc1 //  2 Stack adjustments */
/*		     6fc3 //  3 Temporary labels */
/*		     6fc5 //  4 Unref'ed labels */
/*		     6fc7 //  5 Unreachable code */
/*		     6fc9 //  6 Jumps to .+1 */
/*		     6fcb //  7 Skips over jumps */
/*		     6fcd //  8 Common code seq's */
/*		     6fcf //  9 Redundant exx's */
/*		     6fd1 // 10 Ex (sp),hl's used */
/*		     6fd3 // 11 Redundant operations */
/*		     6fd5 // 12 Redundant loads/stores */
/*		     6fd7 // 13 Simplified addresses */
/*		     6fd9 // 14 Xor a's used */
/*		     6fdb // 15 Redundant ex de,hl's */
/*		     6fdd // 16 Code motions */
/*		     6fdf // 17 Loops inverted */

list_t *freeOperandList; /* 6fe1	struct size 6 */
inst_t *word_6fe3;       /* 6fe3 */
inst_t *word_6fe5;       /* 6fe5 */
list_t *freeInstList;    /* 6fe7 */
char psect;              /* 6fe9	Program section */
int cur_psect;           /* 6fea	Current program section */
int expectCond;          /* 6fec	ok */
inst_t *word_6fee;       /* 6fee */
int tokType;             /* 6ff0	Token value */
inst_t *word_6ff2;       /* 6ff2 */
/* static term_t termTmp; // 6ff4	[4] */
inst_t *root;            /* 6ff8 */
int cntOperand;          /* 6ffa	??? used only in sub_39a3 */
inst_t *word_6ffc;       /* 6ffc */
jmp_buf jmpbuf;          /* 6ffe	[4] */
                         /* 7002	[4] */
int word_7006;           /* 7006 */
operand_t regValues[19]; /* 7008 */
char *alloct;            /* 707a	ok */
char *name_fun;          /* 707c	Function name */
                         /* 707e */
                         /* 707f */
list_t *freeSymbolList;  /* 7080 */
char *allocs;            /* 7082	ok */
char *programBreak;      /* 7084	ok */
/* char       * arry_7086[311];	//7086	[622] */
/* 72f4 */
int asdf;
/****************************************************************
 *	Initialized variables
 ****************************************************************/

#define _Z 0  /* 0000 0000 */
#define _U 1  /* 0000 0001 */
#define _L 2  /* 0000 0010 */
#define _D 4  /* 0000 0100 */
#define _H 8  /* 0000 1000 */
#define _S 16 /* 0001 0000 */

/*
 *	Definitions of valid characters and their types in oprtmizer
 */
char ccClass[] = { /* 62cc */
    _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _S,      _S,      _Z, _Z, _S, _S, _Z, _Z,
    _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z, _Z, _Z, _Z, _Z, _Z,
    _S,      _Z,      _Z,      _Z,      _L,      _Z,      _Z,      _Z,      _Z,      _Z,      _Z, _Z, _Z, _Z, _Z, _Z,
    _D | _H, _D | _H, _D | _H, _D | _H, _D | _H, _D | _H, _D | _H, _D | _H, _D | _H, _D | _H, _Z, _Z, _Z, _Z, _Z, _L,
    _Z,      _U | _H, _U | _H, _U | _H, _U | _H, _U | _H, _U | _H, _U,      _U,      _U,      _U, _U, _U, _U, _U, _U,
    _U,      _U,      _U,      _U,      _U,      _U,      _U,      _U,      _U,      _U,      _U, _Z, _Z, _Z, _Z, _L,
    _Z,      _L | _H, _L | _H, _L | _H, _L | _H, _L | _H, _L | _H, _L,      _L,      _L,      _L, _L, _L, _L, _L, _L,
    _L,      _L,      _L,      _L,      _L,      _L,      _L,      _L,      _L,      _L,      _L, _Z, _Z, _Z, _Z, _Z
};

#define ISALPHA(c)  (ccClass[c] & (_U | _L))
#define ISUPPER(c)  (ccClass[c] & _U)
#define ISDIGIT(c)  (ccClass[c] & _D)
#define ISXDIGIT(c) (ccClass[c] & _H)
#define ISSPACE(c)  (ccClass[c] & _S)
#define ISALNUM(c)  (ccClass[c] & (_U | _L | _D))

/*
 * Determining the condition number
 * (its offset in the conditions[offset] table) */

#define COND_NZ     1 /* 	anz, fnz, lnz,	nz */
#define COND_Z      2 /* 	az,  fz,  lz,	z */
#define COND_LGE    3 /* 	          lge,	nc */
#define COND_LLT    4 /* 	          llt */
/*#define COND_PO	5 // 			po */
/*#define COND_PE	6 // 			pe */
#define COND_GE     7 /* 	age, fge,       p */
#define COND_LT     8 /* 	alt, flt,       m */

char *conditions[] = {
    0,    /* 63db	 0 */
    "nz", /* 63dd	 1 COND_NZ */
    "z",  /* 63df	 2 COND_Z */
    "nc", /* 63e1	 3 COND_LGE */
    "c",  /* 63e3	 4 COND_LLT */
    "po", /* 63e5	 5 COND_PO */
    "pe", /* 63e7	 6 COND_PE */
    "p",  /* 63e9	 7 COND_GE */
    "m"   /* 63eb	 8 COND_LT */
};

/*
 *	Determining register number
 *	(its offset in regs[offset] table)
 */
#define REG_B   0x00
#define REG_C   0x01
#define REG_D   0x02
#define REG_E   0x03
#define REG_H   0x04
#define REG_L   0x05
#define REG_F   0x06
#define REG_A   0x07
#define REG_I   0x08
#define REG_R   0x09 /* Memory Refresh Register */
#define REG_BC  0x0A
#define REG_DE  0x0B
#define REG_HL  0x0C
#define REG_SP  0x0D
#define REG_AF  0x0E
#define REG_AF1 0x0F
#define REG_IX  0x10
#define REG_IY  0x11

char *regs[] = {
    "b",   /* 63ed  0 REG_B */
    "c",   /* 63ef  1 REG_C */
    "d",   /* 63f1  2 REG_D */
    "e",   /* 63f3  3 REG_E */
    "h",   /* 63f5  4 REG_H */
    "l",   /* 63f7  5 REG_L */
    "",    /* 63f9  6 */
    "a",   /* 63fb  7 REG_A */
    "i",   /* 63fd  8 REG_I */
    "r",   /* 63ff  9 REG_R	 Memory Refresh Register */
    "bc",  /* 6401 10 REG_BC */
    "de",  /* 6403 11 REG_DE */
    "hl",  /* 6405 12 REG_HL */
    "sp",  /* 6407 13 REG_SP */
    "af",  /* 6409 14 REG_AF */
    "af'", /* 640b 15 REG_AF1 */
    "ix",  /* 640d 16 REG_IX */
    "iy"   /* 640f 17 REG_IY */
};

operator_t operators[] = {
    /* 6411 */
    { "&", T_AND, P_AND1 },        /*   0   0	Bitwise AND */
    { "(", T_OPAR, P_OPAR },       /*   1   1	Open parenthesis */
    { ")", T_CPAR, P_CPAR },       /*   2   2	Closing parenthesis */
    { "*", T_MUL, P_MUL },         /*   3   3	Multiplication */
    { "+", T_PLUS, P_ADD },        /*   4   4	Addition */
    { ",", T_COMM, P_COMM },       /*   5   5	Comma */
    { "-", T_MINUS, P_SUB1 },      /*   6   6	Subtraction */
    { ".and.", T_AND, P_AND1 },    /*   7   7	Bitwise AND */
    { ".high.", T_HI, P_HI },      /*   8   8	Hi byte of operand */
    { ".low.", T_LOW, P_LOW },     /*   9   9	Low byte of operand */
    { ".mod.", T_MOD, P_MOD },     /*  10   a	Modulus */
    { ".not.", T_NOT, P_NOT },     /*  11   b	Bitwise complement */
    { ".or.", T_OR, P_OR1 },       /*  12   c	Bitwise or */
    { ".res.", T_RES, P_RES },     /*  13   d */
    { ".shl.", T_SHL, P_SHL },     /*  14   e	Shift left */
    { ".shr.", T_SHR, P_SHR },     /*  15   f	Shift right */
    { ".xor.", T_XOR, P_XOR1 },    /*  16   10	Exclusive or */
    { "/", T_DIV, P_DIV },         /*  17   11	Divison */
    { ":", T_COLN, P_COLN },       /*  18   12	Label separator */
    { "<", T_GE, P_GE },           /*  19   13	Signed less than */
    { "=", T_EQ, P_EQU },          /*  20   14	Equality */
    { ">", T_LE, P_LE },           /*  21   15	Signed greater than */
    { "\\", T_NOT, P_NOT },        /*  22   16	Bitwise complement */
    { "^", T_OR, P_OR1 },          /*  23   17	Bitwise or */
    { "a", T_REG, REG_A },         /*  24   18	Register */
    { "adc", T_CARR, P_ADC },      /*  25   19 Add with Carry */
    { "add", T_CADD, P_CADD },     /*  26   1a	Add */
    { "af", T_REG, REG_AF },       /*  27   1b	Register */
    { "af'", T_REG, REG_AF1 },     /*  28   1c	Register */
    { "age", T_COND, COND_GE },    /*  29   1d	Condition code Arithmetic greater or equal */
    { "alt", T_COND, COND_LT },    /*  30   1e	Condition code Arithmetic less than */
    { "and", T_3, P_AND },         /*  31   1f Logical AND */
    { "anz", T_COND, COND_NZ },    /*  32   20	Condition code */
    { "az", T_COND, COND_Z },      /*  33   21	Condition code */
    { "b", T_REG, REG_B },         /*  34   22	Register b */
    { "bc", T_REG, REG_BC },       /*  35   23	Register bc */
    { "bit", T_BIT, P_BIT },       /*  36   24 Tests if the specified bit is set */
    { "c", T_REG, REG_C },         /*  37   25	Register c */
    { "call", T_CALL, P_CALL },    /*  38   26	Call */
    { "ccf", T_ONEBYTE, P_CCF },   /*  39   27 Complement Carry Flag */
    { "cp", T_3, P_CP },           /*  40   28 Compare */
    { "cpl", T_ONEBYTE, P_CPL },   /*  41   29 Complement */
    { "d", T_REG, REG_D },         /*  42   2a	Register d */
    { "de", T_REG, REG_DE },       /*  43   2b	Register de */
    { "dec", T_INCDEC, P_DEC },    /*  44   2c Decrement */
    { "defb", T_DEFB, P_DEFB },    /*  45   2d	Definition byte */
    { "deff", T_DEFF, P_DEFF },    /*  46   2e	Definition real */
    { "defl", T_DEFL, P_DEFL },    /*  47   2f	Definition label */
    { "defm", T_DEFM, P_DEFM },    /*  48   30	Definition a message */
    { "defs", T_DEFS, P_DEFS },    /*  49   31	memory reservation */
    { "defw", T_DEFW, P_DEFW },    /*  50   32	Definition word */
    { "di", T_ONEBYTE, P_DI },     /*  51   33 Disable Interrupts */
    { "djnz", T_DJNZ, P_DJNZ },    /*  52   34	Dec., Jump Non-Zero */
    { "e", T_REG, REG_E },         /*  53   35	Register */
    { "ei", T_ONEBYTE, P_EI },     /*  54   36 Enable Interrupts */
    { "equ", T_EQU, P_OEQU },      /*  55   37	set value of symbol */
    { "ex", T_EX, P_EX },          /*  56   38	Exchange */
    { "exx", T_ONEBYTE, P_EXX },   /*  57   39 Exchange */
    { "fge", T_COND, COND_GE },    /*  58   3a	Condition code ge */
    { "flt", T_COND, COND_LT },    /*  59   3b	Condition code lt */
    { "fnz", T_COND, COND_NZ },    /*  60   3c	Condition code nz */
    { "fz", T_COND, COND_Z },      /*  61   3d	Condition code z */
    { "global", T_GLB, P_GLB },    /*  62   3e	Global */
    { "h", T_REG, REG_H },         /*  63   3f	Register h */
    { "hl", T_REG, REG_HL },       /*  64   40	Register hl */
    { "inc", T_INCDEC, P_INC },    /*  65   41 Increment */
    { "ix", T_REG, REG_IX },       /*  66   42	Register ix */
    { "iy", T_REG, REG_IY },       /*  67   43	Register iy */
    { "jp", T_JP, P_JP },          /*  68   44	Absolute jumps to the address */
    { "jr", T_JR, P_JR },          /*  69   45	Relative jumps to the address */
    { "l", T_REG, REG_L },         /*  70   46	Register l */
    { "ld", T_LD, P_LD },          /*  71   47	Load */
    { "ldir", T_TWOBYTE, P_LDIR }, /*  72   48 Load, Inc., Repeat */
    { "lge", T_COND, COND_LGE },   /*  73   49	Condition code Logical greater or equal */
    { "llt", T_COND, COND_LLT },   /*  74   4a	Condition code Logical less than */
    { "lnz", T_COND, COND_NZ },    /*  75   4b	Condition code nz */
    { "lz", T_COND, COND_Z },      /*  76   4c	Condition code z */
    { "m", T_COND, COND_LT },      /*  77   4d	Condition code Arithmetic less than */
    { "nc", T_COND, COND_LGE },    /*  78   4e	Condition code lge */
    { "neg", T_ONEBYTE, P_NEG },   /*  79   4f Negates the accumulator */
    { "nop", T_ONEBYTE, P_NOP },   /*  80   50 No operation */
    { "nz", T_COND, COND_NZ },     /*  81   51	Condition code */
    { "or", T_3, P_OR },           /*  82   52 Logical inclusive OR */
    { "p", T_COND, COND_GE },      /*  83   53	Condition code Arithmetic greater or equal */
    { "pop", T_STK, P_POP },       /*  84   54	Stack operation pop */
    { "psect", T_PSCT, P_PSCT },   /*  85   55	Psect */
    { "push", T_STK, P_PUSH },     /*  86   56	Stack operation push */
    { "r", T_REG, REG_R },         /*  87   57	Register r */
    { "res", T_BIT, P_RESB },      /*  88   58 Reset bit */
    { "rl", T_6, P_RL },           /*  89   59 06 */
    { "rla", T_ONEBYTE, P_RLA },   /*  90   5a 01 */
    { "rlc", T_6, P_RLC },         /*  91   5b 06 */
    { "rlca", T_ONEBYTE, P_RLCA }, /*  92   5c 01 */
    { "rld", T_TWOBYTE, P_RLD },   /*  93   5d 02 */
    { "rr", T_6, P_RR },           /*  94   5e 06 */
    { "rra", T_ONEBYTE, P_RRA },   /*  95   5f 01 */
    { "rrc", T_6, P_RRC },         /*  96   60 06 */
    { "rrca", T_ONEBYTE, P_RRCA }, /*  97   61 01 */
    { "rrd", T_TWOBYTE, P_RRD },   /*  98   62 02 */
    { "rst", T_RST, P_RST },       /*  99   63	Restart Commands */
    { "sbc", T_CARR, P_SBC },      /* 100   64 Subtract with Carry */
    { "scf", T_ONEBYTE, P_SCF },   /* 101   65 Set Carry Flag */
    { "set", T_BIT, P_SETB },      /* 102   66 Set bit */
    { "sla", T_6, P_SLA },         /* 103   67 06 */
    { "sll", T_6, P_SLL },         /* 104   68 06 */
    { "sp", T_REG, REG_SP },       /* 105   69	Register sp */
    { "sra", T_6, P_SRA },         /* 106   6a 06 */
    { "srl", T_6, P_SRL },         /* 107   6b 06 */
    { "sub", T_3, P_SUB },         /* 108   6c 03 */
    { "xor", T_3, P_XOR },         /* 109   6d 03 */
    { "z", T_COND, COND_Z }        /* 110   6e	Condition code */
};

#define NOPERATORS (sizeof(operators) / sizeof(operators[0]))

char *opt_msg[] = {
    /* 68a3 */
    "Redundant labels",       /*  0	 0 */
    "Jumps to jumps",         /*  1	 1 */
    "Stack adjustments",      /*  2	 2 */
    "Temporary labels",       /*  3	 3 */
    "Unref'ed labels",        /*  4	 4 */
    "Unreachable code",       /*  5	 5 */
    "Jumps to .+1",           /*  6	 6 */
    "Skips over jumps",       /*  7	 7 */
    "Common code seq's",      /*  8	 8 */
    "Redundant exx's",        /*  9	 9 */
    "Ex (sp),hl's used",      /* 10	 a */
    "Redundant operations",   /* 11	 b */
    "Redundant loads/stores", /* 12	 c */
    "Simplified addresses",   /* 13	 d */
    "Xor a's used",           /* 14	 e */
    "Redundant ex de,hl's",   /* 15	 f */
    "Code motions",           /* 16	10 */
    "Loops inverted"          /* 17	11 */
};

#define NOPTIM (sizeof(opt_msg) / sizeof(opt_msg[0]))

int ccSwap[] = { /* 68c7 */
    0, 2, 1, 4, 3, 6, 5, 8, 7
};

/*
 *	psect definitions
 */
#define TEXT   1
#define DATA   2
#define BSS    3
#define SWDATA 4

char *psectNames[] = {
    /* 6a59 */
    "",     /*  0 */
    "text", /*  1 */
    "data", /*  2 */
    "bss",  /*  3 */
    "data"  /*  4 */
};

struct {
    char c0;
    char c1;
} l6c50h[] = {
    { 0, 0 }, /* 6c50	 0 */
    { 0, 0 }, /* 6c52	 1 */
    { 0, 0 }, /* 6c54	 2 */
    { 0, 0 }, /* 6c56	 3 */
    { 0, 0 }, /* 6c58	 4 */
    { 0, 0 }, /* 6c5a	 5 */
    { 0, 0 }, /* 6c5c	 6 */
    { 0, 0 }, /* 6c5e	 7 */
    { 0, 0 }, /* 6c60	 8 */
    { 0, 0 }, /* 6c62	 9 */
    { 0, 1 }, /* 6c64	10 */
    { 2, 3 }, /* 6c66	11 */
    { 4, 5 }, /* 6c68	12 */
};

struct {
    operand_t *lhs;
    operand_t *rhs;
} arry_6c6a[] = {
    /*		;6c6a */
    { &regValues[10], NULL },         /* 0x0744 0x0000	;6c6a	  0 */
    { &regValues[10], NULL },         /* 0x7044 0x0000	;6c6e	  1 */
    { &regValues[11], NULL },         /* 0x704a 0x0000	;6c72	  2 */
    { &regValues[11], NULL },         /* 0x704a 0x0000	;6c76	  3 */
    { &regValues[12], NULL },         /* 0x7050 0x0000	;6c7a	  4 */
    { &regValues[12], NULL },         /* 0x7050 0x0000	;6c7e	  5 */
    { &regValues[14], NULL },         /* 0x705c 0x0000	;6c82	  6 */
    { &regValues[14], NULL },         /* 0x705c 0x0000	;6c86	  7 */
    { NULL, NULL },                   /* 0x0000 0x0000	;6c8a	  8 */
    { NULL, NULL },                   /* 0x0000 0x0000	;6c8e	  9 */
    { &regValues[0], &regValues[0] }, /* 0x7008 0x700e	;6c92	 10 */
    { &regValues[2], &regValues[3] }, /* 0x7014 0x701a	;6c96	 11 */
    { &regValues[4], &regValues[5] }, /* 0x7020 0x7026	;6c9a	 12 */
    { NULL, NULL },                   /* 0x0000 0x0000	;6c9e	 13 */
    { &regValues[7], &regValues[6] }, /* 0x7032 0x702c	;6ca2	 14 */
    { NULL, NULL },                   /* 0x0000 0x0000	;6ca6	 15 */
    { NULL, NULL },                   /* 0x0000 0x0000	;6caa	 16 */
    { NULL, NULL }                    /* 0x0000 0x0000	;6cae	 17 */
};

int regTestMasks[] = {
    0x01, /* 6cb2  0 */
    0x02, /* 6cb4  1 */
    0x04, /* 6cb6  2 */
    0x08, /* 6cb8  3 */
    0x10, /* 6cba  4 */
    0x20, /* 6cbc  5 */
    0x40, /* 6cbe  6 */
    0x80, /* 6cc0  7 */
    0x00, /* 6cc2  8 */
    0x00, /* 6cc4  9 */
    0x03, /* 6cc6 10 */
    0x0C  /* 6cc8 11 */
};

int arry_6cca[] = {
    0x30,  /* 6cca 0 */
    0x00,  /* 6ccc 1 */
    0xC0,  /* 6cce 2 */
    0x00,  /* 6cd0 3 */
    0x100, /* 6cd2 4 */
    0x200, /* 6cd4 5 */
};

/* common code sequences */
#define PEEKCH() (len_inbuf > 0 ? *ptr_inbuf : '\n')
#define GETCH()  (--len_inbuf >= 0 ? *ptr_inbuf++ : get_line())

/****************************************************************
 * Prototype functions are located in sequence of being in
 * original binary image of OPTIM.COM
 *
 * ok++ - Full binary compatibility with code in original file;
 * ok+  - Code generated during compilation differs slightly,
 *        but is logically correct;
 ****************************************************************/
int strtoi(char *fmt, int p2); /*  1 sub_013d ok++ */
char *ptr_token();             /*  2 sub-020f ok++ */
int const_value();             /*  3 sub_0289 ok+ */
int get_token();               /*  4 sub_03c7 ok+ */
int get_line();                /*  5 sub_0758 ok+ */
void clr_len_inbuf();          /*  6 sub_07aa ok++ */
int main(int, char **);        /*  7 sub_07b1 ok+ */
#if defined(__STDC__) || defined(__STDC_VERSION__)
void pr_error(char *fmt, ...);
void pr_warning(char *fmt, ...);
void pr_message(char *fmt, va_list args);
#else
void pr_error();   /*  8 sub_0941 ok++ */
void pr_warning(); /*  9 sub_096f ok++ */
void pr_message(); /* 10 sub_0994 ok++ */
#endif
int find_token(char *, operator_t *, int);   /* 11 sub_09d0 ok++ */
int num_token(char *);                       /* 12 sub_0a97 ok++ */
void pr_token(inst_t *);                     /* 13 sub_0ab2 ok++ */
operand_t *allocOperand();                   /* 16 sub_0ba7 ok++ */
inst_t *allocInst(inst_t *);                 /* 17 sub_0be2 ok++ */
inst_t *allocSymbol(inst_t *);               /* 18 sub_0ca2 ok++ */
void optimise();                             /* 19 sub_0ce4 ok++ */
void chkIXYUsage();                          /* 20 sub_0e67 ok++ */
void sub_0ed1();                             /* 21 sub_0ed1 ok++ */
bool sub_1071(inst_t *);                     /* 22 sub_1071 ok++ */
void sub_122f();                             /* 23 sub_122f		-- */
bool sub_1369(operand_t *);                  /* 24 sub_1369 ok++ */
void removeInstruction(inst_t *);            /* 25 sub_1397 ok++ */
inst_t *getNextRealInst(inst_t *);           /* 26 sub_140b ok++ */
bool operandsSame(operand_t *, operand_t *); /* 27 sub_142f ok++ */
bool instructionsSame(inst_t *, inst_t *);   /* 28 sub_14ac ok++ */
void removeLabelRef(sym_t *);                /* 29 sub_153d ok++ */
void sub_15ad();                             /* 30 sub_15ad ok++ */
bool sub_1795();                             /* 31 sub_1795 ok++ */
bool sub_1aec();                             /* 32 sub_1aec ok++ */
bool sub_1b86();                             /* 33 sub_1b86 ok++ */
bool sub_1c67();                             /* 34 sub_1c67 ok++ */
bool sub_1d94();                             /* 35 sub_1d94 ok++ */

void sub_1ec1(); /* 36 sub_1ec1 */
bool sub_23c1(); /* 37 sub_23c1 */
bool sub_24c0(); /* 38 sub_24c0 ok++ */
bool sub_29c3(); /* 39 sub_29c3 Problem */
bool sub_2bdb(); /* 40 sub_2bdb */
bool sub_2d3b(); /* 41 sub_2d3b */
bool sub_2ef8(); /* 42 sub_2ef8 ok++ */
bool sub_3053(); /* 42asub_3053 strange code */

void swapHLDE();                        /* 43 sub_31ee ok++ */
void pr_psect(int psect);               /* 44 sub_328a ok++ */
int num_psect(char *);                  /* 45 sub_32bf ok++ */
term_t *evalExpr();                     /* 46 sub_3313 ok++ */
void exp_err();                         /* 47 sub_3595 ok++ */
void uconv(int, term_t *);              /* 48 sub_359e ok+ */
void bconv(int, term_t *, term_t *);    /* 49 sub_3630 ok++ */
void rel_err();                         /* 50 sub_384d ok++ */
operand_t *evalOperand();               /* 51 sub_3856 ok+ */
void oper_err();                        /* 52 sub_398e ok++ */
void getOperands(inst_t *);             /* 53 sub_39a3 ok++ */
void loadFunction();                    /* 54 sub_3a15 ok	-+ */
bool sub_4000(inst_t *);                /* 55 sub_4000 ok+ */
void sub_404d();                        /* 56 sub_404d ok++ */
void pr_instruction(inst_t *);          /* 57 sub_420a ok	-- */
void sub_436e(operand_t *);             /* 58 sub_436e ok++ */
void sub_44b2(operand_t *);             /* 59 sub_44b2 ok+ */
void sub_4544(int);                     /* 60 sub_4544 ok+ */
void sub_4601();                        /* 61 sub_4601 ok+ */
bool sub_4625(inst_t *);                /* 62 sub_4625 ok+ */
bool sub_4682(operand_t *);             /* 63 sub_4682 ok++ */
int sub_46b1(operand_t *, int);         /* 64 sub_46b1 ok++ */
bool sub_475c(operand_t *, int);        /* 65 sub_475c ok++ */
bool sub_47a2(operand_t *, int);        /* 66 sub_47a2 ok++ */
bool sub_47e0(int, inst_t *, inst_t *); /* 67 sub_47e0 ok+ */
sym_t *allocSym();                      /* 68 sub_4c33 ok+ */
void freeSymbol(sym_t *);               /* 69 sub_4c6b ok+ */
int hash_index(uchar *, int);           /* 70 sub_4cab ok++ */
sym_t *lookupSym(char *);               /* 71 sub_4cf0 ok	-- */
sym_t *allocBlankSym();                 /* 72 sub_4da7 ok++ */
void resetHeap();                       /* 73 sub_4dbf ok++ */
void sub_4e20();                        /* 74 sub_4e20 ok++ */
void *alloc_mem(int);                   /* 75 sub_4e2d ok+ */

char *sbrk(int);
int brk(void *);

/**************************************************************************
 1	strtoi	sub_013d	ok++	Used in const_value
 *	Converts a numeric string, in various bases, to a integer
 **************************************************************************/
int strtoi(char *s, int base) {
    int val;   /* number */
    int digit; /* digit */

    val = 0;
    while (*s != 0) {
        val *= base;
        if (ISDIGIT(*s)) {
            digit = *(s++) - '0';
        } else {
            if (ISXDIGIT(*s)) {
                digit = (ISUPPER(*s) ? (char)(*s | 0x20) : (char)*s) - ('a' - 10);
            }
        }
        if (digit >= base) {
            pr_warning("Digit out of range");
            return 0;
        }
        val += digit;
    }
    return val;
}

/**************************************************************************
 2	ptr_token	sub_020f	ok++
 *	Returns a pointer to a token.
 **************************************************************************/
char *ptr_token() {
    register char *s;

    s = yyline;
    while (PEEKCH() != 0 && PEEKCH() != '\n')
        *s++ = GETCH();

    *s        = 0;
    len_inbuf = 0;
    return yyline;
}

/**************************************************************************
 3	const_value	sub_0289	ok+
 *	Rerurn integer value numeric string in various bases
 *
 *	Generates correct code, but in a different sequence
 **************************************************************************/
int const_value() {
    register char *pi;
    uchar base;

    pi   = yyline + 1;
    base = 0;
    while (ISXDIGIT(PEEKCH()))
        *pi++ = GETCH();

    switch (PEEKCH()) { /* m17: */
    case 'H':
    case 'h':
        base = 16;
        GETCH();
        break;

    case 'O':
    case 'o':
    case 'Q':
    case 'q':
        base = 8;
        GETCH();
        break;
    default:
        if (pi[-1] != 'f' && pi[-1] != 'b') {
            if (pi[-1] == 'B') {
                pi--;
                base = 2;
            }
            break;
        }
        yytype    = *--pi != 'f' ? T_JBWD : T_JFWD;
        *pi       = 0;
        yylval.ui = strtoi(yyline, 10);
        return yytype;
    }

    *pi = 0;
    if (base == 0)
        base = 10;
    yylval.ui = strtoi(yyline, base);
    return T_CONST;
}

/**************************************************************************
 4	get_token	sub_03c7	ok+
 **************************************************************************/
int get_token() {
    int c;
    register char *pi;

    for (;;) {
        pi = yyline;

        switch (c = GETCH()) {
        case -1:
            return -1;
        case '\t':
        case '\f':
        case ' ':
            continue;
        case 0:
        case ';':
            return T_EOL;
        case '\'': /* Single quote (apostrophe) */
            while (PEEKCH() != 0 && PEEKCH() != '\'')
                *pi++ = GETCH();
            if (PEEKCH() == '\'')
                GETCH();
            else
                pr_warning("Unterminated string");
            *pi           = 0;
            yylval.p_char = yyline;
            return T_STRING;

        case '.':
            *pi++ = c;
            while (ISALPHA(PEEKCH()))
                *pi++ = GETCH();
            if (PEEKCH() == '.') /* m27: */
                *pi++ = GETCH();
            break;
        case ',':
            return T_COMM; /* ","						//m31: */

        case ':':
            return T_COLN; /*":"						//m32: */

        case '(':
            yylval.i = P_OPAR; /* m33: */
            return T_OPAR;     /* "(" */

        case ')':
            yylval.i = P_CPAR; /* m34: */
            return T_CPAR;     /* ")" */

        case '+':
            yylval.i = P_ADD; /* m35: */
            return T_PLUS;    /* "+" */

        case '-':
            yylval.i = P_SUB1; /* m36: */
            return T_MINUS;    /* "-" */

        case '*':
            if (ptr_inbuf == inp_buf + 1) {
                printf("%s\n", inp_buf);
                len_inbuf = 0;
                continue;
            }
        default:
            *pi++ = c;                    /* m50: */
            if (ISALPHA(c)) {             /* goto m46; */
                while (ISALNUM(PEEKCH())) /* m41: */
                    *pi++ = GETCH();
                if (pi == yyline + 2) {
                    if (PEEKCH() == '\'')
                        *pi++ = GETCH();
                }
            } else if (ISDIGIT(c) != 0)
                return const_value();
            break;
        }
        while (ISSPACE(PEEKCH()))
            GETCH();

        *pi = 0;
        if (yyline[0] == '_' || ISDIGIT(pi[-1]) || ((yytype = num_token(yyline)) == -1)) {
            if (ISALPHA(yyline[0])) { /* m57: */
                yylval.pSym = lookupSym(yyline);
                return T_SYMBOL;
            }
            pr_warning("Lexical error"); /* m58: */
        } else
            return yytype; /* m59: */
    }
}

/**************************************************************************
 5	get_line	sub_0758	ok+
 *	Generated code is not significantly different from original binary
 **************************************************************************/
/* PMO this code contains a bug. If strlen returns a 0 it accesses inp_buf[-1]
 * and could overwrite with a 0
 * it is also not clear whether a blank line i.e. one with just a '\n' should
 * return with a '\0' as it currently does or try another line
 *
 * Note needs fixing for linux as '\r' will not be removed on input
 */
int get_line() {

    do {
        if (fgets(inp_buf, sizeof(inp_buf), stdin) == NULL)
            return -1;
        len_inbuf = (int)strlen(ptr_inbuf = inp_buf);
        if (inp_buf[len_inbuf - 1] == '\n') /* If penultimate character is */
            inp_buf[len_inbuf - 1] = 0;     /* '\n' then replace it with 0 */
    } while (--len_inbuf < 0);              /* If the line is empty then repeat reading */
    return *ptr_inbuf++;                    /* otherwise, return first character of string */
}

/**************************************************************************
 6	clr_len_inbuf	sub_0758	ok++
 **************************************************************************/
void clr_len_inbuf() {

    len_inbuf = 0;
}

/**************************************************************************
 7	main	sub_07b1	ok+
 **************************************************************************/
int main(int argc, char **argv) {

    for (--argc, ++argv; 0 < argc; ++argv, --argc) {
        if (argv[0][0] != '-')
            break;
        switch (argv[0][1]) {
        case 'N':
        case 'n':
            key_n = 1;
            break; /* Enables statistics printing */

        case 'L':
        case 'l':
            key_l = 1;
            break; /* Enables printing of additional information */

        case 'R':
        case 'r':
            key_r = 1;
            break; /* */

        case 'F':
        case 'f':
            key_f = 1;
            break; /* */

        case 's':
            key_s = 1;
            break; /* Unbuffered stdout */
        default:
            pr_error("Illegal switch %c", argv[0][1]);
            break;
        }
    }
    if (argc < 0) {
        if (freopen(*argv, "r", stdin) == 0)
            pr_error("Can't open %s", *argv);
        if (1 < argc && freopen(*(argv + 1), "w", stdout) == 0)
            pr_error("Can't create %s", *(argv + 1));
    }
    if (key_s != 0)
        setbuf(stdout, 0); /* Unbuffered stdout (Turns off buffering) */

    optimise();

    if (fclose(stdout) == -1) {
        pr_warning("Error closing output file");
        ++num_warn;
    }
    exit(num_warn != 0);
}

/**************************************************************************
 8	pr_error	sub-0941	ok++
 **************************************************************************/
#ifdef CPM
void pr_error(fmt, p2, p3) char *fmt;
{

    pr_message(fmt, p2, p3);
    fclose(stdout);
    exit(1);
}

/**************************************************************************
 9	pr_warning	sub_096f	ok++
 **************************************************************************/
void pr_warning(fmt p2, p3) char *fmt;
{
    pr_message(fmt, p2, p3);
    ++num_warn;
}

/**************************************************************************
 10	pr_message	sub_0994	ok++
 **************************************************************************/
void pr_message(fmt, p2, p3) char *fmt;
{

    fprintf(stderr, "optim: ");
    fprintf(stderr, fmt, p2, p3);
    fputc('\n', stderr);
}

#else
void pr_error(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    pr_message(fmt, args);
    va_end(args);
    exit(1);
}

void pr_warning(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    pr_message(fmt, args);
    va_end(args);
    ++num_warn;
}

void pr_message(char *fmt, va_list args) {

    fprintf(stderr, "optim: ");
    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
}

#endif

/**************************************************************************
 11	find_token	sub_09d0	ok++	Used in num_token
 **************************************************************************/
int find_token(register char *str, operator_t *p2, int p3) {
    char cmp;
    uchar high, low, mid;

    tableBase = p2;
    low       = 0;
    high      = p3 - 1;
    do {
        mid = (high + low) / 2;
        cmp = strcmp(str, tableBase[mid].str);
        if (cmp == 0) {
            yylval.i = tableBase[mid].aux;
            yytext   = tableBase[mid].str;
            return tableBase[mid].type;
        }
        if (cmp < 0)
            high = mid - 1;
        else
            low = mid + 1;
    } while (high >= low);
    return -1;
}

/**************************************************************************
 12	num_token	sub_0a97	ok++	Used in
 **************************************************************************/
int num_token(char *fmt) {

    return find_token(fmt, operators, NOPERATORS);
}

/**************************************************************************
 13	pr_token	sub_0ab2	ok++
 **************************************************************************/
void pr_token(register inst_t *pi) {
    operator_t *po;

    if (pi->str) {
        printf("%s", pi->str);
        return; /* m1: */
    }

    switch (pi->type) { /* m2: */
    case T_JP:
        printf("jp");
        return;
    case T_CALL:
        printf("call");
        return;
    case T_RET:
        printf("ret");
        return;
    }

    po = operators + NOPERATORS; /*    PMO should not be + 1 */
    do {
        if (--po < operators) { /* m3: */
            pr_error("Can't find op");
            return;
        }
    } while ((pi->type != po->type) || (po->aux != pi->aux)); /* m8: */

    printf("%s", po->str);
    return;
}

/**************************************************************************
 14	sub_0b6a	ok++
 **************************************************************************/
void freeOperand(register operand_t *pi) {

    if (pi == 0)
        return;
    ((list_t *)pi)->pNext = freeOperandList;
    freeOperandList       = (list_t *)pi;
}

/**************************************************************************
 15	sub_0b8b	ok++
 **************************************************************************/
void freeInst(register inst_t *pi) {

    ((list_t *)pi)->pNext = freeInstList;
    freeInstList          = (list_t *)pi;
}
/**************************************************************************
 16	sub_0ba7	ok+
 **************************************************************************/
operand_t *allocOperand() {
    register operand_t *pi;

    if (freeOperandList) {
        pi              = (operand_t *)freeOperandList;
        freeOperandList = ((list_t *)pi)->pNext;
        pi->type = pi->aux = 0;
        pi->oIVal          = 0;
        pi->oPSym          = 0;
        return pi;
    }
    return (operand_t *)alloc_mem(sizeof(operand_t));
}

/**************************************************************************
 17	sub_0be2	ok++
 **************************************************************************/
inst_t *allocInst(register inst_t *pi) {
    inst_t *l1;

    if ((l1 = (inst_t *)freeInstList)) {
        freeInstList = (list_t *)l1->pAlt;
        l1->type = l1->aux = 0;
        l1->iLhs = l1->iRhs = 0;
        l1->str             = 0;
    } else {
        l1 = (inst_t *)alloc_mem(sizeof(inst_t));
    }
    l1->pNext = pi->pNext;
    l1->pAlt  = pi;
    if (pi->pNext != 0)
        pi->pNext->pAlt = l1;
    return pi->pNext = l1;
}

/**************************************************************************
 18	sub_0ca2	ok++
 **************************************************************************/
inst_t *allocSymbol(register inst_t *pi) {

    pi                   = allocInst(pi);
    pi->iPSym            = allocBlankSym();
    pi->iSymId           = ++symbolId;
    pi->iPSym->val.pInst = pi;
    pi->type             = T_SYMBOL;
    return pi;
}

/**************************************************************************
 19	optimise	sub-0ce4	ok++
 **************************************************************************/
void optimise() {
    int l1;
    int l2;
    int iteration;
    char *l4;
    bool l5;
    char *l6;

    l4        = sbrk(0);
    iteration = 0;
    while (!feof(stdin)) { /* not eof */
        freeOperandList = freeInstList = 0;
        resetHeap();    /* fun_73 */
        loadFunction(); /* fun_54 */
        sub_4e20();     /* fun_74 */
        sub_0ed1();     /* fun_21 */
        chkIXYUsage();  /* fun_20 */
        sub_122f();     /* fun_23 */

        l2 = 0;
        do {
            if (iteration < ++l2)
                iteration = l2;

            if (key_l != 0) {
                printf("***** Pass %d\n", l2);
                sub_404d();
            }

            l5 = 0;
            do {
                hasChanged = 0; /* m5: */
                sub_15ad();
                l5 |= hasChanged;
            } while (hasChanged != 0);

            do {
                hasChanged = 0; /* m6: */
                sub_1ec1();
            } while (hasChanged != 0);

        } while ((l5 |= hasChanged) != 0);

        sub_404d();

        if (l6 < sbrk(0))
            l6 = sbrk(0);
    } /* end while */
    if (key_n == 0)
        return;

    fclose(stdout); /* This statement results in an error when you close */
                    /* stdout again in main program. It can be removed. */
    fprintf(stderr, "%dK, %d iterations\n", ((int)(l6 - l4) + 0x400) / 0x3ff, iteration);

    for (l1 = 0; l1 < NOPTIM; l1++)
        if (optimiseCounters[l1] != 0)
            fprintf(stderr, "%d %s\n", optimiseCounters[l1], opt_msg[l1]);
}

/**************************************************************************
 20	sub_0e67	ok++	used in optimise
 **************************************************************************/
void chkIXYUsage() {
    register inst_t *pi;

    usesIXorIY = false;
    for (pi = root; pi; pi = pi->pNext) {
        if ((pi->iLhs && pi->iLhs->type == T_INDEXED) || (pi->iRhs && pi->iRhs->type == T_INDEXED) ||
            (pi->iLhs && pi->iLhs->type == T_REG && pi->iLhs->aux >= REG_IX)) {
            usesIXorIY = true;
            return;
        }
    }
}

/**************************************************************************
 21	sub_0ed1	ok++	used in optimise
 **************************************************************************/
void sub_0ed1() {
    inst_t *pi2;
    operand_t *po;
    bool newLabel; /* Flag of the sub_0ca2 call */
    register inst_t *pi1;

    for (pi1 = word_6ffc; pi1; pi1 = pi1->pAlt) {
        if (pi1->type == T_CONST) {
            newLabel = false;
            optimiseCounters[3]++; /* 6fc3 opt_msg[3] = "Temporary labels" */
            hasChanged = true;
            for (pi2 = pi1->pAlt; pi2 && pi2->type != T_CONST && pi2->aux != pi1->aux; pi2 = pi2->pAlt) {
                if ((po = pi2->iLhs) && po->type == T_JBWD && po->oIVal == pi1->aux) {
                    if (!newLabel) {
                        allocSymbol(pi1);
                        newLabel = true;
                    }
                    po->type      = T_CONST;
                    po->oPOperand = pi1->pNext->iLhs;
                    po->oIVal     = 0;
                }
            }
            if (pi1->aux < REG_BC) { /* m7: */
                if (!newLabel)
                    allocSymbol(pi1);
                for (pi2 = pi1->pNext; pi2; pi2 = pi2->pNext) {
                    if ((po = pi2->iLhs) && po->type == T_JFWD && po->oIVal == pi1->aux) {
                        po->type      = T_CONST;
                        po->oPOperand = pi1->pNext->iLhs;
                        po->oIVal     = 0;
                        break;
                    }
                }
            }
        }
        pi1 = pi1->pNext; /* m12: */
        removeInstruction(pi1->pAlt);
    }
}

/**************************************************************************
 22	sub_1071	ok++	used in sub_15ad
 **************************************************************************/
bool sub_1071(register inst_t *pi) {

    inst_t *pi1;
    inst_t *pi2;
    inst_t *pi3;

    if (pi->type != T_JP || pi->aux != 0 || pi->iLhs->type != T_CONST)
        return false;

    pi1 = pi->iLhs->oPSym->val.pInst;
    while (pi1->type != T_SYMBOL) {
        pi1 = pi1->pAlt;
    }
    if (pi1 == pi) {
        removeInstruction(pi);
        ++optimiseCounters[6]; /* 6fc9 opt_msg[6] = "Jumps to .+1" */
        hasChanged = true;
        return false;
    }
    if (pi1->type != T_JP || pi1->aux != 0)
        return false;

    for (pi3 = pi1->pNext; pi3->type; pi3 = pi3->pNext)
        if (pi3->type == T_JP && pi3->aux == 0)
            break;

    if (pi3 == pi1->pNext || pi3->type == 0 || pi3 == pi)
        return false;

    pi->pNext->pAlt  = pi3;
    pi1->pNext->pAlt = pi;

    pi3->pNext->pAlt = pi1;

    pi2              = pi1->pNext;
    pi1->pNext       = pi3->pNext;
    pi3->pNext       = pi->pNext;
    pi->pNext        = pi2;
    ++optimiseCounters[16]; /* 6fdd opt_msg[16] = "Code motions" */
    hasChanged = true;
    removeInstruction(pi);
    ++optimiseCounters[6]; /* 6fc9 opt_msg[6] = "Jumps to .+1" */
    return hasChanged = true;
}

/**************************************************************************
 23	sub_122f	ok--	Used in: optimise
 **************************************************************************/
void sub_122f() {
    operand_t *po;
    register inst_t *pi;

    for (pi = root->pNext; pi; pi = pi->pNext) /* set initial values for symbols */
        if (pi->type == T_SYMBOL)
            pi->aux = pi->iPSym->name[0] == '_' ? INT_MAX : 0; /* check for public name */

    for (pi = root->pNext; pi; pi = pi->pNext) { /* update reference counts */
        if (pi->type == T_JP || pi->type == T_DJNZ) {
            if ((po = pi->iLhs) && po->type == T_CONST && po->oPSym && po->oPSym->val.i)
                po->oPSym->val.i++;
        }
    }
    for (pi = word_6ff2; pi; pi = pi->pNext) { /* do the same for the jump tables */
        if (pi->type == T_DEFW) {
            if (pi->iLhs && (po = pi->iLhs)->type == T_CONST && po->oPSym->val.i)
                po->oPSym->val.i++;
        }
    }
}

/**************************************************************************
 24	sub_1369	ok++ (PMO)
 **************************************************************************/
bool sub_1369(register operand_t *pi) {

    return pi->type == T_CONST || pi->type == T_INDEXED || (pi->type == T_REGREF && pi->aux != REG_HL);
}

/**************************************************************************
 25	sub_1397	ok++ (PMO)
 **************************************************************************/
void removeInstruction(register inst_t *pi) {

    if (pi->type == T_JP && pi->iLhs->type == T_CONST && pi->iLhs->oPSym)
        removeLabelRef(pi->iLhs->oPSym);

    pi->pAlt->pNext = pi->pNext;
    pi->pNext->pAlt = pi->pAlt;
    if (pi->type != T_SYMBOL) {
        freeOperand(pi->iLhs);
        freeOperand(pi->iRhs);
    }
    freeInst(pi);
}

/**************************************************************************
 26	sub_140b	ok++
 **************************************************************************/
inst_t *getNextRealInst(register inst_t *pi) {

    while (pi->type == T_SYMBOL)
        pi = pi->pNext;
    return pi;
}

/**************************************************************************
 27	sub_142f	ok++
 **************************************************************************/
bool operandsSame(register operand_t *po1, operand_t *po2) {

    if (po1 == 0 && po2 == 0)
        return true;
    if (po1 == 0 || po2 == 0 || po1->type != po2->type || po1->aux != po2->aux || po1->type == 0)
        return false;

    return po1->oPSym == po2->oPSym && po1->oIVal == po2->oIVal;
}

/**************************************************************************
 28	sub_14ac	ok++
 **************************************************************************/
bool instructionsSame(register inst_t *pi1, inst_t *pi2) {

    if (pi1->type == 0 || pi1->type == T_SYMBOL || pi2->type == 0 || pi2->type == T_SYMBOL)
        return false;

    if (pi1->type != pi2->type || pi1->aux != pi2->aux)
        return false;

    return operandsSame(pi1->iLhs, pi2->iLhs) && operandsSame(pi1->iRhs, pi2->iRhs);
}

/**************************************************************************
 29	sub_153d	ok++
 **************************************************************************/
void removeLabelRef(register sym_t *ps) {
    inst_t *pi;

    if ((pi = ps->val.pInst) == 0)
        return;
    if (pi->aux == 0)
        pr_error("Refc == 0");
    if (--pi->aux != 0)
        return;
    removeInstruction(pi);
    ps->val.pInst = 0;
    freeSymbol(ps);
    optimiseCounters[4]++; /* 6fc5 opt_msg[4] = "Unref'ed labels" */
    hasChanged = true;
}

/**************************************************************************
 30	sub_15ad	ok++	Used in optimize
 **************************************************************************/
void sub_15ad() {
    register inst_t *pi;

    for (gPi = root; gPi; gPi = gPi->pNext) {
        if (sub_1795() == 0 && gPi->type == T_JP && sub_1aec() == 0 && sub_1b86() == 0) { /* 162E / 1632 */
            if (gPi->iLhs->type != T_CONST || gPi->iLhs->oPSym->val.pInst != gPi->pNext) {
                if (gPi->aux == 0) { /* 1648 / 164B */
                    while (gPi->pNext->type && gPi->pNext->type != T_SYMBOL) {
                        pi = gPi->pNext;
                        removeInstruction(pi);
                        optimiseCounters[5]++; /* 6fc7 opt_msg[5] = "Unreachable code" */
                        hasChanged = 1;
                    }
                    /* 1696 */
                    if (gPi->iLhs->type != T_REGREF && gPi->iLhs->oPSym->val.pInst != 0 && sub_1071(gPi) != 0)
                        continue;
                }
                /* 16CA / 16D1 */
                if (gPi->iLhs->type == T_CONST && (gPi->pNext->type == T_CALL || gPi->pNext->type == T_JP) &&
                    gPi->pNext->aux == 0 && gPi->iLhs->oPSym->val.pInst == gPi->pNext->pNext) {
                    gPi->pNext->aux = ccSwap[gPi->aux]; /* swap condition code */
                    removeInstruction(gPi);
                    optimiseCounters[7]++; /* 6fcb opt_msg[7] = "Skips over jumps" */
                    hasChanged = 1;
                } else if (sub_1c67() != 0 || sub_1d94() == 0)
                    ;
            } else {
                removeInstruction(gPi);
                optimiseCounters[6]++; /* 6fc9 opt_msg[6] = "Jumps to .+1" */
                hasChanged = true;
            }
        }
    }
}
/**************************************************************************
 31	sub_1795	ok++
 **************************************************************************/
bool sub_1795() {
    register inst_t *pi;

    if (gPi->type != T_LD)
        return false;
    if (gPi->iLhs->type != T_REG || gPi->iLhs->aux != REG_SP)
        return false;
    if ((pi = gPi->pAlt)->type != T_CADD || (pi = pi->pAlt)->type != T_LD)
        return false;
    if (pi->iLhs->type != T_REG || pi->iLhs->aux != REG_HL || pi->iRhs->type != T_CONST)
        return false;
    if (pi->iRhs->oPOperand)
        pr_error("Funny stack adjustment");
    word_6fb9 = pi->iRhs->oIVal;
    pi        = gPi->pNext;
    if (pi->type == T_ONEBYTE && pi->aux == P_EXX)
        pi = pi->pNext;

    for (; pi->type != T_CALL && pi->type != T_JP && pi->type != T_STK; pi = pi->pNext)
        if (pi->type == T_EX && pi->type == REG_SP)
            break;

    if (word_6fb9 > 0 && usesIXorIY != 0 && pi->aux == 0 && sub_4000(pi) != 0) {
        removeInstruction(gPi->pAlt->pAlt);
        removeInstruction(gPi->pAlt);
        gPi = gPi->pAlt;
        removeInstruction(gPi->pNext);
        if (gPi->pNext->type == T_ONEBYTE && gPi->pNext->aux == P_EXX && gPi->type == T_ONEBYTE &&
            gPi->aux == P_EXX) { /* exx */
            removeInstruction(gPi->pNext);
            removeInstruction(gPi);
        }
        ++optimiseCounters[2]; /* 6fc1 opt_msg[2] = "Stack adjustments" m7: */
        hasChanged = 1;
        return true;
    }
    pi = gPi->pAlt->pAlt;
    if (word_6fb9 < 0)
        word_6fb9 = -word_6fb9;
    if (pi->pAlt->type == T_ONEBYTE && pi->pAlt->aux == P_EXX)
        word_6fb9 -= 2;

    if (word_6fb9 > 8 || pi->iRhs->oIVal < 0)
        return false;

    optimiseCounters[2]++; /* 6fc1 opt_msg[2] = "Stack adjustments" */
    hasChanged = 1;

    word_6fb9  = pi->iRhs->oIVal;
    pi         = pi->pAlt;
    removeInstruction(pi->pNext->pNext);
    removeInstruction(pi->pNext);
    removeInstruction(gPi);
    gPi = pi;

    while (word_6fb9 != 0) {
        gPi             = allocInst(gPi);
        gPi->iLhs       = allocOperand();
        gPi->iLhs->type = T_REG;
        if (1 < word_6fb9) {
            gPi->iLhs->aux = REG_BC;
            gPi->type      = T_STK;
            word_6fb9 -= 2;
            gPi->aux = P_POP; /* "pop" */
        } else {
            gPi->iLhs->aux = REG_SP;
            gPi->type      = T_INCDEC; /* Decrement, Increment */
            --word_6fb9;
            gPi->aux = P_INC;
        }
    }
    if (gPi->pNext->type == T_ONEBYTE && gPi->pNext->aux == P_EXX && pi->type == T_ONEBYTE && pi->aux == P_EXX) {
        removeInstruction(gPi->pNext);
        removeInstruction(pi);
    }
    return true;
}

/**************************************************************************
 32	sub_1aec	ok++
 **************************************************************************/
bool sub_1aec() {
    register inst_t *pi;

    if (gPi->iLhs->type != T_REGREF) {
        if ((gPs = gPi->iLhs->oPSym)->val.pInst != 0) {
            pi = getNextRealInst(gPs->val.pInst);
            pi = pi->pAlt;
            if (gPs->val.pInst != pi /*->i_7*/) {
                gPi->iLhs->oPOperand = pi->iLhs;
                removeLabelRef(gPs);
                ++pi->aux;
                optimiseCounters[0]++; /* 6fbd opt_msg[0] = "Redundant labels" */
                return (hasChanged = true);
            }
        }
    }
    return false;
}

/**************************************************************************
 33	sub_1b86	ok++
 **************************************************************************/
bool sub_1b86() {
    register inst_t *pi;

    if (gPi->type == T_JP || gPi->type == T_CALL) {
        if ((gPs = gPi->iLhs->oPSym) && (pi = gPs->val.pInst)) {
            pi = getNextRealInst(pi);
            if (pi->type == T_JP && (pi->aux == 0 || pi->aux == gPi->aux) && pi->iLhs->oPSym != gPs) {
                removeLabelRef(gPs);
                gPs              = pi->iLhs->oPSym;
                gPi->iLhs->oPSym = gPs;
                if (gPs->val.pInst != 0)
                    ++gPs->val.pInst->aux;
                ++optimiseCounters[1]; /* 6fbf opt_msg[1] = "Jumps to jumps" */
                return hasChanged = true;
            }
        }
    }

    return false;
}
/**************************************************************************
 34	sub_1c67	ok++
 **************************************************************************/
bool sub_1c67() {
    register inst_t *pi;

    if (gPi->aux == 0) {
        pi = gPi->pNext;
        while (pi != 0) {
            if (instructionsSame(pi, gPi) != 0) {
                word_6fe3 = gPi;
                word_6fe5 = pi;
                while (instructionsSame(word_6fe5->pAlt, word_6fe3->pAlt) != 0) {
                    word_6fe3 = word_6fe3->pAlt;
                    word_6fe5 = word_6fe5->pAlt;
                }
                if (word_6fe3 != gPi) {
                    word_6fe3                  = allocSymbol(word_6fe3->pAlt);
                    word_6fe5                  = allocSymbol(word_6fe5->pAlt);
                    word_6fe5->iLhs            = allocOperand();
                    word_6fe5->type            = 8;
                    word_6fe5->iLhs->type      = 0x32;
                    word_6fe5->iLhs->oPOperand = word_6fe3->iLhs;
                    ++word_6fe3->aux;
                    removeInstruction(pi);
                    ++optimiseCounters[8]; /* 6fcd opt_msg[8] = "Common code seq's" */
                    return hasChanged = true;
                }
            }
            pi = pi->pNext;
        }
    }
    return false;
}

/**************************************************************************
 35	sub_1d94	ok++
 **************************************************************************/
bool sub_1d94() {
    register inst_t *pi;

    if (gPi->aux != 0 && (pi = gPi->iLhs->oPSym->val.pInst)) {
        for (word_6fe3 = gPi; sub_4625(pi->pNext) && instructionsSame(word_6fe3->pNext, pi->pNext); pi = pi->pNext)
            word_6fe3 = word_6fe3->pNext;

        if (word_6fe3 != gPi) {
            if (pi->pNext->type == T_SYMBOL)
                pi = pi->pNext;
            else
                pi = allocSymbol(pi);
            word_6fe3                      = allocInst(word_6fe3);
            word_6fe3->iLhs                = allocOperand();
            word_6fe3->iLhs->type          = T_CONST;
            word_6fe3->iPSym->val.pOperand = pi->iLhs;
            word_6fe3->type                = gPi->type;
            word_6fe3->aux                 = gPi->aux;
            ++pi->aux;
            removeInstruction(gPi);
            ++optimiseCounters[8]; /* 6fcd opt_msg[8] = "Common code seq's" */
            return hasChanged = true;
        }
    }
    return false;
}

/**************************************************************************
 36	sub_1ec1	ok	Used in optimize
 **************************************************************************/
void sub_1ec1() {
    int l1;
    register inst_t *pi;

    sub_4601();
    for (gPi = root; gPi; gPi = pi->pNext) {
        switch ((pi = gPi)->type) {
        case T_LD:
            if (!key_r) {
                if (sub_24c0())
                    continue;
                if ((pi = gPi)->iLhs->type == T_REG && pi->iLhs->aux == REG_A && sub_4682(pi->iRhs) &&
                    !sub_47e0(REG_F, (pi = gPi)->pNext, gPi)) {
                    pi       = gPi;
                    pi->iRhs = 0;
                    pi->type = T_3;
                    pi->aux  = 0xA8; /* xor */
                    gPi->str = 0;
                    ++optimiseCounters[1]; /* 6fbf opt_msg[1] = "Jumps to jumps" */
                    hasChanged = true;
                }
            }
            sub_2bdb();
            break;
        case T_SYMBOL:
            for (; (pi = gPi)->type == T_SYMBOL && pi->aux == 0; gPi = (pi = gPi)->pNext) {
                removeInstruction(gPi);
                optimiseCounters[4]++; /* 6fc5 opt_msg[4] = "Unref'ed labels" */
                hasChanged = true;
            }
            /* fall through */
        case T_TWOBYTE:
        case T_CALL:
            sub_4601();
            sub_2bdb();
            break;
        case T_EX:
            if ((pi = gPi)->iLhs->type == T_REG) {
                if (sub_23c1())
                    break;
                swapHLDE();
            } else
                sub_4544((pi = gPi)->iRhs->type);
            sub_2bdb();
            break;
        case T_ONEBYTE:
            switch ((pi = gPi)->aux) {
            case P_NOP:
            case P_SCF:
            case P_CCF:
            case P_HALT:
            case P_DI:
            case P_EI:
                break;
            case P_EXX:
                sub_4601();
                break;
            default:
                sub_4544(REG_AF);
                break;
            }
            sub_2bdb();
            break;
        case T_BIT:
            if ((pi = gPi)->aux != 0x40)
                if (pi->iRhs->type == T_REG)
                    sub_4544(pi->iRhs->aux);
                else if ((l1 = sub_46b1((pi = gPi)->iRhs, 0)) != -1)
                    sub_4544(l1);
            sub_2bdb();
            break;
        case T_CARR:
        caseCommon:
            if ((pi = gPi)->iLhs->type == T_REG) {
                if (sub_47e0(pi->iLhs->aux, (pi = gPi)->pNext, gPi)) {
                    if ((pi = gPi)->iLhs->type == T_REG)
                        sub_4544(pi->iLhs->type);
                    else
                        sub_44b2(pi->iLhs);
                    sub_2bdb();
                    break;
                } else if (((pi = gPi)->type != T_INCDEC || pi->iLhs->aux >= REG_BC) &&
                           !sub_47e0(REG_F, (pi = gPi)->pNext, gPi)) {
                    removeInstruction(gPi);
                    optimiseCounters[11]++; /* 6fd3 opt_msg[11] = "Redundant operations" */
                    hasChanged = true;
                    break;
                }
            }
            /* fall through */ /* m25 */
        case T_6:
        case T_0xE:
            pi = gPi;
            if (pi->iLhs->type == T_REG)
                sub_4544(pi->iLhs->aux);
            else
                sub_44b2(pi->iLhs);
            sub_2bdb();
            break;
        case T_CADD:
            if (!sub_47e0(pi->iLhs->aux, (pi = gPi)->pNext, gPi)) {
                removeInstruction(gPi);
                optimiseCounters[11]++; /* 6fd3 opt_msg[11] = "Redundant operations" */
                hasChanged = true;
            } else if ((pi = gPi)->iRhs->type != T_CONST || abs(pi->iRhs->oIVal) != 1 || (pi = gPi)->iRhs->oPOperand)
                goto caseCommon;
            else {
                pi->type        = T_INCDEC;
                (pi = gPi)->aux = pi->iRhs->oIVal == 1 ? REG_L : REG_H;
                gPi->str        = 0;
                freeOperand(pi->iRhs);
                (pi = gPi)->iRhs = 0;
                optimiseCounters[13]++; /* 6fd7 opt_msg[13] = "Simplified addresses" */
                hasChanged = 1;
            }
            /* fall through */
        case T_INCDEC:
            if ((pi = gPi)->iLhs->type != T_REG)
                goto caseCommon;
            if (pi->iLhs->aux != REG_HL)
                goto caseCommon;

            if (!sub_2ef8())
                sub_2bdb();
            break;
        case T_DJNZ:
            sub_4544(0);
            sub_2bdb();
            break;
        case T_STK:
            if ((pi = gPi)->aux == P_PUSH) { /* push */
                if (pi->iLhs->aux == REG_IY && (l1 = sub_46b1(&regValues[17], REG_IY)) != -1 && l1 != REG_IY) {
                    (pi = gPi)->iLhs->aux = pi->type;
                    optimiseCounters[13]++; /* 6fd7 opt_msg[13] = "Simplified addresses" */
                    hasChanged = true;
                }
                /* check for pop */
                if ((pi = gPi)->pNext->type == T_STK && pi->pNext->aux == P_POP &&
                    pi->iLhs->aux == pi->pNext->iLhs->aux) {
                    removeInstruction(pi->pNext);
                    removeInstruction(gPi);
                    hasChanged = true;
                    break;
                }
            } else {
                sub_4544(pi->iLhs->type); /* m39: */
                if ((pi = gPi)->pAlt->type == T_STK && pi->pAlt->aux == P_PUSH) {

                    /* ambiguious code - pi could be modified on rhs before using on lhs
                     * on hitech generated code gets lhs before rhs
                     */
                    regValues[(pi = gPi)->iLhs->aux] = regValues[pi->pAlt->iLhs->aux];
                    if ((pi = gPi)->iLhs->aux == REG_IY && pi->pNext->type == T_STK && pi->pNext->iLhs->aux == REG_IY) {
                        pi->pNext->iLhs->aux = pi->pAlt->iLhs->aux;
                        ++optimiseCounters[13]; /* 6fd7 opt_msg[13] = "Simplified addresses" */
                        hasChanged = 1;
                    }
                }
            }
            sub_2bdb();
            break;
        case T_3:
            if (!sub_2d3b())
                sub_2bdb();
            break;
        }
        pi = gPi;
    }
}

/**************************************************************************
 37	sub_23c1	ok--
 **************************************************************************/
bool sub_23c1() {
    register inst_t *pi;

    pi = gPi->pNext;
    if (pi->type == T_STK && pi->aux == P_PUSH && !sub_47e0(gPi->iLhs->aux, pi->pNext, gPi) &&
        !sub_47e0(gPi->iRhs->aux, pi->pNext, gPi)) {
        pi->iLhs->aux = gPi->iRhs->aux;
        removeInstruction(gPi);
        gPi = pi;
    } else if (gPi->pNext->type == T_EX && gPi->pNext->iLhs->type == T_REG) {
        removeInstruction(gPi->pNext);
        removeInstruction(gPi);
    } else
        return false;
    ++optimiseCounters[15]; /* 6fdb opt_msg[15] = "Redundant ex de,hl's" */
    hasChanged = 1;
    return hasChanged;
}

/**************************************************************************
 38	sub_24c0	ok++
 **************************************************************************/
bool sub_24c0() {
    inst_t *l1;
    operand_t *l2;
    int reg;
    register inst_t *pi;

    if (sub_3053())
        return true;
    for (;;) { /* trick to remove need for gotos */
        if ((pi = gPi)->iLhs->type == T_REG &&
            (pi->iRhs->type == T_INDEXED || pi->iRhs->type == T_ADDRREF || pi->iRhs->type == T_CONST)) {
            if (sub_29c3())
                return true;
        } else if ((pi = gPi)->iRhs->type == T_CONST && (pi = gPi)->iLhs->type == T_INDEXED) {
            if ((reg = sub_46b1(pi->iRhs, REG_A)) != -1) {
                (pi = gPi)->iRhs->type = T_REG; /* m6: */
                pi->iRhs->aux          = reg;
                ++optimiseCounters[13]; /* 6fd7 opt_msg[13] = "Simplified addresses" */
                hasChanged = true;
                return true;
            }
            sub_44b2((pi = gPi)->iLhs);
        } else if ((pi = gPi)->iRhs->type == T_REG &&
                   ((pi = gPi)->iLhs->type == T_INDEXED || pi->iLhs->type == T_ADDRREF)) {
            if (operandsSame((pi = gPi)->iLhs, &regValues[(pi = gPi)->iRhs->aux]))
                break;
            sub_44b2((pi = gPi)->iLhs);
            if (regValues[(pi = gPi)->iRhs->aux].type == 0) {
                sub_4544((pi = gPi)->iRhs->aux);
                regValues[(pi = gPi)->iRhs->aux] = *(pi = gPi)->iLhs;
            }

        } else if ((pi = gPi)->iLhs->type == T_REG && (pi = gPi)->iRhs->type != T_REG) { /* 2824 */
            if (pi->iLhs->aux == pi->iRhs->aux ||
                operandsSame(&regValues[(pi = gPi)->iLhs->aux], &regValues[pi->iRhs->aux])) {
                break;
            }
            word_6fe5 = (pi = gPi)->pNext;
            if (word_6fe5->type == T_LD && operandsSame((pi = word_6fe5)->iLhs, pi->iRhs) &&
                operandsSame((pi = word_6fe5)->iRhs, (pi = gPi)->iLhs) != 0) {
                removeInstruction(word_6fe5);
                optimiseCounters[12]++; /* 6fd5 opt_msg[12] = "Redundant loads/stores" */
                hasChanged = true;
            }
            if (!sub_47e0(pi->iLhs->aux, (pi = gPi)->pNext, gPi))
                break;
            if ((pi = gPi)->iLhs->aux == REG_E && pi->iRhs->aux == REG_L && (word_6fe5 = pi->pNext)->type == T_LD &&
                (pi = word_6fe5)->iLhs->type == T_REG && pi->iLhs->aux == REG_D && pi->iRhs->type == T_REG &&
                pi->iRhs->aux == REG_H && !sub_47e0(REG_HL, pi->pNext, gPi)) {
                removeInstruction((pi = gPi)->pNext);
                pi            = gPi;
                pi->type      = T_EX;
                gPi->str      = 0;
                pi->iLhs->aux = REG_DE;
                pi->iRhs->aux = REG_HL;
                swapHLDE();
                ++optimiseCounters[13]; /* 6fd7 opt_msg[13] = "Simplified addresses" */
                hasChanged = true;
                return true;
            }
            sub_4544((pi = gPi)->iLhs->aux);
            regValues[(pi = gPi)->iLhs->aux] = regValues[(pi = gPi)->iRhs->aux];
        } else if ((pi = gPi)->iLhs->type == T_REG)
            sub_4544((pi = gPi)->iLhs->aux);

        if ((pi = gPi)->iLhs->type == T_REG && (pi = gPi)->iRhs->type == T_REG) {
            if ((l1 = pi->pAlt)->type == T_LD && (l2 = l1->iLhs)->type == T_REG && l2->aux == pi->iRhs->aux &&
                !sub_47e0(l2->aux, pi->pNext, l1) && sub_1369(l1->iRhs)) {
                sub_4544(l2->aux);
                regValues[l2->aux = (pi = gPi)->iLhs->aux] = *l1->iRhs;
                break;
            }
            if ((l1 = (pi = gPi)->pNext)->type == T_LD && (l2 = l1->iRhs)->type == T_REG && l2->aux == pi->iLhs->aux &&
                !sub_47e0(l2->aux, l1->pNext, gPi) && sub_1369(l1->iLhs)) {
                sub_4544(l2->aux);
                l2->aux = (pi = gPi)->iRhs->aux;
                break;
            }
        }
        return false; /* m26: */
    }

    removeInstruction(gPi);
    ++optimiseCounters[12]; /* 6fd5 opt_msg[12] = "Redundant loads/stores" */
    hasChanged = true;
    return true;
}

/**************************************************************************
 39	sub_29c3	ok+
 **************************************************************************/
bool sub_29c3() {
    int l1;
    inst_t *pi1;
    register inst_t *pi;

    if (operandsSame((pi = gPi)->iRhs, &regValues[(pi = gPi)->iLhs->aux]) ||
        !sub_47e0(pi->iLhs->aux, (pi = gPi)->pNext, gPi)) {
        removeInstruction(gPi);
        ++optimiseCounters[12]; /* 6fd5 opt_msg[12] = "Redundant loads/stores" */
        return hasChanged = true;
    }

    sub_4544((pi = gPi)->iLhs->aux);
    if ((pi = gPi)->iLhs->aux <= REG_HL) {
        pi = gPi;
        if ((l1 = sub_46b1(pi->iRhs, pi->iLhs->aux)) != -1) {
            /* code hikes (pi = gPi)->iLhs->aux before test !!! */
            regValues[(pi = gPi)->iLhs->aux] = *(pi = gPi)->iRhs;
            pi                               = gPi;
            pi->iRhs->type                   = T_REG;
            pi->iRhs->aux                    = l1;
            if (pi->iLhs->aux >= REG_BC) { /* goto m5; */
                pi1             = allocInst(gPi);
                pi1->iLhs       = allocOperand();
                pi1->iRhs       = allocOperand();
                pi1->iLhs->type = T_REG;
                pi1->iRhs->type = T_REG;
                pi1->iLhs->aux  = l6c50h[(pi = gPi)->iLhs->aux].c0;
                pi1->iRhs->aux  = l6c50h[pi->iRhs->aux].c0;
                pi1->iLhs->aux  = l6c50h[pi->iLhs->aux].c1;
                pi1->iRhs->aux  = l6c50h[pi->iRhs->aux].c1;
                pi1->type       = T_LD; /* OP_LD */
                gPi             = pi1;
            }
            ++optimiseCounters[13]; /* 6fd7 opt_msg[13] = "Simplified addresses" */
            return hasChanged = true;
        }
    }
    regValues[(pi = gPi)->iLhs->aux] = *(pi = gPi)->iRhs;
    return false;
}

/**************************************************************************
 40	sub_2bdb	ok--
 **************************************************************************/

bool sub_2bdb() {
    register inst_t *pi;

    if (gPi->type == T_STK && gPi->iLhs->aux == REG_BC && gPi->aux == P_POP && !sub_47e0(REG_BC, gPi->pNext, gPi)) {
        pi = gPi;
        do {
            pi = pi->pNext;
            if (pi == 0 || pi->type == T_JP || pi->type == T_CALL || pi->type == T_SYMBOL)
                break;

            if (pi->type == T_STK) {
                if (pi->aux != P_PUSH || pi->pNext->type != T_STK || pi->pNext->aux != P_POP)
                    break;
                pi = pi->pNext;
            }
            if (pi->type == T_EX || (pi->type == T_LD && pi->iLhs->type == T_REG))
                if (pi->iLhs->aux == REG_SP)
                    break;
        } while (pi->type != T_LD || pi->iLhs->type != T_REG);

        if (pi->type == T_STK && pi->aux == P_PUSH && pi->iLhs->aux == REG_HL && !sub_47e0(REG_HL, pi->pNext, pi)) {
            removeInstruction(gPi);
            pi->str        = 0;
            pi->type       = T_EX;
            pi->aux        = 0;
            pi->iRhs       = pi->iLhs;
            pi->iLhs       = allocOperand();
            pi->iLhs->type = T_REGREF;
            pi->iLhs->aux  = REG_SP;
            ++optimiseCounters[10]; /* 6fd1 opt_msg[10] = "Ex (sp),hl'pi used" */
            return hasChanged = true;
        }
    }
    return false;
}

/**************************************************************************
 41	sub_2d3b	ok
 **************************************************************************/

bool sub_2d3b() {
    register operand_t *po;

    switch (gPi->aux) {
    default:
        if (sub_4682(gPi->iLhs) == 0) {
            if ((po = gPi->iLhs)->type != T_REG || (gPi->aux & 0x80)) {
                sub_4544(REG_AF);
                return false;
            }
            break;
        }
        gPi->aux = P_OR;
        /* fall through */
    case P_OR:
        po = gPi->iLhs; /* case 0xB0 */
        if (sub_4682(po) != 0) {
            po->type = T_REG;
            po->aux  = REG_A;
        }
        /* fall through */
    case P_SUB:
    caseP_SUB: /* common */
        if (gPi->iLhs->type != T_REG || gPi->iLhs->aux != REG_A) {
            sub_4544(REG_AF);
            return 0;
        }
        if (gPi->aux != P_SUB) {
            if (sub_47e0(REG_F, gPi->pNext, gPi))
                return false;
            goto remove;
        }
        break;
    case P_AND:
        po = gPi->iLhs;
        if (sub_4682(po))
            break;
        if (po->type == T_CONST && po->oPOperand == 0 && po->aux == 255 /* -1 */) {
            gPi->aux = P_OR;
            po->type = T_REG;
            po->aux  = REG_A;
        }
        goto caseP_SUB;
    case P_CP:
        return 0; /* case 0xB8 */
    }

    if (sub_47e0(REG_F, gPi->pNext, gPi) || sub_4682(&regValues[REG_A]) == 0) {
        gPi->aux                   = P_XOR;
        gPi->str                   = 0;
        gPi->iLhs->type            = T_REG;
        gPi->iLhs->aux             = REG_A;
        regValues[REG_A].type      = T_CONST;
        regValues[REG_A].oPOperand = 0;
        regValues[REG_A].oIVal     = 0;
        return false;
    }
remove:
    removeInstruction(gPi);
    ++optimiseCounters[11]; /* 6fd3 opt_msg[11] = "Redundant operations" */
    return hasChanged = true;
}

/**************************************************************************
 42	sub_2ef8	ok++
 **************************************************************************/
bool sub_2ef8() {
    operand_t tmp;
    int l2;
    register inst_t *pi;

    if ((pi = gPi)->pNext->type == T_INCDEC && operandsSame(pi->iLhs, pi->pNext->iLhs)) {
        if (pi->pNext->aux != (pi = gPi)->aux)
            removeInstruction(pi->pNext);

    } else if (sub_47e0(REG_HL, (pi = gPi)->pNext, gPi)) {
        tmp = regValues[18];
        l2  = word_7006;
        if (regValues[REG_HL].type != 0 ||
            (regValues[REG_L].type == T_INDEXED && regValues[REG_H].type == T_INDEXED &&
             regValues[REG_L].aux == regValues[REG_H].aux && regValues[REG_L].oIVal + 1 == regValues[REG_H].oIVal)) {
            if (regValues[REG_HL].type != 0)
                tmp = regValues[REG_HL];
            else
                tmp = regValues[REG_L];
            l2  = 0;
        }
        sub_4544(REG_HL);
        regValues[18] = tmp;
        word_7006     = l2;
        if ((pi = gPi)->aux == REG_H)
            ++word_7006;
        else
            --word_7006;
        return false;
    }
    removeInstruction(gPi);
    ++optimiseCounters[11]; /* 6fd3 opt_msg[11] = "Redundant operations" */
    return hasChanged = true;
}

/**************************************************************************
 42a	sub_3053	ok+-
 **************************************************************************/
bool sub_3053() {
    int l1;
    int l2;
    register inst_t *pi;

    if ((pi = gPi)->iLhs->type != T_REG || ((l1 = pi->iLhs->aux) != REG_HL && l1 != REG_L))
        return false;

    if (!operandsSame((pi = gPi)->iRhs, &regValues[18]))
        return false;

    l2 = word_7006;
    if ((pi = gPi)->iLhs->aux == REG_L) {
        if ((word_6fe5 = pi->pNext)->type != T_LD || (pi = word_6fe5)->iLhs->type != T_REG || pi->iLhs->aux != REG_H ||
            pi->iRhs->oIVal != (pi = gPi)->iRhs->oIVal + 1) /* note last test order might be swapped */
            return false;

        sub_4544(REG_HL);
        regValues[REG_L] = *(pi = gPi)->iLhs;
        regValues[REG_H] = *(pi = word_6fe5)->iLhs;
        removeInstruction(word_6fe5);
    } else {
        sub_4544(REG_HL);
        regValues[REG_HL] = *(pi = gPi)->iLhs;
    }
    gPi = (pi = gPi)->pAlt; /* m4: */
    removeInstruction((pi = gPi)->pNext);
    while (l2 != 0) {
        gPi              = allocInst(gPi);
        (pi = gPi)->type = T_INCDEC;
        (pi = gPi)->iLhs = allocOperand();
        pi->iLhs->type   = T_REG;
        pi->iLhs->aux    = REG_HL;
        if (l2 < 0) {
            ++l2;
            pi->aux = REG_H;
        } else {
            --l2;
            (pi = gPi)->aux = REG_L;
        }
    }
    ++optimiseCounters[12]; /* 6fd5 opt_msg[12] = "Redundant loads/stores" */
    return hasChanged = true;
}

/**************************************************************************
 43	sub_31ee	ok++
 **************************************************************************/
void swapHLDE() {
    operand_t pi;

    pi                 = regValues[REG_HL];
    regValues[REG_HL]  = regValues[REG_DE];
    regValues[REG_DE]  = pi;

    pi                 = regValues[REG_H];
    regValues[REG_H]   = regValues[REG_D];
    regValues[REG_D]   = pi;

    pi                 = regValues[REG_L];
    regValues[REG_L]   = regValues[REG_C];
    regValues[REG_C]   = pi;
    regValues[18].type = 0;
    ;
};

/**************************************************************************
 44	pr_psect	sub_328a	ok++
 **************************************************************************/
void pr_psect(int psect) {

    if (psect == cur_psect)
        return;
    printf("psect\t%s\n", psectNames[psect]);
    cur_psect = psect;
}

/**************************************************************************
 45	num_psect	sub_32bf	ok++
 **************************************************************************/
int num_psect(char *fmt) {
    int l1;

    for (l1 = 0; l1 < 4; ++l1) {
        if (strcmp(fmt, psectNames[l1]) == 0)
            return l1;
    }
    pr_error("Unknown psect");
}

/**************************************************************************
 46	sub_3313	ok+ (PMO) optimiser moves code blocks differently
 **************************************************************************/
term_t *evalExpr() {
    char expectOp;
    op_t *pOp;
    term_t *pTerm;
    term_t termStack[30];
    op_t opStack[30];
    static term_t exprResult; /* so pointer to term can be returned */

    pTerm     = &termStack[30];
    pOp       = &opStack[29];
    pOp->type = T_MARKER;
    pOp->prec = 0;
    expectOp  = 0;
    do {                               /* REDUCE loop */
        for (;;) {                     /* SHIFT loop */
            if (tokType == T_STRING) { /* in expressions "A" is treated as ascii value of A */
                if (strlen(yylval.p_char) != 1)
                    pr_warning("Bad character const");
                yylval.i = *yylval.p_char;
                tokType  = T_CONST;
            }
            if (T_JBWD <= tokType && tokType <= T_CONST) { /* get the term, note two terms together is an error */
                if (expectOp != 0)
                    exp_err();
                expectOp = 1; /* flag as expect operator next */
                --pTerm;      /* where to push the term */
                switch (tokType) {
                case T_SYMBOL: /* its reocatable */
                    pTerm->u.pSym = yylval.pSym;
                    pTerm->ival   = 0;
                    break;
                case T_CONST: /* its a constant */
                    pTerm->ival  = yylval.i;
                    pTerm->tPSym = 0;
                    break;
                }
            } else if (T_UPLUS <= tokType && tokType <= T_0x2D) {                 /* get the operator */
                if (expectOp == 0 && (tokType == T_PLUS || tokType == T_MINUS)) { /* map unary +/- */
                    tokType  = tokType - 7;
                    yylval.i = 8; /* set its precedence */
                }
                if (tokType <= T_MARKER) { /* unary operator only allowed when not expecting op*/
                    if (expectOp)
                        exp_err();
                } else {
                    if (expectOp == 0 && tokType != T_OPAR) /* binary op only when expecting op*/
                        exp_err();
                    if (pOp->prec >= yylval.i) /* pick up precedence */
                        break;
                }
                if (tokType != T_CPAR) { /* not a closing ) */
                    --pOp;
                    pOp->type = tokType;   /* push its type */
                    if (tokType == T_OPAR) /* if it was a ( then set prec to 1 */
                        yylval.i = 1;
                    else
                        expectOp = 0;             /* now expecting a term */
                    pOp->prec = yylval.i;         /* set the prec */
                } else if (pOp->type == T_MARKER) /* ) with nothing on stack */
                    break;
            } else
                break;
            tokType = get_token(); /* keep going */
        }

        /* REDUCE phase */
        if (pOp->type == T_OPAR) { /* check for matching () */
            if (tokType != T_CPAR)
                exp_err();          /* ")" */
            tokType  = get_token(); /* prime for next part */
            expectOp = 1;           /* assuming its a term */
        } else if (T_MARKER >= pOp->type)
            uconv(pOp->type, pTerm); /* calculate unary operator */
        else {
            bconv(pOp->type, pTerm + 1, pTerm); /* calculate binary operator*/
            ++pTerm;
        }
    } while (++pOp != &opStack[30]); /* loop till end of operator stack */

    exprResult = *pTerm;
    if (&termStack[29] != pTerm) /* oops outstanding term */
        exp_err();
    return &exprResult;
}
/**************************************************************************
 47	exp_err		sub_32bf	ok++ (PMO)
 **************************************************************************/
void exp_err() {

    pr_error("Expression error");
}

/**************************************************************************
 48	sub_359e	ok++ (PMO)
 *	Unary Operators
 **************************************************************************/
void uconv(int opCode, term_t *lhs) {

    switch (opCode) {
    case T_UMINUS:
        lhs->ival = -lhs->ival;
        break;
    case T_NOT:
        lhs->ival = ~lhs->ival;
        break;
    case T_HI:
        lhs->ival = (lhs->ival >> 8) & 0xff;
        break;
    case T_LOW:
        lhs->ival &= 0xff;
        break;
    case T_UPLUS:
        return;
    case 0x1B:
        return;
    default:
        pr_error("uconv - bad op");
    }
    if (lhs->tPSym != 0)
        rel_err();
    return;
}

/**************************************************************************
 49	sub_3630	ok++ (PMO)
 *	Binary Operators
 **************************************************************************/
void bconv(int op, term_t *lhs, term_t *rhs) {

    switch (op) {
    case T_PLUS:
        if (lhs->u.pSym != 0 && rhs->u.pSym != 0)
            rel_err();
        lhs->ival += rhs->ival;
        if (lhs->u.pSym == 0)
            lhs->u.pSym = rhs->u.pSym;
        return;
    case T_MINUS:
        if (rhs->u.pSym != 0)
            rel_err();
        lhs->ival -= rhs->ival;
        return;
    case T_MUL:
        lhs->ival *= rhs->ival;
        break;
    case T_DIV:
        lhs->ival /= rhs->ival;
        break;
    case T_MOD:
        lhs->ival %= rhs->ival;
        break;
    case T_SHR:
        lhs->ival >>= rhs->ival;
        break;
    case T_SHL:
        lhs->ival <<= rhs->ival;
        break;
    case T_AND:
        lhs->ival &= rhs->ival;
        break;
    case T_OR:
        lhs->ival |= rhs->ival;
        break;
    case T_XOR:
        lhs->ival ^= rhs->ival;
        break;
    case T_EQ:
        lhs->ival = lhs->ival == rhs->ival;
        break;
    case T_LE:
        lhs->ival = rhs->ival < lhs->ival;
        break;
    case T_GE:
        lhs->ival = lhs->ival < rhs->ival;
        break;
    case T_ULE:
        lhs->ival = (uint)rhs->ival < (uint)lhs->ival;
        break;
    case T_UGE:
        lhs->ival = (uint)lhs->ival < (uint)rhs->ival;
        break;
    default:
        pr_error("Bconv - bad op");
        break;
    }

    if (lhs->u.pSym != 0 || rhs->u.pSym != 0)
        rel_err();
}

/**************************************************************************
 50	rel_err		ok++
 **************************************************************************/
void rel_err() {

    pr_warning("Relocation error");
}

/**************************************************************************
 51	sub_3856	ok++ (PMO) except for one jp z, that is optimised to jr z,
 **************************************************************************/
operand_t *evalOperand() {
    register operand_t *oper;

    oper = allocOperand();

    switch (tokType) {
    case T_EOL:
        oper->aux = 0;
        break;

    case T_REG:
        if (expectCond && yylval.i == REG_C) { /* check if C is used in jp c context */
            tokType  = T_COND;                 /* convert to condition */
            yylval.i = COND_LLT;
        }
        /* fall through */
    case T_COND:
        oper->type = tokType; /* save type, value and prep for next token */
        oper->aux  = yylval.i;
        tokType    = get_token();
        break;

    case T_OPAR:
        if ((tokType = get_token()) == T_REG) {
            if (yylval.i != REG_C && yylval.i < REG_BC) /* only (C) and (BC) onwards are valid */
                oper_err();
            oper->type = T_REGREF;
            oper->aux  = yylval.i;                   /* save reg id */
            if ((tokType = get_token()) == T_CPAR) { /* simple (reg) so prep for next token */
                tokType = get_token();
                break;
            }
            if (oper->aux < REG_IX) /* only IX & IY are allowed expressions */
                oper_err();
            oper->type = T_INDEXED; /* is IX/IY +/- d operand */
        } else
            oper->type = T_ADDRREF; /* is a (addr) operand */

        oper->val = *evalExpr(); /* get the expression */

        if (tokType != T_CPAR) /* should now be the closing ) */
            oper_err();
        tokType = get_token(); /* prep for next token */
        /* IX & IY are only allowed displacements -128 to 127 */
        if (oper->type == T_INDEXED && (oper->oIVal < -128 || oper->oIVal >= 128))
            pr_warning("Index offset too large");
        break;
    /*
        the operands below are only valid as the last operand on a line
        so there is no preping for the next token
    */
    case T_JBWD:
    case T_JFWD:
        oper->type  = tokType;
        oper->oIVal = yylval.i; /* save the label reference number */
        break;
    default:
        oper->type = T_CONST;
        oper->val  = *evalExpr(); /* allow for more complex expression */
    }
    return oper;
}
/**************************************************************************
 52	oper_err	ok
 **************************************************************************/
void oper_err() {

    pr_warning("Operand error");
    longjmp(jmpbuf, 1);
}

/**************************************************************************
 53	sub_39a3	ok++
 **************************************************************************/
void getOperands(register inst_t *pi) {

    tokType    = get_token();
    cntOperand = 0;
    pi->iLhs   = 0;
    pi->iRhs   = 0;
    if (tokType == T_COMM)
        oper_err();         /* cannot start with a comma */
    if (tokType != T_EOL) { /* no operands */
        pi->iLhs = evalOperand();
        if (tokType == T_COMM) { /* if comma then 2nd operand */
            tokType  = get_token();
            pi->iRhs = evalOperand();
            ++cntOperand;
        }
        ++cntOperand;
    }
    clr_len_inbuf();
}

/**************************************************************************
 54	sub_3a15	ok??
 **************************************************************************/

void loadFunction() {
    sym_t *ps;           /* ??? */
    inst_t *l2;          /* ok */
    inst_t *l3;          /* ok */
    int fpBase;          /* ??? */
    register inst_t *pi; /* ok */

    pi = root       = (inst_t *)alloc_mem(sizeof(inst_t));
    pi->pNext       = (inst_t *)alloc_mem(sizeof(inst_t));
    pi->pNext->pAlt = pi;
    pi              = pi->pNext;
    l2 = word_6ff2 = word_6fee = (inst_t *)alloc_mem(sizeof(inst_t));

    for (;;) {
        tokType = get_token();
        for (;;) {
            if (tokType == T_EOL) {
                clr_len_inbuf();
                break;
            }
            if (pi->type != 0)
                pi = allocInst(pi); /* m3: */

            if (tokType == -1) { /* m4: */
                word_6ffc = pi;
                word_6fee = l2;
                return;
            }
            pi->type = tokType; /* m5: */
            if (psect == SWDATA) {
                if (tokType == T_DEFW) { /* collect the switch table */
                    pi->str = yytext;
                    getOperands(pi);
                    l2->pNext       = pi;
                    pi              = pi->pAlt;
                    pi->pNext       = 0;
                    l2->pNext->pAlt = l2;
                    l2              = l2->pNext;
                    break;
                }
                psect = DATA; /* revert to normal data handling */
            }
            switch (pi->type = tokType) { /* m7: */
            case T_CONST:
                if ((psect == DATA) || (psect == BSS)) {
                    pi->type = 0;
                    pr_psect(psect);
                    printf("%d:\n", yylval.i);
                } else {
                    pi->aux = yylval.i; /* m10: */
                    l3      = pi->pAlt;
                    if (pi->pAlt->type == T_JP && l3->iLhs->type == T_JBWD && l3->iLhs->oIVal == pi->aux)
                        removeInstruction(l3);
                }
                tokType = get_token(); /* m11: */
                if (tokType != T_COLN) /* ":" */
                    pr_error("Bad temp label");
                break;

            case T_SYMBOL:
                ps      = yylval.pSym;
                pi->aux = 0;
                tokType = get_token();
                if (tokType == T_EQU) {
                    if (ps->name[0] != 'f') /* compiler generated equ names begin with f */
                        pr_error("Unknown EQU");

                    pi->type = 0;
                    tokType  = get_token();
                    pi->iLhs = evalOperand();
                    /* check is constant with no unresolved symbol ref */
                    if (pi->iLhs->type != T_CONST || pi->iLhs->oPSym)
                        pr_error("Bad arg to EQU");

                    fpBase    = pi->iLhs->oIVal; /* the frame pointer offset to lowest local (will be 0 or -ve) */

                    word_6ffc = pi;
                    word_6fee = l2;
                    pi        = root;

                    do { /* update any references to the frame size */
                        if (pi->iRhs && pi->iRhs->type == T_CONST && pi->iRhs->oPSym == ps) {
                            pi->iRhs->oIVal += fpBase;
                            pi->iRhs->oPSym = 0;
                        }
                        if (pi->iLhs && pi->iLhs->type == T_CONST && pi->iLhs->oPSym == ps) {
                            pi->iLhs->oIVal += fpBase;
                            pi->iLhs->oPSym = 0;
                        }
                    } while (pi = pi->pNext);
                    return;
                }
                pi->iPSym     = ps;

                ps->val.pInst = pi;

                pi->aux       = INT_MAX;
                if (psect == DATA && ps->name[0] == 'S') { /* compiler generated switch tables start with S */
                    psect           = SWDATA;
                    l2->pNext       = pi;
                    pi              = pi->pAlt;
                    pi->pNext       = 0;
                    l2->pNext->pAlt = l2;
                    l2              = l2->pNext;
                }
                if (psect == DATA || psect == BSS) {
                    pi->type      = 0;
                    pi->iLhs      = 0;
                    ps->val.pInst = 0; /*??? */
                    pr_psect(psect);
                    printf("%s:\n", ps->name);
                } else if (ps->name[0] == '_')
                    name_fun = ps->name;

                if (tokType == T_COLN)
                    break;
                continue; /* inner loop */

            case 255: /* -1 */
                pi->type  = 0;
                word_6ffc = pi;
                return;

            case T_DEFW:
            case T_DEFB:
                if (psect == TEXT)
                    goto case_default;
            case T_DEFM:
            case T_DEFS:
            case T_DEFF:
                if (psect == TEXT)
                    pr_error("DEF[BMSF] in text psect");
                pr_psect(psect);
                /* fall through */
            case T_GLB:
                printf("%s\t%s\n", yytext, ptr_token());
                pi->type = 0;
                break;

            case T_PSCT:
                psect    = num_psect(ptr_token()); /* m30: */
                pi->type = 0;
                break;

            case T_JR:
                pi->type = T_JP; /* convert to jp so it is safe to move code */
                yytext   = "jp";
                /* fall through */
            default:
            case_default:
                pi->str    = yytext;
                pi->aux    = yylval.i;
                expectCond = tokType == T_JP || tokType == T_CALL; /* set if can have conditional */
                getOperands(pi);
                if ((pi->type == T_JP) || (pi->type == T_CALL)) {
                    if (pi->iLhs->type == T_COND) { /* if cond then hoist condition and remove lhs */
                        pi->aux  = pi->iLhs->aux;
                        pi->iLhs = pi->iRhs;
                        pi->iRhs = 0;
                    }
                }
                if (pi->type == T_JP && pi->aux == 0 && pi->iLhs->type != T_REGREF &&
                    (l3 = pi->pAlt)->type == T_CONST && l3->pAlt->type == T_JP && l3->pAlt->aux == 0) {

                    while (l3 = l3->pAlt) {
                        if (l3->type == T_JP && l3->iLhs->type == T_JBWD && l3->iLhs->oIVal == pi->pAlt->aux)
                            *l3->iLhs = *pi->iLhs;
                        else if (l3->type == T_CONST && l3->aux == pi->pAlt->aux)
                            break;
                    }
                    removeInstruction(pi->pAlt);
                    freeOperand(pi->iLhs);
                    pi->type = 0;
                    pi->iLhs = 0;
                    pi->str  = 0;
                }
                break;
            }

            break; /* to outer loop */
        }
    }
}

/**************************************************************************
 55	sub_4000	ok+
 **************************************************************************/
bool sub_4000(register inst_t *pi) {

    return pi->type == T_JP && pi->iLhs->oPSym && strcmp(pi->iLhs->oPSym->name, "cret") == 0;
}

/**************************************************************************
 56	sub_404d	ok++	Used in: optimise
 **************************************************************************/
void sub_404d() {

    register inst_t *pi;

    if (root->pNext != 0) {
        pr_psect(TEXT);
        for (pi = root->pNext; pi; pi = pi->pNext) {
            if (pi->type == T_CALL && strcmp(pi->iLhs->oPSym->name, "ncsv") == 0) {
                pi = pi->pNext;
                if (pi->type != T_DEFW) /* "defw" */
                    pr_error("Expecting defw after call ncsv");
                if (pi->iLhs->oPSym != 0) {
                    if (usesIXorIY)
                        printf("global csv\ncall csv\n");
                } else {
                    usesIXorIY = true;
                    if (pi->iLhs->oIVal >= -4) {
                        printf("global csv\ncall csv\npush hl\n");
                        printf("push hl\n"); /* */
                    } else
                        printf("call ncsv\ndefw %d\n", pi->iLhs->oIVal);
                }
            } else if (usesIXorIY == 0 && sub_4000(pi)) {
                pi->type = T_RET;
                pi->str  = 0;
                pr_instruction(pi);
            } else if (usesIXorIY == 0 && pi->type == T_CALL && pi->aux == 0 && pi->pNext->aux == 0 &&
                       sub_4000(pi->pNext) && pi->iLhs->oPSym->name[0] == '_') {
                pi->type = T_JP; /* "jp" */
                pi->str  = 0;
                pr_instruction(pi);
                pi = pi->pNext;
            } else
                pr_instruction(pi);
        }
    }
    if (word_6ff2->pNext) {
        pr_psect(DATA);
        for (pi = word_6ff2->pNext; pi; pi = pi->pNext)
            pr_instruction(pi);
    }
}

/**************************************************************************
 57	sub_420a	ok--
 **************************************************************************/

void pr_instruction(register inst_t *pi) {

    if (pi->type == 0)
        ;
    else if (pi->type == T_SYMBOL) {
        if ((pi->iPSym->name[0]))
            printf("%s:\n", pi->iPSym->name);
        else
            printf("L%d:\n", pi->iSymId);
    } else if (pi->type == T_CONST) { /* m4: */
        printf("%d:\n", pi->aux);
    } else if (key_f && pi->type == T_CALL && strcmp(pi->iLhs->oPSym->name, "csv") == 0) {
        printf("push\tiy\npush\tix\nld\tix,0\nadd\tix,sp\n");
    } else {
        if (key_n)
            fputc('\t', stdout); /* m7: */

        pr_token(pi);

        if (pi->type == T_JP || pi->type == T_CALL || pi->type == T_RET) {
            fputc('\t', stdout);
            if (pi->aux != 0)
                printf("%s", conditions[pi->aux]);
            if (pi->type != T_RET) {
                if (pi->aux != 0)
                    fputc(',', stdout);
                sub_436e(pi->iLhs); /* m11: */
            }
        } else if (pi->iLhs) { /* m14: */
            fputc('\t', stdout);
            sub_436e(pi->iLhs);
            if (pi->iRhs) {
                fputc(',', stdout);
                sub_436e(pi->iRhs);
            }
        }
        fputc('\n', stdout);
    }
}

/**************************************************************************
 58	sub_436e	ok++
 **************************************************************************/
void sub_436e(register operand_t *pi) {

    switch (pi->type) {
    case T_INDEXED:
    case T_ADDRREF:
        fputc('(', stdout);
        if (pi->type == T_INDEXED) {
            if (pi->aux == REG_IX)
                printf("ix");
            else
                printf("iy");
            fputc('+', stdout);
        }
    case T_CONST:
        if (pi->oPSym) {
            if (pi->oPSym->name[0])
                printf("%s", pi->oPSym->name);
            else
                printf("L%d", pi->oPSym->val.pInst->iSymId);
            if (0 < pi->oIVal)
                fputc('+', stdout);
        }
        if (pi->oIVal != 0 || (pi->oPSym == 0))
            printf("%d", pi->oIVal);
        if (pi->type != T_CONST)
            fputc(')', stdout);
        break;
    case T_REGREF:
        fputc('(', stdout);
    case T_REG:
        printf("%s", regs[pi->aux]);
        if (pi->type != T_REGREF)
            return;
        fputc(')', stdout);
        break;
    case T_JBWD:
        printf("%df", pi->oIVal);
        break;
    default:
        pr_error("Bad operand");
        break;
    }
}

/**************************************************************************
 59	sub_44b2	ok+
 *	Generates correct code, but different from original
 **************************************************************************/
void sub_44b2(register operand_t *po) {
    int n;

    while ((n = sub_46b1(po, 0)) != -1)
        sub_4544(n);
    while ((n = sub_46b1(po, 10)) != -1)
        sub_4544(n);

    if (regValues[17].type && operandsSame(po, &regValues[17]))
        sub_4544(17);

    if (regValues[18].type && !operandsSame(&regValues[18], po))
        regValues[18].type = 0;
}

/**************************************************************************
 60	sub_4544	ok+
 *	Generates correct code, but different from original
 **************************************************************************/
void sub_4544(int reg) {
    register operand_t *pi;

    regValues[reg].type = 0;
    if (arry_6cca[0] & regTestMasks[reg]) {
        word_7006          = 0;
        regValues[18].type = 0;
    }
    if (pi = arry_6c6a[reg].lhs) {
        pi->type = 0;
        if (pi = arry_6c6a[reg].rhs)
            pi->type = 0;
    }
    if (reg != 17)
        return;
    for (pi = regValues; pi < &regValues[18]; ++pi)
        if (pi->type == T_INDEXED && pi->aux == REG_IY)
            pi->type = 0;

    if (regValues[18].type == T_INDEXED && regValues[18].aux == REG_IY)
        regValues[18].type = 0;
}

/**************************************************************************
 61	sub_4601	ok+
 *	Generates correct code, but different from original
 **************************************************************************/
void sub_4601() {
    register operand_t *po;

    for (po = regValues; po < &regValues[18]; ++po)
        po->type = 0;
    regValues[18].type = 0;
}

/**************************************************************************
 62	sub_4625	ok+
 *	Generates correct code, but in a sequence different from original
 **************************************************************************/
bool sub_4625(register inst_t *pi) {

    switch (pi->type) {
    case T_STK:
    case T_LD:
        return true;
    case T_INCDEC:
        return pi->iLhs->type == T_REG && pi->iLhs->aux < REG_BC;
    case T_EX:
        return pi->iLhs->aux != REG_AF;
    }
    return false;
}

/**************************************************************************
 63	sub_4682	ok++
 **************************************************************************/
bool sub_4682(register operand_t *pi) {

    return pi->type == T_CONST && pi->oPSym == 0 && pi->oIVal == 0;
}

/**************************************************************************
 64	sub_46b1	ok++
 **************************************************************************/
int sub_46b1(register operand_t *opr, int reg) {
    operand_t *po;
    int i;

    po = reg < REG_BC ? &regValues[REG_B] : &regValues[REG_BC];
    do {
        if (po->type) {
            if (operandsSame(po, opr)) {
                i = (int)(po - regValues);
                if (i >= REG_BC && reg < REG_BC)
                    return l6c50h[i].c1;
                return i;
            }
        }
    } while (++po < &regValues[REG_SP]);
    return -1;
}

/**************************************************************************
 65	sub_475c	ok++
 **************************************************************************/
bool sub_475c(register operand_t *pi, int p2) {

    return pi && (pi->type == T_REG || pi->type == T_INDEXED || pi->type == T_REGREF) && (p2 & regTestMasks[pi->aux]);
}

/**************************************************************************
 66	sub_47a2	ok++
 **************************************************************************/
bool sub_47a2(register operand_t *pi, int p2) {

    return pi && pi->type == T_REG && (p2 & regTestMasks[pi->aux]);
}

/**************************************************************************
 67	sub_47e0	ok++
 *	Generated code is different from the original
 **************************************************************************/
bool sub_47e0(int reg, register inst_t *pi1, inst_t *pi2) {
    uint msk;
    sym_t *ps;
    inst_t *l3;
    int n; /* number of iterations */

    if (reg == REG_SP || reg == REG_IX)
        return true;

    if (REG_BC <= reg && reg <= REG_HL) {
        if (sub_47e0(l6c50h[reg].c0, pi1, pi2))
            return true;
        reg = l6c50h[reg].c1;
    }
    msk = regTestMasks[reg]; /* m3: */
    n   = 40;

    do {
        switch (pi1->type) {

        case T_CALL: /* "call" */
            if (pi1->aux != 0 && (msk & 0x40))
                return true;

            if (reg == REG_IY)
                break;
            if (pi1->iLhs->oPSym == 0 || pi1->iLhs->oPSym->name[0] == '_')
                return false;

            return (msk & 0xBF) != 0;

        case T_JP: /* "jp" */
            if (pi1->aux != 0 || pi1->iLhs->type == T_REGREF || (ps = pi1->iLhs->oPSym) == 0)
                return true;
            if ((l3 = ps->val.pInst) == 0)
                return strcmp(ps->name, "cret") != 0 || (msk & 0x3C);
            pi1 = l3;
            break;

        case T_ONEBYTE:         /* 0x1 */
            switch (pi1->aux) { /* m14: */
            case 0:             /* "nop" */
            case P_CPL:         /* "cpl" */
            case P_SCF:         /* "scf" */
            case P_CCF:         /* "ccf" */
            case P_NEG:         /* "neg" */
            case P_HALT:
            case P_DI: /* "di" */
            case P_EI:
                break;
            case P_EXX:
                while ((pi1 = pi1->pNext) && (pi1->type != T_ONEBYTE || pi1->aux != P_EXX))
                    if (pi1->type != T_LD && pi1->type != T_STK && pi1->type != T_CADD)
                        return false;
                if (pi1 == 0)
                    return false;
                break;
            default:
                if (msk & 0x80)
                    return true;
                break;
            }
            break;
        case T_TWOBYTE: /* 0x2 */
            if (reg != 17)
                return true;
            break;

        case T_3:
            if (pi1->aux == P_XOR) /* "xor"				//m22: */
                if (pi1->iLhs->type == T_REG && pi1->iLhs->aux == REG_A && reg == REG_A)
                    return false;
            if (msk & 0x80)
                return true; /* m23: */
            if (msk & 0x40)
                return false;
            if (sub_475c(pi1->iLhs, msk))
                return true;
            break;

        case T_6:
            if ((pi1->aux & 0xFFE7) != 0x20 && (msk & 0x40))
                return true;

        case T_INCDEC: /* 0x4 "dec", "inc" */
            if ((msk & 0x40) && (pi1->iLhs->type != T_REG || pi1->iLhs->aux < REG_BC))
                return false;
            if (pi1->iLhs->type == T_REG || sub_475c(pi1->iLhs, msk))
                return true;
            break;

        case T_BIT: /* "set", "res", "bit" */
            if (pi1->aux == 0x40 && (msk & 0x40))
                return false;

        case T_0xF: /* 0xF */
            if (sub_475c(pi1->iRhs, msk) || sub_475c(pi1->iLhs, msk))
                return true;
            break;

        case T_5:
            break;

        case T_DJNZ: /* "djnz" */
            if (msk & 1)
                break;
            return true;

        case T_0xE: /* 0xE */
            if (sub_475c(pi1->iRhs, msk))
                return true;
            if (sub_47a2(pi1->iLhs, msk))
                return false;
            break;

        case T_STK:
            if (pi1->aux == P_PUSH && (msk & regTestMasks[pi1->iLhs->aux]))
                return true;
            if (msk & regTestMasks[pi1->iLhs->aux])
                return false;
            break;

        case T_EX: /* "ex" */
            if (pi1->iLhs->type == T_REGREF && (msk & regTestMasks[pi1->iRhs->aux]))
                return true;
            if (msk & 0x3C)
                return true;
            break;

        case T_CADD: /* CADD */
            if (msk & 0x40)
                return false;

        case T_CARR: /* Add, sub with Carry */
            if ((regTestMasks[pi1->iLhs->aux] | 0x40) & msk)
                return true;
            if (sub_475c(pi1->iRhs, msk))
                return true;
            break;
        case T_LD: /* load */
            if (!operandsSame(pi1->iLhs, pi1->iRhs))
                return sub_475c(pi1->iRhs, msk) || (!sub_47a2(pi1->iLhs, msk) && sub_475c(pi1->iLhs, msk));
            break;

        case 0: /* 0x00 */
            return ((msk & 0x3C) != 0);
        case T_JR: /* 0x9 "jr" */
        case T_RET:
        case T_RST: /* 0xD "rst" */
            break;
        }
        pi1 = pi1->pNext;
        if (pi2 == pi1)
            return false;
    } while (n-- != 0);
    return true;
}

#define HASHSIZE 311
sym_t *hashtab[HASHSIZE]; /* 7086	[622] */

/**************************************************************************
 68	sub_4c33	ok+	Used in: sub_4cf0, sub_4da7
 **************************************************************************/
sym_t *allocSym() {
    register sym_t *pi;

    pi = (sym_t *)freeSymbolList; /* check the free list*/
    if (pi) {                     /* if there is an entry release it*/
        freeSymbolList = ((list_t *)pi)->pNext;
        pi->name       = 0;
        pi->val.pSym   = 0;
        return pi;
    }
    return (sym_t *)alloc_mem(sizeof(sym_t)); /* else allocate a new one */
}

/**************************************************************************
 69	sub_4c6b	ok+
 **************************************************************************/

void freeSymbol(register sym_t *pi) {

    if (strlen(pi->name) >= sizeof(sym_t)) { /* if string could be reused as a symbol at it to the free list*/
        ((list_t *)(pi->name))->pNext = freeSymbolList;
        freeSymbolList                = (list_t *)(pi->name);
    }
    ((list_t *)pi)->pNext = freeSymbolList; /* add the symbol to the free list */
    freeSymbolList        = (list_t *)pi;
}

/**************************************************************************
 70	hash_index	sub_4cab	ok++	Used in: sub_4cf0
 **************************************************************************/
int hash_index(register uchar *p, int size) {
    uint hash;

    for (hash = 0; *p != 0; ++p)
        hash += *p + hash;
    return hash % size;
}

/**************************************************************************
 71	sub_4cf0	ok++ (PMO)			Used in: get_token
 **************************************************************************/

sym_t *lookupSym(register char *p1) {
    sym_t **l1;
    sym_t *l2;

    l1 = &hashtab[hash_index((uchar *)p1, HASHSIZE)];
    while (*l1 && strcmp((*l1)->name, p1))
        if (++l1 == &hashtab[HASHSIZE])
            l1 = hashtab;
    if (l2 = *l1)
        return l2;
    *l1 = l2 = allocSym();
    l2->name = alloc_mem((int)strlen(p1) + 1);
    strcpy(l2->name, p1);
    return l2;
}

/**************************************************************************
 72	sub_4da7	ok++
 **************************************************************************/
sym_t *allocBlankSym() {
    register sym_t *pi;

    pi       = allocSym();
    pi->name = "";
    return pi;
}

/**************************************************************************
 73	sub_4dbf	ok++			Used in: optimise
 **************************************************************************/
void resetHeap() {
    int *p;

    if (programBreak == 0)
        programBreak = sbrk(0); /* current base of heap */
    else
        brk(programBreak);      /* reset the heap */
    alloct = allocs = programBreak;

    for (p = (int *)hashtab; p < (int *) & hashtab[HASHSIZE]; p++)
        *p = 0;
    freeSymbolList = 0;
}

/**************************************************************************
 74	sub_4e20	ok++			Used in: optimise
 **************************************************************************/
void sub_4e20() {

    allocs = (char *) & hashtab;       /* */
    alloct = (char *) & hashtab[HASHSIZE]; /* */
}

/**************************************************************************
 75	alloc_mem	sub_4e2d	ok+
 *
 *	A larger even number is used as size
 **************************************************************************/
void *alloc_mem(int size) {
    char *p;
    register char *pi;

    if (alloct < (allocs + (size = (size + 1) & 0xFE))) {
        if ((allocs = sbrk(512)) == (char *)-1)
            pr_error("Out of memory in %s", name_fun);
        alloct = sbrk(0);
    }
    pi = allocs;
    allocs += size;
    p = pi;
    while (size-- != 0)
        *p++ = 0; /* Clearing allocated memory area */
    return pi;
}

/**************************************************************************

#######				####### ######  #######   ###   #     #
#        #    #  #####		#     # #     #    #       #    ##   ##
#        ##   #  #    #		#     # #     #    #       #    # # # #
#####    # #  #  #    #		#     # ######     #       #    #  #  #
#        #  # #  #    #		#     # #          #       #    #     #
#        #   ##  #    #		#     # #          #       #    #     #
#######  #    #  #####		####### #          #      ###   #     #

*/
