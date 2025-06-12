/*
 *
 * The lex.c file is part of the restored ZAS.EXE program
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
#include "cclass.h"
#include "zas.h"

char *macroBase;         /* 200e */
int16_t macroSize;       /* 2010 */
int16_t pageNo;          /* 2012 */
char outLine[306];       /* 2014 */
yytype_t ungetYylval;    /* 2146 */
int16_t pageLen = 66;    /* 214a - original was bss */
bool lstThisLine;        /* 214c */
char heading[41];        /* 214d */
char *timeStr;           /* 2176 */
time_t curTime;          /* 2178 */
int16_t ungetYytok;      /* 217c */
int16_t hexLineCnt;      /* 217e */
src_t srcStack[MAXINCL]; /* 2180 */
char *pHexCode;          /* 22e8 */
char yytext[100];        /* 22ea */
bool showHex;            /* 234e */
int16_t lineLen;         /* 2350 */
char title[41];          /* 2352 */
char b9f0b;              /* 237b - only has 0 written to it otherwise not used */
char *outPtr;            /* 237c */
int16_t rowCnt;          /* 237e */
int16_t curLineno;       /* 2380 */
char *curFileName;       /* 2382 */
char *inPtr;             /* 2384 */
char controls;           /* 2386 */
int16_t tmpId;           /* 2388 */
char *pHexStart;         /* 238A */
int16_t srcSP;           /* 238c */
char inBuf[256];         /* 238e */
char hexLines[LIST_FRAGMENT_SIZE * MAX_LIST_FRAGMENT]; /* 248e */
int16_t width;                                         /* 25d8 */

static char *skipToNextToken(register char *s);       /* 29 0DDE */
static int32_t zatol(register char *s, uint8_t base); /* 30 0E1C */
static int16_t parseNumber(void);                     /* 35 1424 */
static bool listDirective(char *s);                   /* 38 15EE */
static int16_t parseDirective(void);                  /* 39 1636 */
static int16_t popSrc(void);                          /* 42 1A8A */
static void openFile(char *name);                     /* 44 1C70 */
static void initHexLine(void);                        /* 46 1E3A */
static void initLine(void);                           /* 47 1EA2 */
static int16_t GetCh(void);                           /* 48 1ED0 */
static int16_t PeekCh(void);                          /* 49 1F70 */
static bool readSrc(void);                            /* 50 1FB8 */
static void hex2(register char *p, int16_t val);      /* 52 2088 */
static void hex4(register char *p, int16_t val);      /* 53 20AE */
static void flushLine(void);                          /* 57 21DE */
static void resetMacroList(void);                     /* 59 234A */
static void prHeading(void);                          /* 61 2382 */
static void setTitle(char *text);                     /* 62 2444 */

/* unused functions */
#ifdef _FORCE
static char *sub_13c0(void);       /* 34 13C0 */
static bool sub_1a0a(void);        /* 41 1A0A */
static void sub_1ba8(void);        /* 43 1BA8 */
static void spaceLines(int16_t n); /* 66 2666 */
#endif

/**************************************************************************
29	0dde ++
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
 30	zatol	++
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
           the compiler doesn't detect this and issues a complaint
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
 31 0eaa ++
 **************************************************************************/
void parseCond(int16_t tok) {
    int16_t ch;
    int16_t nest;

    register char *s;
    skipLine();
    nest = 1;
    for (;;) {
        if ((ch = GetCh()) == EOF) {
            error("EOF inside conditional");
            return;
        }
        while (Isspace(ch))
            ch = GetCh();

        switch (ch) {
        case ' ':
        case '\t':
            continue;
        case 'C':
        case 'E':
        case 'I':
        case 'M':
        case 'c':
        case 'e':
        case 'i':
        case 'm':
            s    = yytext;
            *s++ = (char)ch;
            while (Isalnum(PeekCh()))
                *s++ = (char)GetCh();
            *s = 0;
            switch (getKwdId(yytext)) {
            case G_END:
            case T_ELSE:
                if (tok == G_END && --nest == 0)
                    return;
                break;
            case T_ENDM:
                if (tok == T_ENDM && --nest == 0)
                    return;
                break;
            case T_MACRO:
                if (tok == T_ENDM)
                    nest++;
                break;
            case T_COND:
                if (tok == G_END)
                    nest++;
                break;
            }
            break;
        case EOF:
            error("EOF inside conditional");
            return;
        }
        skipLine();
    }
}

/**************************************************************************
 32 0f8c++
 **************************************************************************/
char *parseMacroBody() {
    int16_t ch;
    int16_t idx;
    int16_t depth;
    register char *body;
    sym_t *ps;
    char *t;
    char *r;
    register char *pstr;

    skipLine();
    if (GetCh() == EOF) {
        error("EOF inside macro def'n");
        return "";
    }
    lineLen++;
    inPtr--;

    idx   = 0;
    depth = 1;
    if (!macroBase && !(macroBase = malloc(macroSize = 200)))
        fatalErr("No space for macro def'n");
    macroBase[0] = '\0';
    pstr         = macroBase;
    for (;;) {
        switch (ch = PeekCh()) {
        case EOF:
            goto eof;
        case 0x7f:
            GetCh();
            ch = GetCh();
            inPtr -= 2;
            openArg(ch);
            break;
        case '&':
            if (depth == 1) {
                GetCh();
                continue;
            }
            /* FALLTHRU */
        default:
            if (Isdigit(PeekCh())) {
                do {
                    *pstr++ = (char)GetCh();
                } while (Isxdigit(PeekCh()));
                break;
            } else if (Isalpha(PeekCh())) {
                t    = yytext;

                *t++ = (char)GetCh();
                for (;;) {
                    while (Isalnum(PeekCh()))
                        *t++ = (char)GetCh();
                    if (PeekCh() != 0x7f)
                        break;
                    GetCh();
                    ch = GetCh();
                    inPtr -= 2;
                    openArg(ch);
                }
                *t = '\0';
                ch = getKwdId(yytext);
                if (ch == -1) {
                    ps = findSymSlot(yytext);
                    if (ps && (ps->sFlags & S_MLOCAL)) {
                        *pstr++ = 0x7f;
                        *pstr++ = (char)ps->mSlotCnt;
                        break;
                    }
                } else
                    switch (ch) {
                    case T_MACRO:
                    case T_REPT:
                    case T_IRP:
                    case T_IRPC:
                        depth++;
                        break;
                    case T_ENDM:
                        if (--depth == 0) {
                            while (Isspace(pstr[-1]))
                                pstr--;
                            skipLine();
                            goto done;
                        }
                        break;
                    case T_LOCAL:
                        parseLocal();
                        while (Isspace(pstr[-1]))
                            pstr--;
                        *pstr = 0;
                        skipLine();
                        if (GetCh() == EOF)
                            goto eof;
                        else {
                            lineLen++;
                            inPtr--;
                            continue;
                        }
                    }
                strcpy(pstr, yytext);
                pstr += strlen(yytext);
                break;
            } else { // 11fe
                if ((*pstr++ = (char)GetCh()) != ';')
                    break;
                if (PeekCh() == ';')
                    do {
                        if (--pstr == macroBase)
                            break;
                    } while (Isspace(pstr[-1]));
                /* will fall through to EOL case */
                else {
                    while (PeekCh())
                        *pstr++ = (char)GetCh();
                    break;
                }
            }
            /* FALLTHRU */
        case 0:
            *pstr++ = '\n';
            skipLine();
            if (GetCh() == EOF)
                goto eof;
            lineLen++;
            inPtr--;
            break;
        }
        if (pstr > macroBase + macroSize - 100) {
            idx = (int16_t)(pstr - macroBase);
            if ((macroBase = realloc(macroBase, macroSize += 200)) == NULL)
                fatalErr("Insufficient memory for macro def'n");
            pstr = macroBase + idx;
        }
    }

eof:
    error("EOF inside macro def'n");

done:
    *pstr = '\0';
    if ((body = malloc(pstr - macroBase + 1)) == NULL) {
        body      = realloc(macroBase, pstr - macroBase + 1);
        macroBase = 0;
    } else { // 1071
        r  = body + (pstr - macroBase);
        *r = 0;
        while (pstr != macroBase)
            *--r = *--pstr;
    } // 1094
    return body;
}

/**************************************************************************
 33 125c ++
 **************************************************************************/
char *getMacroArg() {
    uint16_t n;
    int16_t ch2 = 0; // original wasn't intialised !!!
    rval_t expr;
    bool noArg = true;
    int16_t ch;
    int16_t var2;

    register char *s;

    while (Isspace(PeekCh()))
        GetCh();
    if (PeekCh() == '%') {
        GetCh();
        tokType = yylex();
        expr    = *evalExpr();
        if (expr.type != 0)
            error("Macro argument after % must be absolute");
        sprintf(yytext, "%" PRId32, expr.val);
    } else {
        s = yytext;
        while ((ch = PeekCh()) && ch != ',' && ch != ';' && !Isspace(ch)) {
            noArg = false;
            if (ch == '!') { /* verbetim */
                GetCh();
                if (PeekCh())
                    *s++ = (char)GetCh();
            } else if (ch == '<') {
                GetCh();
                n = 1;
#if 0
            /* the handling of nested <..> looks to be broken
               args such as <<a b>,<c d>,<e!<>>
               get stored as
               a b>,c d>,e<!>
               it would be much better to keep < except for the outer one
               also the ! processing stores the !, skips a char and stores the next one
               I suspect the intent was to store the char after the !
               but should probably be store the ! and the following character
               
               i.e.
               <a b>,<c d>,<e!<>
               which on expansion would translate to
               a b
               c d
               e<

            */
            for (;;) {
                if (PeekCh() == 0)  // looks like ch2 = PeekCh() should be here to fix ! processing
                    break;
                if (ch2 == '!') {   //  warning ch2 has a random value on first pass
                    GetCh();        // as the ! is stored below, this trashes the char after !
                    if (PeekCh())   // and stores the one after it!!
                        *s++ = GetCh();
                }
                if ((ch2 = GetCh()) == EOF)
                    break;
                if (ch2 == '<')
                    n++;           // all opening < are removed
                else if (ch2 == 0x7f) {
                    var2 = GetCh();
                    inPtr -= 2;
                    openArg(var2);
                } else {
                    *s++ = ch2;
                    if (ch2 == '>' && --n == 0) {
                        s--;
                        break;
                    }
                }
            }
#else
                /* PMO fixed version */
                while (PeekCh() && (ch2 = GetCh()) != EOF) {
                    if (ch2 == 0x7f) {
                        var2 = GetCh();
                        inPtr -= 2;
                        openArg(var2);
                    } else {
                        *s++ = (char)ch2;
                        if (ch2 == '!') {
                            if (PeekCh())
                                *s++ = (char)GetCh(); // inner !x are left as is
                        } else if (ch2 == '<')
                            n++;
                        else if (ch2 == '>' && --n == 0) {
                            s--; // remove outer >
                            break;
                        }
                    }
                }
#endif
                if (n)
                    error("Unterminated macro arg");
            } else if (ch == 0x7f) {
                GetCh();
                var2 = GetCh();
                inPtr -= 2;
                openArg(var2);
            } else
                *s++ = (char)GetCh();
        }
        *s = '\0';
        if (lineLen > 0 && !Isspace(PeekCh()))
            GetCh();
    }
    return noArg ? NULL : yytext;
}

/**************************************************************************
 34 13c0 ++ (not used)
**************************************************************************/
#if _FORCE
static char *sub_13c0() {
    char *s = yytext;
    int ch;
    while (Isspace(PeekCh()))
        GetCh();
    while ((ch = PeekCh()) && ch != ')' && ch != '\n') {
        if (ch != 0x7f)
            *s++ = (char)GetCh();
        else {
            GetCh();
            ch = GetCh();
            inPtr -= 2;
            openArg(ch);
        }
    }
    if (ch == ')')
        GetCh();
    *s = '\0';
    return yytext;
}
#endif

/**************************************************************************
 35 1424 ++
 **************************************************************************/
static int16_t parseNumber() {
    register char *s = yytext + 1;
    bool isFloat     = false;
    uint8_t base     = 0;

    for (;;) {
        if (Isxdigit(PeekCh()) || PeekCh() == '.') {
            if ((*s++ = (char)GetCh()) == '.' || (floatMode == 2 && (s[-1] == 'e' || s[1] == 'E')))
                isFloat = true;
        } else if (PeekCh() != 0x7f)
            break;
        else {
            GetCh();
            uint8_t argId = (char)GetCh();
            openArg(argId);
        }
    }

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
            isFloat = true;
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
            yylval.yNum = zatol(yytext, 10);
            return tmpId;
        } else if (s[-1] == 'B') {
            s--;
            base = 2;
        }
        break;
    }
    *s = 0;
    if (base == 0)
        base = 10;
    if (isFloat) {
        yylval.yFloat = (float)atof(yytext);
        return G_FLOAT;
    }

    yylval.yNum = zatol(yytext, base);
    return G_INT;
}

/**************************************************************************
 36 1576++
**************************************************************************/
void unget(int16_t dx) {
    ungetYytok  = dx;
    ungetYylval = yylval;
}

/**************************************************************************
 37 1592 ++
**************************************************************************/
bool nextIsMacroKwd() {
    char buf[256];
    char *s = inPtr;
    char *t = buf;
    while (Isspace(*s))
        s++;
    if (!Isalpha(*s))
        return false;
    while (Isalnum(*s))
        *t++ = *s++;
    *t = '\0';
    return getKwdId(buf) == T_MACRO;
}

/**************************************************************************
 38 15ee ++
 **************************************************************************/
static bool listDirective(char *s) {
    s = skipToNextToken(s);
    if ((*s++ + 0x20) != 'o')
        error("Bad arg to *L");
    return i_opt || (*s + 0x20) == 'n';
}

/**************************************************************************
 39 1636 ++
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
        topOfPage();
        break;
    case 'L':
    case 'l': /* List */
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
 40 1708 ++
**************************************************************************/
int16_t yylex() {
    int16_t ch;
    // char *tokStart;  set but not used
    register char *s;
    if (ungetYytok) {
        ch         = ungetYytok;
        yylval     = ungetYylval;
        ungetYytok = 0;
        return ch;
    }
    for (;;) {
        s = yytext;
        // tokStart = inPtr;
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
            while (PeekCh() && PeekCh() != ch) {
                if (PeekCh() == 0x7f) {
                    GetCh();
                    tokType = GetCh();
                    inPtr -= 2;
                    openArg(tokType);
                } else
                    *s++ = (char)GetCh();
            }
            if (PeekCh() == ch)
                GetCh();
            else
                error("Unterminated string");
            *s          = 0;
            yylval.yStr = yytext;
            return G_STR;

        case ',':
            return T_COMMA;
        case ':':
            return T_COLON;
        case '=':
            return G_EQ;
        case '>':
            return G_GT;
        case '<':
            return G_LT;
        case '(':
            yylval.yTok = 9; /* change precedence */
            return T_LPAREN;
        case ')':
            yylval.yTok = 1;
            return T_RPAREN;
        case '+':
            yylval.yTok = 5;
            return T_PLUS;
        case '-':
            yylval.yTok = 5;
            return T_MINUS;
        case '*':
            if (inPtr != inBuf + 1) {
                yylval.yTok = 6;
                return T_MULT;
            }
            if (parseDirective()) {
                skipLine();
                return T_EOL;
            } else
                continue;
        case '\0':
        case ';':
            return T_EOL;
        case '/':
            yylval.yTok = 6;
            return T_DIV;
        case 0x7f:
            tokType = GetCh();
            inPtr -= 2;
            openArg(tokType);
            continue;
        case '$':
            return T_DOLLAR;
        case '.':
            *s++ = (char)ch;
            while (Isalpha(PeekCh()))
                *s++ = (char)GetCh();
            if (PeekCh() == '.')
                *s++ = (char)GetCh();
            break;
        default:
            *s++ = (char)ch;
            if (Isalpha(ch)) {
                for (;;) {
                    if (Isalnum(PeekCh()))
                        *s++ = (char)GetCh();
                    else if (PeekCh() == 0x7f) {
                        GetCh();
                        tokType = GetCh();
                        inPtr -= 2;
                        openArg(tokType);
                    } else
                        break;
                }
                break;
            } else if (Isdigit(ch))
                return parseNumber();
            break;
        }

        if (s == yytext + 2 && PeekCh() == '\'' && (yytext[0] == 'A' || yytext[0] == 'a') &&
            (yytext[1] == 'f' || yytext[1] == 'F'))
            *s++ = (char)GetCh();

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
            return G_SYM;
        } else
            error("Lexical error");
    }
}

/**************************************************************************
 41 1a0a ++ (not used)
 **************************************************************************/
#ifdef _FORCE
static bool sub_1a0a() {
    int16_t savSP = srcSP;

    while (srcSP > 0) {
        if (srcStack[srcSP].srcType == 0) {
            fclose(srcStack[srcSP].srcFp);
            free(srcStack[srcSP--].srcName);
        } else if (srcStack[srcSP--].srcType == 1)
            sub_2996();
    }
    return savSP != 1;
}
#endif

/**************************************************************************
42 1a8a ++
 **************************************************************************/
static int16_t popSrc() {
    register char *name;
    bool isMacroArg;

    if (srcSP > 0) {
        if (srcStack[srcSP].srcType == 0) { /* from file */
            fclose(srcStack[srcSP].srcFp);
            free(srcStack[srcSP--].srcName);
            if (srcSP > 0) {
                curLineno   = srcStack[srcSP].srcLineno;
                controls    = (char)srcStack[srcSP].srcControls;
                curFileName = srcStack[srcSP].srcName;
                if (c_opt && crfFp)
                    fprintf(crfFp, "~%s\n", curFileName);
                return true;
            }
        } else {
            isMacroArg = srcStack[srcSP].srcType == 1;
            controls   = (char)srcStack[--srcSP].srcControls;
            curLineno  = srcStack[srcSP].srcLineno;
            if (isMacroArg)
                nextArgSub();
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
43 1ba8 ++ (not used)
 **************************************************************************/
#ifdef _FORCE
static void sub_1ba8() {
    tokType = yylex();
    while (srcStack[srcSP].srcType != 1) {
        if (srcStack[srcSP].srcType == 0) {
            fclose(srcStack[srcSP].srcFp);
            free(srcStack[srcSP].srcName);
        }
        srcSP--;
    }
    sub_2996();
    curLineno   = srcStack[--srcSP].srcLineno;
    controls    = srcStack[--srcSP].srcControls;
    curFileName = srcStack[--srcSP].srcName;
    if (crfFp && c_opt)
        fprintf(crfFp, "~%s\n", curFileName);
}
#endif

/**************************************************************************
44 1c70 ++
 **************************************************************************/
static void openFile(char *name) {
    char *s;
    register FILE *fp;

    if ((fp = fopen(name, "r")) == 0)
        fatalErr("Can't open %sfile %s", (srcSP != 0) ? "include " : "", name);
    if (crfFp && c_opt)
        fprintf(crfFp, "~%s\n", name);

    srcStack[srcSP].srcLineno   = curLineno;
    srcStack[srcSP].srcControls = controls;
    if (++srcSP == MAXINCL)
        fatalErr("Include files nested too deep");
    srcStack[srcSP].srcType = 0;
    srcStack[srcSP].srcFp   = fp;
    s                       = xalloc(strlen(name) + 1);
    strcpy(s, name);
    srcStack[srcSP].srcName = curFileName = s;

    curLineno                             = 0;
}

/**************************************************************************
45 1d60 ++
 **************************************************************************/
void openMacro(register char *text, uint16_t flag) {
    if (srcSP > 0 && srcStack[srcSP].srcType && lineLen > 0)
        srcStack[srcSP].srcText -= lineLen;
    srcStack[srcSP].srcLineno   = curLineno;
    srcStack[srcSP].srcControls = controls;
    if (++srcSP == MAXINCL)
        fatalErr("Macro expansions nested too deep");
    srcStack[srcSP].srcType = (flag & S_MACROARG) ? 1 : 2;
    srcStack[srcSP].srcName = curFileName;
    srcStack[srcSP].srcText = text;
    lineLen                 = 0;
}

/**************************************************************************
46 1e3a ++
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
47 1ea2 ++
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
48 1ed0 ++
 **************************************************************************/
static int16_t GetCh() {
    if (lineLen > 0) {
        lineLen--;
        return *(uint8_t *)inPtr++;
    }
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
    b9f0b = 0; /* not used */
    if (inBuf[lineLen - 1] == '\n')
        inBuf[lineLen - 1] = srcStack[srcSP].srcType == 2 ? ' ' : 0;
    --lineLen;
    return *(uint8_t *)inPtr++;
}

/**************************************************************************
 49 1f70 ++
 **************************************************************************/
static int16_t PeekCh() {
    int16_t ch;
    if (lineLen > 0)
        return *inPtr;
    if (srcStack[srcSP].srcType == 2) {
        if ((ch = GetCh()) != EOF) {
            lineLen++;
            inPtr--;
        }
        return ch;
    }
    return 0;
}

/**************************************************************************
 50 1fb8 ++
 **************************************************************************/
static bool readSrc() {
    register char *s;

    if (srcSP == 0)
        return false;

    if (srcStack[srcSP].srcType != 0) { /* reading text expansion */
        for (s = inBuf; s < inBuf + sizeof(inBuf) - 1 && *srcStack[srcSP].srcText;)
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
 51 2050 ++
 **************************************************************************/
void skipLine() {
    int16_t ch;
    while (PeekCh() && PeekCh() != EOF)
        if (GetCh() == 0x7f) {
            ch = GetCh();
            inPtr -= 2;
            openArg(ch);
        }
    lineLen = 0;
}

/**************************************************************************
 52 2088 ++
 **************************************************************************/
static void hex2(register char *p, int16_t val) {
    static char hexDigits[] = "0123456789ABCDEF";
    *p++                    = hexDigits[(val >> 4) & 0xf];
    *p                      = hexDigits[val & 0xf];
}

/**************************************************************************
 53 20ae++
 **************************************************************************/
static void hex4(register char *p, int16_t val) {
    hex2(p, val >> 8);
    hex2(p + 2, val);
}

/**************************************************************************
 54 20d2 ++
 **************************************************************************/
void tagHex(uint16_t flag) {
    if (!showHex)
        return;
    if (pHexStart[8] == ' ') {
        hex4(pHexStart + 8, curPsect->pCurLoc);
        if (!(curPsect->sFlags & S_ABS))
            pHexStart[12] = '\'';
    }
    if (pHexStart + 14 == pHexCode)
        return;
    if (flag == TF_EXT)
        *pHexCode++ = '*';
    else if (flag == TF_REL)
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
 55 218a ++
 **************************************************************************/
void putByte(uint16_t n, uint16_t flag) {
    if (showHex) {
        hex2(pHexCode, n);
        pHexCode += 2;
        tagHex(flag);
    }
}
/**************************************************************************
 56 21b4 ++
 **************************************************************************/
void putAddr(uint16_t n, uint16_t flag) {
    if (showHex) {
        hex4(pHexCode, n);
        pHexCode += 4;
        tagHex(flag);
    }
}

/**************************************************************************
 57 21de ++
 **************************************************************************/
static void flushLine() {
    char *s;
    int16_t i;
    int16_t col;
    register char *p;

    col = i = (int16_t)(inPtr - (s = inBuf));

    if (!lstThisLine)
        return;
    p = outPtr;
    while (i--)
        *p++ = *s++;
    *p = '\0';
    if (srcStack[srcSP].srcType == 2)
        outPtr = p;
    else if (lstThisLine) {
        i = 0;
        p = outLine;
        if (hexLineCnt > 1 && &pHexStart[14] == pHexCode)
            hexLineCnt--;
        for (; i < hexLineCnt || *p; i++) {
            if (rowCnt == 0 && pageLen)
                prHeading();
            if (i < hexLineCnt)
                printf("%s", &hexLines[i * 33]);
            if (*p) {
                if (i >= hexLineCnt)
                    printf("\t\t\t\t");
                col = 32;
                while (*p && col < width) {
                    if (*p == '\t')
                        col = (col + 8) & ~7;
                    else
                        col++;
                    fputc(*p++, stdout);
                }
            }
            fputc('\n', stdout);
            if (++rowCnt == pageLen - 5 && pageLen)
                topOfPage();
        }
        lstThisLine = false;
    }
}

/**************************************************************************
 58 232c ++
 ***************************************************************/
void setHeading(char *text) {
    strncpy(heading, text, sizeof(heading) - 1);
    heading[sizeof(heading) - 1] = 0;
}
/**************************************************************************
 59 234a ++
***************************************************************/
static void resetMacroList() {
    if (!i_opt) {
        lineLen     = 0;
        inPtr       = inBuf;
        lstThisLine = false;
    }
}

/**************************************************************************
 60 2364 ++
***************************************************************/
void topOfPage() {
    if (lstThisLine && rowCnt) {
        fputc('\f', stdout);
        rowCnt = 0;
    }
}

/**************************************************************************
 61 2382 ++
***************************************************************/
static void prHeading() {
    int16_t len;
    printf("\n\n");
    printf("HI-TECH SOFTWARE Z80 Macro Assembler: %s", curFileName);

    if (curTime == 0) {
        time(&curTime);
        timeStr = ctime(&curTime);
    }
    len = (int16_t)strlen(timeStr) + (int16_t)strlen(curFileName) +
          (int)sizeof("HI-TECH SOFTWARE Z80 Macro Assembler: ");
    while (len++ < width)
        fputc(' ', stdout);
    printf("%s", timeStr);
    printf("\n%s", title);
    len = width - (int16_t)strlen(title) - 10;
    while (len-- > 0)
        fputc(' ', stdout);
    printf("Page%4d\n%s\n\n", ++pageNo, heading);
    rowCnt = 6;
}

/**************************************************************************
 62 2444 ++
 ***************************************************************/
static void setTitle(char *text) {
    strncpy(title, text, sizeof(title) - 1);
    title[sizeof(title) - 1] = 0;
}

/**************************************************************************
 63 2462 ++
 **************************************************************************/
void putTaggedAddr(rval_t *val, char ch) {
    int16_t var2;
    if (showHex) {
        pHexStart[20] = ch;
        pHexCode      = pHexStart + 8;
        if (val->type == RT_EXT)
            var2 = TF_EXT;
        else if (val->type == RT_REL)
            var2 = TF_REL;
        else
            var2 = 0;
        putAddr((uint16_t)val->val, var2);
    }
}
/**************************************************************************
 64 24bc ++
 **************************************************************************/
void putErrCode(char ch) {
    if (showHex) {
        if (pHexStart[5] == ' ')
            pHexStart[5] = ch;
        else
            pHexStart[6] = ch;
    }
}

/**************************************************************************
 65 24e0 ++
 **************************************************************************/
void prSymbols() {
    char fmt[20];
    int16_t col;
    sym_t **ppSym;
    char xrefType;

    setHeading("");
    lstThisLine = true;
    topOfPage();
    if (pageLen)
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
        if (!((*ppSym)->sFlags & S_MACROARG) &&
            ((*ppSym)->sName[0] != '?' || (*ppSym)->sName[1] != '?' ||
             strlen((*ppSym)->sName) != 6)) {
            if ((*ppSym)->sFlags & S_PSECT)
                xrefType = '#';
            else if ((*ppSym)->sFlags & S_UNDEF)
                xrefType = '*';
            else if ((*ppSym)->rSym)
                xrefType = '\'';
            else
                xrefType = ' ';

            if (col >= maxSymLen) {
                fputc('\n', stdout);
                col = 0;
                if (++rowCnt == pageLen - 5 && pageLen)
                    topOfPage();
            }
            ++col;
            if (rowCnt == 0 && pageLen)
                prHeading();
            hex4(inBuf, (*ppSym)->pMaxLoc);
            inBuf[4] = 0;
            printf(fmt, (*ppSym)->sName, inBuf, xrefType);
        }
        ++ppSym;
    }
    fputc('\n', stdout);
    absPsect->sName = "";
}

/**************************************************************************
 66 2666 ++ (not used)
**************************************************************************/
#ifdef _FORCE
static void spaceLines(int16_t n) {
    while (n--) {
        if (rowCnt == pageLen - 5 && pageLen) {
            topOfPage();
            break;
        }
        fputc('\n', stdout);
    }
}
#endif
