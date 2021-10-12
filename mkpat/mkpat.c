#include "mkpat.h"

#define NODATAREF

/* record types */
enum { TEXT = 1, PSECT, RELOC, SYM, START, END, IDENT, TOO_LONG = -1, PAST_END = -2 };

#define CHUNK 50 // allocation chunk for symbols

typedef unsigned char byte;
typedef unsigned short word;

typedef struct {
    int length;
    int type;
    uint8_t data[512];
} record_t;

record_t record;

typedef struct {
    char *filename;
    long size;
    long startRec;
    long pos;
    long nextRec;
    byte image[1];
} omfFile;

typedef struct {
    unsigned offset : 16;
    unsigned segId : 8;
    unsigned isLocal : 1;
    unsigned instance : 5;
    byte *name;
} symbol_t;

typedef struct {
    unsigned data : 8;
    unsigned dataType : 3;
    unsigned isExternal : 1;
    unsigned indexOrSegId : 16;
} codeByte_t;

#define ALNBOTH 3

enum { // dataType values
    UNDEF = 0,
    ABS,
    REFBYTE,
    REFLOWORD,
    REFHIWORD
};

typedef struct {
    omfFile *fi;
    byte *name;
    int codeSize;
    codeByte_t *codeImage;
    int nSymbols;
    symbol_t *symbols;
    int nExternals;
    symbol_t *externals;
} module_t;


int getWord(FILE *fp) {
    int c1 = getc(fp);
    int c2 = getc(fp);
    if (c2 == EOF)
        return EOF;
    return c1 + c2 * 256;
}

bool getName(FILE *fp, char *name) {
    int c;
    do {
        *name++ = c = getc(fp);
    } while (c > 0);
    return c == 0;
}

int getRecord(FILE *fp) {
    record.length = getword(fp);
    record.type = getc(fp);
    if (record.type == EOF)
        return PAST_END;
    if (record.length > 512)
        return TOO_LONG;
    if (fread(record.data, 1, record.length, fp) != record.length)
        return PAST_END;
    return record.type;
}

#if 0

void printPstr(FILE *fp, byte *name, int deconflict) {
    /* avoid conflict with register names*/
    if (deconflict && name[0] == 1 && strchr("ABCDEFHILM", name[1]))
        fprintf(fp, "_");
    fprintf(fp, "%.*s", name[0], name + 1);
}

int cmpSymbol(const symbol_t *a, const symbol_t *b) {
    int aval, bval;
    aval = a->offset + (a->segId << 16) + (a->isLocal << 24);
    bval = b->offset + (b->segId << 16) + (b->isLocal << 24);

    return aval - bval;
}

markMultipleLocals(module_t *mod) {
    int i, j;
    int len;
    int count;

    /* runs through locals tagging multiple names with sequential numbers */
    for (i = 1; i < mod->nSymbols; i++) {
        if (mod->symbols[i].isLocal == 0)
            continue; // its a public
        len = mod->symbols[i].name[0];
        for (count = j = 0; j < i; j++)
            if (mod->symbols[j].name[0] == len && strncmp(mod->symbols[j].name + 1, mod->symbols[i].name + 1, len) == 0)
                if (mod->symbols[j].offset == mod->symbols[i].offset &&
                    mod->symbols[j].segId == mod->symbols[i].segId) { // matches earlier entry
                    mod->symbols[i].name = ""; // will be seen earlier in list so remove from further checks
                } else {
                    count++;
                }
        mod->symbols[i].instance = count;
    }
}

void dumpPattern(FILE *fpout, module_t *mod) {
    int i, j, k;
    int offset;
    int splitRef = 0;
    unsigned char code[256];
    int loc;

    for (loc = 0; loc < mod->codeSize && loc < 32; loc++) {
        if (mod->codeImage[loc].dataType == ABS)
            fprintf(fpout, "%02X", mod->codeImage[loc].data);
        else
            fprintf(fpout, "..");
    }
    while (loc < 32) {
        fprintf(fpout, "..");
        loc++;
    }
    for (j = 0; j < 255 && loc < mod->codeSize && mod->codeImage[loc].dataType == ABS; j++, loc++)
        code[j] = mod->codeImage[loc].data;

    fprintf(fpout, " %02X %04X %04X", j, crc16(code, j), mod->codeSize);

    qsort(mod->symbols, (size_t)mod->nSymbols, sizeof(symbol_t), &cmpSymbol);

    markMultipleLocals(mod);

    for (i = 0; i < mod->nSymbols && mod->symbols[i].segId == 1; i++) // code seg
        if (mod->symbols[i].isLocal == 0) {                           // public
            fprintf(fpout, " :%04X ", mod->symbols[i].offset);
            printPstr(fpout, mod->symbols[i].name, 1);
        }

    for (i = 0; i < mod->codeSize; i++) { // process references
        if (mod->codeImage[i].dataType == REFLOWORD && i + 1 < mod->codeSize) {
            offset = mod->codeImage[i].data + 256 * mod->codeImage[i + 1].data;
            if (mod->codeImage[i].isExternal) {
                fprintf(fpout, " ^%04X ", i);
                printPstr(fpout, mod->externals[mod->codeImage[i].indexOrSegId].name, offset != 0);
                if (offset != 0)
                    fprintf(fpout, "_%d", offset);
            } else
#ifdef NODATAREF
                if (mod->codeImage[i].indexOrSegId == 1) // compile option is only to include CODE refs & externals
#endif
            {
                for (k = 0; k < mod->nSymbols; k++) {
                    if (mod->symbols[k].offset == offset && mod->symbols[k].segId == mod->codeImage[i].indexOrSegId) {
                        fprintf(fpout, " ^%04X ", i);
                        printPstr(fpout, mod->symbols[k].name, 0);
                        if (mod->symbols[k].isLocal) { // it is a local so add make sure its unique
                            if (mod->symbols[k].instance)
                                fprintf(fpout, "_%d", mod->symbols[k].instance);
                            if (mod->symbols[k].segId == 1) // ida handles locals in code
                                fprintf(fpout, "@");
                            else { // use module name to distinguish
                                fprintf(fpout, "_");
                                printPstr(fpout, mod->name, 0);
                            }
                        }
                        break;
                    }
                }
            }
            i++;
        }
    }

    if (loc < mod->codeSize)
        fprintf(fpout, " ");

    for (; loc < mod->codeSize; loc++) {
        if (mod->codeImage[loc].dataType == ABS)
            fprintf(fpout, "%02X", mod->codeImage[loc].data);
        else
            fprintf(fpout, "..");
    }
    fprintf(fpout, "\n");
}

void addSymbol(module_t *mod, int segId, int offset, byte *name, int isLocal) {
    symbol_t *sym;

    if (mod->nSymbols == 0)
        mod->symbols = (symbol_t *)malloc(sizeof(symbol_t) * CHUNK);
    else if (mod->nSymbols % CHUNK == 0)
        mod->symbols = (symbol_t *)realloc(mod->symbols, sizeof(symbol_t) * (mod->nSymbols + CHUNK));
    if (mod->symbols == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    sym          = &mod->symbols[mod->nSymbols];
    sym->name    = name;
    sym->segId   = segId;
    sym->offset  = offset;
    sym->isLocal = isLocal;
    mod->nSymbols++;
}

void addExternal(module_t *mod, byte *name) {
    symbol_t *sym;

    if (mod->nExternals == 0)
        mod->externals = (symbol_t *)malloc(sizeof(symbol_t) * CHUNK);
    else if (mod->nExternals % CHUNK == 0)
        mod->externals = (symbol_t *)realloc(mod->externals, sizeof(symbol_t) * (mod->nExternals + CHUNK));
    if (mod->externals == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    sym       = &mod->externals[mod->nExternals];
    sym->name = name;
    mod->nExternals++;
}

void addFixup(module_t *mod, int offset, int isExternal, int indexOrSegId, int refType) {
    codeByte_t *codeByte;

    codeByte = &mod->codeImage[offset];
    if (offset >= mod->codeSize)
        fprintf(stderr, "reloc @%04X beyond end of code!!\n", offset);
    else if (codeByte->dataType < REFBYTE) { // so far no reference
        codeByte->isExternal   = isExternal;
        codeByte->dataType     = refType;
        codeByte->indexOrSegId = indexOrSegId;
    } else
        fprintf(stderr, "multiple fixups at @%04X\n", offset);
}
#endif
bool doModule(char *name, FILE *fpin, FILE *fpout) {
    int type;
    while ((type = getRecord(fpin)) != END && type > 0) {
        switch (type) {
        case TEXT:
        case PSECT:
        case RELOC:
        case SYM:
        case START:
        case IDENT:
            break;
        default:
            fprintf(stderr, "%s: unsupported record type %d\n", name, type);
            return false;
        }
    }
    if (type == END)
        return true;
    if (type == TOO_LONG)
        fprintf(stderr, "%s: record length %d too long\n", name, record.length);
    else
        fprintf(stderr, "%s: unexpected EOF\n", name);
    return false;
}

void doLib(char *file, FILE *fpout) {
    FILE *symin, *modin;
    char modname[128];

    if (!(symin = fopen(file, "rb")))
        fprintf(stderr, "%s: cannot open library\n", file);
    else {
        int symsize   = getWord(symin);
        int modulecnt = getWord(symin);
        FILE *modin   = fopen(file, "rb");

        if (!modin || fseek(modin, symsize + 4, SEEK_SET) != 0) {
            fprintf(stderr, "%s: error locating modules\n", file);
            fclose(symin);
            return;
        }
        while (modulecnt-- != 0) {
            if (fseek(symin, 12, SEEK_CUR) != 0 || !getName(symin, modname) || fseek(symin, symsize, SEEK_CUR) != 0) {
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
        fprintf(stderr, "%s: cannot open file\n");
    else
        doModule(file, fpin, fpout);
}

int main(int argc, char **argv) {
    FILE *fpout;

    if (argc == 2 && strcasecmp(argv[1], "-v") == 0) {
        showVersion(stdout, argv[1][1] == 'V');
        exit(0);
    }

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
