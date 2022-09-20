#ifndef CPM
#include <stdlib.h>
#include <string.h>

#ifndef _MAX_PATH
#ifdef _POSIX_PATH_MAX
#define MAX_PATH    _POSIX_PATH_MAX
#else
#define _MAX_PATH   260
#endif
#endif

static char libdir[_MAX_PATH];
static char *fpath;

#ifdef _WIN32
#define DIRSEP   "\\/:"
#define DIRSEPCH "\\"
#else
#define DIRSEP   "/"
#define DIRSEPCH "/"
#endif

#define LIB80 "lib80" DIRSEPCH


static char *fname(char *s) {   /* get to the file name */
    char *t;
    while ((t = strpbrk(s, DIRSEP)))
        s = t + 1;
    return s;
}

static void initLibdir() {
    char *env = getenv("LIBDIR80");
    char *s;
    if (env) {
        strcpy(libdir, env);
        s = fname(libdir);
        if (*s)
            strcat(s, DIRSEPCH);
    } else if ((env = getenv("HITECH"))) {
        strcpy(libdir, env);
        s = fname(libdir);
        if (*s)
            strcat(s, DIRSEPCH);
        strcat(s, LIB80);
    } else
        strcpy(libdir, "." DIRSEPCH);
    fpath = strchr(libdir, '\0'); // append point for filenames
}


char const *mkLibPath(char const *s) {
    if (strpbrk(s, DIRSEP)) // only apply lib to simple files
        return s;
    if (!fpath)
        initLibdir();
    strcpy(fpath, s);
    return libdir;
}
#endif