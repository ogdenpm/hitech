/*
 *
 * The expr.c file is part of the restored P1.COM program
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

opStk_t *opSP     = &opStk[20]; /* 8bc7 */
int16_t strId     = 0;          /* 8bd7 */
uint8_t byte_8f85 = 0;          /* 8f85 */
bool lexMember    = false;      /* 8f86 */
uint8_t byte_968b;              /* 968b */
int16_t word_968c;              /* 968c */
int16_t tmpLabelId;             /* 968e */

expr_t **exprSP;   /* 9cf1 */
opStk_t opStk[20]; /* 9cf3 */
char pad9d00[27];
expr_t eZero; /* 9d1b */
expr_t eOne;  /* 9d28 */

expr_t *exprFreeList; /* 9d35 */
uint8_t byte_9d37;    /* 9d37 */
expr_t *exprStk[20];  /* 9d38 */

/* expr.c */
expr_t *sub_0817(register attr_t *st);
bool isConstExpr(register expr_t *st);
bool sub_0b93(register expr_t *st);
bool sub_10a8(void);
expr_t *sub_1340(register expr_t *st, expr_t *p2);
expr_t *newFConstLeaf(char *fltStr);
expr_t *makeBool(register expr_t *st);
expr_t *typeAlign(register expr_t *pe, attr_t *pa);
expr_t *sub_1ccc(expr_t *p1, uint8_t p2);
expr_t *sub_1d02(register expr_t *st);
uint8_t getResultDataType(register expr_t *lhs, expr_t *rhs);
expr_t *sub_1df0(register expr_t *st);
expr_t *sub_1e37(register expr_t *st);
expr_t *newAddressOfNode(register expr_t *st);
expr_t *sub_1ebd(register expr_t *st);
bool sub_1ef1(register expr_t *st);
expr_t *sub_1f5d(register expr_t *st, attr_t *p2, bool unscaled);
expr_t *newExprItem(uint8_t tok);
expr_t *getResultAttr(uint8_t p1, register expr_t *st, expr_t *p3);
expr_t *newNode(uint8_t tok, register expr_t *st, expr_t *p3);
expr_t *newSConstLeaf(void);
void complexErr(void);
expr_t *popExpr(void);
void pushOp(uint8_t p1);
uint8_t popOp(void);

/**************************************************
 * 17: 07F5 PMO +++
 **************************************************/
expr_t *sub_07f5(char p1) {
    char l1;
    register expr_t *st;

    l1        = byte_9d37;
    byte_9d37 = p1;
    st        = sub_0bfc();
    byte_9d37 = l1;
    return st;
}

/**************************************************
 * 18: 0817 PMO +++
 * Minor differences due to addition of missing
 * parameters and use of uint8_t parameter
 * also one missed optimisation
 * of pop bc, push hl to ex (sp),hl
 **************************************************/
expr_t *sub_0817(register attr_t *pa) {
    int16_t var2;
    int16_t argCnt;
    expr_t *var6;
    uint8_t tok;
    expr_t *arr[128];


    if (pa && pa->nodeType != FUNCNODE && pa->indirection == 1 && pa->dataType == DT_COMPLEX &&
        pa->nextAttr->nodeType == FUNCNODE)
        pa = pa->nextAttr;
#ifdef BUGGY
    else if (pa->nodeType != FUNCNODE)
        prError("function or function pointer required");
#else
    /*PMO: fixed else clause incase pa is NULL */
    else if (!pa || pa->nodeType != FUNCNODE)
        prError("function or function pointer required");
#endif

    if (pa && pa->nodeType == FUNCNODE && pa->pFargs) {
        argCnt = pa->pFargs->cnt;
        pa   = pa->pFargs->argVec;
    } else {
        pa   = NULL;
        argCnt = 0;
    }

    var2     = 0;
    ungetTok = tok = yylex();
    for (;;) {
        if (pa && pa->dataType == DT_VARGS) {
            argCnt = 0;
            pa   = 0;
        }
        if (tok != T_RPAREN) {
            if (pa && isVarOfType(pa, DT_VOID)) {
                prError("function does not take arguments");
                argCnt = 0;
                pa   = NULL;
            }
            var6 = parseExpr(T_EROOT, sub_07f5(3), 0);
            if (var6) {
                if (pa && argCnt-- == 0) {
                    prError("too many arguments");
                    pa   = 0;
                    argCnt = 0;
                }
                if (pa)
                    var6 = sub_1f5d(var6, pa++, true);
                else
                    var6 = sub_1d02(var6);
                arr[var2++] = var6;
                tok         = yylex();
                if (tok == T_COMMA)
                    continue;
                ungetTok = tok;
            }
        }
        break;
    }
    if ((argCnt != 1 || var2 != 0 || !isVarOfType(pa, DT_VOID)) && argCnt && pa->dataType != DT_VARGS)
        prError("too few arguments");

    if (var2 == 0)
        return newNode(T_120, NULL, NULL); /* dummy 2nd & 3rd args added */
    argCnt = 0;
    while (argCnt + 1 != var2) {
        arr[argCnt + 1] = newNode(T_COMMA, arr[argCnt], arr[argCnt + 1]);
        ++argCnt;
    }
    return arr[argCnt];
}

/**************************************************
 * 19: 0A83 PMO +++
 * Minor differences due to addition of missing
 * parameters and use of uint8_t parameter
 **************************************************/
expr_t *parseConstExpr(uint8_t n) {
    register expr_t *st;

    byte_9d37 = n;
    if ((st = parseExpr(T_EROOT, sub_0bfc(), 0))) { /* PMO added dummy arg3 */
        if (!isConstExpr(st))
            prError("constant expression required");
        else if (byte_9d37 == 2) {
            if (isValidIndex(&st->attr))
                st = sub_1ccc(st, DT_CONST);
            else
                prError("illegal type for array dimension");
        }
    }
    byte_9d37 = 0;
    return st;
}

/**************************************************
 * 20: 0AED PMO +++
 * Locations of code to set return  values 1/0 swapped
 * rest of code adjusted accordingly
 **************************************************/
bool isConstExpr(register expr_t *st) {
    uint8_t op, flags;

    if (st == 0)
        return true;
    op = st->tType;
    if (op == T_ID)
        return isVarOfType(&st->attr, DT_ENUM);
    if (op == T_SIZEOF)
        return true;
    if (op == D_ADDRESSOF && sub_0b93(st->t_lhs))
        return true;
    flags = opTable[(op - T_EROOT)].operandFlags;
    if (!(flags & 0x10))
        return false;
    if (flags & O_LEAF)
        return true;
    return isConstExpr(st->t_lhs) && (!(flags & O_BINARY) || isConstExpr(st->t_rhs));
}

/**************************************************
 * 21: 0B93 PMO +++
 **************************************************/
bool sub_0b93(register expr_t *st) {
    uint8_t op;

    op = st->tType;
    if (op == T_ID)
        return st->t_pSym->sclass == T_EXTERN || st->t_pSym->sclass == T_STATIC;
    if (op == T_DOT)
        return sub_0b93(st->t_lhs);
    return op == D_DEREF && isConstExpr(st->t_lhs);
}

/**************************************************
 * 22: 0BFC PMO +++
 * many basic blocks moved around, logic still valid
 * some optimisation differences but equivalent code
 **************************************************/
expr_t *sub_0bfc(void) {
    attr_t var8;
    expr_t *leaf FORCEINIT;
    opStk_t *savOpSP;
    expr_t **savExprSP;
    uint8_t tok;
    uint8_t tok2;
    uint8_t hasLhs;
    bool more;
    bool hasMember;
    uint8_t hasRhs;
    uint8_t prec;
    int16_t var17;
    // int16_t var19; /* not used */
    register sym_t *st;

    savExprSP = exprSP;
    savOpSP   = opSP;
    pushOp(T_EROOT);
    hasLhs = false;
    // var19  = 0;
    for (;;) {
        hasMember = lexMember = opSP->op == T_DOT || opSP->op == T_POINTER;
        tok                   = yylex();
        lexMember             = false;
        if (tok < T_EROOT || tok >= T_OPTOP) {
            ungetTok = tok;
            tok      = T_EROOT;
        }
        if (opTable[tok - T_EROOT].operandFlags & O_LEAF) {
            if (hasLhs)
                goto error;
            switch (tok) {
            case T_ID: /* c9a */
                st = yylval.ySym;
                if (!hasMember) {
                    if (st->sclass == 0) {
                        if (peekCh() == '(') {
                            var8.nodeType    = 2;
                            var8.dataType    = DT_INT;
                            var8.pExpr      = NULL;
                            var8.indirection = 0;
                            st               = sub_4eed(st, T_EXTERN, &var8, 0);
                            st->flags |= 0x42;
                            st->level = 0;
                            emitVar(st);
                        } else {
                            prError("undefined identifier: %s", st->nVName);
                            st->sclass        = T_STATIC;
                            st->attr.dataType = DT_INT;
                            st->flags         = 0x10 + S_MEM;
                        }
                    } else {
                        var17 = st->flags;
                        if (!(var17 & S_VAR))
                            prError("not a variable identifier: %s", st->nVName);
                        else if (st->sclass == T_EXTERN && !(var17 & S_EMITTED))
                            emitVar(st);
                    }
                    sub_51cf(st);
                } /* d57 */
                leaf = newIdLeaf(st);
                break;
            case T_ICONST: /* d75 */
                leaf = newIntLeaf(yylval.yNum, DT_INT);
                break;
            case T_LCONST: /* d90 */
                leaf = newIntLeaf(yylval.yNum, DT_LONG);
                break;
            case T_FCONST: /* da5 */
                leaf = newFConstLeaf(yylval.yStr);
                break;
            case T_SCONST: /* dae */
                leaf          = newSConstLeaf();
                leaf->t_chCnt = strChCnt;
                emitAscii(leaf, yylval.yStr);
                free(yylval.yStr);
                break;
            case S_TYPE:
                goto error;
            }
            /* d63 */
            pushExpr(leaf);
            hasLhs = true;
            continue;
        } /* dfa */
        switch (tok) {
        case T_LPAREN:
            ungetTok = tok2 = yylex();
            if (tok2 == S_TYPE || (tok2 == T_ID && yylval.ySym->sclass == T_TYPEDEF)) {
                if (hasLhs)
                    goto error;
                sub_5dd1(0, &var8);
                defineArg(st = sub_69ca(T_CAST, &var8, 0, 0));
                sub_51cf(st);
                tok2 = yylex();
                if (tok2 != T_RPAREN)
                    goto error;
                var8 = st->attr;
                pushExpr(newSTypeLeaf(&var8));
                if (opSP->op == T_SIZEOF) {
                    opSP->prec = 100;
                    hasLhs     = true;
                    continue;
                } else
                    tok = T_CAST;
            } else if (hasLhs) {
                pushOp(D_FUNC);
                pushExpr(sub_0817(&(*exprSP)->attr));
            }
            break;
        case T_EROOT:
            break;
        case T_LBRACK:
            if (!hasLhs)
                goto error;
            tok    = T_ARRAYIDX;
            hasLhs = false;
            break;
        case T_RPAREN:
        case T_RBRACK:
            if (!hasLhs)
                goto error;
            break;
        case T_PREINC:
        case T_PREDEC:
            if (hasLhs) /* have lhs so make post INC/DEC */
                tok++;
            break;
        default:
            if ((opTable[tok - T_EROOT].operandFlags & O_ALT) && !hasLhs)
                tok -= 11; /* map to unary function */
            hasRhs = (opTable[tok - T_EROOT].operandFlags & O_BINARY) != 0;
            if (hasRhs != hasLhs)
                goto error;
            hasLhs = false;
            break;
        }
        /* f23 */
        prec = opTable[tok - T_EROOT].prec;
        if ((byte_9d37 >= 3 && tok == T_COMMA) ||
            (byte_9d37 == 1 && tok == T_COLON && opSP->op != T_QUEST))
            prec = 5;
        /* f8e */
        do {
            more = false;
            if (opSP->prec < prec ||
                (opSP->prec == prec && (opTable[tok - T_EROOT].operandFlags & O_RTOL))) {
                switch (tok) {
                case T_POSTINC:
                case T_POSTDEC:
                    prec = 31;
                    break;
                case T_LPAREN:
                case T_ARRAYIDX:
                    prec = 4;
                    break;
                }
                pushOp(tok);
                opSP->prec = prec;
            } else {
                if (opSP->op == T_EROOT) { /* 1058 */
                    if (tok != T_EROOT)
                        ungetTok = tok;
                    leaf = popExpr();
                    if (leaf && exprSP == savExprSP)
                        goto done;
                    else
                        goto error;
                } else if (opSP->op == T_LPAREN) {
                    if (tok != T_RPAREN) {
                        expectErr(")");
                        ungetTok = tok;
                    }
                } else if (opSP->op == T_ARRAYIDX) {
                    if (tok != T_RBRACK) {
                        expectErr("]");
                        ungetTok = tok;
                    }
                } else
                    more = true;
                /* 1037 */
                if (sub_10a8())
                    goto error;
            }
        } while (more);
    }
error:
    prError("expression syntax");
    skipStmt(tok);
    while (exprSP != savExprSP) /* remove partial expression */
        freeExpr(popExpr());
    leaf = NULL;

done:
    exprSP = savExprSP;
    opSP   = savOpSP;
    return leaf;
}

/**************************************************
 * 23: 10A8 PMO +++
 * Minor differences, use of uint8_ parameter and
 * addition of missing parameters
 **************************************************/
bool sub_10a8(void) {
    expr_t *rhsExpr;
    expr_t *pe;
    uint8_t op;
    register expr_t *lhsExpr FORCEINIT;

    if ((op = popOp()) == T_LPAREN)
        return false;

    rhsExpr = NULL;
    if (op != T_120 &&
        (((opTable[op - T_EROOT].operandFlags & O_BINARY) && (rhsExpr = popExpr()) == NULL) ||
         (lhsExpr = popExpr()) == NULL))
        return true;

    switch (op) {
    case T_ARRAYIDX:
        pushOp(D_DEREF);
        opSP->prec = 100;
        op         = T_PLUS;
        if (isValidIndex(&rhsExpr->attr))
            rhsExpr = sub_1ccc(rhsExpr, DT_CONST);
        else
            prError("illegal type for index expression");
        break;
    case T_PREINC:
    case T_POSTINC:
    case T_PREDEC:
    case T_POSTDEC:
        rhsExpr = &eOne;
        op      = op == T_PREINC    ? P1_EQPLUS
                  : op == T_PREDEC  ? P1_EQMINUS
                  : op == T_POSTINC ? P1_POSTINC
                                    : P1_POSTDEC;
        break;
    case T_POINTER:
        op      = T_DOT;
        lhsExpr = parseExpr(D_DEREF, lhsExpr, 0); /* added dummy 3rd arg */
        break;
    case T_SIZEOF:
        if (lhsExpr->tType == T_SCONST) {
            pe = newIntLeaf((long)lhsExpr->t_chCnt + 1, DT_UINT);
            freeExpr(lhsExpr);
            pushExpr(pe);
            return false;
        }
        if (lhsExpr->tType != S_TYPE && lhsExpr->tType != T_ID) {
            pe                = newSTypeLeaf(&lhsExpr->attr);
            pe->attr.pExpr   = NULL;
            pe->attr.nodeType = 0;
            if (lhsExpr->attr.nodeType == EXPRNODE) {
                pe      = parseExpr(T_SIZEOF, pe, 0);
                rhsExpr = sub_1ccc(cloneExpr(lhsExpr->attr.pExpr), DT_UINT);
                op      = T_MUL;
            }
            freeExpr(lhsExpr);
            lhsExpr = pe;
        } else if (lhsExpr->tType == S_TYPE && lhsExpr->attr.nodeType == EXPRNODE) {
            rhsExpr = sub_1ccc(cloneExpr(lhsExpr->attr.pExpr), DT_UINT);
            lhsExpr = parseExpr(T_SIZEOF, lhsExpr, 0);
            op      = T_MUL;
        }
        break;
    case T_COMMA:
        if (opSP[0].op != T_LPAREN || opSP[1].op != D_FUNC)
            op = T_SEMICOLON;
        break;
    case T_CAST:
        pushExpr(typeAlign(parseExpr(T_EROOT, rhsExpr, 0), &lhsExpr->attr));
        freeExpr(lhsExpr);
        return false;
    }
    if ((op == T_QUEST) != (rhsExpr && rhsExpr->tType == T_COLON))
        return true;
    pushExpr(parseExpr(op, lhsExpr, rhsExpr));
    return false;
}

/**************************************************
 * 24: 1340 PMO +++
 * Optimised uint8_t param
 **************************************************/
expr_t *sub_1340(register expr_t *st, expr_t *p2) {
    sym_t *var2;
    sym_t *var4;

    if (!isVarOfType(&st->attr, DT_STRUCT) && !isVarOfType(&st->attr, DT_UNION))
        prError("struct/union required");
    else if (p2->tType != T_ID)
        prError("struct/union member expected");
    else if ((var4 = st->a_nextSym) == 0)
        ;
    else if (!(var4->flags & 1))
        prError("undefined struct/union: %s", var4->nVName);
    else if ((var2 = findMember(var4, p2->t_pSym->nVName))) {
        sub_51cf(var2);
        st       = newExprItem(D_MEMBERID);
        st->t_id = var2->memberId;
        st->attr = var2->attr;
        freeExpr(p2);
        return st;
    }
    return p2;
}

/**************************************************
 * 25: 1441 PMO +++
 * Minor optimiser differences, but equivalent code
 * Also uint8_t parameter differences
 **************************************************/
expr_t *parseExpr(uint8_t p1, register expr_t *lhs, expr_t *rhs) {
    attr_t tmpExpr;
    expr_t *savedLhs;
    expr_t *minusLhs FORCEINIT;
    bool hasRhs;
    bool minusLhsValid;
    int16_t operatorFlags;
    char *opStr;
    uint8_t var13;

    hasRhs = (opTable[p1 - T_EROOT].operandFlags & O_BINARY) != 0;
    opStr  = opTable[p1 - T_EROOT].name;
    if (!lhs || (hasRhs && rhs == 0)) {
        freeExpr(lhs);
        if (hasRhs)
            freeExpr(rhs);
        return NULL;
    }
    minusLhsValid = false;
    operatorFlags = opTable[p1 - T_EROOT].operatorFlags;
    if (p1 == D_ADDRESSOF && lhs->tType == T_ID && (lhs->t_pSym->flags & S_REG))
        prError("can't take address of register variable");

    if (!(operatorFlags & OP_SIZEOF))
        lhs = sub_1e37(lhs);
    if (hasRhs && !(operatorFlags & OP_MEMBER))
        rhs = sub_1e37(rhs);

    if (p1 == D_FUNC) {
        if ((lhs->attr.indirection & 1) && lhs->attr.nodeType == SYMNODE)
            lhs = parseExpr(D_DEREF, lhs, 0); /* dummy 3rd arg */
    } else
        lhs = sub_1df0(lhs);

    if (hasRhs)
        rhs = sub_1df0(rhs);
    if ((operatorFlags & OP_RTOL) && !sub_1ef1(lhs)) {
        if (p1 == D_ADDRESSOF) {
            if (lhs->tType == D_ADDRESSOF && lhs->t_lhs->attr.nodeType == EXPRNODE)
                return lhs;
            else
                prError("can't take this address");
        } else
            prError("only lvalues may be assigned to or modified");
    }
    if ((operatorFlags & OP_DREF) &&
        (!(lhs->attr.indirection & 1) || lhs->attr.nodeType != SYMNODE))
        prError("pointer required");
    if (!(operatorFlags & (OP_RBOOL | OP_LBOOL))) {
        if (isVarOfType(&lhs->attr, DT_BOOL))
            lhs = sub_1ccc(lhs, DT_INT);
        if (hasRhs && isVarOfType(&rhs->attr, DT_BOOL))
            rhs = sub_1ccc(rhs, DT_INT);
    }
    switch (p1) {
    case T_EROOT:
        return lhs;
    case T_DOT:
        rhs = sub_1340(lhs, rhs);
        break;
    case T_121:
        tmpExpr          = curFuncNode->attr;
        tmpExpr.nodeType = SYMNODE;
        if (isVarOfType(&tmpExpr, DT_VOID))
            prError("void function cannot return value");
        else
            lhs = sub_1f5d(lhs, &tmpExpr, true);
        break;
    }
    if ((operatorFlags & (OP_LBOOL | OP_RBOOL))) {
        if ((operatorFlags & OP_LBOOL))
            lhs = makeBool(lhs);
        if ((operatorFlags & OP_RBOOL))
            rhs = makeBool(rhs);
    } else if ((operatorFlags & OP_SCALE) && (lhs->attr.indirection & 1) &&
               lhs->attr.nodeType == SYMNODE && isIntType(&rhs->attr)) /* 16e1 */
        rhs = sub_1ccc(parseExpr(T_STAR, rhs, sub_1ebd(lhs)),
                       (rhs->attr.dataType & DT_UNSIGNED) ? DT_UCONST : DT_CONST);
    else if (p1 == T_PLUS && (rhs->attr.indirection & 1) && rhs->attr.nodeType == SYMNODE &&
             isIntType(&lhs->attr)) { /* 1740 */
        savedLhs = lhs;
        lhs      = rhs;
        rhs      = sub_1ccc(parseExpr(T_STAR, savedLhs, sub_1ebd(lhs)),
                       (rhs->attr.dataType & DT_UNSIGNED) ? DT_UCONST : DT_CONST);
    } else if ((operatorFlags & 8) && (lhs->attr.indirection & 1) &&
               lhs->attr.nodeType == SYMNODE &&
               (!hasRhs ||
                ((rhs->attr.indirection & 1) && rhs->attr.nodeType == SYMNODE))) { /* 17ab */
        if (!(operatorFlags & OP_EREL) || (!isVoidStar(&lhs->attr) && !isVoidStar(&rhs->attr))) {
            if (hasRhs && !haveSameDataType(&lhs->attr, &rhs->attr))
                prWarning("operands of %.3s not same pointer type", opStr);
            else if (p1 == T_MINUS) {
                minusLhs      = lhs;
                minusLhsValid = true;
                lhs           = sub_1ccc(lhs, DT_CONST);
                rhs           = sub_1ccc(rhs, DT_CONST);
            }
        }
    } else if ((operatorFlags & (OP_FLOAT | OP_INT)) && isSimpleType(&lhs->attr) &&
               (!hasRhs || isSimpleType(&rhs->attr))) { /* 187a */
        if (operatorFlags & OP_UNSIGNED) {
            var13 = getResultDataType(lhs, rhs);
            lhs   = sub_1ccc(lhs, var13);
            rhs   = sub_1ccc(rhs, var13);
        } /* 18fa */
        if (!(operatorFlags & OP_FLOAT) &&
            (!isIntType(&lhs->attr) || (hasRhs && !isIntType(&rhs->attr))))
            prError("integral type required");
    } else if (operatorFlags & OP_VOIDFUNC) { /* 1937 */
        if (isVarOfType(&lhs->attr, DT_VOID) || (hasRhs && isVarOfType(&rhs->attr, DT_VOID))) {
            if (p1 == P1_CONVERT && lhs->tType == D_FUNC && isVarOfType(&rhs->attr, DT_VOID)) {
                lhs->attr = rhs->attr;
                freeExpr(rhs);
                return lhs;
            }
            prError("illegal use of void expression");
        } else if (!(operatorFlags & OP_SEP) && (!isLogicalType(&lhs->attr) ||
                                                 (hasRhs && !isLogicalType(&rhs->attr)))) /* 19cc */
            prError("simple type required for %.3s", opStr);
        else if (operatorFlags & OP_AREL) { /* 1a11 */
            if ((operatorFlags & OP_EREL)) {
                if (isZero(lhs) && (rhs->attr.indirection & 1) && rhs->attr.nodeType == SYMNODE)
                    lhs = typeAlign(lhs, &rhs->attr);
                else if (isZero(rhs) && (lhs->attr.indirection & 1) &&
                         lhs->attr.nodeType == SYMNODE)
                    rhs = typeAlign(rhs, &lhs->attr);
            } /* 1a95 */
            if (!haveSameDataType(&lhs->attr, &rhs->attr))
                prWarning("operands of %.3s not same type", opStr);
        }
    } else if (!(operatorFlags & OP_SEP)) /* 1ac3 */
        prError("type conflict");
    /* 1ad1 */
    if (operatorFlags & 0x400)
        rhs = sub_1f5d(rhs, &lhs->attr, !(operatorFlags & OP_SCALE));

    savedLhs = getResultAttr(p1, lhs, rhs);
    if (minusLhsValid)
        savedLhs = parseExpr(T_DIV, savedLhs, sub_1ebd(minusLhs));
    return savedLhs;
}

/**************************************************
 * 26: 1B4B PMO +++
 **************************************************/
expr_t *newIntLeaf(long num, uint8_t intDt) {
    register expr_t *st;

    st                = newIConstLeaf(num);
    st->attr.dataType = intDt;
    return st;
}

/**************************************************
 * 27: 1B70 PMO +++
 * uint8_t parameter
 **************************************************/
expr_t *newFConstLeaf(char *fltStr) {
    register expr_t *st;

    st                = newExprItem(T_FCONST);
    st->t_s           = fltStr;
    st->attr.dataType = DT_DOUBLE;
    return st;
}

/**************************************************
 * 28: 1B94 PMO +++
 * minor optimiser difference, equivalent code
 **************************************************/
expr_t *makeBool(register expr_t *st) {

    if (!isLogicalType(&st->attr))
        prError("logical type required");
    else if (!isVarOfType(&st->attr, DT_BOOL))
        st = parseExpr(T_NE, st, typeAlign(&eZero, &st->attr));

    return st;
}

/**************************************************
 * 29: 1BF7 PMO +++
 * minor optimiser difference, equivalent code
 **************************************************/
expr_t *typeAlign(register expr_t *pe, attr_t *pa) {
    expr_t *pf;

    if (pe->tType == D_FUNC && (pf = pe->t_lhs)->tType == T_ID &&
        (pf->t_pSym->flags & S_IMPLICIT)) {
        prWarning("%s() declared implicit int", pf->t_pSym->nVName);
        pf->t_pSym->flags &= ~S_IMPLICIT;
    }

    if (!haveSameDataType(&pe->attr, pa)) {
        if (pe->tType != T_ICONST || inData(pe))
            pe = newNode(P1_CONVERT, pe, newSTypeLeaf(pa));
        pe->attr = *pa;
    }
    return pe;
}

/**************************************************
 * 30: 1CCC PMO +++
 **************************************************/
expr_t *sub_1ccc(expr_t *p1, uint8_t newDt) {
    attr_t st;

    st.dataType    = newDt;
    st.indirection = 0;
    st.pExpr      = 0;
    st.nodeType    = 0;
    return typeAlign(p1, &st);
}

/**************************************************
 * 31: 1D02 PMO +++
 * uint8_t parameter
 **************************************************/
expr_t *sub_1d02(register expr_t *st) {

    if (st->tType == T_COMMA || st->tType == T_120)
        return st;
    if (st->a_nodeType == SYMNODE && !st->a_indirection) {
        if (st->a_dataType < DT_INT || st->a_dataType == DT_ENUM)
            return sub_1ccc(st, DT_INT);
        if (st->a_dataType == DT_FLOAT)
            return sub_1ccc(st, DT_DOUBLE);
    }
    return st;
}

/**************************************************
 * 32: 1D5A PMO +++
 **************************************************/
uint8_t getResultDataType(register expr_t *lhs, expr_t *rhs) {
    bool mkUnsigned;
    uint8_t resDataType;

    mkUnsigned  = (lhs->a_dataType & DT_UNSIGNED) || (rhs->a_dataType & DT_UNSIGNED);
    resDataType = lhs->a_dataType;
    if (resDataType < rhs->a_dataType)
        resDataType = rhs->a_dataType;
    if (resDataType < DT_INT)
        resDataType = DT_INT;
    if (resDataType == DT_FLOAT || resDataType == DT_DOUBLE)
        return DT_DOUBLE;
    if (resDataType == DT_ENUM)
        resDataType = DT_INT;
    if (mkUnsigned)
        return resDataType | 1;
    return resDataType;
}

/**************************************************
 * 33: 1DF0 PMO +++
 **************************************************/
expr_t *sub_1df0(register expr_t *st) {

    if (st->tType != T_ID || st->attr.nodeType != FUNCNODE)
        return st;
    st->attr.dataType    = DT_COMPLEX;
    st->attr.nodeType    = SYMNODE;
    st->a_nextSym        = st->t_pSym;
    st->attr.indirection = 0;
    return newAddressOfNode(st);
}

/**************************************************
 * 34: 1E37 PMO +++
 **************************************************/
expr_t *sub_1e37(register expr_t *st) {

    if (st->attr.nodeType == EXPRNODE)
        st = newAddressOfNode(st);
    return st;
}

/**************************************************
 * 35: 1E58 PMO +++
 * differences due to added 3rd arg and uint8_t param
 **************************************************/
expr_t *newAddressOfNode(register expr_t *st) {
    expr_t *pi;

    pi                = newNode(D_ADDRESSOF, st, 0); /* PMO missing 3rd arg. added 0 */
    pi->attr          = st->attr;
    pi->attr.pExpr   = 0;
    pi->attr.nodeType = SYMNODE;
    addIndirection(&pi->attr);
    return pi;
}

/**************************************************
 * 36: 1EBD PMO +++
 * differences due to added 3rd arg and uint8_t param
 **************************************************/
expr_t *sub_1ebd(register expr_t *st) {
    st = newSTypeLeaf(&st->attr);
    st->attr.indirection >>= 1;
    return parseExpr(T_SIZEOF, st, 0); /* PMO fixed missing 3rd arg */
}

/**************************************************
 * 37: 1EF1 PMO +++
 **************************************************/
bool sub_1ef1(register expr_t *st) {

    switch (st->tType) {
    case D_DEREF:
        return true;
    case T_ID:
        return (st->t_pSym->flags & S_VAR) && st->t_pSym->sclass != D_CONST &&
               st->attr.nodeType == SYMNODE;
    case T_DOT:
        return st->attr.nodeType == SYMNODE && sub_1ef1(st->t_lhs);
    }
    return false;
}

/**************************************************
 * 38: 1F5D PMO +++
 * minor differences due to uint8_t param
 **************************************************/
expr_t *sub_1f5d(register expr_t *src, attr_t *dAttr, bool unscaled) {
    attr_t *sAttr;

    sAttr = &src->attr;
    if (!haveSameDataType(sAttr, dAttr)) {
        if (isSimpleType(sAttr) && isSimpleType(dAttr)) {
            if (isIntType(dAttr) && isFloatType(sAttr))
                prWarning("implicit conversion of float to integer");
        } else if ((dAttr->indirection & 1) && dAttr->nodeType == SYMNODE && isIntType(sAttr)) {
            if (!unscaled && (isVarOfType(sAttr, DT_CONST) || isVarOfType(sAttr, DT_UCONST)))
                return src;
            if (!isZero(src)) /* a pointer can be set to a zero */
                prWarning("illegal conversion of integer to pointer");
        } else if ((sAttr->indirection & 1) && sAttr->nodeType == SYMNODE && isIntType(dAttr))
            prWarning("illegal conversion of pointer to integer");
        else if ((sAttr->indirection & 1) && sAttr->nodeType == SYMNODE &&
                 (dAttr->indirection & 1) && dAttr->nodeType == SYMNODE) {
            if (!isVoidStar(sAttr) && !isVoidStar(dAttr))
                prWarning("illegal conversion between pointer types");
        } else
            prError("illegal conversion");
    }
    return typeAlign(src, dAttr);
}

/**************************************************
 * 39: 2105 PMO +++
 **************************************************/
bool isZero(register expr_t *st) {

    switch (st->tType) {
    case T_ICONST:
        return st->t_ul == 0L; /* long */
    case P1_CONVERT:
        if (isIntType(&st->attr))
            return isZero(st->t_lhs);
        break;
    }
    return false;
}

/**************************************************
 * 40: 2157 PMO +++
 **************************************************/
bool releaseExprList(void) {
    register expr_t *st;

    if (exprFreeList == 0)
        return false;
    while ((st = exprFreeList)) {
        exprFreeList = st->t_lhs;
        free(st);
    }
    return true;
}

/**************************************************
 * 41: 2186 PMO +++
 **************************************************/
expr_t *newExprItem(uint8_t tok) {
    register expr_t *st;

    if (exprFreeList != 0) {
        st           = exprFreeList;
        exprFreeList = st->t_lhs;
        blkclr(st, sizeof(expr_t));
    } else
        st = xalloc(sizeof(expr_t));
    st->tType         = tok;
    st->attr.dataType = DT_VOID;
    return st;
}

/**************************************************
 * 42: 21C7 PMO +++
 * uint8_t paramater
 **************************************************/
expr_t *cloneExpr(register expr_t *st) {
    expr_t *l1;
    uint16_t operandFlags;

    l1           = newExprItem(0);
    *l1          = *st;
    operandFlags = opTable[st->tType - T_EROOT].operandFlags;
    if ((operandFlags & O_LEAF) || st->tType == T_120)
        return l1;

    l1->t_lhs = cloneExpr(st->t_lhs);
    if (operandFlags & O_BINARY)
        l1->t_rhs = cloneExpr(st->t_rhs);

    return l1;
}

/**************************************************
 * 43: 225A PMO +++
 * uint8_t parameter
 **************************************************/
expr_t *getResultAttr(uint8_t op, register expr_t *lhs, expr_t *rhs) {
    expr_t *res;

    if (op == P1_CONVERT && lhs->tType == T_ICONST) {
        lhs->attr = rhs->attr;
        freeExpr(rhs);
        return lhs;
    }
    res = newNode(op, lhs, rhs);

    switch (opTable[op - 60].nodeType) {
    case 1:
        res->attr = lhs->attr;
        break;
    case 2:
        res->attr = rhs->attr;
        break;
    case 4:
        res->attr = lhs->attr; /* address of */
        addIndirection(&res->attr);
        break;
    case 3:
        res->attr = lhs->attr;
        delIndirection(&res->attr); /* deref */
        break;
    case 5:
        res->attr.dataType = DT_INT; /* sizeof */
        break;
    case 6:
        res->attr.dataType = DT_BOOL; /* bool operators */
        break;
    case 7:
        res->attr.dataType = DT_VOID;
        break;
    }
    return res;
}

/**************************************************
 * 44: 23B4 PMO +++
 * uint8_t parameter
 **************************************************/
expr_t *newNode(uint8_t tok, register expr_t *lhs, expr_t *rhs) {
    expr_t *pi;

    pi = newExprItem(tok);
    if (tok != T_120) {
        pi->t_lhs = lhs;
        if (opTable[tok - T_EROOT].operandFlags & O_BINARY)
            pi->t_rhs = rhs;
    }
    return pi;
}

/**************************************************
 * 45: 240E PMO +++
 * uint8_t parameter
 **************************************************/
expr_t *newIdLeaf(register sym_t *st) {
    expr_t *pi;

    pi         = newExprItem(T_ID);
    pi->t_pSym = st;
    if ((st->flags & 0x10) || st->sclass == D_MEMBER)
        pi->attr = st->attr;
    return pi;
}

/**************************************************
 * 46: 245D PMO +++
 * uint8_t parameter
 **************************************************/
expr_t *newSConstLeaf(void) {
    register expr_t *st;

    st                   = newExprItem(T_SCONST);
    st->attr.dataType    = DT_CHAR;
    st->attr.indirection = 1;
    st->t_id             = ++strId;
    return st;
}

/**************************************************
 * 47: 248A PMO +++
 * uint8_t parameter
 **************************************************/
expr_t *newIConstLeaf(long p1) {
    register expr_t *st;

    st      = newExprItem(T_ICONST);
    st->t_l = p1;
    return st;
}

/**************************************************
 * 48: 24B6 PMO +++
 * uint8_t parameter
 **************************************************/
expr_t *newSTypeLeaf(attr_t *p1) {
    register expr_t *st;

    st       = newExprItem(S_TYPE);
    st->attr = *p1;
    return st;
}

/**************************************************
 * 49: 24DE PMO +++
 **************************************************/
void complexErr(void) {

    fatalErr("expression too complex");
}

/**************************************************
 * 50: 24E7 PMO +++
 **************************************************/
void pushExpr(expr_t *p1) {

    if (exprSP == exprStk)
        complexErr();
    *(--exprSP) = p1;
}

/**************************************************
 * 51: 250A PMO +++
 **************************************************/
expr_t *popExpr(void) {

    if (exprSP != &exprStk[20])
        return *(exprSP++);
    return NULL;
}

/**************************************************
 * 52: 2529 PMO +++
 **************************************************/
void pushOp(uint8_t p1) {
    register opStk_t *st;

    if (opSP == opStk)
        complexErr();
    (--opSP)->op      = p1;
    (st = opSP)->prec = opTable[p1 - T_EROOT].prec;
}

/**************************************************
 * 53: 255D PMO +++
 **************************************************/
uint8_t popOp(void) {

    return (opSP++)->op;
}

/**************************************************
 * 54: 2569 PMO +++
 **************************************************/
void freeExpr(register expr_t *st) {
    uint8_t op;

    if (st) {
        op = st->tType;
        if (!(opTable[op - T_EROOT].operandFlags & O_LEAF) && op != T_120) {
            freeExpr(st->t_lhs);
            if (opTable[op - T_EROOT].operandFlags & O_BINARY)
                freeExpr(st->t_rhs);
        }
        if (!inData(st)) {
            if (op == T_FCONST)
                free(st->t_s);
            st->t_lhs    = exprFreeList; /* but on free list for quick reuse */
            exprFreeList = st;
        }
    }
}

/**************************************************
 * 55: 25F7 PMO +++
 * uint8_t parameter + minor optimisation difference
 * code is equivalent
 **************************************************/
expr_t *sub_25f7(register expr_t *st) {

    if (st) {
        if (!inData(st) && st->tType == T_ICONST) {
            st->t_ul += 1;
        } else if (st->tType == T_PLUS)
            st->t_rhs = sub_25f7(st->t_rhs);
        else
            st = parseExpr(T_PLUS, st, newIntLeaf(1L, DT_INT)); /* m3: */
    }
    return st; /* m4: */
}
