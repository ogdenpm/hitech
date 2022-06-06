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

prop_t gProp;        /* 2006 */

static void unary(int16_t op, register prop_t *pc);                   /* 26 08FA */
static void binary(int16_t op, register prop_t *left, prop_t *right); /* 27 096C */

/**************************************************************************
 26 08fa ++
 **************************************************************************/
static void unary(int16_t op, register prop_t *pc) {
    switch (op) {
    case T_MARKER:
        return;
    case T_UMINUS:
        pc->vNum = -pc->vNum;
        break;
    case T_UPLUS:
        return;
    case G_NOT:
        pc->vNum = ~pc->vNum;
        break;
    case T_HIGH:
        pc->vNum >>= 8;
        /* FALLTHRU */
    case T_LOW:
        pc->vNum &= 0xff;
    case T_RES:
    default:
        break;
    }
    if (pc->rType)
        relocErr();
}
/**************************************************************************
27 096c ++
**************************************************************************/
static void binary(int16_t op, register prop_t *left, prop_t *right) {
    switch (op) {
    case T_PLUS:
        if (left->rType && right->rType)
            relocErr();
        left->vNum += right->vNum;
        if (left->rType == RT_ABS) {
            left->rType = right->rType;
            left->rSym  = right->rSym;
        }
        return;
    case T_MINUS:
        if (right->rType &&
            (right->rType != RT_REL || left->rType != RT_REL || right->rSym != left->rSym))
            relocErr();
        else if (right->rSym == left->rSym) {   
            left->rSym = NULL;
            left->rType     = RT_ABS;
        }
        left->vNum -= right->vNum;
        return;
    case T_MULT:
        left->vNum *= right->vNum;
        break;
    case T_DIV:
        if (right->vNum == 0)
            error("Division by zero");
        else
            left->vNum /= right->vNum;
        break;
    case T_MOD:
        left->vNum %= right->vNum;
        break;
    case T_SHR:
        left->vNum >>= right->vNum;
        break;
    case T_SHL:
        left->vNum <<= right->vNum;
        break;
    case G_AND:
        left->vNum &= right->vNum;
        break;
    case G_OR:
        left->vNum |= right->vNum;
        break;
    case T_XOR:
        left->vNum ^= right->vNum;
        break;
    case G_EQ:
        left->vNum = left->vNum == right->vNum;
        break;
    case G_GT:
        left->vNum = left->vNum > right->vNum;
        break;
    case G_LT:
        left->vNum = left->vNum < right->vNum;
        break;
    case T_UGT:
        left->vNum =
            (uint16_t)left->vNum >
            (uint16_t)
                right->vNum; /* note uint16_t matches code, uint32_t would possibly be better */
        break;
    case T_ULT:
        left->vNum = (uint16_t)left->vNum < (uint16_t)right->vNum;
        break;
    }
    if (left->rType ||
        right->rType) /* PMO fix neither should be relocatable original used left for both */
        relocErr();
}

/**************************************************************************
 28 0b1c ++
 **************************************************************************/
prop_t *evalExpr() {
    bool expectOp;
    struct {
        int8_t op;
        uint8_t prec;
    } * var3, opStack[30];
    register prop_t *iy;
    prop_t valStack[30];

    iy               = &valStack[30];
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
            iy--;
            switch (tokType) {
            case G_INT:
                iy->vNum   = yylval.yNum;
                iy->rSym = NULL;
                iy->rType  = RT_ABS;
                break;
            case T_DOLLAR:
                iy->vNum = curPsect->sProp.vCurLoc;
                if (isAbsPsect(curPsect)) {
                    iy->rSym = NULL;
                    iy->rType  = RT_ABS;
                } else {
                    iy->rSym  = curPsect;
                    iy->rType = RT_REL;
                }
                break;
            case G_SYM:
                if (yylval.ySym->sFlags & S_UNDEF) {
                    if (phase == 2 && !(yylval.ySym->sFlags & F_GLOBAL)) {
                        error("Undefined symbol %s", yylval.ySym->sName);
                        yylval.ySym->sFlags |= S_GLOBAL; /* treat as global */
                    }
                    iy->vNum  = 0;
                    iy->rSym  = yylval.ySym;
                    iy->rType = RT_EXT;     // treat as external
                } else
                    *iy = yylval.ySym->sProp;
                break;
            case G_FWD:
            case G_BWD:
                *iy = *findLocalLabel(yylval.yNum, tokType);
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
            unary(var3->op, iy);
        } else {
            binary(var3->op, iy + 1, iy);
            iy++;
        }
        if (++var3 == &opStack[30]) {
            gProp = *iy;
            if (iy == &valStack[29])
                return &gProp;
            break;
        }
    }

    error("Expression error");
    skipLine();
    tokType      = T_EOL;
    gProp.vNum   = 0;
    gProp.rType  = RT_ABS;
    gProp.rSym = NULL;
    return &gProp;
}
