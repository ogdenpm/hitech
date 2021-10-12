#ifndef _dump_h
#define _dump_h
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

void showVersion(FILE *fp, bool full);
#ifdef _MSC_VER
#define strcasecmp  _stricmp
#endif


#endif
