/*
 * File created 14.11.2021, last modified 01.01.2022
 *
 * The c.c file is part of the restored LINK.COM program
 * from the Hi-Tech C compiler v3.09 package.
 *
 *	Andrey Nikitin	01.01.2022
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#if CPM
#include <sys.h>
#endif

#include "link.h"

/**************************************************************************
 28	visitSymbols	sub_0bc9h	ok++ (PMO)
 as all actions use type as a uint8_t, the prototype now reflects this
 as a result the optimiser doesn't load the high byte of type
 **************************************************************************/
void visitSymbols(vsfuncptr action) {
    char moduleBuf[100];
    int cnt, type;

    for (cnt = symCnt; cnt != 0; --cnt) {
        if ((type = fgetc(libraryFp)) == -1)
            unexp_eof();
        readName(moduleBuf);
        action(moduleBuf, type); /* <- chkModuleNeeded(char * offset, int relocType) */
    }
}

/**************************************************************************
 29	readName	sub_0c2eh	ok++ (PMO)
 **************************************************************************/
void readName(register char *p1) {
    int l1;

    do {
        if ((l1 = fgetc(libraryFp)) == -1)
            unexp_eof();
        *(p1++) = l1;
    } while (l1 != 0);
}

/**************************************************************************
 30	unexp_eof	sub_0c62h	ok++
 **************************************************************************/
void unexp_eof() {

    badFormat("unexpected end of file");
}

/**************************************************************************
 31	main		sub_0c6b	ok++ (PMO)
 **************************************************************************/
int main(int argc, char **argv) {
    char *pOption;
#ifndef CPM
    moduleFp = stdin;
#endif
#if CPM
    if (argc == 1) {
        argv = _getargs(0, "link");
        argc = _argc_;
    }
#endif
    for (--argc, ++argv; argc != 0 && **argv == '-'; --argc, ++argv) {

        pOption = *argv + 1; /* m2: */
        while (*pOption) {
            switch (*pOption++) { /* m5: */
            case 'R':
            case 'r':      /* Leave the output relocatable */
                key_R = 1; /* m7: */
                break;

            case 'L':
            case 'l':                       /* Retain absolute relocation info */
                if ((*pOption == 'm')       /* m8: */
                    || (*pOption == 'M')) { /* Will retain only segement relocation */
                    key_LM = 1;             /* information				/* m9: */
                    pOption++;              /* m10: */
                    break;
                }
                key_L = 1; /*m11: */
                break;

            case 'N':
            case 'n':      /* Sort symbols by address */
                key_N = 1; /* m12: */
                break;

            case 'C':
            case 'c':                     /* Produce a binary output file offset */
                key_C = 1; /* by value */ /* m13: */
                parseLongVal(&pOption, &offset_address);
                break; /* m14: */

            case 'S':
            case 's':      /* Strip symbol information from output file */
                key_S = 1; /* m15: */

            case 'X':
            case 'x':      /* Suppress local symbols in output file */
                key_X = 1; /* m16: */

            case 'Z':
            case 'z': /* Suppress trivial (compiler-generated) */
                key_Z = 1; /* symbols in theoutput file */ /* m17: */
                break;

            case 'O':
            case 'o':                  /* Call output file name */
                if (fname_outp == 0) { /* m18: */
                    if (*pOption != 0) {
                        fname_outp = pOption;
                        pOption    = "";
                        break;
                    }
                }
                fatal_err("Illegal -o flag"); /* m19: */
                break;

            case 'P':
            case 'p':                      /* Spec is a psectSym location specification */
                if (psect_location == 0) { /* m21: */
                    if (*pOption != 0) {
                        psect_location = pOption;
                        pOption        = "";
                        break;
                    }
                }
                fatal_err("Illegal -p flag"); /* m22: */
                break;

            case 'M':
            case 'm':                 /* Write a link map to the file name */
                if (fname_map == 0) { /* m23: */
                    key_M     = 1;
                    fname_map = pOption;
                    pOption   = "";
                    break;
                }
                fatal_err("Duplicate -m flag"); /* m24: */
                break;

            case 'U':
            case 'u':                /* Make symbol initially undefined */
                if (*pOption != 0) { /* m25: */
                    addSym(pOption, 0x10);
                    pOption = "";
                    break;
                }
                fatal_err("Missing arg to -u"); /* m26: */
                break;

            case 'H':
            case 'h':
                key_H = 1; /* m27: */

            case 'D':
            case 'd':               /* Write a symbol file */
                if (fname_sym != 0) /* m28: */
                    fatal_err("Duplicate -d flag");
                if (*pOption != 0)
                    fname_sym = pOption;
                else
                    fname_sym = "l.sym"; /* m30: */
                pOption = "";            /* m31: */
                break;

            case 'W':
            case 'w':                         /* Specify map width */
                if (isdigit(*pOption) != 0) { /* m32: */
                    width   = atoi(pOption);
                    pOption = "";
                    break;
                }
                fatal_err("Missing arg to -w"); /* m33: */
                break;

            case 'I':
            case 'i':      /* Ignore undefined symbols */
                key_I = 1; /* m34: */
                break;
            default:
                fatal_err("Illegal flag %c\n%s", *(pOption - 1), usageMsg); /* m35: */
                break;
            } /* end switch */
        }     /* end pOption while */
    }         /* end argc while */

    if (key_C && (key_R || key_L)) {
        fprintf(stderr, "-c illegal with -r or -l"); /* m38: */
        exit(1);
    }
    if (argc == 0)
        fatal_err(usageMsg); /* m39: */
    create_symtab();         /* m40: */
    if (fname_outp == 0)     /* Assign default output file name */
        if (key_C)
            fname_outp = "l.bin";
        else
            fname_outp = "l.obj";

    outFp = fopen(fname_outp, "wb"); /* m42: */
    if (outFp == 0)
        fatal_err("%s: Can't create", fname_outp);
    if (key_M && *fname_map && freopen(fname_map, "w", stdout) == 0)
        fatal_err("%s: Can't create", fname_map);

    if (fname_sym != 0) { /* m44: */
        if ((symFp = fopen(fname_sym, "w")) == 0)
            fatal_err("%s: Can't create", fname_sym);
    }
    absSym        = addSym("", SF_PSECT | 0xD0); /* m45: */
    num_lib_files = 0;
    for (curFileId = 0; argc != curFileId; ++curFileId) { /* m48: */
        if (is_library(argv[curFileId]) != 0)
            ++num_lib_files;
    }
    allocModuleArrays(num_lib_files);
    for (linker_pass = 0; linker_pass < 2; ++linker_pass) {               /* m56: */
        num_lib_files = 0;                                                /* m49: */
        for (curFileId = 0; curFileId < argc; ++curFileId) {              /* m54: */
            if (freopen((fname_obj = argv[curFileId]), "rb", stdin) == 0) /* m50: */
                fatal_err("%s: Can't open", fname_obj);
            if (is_library(fname_obj) != 0) { /* lib file */ /* m51: */
                openLibrary();
                ++num_lib_files;
            } else
                doObjFile(); /* m52: */
            fname_obj = 0;   /* m53: */
        }                    /*    / finPass1 */
        (finPassHandler[linker_pass])();
        if (err_num != 0)
            exit(1); /*    \ finPass2 */
    }
    exit(0);
} /* End main */

/**************************************************************************
 32	doObjFile	ok++ (PMO)
 **************************************************************************/
void doObjFile() {
    do {
        readRecHdr();
        (recHandler[rectyp][linker_pass])();
    } while (rectyp != END_RECORD);
    numRecord = 0;
    fname_obj = 0;
}

/**************************************************************************
 33	sub-10a3h	ok++ (PMO)
 **************************************************************************/
void skipRecData() {

    readRecData(recbuf);
}

/**************************************************************************
 34	is_library	sub_10ach	ok++ (PMO)
 **************************************************************************/
char is_library(char *p1) {

    return (p1 = strrchr(p1, '.')) && (strcmp(p1, ".lib") == 0 || strcmp(p1, ".LIB") == 0);
}

#ifdef CPM
/* original non stdarg functions */

/**************************************************************************
 35	err_message	sub_10fdh	ok++ (PMO)
 **************************************************************************/
void err_message(p1, p2, p3, p4, p5) char *p1;
{

    fflush(stdout);

    if (libraryName)
        fprintf(stderr, "%s: ", libraryName);
    if (fname_obj)
        fprintf(stderr, "%s: ", fname_obj);
    if (numRecord != 0)
        fprintf(stderr, "%d: ", numRecord);

    fprintf(stderr, p1, p2, p3, p4, p5);
    fputc('\n', stderr);
}

/**************************************************************************
 36	fatal_err	sub_1187h	ok++ (PMO)
 **************************************************************************/
void fatal_err(p1, p2, p3, p4, p5) {

    err_message(p1, p2, p3, p4, p5);
    exit(1);
}

/**************************************************************************
 37	simpl_err	sub_11bfh	ok++ (PMO)
 **************************************************************************/
void simpl_err(p1, p2, p3, p4, p5) {

    err_message(p1, p2, p3, p4, p5);
    ++err_num;
}

/**************************************************************************
 38	warning		sub_11f2h	ok++ (PMO)
 **************************************************************************/
void warning(p1, p2, p3, p4, p5) char *p1;
{

    fprintf(stderr, p1, p2, p3, p4, p5);
    fprintf(stderr, " (warning)\n");
}

/**************************************************************************
 39	badFormat	sub_1232h	ok++ (PMO)
 **************************************************************************/
void badFormat(p1, p2, p3, p4, p5) {

    err_message("bad object code format");
    fatal_err(p1, p2, p3, p4, p5);
}

#else
/**************************************************************************
 shared err_message using va_list
 **************************************************************************/
static void verrMsg(char const *fmt, va_list args) {

    fflush(stdout);

    if (libraryName)
        fprintf(stderr, "%s: ", libraryName);
    if (fname_obj)
        fprintf(stderr, "%s: ", fname_obj);
    if (numRecord != 0)
        fprintf(stderr, "%d: ", numRecord);

    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
}

void err_message(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    verrMsg(fmt, args);
    va_end(args);
}

/**************************************************************************
 36	fatal_err	sub_1187h	ok++ (PMO)
 **************************************************************************/
_Noreturn void fatal_err(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    verrMsg(fmt, args);
    va_end(args);
    exit(1);
}

/**************************************************************************
 37	simpl_err	sub_11bfh	ok++ (PMO)
 **************************************************************************/
void simpl_err(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    verrMsg(fmt, args);
    va_end(args);
    ++err_num;
}

/**************************************************************************
 38	warning		sub_11f2h	ok++ (PMO)
 **************************************************************************/
void warning(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, " (warning)\n");
    va_end(args);
}


/**************************************************************************
 39	badFormat	sub_1232h	ok++ (PMO)
 **************************************************************************/
void badFormat(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    err_message("bad object code format");
    verrMsg(fmt, args);
    va_end(args);
    exit(1);
}
#endif

/**************************************************************************
 40	xalloc	sub_1265h	ok++
 **************************************************************************/
void *xalloc(size_t p1) {
    register char *st;

    if ((st = malloc(p1)) == 0)
        fatal_err("Cannot get memory");
    clrbuf(st, p1);
    return st;
}

/**************************************************************************
 41	clrbuf	ok++ (PMO)
 **************************************************************************/
void clrbuf(register char *st, size_t p2) {

    if (p2 == 0)
        return;
    *st = 0;
    if (--p2 == 0)
        return;
    bmove(st, st + 1, p2); /* use bmove to copy 0 to remaining locations*/
}

/*
 *	Relocation type
 */
#define RelocType(n)  ((n)&0xf0)
#define RelocSize(n)  ((n)&0xf)

#define RELOCBASEMASK 0x30

#define RABS          0x00          /* Absolute - no relocation (i.e. no change)     */
#define RPSECT        0x10          /* Relocation within named psect                 */
#define RNAME         0x20          /* Relocation by value of name                   */
#define RR            0x40          /* psect relative */
#define RRPSECT       (RR | RPSECT) /* Relocation within psect, less the current pc  */
#define RRNAME        (RR | RNAME) /* As for RRPSECT, but relative to a symbol rather than a psect */
#define RS            0x80         /* segment relative */
#define RSPSECT       (RS | RPSECT) /* Relocation by the segment value for the psect  */
#define RSNAME        (RS | RNAME)  /* Relocation by the segment value for the symbol */

/**************************************************************************
 42	sub_12d2	relocRecPass1	ok++ (PMO)
 **************************************************************************/
void relocRecPass1() {
    char *name; /* Psect or external name      */
    register uint8_t *s;

    readRecData(recbuf); /* Read RELOC record to recbuf */

    for (s = recbuf; s < recbuf + length; s += strlen(name) + RELOC_NAME + 1) {
        name = (char *)s + RELOC_NAME;
        if (RelocType(s[RELOC_TYPE]) == RNAME || RelocType(s[RELOC_TYPE]) == RRNAME)
            addSym(name, SF_GLOBAL);
    }
}

/**************************************************************************
 43	relocRecPass2	ok++ (PMO)
 3 minor differences as chkAddRecordItem 1st param is uint8_t and compiler
 doesn't load high byte
 1 instance of benign code differences
 original ex de,hl | ld (ix-4),e | ld (ix-3),d | ld hl,8
 new      ld (ix-4),l | ld (ix-3),h | ex de,hl | ld hl,8
 **************************************************************************/
void relocRecPass2() {
    uint8_t *rp; /* Pointer relocation information field */
    sym_t *ps;
    char *name; /* Psect or external name              */
    size_t len; /* Length relocation information field */
    uint16_t offset;
    uint32_t relocatability;
    uint8_t reloc_type; /* Relocation type */
    register psect_t *pp;

    readRecData(recbuf); /* Read RELOC record to recbuf */

    for (rp = recbuf; rp < (recbuf + length);
         rp += strlen((char *)rp + RELOC_NAME) + RELOC_NAME + 1) {
        name      = (char *)rp + RELOC_NAME;
        fixupName = name;
        offset    = (uint16_t)conv_letoi16(rp);

        if (offset >= textLen)
            badFormat("relocation offset %d out of range 0..%d-%d-1", offset, textLen,
                      textRecPtr - textRecBuf);

        reloc_type = rp[RELOC_TYPE];

        if (key_R) {
            if ((reloc_type & RELOCBASEMASK) == RNAME) {
                ps = addSym(name, 0);
                if (LowFlags(ps->flags) != SF_EXTERN) {
                    /* convert to PSECT relative */
                    reloc_type = (reloc_type & ~RELOCBASEMASK) | RPSECT;
                    fixupName = name = ps->psectSym->name;
                    /* calc length of psect reloc record */
                    len = RELOC_NAME + strlen(name) + 1;
                    chkAddRecordItem(RELOC_RECORD, len);

                    /* adjust offset for data already written from this block
                     * and convert delta account for the psect start. This is
                     * written to the reloc file for final fixup
                     * the adjustment for to account for psect relative is done
                     * below
                     */
                    fixup(offset - alreadyWritten, reloc_type,
                          ps->p.value - addSym(name, SF_PSECT)->p.pinfo->blkStartAddress);
                }
            }

            len = RELOC_NAME + strlen(name) + 1;
            chkAddRecordItem(RELOC_RECORD, len);

            offset -= alreadyWritten;           /* ajust for already written text */
            conv_u16tob(offset, nonTextRecPtr); /* save offset in record */

            nonTextRecPtr[RELOC_TYPE] = reloc_type;
            strcpy((char *)nonTextRecPtr + RELOC_NAME, name);
            nonTextRecPtr += len;

            switch (RelocType(reloc_type)) { /* type */
            default:
                badFormat("illegal relocation type: %02x", reloc_type);
                break;

            case RABS:
            case RNAME:
            case RRNAME:
            case RS:
            case RSPSECT:
            case RSNAME:
                fixup(offset, reloc_type, 0); /* doesn't change but updates end marker */
                break;

            case RPSECT:
            case RR:
            case RRPSECT:
                fixup(offset, reloc_type, addSym(name, SF_PSECT)->p.pinfo->blkStartAddress);
                break;
            }
        } else {

            if (key_L || key_LM)
                chkAddRecordItem(RELOC_RECORD, RELOC_NAME + 1); /* item with name set to "" */

            offset -= alreadyWritten;

            switch (RelocType(reloc_type)) {

            default:
                badFormat("illegal relocation type: %02x", reloc_type);
                break;

            case RABS:
            case RS:
                ps = 0; /* no name */
                fixup(offset, reloc_type, 0);
                break;

            case RR:
            case RRPSECT:
                pp = (ps = addSym(name, SF_PSECT))->p.pinfo;
                fixup(offset, reloc_type,
                      0 - textBaseAddress - (uint32_t)offset + pp->linkAddress +
                          pp->blkStartAddress);
                break;

            case RPSECT:
                pp = (ps = addSym(name, SF_PSECT))->p.pinfo;
                fixup(offset, reloc_type, pp->linkAddress + pp->blkStartAddress);
                break;

            case RSPSECT:
                pp             = (ps = addSym(name, SF_PSECT))->p.pinfo;
                relocatability = pp->align;
                if (relocatability == 0)
                    relocatability = 1;
                if (ps->flags & SF_BIGSEG)
                    relocatability <<= 16;
                fixup(offset, reloc_type, (pp->loadAddress - pp->linkAddress) / relocatability);
                break;

            case RRNAME:
                fixup(offset, reloc_type,
                      0 - textBaseAddress - (uint32_t)offset +
                          (ps = addSym(name, 0))->p.value); /* m22: */
                ps = ps->psectSym;
                break;

            case RNAME:
                ps = addSym(name, 0);
                fixup(offset, reloc_type, ps->p.value);
                ps = ps->psectSym;
                break;

            case RSNAME:
                pp             = (ps = addSym(name, 0)->psectSym)->p.pinfo; /* m25: */
                relocatability = pp->align;
                if (relocatability == 0)
                    relocatability = 1;
                if (ps->flags & SF_BIGSEG)
                    relocatability <<= 0x10;
                fixup(offset, reloc_type, (pp->loadAddress - pp->linkAddress) / relocatability);
                break;
            }
            if ((key_L && !(reloc_type & RS)) || (key_LM && (reloc_type & RS)))
                if (ps && !(ps->flags & SF_ABS)) {
                    conv_u16tob(offset, nonTextRecPtr); /* reloc item offset */
                    nonTextRecPtr[RELOC_TYPE] = reloc_type & (SF_ABS | SF_LOWMASK);
                    strcpy((char *)nonTextRecPtr + RELOC_NAME, ps->name);
                    nonTextRecPtr += (strlen(ps->name) + RELOC_NAME + 1);
                }
        }
    } /* m29: */
}

/**************************************************************************
 44	fixup	ok++ (PMO)
 code same except that the BB block after the switch is moved to earlier
 in the code image
 **************************************************************************/
void fixup(int offset, uint16_t relocType, uint32_t delta) {
    uint32_t nval;
    uint32_t nmask;
    uint8_t *fixloc;

    fixloc  = offset + curAddr;
    endAddr = fixloc + RelocSize(relocType);

    switch (RelocSize(relocType)) {
    case 1:
        nval  = delta + *fixloc;
        nmask = 0xff;
        *fixloc += (uint8_t)delta;
        break;
    case 2:
        nval  = delta + (long)conv_letoi16(fixloc);
        nmask = 0xffff;
        conv_u16tob((uint8_t)nval, fixloc);
        break;
    case 3:
        nval = delta + conv_btou24(fixloc);
        conv_u24tob(nval, fixloc);
        nmask = 0xffffff;
        break;

    case 4:
        conv_u32tob(delta + conv_btou32(fixloc), fixloc);
        return;
    default:
        badFormat("illegal relocation size: %02x", relocType);
        return;
    }
    if ((~nmask & nval) == 0 || (nval | nmask) == -1L) /* check overflow */
        return;
    simpl_err("Fixup overflow referencing %s %s", (relocType & RNAME) ? "symbol" : "psect",
              fixupName);
}

/**************************************************************************
 45	create_symtab	sub-1af4h	ok++ (PMO)
 **************************************************************************/
void create_symtab() {

    symbol_table = (sym_t **)xalloc(SIZE_SYMTAB);
}

/**************************************************************************
 46	getSymbolSlot	ok++ (PMO)
 **************************************************************************/
sym_t **getSymbolSlot(char *symbol_name, int flags) {
    sym_t **startp;
    sym_t **testp;
    uint16_t hashval;
    uint8_t *puc;
    register sym_t *ps;

    for (hashval = 0, puc = (uint8_t *)symbol_name; *puc != 0; puc++)
        hashval += *puc;
    startp = symbol_table + (hashval % MAX_SYMBOLS);
    flags &= 0xC000;
    testp = startp;
    while (ps = *testp) {
        if ((ps->flags & 0xC000) == flags) {
            if ((ps->flags & SF_GLOBAL) || ps->fileId == curFileId || key_R)
                if (strcmp(ps->name, symbol_name) == 0)
                    break;
        }
        if (++testp == &symbol_table[MAX_SYMBOLS])
            testp = symbol_table;
        if (testp == startp)
            fatal_err("Too many symbols");
    }
    return testp;
}

/**************************************************************************
 47	getSymbol	ok++ (PMO)
 **************************************************************************/
sym_t *getSymbol(char *symbol_name, int flags) {

    return *getSymbolSlot(symbol_name, flags);
}

/**************************************************************************
 48	addSym	ok++ (PMO)
 **************************************************************************/
sym_t *addSym(char *symbol_name, int flags) {
    sym_t **slot;
    register sym_t *ps;

    slot = getSymbolSlot(symbol_name, flags);
    ps   = *slot;

    if (ps == 0) {
        ++newSymCnt;
        *slot = ps = xalloc(sizeof(sym_t));
        ps->name   = xalloc(strlen(symbol_name) + 1);
        strcpy(ps->name, symbol_name);
        ps->fileId = (uint8_t)curFileId;

        if ((flags & 0xC000) == 0) {
            ++cntUnresolved;
            ps->flags = SF_EXTERN;
        } else {
            if (nextPsect == psectInfo + MAX_PSECTS)
                fatal_err("Too many psects");
            nextPsect->psectSym = ps; /* m2: */
            ps->p.pinfo         = nextPsect++;
        }
    }
    ps->flags |= (flags & 0xFFF0);
    return ps;
}

/**************************************************************************
 49	prSymbol	ok++ (PMO)

 **************************************************************************/
void prSymbol(char *symbol_name, uint32_t value, int lflag, register sym_t *psectSym) {

    if (!key_H) {
        if (lflag != 0)
            return;
        fprintf(symFp, "%4.4lx %s\n", value, symbol_name);
        return;
    }

    switch (lflag) {
    case SF_REGNAM:
        fprintf(symFp, "%s reg %lx\n", symbol_name, value);
        return;

    case SF_FILNAM:
        fprintf(symFp, "%s\n", symbol_name);
        return;

    case SF_STACK:
        fprintf(symFp, "%s stk %ld\n", symbol_name, value);
        return;
    }

    fprintf(symFp, "%s %lx", symbol_name, value);
    if (psectSym != 0)
        fprintf(symFp, " %lx", psectSym->p.pinfo->loadAddress - psectSym->p.pinfo->linkAddress);
    fputc('\n', symFp);
    return;
}

/**************************************************************************
 50	symRecPass2	ok++ (PMO)
 minor optimisation on type parameter for chkAddRecordItem
 **************************************************************************/
void symRecPass2() {
    uint32_t value;
    uint8_t *ptr_sym;  /* ptr to sym record   */
    char *psect_name;  /* psectSym name       */
    char *symbol_name; /* symbol name         */
    sym_t *psectSym;   /* ptr to psect symbol */
    uint16_t flag;     /* flags               */
    uint16_t lflag;    /* low flags           */
    size_t len;        /* sub record length   */

    readRecData(recbuf); /*  Read SYM record to recbuf */

    for (ptr_sym = recbuf; recbuf + length > ptr_sym; ptr_sym += len) {
        flag        = (uint16_t)conv_letoi16(ptr_sym + 4);
        lflag       = LowFlags(flag);
        symbol_name = (psect_name = (char *)ptr_sym + SYM_PNAME);

        while (*symbol_name++) /* Skip psectSym name */
            ;

        len      = SYM_PNAME + strlen(psect_name) + 1 + strlen(symbol_name) + 1;
        psectSym = *psect_name ? addSym(psect_name, SF_PSECT) : (sym_t *)0;
        value    = conv_btou32(ptr_sym);

        switch (lflag) {
        case SF_NULL:
            if (flag & SF_GLOBAL)
                break;

        case SF_LINENO:
            if (psectSym != 0) {
                if (!(psectSym->flags & SF_OVRLD))
                    value += psectSym->p.pinfo->blkStartAddress;
                if (!key_R)
                    value += psectSym->p.pinfo->linkAddress;
            }
            conv_u32tob(value, (uint8_t *)ptr_sym); /* m9: */

        case SF_STACK:
        case SF_REGNAM:
        case SF_FILNAM:
            if (key_X || (key_Z && isLocalName(symbol_name)))
                break;

            if (fname_sym)
                prSymbol(symbol_name, value, lflag, psectSym);

            if (!key_C) {
                chkAddRecordItem(SYM_RECORD, len);
                bmove(ptr_sym, nonTextRecPtr, len);
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
    uint32_t value;
    uint8_t *ptr_sym;  /*  ptr to sym record    */
    char *psect_name;  /*  psect name           */
    char *symbol_name; /*  symbol name          */
    sym_t *psectSym;   /*  ptr to symbol table  */
    uint16_t flags;    /*  flags                */
    uint16_t lflags;   /*  low flags            */
    size_t symdefLen;  /*  length of symbol def */

    readRecData(recbuf); /*  Read SYM record to recbuf */

    for (ptr_sym = recbuf; ptr_sym < recbuf + length; ptr_sym += symdefLen) {
        flags       = (uint16_t)conv_letoi16(ptr_sym + SYM_FLAGS);
        lflags      = flags & 0xF;
        symbol_name = psect_name = (char *)ptr_sym + SYM_PNAME;

        while (*symbol_name++ != 0) /* skip psectSym name */
            ;

        symdefLen = SYM_PNAME + strlen(psect_name) + 1 + strlen(symbol_name) + 1;
        psectSym  = lflags == SF_NULL ? addSym(psect_name, SF_PSECT) : (sym_t *)0;
        value     = conv_btou32(ptr_sym + SYM_VALUE);

        switch (lflags) {
        case SF_EXTERN:
            addSym(symbol_name, flags | SF_GLOBAL); /* will add if not already present */
            break;

        case SF_NULL:
            if (!(flags & SF_GLOBAL)) /* skip local define names */
                break;

        case SF_COMM:
            defineSym(symbol_name, psectSym, value, flags);
            break;

        case SF_STACK:
        case SF_REGNAM:
        case SF_LINENO:
        case SF_FILNAM:
            if (flags & SF_GLOBAL)
                simpl_err("symbol %s cannot be global", symbol_name);
            break;
        }
    }
}

/**************************************************************************
 52	defineSym	ok++
 **************************************************************************/
void defineSym(char *symbol_name, sym_t *psectSym, uint32_t value, int flags) {
    uint8_t slflag, lflag;
    register sym_t *ps;

    ps = addSym(symbol_name, flags);
    ps->flags |= flags & 0xFFF0; /* merge high flags */
    slflag = ps->flags & 0xF;    /* current symbol low flags*/
    lflag  = flags & 0xF;
    if (slflag == SF_COMM) {
        if (lflag != SF_COMM)
            simpl_err("common symbol conflict: %s", symbol_name);
        else if (ps->p.value < value)
            ps->p.value = value;
    } else if (slflag == SF_EXTERN) {
        --cntUnresolved; /* symbol now resolved */
        ps->p.value  = value;
        ps->psectSym = psectSym;
        if (lflag != SF_COMM && !(psectSym->flags & SF_OVRLD))
            ps->p.value += psectSym->p.pinfo->blkStartAddress;

        ps->flags = (ps->flags & 0xFFF0) | lflag; /* update low flags */
    } else
        simpl_err("multiply defined symbol: %s", symbol_name);
}

/**************************************************************************
 53	defineIfNeeded	ok++ (PMO)
 **************************************************************************/
void defineIfNeeded(char *symbol_name, sym_t *psectSym, uint32_t value, int flags) {
    register sym_t *ps;

    if ((ps = getSymbol(symbol_name, flags)) && LowFlags(ps->flags) != SF_EXTERN)
        return;
    defineSym(symbol_name, absSym, value, flags);
    addSym(symbol_name, flags)->psectSym = psectSym;
}

/**************************************************************************
 54	psectRecPass1	ok++ (PMO)
 optimiser changes ld a,h | or 80h | ld h,a with set 7,h
 **************************************************************************/
void psectRecPass1() {
    uint16_t psect_flag;
    register sym_t *ps;

    readRecData(recbuf); /* Read PSECT record to recbuf */

    psect_flag = (uint16_t)conv_letoi16(recbuf + PSECT_FLAGS) | SF_PSECT;
    ps         = addSym((char *)recbuf + PSECT_PNAME, psect_flag);
    if ((ps->flags & SF_GLOBAL) && !(psect_flag & SF_GLOBAL))
        simpl_err("local psect '%s' conflicts with global psect of same name", ps->name);
}

/**************************************************************************
 55	xpsectRecPass1	ok++
 **************************************************************************/
void xpsectRecPass1() {
    sym_t *classSym;
    char *className;
    uint32_t max_size;
    uint16_t relocatability;
    register sym_t *ps;

    readRecData(recbuf); /* Read XPSECT record to recbuf */

    ps = addSym((char *)recbuf + XPSECT_PNAME, SF_PSECT);
    /* force className to be set before adding to it */
    className = (char *)recbuf + XPSECT_PNAME;
    className += strlen(className) + 1;
    if (className - (char *)recbuf < length) {
        classSym = addSym(className, SF_CLASS | SF_GLOBAL);
        if (ps->p.pinfo->classSym == 0)
            ps->p.pinfo->classSym = classSym;
        else {
            if (classSym != ps->p.pinfo->classSym)
                simpl_err("psect %s cannot be in classes %s and %s", ps->name, classSym->name,
                          ps->p.pinfo->classSym->name);
        }
    }
    max_size       = conv_btou32(recbuf + XPSECT_MAX);
    relocatability = conv_letoi16(recbuf + XPSECT_RELOC);
    if (max_size != 0) {
        if (ps->p.pinfo->maxSize == 0 || max_size < ps->p.pinfo->maxSize)
            ps->p.pinfo->maxSize = max_size;
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

    if (key_M)
        prFileLinkMap();
    endRecPass1();
}

/**************************************************************************
 58	parseLongVal	sub_25a8h	ok++ (PMO)
 * Converts a numeric string in various databases to a uint32_t integer value.
 * Returns 0 on successful conversion and 1 on failure.
 **************************************************************************/
char parseLongVal(char **p1, uint32_t *p2) {
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
void setPsectOrigin(register psect_t *st) {

    if (st->originSet)
        fatal_err("psect '%s' re-orged", st->psectSym->name);
    if (!(st->psectSym->flags & SF_GLOBAL)) {
        if (st->align != 0) {
            linkAddress += (st->align - 1);
            linkAddress &= ~(st->align - 1L);
            loadAddress += (st->align - 1);
            loadAddress &= ~(st->align - 1L);
        }
        st->linkAddress = linkAddress;
        st->loadAddress = loadAddress;
        linkAddress += st->blkStartAddress;
        loadAddress += st->blkStartAddress;
    }
    if (st->linkAddress + st->blkStartAddress > maxLinkAddress) /* m3: */
        maxLinkAddress = st->linkAddress + st->blkStartAddress;
    st->originSet = true;
}
