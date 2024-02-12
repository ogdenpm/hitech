#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "showVersion.h"
#ifndef _MSC_VER
#define stricmp strcasecmp
#endif
unsigned short crc16(unsigned char *data_p, size_t length);

#define NODATAREF

/* record types */
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
    TOO_LONG = -1,
    PAST_END = -2
};
enum { UNDEF = 0, ABS, FIXUP };
enum { RABS, RPSECT, RNAME, RRPSECT = 5, RRNAME, RSPSECT = 9, RSNAME, RCPLX = 3 };

#define CHUNK 50 // allocation chunk for symbols

typedef unsigned char byte;
typedef unsigned short word;
#define MAXLABEL   1024
#define MAXNAMELEN 64

struct {
    int length;
    int pos;
    int tType;
    uint8_t data[512];
} record;

uint8_t code[0x8000];
uint8_t flags[0x8000];
uint16_t codesize;
uint16_t codebase;

#define EXTERNAL 0x16
#define PUBLIC   0x10
#define HASDELTA 0x20

struct {
    char *name;
    uint16_t offset;
    uint8_t tType;
} labels[MAXLABEL];
int labelCnt;


int getWord(FILE *fp) {
    int c1 = getc(fp);
    int c2 = getc(fp);
    return c2 == EOF ? -1 : c1 + c2 * 256;
}

int unpackByte() {
    return record.pos < record.length ? record.data[record.pos++] : -1;
}

int unpackWord() {
    int val1 = unpackByte();
    int val2 = unpackByte();
    return val2 < 0 ? -1 : val1 + (val2 << 8);
}

int unpackDWord() {
    int val1 = unpackWord();
    int val2 = unpackWord();
    return val2 < 0 ? -1 : (val2 << 16) + val1;
}

bool getName(FILE *fp, char *name) {
    int c;
    int i = 0;
    do {
        *name++ = c = getc(fp);
    } while (c > 0 && ++i < 128);
    return c == 0;
}

bool unpackName(char *name) {
    int c;
    int i = 0;
    do {
        *name++ = c = unpackByte();
    } while (c > 0 && ++i < 128);
    return c == 0;
}

int getRecord(FILE *fp) {
    record.length = getWord(fp);
    record.tType   = getc(fp);
    record.pos    = 0;
    if (record.tType == EOF)
        return PAST_END;
    if (record.length > 512)
        return TOO_LONG;
    if (fread(record.data, 1, record.length, fp) != record.length)
        return PAST_END;
    return record.tType;
}

void dumpPattern(FILE *fpout) {
    int j;

    int loc;
    bool hasPublic = false;
    int abs     = 0;

    for (loc = 0; loc < codesize && loc < 32; loc++)
        if (flags[loc] == ABS)
            abs++;

    if (abs < 6)
        return;

    for (loc = 0; loc < codesize && loc < 32; loc++) {
        if (flags[loc] == ABS)
            fprintf(fpout, "%02X", code[loc]);
        else
            fputs("..", fpout);
    }
    while (loc < 32) {
        fputs("..", fpout);
        loc++;
    }
    for (j = loc; loc < j + 255 && loc < codesize && flags[loc] == ABS; loc++)
        ;

    fprintf(fpout, " %02X %04X %04X ", loc - j, crc16(code + j, loc - j), codesize);

    for (int i = 0; i < labelCnt; i++)
        if (labels[i].tType == PUBLIC) {
            fprintf(fpout, ":%04X %s", labels[i].offset, labels[i].name);
            for (j = i + 1; j < labelCnt; j++) {
                if (labels[j].tType == PUBLIC && labels[j].offset == labels[i].offset) {
                    fprintf(fpout, "$%s", labels[j].name);
                    labels[j].tType = 0;
                }
            }
            putc(' ', fpout);
            hasPublic = true;
        }
    if (!hasPublic)
        fprintf(fpout, ":0000 ? ");

    for (int i = 0; i < labelCnt; i++)
        if (labels[i].tType == EXTERNAL)
            fprintf(fpout, "^%04X %s ", labels[i].offset, labels[i].name);

    for (; loc < codesize; loc++)
        if (flags[loc] == ABS)
            fprintf(fpout, "%02X", code[loc]);
        else
            fputs("..", fpout);

    fputc('\n', fpout);
}

void clearLabels() {
    for (int i = 0; i < labelCnt; i++) {
        free(labels[i].name);
        labels[i].name = NULL;
    }
    labelCnt = 0;
}

void addLabel(int offset, char *label, uint8_t tType) {
    for (int i = 0; i < labelCnt; i++) {
        if (strcmp(labels[i].name, label) == 0) {
            if (tType == PUBLIC ||
                ((labels[i].tType & HASDELTA) && code[offset] + code[offset + 1] == 0)) {
                labels[i].offset = offset;
                labels[i].tType   = tType;
            }
            return;
        }
    }
    if (labelCnt == MAXLABEL) {
        fprintf(stderr, "Too many labels\n");
        exit(1);
    }
    if (tType != PUBLIC && code[offset] + code[offset + 1])
        tType |= HASDELTA;
    labels[labelCnt].name   = strdup(label);
    labels[labelCnt].offset = offset;
    labels[labelCnt++].tType = tType;
}

int doText(char *name) {
    int offset = unpackDWord();
    char psect[MAXNAMELEN];

    if (offset < 0 || !unpackName(psect)) {
        fprintf(stderr, "%s: unexpected EOF in TEXT record\n", name);
        return false;
    }
    if (stricmp(psect, "text") != 0 && stricmp(psect, "_text") != 0)
        return -1;

    int length = record.length - record.pos;
    if (codesize == 0)
        codebase = offset;
    if (offset + length - codebase >= sizeof(code)) {
        fprintf(stderr, "%s: out of bounds - offset = %04X length = %04X\n", name, offset, length);
        exit(1);
    }
    memcpy(code + offset - codebase, record.data + record.pos, length);
    memset(flags + offset - codebase, ABS, length);
    if (length != 0 && offset + length - codebase > codesize)
        codesize = offset + length - codebase;

    return offset;
}

void doReloc(char *name, int base) {
    while (record.pos < record.length) {
        int offset = unpackWord(); // assumption is that byte order is 0, 1
        int tType   = unpackByte();
        int cplx;
        char label[MAXNAMELEN] = "";
        if (tType != (RCPLX << 4) + 2) {
            if (!unpackName(label)) {
                fprintf(stderr, "%s: unexpected EOF in RELOC record\n", name);
                exit(1);
            }
        }
        int size = tType & 0xf;
        tType >>= 4;
        switch (tType) {
        case RABS:
            break;
        case RCPLX:
            while ((cplx = unpackByte())) {
                if (cplx == 3) {
                    unpackWord();
                    unpackWord();
                } else if (cplx == 16 || cplx == 32) {
                    char tmp[MAXNAMELEN];
                    if (!unpackName(tmp)) {
                        fprintf(stderr, "%s: unexpected EOF in RELOC Complex record\n", name);
                        exit(1);
                    }
                }
            }

        case RPSECT:
        case RRPSECT:
        case RSPSECT:
        case RNAME:
        case RRNAME:
        case RSNAME:
            memset(flags + base + offset - codebase, FIXUP, size);
            if (tType == RNAME && size == 2)
                addLabel(base + offset - codebase, label, EXTERNAL);
            break;
        default:
            fprintf(stderr, "%s: unsupported reloc - offset=%04X type=%d size=%d psect=%s\n", name, offset,
                    tType, size, label);
            break;
        }
    }
}

void doSym(char *name) {
    while (record.pos < record.length) {
        int value = unpackDWord();
        int flags = unpackWord();
        char psect[MAXNAMELEN];
        char symbol[MAXNAMELEN];
        if (!unpackName(psect) || !unpackName(symbol)) {
            fprintf(stderr, "%s: unexpected EOF in SYM record\n", name);
            exit(1);
        }
        if ((flags & 0x1f) == PUBLIC && (stricmp(psect, "text") == 0 || stricmp(psect, "_text") == 0))
            addLabel(value - codebase, symbol, PUBLIC);
    }
}

bool doModule(char *name, FILE *fpin, FILE *fpout) {
    int tType;
    int textBase = -1;

    memset(flags, UNDEF, codesize ? codesize : sizeof(flags));
    codesize = 0;
    clearLabels();

    while ((tType = getRecord(fpin)) != END && tType > 0) {
        switch (tType) {
        case TEXT:
            textBase = doText(name);
            break;
        case RELOC:
            if (textBase >= 0)
                doReloc(name, textBase);
            break;
        case SYM:
            doSym(name);
            break;
        case PSECT:
        case START:
        case IDENT:
        case XPSECT:
        case SEGMENT:
        case XSYM:
        case SIGNAT:
        case FNINFO:
        case FNCONF:
            break;
        default:
            fprintf(stderr, "%s: unsupported record type %d\n", name, tType);
            return false;
        }
    }
    if (tType == END) {
        dumpPattern(fpout);
        return true;
    }
    if (tType == TOO_LONG)
        fprintf(stderr, "%s: record length %d too long\n", name, record.length);
    else
        fprintf(stderr, "%s: unexpected EOF\n", name);
    return false;
}

void doLib(char *file, FILE *fpout) {
    FILE *symin;

    if (!(symin = fopen(file, "rb")))
        fprintf(stderr, "%s: cannot open library\n", file);
    else {
        int symsize   = getWord(symin);
        int modulecnt = getWord(symin);
        FILE *modin   = fopen(file, "rb");
        char modname[128];

        if (!modin || fseek(modin, symsize + 4, SEEK_SET) != 0) {
            fprintf(stderr, "%s: error locating modules\n", file);
            fclose(symin);
            return;
        }
        while (modulecnt-- != 0) {
            int modsymsize;

            if ((modsymsize = getWord(symin)) < 0 || fseek(symin, 10, SEEK_CUR) != 0 ||
                !getName(symin, modname) || fseek(symin, modsymsize, SEEK_CUR) != 0) {
                fprintf(stderr, "%s: error processing symbols\n", file);
                break;
            }
            if (!doModule(modname, modin, fpout)) {
                if (modulecnt != 0)
                    fprintf(stderr, "%s: skipping %d remaining module(s)\n", file, modulecnt);
                break;
            }
        }
        fclose(modin);
        fclose(symin);
    }
}

void doFile(char *file, FILE *fpout) {
    FILE *fpin = fopen(file, "rb");
    if (!fpin)
        fprintf(stderr, "%s: cannot open file\n", file);
    else
        doModule(file, fpin, fpout);
}

int main(int argc, char **argv) {
    FILE *fpout;

    CHK_SHOW_VERSION(argc, argv);

    if (argc < 3 || (fpout = fopen(argv[1], "wt")) == NULL) {
        fprintf(stderr, "usage: %s patfile objfile+\n", argv[0]);
        exit(1);
    }

    for (int i = 2; i < argc; i++) {
        char *s = strrchr(argv[i], '.');

        if (s && stricmp(s, ".lib") == 0)
            doLib(argv[i], fpout);
        else if (s && stricmp(s, ".obj") == 0)
            doFile(argv[i], fpout);
        else
            fprintf(stderr, "%s: skipped, must end in .lib or .obj\n", argv[i]);
    }

    fprintf(fpout, "---\n");
    fclose(fpout);

    return 0;
}
