/*
 *
 * The parse.c file is part of the restored ZAS.COM program
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

yytype_t yylval;    /* 9e70 */
uint16_t floatMode; /* 9e74 */
uint16_t symFlags;  /* 9e76 */
int16_t tokVal;     /* 9e78 */
int jmpOptCnt;      /* 9e7c */
int16_t tokType;    /* 9e7c */
int jOptIdx;        /* 9e7e */
int16_t savTokType; /* 9e80 */
operand_t lOp;      /* 9e82 */
operand_t rOp;      /* 9e8e */
operand_t tmpOp;    /* 9e9a */
int16_t operandCnt; /* 9ea6 */
char jOptTab[1000]; /* 9ea8 */
jmp_buf jmpBuf;     /* a290 */

static void chkPositiveAbs(register operand_t *po); /* 69 364F +-- */
static void evalOperand(register operand_t *po);    /* 71 3698 +-- */
static _Noreturn void operErr(void);                /* 72 38A5 +-- */
static void getOperands(int minOperand);            /* 73 38BA +-- */
static void parsePush_Pop(void);                    /* 75 3D61 +-- */
static void parseAdc_Sbc(void);                     /* 76 3DCE +-- */
static void parseDefb_w(void);                      /* 77 3E63 +-- */
static void parseDeff(void);                        /* 78 3EA8 +-- */
static void markGlobals(void);                      /* 79 3F58 +-- */
static void addObjFloat(zfloat f);                  /* 81 3F98 +-- */
static void parsePsect(void);                       /* 82 3FF8 +-- */
static void parseSym(void);                         /* 83 40A6 +-- */
static void parseMacroDef(void);                    /* 84 41FA +-- */
static void parseAdd(void);                         /* 85 4252 +-- */
static void parseJp_Call(void);                     /* 86 430B +-- */
static void parseArith8(void);                      /* 87 44FD +-- */
static void parseEx(void);                          /* 88 4584 +-- */
static void parseInc_Dec(void);                     /* 89 4636 +-- */
static void parseIn_Out(int16_t opBase);            /* 90 4723 +-- */
static void parseDjnz_Jr(void);                     /* 91 47AB +-- */
static void parseBit_Rotate(void);                  /* 92 487E +-- */
static void parseIm(void);                          /* 93 48F9 +-- */
static void parseLd(void);                          /* 94 4975 +-- */
static void parseMlt(void);                         /* 95 4D7F +-- */
static void parseIn0_Out0(int16_t opBase);          /* 96 4DBF +-- */
static void parseTstio(void);                       /* 97 4E0C +-- */
static void parseTst(void);                         /* 98 4E31 +-- */
static void defineLabel(register sym_t *ps);        /* 99 4EB8 +-- */
static void multdefErr(register sym_t *ps);         /* 100 4EF3 +-- */
static void needOneOperand(int type);               /* 101 4F10 +-- */

/**************************************************************************
 69	sub_364fh +++
 **************************************************************************/

static void chkPositiveAbs(register operand_t *pe) {
    if (pe->oProp.cExtSym || pe->oProp.cPsectSym || pe->oProp.vNum < 0) {
        relocErr();
        if (pe->oProp.vNum < 0)
            pe->oProp.vNum = 0;
    }
}

/**************************************************************************
 70	relocErr	+++
 **************************************************************************/
void relocErr() {
    error("Relocation error");
}

/**************************************************************************
 71	sub_3698h	+++
 * minor optimisation difference, but code equivalent
 * used ld de,(_yylval) ... rather than ld hl,(-yylval) ... ex de,hl
 **************************************************************************/
static void evalOperand(register operand_t *pe) {
    uint16_t var2;
    switch (tokType) {
    case T_EOL:
        pe->oType = 0;
        return;
    case G_REG:
        if (floatMode == 1 && yylval.yVal == 1) {
            tokType     = G_CC;
            yylval.yVal = 3;
        }
        break;
    case G_CC:
        break;
    case T_LPAREN:
        tokType = yylex();
        if (tokType == G_REG) {
            if (yylval.yVal != R_C && yylval.yVal < R_BC)
                operErr();
            pe->oType = T_REGIND;
            pe->oVal  = yylval.yVal;
            tokType   = yylex();
            if (tokType == T_RPAREN) {
                tokType = yylex();
                if (pe->oVal >= R_IX) {
                    pe->oProp.vNum      = 0;
                    pe->oProp.cPsectSym = pe->oProp.cExtSym = NULL;
                    pe->oType                               = T_INDEXED;
                }
                return;
            } else {
                if (pe->oVal < R_IX)
                    operErr();
                pe->oType = T_INDEXED;
            }
        } else
            pe->oType = T_MEM;
        pe->oProp = *evalExpr();
        if (tokType != T_RPAREN)
            operErr();
        tokType = yylex();
        if (pe->oType == T_INDEXED && (pe->oProp.vNum < -128 || pe->oProp.vNum >= 128))
            error("Index offset too large");
        return;
    default:
        if (tokType < T_UPLUS) {
            if (floatMode == 1 && tokType == G_SIMPLE &&
                (yylval.yVal == 0xfb || yylval.yVal == 0xf3)) {
                tokType     = G_CC;
                yylval.yVal = (yylval.yVal == 0xfb) ? 5 : 4;
                break;
            } else {
                tokType     = G_INT;
                yylval.yNum = (var2 = yylval.yVal);
            }
        }
        pe->oType = G_INT;
        pe->oProp = *evalExpr();
        return;
    }
    pe->oType = tokType;
    pe->oVal  = yylval.yVal;
    tokType   = yylex();
}

/**************************************************************************
 72	operErr	sub_38a5h	+++
 **************************************************************************/
static _Noreturn void operErr() {
    error("Operand error");
    longjmp(jmpBuf, 1);
}

/**************************************************************************
 73	sub_38bah	+++
 **************************************************************************/

static void getOperands(int minOperand) {
    tokType    = yylex();
    operandCnt = 0;
    if (tokType == T_COMMA)
        operErr();
    if (tokType != T_EOL) {
        evalOperand(&lOp);
        if (tokType == T_COMMA) {
            tokType = yylex();
            evalOperand(&rOp);
            operandCnt++;
        }
        operandCnt++;
    }
    if (operandCnt < minOperand)
        operErr();
    if (tokType != T_EOL) {
        error("Garbage after operands");
        tokType = T_EOL;
    }
    skipLine();
}

/**************************************************************************
 74 393d +++
 * trivial difference in switch jmp table.  new has extra jp for EOL,
 * old version has extra jp for ENDC
 **************************************************************************/
void doPass() {
    sym_t *nLabel;
    register char *iy;
    jOptIdx = -1;
    initLocalLabels();
    if (setjmp(jmpBuf)) /* line error recovery point */
        skipLine();
    for (;;) {
        tokType   = yylex();
        tokVal    = yylval.yVal;
        floatMode = 0;
        symFlags  = 0;
        switch (tokType) {
        case T_END:
            getOperands(0);
            if (operandCnt) {
                needOneOperand(G_INT);
                startAddr = lOp.oProp;
                tagHex(0);
            }
        case -1: /* EOF */
            return;
        case G_EDSIMPLE:
            addObjByte(0xed);
            /* FALLTHRU */
        case G_SIMPLE:
            addObjByte(tokVal);
            tokType = yylex();
            break;
        case T_EOL:
            skipLine();
            continue;
        case T_GLOBAL:
            markGlobals();
            break;
        case T_PSECT:
            parsePsect();
            break;
        case G_INT:
            nLabel = yylval.ySym;
            if ((tokType = yylex()) != T_COLON)
                syntaxErr();
            defTmpLabel(nLabel);
            tagHex(0);
            continue;
        case G_SYM:
            parseSym();
            continue;
        case T_DEFF:
            parseDeff();
            break;
        case T_DEFB:
        case T_DEFW:
            parseDefb_w();
            break;
        case T_DEFM:
            if ((tokType = yylex()) != G_STR)
                operErr();
            for (iy = yylval.yStr; *iy; iy++)
                addObjByte(*iy);
            tokType = yylex();
            break;
        case T_COND:
            getOperands(1);
            needOneOperand(G_INT);
            if (lOp.oProp.cExtSym || lOp.oProp.cPsectSym)
                error("Absolute expression required");
            if (lOp.oProp.vNum)
                break;
            parseCond(T_ENDC);
            /* fall through */
        case T_ENDC:
            tokType = yylex();
            break;
        case T_MACRO:
            parseMacroDef();
            break;
        case T_ENDM:
            syntaxErr(); /* as  no return ignore fall through */
        case T_DEFS:
            getOperands(1);
            needOneOperand(G_INT);
            chkPositiveAbs(&lOp);
            tagHex(0);
            curPsect->sProp.vNum += lOp.oProp.vNum;
            finishRecords();
            break;
        case T_ORG:
            getOperands(1);
            needOneOperand(G_INT);
            curPsect = absPsect;
            chkPositiveAbs(&lOp);
            curPsect->sProp.vNum = lOp.oProp.vNum;
            tagHex(0);
            finishRecords();
            break;
        case T_JP:
        case T_CALL:
            parseJp_Call();
            continue;
        case T_ADD:
            parseAdd();
            break;
        case G_ARITH8:
            getOperands(1);
            if (operandCnt != 1)
                operErr();
            parseArith8();
            break;
        case T_EX:
            parseEx();
            break;
        case G_ADCSBC:
            parseAdc_Sbc();
            break;
        case G_PUSHPOP:
            parsePush_Pop();
            break;
        case G_INCDEC:
            parseInc_Dec();
            break;
        case T_OUT:
            getOperands(2);
            parseIn_Out(0x41);
            break;
        case T_IN:
            getOperands(2);
            tmpOp = lOp; /* swap left & right */
            lOp   = rOp;
            rOp   = tmpOp;
            parseIn_Out(0x40);
            break;
        case T_RST:
            getOperands(1);
            needOneOperand(G_INT);
            if (lOp.oProp.vNum & ~0x38)
                operErr();
            chkPositiveAbs(&lOp);
            addObjByte(tokVal + (int16_t)lOp.oProp.vNum);
            break;
        case T_RET:
            floatMode = 1;
            getOperands(0);
            floatMode = 0;
            if (operandCnt == 0)
                addObjByte(tokVal);
            else {
                if (lOp.oType != G_CC)
                    operErr();
                addObjByte(0xc0 + (lOp.oVal << 3));
            }
            break;
        case T_JR:
            floatMode = 1;
            getOperands(1);
            floatMode = 0;
            parseDjnz_Jr();
            break;
        case T_DJNZ:
            getOperands(1);
            if (operandCnt != 1)
                operErr();
            parseDjnz_Jr();
            break;
        case G_BIT:
            getOperands(2);
            if (lOp.oType != G_INT || lOp.oProp.vNum < 0 || lOp.oProp.vNum >= 8)
                error("Bad bit number");
            chkPositiveAbs(&lOp);
            tokVal += lOp.oProp.vNum << 3;
            parseBit_Rotate();
            break;
        case G_ROTATE:
            getOperands(1);
            if (operandCnt != 1)
                operErr();
            if (j_opt && lOp.oType == G_REG && lOp.oVal == 7 && tokVal <= 0x18)
                addObjByte(tokVal + 7);
            else {
                rOp = lOp;
                parseBit_Rotate();
            }
            break;
        case T_IM:
            parseIm();
            break;
        case T_LD:
            parseLd();
            break;
        case T_MLT:
            parseMlt();
            break;
        case T_OUT0:
            getOperands(2);
            parseIn0_Out0(1);
            break;
        case T_IN0:
            getOperands(2);
            tmpOp = lOp;
            lOp   = rOp;
            rOp   = tmpOp;
            parseIn0_Out0(0);
            break;
        case T_TST:
            parseTst();
            break;
        case T_TSTIO:
            parseTstio();
            break;

        default:
            syntaxErr();
            break;
        }
        if (tokType != T_EOL)
            error("Garbage on end of line");
        skipLine();
    }
}
/**************************************************************************
75 3d61 +++
* optimiser does away with call csv, jp cret
**************************************************************************/
static void parsePush_Pop() {
    getOperands(1);
    if (lOp.oType != G_REG || lOp.oVal < R_BC || lOp.oVal == R_SP || lOp.oVal == R_AFQ)
        operErr();
    if (lOp.oVal >= R_IX) {
        addObjByte(lOp.oVal);
        lOp.oVal = R_HL;
    }
    addObjByte(tokVal + ((lOp.oVal & 6) << 3));
}
/**************************************************************************
 76 3dce +++
 **************************************************************************/
static void parseAdc_Sbc() {
    getOperands(2);
    if (lOp.oType != G_REG)
        operErr();
    if (lOp.oVal == R_A) {
        lOp = rOp;
        parseArith8();
        return;
    }
    if (rOp.oType != G_REG || lOp.oVal != R_HL || rOp.oVal > R_SP || rOp.oVal < R_BC)
        operErr();
    tokVal = tokVal == 0x88 ? 0x4a : 0x42;
    addObjByte(0xed);
    addObjByte(tokVal + ((rOp.oVal & 6) << 3));
}
/**************************************************************************
 77 3e63 +++
 **************************************************************************/
static void parseDefb_w() {
    tokVal = tokType;
    do {
        tokType = yylex();
        evalOperand(&lOp);
        if (lOp.oType != G_INT)
            operErr();
        if (tokVal == T_DEFB)
            addObjRelocByte(&lOp.oProp);
        else
            addObjRelocWord(&lOp.oProp);
    } while (tokType == T_COMMA);
}

/**************************************************************************
 78 3ea8 +++
 **************************************************************************/
static void parseDeff() {
    zfloat val;
    uint8_t sign;
    floatMode = 2;
    do {
        sign    = 0;
        tokType = yylex();
        if (tokType == T_MINUS) {
            sign++;
            tokType = yylex();
        }
        if (tokType == G_INT)
            val = altof(yylval.yNum);
        else if (tokType != G_FLOAT) {
            error("Floating number expected)");
            val = 0L;
        } else
            val = yylval.yFloat;
        if (sign)
            val = negf(val);
        addObjFloat(val);
        tokType = yylex();
    } while (tokType == T_COMMA);
    floatMode = 0;
}

/**************************************************************************
 79 3f58 +++
 **************************************************************************/
static void markGlobals() {
    register sym_t *pSym;
    do {
        if ((tokType = yylex()) != G_SYM)
            operErr();
        pSym = yylval.ySym;
        pSym->sFlags |= 0x10;
    } while ((tokType = yylex()) == T_COMMA);
}

/**************************************************************************
 80 3f83 +++
 **************************************************************************/
_Noreturn void syntaxErr() {
    error("Syntax Error");
    longjmp(jmpBuf, 1);
}
/**************************************************************************
81 3f98 +++
**************************************************************************/
static void addObjFloat(zfloat f) {

#if CPM
    int8_t *p;
    int16_t cnt;
    zfloat tmp = f;
    p          = (int8_t *)&tmp;
    cnt        = 4;
    while (cnt--)
        addObjByte(*p++ & 0xff);
#else
    /* portable write little edian */
    /* relies on zfloat being defined as a uint32_t */
    zfloat tmp = f;
    int8_t cnt = 4;
    while (cnt--) {
        addObjByte(tmp & 0xff);
        tmp /= 256;
    }
#endif
}

/**************************************************************************
 82 3ff8 +++
 **************************************************************************/

static void parsePsect() {
    symFlags = 0x100;
    tokType  = yylex();
    if (tokType != G_SYM)
        operErr();
    if (yylval.ySym != curPsect) {
        curPsect = yylval.ySym;
        finishRecords();
    }
    for (tokType = yylex(); tokType == T_COMMA; tokType = yylex()) {
        tokType = yylex();
        if (tokType != G_PSECT) {
            error("Flag %s unknown", yytext);
            skipLine();
            break;
        }
        curPsect->sFlags |= yylval.yVal;
    }
    if (curPsect->sFlags & F_LOCAL) {
        if (curPsect->sFlags & F_GLOBAL)
            error("Psect may not be local and global");
    } else
        curPsect->sFlags |= 0x10;
    tagHex(0);
    symFlags = 0;
}

/**************************************************************************
 83 40a6 +++
 * optimiser didn't optimise the bit reset ps->sFlags &= ~ 0x200, unlike
 * the original
 **************************************************************************/
static void parseSym() {
    register sym_t *ps;
    ps = yylval.ySym;
    if (ps->sFlags & F_ARGS) {
        parseMacroCall(ps);
        return;
    }
    if (c_opt && crfFp)
        fprintf(crfFp, "#%s %d\n", ps->sName, curLineno);
    if ((tokType = yylex()) == T_COLON) {
        defineLabel(ps);
        if (phase != 2) {
            ps->sProp.vNum = curPsect->sProp.vNum;
            if ((curPsect->sFlags & 0xc0) == 0xc0)
                ps->sProp.cPsectSym = NULL;
            else
                ps->sProp.cPsectSym = curPsect;
            ps->sProp.cExtSym = NULL;

        } else if (!(ps->sFlags & 0x400) && ps->sProp.vNum != curPsect->sProp.vNum)
            error("Phase error");
        tagHex(0);
        return;
    }
    if (tokType == T_EQU)
        defineLabel(ps);
    else if (tokType != T_DEFL)
        syntaxErr();
    savTokType = tokType;
    getOperands(1);
    needOneOperand(G_INT);
    if (ps->sFlags & F_ARGS) {
        if (savTokType == T_DEFL)
            multdefErr(ps);
    } else
        ps->sProp = lOp.oProp;
    ps->sFlags &= ~0x200;
    if (controls)
        putTaggedAddr(&lOp.oProp, '=');
}

/**************************************************************************
 84 41fa +++
 * basic bloc for tokType = yylex() moved  and bit reset not optimised
 * otherwise code same
 **************************************************************************/
static void parseMacroDef() {
    register sym_t *ps;
    tokType = yylex();
    if (tokType != G_SYM)
        syntaxErr();
    ps = yylval.ySym;
    if (!(ps->sFlags & (F_ARGS | F_BPAGE))) {
        multdefErr(ps);
        parseCond(T_ENDM);
    } else {
        if (ps->sFlags & F_ARGS)
            free(ps->sProp.vText);
        ps->sFlags |= F_ARGS;
        ps->sFlags &= ~F_BPAGE;
        parseParamAndBody(ps);
    }
    tokType = yylex();
}

/**************************************************************************
 85 4252 +++
 **************************************************************************/
static void parseAdd() {
    getOperands(2);
    if (lOp.oType != G_REG || (lOp.oVal != R_A && lOp.oVal != R_HL && lOp.oVal < R_IX))
        operErr();

    if (lOp.oVal >= R_BC) {
        if (rOp.oType != G_REG ||
            (rOp.oVal != lOp.oVal && rOp.oVal != R_DE && rOp.oVal != R_BC && rOp.oVal != R_SP))
            operErr();
        if (lOp.oVal >= R_IX)
            addObjByte(lOp.oVal);
        addObjByte(9 + ((rOp.oVal & 6) << 3));
    } else {
        lOp = rOp;
        parseArith8();
    }
}

/**************************************************************************
 86 430b +++
 **************************************************************************/
static void parseJp_Call() {
    int16_t span;
    savTokType = tokType;
    floatMode  = 1;
    getOperands(1);
    if (operandCnt == 1)
        rOp = lOp;
    if (j_opt && jOptIdx != 999 && rOp.oType == G_INT && savTokType == T_JP &&
        (operandCnt == 1 || (lOp.oType == G_CC && lOp.oVal <= 3))) {
        jOptIdx++;
        span   = rOp.oProp.vNum - curPsect->sProp.vNum;
        tokVal = 0x18;
        if (phase == 2 && jOptTab[jOptIdx]) {
            jmpOptCnt++;
            parseDjnz_Jr();
            return;
        } else if (phase != 2 && rOp.oProp.cExtSym == NULL && -0x7e <= span && span <= 0x81 &&
                   (rOp.oProp.cPsectSym == curPsect ||
                    (!rOp.oProp.cPsectSym && (curPsect->sFlags & 0xc0) == 0xc0))) {
            jOptTab[jOptIdx] = 1;
            parseDjnz_Jr();
            return;
        } else
            tokVal = 0xc3;
    }
    if (operandCnt == 2) {
        if (lOp.oType != G_CC)
            syntaxErr();
        tokVal = (lOp.oVal << 3) + (savTokType == T_JP ? 0xc2 : 0xc4);
        lOp    = rOp;
    }
    if ((operandCnt == 2 || savTokType == T_CALL) && lOp.oType != G_INT)
        operErr();
    if (lOp.oType == G_INT) {
        addObjByte(tokVal);
        addObjRelocWord(&lOp.oProp);
    } else if (lOp.oType == T_INDEXED) {
        addObjByte(lOp.oVal);
        addObjByte(0xe9);
    } else {
        if (lOp.oType != T_REGIND || lOp.oVal != R_HL)
            operErr();
        addObjByte(0xe9);
    }
}

/**************************************************************************
 87 44fd +++
 **************************************************************************/
static void parseArith8() {
    switch (lOp.oType) {
    case T_INDEXED:
        addObjByte(lOp.oVal);
        lOp.oVal = R_HL;
        /* FALLTHRU */
    case T_REGIND:
        if (lOp.oVal != R_HL)
            operErr();
        addObjByte(tokVal + 6);
        if (lOp.oType == T_INDEXED)
            addObjRelocByte(&lOp.oProp);
        break;
    case G_REG:
        if (lOp.oVal > R_A)
            operErr();
        addObjByte(tokVal + lOp.oVal);
        break;
    case G_INT:
        addObjByte(tokVal + 0x46);
        addObjRelocByte(&lOp.oProp);
        break;
    default:
        operErr();
        break;
    }
}

/**************************************************************************
 88 4584 +++
 **************************************************************************/
static void parseEx() {
    getOperands(2);
    if (lOp.oType == T_REGIND) {
        if (lOp.oVal != R_SP || rOp.oType != G_REG || (rOp.oVal < R_IX && rOp.oVal != R_HL))
            operErr();
        if (rOp.oVal >= R_IX)
            addObjByte(rOp.oVal);
        addObjByte(0xe3);
    } else {
        if (lOp.oType != G_REG || rOp.oType != G_REG)
            operErr();
        if (lOp.oVal == R_DE) {
            if (rOp.oVal != R_HL)
                operErr();
            addObjByte(0xeb);
        } else {
            if (lOp.oVal != R_AF || rOp.oVal != R_AFQ)
                operErr();
            addObjByte(8);
        }
    }
}

/**************************************************************************
 89 4636 +++
 **************************************************************************/
static void parseInc_Dec() {
    getOperands(1);
    if (lOp.oType == G_REG && lOp.oVal >= R_BC) {
        if (lOp.oVal == R_AF || lOp.oVal == R_AFQ)
            operErr();
        if (lOp.oVal >= R_IX) {
            addObjByte(lOp.oVal);
            lOp.oVal = R_HL;
        }
        tokVal = tokVal == 4 ? 3 : 0xb;
        addObjByte(tokVal + ((lOp.oVal & 6) << 3));
    } else {
        switch (lOp.oType) {
        case T_INDEXED:
            addObjByte(lOp.oVal);
            lOp.oVal = R_HL;
            /* FALLTHRU */
        case T_REGIND:
            if (lOp.oVal != R_HL)
                operErr();
            addObjByte(0x30 + tokVal);
            if (lOp.oType == T_INDEXED)
                addObjRelocByte(&lOp.oProp);
            break;
        case G_REG:
            if (lOp.oVal > R_A)
                operErr();
            addObjByte(tokVal + (lOp.oVal << 3));
            break;
        default:
            operErr();
            break;
        }
    }
}

/**************************************************************************
 90 4723 +++
 **************************************************************************/
static void parseIn_Out(int16_t opBase) {
    if (lOp.oType == T_MEM) {
        if (rOp.oType != G_REG || rOp.oVal != R_A)
            operErr();
        addObjByte(tokVal);
        addObjRelocByte(&lOp.oProp);
    } else {
        if (lOp.oType != T_REGIND || lOp.oVal != R_C || rOp.oType != G_REG || rOp.oVal > R_A)
            operErr();
        addObjByte(0xed);
        addObjByte(opBase + (rOp.oVal << 3));
    }
}

/**************************************************************************
 91 47ab +++
**************************************************************************/
static void parseDjnz_Jr() {
    if (operandCnt == 2) {
        if (lOp.oType != G_CC || lOp.oVal > 3)
            operErr();
        tokVal     = 0x20 + (lOp.oVal << 3);
        lOp        = rOp;
        operandCnt = 1;
    }
    needOneOperand(G_INT);
    savTokType = lOp.oProp.vNum - curPsect->sProp.vNum;
    if (lOp.oProp.cExtSym || savTokType > 0x81 || savTokType < -0x7e ||
        (lOp.oProp.cPsectSym != curPsect &&
         ((curPsect->sFlags & 0xc0) != 0xc0 || lOp.oProp.cPsectSym)))
        error("Jump out of range");
    addObjByte(tokVal);
    addObjByte(savTokType - 2);
}

/**************************************************************************
 92 487e +++
**************************************************************************/
static void parseBit_Rotate() {
    switch (rOp.oType) {
    case T_INDEXED:
        addObjByte(rOp.oVal);
        rOp.oVal = R_HL;
        /* FALLTHRU */
    case T_REGIND:
        if (rOp.oVal != R_HL)
            operErr();
        addObjByte(0xcb);
        if (rOp.oType == T_INDEXED)
            addObjRelocByte(&rOp.oProp);
        addObjByte(tokVal + 6);
        break;
    case G_REG:
        if (rOp.oVal > R_A)
            operErr();
        addObjByte(0xcb);
        addObjByte(tokVal + rOp.oVal);
        break;
    default:
        operErr();
        break;
    }
}

/**************************************************************************
 93 sub_48f9h +++
 * optimiser removed call csv && jp cret
 **************************************************************************/
static void parseIm() {
    getOperands(1);
    needOneOperand(G_INT);
    if (lOp.oProp.vNum < 0 || lOp.oProp.vNum >= 3)
        error("Bad arg to IM");
    else
        chkPositiveAbs(&lOp);
    addObjByte(0xed);
    switch ((int16_t)lOp.oProp.vNum) {
    case 0:
        addObjByte(0x46);
        break;
    case 1:
        addObjByte(0x56);
        break;
    case 2:
        addObjByte(0x5e);
    }
}

/**************************************************************************
 94 4975 +++
 * small number of basic blocks located differently and a couple of benign
 * differences on argument popping, i.e. using ex (sp),hl vs. pop and push
**************************************************************************/
static void parseLd() {
    getOperands(2);
    switch (lOp.oType) {
    case G_REG:
        if (lOp.oVal >= R_BC) {
            if (lOp.oVal == R_AF || lOp.oVal == R_AFQ)
                operErr();
            if (lOp.oVal == R_SP && rOp.oType == G_REG) {
                if (rOp.oVal == 0xdd || rOp.oVal == 0xfd)
                    addObjByte(rOp.oVal);
                else if (rOp.oVal != R_HL)
                    operErr();
                addObjByte(0xf9);
                break;
            }
            if (lOp.oVal >= R_IX) {
                addObjByte(lOp.oVal);
                lOp.oVal = R_HL;
            }
            if (lOp.oVal > R_SP)
                operErr();
            tokVal = (lOp.oVal & 6) << 3;
            if (rOp.oType == G_INT)
                addObjByte(tokVal + 1);
            else {
                if (rOp.oType != T_MEM)
                    operErr();
                if (lOp.oVal == R_HL)
                    addObjByte(0x2a);
                else {
                    addObjByte(0xed);
                    addObjByte(tokVal | 0x4b);
                }
            }
            addObjRelocWord(&rOp.oProp);
        } else if (rOp.oType == G_REG) {
            if (rOp.oVal >= R_I || lOp.oVal >= R_I) {
                if (rOp.oVal != R_A && lOp.oVal != R_A)
                    operErr();
                addObjByte(0xed);
                if (lOp.oVal == R_A) {
                    tokVal = 0x50;
                    lOp    = rOp;
                } else
                    tokVal = 0x40;
                tokVal += lOp.oVal == R_I ? 7 : 0xf;
                addObjByte(tokVal);
            } else {
                if (rOp.oVal > R_A)
                    operErr();
                addObjByte(0x40 + rOp.oVal + (lOp.oVal << 3));
            }
        } else {
            if (lOp.oVal > R_A)
                operErr();
            if (rOp.oType == G_INT) {
                addObjByte(6 + (lOp.oVal << 3));
                addObjRelocByte(&rOp.oProp);
                break;
            } else if (rOp.oType == T_INDEXED)
                addObjByte(rOp.oVal);
            else if (rOp.oType == T_REGIND) {
                if (rOp.oVal != R_HL) {
                    if (lOp.oVal != R_A)
                        operErr();
                    if (rOp.oVal != R_DE && rOp.oVal != R_BC)
                        operErr();
                    addObjByte(0xa + ((rOp.oVal & 6) << 3));
                    break;
                }
            } else if (rOp.oType == T_MEM) {
                if (lOp.oVal != R_A)
                    operErr();
                addObjByte(0x3a);
                addObjRelocWord(&rOp.oProp);
                break;
            } else
                operErr();
            addObjByte(0x46 + (lOp.oVal << 3));
            if (rOp.oType == T_INDEXED)
                addObjRelocByte(&rOp.oProp);
        }
        break;
    case T_REGIND:
        if (rOp.oType == G_INT && lOp.oVal == R_HL) {
            addObjByte(0x36);
            addObjRelocByte(&rOp.oProp);
        } else {
            if (rOp.oType != G_REG || rOp.oVal > R_A || (lOp.oVal != R_HL && rOp.oVal != R_A))
                operErr();
            if (lOp.oVal == R_HL)
                addObjByte(0x70 + rOp.oVal);
            else
                addObjByte(((lOp.oVal & 0xffde) << 3) + 2);
        }
        break;
    case T_MEM:
        if (rOp.oType != G_REG)
            operErr();
        if (rOp.oVal >= R_BC) {
            if (rOp.oVal >= R_IX) {
                addObjByte(rOp.oVal);
                rOp.oVal = R_HL;
            }
            if (rOp.oVal == R_HL)
                addObjByte(0x22);
            else if (rOp.oVal > R_SP)
                operErr();
            else {
                addObjByte(0xed);
                addObjByte(((rOp.oVal & 6) << 3) + 0x43);
            }
        } else {
            if (rOp.oVal != R_A)
                operErr();
            addObjByte(0x32);
        }
        addObjRelocWord(&lOp.oProp);
        break;
    case T_INDEXED:
        addObjByte(lOp.oVal);
        if (rOp.oType == G_INT) {
            addObjByte(0x36);
            addObjRelocByte(&lOp.oProp);
            addObjRelocByte(&rOp.oProp);
        } else {
            if (rOp.oType != G_REG || rOp.oVal > R_A)
                operErr();
            addObjByte(rOp.oVal + 0x70);
            addObjRelocByte(&lOp.oProp);
        }
        break;
    default:
        operErr();
        break;
    }
}

/**************************************************************************
 95 4d7f +++
**************************************************************************/
static void parseMlt() {
    getOperands(1);
    if (lOp.oType != G_REG || lOp.oVal < R_BC)
        operErr();
    addObjByte(0xed);
    addObjByte(0x4c + ((lOp.oVal & 0x6) << 3));
}
/**************************************************************************
 96 4dbf +++
**************************************************************************/
static void parseIn0_Out0(int16_t opBase) {
    if (lOp.oType != T_MEM || rOp.oType != G_REG || rOp.oVal > R_A)
        operErr();
    addObjByte(0xed);
    addObjByte((uint8_t)opBase + (rOp.oVal << 3));
    addObjRelocByte(&lOp.oProp);
}

/**************************************************************************
 97 4e0c +++
**************************************************************************/
static void parseTstio() {
    getOperands(1);
    needOneOperand(G_INT);
    addObjByte(0xed);
    addObjByte(0x74);
    addObjRelocByte(&lOp.oProp);
}

/**************************************************************************
 98 4e31 +++
**************************************************************************/
static void parseTst() {
    getOperands(1);
    if (operandCnt != 1)
        operErr();
    switch (lOp.oType) {
    case G_REG:
        if (lOp.oVal > R_A)
            operErr();
        addObjByte(0xed);
        addObjByte((lOp.oVal << 3) + 4);
        break;
    case G_INT:
        addObjByte(0xed);
        addObjByte(0x64);
        addObjRelocByte(&lOp.oProp);
        break;
    case T_REGIND:
        if (lOp.oVal != R_HL)
            operErr();
        addObjByte(0xed);
        addObjByte(0x34);
        break;
    default:
        operErr();
        break;
    }
}

/**************************************************************************
 99 4eb8 +++
 bit reset not optimised
**************************************************************************/
static void defineLabel(register sym_t *ps) {
    if (phase == 0) {
        if (!(ps->sFlags & 0x200))
            ps->sFlags |= 0x400;
        ps->sFlags &= ~0x200;
    } else if (phase == 2 && (ps->sFlags & 0x400))
        multdefErr(ps);
}
/**************************************************************************
 100 4ef3 +++
**************************************************************************/
static void multdefErr(register sym_t *ps) {
    error("Multiply defined symbol %s", ps->sName);
}

/**************************************************************************
 101 4f10 +++
**************************************************************************/
static void needOneOperand(int type) {
    if (operandCnt != 1 || lOp.oType != type)
        operErr();
}
