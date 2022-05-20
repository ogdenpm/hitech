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
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
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
    uint32_t linkAddress;
    uint32_t loadAddress;
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
/*------------------------------------------------------------------- File a.c */
extern void err_write();                           /* 013d  1 ok++ */
extern void identRecPass1();                       /* 014b  2 ok++ */
extern void readRecHdr();                          /* 0227  3 ok++ */
extern void readRecData(uint8_t *);                /* 02b3  4 ok++ */
extern void writeRec(int, uint16_t, uint8_t *);    /* 02f6  5 ok++ */
extern void writeText();                           /* 0365  6 ok+- */
extern void flushText();                           /* 050a  7 ok++ */
extern void wrRecord();                            /* 0518  8 ok++ */
extern void chkAddRecordItem(uint8_t, size_t);     /* 0591  9 ok++ */
extern void conv_i16tole(int16_t, uint8_t *);      /* 05bf 10 ok++ */
extern int16_t conv_letoi16(register uint8_t *p1); /* 05e1 11 ok+- */
extern void conv_u16tob(uint16_t, uint8_t *);      /* 0616 12 ok++ */
extern uint32_t conv_btou32(uint8_t *);            /* 0647 13 ok++ */
extern void conv_u32tob(uint32_t, uint8_t *);      /* 0647 14 ok++ */
extern uint32_t conv_btou24(uint8_t *p1);          /* 0706 15 ok++ */
extern void conv_u24tob(uint32_t, uint8_t *);      /* 0783 16 ok++ */
/*------------------------------------------------------------------- File b.c */
extern void seek_err();                       /* 07c5 17 ok++ */
extern void allocModuleArrays(int);           /* 07d3 18 ok++ */
extern uint32_t conv_letou32(uint8_t *);      /* 07ea 19 ok++ */
extern uint16_t conv_btou16(uint8_t *);       /* 082a 20 ok++ */
extern void openLibrary();                    /* 084a 21 ok++ */
extern void libPass1();                       /* 08cd 22 ok+- */
extern void scanModule(int);                  /* 0944 23 ok++ */
extern void chkModuleNeeded(char *, uint8_t); /* 0a23 24 ok++ */
extern void libPass2();                       /* 0a65 25 ok++ */
extern void doModule(int);                    /* 0aaf 26 ok++ */
typedef void (*vmfuncptr)(int);               /* added as hitech C gets confused */

extern void visitModules(vmfuncptr); /* 0b38 27 ok++ */
/*------------------------------------------------------------------- File c.c */
typedef void (*vsfuncptr)(char *, uint8_t);

extern void visitSymbols(vsfuncptr); /* 0bc9 28 ok++ */
extern void readName(char *);        /* 0c2e 29 ok++ */
extern void unexp_eof();             /* 0c62 30 ok++ */
/* extern int main();                   0c6b 31 ok+- */

extern void doObjFile();        /* 1073 32 ok++ */
extern void skipRecData();      /* 10a3 33 ok++	ptr_l6c3eh */
extern char is_library(char *); /* 10ac 34 ok++ */
#ifdef CPM
extern void err_message();         /* 10fd 35 ok++ */
extern _Noreturn void fatal_err(); /* 1187 36 ok++ */
extern void simpl_err();           /* 11bf 37 ok++ */
extern void warning();             /* 11f2 38 ok++ */
extern void badFormat();           /* 1232 39 ok++ */
#else
void err_message(char const *fmt, ...);         /* 10fd 35 ok++ */
_Noreturn void fatal_err(char const *fmt, ...); /* 1187 36 ok++ */
void simpl_err(char const *fmt, ...);           /* 11bf 37 ok++ */
void warning(char const *fmt, ...);             /* 11f2 38 ok++ */
void badFormat(char const *fmt, ...);
#endif

extern void *xalloc(size_t);                                /* 1265 40 ok++ */
#ifdef CPM
extern void clrbuf(char *, size_t);                         /* 1296 41 ok++ */
#else
#define clrbuf(b, n) memset(b, 0, n)
#endif
extern void relocRecPass1();                                /* 12d2 42 ok++	ptr_l6c3eh */
extern void relocRecPass2();                                /* 1339 43 ok+-	ptr_l6c3eh */
extern void fixup(int, uint16_t, uint32_t);                 /* 1912 44 ok+- */
extern void create_symtab();                                /* 1af4 45 ok++ */
extern sym_t **getSymbolSlot(char *, int);                  /* 1b00 46 ok++ */
extern sym_t *getSymbol(char *, int);                       /* 1c1a 47 ok++ */
extern sym_t *addSym(char *, int);                          /* 1c37 48 ok++ */
extern void prSymbol(char *, uint32_t, int, sym_t *);       /* 1d1d 49 ok++ */
extern void symRecPass2();                                  /* 1e32 50 ok++	ptr_l6c3eh */
extern void symRecPass1();                                  /* 203a 51 ok++	ptr_l6c3eh */
extern void defineSym(char *, sym_t *, uint32_t, int);      /* 2197 52 ok++ */
extern void defineIfNeeded(char *, sym_t *, uint32_t, int); /* 22c3 53 ok++ */
extern void psectRecPass1();                                /* 233a 54 ok++	ptr_l6c3eh */
extern void xpsectRecPass1();                               /* 2382 55 ok++	ptr_l6c3eh */
extern void endRecPass1();                                  /* 2514 56 ok++	ptr_l6c3eh */
extern void endRecPass2();                                  /* 259e 57 ok++	ptr_l6c3eh */
extern char parseLongVal(char **, uint32_t *);              /* 25a8 58 ok++ */
extern void setPsectOrigin(psect_t *);                      /* 2766 59 ok++ */
/*------------------------------------------------------------------- File ds.c */
extern void finPass1(); /* 28ca 60 ok+- */
/*------------------------------------------------------------------- File e.c */
extern void finPass2();                             /* 33ad 61 ok++ */
extern void wrSymbol(sym_t *);                      /* 3420 62 ok++ */
extern char isLocalName(char *);                    /* 3533 63 ok++ */
extern void prFileLinkMap();                        /* 3576 64 ok++ */
extern void output_summary(psect_t *);              /* 36f3 65 ok++ */
extern void wr_linkmap();                           /* 3773 66 ok++ */
extern int compare_fun(const void *, const void *); /* 3a5b 67 ok++ */
extern int textRecPass1();                          /* 3b30 68 ok++	ptr_l6c3eh */
extern void textRecPass2();                         /* 3c04 69 ok++	ptr_l6c3eh */
extern void startRecPass2();                        /* 3cea 70 ok++	ptr_l6c3eh */

/*------------------------------------------------------------------- File extra.c */
#ifndef CPM
char const *mkLibPath(char const *s);
#endif


/* End prototype functions LINK */

/*------------------------------------------------------------------- File a.c */
extern uint8_t *nonTextRecPtr;      /* 6acd   */
extern uint8_t order32[];           /* 6acf   */
extern uint8_t order16[];           /* 6ad3   */
extern void (*libHandlers[])();     /* 6be7 * */
extern FILE *moduleFp;              /* 6c28 * */
extern int width;                   /* 6c2a * */
extern char *rec_types[];           /* 6c2c   */
extern void (*recHandler[][2])();   /* 6c3e   */
extern void (*finPassHandler[2])(); /* 6c62 * */
extern char usageMsg[];             /* 6c66 * */
extern psect_t *nextPsect;          /* 6f69   */

/*------------------------------------------------------------------- File a.c */
extern bool haveIdent;                /* 7616   */
extern uint8_t *textRecPtr;           /* 7617   */
extern uint8_t nonTextRecBuf[512];    /* 7619   */
extern uint32_t targetAddress;        /* 7819   */
extern int textLen;                   /* 781d   */
extern uint8_t textRecBuf[512];       /* 781f   */
extern uint8_t rectyp;                /* 7a1f   */
extern uint8_t *endAddr;              /* 7a20   */
extern uint8_t recbuf[512];           /* 7a22   */
extern int alreadyWritten;            /* 7c22   */
extern uint8_t *curAddr;              /* 7c24   */
extern uint32_t moduleSize;           /* 7c26 * */
extern int symSize;                   /* 7c2a * */
extern int num_modules;               /* 7c2c * */
extern bool moduleLoaded;             /* 7c2e * */
extern int size_symbols;              /* 7c2f * */
extern bool moduleNeeded;             /* 7c31 * */
extern int num_files;                 /* 7c32 * */
extern FILE *libraryFp;               /* 7c34 * */
extern int symCnt;                    /* 7c36 * */
extern uint8_t libBuf[100];           /* 7c38 * */
extern vec_t **libTable;              /* 7c9c * */
extern bool haveEntryPt;              /* 7c9e   */
extern char *libraryName;             /* 7c9f * */
extern bool key_LM;                   /* 7ca1 * */
extern bool key_C;                    /* 7ca2 * */
extern FILE *symFp;                   /* 7ca3   */
extern uint8_t linker_pass;           /* 7ca5 * */
extern char *fname_sym;               /* 7ca6   */
extern int cntUnresolved;             /* 7ca8   */
extern char *fname_obj;               /* 7caa * */
extern bool key_R;                    /* 7cac * */
extern char *fname_map;               /* 7cad   */
extern bool key_S;                    /* 7caf * */
extern uint16_t curFileId;            /* 7cb0   */
extern bool key_H;                    /* 7cb2   */
extern uint16_t length;               /* 7cb3   */
extern char *fname_outp;              /* 7cb5   */
extern bool key_I;                    /* 7cb7 * */
extern char *psect_location;          /* 7cb8   */
extern bool key_X;                    /* 7cbb * */
extern FILE *outFp;                   /* 7cbc   */
extern bool key_L;                    /* 7cbe * */
extern int num_lib_files;             /* 7cbf * */
extern bool key_M;                    /* 7cc1 * */
extern bool key_Z;                    /* 7cc2   */
extern int err_num;                   /* 7cc3   */
extern uint32_t offset_address;       /* 7cc5   */
extern int numRecord;                 /* 7cc9   */
extern bool key_N;                    /* 7ccb * */
extern char *fixupName;               /* 7_psect   */
extern uint32_t linkAddress;          /* 7cce   */
extern sym_t *absSym;                 /* 7cd2   */
extern psect_t psectInfo[MAX_PSECTS]; /* 7cd4   */
extern uint32_t saveLoadAddress;      /* 7ef0   */
extern uint32_t maxLinkAddress;       /* 7ef4   */
extern int newSymCnt;                 /* 7ef8   */
extern uint32_t loadAddress;          /* 7efa   */
extern sym_t **symbol_table;          /* 7efe   */
extern uint32_t textBaseAddress;      /* 7f00   */
