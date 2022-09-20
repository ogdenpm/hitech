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

static void writeText();                 /* 0365  6 */
static void i16tole(int16_t, uint8_t *); /* 05bf 10 */

/****************************************************************
 *	Initialized variables
 ****************************************************************/

uint8_t *nonTextRecPtr   = nonTextRecBuf + 3; /* 6acd */

static uint8_t order32[] = { /* 6acf */
                             0, 1, 2, 3
};

static uint8_t order16[] = { /* 6ad3 */
                             0, 1
};

void (*libHandlers[])() = { /* 6be7 */
                            libPass1, libPass2
};

#ifdef CPM
FILE *moduleFp = stdin; /*6c28 */
#else
FILE *moduleFp = NULL; /* for GCC and VC stdin is actually a function call so can't be used here */
#endif

int width                  = 80; /* 6c2a */

static char *recordTypes[] = {
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

/*
 *	Uninitialized variables and arrays
 */
static bool haveIdent;         /* 7616   */
uint8_t *textRecPtr;           /* 7617   */
uint8_t nonTextRecBuf[512];    /* 7619   */
static uint32_t targetAddress; /* 7819   */
int textLen;                   /* 781d   */
uint8_t textRecBuf[512];       /* 781f   */
uint8_t recTyp;                /* 7a1f   */
uint8_t *endAddr;              /* 7a20   */
uint8_t recbuf[512];           /* 7a22   */
int alreadyWritten;            /* 7c22   */
uint8_t *curAddr;              /* 7c24   */

/*int asdf = 0xfff6;  */

/**************************************************************************
 1	writeErr	sub-013dh	ok++ (nau)(PMO)
 **************************************************************************/
static void writeErr() {

    fatalErr("%s: Write error (out of disk space?)", outFileName);
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

    if (optM != 0)
        printf("Machine type is %s\n\n", recbuf + IDENT_MACHINE);

    if (optC == 0)
        writeRec(IDENT_RECORD, recLen, recbuf); /* copy the Ident record */
}

/**************************************************************************
 3	readRecHdr	sub_0227h	ok++ (nau)(PMO)
 **************************************************************************/
void readRecHdr() {

    if (fread(recbuf, RECORD_HDR, 1, moduleFp) != 1)
        badFormat("no end record found");

    ++numRecord;

    recLen = (recbuf[1] << 8) + recbuf[0];

    recTyp = recbuf[RECORD_TYPE];

    if (recTyp <= 0 || recTyp >= SEGMENT_RECORD)
        badFormat("unknown record type: %d", recTyp);

    if (recLen > (512 - RECORD_HDR))
        badFormat("record too long: %d+%d", 3, recLen);
}

/**************************************************************************
 4	readRecData	ok++ (nau)(PMO)
 **************************************************************************/
void readRecData(uint8_t *buf) {

    if (fread(buf, 1, recLen, moduleFp) != recLen)
        badFormat("incomplete %s record body: length = %d", recordTypes[*(recbuf + RECORD_TYPE)],
                  recLen);
}

/**************************************************************************
 5	writeRec	ok++ (nau)(PMO)
 *  optimiser improves on calculation of address of tmp
 **************************************************************************/
void writeRec(int type, uint16_t len, uint8_t *buf) {
    uint8_t tmp[RECORD_HDR];

    tmp[RECORD_TYPE] = type;
    i16tole(len, tmp);
    if (fwrite(tmp, RECORD_HDR, 1, outFp) == 1 && fwrite(buf, 1, len, outFp) == len)
        return;
    writeErr();
}

/**************************************************************************
 6	writeText	ok++ (nau)(PMO)
 optimiser improves on calculation of address of tmp, but misses ex (sp),hl
 optimisation using pop bc, push hl instead
 **************************************************************************/
static void writeText() {
    uint8_t tmp[RECORD_HDR];
    int textHdrLen;
    int writeLen;

    if (curAddr < textRecPtr || endAddr <= curAddr)
        return;

    textHdrLen = TEXT_PNAME + (int)strlen((char *)textRecBuf + TEXT_PNAME) + 1;
    writeLen   = (int)(endAddr - curAddr);

    i16tole(textHdrLen + writeLen, tmp); /* fillout the record header  */
    tmp[RECORD_TYPE] = TEXT_RECORD;

    if (optC) {
        targetAddress = btou32(textRecBuf); /* pick up the text record offset */

        if (targetAddress < offsetAddress)
            fatalErr("module has code below file base of 0%" PRIx32 "h", offsetAddress);

        if (fseek(outFp, targetAddress - offsetAddress, SEEK_SET) == -1)
            fatalErr("%s: Seek error", outFileName);

        if (fwrite(curAddr, 1, writeLen, outFp) != writeLen)
            writeErr();
    } else {
        /* copy the text record */
        if (fwrite(tmp, RECORD_HDR, 1, outFp) != 1 ||
            fwrite(textRecBuf, 1, textHdrLen, outFp) != textHdrLen ||
            fwrite(curAddr, 1, writeLen, outFp) != writeLen)
            writeErr();
    }

    u32tob(btou32(textRecBuf) + writeLen, textRecBuf); /* update the offset */
    curAddr = endAddr;                                 /* advance to end */
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
    i16tole(len - RECORD_HDR, nonTextRecBuf); /* length of data item */

    if (fwrite(nonTextRecBuf, 1, len, outFp) != len)
        writeErr();

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
 10	i16tole	sub-05bfh	ok++ (nau)
 **************************************************************************/
static void i16tole(int16_t n, uint8_t *p) {

    p[0] = (uint8_t)n;
    p[1] = n >> 8;
}

/**************************************************************************
 11	letoi16	sub-05e1h	ok++ (PMO)
 * Convert leading low string to int
 * Optimiser eliminates the odd code of the original which did spurious
 * unrequired operations
 **************************************************************************/
int16_t btoi16(register uint8_t *p1) {

    return (p1[order16[1]] << 8) + p1[order16[0]];
}

/**************************************************************************
 12	conv_u16tob	sub-0616h	ok++ (PMO)
 * Convert int to leading low string
 **************************************************************************/
void u16tob(uint16_t n, register uint8_t *buf) {

    buf[order16[0]] = (uint8_t)n;
    buf[order16[1]] = n >> 8;
}

/**************************************************************************
 13	conv_btou32	sub_0647h	ok ++ (PMO)
 *	Calculate uint32_t value
 * the hitech compiler generates invalid code for shift operation using
 * the obvious casting.
 * The double layer cast does however generate correct code and is marginally
 * optimised over the original
 **************************************************************************/
uint32_t btou32(register uint8_t *buf) {
    uint32_t n;
    char i;

    i = 4;
    n = 0;
    while (i-- > 0)
        n += ((uint32_t)(uint16_t)buf[order32[(int)i]]) << (i * 8);
    return n;
}

/**************************************************************************
 14	conv_u32tob	ok++
 **************************************************************************/
void u32tob(uint32_t n, register uint8_t *buf) {
    uint8_t i;

    for (i = 0; i < 4; ++i) {
        buf[order32[i]] = (uint8_t)n;
        n >>= 8;
    }
}

/**************************************************************************
 15	conv_btou24	ok ++ (PMO)
 same issue as conv_btou32
 **************************************************************************/
uint32_t btou24(register uint8_t *buf) {
    uint32_t n;
    char i;

    i = 3;
    n = 0;
    while (i-- > 0)
        n += ((uint32_t)(uint16_t)buf[order32[(int)i]] << (i * 8));
    return n;
}

/**************************************************************************
 16	conv_u24tob	ok++ (nau) (PMO)
 **************************************************************************/
void u24tob(uint32_t n, register uint8_t *buf) {
    uint8_t i;

    for (i = 0; i < 3; ++i) {
        buf[order32[i]] = (uint8_t)n;
        n >>= 8;
    }
}
