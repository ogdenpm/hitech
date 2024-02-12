#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
/*
 *	Assigned type abbreviations
 */

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned
#endif

#ifndef ulong
#define ulong unsigned long
#endif

#if !defined(_STDC_VERSION__) || __STDC_VERSION < 201112L
#define _Noreturn
#endif
#if defined(_MSC_VER) && !defined(__STDC__)
#define __STDC__ 1
#endif

#ifdef __STDC__
#include <stdarg.h>
#endif
#if CPM
#include <sys.h>
#else
#define index strchr
#ifndef _MSC_VER
#include <unistd.h> // for unlink
#endif
#endif

/* libr.c */
void (*dispatch[])();
int cmpNames(register char *st, char *p2);
void allocModuleArrays ( int p1 , char **p2 );
uchar lookupName ( uint8_t *p1 );
void processUnmatched ( void (*fun )(uint8_t *,uint ));
void copyUnchangedSymbols ( uint8_t *name , long dummy );
void copyUnchangedModules ( uint8_t *name , long dummy );
void deleteModule ( void );
void extractNamedModule ( uint8_t *p1 , long dummy );
void extractModules ( void );
void openTemp ( void );
int writeFile ( uint8_t *buf , uint size , uint count , FILE *fp );
void closeTemp ( void );
void openLibrary ( char *name );
void openContent ( void );
void rewindLibrary ( void );
void commitNewLibrary ( void );
void visitModules ( void (*funptr )(uint8_t *,long ));
void visitSymbols ( void (*action )(uint8_t *,int ));
void copySymbolsToTemp ( void );
void copyModuleToTemp ( void );
void extractOneModule ( char *name );
void copyNewModule ( uint8_t *p1 , uint moduleId );
void copyNewSymbols ( uint8_t *moduleName , uint moduleId );
void conv_u32tob ( unsigned long p1 , uint8_t *p2 );
void conv_u16tob ( uint p1 , uint8_t *p2 );
uint conv_btou16 ( register uchar *p1 );
long conv_btou32 ( register uchar *p1 );
void readName ( register uint8_t *p1 );
void writeName ( register uint8_t *p1 );
void unexp_eof ( void );
void checkToList ( uint8_t *p1 , int tType );
void listOneModule ( uint8_t *p1 , long dummy );
void listModules ( char *key , char *name );
void printSymbol ( uint8_t *name , int tType );
void printObjAndSymbols ( uint8_t *p1 , long dummy );
void listWithSymbols ( void );
int main ( int argc , char **argv );
#ifdef CPM
void fatal_err P((int p1, int p2, int p3, int p4, int p5));
#else
void vfatal_err(char *fmt, va_list args);
void fatal_err(char *fmt, ...);
#endif
_Noreturn void open_err(char *p1);
void seek_err(char *p1);
#ifdef CPM
void simpl_err(char *p1, char *p2, int p3, int p4, int p5);
void warning(char *p1, char *p2, int p3, int p4, int p5);
void badFormat(char *name, char *fmt, uint p3, uint p4, int p5, int p6);
#else
void simpl_err ( char *p1 , char *p2 );
void warning ( char *p1 , char *p2 );
void badFormat ( char *name , char *fmt , ...);
#endif
void noModule ( uint8_t *p1 , uint dummy );
_Noreturn void finish ( int p1 );
void sigintHandler ( int p1 );
void *xalloc ( int p1 );
void parseIdentRec ( void );
uint get_modu16 ( uchar *p1 );
void addSymbol ( uchar *name , int flags );
int scanModule ( char *name );
uint conv_btou16a ( register uchar *st );
void getRecord ( void );
void skipRecord ( void );
void parseSymbolRec ( void );
void copyMatchedSymbols ( uint8_t *p1 , long dummy );
void copyMatchedModules ( uint8_t *p1 , long dummy );
void replaceModule ( void );

