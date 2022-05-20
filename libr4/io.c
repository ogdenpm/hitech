#include "libr.h"

int size_symbols;
int symSize;
int num_modules; /* Number of modules in library file */
int symCnt;
FILE *libraryFp;
char *libraryName;
FILE *libContentFp;
size_t newSymSize;
int newModuleCnt;
FILE *tempFp;
size_t tempFileSize;
long moduleSize;
time_t libTime;
time_t curTime;
bool symbolsRead;
bool moduleRead;
char *tmpFileName;
uint8_t moduleBuf[BLOCKSIZE];
uint8_t libBuf[BLOCKSIZE];

void openTemp() {
#ifdef CPM
    tmpFileName = "libtmp.$$$";
#else
    tmpFileName = tmpnam(NULL);
#endif

    if ((tempFp = fopen(tmpFileName, "wb")) == 0) {
        open_err(tmpFileName);
    }
}

size_t writeBlock(void *buf, size_t size, size_t count, FILE *fp) {
    size_t written;
    if ((written = (int)fwrite(buf, size, count, fp)) != count) {
        fatal_err("Write error on %s file", (fp == tempFp) ? "temp" : "output");
    }
    return written;
}

void closeTemp() {

    if (tempFp != 0) {
        fclose(tempFp);
        unlink(tmpFileName);
    }
}

void openLibrary(char *name) {
    register char *st;

    libraryName = name;
    libraryFp   = fopen(libraryName, "rb");

    if (libraryFp == 0) {
        if (cmdIndex != 0)
            open_err(libraryName);

        st = strrchr(libraryName, '.');

        if (st == 0 || (strcmp(st, ".lib") && strcmp(st, ".LIB")))
            warning("library file names should have .lib extension: %s", libraryName);

        size_symbols = 0;
        num_modules  = 0;
    } else {

        if (fread(libBuf, 4, 1, libraryFp) != 1)
            unexp_eof();

        size_symbols = get16le(libBuf);

        /*  Get the number of modules in a library file */
        num_modules = get16le(libBuf + 2);
    }
#ifndef CPM
    time(&curTime);
#endif
}

void openContent() {

    if (libraryFp == 0)
        return;
    if ((libContentFp = fopen(libraryName, "rb")) != 0) {
        if (fseek(libContentFp, ((long)size_symbols + 4), SEEK_SET) != -1)
            return;
    }
    open_err(libraryName);
}

void rewindLibrary() {

    if (err_num != 0)
        finish(5);
    if (libraryFp == 0)
        return;
    if (fseek(libraryFp, 4, SEEK_SET) != -1) {
        if (fseek(libContentFp, ((long)size_symbols + 4), SEEK_SET) != -1)
            return;
    }
    seek_err(libraryName);
}

/*
    close original library and replace with the new library created in
   tmpFileName, the symbol directory sizing information and number of
    modules is also added
*/
void commitNewLibrary() {
    size_t readLen;

    fclose(tempFp);
    if (libraryFp != NULL) {
        fclose(libraryFp);
        fclose(libContentFp);
    }
    if ((tempFp = fopen(tmpFileName, "rb")) == NULL)
        open_err(tmpFileName);
    if ((libraryFp = fopen(libraryName, "wb")) == NULL)
        open_err(libraryName);

    put16le((uint16_t)newSymSize, libBuf);
    put16le(newModuleCnt, libBuf + 2);

    writeBlock(libBuf, 1, 4, libraryFp);

    while ((readLen = fread(libBuf, 1, BLOCKSIZE, tempFp)) != 0)
        writeBlock(libBuf, 1, readLen, libraryFp);
    fclose(libraryFp);
}

/**************************************************************************
 visitor routines for modules & symbols
 **************************************************************************/
void visitModules(mfuncptr action) {
    int cntModulesLeft;

    for (cntModulesLeft = num_modules; cntModulesLeft; --cntModulesLeft) {
        if (fread(libBuf, 12, 1, libraryFp) != 1)
            unexp_eof();

        symSize    = get16le(libBuf);
        symCnt     = get16le(libBuf + 2);
        moduleSize = get32le(libBuf + 4);
        libTime    = get32le(libBuf + 8);

        readName(libBuf + 12);

        symbolsRead = moduleRead = false;

        action((char *)libBuf + 12, (time_t)libTime);

        if (!symbolsRead && fseek(libraryFp, symSize, SEEK_CUR) == -1)
            seek_err(libraryName);

        if (libContentFp && !moduleRead && fseek(libContentFp, moduleSize, SEEK_CUR) == -1)
            seek_err(libraryName);
    }
}

void visitSymbols(sfuncptr action) {
    int cnt;
    int type;

    for (cnt = symCnt; cnt; cnt--) {
        if ((type = fgetc(libraryFp)) == EOF)
            unexp_eof();
        readName(moduleBuf);
        action((char *)moduleBuf, type);
    }
    symbolsRead = true;
}

void copySymbolsToTemp() {
    size_t remaining, chunkSize;

    writeBlock(libBuf, 1, (remaining = strlen((char *)libBuf + 12) + 13), tempFp);
    tempFileSize += remaining;
    newSymSize += (remaining + symSize);
    remaining = symSize;
    while (remaining != 0) {
        chunkSize = (remaining < BLOCKSIZE) ? remaining : BLOCKSIZE;
        if (fread(moduleBuf, 1, chunkSize, libraryFp) != chunkSize)
            unexp_eof();
        writeBlock(moduleBuf, 1, chunkSize, tempFp);
        tempFileSize += chunkSize;
        remaining -= chunkSize;
    }
    ++newModuleCnt;
    symbolsRead = true;
}

void copyModuleToTemp() {
    uint32_t remaining;
    uint16_t chunkSize;

    remaining = moduleSize;
    while (remaining != 0) {
        chunkSize = (remaining < BLOCKSIZE) ? remaining : BLOCKSIZE;
        if (fread(moduleBuf, 1, chunkSize, libContentFp) != chunkSize)
            unexp_eof();
        writeBlock(moduleBuf, 1, chunkSize, tempFp);
        tempFileSize += chunkSize;
        remaining -= chunkSize;
    }
    moduleRead = true;
}

void extractOneModule(char *name) {
    int remaining, chunkSize;
    register FILE *fp;

    if ((fp = fopen(name, "wb")) == 0)
        open_err(name);
    remaining = moduleSize;
    while (remaining != 0) {
        chunkSize = (remaining < BLOCKSIZE) ? remaining : BLOCKSIZE;
        if (fread(moduleBuf, 1, chunkSize, libContentFp) != chunkSize)
            unexp_eof();
        writeBlock(moduleBuf, 1, chunkSize, fp);
        remaining -= chunkSize;
    }
    fclose(fp);
    moduleRead = true;
}

void copyNewModule(int id) {
    size_t remaining, written;
    size_t chunkSize;
    FILE *fp;

    if ((fp = fopen(cmdLineNames[id], "rb")) == 0)
        open_err(cmdLineNames[id]);
    written   = 0;
    remaining = moduleSizes[id];

    while ((chunkSize = fread(moduleBuf, 1, remaining > BLOCKSIZE ? BLOCKSIZE : remaining, fp)) !=
           0) {
        writeBlock(moduleBuf, 1, chunkSize, tempFp);
        written += chunkSize;
        tempFileSize += chunkSize;
        remaining -= chunkSize;
    }
    fclose(fp);
}

/* as the objFileName may include a path element, this routine
   removes the path component before writing.
   this also applies to CPM as a:file.obj may have been specified
   if !caseSentive also map name to lowercase
*/
void copyNewSymbols(int id) {
    uint32_t modsize;
    size_t simsize;
    uint16_t cnt;
    register struct sym *st;
    
    if (verbose)
        printf("%c %s\n", moduleFlags[id] ? 'r' : 'a', moduleStdNames[id]);
    moduleSizes[id] = (modsize = scanModule(cmdLineNames[id]));

    cnt             = (uint16_t)(curSymPtr - symbols);
    simsize         = cnt * 2; /* flag & trailing 0 */

    for (st = symbols; st != curSymPtr; ++st)
        simsize += strlen(st->name); /* add in the symbol lengths */
    /* 13 -> header size + trailing 0 of module name */
    newSymSize += strlen(moduleStdNames[id]) + simsize + 13;
    put16le((uint16_t)simsize, libBuf);
    put16le(cnt, libBuf + 2);
    put32le(modsize, libBuf + 4);
    put32le((uint32_t)curTime, libBuf + 8); /* time may be too big, but truncate */
    writeBlock(libBuf, 1, 12, tempFp);
    tempFileSize += 12;

    writeName(moduleStdNames[id]);

    for (st = symbols; st != curSymPtr; ++st) {
        fputc(st->flags, tempFp);
        ++tempFileSize;
        writeName(st->name);
    }
    ++newModuleCnt;
}

/**************************************************************************
 routines to read / write 16/32 numbers in little edian format
 **************************************************************************/
void put32le(uint32_t val, uint8_t *buf) {

    buf[0] = (uint8_t)val;
    buf[1] = (uint8_t)(val >> 8);
    buf[2] = (uint8_t)(val >> 0x10);
    buf[3] = (uint8_t)(val >> 0x18);
}

void put16le(uint16_t val, uint8_t *buf) {

    buf[0] = (uint8_t)val;
    buf[1] = (uint8_t)(val >> 8);
}

uint16_t get16le(uint8_t *buf) {

    return buf[0] + (buf[1] << 8);
}

uint32_t get32le(uint8_t *buf) {
#if UINT_MAX < 65536
    return (uint32_t)get16le(buf) + (((uint32_t)get16le(buf + 2)) << 16);
#else
    return buf[0] + (buf[1] << 8) + (buf[2] << 16) + (buf[3] << 24);
#endif
}

void readName(uint8_t *p1) {
    int ch;

    do {
        if ((ch = fgetc(libraryFp)) == EOF)
            unexp_eof();
        *p1++ = ch;
    } while (ch != 0);
}

void writeName(char *p1) {
    do {
        ++tempFileSize;
    } while (fputc(*p1++, tempFp) != 0);
}

void unexp_eof() {

    badFormat(libraryName, "unexpected end of file");
}
