/*
 * File data.c Created 17.05.2019 Last Modified 03.02.2021
 */

#include "cgen.h"
#include "showVersion.h"
/* ===== start bss section ======= */

int lineno;             /* getToken, sub_6AD0, prMsg*/
char progname[MAXNAME]; /* getToken, prWarning, prMsg */

member_t *typeLong; /* "l" - long		   */ /* initializeTypesAndSymbols, makeConstNode, makeOpNode */
int array_AE13[MAXFUN]; /*			   */     /* leaveBlock,  sub_17E0, allocateOrEmitVariable */
member_t *typeUChar;                          /* "uc" - uint8_t	   */
uint16_t nstdpth;                             /* Current nesting depth   */
int array_AE57[MAXFUN];                       /*			   */
int array_AE97[MAXFUN];                       /*			   */
member_t *typeDouble;                         /* "d" - double 	   */
member_t *typeChar;                           /* "c" - char 		   */
member_t *array_AEDB[MAXFUN];                 /*			   */
member_t *typeB;                              /* "b"			   */
member_t *typeX;                              /* "x"			   */
member_t *hashtab[101];                       /* hash table (array_AF1F) */
member_t *typeVar;                            /* "v" - variable  	   */
int lvlidx; /* Level nested function   */     /* leaveBlock, initializeTypesAndSymbols */

int word_AFF8;            /* emitCodeTemplate, emitNodeCodeFragments */
char lastReferencedReg;           /* computeUsedRegsForStep, chooseResultRegister */
int word_AFFB;            /* emitCodeTemplate, emitTreeCode */
node_t *array_AFFD[0x14]; /* rewriteExprForCodegen, compileExpression */
void *nodeFreeList;       /* sub_36E0, allocNode, releaseNodeFreeList */
bool byte_B013;           /* sub_36E0, allocNode, ... */
uint8_t byte_B014;        /* rewriteExprForCodegen, compileExpression */
char *warningMsg;         /* Pointer for printf      */
int word_B017;            /* leaveBlock, sub_6D1, computeUsedRegsForStep, generateCodeForExpr, assignVariableToRegister */
bool wflag;               /* Warning messages	   */
#if 0
bool pflag;               /* Not used		   */
bool hflag;               /* Not used		   */
#endif
int errcnt;               /* Number of errors	   */
#if 0
bool bflag;               /* Not used		   */
#endif
#ifdef CPM
char *baseHeap; /* Current highest memory  */
#endif
#if 0
bool eflag; /* Not used		   */
#endif
bool rflag;

/* ===== End of bss section ======= */

/* these tables were buit using a perl script so that string tables did
 * not cause out of memory
 */
extern char stab0[], stab1[], stab2[], stab3[], stab4[];
/* clang-format off */
char *otherFrag[] = {
0,           0,           stab4+0x1BB, 0,           0,           0,           stab4+0x18D, stab4+0x189, 
0,           0,           0,           0,           stab4+0x185, 0,           stab4+0x179, stab4+0x175, 
0,           0,           stab4+0x171, stab4+0x1A9, 0,           stab3+0x101, 0,           0,           
stab4+0x1A5, 0,           0,           0,           0,           0,           stab4+0x1C7, stab0+0x2F5, 
0,           0,           stab4+0x18D, stab4+0x189, stab4+0x185, stab4+0x179, stab4+0x171, stab4+0x1A5, 
stab0+0x2F5, stab4+0x1BC, stab0+0x22E, stab4+0x1A1, stab4+0x1A2, 0,           stab4+0x1C4, stab0+0x22E, 
0,           0,           0,           0,           0,           0,           0,           0,           
0,           0,           stab4+0x1A1, 0,           stab4+0x1A2, 0,           0,           stab4+0x1C1, 
0,           0,           0,           0,           0,           0,           0,           0,           
};


struct codeFrag_t codeFrag[] = {
    {0,    0,    0,    0,    0,    0,    0,           0},           /* 0 */
    {0,    0,    0,    0x1C, 'H',  'H',  0,           stab0+0x261}, /* 1 */
    {1,    0,    0,    0x2C, 'I',  'J',  stab3+0x28E, stab0+0x58},  /* 2 */
    {2,    0,    0,    0x23, 'I',  'J',  stab3+0x2B5, stab0+0x58},  /* 3 */
    {3,    0,    0,    0x0F, 'I',  'K',  stab4+0x21,  stab0+0x58},  /* 4 */
    {3,    0,    0,    0x0F, 'I',  'L',  stab4+0x35,  stab0+0x58},  /* 5 */
    {3,    0,    0,    0x13, 'I',  'K',  stab4+0x3F,  stab0+0x58},  /* 6 */
    {0,    0,    0x12, 0x0A, 'M',  'N',  stab1+0x218, stab0+0x58},  /* 7 */
    {0,    0,    0,    5,    'O',  0,    stab4+0x15D, stab0+0x261}, /* 8 */
    {0,    0,    0,    4,    'P',  'O',  stab4+0x12F, stab0+0x58},  /* 9 */
    {0,    0,    0,    4,    'Q',  'O',  stab3+0x24D, stab0+0x58},  /* 10 */
    {4,    0,    0,    0x0B, 'R',  0,    0,           stab0+0x58},  /* 11 */
    {5,    0,    0,    0x0B, 'S',  0,    0,           stab0+0x58},  /* 12 */
    {6,    0,    0,    0x0B, 'T',  0,    0,           stab0+0x58},  /* 13 */
    {3,    6,    0,    0x0B, 'U',  0,    0,           stab0+0x58},  /* 14 */
    {3,    0,    6,    0x0B, 'V',  0,    stab4+0x95,  stab0+0x58},  /* 15 */
    {0,    0,    0,    0x1A, 'O',  0,    stab4+0x1B8, stab0+0x58},  /* 16 */
    {3,    0,    0,    0x21, 'I',  'J',  stab4+0xA7,  stab0+0x58},  /* 17 */
    {3,    0,    0,    0x46, 'V',  0,    0,           stab0+0x58},  /* 18 */
    {3,    0,    0,    0x31, 'J',  0,    stab4+0x128, stab0+0x58},  /* 19 */
    {0,    0,    0,    0x57, 0,    0,    0,           stab0+0x58},  /* 20 */
    {3,    0,    0,    0x55, 0,    0,    0,           stab0+0x58},  /* 21 */
    {7,    0,    0,    0x21, 'I',  'J',  stab0+0x107, stab0+0x58},  /* 22 */
    {8,    0,    0,    0x31, 'X',  0,    stab4+0x121, stab0+0x58},  /* 23 */
    {5,    0,    0,    0x31, 'J',  0,    stab3+0x115, stab0+0x58},  /* 24 */
    {5,    0,    0,    0x53, 0,    0,    0,           stab0+0x58},  /* 25 */
    {6,    0,    0,    0x21, 'I',  'J',  stab2+0x3D,  stab0+0x261}, /* 26 */
    {6,    0,    0,    0x31, 'Y',  0,    stab4+0x113, stab0+0x58},  /* 27 */
    {6,    0,    0,    0x5A, 0,    0,    0,           stab0+0x58},  /* 28 */
    {0,    0,    0,    0x5B, 0,    0,    0,           stab0+0x58},  /* 29 */
    {0,    1,    0,    0x55, 0,    0,    0,           stab0+0x261}, /* 30 */
    {0,    0,    1,    0x55, 0,    0,    stab4+0xEF,  stab0+0x2C3}, /* 31 */
    {0,    0,    0,    0x1B, 'J',  0,    0,           stab4+0x14E}, /* 32 */
    {0,    0,    0,    9,    '\\', 0,    0,           stab0+0x261}, /* 33 */
    {0,    0,    0,    0x43, 0,    0,    0,           stab4+0x1BE}, /* 34 */
    {6,    0,    0,    0x14, 'Y',  0,    0,           stab0+0x261}, /* 35 */
    {0,    0,    0,    0x0E, 'Y',  'J',  0,           stab4+0x162}, /* 36 */
    {0,    0,    0,    0x49, 0,    0,    0,           stab0+0x261}, /* 37 */
    {3,    0,    0,    0x55, 0,    0,    0,           stab0+0x261}, /* 38 */
    {3,    0,    0x1A, 0x56, 0,    0,    stab4+0x95,  stab0+0x2C3}, /* 39 */
    {0,    0,    0,    0x5A, 0,    0,    0,           stab4+0xF7},  /* 40 */
    {0,    0,    0,    0x5E, 0,    0,    0,           stab4+0xF7},  /* 41 */
    {5,    0,    0,    0x53, 0,    0,    0,           stab4+0xE7},  /* 42 */
    {3,    6,    0,    0x55, 0,    0,    stab4+0xDF,  stab4+0x1CA}, /* 43 */
    {3,    0,    2,    0x56, 0,    0,    stab3+0x127, stab4+0x1CA}, /* 44 */
    {0,    0,    0,    0x57, 0,    0,    stab4+0x10C, stab4+0x1CA}, /* 45 */
    {0,    0,    0,    0x5F, 0,    0,    0,           stab4+0x1CC}, /* 46 */
    {0,    0,    0,    0x5A, 0,    0,    stab4+0xD7,  stab4+0x1CA}, /* 47 */
    {4,    0,    0x10, 0x60, 0,    0,    stab0+0x1FC, stab4+0x1B5}, /* 48 */
    {0,    0,    0,    0x11, 'N',  'N',  0,           stab4+0x19D}, /* 49 */
    {0,    0,    0,    0x17, 0,    0,    0,           stab3+0x101}, /* 50 */
    {3,    0,    1,    0x62, 0,    0,    stab4+0xCF,  stab4+0xC7},  /* 51 */
    {3,    0,    1,    0x5C, 0,    0,    stab4+0x5D,  stab4+0x53},  /* 52 */
    {6,    0,    0x0E, 0x5C, 0,    0,    stab4+0x5D,  stab4+0x53},  /* 53 */
    {0,    0,    0x0E, 0x57, 0,    0,    stab3+0x215, stab3+0x231}, /* 54 */
    {6,    0,    0x0E, 0x49, 0,    0,    stab3+0x9E,  stab2+0x259}, /* 55 */
    {6,    0,    0x0E, 0x0D, 'd',  0,    stab0+0x2C6, stab0+0x295}, /* 56 */
    {0,    0,    0x51, 0x65, 0,    0,    stab0+0xB1,  stab0+0x1C6}, /* 57 */
    {0,    0,    0x18, 0x57, 0,    0,    stab3+0x215, stab3+0x231}, /* 58 */
    {6,    0,    0x18, 0x49, 0,    0,    stab3+0x9E,  stab3+0xC8},  /* 59 */
    {6,    0,    0x1D, 0x0D, 'T',  0,    stab1+0x29B, stab1+0x2BA}, /* 60 */
    {0,    0,    0,    0x63, 0,    0,    0,           stab0+0x261}, /* 61 */
    {0,    0,    0,    0x47, 'R',  0,    0,           stab2+0x2B6}, /* 62 */
    {1,    0,    0,    7,    ']',  'J',  stab3+0x25A, stab0+0x58},  /* 63 */
    {0,    0,    0,    8,    'h',  'Q',  stab2+0x171, stab0+0x58},  /* 64 */
    {0,    0,    0,    0x51, 0,    0,    stab2+0x11F, stab0+0x261}, /* 65 */
    {0,    0,    0,    1,    'Q',  0,    stab2+0x1BF, stab0+0x58},  /* 66 */
    {0,    0,    0,    0x3D, 'i',  'Q',  stab2+0x171, stab0+0x58},  /* 67 */
    {0,    0,    0,    0x51, 0,    0,    stab3+0x256, stab0+0x261}, /* 68 */
    {0,    0,    0,    0x50, 0,    0,    stab3+0x18C, stab0+0x58},  /* 69 */
    {3,    0,    0,    0x5D, 0,    0,    0,           stab0+0x261}, /* 70 */
    {3,    0,    0x1A, 0x0D, 'k',  0,    stab3+0x1F7, stab0+0x2C3}, /* 71 */
    {3,    0,    0x1A, 0x0D, 'l',  0,    stab3+0x29B, stab0+0x2C3}, /* 72 */
    {3,    0,    0x5A, 0x49, 0,    0,    stab4+0xCF,  stab0+0x2C3}, /* 73 */
    {0,    0,    0,    0x1C, 'H',  'U',  0,           stab3+0x1B8}, /* 74 */
    {0,    0,    0,    0x21, 'I',  'U',  stab4+0xBF,  stab3+0x1B8}, /* 75 */
    {3,    0,    0,    0x30, 'i',  'm',  0,           stab3+0x1B8}, /* 76 */
    {3,    0,    0x1A, 0x14, 'P',  0,    stab2+0x107, stab0+0x2C3}, /* 77 */
    {3,    0,    0x1A, 0x14, 'Q',  0,    stab1+0x1F6, stab0+0x2C3}, /* 78 */
    {3,    0,    0,    0x14, 'U',  0,    0,           stab2+0x2B6}, /* 79 */
    {3,    0,    0x5A, 0x14, 'Z',  0,    stab4+0x2B,  stab0+0x2C3}, /* 80 */
    {9,    0,    0x52, 0x14, 'S',  0,    stab3+0x72,  stab4+0x6},   /* 81 */
    {3,    0,    0x5A, 0x14, 'S',  0,    stab4+0x0,   stab0+0x2C3}, /* 82 */
    {3,    0,    0,    0x21, '\\', 'V',  stab4+0x49,  stab3+0x1B8}, /* 83 */
    {3,    0,    0x5A, 0x6E, 0,    0,    stab4+0x16,  stab0+0x2C3}, /* 84 */
    {0,    0,    0,    0x1F, 'U',  'o',  stab3+0x267, stab2+0x2B6}, /* 85 */
    {0,    0,    0,    0x1F, 'U',  'p',  stab1+0x91,  stab2+0x2B6}, /* 86 */
    {0,    0,    0,    0x28, 'a',  'o',  stab3+0x1CA, stab2+0x2B6}, /* 87 */
    {0,    0,    0,    0x28, 'a',  'p',  stab1+0x62,  stab2+0x2B6}, /* 88 */
    {0,    0,    0,    0x0E, 'V',  ']',  stab4+0x11A, stab2+0x2B6}, /* 89 */
    {0x0A, 0,    0,    7,    'V',  ']',  stab4+0x167, stab2+0x2B6}, /* 90 */
    {0,    0,    0,    0x25, 'a',  ']',  stab4+0x8C,  stab2+0x2B6}, /* 91 */
    {0x0A, 0,    0,    0x23, 'a',  ']',  stab4+0x105, stab2+0x2B6}, /* 92 */
    {3,    0,    0x1A, 0x0F, 'I',  'K',  stab3+0x16B, stab0+0x2C3}, /* 93 */
    {0,    0,    0x1B, 0x0F, 'a',  'q',  stab3+0x1BB, stab0+0x2C3}, /* 94 */
    {0,    0,    0,    0x3F, 'V',  0,    stab4+0x17D, stab2+0x2B6}, /* 95 */
    {0,    0,    0,    0x15, 'V',  0,    stab4+0x181, stab2+0x2B6}, /* 96 */
    {3,    0,    1,    0x5C, 0,    0,    stab4+0x5D,  stab0+0x2C3}, /* 97 */
    {0,    0,    0x12, 0x0A, 'M',  'N',  stab1+0xE9,  stab4+0x16C}, /* 98 */
    {0,    0,    0,    0x19, 'r',  's',  stab1+0x1F2, stab2+0x2B6}, /* 99 */
    {0,    0,    0,    0x72, 0,    0,    stab3+0x2F1, stab0+0x58},  /* 100 */
    {5,    0,    0,    0x53, 0,    0,    0,           stab0+0x261}, /* 101 */
    {6,    0,    0,    0x54, 0,    0,    0,           stab0+0x261}, /* 102 */
    {3,    0,    0,    0x56, 0,    0,    0,           stab0+0x261}, /* 103 */
    {0,    0,    0,    0x43, 0,    0,    0,           stab4+0xBC},  /* 104 */
    {0,    3,    0,    0x55, 0,    0,    0,           stab0+0x261}, /* 105 */
    {0,    0,    3,    0x5D, 0,    0,    stab4+0xCF,  stab0+0x2C3}, /* 106 */
    {0,    0x0D, 0,    0x5A, 0,    0,    0,           stab0+0x261}, /* 107 */
    {0,    0x0E, 0x0D, 0x5A, 0,    0,    stab4+0x9E,  stab0+0x2C3}, /* 108 */
    {0,    0x19, 0,    0x5A, 0,    0,    0,           stab0+0x261}, /* 109 */
    {0,    0,    0,    0x64, 0,    0,    0,           stab0+0x261}, /* 110 */
    {0,    0,    0,    0x0D, 'Y',  0,    0,           stab0+0x261}, /* 111 */
    {0,    0,    0,    0x42, 0,    0,    0,           stab4+0x1BE}, /* 112 */
    {0,    0,    0,    0x44, 0,    0,    stab1+0x1B0, stab4+0x199}, /* 113 */
    {0,    0,    0,    0x17, 0,    0,    0,           stab0+0x58},  /* 114 */
    {0,    0,    0,    0x44, 0,    0,    0,           stab4+0x1BE}, /* 115 */
    {0,    0,    0,    2,    'g',  'u',  0,           stab2+0x104}, /* 116 */
    {0,    0,    0,    2,    'v',  'u',  0,           stab4+0x153}, /* 117 */
    {0,    0,    0,    2,    'V',  'u',  stab4+0x13C, stab4+0x153}, /* 118 */
    {0x0A, 0,    0,    2,    'V',  ']',  stab4+0x158, stab2+0x104}, /* 119 */
    {0x0A, 0,    0,    2,    'V',  'p',  stab2+0x1A5, stab4+0x153}, /* 120 */
    {0x0B, 0,    1,    2,    'I',  'u',  stab3+0x17C, stab2+0x104}, /* 121 */
    {0x0B, 0,    0x1C, 2,    '\\', 'u',  stab2+0x79,  stab2+0x104}, /* 122 */
    {0x0B, 0,    1,    2,    'R',  'u',  stab2+0x1F3, stab2+0x104}, /* 123 */
    {0x0B, 0,    1,    2,    ']',  'u',  stab3+0x17C, stab2+0x104}, /* 124 */
    {0x0B, 0,    0,    0x1E, ']',  'u',  stab3+0x2E6, stab4+0x1BB}, /* 125 */
    {0x0B, 0,    0,    0x2E, ']',  'u',  stab3+0x2E6, stab4+0x1BC}, /* 126 */
    {0x0C, 0,    1,    2,    ']',  'u',  stab1+0x25B, stab2+0x104}, /* 127 */
    {0x0C, 0,    0,    0x1E, ']',  'u',  stab3+0x2DB, stab4+0x1BB}, /* 128 */
    {0x0C, 0,    0,    0x2E, ']',  'u',  stab3+0x2DB, stab4+0x1BC}, /* 129 */
    {0x0B, 0,    0,    2,    'T',  'd',  stab3+0x1E8, stab2+0x104}, /* 130 */
    {0,    0,    1,    2,    'T',  'd',  stab2+0x1D9, stab4+0x153}, /* 131 */
    {0,    0,    0x52, 2,    'S',  '_',  stab2+0xCF,  stab4+0x153}, /* 132 */
    {0,    0,    0,    0x5C, 0,    0,    0,           stab0+0x261}, /* 133 */
    {0,    0,    0,    0x0D, 'T',  0,    0,           stab4+0x142}, /* 134 */
    {0,    0x0E, 0,    0x5A, 0,    0,    0,           stab2+0x2B6}, /* 135 */
    {0,    0x0D, 0x0E, 0x5A, 0,    0,    stab4+0x9E,  stab0+0x2C3}, /* 136 */
    {0,    0,    0,    0x0F, 'c',  'J',  0,           stab3+0x281}, /* 137 */
    {0,    0,    0,    0x0E, 'W',  'x',  0,           stab4+0x162}, /* 138 */
    {0,    0,    0,    0x57, 0,    0,    0,           stab4+0x195}, /* 139 */
    {0,    0,    9,    0x0E, '\\', 'x',  stab4+0x5D,  stab4+0x148}, /* 140 */
    {0x0D, 0,    0,    0x0F, 'W',  'J',  0,           stab2+0x2C6}, /* 141 */
    {0x0E, 0,    0,    0x45, 0,    0,    0,           stab4+0x1BE}, /* 142 */
    {0x0D, 0,    0,    0x25, 'W',  'J',  stab4+0x21,  stab0+0x261}, /* 143 */
    {0,    0,    0,    0x25, 'W',  '^',  stab4+0x7A,  stab0+0x261}, /* 144 */
    {0,    0,    0,    0x21, 'W',  'Y',  stab4+0xFE,  stab0+0x261}, /* 145 */
    {0,    0,    0,    0x21, 'W',  '\\', stab4+0x71,  stab0+0x261}, /* 146 */
    {0,    0,    0,    0x21, '\\', 'W',  stab4+0x83,  stab0+0x148}, /* 147 */
    {0,    0,    0,    0x1B, 'J',  0,    0,           stab4+0x1AD}, /* 148 */
    {0,    0,    0,    0x42, 0,    0,    0,           stab4+0x1BE}, /* 149 */
    {0,    0,    0,    0x43, 0,    0,    0,           stab4+0x1B1}, /* 150 */
    {5,    0,    0,    0x53, 0,    0,    stab3+0x19C, stab0+0x58},  /* 151 */
    {3,    0,    0,    0x49, 0,    0,    0,           stab0+0x261}, /* 152 */
    {3,    0,    0,    0x0D, 'Z',  0,    0,           stab1+0x2B5}, /* 153 */
    {0x0F, 0,    0,    0x43, 0,    0,    0,           stab4+0xBC},  /* 154 */
    {0x10, 0,    0,    0x43, 0,    0,    0,           stab0+0x58},  /* 155 */
    {3,    0,    0,    0x25, 'I',  'o',  stab4+0x21,  stab0+0x261}, /* 156 */
    {3,    0,    0,    0x25, 'I',  'L',  stab4+0x35,  stab0+0x261}, /* 157 */
    {0,    0,    0x52, 0x47, 'T',  0,    stab0+0xDC,  stab4+0x136}, /* 158 */
    {0,    0,    0,    0x21, 'e',  'd',  stab1+0xBE,  stab2+0x2B6}, /* 159 */
    {6,    0,    0,    0x30, 'i',  'm',  0,           stab3+0x1B8}, /* 160 */
    {0,    0,    0x18, 0x59, 0,    0,    stab4+0xCF,  stab0+0x2C3}, /* 161 */
    {6,    0,    0x18, 0x5C, 0,    0,    stab4+0x5D,  stab0+0x2C3}, /* 162 */
    {6,    0,    0x18, 0x49, 0,    0,    stab3+0x9E,  stab0+0x2C3}, /* 163 */
    {0,    0,    0,    0x1C, 'H',  'Z',  0,           stab3+0x1B8}, /* 164 */
    {0,    0,    0x18, 0x57, 0,    0,    stab3+0x215, stab0+0x2C3}, /* 165 */
    {6,    0,    0x17, 0x22, 'R',  'd',  stab2+0x18B, stab2+0x2B6}, /* 166 */
    {6,    0,    0x17, 6,    'T',  'd',  stab3+0x5C,  stab2+0x2B6}, /* 167 */
    {0,    0,    0,    0x2F, 'Z',  'o',  stab3+0xDD,  stab2+0x2B6}, /* 168 */
    {0,    0,    0,    0x1F, 'T',  'o',  stab3+0x223, stab2+0x2B6}, /* 169 */
    {6,    0,    1,    0x28, 'R',  'p',  stab2+0x18B, stab2+0x2B6}, /* 170 */
    {0,    0,    1,    0x1F, 'T',  'p',  stab2+0x20D, stab2+0x2B6}, /* 171 */
    {0,    0,    0,    0x13, 'f',  'o',  stab2+0x2B9, stab2+0x2B6}, /* 172 */
    {0,    0,    0,    0x0F, 'f',  'o',  stab2+0x2D1, stab2+0x2B6}, /* 173 */
    {2,    0,    0,    0x23, 'f',  'J',  stab3+0x138, stab2+0x2B6}, /* 174 */
    {2,    0,    0,    7,    'Z',  'J',  stab3+0x1D9, stab2+0x2B6}, /* 175 */
    {1,    0,    0,    0x2C, 'f',  'J',  stab3+0x149, stab2+0x2B6}, /* 176 */
    {1,    0,    0,    0x3C, 'Z',  'J',  stab3+0x206, stab2+0x2B6}, /* 177 */
    {6,    0,    0x5C, 7,    ']',  ']',  stab0+0x263, stab1+0x2D5}, /* 178 */
    {6,    0,    1,    0x23, 'f',  ']',  stab0+0x230, stab2+0x2B6}, /* 179 */
    {6,    0,    0x1D, 0x0F, 'c',  'J',  stab2+0x0,   stab2+0x2B6}, /* 180 */
    {6,    0,    0x1D, 0x13, 'c',  'J',  stab1+0x18B, stab2+0x2B6}, /* 181 */
    {6,    0,    0x18, 0x0D, 'k',  0,    stab2+0x5B,  stab0+0x2C3}, /* 182 */
    {6,    0,    0x1D, 0x0D, 'l',  0,    stab1+0x113, stab0+0x2C3}, /* 183 */
    {6,    0,    0x1D, 0x0D, 'T',  0,    stab1+0x29B, stab0+0x2C3}, /* 184 */
    {6,    0,    0x1A, 0x52, 0,    0,    stab1+0x13B, stab2+0x2B6}, /* 185 */
    {6,    0,    0x18, 0x14, 'P',  0,    stab2+0x107, stab0+0x2C3}, /* 186 */
    {6,    0,    0x18, 0x14, 'Q',  0,    stab1+0x1D3, stab0+0x2C3}, /* 187 */
    {0,    0,    0x18, 0x25, 'W',  '^',  stab3+0x18,  stab0+0x2C3}, /* 188 */
    {6,    0,    0,    0x25, 'f',  'o',  stab3+0x2A8, stab2+0x2B6}, /* 189 */
    {6,    0,    0,    0x26, 'f',  'o',  stab3+0x274, stab2+0x2B6}, /* 190 */
    {6,    0,    0,    0x25, 'f',  'L',  stab3+0x2C2, stab2+0x2B6}, /* 191 */
    {6,    0,    0,    0x26, 'c',  '^',  stab3+0x15A, stab2+0x2B6}, /* 192 */
    {6,    0,    0,    0x25, 'c',  '^',  stab3+0x2CF, stab2+0x2B6}, /* 193 */
    {6,    0,    0,    0x21, '\\', 'Z',  stab4+0x49,  stab3+0x1B8}, /* 194 */
    {6,    0,    0,    0x21, 'I',  'Z',  stab3+0xB3,  stab3+0x1B8}, /* 195 */
    {6,    0,    0,    0x21, 'R',  '^',  stab1+0x2D9, stab3+0x1B8}, /* 196 */
    {6,    0,    0,    0x12, 'T',  '^',  stab3+0x1AC, stab2+0x2B6}, /* 197 */
    {0,    0,    0,    0x0E, 'Z',  'o',  stab2+0x2C6, stab2+0x2B6}, /* 198 */
    {0,    0,    0,    0x0E, 'Z',  'L',  stab4+0xB,   stab2+0x2B6}, /* 199 */
    {6,    0x1D, 0x0E, 0x0E, 'Z',  'Y',  stab3+0x103, stab0+0x2C3}, /* 200 */
    {6,    0,    0,    0x0E, 'T',  '^',  stab4+0x67,  stab2+0x2B6}, /* 201 */
    {0,    0,    0x0E, 0x15, '^',  0,    stab2+0x2A1, stab0+0x2C3}, /* 202 */
    {0,    0,    0,    0x21, 'W',  'Z',  stab3+0x23F, stab3+0x1B8}, /* 203 */
    {6,    0,    0x58, 0x6E, 0,    0,    stab2+0x289, stab0+0x2C3}, /* 204 */
    {0x11, 0,    0x58, 0x14, 'j',  0,    stab3+0xF1,  stab0+0x2C3}, /* 205 */
    {0x12, 0,    0x18, 0x14, 'V',  0,    stab2+0x1F,  stab0+0x2C3}, /* 206 */
    {0,    0,    0,    9,    '[',  0,    0,           stab0+0x261}, /* 207 */
    {0x13, 0,    0x52, 0x14, 'S',  0,    stab3+0x72,  stab3+0x1E4}, /* 208 */
    {6,    0,    0,    0x14, 'Z',  0,    0,           stab2+0x2B6}, /* 209 */
    {6,    0,    0,    0x14, 'S',  0,    0,           stab3+0x1E4}, /* 210 */
    {8,    0,    1,    0x15, 'S',  0,    stab3+0x88,  stab2+0x2B6}, /* 211 */
    {5,    0,    0x0F, 0x5C, 0,    0,    stab2+0x240, stab0+0x2C3}, /* 212 */
    {0,    0,    0x0F, 0x43, 0,    0,    stab3+0x46,  stab0+0x2C3}, /* 213 */
    {5,    0,    0x0F, 0x49, 0,    0,    stab1+0x31,  stab0+0x2C3}, /* 214 */
    {5,    0,    0,    0x6E, 0,    0,    0,           stab0+0x261}, /* 215 */
    {5,    0,    0,    0x30, 'i',  'm',  0,           stab3+0x1B8}, /* 216 */
    {5,    0,    0x54, 0x0D, 'T',  0,    stab0+0x59,  stab1+0x2D5}, /* 217 */
    {7,    0,    0x0C, 0x0E, 'S',  'J',  stab0+0x18C, stab2+0x2B6}, /* 218 */
    {5,    0,    0x52, 0x22, 'R',  '_',  stab2+0xEB,  stab4+0x16C}, /* 219 */
    {5,    0,    0x52, 0x0F, 'R',  0,    stab2+0x271, stab4+0x16C}, /* 220 */
    {5,    0,    0x52, 6,    'S',  '_',  stab3+0x0,   stab2+0x2B6}, /* 221 */
    {7,    0,    0x4F, 0x28, 'R',  'p',  stab1+0x27B, stab0+0x2C3}, /* 222 */
    {7,    0,    0x54, 0x1F, 'S',  'p',  stab2+0xB3,  stab2+0x2B6}, /* 223 */
    {5,    0,    0,    0x21, '\\', 'S',  stab2+0x227, stab3+0x1B8}, /* 224 */
    {5,    0,    0,    0x21, 'I',  'S',  stab1+0x0,   stab3+0x1B8}, /* 225 */
    {5,    0,    0x51, 0x21, 'R',  '_',  stab0+0x0,   stab0+0xAD},  /* 226 */
    {7,    0,    0x11, 0x15, '_',  0,    stab0+0x14A, stab0+0xAD},  /* 227 */
    {0x14, 0,    0x54, 0x14, 'd',  0,    stab1+0x23A, stab1+0x2D5}, /* 228 */
    {0x14, 0,    0x54, 0x14, 'V',  0,    stab1+0x163, stab1+0x2D5}, /* 229 */
    {0x15, 0,    0x4F, 0x14, 'd',  0,    stab4+0xAF,  stab0+0x2C3}, /* 230 */
    {0x15, 0,    0x4F, 0x14, 'U',  0,    stab3+0x2F,  stab0+0x2C3}, /* 231 */
    {0x16, 0,    0x52, 0x14, 'S',  0,    stab2+0x123, stab2+0x2B6}, /* 232 */
    {0x17, 0,    0x52, 0x14, 'T',  0,    stab2+0x13D, stab4+0x16C}, /* 233 */
    {0x18, 0,    0x52, 0x14, 'V',  0,    stab2+0x157, stab4+0x16C}, /* 234 */
    {0x19, 0,    0x52, 0x14, 'S',  0,    stab3+0x72,  stab2+0x2B6}, /* 235 */
    {0,    0,    0,    0x14, 'S',  0,    0,           stab2+0x2B6}, /* 236 */
    {0,    0,    0,    0x43, 0,    0,    0,           stab4+0xB7},  /* 237 */
    {0,    0,    0,    0x76, 0,    0,    0,           stab0+0x261}, /* 238 */
    {0,    0,    0,    0x0D, 'w',  0,    0,           stab4+0x63},  /* 239 */
    {3,    0,    0,    0x0D, 'T',  0,    0,           stab1+0x2B5}, /* 240 */
    {0x1A, 0,    0,    0x43, 0,    0,    0,           stab0+0x58},  /* 241 */
    {0x1B, 0,    0,    0x43, 0,    0,    0,           stab0+0x58},  /* 242 */
    {0,    0x0D, 0,    0x5B, 0,    0,    0,           stab0+0x261}, /* 243 */
    {0,    0,    0x0D, 0x0D, 'T',  0,    stab4+0x9E,  stab0+0x2C3}, /* 244 */
    {0,    0x0E, 0,    0x5B, 0,    0,    0,           stab0+0x261}, /* 245 */
    {0,    0,    0,    0x0D, 'T',  0,    0,           stab0+0x261}, /* 246 */
    {4,    0,    0x0C, 0x21, '`',  'R',  stab2+0x96,  stab3+0x1B8}, /* 247 */
    {0,    0,    0x18, 0x5C, 0,    0,    stab4+0xCF,  stab0+0x2C3}, /* 248 */
    {0,    0,    0,    0x0D, 'Z',  0,    0,           stab0+0x261}, /* 249 */
    {4,    0,    0,    0x6E, 0,    0,    0,           stab4+0x191}, /* 250 */
    {0x1C, 0,    0,    0x14, '[',  0,    0,           stab0+0x261}, /* 251 */
    {0x1D, 0,    0,    0x43, 0,    0,    0,           stab4+0xBC},  /* 252 */
    {0x1E, 0,    0,    0x43, 0,    0,    0,           stab0+0x58},  /* 253 */
};

char stab0[] = {
    "pop de\n"               /* 0x0 */
    "ld (hl),e\n"
    "inc\thl\n"
    "ld (hl),d\n"
    "inc hl\n"
    "pop bc\n"
    "ld (hl),c\n"
    "inc hl\n"
    "ld (hl),b\n"
    "ld\tl,c\n"
    "ld\th,b\0"
    "ld X000N,(GL)\n"        /* 0x59 */
    "inc GL\n"
    "ld X001N,(GL)\n"
    "inc GL\n"
    "ld X1N,(GL)\n"
    "inc\tGL\n"
    "ld X011N,(GL)\n"
    "ld X010N,X1N\0"
    "ld e,(hl)\n"            /* 0xB1 */
    "inc hl\n"
    "ld d,(hl)\n"
    "dec hl\n"
    "ex de,hl\n"
    "global bfext\n"
    "call bfext\n"
    "defb TN+(CN.shl.4)\0"
    "ld L,.low.VR\n"         /* 0x107 */
    "ld ~+1L,.high.VR\n"
    "ld ~+2L,.low.V+2R\n"
    "ld ~+3L,.high.V+2R\0"
    "ld hl,ON\n"             /* 0x14A */
    "pop bc\n"
    "or a\n"
    "sbc hl,bc\n"
    "pop\tbc\n"
    "ex de,hl\n"
    "ld hl,ON\n"
    "sbc hl,bc\0"
    "ex de,hl\n"             /* 0x18C */
    "ld bc,VR\n"
    "add hl,bc\n"
    "ex de,hl\n"
    "ld bc,V+2R\n"
    "adc hl,bc\0"
    "ex X10N,GL\n"           /* 0x1C6 */
    "global bfins\n"
    "call bfins\n"
    "defb TN+(CN.shl.4)\0"
    "ld hl,-ZN\n"            /* 0x1FC */
    "add\thl,sp\n"
    "ld sp,hl\n"
    "ex de,hl\n"
    "ld bc,ZN\n"
    "ldir\0"
    "ld a,G0L\n"             /* 0x230 */
    "ON R\n"
    "ld G0L,a\n"
    "ld a,G1L\n"
    "ON\t~+1R\n"
    "ld G1L,a\n"
    "L\0"
    "ld a,L\n"               /* 0x263 */
    "ON R\n"
    "ld X00N,a\n"
    "ld a,~+1L\n"
    "ON\t~+1R\n"
    "ld X01N,a\0"
    "ex de,hl\n"             /* 0x295 */
    "ld (XN),G1L\n"
    "dec XN\n"
    "ld (XN),G0L\n"
    "ex\tde,XN\0"
    "ex de,hl\n"             /* 0x2C6 */
    "ld G0L,(XN)\n"
    "inc XN\n"
    "ld G1L,(XN)\n"
    "ex\tde,hl"
};

char stab1[] = {
    "ld L,G00R\n"            /* 0x0 */
    "ld ~+1L,G01R\n"
    "ld ~+2L,G10R\n"
    "ld ~+3L,G11R\0"
    "ld X00N,L\n"            /* 0x31 */
    "ld X01N,~+1L\n"
    "ld X10N,~+2L\n"
    "ld X11N,~+3L\0"
    "inc GR\n"               /* 0x62 */
    "dec GR\n"
    "jr z,2f\n"
    "1:\n"
    "sONAN GL\n"
    "djnz 1b\n"
    "2:\n"
    "L\0"
    "inc GR\n"               /* 0x91 */
    "dec GR\n"
    "jr z,2f\n"
    "1:\n"
    "sONAN GL\n"
    "djnz 1b\n"
    "2:\0"
    "global bfins\n"         /* 0xBE */
    "call bfins\n"
    "defb TL+(CL.shl.4)\0"
    "call L\n"               /* 0xE9 */
    "exx\n"
    "ld hl,R\n"
    "add hl,sp\n"
    "ld sp,hl\n"
    "exx\0"
    "ld X0N,(GL)\n"          /* 0x113 */
    "inc GL\n"
    "ld X1N,(GL)\n"
    "dec GL\n"
    "L\0"
    "ld XN,(GL)\n"           /* 0x13B */
    "inc GL\n"
    "ld\tG1L,(GL)\n"
    "ld G0L,XN\0"
    "ld e,a\n"               /* 0x163 */
    "rla\n"
    "sbc a,a\n"
    "ld d,a\n"
    "ld l,a\n"
    "ld h,a\0"
    "ld XN,-VR\n"            /* 0x18B */
    "add\tGL,XN\n"
    "L\n"
    "or a\n"
    "sbc GL,XN\0"
    "psect data\n"           /* 0x1B0 */
    "eFN: deff SN\n"
    "psect text\0"
    "U0:\n"                  /* 0x1D3 */
    "ld XN,1\n"
    "jp U2f\n"
    "U1:\n"
    "ld XN,0\n"
    "U2:\0"
    "U0:\n"                  /* 0x1F6 */
    "ld XN,1\n"
    "p U2f\n"
    "U1:\n"
    "ld XN,0\n"
    "U2:\0"
    "call L\n"               /* 0x218 */
    "ld hl,R\n"
    "add hl,sp\n"
    "ld\tsp,hl\0"
    "ld a,d\n"               /* 0x23A */
    "rla\n"
    "sbc a,a\n"
    "ld l,a\n"
    "ld h,a\0"
    "ld XN,L\n"              /* 0x25B */
    "or ~+1L\n"
    "or ~+2L\n"
    "or ~+3L\0"
    "global\tasANlONsh\n"    /* 0x27B */
    "call\tasANlONsh\0"
    "ld X0N,(GL)\n"          /* 0x29B */
    "inc GL\n"
    "ld X1N,(GL)\0"
    "ld (GL),X1N\n"          /* 0x2BA */
    "dec GL\n"
    "ld (GL),X0N\0"
    "ld (GL),G0R\n"          /* 0x2D9 */
    "inc GL\n"
    "ld (GL),G1R"
};

char stab2[] = {
    "ld XN,VR\n"             /* 0x0 */
    "add GL,XN\n"
    "L\n"
    "sbc GL,XN\0"
    "ld X0N,a\n"             /* 0x1F */
    "rla\n"
    "sbc a,a\n"
    "ld X1N,a\0"
    "ld L,.low.VR\n"         /* 0x3D */
    "ld ~+1L,.high.VR\0"
    "ld X0N,(GL+0)\n"        /* 0x5B */
    "ld X1N,(GL+1)\n"
    "L\0"
    "ld X0N,(L)\n"           /* 0x79 */
    "ld\ta,X00N\n"
    "or X01N\0"
    "push hl\n"              /* 0x96 */
    "ld XN,ZN\n"
    "ldir\n"
    "pop hl\0"
    "global\tANlONsh\n"      /* 0xB3 */
    "call ANlONsh\0"
    "global\tALrelop\n"      /* 0xCF */
    "call ALrelop\0"
    "global\tasANlON\n"      /* 0xEB */
    "call asANlON\0"
    "ld XN,1\n"              /* 0x107 */
    "jp L,U0f\n"
    "dec\tXN\n"
    "U0:\0"
    "global\tALltof\n"       /* 0x123 */
    "call ALltof\0"
    "global\tALitof\n"       /* 0x13D */
    "call ALitof\0"
    "global\tALbtof\n"       /* 0x157 */
    "call ALbtof\0"
    "U1:jp ~-1U1f\n"         /* 0x171 */
    "U0:jp ~-1U0f\0"
    "global\tasANON\n"       /* 0x18B */
    "call asANON\0"
    "global\tbrelop\n"       /* 0x1A5 */
    "call brelop\0"
    "U1:jp ~-1U0f\n"         /* 0x1BF */
    "U0:jp ~-1U1f\0"
    "global wrelop\n"        /* 0x1D9 */
    "call wrelop\0"
    "ld XN,(GL)\n"           /* 0x1F3 */
    "inc GL\n"
    "or\t(GL)\0"
    "global\tshANON\n"       /* 0x20D */
    "call shANON\0"
    "ld (L),G0R\n"           /* 0x227 */
    "ld\t(~+2L),G1R\0"
    "ld X0N,(L)\n"           /* 0x240 */
    "ld\tX1N,(~+2L)\0"
    "ld L,X0N\n"             /* 0x259 */
    "ld ~+1L,X1N;XN\0"
    "global\tlANON\n"        /* 0x271 */
    "call lANON\0"
    "ld X0N,G10L\n"          /* 0x289 */
    "ld X1N,G11L\0"
    "ld XN,ON\n"             /* 0x2A1 */
    "or a\n"
    "sbc XN,GL\0"
    "dec GLV--R\n"           /* 0x2B9 */
    "L\n"
    "inc GLV--R\0"
    "inc GLV--R\n"           /* 0x2D1 */
    "L\n"
    "dec GLV--R"
};

char stab3[] = {
    "global\tANlON\n"        /* 0x0 */
    "call ANlON\0"
    "add L,GR\n"             /* 0x18 */
    "push\tL\n"
    "pop XN\0"
    "ld hl,0\n"              /* 0x2F */
    "ld d,l\n"
    "ld e,GL\0"
    "ld X0N,VN\n"            /* 0x46 */
    "ld X1N,V+2N\0"
    "global\tANON\n"         /* 0x5C */
    "call ANON\0"
    "global\tftol\n"         /* 0x72 */
    "call ftol\0"
    "ld a,h\n"               /* 0x88 */
    "xor 80h\n"
    "ld h,a\0"
    "ld X0N,L\n"             /* 0x9E */
    "ld X1N,~+1L\0"
    "ld L,G0R\n"             /* 0xB3 */
    "ld ~+1L,G1R\0"
    "ld L,X0N\n"             /* 0xC8 */
    "ld ~+1L,X1N\0"
    "srAN G1L\rrr G0LV--R\0" /* 0xDD */
    "ld X0N,L\n"             /* 0xF1 */
    "ld G1N,0\0"
    "ld XN,R\n"              /* 0x103 */
    "add XN,GL\0"
    "defw VL\n"              /* 0x115 */
    "defw V+2L\0"
    "ld XN,GL\n"             /* 0x127 */
    "push bc\0"
    "res TR&7CR,G0L\n"       /* 0x138 */
    "L\0"
    "set TR&7CR,G0L\n"       /* 0x149 */
    "L\0"
    "or a\n"                 /* 0x15A */
    "sbc GL,GR\n"
    "L\0"
    "ld XN,L\n"              /* 0x16B */
    "ON LV--R\0"
    "ld XN,L\n"              /* 0x17C */
    "or ~+1L\0"
    "jp L,U0f\n"             /* 0x18C */
    "jp U1f\0"
    "push hl\n"              /* 0x19C */
    "push de\0"
    "or a\n"                 /* 0x1AC */
    "sbc GL,GR\0"
    "ld XN,a\n"              /* 0x1BB */
    "ON a\n"
    "L\0"
    "sONAN GLV--R\n"         /* 0x1CA */
    "L\0"
    "res TR&7CR,G0L\0"       /* 0x1D9 */
    "or a\n"                 /* 0x1E8 */
    "sbc hl,de\0"
    "ld XN,(GL+0)\n"         /* 0x1F7 */
    "L\0"
    "set TR&7CR,G0L\0"       /* 0x206 */
    "push L\n"               /* 0x215 */
    "pop XN\0"
    "add hl,hlV--R\0"        /* 0x223 */
    "push XN\n"              /* 0x231 */
    "pop L\0"
    "push GR\n"              /* 0x23F */
    "pop L\0"
    "U0:\n"                  /* 0x24D */
    "jp R\n"
    "U1:\0"
    "bit\tTR&7CR,L\0"        /* 0x25A */
    "sONAN GLV--R\0"         /* 0x267 */
    "dec GLV--R\n"           /* 0x274 */
    "L\0"
    "inc hlV--R\n"           /* 0x281 */
    "L\0"
    "set\tTR&7CR,L\0"        /* 0x28E */
    "ld XN,(GL)\n"           /* 0x29B */
    "L\0"
    "inc GLV--R\n"           /* 0x2A8 */
    "L\0"
    "res\tTR&7CR,L\0"        /* 0x2B5 */
    "dec GLV++R\n"           /* 0x2C2 */
    "L\0"
    "add GL,GR\n"            /* 0x2CF */
    "L\0"
    "bit 7,~+3L\0"           /* 0x2DB */
    "bit 7,~+1L\0"           /* 0x2E6 */
    "jp U2f\n"               /* 0x2F1 */
    "U0:"
};

char stab4[] = {
    "ld XN,G00L\0"           /* 0x0 */
    "dec GLV++R\0"           /* 0xB */
    "ld XN,G10L\0"           /* 0x16 */
    "inc LV--R\0"            /* 0x21 */
    "ld XN,G0L\0"            /* 0x2B */
    "dec LV++R\0"            /* 0x35 */
    "dec LV--R\0"            /* 0x3F */
    "ld (L),GR\0"            /* 0x49 */
    "ld (L),XN\0"            /* 0x53 */
    "ld XN,(L)\0"            /* 0x5D */
    "add GL,GR\0"            /* 0x67 */
    "ld L,(R)\0"             /* 0x71 */
    "add L,GR\0"             /* 0x7A */
    "ld (L),R\0"             /* 0x83 */
    "ON a,R\n"               /* 0x8C */
    "L\0"
    "ld XN,GL\0"             /* 0x95 */
    "ex de,hl\0"             /* 0x9E */
    "ld L,VR\0"              /* 0xA7 */
    "ld hl,0\0"              /* 0xAF */
    ".low.VN\0"              /* 0xB7 */
    "ld L,GR\0"              /* 0xBF */
    "ld L,XN\0"              /* 0xC7 */
    "ld XN,L\0"              /* 0xCF */
    "push GL\0"              /* 0xD7 */
    "push hl\0"              /* 0xDF */
    "G00L;GL\0"              /* 0xE7 */
    "ld a,GL\0"              /* 0xEF */
    "G0L;GL\0"               /* 0xF7 */
    "ld L,R\0"               /* 0xFE */
    "ON R\n"                 /* 0x105 */
    "L\0"
    "push L\0"               /* 0x10C */
    "defw L\0"               /* 0x113 */
    "ON a,R\0"               /* 0x11A */
    "deff L\0"               /* 0x121 */
    "defb L\0"               /* 0x128 */
    "jp L,R\0"               /* 0x12F */
    "X111N\0"                /* 0x136 */
    "or GL\0"                /* 0x13C */
    "indir\0"                /* 0x142 */
    "XN+SR\0"                /* 0x148 */
    "VL9f\0"                 /* 0x14E */
    "ALON\0"                 /* 0x153 */
    "cp R\0"                 /* 0x158 */
    "jp L\0"                 /* 0x15D */
    "L+VR\0"                 /* 0x162 */
    "ON R\0"                 /* 0x167 */
    "X11N\0"                 /* 0x16C */
    "sub\0"                  /* 0x171 */
    "inc\0"                  /* 0x175 */
    "add\0"                  /* 0x179 */
    "cpl\0"                  /* 0x17D */
    "neg\0"                  /* 0x181 */
    "mul\0"                  /* 0x185 */
    "and\0"                  /* 0x189 */
    "mod\0"                  /* 0x18D */
    "G1L\0"                  /* 0x191 */
    "L+0\0"                  /* 0x195 */
    "eFN\0"                  /* 0x199 */
    "L+R\0"                  /* 0x19D */
    "xor\0"                  /* 0x1A1 */
    "div\0"                  /* 0x1A5 */
    "dec\0"                  /* 0x1A9 */
    "VL9\0"                  /* 0x1AD */
    "lVN\0"                  /* 0x1B1 */
    "ZN\0"                   /* 0x1B5 */
    "L:\0"                   /* 0x1B8 */
    "nz\0"                   /* 0x1BB */
    "SN\0"                   /* 0x1BE */
    "-1\0"                   /* 0x1C1 */
    "ge\0"                   /* 0x1C4 */
    "lt\0"                   /* 0x1C7 */
    "2\0"                    /* 0x1CA */
    "4"                    /* 0x1CC */
};



uint16_t dopetab[72] = {
    /* array_A7C0 */
    0x000C, /*  0000 0000 0000 1100	 0  0	""      NULSTR		*/
    0x0227, /*  0000 0010 0010 0111	 1  1	"!"	NOT 		*/
    0x0468, /*  0000 0100 0110 1000	 2  2	"!="    NEQL	EQUOP	*/
    0x0014, /*  0000 0000 0001 0100	 3  3	"#"     HASHSIGN	*/
    0x4208, /*  0100 0010 0000 1000	 4  4	"$"     DOLLAR		*/
    0x4004, /*  0100 0010 0000 1000	 5  5	"$U"    DOLLARU		*/
    8,      /*  0000 0000 0000 1000	 6  6	"%"    -MOD 		*/
    0x2848, /*  0010 1000 0100 1000	 7  7	"&"    -BAND	BITWOP	*/
    0x4328, /*  0100 0011 0010 1000	 8  8	"&&"	LAND 	LOGICOP	*/
    4,      /*  0000 0000 0000 0100	 9  9	"&U"    GADDR		*/
    0x4008, /*  0100 0000 0000 1000	10  A	"("	LPAREN 		*/
    0x4004, /*  0100 0000 0000 0100	11  B	")"	RPAREN		*/
    0x2048, /*  0010 0000 0100 1000	12  C	"*"    +MUL   	ARITMOP */
    0x1004, /*  0001 0000 0000 0100	13  D	"*U"    MULU		*/
    0x2C48, /*  0010 1100 0100 1000	14  E	"+"    -ADD   	ARITMOP */
    8,      /*  0000 0000 0000 1000	15  F	"++" 	INCR   		*/
    4,      /*  0000 0000 0000 0100	16 10	"+U"    PLUSU		*/
    8,      /*  0000 0000 0000 1000	17 11	","     COMMA		*/
    0x0C08, /*  0000 1100 0000 1000	18 12	"-"    -SUB   	ARITMOP */
    8,      /*  0000 0000 0000 1000	19 13	"--" 	DECR   		*/
    0x0208, /*  0000 0010 0000 1000	20 14	"->"    TCAST		*/
    0x0C07, /*  0000 1100 0000 0111	21 15	"-U"    MINUSU		*/
    8,      /*  0000 0000 0000 1000	22 16	"."     DOT		*/
    0x0030, /*  0000 0000 0011 0000	23 17	".."    TDOT		*/
    8,      /*  0000 0000 0000 1000	24 18	"/"    -DIV	ARITMOP */
    0x4008, /*  0100 0000 0000 1000	25 19	":"     COLON		*/
    0x4004, /*  0100 0010 0000 1000	26 1A	":U"    COLONU		*/
    0x4004, /*  0100 0010 0000 1000	27 1B	":s"    COLONS		*/
    0x4108, /*  0100 0001 0000 1000	28 1C	";"     SCOLON		*/
    0x000C, /*  0000 0000 0000 1100	29 1D	";;"    TSCOLON		*/
    0x0428, /*  0000 0100 0010 1000	30 1E	"<"     LT	RELOP	*/
    0x0C88, /*  0000 1100 1000 1000	31 1F	"<<"   -LSHIFT  SHIFTOP	*/
    0x0428, /*  0000 0100 0010 1000	32 20	"<="  	LEQ  	RELOP	*/
    8,      /*  0000 0000 0000 1000	33 21	"="   	ASSIGN		*/
    0x0408, /*  0000 0100 0000 1000	34 22	"=%"  	ASMOD		*/
    0x0C08, /*  0000 1100 0000 1000	35 23	"=&"  	ASAND		*/
    0x0C08, /*  0000 1100 0000 1000	36 24	"=*"  	ASMUL		*/
    0x0C08, /*  0000 1100 0000 1000	37 25	"=+"  	ASADD		*/
    0x0C08, /*  0000 1100 0000 1000	38 26	"=-"  	ASSUB		*/
    8,      /*  0000 0000 0000 1000	39 27	"=/"  	ASDIV		*/
    0x0C88, /*  0000 1100 1000 1000	40 28	"=<<" 	ASLSHIFT	*/
    0x0468, /*  0000 0100 0110 1000	41 29	"=="  	EQL  	EQUOP	*/
    0x0088, /*  0000 0000 1000 1000	42 2A	"=>>" 	ASRSHIFT	*/
    0x0C08, /*  0000 1100 0000 1000	43 2B	"=^"  	ASEXOR		*/
    0x0C08, /*  0000 1100 0000 1000	44 2C	"=|"  	ASEOR		*/
    0x0428, /*  0000 0100 0010 1000	45 2D	">"   	GT  	RELOP	*/
    0x0428, /*  0000 0100 0010 1000	46 2E	">="  	GEQ	RELOP	*/
    0x0088, /*  0000 0000 1000 1000	47 2F	">>"   -RSHIFT  SHIFTOP	*/
    0x4308, /*  0100 0011 0000 1000	48 30	"?"     QUEST		*/
    0x4004, /*  0100 0010 0000 1000	49 31	"@"     ATGIGN		*/

    0x000C, /*  0000 0000 0000 1100	50 32	"[\\"   CASE		*/
    0x000C, /*  0000 0000 0000 1100	51 33	"[a"    UNKNOWN		*/
    0x000C, /*  0000 0000 0000 1100	52 34	"[c"    ENUM		*/
    0x000C, /*  0000 0000 0000 1100	53 35	"[e"    EXPR		*/
    0x000C, /*  0000 0000 0000 1100	54 36	"[i"    INIT		*/
    0x000C, /*  0000 0000 0000 1100	55 37	"[s"    STRUCT		*/
    0x000C, /*  0000 0000 0000 1100	56 38	"[u"    UNION		*/

    0x000C, /*  0000 0000 0000 1100	57 39	"[v"    		*/
    0x2848, /*  0010 1000 0100 1000	58 3A	"^"    -BXOR   	BITWOP	*/
    0x000C, /*  0000 0000 0000 1100	59 3B	"{"     LBRACE		*/
    0x2848, /*  0010 1000 0100 1000	60 3C	"|"    -BOR	BITWOP	*/
    0x4328, /*  0100 0011 0010 1000	61 3D	"||" 	LOR   	LOGICOP	*/
    0x000C, /*  0000 0000 0000 1100	62 3E	"}"     RBRACE		*/
    0x0C07, /*  0000 1100 0000 0111	63 3F	"~"  	BNOT	BITWOP	*/
    4,      /*  0000 0000 0000 0100	64 40	"RECIP"	   		*/
    0,      /*  0000 0000 0000 0000	65 41	"TYPE"     		*/
    0x1002, /*  0001 0000 0000 0010	66 42	"ID"	   		*/
    0x0010, /*  0000 0000 0001 0000	67 43	"CONST"    		*/
    3,      /*  0000 0000 0000 0011	68 44	"FCONST"   		*/
    2,      /*  0000 0000 0000 0010	69 45	"REG"      		*/
    0x4004, /*  0100 0010 0000 1000	70 46	"INAREG"   		*/
    4       /*  0000 0000 0000 0100	71 47	"BITFIELD" 		*/
};


char *regNames[] = {
    "", "a", "c", "b", "e", "d", "l", "h", "ix", "iy", "sp", "af", "bc", "de", "hl"
};

/* clang-format off */
int registerMaskById[]     = { 0,     1,    2,    4,    8,    0x10, 0x20, 0x40, 0x80, 0x100,    /* 0-9 */
                         0x200, 1,    6,    0x18, 0x60, 0x78, 0x66, 0x7E, 0x7F, 0,        /* 10-19 */
                         0x79,  0x61, 0x19, 7,    0x7E, 0x1E, 0x3F, 0x3E, 0x7F, 0x1E };   /* 20-29 */

uint8_t registerAliasBySuffix[] = { 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
                         0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
                         0,  0,  1,  0,  2,  3,  4,  5,  6, 7,   
                         13, 14, 12, 14, 12, 15, 1,  17, 0, 0,
                         15, 1,  14, 1,  13, 1,  12, 1 };

uint8_t array_AB54[] = { 14, 13, 12, 0, 0, 0,         /* groups of 6 bytes, each is index into registerMaskById */
                         13, 12, 0,  0, 0, 0,
                         1,  4,  5,  2, 3, 6,
                         4,  5,  2,  3, 6, 0,
                         21, 22, 23, 0, 0, 0,
                         12, 13, 0,  0, 0, 0 };
/* clang-format on */

/* end of file data.c */
/*
 * File - lex1u.c
 */

/* clang-format on */

/* offsets into character array below */
static int16_t array_987D[] = { 0,     0,     4,     9,     0x0A,  0x0C,  0x0E,  0x1C,  0x2D,
                                0x31,  0x3E,  0x52,  0x54,  0x62,  0x7C,  0x8E,  0x0A0, 0x0A1,
                                0x0A3, 0x0B3, 0x0C3, 0x0D7, 0x0E7, 0x0E8, 0x0EB, 0x0F9, 0x0FB,
                                0x0FD, 0x10B, 0x119, 0x11A, 0x11F, 0x12F, 0x130, 0x147, 0x155,
                                0x165, 0x173, 0x18B, 0x19B, 0x1A9, 0x1B9, 0x1BE, 0x1CE, 0x1DE,
                                0x1EE, 0x1EF, 0x1F4, 0x204, 0x214, 0x216, 0x217, 0x218, 0x219,
                                0x21A, 0x21B, 0x21C, 0x21D, 0x21E, 0x22E, 0x22F, 0x23F, 0x243,
                                0x244, 0x254, 0x255, 0x256, 0x26F, 0x28D, 0x2A6, 0x2B6, 0x2B8 };

static uint8_t array_990D[] = {
    "Qhi\0"                           /* [0 or 1] 000h */
    "PQhi\0"                          /* [2] 004h */
    "\0"                              /* [3] 009h */
    "H\0"                             /* [4] 00Ah */
    "H\0"                             /* [5] 00Ch */
    "HNSTZ]^_djprs\0"                 /* [6] 00Eh */
    "HNSTUVZ]^_dgjprs\0"              /* [7] 01Ch */
    "Qhi\0"                           /* [8] 02Dh */
    "HNTYZ]^djprs\0"                  /* [9] 031h */
    "HNRSTUVZ[]^_`djnprs\0"           /* [10] 03Eh */
    "H\0"                             /* [11] 052h */
    "HNSTZ]^_djprs\0"                 /* [12] 054h */
    "HIMNRSTUVZ[\\]^_`abcdfjprs\0"    /* [13] 062h */
    "HNSTUVYZ]^_djprsw\0"             /* [14] 07Ch */
    "HNSTUVZ]^_djklprs\0"             /* [15] 08Eh */
    "\0"                              /* [16] 0A0h */
    "N\0"                             /* [17] 0A1h */
    "HNSTUVZ]^_djprs\0"               /* [18] 0A3h */
    "HNSTUVZ]^_djprs\0"               /* [19] 0B3h */
    "HNRSTUVYZ[]^_`djprs\0"           /* [20] 0C3h */
    "HNSTUVZ]^_djprs\0"               /* [21] 0D7h */
    "\0"                              /* [22] 0E7h */
    "Nt\0"                            /* [23] 0E8h */
    "HNSTZ]^_djprs\0"                 /* [24] 0EBh */
    "m\0"                             /* [25] 0F9h */
    "H\0"                             /* [26] 0FBh */
    "HNOTYZ]^djprs\0"                 /* [27] 0FDh */
    "HNTUVZ]^djprs\0"                 /* [28] 10Bh */
    "\0"                              /* [29] 119h */
    "PQhi\0"                          /* [30] 11Ah */
    "HNSTUVZ]^_djprs\0"               /* [31] 11Fh */
    "\0"                              /* [32] 12Fh */
    "HNRSTUVWZ[]^_`cdfjprsw\0"        /* [33] 130h */
    "HNSTZ]^_djprs\0"                 /* [34] 147h */
    "HNSTUVZ]^_djprs\0"               /* [35] 155h */
    "HNSTZ]^_djprs\0"                 /* [36] 165h */
    "HINSTUVWZ]^_abcdfjprsvw\0"       /* [37] 173h */
    "HNSTUVZ]^_djprs\0"               /* [38] 18Bh */
    "HNSTZ]^_djprs\0"                 /* [39] 19Bh */
    "HNSTUVZ]^_djprs\0"               /* [40] 1A9h */
    "PQhi\0"                          /* [41] 1B9h */
    "HNSTUVZ]^_djprs\0"               /* [42] 1BEh */
    "HNSTUVZ]^_djprs\0"               /* [43] 1CEh */
    "HNSTUVZ]^_djprs\0"               /* [44] 1DEh */
    "\0"                              /* [45] 1EEh */
    "PQhi\0"                          /* [46] 1EFh */
    "HNSTUVZ]^_djprs\0"               /* [47] 1F4h */
    "HNSTUVZ]^_djprs\0"               /* [48] 204h */
    "H\0"                             /* [49] 214h */
    "\0"                              /* [50] 216h */
    "\0"                              /* [51] 217h */
    "\0"                              /* [52] 218h */
    "\0"                              /* [53] 219h */
    "\0"                              /* [54] 21Ah */
    "\0"                              /* [55] 21Bh */
    "\0"                              /* [56] 21Ch */
    "\0"                              /* [57] 21Dh */
    "HNSTUVZ]^_djprs\0"               /* [58] 21Eh */
    "\0"                              /* [59] 22Eh */
    "HNSTUVZ]^_djprs\0"               /* [60] 22Fh */
    "Qhi\0"                           /* [61] 23Fh */
    "\0"                              /* [62] 243h */
    "HNSTUVZ]^_djprs\0"               /* [63] 244h */
    "\0"                              /* [64] 254h */
    "\0"                              /* [65] 255h */
    "HMNORSTUVZ[\\]^_`acdfjprs\0"     /* [66] 256h */
    "HIJKLNOSTUVYZ]^_abcdfjopqrsux\0" /* [67] 26Fh */
    "HMNRSTUVXZ[\\]^_`acdfjprs\0"     /* [68] 28Dh */
    "HNTWZ]^cdfjprsw\0"               /* [69] 2A6h */
    "H\0"                             /* [70] 2B6h */
    "HNTZ]^cdefjprs"                  /* [71] 2B8h */
};

static int16_t array_9BD4[] = {
    -66,  -65,  -68,  0,    89,   -69,  -65,  -68,  0,    0,    1,    0,    -8,   0,    3,
    62,   -221, 141,  -167, 231,  251,  -151, 264,  -70,  -106, 276,  -100, 0,    5,    64,
    -221, 141,  -90,  163,  170,  234,  251,  -151, 264,  -63,  -70,  274,  278,  -100, 0,
    -64,  -65,  -68,  0,    -28,  -47,  141,  -33,  172,  239,  251,  264,  -70,  -106, -102,
    -100, 0,    8,    68,   -245, -215, 141,  -84,  163,  174,  -250, 234,  251,  -151, -243,
    264,  -70,  -98,  274,  278,  -100, 0,    13,   0,    3,    62,   -221, 141,  -167, 231,
    251,  -151, 264,  -70,  -106, 276,  -100, 0,    9,    58,

    60,   68,   116,  118,  141,  143,  163,  176,  229,  -111, 241,  251,  -151, 253,  255,
    257,  259,  264,  266,  -70,  274,  278,  -100, 0,    5,    64,   121,  141,  -89,  163,
    -36,  182,  234,  251,  -151, 264,  -70,  274,  278,  -100, 283,  0,    18,   64,   -220,
    141,  147,  163,  187,  234,  251,  -151, 264,  -70,  -141, -137, 274,  278,  -100, 0,
    0,    -49,  0,    5,    64,   -221, 141,  -90,  163,  -197, 234,  251,  -151, 264,  -70,
    274,  278,  -100, 0,    23,   64,   -220, 141,  147,  163,  189,  234,  251,  -151, 264,
    -70,  274,  278,  -100, 0,    9,    68,   -245, 123,  141,

    149,  163,  -35,  191,  -251, 234,  251,  -151, -243, 264,  -70,  274,  278,  -100, 0,
    5,    64,   132,  141,  -96,  163,  -202, 234,  251,  -151, 264,  -70,  274,  278,  -100,
    0,    0,    -50,  -114, 0,    3,    62,   -221, 141,  -167, 231,  251,  -151, 264,  -70,
    -106, 276,  -100, 0,    -99,  0,    -16,  0,    -28,  -47,  -148, 141,  -32,  -161, 239,
    251,  264,  -70,  -106, -102, -100, 0,    27,   73,   141,  -74,  163,  -164, 247,  251,
    264,  -70,  274,  279,  -100, 0,    0,    102,  -69,  -65,  -68,  0,    5,    64,   -223,
    141,  155,  163,  200,  234,  251,  -151, 264,  -70,  274,

    278,  -100, 0,    0,    30,   76,   -245, 134,  141,  157,  163,  165,  202,  -247, 234,
    251,  -151, -243, -54,  264,  269,  -70,  274,  278,  -100, -139, 0,    3,    62,   -219,
    141,  -166, 231,  251,  -151, 264,  -70,  -106, 276,  -100, 0,    38,   64,   -219, 141,
    -92,  163,  209,  234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    3,    62,   -219,
    141,  -166, 231,  251,  -151, 264,  -70,  -106, 276,  -100, 0,    42,   -238, 82,   137,
    141,  159,  163,  168,  211,  241,  251,  -151, -51,  -152, 262,  264,  271,  -70,  274,
    278,  -100, 281,  -139, 0,    23,   64,   -219, 141,  -92,

    163,  217,  234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    3,    62,   -219, 141,
    -166, 231,  251,  -151, 264,  -70,  -106, 276,  -100, 0,    5,    64,   -222, 141,  161,
    163,  -170, 234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    89,   -69,  -65,  -68,
    0,    5,    64,   -222, 141,  161,  163,  -170, 234,  251,  -151, 264,  -70,  274,  278,
    -100, 0,    5,    64,   -219, 141,  -92,  163,  -179, 234,  251,  -151, 264,  -70,  274,
    278,  -100, 0,    48,   64,   -219, 141,  -92,  163,  219,  234,  251,  -151, 264,  -70,
    274,  278,  -100, 0,    0,    109,  -69,  -65,  -68,  0,

    5,    64,   -223, 141,  155,  163,  221,  234,  251,  -151, 264,  -70,  274,  278,  -100,
    0,    5,    64,   -216, 141,  -76,  163,  -160, 234,  251,  -151, 264,  -70,  274,  278,
    -100, 0,    52,   0,    0,    0,    0,    0,    0,    0,    0,    0,    5,    64,   -221,
    141,  -90,  163,  -178, 234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    0,    5,
    64,   -221, 141,  -90,  163,  223,  234,  251,  -151, 264,  -70,  274,  278,  -100, 0,
    -67,  -65,  -68,  0,    0,    5,    64,   -227, 141,  -95,  163,  -202, 234,  251,  -151,
    264,  -70,  274,  278,  -100, 0,    0,    0,    9,    -133,

    68,   -149, -245, -212, 141,  -97,  163,  225,  -248, -112, 234,  251,  -151, -243, -52,
    -53,  264,  -61,  -70,  274,  278,  -100, 0,    5,    -237, -104, -252, -242, 64,   -150,
    139,  141,  -73,  163,  -34,  227,  241,  251,  -151, -51,  -152, -55,  264,  272,  -70,
    -241, 274,  -155, 278,  -100, -253, -154, 0,    9,    -133, 68,   -245, -212, 141,  -97,
    163,  -115, 225,  -248, -113, 234,  251,  -151, -243, -52,  -53,  264,  -61,  -70,  274,
    278,  -100, 0,    56,   87,   141,  -142, -165, 239,  251,  -54,  264,  269,  -70,  -106,
    -102, -100, -139, 0,    -18,  0,    -28,  -47,  141,  -158,

    239,  251,  -57,  264,  -62,  -61,  -70,  -106, -102, -100, 0
};

/*********************************************************
 * sub_13D	Ok++ PMO		Used in: selectCodePattern
 * This function wasn't optimised in original code hence
 * it is split out separately
 *********************************************************/
int lookupPatternRule(int a, int b) {
    int regIdx;

    for (regIdx = array_987D[b]; array_990D[regIdx] != 0 && array_990D[regIdx] != a; regIdx++)
        ;
    return array_9BD4[regIdx];
}

/* end of file lex1u.c */
/*
 * File - lex2.c
 */

/*********************************************************
 * char sub_1B2 OK++ PMO	       Used in: sub_6D1, sub_4192
 *
 * Token search		(Binary search algorithm is used)
 *********************************************************/
int lookupTokenId(register char *target) {
    uint8_t hi, lo, mid;
    int cmp;

    /* clang-format off */
    static char *tnames[] = {
        "",    "!",  "!=",  "#",  "$",  "$U", "%",  "&",  "&&", "&U",
        "(",   ")",  "*",   "*U", "+",  "++", "+U", ",",  "-",  "--",
        "->",  "-U", ".",   "..", "/",  ":",  ":U", ":s", ";",  ";;",
        "<",   "<<", "<=",  "=",  "=%", "=&", "=*", "=+", "=-", "=/",
        "=<<", "==", "=>>", "=^", "=|", ">",  ">=", ">>", "?",  "@",
        "[\\", "[a", "[c",  "[e", "[i", "[s", "[u", "[v", "^",  "{",
        "|",   "||", "}",   "~", "RECIP", "TYPE",
        "ID", "CONST", "FCONST", "REG", "INAREG", "BITFIELD"
    };
    /* clang-format on */

    static char lastTok = 65;

    lo                  = 0;
    hi                  = lastTok;
    do {
        mid = (hi + lo) / 2;
        if ((cmp = strcmp(target, tnames[mid])) == 0)
            return mid;
        if (cmp < 0)
            hi = mid - 1;
        else
            lo = mid + 1;
    } while (hi >= lo);
    return (-1); /* Search terminates as unsuccessful */
}

/*********************************************************
 * gethashptr OK++ PMO		Used in: getOrCreateSymbol, getOrCreateScopedSymbol
 *
 * Convert name to a hash table ptr (sub_21F)
 *
 * Returns pointer to pointer to structure associated with
 * pointer to token.  for example
 *
 * Input	Hash key  Destination
 * string  	dec hex
 *   "f"  	 1	- float
 *   "i"  	 4	- int
 *   "l"  	 7	- long
 *   "s"  	14 0eh	- short
 *   "v"  	17 11h	- void
 *   "x"  	19 13h	- x ?
 *   "uc" 	30 1eh	- uint8_t
 *   "ui" 	36 24h	- uint16_t
 *   "ul" 	39 27h	- uint32_t
 *   "us" 	46 2eh	- uint16_t short
 *   "ux" 	51 33h	- uint16_t ?
 *   "b"  	98 62h	- b ?
 *   "c"  	99 63h	- char
 **********************************************************/

#define HASHTABSIZE 101

member_t **gethashptr(register char *str) {
    uint16_t key;

    /* calculate hash */
    for (key = 0; *str; str++)
        key = key * 2 + *(uint8_t *)str;

    /* Hash table index is determined by    */
    /* hash function using division method  */
    return &hashtab[key % HASHTABSIZE];
}

/*********************************************************
 * sub_265 OK++ PMO	     Used in: parseTypeWithIndirection,  sub_B19,  sub_E43,
 *			      initializeTypesAndSymbols, getOrCreateScopedSymbol, sub_4192
 *
 * Return pointer to struct associated with pointer to token
 *********************************************************/
member_t *getOrCreateSymbol(char *str) {
    member_t **l1b;
    register member_t *sb;

    /* In hash table, we look for pointer to    */
    l1b = gethashptr(str); /* entry in symbol table associated with    */
    /* scan for the matching name on the hash list */
    for (sb = *l1b; sb; sb = sb->hashNext)
        if (strcmp(sb->name, str) == 0)
            return sb;
    /* not found so create new record & insert at head of list */
    sb         = allocMem(sizeof(member_t)); /* 22 bytes */
    sb->hashNext = *l1b;
    sb->name = allocMem(strlen(str) + 1); /* effectively strdup */
    strcpy(sb->name, str);
    sb->nestDepth = (uint8_t)nstdpth;
    *l1b        = sb;

    return sb; /* position and return pointer to record.   */
}

/*********************************************************
 * sub_306 v1 OK++ PMO    Used in: sub_6D1,  sub_793,  sub_B19,
 *			      sub_E43,  sub_17E0, sub_19C1,
 *			      sub_4192
 * get_token
 * Optimiser one basic blocked moved between original code
 *  and new code. Behaviour unchanged
 *********************************************************/
char *getToken() {
    int ch, expectName;
    register char *ptr;
    static char buffer[MAXBUF];

    expectName = false;
    for (;;) {
        ptr = buffer;

        while ((ch = fgetchar()) != EOF && isspace(ch))
            ;
        if (ch == EOF)
            return (char *)~0;
        *ptr++ = ch;
        do {
            *ptr++ = ch = fgetchar();
        } while (ch != EOF && !isspace(ch));
        *--ptr = 0;
        if (buffer[0] == '"') {
            lineno     = atoi(buffer + 1);
            expectName = ch != '\n';
        } else if (expectName) {
// GCC moans about truncating the string, which is what we actually want
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-truncation"
#endif
            strncpy(progname, buffer, sizeof(progname) - 1);
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
            expectName = false;
        } else if (buffer[0] == ';' && buffer[1] == ';') {
            do {
                fputchar(ch = fgetchar());
            } while (ch != '\n');
        } else
            return buffer;
    }
}

/*********************************************************
 * sub_406 v3 OK++ PMO			 Used in: sub_6D1
 *
 * Notes:
 *   Added 0 parameter to allocateOrEmitVariable function call to
 *   match number and types actual and formal parameters
 *   this function.
 *   Modified code to get sb->hashNext before freeing sb
 *   Other than code changes to handle the above, the code is identical
 *********************************************************/
/* remove and free up items which have got out of scope */

void leaveBlock() {
    member_t **pHashEntry;
    int l2;
    member_t *newlist;
    member_t *next;
    member_t **l5;
    int l6;
    register member_t *sb;

    l2         = HASHTABSIZE;
    pHashEntry = hashtab;
    do {
        newlist = 0;
        /* note with the fixed handling of free, this could be converted to a for loop */
        sb = *pHashEntry;
        while (sb && sb->nestDepth == nstdpth) {
            if (sb->symKind == VAR) {
                if (sb->StorageClass == 2)
                    word_B017 |= registerMaskById[sb->payload.regIdx];
                if (sb->StorageClass == 4 || sb->StorageClass == 3)
                    allocateOrEmitVariable(sb, 0); /* Add parameter 0! */
                if (0 < nstdpth && sb->StorageClass == 3) {
                    next       = sb->hashNext;
                    sb->hashNext = newlist;
                    newlist    = sb;
                    sb->nestDepth--;
                    sb = next;
                    continue;
                }
            }

            free(sb->name);

            if (sb->symKind == UNION || sb->symKind == STRUCT) {
                l6 = sb->payload.memberList->cnt;
                l5 = sb->payload.memberList->vals;
                while (l6-- != 0)
                    free(*l5++);
                free(sb->payload.memberList);
            }
            /*  code modified to get sb->hashNext before freeing sb !!!*/
            next = sb->hashNext;
            free(sb);
            /* sb = sb->hashNext original code relied on hashNext not being at start of block !!!*/
            sb = next;
        }
        if (newlist) {                 /* if l3b list exists add to end */
            *(pHashEntry++) = newlist; /* set hash table to the l3b list */
            while (newlist->hashNext)
                newlist = newlist->hashNext; /* m14: */
            newlist->hashNext = sb;
        } else
            *(pHashEntry++) = sb; /* else initialise hash table entry with new item  */
    } while (--l2 != 0);

    nstdpth--;
    if (lvlidx >= 0) {
        if (array_AE57[lvlidx] == nstdpth) {
            sb = array_AEDB[lvlidx];
            if (sb->typeDesc->symKind == STRUCT && (sb->indirFlags & 4) == 0)
                emitStructCopy(sb->offset, sb->typeSize);
            prFrameTail(sb->offset, array_AE13[lvlidx]);
            lvlidx--;
            word_B017 = 0x17F;
        }
    }
}

/*********************************************************
 * sub_627 OK++ PMO     Used in: sub_17E0, sub_19C1, sub_4192
 *********************************************************/
/* encode the accessor prefix */
member_t *parseTypeWithIndirection(register char *ch, uint16_t *par) {
    uint16_t loc;

    loc = 0;
    ch++;
    do {
        loc <<= 2;
        if (*ch == '(') {
            loc |= 2;
            ch++;
        } else if (*ch == '*') {
            loc |= 1;
            ch++;
        }
    } while (!isalnum(*ch) && *ch != '_');
    /* invert them */
    *par = 0;
    while (loc != 0) {
        *par <<= 2;
        *par |= (loc & 3);
        loc >>= 2;
    }
    return getOrCreateSymbol(ch);
}

/*********************************************************
 * sub_6C8 OK++ PMO			Used in: sub_6D1, expect
 *********************************************************/
void badIntCode() {

    fatalErr("Bad int. code");
}

/*********************************************************
 * sub_6D1 OK++				    Used in: main
 *
 * Compiling intermediate code
 *
 * note optimiser uses hl in jmp table calculations
 * then exchanges with de. The original code uses de
 * the effect is the same and the rest of the code is identical
 *********************************************************/
void parseStmt() {
    register char *ch;
    int tok;

    word_B017 = 0x17F;
    while ((ch = getToken()) != (char *)~0) { /* get_token    */
        tok = lookupTokenId(ch);
        switch (tok) { /* search_token */
        case LBRACE:   /* "{" opening block */
            nstdpth++; /* Increase the current nesting depth */
            break;
        case RBRACE: /* "}" end of block 	*/
            leaveBlock();
            break;
        case EXPR: /* "[e" expression	*/
            prPsect(P_TEXT);
            compileExpression(parseExpr());
            expect(']');
            break;
        case VAR: /* "[v" variable	*/
            parseVariable();
            break;
        case STRUCT: /* "[s" struct	*/
        case UNION:  /* "[u" union	*/
            parseMembers(tok);
            break;
        case CASE: /* "[\\" */
            parseSwitch();
            break;
        case ENUM: /* "[c" enum		*/
            parseEnum();
            break;
        case INIT: /* "[i" initialization	*/
            parseInit();
            break;
        case UNKNOWN: /* "[a" 		*/
            parseData();
            break;
        case BXOR: /* "^" */
        case BOR:  /* "|" */
        case LOR:  /* "||" */
        default:
            badIntCode();
        }
    }
    leaveBlock();
}

/*********************************************************
 * sub_76F OK	      Used in: sub_6D1,  sub_B19, sub_E43,
 * 			       sub_17E0, sub_1B0C
 ;
 * Search for expected character (closing square bracket)
 *********************************************************/
void expect(char par) {
    char ch;

    do {
        ch = fgetchar();
    } while (isspace(ch)); /* Skip white-space characters */

    if (ch != par)
        badIntCode();
}

/*********************************************************
 * sub_793 OK++ 			 Used in: sub_6D1
 * minor variance in code as makeOpNode the first parameter
 * is explicitly declared uint8_t, rather than the default int
 *********************************************************/
void parseData() {
    char *loc1;
    char buf[1024];
    register char *ptr;

    prPsect(P_DATA);
    generateCodeForExpr(optimizeExpression(makeOpNode(COLON_U, makeOpNode(COLON_S, parseExpr(), 0), 0)));
    ptr = buf;
    for (;;) {
        if (*(loc1 = getToken()) == ']') /* parse non-terminating tokens */
            break;
        *ptr = atoi(loc1); /* Convert string to int value and place it in buffer */
        ptr++;
    }

    prDefb(buf, (int)(ptr - buf)); /* Emit data "defb byte1, ..." ("ptr-buf" bytes from "buf")*/
}
/* end of lex2.c */
/*
 * File - code.c
 */
/*********************************************************
 * sub_808 OK++ PMO				 Used in: sub_B19
 * code identical except for where the original code had
 * l = l4b->bitOffset immediately followed
 * by hl = 0. The useless l = l4b->b-b6 code is no longer there
 * Note there appears to be a problem with hitech code generation
 * around << of a long value
 * if the rhs is uint8_t then the calculation is done incorrectly
 *
 *********************************************************/

int emitInitializerData(register member_t *sb, node_t *p2a) {
    int16_t l1;
    int16_t l2;
    member_t *l3b;
    member_t *l4b;
    int l5;
    node_t *l6a FORCEINIT; // 

    l1 = 0;
    if (p2a->op == COLON_U) {
        freeNodeTree(p2a);
        l5 = 0;
        if (sb->symKind == STRUCT) {
            l3b = sb;
            while ((p2a = parseExpr())->op != DOT_DOT) {
                if ((l2 = getTypeAlignment(l4b = l3b->payload.memberList->vals[l5++])) != 0 && l1 % ++l2 != 0) {
                    l2 -= l1 % l2;
                    l1 += l2;
                    prDefb0s(l2); /* emit defb 0 to pad to item boundary */
                }
                if (l4b->storageFlags & 0x10) {
                    p2a = makeOpNode(BAND, p2a, makeConstNode((1L << (int8_t)(l4b->bitWidth)) - 1L));
                    if (l4b->bitOffset != 0)
                        /* PMO: bug fix, replaced 0L arg to makeConstNode with bit offset l4b->bitOffset*/
                        l6a = makeOpNode(BOR, l6a, makeOpNode(LSHIFT, p2a, makeConstNode(l4b->bitOffset)));
                    else
                        l6a = p2a;

                    if (l5 != l3b->payload.memberList->cnt &&
                        (l3b->payload.memberList->vals[l5]->storageFlags & 0x10) &&
                        l3b->payload.memberList->vals[l5]->offset == l4b->offset)
                        continue;
                    p2a = l6a;
                }
                l1 += emitInitializerData(l4b, p2a);
            }

            freeNodeTree(p2a);
        } else {
            l3b = sb->typeDesc;
            for (;;) {
                if ((p2a = parseExpr())->op == COLON_U)
                    l1 += emitInitializerData(l3b, p2a);
                else if (p2a->op == DOT_DOT) {
                    freeNodeTree(p2a);
                    break;
                } else {
                    l1 += nodesize(p2a);
                    generateCodeForExpr(optimizeExpression(makeOpNode(ATGIGN, p2a, 0)));
                }
            }
        }
    } else {
        p2a = optimizeExpression(makeOpNode(ATGIGN, p2a, 0));
        l1  = nodesize(p2a);
        generateCodeForExpr(p2a);
    }
    if (l1 < sb->typeSize) {
        prDefb0s(sb->typeSize - l1);
        l1 = sb->typeSize;
    } else if (sb->typeSize < l1 && sb->typeSize != 0)
        prError("Too many initializers");

    return l1; /* m15: */
}

/*********************************************************
 * sub_B19 OK++	PMO			 Used in: sub_6D1
 *********************************************************/
void parseInit() {
    register member_t *sb;
    int l1;
    int l2;

    sb = getOrCreateSymbol(getToken());
    prPsect(P_DATA);
    emitSymbolLabel(sb); /* Emit "symbolic_name:" (identifier label) */
    l1 = emitInitializerData(sb, parseExpr());
    l2 = sb->indirFlags ? 2 : sb->typeDesc->typeSize;
    if (sb->elemCount == 0) { /* make sure nelem is set */
        sb->elemCount = l1 / l2;
        sb->typeSize  = computeVarSize(sb);
    }
    expect(']');
}

/*********************************************************
 * sub_B96 OK++ PMO				Used in: generateCodeForExpr
 * emit_call_ncsv
 *********************************************************/
void prFrameHead(int fId) {
    static bool frameGlobalsEmitted; /* First call ncsv	   */

    prPsect(P_TEXT);
    if (frameGlobalsEmitted == false) /* if first call	*/
        printf("global\tncsv, cret, indir\n");

    printf("call\tncsv\n");
    frameGlobalsEmitted = true; /* first call is done	*/
    printf("defw\tf%d\n", fId);
}

/*********************************************************
 * sub_BCC OK++ PMO				 Used in: leaveBlock
 *********************************************************/
void prFrameTail(int fId, int fSize) {

    prPsect(P_TEXT);
    printf("jp\tcret\n"
           "f%d\tequ\t%d\n",
           fId, fSize);
}

/*********************************************************
 * sub_BEE OK++ PMO				 Used in: leaveBlock
 *********************************************************/
void emitStructCopy(int kId, int size) {

    prPsect(P_TEXT);
    printf("ld\tde,k%d\n"
           "ld\tbc,%d\n"
           "ldir\n"
           "ld\thl,k%d\n",
           kId, size, kId);
    prPsect(P_BSS);
    printf("k%d:defs\t%d\n", kId, size);
}

/*********************************************************
 * sub_C36 OK++ PMO       Used in: emitBssDefinition, emitSymbolLabel, sub_4192
 *********************************************************/
void prGlobalDef(register member_t *sb) {

    printf("global\t%s\n", sb->name);
    sb->storageFlags |= 2;
}

/*********************************************************
 * sub_C57 OK++ PMO				Used in: allocateOrEmitVariable
 *********************************************************/
void emitBssDefinition(register member_t *sb) {

    if ((sb->storageFlags & 1) == 0 && sb->elemCount != 0 && (sb->indirFlags & 2) == 0) {
        prPsect(P_BSS);
        if (sb->StorageClass == 3 && (sb->storageFlags & 2) == 0)
            prGlobalDef(sb); /* Emit "global name" */
        emitSymbolLabel(sb);         /* Emit "symbolic_name:" (identifier label) */
        printf("\tdefs\t%u\n", sb->typeSize);
    }
}

/*********************************************************
 * sub_CAB OK++ PMO			Used in: sub_B19, emitBssDefinition
 *
 * Emit "symbolic_name:" (identifier label)
 *********************************************************/
void emitSymbolLabel(register member_t *sb) {

    if ((sb->storageFlags & 2) == 0 && sb->StorageClass == 3)
        prGlobalDef(sb); /* Emit "global name" */
    sb->storageFlags |= 1;
    printf("%s:\n", sb->name);
}

/*********************************************************
 * sub_CDF OK++ PMO				 Used in: emitInitializerData
 * Emit "defb 0, ..." (num bytes)
 *********************************************************/
void prDefb0s(int num) {
    char cnt;

    cnt = 0;             /* Reset counter bytes printed	   */
    while (num-- != 0) { /* While data is available	   */
        if (cnt == 0)
            printf("defb\t0"); /* Initially output "defb 0",	   */
        else
            printf(",0");   /* later ",0"			   */
        cnt++;              /* and update number bytes output  */
        if (cnt == 16) {    /* If number bytes in string is 16 */
            cnt = 0;        /* Reset counter and		   */
            fputchar('\n'); /* continue output in next line	   */
        }
    } /* continue processing		   */
    if (cnt != 0)
        fputchar('\n'); /* If line is incomplete, new line */
}

/*********************************************************
 * prPsect OK++ PMO     Used in: sub_6D1,  sub_793,  sub_B19,
 * 			      prFrameHead,  prFrameTail,  emitStructCopy,
 * Select psect		      emitBssDefinition,  sub_E43
 *********************************************************/
void prPsect(int section) {
    static int curPsect;
    static char *psectNames[] = { "", "bss", "text", "data" };

    if (section != curPsect) /* Only when changing section */
        printf("psect\t%s\n", psectNames[curPsect = section]);
}

/*********************************************************
 * sub_D66 OK++ PMO				 Used in: sub_E43
 *
 *********************************************************/
void sortCaseLabels(int *pCase, int *pLabel, int nCase) {
    bool changed;
    int *pl;
    int cnt;
    int tCase;
    int tLabel;
    register int *pc;

    do {
        changed = false;
        pc      = pCase;
        pl      = pLabel;
        for (cnt = nCase; --cnt > 0; pc++, pl++) {
            if (pc[1] < pc[0]) {
                changed = true;
                tCase   = pc[0];
                pc[0]   = pc[1];
                pc[1]   = tCase;
                tLabel  = pl[0];
                pl[0]   = pl[1];
                pl[1]   = tLabel;
            } else if (pc[0] == pc[1]) {
                prError("Duplicate case label");
                return;
            }
        }
    } while (changed != 0);
    return;
}

/*********************************************************
 * sub_E43 OK++	PMO		 Used in: sub_6D1
 * Only minor code differences due to the declaration of
 * functions with char / uint8_t parameters rather than
 * defaulting to int.
 * One other change is where the compiler saves l to the high
 * and low byte, but as the optimiser detected that h and l
 * were both 0 this is not a problem
 *********************************************************/
void parseSwitch() {
    node_t *l1a;
    int codeLabel, swTableLabel, caseRange, caseCnt, defaultCodeLabel;
    int16_t l7, l8;
    bool loTest, hiTest;
    int caseVals[255], codeLabels[255];
    register node_t *sa;

    l1a     = parseExpr();
    caseCnt = 0;
    for (;;) {
        sa        = optimizeExpression(parseExpr());
        codeLabel = atoi(getToken());
        if (sa->op == DOT_DOT) { /* end of switch block */
            defaultCodeLabel = codeLabel;
            freeNode(sa);
            expect(']');
            if (caseCnt != 0)
                break;
            prWarning("No case\tlabels");
            freeNodeTree(l1a);
            printf("jp\tl%d\n", defaultCodeLabel);
            return;
        }
        if (sa->op == CONST) { /* only constants allowed */
            caseVals[caseCnt]     = sa->val.l;
            codeLabels[caseCnt++] = codeLabel;
        } else
            prError("Non-constant case label");
        freeNodeTree(sa);
    }
    sortCaseLabels(caseVals, codeLabels, caseCnt); /* m6:  */
    caseRange = caseVals[caseCnt - 1] - caseVals[0];
    if (0 <= caseRange && caseRange < 16000 &&
        caseRange * 2 + 20 < caseCnt * 5) { /* if jmp table is shorter */
        /* jump table option is smaller so use it
           note the alternative cmp/jp option may be slower
           even if it is shorter
        */
        sa        = allocNode();
        sa->op  = TYPE;
        sa->type    = l1a->type;
        sa->ptrFlags = l1a->ptrFlags;
        sa        = makeOpNode(CONV, makeConstNode(caseVals[0]), sa);
        sa        = makeOpNode(SUB, l1a, sa);
        if (nodesize(sa) != 2) {
            l1a       = allocNode();
            l1a->op = TYPE;
            l1a->type   = getOrCreateSymbol("us");
            sa        = makeOpNode(CONV, sa, l1a);
        }
        prPsect(P_TEXT);
        compileExpression(makeOpNode(RPAREN, sa, 0));
        swTableLabel = newLocal(); /* swTableCnt++ */
        /*
            with the switch value in hl, the code
            emitted is effectively
            ld  a,.high. caseRange
            cp  h
            jp  c,l{defaultCodeLabel}
            jp  nz,1f
            ld  a,.low. caseRange
            cp  l
            jp  c,l{defaultCodeLabel}
         1: add hl,hl
            ld  de,S{swTableLabel}
            ld  a,(hl)
            inc hl
            ld  h,(hl)
            ld  l,a
            jp  (hl)
            where {xxx} indicates the respective label number of xxx
        */
        printf("ld\ta,%u\n"
               "cp\th\n"
               "jp\tc,l%d\n"
               "jp\tnz,1f\n"
               "ld\ta,%u\n"
               "cp\tl\n"
               "jp\tc,l%d\n"
               "1:add\thl,hl\n"
               "ld\tde,S%u\n"
               "add\thl,de\n"
               "ld\ta,(hl)\n"
               "inc\thl\n"
               "ld\th,(hl)\n"
               "ld\tl,a\n"
               "jp\t(hl)\n",
               caseRange >> 8, defaultCodeLabel, caseRange & 0xff, defaultCodeLabel, swTableLabel);
        prPsect(P_DATA);
        printf("S%d:\n", swTableLabel);
        codeLabel = 0;
        caseRange = caseVals[0];
        do {
            if (caseRange == caseVals[codeLabel]) {
                printf("defw\tl%d\n", codeLabels[codeLabel]);
                codeLabel++;
            } else
                printf("defw\tl%d\n", defaultCodeLabel); /* fill holes with default */

            caseRange++;
        } while (codeLabel < caseCnt);
        return;
    }
    if (nodesize(l1a) == 2) {
        prPsect(P_TEXT);
        compileExpression(makeOpNode(RPAREN, l1a, 0));
        l7 = -1;
        l8 = (int)(loTest = hiTest = false);

        for (codeLabel = 0; codeLabel < caseCnt; codeLabel++) {
            l7 &= caseVals[codeLabel];
            l8 |= caseVals[codeLabel];
            if (l7 >> 8 != l8 >> 8 && (l7 & 0xFF) != (l8 & 0xFF)) {
                if (hiTest | loTest)
                    printf("1:\n"); /* target of previous hi/lo test */
                loTest = hiTest = false;
                l7 = l8 = caseVals[codeLabel];
            }
            if (l7 >> 8 == l8 >> 8) {
                if (!hiTest) {
                    printf("ld\ta,h\n");
                    emitCompareWithA(l7 >> 8);
                    printf("jp\tnz,1f\n"
                           "ld\ta,l\n");
                    hiTest = true;
                }
                caseVals[codeLabel] &= 0xFF;
            } else {
                if (!loTest) { /* m16: */
                    if (hiTest)
                        printf("1:\n");
                    printf("ld\ta,l\n"); /* m17: */
                    emitCompareWithA(l7 & 0xFF);
                    printf("jp\tnz,1f\n"
                           "ld\ta,h\n");
                    loTest = true;
                }
                caseVals[codeLabel] >>= 8;
                caseVals[codeLabel] &= 0xFF;
            }
            emitCompareWithA(caseVals[codeLabel]); /* m19: */
            printf("jp\tz,l%d\n", codeLabels[codeLabel]);
        }
        if (hiTest | loTest)
            printf("1:\n");
        printf("jp\tl%d\n", defaultCodeLabel); /* m21: */
        return;
    }

    prPsect(P_TEXT);
    compileExpression(makeOpNode(INAREG, l1a, 0));
    for (codeLabel = 0; codeLabel < caseCnt; codeLabel++) {
        if (caseVals[codeLabel] < 256 && caseVals[codeLabel] >= -128) {
            emitCompareWithA(caseVals[codeLabel]);
            printf("jp\tz,l%d\n", codeLabels[codeLabel]);
        }
    }
    printf("jp\tl%d\n", defaultCodeLabel);
}

/*********************************************************
 * sub_1420 OK++ PMO			 Used in: sub_E43
 *********************************************************/
void emitCompareWithA(int par) {
    if (par)
        printf("cp\t%d\n", par);
    else
        printf("or\ta\n"); /* if stepIndex == 0 then "or a" */
}

/*********************************************************
 * sub_143F OK++ PMO			Used in: emitTreeCode
 *********************************************************/
void prPush(uint8_t reg) {

    if (reg == REG_DEHL) {
        printf("push\thl\n"
               "push\tde\n");
        return;
    }
    if (reg <= REG_H)
        reg = reg / 2 + REG_AF;
    printf("push\t%s\n", regNames[reg]);
}

/*********************************************************
 * sub_1489 OK++ PMO			Used in: emitTreeCode
 *********************************************************/
void prPop(uint8_t reg) {

    if (reg == REG_DEHL) {
        printf("pop\tde\n"
               "pop\thl\n");
        return;
    }
    if (reg <= REG_H)
        reg = reg / 2 + REG_AF;
    printf("pop\t%s\n", regNames[reg]);
}

/*********************************************************
 * sub_14D3 OK++ PMO			Used in: emitRegisterVarLoads
 *
 * Assigning register "IY" value formal parameter with
 * type register
 *********************************************************/
void prIXnPush(register member_t *sb) {

    printf("ld\tl,(ix+%d)\n"
           "ld\th,(ix+%d)\n"
           "push\thl\n"
           "pop\tiy\n",
           sb->offset, sb->offset + 1);
}

/*********************************************************
 * sub_14F3 OK++ PMO   Used in: emitTypeSuffix, emitCodeTemplate, sub_39CA,
 *			    convertNodeToType, foldConstantExpressions, isPatternApplicable,
 *			    strengthReduceMulDivMod, simplifyConversion, optimizeExpressionTree,
 *			    fitsInTargetType, isSameTypeAndSize, areBothSigned
 *********************************************************/
uint8_t getTypeClass(register node_t *sa) {

    if (sa->ptrFlags & 2)
        return 0;
    if (sa->ptrFlags != 0)
        return 2;
    if (sa->type->elemCount > 1)
        return 0;
    return sa->type->StorageClass;
}

/*********************************************************
 * sub_153A OK++ PMO			Used in: emitCodeTemplate
 *********************************************************/
void emitTypeSuffix(register node_t *sa) {

    static char array_A542[] = { 0, 'a', 'l', 'f' };

    fputchar(array_A542[getTypeClass(sa)]);
}

/*********************************************************
 * sub_155D OK++ PMO			 Used in: sub_793
 *
 * Emit "defb byte1, ..." (from ptr num bytes)
 *********************************************************/
void prDefb(register char *ptr, int num) {
    char cnt;

    cnt = 0;             /* Reset counter bytes printed	   */
    while (num-- != 0) { /* While data is available	   */
        if (cnt == 0)
            printf("defb\t"); /* Initially output "defb",	   */
        else
            fputchar(',');             /* later "," 			   */
        printf("%d", (uint8_t)*ptr++); /* Output byte and advance pointer */
        cnt++;                         /* update number bytes output 	   */
        if (cnt == 16) {               /* max 16 bytes per line */
            fputchar('\n');
            cnt = 0;
        }
    }
    if (cnt != 0)
        fputchar('\n'); /* If line is incomplete, new line */
}

/*********************************************************
 * xx1	 OK++ PMO		Used in: Explicit calls are absent
 *********************************************************/
void prJmpLabel(int p) {
    printf("j%d:\n", p);
}

/*********************************************************
 * xx2	 OK++ PMO		Used in: Explicit calls are absent
 *********************************************************/
void prJump(int p) {
    printf("jp\tj%d\n", p);
}

/*********************************************************
 * sub_15FB OK++ PMO			Used in: sub_1B0C
 *********************************************************/
void setEnumStorageType(register member_t *sb, int p2, int p3) {

    if (p2 >= 0) {
        sb->StorageClass = 2;
        if (p3 <= 255)
            sb->typeSize = 1;
        else
            sb->typeSize = 2;
    } else {
        sb->StorageClass = 1;
        if (p3 <= 127 && p2 >= -128)
            sb->typeSize = 1;
        else
            sb->typeSize = 2;
    }
}

/*********************************************************
 * sub_1659 OK++ PMO			Used in: finalizeStructOrUnionLayout
 * Find maximum between two numbers
 *********************************************************/
int max(int num1, int num2) {
    return (num1 > num2) ? num1 : num2;
}

#define NVARS 14

struct tType {
    char *t_str;
    int t_size;
    int t_alig;
    char t_flag;
};

/*********************************************************
 * sub_1680 OK++ PMO			    Used in: main
 *
 * first_init
 *********************************************************/
void initializeTypesAndSymbols() {
    member_t *sb;
    int16_t cnt;
    register struct tType *tp;

    /*
     *	Initializaion of type pointers
     */
    static struct tType vars[NVARS] = { /* initializeTypesAndSymbols */
                                        { "i", 2, 0, 1 },  { "s", 2, 0, 1 },  { "c", 1, 0, 1 },
                                        { "l", 4, 0, 1 },  { "ui", 2, 0, 2 }, { "us", 2, 0, 2 },
                                        { "uc", 1, 0, 2 }, { "ul", 4, 0, 2 }, { "f", 4, 0, 3 },
                                        { "d", 4, 0, 3 },  { "x", 2, 0, 1 },  { "ux", 2, 0, 2 },
                                        { "b", 0, 0, 0 },  { "v", 0, 0, 0 }
    };

    /* Clear hash table */

    blkclr((char *)hashtab, sizeof(hashtab));

    /* Create a hash table of templates for standard types */

    cnt = NVARS;
    tp  = vars;
    do {
        sb          = getOrCreateSymbol(tp->t_str);
        sb->symKind = TYPE;
        sb->offset   = tp->t_alig;
        sb->typeSize  = tp->t_size;
        sb->StorageClass  = tp->t_flag;
        tp++;
    } while (--cnt != 0);

    /* Additional patterns for types */

    typeLong   = getOrCreateSymbol("l");  /* long	  	*/
    typeDouble = getOrCreateSymbol("d");  /* double 	*/
    typeB      = getOrCreateSymbol("b");  /* b   	  	*/
    typeVar    = getOrCreateSymbol("v");  /* variable 	*/
    typeChar   = getOrCreateSymbol("c");  /* char   	*/
    typeUChar  = getOrCreateSymbol("uc"); /* uint8_t  	*/
    typeX      = getOrCreateSymbol("x");  /* x      	*/
    lvlidx     = -1;
}

/*********************************************************
 * sub_174C OK++ PMO    Used in: sub_E43,  sub_17E0, sub_39CA,
 *			     sub_4192, simplifyConversion
 *********************************************************/
int newLocal() {
    static int localLabelCnt;
    return ++localLabelCnt;
}

/*********************************************************
 * sub_1754 OK++ PMO    Used in: sub_17E0, sub_19C1, sub_1B0C
 *********************************************************/
member_t *getOrCreateScopedSymbol(char *token, uint8_t cls) {
    member_t **l1b;
    register member_t *sb;

    sb = getOrCreateSymbol(token);                          /* Set pointer to struct associated with   */
                                                  /* pointer to token.			   */
    if (sb->nestDepth != nstdpth) {                 /* If nesting depth not correspond current,*/
        l1b        = gethashptr(token);           /* Get pointer to pointer to struct from   */
        sb         = allocMem(sizeof(member_t));  /* hash table. Create new struct and save  */
        sb->hashNext = *l1b;                        /* pointer to struct from hash table in    */
                                                  /* struct as associated with it. 	   */
        *l1b = sb;                                /* Save pointer to this struct in current  */
                                                  /* position hash table.			   */
        sb->name = allocMem(strlen(token) + 1); /* Get memory address allocated for token  */
                                                  /* and assign it to corresponding member.  */
        strcpy(sb->name, token);                /* Copy specified token to this address.   */
        sb->nestDepth = (uint8_t)nstdpth;           /* Save current nesting depth in struct    */
                                                  /*
                                                        if(++symcnt > dynmem)   dynmem = symcnt;
                                                  */
    }
    sb->symKind = cls;
    return sb;
}
/* end of code.c */
/*
 * File - sym1.c
 */
/*********************************************************
 * sub_17E0 OK++ PMO			Used in: sub_6D1, sub_4192
 *
 * Two related Basic Blocks moved and one optimisation
 * loading a from l rather then sb->typeSize
 *********************************************************/
void parseVariable() {
    node_t *l1a;
    int l2;
    register member_t *sb;

    sb         = getOrCreateScopedSymbol(getToken(), VAR);
    sb->typeDesc = parseTypeWithIndirection(getToken(), &sb->indirFlags);
    l1a        = optimizeExpression(parseExpr());
    if (l1a->op != CONST)
        fatalErr("Bad element count expr");
    sb->elemCount = (uint16_t)l1a->val.l;
    freeNodeTree(l1a);
    l2 = *getToken();
    expect(']');

    switch (l2) {
    case 'A': /* auto		*/
    case 'a':
        sb->StorageClass = 1;
        break;
    case 'R': /* register	*/
    case 'r':
        sb->storageFlags |= 8;
        // fall through
    case 'P': /* pointer	*/
    case 'p':
        sb->StorageClass = 5;
        break;
    case 'S': /* static 	*/
    case 's':
        sb->StorageClass = 4;
        break;
    case 'E': /* extern	*/
    case 'e':
        sb->StorageClass = 3;
        break;
    case 'T': /* typedef	*/
    case 't':
        sb->symKind = TYPE;
        if (sb->indirFlags != 0) {
            sb->offset  = 0;
            sb->StorageClass = 2;
        } else {
            sb->offset  = sb->typeDesc->offset;
            sb->StorageClass = sb->typeDesc->StorageClass;
        }
        if (sb->elemCount != 1)
            sb->StorageClass = 0;
        break;
    default:
        fatalErr("Bad storage class");
    }
    sb->typeSize = computeVarSize(sb);
    if (sb->symKind != TYPE) {
        if (sb->indirFlags == 0 && sb->typeSize == 0 && sb->typeDesc->typeSize == 0)
            prError("Bad dimensions");

        if (sb->StorageClass == 5 || sb->StorageClass == 1)
            allocateOrEmitVariable(sb, l2);
        else
            sb->offset = newLocal(); /* swTableCnt++ */

        if ((sb->indirFlags & 0x2) && sb->elemCount != 0) {
            if (++lvlidx == MAXFUN)
                fatalErr("Functions nested too deep");

            array_AE57[lvlidx] = nstdpth; /* Save current nesting depth */
            array_AE97[lvlidx] = 6;
            array_AE13[lvlidx] = 0;
            array_AEDB[lvlidx] = sb;
        }
    }
}

typedef struct {
    uint16_t cnt;
    member_t *vals[257];
} memberb_t;

typedef struct {
    uint16_t cnt;
    int16_t vals[257];
} memberi_t;

/*********************************************************
 * sub_19C1 OK++ PMO	       Used in: sub_6D1, sub_4192
 * One minor optimisation as getOrCreateScopedSymbol now declared as taking
 * a uint8_t rather than int for last parameter
 *********************************************************/
void parseMembers(int typeKind) {
    size_t memberListSize;
    member_t *aggregateType;
    memberb_t *memberList;
    node_t *elemCountExpr;
    char *tokenText;
    memberb_t memberListBuffer;
    register member_t *member;

    aggregateType   = getOrCreateScopedSymbol(getToken(), typeKind);
    memberList      = &memberListBuffer;
    memberList->cnt = 0;

    for (;;) {
        tokenText = getToken();
        if (*tokenText == ']')
            break;

        member          = (member_t *)allocMem(sizeof(member_t));
        member->symKind = MEMBER;

        if (*tokenText == ':') {
            member->bitWidth = atoi(tokenText + 1);
            member->storageFlags |= 0x10;
            tokenText = getToken();
        }

        member->typeDesc = parseTypeWithIndirection(tokenText, &member->indirFlags);
        elemCountExpr    = optimizeExpression(parseExpr());
        if (elemCountExpr->op != CONST)
            fatalErr("Strucdecl - bad\tnelem");

        member->elemCount = (uint16_t)elemCountExpr->val.l;
        freeNodeTree(elemCountExpr);
        member->typeSize                    = computeVarSize(member);
        memberList->vals[memberList->cnt++] = member;
    }
    /* note in the size calculation below an extra member_t pointer is reserved
     * in the decompilation I have assumed struct _memb (defined in struct bbb)
     * used a dummy array size of [1] for the vals, this gives the extra pointer
     */
    memberListSize = (memberList->cnt - 1) * sizeof(member_t *) + sizeof(struct _memb);
    memberList     = allocMem(memberListSize);
    bmove(&memberListBuffer, memberList, memberListSize);
    aggregateType->payload.memberList = (struct _memb *)memberList;
    finalizeStructOrUnionLayout(aggregateType);
}


/*********************************************************
 * sub_1B0C OK++ PMO		Used in: sub_6D1, sub_4192
 *
 * There are three minor differences of equivalent code
 * 1) optimisation of last parameter passed to getOrCreateScopedSymbol as it
 *    is declared a uint8_t
 * 2) Slightly inferior code to calculate (pMember->cnt - 1)
 *    using explicity add -1 rather than dec hl
 * 3) code generated following expect includes popping the
 *    passed in paramater, before jp cret. As cret will
 *    clean up the stack this isn't strictly necessary
 *
 *********************************************************/
void parseEnum() {
    node_t *l1a;
    memberi_t *pMember;
    int lobnd;
    int hibnd;
    size_t size;
    memberi_t members;
    register member_t *sb;

    lobnd        = MININT; /* arithmetic overflow in constant expression */
    hibnd        = MAXINT;
    sb           = getOrCreateScopedSymbol(getToken(), ENUM);
    pMember      = &members;
    pMember->cnt = 0;
    for (;;) {
        l1a = parseExpr();
        if (l1a->op == DOT_DOT) {
            freeNodeTree(l1a);
            size    = (pMember->cnt - 1) * sizeof(uint16_t) + sizeof(struct _memi);
            pMember = allocMem(size);
            bmove(&members, pMember, size);
            sb->payload.enumList = (struct _memi *)pMember;
            setEnumStorageType(sb, hibnd, lobnd);
            expect(']');
            return;
        }
        l1a                           = optimizeExpression(l1a);

        pMember->vals[pMember->cnt++] = (uint16_t)l1a->val.l;

        if (lobnd < l1a->val.l)
            lobnd = l1a->val.l;
        if (l1a->val.l < hibnd)
            hibnd = l1a->val.l;
        freeNodeTree(l1a);
    }
}

/*********************************************************
 * sub_1C6D OK++ PMO			Used in: finalizeStructOrUnionLayout
 *********************************************************/
int alignUpByMask(int p1, int p2) {

    return (p1 + p2) & ~p2;
}

/*********************************************************
 * sub_1C8E OK++ PMO   Used in: sub_B19, sub_17E0, sub_19C1
 *********************************************************/
int computeVarSize(register member_t *sb) {

    if (sb->indirFlags & 1)
        return sb->elemCount * 2;
    return sb->typeDesc->typeSize * sb->elemCount;
}

/*********************************************************
 * sub_1CC4 OK++ PMO	       Used in: emitInitializerData, finalizeStructOrUnionLayout
 *********************************************************/
int getTypeAlignment(register member_t *sb) {

    if (sb->indirFlags != 0)
        return 0;
    return sb->typeDesc->offset;
}

/*********************************************************
 * sub_1CEF OK++ PMO			Used in: sub_19C1
 *********************************************************/
void finalizeStructOrUnionLayout(register member_t *aggregateType) {
    int layoutSize;
    int memberIndex;
    int bitOffsetInWord;
    member_t *member;

    layoutSize = 0;

    for (memberIndex = bitOffsetInWord = 0; memberIndex != aggregateType->payload.memberList->cnt;
         memberIndex++) {

        member = aggregateType->payload.memberList->vals[memberIndex];
        if (aggregateType->symKind == UNION) {
            layoutSize     = max(layoutSize, member->typeSize);
            member->offset = 0;
        } else {
            layoutSize = member->offset = alignUpByMask(layoutSize, getTypeAlignment(member));
            if (member->storageFlags & 0x10) {
                if (16 < bitOffsetInWord + member->bitWidth || member->bitWidth == 0) {
                    if (bitOffsetInWord != 0)
                        member->offset = (layoutSize += 2);
                    bitOffsetInWord = 0;
                }
                member->bitOffset = bitOffsetInWord;
                bitOffsetInWord += member->bitWidth;
                if (bitOffsetInWord == 32) {
                    bitOffsetInWord = 0;
                    layoutSize += 2;
                }
            } else {
                if (bitOffsetInWord != 0) {
                    bitOffsetInWord = 0;
                    member->offset  = (layoutSize += 2);
                }
                layoutSize += member->typeSize;
            }
        }
    }

    if (bitOffsetInWord != 0) {
        bitOffsetInWord = 0;
        layoutSize += 2;
    }

    aggregateType->typeSize = alignUpByMask(layoutSize, 0);
    aggregateType->offset   = 0;
    aggregateType->symKind  = STRUCT;
}

/*********************************************************
 * sub_1EDF OK++ PMO			Used in: generateCodeForExpr
 *********************************************************/
void emitRegisterVarLoads() {
    member_t **l1b;
    register member_t *sb;

    l1b = hashtab;
    do {
        for (sb = *l1b; sb != 0 && sb->nestDepth == nstdpth; sb = sb->hashNext)
            if (sb->symKind == VAR && sb->StorageClass == 2 && (sb->storageFlags & 4))
                prIXnPush(sb);
    } while (++l1b != &hashtab[HASHTABSIZE]);
}

/* end of file sym1.c */

/*
 * File - sym2s.c
 */

/* macros to make reading the code easier */
/* clang-format off */
/* don't reformat as hitech cpp includes the extra spaces
   which can cause line overflow
*/
#ifndef TOPBIT
#define TOPBIT 0x8000
#define TopBitSet(selectedReg) ((selectedReg)&TOPBIT)
#define MapVal(selectedReg) (TopBitSet(selectedReg)?~(selectedReg):registerMaskById[selectedReg])
#endif
/* clang-format on */
static int array_A162[] = {
    0,    9,    -10,  25,   -28, 21,   25,   -28,  7,    21,   25,   28,   -29,  11,   12,
    13,   14,   -15,  4,    5,   21,   25,   -28,  6,    21,   25,   -28,  1,    21,   -28,
    17,   20,   21,   22,   25,  26,   28,   -29,  3,    21,   25,   -28,  4,    5,    20,
    21,   25,   -28,  2,    21,  25,   -28,  19,   23,   24,   -27,  20,   -28,  239,  -240,
    133,  -134, 46,   -47,  43,  44,   46,   -47,  43,   44,   46,   47,   -48,  43,   44,
    -47,  43,   44,   45,   46,  47,   -48,  43,   44,   45,   46,   -47,  45,   -47,  116,
    117,  118,  119,  120,  121, 122,  123,  124,  127,  130,

    131,  -132, 117,  118,  120, 125,  128,  131,  -132, 117,  118,  120,  126,  129,  131,
    -132, 245,  -246, 212,  214, -217, 218,  -221, 228,  229,  230,  231,  232,  233,  234,
    235,  -236, 211,  -227, 224, 225,  -226, 214,  -219, 213,  -214, 135,  -136, 71,   72,
    73,   -97,  93,   -94,  77,  78,   79,   80,   81,   -82,  85,   -86,  75,   -83,  73,
    -91,  87,   -88,  30,   -31, 145,  146,  -147, 143,  -144, 175,  -178, 161,  -207, 185,
    -204, 162,  163,  182,  183, 184,  -185, 161,  198,  199,  200,  -201, 173,  -180, 172,
    -181, 161,  185,  186,  187, 205,  206,  208,  209,  -210,

    169,  -171, 159,  165,  185, 194,  195,  196,  -203, 174,  -179, 163,  165,  188,  189,
    191,  -193, 190,  -192, 176, -179, 168,  -171, 177,  -178, 162,  -185, 161,  -163, 248,
    -249, 40,   41,   -42,  38,  39,   40,   41,   -42,  40,   -41,  37,   38,   39,   40,
    41,   -42,  38,   39,   40,  -41,  109,  -110, 243,  -244, 51,   -52,  152,  -153, 53,
    55,   -56,  54,   -55,  107, -108, 59,   60,   -61,  58,   -61,  58,   59,   -61,  105,
    -106, 101,  -102, 101,  102, -103, 156,  -157, 138,  -140
};

/*********************************************************
 * sub_1F4B OK++ PMO	Used in: generateCodeForExpr
 * one small block of code moved by optimiser otherwise code
 * identical
 * Note needs standalone ported optimiser to optimise
 *********************************************************/
int selectCodePattern(node_t *node, int patternClass, int availableRegs, int requiredResult, int *usedRegsOut) {
    int ruleIndex, leftUsedRegs, rightUsedRegs, rightLiveRegs, currentRuleIndex, resultConstraint;
    uint16_t righRequiredResult, leftUsedMask;
    register struct codeFrag_t *frag;
    static int regIdx; /* afed */
    static char *regTemplate;
    static char *aliasSuffixes;
    static char templateCode;
    static int scratchCandidates;
    static int selectedReg;
    // initialise to avoid warnings
    leftUsedRegs = rightUsedRegs = 0;

    if (node->fragCount == 0)
        node->evalOrder = 0;
    if ((ruleIndex = lookupPatternRule(patternClass, node->op)) == 0)
        return (-1);

    if (requiredResult != 0 && TopBitSet(requiredResult) == 0 && findRegisterMatch(availableRegs, requiredResult) == 0 &&
        (node->op != USEREG || findRegisterMatch(registerMaskById[node->val.l], requiredResult) == 0))
        return (-1);

    do {
        if (ruleIndex > 0)
            regIdx = currentRuleIndex = array_A162[ruleIndex++];
        else
            regIdx = currentRuleIndex = ruleIndex;

        if (regIdx < 0)
            regIdx = -regIdx;

        frag = &codeFrag[regIdx];

        if (frag->scratchRegClass != 0 && findRegisterMatch(availableRegs, frag->scratchRegClass) == 0)
            continue;

        if ((uint8_t)frag->emitClass < 'H' && frag->leftTokenClass != 0 &&
            (lookupPatternRule((uint8_t)frag->leftTokenClass, node->val.np[0]->op) == 0 ||
             (frag->rightTokenClass != 0 && lookupPatternRule(frag->rightTokenClass, node->val.np[1]->op) == 0)))
            continue;
        if (frag->nodePredicateIdx != 0 && isPatternApplicable(node, frag->nodePredicateIdx) == 0)
            continue;

        resultConstraint = frag->resultRegClass;
        righRequiredResult = 0;
        if (requiredResult == 0 && frag->emitClass == 'E')
            requiredResult = frag->resultRegClass;

        if (requiredResult != 0 && (!TopBitSet(requiredResult) || resultConstraint == 0 || findRegisterMatch(requiredResult & 0x7fff, resultConstraint) != 0)) {
            if ((regTemplate = frag->regTemplate) != 0) {
                if (regTemplate[0] == 'L' && regTemplate[1] == 0)
                    regTemplate = "GL";
                while (*regTemplate) {
                    templateCode = *regTemplate;
                    if (templateCode == 'X' || templateCode == 'G' || (templateCode == 'S' && node->op == USEREG)) {
                        if (isdigit(*++regTemplate))
                            aliasSuffixes = regTemplate;
                        else
                            aliasSuffixes = 0;
                        while (*regTemplate < 'A')
                            regTemplate++;
                        switch (*regTemplate) {
                        case 'L':
                            if ((resultConstraint = mergeRegisterConstraints(resultConstraint, requiredResult, availableRegs, aliasSuffixes)) == 0)
                                resultConstraint = -1;
                            break;
                        case 'R':
                            righRequiredResult = requiredResult;
                            break;
                        case 'N':
                            if (templateCode == 'S') {
                                if (node->op == USEREG &&
                                    mergeRegisterConstraints(resultConstraint, requiredResult, registerMaskById[node->val.l], aliasSuffixes) == 0)
                                    resultConstraint = -1;
                            } else if (selectCompatibleRegister(availableRegs, requiredResult, frag->scratchRegClass) == 0 &&
                                       (!TopBitSet(requiredResult) || mergeRegisterConstraints(frag->scratchRegClass, requiredResult, availableRegs, aliasSuffixes) == 0))
                                resultConstraint = -1;
                            break;
                        default:
                            continue;
                        }
                        break;
                    } else
                        regTemplate++;
                }
            } else if ((resultConstraint = mergeRegisterConstraints(resultConstraint, requiredResult, availableRegs, 0)) == 0)
                resultConstraint = -1;
        }

        if (resultConstraint == -1)
            continue;
        rightLiveRegs = 0;
        if ((uint8_t)frag->emitClass >= 'H') {
            node->fragCount = 0;
            if (selectCodePattern(node, (uint8_t)frag->emitClass, availableRegs, resultConstraint, &leftUsedRegs) < 0) {
                node->fragCount = 0;
                continue;
            }
        } else if (frag->leftTokenClass != 0) {
            node->val.np[0]->fragCount = 0;
            if (selectCodePattern(node->val.np[0], (uint8_t)frag->leftTokenClass, availableRegs, resultConstraint, &leftUsedRegs) < 0)
                continue;
            if (frag->rightTokenClass != 0) {
                node->val.np[1]->fragCount = 0;
                leftUsedMask                    = computeUsedRegs(node->val.np[0]);
                if (righRequiredResult == 0) {
                    if (frag->scratchRegClass != 0)
                        righRequiredResult = registerMaskById[(uint8_t)selectCompatibleRegister(availableRegs, requiredResult, frag->scratchRegClass)];
                    else
                        righRequiredResult = 0;
                    righRequiredResult = (leftUsedMask | righRequiredResult) ? (leftUsedMask | righRequiredResult | 0x8000) : 0;
                }
                if (selectCodePattern(node->val.np[1], frag->rightTokenClass, availableRegs, righRequiredResult, &rightUsedRegs) < 0)
                    continue;
                rightLiveRegs = computeUsedRegs(node->val.np[1]);
                if (rightLiveRegs & leftUsedMask) {
                    node->val.np[1]->fragCount = 0;
                    if (selectCodePattern(node->val.np[1], frag->rightTokenClass, availableRegs & ~leftUsedMask, righRequiredResult, &rightUsedRegs) <= 0)
                        continue;
                    rightLiveRegs = computeUsedRegs(node->val.np[1]);
                }
                if ((dopetab[node->op] & 0x100) || (rightLiveRegs & leftUsedRegs)) {
                    if (leftUsedMask & rightUsedRegs) {
                        if (dopetab[node->op] & 0x100)
                            continue;
                        node->evalOrder = 2;
                        rightLiveRegs        = 0;
                    } else
                        node->evalOrder = 1;
                } else
                    node->evalOrder = 0;
            }
        } else if (resultConstraint != 0)
            requiredResult = resultConstraint;

        if (frag->scratchRegClass != 0) {
            scratchCandidates = availableRegs;
            if (!(frag->scratchRegClass & 0x40) || (selectedReg = selectCompatibleRegister(computeUsedRegs(node), requiredResult, frag->scratchRegClass)) == 0) {
                if ((frag->scratchRegClass & 0x40) == 0)
                    scratchCandidates &= ~computeUsedRegs(node);
                scratchCandidates &= ~rightLiveRegs;
                selectedReg = selectCompatibleRegister(scratchCandidates, requiredResult, frag->scratchRegClass);
                if (selectedReg == 0 && (selectedReg = findRegisterMatch(scratchCandidates, frag->scratchRegClass)) == 0)
                    continue;
            }
            node->scratchReg[node->fragCount] = selectedReg;
        } else
            node->scratchReg[node->fragCount] = 0;

        node->fragIdx[node->fragCount++]    = (uint8_t)(frag - codeFrag);
        selectedReg                         = (uint8_t)chooseResultRegister(node);
        assert(node->fragCount > 0);
        node->resultReg[node->fragCount - 1] = selectedReg;
        if (selectedReg == 0 && node->op == USEREG)
            node->resultReg[node->fragCount - 1] = selectedReg = node->val.l;
        /* clang-format off */
        if ((requiredResult != 0 && !TopBitSet(requiredResult) && (selectedReg == 0 || findRegisterMatch(MapVal(requiredResult), selectedReg) != selectedReg)) ||
            (TopBitSet(requiredResult) && (MapVal(requiredResult) & MapVal(selectedReg)) != MapVal(selectedReg))) {
                node->fragCount--;
                continue;
            }
        /* clang-format on */
        *usedRegsOut = registerMaskById[node->scratchReg[node->fragCount - 1]];

        if ((uint8_t)frag->emitClass >= 'H' || frag->leftTokenClass != 0)
            *usedRegsOut |= leftUsedRegs;
        if (frag->rightTokenClass != 0)
            *usedRegsOut |= rightUsedRegs;
        return 1;
    } while (currentRuleIndex >= 0);
    return -1;
}

/* end of file sym2s.c */
/*
 * File - sym3.c
 */

/*********************************************************
 * sub_283E OK++ PMO				 Used in: computeUsedRegs
 *
 * apart from one minor optimisation difference to save
 * a pop bc, the code is identical
 *********************************************************/
int computeUsedRegsForStep(register node_t *node, int stepIndex) {
    char *regTemplate;
    struct codeFrag_t *frag;
    node_t *targetNode;
    char *aliasSuffixes;
    uint8_t templateCode;
    int targetStep;
    int usedRegsMask;

    frag = &codeFrag[node->fragIdx[stepIndex]];
    usedRegsMask  = 0;

    for (regTemplate = frag->regTemplate; *regTemplate;) {
        switch (templateCode = *(regTemplate++)) {
        case 'X':
        case 'G':
            if (isdigit(*regTemplate)) {
                aliasSuffixes = regTemplate;
                while (isdigit(*regTemplate))
                    regTemplate++;
            } else
                aliasSuffixes = 0;

            switch (*regTemplate++) {
            case 'N':
                targetStep  = stepIndex;
                targetNode = node;
                break;
            case 'L':
                if (stepIndex > 0) {
                    targetNode = node;
                    targetStep  = stepIndex - 1;
                } else {
                    targetNode = node->val.np[0];
                    targetStep  = targetNode->fragCount - 1;
                }
                break;
            case 'R':
                targetNode = node->val.np[1];
                targetStep  = targetNode->fragCount - 1;
                break;
            default:
                fprintf(stderr, "%s: line %d - internal error\n", __FILE__, __LINE__);
                exit(1);
            }
            if (templateCode == 'S') {
                if (targetNode->op == USEREG)
                    templateCode = (uint8_t)targetNode->val.l;
                else
                    templateCode = 0;
            } else {
                templateCode = templateCode == 'G' ? targetNode->resultReg[targetStep] : targetNode->scratchReg[targetStep];
                if (aliasSuffixes)
                    while (isdigit(*aliasSuffixes) != 0)
                        templateCode = registerAliasBySuffix[templateCode * 2 + (*aliasSuffixes++ - '0')];
            }
            usedRegsMask |= registerMaskById[templateCode];
            if (templateCode != 0)
                lastReferencedReg = templateCode;
            break;
        case 'A':
        case 'B':
        case 'C':
        case 'F':
        case 'M':
        case 'O':
        case 'P':
        case 'Q':
        case 'S':
        case 'T':
        case 'V':
        case 'W':
        case 'Z':
            while (*regTemplate && *regTemplate != 'N' && *regTemplate != 'L' && *regTemplate != 'R')
                regTemplate++;
            break;
        case '~':
            while (*regTemplate && *regTemplate != 'L' && *regTemplate != 'R')
                regTemplate++;
            break;
        case 'L':
            if (stepIndex > 0)
                usedRegsMask |= computeUsedRegsForStep(node, stepIndex - 1);
            else
                usedRegsMask |= computeUsedRegs(node->val.np[0]);

            break;
        case 'R':
            usedRegsMask |= computeUsedRegs(node->val.np[1]);
            break;
        case 'D':
        case 'U':
            break;
        }
    }
    return usedRegsMask & word_B017;
}

/*********************************************************
 * sub_2B2A OK++ PMO   Used in: selectCodePattern, computeUsedRegsForStep, chooseResultRegister
 * optimiser improves on code for node->a_c1 - 1
 *********************************************************/
int computeUsedRegs(register node_t *sa) {

    if (sa->fragCount == 0) {
        if ((dopetab[sa->op] & 0xC) == 0)
            return 0;
        return computeUsedRegs(sa->val.np[0]); /* LOGOP & QUEST */
    }
    return computeUsedRegsForStep(sa, sa->fragCount - 1);
}

/*********************************************************
 * sub_2B79 OK++ PMO			 Used in: selectCodePattern
 *********************************************************/
uint8_t chooseResultRegister(register node_t *node) {
    uint8_t scratchReg;
    int usedRegsMask;

    scratchReg   = node->scratchReg[node->fragCount - 1];
    lastReferencedReg    = 0;
    usedRegsMask = computeUsedRegs(node);
    if (scratchReg != 0 && findRegisterMatch(usedRegsMask, scratchReg) == scratchReg)
        return scratchReg;
    return lastReferencedReg;
}
/* end of file sym3.c */
/*
 * File - cgen1.c
 */

/*********************************************************
 * sub_2BD0 OK++ PMO      Used in: sub_793, emitInitializerData, rewriteExprForCodegen
 *			       compileExpression
 *********************************************************/
void generateCodeForExpr(register node_t *sa) {
    int tmp;

    sa->fragCount = 0;

    if (selectCodePattern(sa, 0x48, word_B017, 0, &tmp) <= 0)
        fatalErr("Expression too complicated");

    emitTreeCode(sa);
    if (sa->op == COLON_U) {
        if (sa->ptrFlags & 2) {
            prFrameHead(array_AEDB[lvlidx]->offset); /* emit_call_ncsv */
            emitRegisterVarLoads();
        }
        if (sa->val.np[0]->op == IDOP)
            sa->val.np[0]->val.mp[0]->storageFlags |= 1; /* may ba struct aaa fragIdx[0] */
    }
    freeNodeTree(sa);
}

/*********************************************************
 * sub_2C5E OK++ PMO   	      Used in: emitSizedConstant, isPatternApplicable
 *
 *********************************************************/
long signExtendToNodeSize(node_t *sa, long p2) {
    char loc;

    if ((loc = nodesize(sa) * 8) >= 32)
        return p2;
    if (p2 & (1L << (loc - 1)))
        p2 |= ~((1L << loc) - 1L);
    return p2;
}

/*********************************************************
 *  sub_2CE0 OK++ PMO			Used in: emitCodeTemplate
 *********************************************************/
void emitSizedConstant(node_t *p1a, long p2) {

    printf("%ld", signExtendToNodeSize(p1a, p2));
}
/* end of cgen1.c */

/*
 * File - cgen2s.c	BIG size - problems compiling v3.09
 */

/* compiling this function with Hitech C runs out of memory
   so here the external functions are declared explicitly
   so that the normal function declarations and some of the
   unused include files are not processed.
*/
#ifndef _CGEN_H
#define MINI
#include "cgen.h"

int atoi(char *);
uint8_t getTypeClass(node_t *);
uint16_t getPointeeSize(node_t *);
uint16_t nodesize(node_t *);
uint8_t log2IfPowerOfTwo(long);
#endif
/*.......................................................*
 *  sub_2D09_v2 OK++	Used in: emitNodeCodeFragments
 * minor differences
 * 1) block of 5 instructions has different order but same effect
 * 2) one optimisation missed on loading a from activeStep, possibly
 *    related to note 1
 * 3) optimisation because targetClass is passed recursively as a char
 *.......................................................*/
void emitCodeTemplate(register node_t *node, char *templateText, char stepIndex) {
    struct codeFrag_t *selectedFrag FORCEINIT; // avoid uninitialised warning
    node_t *targetNode FORCEINIT; // avoid uninitialised warning
    char *aliasDigits FORCEINIT;   // avoid uninitialised warning
    uint8_t regId;
    char offsetAdjust = 0;       // avoid uninitialised warning
    char targetSelector;
    char directive;
    int modifier;
    long value;
    uint8_t activeStep = 0;   // avoid uninitialised warning
    char deferredValuePending;
    char *templateLineStart;
    uint32_t deferredValue = 0;  // avoid uninitalised warning
    bool atLineStart;

    templateLineStart = templateText;
    deferredValuePending = atLineStart = false;
    for (;;) {
        if ((directive = *templateText++) == 0)
            return;
        switch (directive) {
        case ' ':
            if (!atLineStart) {
                fputchar('\t');
                atLineStart = true;
            } else
                fputchar(directive);
            continue;
        case ';':
            return;
        case '\n':
        case '\r':
            fputchar('\n');
            atLineStart = false;
            continue;
        case 'G':
        case 'X':
            if (isdigit(*templateText)) {
                aliasDigits = templateText;
                while (isdigit(*templateText))
                    templateText++;
            } else
                aliasDigits = 0;
            targetSelector = *templateText++;
            modifier  = 'G';
            break;
        case 'A':
        case 'B':
        case 'C':
        case 'F':
        case 'M':
        case 'O':
        case 'P':
        case 'Q':
        case 'S':
        case 'T':
        case 'V':
        case 'W':
        case 'Z':
        case '~':
            if ((modifier = *templateText) == '-' || modifier == '+') {
                if (isdigit(*++templateText)) {
                    offsetAdjust = atoi(templateText);
                    if (modifier == '-')
                        offsetAdjust = -offsetAdjust;
                    modifier = 0;
                } else
                    offsetAdjust = 0;
                while (isdigit(*templateText) || *templateText == '+' || *templateText == '-')
                    templateText++;
            } else if (modifier == '>') {
                for (offsetAdjust = 0; *templateText == '>'; templateText++, offsetAdjust++)
                    ;
            } else {
                modifier  = 0;
                offsetAdjust = 0;
            }

            targetSelector = *templateText++;
            break;
        case 'L':
        case 'R':
        case 'U':
            targetSelector = directive;
            directive = '~';
            modifier  = 0;
            offsetAdjust = 0;
            break;
        case 'D':
            targetSelector = directive;
            modifier  = 0;
            offsetAdjust = 0;
            break;

        default:
            fputchar(directive);
            continue;
        }

        switch (targetSelector) {
        case 'L':
            if (stepIndex > 0) { /* m27: */
                targetNode  = node;
                activeStep = stepIndex - 1;
                selectedFrag  = &codeFrag[node->fragIdx[activeStep]];
            } else {
                targetNode  = node->val.np[0];
                activeStep = targetNode->fragCount - 1;
                selectedFrag  = &codeFrag[targetNode->fragIdx[activeStep]];
            }
            break;
        case 'R':
            targetNode  = node->val.np[1];
            activeStep = targetNode->fragCount - 1;
            selectedFrag  = &codeFrag[targetNode->fragIdx[activeStep]];
            break;
        case 'N':
            targetNode  = node;
            activeStep = stepIndex;
            break;
        }
        switch (directive) {
        case 'D':
            if (word_AFF8 != 0) {
                printf("%d", word_AFF8);
                word_AFF8 = 0;
            }
            break;
        case 'S':
            if (targetNode->op == USEREG)
                printf("%s", regNames[targetNode->val.l]);
            else if (targetNode->op == CONST)
                emitSizedConstant(targetNode, targetNode->val.l);
            else if (targetNode->op == FCONST)
                printf("%s", targetNode->val.sv.s);
            else
                printf("%s", targetNode->val.mp[0]->name);
        proff:
            if (modifier == 0) {
                offsetAdjust += word_AFF8;
                word_AFF8 = 0;
                if (offsetAdjust > 0)
                    printf("+%d", offsetAdjust);
                else if (offsetAdjust < 0)
                    printf("%d", offsetAdjust);
            }
            break;
        case 'F':
            printf("%d", targetNode->val.sv.v);
            goto proff;

        case 'Z':
            value = nodesize(targetNode);
            goto m46;
        case 'B':
            value = getPointeeSize(targetNode);
        m46:
            if (modifier == '-') {
                if (deferredValuePending == 0) {
                    deferredValue      = value + (long)word_AFF8;
                    word_AFF8 = 0;
                    deferredValuePending      = 1;
                }
                goto m54;
            }
            printf("%lu", value);
            break;
        case 'O':
            printf("%s", otherFrag[targetNode->op]);
            break;
        case 'A':
            emitTypeSuffix(targetNode);
            break;
        case 'V':
            if (modifier == '-' || modifier == '+') {
                if (deferredValuePending == 0) {
                    deferredValue      = targetNode->val.l + (long)word_AFF8;
                    word_AFF8 = 0;
                    deferredValuePending      = 1;
                }
            m54:
                deferredValue += modifier == '-' ? -1L : 1L;
                if (getTypeClass(targetNode) == 2 && nodesize(targetNode) < 4)
                    deferredValue &= (1 << (int)(nodesize(targetNode) * 8)) - 1;

                if (deferredValue != 0) {
                    while (templateLineStart < templateText && templateText[-1] != '\n')
                        templateText--;
                    fputchar('\n');
                } else
                    deferredValuePending = 0;
            } else {
                offsetAdjust += word_AFF8;
                word_AFF8 = 0;
                emitSizedConstant(targetNode, targetNode->val.l >> (offsetAdjust * 8));
            }
            break;

        case 'C':
            if (targetNode->op == BFIELD)
                printf("%d", targetNode->val.mp[1]->bitOffset);
            else {
                value = targetNode->val.l;
                if (log2IfPowerOfTwo(value) == 0)
                    value = ~value;
                word_AFF8 += (log2IfPowerOfTwo(value) - 1) / 8;
            }
            break;
        case 'T':
            if (targetNode->op == BFIELD)
                printf("%d", targetNode->val.mp[1]->bitWidth);
            else {
                value = targetNode->val.l;
                if (log2IfPowerOfTwo(value) == 0)
                    value = ~value;
                printf("%d", log2IfPowerOfTwo(value) - 1);
            }
            break;
        case 'G':
        case 'X':
            assert(targetNode != NULL); // Ensure targetNode is not NULL
            regId = directive == 'G' ? targetNode->resultReg[activeStep] : targetNode->scratchReg[activeStep];

            if (aliasDigits != 0)
                while (isdigit(*aliasDigits))
                    regId = registerAliasBySuffix[regId * 2 + (*aliasDigits++ - '0')];

            if (*templateText != '+') {
                regId += word_AFF8;
                word_AFF8 = 0;
            }
            printf("%s", regNames[regId]);
            break;
        case '~':
            if (targetSelector == 'U') {
                offsetAdjust += word_AFFB;
                if ((dopetab[node->op] & 0x200) && stepIndex != 0)
                    offsetAdjust--;
                printf("%d", offsetAdjust);
            } else {
                word_AFF8 += offsetAdjust;
                emitCodeTemplate(targetNode, selectedFrag->regTemplate, activeStep);
            }
            break;
        }
    }
}

/* end of file cgen2s.c */
/*
 * File - cgen3.c Created 09.03.2019 Last Modified 30.05.2020
 */

/*********************************************************
 * sub_3564 OK++ PMO			Used in: emitTreeCode
 * minor optimisation difference due to last parameter
 * of emitCodeTemplate being declared as char
 *********************************************************/
void emitNodeCodeFragments(register node_t *sa) {
    uint8_t l1;
    struct codeFrag_t *l2z;

    word_AFF8 = 0;
    for (l1 = 0; l1 != sa->fragCount; l1++) {
        if ((l2z = &codeFrag[sa->fragIdx[l1]])->emitTemplate) {
            emitCodeTemplate(sa, l2z->emitTemplate, l1);
            fputchar('\n');
        }
    }
}

/*********************************************************
 * sub_35E6 OK++ PMO				Used in: generateCodeForExpr
 *
 *********************************************************/
void emitTreeCode(register node_t *sa) {
    int l1;

    if (dopetab[sa->op] & 0x200)
        word_AFFB++;
    l1 = dopetab[sa->op] & 0xC;
    if (8 == l1) {
        if (sa->evalOrder & 1) {
            emitTreeCode(sa->val.np[0]);
            emitTreeCode(sa->val.np[1]);
        } else {
            emitTreeCode(sa->val.np[1]);
            if (sa->evalOrder & 2)
                prPush(sa->val.np[1]->resultReg[sa->val.np[1]->fragCount - 1]);
            emitTreeCode(sa->val.np[0]);
        }
    }
    if (l1 == 4)
        emitTreeCode(sa->val.np[0]);
    if (sa->evalOrder & 2)
        prPop(sa->val.np[1]->resultReg[sa->val.np[1]->fragCount - 1]);
    emitNodeCodeFragments(sa);
    if (dopetab[sa->op] & 0x200)
        word_AFFB--;
}

/*********************************************************
 * sub_36E0 OK++ PMO   Used in: sub_E43,  sub_39CA, rewriteExprForCodegen,
 *			    compileExpression, foldConstantExpressions, makeOpNode,
 *			    freeNodeTree, simplifyLogicalNot, dropRightOperand,
 *			    simplifyConversion, collapseAddressDereference, optimizeExpressionTree,
 *			    normalizeUnaryMinusAndSub, normalizeAddSubForms
 *********************************************************/
void freeNode(register node_t *sa) {

    byte_B013 = true;
    if (sa->op == FCONST)
        free(sa->val.np[0]);
    sa->type       = nodeFreeList;
    nodeFreeList = sa;
}

/*********************************************************
 * sub_3712 OK++ PMO    Used in: sub_E43,  cloneNodeTree, makeConstNode,
 *			     sub_4192, makeOpNode, resolveIdentifierNode,
 *			     optimizeExpressionTree
 *********************************************************/
node_t *allocNode(void) {
    register node_t *sa;

    byte_B013 = true;
    if (nodeFreeList) {
        sa           = nodeFreeList;
        nodeFreeList = sa->type;
        blkclr((char *)sa, sizeof(node_t));
    } else { /* create node_t */
        sa = allocMem(sizeof(node_t));
    }

    return sa;
}

/*********************************************************
 *  sub_374C OK++ PMO			Used in: allocMem
 *********************************************************/
bool releaseNodeFreeList(void) {
    register node_t *sa;

    if (nodeFreeList == 0)
        return false;
    while ((sa = nodeFreeList)) {
        nodeFreeList = sa->type;
        free(sa);
    }
    return true;
}

/*********************************************************
 *  sub_377A OK++ PMO			Used in: rewriteExprForCodegen
 *********************************************************/
node_t *cloneNodeTree(node_t *p1a) {
    register node_t *sa;

    sa  = allocNode();
    *sa = *p1a;

    if (dopetab[sa->op] & 0xC)
        sa->val.np[0] = cloneNodeTree(sa->val.np[0]);
    if ((dopetab[sa->op] & 0xC) == 8)
        sa->val.np[1] = cloneNodeTree(sa->val.np[1]);
    return sa;
}

/*********************************************************
 * sub_37ED v1 OK++ OK	      Used in: getPointeeSize, makeOpNode
 *
 * missed optimisation on reloading member but otherwise
 * identical
 *********************************************************/
void dereferenceNodeType(register node_t *sa) {
    member_t *l1b;

    l1b = sa->type;
    if (sa->ptrFlags != 0)
        sa->ptrFlags >>= 2;
    else {
        while (l1b->indirFlags == 0)
            l1b = l1b->typeDesc;
        sa->type    = l1b->typeDesc;
        sa->ptrFlags = l1b->indirFlags >> 2;
    }
}

/*********************************************************
 * sub_385B OK++ PMO    Used in: getPointeeSize, makeOpNode, resolveIdentifierNode,
 *			     rewriteMemberAccess
 *********************************************************/
void markPointerType(register node_t *sa) {
    sa->ptrFlags = (sa->ptrFlags * 4) | 1;
}

/*********************************************************
 * sub_387A OK++ PMO			Used in: emitCodeTemplate
 *********************************************************/
uint16_t getPointeeSize(register node_t *sa) {
    uint8_t loc;

    if (sa->ptrFlags == 0 && sa->type->typeDesc == 0 && sa->type->indirFlags == 0)
        return 1;

    dereferenceNodeType(sa);
    loc = (uint8_t)nodesize(sa);
    markPointerType(sa);
    return loc;
}

/*********************************************************
 * sub_38CA OK++ PMO	      Used in: hasPointerFlag, hasFunctionFlag
 * minor difference as function declared as bool
 *********************************************************/
bool hasTypeFlag(node_t *p1a, int p2) {
    register member_t *sb;

    if (p1a->ptrFlags & p2)
        return true;
    if (p1a->ptrFlags != 0)
        return false;
    sb = p1a->type;
    do {
        if (sb->indirFlags & p2)
            return true;
        if (sb->indirFlags != 0)
            return false;
    } while ((sb = sb->typeDesc) != 0);
    return false;
}

/*********************************************************
 * sub_393C OK++ PMO			Used in: Not used
 *********************************************************/
bool hasPointerFlag(node_t *sa) {
    return hasTypeFlag(sa, 1);
}

/*********************************************************
 * sub_3952 OK++ PMO			Used in: Not used
 *********************************************************/
bool hasFunctionFlag(node_t *sa) {
    return hasTypeFlag(sa, 2);
}

/*********************************************************
 * sub_3968 OK++ PMO			Used in: isPatternApplicable
 *********************************************************/
bool isStructValueNode(register node_t *sa) {
    return sa->type->symKind == STRUCT && (sa->ptrFlags & 1) == 0;
}

/*********************************************************
 * nodesize OK++ PMO    Used in: emitInitializerData,  sub_E43,  signExtendToNodeSize,
 *			     emitCodeTemplate, getPointeeSize, convertNodeToType,
 *			     makeOpNode, isPatternApplicable, simplifyConversion,
 *			     optimizeExpressionTree, fitsInTargetType, isSameTypeAndSize,
 *			     constFitsComparisonRange
 *********************************************************/
uint16_t nodesize(register node_t *sa) {

    if (sa->ptrFlags & 2)
        prError("can\'t take sizeof func");

    if (sa->ptrFlags & 1)
        return 2;
    return sa->type->typeSize;
}

/*********************************************************
 * sub_39CA OK++ PMO			Used in: foldConstantExpressions
 *********************************************************/
node_t *foldConstantConversion(register node_t *sa) {
    char buf[50];

    freeNode(sa->val.np[1]);
    if (getTypeClass(sa) == 3) {
        sprintf(buf, "%ld.", sa->val.np[0]->val.l);
        freeNode(sa->val.np[0]);
        sa->val.sv.s = allocMem(strlen(buf) + 1); /* create string */
        strcpy(sa->val.sv.s, buf);
        sa->val.sv.v = newLocal();
        sa->op      = FCONST;
        return sa;
    }
    convertNodeToType(sa, sa->val.np[0]);
    freeNode(sa);
    return sa->val.np[0];
}

/*********************************************************
 * sub_3A79 OK++ PMO	              Used in: foldConstantExpressions, sub_39CA
 *
 * Compiler generates code that performs expected action,
 * but differs from original image
 *********************************************************/
void convertNodeToType(register node_t *sa, node_t *p2a) {
    int l1;

    l1 = nodesize(sa);
    if (l1 != 0 && l1 < 4) {
        l1 <<= 3;
        p2a->val.l &= (1L << l1) - 1L;
        if (getTypeClass(sa) == 1) {
            if (p2a->val.l & (long)(1 << (l1 - 1))) { /* sign extend */
                p2a->val.l |= ~((1L << l1) - 1L);
            }
        }
    }
    p2a->type    = sa->type;
    p2a->ptrFlags = sa->ptrFlags;
}

/*********************************************************
 * sub_3B65 OK++ PMO			Used in: foldConstantExpressions
 *********************************************************/
void evalUnsignedOperation(register unsigned long *ptr, long p2, int operator) {

    switch (operator) {
    case DIV:
        *ptr /= p2;
        break;
    case MOD:
        *ptr %= p2;
        break;

    case RSHIFT:
        *ptr >>= p2;
        break;
    }
}

/*********************************************************
 * sub_3BC6 v1 OK++ PMO			Used in: foldConstantExpressions
 *
 *********************************************************/
void evalBinaryOperation(register long *ptr, long p2, int operator) {

    switch (operator) {
    case ADD:
        *ptr += p2;
        break;
    case SUB:
        *ptr -= p2;
        break;
    case MUL:
        *ptr *= p2;
        break;
    case DIV:
        *ptr /= p2;
        break;
    case MOD:
        *ptr %= p2;
        break;
    case BOR:
        *ptr |= p2;
        break;
    case BAND:
        *ptr &= p2;
        break;
    case BXOR:
        *ptr ^= p2;
        break;
    case LSHIFT:
        *ptr <<= p2;
        break;
    case RSHIFT:
        *ptr >>= p2;
        break;
    }
}

/*********************************************************
 * sub_3CDF OK++ PMO			Used in: compileExpression
 *********************************************************/
node_t *rewriteExprForCodegen(register node_t *sa) {
    int loc;

    if (sa->op == SCOLON) {
        generateCodeForExpr(sa->val.np[0]);
        freeNode(sa);
        sa = sa->val.np[1];
    }
    if (byte_B014 != 10) {
        if (dopetab[sa->op] & 0x4000)
            return sa;
        if ((sa->op == INCR || sa->op == DECR) && isRegisterIndirection(sa)) {
            array_AFFD[byte_B014++] = sa;
            sa->op                = sa->op == INCR ? ASADD : ASSUB;
            sa                      = cloneNodeTree(sa->val.np[0]);
        }
        loc = dopetab[sa->op];
        if (loc & 0xC)
            sa->val.np[0] = rewriteExprForCodegen(sa->val.np[0]);
        if ((loc & 0xC) == 8)
            sa->val.np[1] = rewriteExprForCodegen(sa->val.np[1]);
    }
    return sa;
}

/* end of file cgen3.c */
/*
 * File - tree1.c Created 09.03.2019 Last Modified 17.06.2020
 */
/*********************************************************
 * sub_3DC9 OK++ PMO		Used in: sub_6D1, sub_D66
 *********************************************************/
void compileExpression(register node_t *sa) {
    uint16_t loc;

    sa = optimizeExpression(sa);
    if (sa->op == DOLLAR && sa->val.np[0]->op == CONST) {
        prWarning("constant conditional branch");
        if (sa->val.np[0]->val.l != 0) {
            sa->op = DOLLAR_U;
            freeNode(sa->val.np[0]);
            sa->val.np[0] = sa->val.np[1];
        } else {
            freeNodeTree(sa);
            return;
        }
    }
    byte_B014 = 0;
    if (sa->op == INCR)
        sa->op = ASADD;
    else if (sa->op == DECR)
        sa->op = ASSUB;

    sa = rewriteExprForCodegen(sa);
    if (byte_B014 != 0)
        sa = optimizeExpression(sa);
    generateCodeForExpr(sa);
    for (loc = 0; loc < byte_B014; loc++)
        generateCodeForExpr(array_AFFD[loc]);
}

/*********************************************************
 * sub_3EAA OK++ PMO				Used in: optimizeExpression
 *********************************************************/

node_t *foldConstantExpressions(register node_t *sa) {
    node_t *l1a;
    int l2;

    if ((l2 = dopetab[sa->op] & 0xC))
        sa->val.np[0] = foldConstantExpressions(sa->val.np[0]);
    if (l2 == 8)
        sa->val.np[1] = foldConstantExpressions(sa->val.np[1]);
    if (sa->op == CONV && sa->val.np[0]->op == FCONST && getTypeClass(sa) == 3) {
        l1a     = sa->val.np[0];
        l1a->type = sa->type;
        freeNode(sa->val.np[1]);
        freeNode(sa);
        return l1a;
    }
    if (l2 == 0 || sa->val.np[0]->op != CONST)
        return sa;

    if (sa->op == CONV)
        return foldConstantConversion(sa);

    if (l2 == 8 && sa->val.np[1]->op != CONST)
        return sa;

    if (getTypeClass(sa) == 2) {
        switch (sa->op) {
        case LT:
        case LEQ:
        case GT:
        case GEQ:
            warningMsg = "constant relational expression";
            return sa;
        case MOD:
        case DIV:
        case RSHIFT:
            evalUnsignedOperation(&sa->val.np[0]->val.ul, sa->val.np[1]->val.l, sa->op);
        finish:
            if (l2 == 8)
                freeNodeTree(sa->val.np[1]);
            convertNodeToType(sa, sa->val.np[0]);
            freeNode(sa);
            return sa->val.np[0];
        }
    }
    switch (sa->op) { /* m10: */
    case NEQL:
    case LT:
    case LEQ:
    case EQL:
    case GT:
    case GEQ:
        warningMsg = "constant relational expression";
        return sa;
    case BAND:
    case LAND:
    case SUB:
    case BXOR:
    case BOR:
    case LOR:
    case ADD:
    case MUL:
    case DIV:
    case MOD:
    case RSHIFT:
    case LSHIFT:
        evalBinaryOperation(&sa->val.np[0]->val.l, sa->val.np[1]->val.l, sa->op);
        goto finish;
    case MINUS_U:
        sa->val.np[0]->val.l = -sa->val.np[0]->val.l;
        goto finish;
    case NOT:
        sa->val.np[0]->val.l = sa->val.np[0]->val.l == 0;
        goto finish;
    case BNOT:
        sa->val.np[0]->val.l = ~sa->val.np[0]->val.l;
        goto finish;
    default:
        return sa;
    }
}

/*********************************************************
 * sub_415E OK   Used in: emitInitializerData,  sub_E43,  sub_4192,
 *			    resolveIdentifierNode, optimizeExpressionTree
 *********************************************************/
node_t *makeConstNode(long number) {
    register node_t *sa;
    sa         = allocNode();
    sa->op   = CONST;
    sa->type     = typeLong;
    sa->val.l = number;
    return sa;
}

/* end of file tree1.c */
/*
 * File - tree2.c Created 09.03.2019 Last Modified 17.06.2020
 */

/* when compiling with the Hitech C compiler, to avoid a compiler crash
   use a subset of the cgen.h and declare only used functions
*/

#ifndef _CGEN_H
#define MINI
#include "cgen.h"

char lookupTokenId(char *);
member_t *getOrCreateSymbol(char *);
member_t *parseTypeWithIndirection(char *, uint16_t *);
void parseVariable();
void parseEnum();
node_t *parseExpr();
node_t *makeOpNode(uint8_t, node_t *, node_t *);
long atol(char *str);
void *allocMem(size_t);
char *getToken();
int newLocal();
node_t *makeConstNode(long);
node_t *allocNode();

void prGlobalDef(member_t *);
#endif
/*********************************************************
 * sub_4192 OK++ PMO     Used in: sub_6D1,  sub_793,  emitInitializerData,
 *			     sub_B19,  sub_E43,  sub_17E0,
 *			     sub_19C1, sub_1B0C
 * minor variation due to paramater 1 of makeOpNode being declared
 * uint8_t, otherwise identical
 *********************************************************/
node_t *parseExpr() {
    node_t *leftNode;
    char *tokenText;
    int tokenKindFlags;
    int tokenId;
    register node_t *node;

    for (;;) {
        tokenText = getToken();
        if (isdigit(*tokenText) || (*tokenText == '-' && isdigit(tokenText[1]))) {
            if (*tokenText == '-') {
                tokenId = 1;
                tokenText++;
            } else
                tokenId = 0;

            node = makeConstNode(atol(tokenText));
            if (tokenId != 0)
                node->val.l = -node->val.l;
            return node;
        }

        if (*tokenText == '_' || isalpha(*tokenText)) {
            (node = allocNode())->op = IDOP; /* m8:  */
            node->val.mp[0]           = getOrCreateSymbol(tokenText);
            node->type                   = node->val.mp[0]->typeDesc;
            node->ptrFlags                = node->val.mp[0]->indirFlags;
            if (node->val.mp[0]->StorageClass == 3 && (node->val.mp[0]->storageFlags & 2) == 0) {
                prGlobalDef(node->val.mp[0]); /* Emit "global name" */
            }
            return node;
        }
        if (*tokenText == '`') {
            node       = allocNode();
            node->type   = parseTypeWithIndirection(tokenText, &node->ptrFlags);
            node->op = TYPE;
            return node;
        }
        if (*tokenText == '.' && tokenText[1] && tokenText[1] != '.') {
            node            = allocNode();
            node->type        = typeDouble;                   /* "d" - double */
            node->val.sv.s = (char *)allocMem(strlen(tokenText)); /* create string */
            strcpy(node->val.sv.s, tokenText + 1);
            node->val.sv.v = newLocal(); /* swTableCnt++ */
            node->op      = FCONST;
            return node;
        }
        tokenId = lookupTokenId(tokenText); /* Token search */ /* m12: */
        tokenKindFlags = dopetab[tokenId] & 0xC;
        switch (tokenKindFlags) {
        case 0xc:
            switch (tokenId) {
            case '9':
                parseVariable();
                continue;
            case '7':
            case '8':
                parseMembers(tokenId);
                continue;
            case '4':
                parseEnum();
                continue;
            default:
                fatalErr("Expression error");
                break;
            }
            /* fall through */
        case 0:
            return makeOpNode(tokenId, 0, 0);
        case 4:
            return makeOpNode(tokenId, parseExpr(), 0);
        case 8:
            leftNode = parseExpr();
            return makeOpNode(tokenId, leftNode, parseExpr());
        }
    }
}

/* end of file tree2.c */
/*
 * File - tree3.c Created 09.03.2019 Last Modified 17.06.2020
 */

/*********************************************************
 * sub_43EF OK++ PMO      Used in: sub_793,  emitInitializerData,  sub_E43,
 *                            sub_4192, simplifyLogicalNot, resolveIdentifierNode,
 *                            rewriteMemberAccess, simplifyConversion, optimizeExpressionTree,
 *                            normalizeUnaryMinusAndSub

 *********************************************************/
node_t *makeOpNode(uint8_t op, node_t *left, node_t *right) {
    member_t *member;
    long sizeValue;
    register node_t *node;

    node             = allocNode();
    node->op       = op;
    node->val.np[0] = left;
    node->val.np[1] = right;
    switch (dopetab[node->op] & 0x30) {
    case 0x10:
        node->type = typeLong; /* long	  */
        break;
    case 0x20:
        node->type = typeB; /* b	  */
        break;

    case 0x30:
        node->type = typeVar; /* variable */
        break;

    default:
        node->type    = left->type;
        node->ptrFlags = left->ptrFlags;
    }
    switch (node->op) {
    case DOT:
        if (left->op == TYPE) {
            member = left->type;
            freeNode(node);
            freeNode(left);
            node          = right;
            node->type      = member;
            right->val.l = (long)member->payload.enumList->vals[node->val.l];
            break;
        }
        member         = node->type->payload.memberList->vals[right->val.l];
        node->type      = member->typeDesc;
        node->ptrFlags   = member->indirFlags;
        right->val.l = (long)member->offset;
        right->type     = typeX; /* x      */
        if (member->storageFlags & 0x10) {
            left             = allocNode();
            *left            = *node;
            left->val.np[0] = node;
            node              = left;
            node->op        = BFIELD;
            node->val.mp[1]  = member;
        }
        break;
    case CONV:
    case SCOLON:
    case QUEST:
        node->type    = node->val.np[1]->type;
        node->ptrFlags = node->val.np[1]->ptrFlags;
        break;
    case GADDR:
        if (node->ptrFlags == 0 && node->type->elemCount > 1) {
            node->ptrFlags = node->type->indirFlags;
            node->type    = node->type->typeDesc;
        }
        markPointerType(node);
        break;
    case LPAREN:
    case MUL_U:
        dereferenceNodeType(node);
        break;
    case COLON_S:
        node->type    = typeChar; /* char   */
        node->ptrFlags = 1;
        break;
    case HASHSIGN:
        if (node->val.np[0]->op == IDOP)
            sizeValue = node->val.np[0]->val.mp[0]->typeSize;
        else
            sizeValue = (uint16_t)nodesize(node->val.np[0]);
        if (sizeValue == 0)
            prWarning("Sizeof yields 0");
        freeNodeTree(node->val.np[0]);
        node->op   = CONST;
        node->type     = typeLong; /* long	  */
        node->ptrFlags  = 0;
        node->val.l = sizeValue;
        break;
    }
    return node;
}

/*********************************************************
 * sub_46F7 OK++ PMO     Used in: emitCodeTemplate, isPatternApplicable, strengthReduceMulDivMod
 *			      optimizeExpressionTree
 *********************************************************/
uint8_t log2IfPowerOfTwo(long p1) {
    uint8_t l1;

    if ((p1 & (p1 - 1)) || p1 < 1)
        return 0;
    for (l1 = 0; p1 >>= 1; l1++)
        ;

    return (l1 + 1);
}

/*********************************************************
 * sub_475C OK++ PMO    Used in: emitInitializerData,  sub_E43,  sub_17E0,
 *			     sub_19C1, sub_1B0C, generateCodeForExpr,
 *			     compileExpression, foldConstantExpressions, makeOpNode,
 *			     freeNodeTree, resolveIdentifierNode, dropRightOperand,
 *			     simplifyConversion, optimizeExpressionTree
 *********************************************************/
void freeNodeTree(register node_t *sa) {
    int loc;

    if ((loc = dopetab[sa->op] & 0xC)) {
        freeNodeTree(sa->val.np[0]);
        if (loc == 8)
            freeNodeTree(sa->val.np[1]);
    }
    freeNode(sa);
}

/*********************************************************
 * sub_47B2 OK++ PMO				Used in: selectCodePattern
 * The code optimisers generate many differences in the code
 * however the vast majority relate to the choice of the code
 * fragments to share for returning true/false and generating
 * true/false from != condition
 * I have tried multiple variants of code to get better matches
 * for the current code, the other differences are
 * 1) at m49dc:, code for sub_14FE(node) != 3 is moved
 * 2) case SUB: nodesize(node) == 2 code moved and missed sharing
 *    of code for or a ! sbc hl,de ! jp nz false
 * 3) case DECR: similar to (2)
 * 4) case GADDR: similar to (2)
 * 5) an instance of missed sharing of code
 * 6) instances of inversion of jp conditions with labels also
 *    flipped
 * Note removing the gotos was initially tried, but the optimiser
 * match was poorer. Similarly using compound returns rather
 * than if / break, also produced a poorer match.
 *********************************************************/
uint8_t isPatternApplicable(register node_t *sa, int p2) {
    long l1;

    switch (p2) {
    case MUL_U:
        sa = sa->val.np[1];
        // fallthrough
    case T_SCOLON:
        return sa->val.l >= 1L && sa->val.l < 3L;
    case RPAREN:
        sa = sa->val.np[0];
        // fallthrough
    case MOD:
        if (nodesize(sa) == 2 && !isStructValueNode(sa))
            return true;
        break;
    case BAND:
        if (getTypeClass(sa) == 3)
            return false;
        goto m485f;
    case MUL:
        sa = sa->val.np[0];
        // fallthrough
    case DOLLAR_U:
    m485f:
        if (nodesize(sa) == 4 && !isStructValueNode(sa))
            return true;
        break;
    case SCOLON:
        sa = sa->val.np[0];
        // fallthrough
    case DOLLAR:
        return isStructValueNode(sa);
    case ADD:
        return (uint8_t)sa->val.l == 8 || (uint8_t)sa->val.l == 9;
    case INCR:
        l1 = signExtendToNodeSize(sa, sa->val.l);
        return -128L <= l1 && l1 < 125L;
    case COLON_U:
        return 1L <= sa->val.l && sa->val.l < 5L;
    case COLON_S:
        l1 = sa->val.l;
        if (getTypeClass(sa) == 2 && (l1 & (uint16_t)(1 << ((int16_t)nodesize(sa) << 3))))
            l1 |= (uint16_t) ~((1 << ((int16_t)nodesize(sa) << 3)) - 1);
        return l1 < 0 && l1 >= -4L;
    case LPAREN:
        sa = sa->val.np[1];
        //  fallthrough
    case HASHSIGN:
        return nodesize(sa) == 1 && !isStructValueNode(sa);
    case MINUS_U:
        if (nodesize(sa) == 4)
            goto m49dc;
        break;
    case COMMA:
        if (nodesize(sa) == 2)
        m49dc:
            if (getTypeClass(sa) != 3 && getTypeClass(sa->val.np[0]) != 3)
                return getTypeClass(sa) == 2 || getTypeClass(sa->val.np[0]) == 2;
        break;
    case LT:
        return sa->val.l == 0;
    case CONV:
        if (nodesize(sa) == 4)
        m4a48:
            return getTypeClass(sa) == 1 && getTypeClass(sa->val.np[0]) == 1;
        return false;

    case SUB:
        if (nodesize(sa) == 2)
            goto m4a48;
        break;
    case PLUS_U:
        return 1L == sa->val.l;
    case NOT:
        return log2IfPowerOfTwo(sa->val.np[1]->val.l);
    case NEQL:
        return log2IfPowerOfTwo(~sa->val.np[1]->val.l);
    case COLON:
        if (nodesize(sa) == 4)
            goto m4b02;
        break;
    case DECR:
        if (nodesize(sa) == 2)
            goto m4b02;
        break;

    case GADDR:
        if (nodesize(sa) != 1)
            return false;
    m4b02:
        return (getTypeClass(sa) == 1 || getTypeClass(sa) == 2) && getTypeClass(sa->val.np[0]) == 3;
    case DIV:
        if (nodesize(sa->val.np[0]) == 1)
            goto dotp;
        break;
    case DOT_DOT:
        if (nodesize(sa->val.np[0]) == 2)
            goto dotp;
        break;
    case DOT:
        if (nodesize(sa->val.np[0]) == 4) {
        dotp:
            if (getTypeClass(sa) != 3)
                return false;
            else
                return getTypeClass(sa->val.np[0]) == 1 || getTypeClass(sa->val.np[0]) == 2;
        }
        break;
    case LAND:
        return getTypeClass(sa) == 3;
    }
    return 0;
}

/*********************************************************
 * sub_4B89 OK++ PMO		      Used in: getExprComplexityRank, optimizeExpressionTree

 *********************************************************/
bool isAddressLikeExpr(register node_t *sa) {
    /* Any operator except "#", "..", "CONST" */
    return (dopetab[sa->op] & 0x10) || (sa->op == GADDR && sa->val.np[0]->op == IDOP) ||
           (sa->op == ADD && sa->val.np[1]->op == CONST && isAddressLikeExpr(sa->val.np[0]) != 0);
}

/*********************************************************
 * sub_4BE5 OK++ PMO			Used in: optimizeExpressionTree
 *********************************************************/
bool isZeroConst(register node_t *sa) {

    return sa->op == CONST && sa->val.l == 0;
}

/*********************************************************
 * sub_4C12++ PMO			Used in: optimizeExpressionTree
 *********************************************************/
int getExprComplexityRank(register node_t *sa) {
    if (sa->op == GADDR && sa->val.np[0]->op == IDOP)
        return 1;
    if (dopetab[sa->op] & 0x10)
        return 0; /* if "#", "..", "CONST"  */
    if (isAddressLikeExpr(sa))
        return 1;
    return dopetab[sa->op] & 0xF;
}

/*********************************************************
 * sub_4C6D OK++ PMO				Used in: rewriteExprForCodegen
 * bool causes optimiser to use ld l, rather than ld hl
 *********************************************************/
bool isRegisterIndirection(node_t *p1a) {
    return p1a->val.np[0]->op == USEREG;
}

/*********************************************************
 * sub_4C8B OK++ PMO			Used in: optimizeExpressionTree
 * makeOpNode using bool as first parameter is optimised
 * but misses ex (sp),hl rather than pop bc ! push hl
 *********************************************************/
node_t *simplifyLogicalNot(register node_t *sa) {
    node_t *l1;

    l1 = sa->val.np[0];
    if (sa->val.np[0]->op == NOT) {
        l1 = l1->val.np[0];
        freeNode(sa->val.np[0]);
        freeNode(sa);
        return l1;
    }
    if ((dopetab[l1->op] & 0x12C) == 0x28) {
        freeNode(sa);
        l1->op = invertTest(l1->op);
        return l1;
    }
    if (dopetab[l1->op] & 0x20) {
        l1->val.np[0] = makeOpNode(NOT, l1->val.np[0], (node_t *)0);
        l1->val.np[1] = makeOpNode(NOT, l1->val.np[1], (node_t *)0);
        freeNode(sa);
        l1->op = l1->op == LAND ? LOR : LAND;
        return l1;
    }
    return sa;
}

/*********************************************************
 * sub_4DA3 OK++ PMO			Used in: optimizeExpressionTree
 * makeOpNode using bool as first parameter is optimised
 * but misses ex (sp),hl rather than pop bc ! push hl
 *********************************************************/
node_t *resolveIdentifierNode(register node_t *sa) {
    node_t *l1a;

    if (sa->val.mp[0]->StorageClass == 1) {
        l1a        = makeConstNode(sa->val.mp[0]->offset);
        l1a->type    = sa->type;
        l1a->ptrFlags = sa->ptrFlags;
        freeNodeTree(sa);
        markPointerType(l1a);
        sa         = allocNode();
        *sa        = *l1a;
        sa->op   = USEREG;
        sa->val.l = 8L;
        sa         = makeOpNode(ADD, sa, l1a);
        return makeOpNode(MUL_U, sa, 0);
    }
    if (sa->val.mp[0]->StorageClass == 2) {
        sa->op   = USEREG;
        sa->val.l = sa->val.mp[0]->payload.regIdx;
    }
    return sa;
}

/*********************************************************
 * sub_4E8D OK++ PMO 			Used in: optimizeExpressionTree
 * makeOpNode using bool as first parameter is optimised
 * but misses ex (sp),hl rather than pop bc ! push hl
 *********************************************************/
node_t *rewriteMemberAccess(register node_t *sa) {
    node_t *l1a;

    if (dopetab[(l1a = sa->val.np[0])->op] & 0x1000) {
        l1a->type        = sa->type;
        l1a->ptrFlags     = sa->ptrFlags;
        sa->val.np[0] = l1a = makeOpNode(GADDR, l1a, 0);
    } else {
        l1a       = allocNode();
        *l1a      = *sa;
        l1a->op = TYPE;
        markPointerType(l1a);
        sa->val.np[0] = makeOpNode(CONV, makeOpNode(GADDR, sa->val.np[0], 0), l1a);
    }
    sa->type                = l1a->type;
    sa->ptrFlags             = l1a->ptrFlags;
    sa->val.np[1]->ptrFlags = sa->ptrFlags;
    sa->val.np[1]->type    = sa->type;
    sa->op              = ADD;
    return makeOpNode(MUL_U, sa, 0);
}

/*********************************************************
 * sub_4FA8 OK++ PMO			Used in: optimizeExpressionTree
 *********************************************************/
node_t *dropRightOperand(register node_t *sa) {

    freeNodeTree(sa->val.np[1]);
    freeNode(sa);
    return sa->val.np[0];
}

/*********************************************************
 * sub_4FCE OK++ OK				Used in: optimizeExpressionTree
 *
 *********************************************************/
node_t *strengthReduceMulDivMod(register node_t *sa) {

    switch (sa->op) {
    case MUL:
        sa->op = LSHIFT;
        break;
    case ASMUL:
        sa->op = ASLSHIFT;
        break;
    case DIV:
        if (getTypeClass(sa) != 2)
            return sa;
        sa->op = RSHIFT;
        break;
    case ASDIV:
        if (getTypeClass(sa) != 2)
            return sa;
        sa->op = ASRSHIFT;
        break;
    case ASMOD:
        sa->op = ASAND;
        sa->val.np[1]->val.l--;
        return sa;
    case MOD:
        sa->op = BAND;
        sa->val.np[1]->val.l--;
        return sa;
    }
    byte_B013              = true;
    sa->val.np[1]->val.l = log2IfPowerOfTwo(sa->val.np[1]->val.l) - 1;
    return sa;
}

/*********************************************************
 * sub_508A OK++ PMO			Used in: optimizeExpressionTree
 * optimiser optimises code for parameter 1 of makeOpNode
 *********************************************************/
node_t *simplifyConversion(register node_t *sa) {
    node_t *l1a;
    node_t *l2a;
    char buf[15];
    long l3;

    if (getTypeClass(sa) == 3 && sa->val.np[0]->op == CONST) {
        l3 = sa->val.np[0]->val.l;
        freeNode(sa->val.np[0]);
        freeNode(sa->val.np[1]);
        sprintf(buf, "%ld", l3);
        sa->val.sv.s = allocMem(strlen(buf) + 1); /* create string */
        strcpy(sa->val.sv.s, buf);
        sa->val.sv.v = newLocal();
        sa->op      = FCONST;
        return sa;
    }
    if ((dopetab[(l1a = sa->val.np[0])->op] & 0x1000) && nodesize(l1a) >= nodesize(sa) &&
        getTypeClass(sa) != 3 && getTypeClass(l1a) != 3) {
        l1a->type    = sa->type;
        l1a->ptrFlags = sa->ptrFlags;
        freeNode(sa->val.np[1]);
        freeNode(sa);
        return l1a;
    }
    if (isSameTypeAndSize(sa, l1a)) {
        freeNodeTree(sa->val.np[1]);
        l1a->type    = sa->type;
        l1a->ptrFlags = sa->ptrFlags;
        freeNode(sa);
        return l1a;
    }
    if (nodesize(l1a) < nodesize(sa))
        return sa;
    if (l1a->op == CONV && nodesize(l1a->val.np[0]) >= nodesize(sa)) {
        if (isSameTypeAndSize(sa, l1a->val.np[0]) ||
            (getTypeClass(sa) == getTypeClass(l1a) && getTypeClass(sa) == getTypeClass(l1a->val.np[0]))) {
            sa->val.np[0] = l1a->val.np[0];
            freeNode(l1a->val.np[1]);
            freeNode(l1a);
            return sa;
        }
    }
    if ((dopetab[l1a->op] & 0xC00) == 0 || getTypeClass(l1a) == 3)
        return sa;

    if ((dopetab[l1a->op] & 0x400) &&
        (l1a->val.np[0]->op != CONV || nodesize(l1a->val.np[0]->val.np[0]) >= nodesize(l1a)))
        return sa;

    l2a = makeOpNode(CONV, l1a->val.np[0], sa->val.np[1]);
    *sa = *sa->val.np[1];
    if (dopetab[l1a->op] & 8) {
        sa = makeOpNode(CONV, l1a->val.np[1], sa);
    } else {
        freeNode(sa);
        sa = 0;
    }
    l2a = makeOpNode((uint8_t)l1a->op, l2a, sa);
    freeNode(l1a);
    return l2a;
}

/*********************************************************
 * sub_53EE  OK++ PMO			Used in: optimizeExpressionTree
 *********************************************************/
node_t *collapseAddressDereference(register node_t *sa) {
    node_t *l1a;

    if (dopetab[(l1a = sa->val.np[0])->val.np[0]->op] & 0x1000) {
        l1a        = l1a->val.np[0];
        l1a->type    = sa->type;
        l1a->ptrFlags = sa->ptrFlags;
        freeNode(sa->val.np[0]);
        freeNode(sa);
        return l1a;
    }
    sa->op       = CONV;
    sa->val.np[1] = l1a;
    sa->val.np[0] = l1a->val.np[0];
    l1a->op      = TYPE;
    l1a->type        = sa->type;
    l1a->ptrFlags     = sa->ptrFlags;
    byte_B013      = true;
    return sa;
}

/* end of file tree3.c */
/*
 * File - local1s.c
 */

#ifndef _CGEN_H
#define MINI
#include "cgen.h"

node_t *allocNode(void);
uint16_t nodesize(node_t *);
uint8_t getTypeClass(node_t *);
node_t *makeConstNode(long);
node_t *makeOpNode(uint8_t, node_t *, node_t *);
uint8_t log2IfPowerOfTwo(long);
bool isAddressLikeExpr(node_t *);
bool isZeroConst(node_t *);
int getExprComplexityRank(node_t *);
node_t *simplifyLogicalNot(node_t *);
node_t *resolveIdentifierNode(node_t *);
node_t *rewriteMemberAccess(node_t *);
node_t *dropRightOperand(node_t *);
node_t *strengthReduceMulDivMod(node_t *);
node_t *simplifyConversion(node_t *);
node_t *collapseAddressDereference(node_t *);
bool fitsInTargetType(node_t *, node_t *);
bool isSameTypeAndSize(node_t *, node_t *);
bool constFitsComparisonRange(node_t *, node_t *);
#endif

/*********************************************************
 * sub_54B6 - OK++ PMO	Used in: optimizeExpression
 * needs ported optimiser to build
 * Optimiser differences
 * 1) in the GT ? GEQ : LT the GEQ assignment is moved
 * 2) in MUL_U, the optimiser uses bc rather than hl, then
 *    does hl = bc
 *********************************************************/
node_t *optimizeExpressionTree(register node_t *node) {
    node_t *tempNode;
    node_t *convNode;
    int operandKind;
    uint32_t valueMask;

    operandKind = dopetab[node->op] & 0xC;
    if (operandKind != 0)
        node->val.np[0] = optimizeExpressionTree(node->val.np[0]);

    if (operandKind == 8)
        node->val.np[1] = optimizeExpressionTree(node->val.np[1]);

    if (dopetab[node->op] & 0x40) {
        if (getExprComplexityRank(node->val.np[0]) < getExprComplexityRank(node->val.np[1])) {
            byte_B013      = true;
            tempNode            = node->val.np[0];
            node->val.np[0] = node->val.np[1];
            node->val.np[1] = tempNode;
        }
        if ((dopetab[node->op] & 0x2000) && node->op == node->val.np[0]->op) {
            if (isAddressLikeExpr(node->val.np[1]) && isAddressLikeExpr((tempNode = node->val.np[0])->val.np[1])) {
                byte_B013       = true;
                node->val.np[0]  = tempNode->val.np[1];
                tempNode->val.np[1] = node;
                node              = tempNode;
            } else if (getExprComplexityRank(node->val.np[0]->val.np[1]) < getExprComplexityRank(node->val.np[1])) {
                byte_B013                  = true;
                tempNode                        = node->val.np[1];
                node->val.np[1]             = node->val.np[0]->val.np[1];
                node->val.np[0]->val.np[1] = tempNode;
            }
        }
    }

    if ((dopetab[node->op] & 0xC00) == 0x800 && node->val.np[0]->op == CONV &&
        nodesize(node->val.np[0]->val.np[0]) < nodesize(node) &&
        fitsInTargetType(node->val.np[1], node->val.np[0]->val.np[0])) {

        convNode                   = node->val.np[0];
        node->val.np[0]        = convNode->val.np[0];
        node->type                = node->val.np[0]->type;
        node->ptrFlags             = node->val.np[0]->ptrFlags;
        node->val.np[1]->type    = node->type;
        node->val.np[1]->ptrFlags = node->ptrFlags;
        convNode->val.np[0]       = node;
        node                    = convNode;
    }

    if ((dopetab[node->op] & 0x420) == 0x420 && (tempNode = node->val.np[0])->op == CONV &&
        nodesize(tempNode->val.np[0]) != 0 && nodesize(tempNode->val.np[0]) < nodesize(tempNode)) {
        if (node->val.np[1]->op == CONST &&
            (getTypeClass(tempNode) == 1 || getTypeClass(tempNode->val.np[0]) == 2)) {
            if (constFitsComparisonRange(node->val.np[0], node->val.np[1])) {
                freeNode(node->val.np[0]);
                freeNode(node->val.np[0]->val.np[1]);
                node->val.np[0]        = node->val.np[0]->val.np[0];
                node->val.np[1]->type    = node->val.np[0]->type;
                node->val.np[1]->ptrFlags = node->val.np[0]->ptrFlags;
            } else
                warningMsg = "mismatched comparision"; /* m8: */
        } else if (node->val.np[1]->op == CONV &&
                   isSameTypeAndSize(node->val.np[0]->val.np[0], node->val.np[1]->val.np[0])) {
            tempNode            = node->val.np[0];
            node->val.np[0] = tempNode->val.np[0];
            freeNode(tempNode->val.np[1]);
            freeNode(tempNode);
            tempNode            = node->val.np[1];
            node->val.np[1] = tempNode->val.np[0];
            freeNode(tempNode->val.np[1]);
            freeNode(tempNode);
        }
    }

    switch (node->op) {
    case IDOP:
        return resolveIdentifierNode(node);
    case DOT:
        return rewriteMemberAccess(node);
    case NOT:
        return simplifyLogicalNot(node);
    case LT:
    case GEQ:
        if (getTypeClass(node->val.np[0]) == 2 && isZeroConst(node->val.np[1])) {
            warningMsg = "degenerate unsigned comparision";
            freeNodeTree(node);
            node = makeConstNode(node->op == GEQ ? 1L : 0L);
        }
        break;
    case LEQ:
    case GT:
        if (getTypeClass(node->val.np[0]) == 2 && isZeroConst(node->val.np[1]))
            node->op = node->op == GT ? NEQL : EQL;
        else if (node->val.np[1]->op == CONST) {
            node->val.np[1]->val.l += 1;
            node->op = node->op == GT ? GEQ : LT;
        } else {
            tempNode            = node->val.np[0];
            node->val.np[0] = node->val.np[1];
            node->val.np[1] = tempNode;
            node->op       = node->op != GT ? GEQ : LT;
        }
        break;
    case ASEOR:
    case BOR:
        if (node->val.np[1]->op == CONST && node->val.np[1]->val.l == -1L) {
            freeNodeTree(node->val.np[0]);
            freeNode(node);
            return node->val.np[1];
        }
        /* fall through */
    case ADD:
    case SUB:
    case LSHIFT:
    case ASADD:
    case ASSUB:
    case ASLSHIFT:
    case ASRSHIFT:
    case RSHIFT:
        if (node->val.np[1]->op == CONST && node->val.np[1]->val.l == 0L)
            return dropRightOperand(node);

        if ((dopetab[node->op] & 0x80) && nodesize(node->val.np[1]) != 1) {
            tempNode            = allocNode();
            tempNode->type        = getTypeClass(node->val.np[1]) == 2 ? typeUChar : typeChar;
            tempNode->op      = TYPE;
            node->val.np[1] = makeOpNode(CONV, node->val.np[1], tempNode);
        }
        break;
    case MUL:
    case DIV:
    case ASMUL:
    case ASDIV:
        if (node->val.np[1]->op == CONST && node->val.np[1]->val.l == 1L)
            return dropRightOperand(node);
        /* fall through */
    case MOD:
    case ASMOD:
        if (node->val.np[1]->op == CONST && log2IfPowerOfTwo(node->val.np[1]->val.l) != 0)
            return strengthReduceMulDivMod(node);
        /* fall through */
    case BAND:
    case ASAND:
        if (node->val.np[1]->op == CONST && node->val.np[1]->val.l == 0L)
            switch (node->op) {
            case MOD:
            case DIV:
            case ASMOD:
            case ASDIV:
                prWarning("Division by zero");
                return node;
            case BAND:
            case MUL:
                freeNodeTree(node->val.np[0]);
                freeNodeTree(node->val.np[1]);
                node->op   = CONST;
                node->val.l = 0;
                return node;
            case ASAND:
            case ASMUL:
                node->op = ASSIGN;
                return node;
            }
        valueMask = nodesize(node) >= 4 ? -1L : (1L << (nodesize(node) * 8)) - 1;
        if ((node->op == BAND || node->op == ASAND) && node->val.np[1]->op == CONST &&
            valueMask == (node->val.np[1]->val.l & valueMask))
            return dropRightOperand(node);
        break;
    case CONV:
        return simplifyConversion(node);
    case PLUS_U:
        freeNode(node);
        node = node->val.np[0];
        break;
    case GADDR:
        if (node->val.np[0]->op == MUL_U)
            return collapseAddressDereference(node);
        break;
    case MUL_U:
        if (node->val.np[0]->op == GADDR) {
            tempNode = node->val.np[0]->val.np[0];
            if (tempNode->op != LPAREN && tempNode->op != ASSIGN && tempNode->op != QUEST)
                return collapseAddressDereference(node);
        }
        break;
    }
    return node;
}

/* end of file local1s.c */
/*
 * File - local2.c
 */

/*********************************************************
 * sub_5CF5 OK++ PMO			Used in: leaveBlock, sub_17E0
 *
 *********************************************************/
void allocateOrEmitVariable(register member_t *sb, int p2) {

    switch (sb->StorageClass) {
    case 1:
        if (assignVariableToRegister(sb, p2) == 0) {
            array_AE13[lvlidx] -= sb->typeSize;
            if ((sb->offset = array_AE13[lvlidx]) < -128 && sb->typeSize <= 4)
                prWarning("%s: large offset", sb->name);
        }
        break;
    case 5:
        sb->offset = array_AE97[lvlidx];
        array_AE97[lvlidx] += sb->typeSize;
        if (sb->typeSize == 1 && sb->typeDesc->symKind != STRUCT && sb->typeDesc->symKind != UNION)
            array_AE97[lvlidx]++;

        if (!assignVariableToRegister(sb, p2))
            sb->StorageClass = 1;
        break;
    case 3:
    case 4:
        emitBssDefinition(sb);
        break;
    }
}

/*********************************************************
 * sub_5DF6 OK++ PMO			Used in: optimizeExpression
 * parameter 1 of makeOpNode optimised
 *********************************************************/
node_t *normalizeUnaryMinusAndSub(register node_t *sa) {
    char l1;
    char *l2;

    l1 = dopetab[sa->op] & 0xC;
    if (l1 == 8)
        sa->val.np[1] = normalizeUnaryMinusAndSub(sa->val.np[1]);
    if (l1 != 0)
        sa->val.np[0] = normalizeUnaryMinusAndSub(sa->val.np[0]);

    switch (sa->op) {
    case SUB:
    case ASSUB:
        if (sa->val.np[1]->op == CONST)
            sa->val.np[1]->val.l = -sa->val.np[1]->val.l;
        else
            sa->val.np[1] = makeOpNode(MINUS_U, sa->val.np[1], 0);
        sa->op = sa->op == SUB ? ADD : ASADD;
        break;
    case MINUS_U:
        if (sa->val.np[0]->op == MINUS_U) {
            freeNode(sa);
            sa = sa->val.np[0];
            freeNode(sa);
            sa = sa->val.np[0];
        }
        if (sa->val.np[0]->op == FCONST) {
            freeNode(sa);
            sa = sa->val.np[0];
            l2 = allocMem(strlen(sa->val.sv.s) + 2);
            strcat(strcpy(l2, "-"), sa->val.sv.s);
            free(sa->val.sv.s);
            sa->val.sv.s = l2;
        }
    }
    return sa;
}

/*********************************************************
 * sub_5F52 OK++ PMO			Used in: optimizeExpression
 *********************************************************/
node_t *normalizeAddSubForms(register node_t *sa) {
    char l1;
    node_t *l2;

    l1 = dopetab[sa->op] & 0xC;
    if (l1 == 8)
        sa->val.np[1] = normalizeAddSubForms(sa->val.np[1]);
    if (l1 != 0)
        sa->val.np[0] = normalizeAddSubForms(sa->val.np[0]);

    switch (sa->op) {
    case ADD:
        if (sa->val.np[0]->op == MINUS_U) {
            l2             = sa->val.np[0];
            sa->val.np[0] = sa->val.np[1];
            sa->val.np[1] = l2;
        }
        // fall through
    case ASADD:
        if (sa->val.np[1]->op == MINUS_U) {
            freeNode(sa->val.np[1]);
            sa->val.np[1] = sa->val.np[1]->val.np[0];
            sa->op       = sa->op == ASADD ? ASSUB : SUB;
        }
    }

    return sa;
}

/*********************************************************
 * sub_600E OK++ PMO     Used in: sub_793,  emitInitializerData,  sub_E43,
 *                            sub_17E0, sub_19C1, sub_1B0C,
 *			      compileExpression
 *********************************************************/
node_t *optimizeExpression(register node_t *sa) {

    // int upperBound; /* Not used */

    warningMsg = 0;
    sa         = normalizeUnaryMinusAndSub(sa);
    // upperBound    = 0; /* Not used */
    do {
        byte_B013 = false;
        /*
              Excluded part optimization code
              present in the DOS version (3.06)
        */
        sa = foldConstantExpressions(optimizeExpressionTree(sa));
    } while (byte_B013);

    if (warningMsg)
        prWarning(warningMsg);

    return normalizeAddSubForms(sa);
}

/*********************************************************
 * sub_605E OK++ PMO				Used in: simplifyLogicalNot
 *
 *********************************************************/

int invertTest(int op) {

#ifdef DEBUG
    printf("\tinvertTest(%d)\n", op);
#endif

    switch (op) {
    case EQL:
        return NEQL;
    case NEQL:
        break;
    case LT:
        return GEQ;
    case LEQ:
        return GT;
    case GEQ:
        return LT;
    case GT:
        return LEQ;
    }
    return EQL;
}

/*********************************************************
 * sub_60A8 OK++ PMO				Used in: optimizeExpressionTree
 *
 *********************************************************/
bool fitsInTargetType(register node_t *sa, node_t *p2a) {
    long l1;

    if (sa->op != 'C')
        return 0;
    if (nodesize(p2a) >= 4)
        return sa->val.l >= 0 || getTypeClass(p2a) == 1;

    l1 = (uint16_t)(1 << (nodesize(p2a) * 8));
    if (getTypeClass(p2a) == 2) {
        if (sa->val.l < 0)
            return 0;
    } else {
        l1 /= 2;
        if (sa->val.l < 0)
            return sa->val.l >= -l1;
    }
    return sa->val.l < l1;
}

/*********************************************************
 * sub_61AA OK++ PMO			Used in: allocateOrEmitVariable
 *********************************************************/
bool assignVariableToRegister(register member_t *sb, int p2) {

    if (!rflag && isupper(p2) && sb->indirFlags == 1 && sb->elemCount <= 1) {
        if (findRegisterMatch(word_B017, 9) == 0)
            return false;
        if (sb->StorageClass == 5)
            sb->storageFlags |= 4;
        sb->StorageClass   = 2;
        sb->payload.regIdx = findRegisterMatch(word_B017, 9);
        word_B017 &= ~registerMaskById[sb->payload.regIdx];
        return true;
    }

    return false;
}

/*********************************************************
 * sub_6246 OK++ PMO	      Used in: simplifyConversion, optimizeExpressionTree
 *********************************************************/
bool isSameTypeAndSize(node_t *p1a, node_t *p2a) {

    return nodesize(p1a) == nodesize(p2a) && getTypeClass(p1a) == getTypeClass(p2a);
}

/*********************************************************
 * sub_628F OK++ PMO
 *********************************************************/
bool areBothSigned(node_t *p1a, node_t *p2a) {
    return getTypeClass(p1a) == 1 && getTypeClass(p2a) == 1;
}

/*********************************************************
 * sub_62BE OK++ PMO			Used in: optimizeExpressionTree
 *********************************************************/
bool constFitsComparisonRange(register node_t *comparisonNode, node_t *constNode) {
    long upperBound, lowerBound;
    char bitCount;

    bitCount = nodesize(comparisonNode->val.np[0]) * 8;
    if (bitCount >= 32)
        return true;
    upperBound = 1L << bitCount;
    lowerBound = 0;
    if (areBothSigned(comparisonNode, comparisonNode->val.np[0])) {
        upperBound /= 2;
        lowerBound = -upperBound;
    }
    return lowerBound <= constNode->val.l && constNode->val.l < upperBound;
}

/* macros to make reading the code easier */
/* clang-format off */
/* don't reformat as hitech cpp includes the extra spaces
   which can cause line overflow
*/
#ifndef TOPBIT
#define TOPBIT 0x8000
#define TopBitSet(selectedReg) ((selectedReg)&TOPBIT)
#define MapVal(selectedReg) (TopBitSet(selectedReg)?~(selectedReg):registerMaskById[selectedReg])
#endif
/* clang-format on */
/*********************************************************
 * sub_63B8 OK++ PMO				Used in: selectCodePattern
 *
 *********************************************************/
uint8_t selectCompatibleRegister(int candidateMask, int requiredMatch, int targetClass) {
    uint8_t selectedReg;
    uint8_t candidateReg;
    int fallbackReg;
    register uint8_t *classOptions;

    targetClass &= ~0x40;
    selectedReg = 0;

    if (requiredMatch == 0)
        selectedReg = findRegisterMatch(candidateMask, targetClass);
    else if (requiredMatch & 0x8000)
        selectedReg = findRegisterMatch(MapVal(requiredMatch) & candidateMask, targetClass);
    else if (targetClass < 24) {
        if ((selectedReg = findRegisterMatch(MapVal(requiredMatch) & candidateMask, targetClass)) == 0 && (fallbackReg = findRegisterMatch(candidateMask, targetClass)) != 0 &&
            findRegisterMatch(MapVal(fallbackReg), requiredMatch) != 0)
            selectedReg = fallbackReg;
    } else {
        fallbackReg = 6;
        classOptions = &array_AB54[(targetClass - 24) * 6];
        while (*classOptions && fallbackReg-- != 0)
            if ((candidateReg = findRegisterMatch(candidateMask, *classOptions++)) != 0 &&
                (findRegisterMatch(registerMaskById[candidateReg], requiredMatch) != 0 || findRegisterMatch(registerMaskById[requiredMatch], candidateReg) != 0)) {
                selectedReg = candidateReg;
                break;
            }
    }
    return selectedReg;
}

/*********************************************************
 * sub_6589 OK++ PMO    Used in: selectCodePattern, chooseResultRegister, assignVariableToRegister,
 *			     selectCompatibleRegister, mergeRegisterConstraints
 * Optimiser improves on
 *      ld a,(ix-1) ! add a,255 ! ld (ix-1),a ! or a
 * with dec (ix-1)
 *********************************************************/
uint8_t findRegisterMatch(int availableMask, int requestedClass) {
    char remainingChoices;
    uint8_t *classRegList;

    requestedClass &= ~0x40;
    if (requestedClass < 24) {
        if ((availableMask & registerMaskById[requestedClass]) == registerMaskById[requestedClass])
            return requestedClass;
        else
            return 0;
    }

    requestedClass -= 24;
    remainingChoices = 6;
    classRegList     = &array_AB54[requestedClass * 6];

    do {
        if (*classRegList != 0 &&
            (availableMask & registerMaskById[*classRegList]) == registerMaskById[*classRegList])
            return *classRegList;
    } while (*++classRegList && --remainingChoices != 0);

    return 0;
}

/*********************************************************
 * sub_665B OK++ PMO			Used in: mergeRegisterConstraints
 *********************************************************/
uint16_t mapRegisterAlias(uint16_t p1, uint8_t p2) {
    uint16_t loc;

    if (p1 == 0)
        return 0;
    p2 -= 48;
    for (loc = 1; loc < 24; loc++)
        if (registerAliasBySuffix[loc * 2 + p2] == p1)
            return loc;
    return 0;
}

/*********************************************************
 * sub_66BC OK++ PMO			Used in: selectCodePattern
 * Optimiser passes param 2 as uint8_t rather than promoting
 * to int
 *********************************************************/

int mergeRegisterConstraints(int existingConstraint, int newConstraint, int availableMask,
                             char *aliasSuffixes) {
    int16_t mergedMaskOrReg;
    int mergedConstraint;
    char *suffixPtr;

    mergedConstraint = 0;
    if ((newConstraint & 0x8000) != 0) {
        if (existingConstraint == 0)
            mergedConstraint = newConstraint;
        else if ((mergedMaskOrReg = findRegisterMatch(((newConstraint & 0x8000)
                                                           ? ~newConstraint
                                                           : registerMaskById[newConstraint]) &
                                                          availableMask,
                                                      existingConstraint)) != 0)
            mergedConstraint = mergedMaskOrReg;
        else
            mergedConstraint = findRegisterMatch(availableMask, existingConstraint);
    } else if (existingConstraint == 0) {
        if (newConstraint == 0 || aliasSuffixes == 0)
            mergedConstraint = newConstraint;
        else {
            for (suffixPtr = aliasSuffixes; isdigit(suffixPtr[1]); suffixPtr++)
                ;
            if (newConstraint >= 24 &&
                (newConstraint = findRegisterMatch(availableMask, newConstraint)) == 0)
                mergedConstraint = 0;
            else {
                do {
                    newConstraint = mapRegisterAlias(newConstraint, (uint8_t)*suffixPtr);
                } while (suffixPtr-- != aliasSuffixes);
                mergedConstraint = newConstraint;
            }
        }
    } else if (newConstraint == 0)
        mergedConstraint = existingConstraint;
    else {
        mergedMaskOrReg =
            ((existingConstraint & 0x8000) ? ~existingConstraint
                                           : registerMaskById[existingConstraint]) &
            ((newConstraint & 0x8000) ? ~newConstraint : registerMaskById[newConstraint]);

        if (((existingConstraint & 0x8000)
                 ? ~existingConstraint
                 : registerMaskById[existingConstraint]) == mergedMaskOrReg)
            mergedConstraint = existingConstraint;
        else if (((newConstraint & 0x8000) ? ~newConstraint : registerMaskById[newConstraint]) ==
                 mergedMaskOrReg)
            mergedConstraint = newConstraint;
        else
            mergedConstraint = findRegisterMatch(mergedMaskOrReg, existingConstraint);
    }
    return mergedConstraint;
}
/* end of local2.c*/
/*
 * File - main.c
 */
/*********************************************************
 * main OK++ PMO
 *
 *********************************************************/
int main(int argc, char **argv) {
    CHK_SHOW_VERSION(argc, argv);
#ifdef CPM
    baseHeap = sbrk(0); /* Current highest memory */
#endif
    --argc, ++argv;
    while (argc > 0 && **argv == '-') { /* Parsing options */
        switch (argv[0][1]) {
#if 0
        case 'P':
        case 'p':
            pflag = true;
            break; /* Not use */
#endif
        case 'W':
        case 'w':
            wflag = true;
            break; /* Displaying warnings */
        case 'R':
            rflag = true;
            break;
#if 0
        case 'B':
            bflag = true;
            break; /* Not use */
        case 'E':
            eflag = true;
            break; /* Not use */
        case 'H':
            hflag = true;
            break; /* Not use */
#endif
        default:
            fatalErr("Illegal\tswitch %c", argv[0][1]);
            break;
        }
        argv++, argc--;
    }
    if (argc-- > 0) {
        if (freopen(*argv, "r", stdin) == NULL) /* Open input file */
            fatalErr("Can't open %s", *argv);
        else if (argc > 0 && freopen(argv[1], "w", stdout) == NULL) /* Open output file */
            fatalErr("Can't create %s", argv[1]);
    }
    initializeTypesAndSymbols();                  /* First_init */
    parseStmt();                 /* Compiling intermediate code */
    if (fclose(stdout) == EOF) { /* Close output file */
        prError("Error closing output file");
    }
    /* Exit with error code */
    exit(errcnt != 0); /* Generated code is not significantly different */
}

/*
 * To comply with C standard functions are replaced with similar
 * ones with a variable number of parameters
 */

/*********************************************************
 * sub_6AA2 OK PMO     Used in: badIntCode,  sub_17E0, sub_19C1,
 *			      generateCodeForExpr, sub_4192, sub_6B1D,
 * fatalErr error  	      sub_6B9B,
 * Difference due to change to use stdarg
 *********************************************************/
_Noreturn void fatalErr(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    prMsg(fmt, args);
    va_end(args);
    fclose(stdout);
    exit(2);
}

/*********************************************************
 * sub_6AD0  OK PMO  Used in: sub_E43,  compileExpression, makeOpNode,
 * Warning message	      optimizeExpressionTree, allocateOrEmitVariable, optimizeExpression
 * Difference due to change to use stdarg
 *********************************************************/
void prWarning(char *fmt, ...) {
    va_list args;

    if (wflag == 0) {
        fprintf(stderr, "%s:%d:\t", progname, lineno);
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
        fprintf(stderr, " (warning)\n");
    }
}

/*********************************************************
 * prError OK PMO
 * Nonfatal error
 * Difference due to use of stdarg
 *********************************************************/
void prError(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    prMsg(fmt, args);
    va_end(args);
    if (++errcnt >= MAXERR)
        fatalErr("Too many errors");
}

/*********************************************************
 * prMsg OK PMO	      	  Used in: ferror, prError
 * Difference due to use of stdarg
 *********************************************************/
void prMsg(char *fmt, va_list args) {
    fprintf(stderr, "%s:%d:\t", progname, lineno);
    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
}

/*********************************************************
 * allocMem OK    Used in: getOrCreateSymbol,  getOrCreateScopedSymbol, sub_19C1,
 *			     sub_1B0C, allocNode, sub_39CA,
 * alloc_mem & return ptr    sub_4192, simplifyConversion, normalizeUnaryMinusAndSub
 *********************************************************/
void *allocMem(size_t size) {
    register char *ptr;

    do {
        if ((ptr = malloc(size)))
            goto done;
    } while (releaseNodeFreeList());
    fatalErr("No room");
done:
    blkclr(ptr, size);
    return ptr;
}

/* end of file main.c */
/*
 * File - malloc.c Created 09.03.2019 Last Modified 30.05.2020
 */

#ifdef CPM
static uint8_t *freeList; /* wB024 */

#define Len(p)     (uint16_t)((p)[-1] & 0x80 ? *(uint16_t *)((p)-3) : (p)[-1])
/* get the real start of the reserved block */
#define BlkAddr(p) ((p)[-1] & 0x80 ? ((p)-3) : (p)-1)
#define Link(p)    (*(uint8_t **)(p))
/*
 * the memory allocator reserves multiple blocks of memory
 * each block is stored as
 * [block size][data]
 * next points to the next allocated memory block
 * block size is encoded as 0-127 for data lengths 1-128
 * other wise (length - 3) as a word and a flag byte of 0x80
 *
 * When freed the data is replaced by a pointer to the next largest
 * free block.
 * The above implies that a minimum data length is sizeof(uint8_t *)
 *
 */
/* encode the data block size. Return the pointer to the data
 * note the passed in size should account for the block size header
 * and the minimum data length
 */
static uint8_t *setSize(register uint8_t *p, short size) {
    if (size > 0x80) {
        *((uint16_t *)p) = size - 3;
        p += 3;
        p[-1] = 0x80;
    } else {
        *p = (uint8_t)size - 1;
        p++;
    }
    return p;
}

static bool pack() {
    uint8_t *loblk;
    uint8_t *hiblkAddr;
    uint8_t **curLo;
    uint8_t **curHi;
    bool packed;
    register uint8_t *hiblk;

    packed = false;
rescan:
    for (curHi = &freeList; hiblk = *curHi; curHi = &Link(hiblk)) {
        hiblkAddr = BlkAddr(hiblk); /* optimised over original */
        for (curLo = &freeList; loblk = *curLo; curLo = &Link(loblk)) {
            if (hiblkAddr != loblk + Len(loblk)) /* loop until we find adjacent blocks */
                continue;
            /* unlink the blocks to be joined */
            if (&Link(hiblk) == curLo)      /* free list order is hi lo next */
                *curHi = Link(loblk);       /* move the next val to the hi block */
            else if (curHi == &Link(loblk)) /* free list order is low hi next */
                *curLo = Link(hiblk);       /* move the next val to the lo block */
            else {                          /* not adjacent in freelist */
                *curLo = Link(loblk);       /* move the lo -> next val */
                *curHi = Link(hiblk);       /* move the hi -> next val */
            }
            loblk = BlkAddr(loblk); /* make sure we also include the header */
            free(setSize(loblk, hiblk + Len(hiblk) - loblk)); /* join the blocks */
            packed = true;
            goto rescan;
        }
    }
    /* Bug? the original code unintentionally returned int(curHi) + 1 */
    return packed;
}

/*********************************************************
 * malloc v2 OK			Used in: allocMem
 *********************************************************/
void *malloc(size_t size) {
    uint8_t *upperBound;
    size_t tokenText;
    bool done;
    register uint8_t *sst;

    if (size < sizeof(uint8_t *))
        size = sizeof(uint8_t *);
    done = false;
    /*
     * see if we can find a suitable previously allocated block
     * if not consolidate and try again
     * failing that allocate a new block
     */
    do {
        for (sst = (uint8_t *)&freeList; upperBound = Link(sst); sst = upperBound) {
            if (Len(upperBound) >= size) {
                Link(sst) = Link(upperBound);
                sst       = upperBound;
                /* if splitting the block would leave sufficient space
                 * for a new block regIdx.e. header + data/pointer then split it */
                if ((tokenText = Len(sst)) > size + 2 + sizeof(uint8_t *)) { /* ? +1 ok */
                    upperBound = sst + size;
                    free(setSize(upperBound, tokenText - size));
                    sst = BlkAddr(sst);
                    return setSize(sst, size);
                } else
                    return sst;
            }
        }
    } while (!done && (done = pack()));
    tokenText = size < 128 ? 1 : 3; /* size of block header */
    if ((sst = sbrk(size + tokenText)) == (uint8_t *)-1)
        return 0;

    return setSize(sst, size + tokenText);
}

/*********************************************************
 * free v6 OK  Used in: leaveBlock,  sub_36E0, releaseNodeFreeList
 *			      normalizeUnaryMinusAndSub, sub_6D61, cmalloc
 * free the given block inserting on free chain in size order
 *
 *********************************************************/
void free(void *p) {
    register uint8_t *classOptions;

    for (classOptions = (uint8_t *)&freeList; Link(classOptions) && Len(Link(classOptions)) < Len((uint8_t *)p); classOptions = Link(classOptions))
        ;
    Link(p)  = Link(classOptions);
    Link(classOptions) = (uint8_t *)p;
}
#endif
/* end of file malloc.c */

/*
 * File - getchar.c
 * simple file used for function versions of getchar & putchar
 */
#
#ifdef CPM
int fgetchar() {
    return fgetc(stdin);
}
int fputchar(int c) {
    fputc(c, stdout);
}
#else
#if !defined(_WIN32)
/* assume unix convention and ingore \r on input and add \r on output */
int fgetchar() {
    int c;
    while ((c = fgetc(stdin)) == '\r')
        ;
    return c;
}
int fputchar(int c) {
    if (c == '\n')
        fputc('\r', stdout);
    return fputc(c, stdout);
}
#endif
#endif
/* end of file getchar.c */
