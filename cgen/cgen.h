#ifndef _CGEN_H
#define _CGEN_H 1
/* File cgen.h Created 17.05.2019 Last Modified 17.06.2020 */

/* Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH C compiler V3.09
 * (HI-TECH Software) and extend its life, outside of the CP/M environment
 * (Digital Research, Inc), for full operation in a  Unix-like operating
 * system UZI-180 without using the CP/M emulator.
 *
 * The HI-TECH C compiler V3.09 is provided free of charge for any use,
 * private or commercial, strictly as-is. No warranty or product support
 * is offered or implied including merchantability, fitness for a particular
 * purpose, or non-infringement. In no event will HI-TECH Software or its
 * corporate affiliates be liable for any direct or indirect damages.
 *
 * You may use this software for whatever you like, providing you acknowledge
 * that the copyright to this software remains with HI-TECH Software and its
 * corporate affiliates.
 *
 * All copyrights to the algorithms used, binary code, trademarks, etc.
 * belong to the legal owner - Microchip Technology Inc. and its subsidiaries.
 * Commercial use and distribution of recreated source codes without permission
 * from the copyright holderis strictly prohibited.
 *
 * The solution to this problem is to recreate the object code being moved,
 * replace the CP/M system functions (I/O, memory allocation, etc.) with
 * similar UZI-180 calls, and compile an executable file for this operating
 * system.
 */

/*
#define DEBUG
*/
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if defined(__STDC__) || defined(__STDC_VERSION__)
#include <stdbool.h>
#include <stdint.h>
#if __STDC_VERSION__ < 201112L
#define _Noreturn
#endif
#if __STDC_VERSION__ >= 201710L
#define register
#endif
/* in certain functions the VC compiler complains reasonably that
 *  certain variables may be used before being initialised
 * this macro forces a 0 initialisation which will cause
 * exceptions if the variable is used, rather than rely on
 * random data
 */

#define FORCEINIT   = NULL

#else
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned long uint32_t;
#ifndef bool
#define bool char
#define true 1
#define false 0
#endif
#define FORCEINIT
#define _Noreturn
#endif

#undef max /* replaced by function call */
#ifndef CPM
#define bmove(src, dst, cnt) memcpy(dst, src, cnt)
#endif
/*
 *	Constant declarations
 */
#define MININT  -32768 /* min for int (0x8000)	*/
#define MAXINT  32767  /* max for int (0x7fff)	*/
#define MAXFUN  0x20   /* Maximum limit nested function */
#define MAXBUF  60     /* Maximum buffer size 		*/
#define MAXNAME 40     /* Maximum file name length	*/
#define MAXERR  30     /* Maximum number nonfatal errors*/

#define NULSTR   0    /*  0  ""	*/
#define NOT      1    /*  1  "!"	*/
#define NEQL     2    /*  2  "!="	*/
#define HASHSIGN 3    /*  3  "#"	*/
#define DOLLAR   4    /*  4  "$"	*/
#define DOLLAR_U 5    /*  5  "$U"	*/
#define MOD      6    /*  6  "%"	*/
#define BAND     7    /*  7  "&"	*/
#define LAND     8    /*  8  "&&"	*/
#define GADDR    9    /*  9  "&U"	*/
#define LPAREN   0xA  /* 10  "("	*/
#define RPAREN   0xB  /* 11  ")"	*/
#define MUL      0xC  /* 12  "*"	*/
#define MUL_U    0xD  /* 13  "*U"	*/
#define ADD      0xE  /* 14  "+"	*/
#define INCR     0xF  /* 15  "++"	*/
#define PLUS_U   0x10 /* 16  "+U"	*/
#define COMMA    0x11 /* 17  ","	*/
#define SUB      0x12 /* 18  "-"	*/
#define DECR     0x13 /* 19  "--"	*/
#define CONV     0x14 /* 20  "->"	*/
#define MINUS_U  0x15 /* 21  "-U"	*/
#define DOT      0x16 /* 22  "."	*/
#define MEMBER   0x16 /* Alias for use in class*/
#define DOT_DOT  0x17 /* 23  ".."	*/
#define DIV      0x18 /* 24  "/"	*/
#define COLON    0x19 /* 25  ":"	*/
#define COLON_U  0x1A /* 26  ":U"	*/
#define COLON_S  0x1B /* 27  ":s"	*/
#define SCOLON   0x1C /* 28  ";"	*/
#define T_SCOLON 0x1D /* 29  ";;"	*/
#define LT       0x1E /* 30  "<"	*/
#define LSHIFT   0x1F /* 31  "<<"	*/
#define LEQ      0x20 /* 32  "<="	*/
#define ASSIGN   0x21 /* 33  "="	*/
#define ASMOD    0x22 /* 34  "=%"	*/
#define ASAND    0x23 /* 35  "=&"	*/
#define ASMUL    0x24 /* 36  "=*"	*/
#define ASADD    0x25 /* 37  "=+"	*/
#define ASSUB    0x26 /* 38  "=-"	*/
#define ASDIV    0x27 /* 39  "=/"	*/
#define ASLSHIFT 0x28 /* 40  "=<<"	*/
#define EQL      0x29 /* 41  "=="	*/
#define ASRSHIFT 0x2A /* 42  "=>>"	*/
#define ASEXOR   0x2B /* 43  "=^"	*/
#define ASEOR    0x2C /* 44  "=|"	*/
#define GT       0x2D /* 45  ">"	*/
#define GEQ      0x2E /* 46  ">="	*/
#define RSHIFT   0x2F /* 47  ">>"	*/
#define QUEST    0x30 /* 48  "?"	*/
#define ATGIGN   0x31 /* 49  "@"	*/
#define CASE     0x32 /* 50  "[\\"	*/
#define UNKNOWN  0x33 /* 51  "[a"	*/
#define ENUM     0x34 /* 52  "[c"	*/
#define EXPR     0x35 /* 53  "[e"	*/
#define INIT     0x36 /* 54  "[i"	*/
#define STRUCT   0x37 /* 55  "[s"	*/
#define UNION    0x38 /* 56  "[u"	*/
#define VAR      0x39 /* 57  "[v"	*/
#define BXOR     0x3A /* 58  "^"	*/
#define LBRACE   0x3B /* 59  "{"	*/
#define BOR      0x3C /* 60  "|"	*/
#define LOR      0x3D /* 61  "||"	*/
#define RBRACE   0x3E /* 62  "}"	*/
#define BNOT     0x3F /* 63  "~"	*/
#define RECIP    0x40 /* 64  "RECIP"   */
#define TYPE     0x41 /* 65  "TYPE"    */
#define IDOP     0x42 /* 66  "ID"	*/
#define CONST    0x43 /* 67  "CONST"   */
#define FCONST   0x44 /* 68  "FCONST"  */
#define USEREG   0x45 /* 69  "REG"     */
#define INAREG   0x46 /* 70  "INAREG"  */
#define BFIELD   0x47 /* 71  "BITFIELD"*/


/* register indexes*/
enum { /* REG_A=1, REG_C, REG_B, REG_E, REG_D, REG_L*/
       REG_H = 7,
       /* REG_IX, REG_IY, REG_SP */
       REG_AF = 11,
       /* REG_BC, REG_DE, REG_HL */
       REG_DEHL = 15
};

/* enums */
enum psect { P_BSS = 1, P_TEXT, P_DATA };

/*
 *	Structural declarations
 */

typedef struct node {
    uint8_t a_c0;
    uint8_t a_c1;
    uint8_t a_c2; /* two bits used */
    uint8_t a_c3[6];
    uint8_t a_uc9[6];
    uint8_t a_reg[6];
    uint16_t a_i15;
    struct member *pm; /* pointer to member */
    union {
        long l;               /* long */
        unsigned long ul;     /* unsigned long, to avoid cast*/
        struct node *np[2];   /* node pair */
        struct member *mp[2]; /* member pair */
        struct {              /* string + int value */
            char *s;
            int v;
        } sv;
    } info;
} node_t;

typedef struct member {    /* Offset Member Description			*/
    char *b_name;          /* +0   0 s_name Pointer to Name identifier 	*/
                           /* +1   1					*/
    char b_class;          /* +2   2 s_class 0x16 - MEMBER 	*/
                           /*			      '4' -  ENUM	*/
                           /*			      '7' -  STRUCT 	*/
                           /*			      '8' -  UNION	*/
                           /*			      '9' - 		*/
                           /*			      'A' -  TYPE		*/
    char b_sloc;           /* +3   3 s_strg Bits used: 0 0000001 -		*/
                           /*		            1 0000010 -	global?	*/
                           /*		            2 0000100 -		*/
                           /*		            3 0001000 -	register?*/
                           /*		            4 0010000 -		*/
    uint8_t b_ndpth;       /* +4   4 s_ndpth Nesting depth of block	*/
    uint8_t bWidth;          /* +5   5					*/
    uint8_t bOffset;          /* +6   6					*/
    struct member *b_next; /* +7   7					*/
                           /* +8   8					*/
    uint16_t b_size;       /* +9   9 s_size Type size			*/
                           /* +A  10					*/
    uint16_t b_nelem;      /* +B  11 s_nelem				*/
                           /* +C  12					*/
    uint16_t b_refl;       /* +D  13 s_refl				*/
                           /* +E  14					*/
    struct member *b_type; /* +F  15 s_type				*/
                           /* +10 16					*/
    int b_off;             /* +11 17 s_alig Type alig  size stack frame	*/
                           /* +12 18					*/
    union {                /* +13 18  - +14 19 */
        int16_t i;
        struct _memb {
            int16_t cnt;
            struct member *vals[1];
        } * mlist;
        struct _memi {
            int16_t cnt;
            int16_t vals[1];
        } * ilist;
    } b_memb;
    char b_flag; /* +15 21	 type flag 0, 1, 2, 3, 4, 5,	*/
} member_t;

struct codeFrag_t {
    char c_0;
    char c_1;
    char c_2;
    char c_3;
    uint8_t c_4;
    uint8_t c_5;
    char *p_6;
    char *p_8;
};

/*
 *	Descriptions of variables and arrays
 *
 * Declarations are located in sequence of being in
 * original binary image of CGEN.COM
 *					Purpose				Where it is used
 * ===== Start bss section ======= */
extern int lineno;             /* getToken, sub_6AD0, prMsg*/
extern char progname[MAXNAME]; /* getToken  */
extern member_t *typeLong;     /* sub_1680, makeConstNode, makeOpNode */
extern int array_AE13[MAXFUN]; /* leaveBlock,  sub_17E0, allocateOrEmitVariable */
extern member_t *typeUChar;    /* "uc" - uint8_t	   */
extern uint16_t nstdpth;       /* Current nesting depth   */
extern int array_AE57[MAXFUN];
extern int array_AE97[MAXFUN];
extern member_t *typeDouble;         /* "d" - double 	   */
extern member_t *typeChar;           /* "c" - char 		   */
extern member_t *array_AEDB[MAXFUN]; /*			   */
extern member_t *typeB;              /* "b"			   */
extern member_t *typeX;              /* "x"			   */
#define HASHTABSIZE 101
extern member_t *hashtab[HASHTABSIZE]; /* hash table (array_AF1F) */
extern member_t *typeVar;              /* "v" - variable  	   */
extern int lvlidx;                     /* Level nested function - leaveBlock, sub_1680 */

extern int word_AFF8;            /* emitCodeTemplate, emitNodeCodeFragments */
extern char byte_AFFA;           /* computeUsedRegsForStep, chooseResultRegister */
extern int word_AFFB;            /* emitCodeTemplate, emitTreeCode */
extern node_t *array_AFFD[0x14]; /* rewriteExprForCodegen, compileExpression */
extern void *nodeFreeList;       /* sub_36E0, allocNode, releaseNodeFreeList */
extern bool byte_B013;           /* sub_36E0, allocNode, ... */
extern uint8_t byte_B014;        /* rewriteExprForCodegen, compileExpression */
extern char *warningMsg;         /* msgptr  Pointer str printf       */
extern int word_B017;            /* leaveBlock, sub_6D1, computeUsedRegsForStep, generateCodeForExpr, assignVariableToRegister */
extern bool wflag;               /* Warning messages */
#if 0
extern bool pflag;               /* Not used */
extern bool hflag;               /* Not used */
#endif
extern int errcnt;               /* Number of errors */
#if 0
extern bool bflag;               /* Not used */
#endif
extern char *baseHeap;           /* Current highest memory */
#if 0
extern bool eflag;               /* Not used */
#endif
extern bool rflag;

/* ===== End of bss section ======= */

/* ===== Start data section ======= */

extern char *otherFrag[];            /*+emitCodeTemplate */
extern struct codeFrag_t codeFrag[]; /* selectCodePattern, computeUsedRegsForStep, emitCodeTemplate, emitNodeCodeFragments */

extern uint16_t dopetab[72]; /*+selectCodePattern, sub_2B8A, emitCodeTemplate, emitTreeCode, cloneNodeTree, ... */
extern char array_A94A[];    /*+selectCodePattern */
extern int array_AAE8[];     /*+leaveBlock,  selectCodePattern, computeUsedRegsForStep, assignVariableToRegister, ... */
extern uint8_t array_AB24[]; /*+computeUsedRegsForStep, emitCodeTemplate, mapRegisterAlias */
extern uint8_t array_AB54[]; /*+selectCompatibleRegister, findRegisterMatch */

extern char *regNames[];

/* ===== End of data section ======= */

/*
 * Library Function prototypes
 *
 */
#ifdef CPM
long atol(char *str);
void blkclr(char *, uint16_t size);
void *sbrk(int);
#else
#define blkclr(buf, len) memset(buf, 0, len)
#endif

/****************************************************************
 * Prototype functions are defined in sequence of being in
 * original binary image of CGEN.COM

 ****************************************************************/
#ifndef _WIN32
int fgetchar(void);
int fputchar(int);
#else
#define fgetchar getchar
#define fputchar putchar
#endif

/* for some functions the list of declarations below causes the compilation
 * to fail. When this happens the individual function defines MINI and declares
 * its used functions only
 */
#ifndef MINI
/* lex.c -----------------------------------------------------*/
int lookupPatternRule(int, int);
int lookupTokenId(char *);
member_t **gethashptr(char *);
member_t *getOrCreateSymbol(char *);
char *getToken();
void leaveBlock();
member_t *parseTypeWithIndirection(char *, uint16_t *);
void badIntCode();
void parseStmt();
void expect(char);
void parseData();
/* code.c ----------------------------------------------------*/
int emitInitializerData(member_t *, node_t *);
void parseInit();
void prFrameHead(int);
void prFrameTail(int, int);
void emitStructCopy(int, int);
void prGlobalDef(member_t *);
void emitBssDefinition(member_t *);
void emitSymbolLabel(member_t *);
void prDefb0s(int);
void prPsect(int);
void sortCaseLabels(int *pCase, int *pLabel, int nCase);
void parseSwitch();
void emitCompareWithA(int);
void prPush(uint8_t);
void prPop(uint8_t);
void prIXnPush(member_t *);
uint8_t getTypeClass(node_t *);
void emitTypeSuffix(node_t *);
void prDefb(char *, int);
void prJmpLabel(int);
void prJump(int);
void setEnumStorageType(member_t *, int, int);
int max(int, int);
void initializeTypesAndSymbols();
int newLocal();
member_t *getOrCreateScopedSymbol(char *, uint8_t);
/* sym.c -----------------------------------------------------*/
void parseVariable();
void parseMembers(int);
void parseEnum();
int alignUpByMask(int, int);
int computeVarSize(member_t *);
int getTypeAlignment(member_t *);
void finalizeStructOrUnionLayout(member_t *);
void emitRegisterVarLoads();
int selectCodePattern(node_t *, int, int, int, int *);
int computeUsedRegsForStep(node_t *, int);
int computeUsedRegs(node_t *);
uint8_t chooseResultRegister(node_t *);
/* cgen.c ----------------------------------------------------*/
void generateCodeForExpr(node_t *);
long signExtendToNodeSize(node_t *, long);
void emitSizedConstant(node_t *, long);
void emitCodeTemplate(node_t *, char *, char);
void emitNodeCodeFragments(node_t *);
void emitTreeCode(node_t *);
void freeNode(node_t *);
node_t *allocNode(void);
bool releaseNodeFreeList(void);
node_t *cloneNodeTree(node_t *);
void dereferenceNodeType(node_t *);
void markPointerType(node_t *);
uint16_t getPointeeSize(node_t *);
bool hasTypeFlag(node_t *, int);
bool hasPointerFlag(node_t *);
bool hasFunctionFlag(node_t *);
bool isStructValueNode(node_t *);
uint16_t nodesize(node_t *); /*sub_3993*/
node_t *foldConstantConversion(node_t *);
void convertNodeToType(node_t *, node_t *);
void evalUnsignedOperation(unsigned long *, long, int);
void evalBinaryOperation(long *, long, int);
node_t *rewriteExprForCodegen(node_t *);
/* tree.c ----------------------------------------------------*/
void compileExpression(node_t *);
node_t *foldConstantExpressions(node_t *);
node_t *makeConstNode(long);
node_t *parseExpr(void);
node_t *makeOpNode(uint8_t, node_t *, node_t *);
uint8_t log2IfPowerOfTwo(long);
void freeNodeTree(node_t *);
uint8_t isPatternApplicable(node_t *, int);
bool isAddressLikeExpr(node_t *);
bool isZeroConst(node_t *);
int getExprComplexityRank(node_t *);
bool isRegisterIndirection(node_t *);
node_t *simplifyLogicalNot(node_t *);
node_t *resolveIdentifierNode(node_t *);
node_t *rewriteMemberAccess(node_t *);
node_t *dropRightOperand(node_t *);
node_t *strengthReduceMulDivMod(node_t *);
node_t *simplifyConversion(node_t *);
node_t *collapseAddressDereference(node_t *);
/* local.c ---------------------------------------------------*/
node_t *optimizeExpressionTree(node_t *);
void allocateOrEmitVariable(member_t *, int);
node_t *normalizeUnaryMinusAndSub(node_t *);
node_t *normalizeAddSubForms(node_t *);
node_t *optimizeExpression(node_t *);
int invertTest(int);
bool fitsInTargetType(node_t *, node_t *);
bool assignVariableToRegister(member_t *, int);
bool isSameTypeAndSize(node_t *, node_t *);
bool areBothSigned(node_t *, node_t *);
bool constFitsComparisonRange(node_t *, node_t *);
uint8_t selectCompatibleRegister(int, int, int);
uint8_t findRegisterMatch(int, int);
uint16_t mapRegisterAlias(uint16_t, uint8_t);
int mergeRegisterConstraints(int, int, int, char *);
/* main.c  ---------------------------------------------------*/
/* int main(int, char **);	*/

/*
 * original C functions replaced to use stdarg
 */
#ifdef CPM
#define vfprintf _doprnt
#endif
_Noreturn void fatalErr(char *fmt, ...); /* ok   sub_6AA2.c	*/
void prWarning(char *fmt, ...);          /* ok sub_6AD0*/
void prError(char *fmt, ...);            /* ok sub_6B1D.c	*/
void prMsg(char *fmt, va_list args);
void *allocMem(size_t); /*sub_6B9B*/ /* ok sub_6B9B.c	*/
/* end of function declarations */
#endif

/* End file cgen.h */
#endif
