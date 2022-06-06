/*
 *
 * The zas.h file is part of the restored ZAS.EXE program
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
#ifndef _ZAS_H
#define _ZAS_H
#include <inttypes.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef _MSC_VER
#define fgets afgets
char *afgets(char *str, int n, FILE *stream);
#endif

#include "kwd.h"

#define MAX_OPERATORS      353
#define MAX_PSECT          17
#define MAX_TMP            500
/*
 *	Linker Limitations
 */
#define MAXINCL            30

#define MAX_SYMBOLS        2003 /* Maximum symbols */

#define LIST_FRAGMENT_SIZE 33 /* includes trailing 0*/
#define MAX_LIST_FRAGMENT  10

typedef union {
    int16_t yTok;
    int32_t yNum;
    float yFloat;
    char *yStr;
    struct _sym *ySym;
} yytype_t;

struct _macro {
    char *_vText;
    uint16_t _vArg;
};


typedef struct {
    union {
        int32_t _vNum;
        struct {
            char *_vText;
            uint16_t _vArg;
        } s;
        struct {
            uint16_t _vMaxLoc;
            uint16_t _vCurLoc;
        } l;
    } u1;

    union {
        uint16_t _psSize;  /* psect size */
        uint16_t _mArgCnt; /* macro arg cnt*/
        uint8_t _rType;
    } u2;
    union {
        uint16_t _pFlags;
        uint16_t _rFlags;
        struct _sym *_rSym; /* psect name */
        uint16_t _mIdx;
    } u3;
} prop_t;

#define vNum    u1._vNum
#define vText   u1.s._vText
#define vArg    u1.s._vArg
#define vMaxLoc u1.l._vMaxLoc
#define vCurLoc u1.l._vCurLoc

#define psSize  u2._psSize
#define mArgCnt u2._mArgCnt
#define rType   u2._rType
#define pFlags  u3._pFlags
#define rSym    u3._rSym
#define rFlags  u3._rFlags
#define mIdx    u3._mIdx

typedef struct {
    int16_t oType;
    int16_t oVal;
    prop_t oProp;
} operand_t;

typedef struct _sym {
    char *sName;
    prop_t sProp;
    uint16_t sFlags;
    union {
        char *irpcList;
        char **irpList;
    };
    struct _sym *sChain;
} sym_t;

typedef struct src_ { /* input management structure: file & macro */
    char srcType;
    union {
        FILE *_srcFp;
        char *_srcText;
    } u;
    int16_t srcLineno;   /* saved lineno */
    int16_t srcControls; /* saved listing controls */
    char *srcName;       /* src file name */
} src_t;
#define srcFp   u._srcFp
#define srcText u._srcText

typedef struct tmpLab_ {
    int16_t tLabel;
    int16_t tLoc;
    sym_t *tPsect;
} tmpLabel_t;

typedef struct {
    sym_t *mSym;
    char **mArgs;

} strstk_t;

/**************************************************************************
 * Prototype functions are in location order
 * +    compiles under VC
 * ++   compiles and appears to work under VC
 * +++  clean under gcc and VC and appears to work
 **************************************************************************/
typedef kwd_t *(*kwdfptr)(register char *s);

/* code.c */
void writeObjHeader(void);                             /* 7 021E */
void writeRecords(void);                               /* 9 027C */
void finishRecords(void);                              /* 11 02E2 */
void updateMaxLoc(sym_t *si);                          /* 13 037C */
void addObjByte(int16_t n);                            /* 15 03F2 */
void addObjRelocWord(register prop_t *pc, uint8_t al); /* 16 044C */
void addObjRelocByte(register prop_t *pc, uint8_t al); /* 18 052C */
void initSymRecord(void);                              /* 19 05F2 */
void addObjSymbol(register sym_t *ps);                 /* 22 0644 */
void addObjAllSymbols(void);                           /* 24 0804 */
void addObjEnd(void);                                  /* 25 0864 */

/* expr.c */
prop_t *evalExpr(void); /* 28 0B1C */

/* kwd.c */
int16_t getKwdId(char *p1);   /* 85 311A */
int16_t getPsectId(char *p1); /* 86 312C */

/* lex.c */
void parseCond(int16_t tok);                        /* 31 0EAA */
char *parseMacroBody(void);                         /* 32 0F8C */
char *getMacroArg(void);                            /* 33 125C */
void unget(int16_t dx);                             /* 36 1576 */
bool nextIsMacroKwd(void);                          /* 37 1592 */
int16_t yylex(void);                                /* 40 1708 */
void openMacro(register char *text, uint16_t flag); /* 45 1D60 */
void skipLine(void);                                /* 51 2050 */
void tagHex(uint16_t flag);                         /* 54 20D2 */
void putByte(uint16_t n, uint16_t flag);            /* 55 218A */
void putAddr(uint16_t n, uint16_t flag);            /* 56 21B4 */
void setHeading(char *text);                        /* 58 232C */
void topOfPage(void);                               /* 60 2364 */
void putTaggedAddr(prop_t *sProp, char ch);         /* 63 2462 */
void putErrCode(char ch);                           /* 64 24BC */
void prSymbols(void);                               /* 65 24E0 */

/* macro.c */
void parseParamAndBody(register sym_t *ps); /* 67 26A6 */
void parseMacroCall(register sym_t *ps);    /* 68 286E */
void nextArgSub(void);                        /* 69 2996 */
void openArg(uint16_t id);                  /* 70 2A2E */
void illegalLocal(void);                    /* 71 2A54 */
void parseLocal(void);                      /* 72 2A66 */
void parseIrp(void);                        /* 73 2AE2 */
void parseIrpc(void);                       /* 74 2B0A */
void parseRept(void);                       /* 75 2B32 */

/* main.c */
int main(int argc, char **argv);               /* 77 2BB2 */
char *getNextFile(void);                       /* 78 2EF4 */
void prMsg(char const *fmt, va_list args);     /* 79 2F16 */
_Noreturn void fatalErr(char const *fmt, ...); /* 80 2F5C */
void error(char const *fmt, ...);              /* 81 2F7C */

/* parse.c */
void relocErr(void);            /* 87 313E */
void parseElse(void);           /* 92 338E */
void doPass(void);              /* 94 33CC */
_Noreturn void syntaxErr(void); /* 100 3B1E */

bool isAbsPsect(sym_t *ps);       /* 106 3DBC */

/* sym.c */
sym_t *findSymSlot(char *name);                     /* 126 4ECE */
sym_t *getSym(register char *name, uint16_t flags); /* 127 4F02 */
void *xalloc(size_t size);                          /* 128 4FE0 */
void enterAbsPsect(void);                           /* 129 5014 */
void resetVals(void);                               /* 130 5046 */
void sortSymbols(void);                             /* 132 50BE */
sym_t *remSym(register sym_t *pSym);                /* 133 511A */
void addSym(register sym_t *pSym);                  /* 134 5178 */
sym_t *dupSym(register sym_t *pSym);                /* 135 5196 */
void delSym(sym_t *si);                             /* 136 51C0 */

/* tlab.c */
void initLocalLabels(void);                          /* 137 51D8 */
void defTmpLabel(int16_t tLabel);                    /* 138 51FE */
prop_t *findLocalLabel(int16_t nLabel, int16_t tok); /* 139 5270 */

extern prop_t startAddr;             /* 9799 */
extern char yytext[100];             /* 9b28 */
extern int16_t curLineno;            /* 9bbe */
extern char *curFileName;            /* 9bc0 */
extern char controls;                /* 9bc5 */
extern int16_t width;                /* 9e16 */
extern FILE *crfFp;                  /* 9e18 */
extern bool i_opt;                   /* 9e38 */
extern char l_opt;                   /* 9e39 */
extern char phase;                   /* 9e3a */
extern bool j_opt;                   /* 9e59 */
extern bool s_opt;                   /* 9e5a */
extern uint8_t c_opt;                /* 9e61 */
extern bool n_opt;                   /* 9e68 */
extern bool x_opt;                   /* 9e69 */
extern FILE *objFp;                  /* 9e6e */
extern yytype_t yylval;              /* 9e70 */
extern uint16_t floatMode;           /* 9e74 */
extern uint16_t symFlags;            /* 9e76 */
extern int16_t tokType;              /* 9e7c */
extern sym_t *absPsect;              /* a29c */
extern sym_t *curPsect;              /* a298 */
extern int16_t maxSymLen;            /* a29a */
extern sym_t *symTable[MAX_SYMBOLS]; /* a2a0 */
extern int16_t jmpOptCnt;            /* 9e7c */
extern prop_t retProp;               /* a752 */
extern int16_t pageLen;
extern int16_t localsCnt;

extern uint32_t curLoc32; /* 9b90 */
#endif
