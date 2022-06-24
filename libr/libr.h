#ifdef __STDC__
# define	P(s) s
#else
# define P(s) ()
#endif


/* libr.c */
/int cmpNames P((register char *st , char *p2 ));
void allocModuleArrays P((int p1 , char **p2 ));
uchar lookupName P((char *p1 ));
void processUnmatched P((void (*fun )(char *,uint )));
void copyUnchangedSymbols P((char *name , long dummy ));
void copyUnchangedModules P((char *name , long dummy ));
void deleteModule P((void ));
void extractNamedModule P((char *p1 , long dummy ));
void extractModules P((void ));
void openTemp P((void ));
int writeFile P((char *buf , uint size , uint count , FILE *fp ));
void closeTemp P((void ));
void openLibrary P((char *name ));
void openContent P((void ));
void rewindLibrary P((void ));
void commitNewLibrary P((void ));
void visitModules P((void (*funptr )(char *,long )));
void visitSymbols P((void (*action )(char *,int )));
void copySymbolsToTemp P((void ));
void copyModuleToTemp P((void ));
void extractOneModule P((char *name ));
void copyNewModule P((char *p1 , uint moduleId ));
void copyNewSymbols P((char *moduleName , uint moduleId ));
void conv_u32tob P((unsigned long p1 , char *p2 ));
void conv_u16tob P((uint p1 , char *p2 ));
uint conv_btou16 P((register uchar *p1 ));
long conv_btou32 P((register uchar *p1 ));
void readName P((register char *p1 ));
void writeName P((register char *p1 ));
void unexp_eof P((void ));
void checkToList P((char *p1 , int tType ));
void listOneModule P((char *p1 , long dummy ));
void listModules P((char *key , char *name ));
void printSymbol P((char *name , int tType ));
void printObjAndSymbols P((char *p1 , long dummy ));
void listWithSymbols P((void ));
int main P((int argc , char **argv ));
void vfatal_err P((char *fmt , va_list args ));
void fatal_err P((char *fmt , ...));
void fatal_err P((int p1 , int p2 , int p3 , int p4 , int p5 ));
_Noreturn void open_err P((char *p1 ));
void seek_err P((char *p1 ));
void simpl_err P((char *p1 , char *p2 , int p3 , int p4 , int p5 ));
void simpl_err P((char *p1 , char *p2 ));
void warning P((char *p1 , char *p2 , int p3 , int p4 , int p5 ));
void warning P((char *p1 , char *p2 ));
void badFormat P((char *name , char *fmt , uint p3 , uint p4 , int p5 , int p6 ));
void badFormat P((char *name , char *fmt , ...));
void noModule P((char *p1 , uint dummy ));
void finish P((int p1 ));
void sigintHandler P((int p1 ));
char *xalloc P((int p1 ));
void parseIdentRec P((void ));
uint get_modu16 P((uchar *p1 ));
void addSymbol P((uchar *name , int flags ));
//clang -format off //Object record types :|Length P((16 bits ));
uint conv_btou16a P((register uchar *st ));
void getRecord P((void ));
void skipRecord P((void ));
void parseSymbolRec P((void ));
void copyMatchedSymbols P((char *p1 , long dummy ));
void copyMatchedModules P((char *p1 , long dummy ));
void replaceModule P((void ));

#undef P
