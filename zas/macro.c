/*
 *
 * The macro.c file is part of the restored ZAS.COM program
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

/**************************************************************************
 56 2c1b +++
 **************************************************************************/
void parseParamAndBody(register sym_t *ps) {
    sym_t *var2;
    sym_t *var3e[30];
    uint16_t cntParam;
    int16_t var42, tok;

    cntParam = 0;
    while ((tok = yylex()) != T_EOL) {
        if (tok == T_COMMA)
            tok = yylex();
        if (tok != G_SYM)
            syntaxErr();
        else {
            var2 = yylval.ySym;
            if (var2->sFlags & S_UNDEF)
                remSym(var2);
            else
                var2 = dupSym(var2);
            var2->sFlags = S_MACROPARAM;
            if (cntParam == 30)
                fatalErr("Too many macro parameters");
            var3e[cntParam++] = var2;
        }
    }
    if (phase != 0) {
        if (ps->mArgs) {
            for (var42 = 0; var42 < ps->mArgCnt;)
                free(ps->mArgs[var42++]);
            free(ps->mArgs);
        }
        if (cntParam != ps->mArgCnt)
            error("Phase error in macro args");
    }
    if (cntParam) {
        ps->mArgs = xalloc(cntParam * sizeof(sym_t));
    } else
        ps->mArgs = 0;
    ps->mArgCnt = cntParam;
    while (cntParam--)
        ps->mArgs[cntParam] = var3e[cntParam];
    skipLine();
    ps->mText = parseMacroBody();
}
/**************************************************************************
57 2dc5
**************************************************************************/
void parseMacroCall(register sym_t *ps) {
    int var2;
    char *var4;
    if (ps->sFlags & S_MACRO) {
        for (var2 = 0; var2 < ps->mArgCnt; var2++) {
            if (!(var4 = getMacroArg()))
                var4 = "";

            ps->mArgs[var2]->mText = xalloc(strlen(var4) + 1);
            strcpy(ps->mArgs[var2]->mText, var4);
            addSym(ps->mArgs[var2]);
        }
        skipLine();
    }
    openMacro(ps);
}

/**************************************************************************
58 2e89 +++
 **************************************************************************/
void freeMacro(register sym_t *ps) {
    int16_t var2 = 0;
    while (var2 < ps->mArgCnt) {
        free(ps->mArgs[var2]->mText);
        remSym(ps->mArgs[var2]);
        var2++;
    }
}
