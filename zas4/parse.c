/*
 *
 * The parse.c file is part of the restored ZAS.EXE program
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

yytype_t yylval;    /* 26f0 */
uint16_t floatMode; /* 26f4 */
uint16_t symFlags;  /* 26f6 */
int16_t tokVal;     /* 26f8 */
int16_t jmpOptCnt;  /* 26fa */
int16_t tokType;    /* 26fc */
int16_t jOptIdx;    /* 26fe */
int16_t saveVal;    /* 2700 */
operand_t lOp;      /* 2702 */
operand_t rOp;      /* 270e */
operand_t tmpOp;    /* 271a */
int16_t operandCnt; /* 2726 */
char jOptTab[1000]; /* 2728 */
jmp_buf jmpBuf;     /* 2b10 */

static _Noreturn void operErr(void);                /* 88 314A */
static void chkPositiveAbs(register operand_t *pe); /* 89 315C */
static void evalOperand(register operand_t *pe);    /* 90 3180 */
static void getOperands(int16_t minOperand);        /* 91 3322 */
static void needOneOperand(int16_t type);           /* 93 33B0 */
static void parsePush_Pop(void);                    /* 95 3904 */
static void parseAdc_Sbc(void);                     /* 96 3974 */
static void parseDefb_w(void);                      /* 97 3A14 */
static void parseDeff(void);                        /* 98 3A74 */
static void parseGlobal(void);                      /* 99 3AFC */
static void addObjFloat(double d);                  /* 101 3B30 */
static void addObjFloat(double d);                  /* 101 3B30 */
static void parsePsect(void);                       /* 102 3CA2 */
static void multdefErr(register sym_t *ps);         /* 103 3D36 */
static void parseMacroType1(sym_t *ps);             /* 104 3D48 */
static void defineLabel(register sym_t *ps);        /* 105 3D8A */
static void parseSym(void);                         /* 107 3DDA */
static void parseMacroType2(void);                  /* 108 3F42 */
static void parseAdd(void);                         /* 109 3FA4 */
static void parseJp_Call(void);                     /* 110 405A */
static void parseArith8(void);                      /* 111 421E */
static void parseEx(void);                          /* 112 42DA */
static void parseInc_Dec(void);                     /* 113 4388 */
static void parseIn_Out(int16_t opBase);            /* 114 449E */
static void parseDjnz_Jr(void);                     /* 115 453E */
static void parseBit_Rotate(void);                  /* 116 4604 */
static void parseIm(void);                          /* 117 46C6 */
static void parseLd(void);                          /* 118 4756 */
static void parseMlt(void);                         /* 119 4C1A */
static void parseIn0_Out0(int16_t opBase);          /* 120 4C6C */
static void parseTstio(void);                       /* 121 4CE2 */
static void parseTst(void);                         /* 122 4D34 */
static void parseLine(void);                        /* 123 4E08 */
static void parseFile(void);                        /* 124 4E62 */

/* simplify code, probably done with macros in original */
static inline void optAddObjByte(int16_t n) {
    if (phase == 2)
        addObjByte(n);
    else
        curPsect->sProp.vCurLoc++;
}

static inline void optAddObjRelocByte(prop_t *p, uint8_t reloc) {
    if (phase == 2)
        addObjRelocByte(p, reloc);
    else
        curPsect->sProp.vCurLoc++;
}

static inline void optAddObjRelocWord(prop_t *p, uint8_t reloc) {
    if (phase == 2)
        addObjRelocWord(p, reloc);
    else
        curPsect->sProp.vCurLoc += 2;
}

/**************************************************************************
 87 313e ++
 **************************************************************************/
void relocErr() {
    error("Relocation error");
}

/**************************************************************************
 88 314a ++
 **************************************************************************/
static _Noreturn void operErr() {
    error("Operand error");
    longjmp(jmpBuf, 1);
}

/**************************************************************************
 89 315c ++
 **************************************************************************/

static void chkPositiveAbs(register operand_t *pe) {
    if (pe->oProp.rType || pe->oProp.vNum < 0) {
        relocErr();
        if (pe->oProp.vNum < 0)
            pe->oProp.vNum = 0;
    }
}

/**************************************************************************
 90 3180 ++
 **************************************************************************/
static void evalOperand(register operand_t *pe) {
    int32_t var4;
    switch (tokType) {
    case T_EOL:
        pe->oType = 0;
        return;
    case G_REG:
        if (floatMode == 1 && yylval.yTok == 1) {
            tokType     = G_CC;
            yylval.yTok = 3;
        }
        break;
    case G_CC:
        break;
    case T_LPAREN:
        tokType = yylex();
        if (tokType == G_REG) {
            if (yylval.yTok != R_C && yylval.yTok < R_BC)
                operErr();
            pe->oType = T_REGIND;
            pe->oVal  = yylval.yTok;
            tokType   = yylex();
            if (tokType == T_RPAREN) {
                tokType = yylex();
                if (pe->oVal >= R_IX) {
                    pe->oProp.vNum  = 0;
                    pe->oProp.rType = RT_ABS;
                    pe->oType       = T_INDEXED;
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
                (yylval.yTok == 0xfb || yylval.yTok == 0xf3)) {
                tokType     = G_CC;
                yylval.yTok = (yylval.yTok == 0xfb) ? 5 : 4;
                break;
            } else {
                tokType     = G_INT;
                yylval.yNum = (var4 = yylval.yTok);
            }
        }
        pe->oType = G_INT;
        pe->oProp = *evalExpr();
        return;
    }
    pe->oType = tokType;
    pe->oVal  = yylval.yTok;
    tokType   = yylex();
}

/**************************************************************************
 91 3322 ++
 **************************************************************************/

static void getOperands(int16_t minOperand) {
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
 92 3383 ++
 **************************************************************************/
void parseElse() {
    char savControls;
    savControls = controls;
    parseCond(G_END);
    tokType  = yylex();
    controls = savControls;
}

/**************************************************************************
 93 33b0 ++
 **************************************************************************/
static void needOneOperand(int16_t type) {
    if (operandCnt != 1 || lOp.oType != type)
        operErr();
}

/**************************************************************************
 94 33cc ++
 **************************************************************************/
void doPass() {
    int16_t nLabel;
    register char *iy;
    jOptIdx   = -1;
    localsCnt = 0; // restart locals for each pass
    initLocalLabels();
    if (setjmp(jmpBuf)) /* line error recovery point */
        skipLine();
    for (;;) {
        tokType   = yylex();
        tokVal    = yylval.yTok;
        floatMode = 0;
        symFlags  = S_NONPSECT;
        switch (tokType) {
        case T_EOL:
            skipLine();
            continue;
        case T_END:
            getOperands(0);
            if (operandCnt) {
                needOneOperand(G_INT);
                startAddr = lOp.oProp;
                if (controls)
                    tagHex(0);
            }
            return;
        case -1: /* EOF */
            return;
        case G_EDSIMPLE:
            optAddObjByte(0xed);
            /* FALLTHRU */
        case G_SIMPLE:
            optAddObjByte(tokVal);
            tokType = yylex();
            break;
        case T_GLOBAL:
            parseGlobal();
            break;
        case T_PSECT:
            parsePsect();
            break;
        case G_INT:
            nLabel = yylval.yNum;
            if ((tokType = yylex()) != T_COLON)
                syntaxErr();
            defTmpLabel(nLabel);
            if (controls)
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
                optAddObjByte(*iy);
            tokType = yylex();
            break;
        case T_COND:
            getOperands(1);
            needOneOperand(G_INT);
            if (lOp.oProp.rType)
                error("Absolute expression required");
            if (lOp.oProp.vNum)
                break;
            parseCond(G_END);
            tokType = yylex();
            break;
        case T_ELSE:
            parseElse();
            break;
        case G_END:
            tokType = yylex();
            break;
        case T_MACRO:
            parseMacroType2();
            break;
        case T_IRP:
            parseIrp();
            break;
        case T_IRPC:
            parseIrpc();
            break;
        case T_REPT:
            parseRept();
            break;
        case T_FILE:
            parseFile();
            break;
        case T_LINE:
            parseLine();
            break;
        case T_ENDM:
            syntaxErr(); /* as  no return ignore fall through */
        case T_DEFS:
            getOperands(1);
            needOneOperand(G_INT);
            chkPositiveAbs(&lOp);
            if (controls)
                tagHex(0);
            curPsect->sProp.vCurLoc += lOp.oProp.vNum;
            updateMaxLoc(curPsect); // PMO fixes reported 0 size bss
            finishRecords();
            break;
        case T_ORG:
            getOperands(1);
            needOneOperand(G_INT);
            curPsect = absPsect;
            chkPositiveAbs(&lOp);
            curPsect->sProp.vMaxLoc = lOp.oProp.vNum;
            if (controls)
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
            optAddObjByte(tokVal + (int16_t)lOp.oProp.vNum);
            break;
        case T_RET:
            floatMode = 1;
            getOperands(0);
            floatMode = 0;
            if (operandCnt == 0) {

                optAddObjByte(tokVal);

            } else {
                if (lOp.oType != G_CC)
                    operErr();
                optAddObjByte(0xc0 + (lOp.oVal << 3));
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
            if (lOp.oType != G_INT || lOp.oProp.vNum < 0 || lOp.oProp.vNum > 7)
                error("Bad bit number");
            chkPositiveAbs(&lOp);
            tokVal += lOp.oProp.vNum << 3;
            parseBit_Rotate();
            break;
        case G_ROTATE:
            getOperands(1);
            if (operandCnt != 1)
                operErr();
            if (j_opt && lOp.oType == G_REG && lOp.oVal == R_A && tokVal <= 0x18)
                optAddObjByte(tokVal + 7);
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
 95 3904 ++
**************************************************************************/
static void parsePush_Pop() {
    getOperands(1);
    if (lOp.oType != G_REG || lOp.oVal < R_BC || lOp.oVal == R_SP || lOp.oVal == R_AFQ)
        operErr();
    if (lOp.oVal >= R_IX) {
        optAddObjByte(lOp.oVal);
        lOp.oVal = R_HL;
    }
    optAddObjByte(tokVal + ((lOp.oVal & 6) << 3));
}

/**************************************************************************
 96 3974 ++
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
    optAddObjByte(0xed);
    optAddObjByte(tokVal + ((rOp.oVal & 6) << 3));
}

/**************************************************************************
 97 3a14
 **************************************************************************/
static void parseDefb_w() {
    tokVal = tokType;
    do {
        tokType = yylex();
        /* allow string arg to defb
           note single characters are passed as before to allow expressions
           e.g. 'A'+20h
        */
        if (tokType == G_STR && tokVal == T_DEFB && strlen(yylval.yStr) > 1) {
            for (char *s = yylval.yStr; *s; s++)
                optAddObjByte(*s);
            tokType = yylex();
        } else {
            evalOperand(&lOp);
            if (lOp.oType != G_INT)
                operErr();
            if (tokVal == T_DEFB)
                optAddObjRelocByte(&lOp.oProp, 0);
            else
                optAddObjRelocWord(&lOp.oProp, 0);
        }
    } while (tokType == T_COMMA);
}

/**************************************************************************
 98 3a74 ++
 **************************************************************************/
static void parseDeff() {
    float val;
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
            val = (float)(yylval.yNum);
        else if (tokType != G_FLOAT) {
            error("Floating number expected)");
            val = 0.0f;
        } else
            val = yylval.yFloat;
        if (sign)
            val = -val;
        addObjFloat(val);
        tokType = yylex();
    } while (tokType == T_COMMA);
    floatMode = 0;
}

/**************************************************************************
 99 3afc ++
 **************************************************************************/
static void parseGlobal() {
    register sym_t *pSym;
    do {
        if ((tokType = yylex()) != G_SYM)
            operErr();
        pSym = yylval.ySym;
        pSym->sFlags |= F_GLOBAL;
    } while ((tokType = yylex()) == T_COMMA);
}

/**************************************************************************
 100 3b1e ++
 **************************************************************************/
_Noreturn void syntaxErr() {
    error("Syntax Error");
    longjmp(jmpBuf, 1);
}
/**************************************************************************
 101 3b30 ++
**************************************************************************/
#if _FORCE
/* original code */
static void addObjFloat(double d) {
    float f          = d;
    int8_t *pf       = &f;
    uint32_t matissa = 0;
    int16_t exp      = (((pf[2] & 0x80) >> 7) + (pf[3] << 1)) & 0xff;
    if (exp == 0)
        matissa = 0;
    else {
        exp -= 0x7e;
        if (exp > 0x3f)
            error("Floating exponent too large");
        exp += 0x40;

        if (f < 0.0) {
            f = -f;
            exp |= 0x80;
        }
        matissa = ((uint32_t)(pf[2] & 0x7f) << 16) + ((uint32_t)pf[1] << 8) + (uint32_t)pf[0] +
                  0x800000UL;
    }
    optAddObjByte(matissa & 0xff);
    optAddObjByte((matissa >> 8) & 0xff);
    optAddObjByte((matissa >> 16) & 0xff);
    optAddObjByte(exp);
}
#else
/* PMO - replacement code */
static void addObjFloat(double d) {
#define ZBIAS    64
#define IEEEBIAS 126

    union {
        uint32_t zf; /* warning relies same on byte ordering cf. float */
        float f;
    } u;
    u.f          = (float)d; /* reduce to float */
    int16_t zexp = ((u.zf >> 23) & 0xff);
    if (zexp == 0)
        u.zf = 0;
    else if ((zexp = zexp - IEEEBIAS + ZBIAS) > 127 || zexp < 0) {
        /* detects underflow as well as overflow */
        error("Floating exponent too %s", zexp < 0 ? "small" : "large");
        u.zf = 0;
    } else {
        u.zf &= 0x807fffff;                        /* remove original exponent */
        u.zf |= 0x800000 + ((uint32_t)zexp << 24); /* add in missing hidden bit and new exponent */
    }
    if (phase == 2) { /* case specific optimisation to avoid multiple tests */
        addObjByte(u.zf & 0xff);
        addObjByte((u.zf >> 8) & 0xff);
        addObjByte((u.zf >> 16) & 0xff);
        addObjByte((u.zf >> 24) & 0xff);
    } else
        curPsect->sProp.vCurLoc += 4;
}
#endif

/**************************************************************************
 102 3ca2 ++
 **************************************************************************/

static void parsePsect() {
    symFlags = S_PSECT;
    tokType  = yylex();
    if (tokType != G_SYM)
        operErr();
    if (yylval.ySym != curPsect) {
        curPsect = yylval.ySym;
        finishRecords();
    }
    while ((tokType = yylex()) == T_COMMA) {
        tokType = yylex();
        if (tokType != G_PSECT) {
            error("Flag %s unknown", yytext);
            skipLine();
            break;
        }
        curPsect->sFlags |= yylval.yTok;
    }
    if (curPsect->sFlags & F_LOCAL) {
        if (curPsect->sFlags & F_GLOBAL)
            error("Psect may not be local and global");
    } else
        curPsect->sFlags |= F_GLOBAL;
    tagHex(0);
    symFlags = S_NONPSECT;
}

/**************************************************************************
 103 3d36 ++
**************************************************************************/
static void multdefErr(register sym_t *ps) {
    error("Multiply defined symbol %s", ps->sName);
}

/**************************************************************************
 104 3d48 ++
 parse macro def of form
 macroname  MACRO macroparameters
**************************************************************************/
static void parseMacroType1(sym_t *ps) {
    if (!(ps->sFlags & (S_UNDEF | S_MACROARG))) {
        multdefErr(ps);
        parseCond(T_ENDM);
        tokType = yylex();
    } else {
        if (ps->sFlags & S_MACROARG)
            free(ps->sProp.vText);
        ps->sFlags = (ps->sFlags | S_MACROARG) & ~S_UNDEF;
        parseParamAndBody(ps);
        tokType = T_EOL;
    }
}
/**************************************************************************
 105 3d8a ++
**************************************************************************/
static void defineLabel(register sym_t *ps) {
    if (phase == 0) {
        if (!(ps->sFlags & S_UNDEF))
            ps->sFlags |= S_DEFINED;
        ps->sFlags &= ~S_UNDEF;
    } else if (phase == 2 && (ps->sFlags & S_DEFINED))
        multdefErr(ps);
}

/**************************************************************************
 106 3dbc ++
**************************************************************************/
bool isAbsPsect(sym_t *ps) {
    return (ps->sFlags & S_ABSPSECT) == S_ABSPSECT;
}

/**************************************************************************
 107 3dda++
 **************************************************************************/
static void parseSym() {
    register sym_t *ps = yylval.ySym;

    if (nextIsMacroKwd()) {
        tokType = yylex();
        if (c_opt && crfFp)
            fprintf(crfFp, "#%s %d\n", ps->sName, curLineno);
        parseMacroType1(ps);
    } else if (ps->sFlags & S_MACROARG)
        parseMacroCall(ps);
    else {
        if (c_opt && crfFp)
            fprintf(crfFp, "#%s %d\n", ps->sName, curLineno);
        if ((tokType = yylex()) == T_COLON) {
            defineLabel(ps);
            if (phase != 2) {
                ps->sProp.vNum = curPsect->sProp.vCurLoc;
                if (isAbsPsect(ps))
                    ps->sProp.rType = RT_ABS;
                else {
                    ps->sProp.rSym  = curPsect;
                    ps->sProp.rType = RT_REL;
                }
            } else if (!(ps->sFlags & S_DEFINED) && ps->sProp.vNum != curPsect->sProp.vCurLoc)
                error("Phase error");
            if (controls)
                tagHex(0);
        } else {
            if (tokType == T_EQU)
                defineLabel(ps);
            else if (tokType != T_DEFL)
                syntaxErr();
            saveVal = tokType;
            getOperands(1);
            needOneOperand(G_INT);
            if (ps->sFlags & S_MACROARG) {
                if (saveVal == T_DEFL)
                    multdefErr(ps);
            } else
                ps->sProp = lOp.oProp;
            ps->sFlags &= ~S_UNDEF;
            if (controls)
                putTaggedAddr(&lOp.oProp, '=');
        }
        if (phase == 2 && !x_opt && !(ps->sFlags & (S_GLOBAL | S_UNDEF)))
            addObjSymbol(ps);
    }
}

/**************************************************************************
 108 3f42++
 define macro of type
    MACRO macroname, parameters
 **************************************************************************/
static void parseMacroType2() {
    register sym_t *ps;
    tokType = yylex();
    if (tokType != G_SYM)
        syntaxErr();
    ps = yylval.ySym;
    if (!(ps->sFlags & (S_MACROARG | S_UNDEF))) {
        multdefErr(ps);
        parseCond(T_ENDM);
    } else {
        if (ps->sFlags & S_MACROARG)
            free(ps->sProp.vText);
        ps->sFlags |= S_MACROARG;
        ps->sFlags &= ~S_UNDEF;
        tokType = yylex();
        if (tokType != T_COMMA)
            unget(tokType);
        parseParamAndBody(ps);
        tokType = T_EOL;
    }
}
/**************************************************************************
 109 3fa4++
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
            optAddObjByte(lOp.oVal);
        optAddObjByte(9 + ((rOp.oVal & 6) << 3));
    } else {
        lOp = rOp;
        parseArith8();
    }
}

/**************************************************************************
 110 305a+++
 **************************************************************************/
static void parseJp_Call() {
    int16_t span;
    saveVal   = tokType;
    floatMode = 1;
    getOperands(1);
    if (operandCnt == 1)
        rOp = lOp;
    if (j_opt && jOptIdx != 999 && rOp.oType == G_INT && saveVal == T_JP &&
        (operandCnt == 1 || (lOp.oType == G_CC && lOp.oVal <= 3))) {
        jOptIdx++;
        span   = rOp.oProp.vCurLoc - curPsect->sProp.vCurLoc;
        tokVal = 0x18;
        if (phase == 2) {
            if (jOptTab[jOptIdx]) {
                jmpOptCnt++;
                parseDjnz_Jr();
                return;
            }
        } else if (rOp.oProp.rType == RT_REL && span <= 0x81 && -0x7e <= span &&
                   (rOp.oProp.rSym == curPsect ||
                    (isAbsPsect(curPsect) && rOp.oProp.rType == RT_ABS))) {
            jOptTab[jOptIdx] = 1;
            parseDjnz_Jr();
            return;
        } else
            tokVal = 0xc3;
    }

    if (operandCnt == 2) {
        if (lOp.oType != G_CC)
            syntaxErr();
        tokVal = (lOp.oVal << 3) + (saveVal == T_JP ? 0xc2 : 0xc4);
        lOp    = rOp;
    }
    if ((operandCnt == 2 || saveVal == T_CALL) && lOp.oType != G_INT)
        operErr();
    if (lOp.oType == G_INT) {
        optAddObjByte(tokVal);
        optAddObjRelocWord(&lOp.oProp, 0);
    } else if (lOp.oType == T_INDEXED) {
        optAddObjByte(lOp.oVal);
        optAddObjByte(0xe9);
    } else {
        if (lOp.oType != T_REGIND || lOp.oVal != R_HL)
            operErr();
        optAddObjByte(0xe9);
    }
}

/**************************************************************************
 111 421e++
 **************************************************************************/
static void parseArith8() {
    switch (lOp.oType) {
    case T_INDEXED:
        optAddObjByte(lOp.oVal);
        lOp.oVal = R_HL;
        /* FALLTHRU */
    case T_REGIND:
        if (lOp.oVal != R_HL)
            operErr();
        optAddObjByte(tokVal + 6);
        if (lOp.oType == T_INDEXED)
            optAddObjRelocByte(&lOp.oProp, 0);
        break;
    case G_REG:
        if (lOp.oVal > R_A)
            operErr();
        optAddObjByte(tokVal + lOp.oVal);
        break;
    case G_INT:
        optAddObjByte(tokVal + 0x46);
        optAddObjRelocByte(&lOp.oProp, 0);
        break;
    default:
        operErr();
        break;
    }
}

/**************************************************************************
 112 42da++
 **************************************************************************/
static void parseEx() {
    getOperands(2);
    if (lOp.oType == T_REGIND) {
        if (lOp.oVal != R_SP || rOp.oType != G_REG || (rOp.oVal < R_IX && rOp.oVal != R_HL))
            operErr();
        if (rOp.oVal >= R_IX)
            optAddObjByte(rOp.oVal);
        optAddObjByte(0xe3);
    } else {
        if (lOp.oType != G_REG || rOp.oType != G_REG)
            operErr();
        if (lOp.oVal == R_DE) {
            if (rOp.oVal != R_HL)
                operErr();
            optAddObjByte(0xeb);
        } else {
            if (lOp.oVal != R_AF || rOp.oVal != R_AFQ)
                operErr();
            optAddObjByte(8);
        }
    }
}

/**************************************************************************
 113 4388++
 **************************************************************************/
static void parseInc_Dec() {
    getOperands(1);
    if (lOp.oType == G_REG && lOp.oVal >= R_BC) {
        if (lOp.oVal == R_AF || lOp.oVal == R_AFQ)
            operErr();
        if (lOp.oVal >= R_IX) {
            optAddObjByte(lOp.oVal);
            lOp.oVal = R_HL;
        }
        tokVal = tokVal == 4 ? 3 : 0xb;
        optAddObjByte(tokVal + ((lOp.oVal & 6) << 3));
    } else {
        switch (lOp.oType) {
        case T_INDEXED:
            optAddObjByte(lOp.oVal);
            lOp.oVal = R_HL;
            /* FALLTHRU */
        case T_REGIND:
            if (lOp.oVal != R_HL)
                operErr();
            optAddObjByte(0x30 + tokVal);
            if (lOp.oType == T_INDEXED)
                optAddObjRelocByte(&lOp.oProp, 0);
            break;
        case G_REG:
            if (lOp.oVal > R_A)
                operErr();
            optAddObjByte(tokVal + (lOp.oVal << 3));
            break;
        default:
            operErr();
            break;
        }
    }
}

/**************************************************************************
 114 449e+++
 **************************************************************************/
static void parseIn_Out(int16_t opBase) {
    if (lOp.oType == T_MEM) {
        if (rOp.oType != G_REG || rOp.oVal != R_A)
            operErr();
        optAddObjByte(tokVal);
        optAddObjRelocByte(&lOp.oProp, 0);
    } else {
        if (lOp.oType != T_REGIND || lOp.oVal != R_C || rOp.oType != G_REG || rOp.oVal > R_A)
            operErr();
        optAddObjByte(0xed);
        optAddObjByte(opBase + (rOp.oVal << 3));
    }
}

/**************************************************************************
 115 453e++
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
    saveVal = lOp.oProp.vCurLoc - curPsect->sProp.vCurLoc;
    /* range tests fixed as they were not adjusted for the -2 delta */
    if (lOp.oProp.rType != 0x10 || lOp.oProp.rSym != curPsect || saveVal < -126 || saveVal > 129)
        error("Jump out of range");
    optAddObjByte(tokVal);
    optAddObjByte(saveVal - 2);
}

/**************************************************************************
 116 4604++
**************************************************************************/
static void parseBit_Rotate() {
    switch (rOp.oType) {
    case T_INDEXED:
        optAddObjByte(rOp.oVal);
        rOp.oVal = R_HL;
        /* FALLTHRU */
    case T_REGIND:
        if (rOp.oVal != R_HL)
            operErr();
        optAddObjByte(0xcb);
        if (rOp.oType == T_INDEXED)
            addObjRelocByte(&rOp.oProp, 0);
        optAddObjByte(tokVal + 6);
        break;
    case G_REG:
        if (rOp.oVal > R_A)
            operErr();
        optAddObjByte(0xcb);
        optAddObjByte(tokVal + rOp.oVal);
        break;
    default:
        operErr();
        break;
    }
}

/**************************************************************************
 117 46c6++
 **************************************************************************/
static void parseIm() {
    getOperands(1);
    needOneOperand(G_INT);
    if (lOp.oProp.vNum < 0 || lOp.oProp.vNum > 2)
        error("Bad arg to IM");
    else
        chkPositiveAbs(&lOp);
    optAddObjByte(0xed);
    switch ((int16_t)lOp.oProp.vNum) {
    case 0:
        optAddObjByte(0x46);
        break;
    case 1:
        optAddObjByte(0x56);
        break;
    case 2:
        optAddObjByte(0x5e);
    }
}

/**************************************************************************
 118 4756++
**************************************************************************/
static void parseLd() {
    getOperands(2);
    switch (lOp.oType) {
    case G_REG:
        if (lOp.oVal >= R_BC) {
            if (lOp.oVal == R_AF || lOp.oVal == R_AFQ)
                operErr();
            if (lOp.oVal == R_SP && rOp.oType == G_REG) {
                if (rOp.oVal == R_IX || rOp.oVal == R_IY)
                    optAddObjByte(rOp.oVal);
                else if (rOp.oVal != R_HL)
                    operErr();
                optAddObjByte(0xf9);
                break;
            }
            if (lOp.oVal >= R_IX) {
                optAddObjByte(lOp.oVal);
                lOp.oVal = R_HL;
            }
            if (lOp.oVal > R_SP)
                operErr();
            tokVal = (lOp.oVal & 6) << 3;
            if (rOp.oType == G_INT)
                optAddObjByte(tokVal + 1);
            else {
                if (rOp.oType != T_MEM)
                    operErr();
                if (lOp.oVal == R_HL)
                    optAddObjByte(0x2a);
                else {
                    optAddObjByte(0xed);
                    optAddObjByte(tokVal | 0x4b);
                }
            }
            optAddObjRelocWord(&rOp.oProp, 0);
        } else if (rOp.oType == G_REG) {
            if (rOp.oVal >= R_I || lOp.oVal >= R_I) {
                if (rOp.oVal != R_A && lOp.oVal != R_A)
                    operErr();
                optAddObjByte(0xed);
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
                optAddObjByte(0x40 + rOp.oVal + (lOp.oVal << 3));
            }
        } else {
            if (lOp.oVal > R_A)
                operErr();
            if (rOp.oType == G_INT) {
                addObjByte(6 + (lOp.oVal << 3));
                addObjRelocByte(&rOp.oProp, 0);
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
                addObjRelocWord(&rOp.oProp, 0);
                break;
            } else
                operErr();
            optAddObjByte(0x46 + (lOp.oVal << 3));
            if (rOp.oType == T_INDEXED)
                optAddObjRelocByte(&rOp.oProp, 0);
        }
        break;
    case T_REGIND:
        if (rOp.oType == G_INT && lOp.oVal == R_HL) {
            optAddObjByte(0x36);
            optAddObjRelocByte(&rOp.oProp, 0);
        } else {
            if (rOp.oType != G_REG || rOp.oVal > R_A || (lOp.oVal != R_HL && rOp.oVal != R_A))
                operErr();
            if (lOp.oVal == R_HL)
                optAddObjByte(0x70 + rOp.oVal);
            else
                optAddObjByte(((lOp.oVal & 0xffde) << 3) + 2);
        }
        break;
    case T_MEM:
        if (rOp.oType != G_REG)
            operErr();
        if (rOp.oVal >= R_BC) {
            if (rOp.oVal >= R_IX) {
                optAddObjByte(rOp.oVal);
                rOp.oVal = R_HL;
            }
            if (rOp.oVal == R_HL)
                optAddObjByte(0x22);
            else if (rOp.oVal > R_SP)
                operErr();
            else {
                optAddObjByte(0xed);
                optAddObjByte(((rOp.oVal & 6) << 3) + 0x43);
            }
        } else {
            if (rOp.oVal != R_A)
                operErr();
            optAddObjByte(0x32);
        }
        addObjRelocWord(&lOp.oProp, 0);
        break;
    case T_INDEXED:
        optAddObjByte(lOp.oVal);
        if (rOp.oType == G_INT) {
            optAddObjByte(0x36);
            optAddObjRelocByte(&lOp.oProp, 0);
            optAddObjRelocByte(&rOp.oProp, 0);
        } else {
            if (rOp.oType != G_REG || rOp.oVal > R_A)
                operErr();
            optAddObjByte(rOp.oVal + 0x70);
            optAddObjRelocByte(&lOp.oProp, 0);
        }
        break;
    default:
        operErr();
        break;
    }
}

/**************************************************************************
 119 4c1a++
**************************************************************************/
static void parseMlt() {
    getOperands(1);
    if (lOp.oType != G_REG || lOp.oVal < R_BC)
        operErr();
    optAddObjByte(0xed);
    optAddObjByte(0x4c + ((lOp.oVal & 0x6) << 3));
}
/**************************************************************************
 120 4c6c++
**************************************************************************/
static void parseIn0_Out0(int16_t opBase) {
    if (lOp.oType != T_MEM || rOp.oType != G_REG || rOp.oVal > R_A)
        operErr();
    optAddObjByte(0xed);
    optAddObjByte((uint8_t)opBase + (rOp.oVal << 3));
    optAddObjRelocByte(&lOp.oProp, 0);
}

/**************************************************************************
 121 4ce2++
**************************************************************************/
static void parseTstio() {
    getOperands(1);
    needOneOperand(G_INT);
    optAddObjByte(0xed);
    optAddObjByte(0x74);
    optAddObjRelocByte(&lOp.oProp, 0);
}

/**************************************************************************
 122 4d34++
**************************************************************************/
static void parseTst() {
    getOperands(1);
    if (operandCnt != 1)
        operErr();
    switch (lOp.oType) {
    case G_REG:
        if (lOp.oVal > R_A)
            operErr();
        optAddObjByte(0xed);
        optAddObjByte((lOp.oVal << 3) + 4);
        break;
    case G_INT:
        optAddObjByte(0xed);
        optAddObjByte(0x64);
        optAddObjRelocByte(&lOp.oProp, 0);
        break;
    case T_REGIND:
        if (lOp.oVal != R_HL)
            operErr();
        optAddObjByte(0xed);
        optAddObjByte(0x34);
        break;
    default:
        operErr();
        break;
    }
}

/**************************************************************************
 123 4e08+++
**************************************************************************/
static void parseLine() {
    char buf[20];
    sym_t sym;

    if (yylex() != G_INT)
        operErr();
    sprintf(buf, "%" PRId32, yylval.yNum);
    tokType         = yylex();
    sym.sName       = buf;
    sym.sFlags      = S_LINENO;
    sym.sProp.vNum  = curPsect->sProp.vCurLoc;
    sym.sProp.rType = RT_REL;
    sym.sProp.rSym  = curPsect;
    addObjSymbol(&sym);
}

/**************************************************************************
 124 4e62
**************************************************************************/
static void parseFile() {
    sym_t sym;
    if (yylex() != G_STR)
        operErr();
    sym.sName       = yylval.yStr;
    sym.sFlags      = S_FILNAM;
    sym.sProp.vNum  = 0;
    sym.sProp.rType = RT_ABS;
    sym.sProp.rSym  = NULL;
    addObjSymbol(&sym);
    tokType = yylex();
}
