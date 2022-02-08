#include "libr.h"

void deleteModule() {

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
