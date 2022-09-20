/*
 * File created 14.11.2021, last modified 30.12.2021.
 *
 * The link.h file is part of the restored LINK.COM program
 * from the Hi-Tech C compiler v3.09 package.
 *
 *	Andrey Nikitin  30.12.2021
 */

/*
 *	Linker Limitations
 */
#define MAX_PSECTS  20  /* Maximum program sections */
#define MAX_SYMBOLS 997 /* Maximum symbols          */
/*
 *	Derived quantities
 */
#define SIZE_PSECTS MAX_PSECTS * sizeof(psect_t *) /*  540 */
#define SIZE_SYMTAB MAX_SYMBOLS * sizeof(sym_t *)  /* 1994 */

/*
 *	These definitions are not present in the header files of the compiler.
 */
#if CPM
#define SEEK_SET 0 /* from beginning of file */
#define SEEK_CUR 1 /* from current position  */
#define SEEK_END 2 /* from end of file       */
#endif

/* Object record -> Length (16 bits) | Record type (8 bits) | Data (Length*8 bits) */
#define RECORD_LEN      0
#define RECORD_TYPE     2
#define RECORD_HDR      3 /* length of record hdr */

#define TEXT_RECORD     1
/* data -> offset (32 bits) | psectSym name | bytes* */
#define TEXT_OFFSET     0
#define TEXT_PNAME      4

#define PSECT_RECORD    2
/* data -> flags (16 bits) | psectSym name */
#define PSECT_FLAGS     0
#define PSECT_PNAME     2

#define RELOC_RECORD    3
/* data -> (offset (16 bits) | reloc type (8 bits) | psect or external name)* */
#define RELOC_OFFSET    0
#define RELOC_TYPE      2
#define RELOC_NAME      3

#define SYM_RECORD      4
/* data ->  value (32 bits) | flags (16 bits) | psectSym name | symbol name  */
#define SYM_VALUE       0
#define SYM_FLAGS       4
#define SYM_PNAME       6

#define START_RECORD    5
/* data -> offset (32 bits) | psectSym name */
#define START_OFFSET    0
#define START_PNAME     4

#define END_RECORD      6
/* data -> flags (16 bits) */
#define END_FLAGS       0

#define IDENT_RECORD    7
/* data ->  byte order (32 bits) | byte order (16 bits) | machine name | version number (16 bits) */
#define IDENT_ORDER32   0
#define IDENT_ORDER16   4
#define IDENT_MACHINE   6

#define XPSECT_RECORD   8
/* data -> max size (32 bits) | align (16 bits) |
           selector (16 bits) | reserved (24 bits) | type (8 bits) | psectSym name | class name
   (optional) */
#define XPSECT_MAX      0
#define XPSECT_RELOC    4
#define XPSECT_SELECTOR 6
#define XPSECT_TYPE     11
#define XPSECT_PNAME    12

#define SEGMENT_RECORD  9

#if defined(__STDC__) || defined(__STDC_VERSION__)
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#if __STDC_VERSION__ < 201112L
#define _Noreturn
#endif
#if __STDC_VERSION__ >= 201710L
#define register
#endif
#define bmove(f, t, c) memcpy(t, f, c)
#else
typedef char bool;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
#define true 1
#define false 0
#define const
#define _Noreturn
#define PRIx32 "lx" /* assume uint32_t is a long */
#define PRId32 "ld"
#endif

typedef struct _sym {
    union {
        uint32_t value;
        struct _psect *pinfo; /* for psect name entries */
    } p;
    struct _sym *psectSym;
    char *name;
    uint16_t flags;
    uint8_t fileId;
} sym_t;

/*
 *	Value low order 4 bits flags from SYM record
 */
#define SF_NULL      0
#define SF_STACK     1
#define SF_COMM      2
#define SF_REGNAM    3
#define SF_LINENO    4
#define SF_FILNAM    5
#define SF_EXTERN    6
#define SF_LOWMASK   0xF
#define LowFlags(f)  ((f)&SF_LOWMASK)
/* bit flags for other info */
#define SF_GLOBAL    0x10
#define SF_PURE      0x20
#define SF_OVRLD     0x40
#define SF_ABS       0x80
#define SF_BIGSEG    0x100
#define SF_BPAGE     0x200
#define SF_CLASS     0x4000
#define SF_PSECT     0x8000
#define HighFlags(f) ((f)&0xfff0)

typedef struct _psect {
    uint32_t linkPt;
    uint32_t loadPt;
    uint32_t maxSize;
    uint16_t align;
    uint32_t blkStartAddress;
    uint32_t endAddr;
    sym_t *psectSym;
    sym_t *classSym;
    bool originSet;
} psect_t;

/* underlying type for library module vector */
typedef unsigned vec_t;

/****************************************************************
 * Prototype functions are located in sequence of being in
 * original binary image of LINK.COM
 *
 * ok++ - Full binary compatibility with code in original file;
 * ok   - Code generated during compilation differs slightly,
 *        but is logically correct;
 ****************************************************************/
/*------------------------------------------------------------------- File io.c */
void identRecPass1();                    /* 014b  2 */
void readRecHdr();                       /* 0227  3 */
void readRecData(uint8_t *);             /* 02b3  4 */
void writeRec(int, uint16_t, uint8_t *); /* 02f6  5 */
void flushText();                        /* 050a  7 */
void wrRecord();                         /* 0518  8 */
void chkAddRecordItem(uint8_t, size_t);  /* 0591  9 */
int16_t btoi16(register uint8_t *p1);    /* 05e1 11 */
void u16tob(uint16_t, uint8_t *);        /* 0616 12 */
uint32_t btou32(uint8_t *);              /* 0647 13 */
void u32tob(uint32_t, uint8_t *);        /* 0647 14 */
uint32_t btou24(uint8_t *p1);            /* 0706 15 */
void u24tob(uint32_t, uint8_t *);        /* 0783 16 */

/*------------------------------------------------------------------- File lib.c */
void allocModuleArrays(int); /* 07d3 18 */
void openLibrary();          /* 084a 21 */
void libPass1();             /* 08cd 22 */
void libPass2();             /* 0a65 25 */
/*------------------------------------------------------------------- File main.c */
/* int main(int argc, char **argv); /* 0c6b 31 */
void doObjFile(); /* 1073 32 */
#ifdef CPM
_Noreturn void fatalErr(); /* 1187 36 */
void simpleErr();          /* 11bf 37 */
void warning();            /* 11f2 38 */
void badFormat();          /* 1232 39 */
#else
/*void errMessage(char const *fmt, ...);         /* 10fd 35 */
_Noreturn void fatalErr(char const *fmt, ...); /* 1187 36*/
void simpleErr(char const *fmt, ...);          /* 11bf 37 */
void warning(char const *fmt, ...);            /* 11f2 38 */
void badFormat(char const *fmt, ...);
#endif

/*---------------------------------------------------------------- File misc.c */
void *xalloc(size_t); /* 1265 40 */
#ifndef CPM
#define clrbuf(b, n) memset(b, 0, n)
#endif

/*---------------------------------------------------------------- File reloc.c */
void relocRecPass1(); /* 12d2 42 */
void relocRecPass2(); /* 1339 43 */
/*void fixup(int, uint16_t, uint32_t); /* 1912 44 */

/*------------------------------------------------------------------ File sym.c */
void allocSymTab();                 /* 1af4 45 */
sym_t *getSymbol(char *, int);      /* 1c1a 47 */
sym_t *addSym(char *, int);         /* 1c37 48 */
void symRecPass2();                 /* 1e32 50 */
void symRecPass1();                 /* 203a 51 */
void psectRecPass1();               /* 233a 54 */
void xpsectRecPass1();              /* 2382 55 */
void endRecPass1();                 /* 2514 56 */
void endRecPass2();                 /* 259e 57 */
char parseNum(char **, uint32_t *); /* 25a8 58 */
void finPass1();                    /* 28ca 60 */
void finPass2();                    /* 33ad 61 */

/*----------------------------------------------------------------- File text.c */
int textRecPass1();   /* 3b30 68 */
void textRecPass2();  /* 3c04 69 */
void startRecPass2(); /* 3cea 70 */

/*---------------------------------------------------------------- File extra.c */
#ifndef CPM
char const *mkLibPath(char const *s);
#endif

/* End prototype functions LINK */

/*------------------------------------------------------------------- File io.c */
extern uint8_t *nonTextRecPtr;     /* 6acd */
extern void (*libHandlers[])();    /* 6be7 */
extern FILE *moduleFp;             /* 6c28 */
extern int width;                  /* 6c2a */
extern uint8_t *textRecPtr;        /* 7617 */
extern uint8_t nonTextRecBuf[512]; /* 7619 */
extern int textLen;                /* 781d */
extern uint8_t textRecBuf[512];    /* 781f */
extern uint8_t recTyp;             /* 7a1f */
extern uint8_t *endAddr;           /* 7a20 */
extern uint8_t recbuf[512];        /* 7a22 */
extern int alreadyWritten;         /* 7c22 */
extern uint8_t *curAddr;           /* 7c24 */
/*------------------------------------------------------------------- File main.c */

extern bool haveEntryPt;       /* 7c9e */
extern char *libraryName;      /* 7c9f */
extern bool optLM;             /* 7ca1 */
extern bool optC;              /* 7ca2 */
extern FILE *symFp;            /* 7ca3 */
extern uint8_t pass;           /* 7ca5 */
extern char *symFileName;      /* 7ca6 */
extern int cntUnresolved;      /* 7ca8 */
extern char *objFileName;      /* 7caa */
extern bool optR;              /* 7cac */
extern bool optS;              /* 7caf */
extern uint16_t fileIdx;       /* 7cb0 */
extern bool optH;              /* 7cb2 */
extern uint16_t recLen;        /* 7cb3 */
extern char *outFileName;      /* 7cb5 */
extern bool optI;              /* 7cb7 */
extern char *psectLoc;         /* 7cb8 */
extern bool optX;              /* 7cbb */
extern FILE *outFp;            /* 7cbc */
extern bool optL;              /* 7cbe */
extern int libFileIdx;         /* 7cbf */
extern bool optM;              /* 7cc1 */
extern bool optZ;              /* 7cc2 */
extern uint32_t offsetAddress; /* 7cc5 */
extern int numRecord;          /* 7cc9 */
extern bool optN;              /* 7ccb */

/*------------------------------------------------------------------- File sym.c */
extern sym_t *absSym; /* 7cd2   */

/*------------------------------------------------------------------- File text.c */

extern uint32_t textBaseAddress; /* 7f00   */
