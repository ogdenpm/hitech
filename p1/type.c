/*
 *
 * The type.c file is part of the restored P1.COM program
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

void sub_5c50(void);
void sub_6531(register sym_t *st);
args_t *parseArgs(uint16_t p1);
void parseDeclaration(uint8_t p1);
uint16_t normaliseIndirection(uint16_t n);

/**************************************************
 * 132: 5BE1 PMO +++
 **************************************************/
void addIndirection(register attr_t *st) {
    uint16_t ch;
    ch = st->indirection;
    if (ch & 0x8000)
        prError("too much indirection");
    st->indirection = (ch << 1) | 1;
}

/**************************************************
 * 133: 5C19 PMO +++
 **************************************************/
void sub_5c19(uint8_t sclass) {
    register sym_t *st; /* may not be needed */
    uint8_t tok;

    defSClass = sclass;
    for (;;) {
        ungetTok = tok = yylex();
        if (tok == S_CLASS || tok == S_TYPE ||
            (tok == T_ID && (st = yylval.ySym)->sclass == T_TYPEDEF))
            sub_5c50();
        else
            break;
    }
    defSClass = 0;
}

/**************************************************
 * 134: 5C50 PMO +++
 * trivial optimiser differences, use of uint8_t arg
 * and dummy arg
 **************************************************/
void sub_5c50(void) {
    uint8_t scType;
    attr_t attr;
    uint8_t tok;
    uint8_t scFlags;
    uint8_t varc;
    bool vard;
    register sym_t *st;

    scFlags = sub_5dd1(&scType, &attr);
    if (scType != D_STACK && scType != T_REGISTER && defSClass == D_STACK) {
        prError("only register storage class allowed");
        scType = D_STACK;
    }
    if ((tok = yylex()) == T_SEMI)
        return;
    ungetTok = tok;
    for (;;) {
        st   = sub_69ca(scType, &attr, scFlags & ~1, 0); /* dummy last param */
        vard = st && (st->flags & S_VAR) && st->attr.nodeType == FUNCNODE;
        varc = (scFlags & 1) && scType != D_STACK && !vard;
        if ((tok = yylex()) == T_EQ) {
            if (vard || scType == D_STACK || scType == T_EXTERN || scType == T_TYPEDEF)
                prError("illegal initialisation");
            if (scType == T_STATIC || scType == T_EXTERN) {
                defineArg(st);
                if (depth && scType == T_STATIC)
                    st->flags |= S_NAMEID;
                emitVar(st);
                sub_3c7e(st);
            } else {
                defineArg(st);
                emitVar(st);
                sub_6531(st);
            }
            tok = yylex();
        } else if (scType != D_STACK) {
            if (varc)
                defineArg(st);
            if (depth && scType == T_STATIC)
                st->flags |= S_NAMEID;
            emitVar(st);
        } /* 5d95 */
        if (tok == T_ID || tok == T_STAR) {
            expectErr(",");
            ungetTok = tok;
        } else if (tok != T_COMMA) {
            if (tok != T_SEMI) {
                expectErr(";");
                skipStmt(tok);
            }
            return;
        }
    }
}

/**************************************************
 * 135: 5DD1 PMO +++
 * use of uint8_t arg
 * some optimisations different some better some worse
 **************************************************/
uint8_t sub_5dd1(uint8_t *pscType, register attr_t *attr) {
    uint8_t scType;
    uint8_t dataType;
    int16_t sizeIndicator; /* -1 short, 0 int, 1 long */
    bool isUnsigned;
    uint8_t tok;
    uint8_t scFlags; /* storage class */
    sym_t *var9;
    sym_t *ps;

    attr->indirection = 0;
    attr->pExpr      = 0;
    attr->nextSym   = NULL;
    attr->nodeType    = 0;
    scType = dataType = 0;
    sizeIndicator     = 0;
    isUnsigned        = false;
    scFlags           = 0;

    for (;;) {
        if ((tok = yylex()) == S_CLASS) {
            if (pscType == NULL)
                prError("storage class illegal");
            else {
                switch (tok = yylval.yVal) {
                case T_REGISTER:
                    scFlags |= S_REG;
                    break;
                case T_AUTO:
                    if (!depth)
                        prError("bad storage class");
                    /* FALLTHRU */
                case T_STATIC:
                case T_TYPEDEF:
                    scFlags |= S_MEM;
                    /* FALLTHRU */
                case T_EXTERN:
                    if (scType && scType != tok)
                        prError("inconsistent storage class");
                    else
                        scType = tok;
                    break;
                }
            }
        } else if (tok == S_TYPE) { /* 5e78 */
            switch (tok = yylval.yVal) {
            case T_SHORT:
                sizeIndicator--;
                break;
            case T_LONG:
                sizeIndicator++;
                break;
            case T_UNSIGNED:
                isUnsigned = true;
                break;
            case T_UNION:
                dataType        = DT_UNION;
                attr->nextSym = sub_60db(D_UNION);
                if (attr->nextSym)
                    sub_51cf(attr->nextSym);
                break;
            case T_STRUCT:
                dataType        = DT_STRUCT;
                attr->nextSym = sub_60db(D_STRUCT);
                if (attr->nextSym)
                    sub_51cf(attr->nextSym);
                break;
            case T_ENUM:
                dataType        = DT_ENUM;
                attr->nextSym = sub_6360();
                sub_51cf(attr->nextSym);
                break;
            case T_CHAR:
            case T_DOUBLE:
            case T_FLOAT:
            case T_INT:
            case T_VOID:
                if (dataType)
                    prError("inconsistent type");
                else
                    dataType = tok == T_INT     ? DT_INT
                               : tok == T_CHAR  ? DT_CHAR
                               : tok == T_VOID  ? DT_VOID
                               : tok == T_FLOAT ? DT_FLOAT
                                                : DT_DOUBLE;
                break;
            }
        } else if (tok == T_ID && yylval.ySym->sclass == T_TYPEDEF && dataType == 0) { /* 5f68 */
            ps = yylval.ySym;
            sub_51cf(ps);
            var9 = ps;
            if (var9->a_nodeType) {
                dataType        = DT_COMPLEX;
                attr->nextSym = ps;
            } else {
                dataType          = var9->a_dataType;
                attr->u1          = var9->attr.u1;
                attr->u2          = var9->attr.u2;
                attr->indirection = var9->attr.indirection;
            }
        } else
            break;

    } /* 6003 */
    ungetTok = tok;
    if (scType == 0) {
        scType = depth ? defSClass : T_EXTERN;
        scFlags |= S_MEM;
    }
    if ((scFlags & S_REG) && scType != T_AUTO && scType != D_STACK && scType != D_14 &&
        scType != D_15)
        prError("can't be a register");
    if (dataType == 0)
        dataType = DT_INT;
    if (sizeIndicator > 0) {
        if (dataType == DT_FLOAT || dataType == DT_INT)
            dataType += 2; /* to DT_DOUBLE or DT_LONG*/
        else
            prError("can't be long");
    } else if (sizeIndicator < 0) {
        if (dataType == DT_INT)
            dataType = DT_SHORT;
        else
            prError("can't be short");
    }
    if (isUnsigned) {
        if (dataType < DT_FLOAT)
            dataType |= 1;
        else
            prError("can't be unsigned");
    }
    if (pscType)
        *pscType = scType;
    attr->dataType = dataType;
    return scFlags;
}

/**************************************************
 * 136: 60DB PMO +++
 * differences due to dummy args, use of uint8_t args
 * and equivalent optimiser differences.
 **************************************************/
sym_t *sub_60db(uint8_t p1) {
    sym_t *pSym;
    sym_t **ppMembers;
    uint8_t tok;
    int16_t id;
    attr_t attr;
    register sym_t *st;

    byte_8f85 = true;
    tok       = yylex();
    byte_8f85 = false;
    if (tok == T_ID) {
        st = yylval.ySym;
        if (st->sclass != p1)
            st = sub_4eed(st, p1, 0, 0);
        tok = yylex();
    } else {
        st = sub_4eed(newTmpSym(), p1, 0, 0);
        if (tok != T_LBRACE)
            expectErr("struct/union tag or '{'");
    }
    ppMembers = NULL;
    if (tok == T_LBRACE) {
        if ((st->flags & (S_NAMEID | S_MEM)) == S_MEM)
            prError("struct/union redefined: %s", st->nVName);
        else
            ppMembers = &st->memberList;
        id = 0;
        for (;;) {
            sub_5dd1(0, &attr);
            lexMember = true;
            do {
                pSym = sub_69ca(D_MEMBER, &attr, 0, st);
                if (pSym) {
                    if (pSym->attr.nodeType == FUNCNODE)
                        prError("members cannot be functions");
                    defineArg(pSym);
                    if (ppMembers) {
                        *ppMembers = pSym;
                        ppMembers  = &pSym->memberList;
                    }
                    pSym->memberId = id++;
                }
                if ((tok = yylex()) == T_COLON) {
                    if (!(pSym->attr.dataType & DT_UNSIGNED))
                        pSym->attr.dataType |= DT_UNSIGNED;
                    if (!isVarOfType(&pSym->attr, DT_UINT))
                        prError("bad bitfield type");
                    if ((tok = yylex()) != T_ICONST)
                        prError("integer constant expected");
                    else {
                        if (!pSym) {
                            defineArg(pSym = sub_4eed(newTmpSym(), D_MEMBER, &attr, st));
                            if (ppMembers) {
                                *ppMembers = pSym;
                                ppMembers  = &pSym->memberList;
                            }
                            pSym->memberId = id++;
                        } /* 62ce */
                        pSym->flags |= S_BITFIELD;
                        pSym->bwidth = (int16_t)yylval.yNum;
                        tok          = yylex();
                    }
                }
            } while (tok == T_COMMA); /* 62f2 */
            lexMember = false;
            if (tok != T_SEMI)
                expectErr(";");
            if ((tok = yylex()) == T_RBRACE) {
                if (!(st->flags & S_MEM))
                    defineArg(st);
                if (ppMembers) {
                    *ppMembers = st;
                    emitStructUnion(st, p1);
                }
                return st;
            }
            ungetTok = tok;
        }
    }
    ungetTok = tok;
    return st;
}
/**************************************************
 * 137: 6360 PMO +++
 * differences due to dummy and uint8_t args
 **************************************************/
sym_t *sub_6360(void) {
    attr_t var8;
    sym_t *vara;
    expr_t *varc;
    int16_t vare;
    uint8_t tok;
    register sym_t *st;

    if ((tok = yylex()) == T_ID) {
        st = yylval.ySym;
        if ((tok = yylex()) != T_LBRACE) {
            if (!(st->flags & S_MEM))
                prError("undefined enum tab: %s", st->nVName);
            ungetTok = tok;
        }
    } else if (tok == T_LBRACE)
        st = newTmpSym();
    else {
        expectErr("enum tag or {");
        st = NULL;
    }
    if (tok == T_LBRACE) {
        defineArg(st = sub_4eed(st, D_ENUM, 0, 0));
        var8.dataType    = DT_ENUM;
        var8.nextSym   = st;
        var8.indirection = 0;
        var8.pExpr      = NULL;
        var8.nodeType    = SYMNODE;
        printf("[c ");
        emitSymName(st, stdout);
        putchar('\n');
        vare = 0;
        varc = newIntLeaf(0, DT_INT);
        for (;;) {
            if ((tok = yylex()) != T_ID) {
                expectErr("identifier");
                break;
            } else { /* 6474 */
                if ((vara = sub_4eed(yylval.ySym, DT_CONST, &var8, st)))
                    vara->memberId = vare++;
                if ((tok = yylex()) == T_EQ) {
                    freeExpr(varc);
                    parseConstExpr(T_LBRACE);
                    if (!isIntType(&varc->attr) || varc->attr.dataType >= DT_LONG)
                        prError("integer expression required");
                    tok = yylex();
                }
                defineArg(vara);
                sub_05d3(varc);
                if (tok != T_COMMA)
                    break;
                varc = sub_25f7(varc);
            }
        }
        printf(".. ]\n");
        freeExpr(varc);
        if (tok != T_RBRACE) {
            expectErr("}");
            skipStmt(tok);
        }
    }
    return st;
}
/**************************************************
 * 138: 6531 PMO +++
 * differences due to dummy and uint8_t args
 **************************************************/
void sub_6531(register sym_t *st) {
    expr_t *var2;
    uint8_t tok;
    bool var4;

    if (st && !isLogicalType(&st->attr)) {
        prError("can't initialise auto aggregates");
        skipToSemi();
    } else {
        if (!(var4 = (tok = yylex()) == T_LBRACE))
            ungetTok = tok;
        if ((var2 = parseExpr(T_EROOT, sub_07f5(T_RBRACE), 0)) && st) {
            var2 = parseExpr(T_EQ, newIdLeaf(st), var2);
            emitCast(var2);
            freeExpr(var2);
        }
        if (var4 && yylex() != T_RBRACE)
            expectErr("}");
    }
}

/**************************************************
 * 139: 65E2 PMO +++
 * equivalent optimiser differences including basic
 * block moves
 * differences due to dummy and uint8_t args
 **************************************************/
args_t *parseArgs(uint16_t p1) {
    uint8_t scType;
    attr_t attr;
    attr_t *pAttr;
    uint8_t tok;
    sym_t *vare FORCEINIT;
    uint8_t scFlags;
    uint8_t var10;
    bool protoArg;
    bool nonProtoArg;
    attr_t var1a;
    int16_t i;
    struct {
        int16_t cnt;
        attr_t argVec[128];
    } args;
    register sym_t *st;

    var10             = defSClass;
    defSClass         = D_15;
    args.cnt          = 0;
    nonProtoArg       = false;
    protoArg          = false;
    var1a.dataType    = DT_INT;
    var1a.indirection = 0;
    var1a.pExpr      = 0;
    var1a.nodeType    = 0;
    for (;;) { /* 6619 */
        if ((tok = yylex()) == T_3DOT) {
            args.argVec[args.cnt].dataType      = DT_VARGS;
            args.argVec[args.cnt].pExpr        = 0;
            args.argVec[args.cnt].nodeType      = 0;
            args.argVec[args.cnt++].indirection = 0;
            tok                                  = yylex();
            break;
        } /* 66db */
        if (tok == T_ID && yylval.ySym->sclass != T_TYPEDEF)
            if (p1)
                nonProtoArg = true;
            else
                prError("type specifier reqd. for proto arg");
        else
            protoArg = true;
        if (protoArg && nonProtoArg) {
            nonProtoArg = false;
            prError("can't mix proto and non-proto args");
        }
        ungetTok = tok;
        scFlags  = sub_5dd1(&scType, &attr);
        if (scType != D_15 && scType != T_REGISTER)
            prError("bad storage class");
        scType = p1 ? D_15 : D_14;
        st     = sub_69ca(scType, &attr, scFlags & ~1, 0);
        pAttr  = &st->attr;
        if (pAttr->nodeType == FUNCNODE) {
            pAttr->nextSym   = sub_4eed(newTmpSym(), T_TYPEDEF, pAttr, 0);
            pAttr->dataType    = DT_COMPLEX;
            pAttr->nodeType    = 0;
            pAttr->indirection = 1;
        }
        if (protoArg)
            cloneAttr(pAttr, &args.argVec[args.cnt++]);
        scFlags &= ~1;
        scType = D_STACK;
        st     = sub_4eed(st, scType, protoArg ? pAttr : &var1a, 0);
        if (p1 && !isVarOfType(pAttr, T_AUTO)) {
            if (!p25_a28f) {
                p25_a28f = st;
                vare     = st;
                st->flags |= scFlags | S_ARGDECL;
            } else if (st->flags & S_ARGDECL) /* 6893 */
                prError("argument redeclared: %s", st->nVName);
            else {
                vare->memberList = st;
                st->flags |= scFlags | S_ARGDECL;
                vare = st;
            }
            if (protoArg)
                st->flags |= 0x208;
            st->memberList = 0;
        }
        if ((tok = yylex()) == T_EQ) {
            prError("can't initialize arg");
            skipStmt(tok);
        }
        if (tok == T_ID || tok == S_CLASS || tok == S_TYPE) {
            expectErr(",");
            ungetTok = tok;
        } else if (tok != T_COMMA)
            break;
    } /* 669c */
    defSClass = var10;
    if (tok != T_RPAREN) {
        expectErr(")");
        skipStmt(tok);
    }
    if (args.cnt == 0)
        return 0;
    i = args.cnt;
    while (i--) {
        if (args.argVec[i].nodeType == EXPRNODE) {
            args.argVec[i].nodeType = SYMNODE;
            freeExpr(args.argVec[i].pExpr);
            addIndirection(&args.argVec[i]);
        }
    }
    return cloneArgs((args_t *)&args);
}

/**************************************************
 * 140: 69CA PMO +++
 * minor code optimiser differences and deltas
 * due to dummy and uit8_t args
 **************************************************/
sym_t *sub_69ca(uint8_t p1, register attr_t *p2, uint8_t p3, sym_t *p4) {
    uint16_t indirection;
    sym_t *var4;
    decl_t *savDecl;
    decl_t decl;
    uint8_t tok;
    attr_t attr;

    savDecl              = curDecl;
    curDecl              = &decl;
    attr.pExpr          = NULL; /* other options */
    attr.nextSym       = NULL;
    attr.nodeType        = 0;
    attr.indirection     = 0;
    attr.dataType        = 0;
    curDecl->pAttr       = &attr;
    curDecl->indirection = 0;
    curDecl->pSym1       = NULL;
    curDecl->pSym2       = NULL;
    curDecl->uca         = false;
    curDecl->needDim     = false;
    curDecl->badInd  = false;
    curDecl->ucb         = false;
    parseDeclaration(p1);
    ungetTok = tok = yylex();
    if (curDecl->ucb) {
        if (p1 == T_CAST || p1 == D_14 || p1 == D_15 || (p1 == D_MEMBER && tok == T_COLON)) {
            curDecl->pSym1 = newTmpSym();
            if (p1 == T_CAST)
                p1 = T_TYPEDEF;
        } else
            prError("no identifier in declaration");
    } /* 6aaf */
    curDecl->pAttr->dataType = p2->dataType;
    curDecl->pAttr->u1       = p2->u1;

    for (indirection = p2->indirection; indirection; indirection >>= 1) {
        if (curDecl->indirection & 1) {
            curDecl->badInd = true;
            break;
        }
        curDecl->indirection = (curDecl->indirection >> 1) | ((indirection & 1) << 15);
    }
    /* ^^^ */
    for (;;) {
        if (curDecl->pAttr->nodeType == SYMNODE && curDecl->pAttr->dataType == DT_COMPLEX &&
            (curDecl->indirection == 0 || curDecl->pAttr->nextAttr->nodeType == SYMNODE)) {
            for (indirection = curDecl->pAttr->nextAttr->indirection; indirection;
                 indirection >>= 1) {
                if (curDecl->indirection & 1) {
                    curDecl->badInd = true;
                    break;
                }
                curDecl->indirection = (curDecl->indirection >> 1) | ((indirection & 1) << 15);
            }
            cloneAttr(curDecl->pAttr->nextAttr, curDecl->pAttr);
        } else
            break;
    } /* 6c13 vvv */
    if (curDecl->badInd)
        prError("declarator too complex");
    curDecl->pAttr->indirection = normaliseIndirection(curDecl->indirection);
    if (curDecl->pSym1 && p1 != T_TYPEDEF && p1 != D_14 && p1 != D_15 &&
        isVarOfType(curDecl->pAttr, DT_VOID) && curDecl->pAttr->nodeType != FUNCNODE)
        prError("only functions may be void");
    else if (isVarOfType(curDecl->pAttr, DT_COMPLEX)) {
        if (curDecl->pAttr->nodeType == FUNCNODE &&
            curDecl->pAttr->nextAttr->nodeType == EXPRNODE)
            prError("functions can't return arrays");
        else if (curDecl->pAttr->nodeType == EXPRNODE &&
                 curDecl->pAttr->nextAttr->nodeType == FUNCNODE)
            prError("can't have array of functions");
    }
    if (curDecl->pSym2) {
        curDecl->pSym2 = sub_4eed(curDecl->pSym2, T_TYPEDEF, &curDecl->pSym2->attr, 0);
        defineArg(curDecl->pSym2);
        sub_51cf(curDecl->pSym2);
        if (curDecl->pSym2->attr.nodeType != FUNCNODE || !(curDecl->pSym2->flags & 0x80))
            emitVar(curDecl->pSym2);
    } /* 6d95 */
    if (p1 != T_TYPEDEF && curDecl->pAttr->indirection == 0 &&
        (isVarOfType(p2, DT_STRUCT) || isVarOfType(p2, DT_UNION)) && p2->nextSym &&
        !(p2->nextSym->flags & 1))
        prError("undefined struct/union: %s", curDecl->pAttr->nextSym->nVName);
    if (curDecl->pSym1) { /* 6e0b */
        if (defSClass == D_STACK && p1 != D_MEMBER) {
            if (curDecl->pSym1->flags & 8)
                prError("argument redeclared: %s", curDecl->pSym1->nVName);
            else if (!(curDecl->pSym1->flags & S_ARGDECL))
                prError("not an argument: %s", curDecl->pSym1->nVName);
            else {
                curDecl->pSym1->flags |= p3 | 8;
                curDecl->pSym1->attr = attr;
                if (isVarOfType(&attr, DT_FLOAT)) {
                    prWarning("float param coerced to double");
                    curDecl->pSym1->attr.dataType = DT_DOUBLE;
                }
            }
        } else if (defSClass != D_14 && defSClass != D_15) { /* 6ecd */
            if (p1 == T_AUTO && attr.nodeType == FUNCNODE)
                p1 = T_EXTERN;
            if ((curDecl->pSym1 = sub_4eed(curDecl->pSym1, p1, &attr, p4)))
                curDecl->pSym1->flags |= p3;
        } else {
            if (curDecl->pSym1->sclass && curDecl->pSym1->level != depth) /* 6f39 */
                curDecl->pSym1 = sub_4eed(curDecl->pSym1, 0, &attr, 0);
            curDecl->pSym1->attr = attr;
        }
    }
    /* 6f91 */
    var4    = curDecl->pSym1;
    curDecl = savDecl;
    return var4;
}
/**************************************************
 * 141: 6FAB PMO +++
 * minor equivalent optimiser differences
 * differnces due to dummy & uint8_t args
 **************************************************/
void parseDeclaration(uint8_t p1) {
    bool savLexMember;
    uint8_t starCnt;
    uint8_t tok;
    uint8_t sclass;
    uint8_t var5;
    register expr_t *st;

    byte_a29a = false;
    sclass    = 1;
    for (starCnt = 0; (tok = yylex()) == T_STAR; starCnt++)
        ;
    if (tok == T_ID) {
        curDecl->pSym1 = yylval.ySym;
        tok            = yylex();
        sclass         = curDecl->pSym1->sclass;
        if (!curDecl->pSym1->sclass)
            curDecl->pSym1->sclass = p1;
        byte_a29a = p1 != D_14;
    } else if (tok == T_LPAREN) { /* 701b */
        ungetTok = tok = yylex();
        if (tok == T_RPAREN || tok == S_CLASS || tok == S_TYPE ||
            (tok == T_ID && yylval.ySym->sclass == T_TYPEDEF))
            tok = T_LPAREN;
        else {
            parseDeclaration(p1);
            if ((tok = yylex()) != T_RPAREN)
                expectErr(")");
            tok = yylex();
        }
    } /* 707b */
    curDecl->ucb = curDecl->pSym1 == NULL;
    for (;;) { /* 7091 */
        if (tok == T_LPAREN) {
            if (curDecl->needDim) {
                prError("can't have array of functions");
                curDecl->needDim = false;
            }
            if (curDecl->pAttr->nodeType == FUNCNODE && curDecl->indirection == 0)
                prError("functions can't return functions");
            if (curDecl->indirection & 0x8000) { /* 70e7 */
                curDecl->pAttr->dataType    = DT_COMPLEX;
                curDecl->pAttr->indirection = normaliseIndirection(curDecl->indirection);
                curDecl->indirection        = 0;
                curDecl->pAttr->nextSym   = newTmpSym();
                if (curDecl->pSym2)
                    curDecl->pSym2 = sub_4eed(curDecl->pSym2, T_TYPEDEF, &curDecl->pSym2->attr, 0);
                curDecl->pSym2 = curDecl->pAttr->nextSym;
                curDecl->pAttr = &curDecl->pSym2->attr;
            } /* 7195 */
            curDecl->pAttr->nodeType = FUNCNODE;
            byte_a29a                = byte_a29a && !depth;
            if (!byte_a29a) {
                var5 = true;
                depth++;
            } else
                var5 = false;
            /* 71cc */
            depth++;
            if ((tok = yylex()) == S_CLASS || tok == S_TYPE || tok == T_ID) {
                ungetTok               = tok;
                curDecl->pAttr->pFargs = parseArgs(byte_a29a);
            } else if (tok != T_RPAREN) {
                expectErr(")");
                skipStmt(tok);
            }
            byte_a29a = false;
            if (var5) {
                releaseScopeSym();
                depth--;
            }
            depth--;
        } else if (tok == T_LBRACK) { /* 7248 */
            if (curDecl->pAttr->nodeType == FUNCNODE)
                prError("functions can't return arrays");
            if (curDecl->uca || (curDecl->indirection & 0x8000)) {
                curDecl->uca                = false;
                curDecl->pAttr->dataType    = DT_COMPLEX;
                curDecl->pAttr->indirection = normaliseIndirection(curDecl->indirection);
                curDecl->indirection        = 0;
                curDecl->pAttr->nextSym   = newTmpSym();
                if (curDecl->pSym2)
                    curDecl->pSym2 = sub_4eed(curDecl->pSym2, T_TYPEDEF, &curDecl->pSym2->attr, 0);
                curDecl->pSym2 = curDecl->pAttr->nextSym;
                curDecl->pAttr = &curDecl->pSym2->attr;
            } /* 732a */
            savLexMember = lexMember;
            lexMember    = false;
            if ((tok = yylex()) == T_RBRACK) {
                if (curDecl->needDim)
                    prError("dimension required");
                st = &eZero;
            } else {
                ungetTok = tok;
                st       = parseConstExpr(T_SEMI);
                if ((tok = yylex()) != T_RBRACK) {
                    expectErr("]");
                    skipStmt(tok);
                }
            } /* 738a */
            curDecl->uca             = true;
            curDecl->needDim         = true;
            lexMember                = savLexMember;
            curDecl->pAttr->nodeType = EXPRNODE;
            curDecl->pAttr->pExpr   = st;
        } else { /* 73c1 */
            ungetTok = tok;
            if (!sclass)
                curDecl->pSym1->sclass = 0;
            if (!starCnt)
                return;
            curDecl->needDim = false;
            do {
                if (curDecl->indirection & 1)
                    curDecl->badInd = true;
                else
                    curDecl->indirection = (curDecl->indirection >> 1) | 0x8000; /* rotate */
            } while (--starCnt);
            return;
        }
        tok = yylex();
    }
}

/**************************************************
 * 142: 742A PMO +++
 **************************************************/
uint16_t normaliseIndirection(uint16_t n) {
    if (n)
        while (!(n & 1))
            n >>= 1;
    return n;
}

/**************************************************
 * 143: 7454 PMO +++
 **************************************************/
void emitAttr(register attr_t *st) {
    uint16_t indirection;
    uint8_t dataType;

    putchar('`');
    for (;;) {
        if (st->nodeType == FUNCNODE)
            putchar('(');
        for (indirection = st->indirection; indirection; indirection >>= 1)
            if (indirection & 1)
                putchar('*');
        if (st->dataType == DT_COMPLEX && st->nextAttr->nodeType == FUNCNODE)
            st = st->nextAttr;
        else
            break;
    }
    dataType = st->dataType;
    switch (dataType) {
    case DT_ENUM:
    case DT_COMPLEX:
        emitSymName(st->nextSym, stdout);
        break;
    case DT_STRUCT:
    case DT_UNION:
        printf("S%d", st->nextSym->a_labelId);
        break;
    default:
        if (dataType & 1) {
            putchar('u');
            dataType &= ~1;
        }
        putchar("?bcsilxfd?v"[dataType >> 1]);
        break;
    }
}
