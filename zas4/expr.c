/*
 *
 * The expr.c file is part of the restored ZAS.EXE program
 * from the Hi-Tech Z80 C cross compiler v4.11
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH Z80 C cross compiler V4.11 
 * (HI-TECH Software) and extend its life, outside of the MSDOS 16 bit environment
 * for full operation in windows 32/64 and Unix-like operating systems
 *
 * The HI-TECH Z80 C cross compiler V4.11 is provided free of charge for any use,
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
 * This work is an extension of earlier work on decompiling ZAS.COM from the
 * Hi-Tech CP/M based compiler v3.09
 *
 * See the readme.md file for additional commentary
 *
 * Mark Ogden
 * 06-Jun-2022
 */
#include "zas.h"

rval_t gProp;        /* 2006 */

static void unary(int16_t op, register rval_t *pc);                   /* 26 08FA */
static void binary(int16_t op, register rval_t *left, rval_t *right); /* 27 096C */

/**************************************************************************
 26 08fa ++
 **************************************************************************/
static void unary(int16_t op, register rval_t *pc) {
    switch (op) {
    case T_MARKER:
        return;
    case T_UMINUS:
        pc->val = -pc->val;
        break;
    case T_UPLUS:
        return;
    case G_NOT:
        pc->val = ~pc->val;
        break;
    case T_HIGH:
        pc->val >>= 8;
        /* FALLTHRU */
    case T_LOW:
        pc->val &= 0xff;
    case T_RES:
    default:
        break;
    }
    if (pc->type)
        relocErr();
}
/**************************************************************************
27 096c ++
**************************************************************************/
static void binary(int16_t op, register rval_t *left, rval_t *right) {
    switch (op) {
    case T_PLUS:
        if (left->type && right->type)
            relocErr();
        left->val += right->val;
        if (left->type == RT_ABS) {
            left->type = right->type;
            left->sym  = right->sym;
        }
        return;
    case T_MINUS:
        if (right->type &&
            (right->type != RT_REL || left->type != RT_REL || right->sym != left->sym))
            relocErr();
        else if (right->sym == left->sym) {   
            left->sym = NULL;
            left->type     = RT_ABS;
        }
        left->val -= right->val;
        return;
    case T_MULT:
        left->val *= right->val;
        break;
    case T_DIV:
        if (right->val == 0)
            error("Division by zero");
        else
            left->val /= right->val;
        break;
    case T_MOD:
        left->val %= right->val;
        break;
    case T_SHR:
        left->val >>= right->val;
        break;
    case T_SHL:
        left->val <<= right->val;
        break;
    case G_AND:
        left->val &= right->val;
        break;
    case G_OR:
        left->val |= right->val;
        break;
    case T_XOR:
        left->val ^= right->val;
        break;
    case G_EQ:
        left->val = left->val == right->val;
        break;
    case G_GT:
        left->val = left->val > right->val;
        break;
    case G_LT:
        left->val = left->val < right->val;
        break;
    case T_UGT:
        left->val =
            (uint16_t)left->val >
            (uint16_t)
                right->val; /* note uint16_t matches code, uint32_t would possibly be better */
        break;
    case T_ULT:
        left->val = (uint16_t)left->val < (uint16_t)right->val;
        break;
    }
    if (left->type ||
        right->type) /* PMO fix neither should be relocatable original used left for both */
        relocErr();
}

/**************************************************************************
 28 0b1c ++
 **************************************************************************/
rval_t *evalExpr() {
    bool expectOp;
    struct {
        int8_t op;
        uint8_t prec;
    } * var3, opStack[30];
    register rval_t *pv;
    rval_t valStack[30];

    pv               = &valStack[30];
    var3             = &opStack[29];
    opStack[29].op   = 27;
    opStack[29].prec = 0;
    expectOp         = false;
    for (;;) {
        if (tokType == G_STR) {
            if (strlen(yylval.yStr) != 1)
                error("Bad character const");
            yylval.yNum = yylval.yStr[0];
            tokType     = G_INT;
        }
        if (tokType == G_ARITH8) {
            if (yylval.yTok == 0xa0) {
                tokType     = G_AND;
                yylval.yTok = 4;
            } else if (yylval.yTok == 0xb0) {
                tokType     = G_OR;
                yylval.yTok = 3;
            } else if (yylval.yTok == 0xb8) {
                tokType     = T_XOR;
                yylval.yTok = 3;
            }
        }
        if (G_FWD <= tokType && tokType <= G_INT) {
            if (expectOp)
                break;
            expectOp = true;
            pv--;
            switch (tokType) {
            case G_INT:
                pv->val   = yylval.yNum;
                pv->sym = NULL;
                pv->type  = RT_ABS;
                break;
            case T_DOLLAR:
                pv->val = curPsect->pCurLoc;
                if (isAbsPsect(curPsect)) {
                    pv->sym = NULL;
                    pv->type  = RT_ABS;
                } else {
                    pv->sym  = curPsect;
                    pv->type = RT_REL;
                }
                break;
            case G_SYM:
                if (yylval.ySym->sFlags & S_UNDEF) {
                    if (phase == 2 && !(yylval.ySym->sFlags & F_GLOBAL)) {
                        error("Undefined symbol %s", yylval.ySym->sName);
                        yylval.ySym->sFlags |= S_GLOBAL; /* treat as global */
                    }
                    pv->val  = 0;
                    pv->sym  = yylval.ySym;
                    pv->type = RT_EXT;     // treat as external
                } else
                    *pv = yylval.ySym->rv;
                break;
            case G_FWD:
            case G_BWD:
                *pv = *findLocalLabel((int16_t)yylval.yNum, tokType);
                break;
            }
            tokType = yylex();
            continue;
        } else if (T_UPLUS <= tokType && tokType <= 0x2d) {
            if (!expectOp && (tokType == T_PLUS || tokType == T_MINUS)) {
                tokType -= (T_PLUS - T_UPLUS);
                yylval.yTok = 8; /* precedence */
            }
            if (tokType <= T_MARKER) {
                if (expectOp)
                    break;
                else
                    goto Ld35; /* best option on code match - personally don't like */
            } else if (!expectOp && tokType != T_LPAREN)
                break;
            if (var3->prec < yylval.yTok) {
            Ld35:
                if (tokType != T_RPAREN) {
                    var3--;
                    var3->op = (int8_t)tokType;
                    if (tokType == T_LPAREN)
                        yylval.yTok = 1;
                    else
                        expectOp = false;
                    var3->prec = (uint8_t)yylval.yTok;
                    tokType    = yylex();
                    continue;
                } else if (var3->op != T_MARKER) {
                    tokType = yylex();
                    continue;
                }
            }
        }
        if (var3->op == T_LPAREN) {
            if (tokType != T_RPAREN)
                break;
            tokType  = yylex();
            expectOp = true;
        } else if (var3->op <= T_MARKER) {
            unary(var3->op, pv);
        } else {
            binary(var3->op, pv + 1, pv);
            pv++;
        }
        if (++var3 == &opStack[30]) {
            gProp = *pv;
            if (pv == &valStack[29])
                return &gProp;
            break;
        }
    }

    error("Expression error");
    skipLine();
    tokType      = T_EOL;
    gProp.val   = 0;
    gProp.type  = RT_ABS;
    gProp.sym = NULL;
    return &gProp;
}
