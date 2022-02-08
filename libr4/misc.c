#include "libr.h"

void *allocmem(size_t size) {
    void *p;

    if ((p = malloc(size)) == NULL)
        fatal_err("Cannot get memory");
    return memset(p, 0, size);
}
