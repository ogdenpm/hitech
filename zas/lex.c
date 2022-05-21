/*
 *
 * The lex.c file is part of the restored ZAS.COM program
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
#include "cclass.h"
#include "zas.h"

int16_t pageNo;                                        /* 97aa */
char outLine[512];                                     /* 97ac */
int16_t macroSize;                                     /* 99ac */
int16_t macroUsed;                                     /* 99ae */
bool lstThisLine;                                      /* 99b0 */
char heading[41];                                      /* 99b1 */
int16_t hexLineCnt;                                        /* 99da */
src_t srcStack[MAXINCL];                               /* 99dc */
char *pHexCode;                                        /* 9b26 */
char yytext[100];                                      /* 9b28 */
bool showHex;                                          /* 9b8c */
int16_t lineLen;                                       /* 9b8d */
char title[41];                                        /* 9b8f */
char *macroBase;                                       /* 9bb8 */
char *outPtr;                                          /* 9bba */
int16_t rowCnt;                                        /* 9bbc */
int16_t curLineno;                                     /* 9bbe */
char *curFileName;                                     /* 9bc0 */
char l9bc2h;                                           /* 9bc2 */
char *inPtr;                                           /* 9bc3 */
char controls;                                         /* 9bc5 */
int16_t tmpId;                                         /* 9bc6 */
char *pHexStart;                                       /* 9bc8 */
int16_t srcSP;                                         /* 9bca */
char inBuf[256];                                       /* 9bcc */
char hexLines[LIST_FRAGMENT_SIZE * MAX_LIST_FRAGMENT]; /* 9ccc */
int16_t width;                                             /* 9e16 */

static char *skipToNextToken(register char *s);       /* 24 1217 +-- */
static int32_t zatol(register char *s, uint8_t base); /* 25 1276 +-- */
static int16_t isFloat(char *s);                      /* 29 180A +-- */
static int16_t parseDirective(void);                  /* 30 1896 +-- */
static int parseNumber(void);                         /* 31 1985 +-- */
static int16_t popSrc(void);                          /* 33 1F54 +-- */
static void openFile(char *name);                     /* 34 2052 +-- */
int16_t getText(void);                                /* 36 225C +-- */
static bool readSrc(void);                            /* 37 22E7 +-- */
static bool listDirective(char *s);                   /* 38 2392 +-- */
static void initLine(void);                           /* 40 2408 +-- */
static void initHexLine(void);                        /* 41 242E +-- */
static void flushLine(void);                          /* 45 25EC +-- */
static void hex2(register char *p, int16_t val);      /* 46 2829 +-- */
static void hex4(register char *p, int16_t val);      /* 47 286D +-- */
static void resetMacroList(void);                     /* 49 28BC +-- */
static void prHeading(void);                          /* 51 28F1 +-- */
static void setTitle(char *text);                     /* 52 2970 +-- */

/* pseudo functions to make code readable */
#ifdef CPM
#define PeekCh() (lineLen > 0 ? *inPtr : 0)
#define GetCh()  (--lineLen >= 0 ? *inPtr++ : getText())
#else
static inline int16_t PeekCh() {
    return lineLen > 0 ? *inPtr : 0;
};
static int16_t GetCh() {
    return --lineLen < 0 ? getText() : *inPtr++;
}
#endif

/**************************************************************************
24	skipToNextToken	+++
**************************************************************************/
static char *skipToNextToken(register char *s) {
    char *t;

    for (; *s && !Isspace(*s); ++s)
        ;
    for (; Isspace(*s); ++s)
        ;
    for (t = s; *t && *t != '\n'; ++t)
        ;
    *t = 0;
    return s;
}

/**************************************************************************
 25	zatol	+++
 **************************************************************************/
static int32_t zatol(register char *s, uint8_t base) {
    int32_t val;
    int16_t digit;

    for (val = 0; *s != 0; val += digit) {
        val *= base;
        if (Isdigit(*s)) {
            digit = *s - '0';
            ++s;
        } else if (Isxdigit(*s)) {
            digit = Tolower(*s) - 'a' + 10;
            ++s;
        }
#ifndef CPM
        /* although zatol is only called after a pre check of digits
           the compiler doesn't know this and issues a complaint
           about uninitialised digit
        */
        else
            digit = 99;
#endif
        if (digit >= base) {
            error("Digit out of range");
            return 0;
        }
    }
    return val;
}

/**************************************************************************
 26 134e +++
 * optimiser used a different location for skipLine code and shared code
 * for nest++
 **************************************************************************/
void parseCond(int16_t tok) {
    int16_t ch;
    int16_t nest;

    register char *s;
    skipLine();
    nest = 1;
    for (;;) {
        switch (ch = GetCh()) {
        case ' ':
        case '\t':
            continue;
        case 'C':
        case 'E':
        case 'M':
        case 'c':
        case 'e':
        case 'm':
            s    = yytext;
            *s++ = (char)ch;
            while (Isalnum(PeekCh()))
                *s++ = (char)GetCh();
            *s = 0;
            /* PMO note fall throughs below look wrong but match code */
            switch (getKwdId(yytext)) {
            case T_ENDC:
                if (tok == T_ENDC && --nest == 0)
                    return;
                /* FALLTHRU */
            case T_ENDM:
                if (tok == T_ENDM && --nest == 0)
                    return;
                /* FALLTHRU */
            case T_MACRO:
                if (tok == T_ENDM)
                    nest++;
                break;
            case T_COND:
                if (tok == T_ENDC)
                    nest++;
                break;
            }
            /* fall through */
        default:
            skipLine();
            break;
        case EOF:
            error("EOF inside conditional");
            return;
        }
    }
}

/**************************************************************************
 27 14b9 +++
 *  optimiser used better code for ps = yylval.ySym and inverted T_ENDM
 * tests and jumps i.e. equivalent code
 **************************************************************************/
char *parseMacroBody() {
    sym_t *ps;
    int16_t var4;
    int16_t tok;
    register char *pstr;
    skipLine();
    if (GetCh() == EOF) {
        error("EOF inside macro def'n");
        return "";
    }
    inPtr--;
    lineLen++;
    macroSize = 200;
    macroUsed = 0;
    var4      = 1;
    if ((pstr = malloc(macroSize)) == NULL)
        fatalErr("No space for macro def'n");
    *pstr     = '\0';
    macroBase = pstr;
    for (;;) {
        switch (tok = yylex()) {
        case T_MACRO:
            var4++;
            continue;
        case EOF:
            error("EOF inside macro defn'n");
            break;
        case T_ENDM:
            if (--var4)
                continue;
            break;
        case G_SYM:
            ps = yylval.ySym;
            if ((ps->sFlags & 0x2210) == F_BPAGE) {
                remSym(ps);
                free(ps->sName);
                free(ps);
            }
            continue;
        case T_EOL:
            skipLine();
            continue;

        default:
            continue;
        }
        macroBase[macroUsed] = '\0';
        pstr                 = realloc(macroBase, macroUsed + 1);
        macroBase            = 0;
        return pstr;
    }
}

/**************************************************************************
 28 15fc +++
 * minor variance in that optimiser generates slightly worse code for --n
 **************************************************************************/
char *getMacroArg() {
    uint16_t n;

    register char *s = yytext;
    while (Isspace(PeekCh()))
        GetCh();
    while (lineLen > 0 && PeekCh() != ',' && PeekCh() != ';' && !Isspace(PeekCh())) {
        if (PeekCh() == '<') {
            GetCh();
            n = 1;
            while (lineLen > 0) {
                if (PeekCh() == '<')
                    n++;
                if ((*s++ = (char)GetCh()) == '>' && --n == 0) {
                    s--;
                    break;
                }
            }
            if (lineLen <= 0)
                error("Unterminated macro arg");
        } else
            *s++ = (char)GetCh();
    }
    *s++ = ' ';
    *s   = '\0';
    if (PeekCh() == ';')
        skipLine();
    if (lineLen > 0)
        GetCh();
    return yytext;
}
/**************************************************************************
29	sub_180ah +++
**************************************************************************/
static int16_t isFloat(char *s) {
    bool hasE = false;

    if (*s == '+' || *s == '-')
        s++;

    for (; *s; ++s) {
        if (*s == 'e' || *s == 'E') {
            hasE = true;
            if (s[1] == '+' || s[1] == '-')
                return true;
            continue;
        }
        if (*s == '.')
            return true;
        else if (!Isdigit(*s))
            return false;
    }
    return hasE;
}

/**************************************************************************
 30	parseDirective +++
 * a couple of basic blocks moved but code equivalent
 **************************************************************************/
static int16_t parseDirective() {
    char *fname;
    char *s;

    switch (inBuf[1]) {
    case 'T':
    case 't': /* Title */
        setTitle(skipToNextToken(inBuf + 2));
        break;
    case 'H':
    case 'h':; /* Heading */
        topOfPage();
        setHeading(skipToNextToken(inBuf + 2));
        break;
    case 'E':
    case 'e': /* Eject */
        if (macroBase != 0)
            return true;
        topOfPage();
        break;
    case 'L':
    case 'l': /* List */
        if (macroBase != 0)
            return true;
        controls = l_opt && phase == 2 && listDirective(inBuf + 2);
        break;

    case 'I':
    case 'i': /* Include */
        s = fname = skipToNextToken(inBuf + 2);
        while (*s != 0 && !Isspace(*s))
            ++s;
        *s = 0;
        openFile(fname);
        break;
    default:
        error("Directive not recognized");
        return true;
    }
    resetMacroList();
    return false;
}

/**************************************************************************
 31 1985 +++
 * minor variant as zatol now declared with base as uint8_t
 * also different way of doing --iy, neither optimal
 **************************************************************************/
static int parseNumber() {
    register char *s = yytext + 1;
    uint8_t base     = 0;

    while (Isxdigit(PeekCh()) || (floatMode == 2 && PeekCh() == '.'))
        *s++ = (char)GetCh();
    switch (PeekCh()) {
    case 'H':
    case 'h':
        base = 16;
        GetCh();
        break;
    case 'O':
    case 'o':
    case 'Q':
    case 'q':
        base = 8;
        GetCh();
        break;
    case '+':
    case '-':
        if (s[-1] == 'e' || s[-1] == 'E') {
            do {
                *s++ = (char)GetCh();
            } while (Isdigit(PeekCh()));
            break;
        }
        /* fall through */

    default:
        if (s[-1] == 'f' || s[-1] == 'b') {
            s--;
            tmpId       = *s == 'f' ? G_FWD : G_BWD;
            *s          = 0;
            yylval.yNum = atol(yytext);
            return tmpId;
        } else if (s[-1] == 'B') {
            s--;
            base = 2;
        }
        break;
    }
    *s = 0;
    if (base == 0 && floatMode == 2 && isFloat(yytext)) {
        yylval.yFloat = zatof(yytext);
        return G_FLOAT;
    }
    if (base == 0)
        base = 10;
    yylval.yNum = zatol(yytext, base);
    return G_INT;
}

/**************************************************************************
32	1b8c +++
**************************************************************************/
int16_t yylex() {
    int ch;
    char *tokStart;
    register char *s;
    for (;;) {
        s        = yytext;
        tokStart = inPtr;
        switch (ch = GetCh()) {
        case -1:
            return -1;
        case '\t':
        case ' ':
            continue;
        case '\f':
            topOfPage();
            continue;
        case '\'':
            while (PeekCh() && PeekCh() != '\'')
                *s++ = (char)GetCh();
            if (PeekCh() == '\'')
                GetCh();
            else
                error("Unterminated string");
            *s          = 0;
            yylval.yStr = yytext;
            return G_STR;
        case '.':
            *s++ = ch;
            while (Isalpha(PeekCh()))
                *s++ = (char)GetCh();
            if (PeekCh() == '.')
                *s++ = (char)GetCh();
            break;
        case ',':
            return T_COMMA;
        case ':':
            return T_COLON;
        case '(':
            yylval.yVal = 9; /* change precedence */
            return T_LPAREN;
        case ')':
            yylval.yVal = 1;
            return T_RPAREN;
        case '+':
            yylval.yVal = 5;
            return T_PLUS;
        case '-':
            yylval.yVal = 5;
            return T_MINUS;
        case '*':
            if (inPtr != inBuf + 1)
                goto getId;
            if (!parseDirective())
                continue;
            else
                skipLine();
            /* fall through */
        case '\0':
        case ';':
            return T_EOL;
        default:
        getId:
            *s++ = ch;
            if (Isalpha(ch)) {
                while (Isalnum(PeekCh()))
                    *s++ = (char)GetCh();
                if (s == yytext + 2 && PeekCh() == '\'')
                    *s++ = (char)GetCh();
            } else if (Isdigit(ch))
                return parseNumber();
            break;
        }

        while (Isspace(PeekCh()))
            GetCh();
        *s = 0;
        if (symFlags) {
            tmpId = getPsectId(yytext);
            if (tmpId != -1)
                return tmpId;
        }
        if (yytext[0] != '_') {
            tmpId = getKwdId(yytext);
            if (tmpId != -1)
                return tmpId;
        }
        if (Isalpha(yytext[0])) {
            yylval.ySym = getSym(yytext, symFlags);
            if (yylval.ySym->sFlags & 0x2000) {
                inPtr = tokStart;
                openMacro(yylval.ySym);
            } else
                return G_SYM;
        } else
            error("Lexical error");
    }
}

/**************************************************************************
 33	1f54	+++
 **************************************************************************/
static int16_t popSrc() {
    register char *name;

    if (srcSP > 0) {
        if (srcStack[srcSP].srcType == 0) { /* from file */
            fclose(srcStack[srcSP].srcFp);
            free(srcStack[srcSP].srcName);
        } else if (srcStack[srcSP].srcType == 1)
            freeMacro(srcStack[srcSP].srcSym);
        if (--srcSP > 0) {
            curLineno   = srcStack[srcSP].srcLineno;
            controls    = (char)srcStack[srcSP].srcControls;
            curFileName = srcStack[srcSP].srcName;
            if (c_opt && crfFp)
                fprintf(crfFp, "~%s\n", curFileName);
            return true;
        }
    }
    curFileName = "";
    if ((name = getNextFile()) == NULL)
        return false;
    openFile(name);
    return true;
}

/**************************************************************************
 34	openFile +++
 **************************************************************************/
static void openFile(char *name) {
    char *s;
    register FILE *fp;

    if ((fp = fopen(name, "r")) == 0)
        fatalErr("Can't open %sfile %s", (srcSP != 0) ? "include " : "", name);
    srcStack[srcSP].srcLineno   = curLineno;
    srcStack[srcSP].srcControls = controls;
    if (++srcSP == MAXINCL)
        fatalErr("Include files nested too deep");
    srcStack[srcSP].srcType = 0;
    srcStack[srcSP].srcFp   = fp;
    s                       = xalloc(strlen(name) + 1);
    strcpy(s, name);
    srcStack[srcSP].srcName = curFileName = s;
    if (crfFp && c_opt)
        fprintf(crfFp, "~%s\n", name);
    curLineno = 0;
}

/**************************************************************************
 35	openMacro +++
 **************************************************************************/
void openMacro(register sym_t *pSym) {
    if (srcSP > 0 && srcStack[srcSP].srcType && lineLen > 0)
        srcStack[srcSP].srcText -= lineLen;
    srcStack[srcSP].srcLineno   = curLineno;
    srcStack[srcSP].srcControls = controls;
    if (++srcSP == MAXINCL)
        fatalErr("Macro expansions nested too deep");
    srcStack[srcSP].srcType = (pSym->sFlags & 0x1000) ? 1 : 2;
    srcStack[srcSP].srcName = curFileName;
    srcStack[srcSP].srcText = pSym->sProp.vText;
    srcStack[srcSP].srcSym  = pSym;
    lineLen                 = 0;
}

/**************************************************************************
 36	getText	+++
 **************************************************************************/
int16_t getText() {
    flushLine();
    for (;;) {
        if (readSrc())
            break;
        if (!popSrc())
            return EOF;
    }
    lineLen = (int16_t)strlen(inBuf);
    if (srcStack[srcSP].srcType == 0)
        ++curLineno;
    inPtr = inBuf;
    initLine();
    l9bc2h = 0;
    if (inBuf[lineLen - 1] == '\n')
        inBuf[lineLen - 1] = srcStack[srcSP].srcType == 2 ? ' ' : 0;
    --lineLen;
    return *(uint8_t *)inPtr++;
}

/**************************************************************************
 37	readSrc	+++
 **************************************************************************/

static bool readSrc() {
    register char *s;

    if (srcSP == 0)
        return 0;

    if (srcStack[srcSP].srcType != 0) { /* reading text expansion */
        s = inBuf;

        for (s = inBuf; s < inBuf + sizeof(inBuf) && *srcStack[srcSP].srcText;)
            if ((*s++ = *srcStack[srcSP].srcText++) == '\n')
                break;
        *s = 0;
        return s != inBuf;
    } else
        return fgets(inBuf, 256, srcStack[srcSP].srcFp) != 0;
}

/* Linux by default passes through \r on fgets
   this mapped function ignores it
*/
#if !defined(CPM) && !defined(_MSC_VER)
#define CPMEOF 0x1a

char *afgets(char *s, int n, FILE *stream) {

    int ch = EOF;
    char *ptr;

    ptr = s;
    while (--n && (ch = getc(stream)) != EOF && ch != CPMEOF)
        if (ch != '\r' && (*ptr++ = ch) == '\n')
            break;

    if (ch == CPMEOF) /* incase partial last line is terminated with CPMEOF */
        ungetc(ch, stream);
    *ptr = '\0';
    return ptr == s ? NULL : s;
}

#endif

/**************************************************************************
 38	listDirective +++
 **************************************************************************/
static bool listDirective(char *s) {
    s = skipToNextToken(s);
    if ((*s++ + 0x20) != 'o')
        error("Bad arg to *L");
    return i_opt || (*s + 0x20) == 'n';
}

/**************************************************************************
 39	skipLine	+++
 **************************************************************************/
void skipLine() {
    if (lineLen >= 0)
        inPtr += lineLen;
    lineLen = 0;
}

/**************************************************************************
 40	initLine +++
 **************************************************************************/
static void initLine() {
    if (lstThisLine)
        return;
    if ((showHex = lstThisLine = controls) == 0)
        return;
    outPtr    = outLine;
    pHexStart = hexLines;
    initHexLine();
    hexLineCnt = 1;
}

/**************************************************************************
 41	initHexLine: +++
 **************************************************************************/
static void initHexLine() {
    register char *p;

    p    = pHexStart + LIST_FRAGMENT_SIZE;
    *--p = 0;

    while (p > pHexStart)
        *--p = ' ';

    if (pHexStart == hexLines && srcStack[srcSP].srcType == 0)
        sprintf(pHexStart, "%4d", curLineno);

    pHexStart[4] = (srcSP > 1) ? '+' : ' ';
    pHexCode     = &pHexStart[14];
}

/**************************************************************************
 42 tagHex 24b8 +++
 * code generated for flag == is different but equivalent. The original
 * tests each byte separately, the current code compares using sbc on the
 * whole value
 * also one basic block located differently
 **************************************************************************/
void tagHex(uint16_t flag) {
    if (!showHex)
        return;
    if (pHexStart[8] == ' ') {
        hex4(pHexStart + 8, curPsect->sProp.vNum);
        if ((curPsect->sFlags & 0xc0) != 0xc0)
            pHexStart[12] = '\'';
    }
    if (pHexStart + 14 == pHexCode)
        return;
    if (flag == 0x10)
        *pHexCode++ = '*';
    else if (flag == 0x100)
        *pHexCode++ = '\'';
    if (pHexStart + 26 <= ++pHexCode) {
        if (hexLineCnt == 10)
            showHex = false;
        else {
            pHexStart = &hexLines[hexLineCnt++ * 33];
            initHexLine();
        }
    }
}

/**************************************************************************
 43 putByte 258c +++
 **************************************************************************/
void putByte(uint16_t n, uint16_t flag) {
    if (showHex) {
        hex2(pHexCode, n);
        pHexCode += 2;
        tagHex(flag);
    }
}
/**************************************************************************
 44 putAddr 25bb +++
 **************************************************************************/
void putAddr(uint16_t n, uint16_t flag) {
    if (showHex) {
        hex4(pHexCode, n);
        pHexCode += 4;
        tagHex(flag);
    }
}

/**************************************************************************
 45 flushLine 25ec +++
 **************************************************************************/
static void flushLine() {
    char *s;
    int16_t i;
    int16_t j;
    register char *p;

    j = i = (int16_t)(inPtr - (s = inBuf));
    if (macroBase) {
        if (macroUsed + i + 2 >= macroSize) {
            macroSize = macroUsed + i + 200;
            macroBase = realloc(macroBase, macroSize);
            if (!macroBase)
                fatalErr("No space for macro def'n");
        }
        p = macroBase + macroUsed;
        macroUsed += i;
        while (j--)
            *p++ = *s++;
        if (*--p == 0)
            *p = '\n';
    }
    if (!lstThisLine)
        return;
    p = outPtr;
    s = inBuf;
    while (i--)
        *p++ = *s++;
    if (p[-1]) {
        outPtr = p;
        return;
    }
    if (!lstThisLine)
        return;
    i = 0;
    p = outLine;
    if (hexLineCnt > 1 && &pHexStart[14] == pHexCode)
        hexLineCnt--;
    for (; i < hexLineCnt || *p; i++) {
        if (rowCnt == 0)
            prHeading();
        if (i < hexLineCnt)
            printf("%s", &hexLines[i * 33]);
        if (*p) {
            if (i >= hexLineCnt)
                printf("\t\t\t\t");
            j = 32;
            while (*p && j < width) {
                if (*p == '\t')
                    j = (j + 8) & ~7;
                else
                    j++;
                fputc(*p++, stdout);
            }
        }
        fputc('\n', stdout);
        if (++rowCnt == 61)
            topOfPage();
        ;
    }
    lstThisLine = false;
}

/**************************************************************************
46 hex2	2829h +++
 **************************************************************************/
static void hex2(register char *p, int16_t val) {
    *p++ = "0123456789ABCDEF"[(val >> 4) & 0xf];
    *p   = "0123456789ABCDEF"[val & 0xf];
}

/**************************************************************************
 47 hex4	286dh +++
 **************************************************************************/
static void hex4(register char *p, int16_t val) {
    hex2(p, val >> 8);
    hex2(p + 2, val);
}

/**************************************************************************
 48	setHeading	sub-289Fh	+++
 ***************************************************************/
void setHeading(char *text) {
    strncpy(heading, text, sizeof(heading) - 1);
    heading[sizeof(heading) - 1] = 0;
}
/**************************************************************************
49 28bc +++
***************************************************************/
static void resetMacroList() {
    if (!i_opt) {
        lineLen     = 0;
        inPtr       = inBuf;
        lstThisLine = false;
    }
}
/**************************************************************************
50	topOfPage	sub-28D2h	+++
***************************************************************/
void topOfPage() {
    if (controls && rowCnt) {
        fputc('\f', stdout);
        rowCnt = 0;
    }
}

/**************************************************************************
51	prHeading	sub-28F1h	+++
***************************************************************/
static void prHeading() {
    int16_t spc;

    printf("\n\n");
    printf("HI-TECH SOFTWARE Z80 Macro Assembler: %s", curFileName);
    printf("\n%s", title);
    spc = width - (int16_t)strlen(title) - 10;
    while (spc-- > 0)
        fputc(' ', stdout);
    printf("Page%4d\n%s\n\n", ++pageNo, heading);
    rowCnt = 6;
}

/**************************************************************************
 52	setTitle	sub-2970h	+++
 ***************************************************************/
static void setTitle(char *text) {
    strncpy(title, text, sizeof(title) - 1);
    title[sizeof(title) - 1] = 0;
}

/**************************************************************************
 53 298d +++
 **************************************************************************/
void putTaggedAddr(prop_t *sProp, int16_t ch) {
    int16_t var2;
    if (showHex) {
        pHexStart[20] = (char)ch;
        pHexCode      = pHexStart + 8;
        if (sProp->cExtSym)
            var2 = F_GLOBAL;
        else if (sProp->cPsectSym)
            var2 = F_PSECT;
        else
            var2 = 0;
        putAddr(sProp->vNum, var2);
    }
}
/**************************************************************************
 54 29fe +++
 **************************************************************************/
void putErrCode(int16_t ch) {
    if (showHex) {
        if (pHexStart[5] == ' ')
            pHexStart[5] = (char)ch;
        else
            pHexStart[6] = (char)ch;
    }
}

/**************************************************************************
 55	prSymbols 2a23 +++
 **************************************************************************/
void prSymbols() {
    char fmt[20];
    int col;
    sym_t **ppSym;
    char xrefType;

    setHeading("");
    topOfPage();
    prHeading();
    col = (width - 35) / 2;
    fputc('\n', stdout);
    while (col-- != 0)
        fputc(' ', stdout);

    printf("%s\n\n", "---------- Symbol Table ----------");
    rowCnt += 3;
    setHeading("Symbol Table");
    absPsect->sName = "(ABS)";
    if (maxSymLen < 6)
        maxSymLen = 6;
    sprintf(fmt, "%%%ds %%s%%c  ", maxSymLen);
    ppSym     = symTable;
    maxSymLen = width / (maxSymLen + 8); /* reuse maxSymLen for symbols per line */
    col       = 0;
    while (*ppSym) {
        if (!((*ppSym)->sFlags & 0x1000)) {
            if ((*ppSym)->sFlags & 0x100)
                xrefType = '#';
            else if ((*ppSym)->sFlags & 0x200)
                xrefType = '*';
            else if ((*ppSym)->sProp.cPsectSym)
                xrefType = '\'';
            else
                xrefType = ' ';

            if (col >= maxSymLen) {
                fputc('\n', stdout);
                col = 0;
                if (++rowCnt == 61)
                    topOfPage();
            }
            ++col;
            if (rowCnt == 0)
                prHeading();
            hex4(inBuf, (*ppSym)->sProp.vNum);
            inBuf[4] = 0;
            printf(fmt, (*ppSym)->sName, inBuf, xrefType);
        }
        ++ppSym;
    }
    fputc('\n', stdout);
    absPsect->sName = "";
}
