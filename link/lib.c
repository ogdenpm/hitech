/*
 * File created 14.11.2021, last modified 01.01.2022
 *
 * The b.c file is part of the restored LINK.COM program
 * from the Hi-Tech C compiler v3.09 package.
 *
 *	Andrey Nikitin	01.01.2022
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#include <sys.h>*/
#include "link.h"
/* the following macros allow for different bit vector implementations */
#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif

#define VECBITS             (sizeof(vec_t) * CHAR_BIT)
#define VECBYTES(bits)      (bits + VECBITS - 1) / VECBITS * sizeof(vec_t)
#define SetBit(v, libFiles) ((v)[(libFiles) / VECBITS] |= (1 << ((libFiles) & (VECBITS - 1))))
#define TstBit(v, libFiles) ((1 << ((libFiles) & (VECBITS - 1))) & (v)[(libFiles) / VECBITS])

/*------------------------------------------------------------------- File lib.c */
static void seekErr();                        /* 07c5 17 */
static uint32_t letou32(uint8_t *);           /* 07ea 19 */
static uint16_t letou16(uint8_t *);           /* 082a 20 */
static void scanModule(int);                  /* 0944 23 */
static void chkModuleNeeded(char *, uint8_t); /* 0a23 24 */
static void doModule(int);                    /* 0aaf 26 */

typedef void (*vmfuncptr)(int);      /* added as hitech C gets confused */
static void visitModules(vmfuncptr); /* 0b38 27 */

typedef void (*vsfuncptr)(char *, uint8_t);
static void visitSymbols(vsfuncptr); /* 0bc9 28 */

static void readName(char *); /* 0c2e 29 */
static void unexp_eof();      /* 0c62 30 */

static uint32_t moduleSize; /* 7c26 * */
static int symTabSize;      /* 7c2a * */
static int nModules;        /* 7c2c * */
static bool moduleLoaded;   /* 7c2e * */
static int sizeSymbols;     /* 7c2f * */
static bool moduleNeeded;   /* 7c31 * */
static int nLibFiles;       /* 7c32 * */
static FILE *libraryFp;     /* 7c34 * */
static int symTabCnt;       /* 7c36 * */
static uint8_t libBuf[100]; /* 7c38 * */
static vec_t **libTable;    /* 7c9c * */

/**************************************************************************
 17	seekErr		sub-07c5h	ok++ (nau) (PMO)
 **************************************************************************/
static void seekErr() {

    fatalErr("%s: Can't seek", libraryName);
}

/**************************************************************************
 18	allocModuleArrays	sub_07d3h	ok++ (nau) (PMO)
 **************************************************************************/
void allocModuleArrays(int libFiles) {
    /* allocate space for the library module include flags */
    /* the include flag space itself is allocated as each file is processed */
    nLibFiles = libFiles;
    libTable  = xalloc(nLibFiles * sizeof(vec_t *));
}

/**************************************************************************
 19	letou32		sub_07ea	ok++ (nau) (PMO)
 **************************************************************************/
static uint32_t letou32(register uint8_t *p) {

    return *p + (*(p + 1) << 8) + (*(p + 2) << 0x10) + (*(p + 3) << 0x18);
}

/**************************************************************************
 20	letou16		sub_082a	ok++ (nau) (PMO)
 **************************************************************************/
static uint16_t letou16(register uint8_t *buf) {

    return *buf + (*(buf + 1) << 8);
}

/**************************************************************************
 21	openLibrary		sub_084a	ok++ (nau) (PMO)
 **************************************************************************/
void openLibrary() {

    libraryName = objFileName;
    objFileName = 0;
#ifdef CPM
    if ((libraryFp = fopen(libraryName, "rb")) == 0)
#else
    if ((libraryFp = fopen(libraryName, "rb")) == 0 &&
        (libraryFp = fopen(mkLibPath(libraryName), "rb")) == 0)

#endif

        fatalErr("%s: Can't open", libraryName);

    if (fread(libBuf, 1, 4, libraryFp) != 4)
        unexp_eof();

    nModules    = letou16(libBuf + 2);
    sizeSymbols = letou16(libBuf);
    /*    / libPass1() */
    (libHandlers[pass])();
    /*    \ libPass2() */
    libraryName = 0;
    fclose(libraryFp);
}

/**************************************************************************
 22	libPass1		ok++ (PMO)
 **************************************************************************/
void libPass1() {
    /* allocate uint8_t values to store a flag for whether the module within
     * a library is needed or not
     */
    libTable[libFileIdx] = xalloc(VECBYTES(nModules));

    if (fseek(libraryFp, 4, SEEK_SET) == -1 ||
        fseek(moduleFp, (long)sizeSymbols + 4, SEEK_SET) == -1)
        seekErr();
    visitModules(scanModule);
}

/**************************************************************************
 23	scanModule		ok++ (PMO)
 **************************************************************************/
static void scanModule(int modIdx) {

    moduleNeeded = false;
    if (TstBit(libTable[libFileIdx], modIdx)) {
        if (fseek(libraryFp, symTabSize, SEEK_CUR) == -1)
            seekErr();
    } else {
        visitSymbols(chkModuleNeeded);
        if (moduleNeeded) {
            SetBit(libTable[libFileIdx], modIdx);
            moduleLoaded = true; /* not actually used */
            doObjFile();
        }
    }
    if (!moduleNeeded && fseek(moduleFp, moduleSize, SEEK_CUR) == -1)
        seekErr();
}

/**************************************************************************
 24	chkModuleNeeded:			ok++ (PMO)
 **************************************************************************/
static void chkModuleNeeded(char *name, uint8_t sType) {
    register sym_t *st;

    if (moduleNeeded) /* already determined */
        return;
    if (sType != 0) /* symbol is not a global definition */
        return;
    /* check if it resolves an external */
    if ((st = getSymbol(name, 0)) == 0 || (st->flags & 0xF) != SF_EXTERN)
        return;
    moduleNeeded = true;
}

/**************************************************************************
 25	libPass2:		ok++ (PMO)
 **************************************************************************/
void libPass2() {

    if (optM)
        printf("\n%s\n", libraryName);
    if (fseek(moduleFp, (long)sizeSymbols + 4, SEEK_CUR) == -1)
        seekErr();
    visitModules(doModule);
}

/**************************************************************************
 26	doModule		ok++ (PMO)
 **************************************************************************/
static void doModule(int modIdx) {
    /* process or skip the module, based on flag set in libTable */
    if (TstBit(libTable[libFileIdx], modIdx))
        doObjFile();
    else if (fseek(moduleFp, moduleSize, SEEK_CUR) == -1)
        seekErr();

    if (fseek(libraryFp, symTabSize, SEEK_CUR) == -1)
        seekErr();
}

/**************************************************************************
 27	visitModules	sub_0b38h	ok++ (PMO)
 **************************************************************************/

static void visitModules(vmfuncptr action) {
    int modIdx;

    for (modIdx = 0; modIdx != nModules; ++modIdx) {
        if (fread(libBuf, 12, 1, libraryFp) != 1)
            unexp_eof();

        symTabSize = letou16(libBuf);
        symTabCnt  = letou16(libBuf + 2);
        moduleSize = letou32(libBuf + 4);

        readName(objFileName = (char *)libBuf + 12);
        action(modIdx);
        objFileName = 0;
    }
}

/**************************************************************************
 28	visitSymbols	sub_0bc9h	ok++ (PMO)
 as all actions use type as a uint8_t, the prototype now reflects this
 as a result the optimiser doesn't load the high byte of type
 **************************************************************************/
static void visitSymbols(vsfuncptr action) {
    char moduleBuf[100];
    int symIdx, sType;

    for (symIdx = symTabCnt; symIdx != 0; --symIdx) {
        if ((sType = fgetc(libraryFp)) == -1)
            unexp_eof();
        readName(moduleBuf);
        action(moduleBuf, sType); /* <- chkModuleNeeded(char * offset, int relocType) */
    }
}

/**************************************************************************
 29	readName	sub_0c2eh	ok++ (PMO)
 **************************************************************************/
static void readName(register char *p) {
    int ch;

    do {
        if ((ch = fgetc(libraryFp)) == -1)
            unexp_eof();
        *(p++) = ch;
    } while (ch);
}

/**************************************************************************
 30	unexp_eof	sub_0c62h	ok++
 **************************************************************************/
static void unexp_eof() {

    badFormat("unexpected end of file");
}
