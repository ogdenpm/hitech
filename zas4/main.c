/*
 *
 * The main.c file is part of the restored ZAS.EXE program
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
#include "zas.h"

FILE *crfFp;          /* 2694 */
char crfNameBuf[30];  /* 2696 */
bool i_opt;           /* 26b4 */
char l_opt;           /* 26b5 */
char phase;           /* 26b6 */
char objNameBuf[30];  /* 26b8 */
bool j_opt;           /* 26d6 */
bool s_opt;           /* 26d7 */
int16_t nInput;       /* 26d8 */
char *crfFileName;    /* 26da */
int16_t inputFileCnt; /* 26dc */
uint8_t c_opt;        /* 26de */
char **inputFileList; /* 26e0 */
bool u_opt;           /* 26e2 */
int16_t numerror;     /* 26e4 */
bool e_opt;           /* 26e6 */
bool n_opt;           /* 26e7 */
bool x_opt;           /* 26e8 */
char *lstFileName;    /* 26ea */
char *objFileName;    /* 26ec */
FILE *objFp;          /* 26ee */

/***************************************************************
 77 2bb2 ++
 ***************************************************************/
int main(int argc, char **argv) {
    int16_t i;
    size_t extPt;

    for (--argc, ++argv; argc > 0 && **argv == '-'; ++argv, --argc) {
        switch (argv[0][1]) {
        case 'E':
        case 'e': /* Change default fatalErr message format */
            e_opt = true;
            break;
        case 'L':
        case 'l': /* Place an assembly listing in the file */
            if (argv[0][2])
                lstFileName = &argv[0][2];
            l_opt = true;
            break;
        case 'U':
        case 'u': /* Treat undefined symbols as  external */
            u_opt = true;
            break;
        case 'J':
        case 'j': /* Attempt to optimize jumps to branches */
            j_opt = true;
            break;
        case 'W':
        case 'w': /* Set page width */
            if ((width = (int16_t)atoi(&argv[0][2])) < 41)
                fatalErr("Page width must be >= 41");
            break;
        case 'P':
        case 'p': /* Set page len */
            if ((pageLen = (int16_t)atoi(&argv[0][2])) < 15 && pageLen != 0)
                fatalErr("Page length must be 0 or >= 15");
            break;

        case 'N':
        case 'n': /* Ignore arithmetic overflow in expressions */
            n_opt = true;
            break;
        case 'I':
        case 'i': /* Print listing macro extensions */
            i_opt = true;
            break;
        case 'S':
        case 's': /* Suppress "Size fatalErr" messages */
            s_opt = true;
            break;
        case 'O':
        case 'o': /* Place the object code in file */
            objFileName = &argv[0][2];
            if (*objFileName == '\0')
                fatalErr("No arg to -o");
            break;
        case 'X':
        case 'x': /* Prevent inclusion of local symbols in object file */
            x_opt = true;
            break;
        case 'C':
        case 'c': /* Produce cross reference information in a file */
            ++c_opt;
            break;
        default:
            fatalErr("Illegal switch %c", argv[0][1]);
            break;
        }
    }
    if (argc <= 0)
        fatalErr("No file arguments");
    if (!objFileName) {
        for (i = 0, extPt = strlen(argv[0]); argv[0][i]; i++)
            if (argv[0][i] == '.')
                extPt = i;
        if (extPt > 25)
            extPt = 25;
#ifdef _MSC_VER
#pragma warning(disable : 6053) /* the buffers used below are all zeros before here so             \
                                   strncpy/strcat is safe */
#endif
        strncpy(objNameBuf, *argv, extPt);
        strcat(objNameBuf, ".obj");
        objFileName = objNameBuf;
        strncpy(crfNameBuf, *argv, extPt);
        strcat(crfNameBuf, ".crf");
#ifdef _MSC_VER
#pragma warning(default : 6053)
#endif
        crfFileName = crfNameBuf;
    }
    nInput        = 0;
    inputFileList = argv;
    inputFileCnt  = (int16_t)argc;
    enterAbsPsect();
    phase = 0;
    if (j_opt) { /* jump optimizations */
        doPass();
        resetVals();
        nInput = 0;
        phase  = 1;
    }
    doPass();
    phase = 2;
    resetVals();
    if (c_opt && !(crfFp = fopen(crfFileName, "w")))
        fatalErr("Can't create cross reference file %s", crfFileName);
    nInput = 0;
    objFp  = fopen(objFileName, "wb");
    if (!objFp)
        fatalErr("Can't create %s", objFileName);

    controls = l_opt;
    if (controls && lstFileName && !freopen(lstFileName, "w", stdout))
        fatalErr("Can't create %s", lstFileName);
    setHeading("");
    if (l_opt && width == 0)
        width = 80;

    initSymRecord();
    writeObjHeader();
    doPass();
    writeRecords();
    sortSymbols();
    if (l_opt) {
        prSymbols();
        if (l_opt && j_opt)
            printf("\n%d jump optimizations\n", jmpOptCnt);
        topOfPage();
    }
    addObjAllSymbols(); /* m31: */
    addObjEnd();
    exit(numerror != 0);
}

/**************************************************************************
 78 2ef4 ++
 **************************************************************************/
char *getNextFile() {
    return nInput < inputFileCnt ? inputFileList[nInput++] : NULL;
}

/**************************************************************************
 79 2f16 ++
 **************************************************************************/

void prMsg(char const *fmt, va_list args) {
    if (curFileName && *curFileName)
        fprintf(stderr, "%s:%d:\t", curFileName, curLineno);

    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
}

/**************************************************************************
 80 2f5c ++
 **************************************************************************/
_Noreturn void fatalErr(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    prMsg(fmt, args);
    va_end(args);
    fclose(stdout);
    exit(1);
}

/**************************************************************************
 81 2f7c ++
 **************************************************************************/

void error(char const *fmt, ...) {
    if (phase != 2)
        return;

    va_list args;
    va_start(args, fmt);
    prMsg(fmt, args);
    va_end(args);
    putErrCode(*fmt);
    if (++numerror < 100)
        return;
    fatalErr("Too many errors");
}
