/*
 *
 * The macro.c file is part of the restored ZAS.EXE program
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
static strstk_t mArgStk[30]; /* 25da */
static int16_t macroIdx;     /* 2652 */
static int16_t argSP;        /* 2654 */
static sym_t *macroTab[30];  /* 2656 */
int16_t localsCnt;           /* 2692 */

static void freeRepSym(sym_t *ps); /* 76 2BA2 */
/**************************************************************************
 67 26a6 ++
**************************************************************************/
void parseParamAndBody(register sym_t *ps) {
    int16_t cntParam;
    char *paramList[30];
    char *di;
    sym_t *si;

    if (phase == 0)
        ps->sProp.vArg = 0;
    macroIdx = 0;

    if ((ps->sFlags & S_REPMASK) != S_REPT && (tokType = yylex()) != T_EOL)
        do {
            if (tokType != G_SYM) // 273e
                syntaxErr();
            else {
                si = yylval.ySym;
                if (!(si->sFlags & S_UNDEF))
                    addSym(si = dupSym(si));
                si->sFlags     = S_MLOCAL;
                si->sProp.vArg = macroIdx + 1;
                if (macroIdx == 30)
                    fatalErr("Too many macro parameters");
                macroTab[macroIdx++] = si;
            }
            tokType = yylex();
        } while (tokType == T_COMMA && !(ps->sFlags & (S_IRP | S_IRPC)) &&
                 (tokType = yylex()) != T_EOL);

    if (phase == 2 && (ps->sFlags & S_MACROARG) && macroIdx != ps->sProp.mArgCnt) // 26de
        error("Phase error in macro args");
    ps->sProp.mArgCnt = macroIdx;
    if (ps->sFlags & S_IRPC) {
        if (!(di = getMacroArg()))
            di = "";
        ps->irpcList = xalloc(strlen(di) + 1);
        strcpy(ps->irpcList, di);
        ps->sProp.mIdx = 0;
    } else if (ps->sFlags & S_IRP) {
        cntParam = 0;
        while ((di = getMacroArg())) {
            paramList[cntParam] = xalloc(strlen(di) + 1);
            strcpy(paramList[cntParam++], di);
        }
        ps->irpList = xalloc((cntParam + 1) * sizeof(char *));
        while (cntParam--)
            ps->irpList[cntParam] = paramList[cntParam];
        ps->sProp.mIdx = 0;
    } // 2826
    skipLine();
    ps->sProp.vText = parseMacroBody();
    ps->sProp.vArg  = macroIdx;
    while (macroIdx--) {
        remSym(macroTab[macroIdx]);
        delSym(macroTab[macroIdx]);
    }
    tokType = T_EOL;
}

/**************************************************************************
 68 286e ++
**************************************************************************/
void parseMacroCall(register sym_t *ps) {
    int16_t var2;
    char label[20];
    char *si;
    register char **di = NULL;
    if (ps->sFlags & (S_MACROARG | S_REPT)) {
        di = xalloc(ps->sProp.vArg * sizeof(char *)); // vArg is real args + locals
        if (ps->sFlags & S_MACROARG) {                // collect normal macro args
            for (var2 = 0; var2 != ps->sProp.mArgCnt; var2++) {
                if (!(si = getMacroArg()))
                    si = "";
                di[var2] = xalloc(strlen(si) + 1);
                strcpy(di[var2], si);
            }
        }
        skipLine();                                                      // waste rest of line
        for (var2 = ps->sProp.mArgCnt; var2 != ps->sProp.vArg; var2++) { // allocate locals
            sprintf(label, "??%04d", localsCnt++);
            di[var2] = xalloc(strlen(si = label) + 1);
            strcpy(di[var2], si);
        }
        if (ps->sFlags & S_IRP) // initialise IRP dummy
            di[0] = ps->irpList[ps->sProp.mIdx];
        if (ps->sFlags & S_IRPC) { // initialise IRPC dummy
            di[0]    = xalloc(2);
            di[0][0] = ps->irpcList[ps->sProp.mIdx];
        }
    } // 2965
    mArgStk[++argSP].mSym = ps;
    mArgStk[argSP].mArgs  = di;
    openMacro(ps->sProp.vText, S_MACROARG);
}

/**************************************************************************
 69 2996 ++
 **************************************************************************/
void nextArgSub() {
    register char **di = mArgStk[argSP].mArgs;
    register sym_t *si = mArgStk[argSP--].mSym;
    int16_t i;

    if (di) {
        for (i = 0; i != si->sProp.vArg; i++)
            free(di[i]);
        free(di);
    }
    /*
        note original code seems to have a bug in that the actual test for IRP is
        (int8_t) si->irpList[++si->sProp.mIdx]
        there are three options to check
        1) the error is fine (unlikely)
        2) the test was actually against si->irpList[++si->sProp.mIdx] a char *
        3) si->irpList[++si->sProp.mIdx][0] was intended
        currently option 2 is used here and appears to work
    */
    if (si->sFlags & S_IRP) {
        if (si->irpList[++si->sProp.mIdx]) {
            parseMacroCall(si);
            return;
        }
    } else if (si->sFlags & S_IRPC) {
        if (si->irpcList[++si->sProp.mIdx]) {
            parseMacroCall(si);
            return;
        }
    } else if (si->sFlags & S_REPT) {
        if (--si->sProp.mIdx) {
            parseMacroCall(si);
            return;
        }
    }
    if (si->sFlags & S_REPT)
        freeRepSym(si);
}

/**************************************************************************
 70 2a2e ++
 **************************************************************************/
void openArg(uint16_t id) {
    char **pArgs = mArgStk[argSP].mArgs;
    openMacro(pArgs[id - 1], 0);
}

/**************************************************************************
 71 2a54 ++
 **************************************************************************/
void illegalLocal() {
    error("Local illegal outside macros");
    skipLine();
    tokType = T_EOL;
}

/**************************************************************************
 72 2a66 ++
 **************************************************************************/
void parseLocal() {
    register sym_t *ps;
    while ((tokType = yylex()) != T_EOL) {
        if (tokType == T_COMMA)
            tokType = yylex();
        if (tokType != G_SYM)
            syntaxErr();
        else {
            ps = yylval.ySym;
            if (ps->sFlags & S_MLOCAL)
                error("Macro argument may not appear after LOCAL");
            if (!(ps->sFlags & S_UNDEF))
                addSym(ps = dupSym(ps));
            ps->sFlags     = S_MLOCAL;
            ps->sProp.vArg = macroIdx + 1;
            if (macroIdx == 30)
                fatalErr("Too many macro parameters");
            macroTab[macroIdx++] = ps;
        }
    }
}

/**************************************************************************
 73 2ae2 ++
 **************************************************************************/
void parseIrp() {
    sym_t *pSym  = xalloc(sizeof(sym_t));
    pSym->sFlags = S_REPT + S_IRP;
    parseParamAndBody(pSym);
    if (pSym->irpList)
        parseMacroCall(pSym);
    else
        freeRepSym(pSym);
}

/**************************************************************************
 74 2b0a ++
 **************************************************************************/
void parseIrpc() {
    sym_t *pSym  = xalloc(sizeof(sym_t));
    pSym->sFlags = S_REPT + S_IRPC;
    parseParamAndBody(pSym);
    if (pSym->irpcList)
        parseMacroCall(pSym);
    else
        freeRepSym(pSym);
}

/**************************************************************************
 75 2b32 ++
 **************************************************************************/
void parseRept() {
    prop_t repCnt;
    tokType = yylex();
    repCnt  = *evalExpr();
    if (repCnt.rType || repCnt.vNum < 0) {
        error("Rept argument must be >= 0");
        repCnt.vNum = 1;
    }
    sym_t *pSym      = xalloc(sizeof(sym_t));
    pSym->sFlags     = S_REPT;
    pSym->sProp.mIdx = repCnt.vNum;
    parseParamAndBody(pSym);
    if (pSym->sProp.mIdx)
        parseMacroCall(pSym);
    else
        freeRepSym(pSym);
}

/**************************************************************************
 76 2ba2 ++
 **************************************************************************/
static void freeRepSym(sym_t *ps) {
    free(ps->sProp.vText);
    free(ps);
}
