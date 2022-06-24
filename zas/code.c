/*
 *
 * The code.c file is part of the restored ZAS.COM program
 * from the Hi-Tech C compiler v3.09
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH C compiler V3.09
 * (HI-TECH Software) and extend its life, outside of the CP/M environment
 * (Digital Research, Inc), for full operation in a  Unix-like operating
 * system UZI-180 without using the CP/M emulator.
 *
 * The HI-TECH C compiler V3.09 is provided free of charge for any use,
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
 * Early work on the decompilation was done by Andrey Nikitin
 * Completion of the work and porting to work under modern compilers done by Mark Ogden
 * 19-May-2022
 */
#include "cclass.h"
#include "zas.h"

/*
 *	IDENT Record
 */
char recIdent[] = {
    /* 80ec */
    10,               /* Length (16 bits) */
    0,   7,           /* Record type (8 bits) (IDENT) */
    0,   1,   2,   3, /* byte order (32 bits) */
    0,   1,           /* byte order (16 bits) */
    'Z', '8', '0', 0  /* machine srcType */
};

char relocRecord[512]; /* 9391 */
char textRecord[512];  /* 9591 */
char *pTextData;       /* 9791 */
char *pRelocData;      /* 9793 */
char *pEndTextRecord;  /* 9795 */
char *pSymData;        /* 9797 */
rval_t startAddr;      /* 9799 */

#ifdef CPM
static int nameCmp(register char *str1, char *str2); /* 1 013D +++ */
#endif
static void initRecords();                                                     /* 3 01E1 +++ */
static void writeTextRecord();                                                 /* 4 0238 +++ */
static void add_reloc(register rval_t *pv, uint16_t relocSize, size_t offset); /* 7 02F1 +-- */
static _Noreturn void objWriteErr();                                           /* 11 067C +-- */
static void addObjSymbol(register sym_t *ps);                                  /* 12 0685 +-- */
static void initSymRecord(void);                                               /* 13 078B +-- */
static void writeSymRecord(void);                                              /* 14 0797 +-- */
static void nextSymRecord(void);                                               /* 15 07ED +-- */
static void addObjPsect(register sym_t *ps);                                   /* 16 07F2 +-- */
static void i16tole(char *buf, int16_t val);                                   /* 18 0A09 +-- */
static void u32tole(char *buf, uint32_t val);                                  /* 19 0A32 +-- */

/**************************************************************************
 1	013d +++ (not used)
 **************************************************************************/
#ifdef CPM
static int nameCmp(register char *str1, char *str2) {
    while (*str1) {
        if (Tolower(*str1) != *str2)
            break;
        ++str1;
        ++str2;
    }
    return Tolower(*str1) - *str2;
}
#endif

/**************************************************************************
 2	01c1 +++
 * note optimiser removes call to csv and does tail end jp
 **************************************************************************/
void writeObjHeader() {
    fwrite(recIdent, 1, sizeof(recIdent), objFp); /* IDENT Record */
    initRecords();
}

/**************************************************************************
 3	01e1 +++
 **************************************************************************/
static void initRecords() {
    register sym_t *pPsect;

    textRecord[2] = 1; /* TEXT record */
    pPsect        = curPsect;
    u32tole(textRecord + 3, pPsect->pCurLoc);                              /* write offset */
    strcpy(textRecord + 7, curPsect->sName);                               /* write psect srcType */
    pTextData = pEndTextRecord = textRecord + 8 + strlen(curPsect->sName); /* calc start of data */
    relocRecord[2]             = 3;
    pRelocData                 = relocRecord + 3;
}

/**************************************************************************
 4	writeTextRecord	+++
 **************************************************************************/
static void writeTextRecord() {
    size_t textLen;

    textLen = (size_t)(pEndTextRecord - textRecord);
    i16tole(textRecord, (int16_t)textLen - 3);
    if (fwrite(textRecord, 1, textLen, objFp) == textLen)
        return;
    objWriteErr();
}

/**************************************************************************
 5	writeRecords	ok++
 **************************************************************************/
void writeRecords() {
    size_t relocLen;

    if (pEndTextRecord != pTextData)
        writeTextRecord();
    if (pRelocData == relocRecord + 3)
        return;
    relocLen = (size_t)(pRelocData - relocRecord);
    i16tole(relocRecord, (int16_t)relocLen - 3);
    if (fwrite(relocRecord, 1, relocLen, objFp) != relocLen)
        objWriteErr();
}

/**************************************************************************
 6	finishRecords	ok++
 **************************************************************************/
void finishRecords() {
    if (phase == 2) {
        writeRecords();
        initRecords();
    }
}

/**************************************************************************
 7	add_reloc +++
 * optimiser avoids ex de,hl by swapping test
 **************************************************************************/

static void add_reloc(register rval_t *pv, uint16_t relocSize, size_t offset) {
    size_t nameLen;
    char relocType;
    bool textWritten;
    char *name;

    textWritten = false;
    if (pv->eSym) {
        relocType = R_RNAME;
        name      = pv->eSym->sName;
    } else if (pv->pSym) {
        relocType = R_RPSECT;
        name      = pv->pSym->sName;
    } else
        return;

    if (relocSize > 15)
        fatalErr("add_reloc - bad size");
    relocType += relocSize;
    nameLen = strlen(name) + 1;
    if (pRelocData + nameLen + 3 >= &relocRecord[512]) {
        finishRecords(); /* this writes text & reloc records */
        textWritten = 1;
    }
    i16tole(pRelocData, (int16_t)offset);
    pRelocData[2] = relocType;
    strcpy(pRelocData + 3, name);
    pRelocData += (nameLen + 3);
    if (textWritten) /* need to force reloc data to refer to already written textRecord */
        finishRecords();
    return;
}

/**************************************************************************
8	03d0 +++
**************************************************************************/
void addObjByte(int16_t n) {
    if (phase != 2)
        curPsect->pCurLoc++;
    else {
        if (controls)
            putByte(n, 0);
        if (pEndTextRecord == &textRecord[512])
            finishRecords();
        curPsect->pCurLoc++;
        *pEndTextRecord++ = (char)n;
        if (curPsect->pSize < curPsect->pCurLoc)
            curPsect->pSize = curPsect->pCurLoc;
    }
}

/**************************************************************************
 9	0461 +++
 **************************************************************************/
void addObjRelocWord(register rval_t *pv) {
    uint16_t flags;
    if (phase != 2)
        curPsect->pCurLoc += 2;
    else {
        if (pv->eSym)
            flags = TF_EXT;
        else if (pv->pSym)
            flags = TF_REL;
        else
            flags = 0;
        if (controls)
            putAddr(pv->val, flags);
        if (pEndTextRecord >= &textRecord[511])
            finishRecords();
        curPsect->pCurLoc += 2;
        *pEndTextRecord++ = pv->val;
        *pEndTextRecord++ = pv->val >> 8;
        if (curPsect->pSize < curPsect->pCurLoc)
            curPsect->pSize = curPsect->pCurLoc;
        add_reloc(pv, 2, pEndTextRecord - pTextData - 2);
    }
}

/**************************************************************************
 10 055a +++
 **************************************************************************/
void addObjRelocByte(register rval_t *pv) {
    uint16_t flags;
    if (phase != 2)
        curPsect->pCurLoc += 1L;
    else {
        if (!s_opt && (pv->val >= 256 || pv->val < -128))
            error("Size error");
        if (pv->eSym)
            flags = TF_EXT;
        else if (pv->pSym)
            flags = TF_REL;
        else
            flags = 0;
        if (controls)
            putByte(pv->val, flags);
        if (pEndTextRecord == &textRecord[512])
            finishRecords();
        curPsect->pCurLoc++;
        *pEndTextRecord++ = pv->val;
        if (curPsect->pSize < curPsect->pCurLoc)
            curPsect->pSize = curPsect->pCurLoc;
        add_reloc(pv, 1, pEndTextRecord - pTextData - 1);
    }
}

/**************************************************************************
 11 objWriteErr 067c +++
 **************************************************************************/
static _Noreturn void objWriteErr() {
    fatalErr("Write error on object file");
}

/**************************************************************************
 12 0685 +++
 **************************************************************************/
static void addObjSymbol(register sym_t *ps) {
    size_t len = strlen(ps->sName) + 2;
    char *var4;
    if (ps->sPsym)
        len += strlen(ps->sPsym->sName);
    if (pSymData + len + 6 >= &textRecord[512])
        nextSymRecord();
    u32tole(pSymData, ps->sVal);
    i16tole(pSymData + 4, ps->sFlags);
    if (ps->sPsym) {
        strcpy(pSymData + 6, ps->sPsym->sName);
        var4 = pSymData + 7 + strlen(ps->sPsym->sName);
    } else {
        var4    = pSymData + 6;
        *var4++ = 0;
    }
    strcpy(var4, ps->sName);
    pSymData += len + 6;
}
/**************************************************************************
 13 0788 +++
 **************************************************************************/
static void initSymRecord() {
    textRecord[2] = 4;
    pSymData      = &textRecord[3];
}

/**************************************************************************
 14 0797 +++
 **************************************************************************/
static void writeSymRecord() {
    size_t recLen;
    if (pSymData != &textRecord[3]) {
        recLen = (size_t)(pSymData - textRecord);
        i16tole(textRecord, (int16_t)recLen - 3);
        if (fwrite(textRecord, 1, recLen, objFp) != recLen)
            objWriteErr();
    }
}

/**************************************************************************
15 07ed +++
**************************************************************************/
static void nextSymRecord() {
    writeSymRecord();
    initSymRecord();
}

/**************************************************************************
 16 07f2 +++
 **************************************************************************/
static void addObjPsect(register sym_t *ps) {
    size_t len     = strlen(ps->sName) + 1;
    relocRecord[2] = 2; /* PSECT */
    i16tole(relocRecord, (int16_t)len + 2);
    strcpy(relocRecord + 5, ps->sName);
    i16tole(relocRecord + 3, ps->sFlags);
    len += 5;
    if (fwrite(relocRecord, 1, len, objFp) != len)
        objWriteErr();
    if (ps->pCurLoc > ps->pSize) {
        relocRecord[2] = 1; /* TEXT */
        u32tole(relocRecord + 3, ps->pCurLoc);
        strcpy(relocRecord + 7, ps->sName);
        len = strlen(ps->sName) + 5;
        i16tole(relocRecord, (int16_t)len);
        len += 3;
        if (fwrite(relocRecord, 1, len, objFp) != len)
            objWriteErr();
    }
}

/**************************************************************************
 17 091f +++
 **************************************************************************/
void addObjAllSymbols() {
    sym_t **ppSym = symTable;
    initSymRecord();
    for (; *ppSym; ppSym++) {
        if ((*ppSym)->sFlags & S_PSECT) {
            (*ppSym)->sFlags &= S_PTYPEMASK;
            addObjPsect(*ppSym);
        } else if (!((*ppSym)->sFlags & S_MACRO)) {
            if (!x_opt || ((*ppSym)->sFlags & (S_GLOBAL | S_UNDEF))) {
                if ((*ppSym)->sFlags & S_UNDEF)
                    (*ppSym)->sFlags = S_GLOBAL + S_EXTERN;
                (*ppSym)->sFlags &= S_STYPEMASK;
                addObjSymbol(*ppSym);
            }
        }
    }
    writeSymRecord();
}

/**************************************************************************
 18	i16tole	0a09h	+++
 **************************************************************************/
static void i16tole(char *buf, int16_t val) {
    *buf++ = (char)val;
    *buf   = val >> 8;
}

/**************************************************************************
 19	u32tole	sub-0a32h	+++
 **************************************************************************/
static void u32tole(char *buf, uint32_t val) {
    *buf++ = val;
    *buf++ = val >> 8;
    *buf++ = val >> 16;
    *buf   = val >> 24;
}

/**************************************************************************
 20 0aa0 +++
 **************************************************************************/
void addObjEnd() {
    size_t len;
    if (startAddr.pSym) {
        textRecord[2] = 5; /* START */
        len           = strlen(startAddr.pSym->sName) + 5;
        strcpy(textRecord + 7, startAddr.pSym->sName);
        i16tole(textRecord, (int16_t)len);
        u32tole(textRecord + 3, startAddr.val);
        if (fwrite(textRecord, 1, len + 3, objFp) != len + 3)
            objWriteErr();
    }
    textRecord[2] = 6; /* END */
    i16tole(textRecord, 2);
    i16tole(textRecord + 3, 0);
    if (fwrite(textRecord, 1, 5, objFp) != 5)
        objWriteErr();
}
