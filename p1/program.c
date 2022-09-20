/*
 *
 * The program.c file is part of the restored P1.COM program
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

int8_t depth;       /* a288 */
uint8_t voidReturn;  /* a289 */
bool unreachable;   /* a28a */
int16_t returnLabel;  /* a28b */
sym_t *curFuncNode; /* a28d */
sym_t *p25_a28f;    /* ad8f */

int16_t parseInitializer(register sym_t *st, bool p2);

/**************************************************
 * 81: 3ADF +++
 * minor differences due to adding missing arg and use
 * of uint8_t paramater
 * one use of add a,255 vs sub a,1 i.e. equivalent
 **************************************************/
void sub_3adf(void) {
    uint8_t tok;
    uint8_t scType;
    attr_t attr;
    uint8_t varb;
    uint8_t scFlags;

    register sym_t *st;

    scFlags = sub_5dd1(&scType, &attr);
    if ((tok = yylex()) == T_SEMI)
        return;
    ungetTok = tok;
    varb     = true;

    for (;;) {
        p25_a28f = 0;
        st       = sub_69ca(scType, &attr, scFlags & ~1, 0);
        tok      = yylex();

        if (st && (st->flags & S_VAR) && st->a_nodeType == FUNCNODE) {
            if (varb && tok != T_COMMA && tok != T_SEMI && scType != T_TYPEDEF) {
                voidReturn = st->a_nodeType == FUNCNODE && st->a_indirection == 0 &&
                            (st->a_dataType == DT_VOID || st->a_dataType == DT_INT);
                ungetTok = tok;
                defineArg(st);
                emitVar(st);
                curFuncNode = st;
                parseFunction();
                return;
            }
            if (p25_a28f && !(p25_a28f->flags & 8))
                expectErr("function body");
            ++depth;
            releaseScopeSym();
            --depth;
            emitVar(st);
        } else if (tok == T_EQ) {
            if (scType == T_TYPEDEF)
                prError("illegal initialisation");
            defineArg(st);
            emitVar(st);
            sub_3c7e(st);
            tok = yylex();
        } else if (st) {
            if ((scFlags & 1) || st->sclass != T_EXTERN) {
                defineArg(st);
                emitVar(st);
            } else
                emitDependentVar(st);
        }
        if (tok == T_ID || tok == T_STAR) {
            expectErr(",");
            ungetTok = tok;
        } else if (tok != T_COMMA)
            break;
        varb = false;
    }

    if (tok != T_SEMI) {
        expectErr(";");
        while (tok > T_RBRACE)
            tok = yylex();
    }
}

/**************************************************
 * 82: 3C7E PMO +++
 * use of uint8_t param
 **************************************************/
void sub_3c7e(sym_t *p1) {
    int16_t var2;
    register sym_t *st;

    if (p1) {
        printf("[i ");
        emitSymName(p1, stdout);
        putchar('\n');
        st = p1;
        if ((var2 = parseInitializer(st, true)) < 0) {
            prError("initialisation syntax");
            skipToSemi();
        } else if (st->a_nodeType == EXPRNODE && st->a_expr && isZero(st->a_expr)) {
            freeExpr(st->a_expr);
            st->a_expr = newIConstLeaf(var2);
        }
        printf("]\n");
    } else
        skipToSemi();
}

/**************************************************
 * 83: 3D24 +++
 * minor optimiser differences including moving basic
 * blocks. Use of uint8_t parameter
 **************************************************/
int16_t parseInitializer(register sym_t *st, bool p2) {
    int16_t initCnt;
    uint8_t tok;
    char *s;



#ifdef CPM
    /* manual string optimisation */
    static char Ustr[] = ":U ..\n";
    static char Dstr[] = "..\n";
#else
#define Ustr ":U ..\n"
#define Dstr "..\n"
#endif

    initCnt = -1;
    if (p2 && st->a_nodeType == EXPRNODE && st->a_expr) {
        bool inBraces;

        printf(":U ..\n");
        if ((inBraces = ((tok = yylex()) == T_LBRACE)))
            tok = yylex();
        if (tok == T_SCONST && st->attr.indirection == 0 && (st->attr.dataType & ~1) == DT_CHAR) {
            for (initCnt = 0, s = yylval.yStr; initCnt < strChCnt; initCnt++)
                printf("-> %d `c\n", *s++);
            free(yylval.yStr);
            if (isZero(st->a_expr)) {
                printf("-> %d `c\n", 0);
                ++initCnt;
            }
            if (inBraces)
                tok = yylex();
        } else if (!inBraces) /* 3e4a */
            expectErr("{");
        else {
            ungetTok = tok;
            if (st->a_indirection == 0 && st->a_dataType == DT_COMPLEX)
                st = st->a_nextSym;
            else
                p2 = false;
            initCnt = 0;
            for (;;) {
                if (parseInitializer(st, p2) < 0)
                    break;
                initCnt++;
                if ((tok = yylex()) == T_RBRACE || tok != T_COMMA || (tok = yylex()) == T_RBRACE)
                    break;
                ungetTok = tok;
            }
        }
        /* 3e22 */
        if (inBraces && tok != T_RBRACE) { /* end of initialiser list */
            expectErr("}");
            initCnt = -1;
        }
        printf(Dstr);
    } else if ((!p2 || st->a_nodeType != EXPRNODE) && st->a_indirection == 0 &&
               st->a_dataType == DT_STRUCT) { /* 3ec6 */
        sym_t *pNextSym;
        sym_t *pMember;
        bool inBraces;

        if (p2)
            printf(Ustr);
        printf(Ustr);
        if ((pNextSym = st->a_nextSym)) {
            if (!(inBraces = (tok = yylex()) == T_LBRACE))
                ungetTok = tok;
            pMember = pNextSym->memberList;
            do {
                if ((parseInitializer(pMember, true) < 0))
                    break;
                if ((pMember = pMember->memberList) == pNextSym) /* end of circular list */
                    break;
                if ((tok = yylex()) != T_COMMA) { /* end of this set of initialisers */
                    ungetTok = tok;
                    break;
                }
            } while (!inBraces || (ungetTok = tok = yylex()) != T_RBRACE);
            /* 3f7c: */
            if (inBraces) {
                if ((tok = yylex()) == T_COMMA) /* allow trailing , before } */
                    tok = yylex();
                if (tok != T_RBRACE)
                    expectErr("}");
                else
                    initCnt = 1;
            } else
                initCnt = 1;
        } /* 3fcd */
        printf(Dstr);
        if (p2)
            printf(Dstr);

    } else if ((p2 && st->attr.nodeType == EXPRNODE) || st->attr.nodeType == FUNCNODE ||
               (!(st->a_indirection & 1) && st->attr.dataType >= T_AUTO))
        prError("illegal initialisation");
    else {
        expr_t *vard;
        bool inBraces ;

        if (!(inBraces = (tok = yylex()) == T_LBRACE))
            ungetTok = tok;
        vard          = newSTypeLeaf(&st->attr);
        vard->attr.nodeType = SYMNODE;
        if ((vard = parseExpr(T_125, vard, parseConstExpr(3))))
            sub_05b5(vard->t_rhs);

        if (inBraces && yylex() != T_RBRACE)
            expectErr("}");
        freeExpr(vard);
        initCnt = 1;
    }
    return initCnt;
}
