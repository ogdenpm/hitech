/*
 *
 * The sym.c file is part of the restored ZAS.EXE program
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
#include "zas.h"

sym_t *curPsect;              /* 2b20 */
int16_t maxSymLen;            /* 2b22 */
sym_t *absPsect;              /* 2b24 */
int16_t numSymbols;           /* 2b26 */
sym_t *symTable[MAX_SYMBOLS]; /* 2b28 */
rval_t retProp;               /* 3ace */

static int16_t hash(register char *str, int16_t hashSize);      /* 125 4EA2 */
static int sym_cmpfunc(const void *ppSym1, const void *ppSym2); /* 131 5080 */

/**************************************************************************
 125 4ea2 ++
 **************************************************************************/
static int16_t hash(register char *str, int16_t hashSize) {
    uint16_t sum;

    for (sum = 0; *str != 0; ++str)
        sum += *(uint8_t *)str + sum;
    return sum % hashSize;
}

/**************************************************************************
 126 4ece++
 **************************************************************************/
sym_t *findSymSlot(char *name) {
    sym_t *pSym = symTable[hash(name, MAX_SYMBOLS)];
    while (pSym && ((pSym->sFlags & S_PSECT) || strcmp(pSym->sName, name)))
        pSym = pSym->sChain;
    return pSym;
}

/**************************************************************************
 127 4f02 ++
 **************************************************************************/
/* flags == S_PSECT to find the psect else flags = 0 to find other symbols*/
sym_t *getSym(register char *name, uint16_t flags) {
    sym_t *pSym;
    sym_t **pSlot;
    int16_t nameLen;

    if (!(flags & S_PSECT) && crfFp && c_opt)
        fprintf(crfFp, "%s %d\n", name, curLineno);

    pSlot = symTable + hash(name, MAX_SYMBOLS);
    pSym  = *pSlot;

    while (pSym && ((pSym->sFlags & S_PSECT) != flags || strcmp(pSym->sName, name)))
        pSym = pSym->sChain;

    if (pSym)
        return pSym;

    if (++numSymbols == MAX_SYMBOLS)
        fatalErr("Too may symbols");

    /* insert new symbol at head of hash chain */
    pSym         = xalloc(sizeof(sym_t));
    pSym->sChain = *pSlot;
    *pSlot       = pSym;
    nameLen      = (int16_t)strlen(name);
    pSym->sName  = xalloc(nameLen + 1); /* insert symbol srcType */
    strcpy(pSym->sName, name);
    if (maxSymLen < nameLen)
        maxSymLen = nameLen;
    if ((flags & S_PSECT))
        pSym->sFlags = flags;
    else {
        pSym->sFlags      = S_UNDEF;
        pSym->rSym  = pSym;
        pSym->rType = RT_EXT; // default to external
    }
    return pSym;
}

/**************************************************************************
 128 4fe0++
 **************************************************************************/
void *xalloc(size_t size) {
    register char *si;
    register char *di;

    if ((si = malloc(size)) == 0)
        fatalErr("Out of memory");
    for (di = si; size--; di++)
        *di = 0;
    return si;
}

/**************************************************************************
 129 5014 ++
 **************************************************************************/
void enterAbsPsect() {
    register sym_t *ps;

    if ((absPsect = getSym("", S_PSECT)) == 0)
        fatalErr("Can't enter abs psect");
    ps = absPsect;
    ps->sFlags |= (S_GLOBAL | S_ABSPSECT);
    ps->rSym  = NULL;
    ps->rType = RT_ABS;
    curPsect        = absPsect;
}

/**************************************************************************
 130 5046 ++
 **************************************************************************/
void resetVals() {
    sym_t **ppSym;
    register sym_t *pSym;

    ppSym = symTable;
    do {
        for (pSym = *ppSym; pSym; pSym = pSym->sChain)
            if (pSym && (pSym->sFlags & S_PSECT))
                pSym->rVal = 0L;
    } while (++ppSym < &symTable[MAX_SYMBOLS]);
    curPsect = absPsect;
}

/**************************************************************************
131 5000 ++
 **************************************************************************/
static int sym_cmpfunc(const void *ppSym1, const void *ppSym2) {
    register sym_t const *pSym1 = *(sym_t const **)ppSym1;
    sym_t const *pSym2          = *(sym_t const **)ppSym2;

    if (pSym2 == pSym1)
        return 0;
    if (pSym1 == 0)
        return 1;
    if (pSym2 == 0)
        return -1;
    return strcmp(pSym1->sName, pSym2->sName);
}

/**************************************************************************
 132 50be ++
 **************************************************************************/
void sortSymbols() {
    sym_t **pSlot;
    sym_t **pEmptySlot;
    sym_t *tmpPSym;
    register sym_t *pSym;

    pEmptySlot = pSlot = symTable;
    /* raise all of the hash chained symbols to the top level, using free slots */
    while (pSlot < &symTable[MAX_SYMBOLS]) {
        pSym = *pSlot;
        while ((pSym && pSym->sChain)) {
            while (*pEmptySlot) /* find the first free slot */
                ++pEmptySlot;
            *pEmptySlot     = pSym->sChain; /* move the first chained symbol to its own slot */
            tmpPSym         = pSym;
            pSym            = pSym->sChain; /* continue with next symbol */
            tmpPSym->sChain = 0;            /* remove the chain from the original sym */
        }
        ++pSlot;
    }
    qsort(symTable, MAX_SYMBOLS, sizeof(symTable[0]), sym_cmpfunc);
}

/**************************************************************************
 133 511a ++
 **************************************************************************/
sym_t *remSym(register sym_t *pSym) {
    sym_t **pSlot;
    sym_t *ps;

    pSlot = &symTable[hash(pSym->sName, MAX_SYMBOLS)];
    if (*pSlot == pSym) {
        *pSlot = pSym->sChain;
        return pSym;
    }
    for (ps = *pSlot; ps->sChain && ps->sChain != pSym; ps = ps->sChain)
        ;

    if (!ps)
        fatalErr("REMSYM error");
    ps->sChain = pSym->sChain; /* remove from the chain */
    return pSym;
}

/**************************************************************************
 134 5178++
 **************************************************************************/
void addSym(register sym_t *pSym) {
    sym_t **pSlot = &symTable[hash(pSym->sName, MAX_SYMBOLS)];
    pSym->sChain  = *pSlot;
    *pSlot        = pSym;
}

/**************************************************************************
 135 5196++
 **************************************************************************/
sym_t *dupSym(register sym_t *pSym) {
    sym_t *pNewSym;

    pNewSym         = xalloc(sizeof(sym_t));
    *pNewSym        = *pSym;
    pNewSym->sChain = 0;
    return pNewSym;
}

/**************************************************************************
 136 51c0 ++
 **************************************************************************/
void delSym(sym_t *si) {
    if (si->sName)
        free(si->sName);
    free(si);
    numSymbols--;
}