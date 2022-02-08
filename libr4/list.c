#include "libr.h"

char symbolTypes[] = "D?C???U";
int columns;
int curColumn;
char *listModuleName;
bool listDefinedOpt;
uint8_t listModuleType;
bool listModuleFound;
bool listUndefinedOpt;

static void checkToList(char *testName, int type) {

    if (type == 0 ? listDefinedOpt : listUndefinedOpt) {
        if (strcmp(listModuleName, testName) == 0 ||
            (*testName == '_' && strcmp(listModuleName, testName + 1) == 0)) {

            listModuleFound = 1;
            listModuleType  = type;
        }
    }
}

static void listOneModule(char *testName, time_t libTime) {
    static time_t prevTime;

    if (lookupName(testName) == 0)
        return;
    if (listModuleName) {
        listModuleFound = false;
        visitSymbols(checkToList);
        if (!listModuleFound)
            return;
    }
    printf("%-15.15s", testName);
    if (listModuleName != 0)
        printf(" %c", listModuleType >= 7 ? '?' : symbolTypes[listModuleType]);

    if (libTime != 0 && libTime != prevTime) {
        printf(" %s", ctime(&libTime));
        prevTime = libTime;
    } else
        putchar('\n');
}

void listModules(char *key, char *name) {

    if (*key) {
        listModuleName = name;
        do {
            switch (*key) {
            case 'd':
                listDefinedOpt = true;
                break;
            case 'u':
                listUndefinedOpt = true;
                break;
            default:
                fatal_err("Subkeys: d(defined) u(ndefined)");
            }
        } while (*++key);
    }
    visitModules(listOneModule); /* Print name obj name from library with the key m */
}

static void printSymbol(char *name, int type) {

    if (curColumn >= columns) {
        printf("\t\t");
        curColumn = 0;
    }
    printf("%c %-12.12s", ((type >= 7) ? '?' : symbolTypes[type]), name);
    if (++curColumn >= columns)
        printf("\n");
    else
        printf("  ");
}

static void printObjAndSymbols(char *name, time_t libTime) {

    if (lookupName(name) == 0)
        return;
    printf("%-16.15s", name); /* Print obj name from library with the key s */
    curColumn = 0;
    visitSymbols(printSymbol); /* Print symbol name with the key s */
    if (curColumn != 0 && curColumn < columns)
        putchar('\n');
}

void listWithSymbols() {

    if ((columns = (width - 16) / 16) == 0)
        columns = 1;
    visitModules(printObjAndSymbols); /*  Print obj name and symbol names */
    processUnmatched(noModule);       /* Module not found */
}
