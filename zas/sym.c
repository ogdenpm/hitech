/*
 *
 * The sym.c file is part of the restored ZAS.COM program
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
#include "zas.h"

sym_t *curPsect;              /* a298 */
int16_t maxSymLen;            /* a29a */
sym_t *absPsect;              /* a29c */
int numSymbols;               /* a29e */
sym_t *symTable[MAX_SYMBOLS]; /* a2a0 */
prop_t retProp;               /* a752 */

static int hash(register char *str, int hashSize);              /* 102 4F35 +-- */
static int sym_cmpfunc(const void *ppSym1, const void *ppSym2); /* 107 51AD +-- */

/**************************************************************************
 102	hash	+++
 **************************************************************************/
static int hash(register char *str, int hashSize) {
    uint16_t sum;

    for (sum = 0; *str != 0; ++str)
        sum += *(uint8_t *)str + sum;
    return sum % hashSize;
}

/**************************************************************************
 103	getSym	+++
 **************************************************************************/
sym_t *getSym(register char *name, int flags) {
    sym_t *pSym;
    sym_t **ppSym;
    int16_t nameLen;

    if (!(flags & 0x100) && crfFp && c_opt != 0)
        fprintf(crfFp, "%s %d\n", name, curLineno);

    ppSym = symTable + hash(name, MAX_SYMBOLS);
    pSym  = *ppSym;

    while (pSym && ((pSym->sFlags & 0x100) != flags || (strcmp(pSym->sName, name) != 0)))
        pSym = pSym->sChain;

    if (pSym)
        return pSym;

    if (++numSymbols == MAX_SYMBOLS)
        fatalErr("Too may symbols");

    /* insert new symbol at head of hash chain */
    pSym         = xalloc(sizeof(sym_t));
    pSym->sChain = *ppSym;
    *ppSym       = pSym;
    nameLen      = (int16_t)strlen(name);
    pSym->sName  = xalloc(nameLen + 1); /* insert symbol srcType */
    strcpy(pSym->sName, name);
    if (maxSymLen < nameLen)
        maxSymLen = nameLen;
    if ((flags & 0x100))
        pSym->sFlags = flags;
    else {
        pSym->sFlags        = 0x200;
        pSym->sProp.cExtSym = pSym;
    }
    return pSym;
}

/**************************************************************************
 104	xalloc	sub_50e3h	+++
 **************************************************************************/
void *xalloc(size_t size) {
    register char *st;

    if ((st = calloc(1, size)) == 0)
        fatalErr("Out of memory");
    return st;
}

/**************************************************************************
 105	enterAbsPsect	+++
 **************************************************************************/
void enterAbsPsect() {
    register sym_t *st;

    if ((absPsect = getSym("", 0x100)) == 0)
        fatalErr("Can't enter abs psect");
    st = absPsect;
    st->sFlags |= 0xd0;
    st->sProp.cExtSym = 0;
    curPsect          = absPsect;
}

/**************************************************************************
 106	resetVals	+++
 **************************************************************************/
void resetVals() {
    sym_t **ppSym;
    register sym_t *pSym;

    ppSym = symTable;
    do {
        for (pSym = *ppSym; pSym; pSym = pSym->sChain)
            if (pSym && (pSym->sFlags & 0x100))
                pSym->sProp.vNum = 0L;
    } while (++ppSym < &symTable[MAX_SYMBOLS]);
    curPsect = absPsect;
}

/**************************************************************************
 107	sym_cmpfunc	sub_51adh	+++
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
 108	sortSymbols	+++
 * unchains symbols into one list in symTable and sorts them
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
 109	remSym	+++
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
 110	addSym	+++
 **************************************************************************/
void addSym(register sym_t *pSym) {
    sym_t **pSlot = &symTable[hash(pSym->sName, MAX_SYMBOLS)];
    pSym->sChain  = *pSlot;
    *pSlot        = pSym;
}

/**************************************************************************
 111	dupSym	+++
 **************************************************************************/
sym_t *dupSym(register sym_t *pSym) {
    sym_t *pNewSym;

    pNewSym         = xalloc(sizeof(sym_t));
    *pNewSym        = *pSym;
    pNewSym->sChain = 0;
    return pNewSym;
}
