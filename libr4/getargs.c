/*
 *	_getargs(str, name) - process string into argument buffer.
 *
 *	If str is null, read lines from standard input instead, using name as a
 *	prompt.
 *	Continuation lines are recognized by a \ as the last character on the
 *	line.
 *
 *
 *	Wildcards (? and *) are expanded in the usual way.
 *  Note wildcards in the directory path are NOT supported
 *
 *	The quotes " and ' may be used to enclose arguments which contain
 *	white space.
 *
 *	The argument buffer is malloced and a pointer to it is returned.
 *	The count of arguments is left in the global _argc_. The count
 *	may also be found by counting the arguments; the last one is a null
 *	pointer.
 *	The zero'th argument is set to the name parameter.
 */

#include "dirent.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
#include <conio.h>
#else
#include <unistd.h>

#endif
#ifndef _MAX_PATH
#ifdef PATH_MAX
#define _MAX_PATH PATH_MAX
#else
#define _MAX_PATH 255
#endif
#endif


#define mapcase(c) tolower(c)

char *fname(char *name);



#define MAXARGS         512       /* max number of arguments */
#define MAXLEN          _MAX_PATH /* max length of an argument */
#define QUOTE           -128      /* quoted bit in args */
#define CHUNK           256       /* line input buffer auto expansion value */
#define isterminator(c) ((c) == 0)
#define look()          (*str)

int _argc_;

static char *name, *str, *bp;

static size_t bpSize;
static char interactive;
_Noreturn static void error(char *, ...);
static void *alloc();
static char nxtch();
static bool iswild(char c);
static bool isseparator(char c);

bool match(char *regexp, char *text);
bool matchstar(char *regexp, char *text);

char **_getargs(char *_str, char *_name) {
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
    str   = _str;
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
    argbuf[0] = name;
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
            char pattern[_MAX_PATH];
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

_Noreturn static void error(char *s, ...) {
    va_list args;
    va_start(args, s);
    while (s)
        fputs(s, stderr);
    fputc('\n', stderr);
    exit(-1);
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

    if ((*text != '\0' && mapcase(*regexp) == mapcase(*text)) || *regexp == '?')
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