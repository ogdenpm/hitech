#include "p1.h"

char *keywords[] = { /* 8f87 */
                     "asm",      "auto",   "break",  "case",   "char",   "continue", "default",
                     "do",       "double", "else",   "@@@@@",  "enum",   "extern",   "float",
                     "for",      "goto",   "if",     "int16_t",    "long",   "register", "return",
                     "short",    "sizeof", "static", "struct", "switch", "typedef",  "union",
                     "unsigned", "void",   "while"
};

char lastEmitSrc[64];  /* 9d60 */
bool sInfoEmitted;     /* 9da0 */
int16_t inCnt;         /* 9da1 */
char lastEmitFunc[40]; /* 9da3 */
YYTYPE yylval;         /* 9dcb */
char nameBuf[32];      /* 9dcf */
uint8_t ungetTok;      /* 9def */

int16_t strChCnt;    /* 9df0 */
bool lInfoEmitted;   /* 9df2 */
int16_t startTokCnt; /* 9df3 */
int16_t ungetCh;     /*  9df5 */

uint8_t parseNumber(int16_t ch);
uint8_t parseName(int16_t ch);
void parseAsm(void);
void parseString(int16_t ch);
int16_t getCh(void);
void prErrMsg(void);
int16_t skipWs(void);
int8_t escCh(int16_t ch);

/**************************************************
 * 56: 2671 PMO
 **************************************************/
uint8_t yylex() {
    int16_t ch;
    uint8_t tok;
    char buf[50];
    register char *s;

    if (ungetTok) {
        tok      = ungetTok;
        ungetTok = 0;
        if (tok == T_ID && byte_8f86)
            yylval.ySym = sub_4e90(nameBuf);
        return tok;
    }
    for (;;) {
        ch          = skipWs();
        startTokCnt = inCnt;
        if (Isalpha(ch))
            return parseName(ch);
        if (Isdigit(ch))
            return parseNumber(ch);
        switch (ch) {
        case EOF:
            return T_EOF;
        case '#':
            do {
                ch = getCh();
            } while (Isspace(ch) && ch != '\n');
            if (Isdigit(ch) && parseNumber(ch) == T_ICONST) {
                lineNo = yylval.yNum - 1;
                do {
                    ch = getCh();
                } while (Isspace(ch) && ch != '\n');
                if (ch == '"') {
                    for (s = buf; (ch = getCh()) != '"' && ch != '\n';)
                        *s++ = ch;
                    *s = '\0';
                    if (buf[0])
                        strcpy(srcFile, buf);
                    else if (srcFileArg)
                        strcpy(srcFile, srcFileArg);
                    else
                        *srcFile = '\0';
                    if (crfFp)
                        fprintf(crfFp, "~%s\n", srcFile);
                }
                break;
            } else {
                s = buf;
                do {
                    *s++ = ch;
                    ch   = getCh();
                } while (ch != '\n' && !Isspace(ch));
                *s = '\0';
                while (ch != '\n')
                    ch = getCh();
                if (strcmp(buf, "asm") == 0) {
                    parseAsm();
                    break;
                } else
                    fatalErr("illegal '#' directive");
            }
            /* FALLTHRU */
        case '"':
            parseString('"');
            return T_SCONST;
        case '\'':
            ch          = getCh();
            yylval.yNum = (ch == '\\') ? escCh(getCh()) : ch;
            ch          = getCh();
            if (ch == '\n')
                expectErr("closing quote");
            else if (ch != '\'')
                prError("char const too long");

            while (ch != '\n' && ch != '\'')
                ch = getCh();
            return T_ICONST;
        case ';':
            return T_SEMI;
        case ':':
            return T_COLON;
        case '+':
            ch = getCh();
            if (ch == '+')
                return T_INC;
            ungetCh = ch;
            ch      = skipWs();
            if (ch == '=')
                return T_PLUSEQ;
            ungetCh = ch;
            return T_PLUS;
        case '-':
            ch = getCh();
            if (ch == '-')
                return T_DEC;
            if (ch == '>')
                return T_POINTER;

            ungetCh = ch;
            ch      = skipWs();
            if (ch == '=')
                return T_MINUSEQ;
            ungetCh = ch;
            return T_MINUS;
        case '*':
            ch = skipWs();
            if (ch == '=')
                return T_MULEQ;
            ungetCh = ch;
            return T_STAR; /* deref or multiply */
        case '/':
            ch = skipWs();
            if (ch == '=')
                return T_DIVEQ;
            ungetCh = ch;
            return T_DIV;
        case '%':
            ch = skipWs();
            if (ch == '=')
                return T_MODEQ;
            ungetCh = ch;
            return T_MOD;
        case '&':
            ch = getCh();
            if (ch == '&')
                return T_LAND;
            ungetCh = ch;
            ch      = skipWs();
            if (ch == '=')
                return T_ANDEQ;
            ungetCh = ch;
            return T_BAND;
        case '|':
            ch = getCh();
            if (ch == '|')
                return T_LOR;
            ungetCh = ch;
            ch      = skipWs();
            if (ch == '=')
                return T_OREQ;
            ungetCh = ch;
            return T_BOR;
        case '^':
            ch = skipWs();
            if (ch == '=')
                return T_XOREQ;
            ungetCh = ch;
            return T_XOR;
        case '<':
            ch = getCh();
            if (ch == '<') {
                ch = skipWs();
                if (ch == '=')
                    return T_SHLEQ;
                else {
                    ungetCh = ch;
                    return T_SHL;
                }
            } else if (ch == '=')
                return T_LE;
            ungetCh = ch;
            return T_LT;
        case '>':
            ch = getCh();
            if (ch == '>') {
                ch = skipWs();
                if (ch == '=')
                    return T_SHREQ;
                else {
                    ungetCh = ch;
                    return T_SHR;
                }
            } else if (ch == '=')
                return T_GE;
            ungetCh = ch;
            return T_GT;
        case '=':
            ch = getCh();
            if (ch == '=')
                return T_EQEQ;
            ungetCh = ch;
            return T_EQ;
        case '!':
            ch = getCh();
            if (ch == '=')
                return T_NE;
            ungetCh = ch;
            return T_LNOT;
        case '~':
            return T_BNOT;
        case '(':
            return T_LPAREN;
        case ')':
            return T_RPAREN;
        case '[':
            return T_LBRACK;
        case ']':
            return T_RBRACK;
        case '{':
            return T_LBRACE;
        case '}':
            return T_RBRACE;
        case '.':
            ch = getCh();
            if (Isdigit(ch)) {
                ungetCh = ch;
                return parseNumber('.');
            }
            if (ch == '.') {
                ch = getCh();
                if (ch != '.')
                    prError("'.' expected after '..'");
                return T_3DOT;
            }
            ungetCh = ch;
            return T_DOT;

        case '?':
            return T_QUEST;
        case ',':
            return T_COMMA;
        default:
            prError("illegal character 0%o", ch);
            break;
        }
    }
}

/**************************************************
 * 57: 2CC3 PMO
 **************************************************/
uint8_t parseNumber(int16_t ch) {
    uint8_t digit;
    char buf[50];
    uint8_t base;
    long lval;
    register char *s = buf;

    while (Isdigit(ch)) {
        *s++ = ch;
        ch   = getCh();
    }
    if (ch == '.' || ch == 'e' || ch == 'E') {
        if (ch == '.')
            do {
                *s++ = ch;
                ch   = getCh();
            } while (Isdigit(ch));
        if (ch == 'e' || ch == 'E') {
            *s++ = 'e';
            ch   = getCh();
            if (ch == '+' || ch == '-') {
                *s++ = ch;
                ch   = getCh();
            }
            if (Isdigit(ch))
                do {
                    *s++ = ch;
                    ch   = getCh();
                } while (Isdigit(ch));
            else
                prError("exponent expected");
        }
        ungetCh = ch;
        *s++    = 0;
        if (*buf == '.')
            s++;
        yylval.yStr = xalloc(s - buf);
        if (*buf == '.') {
            strcpy(yylval.yStr, "0");
            strcat(yylval.yStr, buf);
        } else
            strcpy(yylval.yStr, buf);
        return T_FCONST; // float
    }
    base = 10;
    /* PMO code here has bugs, test should be
        (ch == 'x' || ch == 'X') && *buf == '0' && s == buf + 1
        currently it allows numbers such as
        9x123   0999X123 both as 0x123
        an even better option would be to ungetCh the x or X if the
        second part of the test is false
    */
    if (ch == 'x' || (ch == 'X' && *buf == '0')) {
        base = 16;
        *s   = 0;
        s    = buf;
        while (Isxdigit(ch = getCh()))
            *s++ = ch;
        if (s == buf)
            prError("hex digit expected");
    } else if (*buf == '0')
        base = 8;
    lval = 0L;
    s    = buf;
    while (*s) {
        if (*s >= 'A')
            digit = (*s++ | 0x20) - ('a' - 10);
        else
            digit = *s++ - '0';
        if (digit >= base) {
            prError("digit out of range");
            break;
        }
        lval = lval * 10 + digit;
    }
    yylval.yNum = lval;
    if (ch == 'l' || ch == 'L')
        return T_LCONST; // long const
    ungetCh = ch;
    return T_ICONST; // int16_t const
}

/**************************************************
 * 58: 2F75 PMO
 **************************************************/
uint8_t parseName(int16_t ch) {
    int16_t cmp;
    uint8_t hi;
    uint8_t lo;
    uint8_t mid;
    int16_t len;
    register char *s = nameBuf;

    len              = 0;
    do {
        if (len != sizeof(nameBuf) - 1) {
            *s++ = ch;
            len++;
        }
        ch = getCh();
    } while (Isalnum(ch));
    ungetCh = ch;
    *s      = 0;
    lo      = T_ASM;
    hi      = T_WHILE;
    do {
        mid = (lo + hi) / 2;
        cmp = strcmp(nameBuf, keywords[mid - T_ASM]);
        if (cmp <= 0)
            hi = mid - 1;
        if (cmp >= 0)
            lo = mid + 1;
    } while (hi >= lo);
    if (hi > lo - 1) {
        switch (mid) {
        case T_AUTO:
        case T_EXTERN:
        case T_REGISTER:
        case T_STATIC:
        case T_ASM:
        case T_TYPEDEF:
            yylval.yVal = mid;
            return S_CLASS;
        case T_CHAR:
        case T_DOUBLE:
        case T_ENUM:
        case T_FLOAT:
        case T_INT:
        case T_LONG:
        case T_SHORT:
        case T_STRUCT:
        case T_UNION:
        case T_UNSIGNED:
        case T_VOID:
            yylval.yVal = mid;
            return S_TYPE;
        case _T_SIZEOF:
            return T_SIZEOF;
        }
        return mid;
    }
    yylval.ySym = sub_4e90(nameBuf);
    return T_ID;
}

/**************************************************
 * 59: 308B PMO
 **************************************************/
void parseAsm() {
    char buf[512];
    int16_t ch;
    register char *s;

    for (;;) {
        s = buf;
        while ((ch = getCh()) != '\n' && ch != EOF)
            *s++ = ch;
        *s = 0;
        if (ch == EOF)
            fatalErr("EOF in #asm");
        if (strncmp(buf, "#endasm", 7) == 0)
            return;
        printf(";; %s\n", buf);
    }
}

/**************************************************
 * 60: 310B PMO
 **************************************************/
void parseString(int16_t ch) {
    char buf[1024];
    register char *s = buf;
    char *var4;
    char *var2;

    while (ch == '"') {
        while ((ch = getCh()) != '"') {
            if (ch == '\n') {
                expectErr("closing quote");
                break;
            }
            if (ch == '\\') {
                if ((ch = getCh()) != '\n')
                    *s++ = escCh(ch);
            } else
                *s++ = ch;
        }
        ch = skipWs();
    }
    ungetCh  = ch;
    *s       = 0;
    strChCnt = s - buf;
    var2 = var4 = xalloc(strChCnt + 1);
    ch          = strChCnt + 1; /* unwound memcpy. Note strcpy cannot handle embedded '\0' */
    s           = buf;
    while (ch--)
        *var2++ = *s++;
    yylval.yStr = var4;
}

int16_t ungetCh;
/**************************************************
 * 61: 320D PMO
 **************************************************/
int16_t getCh() {
    int16_t ch;
    if (ungetCh) {
        ch      = ungetCh;
        ungetCh = 0;
    } else if ((ch = inBuf[inCnt]) == 0) {
        if (s_opt)
            emitSrcInfo();
        sInfoEmitted = false;
        lInfoEmitted = false;
        if (!fgets(inBuf, 512, stdin))
            return EOF;
        inCnt       = 1;
        startTokCnt = 0;
        lineNo++;
        if (l_opt)
            prErrMsg();
        return inBuf[0];
    }
    return ch;
}

/**************************************************
 * 62: 329A PMO
 **************************************************/
void prErrMsg() {
    register char *iy;
    if (!lInfoEmitted) {
        iy = depth ? curFuncNode->nVName : "";

        if (strcmp(srcFile, lastEmitSrc) || strcmp(iy, lastEmitFunc)) {
            fprintf(stderr, "%s:", srcFile);
            if (*iy)
                fprintf(stderr, " %s()\n", iy);
            else
                fputc('\n', stderr);
            strcpy(lastEmitSrc, srcFile);
            strcpy(lastEmitFunc, iy);
        }
        fprintf(stderr, "%6d:\5%s", lineNo, inBuf);
        lInfoEmitted = true;
    }
}

/**************************************************
 * 63: 3350 PMO
 **************************************************/
void prMsgAt(register char *buf) {
    int16_t i;
    uint16_t col;
    prErrMsg();
    if (!*buf)
        fputs(buf, stderr);
    else {
        fputc('\t', stderr);
        for (i = 0, col = 0; i < startTokCnt - 1; i++)
            if (inBuf[i] == '\t')
                col = (col + 8) & 0xfff8;
            else
                col++;
        if (strlen(buf) + 1 < col)
            fprintf(stderr, "%*s ^ ", col - 1, buf);
        else
            fprintf(stderr, "%*c %s", col + 1, '^', buf);
    }
}

/**************************************************
 * 64: 3429 PMO
 **************************************************/
void emitSrcInfo() {
    register char *s;

    if (!sInfoEmitted && inBuf[0]) {
        for (s = inBuf; *s && Isspace(*s); s++)
            ;
        if (*s && *s != '#')
            printf(";; ;%s: %d: %s:", srcFile, lineNo, inBuf);
    }
    sInfoEmitted = true;
}

/**************************************************
 * 65: 347A PMO
 **************************************************/
int16_t skipWs() {
    int16_t ch;
    while (Isspace(ch = getCh()))
        ;
    return ch;
}

/**************************************************
 * 66: 3495 PMO
 **************************************************/
int8_t escCh(int16_t ch) {
    int16_t val;
    int8_t cnt;
    if (Isdigit(ch)) {
        val = ch - '0';
        ch  = getCh();
        if (Isdigit(ch)) {
            val = val * 8 + ch - '0';
            if (Isdigit(ch))
                val = val * 8 + ch - '0';
            else
                ungetCh = ch;
        } else
            ungetCh = ch;
        return val;
    }
    switch (ch) {
    case 'n':
        return '\n';
    case 'b':
        return '\b';
    case 'r':
        return '\r';
    case 't':
        return '\t';
    case 'f':
        return '\f';
    case 'a':
        return '\a';
    case 'v':
        return '\v';
    case 'x':
        val = 0;
        cnt = 3;
        do {
            ch = getCh();
            if (!Isxdigit(ch)) {
                ungetCh = ch;
                return val;
            }
            val *= 16;
            if (Isupper(ch))
                ch |= 0x20;
            if (Islower(ch))
                val += ch - ('a' + 10);
            else
                val += ch - '0';
        } while (cnt--);
        return val;
    }
    return ch;
}

/**************************************************
 * 67: 35F7 PMO
 **************************************************/
int16_t peekCh() {
    int16_t ch;
    ungetCh = ch = skipWs();
    return ch;
}

/**************************************************
 * 68: 3610 PMO
 **************************************************/
void skipStmt(uint8_t tok) {

    while (tok > T_RBRACE)
        tok = yylex();
    if (tok == T_EOF)
        fatalErr("unexpected EOF");
    ungetTok = tok;
}

/**************************************************
 * 69: 363F PMO
 **************************************************/
void expect(uint8_t etok, char *msg) {
    uint8_t tok;

    if ((tok = yylex()) == etok)
        return;
    expectErr(msg);
    skipStmt(tok);
}

/**************************************************
 * 70: 3666 PMO
 **************************************************/
void skipToSemi() {
    uint8_t tok;

    do {
        tok = yylex();
    } while (tok != T_SEMI);
    ungetTok = T_SEMI;
}
