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

sym_t *tmpSyms;     /* as91 */
sym_t *symFreeList; /* a293 */
sym_t **hashtab;    /* a295 */
decl_t *curDecl;    /* a297 */
uint8_t defSClass;  /* a299 */
uint8_t byte_a29a;  /* a29a */

sym_t **lookup(char *buf);
sym_t *symAlloc(char *s);
void reduceNodeRef(register sym_t *pn);
void freeArgs(register args_t *st);

/**************************************************
 * 103: 4D92 PMO +++
 **************************************************/
void sub_4d92(void) {

    symFreeList = tmpSyms = 0;
    hashtab               = xalloc(HASHTABSIZE * sizeof(hashtab[0]));
}

/**************************************************
 * 104: 4DA7 PMO +++
 **************************************************/
sym_t **lookup(char *buf) {
    sym_t **ps;
    char *s;
    uint16_t crc;
    uint8_t sclass;
    register sym_t *cp;

    for (crc = 0, s = buf; *s; s++)
        crc += crc + *(uint8_t *)s;
    for (ps = &hashtab[crc % 271]; (cp = *ps); ps = &cp->symList) {
        if (buf && strcmp(cp->nVName, buf) == 0) {
            if (((byte_8f85 == ((sclass = cp->sclass) == D_STRUCT || sclass == D_UNION)) &&
                 lexMember == (sclass == D_MEMBER)) ||
                sclass == 0)
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
        *ps = symAlloc(buf);
    if (crfFp && buf)
        fprintf(crfFp, "%s %d\n", buf, lineNo);
    return *ps;
}

/**************************************************
 * 106: 4EED PMO +++
 **************************************************/
sym_t *sub_4eed(register sym_t *st, uint8_t p2, attr_t *p3, sym_t *p4) {
    sym_t **ppSym;
    char *var4;
    int16_t var6;
    if (st->sclass) {
        if (depth == st->level &&
            (p2 != D_MEMBER || (st->sclass == D_MEMBER && st->memberList == p4))) {
            var4 = 0;
            if (p2 != st->sclass)
                var4 = "storage class";
            else if (st->flags & 0x10) {
                if (!haveSameDataType(p3, &st->attr))
                    var4 = "type";
                if (p3->nodeType == FUNCNODE) {
                    if (p3->pFargs && !st->attr.pFargs)
                        var4 = "arguments";
                    else if (p3->pFargs) {
                        if (p3->pFargs->cnt != st->attr.pFargs->cnt)
                            var4 = "no. of arguments";
                        else {
                            var6 = p3->pFargs->cnt;
                            while (var6--) {
                                if (!haveSameDataType(&p3->pFargs->argVec[var6],
                                                      &st->attr.pFargs->argVec[var6])) {
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
            else if (p3->nodeType == EXPRNODE && p3->pExpr && p3->pExpr != st->attr.pExpr) {
                freeExpr(st->attr.pExpr);
                st->attr.pExpr = p3->pExpr;
            } else if (p3->nodeType == FUNCNODE) {
                if (!st->attr.pFargs)
                    st->attr.pFargs = p3->pFargs;
                else if (p3->pFargs && p3->pFargs != st->attr.pFargs) {
                    freeArgs(st->attr.pFargs);
                    st->attr.pFargs = p3->pFargs;
                }
            } /* 50d1 */
            return st;
        } /* 50d7 */
        ppSym             = lookup(st->nVName);
        *ppSym            = symAlloc(st->nVName);
        (*ppSym)->symList = st;
        st                = *ppSym;
    } /* 5116 */
    switch (st->sclass = p2) {
    case DT_USHORT:
    case DT_INT:
    case DT_UINT:
        st->attr.labelId = newTmpLabel();
        return st;
    case D_CONST:
        st->flags |= 0x10;
        /* FALLTHRU */
    case DT_LONG:
        st->memberList = p4;
        break;
    case DT_ULONG:
        return st;
    case T_TYPEDEF:
        break;
    default:
        st->flags |= S_VAR;
        break;
    }
    st->attr = *p3;
    return st;
}
/**************************************************
 * 107: 516C PMO +++
 **************************************************/
void defineArg(register sym_t *st) {
    if (st && !(st->flags & S_NAMEID)) {
        if (st->flags & S_MEM)
            prError("identifier redefined: %s", st->nVName);
        st->flags |= S_MEM;
        if (crfFp && st->nVName && !(st->flags & S_NAMEID)) {
            fprintf(crfFp, "#%s %d\n", st->nVName, lineNo);
        }
    }
}

/**************************************************
 * 108: 51CF PMO +++
 **************************************************/
void sub_51cf(register sym_t *st) {
    if (st)
        st->flags |= 2;
}

/**************************************************
 * 109: 51E7 PMO +++
 * uin8_t param
 **************************************************/
void defineFuncSig(void) {
    int16_t cnt;
    int16_t i;
    args_t *argList;
    register sym_t *st;

    argList = curFuncNode->a_args;
    for (st = p25_a28f; st; st = st->memberList) {
        st->flags &= ~0x28;
        if (argList)
            st->flags |= S_ARG;
        if (st->a_nodeType == EXPRNODE) {
            freeExpr(st->a_expr);
            st->a_expr     = 0;
            st->a_nodeType = SYMNODE;
            addIndirection(&st->attr);
        } /* 523d */
        defineArg(st);
        emitVar(st);
    }
    if (!argList)
        return;
    i   = 0;
    cnt = argList->cnt;
    if (cnt == 1 && isVarOfType(argList->argVec, DT_VOID) && !p25_a28f)
        return;
    for (st = p25_a28f; st && cnt--; st = st->memberList, i++) {
        if (argList->argVec[i].dataType == DT_VARGS) {
            st  = NULL;
            cnt = 0;
            break;
        } else if (!haveSameDataType(&argList->argVec[i], &st->attr))
            break;
    }
    if (st || (cnt && argList->argVec[i].dataType != DT_VARGS))
        prError("argument list conflicts with prototype");
    cnt = 1;
}

/**************************************************
 * 110: 5356 PMO +++
 **************************************************/
bool releaseSymFreeList(void) {
    register sym_t *st;

    if (!symFreeList)
        return false;

    while ((st = symFreeList)) {
        symFreeList = st->memberList;
        free(st);
    }
    return true;
}

char blank[] = "";
/**************************************************
 * 111: 5384 PMO +++
 **************************************************/
sym_t *symAlloc(char *s) {
    register sym_t *ps;
    static int16_t symCnt = 0;

    if (symFreeList) {
        ps          = symFreeList;
        symFreeList = ps->memberList;
        blkclr(ps, sizeof(sym_t));
    } else {
        ps = xalloc(sizeof(sym_t));
    }
    ps->level   = depth;
    ps->nRefCnt = 1;
    ps->symId  = ++symCnt;
    if (s) {
        ps->nVName = (char *)xalloc(strlen(s) + 1);
        strcpy(ps->nVName, s);
    } else
        ps->nVName = blank;
    return ps;
}

/**************************************************
 * 112: 540C PMO +++
 * optimiser has better code for --pn->nRefCnt
 **************************************************/
void reduceNodeRef(register sym_t *pn) {
    /* printf("%p %d %d %s\n", pn, pn->level, pn->nRefCnt,
           pn->a_nodeType == 0   ? (*pn->nVName ? pn->nVName : "blank")
           : pn->a_nodeType == 1 ? "EXPR"
                                 : "FUNC"
                                 ); */
    if (--pn->nRefCnt == 0) {
        if (pn->sclass != 0 && pn->sclass != D_LABEL && pn->sclass != D_STRUCT &&
            pn->sclass != D_UNION && pn->sclass != D_ENUM) {
            if (pn->a_nodeType == FUNCNODE)
                freeArgs(pn->a_args);
            else if (pn->a_nodeType == EXPRNODE)
                freeExpr(pn->a_expr);
#if BUGGY
            /* this code is prone to release symbols too early */
            if (ps->a_dataType == DT_COMPLEX)
                reduceNodeRef(ps->a_nextSym);
#endif
        }
        if (pn->nVName != blank)
            free(pn->nVName);
        pn->memberList = symFreeList;
        symFreeList    = pn;
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

    releaseScopeSym();
    --depth;
    prFuncBrace(T_RBRACE);
}

/**************************************************
 * 115: 54C0 PMO +++
 **************************************************/
void releaseScopeSym(void) {
    sym_t **pSlot;
    sym_t **ppSym;
    uint8_t sclass;
    char *msg;
    register sym_t *pSym;

    for (pSlot = hashtab; pSlot < &hashtab[HASHTABSIZE]; pSlot++) {
        ppSym = pSlot;
        while ((pSym = *ppSym)) {
            if (pSym->level == depth) {
                msg    = 0;
                sclass = pSym->sclass;
                if ((pSym->flags & 3) == 2) {
                    switch (sclass) {
                    case D_LABEL:
                        msg = "label";
                        break;
                    case D_STRUCT:
                    case D_UNION:
                    case T_EXTERN:
                        break;
                    default:
                        msg = "variable";
                        break;
                    }
                    if (msg)
                        prError("undefined %s: %s", msg, pSym->nVName);
                } else if ((depth || sclass == T_STATIC) && !(pSym->flags & 2)) { /* 5555  */
                    switch (sclass) {
                    case D_LABEL:
                        msg = "label";
                        break;
                    case D_STRUCT:
                        msg = "structure";
                        break;
                    case D_UNION:
                        msg = "union";
                        break;
                    case D_MEMBER:
                        msg = "member";
                        break;
                    case D_ENUM:
                        msg = "enum";
                        break;
                    case D_CONST:
                        msg = "constant";
                        break;
                    case T_TYPEDEF:
                        msg = "typedef";
                        break;
                    case D_STACK:
                        msg = 0;
                        break;
                    default:
                        if (sclass) {
                            if (pSym->flags & S_MEM)
                                msg = "variable definition";
                            else
                                msg = "variable declaration";
                        }
                        break;
                    }
                    if (msg)
                        prWarning("unused %s: %s", msg, pSym->nVName);

                } /* 55d2 */
                *ppSym = pSym->symList;
                reduceNodeRef(pSym);
            } else
                ppSym = &pSym->symList;
        }
    }
    ppSym = &tmpSyms;
    while ((pSym = *ppSym)) {
        if (pSym->level == depth) {
            *ppSym = pSym->symList; /* remove from list and reduce its ref count */
            reduceNodeRef(pSym);
        } else
            ppSym = &pSym->symList; /* skip to next entry */
    }
}

/**************************************************
 * 116: 56A4 PMO +++
 **************************************************/
sym_t *newTmpSym(void) {
    register sym_t *st;

    st = symAlloc(0);
    st->flags |= S_NAMEID + 2 + S_MEM;
    st->symList = tmpSyms;
    tmpSyms     = st;
    return st;
}

/**************************************************
 * 117: 56CD PMO +++
 **************************************************/
sym_t *findMember(sym_t *pSym, char *name) {
    register sym_t *ps;

    for (ps = pSym->memberList; pSym != ps; ps = ps->memberList)
        if (strcmp(ps->nVName, name) == 0)
            return ps;
    prError("%s is not a member of the struct/union %s", name, pSym->nVName);
    return NULL;
}

/**************************************************
 * 118: 573B PMO +++
 **************************************************/
void emitSymName(register sym_t *st, FILE *fp) {

    if (st) {
        if (st->flags & S_NAMEID)
            fprintf(fp, "F%d", st->symId);
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
args_t *cloneArgs(register args_t *pArgs) {
    args_t *newList;
    attr_t *pAttr;
    int16_t i;
    if (!pArgs)
        return pArgs;
    newList = xalloc(sizeof(args_t) + (pArgs->cnt - 1) * sizeof(attr_t));
    i = newList->cnt = pArgs->cnt;
    while (i--) {
        pAttr  = &newList->argVec[i];
        *pAttr = pArgs->argVec[i];
        if (pAttr->dataType == DT_COMPLEX)
            pAttr->nextSym->nRefCnt++;
    }
    return newList;
}

/**************************************************
 * 121: 583A PMO +++
 **************************************************/
void freeArgs(register args_t *pArgs) {
    attr_t *pAttr;
    if (pArgs) {
        for (pAttr = pArgs->argVec; pArgs->cnt--; pAttr++) {
            if (pAttr->nodeType == FUNCNODE && pAttr->pFargs)
                freeArgs(pAttr->pFargs);
            if (pAttr->dataType == DT_COMPLEX)
                reduceNodeRef(pAttr->nextSym);
        }
        free(pArgs);
    }
}

/**************************************************
 * 122: 58BD PMO +++
 **************************************************/
void cloneAttr(register attr_t *st, attr_t *p2) {
    *p2 = *st;
    if (p2->nodeType == EXPRNODE)
        p2->pExpr = cloneExpr(p2->pExpr);
    else if (p2->nodeType == FUNCNODE)
        p2->pFargs = cloneArgs(p2->pFargs);
}

/**************************************************
 * 123: 591D PMO +++
 * some optimiser differences including movement
 * of some basic blocks
 **************************************************/
bool haveSameDataType(register attr_t *st, attr_t *p2) {
    int16_t var2;

    if (st == p2)
        return true;
    if (st->nodeType != p2->nodeType || st->dataType != p2->dataType ||
        st->indirection != p2->indirection)
        return false;
    switch (st->dataType) {
    case DT_ENUM:
    case DT_STRUCT:
    case DT_UNION:
        return st->nextSym == p2->nextSym;
    case DT_COMPLEX:
        return haveSameDataType(st->nextAttr, p2->nextAttr);
    }
    if (st->nodeType != FUNCNODE || !st->pFargs || !p2->pFargs)
        return true;
    if (st->pFargs->cnt != p2->pFargs->cnt)
        return false;
    var2 = st->pFargs->cnt;
    do {
        if (var2-- == 0)
            return true;
    } while (haveSameDataType(&st->pFargs->argVec[var2], &p2->pFargs->argVec[var2]));
    return false;
}

/**************************************************
 * 124: 5A4A PMO +++
 **************************************************/
bool isVoidStar(register attr_t *st) {
    return st->dataType == DT_VOID && st->indirection == 1;
}

/**************************************************
 * 125: 5A76 PMO +++
 **************************************************/
bool isVarOfType(register attr_t *st, uint8_t p2) {

    return st->dataType == p2 && st->indirection == 0 && st->nodeType == SYMNODE;
}

/**************************************************
 * 126: 5AA4 PMO +++
 **************************************************/
bool isLogicalType(register attr_t *st) {
    return st->nodeType == SYMNODE &&
           (((st->indirection & 1) && st->nodeType == SYMNODE) || st->dataType < DT_VOID);
}

/**************************************************
 * 127: 5AD5 PMO +++
 **************************************************/
bool isSimpleType(register attr_t *st) {
    return st->nodeType == SYMNODE && st->indirection == 0 && st->dataType <= DT_ENUM;
}

/**************************************************
 * 128: 5B08 PMO +++
 **************************************************/
bool isIntType(register attr_t *st) {
    return (st->nodeType == SYMNODE && st->indirection == 0 && st->dataType < DT_FLOAT);
}

/**************************************************
 * 129: 5B38 PMO +++
 **************************************************/
bool isFloatType(register attr_t *st) {
    return st->nodeType == SYMNODE && st->indirection == 0 &&
           (st->dataType == DT_FLOAT || st->dataType == DT_DOUBLE);
}

/**************************************************
 * 130: 5B69 PMO +++
 **************************************************/
bool isValidIndex(register attr_t *st) {

    return isIntType(st) || isVarOfType(st, DT_ENUM);
}

/**************************************************
 * 131: 5B99 PMO +++
 * uint8_t parameter
 **************************************************/
void delIndirection(register attr_t *st) {
    if (st->nodeType == FUNCNODE)
        st->nodeType = SYMNODE;
    else
        st->indirection >>= 1;

    if (isVarOfType(st, DT_COMPLEX))
        *st = *(st->nextAttr);
}
