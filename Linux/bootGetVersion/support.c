#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include "support.h"

#define DEFAULTCHUNK    256
bool debug;


/// <summary>
/// emit Fatal error message with '\n' appended to stderr and exit
/// </summary>
/// <param name="fmt">printf compatible format string</param>
/// <param name="">optional parameters</param>
/// <returns>exits with 1</returns>
_Noreturn void fatal(char const* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
    va_end(args);
    exit(1);
}


/// <summary>
/// emit warning error message with '\n' appended to stderr
/// </summary>
/// <param name="fmt">printf compatible format string</param>
/// <param name="">optional parameters</param>
/// <returns>exits with 1</returns>
void warn(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
    va_end(args);
}


/// <summary>
/// emit message with '\n' appended to stderr, if debug flag set
/// </summary>
/// <param name="fmt">printf compatible format string</param>
/// <param name="">optional parameters</param>
void debugPrint(char const* fmt, ...) {
    if (debug) {
        va_list args;
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        fputc('\n', stderr);
        va_end(args);
    }
}

#ifdef _MSC_VER
/// <summary>
/// Equivalent to POSIX basename for visual C
/// </summary>
/// <param name="path">full path to file</param>
/// <returns>pointer filename only</returns>

char const* basename(char const* path) {
    char* s;
    if (path[0] && path[1] == ':') // strip any device
        path += 2;
    while ((s = strpbrk(path, "/\\"))) // allow / or \ directory separators
        path = s + 1;
    return path;
}
#endif




/// <summary>
/// helper to malloc memory and check for out of memory
/// </summary>
/// <param name="size">Amount of memory to allocate in bytes.</param>
/// <returns>pointer to the allocated block</returns>
void* safeMalloc(size_t size) {
    void* p = malloc(size);
    if (!p)
        fatal("Out of memory");
    return p;
}


/// <summary>
/// helper to relloc memory and check for out of memory
/// </summary>
/// <param name="old">The old memory block</param>
/// <param name="size">The new size</param>
/// <returns></returns>
void *safeRealloc(void *old, size_t size) {
    void *p = realloc(old, size);
    if (!p)
        fatal("Out of memory");
    return p;
}

/// <summary>
/// helper to strdup string and check for out of memory
/// </summary>
/// <param name="size">string to duplicate</param>
/// <returns>pointer to the allocated block</returns>
char *safeStrdup(char const *str) {
    char *s = strdup(str);
    if (!s)
        fatal("Out of memory");
    return s;
}

void initString(string_t *str, int chunk) {
    str->chunk = chunk;
    str->pos   = 0;
    str->capacity = 0;
    free(str->str);
    str->str = NULL;
}


void appendString(string_t *str, char *s) {
    appendBuffer(str, s, (int)strlen(s));
}

void appendBuffer(string_t *str, char *s, int len) {
    if (str->pos + len + 1> str->capacity) {
        if (!str->chunk)
            str->chunk = DEFAULTCHUNK;
        while (str->pos + len > (str->capacity += str->chunk))
            ;
        str->str = safeRealloc(str->str, str->capacity); 
    }
    memcpy(str->str + str->pos, s, len);
    str->str[str->pos += len] = '\0';    // make sure null terminated
}