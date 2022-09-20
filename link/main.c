/*
 * File created 14.11.2021, last modified 01.01.2022
 *
 * The c.c file is part of the restored LINK.COM program
 * from the Hi-Tech C compiler v3.09 package.
 *
 *	Andrey Nikitin	01.01.2022
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if CPM
#include <sys.h>
#endif

#include "link.h"

#ifndef CPM
static void errMessage(char const *fmt, ...);
#endif
static void skipRecData();
static char isLibrary(char *fname);

/* record handler {pass1, pass2} */
static void (*recHandler[][2])() = {
    /* 6c3e */
    { NULL, NULL },                             /* 6c3e 0 ""	  */
    { (void (*)())textRecPass1, textRecPass2 }, /* 6c42 1 "TEXT"   */
    { psectRecPass1, skipRecData },             /* 6c46 2 "PSECT"  */
    { relocRecPass1, relocRecPass2 },           /* 6c4a 3 "RELOC"  */
    { symRecPass1, symRecPass2 },               /* 6c4e 4 "SYM"	  */
    { skipRecData, startRecPass2 },             /* 6c52 5 "START"  */
    { endRecPass1, endRecPass2 },               /* 6c56 6 "END"	  */
    { identRecPass1, skipRecData },             /* 6c5a 7 "IDENT"  */
    { xpsectRecPass1, skipRecData }             /* 6c5e 8 "XPSECT" */
};

static void (*finPassHandler[2])() = { finPass1, finPass2 };
static char usageMsg[]                    = /* 6c66 */
    "Usage: link [-cbase][-dsymfile][-r][-n][-s][-x][-z][-oofile][-pspec][-mmap]{-usym}[-wwidth] "
    "input ...";



bool haveEntryPt;         /* 7c9e   */
char *libraryName;        /* 7c9f * */
bool optLM;              /* 7ca1 * */
bool optC;                /* 7ca2 * */
FILE *symFp;              /* 7ca3   */
uint8_t pass;             /* 7ca5 * */
char *symFileName;          /* 7ca6   */
int cntUnresolved;        /* 7ca8   */
char *objFileName;        /* 7caa * */
bool optR;               /* 7cac * */
static char *mapFileName;          /* 7cad   */
bool optS;               /* 7caf * */
uint16_t fileIdx;       /* 7cb0   */
bool optH;               /* 7cb2   */
uint16_t recLen;          /* 7cb3   */
char *outFileName;        /* 7cb5   */
bool optI;               /* 7cb7 * */
char *psectLoc;     /* 7cb8   */
bool optX;               /* 7cbb * */
FILE *outFp;              /* 7cbc   */
bool optL;               /* 7cbe * */
int libFileIdx;           /* 7cbf * */
bool optM;                /* 7cc1 * */
bool optZ;               /* 7cc2   */
static int errCnt;              /* 7cc3   */
uint32_t offsetAddress;   /* 7cc5   */
int numRecord;            /* 7cc9   */
bool optN;               /* 7ccb * */


/**************************************************************************
 31	main		sub_0c6b	ok++ (PMO)
 **************************************************************************/
int main(int argc, char **argv) {
    char *pOption;
#ifndef CPM
    moduleFp = stdin;
#endif
#if CPM
    if (argc == 1) {
        argv = _getargs(0, "link");
        argc = _argc_;
    }
#endif
    allocSymTab(); /* PMO: moved before -U option which uses symtab */

    for (--argc, ++argv; argc != 0 && **argv == '-'; --argc, ++argv) {

        pOption = *argv + 1;
        while (*pOption) {
            switch (*pOption++) {
            case 'R':
            case 'r': /* Leave the output relocatable */
                optR = 1;
                break;

            case 'L':
            case 'l': /* Retain absolute relocation info */
                if ((*pOption == 'm') ||
                    (*pOption == 'M')) { /* Will retain only segement relocation */
                    optLM = 1;          /* information */
                    pOption++;
                    break;
                }
                optL = 1; /*m11: */
                break;

            case 'N':
            case 'n': /* Sort symbols by address */
                optN = 1;
                break;

            case 'C':
            case 'c':      /* Produce a binary output file offset */
                optC = 1; /* by value */
                parseNum(&pOption, &offsetAddress);
                break;

            case 'S':
            case 's': /* Strip symbol information from output file */
                optS = 1;

            case 'X':
            case 'x': /* Suppress local symbols in output file */
                optX = 1;

            case 'Z':
            case 'z':      /* Suppress trivial (compiler-generated) */
                optZ = 1; /* symbols in the output file */
                break;

            case 'O':
            case 'o': /* Call output file name */
                if (outFileName || *pOption == '\0')
                    fatalErr("Illegal -o flag");
                else {

                    outFileName = pOption;
                    pOption    = "";
                }
                break;

            case 'P':
            case 'p': /* Spec is a psectSym location specification */
                if (psectLoc|| *pOption == '\0')
                    fatalErr("Illegal -p flag");
                else {
                    psectLoc = pOption;
                    pOption        = "";
                }
                break;

            case 'M':
            case 'm': /* Write a link map to the file name */
                if (mapFileName != 0)
                    fatalErr("Duplicate -m flag");
                else {
                    optM     = 1;
                    mapFileName = *pOption ? pOption : "l.map";
                    pOption   = "";
                }
                break;

            case 'U':
            case 'u': /* Make symbol initially undefined */
                if (*pOption == '\0')
                    fatalErr("Missing arg to -u");
                else {
                    addSym(pOption, 0x10);
                    pOption = "";
                }
                break;

            case 'H':
            case 'h':
                optH = 1;

            case 'D':
            case 'd': /* Write a symbol file */
                if (symFileName != 0)
                    fatalErr("Duplicate -d flag");
                else {
                    symFileName = *pOption ? pOption : "l.sym";
                    pOption   = "";
                }
                break;

            case 'W':
            case 'w': /* Specify map width */
                if (!isdigit(*pOption) != 0)
                    fatalErr("Missing arg to -w");
                else {
                    width   = atoi(pOption);
                    pOption = "";
                }
                break;

            case 'I':
            case 'i': /* Ignore undefined symbols */
                optI = 1;
                break;
            default:
                fatalErr("Illegal flag %c\n%s", *(pOption - 1), usageMsg);
                break;
            } /* end switch */
        }     /* end pOption while */
    }         /* end argc while */

    if (optC && (optR || optL)) {
        fprintf(stderr, "-c illegal with -r or -l");
        exit(1);
    }
    if (argc == 0)
        fatalErr(usageMsg);
    /* create_symtab();  moved to before option processing as -U uses symbol table */
    if (outFileName == 0) { /* Assign default output file name */
        if (optC)
            outFileName = "l.bin";
        else
            outFileName = "l.obj";
    }
    outFp = fopen(outFileName, "wb");
    if (outFp == 0)
        fatalErr("%s: Can't create", outFileName);
    if (optM && *mapFileName && freopen(mapFileName, "w", stdout) == 0)
        fatalErr("%s: Can't create", mapFileName);

    if (symFileName != 0) {
        if ((symFp = fopen(symFileName, "w")) == 0)
            fatalErr("%s: Can't create", symFileName);
    }
    absSym        = addSym("", SF_PSECT | 0xD0);
    libFileIdx = 0;
    for (fileIdx = 0; argc != fileIdx; ++fileIdx) {
        if (isLibrary(argv[fileIdx]) != 0)
            ++libFileIdx;
    }
    allocModuleArrays(libFileIdx);
    for (pass = 0; pass < 2; ++pass) {
        libFileIdx = 0;
        for (fileIdx = 0; fileIdx < argc; ++fileIdx) {
#ifdef CPM
            if (freopen((objFileName = argv[fileIdx]), "rb", stdin) == 0)
#else
            if (freopen((objFileName = argv[fileIdx]), "rb", stdin) == 0 &&
                freopen(mkLibPath(objFileName), "rb", stdin) == 0)
#endif
                fatalErr("%s: Can't open", objFileName);
            if (isLibrary(objFileName)) { /* lib file */
                openLibrary();
                ++libFileIdx;
            } else
                doObjFile();
            objFileName = 0;
        } /*    / finPass1 */
        (finPassHandler[pass])();
        if (errCnt != 0)
            exit(1); /*    \ finPass2 */
    }
    exit(0);
} /* End main */

/**************************************************************************
 32	doObjFile	ok++ (PMO)
 **************************************************************************/
void doObjFile() {
    do {
        readRecHdr();
        (recHandler[recTyp][pass])();
    } while (recTyp != END_RECORD);
    numRecord = 0;
    objFileName = 0;
}

/**************************************************************************
 33	sub-10a3h	ok++ (PMO)
 **************************************************************************/
static void skipRecData() {

    readRecData(recbuf);
}

/**************************************************************************
 34	is_library	sub_10ach	ok++ (PMO)
 **************************************************************************/
static char isLibrary(char *fname) {

    return (fname = strrchr(fname, '.')) && (strcmp(fname, ".lib") == 0 || strcmp(fname, ".LIB") == 0);
}

#ifdef CPM
/* original non stdarg functions */

/**************************************************************************
 35	err_message	sub_10fdh	ok++ (PMO)
 **************************************************************************/
static void errMessage(fname, p2, p3, p4, p5) char *fname;
{

    fflush(stdout);

    if (libraryName)
        fprintf(stderr, "%s: ", libraryName);
    if (objFileName)
        fprintf(stderr, "%s: ", objFileName);
    if (numRecord != 0)
        fprintf(stderr, "%d: ", numRecord);

    fprintf(stderr, fname, p2, p3, p4, p5);
    fputc('\n', stderr);
}

/**************************************************************************
 36	fatal_err	sub_1187h	ok++ (PMO)
 **************************************************************************/
void fatalErr(fname, p2, p3, p4, p5) {

    errMessage(fname, p2, p3, p4, p5);
    exit(1);
}

/**************************************************************************
 37	simpl_err	sub_11bfh	ok++ (PMO)
 **************************************************************************/
void simpleErr(fname, p2, p3, p4, p5) {

    errMessage(fname, p2, p3, p4, p5);
    ++errCnt;
}

/**************************************************************************
 38	warning		sub_11f2h	ok++ (PMO)
 **************************************************************************/
void warning(fname, p2, p3, p4, p5) char *fname;
{

    fprintf(stderr, fname, p2, p3, p4, p5);
    fprintf(stderr, " (warning)\n");
}

/**************************************************************************
 39	badFormat	sub_1232h	ok++ (PMO)
 **************************************************************************/
void badFormat(fname, p2, p3, p4, p5) {

    errMessage("bad object code format");
    fatalErr(fname, p2, p3, p4, p5);
}

#else
/**************************************************************************
 shared err_message using va_list
 **************************************************************************/
static void verrMsg(char const *fmt, va_list args) {

    fflush(stdout);

    if (libraryName)
        fprintf(stderr, "%s: ", libraryName);
    if (objFileName)
        fprintf(stderr, "%s: ", objFileName);
    if (numRecord != 0)
        fprintf(stderr, "%d: ", numRecord);

    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
}

static void errMessage(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    verrMsg(fmt, args);
    va_end(args);
}

/**************************************************************************
 36	fatalErr	sub_1187h	ok++ (PMO)
 **************************************************************************/
_Noreturn void fatalErr(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    verrMsg(fmt, args);
    va_end(args);
    exit(1);
}

/**************************************************************************
 37	simpleErr	sub_11bfh	ok++ (PMO)
 **************************************************************************/
void simpleErr(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    verrMsg(fmt, args);
    va_end(args);
    ++errCnt;
}

/**************************************************************************
 38	warning		sub_11f2h	ok++ (PMO)
 **************************************************************************/
void warning(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, " (warning)\n");
    va_end(args);
}

/**************************************************************************
 39	badFormat	sub_1232h	ok++ (PMO)
 **************************************************************************/
void badFormat(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    errMessage("bad object code format");
    verrMsg(fmt, args);
    va_end(args);
    exit(1);
}
#endif
