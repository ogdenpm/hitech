/*
 *
 * The code.c file is part of the restored ZAS.EXE program
 * from the Hi-Tech Z80 C cross compiler v4.11
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH Z80 C cross compiler V4.11
 * (HI-TECH Software) and extend its life, outside of the MSDOS 16 bit environment
 * for full operation in windows 32/64 and Unix-like operating systems
 *
 * The HI-TECH Z80 C cross compiler V4.11 is provided free of charge for any use,
 * private or commercial, strictly as-is. No warranty or product support
 * is offered or implied including merchantability, fitness for a particular
 * purpose, or non-infringement. In no event will HI-TECH Software or its
 * corporate affiliates be liable for any direct or indirect damages.
 *
 * You may use this software for whatever you like, providing you acknowledge
 * that the copyright to this software remains with HI-TECH Software and its
 * corporate affiliates.
 *
 * All copyrights to the algorithms used, binary code, trademarks, etc.
 * belong to the legal owner - Microchip Technology Inc. and its subsidiaries.
 * Commercial use and distribution of recreated source codes without permission
 * from the copyright holderis strictly prohibited.
 *
 * This work is an extension of earlier work on decompiling ZAS.COM from the
 * Hi-Tech CP/M based compiler v3.09
 *
 * See the readme.md file for additional commentary
 *
 * Mark Ogden
 * 06-Jun-2022
 */
#include "cclass.h"
#include "zas.h"

/*
 *	IDENT Record
 */
char recIdent[] = {   /* 00b6 */
    7,                /* Record type (8 bits) (IDENT) */
    0,   1,   2,   3, /* byte order (32 bits) */
    0,   1,           /* byte order (16 bits) */
    'Z', '8', '0', 0  /* machine srcType */
};
int16_t identLen = sizeof(recIdent) - 1; /* 00c2 */

char relocRecord[512]; /* 19f2 */
char textRecord[512];  /* 1bf2 */
char *pRelocData;      /* 1df2 */
char symRecord[512];   /* 1df4 */
char *pEndTextRecord;  /* 1ff4 */
prop_t startAddr;      /* 1ff6 */
char *pSymData;        /* 1ffe */
uint32_t curLoc32;     /* 2000 - updated but never used */
char *pTextData;       /* 2004 */

static void i16tole(char *p1, int16_t p2);                                       /* 2 00EC */
static void i32tole(char *p1, uint32_t p2);                                      /* 3 00FE */
static _Noreturn void objWriteErr(void);                                         /* 4 0148 */
static void initRecords(void);                                                   /* 6 01DA */
static void writeTextRecord(void);                                               /* 8 0250 */
static void add_reloc(register prop_t *pc, uint16_t relocSize, uint16_t offset); /* 12 02F0 */
static void writeSymRecord(void);                                                /* 20 05FE */
static void nextSymRecord(void);                                                 /* 21 063C */
static void addObjPsect(register sym_t *ps);                                     /* 23 0700 */

/* unused functions or duplicate */
#ifdef _FORCE
static void i16tole_0(char *p1, int16_t p2);                           /* 1 00DA */
static void writeOMFRecord(int8_t rtype, int16_t len, uint8_t *pData); /* 5 0154 */
static void sub_02bc(int16_t dx);                                      /* 10 02BC */
static void addNops(int16_t nNop);                                     /* 14 038C */
static void sub_0500(register prop_t *pc);                             /* 17 0500 */
#else
/* mapped duplicate */
#define i16tole_0 i16tole
#endif

/**************************************************************************
 1	i16tole_0	00da    duplicate of i16tole
 **************************************************************************/
#if _FORCE
static void i16tole_0(char *p1, int16_t p2) {
    *p1++ = (char)p2;
    *p1   = p2 >> 8;
}
#endif

/**************************************************************************
 2	i16tole	00ec	++
 **************************************************************************/
static void i16tole(char *p1, int16_t p2) {
    *p1++ = (char)p2;
    *p1   = p2 >> 8;
}

/**************************************************************************
 3	i32tole	00fe	++
 **************************************************************************/
static void i32tole(char *p1, uint32_t p2) {
    *p1++ = p2;
    *p1++ = p2 >> 8;
    *p1++ = p2 >> 0x10;
    *p1   = p2 >> 0x18;
}

/**************************************************************************
 4 objWriteErr 0148 ++
 **************************************************************************/
static _Noreturn void objWriteErr() {
    fatalErr("Write error on object file");
}

/**************************************************************************
 5	0154 ++ (not used)
 **************************************************************************/
#if _FORCE
static void writeOMFRecord(int8_t rtype, int16_t len, uint8_t *pData) {
    uint16_t var2;
    uint8_t var5[3];
    uint8_t var6;
    int16_t var8;
    var6 = var5[0] = rtype;
    var8           = len;
    i16tole_0(&var5[1], len + 1);
    if (fwrite(var5, 3, 1, objFp) != 1 || fwrite(pData, 1, var8, objFp) != var8)
        objWriteErr();
    for (var2 = var5[1] + var6 + var5[2]; var8--; pData++)
        var2 += *pData;
    fputc(~var2 & 0xff, objFp);
}
#endif

/**************************************************************************
 6	01da ++
 **************************************************************************/
static void initRecords() {
    register sym_t *pPsect;

    textRecord[2] = 1; /* TEXT record */
    pPsect        = curPsect;
    i32tole(textRecord + 3, pPsect->sProp.vCurLoc);            /* write offset */
    strcpy(textRecord + 7, curPsect->sName);                   /* write psect srcType */
    pEndTextRecord = textRecord + 8 + strlen(curPsect->sName); /* calc start of data */
    relocRecord[2] = 3;
    pRelocData     = relocRecord + 3;
    pTextData      = pEndTextRecord;
}

/**************************************************************************
 7	021e ++
 **************************************************************************/
void writeObjHeader() {
    fputc(identLen & 0xff, objFp);
    fputc(identLen >> 8, objFp);
    fwrite(recIdent, 1, sizeof(recIdent), objFp); /* IDENT Record */
    initRecords();
}

/**************************************************************************
 8	0250	++
 **************************************************************************/
static void writeTextRecord() {
    size_t textLen;

    textLen = (size_t)(pEndTextRecord - textRecord);
    i16tole(textRecord, (int16_t)textLen - 3);
    if (fwrite(textRecord, 1, textLen, objFp) != textLen)
        objWriteErr();
}

/**************************************************************************
 9	027c++
 **************************************************************************/
void writeRecords() {
    uint16_t relocLen;

    if (pEndTextRecord != pTextData)
        writeTextRecord();
    if (pRelocData == relocRecord + 3)
        return;
    relocLen = (uint16_t)(pRelocData - relocRecord);
    i16tole(relocRecord, relocLen - 3);
    if (fwrite(relocRecord, 1, relocLen, objFp) != relocLen)
        objWriteErr();
}

/**************************************************************************
 10	02bc ++ (not used)
 **************************************************************************/
#if _FORCE
static void sub_02bc(int16_t dx) {
    if (pEndTextRecord != pTextData)
        addObjByte(0);
    else {
        curPsect->sProp.vCurLoc++;
        finishRecords();
    }
}
#endif

/**************************************************************************
 11	02e2 ++
 **************************************************************************/
void finishRecords() {
    if (phase == 2) {
        writeRecords();
        initRecords();
    }
}

/**************************************************************************
 12	02f0 ++
 **************************************************************************/
static void add_reloc(register prop_t *pc, uint16_t relocSize, uint16_t offset) {
    int16_t nameLen;
    char relocType;
    bool textWritten;
    char *name;

    textWritten = false;
    if ((relocType = pc->rType)) {
        if (relocSize > 15)
            fatalErr("add_reloc - bad size");
        relocType += relocSize;
        nameLen = (int16_t)strlen(name = pc->rSym->sName) + 1;
        if (pRelocData + nameLen + 3 >= &relocRecord[512]) {
            finishRecords(); /* this writes text & reloc records */
            textWritten = 1;
        }
        i16tole(pRelocData, offset);
        pRelocData[2] = relocType;
        strcpy(pRelocData + 3, name);
        pRelocData += (nameLen + 3);
        if (textWritten) /* need to force reloc data to refer to already written textRecord */
            finishRecords();
    }
}

/**************************************************************************
 13  37c++
 **************************************************************************/
void updateMaxLoc(sym_t *si) {
    if (si->sProp.vCurLoc > si->sProp.vMaxLoc)
        si->sProp.vMaxLoc = si->sProp.vCurLoc;
}

/**************************************************************************
 14 038c++ (not used)
 **************************************************************************/
#if _FORCE
void addNops(int16_t nNop) {
    if (phase != 2)
        curLoc32 = curPsect->sProp.vCurLoc;
    else if (nNop < 0)
        fatalErr("Opps! -ve number of nops required!");
    while (nNop--) {
        if (pEndTextRecord == &textRecord[512])
            finishRecords();
        curPsect->sProp.vCurLoc++;
        *pEndTextRecord++ = 0x90;
        updateMaxLoc(curPsect);
    }
}
#endif

/**************************************************************************
 15	03f2++
 **************************************************************************/
void addObjByte(int16_t n) {
    if (phase != 2) {
        curPsect->sProp.vCurLoc++;
        curLoc32++;
    } else {
        if (controls)
            putByte(n, 0);
        if (pEndTextRecord == &textRecord[512])
            finishRecords();
        curPsect->sProp.vCurLoc++;
        *pEndTextRecord++ = (char)n;
        updateMaxLoc(curPsect);
    }
}

/**************************************************************************
 16	044c++ (note al not used)
 **************************************************************************/
void addObjRelocWord(register prop_t *pc, uint8_t al) {
    uint16_t flags;
    uint8_t lowFlags;
    
    (void)al;

    if (phase != 2) {
        curPsect->sProp.vCurLoc += 2;
        curLoc32 += 2;
    } else {
        lowFlags = pc->rType & 0x3f;
        if (lowFlags == RT_EXT)
            flags = TF_EXT;
        else if (lowFlags == RT_REL)
            flags = TF_REL;
        else
            flags = 0;

        if (controls)
            putAddr(pc->vNum, flags);
        if (pEndTextRecord >= &textRecord[511])
            finishRecords();
        curPsect->sProp.vCurLoc += 2;
        *pEndTextRecord++ = pc->vNum;
        *pEndTextRecord++ = pc->vNum >> 8;
        updateMaxLoc(curPsect);
        add_reloc(pc, 2, (uint16_t)(pEndTextRecord - pTextData - 2));
    }
}

/**************************************************************************
 17 0500 ++(not used)
 **************************************************************************/
#if _FORCE
static void sub_0500(register prop_t *pc) {
    if (phase != 2) {
        curPsect->sProp.vCurLoc += 2;
        curLoc32 += 2;
    } else {
        pc->rType |= S_ABS;
        addObjRelocWord(pc, 0);
    }
}
#endif
/**************************************************************************
 18 52c ++ (note al is not used)
 **************************************************************************/
void addObjRelocByte(register prop_t *pc, uint8_t al) {
    uint16_t flags;
    uint8_t lowFlags;

    (void)al;
    if (phase != 2) {
        curPsect->sProp.vCurLoc++;
        curLoc32++;
    } else {
        if (!s_opt && (pc->vNum >= 256 || pc->vNum < -128))
            error("Size error");
        lowFlags = pc->rType & 0x3f;
        if (lowFlags == RT_EXT)
            flags = TF_EXT;
        else if (lowFlags == RT_REL)
            flags = TF_REL;
        else
            flags = 0;

        if (controls)
            putByte(pc->vNum, flags);
        if (pEndTextRecord == &textRecord[512])
            finishRecords();
        curPsect->sProp.vCurLoc++;
        *pEndTextRecord++ = pc->vNum;
        updateMaxLoc(curPsect);
        add_reloc(pc, 1, (uint16_t)(pEndTextRecord - pTextData - 1));
    }
}

/**************************************************************************
 19 05f2 ++
 **************************************************************************/
void initSymRecord() {
    symRecord[2] = 4;
    pSymData     = &symRecord[3];
}

/**************************************************************************
20 05fe ++
 **************************************************************************/
static void writeSymRecord() {
    uint16_t recLen;
    if (pSymData != &symRecord[3]) {
        recLen = (uint16_t)(pSymData - symRecord);
        i16tole_0(symRecord, recLen - 3);
        if (fwrite(symRecord, 1, recLen, objFp) != recLen)
            objWriteErr();
    }
}

/**************************************************************************
21 63c ++
**************************************************************************/
static void nextSymRecord() {
    writeSymRecord();
    initSymRecord();
}

/**************************************************************************
 22 0664++
 **************************************************************************/
void addObjSymbol(register sym_t *ps) {
    if (phase == 2) {
        int16_t len = (int16_t)strlen(ps->sName) + 2;
        char *s;
        if (ps->sProp.rType == RT_ABS)
            ps->sProp.rSym = NULL;
        if (ps->sProp.rType == RT_REL)
            len += (int16_t)strlen(ps->sProp.rSym->sName);
        if (pSymData + len + 6 >= &symRecord[512])
            nextSymRecord();
        i32tole(pSymData, ps->sProp.vNum);
        i16tole(pSymData + 4, ps->sFlags & S_STYPEMASK); // only GLOBAL &  special/size
        if (ps->sProp.rType == RT_REL) {
            strcpy(pSymData + 6, ps->sProp.rSym->sName);
            s = pSymData + 7 + strlen(ps->sProp.rSym->sName);
        } else {
            s    = pSymData + 6;
            *s++ = 0;
        }
        strcpy(s, ps->sName);
        pSymData += len + 6;
    }
}

/**************************************************************************
 23 0700 ++
 **************************************************************************/
static void addObjPsect(register sym_t *ps) {
    uint16_t len    = (uint16_t)strlen(ps->sName) + 1;
    relocRecord[2] = 2; /* PSECT */
    i16tole(relocRecord, len + 2);
    strcpy(relocRecord + 5, ps->sName);
    i16tole_0(relocRecord + 3, ps->sFlags);
    len += 5;
    if (fwrite(relocRecord, 1, len, objFp) != len)
        objWriteErr();
    if (ps->sProp.vCurLoc & 1) /* make even */
        ps->sProp.vCurLoc++;
    if (ps->sProp.vMaxLoc < ps->sProp.vCurLoc) {
        relocRecord[2] = 1; /* TEXT */
        i32tole(relocRecord + 3, ps->sProp.vCurLoc);
        strcpy(relocRecord + 7, ps->sName);
        len = (uint16_t)strlen(ps->sName) + 5;
        i16tole(relocRecord, len);
        len += 3;
        if (fwrite(relocRecord, 1, len, objFp) != len)
            objWriteErr();
    }
    if (ps->sProp.psSize || ps->sProp.pFlags) {
        relocRecord[2] = 8;                         /* XPSECT */
        i32tole(relocRecord + 3, ps->sProp.psSize); /* max size */
        i16tole(relocRecord + 7, ps->sProp.pFlags); /* relocatability */
        strcpy(relocRecord + 15, ps->sName);
        len = (uint16_t)strlen(ps->sName) + 13;
        i16tole(relocRecord, len);
        len += 3;
        if (fwrite(relocRecord, 1, len, objFp) != len)
            objWriteErr();
    }
}

/**************************************************************************
 24 0804 ++
 **************************************************************************/
void addObjAllSymbols() {
    sym_t **ppSym = symTable;
    uint16_t flags;

    while (*ppSym) {
        flags = (*ppSym)->sFlags;
        if ((flags & S_PSECT)) {
            (*ppSym)->sFlags &= S_PTYPEMASK;
            addObjPsect(*ppSym);
        } else if (!((*ppSym)->sFlags & S_MACROARG) && ((*ppSym)->sFlags & (S_UNDEF | S_GLOBAL))) {
            if ((*ppSym)->sFlags & S_UNDEF)
                (*ppSym)->sFlags = S_GLOBAL + S_EXTERN; /* EXTERNAL */
            addObjSymbol(*ppSym);
        }
        (*ppSym++)->sFlags = flags;
    }
    writeSymRecord();
}

/**************************************************************************
 25 0864 ++
 **************************************************************************/
void addObjEnd() {
    uint16_t len;
    if (startAddr.rSym) {
        textRecord[2] = 5; /* START */
        len           = (uint16_t)strlen(startAddr.rSym->sName) + 5;
        strcpy(textRecord + 7, startAddr.rSym->sName);
        i16tole_0(textRecord, len);
        i32tole(textRecord + 3, startAddr.vNum);
        if (fwrite(textRecord, 1, len + 3, objFp) != (uint16_t)(len + 3))
            objWriteErr();
    }
    textRecord[2] = 6; /* END */
    i16tole_0(textRecord, 2);
    i16tole(textRecord + 3, 0);
    if (fwrite(textRecord, 1, 5, objFp) != 5)
        objWriteErr();
}
