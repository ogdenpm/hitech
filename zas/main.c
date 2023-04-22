/*
 *
 * The main.c file is part of the restored ZAS.COM program
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
#include "zas.h"

FILE *crfFp;          /* 9e18 */
char crfNameBuf[30];  /* 9e1a */
bool i_opt;           /* 9e38 */
char l_opt;           /* 9e39 */
char phase;           /* 9e3a */
char objNameBuf[30];  /* 9e3b */
bool j_opt;           /* 9e59 */
bool s_opt;           /* 9e5a */
int nInput;           /* 9e5b */
char *crfFileName;    /* 9e5d */
int inputFileCnt;     /* 9e5f */
uint8_t c_opt;        /* 9e61 */
char **inputFileList; /* 9e62 */
bool u_opt;           /* 9e64 */
int numerror;         /* 9e65 */
bool e_opt;           /* 9e67 */
bool n_opt;           /* 9e68 */
bool x_opt;           /* 9e69 */
char *lstFileName;    /* 9e6a */
char *objFileName;    /* 9e6c */
FILE *objFp;          /* 9e6e */




/***************************************************************
 59	main	sub_2ef4 +++
 * a block of 3 basic blocks is located differently, specifically
 * the for block code just after the if (!objFileName)
 * also uses bc instead of hl for assignment in case 'o'
 * code is otherwise same
 ***************************************************************/
int main(int argc, char **argv) {
    size_t extPt;

#ifndef CPM 
    if (argc == 2 && strcasecmp(argv[1], "-v") == 0) {
        showVersion(argv[1][1] == 'V');
        exit(0);
    }
#endif
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
            if ((width = atoi(&argv[0][2])) < 41)
                fatalErr("Page width must be >= 41");
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
    if (!objFileName || c_opt) { /* PMO fix incase -O and -C specified */
        char *name = fname(argv[0]);
        char *dot = strrchr(name, '.');
        extPt     = dot ? (dot - name) : strlen(name);
        if (extPt > 25)
            extPt = 25;
        if (!objFileName) {
            strncpy(objNameBuf, name, extPt);
            strcat(objNameBuf, ".obj"); /* relies on objNameBuf having all zeros at start */
            objFileName = objNameBuf;
        }
        strncpy(crfNameBuf, name, extPt); /* relies on crfNameBuf having all zeros at start */
        strcat(crfNameBuf, ".crf");
        crfFileName = crfNameBuf;
    }
    nInput        = 0;
    inputFileList = argv;
    inputFileCnt  = argc;
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
    if (!(objFp = fopen(objFileName, "wb")))
        fatalErr("Can't create %s", objFileName);

    if ((controls = l_opt) && lstFileName && !freopen(lstFileName, "w", stdout))
        fatalErr("Can't create %s", lstFileName);
    setHeading("");
    if (l_opt && width == 0)
        width = 80;

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
 60	getNextFile	+++
 **************************************************************************/
char *getNextFile() {
    if (nInput < inputFileCnt)
        return inputFileList[nInput++];
    return 0;
}
/**************************************************************************
 61	fatalErr	sub_32bfh	+++
 **************************************************************************/
#ifdef CPM
_Noreturn void fatalErr(p1, p2, p3) char *p1;
{
    prMsg(p1, p2, p3);
    exit(1);
}
#else
_Noreturn void fatalErr(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    prMsg(fmt, args);
    va_end(args);
    exit(1);
}
#endif

/**************************************************************************
 62	error	sub-32e6h	+++
 **************************************************************************/
#ifdef CPM
void error(p1, p2, p3) char *p1;
{
    if (phase != 2)
        return;
    prMsg(p1, p2, p3);
    putErrCode(*p1);
    if (++numerror < 100)
        return;
    fatalErr("Too many errors");
}
#else
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

#endif

/**************************************************************************
 63	prMsg	+++
 **************************************************************************/
#ifdef CPM
void prMsg(p1, p2, p3) char *p1;
{
    if (curFileName && *curFileName)
        fprintf(stderr, "%s:%d:\t", curFileName, curLineno);

    fprintf(stderr, p1, p2, p3);
    fputc('\n', stderr);
}
#else
void prMsg(char const *fmt, va_list args) {
    if (curFileName && *curFileName)
        fprintf(stderr, "%s:%d:\t", curFileName, curLineno);

    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
}
#endif
