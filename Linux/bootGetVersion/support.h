#pragma once
#include <stdbool.h>
#include <stdio.h>
#ifndef _MSC_VER
#define stricmp strcasecmp
#endif

// support.c
extern bool debug;
_Noreturn void fatal(char const *fmt, ...);
void warn(char const *fmt, ...);
void debugPrint(char const *fmt, ...);

_Noreturn void usage(char *fmt, ...);

char const *basename(char const *path);

void *safeMalloc(size_t size);
void *safeRealloc(void *old, size_t size);
char *safeStrdup(char const *str);


typedef struct {
    int pos;
    int capacity;
    int chunk;
    char *str;
} string_t;

void initString(string_t *str, int chunk);
void appendString(string_t *str, char *s);
void appendBuffer(string_t *str, char *buf, int len);


// option.c
/*
    Help contains the usage syntax and the option descriptions.
    When shown  it is preceded by the simple version information and app desciption
    And followed by a note about the standard -v, -V and -h options.
    The string can contain one %s which is replaced by the program name used to
    run the application
*/
extern char const help[];  // user supplied
extern char *optarg; // optional argument (or error message)
extern int optind;         // current index into argv
extern int optopt;         // option scanned

int getopt(int argc, char * const *argv, const char *options);
void chkStdOptions(int argc, char * const *argv);
void showVersion(FILE *fp, int what);

// execute.c
int execute(char const *const *cmd, string_t *dst, bool isInteractive);

// template.c
char *parseConfig(char const *cfgFileName);
bool writeNewVersion(char const *versionFile, char const *version, char const *date);
