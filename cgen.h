#ifndef _CGEN_H
#define _CGEN_H 1
/* File cgen.h Created 17.05.2019 Last Modified 17.06.2020 */

/* Not a commercial goal of this laborious work is to popularize among
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
 * The solution to this problem is to recreate the object code being moved,
 * replace the CP/M system functions (I/O, memory allocation, etc.) with
 * similar UZI-180 calls, and compile an executable file for this operating
 * system.
 */

/*
#define DEBUG
*/
#include <assert.h>
#include <ctype.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__STDC__) || defined(__STDC_VERSION__)
#include <stdbool.h>
#include <stdint.h>
#else
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
#ifndef bool
#define bool char
#define true 1
#define false 0
#endif
#define const
#define MININT -32768 /* min for int (0x8000)	*/
#define MAXINT 32767  /* max for int (0x7fff)	*/

#endif
#undef max /* replaced by function call */
/*
 *	Constant declarations
 */

#define MAXFUN  0x20 /* Maximum limit nested function */
#define MAXBUF  60   /* Maximum buffer size 		*/
#define MAXNAME 40   /* Maximum file name length	*/
#define MAXERR  30   /* Maximum number nonfatal errors*/

#if 1
#define NULSTR   0    /*  0  ""	*/
#define NOT      1    /*  1  "!"	*/
#define NEQL     2    /*  2  "!="	*/
#define HASHSIGN 3    /*  3  "#"	*/
#define DOLLAR   4    /*  4  "$"	*/
#define DOLLAR_U 5    /*  5  "$U"	*/
#define MOD      6    /*  6  "%"	*/
#define BAND     7    /*  7  "&"	*/
#define LAND     8    /*  8  "&&"	*/
#define GADDR    9    /*  9  "&U"	*/
#define LPAREN   0xA  /* 10  "("	*/
#define RPAREN   0xB  /* 11  ")"	*/
#define MUL      0xC  /* 12  "*"	*/
#define MUL_U    0xD  /* 13  "*U"	*/
#define ADD      0xE  /* 14  "+"	*/
#define INCR     0xF  /* 15  "++"	*/
#define PLUS_U   0x10 /* 16  "+U"	*/
#define COMMA    0x11 /* 17  ","	*/
#define SUB      0x12 /* 18  "-"	*/
#define DECR     0x13 /* 19  "--"	*/
#define CONV     0x14 /* 20  "->"	*/
#define MINUS_U  0x15 /* 21  "-U"	*/
#define DOT      0x16 /* 22  "."	*/
#define DOT_DOT  0x17 /* 23  ".."	*/
#define DIV      0x18 /* 24  "/"	*/
#define COLON    0x19 /* 25  ":"	*/
#define COLON_U  0x1A /* 26  ":U"	*/
#define COLON_S  0x1B /* 27  ":s"	*/
#define SCOLON   0x1C /* 28  ";"	*/
#define T_SCOLON 0x1D /* 29  ";;"	*/
#define LT       0x1E /* 30  "<"	*/
#define LSHIFT   0x1F /* 31  "<<"	*/
#define LEQ      0x20 /* 32  "<="	*/
#define ASSIGN   0x21 /* 33  "="	*/
#define ASMOD    0x22 /* 34  "=%"	*/
#define ASAND    0x23 /* 35  "=&"	*/
#define ASMUL    0x24 /* 36  "=*"	*/
#define ASADD    0x25 /* 37  "=+"	*/
#define ASSUB    0x26 /* 38  "=-"	*/
#define ASDIV    0x27 /* 39  "=/"	*/
#define ASLSHIFT 0x28 /* 40  "=<<"	*/
#define EQL      0x29 /* 41  "=="	*/
#define ASRSHIFT 0x2A /* 42  "=>>"	*/
#define ASEXOR   0x2B /* 43  "=^"	*/
#define ASEOR    0x2C /* 44  "=|"	*/
#define GT       0x2D /* 45  ">"	*/
#define GEQ      0x2E /* 46  ">="	*/
#define RSHIFT   0x2F /* 47  ">>"	*/
#define QUEST    0x30 /* 48  "?"	*/
#define ATGIGN   0x31 /* 49  "@"	*/
#define CASE     0x32 /* 50  "[\\"	*/
#define UNKNOWN  0x33 /* 51  "[a"	*/
#define ENUM     0x34 /* 52  "[c"	*/
#define EXPR     0x35 /* 53  "[e"	*/
#define INIT     0x36 /* 54  "[i"	*/
#define STRUCT   0x37 /* 55  "[s"	*/
#define UNION    0x38 /* 56  "[u"	*/
#define VAR      0x39 /* 57  "[v"	*/
#define BXOR     0x3A /* 58  "^"	*/
#define LBRACE   0x3B /* 59  "{"	*/
#define BOR      0x3C /* 60  "|"	*/
#define LOR      0x3D /* 61  "||"	*/
#define RBRACE   0x3E /* 62  "}"	*/
#define BNOT     0x3F /* 63  "~"	*/
#define RECIP    0x40 /* 64  "RECIP"   */
#define TYPEOP   0x41 /* 65  "TYPE"    */
#define IDOP     0x42 /* 66  "ID"	*/
#define CONST    0x43 /* 67  "CONST"   */
#define FCONST   0x44 /* 68  "FCONST"  */
#define USEREG   0x45 /* 69  "REG"     */
#define INAREG   0x46 /* 70  "INAREG"  */
#define BFIELD   0x47 /* 71  "BITFIELD"*/
#else
enum op {
    NULSTR,   /*  0  0  ""	*/
    NOT,      /*  1  1  "!"	*/
    NEQL,     /*  2  2  "!="	*/
    HASHSIGN, /*  3  3  "#"	*/
    DOLLAR,   /*  4  4  "$"	*/
    DOLLAR_U, /*  5  5  "$U"	*/
    MOD,      /*  6  6  "%"	*/
    BAND,     /*  7  7  "&"	*/
    LAND,     /*  8  8  "&&"	*/
    GADDR,    /*  9  9  "&U"	*/
    LPAREN,   /* 10  A  "("	*/
    RPAREN,   /* 11  B  ")"	*/
    MUL,      /* 12  C  "*"	*/
    MUL_U,    /* 13  D  "*U"	*/
    ADD,      /* 14  E  "+"	*/
    INCR,     /* 15  F  "++"	*/
    PLUS_U,   /* 16 10  "+U"	*/
    COMMA,    /* 17 11  ","	*/
    SUB,      /* 18 12  "-"	*/
    DECR,     /* 19 13  "--"	*/
    CONV,     /* 20 14  "->"	*/
    MINUS_U,  /* 21 15  "-U"	*/
    DOT,      /* 22 16  "."	*/
    DOT_DOT,  /* 23 17  ".."	*/
    DIV,      /* 24 18  "/"	*/
    COLON,    /* 25 19  ":"	*/
    COLON_U,  /* 26 1A  ":U"	*/
    COLON_S,  /* 27 1B  ":s"	*/
    SCOLON,   /* 28 1C  ";"	*/
    T_SCOLON, /* 29 1D  ";;"	*/
    LT,       /* 30 1E  "<"	*/
    LSHIFT,   /* 31 1F  "<<"	*/
    LEQ,      /* 32 20  "<="	*/
    ASSIGN,   /* 33 21  "="	*/
    ASMOD,    /* 34 22  "=%"	*/
    ASAND,    /* 35 23  "=&"	*/
    ASMUL,    /* 36 24  "=*"	*/
    ASADD,    /* 37 25  "=+"	*/
    ASSUB,    /* 38 26  "=-"	*/
    ASDIV,    /* 39 27  "=/"	*/
    ASLSHIFT, /* 40 28  "=<<"	*/
    EQL,      /* 41 29  "=="	*/
    ASRSHIFT, /* 42 2A  "=>>"	*/
    ASEXOR,   /* 43 2B  "=^"	*/
    ASEOR,    /* 44 2C  "=|"	*/
    GT,       /* 45 2D  ">"	*/
    GEQ,      /* 46 2E  ">="	*/
    RSHIFT,   /* 47 2F  ">>"	*/
    QUEST,    /* 48 30  "?"	*/
    ATGIGN,   /* 49 31  "@"	*/
    CASE,     /* 50 32  "[\\"	*/
    UNKNOWN,  /* 51 33  "[a"	*/
    ENUM,     /* 52 34  "[c"	*/
    EXPR,     /* 53 35  "[e"	*/
    INIT,     /* 54 36  "[i"	*/
    STRUCT,   /* 55 37  "[s"	*/
    UNION,    /* 56 38  "[u"	*/
    VAR,      /* 57 39  "[v"	*/
    BXOR,     /* 58 3A  "^"	*/
    LBRACE,   /* 59 3B  "{"	*/
    BOR,      /* 60 3C  "|"	*/
    LOR,      /* 61 3D  "||"	*/
    RBRACE,   /* 62 3E  "}"	*/
    BNOT,     /* 63 3F  "~"	*/
    RECIP,    /* 64 40  "RECIP"   */
    TYPEOP,   /* 65 41  "TYPE"    */
    IDOP,     /* 66 42  "ID"	    */
    CONST,    /* 67 43  "CONST"   */
    FCONST,   /* 68 44  "FCONST"  */
    USEREG,   /* 69 45  "REG"     */
    INAREG,   /* 70 46  "INAREG"  */
    BFIELD    /* 71 47  "BITFIELD"*/
};
#endif

/* register indexes*/
#define REG_A              1
#define REG_C              2
#define REG_B              3
#define REG_E              4
#define REG_D              5
#define REG_L              6
#define REG_H              7
#define REG_IX             8
#define REG_IY             9
#define REG_SP             10
#define REG_AF             11
#define REG_BC             12
#define REG_DE             13
#define REG_HL             14
#define REG_DEHL           15

/*
 * Classes
 */

#define MEMBER             0x16 /*     */
#define EDECL              0x34 /* '4' */
#define SDECL              0x37 /* '7' */
#define UDECL              0x38 /* '8' */
#define DECL9              0x39 /* '9' */
#define TDECL              0x41 /* 'A' */

/*
 *	Used macros
 */

#define LO_CHAR(a)         *((unsigned char *)&a)
#define HI_CHAR(a)         *(((unsigned char *)&a) + 1)
#define LO_WORD(a)         *((unsigned int *)&a)
#define HI_WORD(a)         *(((unsigned int *)&a) + 1)
#define LO_BYTE(n)         ((uint8_t *)&(n))[0]
#define HI_BYTE(n)         ((uint8_t *)&(n))[1]

#define bittst(var, bitno) ((var)&1 << (bitno))
#define bitset(var, bitno) ((var) |= 1 << (bitno))
#define bitclr(var, bitno) ((var) &= ~(1 << (bitno)))

#ifndef uchar
#define uchar unsigned char
#endif

#define container_of(ptr, type, member) ((type *)((char *)(ptr) - (char *)(&((type *)0)->member)))
/* enums */
enum psect { P_BSS = 1, P_TEXT, P_DATA };

/*
 *	Structural declarations
 */

union pw {
    int *pi;
    char *pc;
    struct aaa *pst;
    int i;
    unsigned int ui;
    char ch[2];
    uchar uch[2];
};

union lw {
    long l;
    unsigned long ul;
    struct aaa *wi[2];
    struct bbb *vi[2];
    char *ci[2];
    uint8_t *puc[2];
    char bc[4];
    int *pl[2];
    unsigned long *lp[2];
    unsigned ii[2];
};

typedef struct aaa {    /* Offset  	Used values  &  Description	*/
    uchar a_c0;         /* +0  0	0 - 0x47			*/
    uchar a_c1;         /* +1  1					*/
    uchar a_c2;         /* +2  2	0, 1, 2,			*/
    uchar a_c3[4];      /* +3  3					*/
                        /* +4  4					*/
                        /* +5  5					*/
                        /* +6  6					*/
    uchar a_c7[2];      /* +7  7					*/
                        /* +8  8					*/
    unsigned int a_u9;  /* +9  9					*/
                        /* +A 10					*/
    unsigned a_ib;      /* +B 11					*/
                        /* +C 12					*/
    unsigned int a_ud;  /* +D 13					*/
                        /* +E 14					*/
    uint8_t a_reg[2];   /* +F 15					*/
                        /*+10 16					*/
    int a_i10;          /*+11 17					*/
                        /*+12 18					*/
    int *a_pi13;        /*+13 19					*/
                        /*+14 20					*/
    unsigned int a_i15; /*+15 21					*/
                        /*+16 22					*/
    struct bbb *a_s17;  /*+17 23					*/
                        /*+18 24					*/
    union lw a_l19;     /*+19 25					*/
                        /*+1A 26					*/
                        /*+1B 27					*/
                        /*+1C 28					*/
} aaa_t;

typedef struct bbb {    /* Offset Member Description			*/
    char *b_name;       /* +0   0 s_name Pointer to Name identifier 	*/
                        /* +1   1					*/
    char b_class;       /* +2	2 s_class	    0x16 - MEMBER 	*/
                        /*			    '4' -  EDECL	*/
                        /*			    '7' -  SDECL 	*/
                        /*			    '8' -  UDECL	*/
                        /*			    '9' - 		*/
                        /*			    'A' -  TYPE		*/
    char b_c3;          /* +3	3 s_strg Bits used: 0 0000001 -		*/
                        /*		            1 0000010 -	global?	*/
                        /*		            2 0000100 -		*/
                        /*		            3 0001000 -	register?*/
                        /*		            4 0010000 -		*/
    uint8_t b_ndpth;    /* +4	4 s_ndpth Nesting depth of block	*/
    uint8_t b_b5;       /* +5   5					*/
    uint8_t b_b6;       /* +6   6					*/
    struct bbb *b_next; /* +7   7					*/
                        /* +8   8					*/
    unsigned b_size;    /* +9   9 s_size Type size			*/
                        /* +A  10					*/
    int b_nelem;        /* +B  11 s_nelem				*/
                        /* +C  12					*/
    uint16_t b_refl;    /* +D  13 s_refl				*/
                        /* +E  14					*/
    struct bbb *b_type; /* +F  15 s_type				*/
                        /* +10 16					*/
    int b_i11;          /* +11 17 s_alig Type alig  size stack frame	*/
                        /* +12 18					*/
    union {
        int i;
        struct {
            uint16_t cnt;
            struct bbb *vals[]; /* to be confirmed */
        } *p;
    } b_memb;
    /* +14 20					*/
    char b_c15; /* +15 21	 type flag 0, 1, 2, 3, 4, 5,	*/
} bbb_t;

struct zzz {
    char c_0;
    char c_1;
    char c_2;
    char c_3;
    char c_4;
    char c_5;
    char *p_6;
    char *p_8;
};

struct ptr {
    struct ptr *next_ptr;
};

struct header1 {
    uchar size;
    struct ptr next;
};

struct header2 {
    unsigned size;
    char aaa;
    struct ptr next;
};

struct type {
    char *t_str;
    int t_size;
    int t_alig;
    char t_flag;
};

/*
 *	Descriptions of variables and arrays
 *
 * Declarations are located in sequence of being in
 * original binary image of CGEN.COM
 *					Purpose				Where it is used
 * ===== Start bss section ======= */
extern char buffer[MAXBUF];                               /* getToken  */
extern int lineno;                                        /* getToken, sub_6AD0, prMsg*/
extern char progname[MAXNAME]; /*			   */         /* getToken  */
extern bool frameGlobalsEmitted; /* First call ncsv	   */ /* sub_2BD0 */
extern int curPsect; /*  Current section	   */         /* selpsect  */
extern int swTableCnt; /*			   */                 /* sub_174C */
extern bbb_t *word_AE11; /* "l" - long		   */         /* sub_1680, sub_415E, sub_43EF */
extern int array_AE13[MAXFUN]; /*			   */         /* leaveBlock,  sub_17E0, sub_5CF5 */
extern bbb_t *word_AE53;                                  /* "uc" - unsigned char	   */
extern unsigned nstdpth;                                  /* Current nesting depth   */
extern int array_AE57[MAXFUN];                            /*			   */
extern int array_AE97[MAXFUN];                            /*			   */
extern bbb_t *word_AED7;                                  /* "d" - double 	   */
extern bbb_t *word_AED9;                                  /* "c" - char 		   */
extern bbb_t *array_AEDB[MAXFUN];                         /*			   */
extern bbb_t *word_AF1B;                                  /* "b"			   */
extern bbb_t *word_AF1D;                                  /* "x"			   */
#define HASHTABSIZE 101
extern bbb_t *hashtab[HASHTABSIZE];              /* hash table (array_AF1F) */
extern bbb_t *word_AFE9;                         /* "v" - variable  	   */
extern int lvlidx; /* Level nested function   */ /* leaveBlock, sub_1680 */

extern int word_AFED;   /* sub_1F4B */
extern char *word_AFEF; /* sub_1F4B */
extern char *word_AFF1; /* sub_1F4B */
extern char byte_AFF3;  /* sub_1F4B */
extern int word_AFF4;   /* sub_1F4B */
extern int word_AFF6;   /* sub_1F4B */

extern int word_AFF8;                                 /* sub_2D09, sub_3564 */
extern char byte_AFFA;                                /* sub_283E, sub_2B79 */
extern int word_AFFB;                                 /* sub_2D09, sub_35E6 */
extern aaa_t *array_AFFD[0x14];                       /* sub_3CDF, sub_3DC9 */
extern void *aaaFreeList;                            /* sub_36E0, allocAaa, releaseAaaFreelist */
extern char byte_B013;                                /* sub_36E0, allocAaa, ... */
extern uchar byte_B014;                               /* sub_3CDF, sub_3DC9 */
extern char *word_B015;                               /* msgptr  Pointer str printf       */
extern int word_B017;                                 /* leaveBlock, sub_6D1, sub_283E, sub_2BD0, sub_61AA */
extern bool wflag; /* Warning messages	    */        /* main, sub_6AD0 */
extern bool pflag; /* Not used		    */            /* main */
extern bool hflag; /* Not used		    */            /* main */
extern int errcnt; /* Number of errors	    */        /* main, prError */
extern bool bflag; /* Not used		    */            /* main */
extern char *baseHeap; /* Current highest memory   */ /* main */
extern bool eflag; /* Not used		    */            /* main */
extern bool rflag; /*			    */                /* main, sub_61AA */

/* static uint8_t *freelist; B024 */

#if 0
extern int          word_B026;						/* sprintf */
extern int          word_B028;						/* sprintf */
extern char         byte_B02E;						/* pnum, doprnt */
extern int          word_B02F;						/* pputc */
extern char         byte_B031;						/* pnum, doprnt */
extern char         buf_B032[512];					/* pnum, doprnt */
extern int          __argc_;						/* startup */
extern int          memtop;
#endif /* brk, sbrk */
/* ===== End of bss section ======= */

/* ===== Start data section ======= */

extern char *array_805F[];         /*+sub_2D09 */
extern struct zzz array_80EF[];    /* sub_1F4B, sub_283E, sub_2D09, sub_3564 */
extern int array_987D[];           /*+sub_13D  */
extern unsigned char array_990D[]; /*+sub_13D  */
extern int array_9BD4[];           /*+sub_13D  */
extern int array_A162[];           /*+sub_1F4B */
extern char *tnames[];             /*+sub_1B2  */

extern char byte_A46A; /* Initial value middle  */ /*+sub_1B2  */
                                                   /* element used in binary search */
extern char array_A542[];                          /*+sub_153A */
extern char *off_A592[];                           /*+selpsect  */
extern int dopetab[72];                            /*+sub_1F4B, sub_2B8A, sub_2D09, sub_35E6, sub_377A, ... */
extern char array_A94A[];                          /*+sub_1F4B */
extern int array_AAE8[];   /*+leaveBlock,  sub_1F4B, sub_283E, sub_61AA, sub_63B8, sub_6589, sub_66BC */
extern uchar array_AB24[]; /*+sub_283E, sub_2D09, sub_665B */
extern uchar array_AB54[]; /*+sub_63B8, sub_6589 */

extern struct type vars[14]; /* sub_1680 */
extern char *regNames[];

/*
 * Added dummy variable "empty" to eliminate sub_5CF5 function
 * call with different number of parameters
 */

/*
extern int	    empty;
extern FILE	   *f_out, *f_in;
*/

/* ===== End of data section ======= */

/*
 * Function prototype
 *
 * Missing Hi-Tech C header files
 */

/*
long	     atol(char *str);
*/
#ifdef CPM
/* long atoi(char *);*/
#endif
#ifdef CPM
void blkclr(char *, unsigned short size);
#else
#define blkclr(buf, len) memset(buf, 0, len)
#endif
void *sbrk(int);
/****************************************************************
 * Prototype functions are located in sequence of being in
 * original binary image of CGEN.COM
 *
 * ok++ - Full binary compatibility with code in original file;
 * ok+  - Code generated during compilation differs slightly,
 *        but is logically correct;
 * ok   - C source code was compiled successfully, but not verified.
 ****************************************************************/
/* lex.c ----------------------------------------------------------------------*/
int sub_13D(int, int);                  /*.ok+  sub_13D.c	*/
char sub_1B2(char *);                   /* ok++ sub_1B2.c	*/
bbb_t **gethashptr(char *); /*sub_21F*/ /* ok++			*/
bbb_t *sub_265(char *);                 /* ok++			*/
char *getToken(void);                   /*.ok+  getToken.c	*/
void leaveBlock(void);                  /*.ok+  leaveBlock.c	*/
bbb_t *sub_627(char *, unsigned *);     /* ok++ 		*/
void sub_6C8(void);                     /* ok++ 		*/
void sub_6D1(void);                     /*.ok+  sub_6D1.c	*/
void expect(char);                      /* ok++ sub_76F.c	*/
void sub_793(void);                     /* ok++ 		*/
/* code.c ----------------------------------------------------------------------*/
int sub_808(bbb_t *, aaa_t *); /*.ok+  sub_808.c	*/
void sub_B19(void);            /* ok++ sub_B19.c	*/
void prFrameHead(int);         /* ok++ 		*/
void prFrameTail(int, int);    /* ok++ 		*/
void sub_BEE(int, int);        /* ok++ 		*/
void prGlobalDef(bbb_t *);     /* ok++ 		*/
void sub_C57(bbb_t *);         /* ok++ 		*/
void sub_CAB(bbb_t *);         /* ok++ 		*/
void prDefb0s(int);            /* ok++ 		*/
void prPsect(int); /*sub_D37*/ /* ok++ 		*/
void sortCaseLabels(int *pCase, int *pLabel, int nCase);
void sub_E43(void);               /* ok++ 		*/
void sub_1420(int);               /* ok++ 		*/
void prPush(uchar);               /* ok++ 		*/
void prPop(uchar);                /* ok++ 		*/
void sub_14D3(bbb_t *);           /* ok++ 		*/
uint8_t sub_14F3(aaa_t *);           /* ok++ 		*/
void sub_153A(aaa_t *);           /* ok++ 		*/
void prDefb(char *, int);         /* ok++ 		*/
void prJmpLabel(int);               /* ok++ 		*/
void prJump(int);               /* ok++ 		*/
void sub_15FB(bbb_t *, int, int); /* ok++ 		*/
int max(int, int);           /* ok++ sub_1659.c	*/
void sub_1680(void);              /* ok++ sub_1680.c	*/
int newSwTable(void);               /* ok++ 		*/
bbb_t *sub_1754(char *, uint8_t);     /* ok++ 		*/
/* sym.c -----------------------------------------------------------------------*/
void sub_17E0(void); /*.ok+  sub_17E0.c	*/
void sub_19C1(int);  /* ok++ sub_19C1.c	*/

void sub_1B0C(void);                         /* missing pop bc	   ok+			*/
int sub_1C6D(int, int);                      /* ok++ sub_1C6D.c	*/
int varSize(bbb_t *);                        /* ok++ varSize.c	*/
int sub_1CC4(bbb_t *);                       /* ok++ 		*/
void sub_1CEF(bbb_t *);                      /* ok++ 		*/
void sub_1EDF(void);                         /* ok++ 		*/
int sub_1F4B(aaa_t *, int, int, int, int *); /*.ok+  optim: out of memory */
int sub_283E(aaa_t *, int);                  /*.ok+  sub_283E.c	*/
int sub_2B2A(aaa_t *);                       /*.ok+  sub_2B2A.c	*/
uchar sub_2B79(aaa_t *);                     /* ok+  sub_2B79.c	*/
/* cgen.c ----------------------------------------------------------------------*/
void sub_2BD0(aaa_t *);                    /* ok++			*/
long sub_2C5E(aaa_t *, long);              /*.ok+  sub_2C5E.c	*/
void sub_2CE0(aaa_t *, long);              /* ok++ sub_2CE0.c	*/
void sub_2D09(aaa_t *, char *, int);       /*.ok   optim: out of memory */
void sub_3564(aaa_t *);                    /*.ok+  sub_3564.c	*/
void sub_35E6(aaa_t *);                    /*.ok+  		*/
void freeAaa(aaa_t *);                     /* ok++ 		*/
aaa_t *allocAaa(void);                     /* ok++ 		*/
bool releaseAaaFreelist(void);             /* ok++ 		*/
aaa_t *sub_377A(aaa_t *);                  /* ok++ 		*/
void sub_37ED(aaa_t *);                    /* ok++ sub_37ED.c	*/
void sub_385B(aaa_t *);                    /* ok++ sub_385B.c	*/
uint16_t sub_387A(aaa_t *);                     /* ok++ 		*/
bool sub_38CA(aaa_t *, int);                /* ok++ 		*/
bool sub_393C(aaa_t *);                     /* ok++ 		*/
bool sub_3952(aaa_t *);                     /* ok++ 		*/
bool sub_3968(aaa_t *);                     /* ok++ 		*/
unsigned nodesize(aaa_t *); /*sub_3993*/   /* ok++ 		*/
aaa_t *sub_39CA(aaa_t *);                  /* ok++ 		*/
void sub_3A79(aaa_t *, aaa_t *);           /*.ok+  sub_3A79.c	*/
void sub_3B65(unsigned long *, long, int); /* ok++ sub_3B65.c	*/
void sub_3BC6(long *, long, int);          /*.ok+  sub_3BC6.c	*/
aaa_t *sub_3CDF(aaa_t *);                  /* ok++ sub_3CDF.c	*/
/* tree.c ----------------------------------------------------------------------*/
void sub_3DC9(aaa_t *);                 /* ok++			*/
aaa_t *sub_3EAA(aaa_t *);               /*.ok+  sub_3EAA.c	*/
aaa_t *sub_415E(long);                  /* ok++ sub_415E.c	*/
aaa_t *sub_4192(void);                  /*.ok+  sub_4192.c	*/
aaa_t *sub_43EF(int, aaa_t *, aaa_t *); /*.ok+  sub_43EF.c	*/
uchar sub_46F7(long);                   /* ok++ sub_46F7.c	*/
void sub_475C(aaa_t *);                 /* ok++ sub_475C.c	*/
char sub_47B2(aaa_t *, int);            /*.ok+  sub_47B2.c	*/
/*
int	     sub_4B89(aaa_t *);			   ok+
*/
uchar sub_4B89(aaa_t *);  /*.ok+  sub_4B89.c	*/
int sub_4BE5(aaa_t *);    /* ok++ sub_4BE5.c	*/
int sub_4C12(aaa_t *);    /* ok++ 		*/
char sub_4C6D(aaa_t *);   /*.ok+  sub_4C6D.c	*/
aaa_t *sub_4C8B(aaa_t *); /* ok++ sub_4C8B.c	*/
aaa_t *sub_4DA3(aaa_t *); /* ok++ 		*/
aaa_t *sub_4E8D(aaa_t *); /* ok++ 		*/
aaa_t *sub_4FA8(aaa_t *); /* ok++ 		*/
aaa_t *sub_4FCE(aaa_t *); /*.ok+  sub_4FCE.c	*/
aaa_t *sub_508A(aaa_t *); /* ok++ sub_508A.c	*/
aaa_t *sub_53EE(aaa_t *); /* ok++ 		*/
/* local.c ---------------------------------------------------------------------*/
aaa_t *sub_54B6(aaa_t *);             /*.ok   optim: out of memory */
void sub_5CF5(bbb_t *, int);          /*.ok+  sub_5CF5.c	*/
aaa_t *sub_5DF6(aaa_t *);             /* ok++ sub_5DF6.c	*/
aaa_t *sub_5F52(aaa_t *);             /* ok++ sub_5F52.c	*/
aaa_t *sub_600E(aaa_t *);             /* ok++ sub_600E.c	*/
int sub_605E(int);                    /*.ok+  sub_605E.c	*/
char sub_60A8(aaa_t *, aaa_t *);      /*.ok+  sub_60A8.c	*/
bool sub_61AA(bbb_t *, int);           /* ok++ sub_61AA.c	*/
bool sub_6246(aaa_t *, aaa_t *);       /* ok++ 		*/
bool sub_628F(aaa_t *, aaa_t *);      /* ok++ 		*/
bool sub_62BE(aaa_t *, aaa_t *);      /* ok++ 		*/
char sub_63B8(int, int, int);         /*.ok+  sub_63B8.c	*/
uchar sub_6589(int, int);             /*.ok+  sub_6589.c	*/
unsigned sub_665B(unsigned, uint8_t); /* ok++ 		*/
int sub_66BC(int, int, int, char *);  /* ok++ 		*/
/* main.c  ---------------------------------------------------------------------*/
/* int	     main(int, char **);		*/ /* ok++ 		*/

/*
 * original C functions replaced to use stdarg
 */

void fatalErr(char *fmt, ...);  /* ok   sub_6AA2.c	*/
void prWarning(char *fmt, ...); /* ok sub_6AD0*/
void prError(char *fmt, ...);   /* ok++ sub_6B1D.c	*/
void prMsg(char *fmt, va_list args);
void *allocmem(unsigned int); /*sub_6B9B*/ /* ok++ sub_6B9B.c	*/

/* int	     fprintf(FILE *, char *, int);	*/

int sub_6BF5(char *, char *, FILE *);

/* s6dc1.c */
/* static uint8_t *setSize(register uint8_t *p, short size) ok++ 6D1C	*/
/* static bool pack();                                      ok++ 6D61 */
#ifdef CPM
void *malloc(unsigned); /* ok++ 6ED4 */
void free(void *);      /* ok++ 7028*/
#endif

int sub_708D(char *, int); /* printf */

#if CPM
int fgetchar(void);
int fputchar(int);
#else
#define fgetchar getchar
#define fputchar putchar
#endif

/*
 * The following declarations may be required to recreate from a binary image
 */
char sub_70CB(char); /* toupper */

/*char	     sub_70F8(struct fcb *, char *);	*/ /* ok++ */ /* def_fcb */

int sub_7247(char *, char *, int); /* sprintf */

int sub_7288(int);                   /* pputc   */
int sub_7325(FILE *, char *, int *); /* doprnt  */
/* int	     fgetc(FILE *); */
int sub_770B(FILE *); /* filbuf  */
char sub_77F5();      /* Test ^c */
/*	     exit(int); */
int sub_7855(FILE *); /* fclose  */
int sub_78F0(FILE *); /* fflush  */

/* End file cgen.h */

/*
 * Debug function declarations
 */
#ifdef DEBUG1
void pr_st_a(aaa_t *st);
void pr_st_b(bbb_t *st);
#endif

#endif