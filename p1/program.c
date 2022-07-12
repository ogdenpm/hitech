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
uint8_t byte_a289;  /* a289 */
bool unreachable;   /* a28a */
int16_t word_a28b;  /* a28b */
sym_t *curFuncNode; /* a28d */
sym_t *p25_a28f;    /* ad8f */

int16_t sub_3d24(register sym_t *st, uint8_t p2);

/**************************************************
 * 81: 3ADF +++
 * minor differences due to adding missing arg and use
 * of uint8_t paramater
 * one use of add a,255 vs sub a,1 i.e. equivalent
 **************************************************/
void sub_3adf(void) {
    uint8_t tok;
    uint8_t scType;
    s8_t attr;
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

        if (st && (st->m18 & 0x10) && st->a_c7 == ANODE) {
            if (varb && tok != T_COMMA && tok != T_SEMI && scType != T_TYPEDEF) {
                byte_a289 = st->a_c7 == ANODE && st->a_i4 == 0 &&
                            (st->a_dataType == DT_VOID || st->a_dataType == DT_INT);
                ungetTok = tok;
                sub_516c(st);
                sub_0493(st);
                curFuncNode = st;
                sub_409b();
                return;
            }
            if (p25_a28f && !(p25_a28f->m18 & 8))
                expectErr("function body");
            ++depth;
            checkScopeExit();
            --depth;
            sub_0493(st);
        } else if (tok == T_EQ) {
            if (scType == T_TYPEDEF)
                prError("illegal initialisation");
            sub_516c(st);
            sub_0493(st);
            sub_3c7e(st);
            tok = yylex();
        } else if (st) {
            if ((scFlags & 1) || st->m20 != T_EXTERN) {
                sub_516c(st);
                sub_0493(st);
            } else
                sub_01ec(st);
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
        sub_573b(p1, stdout);
        putchar('\n');
        st = p1;
        if ((var2 = sub_3d24(st, 1)) < 0) {
            prError("initialisation syntax");
            skipToSemi();
        } else if (st->a_c7 == ENODE && st->a_expr && sub_2105(st->a_expr)) {
            sub_2569(st->a_expr);
            st->a_expr = allocIConst(var2);
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
int16_t sub_3d24(register sym_t *st, uint8_t p2) {
    int16_t var2;
    uint8_t tok;
    char *var5;
    bool haveLbrace;
    sym_t *var8;
    sym_t *vara;
    bool varb;
    expr_t *vard;
    bool vare;

#ifdef CPM
    /* manual string optimisation */
    static char Ustr[] = ":U ..\n";
    static char Dstr[] = "..\n";
#else
#define Ustr ":U ..\n"
#define Dstr "..\n"
#endif

    var2 = -1;
    if (p2 && st->a_c7 == ENODE && st->a_expr) {
        printf(":U ..\n");
        if ((haveLbrace = ((tok = yylex()) == T_LBRACE)))
            tok = yylex();
        if (tok == T_SCONST && st->attr.i4 == 0 && (st->attr.dataType & ~1) == 4) {
            var2 = 0;
            var5 = yylval.yStr;
            while (var2 < strChCnt) {
                printf("-> %d `c\n", *var5++);
                ++var2;
            }
            free(yylval.yStr);
            if (sub_2105(st->a_expr)) {
                printf("-> %d `c\n", 0);
                ++var2;
            }
            if (haveLbrace)
                tok = yylex();
        } else if (!haveLbrace) /* 3e4a */
            expectErr("{");
        else {
            ungetTok = tok;
            if (st->a_i4 == 0 && st->a_dataType == DT_POINTER)
                st = st->a_nextSym;
            else
                p2 = 0;
            var2 = 0;
            for (;;) {
                if (sub_3d24(st, p2) < 0)
                    break;
                var2++;
                if ((tok = yylex()) == T_RBRACE || tok != T_COMMA || (tok = yylex()) == T_RBRACE)
                    break;
                ungetTok = tok;
            }
        }
        /* 3e22 */
        if (haveLbrace && tok != T_RBRACE) {
            expectErr("}");
            var2 = -1;
        }
        printf(Dstr);
    } else if ((p2 == 0 || st->a_c7 != ENODE) && st->a_i4 == 0 &&
               st->a_dataType == DT_STRUCT) { /* 3ec6 */
        if (p2)
            printf(Ustr);
        printf(Ustr);
        if ((var8 = st->a_nextSym)) {
            varb = (tok = yylex()) == T_LBRACE;
            if (!varb)
                ungetTok = tok;
            vara = var8->nMemberList;
            do {
                if ((sub_3d24(vara, 1) < 0))
                    break;
                if ((vara = vara->nMemberList) == var8)
                    break;
                if ((tok = yylex()) != T_COMMA) {
                    ungetTok = tok;
                    break;
                }
            } while (!varb || (ungetTok = tok = yylex()) != T_RBRACE);
            /* 3f7c: */
            if (varb) {
                if ((tok = yylex()) == T_COMMA)
                    tok = yylex();
                if (tok != T_RBRACE)
                    expectErr("}");
                else
                    var2 = 1;
            } else
                var2 = 1;
        } /* 3fcd */
        printf(Dstr);
        if (p2)
            printf(Dstr);

    } else if ((p2 && st->attr.c7 == ENODE) || st->attr.c7 == ANODE ||
               (!(st->a_i4 & 1) && st->attr.dataType >= T_AUTO))
        prError("illegal initialisation");
    else {
        vare = (tok = yylex()) == T_LBRACE;
        if (!vare)
            ungetTok = tok;
        vard          = allocSType(&st->attr);
        vard->attr.c7 = SNODE;
        if ((vard = sub_1441(T_125, vard, sub_0a83(3))))
            sub_05b5(vard->t_alt);

        if (vare && yylex() != T_RBRACE)
            expectErr("}");
        sub_2569(vard);
        var2 = 1;
    }
    return var2;
}
