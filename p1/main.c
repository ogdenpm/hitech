/*
 *
 * The main.c file is part of the restored P1.COM program
 * from the Hi-Tech CP/M Z80 C v3.09
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH Z80 C compiler V3.09
 * (HI-TECH Software) and extend its life, outside of the CP/M environment
 * for full operation in windows 32/64 and Unix-like operating systems
 *
 * The HI-TECH Z80 C cross compiler V3.09 is provided free of charge for any use,
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
 *
 * See the readme.md file for additional commentary
 *
 * Mark Ogden
 * 09-Jul-2022
 */
#include "p1.h"

char *tmpFile = "p1.tmp"; /* 91db */
char errBuf[512];         /* 9df7 */
FILE *crfFp;              /* 9ff7 */
char crfNameBuf[30];      /* 9ff9 */
char srcFile[100];        /* a017 */
char *crfFile;            /* a07b */
bool s_opt;               /* a07d */
bool w_opt;               /* a07e */
int16_t lineNo;           /* a07f */
char *srcFileArg;         /* a081 */
bool l_opt;               /* a083 */
FILE *tmpFp;              /* a084 */
char inBuf[512];          /* a086 */
int16_t errCnt;           /* a286 */

int main(int argc, char *argv[]);
#ifdef CPM
void prMsg(char *p1, int p2, int p3);
#else
void prMsg(char *fmt, va_list args);

#endif
void copyTmp(void);
void closeFiles(void);
void mainParseLoop(void);

/**************************************************
 * 71: 367E PMO +++
 * basic blocks located differently
 * strcpy 2nd arg optimisation missed
 **************************************************/
int main(int argc, char *argv[]) {
    register char *st;

    initMemAddr(); /* get data area range */

    for (--argc, ++argv; argc && *argv[0] == '-'; --argc, argv++) {
        switch (argv[0][1]) {
        case 'E':
        case 'e':
            freopen(*argv + 2, "a", stderr);
            setbuf(stderr, errBuf);
            break;
        case 'S':
        case 's':
            s_opt = true;
            break;
        case 'W':
        case 'w':
            w_opt = true;
            break;
        case 'L':
        case 'l':
            l_opt = true;
            break;
        case 'C':
        case 'c':
            if (argv[0][2])
                crfFile = argv[0] + 2;
            else
                crfFile = crfNameBuf;
            break;
        }
    }
    sub_4d92();
    resetExprStack();
    if (argc) {
        if (freopen(argv[0], "r", stdin) == 0)
            fatalErr("can't open %s", *argv);
        srcFileArg = argv[0];
        strcpy(srcFile, srcFileArg);
        if (argc != 1 && freopen(argv[1], "w", stdout) == NULL)
            fatalErr("can't open %s", argv[1]);
        if (argc == 3)
            tmpFile = argv[2];
    } else
        strcpy(srcFile, srcFileArg = "(stdin)");

    if (crfFile) {
        if (*crfFile == '\0') {
            crfFile = crfNameBuf;
            strcpy(crfNameBuf, srcFile);
            if ((st = rindex(crfNameBuf, '.')))
                strcpy(st, ".crf");
            else
                strcat(crfNameBuf, ".crf");
        }
        if (!(crfFp = fopen(crfFile, "a")))
            prWarning("Can't create xref file %s", crfFile);
        else
            fprintf(crfFp, "~%s\n", srcFile);
    }
    if (!(tmpFp = fopen(tmpFile, "w")))
        fatalErr("can't open %s", tmpFile);

    eOne.tType    = T_ICONST;
    eZero.tType         = T_ICONST;
    eZero.attr.dataType = eOne.attr.dataType = DT_INT;
    eZero.t_l      = 0;
    eOne.t_l      = 1;

    mainParseLoop();
    copyTmp();

    if (fclose(stdout) == -1)
        prError("close error (disk space?)");
    closeFiles();
    exit(errCnt != 0);
}

#ifdef CPM
/**************************************************
 * 72: 3936 PMO +++
 **************************************************/
void prMsg(p1, p2, p3) char *p1;
{
    char buf[128];

    sprintf(buf, p1, p2, p3);
    prMsgAt(buf);
}

/**************************************************
 * 73: 396C PMO +++
 **************************************************/
void prError(p1, p2, p3) char *p1;
{

    ++errCnt;
    prMsg(p1, p2, p3);
    fputc('\n', stderr);
}

/**************************************************
 * 74: 399E PMO +++
 **************************************************/
void fatalErr(p1, p2) char *p1;
char *p2;
{

    prError(p1, p2);
    closeFiles();
    exit(1);
}

/**************************************************
 * 75: 39C1 PMO +++
 **************************************************/
void prWarning(p1, p2, p3) char *p1;
{
    if (w_opt)
        return;
    prMsg(p1, p2, p3);
    fprintf(stderr, " (warning)\n");
}

#else
/**************************************************
 * 72: 3936 PMO
 **************************************************/
void prMsg(char *fmt, va_list args) {
    char buf[128];

    vsprintf(buf, fmt, args);
    prMsgAt(buf);
}

/**************************************************
 * 73: 396C PMO
 **************************************************/
void prError(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ++errCnt;
    prMsg(fmt, args);
    va_end(args);
    fputc('\n', stderr);
}

/**************************************************
 * 74: 399E PMO
 **************************************************/
void fatalErr(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ++errCnt;
    prMsg(fmt, args);
    va_end(args);
    fputc('\n', stderr);
    closeFiles();
    exit(1);
}

/**************************************************
 * 75: 39C1 PMO
 **************************************************/
void prWarning(char *fmt, ...) {
    if (w_opt)
        return;
    va_list args;
    va_start(args, fmt);
    prMsg(fmt, args);
    va_end(args);
    fprintf(stderr, " (warning)\n");
}



#endif

/**************************************************
 * 76: 39F3 PMO +++
 **************************************************/
void expectErr(char *p) {

    prError("%s expected", p);
}

/**************************************************
 * 77: 3A07 PMO +++
 **************************************************/
void copyTmp(void) {
    int ch;

    fclose(tmpFp);

    if ((tmpFp = fopen(tmpFile, "r")) == NULL)
        fatalErr("Can't reopen %s", tmpFile);

    while ((ch = fgetc(tmpFp)) != EOF)
        fputc(ch, stdout);
}

/**************************************************
 * 78: 3A5E PMO +++
 **************************************************/
void closeFiles(void) {

    fclose(stdin);
    fclose(stdout);
    if (tmpFp) {
        fclose(tmpFp);
        unlink(tmpFile);
    }
    if (crfFp) /* PMO - close missing in original */
        fclose(crfFp);
}
/**************************************************
 * 79: 3A80 PMO +++
 **************************************************/
void *xalloc(size_t size) {
    register char *ptr;

    do {
        if ((ptr = malloc(size)) != NULL)
            goto done;
    } while (releaseSymFreeList() || releaseExprList());
    fatalErr("Out of memory");
done:
    blkclr(ptr, size);
    return ptr;
}

/**************************************************
 * 80: 3ABF PMO +++
 **************************************************/
void mainParseLoop(void) {
    uint8_t tok;

    while ((tok = yylex()) != T_EOF) {
        ungetTok = tok;
        sub_3adf();
    }
    releaseScopeSym();
}
