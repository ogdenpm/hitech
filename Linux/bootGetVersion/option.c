#include "verInfo.h"
#include "support.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifdef linux
#include <limits.h>
#endif
/*
 * modified version of the public domain AT&T getopt
 * in addition to : being used to indicate a required argument to the option
 * = is supported to allow an optional argument to the option for example if opts contains
 * "i=" then -i and -i=10 and -i =10 are supported
 * returns EOF on end of processing, else the option or option|OPTNOARG if missing argument
 * Note invalid options are assumed to have no argument
 * sets the globals
 *   optopt    -> the option
 *   optarg    -> the argument or NULL
 *   optind    -> argv index to process next
 */

int optind = 1;
int optopt;
char *optarg;

static char *programName = "???";

/// <summary>
/// Process standard options, currently -v, -V and -h
/// also captures argv[0] as programName 
/// Options must be the only ones present
/// </summary>
/// <param name="s">The s.</param>
void chkStdOptions(int argc, char * const *argv) {
    programName = argv[0];
    if (argc == 2) {
        if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "-V") == 0) {
            showVersion(stdout, argv[1][1] == 'V');
            exit(0);
        } else if (strcmp(argv[1], "-h") == 0)
            usage(NULL);
    }
}

/// <summary>
/// simple option processing
/// Any argv argument starting -- is treated as end of processing, as such long options are not
/// supported It extends AT&T getopt by supporting optional =value arguments When arguments are
/// needed then it consumes the rest of the current argv argument being processed if not at end of
/// string or the next argv argument
/// </summary>
/// <param name="argc">The number of arguments in argv</param>
/// <param name="argv">The array of arguments</param>
/// <param name="opts">A string containing the characters of supported options.
/// If the character is followed by a ':' then it requires an argument
/// If the character is followed by a '=' then it accepts an optional argument</param>
/// <returns>
/// The option or EOF on end of options. If a required argument is missing the OPTNOARG is added to
/// the return value. In addition the following globals are updated optopt contains the option
/// selected, optarg is the argument or NULL optind is index of the next argv argument to process
/// </returns>
int getopt(int argc, char * const *argv, char const *opts) {
    static char *place = ""; // force new arg
    char *cp                 = NULL;

    if (!*place) {
        if (optind == 1)
            chkStdOptions(argc, argv);
        if (optind >= argc || *(place = argv[optind]) != '-' || place[1] == '\0')
            return (EOF);
        else if (*++place == '-') { // -- finishes
            optind++;
            return (EOF);
        }
    }

    if ((optopt = *place++) != ':' && (cp = strchr(opts, optopt)) && (*++cp == ':' || *cp == '=')) {
        if (*place)
            optarg = place;
        else {
            if (++optind >= argc) {
                if (*cp != '=')
                    usage("Missing argument to -%c option", optopt);
                else
                    optarg = "";
            } else
                optarg = argv[optind];
        }
        if (*cp == '=' && *optarg++ != '=')
            optarg = NULL; // backup and leave for next option
        else {
            optind++;
            place = "";
        }
    } else if (cp == NULL)
        usage("Invalid option -%c", optopt);
    else {
        optarg = NULL;
        if (!*place)
            optind++;
    }
    return optopt;
}

/// <summary>
/// Display the application help
/// if the optional fmt, ... is present the formatted
/// string is written to stderr, preceeded by "Error: ", followed by the help and the program exits
/// with 1
/// if fmt is NULL then help is printed to stdout and program exits with 0
/// </summary>
/// <param name="fmt">optional format</param>
/// <param name="">and arguments</param>
_Noreturn void usage(char *fmt, ...) {
    FILE *fp = fmt ? stderr : stdout;
    if (fmt) {
        va_list args;
        va_start(args, fmt);
        fputs("Error: ", fp);
        vfprintf(fp, fmt, args);
        fputs("\n\n", fp);
        va_end(args);
    }
    showVersion(fp, 2);
    putc('\n', fp);
#ifdef _WIN32
    char *s = strrchr(programName, '.');
    if (s && stricmp(s, ".exe") == 0)
        *s = '\0';
#endif
    fprintf(fp, help, basename(programName));
    fputs("\nAlso supports single arguments -v, -V for version info and -h for help\n", fp);
    exit(fmt ? 1 : 0);
}




#ifdef _DEBUG
#define BUILD "Debug "
#else
#define BUILD
#endif
/// <summary>
/// Shows the version information combining the static information from appinfo.h
/// and the generated version information derived from git in _version.h
/// Usually called from chkStdOptions which can be
/// invoked directly or indirectly via getopt
/// </summary>
/// <param name="fp">File stream to write to</param>
/// <param name="what">if 0 (false) show simple version info
/// else if 1 (true) show extended version info
/// else show simple version and description</param>
void showVersion(FILE *fp, int what) {
    fprintf(fp, "%s (C) %s", appInfo.product, appInfo.owner);
    if (appInfo.mods)
        fprintf(fp, " <%s>", appInfo.mods);
    fprintf(fp, " %s\n", appInfo.version);
    if (what != false) {
        if (appInfo.description)
            fprintf(fp, "%s\n", appInfo.description);
        if (what == true) {
            if (appInfo.contributors)
                fprintf(fp, "Contributors: %s\n", appInfo.contributors);
            fprintf(fp, BUILD "%d bit build: ", (int)(sizeof(void *) * CHAR_BIT));
#ifdef _MSC_VER
            fprintf(fp, "(msvc %d.%d.%d) ", _MSC_VER / 100, _MSC_VER % 100, _MSC_FULL_VER % 100000);
#elif __GNUC__
            fprintf(fp, "(gcc %s) ", __VERSION__);
#endif


            fprintf(fp, "%s\n", appInfo.build);
            fprintf(fp, "Support email: %s\n", appInfo.email);
        }
    }
}
