#include "libr.h"

uint8_t order32[]  = { 0, 1, 2, 3 };
uint8_t order16[] = { 0, 1 };

FILE *moduleFp;
char *moduleName;

struct sym *curSymPtr;

int dataLen;
uint32_t reclen;
struct sym symbols[500];
bool haveIdent;
bool hasNonExtern;
uint8_t rectyp;
uint8_t recbuf[512];




void skipRecord() {

    if (fseek(moduleFp, dataLen, SEEK_CUR) == -1)
        badFormat(moduleName, "incomplete record");
}

/**************************************************************************
 get 16 bit value stored in address order
 **************************************************************************/

uint16_t get16ao(uint8_t *p1) {

    return (p1[order16[1]] << 8) + p1[order16[0]];
}

void addSymbol(char *name, uint8_t flags) {
    register struct sym *ps;

    if (curSymPtr == &symbols[500])
        fatal_err("Too many symbols in %s", moduleName);
    ps = curSymPtr;
    if ((ps->flags = flags) != 6)
        hasNonExtern = true;
    strcpy((curSymPtr->name = xalloc(strlen(name) + 1)), name);

    ++curSymPtr;
}

void parseSymbolRec() {
    uint8_t *name;
    uint16_t flags;
    uint8_t loFlags;
    uint8_t *p;

    if (fread(recbuf, 1, dataLen, moduleFp) != dataLen)
        badFormat(moduleName, "incomplete symbol record");

    p = recbuf;

    while (p < recbuf + dataLen) {
        flags   = get16ao(p + 4); /* read loFlags */
        loFlags = flags & 0xF;    /* mask off low 4 bits */
        name    = p + 6;          /* skip to psect name */

        while (*name++) /* skip psect name */
            ;
        /* only process PUBLIC, COMM and EXTERN entries */
        if ((flags & 0x10) && (loFlags == 0 || loFlags == 2 || loFlags == 6))
            addSymbol((char *)name, loFlags);
        p = name;

        while (*(p++) != 0) /* skip symbol name */
            ;
    }
}


void parseIdentRec() {

    if (fread(recbuf, 1, dataLen, moduleFp) != dataLen)
        badFormat(moduleName, "incomplete ident record");

    if (haveIdent) {
        if (memcmp(recbuf, order32, 4) != 0 || memcmp(recbuf + 4, order16, 2) != 0)
            badFormat(moduleName, "ident records do not match");
    } else {
        memcpy(order32, recbuf, 4);
        memcpy(order16, recbuf + 4, 2);
        haveIdent = true;
    }
}


void getRecord() {

    if (fread(recbuf, 3, 1, moduleFp) != 1)
        badFormat(moduleName, "no end record found");

    rectyp = recbuf[2];

    if (rectyp == 0 || rectyp >= 20)
        badFormat(moduleName, "unknown record type: %d", rectyp);
    if (512 - 3 < (dataLen = get16le(recbuf)))
        badFormat(moduleName, "record too long: %d+%d", 3, dataLen);

    reclen += dataLen + 3;
}

int scanModule(char *name) {

    moduleFp = fopen((moduleName = name), "rb");
    if (moduleFp == NULL)
        open_err(moduleName);
    hasNonExtern = 0;
    reclen       = 0;
    curSymPtr    = symbols;

    for (;;) {
        getRecord(); /* Get type of record */

        switch (rectyp) {
        case IDENT_RECORD:
            parseIdentRec();
            break;
        case SYM_RECORD:
            parseSymbolRec();
            break;
        default:
            skipRecord();
            break;
        case END_RECORD:
            fclose(moduleFp);
#ifdef CPM
            if (reclen >= 0x10000)
                fatal_err("file too big ");
#endif
            if (hasNonExtern == 0)
                warning("module %s defines no symbols ", moduleName);
            return reclen;
        }
    }
}


void copyMatchedSymbols(char *moduleName, time_t libTime) {
    int moduleId;

    if ((moduleId = lookupName(moduleName)))
        copyNewSymbols(moduleId - 1);
    else
        copySymbolsToTemp();
}

void copyMatchedModules(char *moduleName, time_t libTime) {
    int moduleId;
    if ((moduleId = lookupName(moduleName)))
        copyNewModule(moduleId - 1);
    else
        copyModuleToTemp();
}







