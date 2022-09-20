#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#endif
#include <ctype.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
#include <process.h> /* for getpid */
#include <io.h>
#else
#include <limits.h> /* picks up PATH_MAX in GCC */
#include <unistd.h> /* for getpid */
#endif

#ifndef PATH_MAX
#ifdef PATH_MAX
#define PATH_MAX PATH_MAX
#else
#define PATH_MAX 260
#endif
#endif

#ifdef _WIN32
#define PATHSEP "/\\:"
#define DIRSEP  "\\"
#else
#define PATHSEP "/"
#define DIRSEP  "/"
#endif

#define DEPSDIR ".deps"



/* zc.c */
int main ( int argc , char **argv );
void setPaths ( void );
void setTarget ( void );
void addCppFlag ( char *s );
void addLinkFlag ( char *s , bool errOnDup );
int unx_exec ( char *name , char **vec );
_Noreturn void error(char *s, ...);
char *xstrdup(char *s);
_Noreturn void usage();
    /* os.c */
bool canExecute ( char *name );
char *fname ( char *name );
void mkDepsDir ( void );
char *newStr ( char *prefix , char *path , char *suffix );
/* getargs.c */
char **_getargs(char *_str, char *_name);