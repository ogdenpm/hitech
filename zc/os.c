
#include "zc.h"
#include <sys/stat.h>

#ifdef _MSC_VER
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#endif

#ifndef S_IFREG
#define S_IFREG _S_IFREG
#define S_IEXEC _S_IEXEC
#define S_IFDIR _S_IFDIR
#endif

bool canExecute(char *name) {
    struct stat buf;
    return stat(name, &buf) == 0 && (buf.st_mode & (S_IFREG | S_IEXEC)) == (S_IFREG | S_IEXEC);
}


char *fname(char *name) {
    char *t;
    while ((t = strpbrk(name, PATHSEP)))
        name = t + 1;
    return name;
}

void mkDepsDir() {
    struct stat buf;
    if (mkdir(DEPSDIR, 0777) != 0 && (stat(DEPSDIR, &buf) != 0 || (buf.st_mode & S_IFDIR) == 0))
        error("Cannot create " DEPSDIR);
}

/* create a new string by contatenating prefix, path and suffix if the are not NULL
   special handling of suffix if is not NULL, it replaces any dot extent
   that is part of path
 */
char *newStr(char *prefix, char *path, char *suffix) {
    char tmp[PATH_MAX + 2];
    char *s;
    strcpy(tmp, prefix ? prefix: "");
    if (path)
        strcat(tmp, path);
    if (suffix) {
        if ((s = strrchr(fname(tmp), '.')))
            *s = '\0';
        strcat(tmp, suffix);
    }
    
    return xstrdup(tmp);
}
