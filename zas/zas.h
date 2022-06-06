/*
 *
 * The zas.h file is part of the restored ZAS.COM program
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
#ifndef _ZAS_H
#define _ZAS_H

#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#ifndef CPM
#include <stdbool.h>
#ifndef _MSC_VER
#define fgets afgets
char *afgets(char *str, int n, FILE *stream);
#endif
#else
typedef char bool;
#define true 1
#define false 0
#define const
#define _Noreturn
#endif

#include "kwd.h"

#define MAX_OPERATORS 331
#define MAX_PSECT     17
#define MAX_TMP       350
/*
 *	Linker Limitations
 */
#define MAXINCL       30
#ifdef CPM
#define MAX_SYMBOLS 601 /* Maximum symbols          */
#else
#define MAX_SYMBOLS 2003 /* allow bigger files */
#endif
#define LIST_FRAGMENT_SIZE 33 /* includes trailing 0*/
#define MAX_LIST_FRAGMENT  10

typedef union {
    int16_t yVal;
    int32_t yNum;
    float yFloat;
    char *yStr;
    struct _sym *ySym;
} yytype_t;

typedef struct {
    union {
        int32_t _vNum;
        char *_vStr;
        struct {
            char *_vText;
            struct _sym **_vArg;
        } s;
    } u1;
    union {
        struct {
            struct _sym *_cPsectSym; /* code psect */
            struct _sym *_cExtSym;   /* code ext name */
        } s;
        int16_t _psSize;  /* psect size */
        int16_t _mArgCnt; /* macro arg cnt*/
    } u2;
} prop_t;

#define vNum      u1._vNum
#define vStr      u1._vStr
#define vText     u1.s._vText
#define vArg      u1.s._vArg

#define psSize    u2._psSize
#define mArgCnt   u2._mArgCnt
#define cPsectSym u2.s._cPsectSym
#define cExtSym   u2.s._cExtSym

typedef struct {
    int16_t oType;
    int16_t oVal;
    prop_t oProp;
} operand_t;

typedef struct _sym {
    char *sName;
    prop_t sProp;
    uint16_t sFlags;
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
    sym_t *srcSym;       /* symbol holding macro expansion */
} src_t;
#define srcFp   u._srcFp
#define srcText u._srcText

typedef struct tmpLab_ {
    int16_t tLabel;
    int16_t tLoc;
    sym_t *tPsect;
} tmpLabel_t;

/**************************************************************************
 * Prototype functions are in location order
 * +--  compiles under VC
 * ++-  compiles under Hitech C
 * +++  code compatible
 **************************************************************************/
typedef kwd_t *(*kwdfptr)(register char *s);

void writeObjHeader(); /* 2 01C1 +-- */

void writeRecords();  /* 5 0282 +-- */
void finishRecords(); /* 6 02E5 +-- */

void addObjByte(int16_t n);                /* 8 03D0 +-- */
void addObjRelocWord(register prop_t *pc); /* 9 0461 +-- */
void addObjRelocByte(register prop_t *pc); /* 10 055A +-- */

void addObjAllSymbols(void); /* 17 091F +-- */

void addObjEnd(void); /* 20 0AA0 +-- */

prop_t *evalExpr(void); /* 21 0B67 +-- */

void parseCond(int16_t type); /* 26 134E +-- */
char *parseMacroBody(void);   /* 27 14B9 +-- */
char *getMacroArg(void);      /* 28 15FC +-- */

int16_t yylex(void); /* 32 1B8C +-- */

void openMacro(register sym_t *pSym); /* 35 2160 +-- */

void skipLine(void); /* 39 23F1 +-- */

void tagHex(uint16_t flag);              /* 42 24B8 +-- */
void putByte(uint16_t n, uint16_t flag); /* 43 258C +-- */
void putAddr(uint16_t n, uint16_t flag); /* 44 25BB +-- */

void setHeading(char *text); /* 48 289F +-- */

void topOfPage(void); /* 50 28D2 +-- */

void putTaggedAddr(prop_t *sProp, int16_t ch); /* 53 298D +-- */
void putErrCode(int16_t n);                    /* 54 29FE +-- */
void prSymbols(void);                          /* 55 2A23 +-- */
void parseParamAndBody(register sym_t *iy);    /* 56 2C1B +-- */
void parseMacroCall(register sym_t *ps);       /* 57 2DC5 +-- */
void freeMacro(register sym_t *iy);            /* 58 2E89 +-- */

int main(int argc, char **argv); /* 59 2EF4 +-- */
char *getNextFile(void);         /* 60 329B +-- */

#ifdef CPM       /**/
void fatalErr(); /* 61 32BF +-- */
void error();    /* 62 32E6 +-- */
void prMsg();    /* 63 3335 +-- */
#else            /**/
_Noreturn void fatalErr(char const *fmt, ...); /* 61 +-- */
void error(char const *fmt, ...);              /* 62 +-- */
void prMsg(char const *fmt, va_list args);     /* 63 +-- */
#endif

int16_t getKwdId(char *p1);   /* 67 3623 +-- */
int16_t getPsectId(char *p1); /* 68 3639 +-- */

void relocErr(void); /* 70 368F +-- */

void doPass(void); /* 74 393D +-- */

_Noreturn void syntaxErr(void); /* 80 3F83 +-- */

sym_t *getSym(register char *name, int flags); /* 103 4F7A +-- */
void *xalloc(size_t size);                     /* 104 50E3 +-- */
void enterAbsPsect(void);                      /* 105 510B +-- */
void resetVals(void);                          /* 106 5146 +-- */

void sortSymbols(void);                         /* 108 5210 +-- */
sym_t *remSym(register sym_t *pSym);            /* 109 52B7 +-- */
void addSym(register sym_t *pSym);              /* 110 5366 +-- */
sym_t *dupSym(register sym_t *pSym);            /* 111 53A1 +-- */
void initLocalLabels(void);                     /* 112 53E5 +-- */
void defTmpLabel(int16_t nLabel);                /* 113 5404 +-- */
prop_t *findLocalLabel(int16_t nLabel, int tokType); /* 114 546A +-- */

extern prop_t startAddr;             /* 9799 */
extern char yytext[100];             /* 9b28 */
extern int16_t curLineno;                /* 9bbe */
extern char *curFileName;            /* 9bc0 */
extern char controls;                /* 9bc5 */
extern int16_t width;                    /* 9e16 */
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
extern int jmpOptCnt;                /* 9e7c */
extern prop_t retProp;               /* a752 */



extern uint32_t curLoc32;
#endif
