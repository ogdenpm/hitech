#ifndef _P1_H
#define _P1_H

#include "cclass.h"
#include "stdio.h"
#include "tok.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#ifdef __GNUC__
#include <unistd.h>
#endif
#if defined(__STDC__) || defined(__STDC_VERSION__)
#include <stdbool.h>
#include <stdint.h>
#if __STDC_VERSION__ < 201112L
#define _Noreturn
#endif
#if __STDC_VERSION__ >= 201710L
#define register
#endif
#else
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned long uint32_t;
typedef long int32_t;
#ifndef bool
#define bool char
#define true 1
#define false 0
#endif
#define _Noreturn
#endif
/* in certain functions the GCC and MSVC compilers reasonably complain that
 * certain variables may be used before being initialised
 * this macro forces a 0 initialisation which will cause
 * exceptions if the variable is used, rather than rely on
 * random data
 */
#ifdef CPM
#define FORCEINIT
#else
#define FORCEINIT    = 0
/* map some old HiTech functions */
#define rindex       strrchr
#define blkclr(p, s) memset(p, 0, s);
#endif

#define HASHTABSIZE 271

/*
 *	Structural declarations
 */

typedef union {
    char *yStr;
    int32_t yNum;
    uint8_t yVal;
    struct _sym *ySym;
} YYTYPE;

typedef struct _s8 {
    union {
        struct _sym *_nextSym;
        struct _s8 *_nextInfo;
        int16_t _labelId;
    } u1;
    union {
        struct _sym *_pSym;
        struct _expr *_pExpr;
        struct _args *_pArgs;
        struct _s8 *_pInfo;
    } u2;
    int16_t i4;
    uint8_t dataType;
    char c7;
} s8_t;

#define i_nextSym  u1._nextSym
#define i_nextInfo u1._nextInfo
#define i_labelId  u1._labelId

#define i_sym      u2._pSym
#define i_expr     u2._pExpr
#define i_args     u2._pArgs
#define i_info     u2._pInfo

typedef struct _sym {
    s8_t attr;
    struct _sym *m8;
    struct _sym *nMemberList;
    int16_t nodeId;
    int16_t m14;
    int16_t m16;
    int16_t m18;
    char m20;
    char m21;
    char nRefCnt;
    char *nVName;
} sym_t;

#define a_labelId  attr.i_labelId
#define a_i4       attr.i4
#define a_dataType attr.dataType
#define a_c7       attr.c7
#define a_nextSym  attr.i_nextSym
#define a_expr     attr.i_expr
#define a_sym      attr.i_sym
#define a_info     attr.i_info
#define a_args     attr.i_args

typedef struct {
    char s0[3];
    char c3;
    uint8_t uc4;
    int16_t i5;
    uint8_t c7;
} t8_t;

typedef struct _args {
    int16_t cnt;
    s8_t s8array[1];
} args_t;

typedef struct _s12 {
    sym_t *p25;
    s8_t *p8;
    sym_t *p25_1;
    uint16_t i6;
    uint8_t uc8;
    bool uc9;
    bool uca;
    bool ucb;
} s12_t;

typedef struct _expr {
    uint8_t tType;
    union {
        unsigned long _t_ul;
        long _t_l;
        char *_t_s;
        struct _sym *_t_pSym;
        struct {
            struct _expr *_t_next;
            struct _expr *_t_alt;
        } s1;
        struct {
            int16_t _t_i0;
            int16_t _t_i2;

        } s2;
    } u1;
#define t_ul   u1._t_ul
#define t_l    u1._t_l
#define t_s    u1._t_s
#define t_next u1.s1._t_next
#define t_alt  u1.s1._t_alt
#define t_i0   u1.s2._t_i0
#define t_i2   u1.s2._t_i2
#define t_pSym u1._t_pSym

    s8_t attr;
} expr_t;

typedef struct {
    expr_t *caseVal;
    int16_t caseLabel;
} s4_t;

typedef struct {
    expr_t *switchExpr;
    int16_t caseCnt;
    int16_t defLabel;
    s4_t caseOptions[255];
} case_t;

typedef struct {
    uint8_t type1;
    uint8_t type2;
} s2_t;

extern s2_t *p2List;          /* 8bc7 */
extern int16_t strId;         /* 8bd7 */
extern uint8_t byte_8f85;     /* 8f85 */
extern bool byte_8f86;        /* 8f86 */
extern char *keywords[];      /* 8f87 */
extern char *tmpFile;         /* 91db */
extern t8_t opTable[68];      /* 9271 */
extern uint8_t byte_968b;     /* 968b */
extern int16_t word_968c;     /* 968c */
extern int16_t tmpLabelId;    /* 968e */
extern int16_t word_9caf;     /* 9caf */
extern char ca9CB1[64];       /* 9cb1 */
extern expr_t **s13SP;        /* 9cf1 */
extern s2_t s2_9cf3[20];      /* 9cf3 */
extern expr_t s13_9d1b;       /* 9d1b */
extern expr_t s13_9d28;       /* 9d28 */
extern expr_t *s13FreeList;   /* 9d35 */
extern uint8_t byte_9d37;     /* 9d37 */
extern expr_t *s13Stk[20];    /* 9d38 */
extern char lastEmitSrc[64];  /* 9d60 */
extern bool sInfoEmitted;     /* 9da0 */
extern int16_t inCnt;         /* 9da1 */
extern char lastEmitFunc[40]; /* 9da3 */
extern YYTYPE yylval;         /* 9dcb */
extern char nameBuf[32];      /* 9dcf */
extern uint8_t ungetTok;      /* 9def */
extern int16_t strChCnt;      /* 9df0 */
extern bool lInfoEmitted;     /* 9df2 */
extern int16_t startTokCnt;   /* 9df3 */
extern int16_t ungetCh;       /* 9df5 */
extern char errBuf[512];      /* 9df7 */
extern FILE *crfFp;           /* 9ff7 */
extern char crfNameBuf[30];   /* 9ff9 */
extern char srcFile[100];     /* a017 */
extern char *crfFile;         /* a07b */
extern bool s_opt;            /* a07d */
extern bool w_opt;            /* a07e */
extern int16_t lineNo;        /* a07f */
extern char *srcFileArg;      /* a081 */
extern bool l_opt;            /* a083 */
extern FILE *tmpFp;           /* a084 */
extern char inBuf[512];       /* a086 */
extern int16_t errCnt;        /* a286 */
extern uint8_t depth;         /* a288 */
extern uint8_t byte_a289;     /* a289 */
extern bool unreachable;      /* a28a */
extern int16_t word_a28b;     /* a28b */
extern sym_t *curFuncNode;    /* a28d */
extern sym_t *p25_a28f;       /* ad8f */
extern sym_t *word_a291;      /* as91 */
extern sym_t *s25FreeList;    /* a293 */
extern sym_t **hashtab;       /* a295 */
extern s12_t *p12_a297;       /* a297 */
extern uint8_t byte_a299;     /* a299 */
extern uint8_t byte_a29a;     /* a29a */

/* emit.c */
void sub_01ec(register sym_t *p);
void prFuncBrace(uint8_t tok);
void emitLabelDef(int16_t p);
void sub_0273(register sym_t *st);
void sub_02a6(case_t *p1);
void sub_0353(sym_t *p, char c);
void sub_042d(register expr_t *p);
void sub_0493(register sym_t *st);
void sub_053f(register expr_t *st, char *pc);
void sub_05b5(expr_t *p1);
void sub_05d3(expr_t *p1);
void sub_07e3(void);

/* expr.c */
expr_t *sub_07f5(char p1);
expr_t *sub_0a83(uint8_t n);
expr_t *sub_0bfc(void);
expr_t *sub_1441(uint8_t p1, register expr_t *lhs, expr_t *rhs);
expr_t *sub_1b4b(long num, uint8_t p2);
bool sub_2105(register expr_t *st);
bool s13ReleaseFreeList(void);
expr_t *sub_21c7(register expr_t *st);
expr_t *allocId(register sym_t *st);
expr_t *allocIConst(long p1);
expr_t *allocSType(s8_t *p1);
void pushS13(expr_t *p1);
void sub_2569(register expr_t *st);
expr_t *sub_25f7(register expr_t *st);

/* lex.c */
uint8_t yylex(void);
void prMsgAt(register char *buf);
void emitSrcInfo(void);
int16_t peekCh(void);
void skipStmt(uint8_t tok);
void expect(uint8_t etok, char *msg);
void skipToSemi(void);

/* main.c */
int main(int argc, char *argv[]);
#ifdef CPM
void prError(char *p1, int p2, int p3);
void fatalErr(char *p1, char *p2);
void prWarning(char *p1, int p2, int p3);
#else
void prError(char *fmt, ...);
void fatalErr(char *fmt, ...);
void prWarning(char *fmt, ...);
#endif
void expectErr(char *p);
void *xalloc(unsigned size);

/* program.c */
void sub_3adf(void);
void sub_3c7e(sym_t *p1);

/* stmt.c */
void sub_409b(void);

/* sym.c */
void sub_4d92(void);
sym_t *sub_4e90(register char *buf);
sym_t *sub_4eed(register sym_t *st, int16_t p2, s8_t *p3, sym_t *p4);
void sub_516c(register sym_t *st);
void sub_51cf(register sym_t *st);
void sub_51e7(void);
bool releaseNodeFreeList(void);
void enterScope(void);
void exitScope(void);
void checkScopeExit(void);
sym_t *sub_56a4(void);
sym_t *findMember(sym_t *p1, char *p2);
void sub_573b(register sym_t *st, FILE *fp);
int16_t newTmpLabel(void);
args_t *sub_578d(register args_t *p);
void sub_58bd(register s8_t *st, s8_t *p2);
bool sub_591d(register s8_t *st, s8_t *p2);
bool sub_5a4a(register s8_t *st);
bool sub_5a76(register s8_t *st, uint8_t p2);
bool sub_5aa4(register s8_t *st);
bool sub_5ad5(register s8_t *st);
bool sub_5b08(register s8_t *st);
bool sub_5b38(register s8_t *st);
bool isValidDimType(register s8_t *st);
void sub_5b99(register s8_t *st);

/* type.c */
void sub_5be1(register s8_t *st);
void sub_5c19(uint8_t p1);
uint8_t sub_5dd1(uint8_t *pscType, register s8_t *attr);
sym_t *sub_60db(uint8_t p1);
sym_t *sub_6360(void);
sym_t *sub_69ca(uint8_t p1, register s8_t *p2, uint8_t p3, sym_t *p4);
void sub_7454(register s8_t *st);

#ifdef CPM
extern char _Hbss;
#define inData(p) (((char *)p) < &_Hbss)
#else
extern const char *_Ldata;
extern const char *_Hbss;
#ifdef _WIN32
void initMemAddr();
#endif
#define inData(p) (_Ldata <= ((const char *)p) && ((const char *)p) < _Hbss)
#endif
#endif