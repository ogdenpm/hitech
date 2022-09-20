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
/* clang-format on */
#ifdef __GNUC__
#include <limits.h>
#endif

#ifdef _WIN32
#define DIRSEP "/\\:"
#else
#define DIRSEP "/"
#define stricmp strcasecmp
#endif

#define MEMINITIAL  256
#define MEMEXTEND   4096
#define LABELEXTEND 128

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
void procFile();
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

typedef struct {
    uint8_t val;
    uint16_t flags;
    char *rname;
} mem_t;

#define HASVAL 0x100

typedef struct {
    unsigned addr;
    char *label;
} label_t;

typedef struct _psect {
    struct _psect *next;
    char *pname;
    uint16_t flags; /* after dumping this is set to 0xffff as a sentinal */
    unsigned labCnt;
    unsigned labSize;
    label_t *labels;
    unsigned lowUsed;
    unsigned highUsed;
    unsigned memSize;
    mem_t *mem;
} psect_t;

int complexCnt;

uint8_t recBuf[512];
char *fname;
int recLen;
int recNum;
uint8_t major;
uint8_t minor;
uint8_t recType;
char ascii[16 + 7 + 1]; /* 16 bytes + possible addition 7 reloc bytes */
uint8_t asciiIdx;
bool haveAscii;
#define ASCIICOL (16 * 4 + 4 + 4)
psect_t *psectList;

bool dumpRecords; /* use -R to force old record format */
psect_t *curPsect;
unsigned curBase;

#define TYPE(n) (unsigned)(((n) >> 4) & 0xf)
#define SIZE(n) (unsigned)((n)&0xf)

void printPsectInfo(char *pname, uint16_t flags);
void addLabel(char *psectName, unsigned addr, char *name);
psect_t *getPsect(char *pname);
void displayPsect(psect_t *p);

void releaseMem() {
    psect_t *q;
    for (psect_t *p = psectList; p; p = q) {
        if (p->labSize) {
            for (unsigned i = 0; i < p->labCnt; i++)
                free(p->labels[i].label);
            free(p->labels);
        }
        if (p->memSize) {
            for (unsigned i = p->lowUsed; i < p->highUsed; i++)
                if (p->mem[i].rname)
                    free(p->mem[i].rname);
            free(p->mem);
        }
        free(p->pname);
        q = p->next;
        free(p);
    }
    psectList = NULL;
}

void memChk(psect_t *mp, size_t addr) {
    if (addr >= mp->memSize) {
        size_t newSize;
        for (newSize = MEMINITIAL; addr >= newSize; newSize += MEMEXTEND)
            ;
        if (!(mp->mem = realloc(mp->mem, sizeof(mem_t) * newSize)))
            fatal("Out of memory");

        memset(mp->mem + mp->memSize, 0, (newSize - mp->memSize) * sizeof(mem_t));
        mp->memSize = newSize;
    }
}

void addMem(uint8_t *pdata, int ldata) {
    memChk(curPsect, curBase + ldata);
    if (curPsect->lowUsed > curBase)
        curPsect->lowUsed = curBase;
    if (curPsect->highUsed < curBase + ldata)
        curPsect->highUsed = curBase + ldata;
    for (int i = 0; i < ldata; i++) {
        curPsect->mem[curBase + i].val = *pdata++;
        curPsect->mem[curBase + i].flags |= HASVAL;
    }
}

void addReloc(unsigned addr, char *name, uint8_t fixup) {
    addr += curBase;
    if (TYPE(curPsect->mem[addr].flags) & 0xff)
        fprintf(stderr, "log %04X already has relocation, skipping %s\n", addr, name);
    else {
        curPsect->mem[addr].flags |= fixup | HASVAL;
        curPsect->mem[addr].rname = strdup(name);
        if (TYPE(fixup) <= RRPSECT &&
            (TYPE(fixup) & 3) < 2) { /* for abs and psect rel add local label */
            if (SIZE(fixup) > 4)
                fatal(
                    "At %s %04X - Relocation of item > 4 bytes not supported in pretty format mode",
                    name, addr);
            uint32_t val = 0;
            for (unsigned i = 0; i < SIZE(fixup); i++)
                if (addr + i < curPsect->highUsed && (curPsect->mem[addr + i].flags & HASVAL))
                    val += (curPsect->mem[addr + i].val) << (i * 8);
            if (TYPE(fixup) < RRABS)
                addLabel(name, val, NULL);
            else
                addLabel(name, (addr + val + 2) & ((1 << SIZE(fixup) * 8) - 1), NULL);
        }
    }
}

/* add a label to the given psect, keeping the labels in address, name order
   A name of NULL is treated specially as it is used to reflect a relocated
   item's target
   if an existing label exists at the address, then the add is ignored
   if there is a NULL label entry and a non NULL label at the address is being
   added then the new label replaces the NULL one

*/
void addLabel(char *psectName, unsigned addr, char *name) {
    psect_t *mp = getPsect(psectName);
    int insertAt;
    if (mp->labCnt == 0 || addr > mp->labels[mp->labCnt - 1].addr) // most likely case
        insertAt = mp->labCnt;
    else {
        for (insertAt = 0; addr > mp->labels[insertAt].addr; insertAt++) // get addr based insert
            ;
        if (addr == mp->labels[insertAt].addr) {
            if (name == NULL)
                return;
            if (mp->labels[insertAt].label == NULL) {
                if (name)
                    mp->labels[insertAt].label = strdup(name);
                return;
            }
            /* refine for label name if more than one label at address */
            while (addr == mp->labels[insertAt].addr &&
                   strcmp(name, mp->labels[insertAt].label) < 0)
                insertAt++;
        }
    }
    if (mp->labCnt == mp->labSize &&
        !(mp->labels = realloc(mp->labels, (mp->labSize += LABELEXTEND) * sizeof(label_t))))
        fatal("Out of memory");
    if (insertAt != mp->labCnt)
        memmove(&mp->labels[insertAt + 1], &mp->labels[insertAt],
                sizeof(label_t) * (mp->labCnt - insertAt));
    mp->labels[insertAt].addr  = addr;
    mp->labels[insertAt].label = name ? strdup(name) : NULL;
    mp->labCnt++;
}

void fixRelocLabels() {
    char fake[128];
    char *s;

    for (psect_t *p = psectList; p; p = p->next) {
        fake[1] = '\0';
        if (strcmp(p->pname, "text") == 0 || strcmp(p->pname, "_TEXT") == 0)
            fake[0] = '$';
        else if (strcmp(p->pname, "data") == 0)
            fake[0] = '\'';
        else if (strcmp(p->pname, "bss") == 0)
            fake[0] = '"';
        else if (strcmp(p->pname, "(abs)") == 0)
            fake[0] = '@';
        else
            sprintf(fake, "%s'", p->pname);
        s = strchr(fake, '\0');
        for (unsigned i = 0; i < p->labCnt; i++)
            if (p->labels[i].label == NULL) {
                sprintf(s, "%04X", p->labels[i].addr);
                p->labels[i].label = strdup(fake);
            }
    }
}

/* locate the first label with a given address in the given psect */
/* this version does a linear search even though a binary search would be more efficient */
char *getLabel(char *psectName, unsigned addr) {
    psect_t *mp = getPsect(psectName);

    for (unsigned i = 0; i < mp->labCnt; i++)
        if (mp->labels[i].addr == addr)
            return mp->labels[i].label;
    fatal("label at %04X not found in psect %s", addr, psectName);
}

psect_t *getPsect(char *pname) {
    psect_t **p = &psectList;
    if (*pname == '\0')
        pname = "(abs)";
    while (*p && strcmp((*p)->pname, pname))
        p = &(*p)->next;
    if (!*p) {
        if (!(*p = calloc(1, sizeof(psect_t))))
            fatal("Out of memory");
        (*p)->pname   = strdup(pname);
        (*p)->lowUsed = UINT_MAX;
    }
    return *p;
}

void printLabel(psect_t *mp, int n) {
    printf("\t\t%s:\n", mp->labels[n].label);
}

int displayVal(psect_t *mp, size_t addr) {
    int width    = 0;
    uint32_t val = 0;
    if (mp->mem[addr].flags == 0) {
        width             = printf("xx");
        ascii[asciiIdx++] = '?';
    } else if (mp->mem[addr].flags == HASVAL) {
        width = printf("%02X", mp->mem[addr].val);
        if (' ' <= mp->mem[addr].val && mp->mem[addr].val <= '~') {
            ascii[asciiIdx++] = mp->mem[addr].val;
            haveAscii         = true;
        } else
            ascii[asciiIdx++] = '.';
    } else {
        int rType = TYPE(mp->mem[addr].flags);
        int rSize = SIZE(mp->mem[addr].flags);

        for (int i = 0; i < rSize; i++)
            if (addr + i < mp->highUsed) {
                if (mp->mem[addr + i].flags & HASVAL)
                    val += (mp->mem[addr + i].val) << (i * 8);
                ascii[asciiIdx++] = '.';
            }
        char *name = mp->mem[addr].rname;
        switch (rType) {
        case RABS:
            width += printf("%s%s", *name ? "@" : "", getLabel(name, val));
            break;
        case RPSECT:
            width += printf("%s", getLabel(name, val));
            break;
        case RNAME:
            width += printf("%s", name);
            if (val)
                width += printf(val < 16 ? "+%d" : "+0x%X", val);
            break;
        case COMPLEX:
            width += printf("%s", name);
            break;
        case RRABS:
            width += printf("REL(%s%s)", *name ? "@" : "",
                            getLabel(name, (addr + val + 2) & ((1 << rSize * 8) - 1)));
            break;
        case RRPSECT:
            width += printf("REL(%s)", getLabel(name, (addr + val + 2) & ((1 << rSize * 8) - 1)));
            break;
        case RRNAME:
            width += printf("REL(%s", name);
            val = (val + 2) & ((1 << rSize * 8) - 1);
            if (val)
                width += printf(val < 16 ? "+%d" : "+0x%X", val);
            width += printf(")");
            break;
        case UNK7:
            width += printf("RELOC ERROR(7)");
            break;
        case RSABS:
            width += printf("ASEG(%s)", *name ? name : "(abs)");
            break;
        case RSPSECT:
            width += printf("SEG(%s)", *name ? name : "(abs)");
            break;
        case RSNAME:
            width += printf("SEG(%s", name);
            if (val)
                width += printf(val < 16 ? "+%d" : "+0x%X", val);
            width += printf(")");
            break;
        case UNK11:
            width += printf("RELOC ERROR(11)");
            break;
        case RELBITS_RABS:
            width += printf("ARBITS(%s)", *name ? name : "(abs)");
            break;
        case RELBITS_RPSECT:
            width += printf("RBITS(%s)", *name ? name : "(abs)");
            break;
        case RELBITS_RNAME:
            width += printf("RBITS(%s", name);
            if (val)
                width += printf(val < 16 ? "+%d" : "+0x%X", val);
            width += printf(")");
            break;
        case RELBITS_COMPLEX:
            printf("RBITS(%s)", name);
            break;
        }
    }
    return width;
}

#define BCNT(pm) (((pm).flags & 0xf) ? ((pm).flags & 0xf) : 1)

void display() {
    /* the order psects are displayed, NULL displays rest in order they were seen */
    static char *order[] = { "cpm", "text", "_TEXT", "data", "bss", "stack", "" };
    fixRelocLabels();
    /* (abs) always goes first  */
    for (psect_t *p = psectList; p; p = p->next)
        if (strcmp(p->pname, "(abs)") == 0) {
            displayPsect(p);
            break;
        }
    /* next comes the absolute psects in address order */
    psect_t *lowp;
    do {
        lowp             = NULL;
        uint32_t lowAddr = UINT32_MAX;
        for (psect_t *p = psectList; p; p = p->next) {
            if ((p->flags & 0200) && p->flags != 0xffff &&
                (p->memSize ? p->lowUsed < lowAddr // check actual data
                 : p->labCnt
                     ? p->labels[0].addr < lowAddr // if no data, then just defined labels e.g. bss
                     : false)) { // psect no data & no labels will be handled as defaults
                lowp    = p;
                lowAddr = p->memSize ? p->lowUsed : p->labels[0].addr;
            }
        }
        if (lowp)
            displayPsect(lowp);
    } while (lowp);
    /* finally to relocatable segments in "order" */
    int orderIdx = 0;
    do {
        char *psectName = order[orderIdx];
        for (psect_t *p = psectList; p; p = p->next) {
            if (strcmp(p->pname, psectName) == 0) { // found
                if (p->flags != 0xffff)             // process if not already done
                    displayPsect(p);
                break;
            } else if (p->flags != 0xffff && *psectName == '\0')
                displayPsect(p);
        }
    } while (*order[orderIdx++]);
}

void printAscii(int col) {
    if (haveAscii) {
        ascii[asciiIdx] = '\0';
        printf("%*s|%s|", col < ASCIICOL ? ASCIICOL - col : 1, "", ascii);
    }
    haveAscii = false;
    asciiIdx  = 0;
}

void displayPsect(psect_t *p) {
    unsigned addr;
    unsigned rowAddr;
    int col, tcol;
    unsigned labIdx;
    printf("\t\tpsect ");
    printPsectInfo(p->pname, p->flags);
    for (labIdx = 0; labIdx < p->labCnt && p->labels[labIdx].addr <= p->lowUsed; labIdx++)
        printf("\n\t%04X  %s:", p->labels[labIdx].addr, p->labels[labIdx].label);
    col     = ASCIICOL;
    rowAddr = p->lowUsed & ~0xf;
    for (addr = p->lowUsed; addr < p->highUsed; addr += BCNT(p->mem[addr])) {
        if (rowAddr != (addr & ~0xf)) {
            printAscii(col);
            col = ASCIICOL;
        }

        for (; labIdx < p->labCnt && p->labels[labIdx].addr <= addr; labIdx++) {
            printAscii(col);
            printf("\n\t%04X  %s:", p->labels[labIdx].addr, p->labels[labIdx].label);
            col = ASCIICOL;
        }

        tcol = (addr & 0xf) * 4 + ((addr & 0xf) / 4) + ((addr & 0xf) / 8);
        if (tcol < col + 1) {
            putchar('\n');
            col = 0;
        }
        if (col == 0)
            printf("\t%04X  ", rowAddr = (addr & ~0xf));
        col += printf("%*s", tcol - col, "");
        col += displayVal(p, addr);
    }
    printAscii(col);
    if (p->memSize && addr != p->highUsed)
        printf("\nWarning relocation item extends past end of psect mem\n");
    for (; labIdx < p->labCnt; labIdx++)
        printf("\n\t%04X  %s:", p->labels[labIdx].addr, p->labels[labIdx].label);
    p->flags = 0xffff;
    putchar('\n');
    putchar('\n');
}

int main(int argc, char **argv) {
    char **parg;
    FILE *fp;

    if (argc == 1) {
        char *s = argv[0];
        char *t;
        while ((t = strpbrk(s, DIRSEP)))
            s = t + 1;
        fprintf(stderr, "Usage: %s [-R] objfile+\n", s);
        exit(0);
    }

    for (parg = argv + 1; parg < argv + argc; parg++) {
        if (stricmp(*parg, "-R") == 0)
            dumpRecords = true;
        else {
            recNum = 0;
            if ((fp = fopen(fname = *parg, "rb")) == NULL)
                fatal("cannot open");
            printf("%s\n", fname);
            procFile(fp);
            fclose(fp);
            if (!dumpRecords) {
                display();
                releaseMem();
            }
        }
    }
    exit(0);
}

void procFile(FILE *fp) {
    handler_t *recEntry;
    while (readRecord(fp)) {
        if (recType >= 20)
            fatal("Bad record type %d", recType);
        recEntry = &recHandlers[recType];
        if (dumpRecords ||
            (recType != TEXT && recType != RELOC && recType != SYM && recType != PSECT))
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

// data dump modified to print 16 items per line. Original dumped 21
// also data offset is shown at start of line and a - is placed
// between the two groups of 10 bytes on a line

void textHandler() {
    uint8_t *pdata;
    char *psname;
    int dataLen;
    curBase = get32(recBuf);
    psname  = (char *)(recBuf + 4);
    for (pdata = (uint8_t *)psname; *pdata; pdata++)
        ;
    pdata++;
    dataLen = recLen - (int)(strlen(psname) + 5);
    if (dataLen < 0)
        fatal("text record has length too small: %d", dataLen);

    if (dumpRecords) {
        printf("\t\t%s\t0x%X\t%d", psname, curBase, dataLen);
        int rowAddr = 1;
        int col     = 0;
        int tcol;
        for (unsigned addr = curBase; addr < curBase + dataLen; addr++) {
            if (rowAddr != (addr & ~0xf)) {
                printAscii(col);
                putchar('\n');
                col = 0;
            }
            tcol = (addr & 0xf) * 4 + ((addr & 0xf) / 4) + ((addr & 0xf) / 8);
            if (col == 0)
                printf("\t\t%04X  ", rowAddr = (addr & ~0xf));
            if (*pdata && *pdata <= '~') {
                ascii[asciiIdx++] = *pdata;
                haveAscii         = true;
            } else
                ascii[asciiIdx++] = '.';
            col += printf("%*s%02X", tcol - col, "", *pdata++);
        }
        printAscii(col);
        putchar('\n');
    } else {
        curPsect = getPsect(psname);
        addMem(pdata, dataLen);
    }
}

/* modified to print out include unknown low 4 bits and show
 * true unknown bit rather than bit >> 4
 */

void printPsectInfo(char *pname, uint16_t flags) {
    printf("%s", pname);
    for (uint8_t bit = 0; flags; flags >>= 1, bit++)
        if (flags & 1) {
            if (bit < 4 || bit >= 11)
                printf("\tUNKNOWN(0x%X)", 1 << bit);
            else
                printf("\t%s", psectNames[bit - 4]);
        }
}

void psectHandler() {
    uint16_t flags = get16(recBuf);
    char *pname    = recBuf[2] ? (char *)recBuf + 2 : "(abs)";

    if (dumpRecords) {
        printf("\t\t");
        printPsectInfo(pname, flags);
        putchar('\n');
    } else
        getPsect(pname)->flags = flags;
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
    uint8_t flags;
    uint16_t offset;

    for (p = recBuf; p < recBuf + recLen;) {
        offset = get16(p);
        flags  = p[2];
        p += 3;
        tType = flags >> 4;
        if (tType == COMPLEX || tType == RELBITS_COMPLEX) {
            if (dumpRecords)
                printf("\t\t%-3d %04X\t%s\t\t%d", offset, curBase + offset, relocNames[tType],
                       flags & 0xf);
            else
                printf("\t\tcomplex-%d", ++complexCnt);
            parseComplex(&p);
            if (!dumpRecords) {
                char complexId[16];
                sprintf(complexId, "complex-%d", complexCnt);
                addReloc(curBase + offset, complexId, flags);
            }
        } else {
            if (dumpRecords)
                printf("\t\t%-3d %04X\t%s\t%s\t%d\n", offset, curBase + offset, relocNames[tType],
                       p, flags & 0xf);
            else
                addReloc(offset, (char *)p, flags);
            p += strlen((char *)p) + 1;
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
    uint32_t loc;
    for (uint8_t *p = recBuf; p < recBuf + recLen; p += strlen(psname) + strlen(syname) + 8) {
        syname = psname = (char *)p + 6;
        while (*syname++)
            ;
        loc            = get32(p);
        uint16_t flags = get16(p + 4);

        if (dumpRecords) {
            printf("\t\t%-15s %s\t%08" PRIX32, syname,
                   *psname              ? psname
                   : (flags & 0xf) == 6 ? ""
                                        : "(abs)",
                   loc);
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
        } else if ((flags & 0xf) == 6)
            printf("\t\t%s %s\n", flags & 0x10 ? "External" : "Local Undefined", syname);
        else
            addLabel(psname, loc, syname);
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
