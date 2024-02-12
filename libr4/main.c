#include "libr.h"
#include "showVersion.h"

int width            = 80;      /* Output width */
char commands[]      = "rdxms"; /* Program Keys */
char usageMsg[]      = "Usage: libr [-w][-pwidth][-v] key [subkeys symbol] file.lib [modules ...]";
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
char **moduleStdNames;
bool verbose;

uint8_t *moduleFlags; /* Pointer to an area of modsize num_ofiles */
#define SEEN        1
#define PROCESSED   2
uint32_t *moduleSizes;     /* Pointer to an area of modsize num_ofiles * sizeof(uint32_t) */

int main(int argc, char *argv[]) {
    char *p;
    char *s;

    CHK_SHOW_VERSION(argc, argv);

    if (signal(SIGINT, SIG_IGN) != SIG_IGN)
        signal(SIGINT, sigintHandler);

    if (argc == 1) {
        argv = _getargs(0, "libr");
        argc = _argc_;
    }

    fclose(stdin);

    for (--argc, ++argv; argc && **argv == '-'; --argc, ++argv) {
        p = *argv + 1;
        while (*p)
            switch (*p++) {
            case 'v':
            case 'V':
                verbose = true;
                break;
            case 'W': /* Suppress non-fatal errors */
            case 'w':
                noWarnings = true; /* Disable warning messages */
                break;
            case 'P': /* Specify page width */
            case 'p':
                if (isdigit(*p)) {
                    width = atoi(p); /* Assigning a new width value */
                    p     = "";
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
    if ((p = strchr(commands, tolower(*s))) == NULL)
        fatal_err(keysMsg);

    cmdIndex = (int)(p - commands);

    if (s[1]) {
        p = *argv;
        --argc;
        ++argv;
    }
    if (argc == 0)
        fatal_err(usageMsg);

    openLibrary(*argv);
    allocModuleArrays(argc - 1, argv + 1);

    (dispatch[cmdIndex])(s + 1, p); /* Execute function */

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

void noModule(int id) {

    simpl_err("no such module: %s", moduleStdNames[id]);
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

void allocModuleArrays(int cnt, char **pnames) {

    cmdLineNames = pnames;
    if ((num_ofiles = cnt) != 0) {
        moduleFlags    = xalloc(num_ofiles * sizeof(uint8_t));
        moduleSizes    = xalloc(num_ofiles * sizeof(uint32_t));
        moduleStdNames = xalloc(num_ofiles * sizeof(char *));
        while (cnt-- >= 0) {
            char *s;
            moduleStdNames[cnt] = fname(cmdLineNames[cnt]);
            for (s = moduleStdNames[cnt]; *s; s++)
                *s = tolower(*s);
        }
    }
}

uint8_t lookupName(char *moduleName) {
    int i;

    if (num_ofiles == 0)
        return 1;
    for (i = 0; i < num_ofiles; i++) {
        if (strcasecmp(moduleStdNames[i], moduleName) == 0) {
            moduleFlags[i] |= SEEN;
            return i + 1;
        }
    }
    return 0;
}

void processUnmatched(pfuncptr action) {
    int i;
    for (i = 0; i != num_ofiles; i++) {
        if (moduleFlags[i] == 0)
            action(i);
    }
}

void copyUnchangedSymbols(char *name, time_t libTime) {
    if (lookupName(name) == 0)
        copySymbolsToTemp();
    else if (verbose)
        printf("d %s\n", name);
}

void copyUnchangedModules(char *name, time_t libTime) {
    
    if (lookupName(name) == 0)
        copyModuleToTemp();
}
