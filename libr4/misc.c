#include "libr.h"

void *xalloc(size_t size) {
    void *p;

    if ((p = malloc(size)) == NULL)
        fatal_err("Cannot get memory");
    return memset(p, 0, size);
}
