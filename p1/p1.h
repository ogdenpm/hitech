/*
 *
 * The p1.h file is part of the restored P1.COM program
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
#ifndef _P1_H
#define _P1_H

#include "cclass.h"
#include <stdio.h>
#include "tok.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#ifdef __GNUC__
#include <unistd.h>
#define _MAX_PATH PATH_MAX
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
#undef putchar
int putchar(int ch);
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
        struct _s8 *_nextAttr; /* short hand for &_nextSym->attr */
        int16_t _labelId;
    } u1;
    union {
        struct _expr *_pExpr;
        struct _args *_pFargs;
    } u2;
    uint16_t indirection;
    uint8_t dataType;
    char nodeType;
} attr_t;

#define nextSym  u1._nextSym
#define nextAttr u1._nextAttr /* short hand for &nextSym->attr */
#define labelId  u1._labelId

#define pExpr     u2._pExpr
#define pFargs     u2._pFargs

;

typedef struct _sym {
    attr_t attr;
    struct _sym *symList;
    struct _sym *memberList;
    int16_t symId;
    int16_t memberId;
    int16_t bwidth;
    int16_t flags;
    uint8_t sclass;
    char level;
    char nRefCnt;
    char *nVName;
} sym_t;



/* flags flags */
#define S_MEM         1
#define S_REG         4
#define S_VAR         0x10
#define S_ARGDECL     0x20
#define S_IMPLICIT    0x40
#define S_NAMEID      0x80
#define S_EMITTED     0x100
#define S_ARG         0x200
#define S_BITFIELD    0x400

#define a_labelId     attr.labelId
#define a_indirection attr.indirection
#define a_dataType    attr.dataType
#define a_nodeType    attr.nodeType
#define a_nextSym     attr.nextSym
#define a_expr        attr.pExpr
#define a_args        attr.pFargs

typedef struct {
    char name[3];
    char prec;
    uint8_t operandFlags;
    int16_t operatorFlags;
    uint8_t nodeType;
} op_t;
/* operand flags */
#define O_LEAF      1 /* leaf expression */
#define O_BINARY    2 /* binary expression */
#define O_ALT      4 /* unary/binary expression */
#define O_RTOL         8
#define O_16        16

/* operator flags */
#define OP_RBOOL    1 /* requires right bool */
#define OP_LBOOL    2 /* requires left bool */
#define OP_SCALE    4 /* operation scales for pointers */
#define OP_FLOAT    0x10
#define OP_INT      0x20
#define OP_UNSIGNED 0x40
#define OP_VOIDFUNC 0x80   /* promote void in function args */
#define OP_SIZEOF   0x100  /* sizeof op */
#define OP_SEP      0x200  /* separates expressions */
#define OP_MEMBER   0x800  /* access member */
#define OP_AREL     0x1000 /* arithmetic rel */
#define OP_RTOL     0x2000 /* right to left associative */
#define OP_DREF     0x4000 /* deref */
#define OP_EREL     0x8000 /* equality rel*/

typedef struct _args {
    int16_t cnt;
    attr_t argVec[1];
} args_t;

typedef struct _s12 {
    sym_t *pSym1;
    attr_t *pAttr;
    sym_t *pSym2;
    uint16_t indirection;
    bool badInd;
    bool needDim;
    bool uca;
    bool ucb;
} decl_t;

typedef struct _expr {
    uint8_t tType;
    union {
        unsigned long _t_ul;
        long _t_l;
        char *_t_s;
        struct _sym *_t_pSym;
        struct {
            struct _expr *_lhs;
            struct _expr *_rhs;
        } s1;
        struct {
            int16_t _id;
            int16_t _chCnt;
        } s2;
    } u1;
#define t_ul    u1._t_ul
#define t_l     u1._t_l
#define t_s     u1._t_s
#define t_lhs   u1.s1._lhs
#define t_rhs   u1.s1._rhs
#define t_id    u1.s2._id
#define t_chCnt u1.s2._chCnt
#define t_pSym  u1._t_pSym

    attr_t attr;
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
    uint8_t op;
    uint8_t prec;
} opStk_t;

extern opStk_t *opSP;           /* 8bc7 */
extern int16_t strId;           /* 8bd7 */
extern uint8_t byte_8f85;       /* 8f85 */
extern bool lexMember;          /* 8f86 */
extern char *keywords[];        /* 8f87 */
extern char *tmpFile;           /* 91db */
extern op_t opTable[68];        /* 9271 */
extern uint8_t byte_968b;       /* 968b */
extern int16_t word_968c;       /* 968c */
extern int16_t tmpLabelId;      /* 968e */
extern int16_t lastLineNo;       /* 9caf */
extern char emittedSrcFile[64]; /* 9cb1 */
extern expr_t **exprSP;         /* 9cf1 */
extern opStk_t opStk[20];       /* 9cf3 */
extern expr_t eZero;            /* 9d1b */
extern expr_t eOne;             /* 9d28 */
extern expr_t *exprFreeList;    /* 9d35 */
extern uint8_t byte_9d37;       /* 9d37 */
extern expr_t *exprStk[20];     /* 9d38 */
extern char lastEmitSrc[64];    /* 9d60 */
extern bool sInfoEmitted;       /* 9da0 */
extern int16_t inCnt;           /* 9da1 */
extern char lastEmitFunc[40];   /* 9da3 */
extern YYTYPE yylval;           /* 9dcb */
extern char nameBuf[32];        /* 9dcf */
extern uint8_t ungetTok;        /* 9def */
extern int16_t strChCnt;        /* 9df0 */
extern bool lInfoEmitted;       /* 9df2 */
extern int16_t startTokCnt;     /* 9df3 */
extern int16_t ungetCh;         /* 9df5 */
extern char errBuf[512];        /* 9df7 */
extern FILE *crfFp;             /* 9ff7 */
extern char crfNameBuf[30];     /* 9ff9 */
extern char srcFile[100];       /* a017 */
extern char *crfFile;           /* a07b */
extern bool s_opt;              /* a07d */
extern bool w_opt;              /* a07e */
extern int16_t lineNo;          /* a07f */
extern char *srcFileArg;        /* a081 */
extern bool l_opt;              /* a083 */
extern FILE *tmpFp;             /* a084 */
extern char inBuf[512];         /* a086 */
extern int16_t errCnt;          /* a286 */
extern int8_t depth;            /* a288 */
extern uint8_t voidReturn;       /* a289 */
extern bool unreachable;        /* a28a */
extern int16_t returnLabel;       /* a28b */
extern sym_t *curFuncNode;      /* a28d */
extern sym_t *p25_a28f;         /* ad8f */
extern sym_t *tmpSyms;        /* as91 */
extern sym_t *symFreeList;      /* a293 */
extern sym_t **hashtab;         /* a295 */
extern decl_t *curDecl;         /* a297 */
extern uint8_t defSClass;       /* a299 */
extern uint8_t byte_a29a;       /* a29a */

/* emit.c */
void emitDependentVar(register sym_t *p);
void prFuncBrace(uint8_t tok);
void emitLocalLabelDef(int16_t p);
void emitLabelDef(register sym_t *st);
void emitCase(case_t *p1);
void emitStructUnion(sym_t *p, char c);
void emitCast(register expr_t *p);
void emitVar(register sym_t *st);
void emitAscii(register expr_t *st, char *pc);
void sub_05b5(expr_t *p1);
void sub_05d3(expr_t *p1);
void resetExprStack(void);

/* expr.c */
expr_t *sub_07f5(char p1);
expr_t *parseConstExpr(uint8_t n);
expr_t *sub_0bfc(void);
expr_t *parseExpr(uint8_t p1, register expr_t *lhs, expr_t *rhs);
expr_t *newIntLeaf(long num, uint8_t p2);
bool isZero(register expr_t *st);
bool releaseExprList(void);
expr_t *cloneExpr(register expr_t *st);
expr_t *newIdLeaf(register sym_t *st);
expr_t *newIConstLeaf(long p1);
expr_t *newSTypeLeaf(attr_t *p1);
void pushExpr(expr_t *p1);
void freeExpr(register expr_t *st);
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
#ifdef OLDCPM
void prError(char *p1, int p2, int p3);
void fatalErr(char *p1, char *p2);
void prWarning(char *p1, int p2, int p3);
#else
void prError(char *fmt, ...);
void fatalErr(char *fmt, ...);
void prWarning(char *fmt, ...);
#endif
void expectErr(char *p);
void *xalloc(size_t size);

/* program.c */
void sub_3adf(void);
void sub_3c7e(sym_t *p1);

/* stmt.c */
void parseFunction(void);

/* sym.c */
void sub_4d92(void);
sym_t *sub_4e90(register char *buf);
sym_t *sub_4eed(register sym_t *st, uint8_t p2, attr_t *p3, sym_t *p4);
void defineArg(register sym_t *st);
void sub_51cf(register sym_t *st);
void defineFuncSig(void);
bool releaseSymFreeList(void);
void enterScope(void);
void exitScope(void);
void releaseScopeSym(void);
sym_t *newTmpSym(void);
sym_t *findMember(sym_t *p1, char *p2);
void emitSymName(register sym_t *st, FILE *fp);
int16_t newTmpLabel(void);
args_t *cloneArgs(register args_t *p);
void cloneAttr(register attr_t *st, attr_t *p2);
bool haveSameDataType(register attr_t *st, attr_t *p2);
bool isVoidStar(register attr_t *st);
bool isVarOfType(register attr_t *st, uint8_t p2);
bool isLogicalType(register attr_t *st);
bool isSimpleType(register attr_t *st);
bool isIntType(register attr_t *st);
bool isFloatType(register attr_t *st);
bool isValidIndex(register attr_t *st);
void delIndirection(register attr_t *st);

/* type.c */
void addIndirection(register attr_t *st);
void sub_5c19(uint8_t p1);
uint8_t sub_5dd1(uint8_t *pscType, register attr_t *attr);
sym_t *sub_60db(uint8_t p1);
sym_t *sub_6360(void);
sym_t *sub_69ca(uint8_t p1, register attr_t *p2, uint8_t p3, sym_t *p4);
void emitAttr(register attr_t *st);


#ifdef _WIN32
void initMemAddr(void); /* for now only needed for windows */
#else
#define initMemAddr()
#endif

#ifdef CPM
extern char _Hbss;
#define inData(p) (((char *)p) < &_Hbss)
#else
#ifdef __APPLE__
#include <malloc/malloc.h>
#define initMemAddr()
#define inData(p) (!malloc_zone_from_ptr(p))
#else
extern const char *_Ldata;
extern const char *_Hbss;
#define inData(p) (_Ldata <= ((const char *)p) && ((const char *)p) < _Hbss)
#endif
#endif
#endif
