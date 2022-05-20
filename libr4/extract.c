#include "libr.h"

void extractNamedModule(char *name, time_t libTime) {
    if (lookupName(name)) {
        extractOneModule(name);
        if (verbose)
            printf("x %s\n", name);
    }
}

void extractModules() {

    openContent();
    visitModules(extractNamedModule);
    processUnmatched(noModule); /* Module not found */
}
