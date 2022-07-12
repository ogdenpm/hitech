/*
 *
 * The sym.c file is part of the restored P1.COM program
 * from the Hi-Tech CP/M Z80 C v3.09
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH Z80 C compiler V3.09
 * (HI-TECH Software) and extend its life, outside of the CP/M environment
 * for full operation in windows 32/64 and Unix-like operating systems
 *
 * The HI-TECH Z80 C cross compiler V3.09 is provided free of charge for any use,
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
 *
 * See the readme.md file for additional commentary
 *
 * Mark Ogden
 * 09-Jul-2022
 */
#include "p1.h"

sym_t *word_a291;   /* as91 */
sym_t *s25FreeList; /* a293 */
sym_t **hashtab;    /* a295 */
s12_t *p12_a297;    /* a297 */
uint8_t byte_a299;  /* a299 */
uint8_t byte_a29a;  /* a29a */



sym_t **lookup(char *buf);
sym_t *nodeAlloc(char *s);
void reduceNodeRef(register sym_t *pn);
void sub_583a(register args_t *st);

/**************************************************
 * 103: 4D92 PMO +++
 **************************************************/
void sub_4d92(void) {

    s25FreeList = word_a291 = 0;
    hashtab                 = xalloc(HASHTABSIZE * sizeof(hashtab[0]));
}

/**************************************************
 * 104: 4DA7 PMO +++
 **************************************************/
sym_t **lookup(char *buf) {
    sym_t **ps;
    char *s;
    uint16_t crc;
    uint8_t type;
    register sym_t *cp;

    for (crc = 0, s = buf; *s; s++)
        crc += crc + *(uint8_t *)s;
    for (ps = &hashtab[crc % 271]; (cp = *ps); ps = &cp->m8) {
        if (buf && strcmp(cp->nVName, buf) == 0) {
            if (((byte_8f85 == ((type = cp->m20) == D_STRUCT || type == D_UNION)) &&
                 byte_8f86 == (type == D_MEMBER)) ||
                type == 0)
                break;
        }
    }
    return ps;
}

/**************************************************
 * 105: 4E90 PMO +++
 **************************************************/
sym_t *sub_4e90(register char *buf) {
    sym_t **ps = lookup(buf);
    if (*ps == 0)
        *ps = nodeAlloc(buf);
    if (crfFp && buf)
        fprintf(crfFp, "%s %d\n", buf, lineNo);
    return *ps;
}

/**************************************************
 * 106: 4EED PMO +++
 **************************************************/
sym_t *sub_4eed(register sym_t *st, uint8_t p2, s8_t *p3, sym_t *p4) {
    sym_t **ppSym;
    char *var4;
    int16_t var6;
    if (st->m20) {
        if (depth == st->m21 &&
            (p2 != D_MEMBER || (st->m20 == D_MEMBER && st->nMemberList == p4))) {
            var4 = 0;
            if (p2 != st->m20)
                var4 = "storage class";
            else if (st->m18 & 0x10) {
                if (!sub_591d(p3, &st->attr))
                    var4 = "type";
                if (p3->c7 == ANODE) {
                    if (p3->i_args && !st->attr.i_args)
                        var4 = "arguments";
                    else if (p3->i_args) {
                        if (p3->i_args->cnt != st->attr.i_args->cnt)
                            var4 = "no. of arguments";
                        else {
                            var6 = p3->i_args->cnt;
                            while (var6--) {
                                if (!sub_591d(&p3->i_args->s8array[var6],
                                              &st->attr.i_args->s8array[var6])) {
                                    var4 = "arguments";
                                    break;
                                }
                            }
                        }
                    }
                }
            } /* 4fea */
            if (var4)
                prError("%s: %s redeclared", st->nVName, var4);
            else if (p3->c7 == ENODE && p3->i_expr && p3->i_expr != st->attr.i_expr) {
                sub_2569(st->attr.i_expr);
                st->attr.i_expr = p3->i_expr;
            } else if (p3->c7 == ANODE) {
                if (!st->attr.i_args)
                    st->attr.i_args = p3->i_args;
                else if (p3->i_args && p3->i_args != st->attr.i_args) {
                    sub_583a(st->attr.i_args);
                    st->attr.i_args = p3->i_args;
                }
            } /* 50d1 */
            return st;
        } /* 50d7 */
        ppSym        = lookup(st->nVName);
        *ppSym       = nodeAlloc(st->nVName);
        (*ppSym)->m8 = st;
        st           = *ppSym;
    } /* 5116 */
    switch (st->m20 = p2) {
    case DT_USHORT:
    case DT_INT:
    case DT_UINT:
        st->attr.i_labelId = newTmpLabel();
        return st;
    case D_CONST:
        st->m18 |= 0x10;
        /* FALLTHRU */
    case DT_LONG:
        st->nMemberList = p4;
        break;
    case DT_ULONG:
        return st;
    case T_TYPEDEF:
        break;
    default:
        st->m18 |= 0x10;
        break;
    }
    st->attr = *p3;
    return st;
}
/**************************************************
 * 107: 516C PMO +++
 **************************************************/
void sub_516c(register sym_t *st) {
    if (st && !(st->m18 & 0x80)) {
        if (st->m18 & 1)
            prError("identifier redefined: %s", st->nVName);
        st->m18 |= 1;
        if (crfFp && st->nVName && !(st->m18 & 0x80)) {
            fprintf(crfFp, "#%s %d\n", st->nVName, lineNo);
        }
    }
}

/**************************************************
 * 108: 51CF PMO +++
 **************************************************/
void sub_51cf(register sym_t *st) {
    if (st)
        st->m18 |= 2;
}

/**************************************************
 * 109: 51E7 PMO +++
 * uin8_t param
 **************************************************/
void sub_51e7(void) {
    int16_t var2;
    int16_t var4;
    args_t *var6;
    register sym_t *st;
    var6 = curFuncNode->a_args;
    st   = p25_a28f;
    while (st) {
        st->m18 &= ~0x28;
        if (var6)
            st->m18 |= 0x200;
        if (st->a_c7 == 1) {
            sub_2569(st->a_expr);
            st->a_expr = 0;
            st->a_c7   = 0;
            sub_5be1(&st->attr);
        } /* 523d */
        sub_516c(st);
        sub_0493(st);
        st = st->nMemberList;
    }
    if (!var6)
        return;
    var4 = 0;
    var2 = var6->cnt;
    if (var2 == 1 && sub_5a76(var6->s8array, DT_VOID) && !p25_a28f)
        return;
    st = p25_a28f;
    while (st && var2--) {
        if (var6->s8array[var4].dataType == DT_VARGS) {
            st   = NULL;
            var2 = 0;
            break;
        } else if (!sub_591d(&var6->s8array[var4], &st->attr))
            break;
        st = st->nMemberList;
        var4++;
    }
    if (st || (var2 && var6->s8array[var4].dataType != DT_VARGS))
        prError("argument list conflicts with prototype");
    var2 = 1;
}

/**************************************************
 * 110: 5356 PMO +++
 **************************************************/
bool releaseNodeFreeList(void) {
    register sym_t *st;

    if (!s25FreeList)
        return false;

    while ((st = s25FreeList)) {
        s25FreeList = st->nMemberList;
        free(st);
    }
    return true;
}

char blank[] = "";
/**************************************************
 * 111: 5384 PMO +++
 **************************************************/
sym_t *nodeAlloc(char *s) {
    register sym_t *pn;
    static int16_t nodeCnt = 0;

    if (s25FreeList) {
        pn          = s25FreeList;
        s25FreeList = pn->nMemberList;
        blkclr(pn, sizeof(sym_t));
    } else {
        pn = xalloc(sizeof(sym_t));
    }
    pn->m21     = depth;
    pn->nRefCnt = 1;
    pn->nodeId  = ++nodeCnt;
    if (s) {
        pn->nVName = (char *)xalloc(strlen(s) + 1);
        strcpy(pn->nVName, s);
    } else
        pn->nVName = blank;
    return pn;
}

/**************************************************
 * 112: 540C PMO +++
 * optimiser has better code for --pn->nRefCnt
 **************************************************/
void reduceNodeRef(register sym_t *pn) {

    if (--pn->nRefCnt == 0) {
        if (pn->m20 != 0 && pn->m20 != D_LABEL && pn->m20 != D_STRUCT && pn->m20 != D_UNION &&
            pn->m20 != D_ENUM) {
            if (pn->a_c7 == ANODE)
                sub_583a(pn->a_args);
            else if (pn->a_c7 == ENODE)
                sub_2569(pn->a_expr);
            if (pn->a_dataType == DT_POINTER)
                reduceNodeRef(pn->a_nextSym);
        }
        if (pn->nVName != blank)
            free(pn->nVName);
        pn->nMemberList = s25FreeList;
        s25FreeList     = pn;
    }
}

/**************************************************
 * 113: 549C PMO +++
 * use of uint8_t param
 **************************************************/
void enterScope(void) {

    prFuncBrace(T_LBRACE);
    ++depth;
}

/**************************************************
 * 114: 54AC PMO +++
 * use of uint8_t param
 **************************************************/
void exitScope(void) {

    checkScopeExit();
    --depth;
    prFuncBrace(T_RBRACE);
}

/**************************************************
 * 115: 54C0 PMO +++
 **************************************************/
void checkScopeExit(void) {
    sym_t **ppSym;
    sym_t **var4;
    uint8_t var5;
    char *var7;
    register sym_t *st;

    for (ppSym = hashtab; ppSym < &hashtab[HASHTABSIZE]; ppSym++) {
        var4 = ppSym;
        while ((st = *var4)) {
            if (st->m21 == depth) {
                var7 = 0;
                var5 = st->m20;
                if ((st->m18 & 3) == 2) {
                    switch (var5) {
                    case D_LABEL:
                        var7 = "label";
                        break;
                    case D_STRUCT:
                    case D_UNION:
                    case T_EXTERN:
                        break;
                    default:
                        var7 = "variable";
                        break;
                    }
                    if (var7)
                        prError("undefined %s: %s", var7, st->nVName);
                } else if ((depth || var5 == T_STATIC) && !(st->m18 & 2)) { /* 5555  */
                    switch (var5) {
                    case D_LABEL:
                        var7 = "label";
                        break;
                    case D_STRUCT:
                        var7 = "structure";
                        break;
                    case D_UNION:
                        var7 = "union";
                        break;
                    case D_MEMBER:
                        var7 = "member";
                        break;
                    case D_ENUM:
                        var7 = "enum";
                        break;
                    case D_CONST:
                        var7 = "constant";
                        break;
                    case T_TYPEDEF:
                        var7 = "typedef";
                        break;
                    case D_6:
                        var7 = 0;
                        break;
                    default:
                        if (var5) {
                            if (st->m18 & 1)
                                var7 = "variable definition";
                            else
                                var7 = "variable declaration";
                        }
                        break;
                    }
                    if (var7)
                        prWarning("unused %s: %s", var7, st->nVName);

                } /* 55d2 */
                *var4 = st->m8;
                reduceNodeRef(st);
            } else
                var4 = &st->m8;
        }
    }
    var4 = &word_a291;
    while ((st = *var4)) {
        if (st->m21 == depth) {
            *var4 = st->m8;
            reduceNodeRef(st);
        } else
            var4 = &st->m8;
    }
}

/**************************************************
 * 116: 56A4 PMO +++
 **************************************************/
sym_t *sub_56a4(void) {
    register sym_t *st;

    st = nodeAlloc(0);
    st->m18 |= 0x83;
    st->m8    = word_a291;
    word_a291 = st;
    return st;
}

/**************************************************
 * 117: 56CD PMO +++
 **************************************************/
sym_t *findMember(sym_t *p1, char *p2) {
    register sym_t *st;

    st = p1->nMemberList;
    for (;;) {
        if (p1 == st) {
            prError("%s is not a member of the struct/union %s", p2, p1->nVName);
            return NULL;
        }
        if (strcmp(st->nVName, p2) == 0)
            return st;
        st = st->nMemberList;
    }
}

/**************************************************
 * 118: 573B PMO +++
 **************************************************/
void sub_573b(register sym_t *st, FILE *fp) {

    if (st) {
        if (st->m18 & 0x80)
            fprintf(fp, "F%d", st->nodeId);
        else
            fprintf(fp, "_%s", st->nVName);
    }
}

/**************************************************
 * 119: 5785 PMO +++
 **************************************************/
int16_t newTmpLabel(void) {

    return ++tmpLabelId;
}

/**************************************************
 * 120: 578D PMO +++
 * trivial optimiser differences
 **************************************************/
args_t *sub_578d(register args_t *p) {
    args_t *var2;
    s8_t *var4;
    int16_t var6;
    if (!p)
        return p;
    var2 = xalloc(sizeof(args_t) + (p->cnt - 1) * sizeof(s8_t));
    var6 = var2->cnt = p->cnt;
    while (var6--) {
        var4  = &var2->s8array[var6];
        *var4 = p->s8array[var6];
        if (var4->dataType == DT_POINTER)
            var4->i_nextSym->nRefCnt++;
    }
    return var2;
}

/**************************************************
 * 121: 583A PMO +++
 **************************************************/
void sub_583a(register args_t *st) {
    s8_t *var2;
    if (st) {
        for (var2 = st->s8array; st->cnt--; var2++) {
            if (var2->c7 == ANODE && var2->i_args)
                sub_583a(var2->i_args);
            if (var2->dataType == DT_POINTER)
                reduceNodeRef(var2->i_nextSym);
        }
        free(st);
    }
}

/**************************************************
 * 122: 58BD PMO +++
 **************************************************/
void sub_58bd(register s8_t *st, s8_t *p2) {
    *p2 = *st;
    if (p2->c7 == ENODE)
        p2->i_expr = sub_21c7(p2->i_expr);
    else if (p2->c7 == ANODE)
        p2->i_args = sub_578d(p2->i_args);
}

/**************************************************
 * 123: 591D PMO +++
 * some optimiser differences including movement
 * of some basic blocks
 **************************************************/
bool sub_591d(register s8_t *st, s8_t *p2) {
    int16_t var2;

    if (st == p2)
        return true;
    if (st->c7 != p2->c7 || st->dataType != p2->dataType || st->i4 != p2->i4)
        return false;
    switch (st->dataType) {
    case DT_ENUM:
    case DT_STRUCT:
    case DT_UNION:
        return st->i_nextSym == p2->i_nextSym;
    case DT_POINTER:
        return sub_591d(st->i_nextInfo, p2->i_nextInfo);
    }
    if (st->c7 != ANODE || !st->i_args || !p2->i_args)
        return true;
    if (st->i_args->cnt != p2->i_args->cnt)
        return false;
    var2 = st->i_args->cnt;
    do {
        if (var2-- == 0)
            return true;
    } while (sub_591d(&st->i_args->s8array[var2], &p2->i_args->s8array[var2]));
    return false;
}

/**************************************************
 * 124: 5A4A PMO +++
 **************************************************/
bool sub_5a4a(register s8_t *st) {
    return st->dataType == DT_VOID && st->i4 == 1;
}

/**************************************************
 * 125: 5A76 PMO +++
 **************************************************/
bool sub_5a76(register s8_t *st, uint8_t p2) {

    return st->dataType == p2 && st->i4 == 0 && st->c7 == SNODE;
}

/**************************************************
 * 126: 5AA4 PMO +++
 **************************************************/
bool sub_5aa4(register s8_t *st) {
    return st->c7 == SNODE && (((st->i4 & 1) && st->c7 == SNODE) || st->dataType < DT_VOID);
}

/**************************************************
 * 127: 5AD5 PMO +++
 **************************************************/
bool sub_5ad5(register s8_t *st) {
    return st->c7 == SNODE && st->i4 == 0 &&  st->dataType <= DT_ENUM;
}

/**************************************************
 * 128: 5B08 PMO +++
 **************************************************/
bool sub_5b08(register s8_t *st) {
    return (st->c7 == SNODE && st->i4 == 0 && st->dataType < DT_FLOAT);
}

/**************************************************
 * 129: 5B38 PMO +++
 **************************************************/
bool sub_5b38(register s8_t *st) {
    return st->c7 == SNODE && st->i4 == 0 &&
           (st->dataType == DT_FLOAT || st->dataType == DT_DOUBLE);
}

/**************************************************
 * 130: 5B69 PMO +++
 **************************************************/
bool isValidDimType(register s8_t *st) {

    return sub_5b08(st) || sub_5a76(st, DT_ENUM);
}

/**************************************************
 * 131: 5B99 PMO +++
 * uint8_t parameter
 **************************************************/
void sub_5b99(register s8_t *st) {
    if (st->c7 == ANODE)
        st->c7 = 0;
    else
        st->i4 >>= 1;

    if (sub_5a76(st, 0x16))
        *st = *(st->i_nextInfo);
}
