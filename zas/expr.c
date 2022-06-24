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

static rval_t exprRetVal;   /* 97a1 */
static bool ignoreOverflow; /* 97a9 */

static void unary(int16_t op, register rval_t *pc);                   /* 22 0EB3 +-- */
static void binary(int16_t op, register rval_t *left, rval_t *right); /* 23 0F71 +-- */

/**************************************************************************
 21 0b67 +++
 * optimiser swaps load of de & hl loads for add. Code equivalent
 **************************************************************************/
rval_t *evalExpr() {
    uint8_t var1;
    struct {
        int8_t op;
        uint8_t prec;
    } * po, opStack[30];
    register rval_t *pv;
    rval_t valStack[30];

    ignoreOverflow   = n_opt;
    pv               = &valStack[30];
    po               = &opStack[29];
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
            pv--;
            switch (tokType) {
            case G_INT:
                pv->val  = yylval.yNum;
                pv->pSym = NULL;
                pv->eSym = NULL;
                break;
            case T_DOLLAR:
                /* PMO
                    note the psec structure copy to an rval_t is safe here
                    since the first location is an int32_t in both cases
                    and the eSym memory loc is unused in the psec structure
                    and will be zero when allocated.
                    curPsect->symRval would work, but here the conversion
                    is explicit
                */
                *pv = *(rval_t *)&curPsect->symPsec;
                if ((curPsect->sFlags & S_ABSPSECT) == S_ABSPSECT)
                    pv->pSym = NULL;
                else
                    pv->pSym = curPsect;

                break;
            case G_SYM:
                *pv = yylval.ySym->symRval;
                if ((yylval.ySym->sFlags & (S_UNDEF | S_GLOBAL)) == S_UNDEF && phase == 2) {
                    error("Undefined symbol %s", yylval.ySym->sName);
                    yylval.ySym->sFlags |= S_GLOBAL; /* treat as global */
                }
                break;
            case G_FWD:
            case G_BWD:
                *pv = *findLocalLabel(yylval.yNum, tokType);
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
            if (po->prec < yylval.yVal) {
            Ldd3:
                if (tokType != T_RPAREN) {
                    po--;
                    po->op = (int8_t)tokType;
                    if (tokType == T_LPAREN)
                        yylval.yVal = 1;
                    else
                        var1 = false;
                    po->prec = (uint8_t)yylval.yVal;
                    tokType  = yylex();
                    continue;
                } else if (po->op != T_MARKER) {
                    tokType = yylex();
                    continue;
                }
            }
        }
        if (po->op == T_LPAREN) {
            if (tokType != T_RPAREN)
                goto bad;
            tokType = yylex();
            var1    = true;
        } else if (po->op <= T_MARKER) {
            unary(po->op, pv);
        } else {
            binary(po->op, pv + 1, pv);
            pv++;
        }
        if (++po == &opStack[30]) {
            exprRetVal = *pv;
            if (pv != &valStack[29])
                goto bad;
            if (!ignoreOverflow && (exprRetVal.val >= 0x10000 || exprRetVal.val < -0x7fff))
                error("Arithmetic overflow");
            return &exprRetVal;
        }
    }
bad:
    error("Expression error");
    exprRetVal.val  = 0; /* return non relocatable 0 */
    exprRetVal.pSym = NULL;
    exprRetVal.eSym = NULL;
    return &exprRetVal;
}

/**************************************************************************
 22 0eb3 +++
 **************************************************************************/
static void unary(int16_t op, register rval_t *pv) {
    switch (op) {
    case T_MARKER:
        return;
    case T_UMINUS:
        pv->val = -pv->val;
        break;
    case T_UPLUS:
        return;
    case G_NOT:
        pv->val = ~pv->val;
        break;
    case T_HIGH:
        pv->val >>= 8;
        pv->val &= 0xff;
        break;
    case T_LOW:
        pv->val &= 0xff;
        break;
    case T_RES:
        ignoreOverflow = true;
        return;
    }
    if (pv->eSym || pv->pSym)
        relocErr();
}
/**************************************************************************
23 0f71 +++
* optimiser delays test in first if in T_MINUS, allowing optimisation
* in code load for test of pSym != and == also swaps de & hl
**************************************************************************/
static void binary(int16_t op, register rval_t *left, rval_t *right) {
    switch (op) {
    case T_PLUS:
        if ((left->eSym || left->pSym) && (right->eSym || right->pSym))
            relocErr();
        left->val += right->val;
        if (left->pSym == 0 && left->eSym == 0) {
            left->pSym = right->pSym;
            left->eSym = right->eSym;
        }
        return;
    case T_MINUS:
        if (right->eSym || (right->pSym && right->pSym != left->pSym))
            relocErr();
        else if (right->pSym == left->pSym)
            left->pSym = NULL;
        left->val -= right->val;
        return;
    case T_MULT:
        left->val *= right->val;
        break;
    case T_DIV:
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
    if (left->eSym || left->pSym || right->eSym || right->pSym)
        relocErr();
}
