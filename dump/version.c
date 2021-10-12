// generate version strings
#include "Generated/version.h"

// determine the target bit width
#if defined _M_X64 || (defined __x86_64 && !defined __IPL32__)
#define BUILDTARGET   "64"
#else
#define BUILDTARGET   "32"
#endif

// and whether it is a debug build
#ifdef _DEBUG
#define DEBUGSUFFIX   " debug"
#else
#define DEBUGSUFFIX
#endif

// convert the GIT_BUILDTYPE into a string
#if GIT_BUILDTYPE == 2
#define DIRTY   " +uncommitted files"
#elif GIT_BUILDTYPE == 3
#define DIRTY   " -untracked files"
#else
#define DIRTY
#endif

// the generate the normal version string
// there are two flavours depending on whether the code is a port
// if it is define PORTVER, typically this would be of the form
// "x.y (C) company"
// e.g. "2.2 (C) Whitesmiths"
#ifdef PORTVER
static const char *git_ver = GIT_APPNAME " [ " PORTVER " ] - {" BUILDTARGET "bit" DEBUGSUFFIX "} " GIT_VERSION " port (C)" GIT_YEAR " Mark Ogden";
#else
static const char *git_ver = GIT_APPNAME " - {" BUILDTARGET "bit" DEBUGSUFFIX "} " GIT_VERSION " (C)" GIT_YEAR " Mark Ogden";
#endif

const char *git_detail = GIT_APPNAME " " GIT_VERSION "  " GIT_SHA1 "  [" GIT_CTIME "]" DIRTY;


// show version information

#include <stdio.h>
#include <stdbool.h>

// optional library includes

const char **git_details[] = {
    &git_detail,
    // insert library details below and before NULL
    NULL
};

// use the following function declaration in the main code
// void showVersion(FILE *fp, bool full);

void showVersion(FILE *fp, bool full) {
    fputs(git_ver, fp);
    fputc('\n', fp);
    if (full) {
        fputs("Git Info:\n", fp);
        for (const char ***s = git_details; *s; s++) {
            fputs(**s, fp);
            fputc('\n', fp);
        }
    }
}

