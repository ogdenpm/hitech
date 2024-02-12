#include "libr.h"

void extractNamedModule(uint8_t *name, time_t libTime) {
    if (lookupName(name)) {
        extractOneModule((char *)name);
        if (verbose)
            printf("x %s\n", (char *)name);
    }
}

void extractModules() {

    openContent();
    visitModules(extractNamedModule);
    processUnmatched(noModule); /* Module not found */
}
