/*
 *
 * The expr.c file is part of the restored ZAS.COM program
 * from the Hi-Tech C compiler v3.09
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH C compiler V3.09
 * (HI-TECH Software) and extend its life, outside of the CP/M environment
 * (Digital Research, Inc), for full operation in a  Unix-like operating
 * system UZI-180 without using the CP/M emulator.
 *
 * The HI-TECH C compiler V3.09 is provided free of charge for any use,
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
 * Early work on the decompilation was done by Andrey Nikitin
 * Completion of the work and porting to work under modern compilers done by Mark Ogden
 * 19-May-2022
 */
#include "zas.h"

prop_t gProp;        /* 97a1 */
bool ignoreOverflow; /* 97a9 */

static void unary(int16_t op, register prop_t *pc);                   /* 22 0EB3 +-- */
static void binary(int16_t op, register prop_t *left, prop_t *right); /* 23 0F71 +-- */

/**************************************************************************
 21 0b67 +++
 * optimiser swaps load of de & hl loads for add. Code equivalent
 **************************************************************************/
prop_t *evalExpr() {
    uint8_t var1;
    struct {
        int8_t op;
        uint8_t prec;
    } * var3, opStack[30];
    register prop_t *iy;
    prop_t valStack[30];

    ignoreOverflow   = n_opt;
    iy               = &valStack[30];
    var3             = &opStack[29];
    opStack[29].op   = 27;
    opStack[29].prec = 0;
    var1             = 0;
    for (;;) {
        if (tokType == G_STR) {
            if (strlen(yylval.yStr) != 1)
                error("Bad character const");
            yylval.yNum = yylval.yStr[0];
            tokType     = G_INT;
        }
        if (G_FWD <= tokType && tokType <= G_INT) {
            if (var1)
                goto bad;
            var1++;
            iy--;
            switch (tokType) {
            case G_INT:
                iy->vNum      = yylval.yNum;
                iy->cPsectSym = 0;
                iy->cExtSym   = 0;
                break;
            case T_DOLLAR:
                *iy = curPsect->sProp;
                if ((curPsect->sFlags & S_ABSPSECT) == S_ABSPSECT)
                    iy->cPsectSym = 0;
                else
                    iy->cPsectSym = curPsect;

                break;
            case G_SYM:
                *iy = yylval.ySym->sProp;
                if ((yylval.ySym->sFlags & (S_UNDEF|S_GLOBAL)) == S_UNDEF && phase == 2) {
                    error("Undefined symbol %s", yylval.ySym->sName);
                    yylval.ySym->sFlags |= S_GLOBAL; /* treat as global */
                }
                break;
            case G_FWD:
            case G_BWD:
                *iy = *findLocalLabel(yylval.yNum, tokType);
                break;
            }
            tokType = yylex();
            continue;
        } else if (T_UPLUS <= tokType && tokType <= 0x2d) {
            if (var1 == 0 && (tokType == T_PLUS || tokType == T_MINUS)) {
                tokType -= (T_PLUS - T_UPLUS);
                yylval.yVal = 8; /* precedence */
            }
            if (tokType <= T_MARKER) {
                if (var1)
                    goto bad;
                else
                    goto Ldd3; /* best option on code match - personally don't like */
            } else if (!var1 && tokType != T_LPAREN)
                goto bad;
            if (var3->prec < yylval.yVal) {
            Ldd3:
                if (tokType != T_RPAREN) {
                    var3--;
                    var3->op = (int8_t)tokType;
                    if (tokType == T_LPAREN)
                        yylval.yVal = 1;
                    else
                        var1 = false;
                    var3->prec = (uint8_t)yylval.yVal;
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
                goto bad;
            tokType = yylex();
            var1    = true;
        } else if (var3->op <= T_MARKER) {
            unary(var3->op, iy);
        } else {
            binary(var3->op, iy + 1, iy);
            iy++;
        }
        if (++var3 == &opStack[30]) {
            gProp = *iy;
            if (iy != &valStack[29])
                goto bad;
            if (!ignoreOverflow && (gProp.vNum >= 0x10000 || gProp.vNum < -0x7fff))
                error("Arithmetic overflow");
            return &gProp;
        }
    }
bad:
    error("Expression error");
    gProp.vNum      = 0;
    gProp.cPsectSym = NULL;
    gProp.cExtSym   = NULL;
    return &gProp;
}

/**************************************************************************
 22 0eb3 +++
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
        pc->vNum &= 0xff;
        break;
    case T_LOW:
        pc->vNum &= 0xff;
        break;
    case T_RES:
        ignoreOverflow = true;
        return;
    }
    if (pc->cExtSym || pc->cPsectSym)
        relocErr();
}
/**************************************************************************
23 0f71 +++
* optimiser delays test in first if in T_MINUS, allowing optimisation
* in code load for test of cPsectSym != and == also swaps de & hl
**************************************************************************/
static void binary(int16_t op, register prop_t *left, prop_t *right) {
    switch (op) {
    case T_PLUS:
        if ((left->cExtSym || left->cPsectSym) && (right->cExtSym || right->cPsectSym))
            relocErr();
        left->vNum += right->vNum;
        if (left->cPsectSym == 0 && left->cExtSym == 0) {
            left->cPsectSym = right->cPsectSym;
            left->cExtSym   = right->cExtSym;
        }
        return;
    case T_MINUS:
        if (right->cExtSym || (right->cPsectSym && right->cPsectSym != left->cPsectSym))
            relocErr();
        else if (right->cPsectSym == left->cPsectSym)
            left->cPsectSym = NULL;
        left->vNum -= right->vNum;
        return;
    case T_MULT:
        left->vNum *= right->vNum;
        break;
    case T_DIV:
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
    if (left->cExtSym || left->cPsectSym || right->cExtSym || right->cPsectSym)
        relocErr();
}
