/*
 * Reverse engineered version of the HI-TECH Software dump Program
 *
 * The C source code is a decompilation of Hi-Tech Software's dump utility
 * as distributed as part of pacific C
 *
 * The file compiles cleanly with MSVC and GCC
 *
 * In decompiling the utility a number of minor changes were made
 * 1) The -v flag was removed as it wasn't used for anything. It may have
 *    been used in a debug version as the path to the file being dumped
 *    was also saved and never used. It too has been removed.
 * 2) Some minor bug fixes, see comments in line
 * 3) Minor clean up of code, including removal of code that would never execute
 * 4) Minor reformatting of the generated dump which I find makes it easier to read
 * 5) Added code to clean up memory allocated during expression processing
 * 6) Rather than use l.obj as a default file, if no files are specified
 *    a simple usage message is printed
 *
 *  Mark Ogden 2-Feb-2022
 */
// clang-format off
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "showVersion.h"
// clang-format on
#ifdef _WIN32
#define DIRSEP "/\\:"
#else
#define DIRSEP "/"
#endif

typedef struct {
    char *name;
    void (*handler)();
} handler_t;

enum {
    TEXT = 1,
    PSECT,
    RELOC,
    SYM,
    START,
    END,
    IDENT,
    XPSECT,
    SEGMENT,
    XSYM,
    SIGNAT,
    FNINFO,
    FNCONF,
    SEGSTART,
    PSECTLIM,
    LISTRELOC,
    LR_TEXT,
    LR_RELOC,
    COND_EXPR
};

void textHandler();
void psectHandler();
void relocHandler();
void symHandler();
void startHandler();
void endHandler();
void identHandler();
void xpsectHandler();
void segmentHandler();
void xsymHandler();
void signatHandler();
void fninfoHandler();
void fnconfHandler();
void psectlimHandler();
void listrelocHandler();
void lr_textHandler();
void lr_relocHandler();
void cond_exprHandler();
void dumpFile();
bool readRecord(FILE *fp);

_Noreturn void fatal(char *fmt, ...);
uint32_t get16(uint8_t *p);
uint32_t get32(uint8_t *p);
void *xmalloc(size_t);

uint8_t order32[]       = { 0, 1, 2, 3 };
uint8_t order16[]       = { 0, 1 };

handler_t recHandlers[] = { { NULL, NULL },
                            { "TEXT", textHandler },
                            { "PSECT", psectHandler },
                            { "RELOC", relocHandler },
                            { "SYM", symHandler },
                            { "START", startHandler },
                            { "END", endHandler },
                            { "IDENT", identHandler },
                            { "XPSECT", xpsectHandler },
                            { "SEGMENT", segmentHandler },
                            { "XSYM", xsymHandler },
                            { "SIGNAT", signatHandler },
                            { "FNINFO", fninfoHandler },
                            { "FNCONF", fnconfHandler },
                            { "SEGSTART", startHandler },
                            { "PSECTLIM", psectlimHandler },
                            { "LISTRELOC", listrelocHandler },
                            { "LR_TEXT", lr_textHandler },
                            { "LR_RELOC", lr_relocHandler },
                            { "COND_EXPR", cond_exprHandler } };

enum {
    RABS = 0,
    RPSECT,
    RNAME,
    COMPLEX,
    RRABS,
    RRPSECT,
    RRNAME,
    UNK7,
    RSABS,
    RSPSECT,
    RSNAME,
    UNK11,
    RELBITS_RABS,
    RELBITS_RPSECT,
    RELBITS_RNAME,
    RELBITS_COMPLEX
};

char *psectNames[] = { "GLOBAL", "PURE", "OVRLD", "ABS", "BIGSEG", "BASEPAGE", "BITSEG" };
char *relocNames[] = { "RABS",         "RPSECT",         "RNAME",         "COMPLEX",
                       "RRABS",        "RRPSECT",        "RRNAME",        "Unknown(7)",
                       "RSABS",        "RSPSECT",        "RSNAME",        "Unknown(11)",
                       "RELBITS RABS", "RELBITS RPSECT", "RELBITS RNAME", "RELBITS COMPLEX" };
char *symNames[]   = { "",        "STACK",       "COMM",     "REG",    "LINENO", "FILNAM",
                       "EXTERN",  "LOCAL",       "REDIRECT", "RC_END", "RC_LOW", "RC_HI",
                       "RC_VAL",  "RC_ADD",      "RC_SUB",   "RC_MUL", "RC_DIV", "RC_SHL",
                       "RC_SHR",  "RC_AND",      "RC_OR",    "RC_XOR", "RC_CPL", "RC_NEG",
                       "RC_BITF", "Bad RC type", "RC_MOD",   "RC_RNG", "RC_KEY", "RC_DEFD" };

// spacing added  around operators to make it easier to read expressions
char *exprNames[]   = { "",    "low ", "high ",       "RC_VAL", " + ",  " - ", " * ",
                        " / ", " << ", " >> ",        " & ",    " | ",  " ^ ", " ~",
                        " -",  "bit",  "Bad RC type", " % ",    " >= ", "Key:" };
char *fninfoNames[] = { "Invalid", "FNCALL", "FNARG",    "FNINDIR",  "FNADDR",
                        "FNSIZE",  "FNROOT", "FNINDARG", "FNSIGARG", "FNBREAK" };

/* expression stack */
struct {
    char *str;
    uint32_t op;
} stack[256];

uint8_t recBuf[512];
char *fname;
int recLen;
int recNum;
uint8_t major;
uint8_t minor;
uint8_t recType;
uint32_t curBase; /* base address for relocation */

int main(int argc, char **argv) {
    char **parg;

    CHK_SHOW_VERSION(argc, argv);
    if (argc == 1) {
        char *s = argv[0];
        char *t;
        while (t = strpbrk(s, DIRSEP))
            s = t + 1;
        fprintf(stderr, "Usage: %s objfile+\n", s);
        exit(0);
    }
    for (parg = argv + 1; parg < argv + argc; parg++) {
        recNum = 0;
        if (freopen(fname = *parg, "rb", stdin) == NULL)
            fatal("cannot open");
        printf("%s\n", fname);
        dumpFile();
    }
    exit(0);
}

void dumpFile() {
    handler_t *recEntry;
    while (readRecord(stdin)) {
        if (recType >= 20)
            fatal("Bad record type %d", recType);
        recEntry = &recHandlers[recType];
        printf("\t%d\t%s\t%u\n", recNum, recEntry->name, recLen);
        recEntry->handler();
        if (recType == END)
            break;
    }
}

bool readRecord(FILE *fp) {
    if (fread(recBuf, 1, 3, fp) != 3)
        return false;
    recNum++;
    recLen  = (recBuf[1] << 8) + recBuf[0];
    recType = recBuf[2];
    if (recType == 0 || recType >= 20)
        fatal("unknown record type: %d");
    if (recLen > 512)
        fatal("record too long (%s): %d", recHandlers[recType].name, recLen);
    if (fread(recBuf, 1, recLen, fp) != recLen)
        fatal("incomplete record: type = %d, length = %d", recType, recLen);
    return true;
}

// data dump modified to print 20 items per line. Original dumped 21
// also data offset is shown at start of line and a - is placed
// between the two groups of 10 bytes on a line

void textHandler() {
    uint8_t *pdata;
    char *psname;
    int16_t dataLen;
    int addr = 0;
    curBase  = get32(recBuf);
    psname   = (char *)(recBuf + 4);
    for (pdata = (uint8_t *)psname; *pdata; pdata++)
        ;
    pdata++;
    dataLen = recLen - (int)(strlen(psname) + 5);
    if (dataLen < 0)
        fatal("text record has length too small: %d", dataLen);
    printf("\t\t%s\t%04" PRIX32 "\t%d", psname, curBase, dataLen);
    int rowAddr = 1;
    int col     = 0;
    int tcol;
    for (unsigned addr = curBase; addr < curBase + dataLen; addr++) {
        tcol = (addr & 0xf) * 3 + ((addr & 0xf) / 4) + ((addr & 0xf) / 8);
        if (rowAddr != (addr & ~0xf)) {
            putchar('\n');
            col = 0;
        }
        if (col == 0)
            printf("\t\t%04X  ", rowAddr = (addr & ~0xf));
        while (col < tcol) {
            putchar(' ');
            col++;
        }
        printf("%02X", *pdata++);
        col += 2;
    }
    putchar('\n');
}

/* modified to print out include unknown low 4 bits and show
 * true unknown bit rather than bit >> 4
 */
void psectHandler() {
    uint16_t flags;
    uint8_t bit;

    printf("\t\t%s", recBuf[2] != '\0' ? (char *)recBuf + 2 : "(abs)");
    flags = get16(recBuf);

    for (bit = 0; flags; flags >>= 1, bit++)
        if (flags & 1) {
            if (bit < 4 || bit >= 11)
                printf("\tUNKNOWN(0x%X)", 1 << bit);
            else
                printf("\t%s", psectNames[bit - 4]);
        }
    putchar('\n');
}

uint32_t convertToInfix(int idx) {
    uint32_t rval2;
    uint32_t rval1;
    uint32_t op;

    if (idx < 0) {
        printf("idx < 0\n");
        return 0;
    }
    op = stack[idx].op;
    switch (op) {
    case 0:
        return 0;
    default:
        printf("%s", stack[idx].str);
        return 1;
    case 1:
    case 2:
    case 13:
    case 14:
        printf("%s", stack[idx].str);
        if (stack[idx - 1].op <= 15 && stack[idx - 1].op != 3)
            putchar('(');
        rval1 = convertToInfix(idx - 1);
        if (stack[idx - 1].op <= 15 && stack[idx - 1].op != 3)
            putchar(')');
        return rval1 + 1;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 17:
    case 18:
        if (stack[idx - 1].op <= 15 && stack[idx - 1].op != 3)
            putchar('(');
        rval1 = convertToInfix(idx - 1) + 1;
        if (stack[idx - 1].op <= 15 && stack[idx - 1].op != 3)
            putchar(')');
        printf("%s", stack[idx].str);
        if (stack[idx - rval1 + 1].op <= 15 && stack[idx - rval1 + 1].op != 3)
            putchar('(');
        rval2 = convertToInfix(idx - rval1);
        if (stack[idx - rval1 + 1].op <= 15 && stack[idx - rval1 + 1].op != 3)
            putchar(')');
        return rval1 + rval2;
    case 15:
        printf("bitf(");
        rval1 = convertToInfix(idx - 1) + 1;
        printf(",");
        rval1 += convertToInfix(idx - rval1);
        printf(",");
        rval1 += convertToInfix(idx - rval1);
        printf(")");
        return rval1;
    case 80:
    case 96:
        printf("REL %s", stack[idx].str);
        return 1;
    case 144:
    case 160:
        printf("SEG %s", stack[idx].str);
        return 1;
    }
}

void parseComplex(uint8_t **pp) {

    int stkIdx;
    uint8_t op;

    stkIdx = 0;
    while (true) {
        op = *((*pp)++);
        switch ((stack[stkIdx].op = op)) {
        case 0:
            break;
        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 17:
            stack[stkIdx++].str = strdup(exprNames[op]);
            continue;
        case 3:
            stack[stkIdx].str = xmalloc(11);
            sprintf(stack[stkIdx++].str, "0x%" PRIX32, get32(*pp));
            *pp += 4;
            continue;
        case 18:
            stack[stkIdx++].str = strdup(exprNames[op]);
            break;
        case 19:
            printf("   Key: %s", *pp);
            *pp += strlen((char *)*pp) + 1;
            continue;
        case 20:
            stack[stkIdx].str = xmalloc(strlen((char *)*pp) + 12); // original had strlen(pp) !!;
            sprintf(stack[stkIdx++].str, "Defined(\"%s\")", *pp);  // same problem as above
            *pp += strlen((char *)*pp) + 1;
            continue;
        case 16:
        case 32:
        case 80:
        case 96:
        case 144:
        case 160:
            stack[stkIdx++].str = strdup((char *)*pp);
            *pp += strlen((char *)*pp) + 1;
            continue;
        default:
            stack[stkIdx++].str = strdup("????");
            continue;
        }
        if (stkIdx != 0) {
            printf("   -> ");
            convertToInfix(--stkIdx);
            /* PMO added clean up of malloced strings */
            while (stkIdx >= 0) {
                free(stack[stkIdx--].str);
            }
        }
        break;
    }
    putchar('\n');
}

// removed type >= 16 test as it cannot happen
// also modified the type test to avoid << 4
void relocHandler() {
    uint8_t *p;
    uint8_t tType;
    uint16_t offset;
    for (p = recBuf; p < recBuf + recLen;) {
        tType  = p[2] >> 4;
        offset = get16(p);
        printf("\t\t%-3d %04X\t%s", offset, curBase + offset, relocNames[tType]);
        if (tType == COMPLEX || tType == RELBITS_COMPLEX) {
            printf("\t\t%d", p[2] & 0xf);
            p += 3;
            parseComplex(&p);
        } else {
            printf("\t%s\t%d\n", p + 3, p[2] & 0xf);
            p += strlen((char *)p + 3) + 4;
        }
    }
}

void cond_exprHandler() {
    uint8_t *p = recBuf;
    parseComplex(&p);
}

void segmentHandler() {

    uint8_t *p;
    for (p = recBuf; p < recBuf + recLen; p += strlen((char *)p + 16) + 17) {
        printf("\t\t%s\t", p + 16);
        printf("%" PRIX32 "\t%" PRIX32 "\t%X\t%" PRIX32 "\n", get32(p + 4), get32(p), get16(p + 8),
               get32(p + 12));
    }
}

void listrelocHandler() {
    uint8_t *p = recBuf;

    printf("\t\t'%s' -> ", p);
    printf("'%s'\n", p + strlen((char *)p) + 1);
}

void lr_textHandler() {
    recBuf[recLen] = 0;
    if (recLen != 0 && recBuf[recLen - 1] == '\n')
        recBuf[recLen - 1] = 0;
    printf("\t\t'%s'\n", recBuf);
}

void lr_relocHandler() {
    for (uint8_t *p = recBuf; p < recBuf + recLen; p++) {
        printf("\t\tRELOC %2.2X ", p[5]);
        p += 7;
        parseComplex(&p);
    }
}

void fninfoHandler() {
    int tType;

    for (uint8_t *p = recBuf; p < recBuf + recLen;) {
        printf("\t\t");
        tType = *p++;
        switch (tType) {
        case 4: // FNADDR
        case 6: // FNROOT
            printf("%s\t%s\n", fninfoNames[tType], p);
            p += strlen((char *)p) + 1;
            break;
        case 1: // FNCALL
        case 2: // FNARG
        case 9: // FNBREAK
            printf("%s\t%s -> ", fninfoNames[tType], p);
            p += strlen((char *)p) + 1;
            printf("%s\n", p);
            p += strlen((char *)p) + 1;
            break;
        case 3: // FNINDIR
            printf("FNINDIR\t%s -> ", p);
            p += strlen((char *)p) + 1;
            printf("%d\n", get16(p));
            p += 2;
            break;
        case 5: // FNSIZE
            printf("FNSIZE\t%s ", p);
            p += strlen((char *)p) + 1;
            printf("%" PRId32 ":%" PRId32 "\n", get32(p), get32(p + 4));
            p += 8;
            break;
        default: // includes FNINDARG & FNSIGARG
            printf("FNUNKOWN\n");
            p = recBuf + recLen + 1;
        }
    }
}

void xsymHandler() {
    char *psname, *syname;
    for (uint8_t *p = recBuf; p < recBuf + recLen; p += strlen(psname) + strlen(syname) + 10) {
        syname = psname = (char *)p + 8;
        while (*syname++)
            ;
        uint16_t flags = get16(p + 4);
        printf("\t\t%s\t%s\t%X:%" PRIX32, syname,
               *psname       ? psname
               : (flags & 6) ? ""
                             : "(abs)",
               get16(p + 6), get32(p));

        if (flags & 0x10)
            printf("\tGLOBAL");
        flags &= 0xf;
        if (flags >= 9)
            printf("\tUNKNOWN(%d)\n", flags);
        else
            printf("\t%s\n", symNames[flags]);
    }
}

void signatHandler() {
    for (uint8_t *p = recBuf; p < recBuf + recLen; p += strlen((char *)p + 2) + 3) {
        printf("\t\t%s\t%u\n", p + 2, get16(p));
    }
}

void fnconfHandler() {
    uint8_t *p = recBuf;
    printf("\t\tPSECT %s; ", p);
    p += strlen((char *)p) + 1;
    printf("local prefix %s; ", p);
    p += strlen((char *)p) + 1;
    printf("arg prefix %s\n", p);
}

void symHandler() {
    char *psname, *syname;
    for (uint8_t *p = recBuf; p < recBuf + recLen; p += strlen(psname) + strlen(syname) + 8) {
        syname = psname = (char *)p + 6;
        while (*syname++)
            ;
        uint16_t flags = get16(p + 4);
        printf("\t\t%-15s %s\t%" PRId32, syname,
               *psname       ? psname
               : (flags & 6) ? ""
                             : "(abs)",
               get32(p));
        if (flags == 6)
            printf("\tLOCAL UNDEFINED\n");
        else {
            if (flags & 0x10)
                printf("\tGLOBAL");
            flags &= 0xf;
            if (flags >= 9)
                printf("\tUNKNOWN(%d)\n", flags);
            else
                printf("\t%s\n", symNames[flags]);
        }
    }
}

void startHandler() {
    printf("\t\t%s\t%" PRIu32 "\n", recBuf[4] ? (char *)recBuf + 4 : "(abs)", get32(recBuf));
}

void endHandler() {
    putchar('\n');
}

void identHandler() {
    int voffset = (int)strlen((char *)recBuf + 6) + 7;
    major = minor = 0;
    if (voffset + 2 <= recLen) {
        minor = recBuf[voffset + 1];
        major = recBuf[voffset];
        printf("\t\tObject code version\t= %d.%d\n", major, minor);
    }
    printf("\t\tMachine\t\t\t= %s\n", recBuf + 6);
    printf("\t\t32 bit order\t\t= %d %d %d %d\n", recBuf[0], recBuf[1], recBuf[2], recBuf[3]);
    memcpy(order32, recBuf, 4);
    printf("\t\t16 bit order\t\t= %d %d\n", recBuf[4], recBuf[5]);
    memcpy(order16, recBuf + 4, 2);
}

void xpsectHandler() {

    char *p = recBuf[12] ? (char *)recBuf + 12 : "(abs)";
    printf("\t\t%s", p);
    if (get32(recBuf) != 0)
        printf("\tsize=%" PRIu32, get32(recBuf));
    if (get16(recBuf + 4) != 0)
        printf("\treloc=%u", get16(recBuf + 4));

    if (major != 0 && get16(recBuf + 6) != 0)
        printf("\rsel=0x%X", get16(recBuf + 6));
    if ((major > 2 || (major != 0 && minor != 0)) && recBuf[11] != 0)
        printf(" type = %2.2X", recBuf[11]);
    if (major > 3 || (major == 3 && minor >= 3))
        printf(" space = %2.2X", recBuf[8]);
    if (major > 3 || (major == 3 && minor >= 4))
        printf(" delta = %2.2X", recBuf[9]);
    p = (char *)recBuf + 12;
    p += strlen(p) + 1;
    if (p < (char *)recBuf + recLen && *p != 0)
        printf(" class=%s", p);
    if (major > 3 || (major == 3 && minor >= 5)) {
        p += strlen(p) + 1;
        if (p < (char *)recBuf + recLen && *p != 0)
            printf(" with=%s", p);
    }
    putchar('\n');
}

void psectlimHandler() {

    char *p = recBuf[16] ? (char *)recBuf + 16 : "(abs)";

    printf("\t\t%s", p);
    if (get32(recBuf) != 0)
        printf("\tlimit=%" PRIu32, get32(recBuf));
    putchar('\n');
}

_Noreturn void fatal(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    putchar('\n');
    fprintf(stderr, "%s: ", fname);
    if (recNum != 0)
        fprintf(stderr, "%d: ", recNum);
    vfprintf(stderr, fmt, args);
    putc('\n', stderr);
    va_end(args);
    exit(1);
}

uint32_t get16(uint8_t *p) {
    return (p[order16[1]] << 8) + p[order16[0]];
}

uint32_t get32(uint8_t *p) {
    return p[order32[0]] + (p[order32[1]] << 8) + (p[order32[2]] << 16) + (p[order32[3]] << 24);
}

// safe malloc
void *xmalloc(size_t size) {
    void *p = malloc(size);
    if (p == NULL)
        fatal("Out of memory");
    return p;
}