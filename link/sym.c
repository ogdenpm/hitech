/*
 * File created 14.11.2021, last modified 01.01.2022
 *
 * The e.c file is part of the restored LINK.COM program
 * from the Hi-Tech C compiler v3.09 package.
 *
 *	Andrey Nikitin	01.01.2022
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "link.h"

static sym_t **getSymSlot(char *, int);                     /* 1b00 46 */
static void prSymbol(char *, uint32_t, int, sym_t *);       /* 1d1d 49 */
static void defineSym(char *, sym_t *, uint32_t, int);      /* 2197 52 */
static void defineIfNeeded(char *, sym_t *, uint32_t, int); /* 22c3 53 */
static void setPsectOrigin(psect_t *);         /* 2766 59 */
static void wrSymbol(sym_t *);                 /* 3420 62 */
static char isLocalName(char *);               /* 3533 63 */
static void prPsectMap();                      /* 3576 64 */
static void prSummary(psect_t *);              /* 36f3 65 */
static void prSymMap();                        /* 3773 66 */
static int symCmp(const void *, const void *); /* 3a5b 67 */
 




static uint32_t linkPt;     /* 7cce */
sym_t *absSym;                   /* 7cd2 */
static psect_t psectInfo[20];    /* 7cd4 */
static uint32_t savLoadPt; /* 7ef0 */
static uint32_t maxLinkPt;  /* 7ef4 */
static int newSymCnt;            /* 7ef8 */
static uint32_t loadPt;     /* 7efa */
static sym_t **symTab;           /* 7efe */

psect_t *nextPsect = psectInfo;  /* 6f69 */

/**************************************************************************
 45	create_symtab	sub-1af4h	ok++ (PMO)
 **************************************************************************/
void allocSymTab() {

    symTab = (sym_t **)xalloc(SIZE_SYMTAB);
}

/**************************************************************************
 46	getSymbolSlot	ok++ (PMO)
 **************************************************************************/
static sym_t **getSymSlot(char *name, int flags) {
    sym_t **startp;
    sym_t **testp;
    uint16_t hashval;
    uint8_t *puc;
    register sym_t *ps;

    for (hashval = 0, puc = (uint8_t *)name; *puc != 0; puc++)
        hashval += *puc;
    startp = symTab + (hashval % MAX_SYMBOLS);
    flags &= 0xC000;
    testp = startp;
    while ((ps = *testp)) {
        if ((ps->flags & 0xC000) == flags) {
            if ((ps->flags & SF_GLOBAL) || ps->fileId == fileIdx || optR)
                if (strcmp(ps->name, name) == 0)
                    break;
        }
        if (++testp == &symTab[MAX_SYMBOLS])
            testp = symTab;
        if (testp == startp)
            fatalErr("Too many symbols");
    }
    return testp;
}

/**************************************************************************
 47	getSymbol	ok++ (PMO)
 **************************************************************************/
sym_t *getSymbol(char *symbol_name, int flags) {

    return *getSymSlot(symbol_name, flags);
}

/**************************************************************************
 48	addSym	ok++ (PMO)
 **************************************************************************/
sym_t *addSym(char *name, int flags) {
    sym_t **slot;
    register sym_t *ps;

    slot = getSymSlot(name, flags);
    ps   = *slot;

    if (ps == 0) {
        ++newSymCnt;
        *slot = ps = xalloc(sizeof(sym_t));
        ps->name   = xalloc(strlen(name) + 1);
        strcpy(ps->name, name);
        ps->fileId = (uint8_t)fileIdx;

        if ((flags & 0xC000) == 0) {
            ++cntUnresolved;
            ps->flags = SF_EXTERN;
        } else {
            if (nextPsect == psectInfo + MAX_PSECTS)
                fatalErr("Too many psects");
            nextPsect->psectSym = ps;
            ps->p.pinfo         = nextPsect++;
        }
    }
    ps->flags |= (flags & 0xFFF0);
    return ps;
}

/**************************************************************************
 49	prSymbol	ok++ (PMO)

 **************************************************************************/
static void prSymbol(char *name, uint32_t value, int loFlag, register sym_t *psectSym) {

    if (!optH) {
        if (loFlag)
            return;
        fprintf(symFp, "%4.4" PRIx32 " %s\n", value, name);
        return;
    }

    switch (loFlag) {
    case SF_REGNAM:
        fprintf(symFp, "%s reg %" PRIx32 "\n", name, value);
        return;

    case SF_FILNAM:
        fprintf(symFp, "%s\n", name);
        return;

    case SF_STACK:
        fprintf(symFp, "%s stk %" PRId32 "\n", name, value);
        return;
    }

    fprintf(symFp, "%s %" PRIx32, name, value);
    if (psectSym != 0)
        fprintf(symFp, " %" PRIx32,
                psectSym->p.pinfo->loadPt - psectSym->p.pinfo->linkPt);
    fputc('\n', symFp);
    return;
}

/**************************************************************************
 50	symRecPass2	ok++ (PMO)
 minor optimisation on type parameter for chkAddRecordItem
 **************************************************************************/
void symRecPass2() {
    uint32_t val;
    uint8_t *p;      /* ptr to sym record   */
    char *psectName; /* psectSym name       */
    char *symName;   /* symbol name         */
    sym_t *psectSym; /* ptr to psect symbol */
    uint16_t flag;   /* flags               */
    uint16_t loFlag; /* low flags           */
    size_t len;      /* sub record length   */

    readRecData(recbuf); /*  Read SYM record to recbuf */

    for (p = recbuf; recbuf + recLen > p; p += len) {
        flag    = (uint16_t)btoi16(p + 4);
        loFlag  = LowFlags(flag);
        symName = (psectName = (char *)p + SYM_PNAME);

        while (*symName++) /* Skip psectSym name */
            ;

        len      = SYM_PNAME + strlen(psectName) + 1 + strlen(symName) + 1;
        psectSym = *psectName ? addSym(psectName, SF_PSECT) : (sym_t *)0;
        val      = btou32(p);

        switch (loFlag) {
        case SF_NULL:
            if (flag & SF_GLOBAL)
                break;

        case SF_LINENO:
            if (psectSym != 0) {
                if (!(psectSym->flags & SF_OVRLD))
                    val += psectSym->p.pinfo->blkStartAddress;
                if (!optR)
                    val += psectSym->p.pinfo->linkPt;
            }
            u32tob(val, (uint8_t *)p);

        case SF_STACK:
        case SF_REGNAM:
        case SF_FILNAM:
            if (optX || (optZ && isLocalName(symName)))
                break;

            if (symFileName)
                prSymbol(symName, val, loFlag, psectSym);

            if (!optC) {
                chkAddRecordItem(SYM_RECORD, len);
                bmove(p, nonTextRecPtr, len);
                nonTextRecPtr += len;
            }
            break;

        case SF_COMM:
        case SF_EXTERN:
            break;
        }
    }
}

/**************************************************************************
 51	symRecPass1	ok++ (PMO)
 **************************************************************************/
void symRecPass1() {
    uint32_t val;
    uint8_t *p;       /*  ptr to sym record    */
    char *psectName;  /*  psect name           */
    char *symName;    /*  symbol name          */
    sym_t *psectSym;  /*  ptr to symbol table  */
    uint16_t flag;    /*  flags                */
    uint16_t loflag;  /*  low flags            */
    size_t symDefLen; /*  length of symbol def */

    readRecData(recbuf); /*  Read SYM record to recbuf */

    for (p = recbuf; p < recbuf + recLen; p += symDefLen) {
        flag    = (uint16_t)btoi16(p + SYM_FLAGS);
        loflag  = flag & 0xF;
        symName = psectName = (char *)p + SYM_PNAME;

        while (*symName++ != 0) /* skip psectSym name */
            ;

        symDefLen = SYM_PNAME + strlen(psectName) + 1 + strlen(symName) + 1;
        psectSym  = loflag == SF_NULL ? addSym(psectName, SF_PSECT) : (sym_t *)0;
        val       = btou32(p + SYM_VALUE);

        switch (loflag) {
        case SF_EXTERN:
            addSym(symName, flag | SF_GLOBAL); /* will add if not already present */
            break;

        case SF_NULL:
            if (!(flag & SF_GLOBAL)) /* skip local define names */
                break;

        case SF_COMM:
            defineSym(symName, psectSym, val, flag);
            break;

        case SF_STACK:
        case SF_REGNAM:
        case SF_LINENO:
        case SF_FILNAM:
            if (flag & SF_GLOBAL)
                simpleErr("symbol %s cannot be global", symName);
            break;
        }
    }
}

/**************************************************************************
 52	defineSym	ok++
 **************************************************************************/
static void defineSym(char *name, sym_t *psectSym, uint32_t val, int flags) {
    uint8_t sloFlag, loFlag;
    register sym_t *ps;

    ps = addSym(name, flags);
    ps->flags |= flags & 0xFFF0; /* merge high flags */
    sloFlag = ps->flags & 0xF;   /* current symbol low flags*/
    loFlag  = flags & 0xF;
    if (sloFlag == SF_COMM) {
        if (loFlag != SF_COMM)
            simpleErr("common symbol conflict: %s", name);
        else if (ps->p.value < val)
            ps->p.value = val;
    } else if (sloFlag == SF_EXTERN) {
        --cntUnresolved; /* symbol now resolved */
        ps->p.value  = val;
        ps->psectSym = psectSym;
        if (loFlag != SF_COMM && !(psectSym->flags & SF_OVRLD))
            ps->p.value += psectSym->p.pinfo->blkStartAddress;

        ps->flags = (ps->flags & 0xFFF0) | loFlag; /* update low flags */
    } else
        simpleErr("multiply defined symbol: %s", name);
}

/**************************************************************************
 53	defineIfNeeded	ok++ (PMO)
 **************************************************************************/
static void defineIfNeeded(char *name, sym_t *psectSym, uint32_t val, int flags) {
    register sym_t *ps;

    if ((ps = getSymbol(name, flags)) && LowFlags(ps->flags) != SF_EXTERN)
        return;
    defineSym(name, absSym, val, flags);
    addSym(name, flags)->psectSym = psectSym;
}

/**************************************************************************
 54	psectRecPass1	ok++ (PMO)
 optimiser changes ld a,h | or 80h | ld h,a with set 7,h
 **************************************************************************/
void psectRecPass1() {
    uint16_t psectFlag;
    register sym_t *ps;

    readRecData(recbuf); /* Read PSECT record to recbuf */

    psectFlag = (uint16_t)btoi16(recbuf + PSECT_FLAGS) | SF_PSECT;
    ps        = addSym((char *)recbuf + PSECT_PNAME, psectFlag);
    if ((ps->flags & SF_GLOBAL) && !(psectFlag & SF_GLOBAL))
        simpleErr("local psect '%s' conflicts with global psect of same name", ps->name);
}

/**************************************************************************
 55	xpsectRecPass1	ok++
 **************************************************************************/
void xpsectRecPass1() {
    sym_t *classSym;
    char *className;
    uint32_t maxSize;
    uint16_t relocatability;
    register sym_t *ps;

    readRecData(recbuf); /* Read XPSECT record to recbuf */

    ps = addSym((char *)recbuf + XPSECT_PNAME, SF_PSECT);
    /* force className to be set before adding to it */
    className = (char *)recbuf + XPSECT_PNAME;
    className += strlen(className) + 1;
    if (className - (char *)recbuf < recLen) {
        classSym = addSym(className, SF_CLASS | SF_GLOBAL);
        if (ps->p.pinfo->classSym == 0)
            ps->p.pinfo->classSym = classSym;
        else {
            if (classSym != ps->p.pinfo->classSym)
                simpleErr("psect %s cannot be in classes %s and %s", ps->name, classSym->name,
                          ps->p.pinfo->classSym->name);
        }
    }
    maxSize        = btou32(recbuf + XPSECT_MAX);
    relocatability = btoi16(recbuf + XPSECT_RELOC);
    if (maxSize != 0) {
        if (ps->p.pinfo->maxSize == 0 || maxSize < ps->p.pinfo->maxSize)
            ps->p.pinfo->maxSize = maxSize;
    }
    if (relocatability == 0)
        return;
    if (ps->p.pinfo->align != 0 && relocatability >= ps->p.pinfo->align)
        return;
    ps->p.pinfo->align = relocatability;
}

/**************************************************************************
 56	endRecPass1	ok++ (PMO)
 **************************************************************************/
void endRecPass1() {
    register psect_t *pp;

    readRecData(recbuf); /* Read END record to recbuf */

    for (pp = psectInfo; pp != nextPsect; ++pp) {
        if (pp->psectSym->flags & SF_OVRLD) {
            if (pp->blkStartAddress < pp->endAddr)
                pp->blkStartAddress = pp->endAddr;
        } else {
            pp->blkStartAddress += pp->endAddr;
        }
        pp->endAddr = 0;
    }
}

/**************************************************************************
 57	endRecPass2	ok++ (PMO)
 **************************************************************************/
void endRecPass2() {

    if (optM)
        prPsectMap();
    endRecPass1();
}

/**************************************************************************
 58	parseNum	sub_25a8h	ok++ (PMO)
 * Converts a numeric string in various databases to a uint32_t integer value.
 * Returns 0 on successful conversion and 1 on failure.
 **************************************************************************/
char parseNum(char **p1, uint32_t *p2) {
    char digit;
    char *endp;
    char *startp;
    char base;
    uint32_t val;

    startp = endp = *p1;
    if (isxdigit(*endp) == 0)
        return 1;
    while (isxdigit(*++endp) != 0)
        ;
    *p1 = endp + 1;

    switch (*endp) {
    case 'O':
    case 'Q':
    case 'o':
    case 'q':
        base = 8;
        val  = 0;
        break;

    case 'H':
    case 'h':
        base = 16;
        val  = 0;
        break;

    default:
        --(*p1);
        switch (digit = *(endp - 1)) {
        case 'D':
        case 'd':
            --endp;
        }
        base = 10;
        val  = 0;
        break;
    }
    while (startp != endp) {
        digit = *startp;
        if (base == 8 && digit > '7')
            return 1;
        if (base == 10 && digit > '9')
            return 1;
        val = val * base + (uint32_t)digit;
        if (isdigit(digit))
            val -= '0';
        else if (islower(digit))
            val -= 'a' - 10;
        else
            val -= 'A' - 10;
        ++startp;
    }
    *p2 = val;
    return 0;
}

/**************************************************************************
 59	setPsectOrigin	ok++ (PMO)
 **************************************************************************/
static void setPsectOrigin(register psect_t *pPsect) {

    if (pPsect->originSet)
        fatalErr("psect '%s' re-orged", pPsect->psectSym->name);
    if (!(pPsect->psectSym->flags & SF_GLOBAL)) {
        if (pPsect->align != 0) {
            linkPt += (pPsect->align - 1);
            linkPt &= ~(pPsect->align - 1L);
            loadPt += (pPsect->align - 1);
            loadPt &= ~(pPsect->align - 1L);
        }
        pPsect->linkPt = linkPt;
        pPsect->loadPt = loadPt;
        linkPt += pPsect->blkStartAddress;
        loadPt += pPsect->blkStartAddress;
    }
    if (pPsect->linkPt + pPsect->blkStartAddress > maxLinkPt)
        maxLinkPt = pPsect->linkPt + pPsect->blkStartAddress;
    pPsect->originSet = true;
}

/* link / load modes */
#define CALCULATE 1
#define EXPLICIT  2

/**************************************************************************
 60	finPass1	ok++ (PMO)
 One very minor code variance where the load order of a & hl is swapped.
 There is no impact on execution
 **************************************************************************/
void finPass1() {
    char buf[20];
    sym_t **pslot;
    psect_t *pinfo;
    psect_t *pp;
    char linkMode;
    char loadMode;
    char *psectSpec;
    char *s;
    char separator;
    register sym_t *ps = NULL; /* PMO: if not key_R then ps may be used uninitialised */

    loadPt        = 0;
    linkPt        = 0;
    maxLinkPt     = 0;
    if (!optR && psectLoc) {
        psectSpec = psectLoc;

        for (;;) {
            if (!*psectSpec) {
                simpleErr("bad '-p' format");
                break;
            }
            for (s = psectSpec; *s && *s != '=' && *s != ',' && *s != '/'; s++)
                ;

            separator = *s;
            *s        = '\0';
            if ((ps = getSymbol(psectSpec, SF_PSECT)) == 0 &&
                (ps = getSymbol(psectSpec, SF_CLASS)) == 0)
                fatalErr("unknown psect: %s", psectSpec);
            if (ps->flags & SF_ABS)
                simpleErr("psect is absolute: %s", psectSpec);

            pinfo = ps->p.pinfo;
            if (pinfo->originSet)
                fatalErr("psect origin multiply defined: %s", psectSpec);

            (psectSpec = s)[0] = separator; /* put back separator */

            if (pinfo->align != 0) {
                linkPt += (pinfo->align - 1);
                linkPt &= ~(pinfo->align - 1L);
                loadPt += (pinfo->align - 1);
                loadPt &= ~(pinfo->align - 1L);
            }
            linkMode = loadMode = CALCULATE;
            savLoadPt     = loadPt;
            if (separator == '=') {
                ++psectSpec;
                if (parseNum(&psectSpec, &linkPt) != 0) { /*  link address */
                    fatalErr("bad origin format in spec");
                    break;
                }
                loadPt = linkPt;
                linkMode    = EXPLICIT;
                if (*psectSpec != '/')
                    loadMode = EXPLICIT;
            }
            if (*psectSpec == '/') {
                loadMode = CALCULATE;
                ++psectSpec;
                if (parseNum(&psectSpec, &loadPt) != 0) /*  load address */
                    loadPt = savLoadPt;
                else
                    loadMode = EXPLICIT;
            }
            if (ps->flags & SF_PSECT) {
                pinfo->linkPt = linkPt;
                if (pinfo->align != 0 && (linkPt & (pinfo->align - 1)))
                    fatalErr("Psect %s not relocated on 0x%x boundary", pinfo->psectSym->name,
                             pinfo->align);

                if (maxLinkPt < (linkPt += pinfo->blkStartAddress))
                    maxLinkPt = linkPt;

                pinfo->loadPt = loadPt;
                if (pinfo->align != 0 && (loadPt & (pinfo->align - 1)))
                    fatalErr("Psect %s not loaded on 0x%x boundary ", pinfo->psectSym->name,
                             pinfo->align);

                loadPt += pinfo->blkStartAddress;
                pinfo->originSet = true;
            } else {
                for (pp = psectInfo; pp != nextPsect; pp++) {
                    if (pp->classSym == ps && !pp->originSet) {
                        if (linkMode == CALCULATE && pp->align != 0) {
                            linkPt += (pp->align - 1); /* align */
                            linkPt &= ~(pp->align - 1L);
                        }

                        pp->linkPt = linkPt;
                        if (pp->align != 0 && (linkPt & (pp->align - 1)))
                            fatalErr("Psect %s not relocated on 0x%x boundary", pp->psectSym->name,
                                     pp->align);

                        if (maxLinkPt < pp->blkStartAddress + linkPt)
                            maxLinkPt = pp->blkStartAddress + linkPt;

                        if (linkMode == CALCULATE)
                            linkPt += pp->blkStartAddress;

                        if (loadMode == CALCULATE && pp->align != 0) {
                            loadPt += (pp->align - 1); /* align */
                            loadPt &= ~(pp->align - 1L);
                        }

                        pp->loadPt = loadPt;
                        if (pp->align != 0 && (loadPt & (pp->align - 1)))
                            fatalErr("Psect %s not loaded on 0x%x boundary ", pp->psectSym->name,
                                     pp->align);

                        if (loadMode == CALCULATE)
                            loadPt += pp->blkStartAddress;
                        pp->originSet = true;
                    }
                }
            }
            if (*psectSpec == ',')
                psectSpec++;
            else {
                if (*psectSpec)
                    fatalErr("bad '-p' format");
                break;
            }
        }
    }

    for (pinfo = psectInfo; pinfo != nextPsect; pinfo++) {
        if (pinfo->maxSize != 0 && pinfo->maxSize < pinfo->blkStartAddress)
            simpleErr("psect exceeds max size: %s", pinfo->psectSym->name);

        if (optR) { /* write records to start each psect */
            if (!(pinfo->psectSym->flags & SF_CLASS)) {
                u32tob(pinfo->blkStartAddress, (uint8_t *)textRecBuf);
                strcpy((char *)textRecBuf + TEXT_PNAME, pinfo->psectSym->name);
                writeRec(TEXT_RECORD, (int)strlen((char *)textRecBuf + TEXT_PNAME) + TEXT_PNAME + 1,
                         textRecBuf);
            }
        } else {
            if (pinfo->originSet == 0 && pinfo->classSym == 0) {
                if (pinfo->psectSym->flags & SF_CLASS) {
                    for (pp = psectInfo; pp != nextPsect; ++pp)
                        if (!pp->originSet && pp->classSym == ps) /* ps potentially uninitialised */
                            setPsectOrigin(pp);
                } else
                    setPsectOrigin(pinfo);
            }

            if ((ps = pinfo->psectSym) != absSym) {
                if ((ps->flags & (SF_CLASS | SF_GLOBAL)) == SF_GLOBAL) {
                    sprintf(buf, "__L%s", ps->name); /* base address */
                    defineIfNeeded(buf, ps, 0, SF_GLOBAL);
                    buf[2] = 'H'; /* highest used address */
                    defineIfNeeded(buf, ps, pinfo->blkStartAddress, SF_GLOBAL);
                    if (pinfo->loadPt != pinfo->linkPt) {
                        buf[2] = 'B'; /* bias load - link */
                        defineIfNeeded(buf, ps, pinfo->loadPt - pinfo->linkPt, SF_GLOBAL);
                    }
                }
            }
        }
        pinfo->blkStartAddress = 0; /* reset for pass 2 */
    }
    if (!optR) {
        if (cntUnresolved != 0 && !optI)
            simpleErr("undefined symbol%c:", (cntUnresolved == 1) ? '\0' : 's');

        /* update all of the symbol values to reflect final locations */
        for (pslot = symTab; &symTab[MAX_SYMBOLS] != pslot; ++pslot) {
            if ((ps = *pslot) && !(ps->flags & (SF_PSECT | SF_CLASS))) {
                if (LowFlags(ps->flags) == SF_EXTERN) {
                    if (!optI)
                        simpleErr("%s", ps->name);
                } else if (!(ps->psectSym->flags & SF_ABS) && LowFlags(ps->flags) != SF_COMM)
                    ps->p.value += ps->psectSym->p.pinfo->linkPt;
            }
        }
    }
    if (optS)
        return;

    for (pslot = symTab; &symTab[MAX_SYMBOLS] != pslot; ++pslot) {
        if ((ps = *pslot)) {
            if (ps->flags & SF_PSECT) {
                if (!optC) {
                    wrRecord();
                    nonTextRecBuf[RECORD_TYPE] = PSECT_RECORD;

                    u16tob((ps->flags & 0x7fff) | (optR ? 0 : SF_ABS), nonTextRecPtr);

                    strcpy((char *)nonTextRecPtr + PSECT_PNAME, ps->name);
                    nonTextRecPtr += (strlen(ps->name) + PSECT_PNAME + 1);
                };
            } else if (!(ps->flags & SF_CLASS) && (!optX || (ps->flags & SF_GLOBAL)) &&
                       (!optZ || !isLocalName(ps->name)))
                wrSymbol(ps);
        }
    }
    if (optH)
        fprintf(symFp, "%%locals\n");
}

/**************************************************************************
 61	finPass2	ok++ (PMO)
 **************************************************************************/

void finPass2() {

    flushText();
    wrRecord();
    if (!optR && !optC) {
        if (haveEntryPt == 0) {
            warning("no start record: entry point defaults to zero");
            u32tob(0, recbuf + START_OFFSET);
            recbuf[START_PNAME] = 0;
            writeRec(START_RECORD, 5, recbuf);
        }
    }

    u16tob(0, recbuf);
    if (!optC)
        writeRec(END_RECORD, 2, recbuf); /* PMO - note doesn't write the 0 for PSECT name !!*/
    if (optM == 0)
        return;
    prSymMap(); /*  Write a link map */
}

/**************************************************************************
 62	wrSymbol	ok++ (PMO)
 optimiser uses marginally better code (1 byte less) for the calculation in final strcpy
 **************************************************************************/
static void wrSymbol(register sym_t *ps) {
    sym_t *psectSym;
    char *symName;
    char *psectName;
    size_t len;

    symName   = ps->name;
    psectName = (psectSym = ps->psectSym) ? psectSym->name : "";

    if (symFileName)
        prSymbol(symName, ps->p.value, SF_NULL, psectSym);

    if (optC)
        return;
    /* write to the object file */
    len = SYM_PNAME + strlen(symName) + 1 + strlen(psectName) + 1;

    chkAddRecordItem(SYM_RECORD, len);                    /* make enough room */
    u32tob(ps->p.value, nonTextRecPtr + SYM_VALUE);       /* save the value */
    u16tob(ps->flags, nonTextRecPtr + SYM_FLAGS);         /* and the flags */
    strcpy((char *)nonTextRecPtr + SYM_PNAME, psectName); /* psect name & symbol name */
    strcpy(strlen(psectName) + SYM_PNAME + 1 + (char *)nonTextRecPtr, symName);
    nonTextRecPtr += len; /* undate for next entry */
}

/**************************************************************************
 63	isLocalName	ok++ (PMO)
 * locals generated by the compiler of form
 * [klfFLS] \d*
 **************************************************************************/
static char isLocalName(register char *name) {

    if (strchr("klfFLS", *name) == 0)
        return 0;

    while (isdigit(*++name))
        ;
    return *name == 0;
}

/**************************************************************************
 64	prPsectMap	ok++ (PMO)
 **************************************************************************/
static void prPsectMap() {
    uint32_t addr;
    int nCols, col;
    register psect_t *pp;

    if (strlen(objFileName) < 16)
        printf("%-16.15s", objFileName); /* print name obj file */
    else
        printf("%s\n%16s", objFileName, "");

    col          = 0;
    nCols        = (width - 10) / 32;
    absSym->name = "(abs)"; /* for printing */

    for (pp = psectInfo; pp != nextPsect; ++pp) {
        if (pp->endAddr != 0) {
            if (pp->psectSym->flags & SF_OVRLD)
                addr = 0;
            else
                addr = pp->blkStartAddress;
            if (!optR)
                addr += pp->linkPt;
            if (nCols < ++col) {
                printf("\n\t\t");
                col = 1;
            } else if (col > 1)
                fputc('\t', stdout);
            printf("%-8.8s %8" PRIx32 " %8" PRIx32, pp->psectSym->name, addr, pp->endAddr);
        }
    }
    fputc('\n', stdout);
    absSym->name = ""; /* revert */
}

/**************************************************************************
 65	output_summary	sub_36f3h	ok++ (PMO)
 **************************************************************************/
static void prSummary(register psect_t *pPsect) {

    printf("\t\t%-8.8s ", pPsect->psectSym->name); /* Name   */

    if (optR != 0) { /* Link   */
        printf("%8c", 0x20);
    } else {
        printf("%8" PRIx32, pPsect->linkPt);
    }
    printf(" %8" PRIx32, pPsect->loadPt);          /* Load   */
    printf(" %8" PRIx32 "\n", pPsect->blkStartAddress); /* Length */
}

/**************************************************************************
 66	prSymMap	sub-3773	ok++ (PMO)
 **************************************************************************/
static void prSymMap() {
    sym_t **pSlot;
    psect_t *pPsect;
    psect_t *pClass;
    uint8_t n;
    uint8_t symColWidth;
    uint8_t nCol; /* number of columns to print */
    uint8_t psectColWidth;
    register sym_t *ps;

    /* 997 */
    qsort(symTab, MAX_SYMBOLS, sizeof(symTab[0]), symCmp);
    absSym->name = "(abs)"; /* for printing use (abs) rather than "" */
    for (pSlot = symTab, symColWidth = 0, psectColWidth = 0; (ps = *pSlot); pSlot++) {
        n = (uint8_t)strlen(ps->name);
        if ((ps->flags & 0xC000)) {
            if (psectColWidth < n)
                psectColWidth = n;
        } else if (symColWidth < n)
            symColWidth = n;
    }
    fputc('\n', stdout);

    printf("TOTAL\t\tName         Link     Load   Length\n");
    for (pPsect = psectInfo, n = 0; pPsect != nextPsect; pPsect++, n++) {
        if (pPsect->classSym == 0) {
            if (pPsect->psectSym->flags & SF_CLASS) {
                printf("\tCLASS.%-8.8s\n", pPsect->psectSym->name);
                for (pClass = psectInfo; pClass != nextPsect; ++pClass) {
                    if (pClass->classSym == pPsect->psectSym)
                        prSummary(pClass);
                }
                fputc('\n', stdout);
            } else
                prSummary(pPsect);
        }
    }
    fputc('\n', stdout);

    for (n = (width - 12) / 2; 0 < n; n--)
        fputc(' ', stdout);

    printf("%s\n\n", "Symbol Table");
    nCol  = width / (symColWidth + psectColWidth + 8);
    pSlot = symTab;

    for (n = 0; (ps = *pSlot); pSlot++) {
        if ((ps->flags & 0xC000) == 0) {
            printf("%-*s", symColWidth, ps->name);
            if ((ps->flags & 0xF) == SF_EXTERN)
                printf("%*c", psectColWidth + 6, ' ');
            else
                printf(" %-*s %04X", psectColWidth, ps->psectSym->name, ps->p.value);
            if (++n >= nCol) {
                n = 0;
                fputc('\n', stdout);
            } else
                printf("  ");
        }
    }
    if (n != 0)
        fputc('\n', stdout);
    absSym->name = ""; /* revert to "" */
}

/**************************************************************************
 67	compare_fun	sub_3a5b	ok++ (PMO)
 **************************************************************************/
static int symCmp(const void *p1, const void *p2) {
    register const sym_t *ps1;
    const sym_t *ps2;

    ps1 = *(const sym_t **)p1;
    ps2 = *(const sym_t **)p2;

    if (ps2 == ps1)
        return 0;
    if (ps1 == 0)
        return 1;
    if (ps2 == 0)
        return -1;
    if (optN != 0) { /* Sort symbols by address */
        if ((ps1->flags & 0xC000) == 0 && (ps2->flags & 0xC000) == 0) {
            if (ps1->p.value != ps2->p.value) {
                if (ps1->p.value >= ps2->p.value)
                    return 1;
                return -1;
            } /* if equal sort by name below */
        }
    }

    return strcmp(ps1->name, ps2->name);
}