#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#ifndef CPM
#include <time.h>
#else
typedef long time_t;
#endif

#if !defined(_STDC_VERSION__) || __STDC_VERSION < 201112L
#define _Noreturn
#endif
#if defined(_MSC_VER) && !defined(__STDC__)
#define __STDC__ 1
#endif

#ifdef __STDC__
#include <stdbool.h>
#include <stdint.h>
#else
typedef char bool;
#define true    1
#define false   0
typedef unsigned long uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
#endif
#if CPM
#include <sys.h>
#include <unixio.h>
#define vfprintf    _doprnt
#else
#ifdef _MSC_VER
#define strcasecmp  _stricmp
#else
#include <unistd.h> // for unlink
#endif
#endif

#ifndef _MAX_PATH
#ifdef PATH_MAX
#define _MAX_PATH PATH_MAX
#else
#define _MAX_PATH 255
#endif
#endif

#ifdef CPM
#define BLOCKSIZE 512
#else
#define BLOCKSIZE 4096 /* DOS used 1k */
#endif




/* clang-format off
   Object record types:   | Length (16 bits)     | Record type (8 bits) | Data (Length*8 bits) | */
#define TEXT_RECORD  1
#define PSECT_RECORD 2
#define RELOC_RECORD 3
#define SYM_RECORD   4 /* | Value (32 bits)      | loFlags (16 bits)      | psect name           | symbol name | */
#define START_RECORD 5
#define END_RECORD   6 /* | loFlags (16 bits)      | */
#define IDENT_RECORD 7 /* | byte order (32 bits) | byte order (16 bits) | machine name         | version number (16 bits) | */
#define XPSECT_RECORD  8
#define SEGMENT_RECORD 9
/* note records types upto 19 are accepted for later versions of the object file format.
   libr doesn't need to know the format
   as only SYM_RECORD, IDENT_RECORD and END_RECORD are processed
   clang-format on */

/* Hitech C has problems with function pointer declarations so define explicit */
typedef void (*mfuncptr)(uint8_t *, time_t);
typedef void (*sfuncptr)(uint8_t *, int);
typedef void (*pfuncptr)(int);



struct sym {
    char *name;
    uint8_t flags;
};




extern int width;
extern int cmdIndex;
extern int err_num;
extern bool noWarnings;
extern int num_ofiles;
extern uint32_t *moduleSizes;
extern uint8_t *moduleFlags;
extern struct sym *curSymPtr;
extern struct sym symbols[];
extern int _argc_;
extern char **cmdLineNames;
extern char **moduleStdNames;
extern bool verbose;


void allocModuleArrays(int name, char **buf);
uint8_t lookupName(uint8_t *name);
void processUnmatched(pfuncptr action);
void copyUnchangedSymbols(uint8_t *name, time_t libTime);
void copyUnchangedModules(uint8_t *name, time_t libTime);
void deleteModule(void);
void extractNamedModule(uint8_t *name, time_t libTime);
void extractModules(void);
void openTemp(void);
size_t writeBlock(void *buf, size_t size, size_t count, FILE *fp);
void closeTemp(void);
void openLibrary(char *name);
void openContent(void);
void rewindLibrary(void);
void commitNewLibrary(void);
void visitModules(mfuncptr action);
void visitSymbols(sfuncptr action);
void copySymbolsToTemp(void);
void copyModuleToTemp(void);
void extractOneModule(char *name);
void copyNewModule(int moduleId);
void copyNewSymbols(int moduleId);
void put32le(uint32_t val, uint8_t *buf);
void put16le(uint16_t val, uint8_t *buf);
uint16_t get16le(uint8_t *buf);
uint32_t get32le(uint8_t *buf);
void readName(uint8_t *buf);
void writeName(char *name);
void writeObjName(char *p1); /* writes object file name, mapping to lower case unless -s option */
void unexp_eof(void);
void listModules(char *key, char *name);
void listWithSymbols(void);
int main(int argc, char **argv);

void fatal_err(char *fmt, ...);

_Noreturn void open_err(char *name);
_Noreturn void seek_err(char *name);

void simpl_err(char *fmt, ...);
void warning(char *fmt, ...);
_Noreturn void badFormat(char *name, char *fmt, ...);

void noModule(int id);
_Noreturn void finish(int name);
_Noreturn void sigintHandler(int name);
void *xalloc(size_t name);
void parseIdentRec(void);
uint16_t get16ao(uint8_t *name);
void addSymbol(char *name, uint8_t loFlags);
int scanModule(char *name);
uint16_t conv_btou16a(uint8_t *p);
void getRecord(void);
void skipRecord(void);
void parseSymbolRec(void);
void copyMatchedSymbols(uint8_t *name, time_t libTime);
void copyMatchedModules(uint8_t *name, time_t libTime);
void replaceModule(void);


char **_getargs(char *, char *);
char *fname(char *name);