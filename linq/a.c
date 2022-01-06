/*
 * File created 14.11.2021, last modified 01.01.2022
 *
 * The a.c file is part of the restored LINK.COM program
 * from the Hi-Tech C compiler v3.09 package.
 *
 *	Andrey Nikitin	01.01.2022
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if CPM
#include <sys.h>
#endif

#include "link.h"

/****************************************************************
 *	Initialized variables
 ****************************************************************/

uint8_t *nonTextRecPtr = nonTextRecBuf + 3; /* 6acd */

uint8_t order32[]      = { /* 6acf */
                      0, 1, 2, 3
};

uint8_t order16[] = { /* 6ad3 */
                      0, 1
};

void (*libHandlers[])() = { /* 6be7 */
                            libPass1, libPass2
};

char usageMsg[] = /* 6c66 */
    "Usage: link [-cbase][-dsymfile][-r][-n][-s][-x][-z][-oofile][-pspec][-mmap]{-usym}[-wwidth] "
    "input ...";

#ifdef CPM
FILE *moduleFp = stdin; /*6c28 */
#else
FILE *moduleFp = NULL; /* for GCC and VC stdin is actually a function call so can't be used here */
#endif


int width         = 80;

char *rec_types[] = {
    /* 6c2c */
    "",      /* 0 */
    "TEXT",  /* 1 */
    "PSECT", /* 2 */
    "RELOC", /* 3 */
    "SYM",   /* 4 */
    "START", /* 5 */
    "END",   /* 6 */
    "IDENT", /* 7 */
    "XPSECT" /* 8 */
};

/* record handler {pass1, pass2} */
void (*recHandler[][2])() = {
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


void (*finPassHandler[2])() = { finPass1, finPass2 };

psect_t *nextPsect         = psectInfo; /* 6f69 */

/*
 *	Uninitialized variables and arrays
 */
bool haveIdent;             /* 7616   */
uint8_t *textRecPtr;        /* 7617   */
uint8_t nonTextRecBuf[512]; /* 7619   */
uint32_t targetAddress;     /* 7819   */
int textLen;                /* 781d   */
uint8_t textRecBuf[512];    /* 781f   */
uint8_t rectyp;             /* 7a1f   */
uint8_t *endAddr;           /* 7a20   */
uint8_t recbuf[512];        /* 7a22   */
int alreadyWritten;         /* 7c22   */
uint8_t *curAddr;           /* 7c24   */
uint32_t moduleSize;        /* 7c26 * */
int symSize;                /* 7c2a * */
int num_modules;            /* 7c2c * */
bool moduleLoaded;          /* 7c2e * */
int size_symbols;           /* 7c2f * */
bool moduleNeeded;          /* 7c31 * */
int num_files;              /* 7c32 * */
FILE *libraryFp;            /* 7c34 * */
int symCnt;                 /* 7c36 * */
uint8_t libBuf[100];        /* 7c38 * */
vec_t **libTable;        /* 7c9c * */
bool haveEntryPt;           /* 7c9e   */
char *libraryName;          /* 7c9f * */
bool key_LM;                /* 7ca1 * */
bool key_C;                 /* 7ca2 * */
FILE *symFp;                /* 7ca3   */
uint8_t linker_pass;        /* 7ca5 * */
char *fname_sym;            /* 7ca6   */
int cntUnresolved;          /* 7ca8   */
char *fname_obj;            /* 7caa * */
bool key_R;                 /* 7cac * */
char *fname_map;            /* 7cad   */
bool key_S;                 /* 7caf * */
uint16_t curFileId;         /* 7cb0   */
bool key_H;                 /* 7cb2   */
uint16_t length;            /* 7cb3   */
char *fname_outp;           /* 7cb5   */
bool key_I;                 /* 7cb7 * */
char *psect_location;       /* 7cb8   */
bool key_X;                 /* 7cbb * */
FILE *outFp;               /* 7cbc   */
bool key_L;                 /* 7cbe * */
int num_lib_files;          /* 7cbf * */
bool key_M;                 /* 7cc1 * */
bool key_Z;                 /* 7cc2   */
int err_num;                /* 7cc3   */
uint32_t offset_address;    /* 7cc5   */
int numRecord;              /* 7cc9   */
bool key_N;                 /* 7ccb * */
char *fixupName;            /* 7ccc   */
uint32_t linkAddress;       /* 7cce   */
sym_t *absSym;              /* 7cd2   */
psect_t psectInfo[20];      /* 7cd4   */
uint32_t saveLoadAddress;   /* 7ef0   */
uint32_t maxLinkAddress;    /* 7ef4   */
int newSymCnt;              /* 7ef8   */
uint32_t loadAddress;       /* 7efa   */
sym_t **symbol_table;       /* 7efe   */
uint32_t textBaseAddress;   /* 7f00   */

/*int asdf = 0xfff6;  */

/**************************************************************************
 1	err_write	sub-013dh	ok++ (nau)(PMO)
 **************************************************************************/
void err_write() {

    fatal_err("%s: Write error (out of disk space?)", fname_outp);
}

/**************************************************************************
 2	identRecPass1	sub-014b	ok++ (nau)(PMO)
 **************************************************************************/
void identRecPass1() {
    uint8_t i;

    readRecData(recbuf);

    if (haveIdent) {
        for (i = 0; i < 4; i++)
            if (recbuf[IDENT_ORDER32 + i] != order32[i])
                badFormat("ident records do not match");
        for (i = 0; i < 2; i++)
            if (recbuf[IDENT_ORDER16 + i] != order16[i])
                badFormat("ident records do not match");
        return;
    }
    for (i = 0; i < 4; i++)
        order32[i] = recbuf[IDENT_ORDER32 + i];

    for (i = 0; i < 2; i++)
        order16[i] = recbuf[IDENT_ORDER16 + i];

    haveIdent = true;

    if (key_M != 0)
        printf("Machine type is %s\n\n", recbuf + IDENT_MACHINE);

    if (key_C == 0)
        writeRec(IDENT_RECORD, length, recbuf); /* copy the Ident record */
}

/**************************************************************************
 3	readRecHdr	sub_0227h	ok++ (nau)(PMO)
 **************************************************************************/
void readRecHdr() {

    if (fread(recbuf, RECORD_HDR, 1, moduleFp) != 1)
        badFormat("no end record found");

    ++numRecord;

    length = (recbuf[1] << 8) + recbuf[0];

    rectyp = recbuf[RECORD_TYPE];

    if (rectyp <= 0 || rectyp >= SEGMENT_RECORD)
        badFormat("unknown record type: %d", rectyp);

    if (length > (512 - RECORD_HDR))
        badFormat("record too uint32_t: %d+%d", 3, length);
}

/**************************************************************************
 4	readRecData	ok++ (nau)(PMO)
 **************************************************************************/
void readRecData(uint8_t *buf) {

    if (fread(buf, 1, length, moduleFp) != length)
        badFormat("incomplete %s record body: length = %d", rec_types[*(recbuf + RECORD_TYPE)], length);
}

/**************************************************************************
 5	writeRec	ok++ (nau)(PMO)
 *  optimiser improves on calculation of address of tmp
 **************************************************************************/
void writeRec(int recType, uint16_t length, uint8_t *recbuf) {
    uint8_t tmp[RECORD_HDR];

    tmp[RECORD_TYPE] = recType;
    conv_i16tole(length, tmp);
    if (fwrite(tmp, RECORD_HDR, 1, outFp) == 1 && fwrite(recbuf, 1, length, outFp) == length)
        return;
    err_write();
}

/**************************************************************************
 6	writeText	ok++ (nau)(PMO)
 optimiser improves on calculation of address of tmp, but misses ex (sp),hl
 optimisation using pop bc, push hl instead
 **************************************************************************/
void writeText() {
    uint8_t tmp[RECORD_HDR];
    int textHdrLen;
    int writeLen;

    if (curAddr < textRecPtr || endAddr <= curAddr)
        return;

    textHdrLen = TEXT_PNAME + (int)strlen((char *)textRecBuf + TEXT_PNAME) + 1;
    writeLen   = (int)(endAddr - curAddr);

    conv_i16tole(textHdrLen + writeLen, tmp); /* fillout the record header  */
    tmp[RECORD_TYPE] = TEXT_RECORD;

    if (key_C) {
        targetAddress = conv_btou32(textRecBuf); /* pick up the text record offset */

        if (targetAddress < offset_address)
            fatal_err("module has code below file base of 0%lxh", offset_address);

        if (fseek(outFp, targetAddress - offset_address, SEEK_SET) == -1)
            fatal_err("%s: Seek error", fname_outp);

        if (fwrite(curAddr, 1, writeLen, outFp) != writeLen)
            err_write();
    } else {
        /* copy the text record */
        if (fwrite(tmp, RECORD_HDR, 1, outFp) != 1 ||
            fwrite(textRecBuf, 1, textHdrLen, outFp) != textHdrLen ||
            fwrite(curAddr, 1, writeLen, outFp) != writeLen)
            err_write();
    }

    conv_u32tob(conv_btou32(textRecBuf) + writeLen, textRecBuf); /* update the offset */
    curAddr = endAddr;                                           /* advance to end */
    alreadyWritten += writeLen;
}

/**************************************************************************
 7	flushText	ok++ (nau)
 **************************************************************************/
void flushText() {

    endAddr = textLen + textRecPtr;
    writeText();
}

/**************************************************************************
 8	wrRecord	ok++ (nau)
 **************************************************************************/
void wrRecord() {
    int len;

    len = (int)(nonTextRecPtr - nonTextRecBuf);

    if (nonTextRecBuf[RECORD_TYPE] == 0 || len == RECORD_HDR)
        return;
    if (nonTextRecBuf[2] == RELOC_RECORD)
        writeText(); /* make sure text that was relocated is written first */
    conv_i16tole(len - RECORD_HDR, nonTextRecBuf); /* length of data item */

    if (fwrite(nonTextRecBuf, 1, len, outFp) != len)
        err_write();

    nonTextRecBuf[RECORD_TYPE] = 0;
    nonTextRecPtr              = nonTextRecBuf + RECORD_HDR;
}

/**************************************************************************
 9	chkAddRecordItem	ok++ (nau)
 **************************************************************************/
void chkAddRecordItem(uint8_t type, size_t len) {
    /* can add if same record type and it fits else flush */
    if (nonTextRecBuf[RECORD_TYPE] == type && nonTextRecBuf + 512 >= nonTextRecPtr + len)
        return;
    wrRecord();
    nonTextRecBuf[RECORD_TYPE] = type;
}

/**************************************************************************
 10	conv_i16tole	sub-05bfh	ok++ (nau)
 **************************************************************************/
void conv_i16tole(int16_t p1, uint8_t *p2) {

    p2[0] = (uint8_t)p1;
    p2[1] = p1 >> 8;
}

/**************************************************************************
 11	conv_letoi16	sub-05e1h	ok++ (PMO)
 * Convert leading low string to int
 * Optimiser eliminates the odd code of the original which did spurious
 * unrequired operations
 **************************************************************************/
int16_t conv_letoi16(register uint8_t *p1) {

    return (p1[order16[1]] << 8) + p1[order16[0]];
}

/**************************************************************************
 12	conv_u16tob	sub-0616h	ok++ (PMO)
 * Convert int to leading low string
 **************************************************************************/
void conv_u16tob(uint16_t p1, register uint8_t *p2) {

    p2[order16[0]] = (uint8_t)p1;
    p2[order16[1]] = p1 >> 8;
}

/**************************************************************************
 13	conv_btou32	sub_0647h	ok ++ (PMO)
 *	Calculate uint32_t value
 * the hitech compiler generates invalid code for shift operation using
 * the obvious casting.
 * The double layer cast does however generate correct code and is marginally
 * optimised over the original
 **************************************************************************/
uint32_t conv_btou32(register uint8_t *p1) {
    uint32_t l1;
    char l2;

    l2 = 4;
    l1 = 0;
    while (l2-- > 0)
        l1 += ((uint32_t)(uint16_t)p1[order32[l2]]) << (l2 * 8);
    return l1;
}

/**************************************************************************
 14	conv_u32tob	ok++
 **************************************************************************/
void conv_u32tob(uint32_t p1, register uint8_t *st) {
    uint8_t l1;

    for (l1 = 0; l1 < 4; ++l1) {
        st[order32[l1]] = (uint8_t)p1;
        p1 >>= 8;
    }
}

/**************************************************************************
 15	conv_btou24	ok ++ (PMO)
 same issue as conv_btou32
 **************************************************************************/
uint32_t conv_btou24(register uint8_t *p1) {
    uint32_t l1;
    char l2;

    l2 = 3;
    l1 = 0;
    while (l2-- > 0)
        l1 += ((uint32_t)(uint16_t)p1[order32[l2]] << (l2 * 8));
    return l1;
}

/**************************************************************************
 16	conv_u24tob	ok++ (nau) (PMO)
 **************************************************************************/
void conv_u24tob(uint32_t p1, register uint8_t *st) {
    uint8_t l1;

    for (l1 = 0; l1 < 3; ++l1) {
        st[order32[l1]] = (uint8_t)p1;
        p1 >>= 8;
    }
}
