/*
 *
 * The stmt.c file is part of the restored P1.COM program
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

void parseStmt(int16_t p1, int16_t p2, register case_t *p3, int16_t *p4);
void parseCompoundStmt(int16_t p1, int16_t p2, case_t *p3, int16_t *p4);
void parseAsmStmt(void);
void parseWhileStmt(case_t *p3);
void parseDoStmt(case_t *p3);
void parseIfStmt(int16_t p1, int16_t p2, case_t *p3, int16_t *p4);
void parseSwitchStmt(int16_t p1);
void parseForStmt(case_t *p1);
void parseBreak_ContinueStmt(int16_t label);
void parseDefaultStmt(int16_t p1, int16_t p2, register case_t *p3, int16_t *p4);
void parseCastStmt(int16_t p1, int16_t p2, register case_t *p3, int16_t *p4);
void parseReturnStmt(void);
void parseGotoStmt(void);
void parseStmtLabel(register sym_t *ps, int16_t p1, int16_t p2, case_t *p3, int16_t *p4);
sym_t *sub_4ca4(register sym_t *ps);
void sub_4ce8(int16_t n);
void sub_4d15(int16_t n, register expr_t *st, char c);
void sub_4d67(register expr_t *st);

/**************************************************
 * 84: 409B PMO +++
 * use of uint8_t parameter
 **************************************************/
void parseFunction(void) {
    uint8_t tok;

    enterScope();
    sub_5c19(D_STACK);
    defineFuncSig();
    if ((tok = yylex()) != T_LBRACE) {
        expectErr("{");
        skipStmt(tok);
    }
    emitLabelDef(curFuncNode);
    unreachable = false;
    sub_5c19(0x14);
    returnLabel = newTmpLabel();
    while ((tok = yylex()) != T_RBRACE) {
        ungetTok = tok;
        parseStmt(0, 0, 0, 0);
    }
    if (!unreachable && !voidReturn)
        prWarning("implicit return at end of non-void function");
    emitLocalLabelDef(returnLabel);
    exitScope();
}

/**************************************************
 * 85: 4126 PMO +++
 * trivial optimiser differences, use of uint8_t param
 * and addition of dummy parameters
 **************************************************/
void parseStmt(int16_t p1, int16_t p2, register case_t *p3, int16_t *p4) {
    uint8_t tok;
    expr_t *var3;

    tok = yylex();
    if (unreachable && tok != T_SEMI && tok != T_LBRACE) {
        if (tok != T_CASE && tok != T_DEFAULT && (tok != T_ID || peekCh() != ':'))
            prWarning("Unreachable code");
        unreachable = false;
    }
    switch (tok) {
    case T_SEMI:
        break;
    case T_LBRACE:
        parseCompoundStmt(p1, p2, p3, p4);
        break;
    case T_ASM:
        parseAsmStmt();
        /* FALLTHRU */
    case T_WHILE:
        parseWhileStmt(p3);
        break;
    case T_DO:
        parseDoStmt(p3);
        break;
    case T_FOR:
        parseForStmt(p3);
        break;
    case T_IF:
        parseIfStmt(p1, p2, p3, p4);
        break;
    case T_SWITCH:
        parseSwitchStmt(p1);
        break;
    case T_CASE:
        parseCastStmt(p1, p2, p3, p4);
        break;
    case T_DEFAULT:
        parseDefaultStmt(p1, p2, p3, p4);
        break;
    case T_BREAK:
        if (p4)
            *p4 = 1;
        parseBreak_ContinueStmt(p2);
        break;
    case T_CONTINUE:
        parseBreak_ContinueStmt(p1);
        break;
    case T_RETURN:
        parseReturnStmt();
        break;
    case T_GOTO:
        parseGotoStmt();
        break;
    case T_ELSE:
        prError("inappropriate 'else'");
        break;
    case T_ID:
        if (peekCh() == ':') {
            tok = yylex();
            parseStmtLabel(yylval.ySym, p1, p2, p3, p4);
            break;
        }
        /* FALLTHRU */
    default:
        ungetTok = tok;
        var3     = parseExpr(T_EROOT, sub_0bfc(), 0); /* dummy 3rd arg added */
        emitCast(var3);
        freeExpr(var3);
        expect(T_SEMI, ";");
        break;
    }
}

/**************************************************
 * 86: 4300 PMO +++
 * trivial optimiser differences and  use of uint8_t param
 **************************************************/
void parseCompoundStmt(int16_t p1, int16_t p2, case_t *p3, int16_t *p4) {
    bool haveDecl;
    uint8_t tok;

    haveDecl = (tok = yylex()) == S_CLASS || tok == S_TYPE ||
               (tok == T_ID && yylval.ySym->sclass == T_TYPEDEF);
    if (haveDecl) {
        ungetTok = tok;
        enterScope();
        sub_5c19(T_AUTO);
        tok = yylex();
    }
    while (tok != T_RBRACE) {
        ungetTok = tok;
        parseStmt(p1, p2, p3, p4);
        tok = yylex();
    }
    if (haveDecl)
        exitScope();
}

/**************************************************
 * 87: 4390 PMO +++
 * use of uint8_t and the code fix
 **************************************************/
void parseAsmStmt(void) {
    uint8_t tok;
    if ((tok = yylex()) != T_LPAREN) {
        expectErr("(");
        ungetTok = tok;
    }
    if ((tok = yylex()) != T_SCONST) {
        expectErr("string");
        ungetTok = tok;
    } else {
        printf(";; %s\n", yylval.yStr);
        free(yylval.yStr);
    }
#ifdef BUGGY
    if ((tok = yylex()) != ')') {
#else
    /* fix to check against token for ) i.e. T_RPAREN */
    if ((tok = yylex()) != T_RPAREN) {
#endif
        expectErr(")");
        ungetTok = tok;
    }
    expect(T_SEMI, ";");
}
/**************************************************
 * 88: 4406 PMO +++
 * trivial optimiser differences and  use of uint8_t param
 **************************************************/
void parseWhileStmt(case_t *p3) {
    uint8_t tok;
    int16_t continueLabel;
    int16_t breakLabel;
    int16_t loopLabel;
    register expr_t *pe;

    if ((tok = yylex()) != T_LPAREN) {
        expectErr("(");
        ungetTok = tok;
    }
    sub_4ce8(continueLabel = newTmpLabel());
    emitLocalLabelDef(loopLabel = newTmpLabel());
    pe = sub_0bfc();
    if ((tok = yylex()) != T_RPAREN) {
        expectErr(")");
        ungetTok = tok;
    }
    parseStmt(continueLabel, breakLabel = newTmpLabel(), p3, 0);
    emitLocalLabelDef(continueLabel);
    sub_4d15(loopLabel, pe, 1);
    emitLocalLabelDef(breakLabel);
    unreachable = false;
}

/**************************************************
 * 89: 44AF PMO +++
 * trivial optimiser differences and  use of uint8_t param
 **************************************************/
void parseDoStmt(case_t *p3) {
    uint8_t tok;
    int16_t continueLabel;
    int16_t breakLabel;
    int16_t loopLabel;
    register expr_t *pe;

    continueLabel = newTmpLabel();
    breakLabel    = newTmpLabel();
    emitLocalLabelDef(loopLabel = newTmpLabel());
    parseStmt(continueLabel, breakLabel, p3, 0);
    emitLocalLabelDef(continueLabel);
    if ((tok = yylex()) != T_WHILE)
        expectErr("while");
    if (tok == T_WHILE || tok == T_FOR)
        tok = yylex();
    else if (tok != T_LPAREN) {
        skipStmt(tok);
        return;
    }
    if (tok != T_LPAREN) {
        expectErr("(");
        ungetTok = tok;
    }
    pe = sub_0bfc();
    expect(T_RPAREN, ")");
    sub_4d15(loopLabel, pe, 1);
    emitLocalLabelDef(breakLabel);
    unreachable = false;
    if ((tok = yylex()) != T_SEMI)
        expectErr(";");
}

/**************************************************
 * 90: 4595 PMO +++
 * trivial optimiser differences and  use of uint8_t param
 **************************************************/
void parseIfStmt(int16_t p1, int16_t p2, case_t *p3, int16_t *p4) {
    uint8_t tok;
    uint16_t endElseLabel;
    uint16_t endIfLabel;
    uint8_t endifUnreachable;
    register expr_t *pe;

    if ((tok = yylex()) != T_LPAREN) {
        expectErr("(");
        ungetTok = tok;
    }
    pe = sub_0bfc();
    if ((tok = yylex()) != T_RPAREN) {
        expectErr(")");
        ungetTok = tok;
    }
    endIfLabel = newTmpLabel();
    sub_4d15(endIfLabel, pe, 0);
    parseStmt(p1, p2, p3, p4);
    endifUnreachable = unreachable;
    unreachable      = false;
    if ((tok = yylex()) == T_ELSE) {
        sub_4ce8(endElseLabel = newTmpLabel());
        emitLocalLabelDef(endIfLabel);
        parseStmt(p1, p2, p3, p4);
        unreachable = unreachable && endifUnreachable;
        emitLocalLabelDef(endElseLabel);
    } else {
        ungetTok = tok;
        emitLocalLabelDef(endIfLabel);
    }
}

/**************************************************
 * 91: 469B PMO +++
 * trivial optimiser differences, use of uint8_t param
 * and addition of dummy paramaters
 **************************************************/
void parseSwitchStmt(int16_t p1) {
    uint8_t tok;
    int16_t endLabel;
    int16_t var5;
    int16_t haveBreak;
    int16_t cnt;
    case_t caseInfo;
    register attr_t *ps;

    if ((tok = yylex()) != T_LPAREN) {
        expectErr("(");
        ungetTok = tok;
    }
    haveBreak         = 0;
    caseInfo.defLabel = 0;
    caseInfo.caseCnt  = 0;
    if ((caseInfo.switchExpr = parseExpr(T_EROOT, sub_0bfc(), 0))) {
        ps = &caseInfo.switchExpr->attr;
        if (!isVarOfType(ps, DT_ENUM) && (!isIntType(ps) || ps->dataType >= DT_LONG))
            prError("illegal type for switch expression");
    }

    if ((tok = yylex()) != T_RPAREN) {
        expectErr(")");
        ungetTok = tok;
    }
    endLabel = newTmpLabel();
    var5     = newTmpLabel();
    sub_4ce8(var5);
    unreachable = true;
    parseStmt(p1, endLabel, &caseInfo, &haveBreak);
    if (caseInfo.defLabel == 0) {
        caseInfo.defLabel = endLabel;
        haveBreak         = true;
    }
    sub_4ce8(endLabel);
    emitLocalLabelDef(var5);
    emitCase(&caseInfo);
    freeExpr(caseInfo.switchExpr);
    cnt = caseInfo.caseCnt;
    while (--cnt >= 0)
        freeExpr(caseInfo.caseOptions[cnt].caseVal);
    emitLocalLabelDef(endLabel);
    unreachable = !haveBreak;
}

/**************************************************
 * 92: 4838 PMO +++
 * trivial optimiser differences, use of uint8_t param
 * and addition of dummy paramaters
 **************************************************/
void parseForStmt(case_t *p1) {
    int16_t continueLabel;
    int16_t breakLabel;
    int16_t bodyLabel;
    int16_t condLabel;
    int16_t haveCond;
    uint8_t tok;
    expr_t *condExpr;
    expr_t *stepExpr;
    register expr_t *st;

    haveCond = false;
    tok      = yylex();
    if (tok != T_LPAREN)
        expectErr("(");

    if ((tok = yylex()) != T_SEMI) {
        ungetTok = tok;
        st       = parseExpr(T_EROOT, sub_0bfc(), 0);
        emitCast(st);
        freeExpr(st);
        expect(T_SEMI, ";");
    }
    if ((tok = yylex()) != T_SEMI) {
        haveCond = true;
        ungetTok = tok;
        condExpr = sub_0bfc();
        expect(T_SEMI, ";");
    } else
        condExpr = NULL;
    if ((tok = yylex()) != T_RPAREN) {
        ungetTok = tok;
        stepExpr = parseExpr(T_EROOT, sub_0bfc(), 0);
        tok      = yylex();
        if (tok != T_RPAREN) {
            expectErr(")");
            ungetTok = tok;
        }
    } else
        stepExpr = NULL;
    bodyLabel     = newTmpLabel();
    breakLabel    = newTmpLabel();
    continueLabel = newTmpLabel();
    if (condExpr)
        sub_4ce8(condLabel = newTmpLabel());
    emitLocalLabelDef(bodyLabel);
    parseStmt(continueLabel, breakLabel, p1, &haveCond);
    emitLocalLabelDef(continueLabel);
    if (stepExpr) {
        emitCast(stepExpr);
        freeExpr(stepExpr);
    }
    if (condExpr) {
        emitLocalLabelDef(condLabel);
        sub_4d15(bodyLabel, condExpr, 1);
    } else
        sub_4ce8(bodyLabel);
    emitLocalLabelDef(breakLabel);
    unreachable = !haveCond;
}

/**************************************************
 * 93: 49E1 PMO +++
 * trivial optimiser differences
 **************************************************/
void parseBreak_ContinueStmt(int16_t label) {
    uint8_t tok;
    if (label) {
        sub_4ce8(label);
        unreachable = true;
    } else
        prError("inappropriate break/continue");
    if ((tok = yylex()) != T_SEMI)
        expectErr(";");
}

/**************************************************
 * 94: 4A1E PMO +++
 **************************************************/
void parseDefaultStmt(int16_t p1, int16_t p2, register case_t *p3, int16_t *p4) {
    uint8_t tok;

    if ((tok = yylex()) != T_COLON)
        expectErr(":");
    if (p3)
        if (p3->defLabel)
            prError("default case redefined");
        else
            emitLocalLabelDef(p3->defLabel = newTmpLabel());
    else
        prError("'default' not in switch");
    unreachable = false;
    parseStmt(p1, p2, p3, p4);
}

/**************************************************
 * 95: 4A90 PMO +++
 * trivial optimiser differences and  use of uint8_t param
 **************************************************/
void parseCastStmt(int16_t p1, int16_t p2, register case_t *p3, int16_t *p4) {
    uint8_t tok;
    expr_t *var3;
    int16_t caseLabel;
    int16_t caseIdx;
    s4_t *var9;

    var3 = parseConstExpr(1);
    if ((tok = yylex()) != T_COLON) {
        expectErr(":");
        ungetTok = tok;
    }
    emitLocalLabelDef(caseLabel = newTmpLabel());
    if (p3) {
        if ((caseIdx = p3->caseCnt++) == 255)
            fatalErr("Too many cases in switch");
        var9            = &p3->caseOptions[caseIdx];
        var9->caseLabel = caseLabel;
        if (var3 && p3->switchExpr) {
            var3          = parseExpr(0x7d, newSTypeLeaf(&p3->switchExpr->attr), var3);
            var9->caseVal = var3->t_rhs;
            var3->t_rhs   = NULL;
            freeExpr(var3);
        }
    } else
        prError("'case' not in switch");
    unreachable = false;
    parseStmt(p1, p2, p3, p4);
}

/**************************************************
 * 96: 4BAA PMO +++
 * trivial optimiser differences and  use of uint8_t param
 **************************************************/
void parseReturnStmt(void) {
    uint8_t tok;
    if ((tok = yylex()) != T_SEMI) {
        ungetTok = tok;
        sub_4d67(parseExpr(T_EROOT, sub_0bfc(), 0));
        if (yylex() != T_SEMI) {
            expectErr(";");
            ungetTok = tok;
        }
    } else if (!voidReturn)
        prWarning("non-void function returns no value");
    sub_4ce8(returnLabel);
    unreachable = true;
}

/**************************************************
 * 97: 4C03 PMO +++
 * trivial optimiser differences and  use of uint8_t param
 **************************************************/
void parseGotoStmt(void) {
    uint8_t tok;
    register sym_t *ps;

    if ((tok = yylex()) != T_ID)
        expectErr("label identifier");
    else {
        ps = sub_4ca4(yylval.ySym);
        if (ps) {
            sub_4ce8(ps->a_labelId);
            ps->flags |= 2;
        }
        unreachable = true;
        tok         = yylex();
        if (tok != T_SEMI)
            expectErr(";");
    }
}

/**************************************************
 * 98: 4C57 PMO +++
 **************************************************/
void parseStmtLabel(register sym_t *ps, int16_t p1, int16_t p2, case_t *p3, int16_t *p4) {
    ps = sub_4ca4(ps);
    if (ps) {
        emitLocalLabelDef(ps->a_labelId);
        ps->flags |= 1;
    }
    unreachable = false;
    parseStmt(p1, p2, p3, p4);
}

/**************************************************
 * 99: 4CA4 PMO +++
 * difference due to two additional dummy parameters
 **************************************************/
sym_t *sub_4ca4(register sym_t *ps) {
    if (ps->sclass) {
        if (ps->sclass != D_LABEL) {
            prError("not a label identifier: %s", ps->nVName);
            return NULL;
        }
    } else {
        ps        = sub_4eed(ps, D_LABEL, 0, 0);
        ps->level = 1;
    }
    return ps;
}

/**************************************************
 * 100: 4CE8 PMO +++
 * differences due to dummy parameter and
 * use of uint8_t param
 **************************************************/
void sub_4ce8(int16_t n) {
    register expr_t *st;
    st = parseExpr(P1_COND, newIConstLeaf(n), 0);
    emitCast(st);
    freeExpr(st);
}

/**************************************************
 * 101: 4D15 PMO +++
 * differences due to dummy parameter and
 * use of uint8_t param
 **************************************************/
void sub_4d15(int16_t n, register expr_t *st, char c) {

    if (st) {
        if (c == 0)
            st = parseExpr(T_LNOT, st, 0);

        st = parseExpr(T_123, st, newIConstLeaf(n));
        emitCast(st);
        freeExpr(st);
    }
}

/**************************************************
 * 102: 4D67 PMO +++
 * differences due to dummy parameter and
 * use of uint8_t param
 **************************************************/
void sub_4d67(register expr_t *st) {

    if (st) {
        st = parseExpr(T_121, st, 0);
        emitCast(st);
        freeExpr(st);
    }
}
