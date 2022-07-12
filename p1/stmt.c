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
void parseStmtGroup(int16_t p1, int16_t p2, case_t *p3, int16_t *p4);
void parseStmtAsm(void);
void parseStmtWhile(case_t *p3);
void parseStmtDo(case_t *p3);
void parseStmtIf(int16_t p1, int16_t p2, case_t *p3, int16_t *p4);
void parseStmtSwitch(int16_t p1);
void parseStmtFor(case_t *p1);
void parseStmtBreak_Continue(int16_t label);
void parseStmtDefault(int16_t p1, int16_t p2, register case_t *p3, int16_t *p4);
void parseStmtCase(int16_t p1, int16_t p2, register case_t *p3, int16_t *p4);
void parseStmtReturn(void);
void parseStmtGoto(void);
void parseStmtLabel(register sym_t *ps, int16_t p1, int16_t p2, case_t *p3, int16_t *p4);
sym_t *sub_4ca4(register sym_t *ps);
void sub_4ce8(int16_t n);
void sub_4d15(int16_t n, register expr_t *st, char c);
void sub_4d67(register expr_t *st);

/**************************************************
 * 84: 409B PMO +++
 * use of uint8_t parameter
 **************************************************/
void sub_409b(void) {
    uint8_t tok;

    enterScope();
    sub_5c19(6);
    sub_51e7();
    if ((tok = yylex()) != T_LBRACE) {
        expectErr("{");
        skipStmt(tok);
    }
    sub_0273(curFuncNode);
    unreachable = false;
    sub_5c19(0x14);
    word_a28b = newTmpLabel();
    while ((tok = yylex()) != T_RBRACE) {
        ungetTok = tok;
        parseStmt(0, 0, 0, 0);
    }
    if (!unreachable && !byte_a289)
        prWarning("implicit return at end of non-void function");
    emitLabelDef(word_a28b);
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
        parseStmtGroup(p1, p2, p3, p4);
        break;
    case T_ASM:
        parseStmtAsm();
        /* FALLTHRU */
    case T_WHILE:
        parseStmtWhile(p3);
        break;
    case T_DO:
        parseStmtDo(p3);
        break;
    case T_FOR:
        parseStmtFor(p3);
        break;
    case T_IF:
        parseStmtIf(p1, p2, p3, p4);
        break;
    case T_SWITCH:
        parseStmtSwitch(p1);
        break;
    case T_CASE:
        parseStmtCase(p1, p2, p3, p4);
        break;
    case T_DEFAULT:
        parseStmtDefault(p1, p2, p3, p4);
        break;
    case T_BREAK:
        if (p4)
            *p4 = 1;
        parseStmtBreak_Continue(p2);
        break;
    case T_CONTINUE:
        parseStmtBreak_Continue(p1);
        break;
    case T_RETURN:
        parseStmtReturn();
        break;
    case T_GOTO:
        parseStmtGoto();
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
        var3     = sub_1441(0x3c, sub_0bfc(), 0); /* dummy 3rd arg added */
        sub_042d(var3);
        sub_2569(var3);
        expect(T_SEMI, ";");
        break;
    }
}

/**************************************************
 * 86: 4300 PMO +++
 * trivial optimiser differences and  use of uint8_t param
 **************************************************/
void parseStmtGroup(int16_t p1, int16_t p2, case_t *p3, int16_t *p4) {
    bool haveDecl;
    uint8_t tok;

    haveDecl = (tok = yylex()) == S_CLASS || tok == S_TYPE ||
               (tok == T_ID && yylval.ySym->m20 == T_TYPEDEF);
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
void parseStmtAsm(void) {
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
void parseStmtWhile(case_t *p3) {
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
    emitLabelDef(loopLabel = newTmpLabel());
    pe  = sub_0bfc();
    if ((tok = yylex()) != T_RPAREN) {
        expectErr(")");
        ungetTok = tok;
    }
    parseStmt(continueLabel, breakLabel = newTmpLabel(), p3, 0);
    emitLabelDef(continueLabel);
    sub_4d15(loopLabel, pe, 1);
    emitLabelDef(breakLabel);
    unreachable = false;
}

/**************************************************
 * 89: 44AF PMO +++
 * trivial optimiser differences and  use of uint8_t param
 **************************************************/
void parseStmtDo(case_t *p3) {
    uint8_t tok;
    int16_t continueLabel;
    int16_t breakLabel;
    int16_t loopLabel;
    register expr_t *pe;

    continueLabel = newTmpLabel();
    breakLabel    = newTmpLabel();
    emitLabelDef(loopLabel = newTmpLabel());
    parseStmt(continueLabel, breakLabel, p3, 0);
    emitLabelDef(continueLabel);
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
    emitLabelDef(breakLabel);
    unreachable = false;
    if ((tok = yylex()) != T_SEMI)
        expectErr(";");
}

/**************************************************
 * 90: 4595 PMO +++
 * trivial optimiser differences and  use of uint8_t param
 **************************************************/
void parseStmtIf(int16_t p1, int16_t p2, case_t *p3, int16_t *p4) {
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
        emitLabelDef(endIfLabel);
        parseStmt(p1, p2, p3, p4);
        unreachable = unreachable && endifUnreachable;
        emitLabelDef(endElseLabel);
    } else {
        ungetTok = tok;
        emitLabelDef(endIfLabel);
    }
}

/**************************************************
 * 91: 469B PMO +++
 * trivial optimiser differences, use of uint8_t param
 * and addition of dummy paramaters
 **************************************************/
void parseStmtSwitch(int16_t p1) {
    uint8_t tok;
    int16_t endLabel;
    int16_t var5;
    int16_t haveBreak;
    int16_t cnt;
    case_t caseInfo;
    register s8_t *ps;

    if ((tok = yylex()) != T_LPAREN) {
        expectErr("(");
        ungetTok = tok;
    }
    haveBreak         = 0;
    caseInfo.defLabel = 0;
    caseInfo.caseCnt  = 0;
    if ((caseInfo.switchExpr = sub_1441(T_60, sub_0bfc(), 0))) {
        ps = &caseInfo.switchExpr->attr;
        if (!sub_5a76(ps, DT_ENUM) && (!sub_5b08(ps) || ps->dataType >= DT_LONG))
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
    emitLabelDef(var5);
    sub_02a6(&caseInfo);
    sub_2569(caseInfo.switchExpr);
    cnt = caseInfo.caseCnt;
    while (--cnt >= 0)
        sub_2569(caseInfo.caseOptions[cnt].caseVal);
    emitLabelDef(endLabel);
    unreachable = !haveBreak;
}

/**************************************************
 * 92: 4838 PMO +++
 * trivial optimiser differences, use of uint8_t param
 * and addition of dummy paramaters
 **************************************************/
void parseStmtFor(case_t *p1) {
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
        st       = sub_1441(T_60, sub_0bfc(), 0);
        sub_042d(st);
        sub_2569(st);
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
        stepExpr = sub_1441(T_60, sub_0bfc(), 0);
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
    emitLabelDef(bodyLabel);
    parseStmt(continueLabel, breakLabel, p1, &haveCond);
    emitLabelDef(continueLabel);
    if (stepExpr) {
        sub_042d(stepExpr);
        sub_2569(stepExpr);
    }
    if (condExpr) {
        emitLabelDef(condLabel);
        sub_4d15(bodyLabel, condExpr, 1);
    } else
        sub_4ce8(bodyLabel);
    emitLabelDef(breakLabel);
    unreachable = !haveCond;
}

/**************************************************
 * 93: 49E1 PMO +++
 * trivial optimiser differences
 **************************************************/
void parseStmtBreak_Continue(int16_t label) {
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
void parseStmtDefault(int16_t p1, int16_t p2, register case_t *p3, int16_t *p4) {
    uint8_t tok;

    if ((tok = yylex()) != T_COLON)
        expectErr(":");
    if (p3)
        if (p3->defLabel)
            prError("default case redefined");
        else
            emitLabelDef(p3->defLabel = newTmpLabel());
    else
        prError("'default' not in switch");
    unreachable = false;
    parseStmt(p1, p2, p3, p4);
}

/**************************************************
 * 95: 4A90 PMO +++
 * trivial optimiser differences and  use of uint8_t param
 **************************************************/
void parseStmtCase(int16_t p1, int16_t p2, register case_t *p3, int16_t *p4) {
    uint8_t tok;
    expr_t *var3;
    int16_t caseLabel;
    int16_t caseIdx;
    s4_t *var9;

    var3 = sub_0a83(1);
    if ((tok = yylex()) != T_COLON) {
        expectErr(":");
        ungetTok = tok;
    }
    emitLabelDef(caseLabel = newTmpLabel());
    if (p3) {
        if ((caseIdx = p3->caseCnt++) == 255)
            fatalErr("Too many cases in switch");
        var9            = &p3->caseOptions[caseIdx];
        var9->caseLabel = caseLabel;
        if (var3 && p3->switchExpr) {
            var3        = sub_1441(0x7d, allocSType(&p3->switchExpr->attr), var3);
            var9->caseVal       = var3->t_alt;
            var3->t_alt = NULL;
            sub_2569(var3);
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
void parseStmtReturn(void) {
    uint8_t tok;
    if ((tok = yylex()) != T_SEMI) {
        ungetTok = tok;
        sub_4d67(sub_1441(T_60, sub_0bfc(), 0));
        if (yylex() != T_SEMI) {
            expectErr(";");
            ungetTok = tok;
        }
    } else if (!byte_a289)
        prWarning("non-void function returns no value");
    sub_4ce8(word_a28b);
    unreachable = true;
}

/**************************************************
 * 97: 4C03 PMO +++
 * trivial optimiser differences and  use of uint8_t param
 **************************************************/
void parseStmtGoto(void) {
    uint8_t tok;
    register sym_t *ps;

    if ((tok = yylex()) != T_ID)
        expectErr("label identifier");
    else {
        ps = sub_4ca4(yylval.ySym);
        if (ps) {
            sub_4ce8(ps->a_labelId);
            ps->m18 |= 2;
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
        emitLabelDef(ps->a_labelId);
        ps->m18 |= 1;
    }
    unreachable = false;
    parseStmt(p1, p2, p3, p4);
}

/**************************************************
 * 99: 4CA4 PMO +++
 * difference due to two additional dummy parameters
 **************************************************/
sym_t *sub_4ca4(register sym_t *ps) {
    if (ps->m20) {
        if (ps->m20 != D_LABEL) {
            prError("not a label identifier: %s", ps->nVName);
            return NULL;
        }
    } else {
        ps      = sub_4eed(ps, D_LABEL, 0, 0);
        ps->m21 = 1;
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
    st = sub_1441(T_122, allocIConst(n), 0);
    sub_042d(st);
    sub_2569(st);
}

/**************************************************
 * 101: 4D15 PMO +++
 * differences due to dummy parameter and
 * use of uint8_t param
 **************************************************/
void sub_4d15(int16_t n, register expr_t *st, char c) {

    if (st) {
        if (c == 0)
            st = sub_1441(T_LNOT, st, 0);

        st = sub_1441(T_123, st, allocIConst(n));
        sub_042d(st);
        sub_2569(st);
    }
}

/**************************************************
 * 102: 4D67 PMO +++
 * differences due to dummy parameter and
 * use of uint8_t param
 **************************************************/
void sub_4d67(register expr_t *st) {

    if (st) {
        st = sub_1441(T_121, st, 0);
        sub_042d(st);
        sub_2569(st);
    }
}
