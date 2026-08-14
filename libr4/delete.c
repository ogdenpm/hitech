#include "libr.h"

void deleteModule(char *p, char *q) {
    (void)p;
    (void)q;
    if (num_ofiles == 0)
        fatal_err("delete what ?");
    openContent();
    openTemp();
    visitModules(copyUnchangedSymbols);
    processUnmatched(noModule); /* Module not found */
    rewindLibrary();
    visitModules(copyUnchangedModules);
    commitNewLibrary();
}
