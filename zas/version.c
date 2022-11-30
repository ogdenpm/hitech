// generate version strings
#ifdef AUTOVER // defined if we are using version.cmd script with Git
#include "Generated/version.h"
#else
#include "version.in"
#endif
// determine the target bit width
#if INTPTR_MAX == INT64_MAX
#define ARCHSIZE "64bit"
#elif INTPTR_MAX == INT32_MAX
#define ARCHSIZE "32bit"
#else
#define ARCHSIZE "??bit"
#endif

// and whether it is a debug build
#ifdef _DEBUG
#define BUILD "{" ARCHSIZE " debug}"
#else
#define BUILD "{" ARCHSIZE "}"
#endif

// convert the GIT_BUILDTYPE into a string
#if GIT_BUILDTYPE == 1
#define DIRTY "+"
#else
#define DIRTY
#endif

// the generate the normal version string
// there are two flavours depending on whether the code is a port
// if it is add a #define GIT_PORT "string" in version.in
// string would typically be of the form
// "x.y (C) company"
// e.g. "2.2 (C) Whitesmiths"
#ifdef GIT_PORT
static const char *git_ver = GIT_APPNAME
    " " GIT_PORT " - port " GIT_VERSION " " BUILD " (C)" GIT_YEAR " Mark Ogden";
#else
static const char *git_ver =
    GIT_APPNAME " - " GIT_VERSION " " BUILD " (C)" GIT_YEAR " Mark Ogden";
#endif

typedef struct {
    const char *name;
    const char *version;
    const char *sha1;
    const char *time;
} git_detail_t;

git_detail_t git_detail = { GIT_APPNAME, GIT_VERSION, GIT_SHA1 DIRTY,
                            GIT_CTIME };

// show version information

#include <stdbool.h>
#include <stdio.h>

// optional library includes
extern const git_detail_t wslib_detail;

// clang-format off
const git_detail_t *git_details[] = {
    &git_detail,
    // insert library details here before NULL
    0
};
// clang-format on

// use the following function declaration in the main code
// void showVersion(FILE *fp, bool full);

void showVersion(FILE *fp, bool full) {
    fputs(git_ver, fp);
    fputc('\n', fp);
    if (full) {
        char *label = "Program:";
        // now print out the version information
        for (const git_detail_t **s = git_details; *s; s++) {
            fprintf(fp, "%s %-8s %-8s %-8s [%s]\n", label, (*s)->name, (*s)->version,
                    (*s)->sha1, (*s)->time);
            label = "Library:";
        }
    }
}
