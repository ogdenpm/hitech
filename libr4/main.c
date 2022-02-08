#include "libr.h"

int width            = 80;      /* Output width */
char commands[]      = "rdxms"; /* Program Keys */
char usageMsg[]      = "Usage: libr [-w][-pwidth] key [subkeys symbol] file.lib [modules ...]";
char keysMsg[]       = "Keys: r(eplace), d(elete), (e)x(tract), m(odules), s(ymbols)";

void (*dispatch[])() = {
    replaceModule,  /* Replace modules */
    deleteModule,   /* Delete modules */
    extractModules, /* Extract modules */
    listModules,    /* List modules */
    listWithSymbols /* List modules with symbols */
};

int cmdIndex;
int err_num;
bool noWarnings;
int num_ofiles; /* number of object files */
char **cmdLineNames;

uint8_t *moduleFlags; /* Pointer to an area of modsize num_ofiles */
int *moduleSizes;     /* Pointer to an area of modsize num_ofiles * sizeof(int) */

int main(int argc, char *argv[]) {
    char *pCmd;
    char *s;

    if (signal(SIGINT, SIG_IGN) != SIG_IGN)
        signal(SIGINT, sigintHandler);
#if CPM
    if (argc == 1) {
        argv = _getargs(0, "libr");
        argc = _argc_;
    }
#endif

    fclose(stdin);

    for (--argc, ++argv; argc && **argv == '-'; --argc, ++argv) {
        pCmd = *argv + 1;
        while (*pCmd)
            switch (*pCmd++) {
            case 'W': /* Suppress non-fatal errors */
            case 'w':
                noWarnings = true; /* Disable warning messages */
                break;
            case 'P': /* Specify page width */
            case 'p':
                if (isdigit(*pCmd)) {
                    width = atoi(pCmd); /* Assigning a new width value */
                    pCmd  = "";
                    break;
                }
            default:
                fatal_err(usageMsg);
                break;
            }
    }

    if (argc < 2)
        fatal_err(usageMsg);
    s = *argv;
    --argc;
    ++argv;
    if ((pCmd = strchr(commands, tolower(*s))) == NULL)
        fatal_err(keysMsg);

    cmdIndex = (int)(pCmd - commands);

    if (*(s + 1) != 0) {
        pCmd = *argv;
        --argc;
        ++argv;
    }
    if (argc == 0)
        fatal_err(usageMsg);

    openLibrary(*argv);
    allocModuleArrays(argc - 1, argv + 1);

    (dispatch[cmdIndex])(s + 1, pCmd); /* Execute function */

    finish(err_num != 0); /* Terminate the program with the appropriate error code */
}

/**************************************************************************
 generic error message functions
 **************************************************************************/
_Noreturn void fatal_err(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
    va_end(args);
    finish(6);
}

void badFormat(char *name, char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "bad file format: %s\n", name);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);
    finish(6);
}

void warning(char *fmt, ...) {
    va_list args;

    if (noWarnings)
        return;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, " (warning)\n");
}

void simpl_err(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, " (warning)\n");
    va_end(args);

    fputc('\n', stderr);
    ++err_num;
}

/**************************************************************************
 specialist error routines
 **************************************************************************/
_Noreturn void open_err(char *p1) {

    fprintf(stderr, "Can't open %s\n", p1);
    finish(2);
}

_Noreturn void seek_err(char *p1) {

    fprintf(stderr, "Seek error on %s\n", p1);
    finish(3);
}

void noModule(char *name, int dummy) {

    simpl_err("no such module: %s", name);
}

/**************************************************************************
 clean up routines
 **************************************************************************/
_Noreturn void finish(int p1) {

    closeTemp();
    exit(p1);
}

void sigintHandler(int p1) {

    finish(4);
}

/**************************************************************************
 utility routines
 **************************************************************************/
int cmpNames(register char *s, char *t) {

    while (*s && tolower(*s) == tolower(*t))
        ++s, ++t;
    return *s - *t;
}

void allocModuleArrays(int p1, char **p2) {

    cmdLineNames = p2;
    if ((num_ofiles = p1) != 0) {
        moduleFlags = allocmem(num_ofiles);
        moduleSizes = (int *)allocmem(num_ofiles * sizeof(int));
    }
}

uint8_t lookupName(char *p1) {
    uint8_t l1;

    if (num_ofiles == 0)
        return 1;
    l1 = num_ofiles;
    do {
        if (l1-- == 0)
            return 0;
    } while (cmpNames(cmdLineNames[l1], p1) != 0);

    moduleFlags[l1] = 1;
    return l1 + 1;
}

void processUnmatched(pfuncptr action) {
    int i;
    for (i = 0; i != num_ofiles; i++) {
        if (moduleFlags[i] == 0)
            action(cmdLineNames[i], i);
    }
}

void copyUnchangedSymbols(char *name, time_t libTime) {

    if (!lookupName(name))
        copySymbolsToTemp();
}

void copyUnchangedModules(char *name, time_t libTime) {

    if (!lookupName(name))
        copyModuleToTemp();
}
