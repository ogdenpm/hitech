/*
 *
 * The getargs.c file is part of the restored P1.COM program
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
 * 21-Aug-2022
 *
 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#endif

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _MSC_VER
#include "missing/dirent.h"
#include <conio.h>
#else
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#endif

#ifndef PATH_MAX
#ifdef _MAX_PATH
#define PATH_MAX _MAX_PATH
#else
#define PATH_MAX 255
#endif
#endif


#define mapcase(c) tolower(c)

char *fname(char *name);



#define MAXARGS         512       /* max number of arguments */
#define MAXLEN          PATH_MAX /* max length of an argument */
#define QUOTE           -128      /* quoted bit in args */
#define CHUNK           256       /* line input buffer auto expansion value */
#define isterminator(c) ((c) == 0)
#define look()          (*str)

int _argc_;

static const char *name;
static char *str, *bp;

static size_t bpSize;
static char interactive;
static _Noreturn void error(char *s, ...);
static void *alloc();
static char nxtch();
static bool iswild(char c);
static bool isseparator(char c);
bool matchstar(char *regexp, char *text);

bool match(char *regexp, char *text);
bool matchstar(char *regexp, char *text);

char **_getargs(char *_str, const char *_name) {
    char **argv;
    char *ap;
    char *cp;
    short argc;
    char c, quote;
    char *argbuf[MAXARGS + 1];
    char buf[MAXLEN];
    bool hasWild;

    bp    = NULL;
    quote = 0;
    name  = _name;
    str   = (char *) _str;
    if ((interactive = str == NULL))
        str = "\\";
    else {
        while (*str == ' ' || *str == '\t')
            str++;
        cp = str + strlen(str);
        while (--cp >= str && isseparator(*cp))
            ;
        cp[1] = '\0';
    }
    argbuf[0] = (char *)name;
    argc      = 1;

    /* first step - process arguments and do globbing */

    while (look()) {
        if (argc == MAXARGS)
            error("too many arguments", 0);
        while (isseparator(c = nxtch()))
            continue;
        if (c == '\0')
            break;
        ap = buf;

        if (c == '\'' || c == '"')
            quote = c;
        else
            *ap++ = c;

        hasWild = iswild(c);

        while ((c = nxtch()) && (quote || !isseparator(c))) {
            if (ap == &buf[MAXLEN])
                error("argument too long", 0);
            if (c == quote)
                quote = 0;
            else if (!quote && (c == '\'' || c == '"'))
                quote = c;
            else {
                if (!quote && iswild(c))
                    hasWild = true;
                *ap++ = c;
            }
        }

        *ap = 0;
        if (hasWild) {
            char pattern[PATH_MAX];
            ap = fname(buf);
            strcpy(pattern, ap);
            *ap      = 0;

            DIR *dir = opendir(*buf ? buf : ".");
            if (dir) {
                struct dirent *entry;
                while ((entry = readdir(dir))) {
                    if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
                        if (match(pattern, entry->d_name)) {
                            argbuf[argc] = alloc(ap - buf + strlen(entry->d_name) + 1);
                            strcpy(argbuf[argc], buf);
                            strcat(argbuf[argc++], entry->d_name);
                        }
                    }
                }
                closedir(dir);

            } else
                error(buf, pattern, ": no match", 0);

        } else {
            strcpy(argbuf[argc++] = alloc(ap - buf + 1), buf);
        }
    }

    _argc_         = argc;
    argbuf[argc++] = NULL;
    argv           = alloc(argc * sizeof *argv);
    memcpy(argv, argbuf, argc * sizeof *argv);

    return argv;
}

/* modified to allow arbitary line length */
static char nxtch() {
    if (interactive && *str == '\\' && str[1] == 0) {
        if (isatty(fileno(stdin)))
            fprintf(stderr, "%s> ", name);
        size_t cnt = 0;
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (cnt + 1 >= bpSize && (bp = realloc(bp, bpSize += CHUNK)) == NULL)
                error("no room for arguments", 0);
            bp[cnt++] = c;
        }
        if (bp) {
            bp[cnt] = 0;
            str     = bp;
        } else
            str = "";
    }
    if (*str)
        return *str++;

    return 0;
}


static void *alloc(size_t n) {
    void *bp;

    if ((bp = malloc(n)) == NULL)
        error("no room for arguments", 0);
    return bp;
}

/* check for wild card in file name
   wildcard in path is not supported
*/
static bool iswild(char c) {
    return c == '*' || c == '?';
}

static bool isseparator(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

/* match: search for glob match */
bool match(char *regexp, char *text) {
    if (*regexp == '\0')
        return *text == '\0';
    if (*regexp == '*')
        return matchstar(regexp + 1, text);

    if (*text != '\0' && (mapcase(*regexp) == mapcase(*text) || *regexp == '?'))
        return match(regexp + 1, text + 1);
    return false;
}

/* matchstar: */
bool matchstar(char *regexp, char *text) {
    do { /* a * matches zero or more instances */
        if (match(regexp, text))
            return true;
    } while (*text++ != '\0');
    return false;
}

static _Noreturn void error(char *s, ...) {
    va_list args;
    va_start(args, s);
    while (s) {
        fputs(s, stderr);
        s = va_arg(args, char *);
    }
    putc('\n', stderr);
    va_end(args);
    exit(1);
}
