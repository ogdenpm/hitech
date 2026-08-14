#include "libr.h"

void replaceModule(char *p, char *q) {
    (void)p;
    (void)q;
    if (num_ofiles == 0)
        fatal_err("replace what ?");
    openContent();
    openTemp();
    visitModules(copyMatchedSymbols);
    processUnmatched(copyNewSymbols);
    rewindLibrary();
    visitModules(copyMatchedModules);
    processUnmatched(copyNewModule);
    commitNewLibrary();
}
