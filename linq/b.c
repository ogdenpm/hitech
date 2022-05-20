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

#define VECBITS        (sizeof(vec_t) * CHAR_BIT)
#define VECBYTES(bits) (bits + VECBITS - 1) / VECBITS * sizeof(vec_t)
#define SetBit(v, n)   ((v)[(n) / VECBITS] |= (1 << ((n) & (VECBITS - 1))))
#define TstBit(v, n)   ((1 << ((n) & (VECBITS - 1))) & (v)[(n) / VECBITS])
/**************************************************************************
 17	seek_err		sub-07c5h	ok++ (nau) (PMO)
 **************************************************************************/
void seek_err() {

    fatal_err("%s: Can't seek", libraryName);
}

/**************************************************************************
 18	allocModuleArrays	sub_07d3h	ok++ (nau) (PMO)
 **************************************************************************/
void allocModuleArrays(int num_lib_files) {
    /* allocate space for the library module include flags */
    /* the include flag space itself is allocated as each file is processed */
    num_files = num_lib_files;
    libTable  = xalloc(num_files * sizeof(vec_t *));
}

/**************************************************************************
 19	conv_letou32		sub_07ea	ok++ (nau) (PMO)
 **************************************************************************/
uint32_t conv_letou32(register uint8_t *p1) {

    return *p1 + (*(p1 + 1) << 8) + (*(p1 + 2) << 0x10) + (*(p1 + 3) << 0x18);
}

/**************************************************************************
 20	conv_btou16		sub_082a	ok++ (nau) (PMO)
 **************************************************************************/
uint16_t conv_btou16(register uint8_t *p1) {

    return *p1 + (*(p1 + 1) << 8);
}

/**************************************************************************
 21	openLibrary		sub_084a	ok++ (nau) (PMO)
 **************************************************************************/
void openLibrary() {

    libraryName = fname_obj;
    fname_obj   = 0;
#ifdef CPM
    if ((libraryFp = fopen(libraryName, "rb")) == 0)
#else
    if ((libraryFp = fopen(libraryName, "rb")) == 0 &&
        (libraryFp = fopen(mkLibPath(libraryName), "rb")) == 0)

#endif

        fatal_err("%s: Can't open", libraryName);

    if (fread(libBuf, 1, 4, libraryFp) != 4)
        unexp_eof();

    num_modules  = conv_btou16(libBuf + 2);
    size_symbols = conv_btou16(libBuf);
    /*    / libPass1() */
    (libHandlers[linker_pass])();
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
    libTable[num_lib_files] = xalloc(VECBYTES(num_modules));

    if (fseek(libraryFp, 4, SEEK_SET) == -1 ||
        fseek(moduleFp, (long)size_symbols + 4, SEEK_SET) == -1)
        seek_err();
    visitModules(scanModule);
}

/**************************************************************************
 23	scanModule		ok++ (PMO)
 **************************************************************************/
void scanModule(int modIdx) {

    moduleNeeded = false;
    if (TstBit(libTable[num_lib_files], modIdx)) {
        if (fseek(libraryFp, symSize, SEEK_CUR) == -1)
            seek_err();
    } else {
        visitSymbols(chkModuleNeeded);
        if (moduleNeeded) {
            SetBit(libTable[num_lib_files], modIdx);
            moduleLoaded = true; /* not actually used */
            doObjFile();
        }
    }
    if (!moduleNeeded && fseek(moduleFp, moduleSize, SEEK_CUR) == -1)
        seek_err();
}

/**************************************************************************
 24	chkModuleNeeded:			ok++ (PMO)
 **************************************************************************/
void chkModuleNeeded(char *p1, uint8_t p2) {
    register sym_t *st;

    if (moduleNeeded) /* already determined */
        return;
    if (p2 != 0) /* symbol is not a global definition */
        return;
    /* check if it resolves an external */
    if ((st = getSymbol(p1, 0)) == 0 || (st->flags & 0xF) != SF_EXTERN)
        return;
    moduleNeeded = true;
}

/**************************************************************************
 25	libPass2:		ok++ (PMO)
 **************************************************************************/
void libPass2() {

    if (key_M)
        printf("\n%s\n", libraryName);
    if (fseek(moduleFp, (long)size_symbols + 4, SEEK_CUR) == -1)
        seek_err();
    visitModules(doModule);
}

/**************************************************************************
 26	doModule		ok++ (PMO)
 **************************************************************************/
void doModule(int modIdx) {
    /* process or skip the module, based on flag set in libTable */
    if (TstBit(libTable[num_lib_files], modIdx))
        doObjFile();
    else if (fseek(moduleFp, moduleSize, SEEK_CUR) == -1)
        seek_err();

    if (fseek(libraryFp, symSize, SEEK_CUR) == -1)
        seek_err();
}

/**************************************************************************
 27	visitModules	sub_0b38h	ok++ (PMO)
 **************************************************************************/

void visitModules(vmfuncptr funptr) {
    int cntModules;

    for (cntModules = 0; cntModules != num_modules; ++cntModules) {
        if (fread(libBuf, 12, 1, libraryFp) != 1)
            unexp_eof();

        symSize    = conv_btou16(libBuf);
        symCnt     = conv_btou16(libBuf + 2);
        moduleSize = conv_letou32(libBuf + 4);

        readName(fname_obj = (char *)libBuf + 12);
        funptr(cntModules);
        fname_obj = 0;
    }
}
