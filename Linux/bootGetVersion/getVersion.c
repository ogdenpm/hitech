// popen.c
/* This program uses _popen and _pclose to receive a
 * stream of text from a system process.
 */
#include <ctype.h>

#include <inttypes.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#ifdef _MSC_VER
#include <direct.h>
#else
#include <unistd.h>
#endif
#include "support.h"

char const help[] = "Usage:  %s [options] [directory | file]*\n"
                    "Where options are:\n"
                    "  -w      write new version file if version has updated\n"
                    "  -f      force write new version file\n"
                    "  -c file set alternative configuration file instead of version.in\n"
                    "  -u      include untracked/ignored files and directories\n"
                    "If no directory or file is specified '.' is assumed\n"
                    "Note -w or -f are only relevant for directories\n";

#ifndef _MAX_PATH
#ifdef PATH_MAX
#define _MAX_PATH PATH_MAX
#else
#define _MAX_PATH 260
#endif
#endif

char *currentWorkingDir;

char decorate[_MAX_PATH]  = "--decorate-refs=tags/appName-r*"; // updated once appName known
char tagPrefix[_MAX_PATH] = "tag: appName-r";                  // updated once appName known
char context[_MAX_PATH];
char fileName[_MAX_PATH];

char const *logCmd[]           = { "git", "log", "-1",     decorate, "--format=g%h,%ct,%D",
                                   "-z",  "--",  fileName, NULL };
char const *diffIndexNameCmd[] = { "git", "diff-index", "--name-only", "--ignore-cr-at-eol",
                                   "-z",  "HEAD",       "--",          fileName,
                                   NULL };
char const *diffIndexCmd[] = { "git", "diff-index", "--quiet", "--ignore-cr-at-eol", "-z", "HEAD",
                               "--",  fileName,     NULL };
char const *statusCmd[]    = { "git", "status", "-z", "--ignored", "-u", fileName, NULL };

string_t exeBuf;
string_t statusBuf;

bool includeUntracked;

int vCol = 14;
char const *appName;
char version[_MAX_PATH];
int versionLoc = 0;
char date[20];
char oldVersion[_MAX_PATH];
char const *configFile = "version.in";
char *versionFile;

bool noGit = false;                    // true if not a git repository
enum { DIRECTORY, SINGLEFILE, OTHER }; // path types

bool writeFile = false;
bool force     = false;

static bool isPrefix(char const *str, char const *prefix) {
    while (*prefix && *str++ == *prefix++)
        ;
    return *prefix == '\0';
}

static char *scanNumber(char *s, int low, int high) {
    if (!isdigit(*s) || *s == '0')
        return NULL;
    int val = 0;
    while (isdigit(*s))
        val = val * 10 + *s++ - '0';
    if (*s++ == '.' && low <= val && val <= high)
        return s;
    return NULL;
}

static char *scanRevision(char *s) {
    char *t = s;
    if (*t == 'g') {
        while (isxdigit(*++t))
            ;
        return t != s + 1 ? t : NULL;
    }
    if (isdigit(*t) && *t != '0') { // valid for both old and new
        while (isdigit(*t))
            t++;
        if (*t == '-' && isalpha(*++t)) {
            while (isalpha(*t))
                t++;
            if (isdigit(*t) && *t != '0') {
                while (isdigit(*t))
                    t++;
                return t;
            }
        }
        t = s;
    }
    while (isxdigit(*t))
        t++;

    return t != s ? t : NULL;
}

static bool parseVersion(char *line) {

    for (char *start = strstr(line, "20"); start; start = strstr(start + 2, "20")) {
        // scan forward looking for 20\d\d\.1?\d\.[123]?\d\.revision
        char *end;
        if ((end = scanNumber(start, 2000, 2099)) && (end = scanNumber(end, 1, 12)) &&
            (end = scanNumber(end, 1, 31)) && (end = scanRevision(end)) && end) {
            if (*end == '+')
                end++;
            if (*end == '?')
                end++;
            *end = '\0';
            // we have a valid start and end
            strcpy(oldVersion, start);
            return true;
        }
    }
    if (strstr(line, "xxxx.xx.xx.x?")) {
        strcpy(oldVersion, "xxxx.xx.xx.x?");
        return true;
    }
    return false;
}

static void getOldVersion() {
    *oldVersion = '\0';
    FILE *fp    = fopen(versionFile, "rt");
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            for (char *s = line; *s; s++)
                *s = tolower(*s);
            if (strstr(line, "git_version") && parseVersion(line))
                break;
        }
        fclose(fp);
    }
}

static int setupContext(char *path) {
    struct stat sb;
#ifdef _MSC_VER
    if (_fullpath(context, path, _MAX_PATH) == NULL)
#else
    if (realpath(path, context) == NULL)
#endif
        warn("Cannot resolve full path for %s", path);
    else if (stat(context, &sb) != 0)
        warn("Cannot access %s", path);
    else {
        char *name = (char *)basename(context);
        if (!*name) {
            name[-1] = '\0';                      // remove the trailing directory separator
            name     = (char *)basename(context); // retry to get the directory name
        }

        if (sb.st_mode & S_IFDIR) {
            strcpy(fileName, ".");
            appName = *name ? name : "_root_";
            return DIRECTORY;
        } else if (sb.st_mode & S_IFREG) {
            strcpy(fileName, name);
            *name   = '\0';
            appName = fileName;
            return SINGLEFILE;
        } else
            warn("%s is not a directory or file", path);
    }
    return OTHER;
}

// note the % 10000 and % 100 are to stop GCC complaining about possible overrun
static void initAsciiDate() {
    time_t tval;
    time(&tval);
    struct tm *timeInfo = gmtime(&tval);
    sprintf(date, "%04u-%02u-%02u %02u:%02u:%02u", timeInfo->tm_year + 1900, timeInfo->tm_mon + 1,
            timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
}

static char *ctimeVersion(char *timeStr) {
    static char verStr[20];
    time_t tval         = strtoull(timeStr, NULL, 10);

    struct tm *timeInfo = gmtime(&tval);
    sprintf(verStr, "%04u.%u.%u", timeInfo->tm_year + 1900, timeInfo->tm_mon + 1,
            timeInfo->tm_mday);
    return verStr;
}

static void generateVersion(bool isApp) {
    int lResult;
    strcpy(version, "xxxx.xx.xx.x?");
    if (noGit || (lResult = execute(logCmd, &exeBuf, false)) < 0) {
        if (!noGit) {
            warn("Cannot run git");
            noGit = true;
        }
        return;
    }
    if (lResult == 0 && exeBuf.str[0]) {
        if (!isApp) { // for files check still live in repo
            if (execute(statusCmd, &statusBuf, false) != 0 || statusBuf.str[0] == '!' ||
                statusBuf.str[0] == '?')
                return;
        }

        // simple split on comma

        char *s;
        char rev[128];
        if ((s = strchr(exeBuf.str, ',')))
            *s = '\0';

        char *pCtime = s ? s + 1 : "";
        strcpy(rev, exeBuf.str); // default to githash
        // check for tag: appname-r
        if ((s = strchr(pCtime, ',')) && isPrefix(++s, tagPrefix)) {
            s += strlen(tagPrefix);
            if (isdigit(*s)) {
                char *t = rev;
                while (isdigit(*s))
                    *t++ = *s++;

                if (*s && *s != '-') // add qualifier if needed
                    *t++ = '-';
                strcpy(t, s);
            }
        }

        sprintf(version, "%s.%s", ctimeVersion(pCtime), rev);

        if (isApp) { // for app check ignore changes to the version file
            if (execute(diffIndexNameCmd, &exeBuf, false) == 0 && exeBuf.str[0]) {
                // if the first file isn't the version file
                // or if there are multiple files then mark with a +
                if (stricmp(basename(exeBuf.str), versionFile) != 0 || strchr(exeBuf.str, '\0')[1])
                    strcat(version, "+");
            }
        } else if (execute(diffIndexCmd, NULL, false) == 1)
            strcat(version, "+");
    }
}

static void getOneVersion(char *name) {
    int type = setupContext(name);
    if (type == OTHER || strcmp(name, ".git") == 0)
        return;

    if (chdir(context) != 0) {
        warn("Cannot change to directory %s", context);
        return;
    }

    sprintf(decorate, "--decorate-refs=tags/%s-r*", appName);
    sprintf(tagPrefix, "tag: %s-r", appName);

    if (type == DIRECTORY) {
        free(versionFile);
        versionFile = parseConfig(configFile);

        generateVersion(true);
        getOldVersion();
        if (*version == 'x' && *oldVersion) {
            strcpy(version, oldVersion);
            if (!strchr(version, '?'))
                strcat(version, "?");

        }
        if (writeFile && (force || strcmp(version, oldVersion) != 0))
            writeNewVersion(versionFile, version, date);
    } else
        generateVersion(false);

    if (chdir(currentWorkingDir))
        ;

    if (isdigit(*version) || (type == DIRECTORY && writeFile) || includeUntracked)
        printf("%-*s %c %s\n", vCol, appName, type == DIRECTORY ? '-' : '+',
               *version == 'x' ? "Unknown" : version);
}

int main(int argc, char **argv) {
    while (getopt(argc, argv, "fwuc:") != EOF) {
        switch (optopt) {
        case 'f':
            force = true;
            // FALLTHROUGH
        case 'w':
            writeFile = true;
            break;
        case 'c':
            configFile = optarg;
            break;
        case 'u':
            includeUntracked = true;
            break;
        }
    }
    currentWorkingDir = getcwd(NULL, 0);

    initAsciiDate();
    if (optind + 1 >= argc)
        vCol = 1;
    else {
        for (int i = optind; i < argc; i++)
            if (strlen(argv[i]) > vCol)
                vCol = (int)strlen(argv[i]);
    }
    if (optind == argc)
        getOneVersion(".");
    else
        while (optind < argc)
            getOneVersion(argv[optind++]);
}
