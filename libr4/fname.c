#ifdef _WIN32
#define DIRSEP "/\\:"
#else
#define DIRSEP "/"
#endif

#include <string.h>

#ifdef CPM
char *fname(char *name) {
    char *s;
    return (s = strchr(name, ':')) ? s + 1 : name;
}
#else
char *fname(char *name) {
    char *t;
    while (t = strpbrk(name, DIRSEP))
        name = t + 1;
    return name;
}
#endif