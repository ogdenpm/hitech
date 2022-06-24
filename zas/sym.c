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
rval_t retProp;               /* a752 */

static int hash(register char *str, int hashSize);              /* 102 4F35 +-- */
static int sym_cmpfunc(const void *pps1, const void *pps2); /* 107 51AD +-- */

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
    sym_t *psIter;
    sym_t **pps;
    int16_t nameLen;

    if (!(flags & S_PSECT) && crfFp && c_opt != 0)
        fprintf(crfFp, "%s %d\n", name, curLineno);

    pps = symTable + hash(name, MAX_SYMBOLS);
    psIter  = *pps;

    while (psIter && ((psIter->sFlags & S_PSECT) != flags || (strcmp(psIter->sName, name) != 0)))
        psIter = psIter->sChain;

    if (psIter)
        return psIter;

    if (++numSymbols == MAX_SYMBOLS)
        fatalErr("Too may symbols");

    /* insert new symbol at head of hash chain */
    psIter         = xalloc(sizeof(sym_t));
    psIter->sChain = *pps;
    *pps       = psIter;
    nameLen      = (int16_t)strlen(name);
    psIter->sName  = xalloc(nameLen + 1); /* insert symbol srcType */
    strcpy(psIter->sName, name);
    if (maxSymLen < nameLen)
        maxSymLen = nameLen;
    if ((flags & S_PSECT))
        psIter->sFlags = flags;
    else {
        psIter->sFlags = S_UNDEF;
        psIter->sEsym  = psIter;
    }
    return psIter;
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
    register sym_t *ps;

    if ((absPsect = getSym("", S_PSECT)) == 0)
        fatalErr("Can't enter abs psect");
    ps = absPsect;
    ps->sFlags |= S_ABSPSECT | S_GLOBAL;
    ps->sEsym = 0;
    curPsect  = absPsect;
}

/**************************************************************************
 106	resetVals	+++
 **************************************************************************/
void resetVals() {
    sym_t **pps;
    register sym_t *ps;

    pps = symTable;
    do {
        for (ps = *pps; ps; ps = ps->sChain)
            if (ps && (ps->sFlags & S_PSECT))
                ps->sVal = 0L;
    } while (++pps < &symTable[MAX_SYMBOLS]);
    curPsect = absPsect;
}

/**************************************************************************
 107	sym_cmpfunc	sub_51adh	+++
 **************************************************************************/
static int sym_cmpfunc(const void *pps1, const void *pps2) {
    register sym_t const *ps1 = *(sym_t const **)pps1;
    sym_t const *ps2          = *(sym_t const **)pps2;

    if (ps2 == ps1)
        return 0;
    if (ps1 == 0)
        return 1;
    if (ps2 == 0)
        return -1;
    return strcmp(ps1->sName, ps2->sName);
}

/**************************************************************************
 108	sortSymbols	+++
 * unchains symbols into one list in symTable and sorts them
 **************************************************************************/
void sortSymbols() {
    sym_t **pSlot;
    sym_t **pEmptySlot;
    sym_t *tmpPSym;
    register sym_t *psIter;

    pEmptySlot = pSlot = symTable;
    /* raise all of the hash chained symbols to the top level, using free slots */
    while (pSlot < &symTable[MAX_SYMBOLS]) {
        psIter = *pSlot;
        while ((psIter && psIter->sChain)) {
            while (*pEmptySlot) /* find the first free slot */
                ++pEmptySlot;
            *pEmptySlot     = psIter->sChain; /* move the first chained symbol to its own slot */
            tmpPSym         = psIter;
            psIter            = psIter->sChain; /* continue with next symbol */
            tmpPSym->sChain = 0;            /* remove the chain from the original sym */
        }
        ++pSlot;
    }
    qsort(symTable, MAX_SYMBOLS, sizeof(symTable[0]), sym_cmpfunc);
}

/**************************************************************************
 109	remSym	+++
 **************************************************************************/
sym_t *remSym(register sym_t *ps) {
    sym_t **pSlot;
    sym_t *psIter;

    pSlot = &symTable[hash(ps->sName, MAX_SYMBOLS)];
    if (*pSlot == ps) {
        *pSlot = ps->sChain;
        return ps;
    }
    for (psIter = *pSlot; psIter->sChain && psIter->sChain != ps; psIter = psIter->sChain)
        ;

    if (!psIter)
        fatalErr("REMSYM error");
    psIter->sChain = ps->sChain; /* remove from the chain */
    return ps;
}

/**************************************************************************
 110	addSym	+++
 **************************************************************************/
void addSym(register sym_t *ps) {
    sym_t **pSlot = &symTable[hash(ps->sName, MAX_SYMBOLS)];
    ps->sChain  = *pSlot;
    *pSlot        = ps;
}

/**************************************************************************
 111	dupSym	+++
 **************************************************************************/
sym_t *dupSym(register sym_t *ps) {
    sym_t *pNewSym;

    pNewSym         = xalloc(sizeof(sym_t));
    *pNewSym        = *ps;
    pNewSym->sChain = 0;
    return pNewSym;
}
