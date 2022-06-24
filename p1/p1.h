#pragma once
#include "cclass.h"
#include "stdio.h"
#include "tok.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#define rindex  strrchr
#define blkclr(p, s) memset(p, 0, s);
/*
 *	Structural declarations
 */

typedef union {
    char *yStr;
    int32_t yNum;
    uint8_t yVal;
    struct _s25 *ySym;
} YYTYPE;

typedef struct _s8 {
    union {
        struct _s25 *chain;
        struct _s8 *chain8;
        char *s0;
        int16_t i0;
    } u1;
    union {
        int16_t i2;
        struct _s25 *ps25;
        struct _s13 *ps13;
        struct _s10 *ps10;
    };
    int16_t i4;
    uint8_t dataType;
    char c7;
} s8_t;

typedef struct _s25 {
    s8_t attr;

    char *m8;                 /*  8h  8	*/
                              /*  9h  9	*/
    struct _s25 *nMemberList; /* 0Ah 10	*/
                              /* 0Bh 11	*/
    int16_t nodeId;           /* 0Ch 12	*/
    int16_t m14;              /* 0Eh 14	*/
                              /* 0Fh 15	*/
    int16_t m16;              /* 10h 16	*/
                              /* 11h 17	*/
    int16_t m18;                  /* 12h 18  ok	*/
                              /* 13h 19	*/
    char m20;                 /* 14h 20	*/
    char m21;                 /* 15h 21  ok	*/
    char nRefCnt;             /* 16h 22  ok	*/
    char *nVName;             /* 17h 23  ok	*/
                              /* 18h 24	*/
                              /* 1Dh 29	*/
} s25_t;

#define n_i0    attr.u1.i0
#define n_i2    attr.i2
#define n_i4    attr.i4
#define n_dataType   attr.dataType
#define n_c7    attr.c7
#define n_chain attr.u1.chain
#define n_ps13  attr.ps13
#define n_ps25  attr.ps25
#define n_s0    nso.u1.s0

typedef struct {
    char s0[3];
    char c3;
    uint8_t uc4;
    int16_t i5;
    uint8_t uc6;
    uint8_t c7;
} t8_t;

typedef struct _s10 {
    int16_t cnt;
    s8_t s8array[1];
} s10_t;

typedef struct _s13 {
    uint8_t tType;
    union {
        unsigned long _t_ul;
        long _t_l;
        char *_t_s;
        char _t_ca[2];
        struct _s25 *_t_ps25;
        struct {
            struct _s13 *_t_next;
            struct _s13 *_t_alt;
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
#define t_ps25 u1._t_ps25
#define t_ca    u1._t_ca

    s8_t attr;
} s13_t;

typedef struct {
    s13_t *caseVal;
    int16_t caseLabel;
} s4_t;

typedef struct {
    s13_t *switchExpr;
    int16_t caseCnt;
    int16_t defLabel;
    s4_t caseOptions[255];
} case_t;




extern s13_t **p13List;         /* 8bc7 */
extern int16_t strId;             /* 8bd7 */
extern uint8_t byte_8f85;     /* 8f85 */
extern uint8_t byte_8f86;     /* 8f86 */
extern char *keywords[];      /* 8f87 */
extern char *tmpFile;         /* 91db */
extern t8_t opTable[68];        /* 9271 */
extern uint8_t byte_8f85;     /* 9f85 */
extern uint8_t byte_8f86;     /* 8f86 */
extern uint8_t byte_968b;     /* 968b */
extern int16_t word_968c;     /* 968c */
extern int16_t tmpLabelId;     /* 968e */
extern int16_t word_9caf;     /* 9caf */
extern char ca9CB1[64];       /* 9cb1 */
extern s13_t **s13SP;       /* 9cf1 */
extern s13_t *s13_9cf3[20];   /* 9cf3 */
extern s13_t s13_9d1b;        /* 9d1b */
extern s13_t s13_9d28;        /* 9d28 */
extern s13_t *s13FreeList;    /* 9d35 */
extern uint8_t byte_9d37;     /* 9d37 */
extern char s13Stk[40];       /* 9d38 */
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
extern int16_t errCnt;            /* a286 */
extern bool inFunc;           /* a288 */
extern uint8_t byte_a289;     /* a289 */
extern uint8_t unreachable;     /* a28a */
extern int16_t word_a28b;     /* a28b */
extern s25_t *curFuncNode;    /* a28d */
extern int16_t pn_a28f;         /* ad8f */
extern int16_t word_a291;         /* as91 */
extern s25_t *s25FreeList;    /* a293 */
extern s25_t **hashtab;     /* a295 */
extern void *word_a297;       /* a297 */
extern uint8_t byte_a299;     /* a299 */
extern uint8_t byte_a29a;     /* a29a */


/* emit.c */
void sub_013d(register FILE *p);
void sub_01c1(register s25_t *p);
void sub_01ec(register s25_t *p);
void prFuncBrace(uint8_t tok);
void sub_0258(int16_t p);
void sub_0273(register s25_t *st);
void sub_02a6(case_t *p1);
void sub_0353(s25_t *p, char c);
void sub_042d(register s13_t *p);
void sub_0470(s13_t *p);
void sub_0493(register s25_t *st);
void sub_053f(register s13_t *st, char *pc);
void sub_05b5(s13_t *p1);
void sub_05d3(s13_t *p1);
void sub_05f1(register s13_t *st);
void sub_07e3(void);

/* expr.c */

/* lex.c */
uint8_t yylex(void);
uint8_t parseNumber(int16_t ch);
uint8_t parseName(int16_t ch);
void parseAsm(void);
void parseString(int16_t ch);
int16_t getCh(void);
void prErrMsg(void);
void prMsgAt(register char *buf);
void emitSrcInfo(void);
int16_t skipWs(void);
int8_t escCh(int16_t ch);
int16_t peekCh(void);
void skipStmt(uint8_t tok);
void expect(uint8_t etok, char *msg);
void skipToSemi(void);

/* main.c */
int main(int argc, char *argv[]);
#ifdef CPM
void prMsg(char *p1, int p2, int p3);
void prError(char *p1, int p2, int p3);
void fatalErr(char *p1, char *p2);
void prWarning(char *p1, int p2, int p3);
#else
void prMsg(char *fmt, va_list args);
void prError(char *fmt, ...);
void fatalErr(char *fmt, ...);
void prWarning(char *fmt, ...);
#endif
void expectedErr(char *p);
void copyTmp(void);
void closeFiles(void);
void *xalloc(unsigned size);
void sub_3abf(void);

/* program.c */



/* stmt.c */
void sub_489b(void);
void parseStmt(int16_t p1, int16_t p2, register case_t *p3, int16_t *p4);
void parseStmtGroup(int16_t p1, int16_t p2, case_t *p3, int16_t *p4);
void parseStmtAsm(void);
void parseStmtWhile(case_t *p3);
void parseStmtDo(case_t *p3);
void parseStmtIf(int16_t p1, int16_t p2, case_t *p3, int16_t *p4);
void parseStmtSwitch(int16_t p1);
void parseStmtFor(case_t *p1);
void parseStmtBreak_Continue(int16_t label);
void parseStmtDefault(int16_t p1, int16_t p2, register case_t *p3, int16_t *p4);
void parseStmtCase(int16_t p1, int16_t p2, register case_t *p3, int16_t *p4);
void parseStmtReturn(void);
void parseStmtGoto(void);
void parseStmtLabel(register s25_t *ps, int16_t p1, int16_t p2, case_t *p3, int16_t *p4);
s25_t *sub_4ca4(register s25_t *ps);
void sub_4ce8(int16_t n);
void sub_4d15(int16_t n, register s13_t *st, char c);
void sub_4d67(register s13_t *st);

/* sym.c */


/* type.c */