#include "libr.h"

void extractNamedModule(uint8_t *name, time_t libTime) {
    (void)libTime;
    if (lookupName(name)) {
        extractOneModule((char *)name);
        if (verbose)
            printf("x %s\n", (char *)name);
    }
}

void extractModules(char *p, char *q) {
    (void)p;
    (void)q;
    openContent();
    visitModules(extractNamedModule);
    processUnmatched(noModule); /* Module not found */
}
