/*
 * File 1.c Created 17.05.2019 Last Modified 03.02.2021
 */

#include "cgen.h"
/* on CPM builds to avoid out of memory, the data tables are built separately
   to do this #define DATA to build the tables, if not defined the code is compiled
*/
/* the above limitation is only for CPM */

#if !defined(CPM) || defined(DATA)
#if 1
/* ===== start bss section ======= */
char buffer[MAXBUF];                                  /* getToken */
int lineno;                                           /* getToken, sub_6AD0, prMsg*/
char progname[MAXNAME];                               /* getToken */
bool frameGlobalsEmitted; /* First call ncsv	   */ /* sub_2BD0 */
int curPsect; /* Current section	   */             /* sub_D37  */
int swTableCnt; /*			   */                     /* sub_174C */
bbb_t *word_AE11; /* "l" - long		   */             /* sub_1680, sub_415E, sub_43EF */
int array_AE13[MAXFUN]; /*			   */             /* leaveBlock,  sub_17E0, sub_5CF5 */
bbb_t *word_AE53;                                     /* "uc" - unsigned char	   */
unsigned nstdpth;                                     /* Current nesting depth   */
int array_AE57[MAXFUN];                               /*			   */
int array_AE97[MAXFUN];                               /*			   */
bbb_t *word_AED7;                                     /* "d" - double 	   */
bbb_t *word_AED9;                                     /* "c" - char 		   */
bbb_t *array_AEDB[MAXFUN];                            /*			   */
bbb_t *word_AF1B;                                     /* "b"			   */
bbb_t *word_AF1D;                                     /* "x"			   */
bbb_t *hashtab[101];                                  /* hash table (array_AF1F) */
bbb_t *word_AFE9;                                     /* "v" - variable  	   */
int lvlidx; /* Level nested function   */             /* leaveBlock, sub_1680 */

int word_AFED;   /* sub_1F4B */
char *word_AFEF; /* sub_1F4B */
char *word_AFF1; /* sub_1F4B */
char byte_AFF3;  /* sub_1F4B */
int word_AFF4;   /* sub_1F4B */
int word_AFF6;   /* sub_1F4B */

int word_AFF8;                                /* sub_2D09, sub_3564 */
char byte_AFFA;                               /* sub_283E, sub_2B79 */
int word_AFFB;                                /* sub_2D09, sub_35E6 */
aaa_t *array_AFFD[0x14];                      /* sub_3CDF, sub_3DC9 */
void *aaaFreeList;                            /* sub_36E0, allocAaa, releaseAaaFreelist */
char byte_B013;                               /* sub_36E0, allocAaa, ... */
uchar byte_B014;                              /* sub_3CDF, sub_3DC9 */
char *word_B015;                              /* Pointer for printf      */
int word_B017;                                /* leaveBlock, sub_6D1, sub_283E, sub_2BD0, sub_61AA */
bool wflag; /* Warning messages	   */         /* main, sub_6AD0 */
bool pflag; /* Not used		   */             /* main */
bool hflag; /* Not used		   */             /* main */
int errcnt; /* Number of errors	   */         /* main, sub_6B1D */
bool bflag; /* Not used		   */             /* main */
char *baseHeap; /* Current highest memory  */ /* main */
bool eflag; /* Not used		   */             /* main */
bool rflag; /* Not used		   */             /* main, sub_61AA */

struct header1 word_B023; /* sub_6D61, cmalloc, free */

char **word_B024;

#if 0
int          word_B026;		/* sprintf */
int          word_B028;		/* sprintf */
char         byte_B02E;		/* pnum, doprint */
int          word_B02F;		/* pputc */
char         byte_B031;		/* pnum, doprint */
char         buf_B032[512];	/* pnum, doprint */
int          __argc_;		/* startup */
int          memtop;		/* brk, sbrk */
#endif
/* ===== End of bss section ======= */
#endif

/*
 *	Variables for new functions for working with files (from the standard library)
 */
FILE *f_inp;
FILE *f_out;

/* End file 1.c */
/*
 * File 2.c Created 17.05.2019 Last Modified 01.04.2020
 */
#if 1
extern char stab0[], stab1[], stab2[], stab3[];

/* clang-format off */
char *array_805F[] = {
0,           0,           stab3+0x1D1, 0,           0,           0,           stab3+0x1A3, stab3+0x19F, 
0,           0,           0,           0,           stab3+0x19B, 0,           stab3+0x18F, stab3+0x18B, 
0,           0,           stab3+0x187, stab3+0x1BF, 0,           stab2+0x211, 0,           0,           
stab3+0x1BB, 0,           0,           0,           0,           0,           stab3+0x1DD, stab0+0x2F5, 
0,           0,           stab3+0x1A3, stab3+0x19F, stab3+0x19B, stab3+0x18F, stab3+0x187, stab3+0x1BB, 
stab0+0x2F5, stab3+0x1D2, stab0+0x22E, stab3+0x1B7, stab3+0x1B8, 0,           stab3+0x1DA, stab0+0x22E, 
0,           0,           0,           0,           0,           0,           0,           0,           
0,           0,           stab3+0x1B7, 0,           stab3+0x1B8, 0,           0,           stab3+0x1D7, 
0,           0,           0,           0,           0,           0,           0,           0,           
};


struct zzz array_80EF[] = {
    {0,    0,    0,    0,    0,    0,    0,           0},           /* 0 */
    {0,    0,    0,    0x1C, 'H',  'H',  0,           stab0+0x261}, /* 1 */
    {1,    0,    0,    0x2C, 'I',  'J',  stab2+0x39E, stab0+0x58},  /* 2 */
    {2,    0,    0,    0x23, 'I',  'J',  stab2+0x3C5, stab0+0x58},  /* 3 */
    {3,    0,    0,    0x0F, 'I',  'K',  stab3+0x37,  stab0+0x58},  /* 4 */
    {3,    0,    0,    0x0F, 'I',  'L',  stab3+0x4B,  stab0+0x58},  /* 5 */
    {3,    0,    0,    0x13, 'I',  'K',  stab3+0x55,  stab0+0x58},  /* 6 */
    {0,    0,    0x12, 0x0A, 'M',  'N',  stab1+0x12F, stab0+0x58},  /* 7 */
    {0,    0,    0,    5,    'O',  0,    stab3+0x173, stab0+0x261}, /* 8 */
    {0,    0,    0,    4,    'P',  'O',  stab3+0x145, stab0+0x58},  /* 9 */
    {0,    0,    0,    4,    'Q',  'O',  stab2+0x35D, stab0+0x58},  /* 10 */
    {4,    0,    0,    0x0B, 'R',  0,    0,           stab0+0x58},  /* 11 */
    {5,    0,    0,    0x0B, 'S',  0,    0,           stab0+0x58},  /* 12 */
    {6,    0,    0,    0x0B, 'T',  0,    0,           stab0+0x58},  /* 13 */
    {3,    6,    0,    0x0B, 'U',  0,    0,           stab0+0x58},  /* 14 */
    {3,    0,    6,    0x0B, 'V',  0,    stab3+0xAB,  stab0+0x58},  /* 15 */
    {0,    0,    0,    0x1A, 'O',  0,    stab3+0x1CE, stab0+0x58},  /* 16 */
    {3,    0,    0,    0x21, 'I',  'J',  stab3+0xBD,  stab0+0x58},  /* 17 */
    {3,    0,    0,    0x46, 'V',  0,    0,           stab0+0x58},  /* 18 */
    {3,    0,    0,    0x31, 'J',  0,    stab3+0x13E, stab0+0x58},  /* 19 */
    {0,    0,    0,    0x57, 0,    0,    0,           stab0+0x58},  /* 20 */
    {3,    0,    0,    0x55, 0,    0,    0,           stab0+0x58},  /* 21 */
    {7,    0,    0,    0x21, 'I',  'J',  stab0+0x107, stab0+0x58},  /* 22 */
    {8,    0,    0,    0x31, 'X',  0,    stab3+0x137, stab0+0x58},  /* 23 */
    {5,    0,    0,    0x31, 'J',  0,    stab2+0x225, stab0+0x58},  /* 24 */
    {5,    0,    0,    0x53, 0,    0,    0,           stab0+0x58},  /* 25 */
    {6,    0,    0,    0x21, 'I',  'J',  stab1+0x24C, stab0+0x261}, /* 26 */
    {6,    0,    0,    0x31, 'Y',  0,    stab3+0x129, stab0+0x58},  /* 27 */
    {6,    0,    0,    0x5A, 0,    0,    0,           stab0+0x58},  /* 28 */
    {0,    0,    0,    0x5B, 0,    0,    0,           stab0+0x58},  /* 29 */
    {0,    1,    0,    0x55, 0,    0,    0,           stab0+0x261}, /* 30 */
    {0,    0,    1,    0x55, 0,    0,    stab3+0x105, stab0+0x2C3}, /* 31 */
    {0,    0,    0,    0x1B, 'J',  0,    0,           stab3+0x164}, /* 32 */
    {0,    0,    0,    9,    '\\', 0,    0,           stab0+0x261}, /* 33 */
    {0,    0,    0,    0x43, 0,    0,    0,           stab3+0x1D4}, /* 34 */
    {6,    0,    0,    0x14, 'Y',  0,    0,           stab0+0x261}, /* 35 */
    {0,    0,    0,    0x0E, 'Y',  'J',  0,           stab3+0x178}, /* 36 */
    {0,    0,    0,    0x49, 0,    0,    0,           stab0+0x261}, /* 37 */
    {3,    0,    0,    0x55, 0,    0,    0,           stab0+0x261}, /* 38 */
    {3,    0,    0x1A, 0x56, 0,    0,    stab3+0xAB,  stab0+0x2C3}, /* 39 */
    {0,    0,    0,    0x5A, 0,    0,    0,           stab3+0x10D}, /* 40 */
    {0,    0,    0,    0x5E, 0,    0,    0,           stab3+0x10D}, /* 41 */
    {5,    0,    0,    0x53, 0,    0,    0,           stab3+0xFD},  /* 42 */
    {3,    6,    0,    0x55, 0,    0,    stab3+0xF5,  stab3+0x1E0}, /* 43 */
    {3,    0,    2,    0x56, 0,    0,    stab2+0x237, stab3+0x1E0}, /* 44 */
    {0,    0,    0,    0x57, 0,    0,    stab3+0x122, stab3+0x1E0}, /* 45 */
    {0,    0,    0,    0x5F, 0,    0,    0,           stab3+0x1E2}, /* 46 */
    {0,    0,    0,    0x5A, 0,    0,    stab3+0xED,  stab3+0x1E0}, /* 47 */
    {4,    0,    0x10, 0x60, 0,    0,    stab0+0x1FC, stab3+0x1CB}, /* 48 */
    {0,    0,    0,    0x11, 'N',  'N',  0,           stab3+0x1B3}, /* 49 */
    {0,    0,    0,    0x17, 0,    0,    0,           stab2+0x211}, /* 50 */
    {3,    0,    1,    0x62, 0,    0,    stab3+0xE5,  stab3+0xDD},  /* 51 */
    {3,    0,    1,    0x5C, 0,    0,    stab3+0x73,  stab3+0x69},  /* 52 */
    {6,    0,    0x0E, 0x5C, 0,    0,    stab3+0x73,  stab3+0x69},  /* 53 */
    {0,    0,    0x0E, 0x57, 0,    0,    stab2+0x325, stab2+0x341}, /* 54 */
    {6,    0,    0x0E, 0x49, 0,    0,    stab2+0x1AE, stab2+0x80},  /* 55 */
    {6,    0,    0x0E, 0x0D, 'd',  0,    stab0+0x2C6, stab0+0x295}, /* 56 */
    {0,    0,    0x51, 0x65, 0,    0,    stab0+0xB1,  stab0+0x1C6}, /* 57 */
    {0,    0,    0x18, 0x57, 0,    0,    stab2+0x325, stab2+0x341}, /* 58 */
    {6,    0,    0x18, 0x49, 0,    0,    stab2+0x1AE, stab2+0x1D8}, /* 59 */
    {6,    0,    0x1D, 0x0D, 'T',  0,    stab1+0x1B2, stab1+0x1D1}, /* 60 */
    {0,    0,    0,    0x63, 0,    0,    0,           stab0+0x261}, /* 61 */
    {0,    0,    0,    0x47, 'R',  0,    0,           stab2+0xDD},  /* 62 */
    {1,    0,    0,    7,    ']',  'J',  stab2+0x36A, stab0+0x58},  /* 63 */
    {0,    0,    0,    8,    'h',  'Q',  stab1+0x380, stab0+0x58},  /* 64 */
    {0,    0,    0,    0x51, 0,    0,    stab1+0x32E, stab0+0x261}, /* 65 */
    {0,    0,    0,    1,    'Q',  0,    stab1+0x3CE, stab0+0x58},  /* 66 */
    {0,    0,    0,    0x3D, 'i',  'Q',  stab1+0x380, stab0+0x58},  /* 67 */
    {0,    0,    0,    0x51, 0,    0,    stab2+0x366, stab0+0x261}, /* 68 */
    {0,    0,    0,    0x50, 0,    0,    stab2+0x29C, stab0+0x58},  /* 69 */
    {3,    0,    0,    0x5D, 0,    0,    0,           stab0+0x261}, /* 70 */
    {3,    0,    0x1A, 0x0D, 'k',  0,    stab2+0x307, stab0+0x2C3}, /* 71 */
    {3,    0,    0x1A, 0x0D, 'l',  0,    stab2+0x3AB, stab0+0x2C3}, /* 72 */
    {3,    0,    0x5A, 0x49, 0,    0,    stab3+0xE5,  stab0+0x2C3}, /* 73 */
    {0,    0,    0,    0x1C, 'H',  'U',  0,           stab2+0x2C8}, /* 74 */
    {0,    0,    0,    0x21, 'I',  'U',  stab3+0xD5,  stab2+0x2C8}, /* 75 */
    {3,    0,    0,    0x30, 'i',  'm',  0,           stab2+0x2C8}, /* 76 */
    {3,    0,    0x1A, 0x14, 'P',  0,    stab1+0x316, stab0+0x2C3}, /* 77 */
    {3,    0,    0x1A, 0x14, 'Q',  0,    stab1+0x10D, stab0+0x2C3}, /* 78 */
    {3,    0,    0,    0x14, 'U',  0,    0,           stab2+0xDD},  /* 79 */
    {3,    0,    0x5A, 0x14, 'Z',  0,    stab3+0x41,  stab0+0x2C3}, /* 80 */
    {9,    0,    0x52, 0x14, 'S',  0,    stab2+0x182, stab3+0x1C},  /* 81 */
    {3,    0,    0x5A, 0x14, 'S',  0,    stab3+0x16,  stab0+0x2C3}, /* 82 */
    {3,    0,    0,    0x21, '\\', 'V',  stab3+0x5F,  stab2+0x2C8}, /* 83 */
    {3,    0,    0x5A, 0x6E, 0,    0,    stab3+0x2C,  stab0+0x2C3}, /* 84 */
    {0,    0,    0,    0x1F, 'U',  'o',  stab2+0x377, stab2+0xDD},  /* 85 */
    {0,    0,    0,    0x1F, 'U',  'p',  stab0+0x388, stab2+0xDD},  /* 86 */
    {0,    0,    0,    0x28, 'a',  'o',  stab2+0x2DA, stab2+0xDD},  /* 87 */
    {0,    0,    0,    0x28, 'a',  'p',  stab0+0x359, stab2+0xDD},  /* 88 */
    {0,    0,    0,    0x0E, 'V',  ']',  stab3+0x130, stab2+0xDD},  /* 89 */
    {0x0A, 0,    0,    7,    'V',  ']',  stab3+0x17D, stab2+0xDD},  /* 90 */
    {0,    0,    0,    0x25, 'a',  ']',  stab3+0xA2,  stab2+0xDD},  /* 91 */
    {0x0A, 0,    0,    0x23, 'a',  ']',  stab3+0x11B, stab2+0xDD},  /* 92 */
    {3,    0,    0x1A, 0x0F, 'I',  'K',  stab2+0x27B, stab0+0x2C3}, /* 93 */
    {0,    0,    0x1B, 0x0F, 'a',  'q',  stab2+0x2CB, stab0+0x2C3}, /* 94 */
    {0,    0,    0,    0x3F, 'V',  0,    stab3+0x193, stab2+0xDD},  /* 95 */
    {0,    0,    0,    0x15, 'V',  0,    stab3+0x197, stab2+0xDD},  /* 96 */
    {3,    0,    1,    0x5C, 0,    0,    stab3+0x73,  stab0+0x2C3}, /* 97 */
    {0,    0,    0x12, 0x0A, 'M',  'N',  stab1+0x0,   stab3+0x182}, /* 98 */
    {0,    0,    0,    0x19, 'r',  's',  stab1+0x109, stab2+0xDD},  /* 99 */
    {0,    0,    0,    0x72, 0,    0,    stab3+0xB,   stab0+0x58},  /* 100 */
    {5,    0,    0,    0x53, 0,    0,    0,           stab0+0x261}, /* 101 */
    {6,    0,    0,    0x54, 0,    0,    0,           stab0+0x261}, /* 102 */
    {3,    0,    0,    0x56, 0,    0,    0,           stab0+0x261}, /* 103 */
    {0,    0,    0,    0x43, 0,    0,    0,           stab3+0xD2},  /* 104 */
    {0,    3,    0,    0x55, 0,    0,    0,           stab0+0x261}, /* 105 */
    {0,    0,    3,    0x5D, 0,    0,    stab3+0xE5,  stab0+0x2C3}, /* 106 */
    {0,    0x0D, 0,    0x5A, 0,    0,    0,           stab0+0x261}, /* 107 */
    {0,    0x0E, 0x0D, 0x5A, 0,    0,    stab3+0xB4,  stab0+0x2C3}, /* 108 */
    {0,    0x19, 0,    0x5A, 0,    0,    0,           stab0+0x261}, /* 109 */
    {0,    0,    0,    0x64, 0,    0,    0,           stab0+0x261}, /* 110 */
    {0,    0,    0,    0x0D, 'Y',  0,    0,           stab0+0x261}, /* 111 */
    {0,    0,    0,    0x42, 0,    0,    0,           stab3+0x1D4}, /* 112 */
    {0,    0,    0,    0x44, 0,    0,    stab1+0xC7,  stab3+0x1AF}, /* 113 */
    {0,    0,    0,    0x17, 0,    0,    0,           stab0+0x58},  /* 114 */
    {0,    0,    0,    0x44, 0,    0,    0,           stab3+0x1D4}, /* 115 */
    {0,    0,    0,    2,    'g',  'u',  0,           stab1+0x313}, /* 116 */
    {0,    0,    0,    2,    'v',  'u',  0,           stab3+0x169}, /* 117 */
    {0,    0,    0,    2,    'V',  'u',  stab3+0x152, stab3+0x169}, /* 118 */
    {0x0A, 0,    0,    2,    'V',  ']',  stab3+0x16E, stab1+0x313}, /* 119 */
    {0x0A, 0,    0,    2,    'V',  'p',  stab1+0x3B4, stab3+0x169}, /* 120 */
    {0x0B, 0,    1,    2,    'I',  'u',  stab2+0x28C, stab1+0x313}, /* 121 */
    {0x0B, 0,    0x1C, 2,    '\\', 'u',  stab1+0x288, stab1+0x313}, /* 122 */
    {0x0B, 0,    1,    2,    'R',  'u',  stab2+0x1A,  stab1+0x313}, /* 123 */
    {0x0B, 0,    1,    2,    ']',  'u',  stab2+0x28C, stab1+0x313}, /* 124 */
    {0x0B, 0,    0,    0x1E, ']',  'u',  stab3+0x0,   stab3+0x1D1}, /* 125 */
    {0x0B, 0,    0,    0x2E, ']',  'u',  stab3+0x0,   stab3+0x1D2}, /* 126 */
    {0x0C, 0,    1,    2,    ']',  'u',  stab1+0x172, stab1+0x313}, /* 127 */
    {0x0C, 0,    0,    0x1E, ']',  'u',  stab2+0x3EB, stab3+0x1D1}, /* 128 */
    {0x0C, 0,    0,    0x2E, ']',  'u',  stab2+0x3EB, stab3+0x1D2}, /* 129 */
    {0x0B, 0,    0,    2,    'T',  'd',  stab2+0x2F8, stab1+0x313}, /* 130 */
    {0,    0,    1,    2,    'T',  'd',  stab2+0x0,   stab3+0x169}, /* 131 */
    {0,    0,    0x52, 2,    'S',  '_',  stab1+0x2DE, stab3+0x169}, /* 132 */
    {0,    0,    0,    0x5C, 0,    0,    0,           stab0+0x261}, /* 133 */
    {0,    0,    0,    0x0D, 'T',  0,    0,           stab3+0x158}, /* 134 */
    {0,    0x0E, 0,    0x5A, 0,    0,    0,           stab2+0xDD},  /* 135 */
    {0,    0x0D, 0x0E, 0x5A, 0,    0,    stab3+0xB4,  stab0+0x2C3}, /* 136 */
    {0,    0,    0,    0x0F, 'c',  'J',  0,           stab2+0x391}, /* 137 */
    {0,    0,    0,    0x0E, 'W',  'x',  0,           stab3+0x178}, /* 138 */
    {0,    0,    0,    0x57, 0,    0,    0,           stab3+0x1AB}, /* 139 */
    {0,    0,    9,    0x0E, '\\', 'x',  stab3+0x73,  stab3+0x15E}, /* 140 */
    {0x0D, 0,    0,    0x0F, 'W',  'J',  0,           stab2+0xED},  /* 141 */
    {0x0E, 0,    0,    0x45, 0,    0,    0,           stab3+0x1D4}, /* 142 */
    {0x0D, 0,    0,    0x25, 'W',  'J',  stab3+0x37,  stab0+0x261}, /* 143 */
    {0,    0,    0,    0x25, 'W',  '^',  stab3+0x90,  stab0+0x261}, /* 144 */
    {0,    0,    0,    0x21, 'W',  'Y',  stab3+0x114, stab0+0x261}, /* 145 */
    {0,    0,    0,    0x21, 'W',  '\\', stab3+0x87,  stab0+0x261}, /* 146 */
    {0,    0,    0,    0x21, '\\', 'W',  stab3+0x99,  stab0+0x148}, /* 147 */
    {0,    0,    0,    0x1B, 'J',  0,    0,           stab3+0x1C3}, /* 148 */
    {0,    0,    0,    0x42, 0,    0,    0,           stab3+0x1D4}, /* 149 */
    {0,    0,    0,    0x43, 0,    0,    0,           stab3+0x1C7}, /* 150 */
    {5,    0,    0,    0x53, 0,    0,    stab2+0x2AC, stab0+0x58},  /* 151 */
    {3,    0,    0,    0x49, 0,    0,    0,           stab0+0x261}, /* 152 */
    {3,    0,    0,    0x0D, 'Z',  0,    0,           stab1+0x1CC}, /* 153 */
    {0x0F, 0,    0,    0x43, 0,    0,    0,           stab3+0xD2},  /* 154 */
    {0x10, 0,    0,    0x43, 0,    0,    0,           stab0+0x58},  /* 155 */
    {3,    0,    0,    0x25, 'I',  'o',  stab3+0x37,  stab0+0x261}, /* 156 */
    {3,    0,    0,    0x25, 'I',  'L',  stab3+0x4B,  stab0+0x261}, /* 157 */
    {0,    0,    0x52, 0x47, 'T',  0,    stab0+0xDC,  stab3+0x14C}, /* 158 */
    {0,    0,    0,    0x21, 'e',  'd',  stab0+0x3B5, stab2+0xDD},  /* 159 */
    {6,    0,    0,    0x30, 'i',  'm',  0,           stab2+0x2C8}, /* 160 */
    {0,    0,    0x18, 0x59, 0,    0,    stab3+0xE5,  stab0+0x2C3}, /* 161 */
    {6,    0,    0x18, 0x5C, 0,    0,    stab3+0x73,  stab0+0x2C3}, /* 162 */
    {6,    0,    0x18, 0x49, 0,    0,    stab2+0x1AE, stab0+0x2C3}, /* 163 */
    {0,    0,    0,    0x1C, 'H',  'Z',  0,           stab2+0x2C8}, /* 164 */
    {0,    0,    0x18, 0x57, 0,    0,    stab2+0x325, stab0+0x2C3}, /* 165 */
    {6,    0,    0x17, 0x22, 'R',  'd',  stab1+0x39A, stab2+0xDD},  /* 166 */
    {6,    0,    0x17, 6,    'T',  'd',  stab2+0x16C, stab2+0xDD},  /* 167 */
    {0,    0,    0,    0x2F, 'Z',  'o',  stab2+0x1ED, stab2+0xDD},  /* 168 */
    {0,    0,    0,    0x1F, 'T',  'o',  stab2+0x333, stab2+0xDD},  /* 169 */
    {6,    0,    1,    0x28, 'R',  'p',  stab1+0x39A, stab2+0xDD},  /* 170 */
    {0,    0,    1,    0x1F, 'T',  'p',  stab2+0x34,  stab2+0xDD},  /* 171 */
    {0,    0,    0,    0x13, 'f',  'o',  stab2+0xE0,  stab2+0xDD},  /* 172 */
    {0,    0,    0,    0x0F, 'f',  'o',  stab2+0xF8,  stab2+0xDD},  /* 173 */
    {2,    0,    0,    0x23, 'f',  'J',  stab2+0x248, stab2+0xDD},  /* 174 */
    {2,    0,    0,    7,    'Z',  'J',  stab2+0x2E9, stab2+0xDD},  /* 175 */
    {1,    0,    0,    0x2C, 'f',  'J',  stab2+0x259, stab2+0xDD},  /* 176 */
    {1,    0,    0,    0x3C, 'Z',  'J',  stab2+0x316, stab2+0xDD},  /* 177 */
    {6,    0,    0x5C, 7,    ']',  ']',  stab0+0x263, stab1+0x1EC}, /* 178 */
    {6,    0,    1,    0x23, 'f',  ']',  stab0+0x230, stab2+0xDD},  /* 179 */
    {6,    0,    0x1D, 0x0F, 'c',  'J',  stab1+0x20F, stab2+0xDD},  /* 180 */
    {6,    0,    0x1D, 0x13, 'c',  'J',  stab1+0xA2,  stab2+0xDD},  /* 181 */
    {6,    0,    0x18, 0x0D, 'k',  0,    stab1+0x26A, stab0+0x2C3}, /* 182 */
    {6,    0,    0x1D, 0x0D, 'l',  0,    stab1+0x2A,  stab0+0x2C3}, /* 183 */
    {6,    0,    0x1D, 0x0D, 'T',  0,    stab1+0x1B2, stab0+0x2C3}, /* 184 */
    {6,    0,    0x1A, 0x52, 0,    0,    stab1+0x52,  stab2+0xDD},  /* 185 */
    {6,    0,    0x18, 0x14, 'P',  0,    stab1+0x316, stab0+0x2C3}, /* 186 */
    {6,    0,    0x18, 0x14, 'Q',  0,    stab1+0xEA,  stab0+0x2C3}, /* 187 */
    {0,    0,    0x18, 0x25, 'W',  '^',  stab2+0x128, stab0+0x2C3}, /* 188 */
    {6,    0,    0,    0x25, 'f',  'o',  stab2+0x3B8, stab2+0xDD},  /* 189 */
    {6,    0,    0,    0x26, 'f',  'o',  stab2+0x384, stab2+0xDD},  /* 190 */
    {6,    0,    0,    0x25, 'f',  'L',  stab2+0x3D2, stab2+0xDD},  /* 191 */
    {6,    0,    0,    0x26, 'c',  '^',  stab2+0x26A, stab2+0xDD},  /* 192 */
    {6,    0,    0,    0x25, 'c',  '^',  stab2+0x3DF, stab2+0xDD},  /* 193 */
    {6,    0,    0,    0x21, '\\', 'Z',  stab3+0x5F,  stab2+0x2C8}, /* 194 */
    {6,    0,    0,    0x21, 'I',  'Z',  stab2+0x1C3, stab2+0x2C8}, /* 195 */
    {6,    0,    0,    0x21, 'R',  '^',  stab1+0x1F0, stab2+0x2C8}, /* 196 */
    {6,    0,    0,    0x12, 'T',  '^',  stab2+0x2BC, stab2+0xDD},  /* 197 */
    {0,    0,    0,    0x0E, 'Z',  'o',  stab2+0xED,  stab2+0xDD},  /* 198 */
    {0,    0,    0,    0x0E, 'Z',  'L',  stab3+0x21,  stab2+0xDD},  /* 199 */
    {6,    0x1D, 0x0E, 0x0E, 'Z',  'Y',  stab2+0x213, stab0+0x2C3}, /* 200 */
    {6,    0,    0,    0x0E, 'T',  '^',  stab3+0x7D,  stab2+0xDD},  /* 201 */
    {0,    0,    0x0E, 0x15, '^',  0,    stab2+0xC8,  stab0+0x2C3}, /* 202 */
    {0,    0,    0,    0x21, 'W',  'Z',  stab2+0x34F, stab2+0x2C8}, /* 203 */
    {6,    0,    0x58, 0x6E, 0,    0,    stab2+0xB0,  stab0+0x2C3}, /* 204 */
    {0x11, 0,    0x58, 0x14, 'j',  0,    stab2+0x201, stab0+0x2C3}, /* 205 */
    {0x12, 0,    0x18, 0x14, 'V',  0,    stab1+0x22E, stab0+0x2C3}, /* 206 */
    {0,    0,    0,    9,    '[',  0,    0,           stab0+0x261}, /* 207 */
    {0x13, 0,    0x52, 0x14, 'S',  0,    stab2+0x182, stab2+0x2F4}, /* 208 */
    {6,    0,    0,    0x14, 'Z',  0,    0,           stab2+0xDD},  /* 209 */
    {6,    0,    0,    0x14, 'S',  0,    0,           stab2+0x2F4}, /* 210 */
    {8,    0,    1,    0x15, 'S',  0,    stab2+0x198, stab2+0xDD},  /* 211 */
    {5,    0,    0x0F, 0x5C, 0,    0,    stab2+0x67,  stab0+0x2C3}, /* 212 */
    {0,    0,    0x0F, 0x43, 0,    0,    stab2+0x156, stab0+0x2C3}, /* 213 */
    {5,    0,    0x0F, 0x49, 0,    0,    stab0+0x328, stab0+0x2C3}, /* 214 */
    {5,    0,    0,    0x6E, 0,    0,    0,           stab0+0x261}, /* 215 */
    {5,    0,    0,    0x30, 'i',  'm',  0,           stab2+0x2C8}, /* 216 */
    {5,    0,    0x54, 0x0D, 'T',  0,    stab0+0x59,  stab1+0x1EC}, /* 217 */
    {7,    0,    0x0C, 0x0E, 'S',  'J',  stab0+0x18C, stab2+0xDD},  /* 218 */
    {5,    0,    0x52, 0x22, 'R',  '_',  stab1+0x2FA, stab3+0x182}, /* 219 */
    {5,    0,    0x52, 0x0F, 'R',  0,    stab2+0x98,  stab3+0x182}, /* 220 */
    {5,    0,    0x52, 6,    'S',  '_',  stab2+0x110, stab2+0xDD},  /* 221 */
    {7,    0,    0x4F, 0x28, 'R',  'p',  stab1+0x192, stab0+0x2C3}, /* 222 */
    {7,    0,    0x54, 0x1F, 'S',  'p',  stab1+0x2C2, stab2+0xDD},  /* 223 */
    {5,    0,    0,    0x21, '\\', 'S',  stab2+0x4E,  stab2+0x2C8}, /* 224 */
    {5,    0,    0,    0x21, 'I',  'S',  stab0+0x2F7, stab2+0x2C8}, /* 225 */
    {5,    0,    0x51, 0x21, 'R',  '_',  stab0+0x0,   stab0+0xAD},  /* 226 */
    {7,    0,    0x11, 0x15, '_',  0,    stab0+0x14A, stab0+0xAD},  /* 227 */
    {0x14, 0,    0x54, 0x14, 'd',  0,    stab1+0x151, stab1+0x1EC}, /* 228 */
    {0x14, 0,    0x54, 0x14, 'V',  0,    stab1+0x7A,  stab1+0x1EC}, /* 229 */
    {0x15, 0,    0x4F, 0x14, 'd',  0,    stab3+0xC5,  stab0+0x2C3}, /* 230 */
    {0x15, 0,    0x4F, 0x14, 'U',  0,    stab2+0x13F, stab0+0x2C3}, /* 231 */
    {0x16, 0,    0x52, 0x14, 'S',  0,    stab1+0x332, stab2+0xDD},  /* 232 */
    {0x17, 0,    0x52, 0x14, 'T',  0,    stab1+0x34C, stab3+0x182}, /* 233 */
    {0x18, 0,    0x52, 0x14, 'V',  0,    stab1+0x366, stab3+0x182}, /* 234 */
    {0x19, 0,    0x52, 0x14, 'S',  0,    stab2+0x182, stab2+0xDD},  /* 235 */
    {0,    0,    0,    0x14, 'S',  0,    0,           stab2+0xDD},  /* 236 */
    {0,    0,    0,    0x43, 0,    0,    0,           stab3+0xCD},  /* 237 */
    {0,    0,    0,    0x76, 0,    0,    0,           stab0+0x261}, /* 238 */
    {0,    0,    0,    0x0D, 'w',  0,    0,           stab3+0x79},  /* 239 */
    {3,    0,    0,    0x0D, 'T',  0,    0,           stab1+0x1CC}, /* 240 */
    {0x1A, 0,    0,    0x43, 0,    0,    0,           stab0+0x58},  /* 241 */
    {0x1B, 0,    0,    0x43, 0,    0,    0,           stab0+0x58},  /* 242 */
    {0,    0x0D, 0,    0x5B, 0,    0,    0,           stab0+0x261}, /* 243 */
    {0,    0,    0x0D, 0x0D, 'T',  0,    stab3+0xB4,  stab0+0x2C3}, /* 244 */
    {0,    0x0E, 0,    0x5B, 0,    0,    0,           stab0+0x261}, /* 245 */
    {0,    0,    0,    0x0D, 'T',  0,    0,           stab0+0x261}, /* 246 */
    {4,    0,    0x0C, 0x21, '`',  'R',  stab1+0x2A5, stab2+0x2C8}, /* 247 */
    {0,    0,    0x18, 0x5C, 0,    0,    stab3+0xE5,  stab0+0x2C3}, /* 248 */
    {0,    0,    0,    0x0D, 'Z',  0,    0,           stab0+0x261}, /* 249 */
    {4,    0,    0,    0x6E, 0,    0,    0,           stab3+0x1A7}, /* 250 */
    {0x1C, 0,    0,    0x14, '[',  0,    0,           stab0+0x261}, /* 251 */
    {0x1D, 0,    0,    0x43, 0,    0,    0,           stab3+0xD2},  /* 252 */
    {0x1E, 0,    0,    0x43, 0,    0,    0,           stab0+0x58},  /* 253 */
};

/* strings table is split to avoid hitech compilation problems with very long strings
   the current split point is around 1k, which does not seem to cause a problem
*/
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
    "ex\tde,hl\0"
    "ld L,G00R\n"            /* 0x2F7 */
    "ld ~+1L,G01R\n"
    "ld ~+2L,G10R\n"
    "ld ~+3L,G11R\0"
    "ld X00N,L\n"            /* 0x328 */
    "ld X01N,~+1L\n"
    "ld X10N,~+2L\n"
    "ld X11N,~+3L\0"
    "inc GR\n"               /* 0x359 */
    "dec GR\n"
    "jr z,2f\n"
    "1:\n"
    "sONAN GL\n"
    "djnz 1b\n"
    "2:\n"
    "L\0"
    "inc GR\n"               /* 0x388 */
    "dec GR\n"
    "jr z,2f\n"
    "1:\n"
    "sONAN GL\n"
    "djnz 1b\n"
    "2:\0"
    "global bfins\n"         /* 0x3B5 */
    "call bfins\n"
    "defb TL+(CL.shl.4)"
};

char stab1[] = {
    "call L\n"               /* 0x0 */
    "exx\n"
    "ld hl,R\n"
    "add hl,sp\n"
    "ld sp,hl\n"
    "exx\0"
    "ld X0N,(GL)\n"          /* 0x2A */
    "inc GL\n"
    "ld X1N,(GL)\n"
    "dec GL\n"
    "L\0"
    "ld XN,(GL)\n"           /* 0x52 */
    "inc GL\n"
    "ld\tG1L,(GL)\n"
    "ld G0L,XN\0"
    "ld e,a\n"               /* 0x7A */
    "rla\n"
    "sbc a,a\n"
    "ld d,a\n"
    "ld l,a\n"
    "ld h,a\0"
    "ld XN,-VR\n"            /* 0xA2 */
    "add\tGL,XN\n"
    "L\n"
    "or a\n"
    "sbc GL,XN\0"
    "psect data\n"           /* 0xC7 */
    "eFN: deff SN\n"
    "psect text\0"
    "U0:\n"                  /* 0xEA */
    "ld XN,1\n"
    "jp U2f\n"
    "U1:\n"
    "ld XN,0\n"
    "U2:\0"
    "U0:\n"                  /* 0x10D */
    "ld XN,1\n"
    "p U2f\n"
    "U1:\n"
    "ld XN,0\n"
    "U2:\0"
    "call L\n"               /* 0x12F */
    "ld hl,R\n"
    "add hl,sp\n"
    "ld\tsp,hl\0"
    "ld a,d\n"               /* 0x151 */
    "rla\n"
    "sbc a,a\n"
    "ld l,a\n"
    "ld h,a\0"
    "ld XN,L\n"              /* 0x172 */
    "or ~+1L\n"
    "or ~+2L\n"
    "or ~+3L\0"
    "global\tasANlONsh\n"    /* 0x192 */
    "call\tasANlONsh\0"
    "ld X0N,(GL)\n"          /* 0x1B2 */
    "inc GL\n"
    "ld X1N,(GL)\0"
    "ld (GL),X1N\n"          /* 0x1D1 */
    "dec GL\n"
    "ld (GL),X0N\0"
    "ld (GL),G0R\n"          /* 0x1F0 */
    "inc GL\n"
    "ld (GL),G1R\0"
    "ld XN,VR\n"             /* 0x20F */
    "add GL,XN\n"
    "L\n"
    "sbc GL,XN\0"
    "ld X0N,a\n"             /* 0x22E */
    "rla\n"
    "sbc a,a\n"
    "ld X1N,a\0"
    "ld L,.low.VR\n"         /* 0x24C */
    "ld ~+1L,.high.VR\0"
    "ld X0N,(GL+0)\n"        /* 0x26A */
    "ld X1N,(GL+1)\n"
    "L\0"
    "ld X0N,(L)\n"           /* 0x288 */
    "ld\ta,X00N\n"
    "or X01N\0"
    "push hl\n"              /* 0x2A5 */
    "ld XN,ZN\n"
    "ldir\n"
    "pop hl\0"
    "global\tANlONsh\n"      /* 0x2C2 */
    "call ANlONsh\0"
    "global\tALrelop\n"      /* 0x2DE */
    "call ALrelop\0"
    "global\tasANlON\n"      /* 0x2FA */
    "call asANlON\0"
    "ld XN,1\n"              /* 0x316 */
    "jp L,U0f\n"
    "dec\tXN\n"
    "U0:\0"
    "global\tALltof\n"       /* 0x332 */
    "call ALltof\0"
    "global\tALitof\n"       /* 0x34C */
    "call ALitof\0"
    "global\tALbtof\n"       /* 0x366 */
    "call ALbtof\0"
    "U1:jp ~-1U1f\n"         /* 0x380 */
    "U0:jp ~-1U0f\0"
    "global\tasANON\n"       /* 0x39A */
    "call asANON\0"
    "global\tbrelop\n"       /* 0x3B4 */
    "call brelop\0"
    "U1:jp ~-1U0f\n"         /* 0x3CE */
    "U0:jp ~-1U1f"
};

char stab2[] = {
    "global wrelop\n"        /* 0x0 */
    "call wrelop\0"
    "ld XN,(GL)\n"           /* 0x1A */
    "inc GL\n"
    "or\t(GL)\0"
    "global\tshANON\n"       /* 0x34 */
    "call shANON\0"
    "ld (L),G0R\n"           /* 0x4E */
    "ld\t(~+2L),G1R\0"
    "ld X0N,(L)\n"           /* 0x67 */
    "ld\tX1N,(~+2L)\0"
    "ld L,X0N\n"             /* 0x80 */
    "ld ~+1L,X1N;XN\0"
    "global\tlANON\n"        /* 0x98 */
    "call lANON\0"
    "ld X0N,G10L\n"          /* 0xB0 */
    "ld X1N,G11L\0"
    "ld XN,ON\n"             /* 0xC8 */
    "or a\n"
    "sbc XN,GL\0"
    "dec GLV--R\n"           /* 0xE0 */
    "L\n"
    "inc GLV--R\0"
    "inc GLV--R\n"           /* 0xF8 */
    "L\n"
    "dec GLV--R\0"
    "global\tANlON\n"        /* 0x110 */
    "call ANlON\0"
    "add L,GR\n"             /* 0x128 */
    "push\tL\n"
    "pop XN\0"
    "ld hl,0\n"              /* 0x13F */
    "ld d,l\n"
    "ld e,GL\0"
    "ld X0N,VN\n"            /* 0x156 */
    "ld X1N,V+2N\0"
    "global\tANON\n"         /* 0x16C */
    "call ANON\0"
    "global\tftol\n"         /* 0x182 */
    "call ftol\0"
    "ld a,h\n"               /* 0x198 */
    "xor 80h\n"
    "ld h,a\0"
    "ld X0N,L\n"             /* 0x1AE */
    "ld X1N,~+1L\0"
    "ld L,G0R\n"             /* 0x1C3 */
    "ld ~+1L,G1R\0"
    "ld L,X0N\n"             /* 0x1D8 */
    "ld ~+1L,X1N\0"
    "srAN G1L\rrr G0LV--R\0" /* 0x1ED */
    "ld X0N,L\n"             /* 0x201 */
    "ld G1N,0\0"
    "ld XN,R\n"              /* 0x213 */
    "add XN,GL\0"
    "defw VL\n"              /* 0x225 */
    "defw V+2L\0"
    "ld XN,GL\n"             /* 0x237 */
    "push bc\0"
    "res TR&7CR,G0L\n"       /* 0x248 */
    "L\0"
    "set TR&7CR,G0L\n"       /* 0x259 */
    "L\0"
    "or a\n"                 /* 0x26A */
    "sbc GL,GR\n"
    "L\0"
    "ld XN,L\n"              /* 0x27B */
    "ON LV--R\0"
    "ld XN,L\n"              /* 0x28C */
    "or ~+1L\0"
    "jp L,U0f\n"             /* 0x29C */
    "jp U1f\0"
    "push hl\n"              /* 0x2AC */
    "push de\0"
    "or a\n"                 /* 0x2BC */
    "sbc GL,GR\0"
    "ld XN,a\n"              /* 0x2CB */
    "ON a\n"
    "L\0"
    "sONAN GLV--R\n"         /* 0x2DA */
    "L\0"
    "res TR&7CR,G0L\0"       /* 0x2E9 */
    "or a\n"                 /* 0x2F8 */
    "sbc hl,de\0"
    "ld XN,(GL+0)\n"         /* 0x307 */
    "L\0"
    "set TR&7CR,G0L\0"       /* 0x316 */
    "push L\n"               /* 0x325 */
    "pop XN\0"
    "add hl,hlV--R\0"        /* 0x333 */
    "push XN\n"              /* 0x341 */
    "pop L\0"
    "push GR\n"              /* 0x34F */
    "pop L\0"
    "U0:\n"                  /* 0x35D */
    "jp R\n"
    "U1:\0"
    "bit\tTR&7CR,L\0"        /* 0x36A */
    "sONAN GLV--R\0"         /* 0x377 */
    "dec GLV--R\n"           /* 0x384 */
    "L\0"
    "inc hlV--R\n"           /* 0x391 */
    "L\0"
    "set\tTR&7CR,L\0"        /* 0x39E */
    "ld XN,(GL)\n"           /* 0x3AB */
    "L\0"
    "inc GLV--R\n"           /* 0x3B8 */
    "L\0"
    "res\tTR&7CR,L\0"        /* 0x3C5 */
    "dec GLV++R\n"           /* 0x3D2 */
    "L\0"
    "add GL,GR\n"            /* 0x3DF */
    "L\0"
    "bit 7,~+3L"             /* 0x3EB */
};

char stab3[] = {
    "bit 7,~+1L\0"           /* 0x0 */
    "jp U2f\n"               /* 0xB */
    "U0:\0"
    "ld XN,G00L\0"           /* 0x16 */
    "dec GLV++R\0"           /* 0x21 */
    "ld XN,G10L\0"           /* 0x2C */
    "inc LV--R\0"            /* 0x37 */
    "ld XN,G0L\0"            /* 0x41 */
    "dec LV++R\0"            /* 0x4B */
    "dec LV--R\0"            /* 0x55 */
    "ld (L),GR\0"            /* 0x5F */
    "ld (L),XN\0"            /* 0x69 */
    "ld XN,(L)\0"            /* 0x73 */
    "add GL,GR\0"            /* 0x7D */
    "ld L,(R)\0"             /* 0x87 */
    "add L,GR\0"             /* 0x90 */
    "ld (L),R\0"             /* 0x99 */
    "ON a,R\n"               /* 0xA2 */
    "L\0"
    "ld XN,GL\0"             /* 0xAB */
    "ex de,hl\0"             /* 0xB4 */
    "ld L,VR\0"              /* 0xBD */
    "ld hl,0\0"              /* 0xC5 */
    ".low.VN\0"              /* 0xCD */
    "ld L,GR\0"              /* 0xD5 */
    "ld L,XN\0"              /* 0xDD */
    "ld XN,L\0"              /* 0xE5 */
    "push GL\0"              /* 0xED */
    "push hl\0"              /* 0xF5 */
    "G00L;GL\0"              /* 0xFD */
    "ld a,GL\0"              /* 0x105 */
    "G0L;GL\0"               /* 0x10D */
    "ld L,R\0"               /* 0x114 */
    "ON R\n"                 /* 0x11B */
    "L\0"
    "push L\0"               /* 0x122 */
    "defw L\0"               /* 0x129 */
    "ON a,R\0"               /* 0x130 */
    "deff L\0"               /* 0x137 */
    "defb L\0"               /* 0x13E */
    "jp L,R\0"               /* 0x145 */
    "X111N\0"                /* 0x14C */
    "or GL\0"                /* 0x152 */
    "indir\0"                /* 0x158 */
    "XN+SR\0"                /* 0x15E */
    "VL9f\0"                 /* 0x164 */
    "ALON\0"                 /* 0x169 */
    "cp R\0"                 /* 0x16E */
    "jp L\0"                 /* 0x173 */
    "L+VR\0"                 /* 0x178 */
    "ON R\0"                 /* 0x17D */
    "X11N\0"                 /* 0x182 */
    "sub\0"                  /* 0x187 */
    "inc\0"                  /* 0x18B */
    "add\0"                  /* 0x18F */
    "cpl\0"                  /* 0x193 */
    "neg\0"                  /* 0x197 */
    "mul\0"                  /* 0x19B */
    "and\0"                  /* 0x19F */
    "mod\0"                  /* 0x1A3 */
    "G1L\0"                  /* 0x1A7 */
    "L+0\0"                  /* 0x1AB */
    "eFN\0"                  /* 0x1AF */
    "L+R\0"                  /* 0x1B3 */
    "xor\0"                  /* 0x1B7 */
    "div\0"                  /* 0x1BB */
    "dec\0"                  /* 0x1BF */
    "VL9\0"                  /* 0x1C3 */
    "lVN\0"                  /* 0x1C7 */
    "ZN\0"                   /* 0x1CB */
    "L:\0"                   /* 0x1CE */
    "nz\0"                   /* 0x1D1 */
    "SN\0"                   /* 0x1D4 */
    "-1\0"                   /* 0x1D7 */
    "ge\0"                   /* 0x1DA */
    "lt\0"                   /* 0x1DD */
    "2\0"                    /* 0x1E0 */
    "4"                      /* 0x1E2 */
};
/* clang-format on */
/* End file 2.c */
#endif

/*
 * File 3.c Created 17.05.2019 Last Modified 21.01.2021
 */
#if 1
/* offsets into character array below */
int array_987D[]           = { 0,     0,     4,     9,     0x0A,  0x0C,  0x0E,  0x1C,  0x2D,  0x31,  0x3E,  0x52,
                     0x54,  0x62,  0x7C,  0x8E,  0x0A0, 0x0A1, 0x0A3, 0x0B3, 0x0C3, 0x0D7, 0x0E7, 0x0E8,
                     0x0EB, 0x0F9, 0x0FB, 0x0FD, 0x10B, 0x119, 0x11A, 0x11F, 0x12F, 0x130, 0x147, 0x155,
                     0x165, 0x173, 0x18B, 0x19B, 0x1A9, 0x1B9, 0x1BE, 0x1CE, 0x1DE, 0x1EE, 0x1EF, 0x1F4,
                     0x204, 0x214, 0x216, 0x217, 0x218, 0x219, 0x21A, 0x21B, 0x21C, 0x21D, 0x21E, 0x22E,
                     0x22F, 0x23F, 0x243, 0x244, 0x254, 0x255, 0x256, 0x26F, 0x28D, 0x2A6, 0x2B6, 0x2B8 };

unsigned char array_990D[] = {
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

int array_9BD4[] = {
    -66,  -65,  -68,  0,    89,   -69,  -65,  -68,  0,    0,    1,    0,    -8,   0,    3,    62,   -221,
    141,  -167, 231,  251,  -151, 264,  -70,  -106, 276,  -100, 0,    5,    64,   -221, 141,  -90,  163,
    170,  234,  251,  -151, 264,  -63,  -70,  274,  278,  -100, 0,    -64,  -65,  -68,  0,    -28,  -47,
    141,  -33,  172,  239,  251,  264,  -70,  -106, -102, -100, 0,    8,    68,   -245, -215, 141,  -84,
    163,  174,  -250, 234,  251,  -151, -243, 264,  -70,  -98,  274,  278,  -100, 0,    13,   0,    3,
    62,   -221, 141,  -167, 231,  251,  -151, 264,  -70,  -106, 276,  -100, 0,    9,    58,

    60,   68,   116,  118,  141,  143,  163,  176,  229,  -111, 241,  251,  -151, 253,  255,  257,  259,
    264,  266,  -70,  274,  278,  -100, 0,    5,    64,   121,  141,  -89,  163,  -36,  182,  234,  251,
    -151, 264,  -70,  274,  278,  -100, 283,  0,    18,   64,   -220, 141,  147,  163,  187,  234,  251,
    -151, 264,  -70,  -141, -137, 274,  278,  -100, 0,    0,    -49,  0,    5,    64,   -221, 141,  -90,
    163,  -197, 234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    23,   64,   -220, 141,  147,  163,
    189,  234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    9,    68,   -245, 123,  141,

    149,  163,  -35,  191,  -251, 234,  251,  -151, -243, 264,  -70,  274,  278,  -100, 0,    5,    64,
    132,  141,  -96,  163,  -202, 234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    0,    -50,  -114,
    0,    3,    62,   -221, 141,  -167, 231,  251,  -151, 264,  -70,  -106, 276,  -100, 0,    -99,  0,
    -16,  0,    -28,  -47,  -148, 141,  -32,  -161, 239,  251,  264,  -70,  -106, -102, -100, 0,    27,
    73,   141,  -74,  163,  -164, 247,  251,  264,  -70,  274,  279,  -100, 0,    0,    102,  -69,  -65,
    -68,  0,    5,    64,   -223, 141,  155,  163,  200,  234,  251,  -151, 264,  -70,  274,

    278,  -100, 0,    0,    30,   76,   -245, 134,  141,  157,  163,  165,  202,  -247, 234,  251,  -151,
    -243, -54,  264,  269,  -70,  274,  278,  -100, -139, 0,    3,    62,   -219, 141,  -166, 231,  251,
    -151, 264,  -70,  -106, 276,  -100, 0,    38,   64,   -219, 141,  -92,  163,  209,  234,  251,  -151,
    264,  -70,  274,  278,  -100, 0,    3,    62,   -219, 141,  -166, 231,  251,  -151, 264,  -70,  -106,
    276,  -100, 0,    42,   -238, 82,   137,  141,  159,  163,  168,  211,  241,  251,  -151, -51,  -152,
    262,  264,  271,  -70,  274,  278,  -100, 281,  -139, 0,    23,   64,   -219, 141,  -92,

    163,  217,  234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    3,    62,   -219, 141,  -166, 231,
    251,  -151, 264,  -70,  -106, 276,  -100, 0,    5,    64,   -222, 141,  161,  163,  -170, 234,  251,
    -151, 264,  -70,  274,  278,  -100, 0,    89,   -69,  -65,  -68,  0,    5,    64,   -222, 141,  161,
    163,  -170, 234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    5,    64,   -219, 141,  -92,  163,
    -179, 234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    48,   64,   -219, 141,  -92,  163,  219,
    234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    0,    109,  -69,  -65,  -68,  0,

    5,    64,   -223, 141,  155,  163,  221,  234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    5,
    64,   -216, 141,  -76,  163,  -160, 234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    52,   0,
    0,    0,    0,    0,    0,    0,    0,    0,    5,    64,   -221, 141,  -90,  163,  -178, 234,  251,
    -151, 264,  -70,  274,  278,  -100, 0,    0,    5,    64,   -221, 141,  -90,  163,  223,  234,  251,
    -151, 264,  -70,  274,  278,  -100, 0,    -67,  -65,  -68,  0,    0,    5,    64,   -227, 141,  -95,
    163,  -202, 234,  251,  -151, 264,  -70,  274,  278,  -100, 0,    0,    0,    9,    -133,

    68,   -149, -245, -212, 141,  -97,  163,  225,  -248, -112, 234,  251,  -151, -243, -52,  -53,  264,
    -61,  -70,  274,  278,  -100, 0,    5,    -237, -104, -252, -242, 64,   -150, 139,  141,  -73,  163,
    -34,  227,  241,  251,  -151, -51,  -152, -55,  264,  272,  -70,  -241, 274,  -155, 278,  -100, -253,
    -154, 0,    9,    -133, 68,   -245, -212, 141,  -97,  163,  -115, 225,  -248, -113, 234,  251,  -151,
    -243, -52,  -53,  264,  -61,  -70,  274,  278,  -100, 0,    56,   87,   141,  -142, -165, 239,  251,
    -54,  264,  269,  -70,  -106, -102, -100, -139, 0,    -18,  0,    -28,  -47,  141,  -158,

    239,  251,  -57,  264,  -62,  -61,  -70,  -106, -102, -100, 0
};

int array_A162[] = {
    0,    9,    -10,  25,   -28,  21,   25,   -28,  7,    21,   25,   28,   -29,  11,   12,   13,   14,
    -15,  4,    5,    21,   25,   -28,  6,    21,   25,   -28,  1,    21,   -28,  17,   20,   21,   22,
    25,   26,   28,   -29,  3,    21,   25,   -28,  4,    5,    20,   21,   25,   -28,  2,    21,   25,
    -28,  19,   23,   24,   -27,  20,   -28,  239,  -240, 133,  -134, 46,   -47,  43,   44,   46,   -47,
    43,   44,   46,   47,   -48,  43,   44,   -47,  43,   44,   45,   46,   47,   -48,  43,   44,   45,
    46,   -47,  45,   -47,  116,  117,  118,  119,  120,  121,  122,  123,  124,  127,  130,

    131,  -132, 117,  118,  120,  125,  128,  131,  -132, 117,  118,  120,  126,  129,  131,  -132, 245,
    -246, 212,  214,  -217, 218,  -221, 228,  229,  230,  231,  232,  233,  234,  235,  -236, 211,  -227,
    224,  225,  -226, 214,  -219, 213,  -214, 135,  -136, 71,   72,   73,   -97,  93,   -94,  77,   78,
    79,   80,   81,   -82,  85,   -86,  75,   -83,  73,   -91,  87,   -88,  30,   -31,  145,  146,  -147,
    143,  -144, 175,  -178, 161,  -207, 185,  -204, 162,  163,  182,  183,  184,  -185, 161,  198,  199,
    200,  -201, 173,  -180, 172,  -181, 161,  185,  186,  187,  205,  206,  208,  209,  -210,

    169,  -171, 159,  165,  185,  194,  195,  196,  -203, 174,  -179, 163,  165,  188,  189,  191,  -193,
    190,  -192, 176,  -179, 168,  -171, 177,  -178, 162,  -185, 161,  -163, 248,  -249, 40,   41,   -42,
    38,   39,   40,   41,   -42,  40,   -41,  37,   38,   39,   40,   41,   -42,  38,   39,   40,   -41,
    109,  -110, 243,  -244, 51,   -52,  152,  -153, 53,   55,   -56,  54,   -55,  107,  -108, 59,   60,
    -61,  58,   -61,  58,   59,   -61,  105,  -106, 101,  -102, 101,  102,  -103, 156,  -157, 138,  -140
};

/* End file 3.c */
#endif
/*
 * File 4.c Created 21.01.2021 Last Modified 21.01.2021
 */
#if 1
int dopetab[72] = {
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

/*
char array_A542[] = {0, 'a', 'l', 'f'};

char *off_A592[] = {"", "bss", "text", "data"};

struct type {
  char	* t_str;
  int	  t_size;
  int	  t_alig;
  char	  t_flag;
};

 *
 *	Initializaion of type pointers
 */

/* sub_1680
struct type vars[14] = {
  {"i",  2, 0, 1}, {"s",  2, 0, 1}, {"c",  1, 0, 1},
  {"l",  4, 0, 1}, {"ui", 2, 0, 2}, {"us", 2, 0, 2},
  {"uc", 1, 0, 2}, {"ul", 4, 0, 2}, {"f",  4, 0, 3},
  {"d",  4, 0, 3}, {"x",  2, 0, 1}, {"ux", 2, 0, 2},
  {"b",  0, 0, 0}, {"v",  0, 0, 0}
};
*/

/* End file 4.c */
#endif
/*
 * File 5.c Created 21.01.2021 Last Modified 21.01.2021
 */
#if 1
char *regNames[] = { "", "a", "c", "b", "e", "d", "l", "h", "ix", "iy", "sp", "af", "bc", "de", "hl" };

/* clang-format off */
int array_AAE8[]     = { 0,     1,    2,    4,    8,    0x10, 0x20, 0x40, 0x80, 0x100,    /* 0-9 */
                         0x200, 1,    6,    0x18, 0x60, 0x78, 0x66, 0x7E, 0x7F, 0,        /* 10-19 */
                         0x79,  0x61, 0x19, 7,    0x7E, 0x1E, 0x3F, 0x3E, 0x7F, 0x1E };   /* 20-29 */

uint8_t array_AB24[] = { 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
                         0,  0,  1,  0,  2,  3,  4,  5,  6, 7,
                         0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
                         13, 14, 12, 14, 12, 15, 1,  17, 0, 0,
                         15, 1,  14, 1,  13, 1,  12, 1 };

uint8_t array_AB54[] = { 14, 13, 12, 0, 0, 0,         /* groups of 6 bytes, each is index into array_AAE8 */
                         13, 12, 0,  0, 0, 0,
                         1,  4,  5,  2, 3, 6,
                         4,  5,  2,  3, 6, 0,
                         21, 22, 23, 0, 0, 0,
                         12, 13, 0,  0, 0, 0,
                         0 };
/* clang-format on */
/* End file 5.c */
#endif
#endif

#if !defined(CPM) || !defined(DATA)
/*
 * File -  sub_13D.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 1
/*********************************************************
 * sub_13D				Used in: sub_1F4B
 *********************************************************/
int sub_13D(int a, int b) {
    int i;

    for (i = array_987D[b]; array_990D[i] != 0 && array_990D[i] != a; i++)
        ;
    return array_9BD4[i];
}

/*
 * File - sub_1B2.c Created 09.03.2019 Last Modified 21.01.2021
 */

/*********************************************************
 * char sub_1B2 OK++	       Used in: sub_6D1, sub_4192
 *
 * Token search		(Binary search algorithm is used)
 *********************************************************/
char sub_1B2(register char *target) {
    unsigned char hi, lo, mid;
    char cmp;

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
 * gethashptr OK++		Used in: sub_265, sub_1754
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
 *   "uc" 	30 1eh	- unsigned char
 *   "ui" 	36 24h	- unsigned int
 *   "ul" 	39 27h	- unsigned long
 *   "us" 	46 2eh	- unsigned short
 *   "ux" 	51 33h	- unsigned ?
 *   "b"  	98 62h	- b ?
 *   "c"  	99 63h	- char
 **********************************************************/

#define HASHTABSIZE 101

bbb_t **gethashptr(register char *str) {
    unsigned int key;

    /* calculate hash */
    for (key = 0; *str; str++)
        key = key * 2 + *(uchar *)str;

    /* Hash table index is determined by    */
    /* hash function using division method  */
    return &hashtab[key % HASHTABSIZE];
}

/*********************************************************
 * sub_265 OK++	     Used in: sub_627,  sub_B19,  sub_E43,
 *			      sub_1680, sub_1754, sub_4192
 *
 * Return pointer to struct associated with pointer to token
 *********************************************************/
bbb_t *sub_265(char *str) {
    bbb_t **l1b;
    register bbb_t *sb;

    /* In hash table, we look for pointer to    */
    l1b = gethashptr(str); /* entry in symbol table associated with    */
    /* scan for the matching name on the hash list */
    for (sb = *l1b; sb; sb = sb->b_next)
        if (strcmp(sb->b_name, str) == 0)
            return sb;
    /* not found so create new record & insert at head of list */
    sb         = allocmem(sizeof(bbb_t)); /* 22 bytes */
    sb->b_next = *l1b;
    sb->b_name = allocmem(strlen(str) + 1); /* effectively strdup */
    strcpy(sb->b_name, str);
    sb->b_ndpth = nstdpth;
    *l1b        = sb;

    return sb; /* position and return pointer to record.   */
}

/* End of file -  sub_1B2.c */
#endif

/*
 * File - getToken.c Created 09.03.2019 Last Modified 11.05.2020
 */
#if 1
/*********************************************************
 * sub_306 v1 OK+    Used in: sub_6D1,  sub_793,  sub_B19,
 *			      sub_E43,  sub_17E0, sub_19C1,
 *			      sub_4192
 * get_token	     No code matching
 *********************************************************/
char *getToken() {
    int ch, expectName;
    register char *ptr;

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
            strncpy(progname, buffer, sizeof(progname) - 1);
            expectName = false;
        } else if (buffer[0] == ';' && buffer[1] == ';') {
            do {
                fputchar(ch = fgetchar());
            } while (ch != '\n');
        } else
            return buffer;
    }
}

/* End of file getToken.c */
#endif
/*
 * File - leaveBlock.c Created 09.03.2019 Last Modified 09.12.2020
 */
#if 1

/*********************************************************
 * sub_406 v3 OK++			 Used in: sub_6D1
 *
 * Note:
 *   Added 0 parameter to sub_5CF5 function call to
 *   match number and types actual and formal parameters
 *   this function.
 *   sub_5CF5 function is called only if value sb->b_c13
 *   is 3 or 4. if this condition is met, variable "empty"
 *   in sub_5CF5 function is not used.
 *********************************************************/
/* remove and free up items which have got out of scope */

void leaveBlock() {
    bbb_t **pHashEntry;
    int l2;
    bbb_t *newlist;
    bbb_t *next;
    bbb_t **l5;
    int l6;
    register bbb_t *sb;

    l2         = HASHTABSIZE;
    pHashEntry = hashtab;
    do {
        newlist = 0;
        /* note with the fixed handling of free, this could be converted to a for loop */
        sb = *pHashEntry;
        while (sb && sb->b_ndpth == nstdpth) {
            if (sb->b_class == DECL9) {
                if (sb->b_c15 == 2)
                    word_B017 |= array_AAE8[sb->b_memb.i];
                if (sb->b_c15 == 4 || sb->b_c15 == 3)
                    sub_5CF5(sb, 0); /* Add parameter 0! */
                if (0 < nstdpth && sb->b_c15 == 3) {
                    next       = sb->b_next;
                    sb->b_next = newlist;
                    newlist    = sb;
                    sb->b_ndpth--;
                    sb = next;
                    continue;
                }
            }

            free(sb->b_name);

            if (sb->b_class == UDECL || sb->b_class == SDECL) {
                l6 = sb->b_memb.p->cnt;
                l5 = sb->b_memb.p->vals;
                while (l6-- != 0)
                    free(*(l5++));

                free(sb->b_memb.p);
            }
            /*  code modified to get sb->b_next before freeing sb !!!*/
            next = sb->b_next;
            free(sb);
            /* sb = sb->b_next original code relied on b_next not being at start of block !!!*/
            sb = next;
        }
        if (newlist) {                 /* if l3b list exists add to end */
            *(pHashEntry++) = newlist; /* set hash table to the l3b list */
            while (newlist->b_next)
                newlist = newlist->b_next; /* m14: */
            newlist->b_next = sb;
        } else
            *(pHashEntry++) = sb; /* else initialise hash table entry with new item  */
    } while (--l2 != 0);

    nstdpth--;
    if (lvlidx >= 0) {
        if (array_AE57[lvlidx] == nstdpth) {
            sb = array_AEDB[lvlidx];
            if (sb->b_type->b_class == SDECL && (sb->b_refl & 4) == 0)
                sub_BEE(sb->b_i11, sb->b_size);
            prFrameTail(sb->b_i11, array_AE13[lvlidx]);
            lvlidx--;
            word_B017 = 0x17F;
        }
    }
}

/*********************************************************
 * sub_627 OK++     Used in: sub_17E0, sub_19C1, sub_4192
 *********************************************************/
/* encode the accessor prefix */
bbb_t *sub_627(register char *ch, unsigned *par) {
    unsigned loc;

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
    return sub_265(ch);
}

/*********************************************************
 * sub_6C8 OK++			Used in: sub_6D1, expect
 *********************************************************/
void badIntCode(void) {

    fatalErr("Bad int. code");
}

/* End of file leaveBlock.c */
#endif
/*
 * File - sub_6D1.c Created 09.03.2019 Last Modified 26.05.2020
 */
#if 1

/*********************************************************
 * sub_6D1 OK+				    Used in: main
 *
 * Compiling intermediate code
 *
 * Note:
 * Compiler generates identical code from restored source
 * program in C, however, location of branches associated
 * with case constants is different from original.
 * This does not affect the function.
 *********************************************************/
void sub_6D1(void) {
    register char *ch;
    int tok;

    word_B017 = 0x17F;
    while ((ch = getToken()) != (char *)~0) { /* get_token    */
        switch ((tok = sub_1B2(ch))) {        /* search_token */
        case LBRACE:                          /* "{" opening block */
            nstdpth++;                        /* Increase the current nesting depth */
            break;
        case RBRACE: /* "}" end of block 	*/
            leaveBlock();
            break;
        case EXPR: /* "[e" expression	*/
            prPsect(P_TEXT);
            sub_3DC9(sub_4192());
            expect(']');
            break;
        case VAR: /* "[v" variable	*/
            sub_17E0();
            break;
        case STRUCT: /* "[s" struct	*/
        case UNION:  /* "[u" union	*/
            sub_19C1(tok);
            break;
        case CASE: /* "[\\" */
            sub_E43();
            break;
        case ENUM: /* "[c" enum		*/
            sub_1B0C();
            break;
        case INIT: /* "[i" initialization	*/
            sub_B19();
            break;
        case UNKNOWN: /* "[a" 		*/
            sub_793();
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

/* End of file sub_6D1.c */
#endif

/*
 * File - expect.c  Created 09.03.2019 Last Modified 26.05.2020
 */
#if 1

/*********************************************************
 * sub_76f OK++	      Used in: sub_6D1,  sub_B19, sub_E43,
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
 *********************************************************/
void sub_793(void) {
    char *loc1;
    char buf[1024];
    register char *ptr;

    prPsect(P_DATA);
    sub_2BD0(sub_600E(sub_43EF(COLON_U, sub_43EF(COLON_S, sub_4192(), 0), 0)));
    ptr = buf;
    for (ptr = buf; *(loc1 = getToken()) != ']'; ptr++) /* parse non-terminating tokens */
        *ptr = atoi(loc1);                              /* Convert string to int value and place it in buffer */

    prDefb(buf, ptr - buf); /* Emit data "defb byte1, ..." ("ptr-buf" bytes from "buf")*/
}

/* End of file expect.c  */
#endif

/*
 * File - sub_808.c Created 09.03.2019 Last Modified 17.06.2020
 */
#if 1

/*********************************************************
 * sub_808 OK+				 Used in: sub_B19
 *
 * Generated code is completely identical, except for
 * incomprehensible code inside function that does not
 * affect program logic
 *********************************************************/
int sub_808(register bbb_t *sb, aaa_t *p2a) {
    unsigned l1;
    int l2;
    bbb_t *l3b;
    bbb_t *l4b;
    int l5;
    aaa_t *l6a;

    l1 = 0;
    if (p2a->a_c0 == COLON_U) {
        sub_475C(p2a);
        l5 = 0;
        if (sb->b_class == SDECL) {
            l3b = sb;
            while ((p2a = sub_4192())->a_c0 != DOT_DOT) {
                if ((l2 = sub_1CC4(l4b = l3b->b_memb.p->vals[l5++])) != 0 && l1 % ++l2 != 0) {
                    l2 -= l1 % l2;
                    l1 += l2;
                    prDefb0s(l2); /* emit defb 0 to pad to item boundary */
                }
                if (l4b->b_c3 & 0x10) {
                    p2a = sub_43EF(BAND, p2a, sub_415E((1L << l4b->b_b5) - 1L));
                    if (l4b->b_b6 != 0)
                        l6a = sub_43EF(BOR, l6a, sub_43EF(LSHIFT, p2a, sub_415E(0L)));
                    else
                        l6a = p2a;

                    if (l5 != l3b->b_memb.p->cnt && (l3b->b_memb.p->vals[l5]->b_c3 & 0x10) &&
                        l3b->b_memb.p->vals[l5]->b_i11 == l4b->b_i11)
                        continue;
                    p2a = l6a;
                }
                l1 += sub_808(l4b, p2a);
            }

            sub_475C(p2a);
        } else {
            l3b = sb->b_type;
            for (;;) {
                while ((p2a = sub_4192())->a_c0 == COLON_U)
                    l1 += sub_808(l3b, p2a);

                if (p2a->a_c0 == DOT_DOT) {
                    sub_475C(p2a);
                    break;
                }
                l1 += nodesize(p2a);
                sub_2BD0(sub_600E(sub_43EF(ATGIGN, p2a, 0)));
            }
        }
    } else {
        p2a = sub_600E(sub_43EF(ATGIGN, p2a, 0));
        l1  = nodesize(p2a);
        sub_2BD0(p2a);
    }
    if (l1 < sb->b_size) {
        prDefb0s(sb->b_size - l1);
        l1 = sb->b_size;
    } else if (sb->b_size < l1 && sb->b_size != 0)
        prError("Too many initializers");

    return l1; /* m15: */
}

/* End of file - sub_808.c  */
#endif

/*
 * File - sub_B19.c Created 09.03.2019 Last Modified 21.01.2021
 */
#if 1

/*********************************************************
 * sub_B19 OK++				 Used in: sub_6D1
 *********************************************************/
void sub_B19(void) {
    register bbb_t *sb;
    int l1;
    int l2;

    sb = sub_265(getToken());
    prPsect(P_DATA);
    sub_CAB(sb); /* Emit "symbolic_name:" (identifier label) */
    l1 = sub_808(sb, sub_4192());
    l2 = sb->b_refl ? 2 : sb->b_type->b_size;
    if (sb->b_nelem == 0) { /* make sure nelem is set */
        sb->b_nelem = l1 / l2;
        sb->b_size  = varSize(sb);
    }
    expect(']');
}

/*********************************************************
 * sub_B96 OK++				Used in: sub_2BD0
 * emit_call_ncsv
 *********************************************************/
void prFrameHead(int fId) {

    prPsect(P_TEXT);
    if (frameGlobalsEmitted == false) /* if first call	*/
        printf("global\tncsv, cret, indir\n");

    printf("call\tncsv\n");
    frameGlobalsEmitted = true; /* first call is done	*/
    printf("defw\tf%d\n", fId);
}

/*********************************************************
 * sub_BCC OK++				 Used in: leaveBlock
 *********************************************************/
void prFrameTail(int fId, int fSize) {

    prPsect(P_TEXT);
    printf("jp\tcret\n"
           "f%d\tequ\t%d\n",
           fId, fSize);
}

/*********************************************************
 * sub_BEE OK++				 Used in: leaveBlock
 *********************************************************/
void sub_BEE(int kId, int size) {

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
 * sub_C36 OK++       Used in: sub_C57, sub_CAB, sub_4192
 *********************************************************/
void prGlobalDef(register bbb_t *sb) {

    printf("global\t%s\n", sb->b_name);
    sb->b_c3 |= 2;
}

/*********************************************************
 * sub_C57 OK++				Used in: sub_5CF5
 *********************************************************/
void sub_C57(register bbb_t *sb) {

    if ((sb->b_c3 & 1) == 0 && sb->b_nelem != 0 && (sb->b_refl & 2) == 0) {
        prPsect(P_BSS);
        if (sb->b_c15 == 3 && (sb->b_c3 & 2) == 0)
            prGlobalDef(sb); /* Emit "global name" */
        sub_CAB(sb);         /* Emit "symbolic_name:" (identifier label) */
        printf("\tdefs\t%u\n", sb->b_size);
    }
}

/*********************************************************
 * sub_CAB OK++			Used in: sub_B19, sub_C57
 *
 * Emit "symbolic_name:" (identifier label)
 *********************************************************/
void sub_CAB(register bbb_t *sb) {

    if ((sb->b_c3 & 2) == 0 && sb->b_c15 == 3)
        prGlobalDef(sb); /* Emit "global name" */
    sb->b_c3 |= 1;
    printf("%s:\n", sb->b_name);
}

/*********************************************************
 * sub_CDF OK++				 Used in: sub_808
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
 * prPsect OK++     Used in: sub_6D1,  sub_793,  sub_B19,
 * 			      prFrameHead,  prFrameTail,  sub_BEE,
 * Select psect		      sub_C57,  sub_E43
 *********************************************************/
void prPsect(int section) {

    static char *psectNames[] = { "", "bss", "text", "data" };

    if (section != curPsect) /* Only when changing section */
        printf("psect\t%s\n", psectNames[curPsect = section]);
}

/*********************************************************
 * sub_D66 OK+				 Used in: sub_E43
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
 * sub_E43 v2 OK++			 Used in: sub_6D1
 *********************************************************/
void sub_E43(void) {
    aaa_t *l1a;
    int codeLabel, swTableLabel, caseRange, caseCnt, defaultCodeLabel;
    uint16_t l7, l8;
    bool loTest, hiTest;
    int caseVals[255], codeLabels[255];
    register aaa_t *sa;

    l1a     = sub_4192();
    caseCnt = 0;
    for (;;) {
        sa        = sub_600E(sub_4192());
        codeLabel = atoi(getToken());
        if (sa->a_c0 == DOT_DOT) { /* end of switch block */
            defaultCodeLabel = codeLabel;
            freeAaa(sa);
            expect(']');
            if (caseCnt != 0)
                break;
            prWarning("No case\tlabels");
            sub_475C(l1a);
            printf("jp\tl%d\n", defaultCodeLabel);
            return;
        }
        if (sa->a_c0 == CONST) { /* only constants allowed */
            caseVals[caseCnt]     = sa->a_l19.ii[0];
            codeLabels[caseCnt++] = codeLabel;
        } else
            prError("Non-constant case label");
        sub_475C(sa);
    }
    sortCaseLabels(caseVals, codeLabels, caseCnt); /* m6:  */
    caseRange = caseVals[caseCnt - 1] - caseVals[0];
    if (0 <= caseRange && caseRange < 16000 && caseRange * 2 + 20 < caseCnt * 5) { /* if jmp table is shorter */
        /* jump table option is smaller so use it
           note the alternative cmp/jp option may be slower
           even if it is shorter
        */
        sa        = allocAaa();
        sa->a_c0  = TYPEOP;
        sa->a_s17 = l1a->a_s17;
        sa->a_i15 = l1a->a_i15;
        sa        = sub_43EF(CONV, sub_415E(caseVals[0]), sa);
        sa        = sub_43EF(SUB, l1a, sa);
        if (nodesize(sa) != 2) {
            l1a        = allocAaa();
            l1a->a_c0  = TYPEOP;
            l1a->a_s17 = sub_265("us");
            sa         = sub_43EF(CONV, sa, l1a);
        }
        prPsect(P_TEXT);
        sub_3DC9(sub_43EF(RPAREN, sa, 0));
        swTableLabel = newSwTable(); /* swTableCnt++ */
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
        sub_3DC9(sub_43EF(RPAREN, l1a, 0));
        l7     = -1;
        hiTest = loTest = false;
        l8              = 0;
        for (codeLabel = 0; codeLabel < caseCnt; codeLabel++) {
            l7 &= caseVals[codeLabel];
            l8 |= caseVals[codeLabel];
            if (l7 >> 8 != l8 >> 8 && (l7 & 0xFF) != (l8 & 0xFF)) {
                if (loTest | hiTest)
                    printf("1:\n"); /* target of previous hi/lo test */
                loTest = hiTest = false;
                l7 = l8 = caseVals[codeLabel];
            }
            if (l7 >> 8 == l8 >> 8) {
                if (!hiTest) {
                    printf("ld\ta,h\n");
                    sub_1420(l7 >> 8);
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
                    sub_1420(l7 & 0xFF);
                    printf("jp\tnz,1f\n"
                           "ld\ta,h\n");
                    loTest = true;
                }
                caseVals[codeLabel] >>= 8;
                caseVals[codeLabel] &= 0xFF;
            }
            sub_1420(caseVals[codeLabel]); /* m19: */
            printf("jp\tz,l%d\n", codeLabels[codeLabel]);
        }
        if (loTest | hiTest)
            printf("1:\n");
        printf("jp\tl%d\n", defaultCodeLabel); /* m21: */
        return;
    }

    prPsect(P_TEXT);
    sub_3DC9(sub_43EF(INAREG, l1a, 0));
    codeLabel = 0;
    for (codeLabel = 0; codeLabel < caseCnt; codeLabel++) {
        if (caseVals[codeLabel] < 0x100) {
            if ((int)caseVals[codeLabel] >= 0xFF80) {
                sub_1420(caseVals[codeLabel]);
                printf("jp\tz,l%d\n", codeLabels[codeLabel]);
            }
        }
    }
    printf("jp\tl%d\n", defaultCodeLabel);
}

/*********************************************************
 * sub_1420 OK++			 Used in: sub_E43
 *********************************************************/
void sub_1420(int par) {

    printf((unsigned)par ? "cp\t%d\n" : "or\ta\n", par);
}

/*********************************************************
 * sub_143F OK++			Used in: sub_35E6
 *********************************************************/
void prPush(uchar reg) {

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
 * sub_1489 OK++			Used in: sub_35E6
 *********************************************************/
void prPop(uchar reg) {

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
 * sub_14D3 OK++			Used in: sub_1EDF
 *
 * Assigning register "IY" value formal parameter with
 * type register
 *********************************************************/
void sub_14D3(register bbb_t *sb) {

    printf("ld\tl,(ix+%d)\n"
           "ld\th,(ix+%d)\n"
           "push\thl\n"
           "pop\tiy\n",
           sb->b_i11, sb->b_i11 + 1);
}

/*********************************************************
 * sub_14F3 OK++   Used in: sub_153A, sub_2D09, sub_39CA,
 *			    sub_3A79, sub_3EAA, sub_47B2,
 *			    sub_4FCE, sub_508A, sub_54B6,
 *			    sub_60A8, sub_6246, sub_628F
 *********************************************************/
uint8_t sub_14F3(register aaa_t *sa) {

    if (sa->a_i15 & 2)
        return 0;
    if (sa->a_i15 != 0)
        return 2;
    if (sa->a_s17->b_nelem > 1)
        return 0;
    return sa->a_s17->b_c15;
}

/*********************************************************
 * sub_153A OK++			Used in: sub_2D09
 *********************************************************/
void sub_153A(register aaa_t *sa) {

    static char array_A542[] = { 0, 'a', 'l', 'f' };

    fputchar(array_A542[sub_14F3(sa)]);
}

/*********************************************************
 * sub_155D OK++			 Used in: sub_793
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
            fputchar(',');           /* later "," 			   */
        printf("%d", (uchar)*ptr++); /* Output byte and advance pointer */
        cnt++;                       /* update number bytes output 	   */
        if (cnt == 16) {             /* max 16 bytes per line */
            fputchar('\n');
            cnt = 0;
        }
    }
    if (cnt != 0)
        fputchar('\n'); /* If line is incomplete, new line */
}

/*********************************************************
 * xx1	 OK++		Used in: Explicit calls are absent
 *********************************************************/
void prJmpLabel(int p) {
    printf("j%d:\n", p);
}

/*********************************************************
 * xx2	 OK++		Used in: Explicit calls are absent
 *********************************************************/
void prJump(int p) {
    printf("jp\tj%d\n", p);
}

/*********************************************************
 * sub_15FB OK++			Used in: sub_1B0C
 *********************************************************/
void sub_15FB(register bbb_t *sb, int p2, int p3) {

    if (p2 >= 0) {
        sb->b_c15  = 2;
        sb->b_size = p3 <= 255 ? 1 : 2;
    } else {
        sb->b_c15  = 1;
        sb->b_size = p3 <= 127 ? 1 : 2;
    }
}

/* End of file - sub_B19.c  */
#endif

/*
 * File - sub_1659.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 1
/*********************************************************
 * sub_1659 OK++			Used in: sub_1CEF
 * Find maximum between two numbers
 *********************************************************/
int max(int num1, int num2) {
    return (num1 > num2) ? num1 : num2;
}

/* End of file - sub_1659.c  */
#endif

/*
 * File - sub_1680.c Created 09.03.2019 Last Modified 21.01.2021
 */
#if 1

#define NVARS 14

/*********************************************************
 * sub_1680 OK++			    Used in: main
 *
 * first_init
 *********************************************************/
void sub_1680(void) {
    bbb_t *sb;
    unsigned cnt;
    register struct type *tp;

    /*
     *	Initializaion of type pointers
     */
    static struct type vars[NVARS] = { /* sub_1680 */
                                       { "i", 2, 0, 1 },  { "s", 2, 0, 1 },  { "c", 1, 0, 1 },  { "l", 4, 0, 1 },
                                       { "ui", 2, 0, 2 }, { "us", 2, 0, 2 }, { "uc", 1, 0, 2 }, { "ul", 4, 0, 2 },
                                       { "f", 4, 0, 3 },  { "d", 4, 0, 3 },  { "x", 2, 0, 1 },  { "ux", 2, 0, 2 },
                                       { "b", 0, 0, 0 },  { "v", 0, 0, 0 }
    };

    /* Clear hash table */

    blkclr((char *)hashtab, sizeof(hashtab));

    /* Create a hash table of templates for standard types */

    cnt = NVARS;
    tp  = vars;
    do {
        sb          = sub_265(tp->t_str);
        sb->b_class = TDECL;
        sb->b_i11   = tp->t_alig;
        sb->b_size  = tp->t_size;
        sb->b_c15   = tp->t_flag;
        tp++;
    } while (--cnt != 0);

    /* Additional patterns for types */

    word_AE11 = sub_265("l");  /* long	  	*/
    word_AED7 = sub_265("d");  /* double 	*/
    word_AF1B = sub_265("b");  /* b   	  	*/
    word_AFE9 = sub_265("v");  /* variable 	*/
    word_AED9 = sub_265("c");  /* char   	*/
    word_AE53 = sub_265("uc"); /* uchar  	*/
    word_AF1D = sub_265("x");  /* x      	*/
    lvlidx    = -1;
}

/*********************************************************
 * sub_174C OK++    Used in: sub_E43,  sub_17E0, sub_39CA,
 *			     sub_4192, sub_508A
 *********************************************************/
int newSwTable(void) {

    return ++swTableCnt;
}

/*********************************************************
 * sub_1754 OK++    Used in: sub_17E0, sub_19C1, sub_1B0C
 *********************************************************/
bbb_t *sub_1754(char *token, uint8_t cls) {
    bbb_t **l1b;
    register bbb_t *sb;

    sb = sub_265(token);                          /* Set pointer to struct associated with   */
                                                  /* pointer to token.			   */
    if (sb->b_ndpth != nstdpth) {                 /* If nesting depth not correspond current,*/
        l1b        = gethashptr(token);           /* Get pointer to pointer to struct from   */
        sb         = allocmem(sizeof(bbb_t));     /* hash table. Create new struct and save  */
        sb->b_next = *l1b;                        /* pointer to struct from hash table in    */
                                                  /* struct as associated with it. 	   */
        *l1b = sb;                                /* Save pointer to this struct in current  */
                                                  /* position hash table.			   */
        sb->b_name = allocmem(strlen(token) + 1); /* Get memory address allocated for token  */
                                                  /* and assign it to corresponding member.  */
        strcpy(sb->b_name, token);                /* Copy specified token to this address.   */
        sb->b_ndpth = nstdpth;                    /* Save current nesting depth in struct    */
                                                  /*
                                                        if(++symcnt > dynmem)   dynmem = symcnt;
                                                  */
    }
    sb->b_class = cls;
    return sb;
}

/* End of file sub_1680.c  */
#endif

/*
 * File - sub_17E0.c Created 09.03.2019 Last Modified 17.06.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_17E0 OK+			Used in: sub_6D1, sub_4192
 *
 * Compiler generates identical code from restored source
 * program in C, however, location of branches associated
 * with case constants is different from original.
 * This does not affect the function.
 *********************************************************/
void sub_17E0(void) {
    aaa_t *l1a;
    int l2;
    register bbb_t *sb;

#ifdef DEBUG
    printf("\tsub_17E0()\n");
#endif

    sb         = sub_1754(getToken(), DECL9);
    sb->b_type = sub_627(getToken(), &sb->b_refl);
    l1a        = sub_600E(sub_4192());
    if (l1a->a_c0 != CONST)
        fatalErr("Bad element count expr");
    sb->b_nelem = l1a->a_l19.ii[0]; /* ??? */
    sub_475C(l1a);
    l2 = *getToken();
    expect(']');

#ifdef DEBUG
    printf("\tsub_17E0\t\tl2=%c\n", l2);
#endif

    switch (l2) {
    case 'A': /* auto		*/
    case 'a':
        sb->b_c13 = 1;
        break;
    case 'E': /* extern	*/
    case 'e':
        sb->b_c13 = 3;
        break;
    case 'R': /* register	*/
    case 'r':
        sb->b_c3 |= 8;
    case 'P': /* pointer	*/
    case 'p':
        sb->b_c13 = 5;
        break;
    case 'S': /* static 	*/
    case 's':
        sb->b_c13 = 4;
        break;
    case 'T': /* typedef	*/
    case 't':
        sb->b_class = TDECL;
        if (sb->b_refl != 0) {
            sb->b_i11 = 0;
            sb->b_c13 = 2;
        } else {
            sb->b_i11 = sb->b_type->b_i11;
            sb->b_c13 = sb->b_type->b_c13;
        }
        if (sb->b_nelem != 1) {
            sb->b_c13 = 0;
        }
        break;
    default:
        fatalErr("Bad storage class");
    }
    sb->b_size = varSize(sb);
    if (sb->b_class != TDECL) {
        if ((sb->b_refl == 0) && (sb->b_size == 0) && (sb->b_type->b_size == 0)) {
            prError("Bad dimensions");
        }
        switch (sb->b_c13) {
        case 1:
        case 5:
            sub_5CF5(sb, l2);
            break;
        default:
            sb->b_i11 = newSwTable(); /* swTableCnt++ */
        }
        if ((sb->b_refl & 0x2) != 0) {
            if (sb->b_nelem != 0) {
                if (++lvlidx == MAXFUN) {
                    fatalErr("Functions nested too deep");
                }
                array_AE57[lvlidx] = nstdpth; /* Save current nesting depth */
                array_AE97[lvlidx] = 6;
                array_AE13[lvlidx] = 0;
                array_AEDB[lvlidx] = sb;
            }
        }
    }
#ifdef DEBUG
    printf("\tsub_17E0\t\t Exit\n");
#endif
}

/* End of file sub_17E0.c  */
#endif

/*
 * File - sub_19C1.c Created 09.03.2019 Last Modified 17.06.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"
#include <stdlib.h>

/*********************************************************
 * sub_19C1 OK++	       Used in: sub_6D1, sub_4192
 *********************************************************/
void sub_19C1(int p1) {
    int l1;
    bbb_t *l2b;
    int *l3;
    aaa_t *l4a;
    char *l5;
    int arr[258];
    register bbb_t *sb;

#ifdef DEBUG
    printf("\tsub_19C1(%d)\n", p1);
#endif

    l2b = sub_1754(getToken(), p1);
    l3  = arr;
    *l3 = 0;
    for (;;) {
        l5 = getToken();
        if (*l5 == ']')
            break;
        sb          = (bbb_t *)allocmem(sizeof(bbb_t)); /* Create bbb_t */
        sb->b_class = MEMBER;
        if (*l5 == ':') {
            sb->b_b5) = atoi(l5 + 1);
            bitset(sb->b_c3, 4);
            l5 = getToken();
        }
        sb->b_type = sub_627(l5, &sb->b_refl);
        l4a        = sub_600E(sub_4192());
        if (l4a->a_c0 != CONST)
            fatalErr("Strucdecl - bad\tnelem");
        sb->b_nelem = l4a->a_l19.ii[0];
        sub_475C(l4a);
        sb->b_size                  = varSize(sb);
        *(((++(*l3)) - 1) + l3 + 1) = sb; /* assigning to "int" from "bbb_t *" */
                                          /*
                                                ++membcnt;
                                          */
    }
    l1 = (0xffff + (unsigned)*l3) * 2 + 4;
    l3 = allocmem(l1); /* create ??? */
    movmem(arr, l3, l1);
    l2b->b_memb = l3;
    sub_1CEF(l2b);
}

/*********************************************************
 * sub_1B0C OK++		Used in: sub_6D1, sub_4192
 *
 * In original executable file CGEN stack recovery code is
 * missing when returning from expect function
 *********************************************************/
void sub_1B0C(void) {
    aaa_t *l1a;
    int *l2;
    int l3;
    int l4;
    int *l5;
    int arr[258];
    register bbb_t *sb;

#ifdef DEBUG
    printf("\tsub_1B0C()\n");
#endif

    l3  = MININT; /* arithmetic overflow in constant expression */
    l4  = MAXINT;
    sb  = sub_1754(getToken(), EDECL);
    l2  = arr;
    *l2 = 0;
    for (;;) {
        l1a = sub_4192();
        if (l1a->a_c0 == DOT_DOT) {
            sub_475C(l1a);
            l5 = ((*l2) - 1) * 2 + 4;                                        /* assigning to "int *" from "int" */
            l2 = allocmem(l5); /* passing "int *" to parameter type "int" */ /* create ??? */
            movmem(arr, l2, l5);
            sb->b_memb = l2;      /*	 In file CGEN.COM stack	recovery */
            sub_15FB(sb, l4, l3); /*	 failed when returning from	 */
            expect(']');         /* <---- function expect 		 */
            return;
        }
        l1a                         = sub_600E(l1a);

        *(((++(*l2)) - 1) + l2 + 1) = l1a->a_l19.ii[0];

        if ((long)l3 < l1a->a_l19.l)
            l3 = l1a->a_l19.ii[0];
        if (l1a->a_l19.l < (long)l4)
            l4 = l1a->a_l19.ii[0];
        sub_475C(l1a);
    }
}

/* End of file sub_19C1.c  */
#endif

/*
 * File - sub_1C6D.c Created 19.03.2019 Last Modified 04.04.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_1C6D OK++			Used in: sub_1CEF
 *********************************************************/
int sub_1C6D(int p1, int p2) {

#ifdef DEBUG
    printf("\tsub_1C6D(%x, %x)\n", p1, p2);
#endif

    return (p1 + p2) & ((-1) - p2);
}

/* End of file sub_1C6D.c  */
#endif

/*
 * File - varSize.c  Created 09.03.2019 Last Modified 17.06.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * varSize OK++   Used in: sub_B19, sub_17E0, sub_19C1
 *********************************************************/
int varSize(register bbb_t *sb) {

#ifdef DEBUG
    printf("\tsub_1C8E(%x)\n", sb);
#endif

    if ((sb->b_refl & 0x1) != 0)
        return sb->b_nelem * 2;
    return sb->b_type->b_size * (sb->b_nelem);
}

/*********************************************************
 * sub_1CC4 OK++	       Used in: sub_808, sub_1CEF
 *********************************************************/
int sub_1CC4(register bbb_t *sb) {

#ifdef DEBUG
    printf("\tsub_1CC4(%x)\n", sb);
#endif

    if (sb->b_refl != 0)
        return 0;
    return sb->b_type->b_i11;
}

/*********************************************************
 * sub_1CEF OK++			Used in: sub_19C1
 *********************************************************/
void sub_1CEF(register bbb_t *sb) {
    int l1;
    int l2;
    int l3;
    bbb_t *l4b;

#ifdef DEBUG
    printf("\tsub_1CEF(%x)\n", sb);
#endif

    l1 = 0;
    l2 = l3 = 0;
    while (l2 != *sb->b_memb) {                 /* m9: */
        l4b = *(sb->b_memb + l2 + 1); /* m1: */ /* assigning to "bbb_t *" from "int"*/
        if (sb->b_class == UDECL) {
            l1         = max(l1, l4b->b_size); /* return max number */
            l4b->b_i11 = 0;
            goto m8;
        }
        l1 = l4b->b_i11 = sub_1C6D(l1, sub_1CC4(l4b)); /* m2: */
        if ((l4b->b_c3 & 0x10) != 0) {
            if (16 < l3 + l4b->b_b5 || l4b->b_b5) == 0)) {
                if (l3 != 0) { /* m3: */
                    l4b->b_i11 = (l1 += 2);
                }
                l3 = 0; /* m4: */
            }
            l4b->b_b6 = l3; /* m5: */
            l3 += l4b->b_b5);
            if (l3 != ' ')
                goto m8;
            l3 = 0;
            l1 += 2;
            goto m8;
        }
        if (l3 != 0) { /* m6: */
            l3         = 0;
            l4b->b_i11 = (l1 += 2);
        }
        l1 += l4b->b_size; /* m7: */
    m8:
        l2++;
    }
    if (l3 != 0) {
        l3 = 0;
        l1 += 2;
    }
    sb->b_size  = sub_1C6D(l1, 0); /* m10: */
    sb->b_i11   = 0;
    sb->b_class = SDECL;
}

/*********************************************************
 * sub_1EDF OK++			Used in: sub_2BD0
 *********************************************************/
void sub_1EDF(void) {
    bbb_t **l1b;
    register bbb_t *sb;

#ifdef DEBUG
    printf("\tsub_1EDF()\n");
#endif

    l1b = hashtab;
    do {
        sb = *l1b;
        while ((sb != 0) && ((uchar)sb->b_ndpth == nstdpth)) {
            if (sb->b_class == DECL9) {
                if (sb->b_c13 == 2) {
                    if ((sb->b_c3 & 4) != 0)
                        sub_14D3(sb); /* Assigning register "IY" value formal parameter with type register */
                }
            }
            sb = sb->b_next;
        }
    } while (++l1b != &word_AFE9); /* variable */
}

/* End of file sub_1C6D.c  */
#endif

/*
 * File - sub_1F4B.c Created 09.03.2019 Last Modified 21.01.2021
 */
#if 0

#include "cgen.h"
#include "stdio.h"
#include <ctype.h>

/* int asdf; */
/*********************************************************
 * sub_1F4B OK+ (optim: Out of memory)	Used in: sub_2BD0
 *********************************************************/
int sub_1F4B(aaa_t *p1a, int p2, int p3, int p4, int *p5) {
    int l1, l2, l3, l4, l5, l6, l7, l8;
    register struct zzz *sz;

#ifdef DEBUG
    printf("\tsub_1F4B(%x, %d, %d, %d, %x)\n", p1a, p2, p3, p4, p5);
#endif

    /**/
    if (p1a->a_c1 == 0)
        p1a->a_c2 = 0;
    if ((l1 = sub_13D(p2, p1a->a_c0)) == 0)
        return (-1);
#if 1
    if (dummy1(p1a, p3, p4) == -1)
        return (-1);
#else
/*
    if(p4 != 0) {
      if((p4 & 0x8000) == 0) {
        if(sub_6589(p3, p4) == (int)0) {
          if(p1a->a_c0 != USEREG) return (-1);
          if(sub_6589(array_AAE8[p1a->a_l19.ii[0]], p4) == (int)0) return (-1);
        }
      }
    }
*/
#endif

m4:
    if (l1 > 0)
        word_AFED = l5 = array_A162[l1++];
    else
        word_AFED = l5 = l1;
k6:
    if (word_AFED < 0)
        word_AFED = (0 - word_AFED); /* ok */
k7:
    sz = &array_80EF[word_AFED];

    if ((sz->c_2 != 0) && (sub_6589(p3, sz->c_2) == 0))
        goto m9;

k8:
    if ((uchar)sz->c_3 < 'H') {
        if (sz->c_4 != 0) {
            if (sub_13D((uchar)sz->c_4, p1a->a_l19.wi[0]->a_c0) == 0)
                goto m9;
            if (sz->c_5 != 0) {
                if (sub_13D((uchar)sz->c_5, p1a->a_l19.wi[1]->a_c0) == 0) {
                m9:
                    if (l5 >= 0)
                        goto m4; /* ok */
                    return (-1);
                }
            }
        }
    }
/**/

/*
m9: if(((unsigned)l5 & 0x8000) != 0) return (-1);
    asdf = 1;
*/

/**/
k10:
    if ((sz->c_0 != 0) && (sub_47B2(p1a, sz->c_0) == 0))
        goto m9;
k11:
    l6 = sz->c_1;
    l7 = 0;
    if ((p4 == 0) && (sz->c_3 == 'E'))
        p4 = sz->c_3;
k12:
    if (p4 != 0) {
        if ((p4 & 0x8000) != 0) {
            if (l6 != 0) {
                if (sub_6589(p4 & (~0x8000), l6) == 0)
                    goto m30;
            }
        }
    k13:
        if ((word_AFEF = sz->p_8) != 0) {
            if ((*word_AFEF == 'L') && (*(word_AFEF + 1) == 0))
                word_AFEF = "GL"; /* array_A94A */
        k28:
            while (*(word_AFEF) != 0) {
            k14:
                byte_AFF3 = *word_AFEF;
                if (byte_AFF3 == 'X')
                    goto m15;
                if (byte_AFF3 == 'G')
                    goto m15;
                if (byte_AFF3 != 'S')
                    goto m26;
                if (p1a->a_c0 == USEREG)
                    goto m15;
                goto m26;
            m15:
                if (isdigit(*(++word_AFEF)) != 0)
                    word_AFF1 = word_AFEF;
                else
                    word_AFF1 = (char *)0;
                while (*(word_AFEF) < 'A')
                    word_AFEF++;
                if (*(word_AFEF) == 'L')
                    goto m20;
                if (*(word_AFEF) == 'N')
                    goto m23;
                if (*(word_AFEF) != 'R')
                    continue;
                goto m22;

            m20:
                if ((l6 = sub_66BC(l6, p4, p3, word_AFF1)) == 0) {
                m21:
                    l6 = -1;
                }
                goto m30;

            m22:
                l7 = p4;
                goto m30;

            m23:
                if (byte_AFF3 != 'S')
                    goto m25;
                if (p1a->a_c0 != USEREG)
                    goto m30;
                if (sub_66BC(l6, p4, array_AAE8[p1a->a_l19.ii[0]], word_AFF1) == 0) {
                    l6 = -1;
                }
                goto m30;

            m25:
                if (sub_63B8(p3, p4, sz->c_2) != 0)
                    goto m30;
                if ((p4 & 0x8000) == 0)
                    goto m21;
                if (sub_66BC(sz->c_2, p4, p3, word_AFF1) == 0) {
                    l6 = -1;
                }
                goto m30;
            m26:
                word_AFEF++;
            }
        } else {
        k29:
            if ((l6 = sub_66BC(l6, p4, p3, 0)) == 0)
                l6 = -1;
        }
    }
/**/
m30:
    if (l6 == -1)
        goto m9;
    l4 = 0;
    if ((uchar)sz->c_3 >= 'H') {
        p1a->a_c1 = 0;
        if (sub_1F4B(p1a, (uchar)sz->c_3, p3, l6, &l2) >= 0)
            goto m42; /* ok */
        p1a->a_c1 = 0;
        goto m9;
    }
k31:
    if (sz->c_4 != 0) {
        *(p1a->a_l19.ci[0] + 1) = 0;
        if (sub_1F4B(p1a->a_l19.wi[0], (uchar)sz->c_4, p3, l6, &l2) < 0)
            goto m9; /* ok */
        if (sz->c_5 == 0)
            goto m42;
        *(p1a->a_l19.ci[1] + 1) = 0;
        l8                      = sub_2B2A(p1a->a_l19.wi[0]);
        if (l7 == 0) {
            if (sz->c_2 != 0)
                l7 = array_AAE8[(uchar)sub_63B8(p3, p4, sz->c_2)];
            else
                l7 = 0;
        k33:
            l7 = ((l8 | l7) != 0) ? (((unsigned)(l8 | l7)) | 0x8000) : 0;
        }
    k36:
        if (sub_1F4B(p1a->a_l19.wi[1], (uchar)sz->c_5, p3, l6, &l3) < 0)
            goto m9; /* ok */
        l4 = sub_2B2A(p1a->a_l19.wi[1]);
        if ((l4 | l8) != 0) {
            *(p1a->a_l19.ci[1] + 1) = 0;
            if (0 >= sub_1F4B(p1a->a_l19.wi[1], (uchar)sz->c_5, (p3 & ((-1) - l8)), l7, &l3))
                goto m9;
            l4 = sub_2B2A(p1a->a_l19.wi[1]);
        }
    k37:
        if ((dopetab[p1a->a_c0] & 0x100) != 0)
            goto m38; /* LOGOP & QUEST */
        if ((l4 & l2) != 0) {
        m38:
            if ((l8 & l3) != 0) { /* m38: */
                if ((dopetab[p1a->a_c0] & 0x100) != 0)
                    goto m9; /* LOGOP & QUEST */
                p1a->a_c2 = 2;
                l4        = 0;
                goto m42;
            } else {
            k39:
                p1a->a_c2 = 1; /* m39: */
                goto m42;
            }
        }
    k40:
        p1a->a_c2 = 0; /* m40: */
    } else {
    k41:
        if (l6 != 0)
            p4 = l6;
    }
m42:
    if (sz->c_2 != 0) {
        word_AFF4 = p3;
        if ((sz->c_2 & 0x40) == 0)
            goto m43;
        word_AFF6 = (unsigned)sub_63B8(sub_2B2A(p1a), p4, sz->c_2);
        if (word_AFF6 == 0) {
        m43:
            if ((sz->c_2 & 0x40) == 0)
                word_AFF4 &= ((-1) - sub_2B2A(p1a));
        k44:
            word_AFF4 &= ((-1) - l4);
            word_AFF6 = (unsigned)sub_63B8(word_AFF4, p4, sz->c_2);
            if (word_AFF6 == 0) {
                word_AFF6 = (uchar)sub_6589(word_AFF4, sz->c_2);
                if (word_AFF6 == 0)
                    goto m9;
            }
        }
    k45:
        *((uchar)p1a->a_c1 + (uchar *)p1a + 9) = word_AFF6;
    } else {
    k46:
        *((uchar)p1a->a_c1 + (uchar *)p1a + 9) = 0;
    }
k47:
    *((uchar)(p1a->a_c1++) + (uchar *)p1a + 3) = (sz - array_80EF);
    word_AFF6                                  = (uchar)sub_2B79(p1a);
    *((uchar *)p1a + (uchar)p1a->a_c1 + 0xE)   = word_AFF6;
    if (word_AFF6 == 0) {
        if (p1a->a_c0 == USEREG) {
            *((uchar *)p1a + (uchar)p1a->a_c1 + 0xE) = (word_AFF6 = p1a->a_l19.ii[0]);
        }
    }
k48:
    if (p4 != 0) {
        if ((p4 & 0x8000) == 0) {
            if (word_AFF6 == 0)
                goto m58;
            if ((uchar)sub_6589(((p4 & 0x8000) != 0) ? ((-1) - p4) : array_AAE8[p4], word_AFF6) != word_AFF6)
                goto m58;
        }
    }

#if 1
    if (dummy2(p4) == -1) {
        p1a->a_c1--;
        goto m9;
    }
#else
k51:
    if ((p4 & 0x8000) != 0) {
        if ((((p4 & 0x8000) ? (-1) - p4 : array_AAE8[p4]) &
             ((word_AFF6 & 0x8000) ? (-1) - word_AFF6 : array_AAE8[word_AFF6])) !=
            ((word_AFF6 & 0x8000) ? (-1) - word_AFF6 : array_AAE8[word_AFF6])) {
        m58:
            p1a->a_c1--;
            goto m9;
        }
    }
#endif

k59:
    *p5 = array_AAE8[*((uchar *)p1a + (uchar)p1a->a_c1 + 8)];
    if (((uchar)sz->c_3 >= 'H') || (sz->c_4 != 0))
        *p5 |= l2;
    if (sz->c_5 != 0)
        *p5 |= l3;
    return 1;
}

/* End of file sub_1F4B.c  */
#endif

#if 0
/*
 * dummy1
 */
int dummy1(aaa_t *p1a, int p3, int p4) {

#ifdef DEBUG
    printf("\tdummy1(%x, %d, %d)\n", p1a, p3, p4);
/*
    pr_st_a(p1a);
*/
#endif

    if (p4 != 0) {
        if ((p4 & 0x8000) == 0) {
            if (sub_6589(p3, p4) == (int)0) {
                if (p1a->a_c0 != USEREG)
                    return (-1);
                if (sub_6589(array_AAE8[p1a->a_l19.ii[0]], p4) == (int)0)
                    return (-1);
            }
        }
    }
    return 0;
}

/*
 * dummy2
 */
int dummy2(int p4) {
#ifdef DEBUG
    printf("\tdummy2(%d)\n", p4);
#endif

    if (p4 != 0) {
        if ((p4 & 0x8000) == 0) {
            if (word_AFF6 == 0)
                goto m58;
            if ((uchar)sub_6589(((p4 & 0x8000) != 0) ? ((-1) - p4) : array_AAE8[p4], word_AFF6) != word_AFF6)
                goto m58;
        }
    }
    if ((p4 & 0x8000) != 0) {
        if ((((p4 & 0x8000) ? (-1) - p4 : array_AAE8[p4]) &
             ((word_AFF6 & 0x8000) ? (-1) - word_AFF6 : array_AAE8[word_AFF6])) !=
            ((word_AFF6 & 0x8000) ? (-1) - word_AFF6 : array_AAE8[word_AFF6])) {
        m58:
            return -1;
        }
    }
    return 0;
}
#endif

/*
 * File - sub_283E.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"
#include <ctype.h>

/*********************************************************
 * sub_283E OK+				 Used in: sub_2B2A
 *
 * Restored source code did not allow optimizer to reduce
 * number of sub_2B2A function calls to one.
 *
 * The switch statement, in comparison with if, more clearly
 * reflects the structure of the program, however, fragments
 * of the generated assembler code are arranged in an order
 * different from the original.
 *********************************************************/
int sub_283E(register aaa_t *sa, int par) {
    char *l1;
    struct zzz *l2z;
    aaa_t *l3a;
    char *l4;
    char l5;
    int l6;
    int l7;

#ifdef DEBUG
    printf("\tsub_283E(%x, %x)\n", sa, par);
#endif

    l2z = &array_80EF[*(par + (uchar *)&sa->a_c3)];
    l7  = 0;
    l1  = l2z->p_8;
m1:
    if (*(l1) == 0)
        return l7 & word_B017;
    switch (l5 = *(l1++)) {
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
        for (;; l1++) { /* m23: */
            if (*l1 == 0)
                goto m1; /* m24: */
            if (*l1 == 'N')
                goto m1;
            if (*l1 == 'L')
                goto m1;
            if (*l1 == 'R')
                goto m1;
        }
    case 'D':
    case 'U':
        goto m1;
    case 'X':
    case 'G':
        if (isdigit(*l1) != 0) { /* m4:	*/
            l4 = l1;
            while (isdigit(*l1) != 0) {
                l1++;
            };
        } else {
            l4 = 0; /* m7:  */
        }
        switch (*(l1++)) { /* m8:	*/
        case 'L':
            if (0 < par) { /* m11: */
                l3a = sa;
                l6  = par - 1;
                break;
            }
            l6 = *((uchar *)(l3a = sa->a_l19.wi[0]) + 1) - 1; /* m14: */
            break;
        case 'N':
            l6  = par; /* m10: */
            l3a = sa;
            break;
        case '~':
            l6 = *((uchar *)(l3a = sa->a_l19.wi[1]) + 1) - 1; /* m15: */
            break;
        }
        if (l5 == 'S') { /* m9: */
            if (l3a->a_c0 == USEREG) {
                l5 = l3a->a_l19.bc[0];
            } else {
                l5 = 0; /* m16: */
            }
        } else {
            l5 = (l5 == 'G') ? /* m17: */
                     *(l6 + (uchar *)&l3a->a_reg)
                             : *(l6 + (uchar *)&l3a->a_i6);
            if (l4 != 0) {
                while (isdigit(*((char *)par)) != 0) { /* cast to "char *" from smaller integer type "int" */
                    l5 = array_AB24[(uchar)l5 * 2 + ((-48) + *(l4++))];
                }
            }
        }
        l7 |= array_AAE8[(uchar)l5]; /* m22: */
        if (l5 != 0)
            byte_AFFA = l5;
        goto m1;
    case 'L':
        l7 |= (0 >= par) ? /* m27: */
                  sub_2B2A(sa->a_l19.wi[0])
                         : sub_283E(sa, par - 1);
        goto m1;
    case 'R':
        l7 |= sub_2B2A(sa->a_l19.wi[1]); /* m31: */
        goto m1;
    case '~':
        for (;; l1++) { /* m25: */
            if (*l1 == 0)
                goto m1; /* m26: */
            if (*l1 == 'L')
                goto m1;
            if (*l1 == 'R')
                goto m1;
        }
    }
    goto m1;
}

/* End of file sub_283E.c  */
#endif

/*
 *  File - sub_2B2A.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 1

/*********************************************************
 * sub_2B2A OK+      Used in: sub_1F4B, sub_283E, sub_2B79
 *********************************************************/
int sub_2B2A(register aaa_t *sa) {

    if (sa->a_c1 == 0) {
        if ((dopetab[sa->a_c0] & 0xC) == 0)
            return 0;
        return sub_2B2A(sa->a_l19.wi[0]); /* LOGOP & QUEST */
    }
    return sub_283E(sa, sa->a_c1 - 1);
}

/* End of file sub_2B2A.c  */
#endif

/*
 * File - sub_2B79.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 1

/*********************************************************
 * sub_2B79 OK++			 Used in: sub_1F4B
 *********************************************************/
uchar sub_2B79(register aaa_t *sa) {
    uchar l1;
    int l2;

    l1        = ((uint8_t *)&sa->a_u9)[sa->a_c1 - 1];
    byte_AFFA = 0;
    l2        = sub_2B2A(sa);
    if (l1 != 0) {
        if (sub_6589(l2, l1) == l1)
            return l1;
    }
    return byte_AFFA;
}

/*********************************************************
 * sub_2BD0 OK++      Used in: sub_793, sub_808, sub_3CDF
 *			       sub_3DC9
 *********************************************************/
void sub_2BD0(register aaa_t *sa) {
    int tmp;

    sa->a_c1 = 0;

    if (sub_1F4B(sa, 0x48, word_B017, 0, &tmp) <= 0)
        fatalErr("Expression too complicated");

    sub_35E6(sa);
    if (sa->a_c0 == COLON_U) {
        if (sa->a_i15 & 2) {
            prFrameHead(array_AEDB[lvlidx]->b_i11); /* emit_call_ncsv */
            sub_1EDF();
        }
        if (sa->a_l19.wi[0]->a_c0 == IDOP)
            sa->a_l19.wi[0]->a_l19.vi[0]->b_c3 |= 1; /* may ba struct aaa a_c3[0] */
    }
    sub_475C(sa);
}

/* End of file sub_2B79.c  */
#endif

/*
 * File - sub_2C5E.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 1
/*********************************************************
 * sub_2C5E OK+	   	      Used in: sub_2CE0, sub_47B2
 *
 *********************************************************/
long sub_2C5E(aaa_t *sa, long p2) {
    char loc;

    if ((loc = nodesize(sa) * 8) >= 32)
        return p2;
    if (p2 & (1L << (loc - 1)))
        p2 |= ~((1L << loc) - 1L);
    return p2;
}

/* End of file sub_2C5E.c */
#endif

/*
 * File - sub_2CE0.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 1

/*********************************************************
 *  sub_2CE0 OK++			Used in: sub_2D09
 *********************************************************/
void sub_2CE0(aaa_t *p1a, long p2) {

    printf("%ld", sub_2C5E(p1a, p2));
}

/* End of file sub_2CE0.c */
#endif

/*
 * File - sub_2D09.c	BIG size - problems compiling v3.09
 */
#if 0

#include "cgen.h"
#include "ctype.h"
#include "stdio.h"

int atoi(char *);

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*.......................................................*
 *  sub_2D09_v2 optim: Out of memory	Used in: sub_3564
 *.......................................................*/
void sub_2D09(register aaa_t *sa, char *p2, int p3) {

    struct zzz *lz1;    /*   ix+0FFh (ix+-1)  h  \	*/
                        /*   ix+0FEh (ix+-2)  l _/li1 	*/
    aaa_t *la2;    /*   ix+0FDh (ix+-3)  h  \	*/
                        /*   ix+0FCh (ix+-4)  l _/li2 	*/
    char *li3;          /* + ix+0FBh (ix+-5)  h  \	*/
                        /* + ix+0FAh (ix+-6)  l _/li3 	*/
    uchar lc4;          /* + ix+0F9h (ix+-7)  h __lc4 	*/
    char lc5;           /* + ix+0F8h (ix+-8)  l __lc5 	*/
    char lc6;           /*   ix+0F7h (ix+-9)  __lc6	*/
    char lc7;           /*   ix+0F6h (ix+-10) __lc7 	*/
    int li8;            /*   ix+0F5h (ix+-11) h  \	*/
                        /*   ix+0F4h (ix+-12) l _/li8 	*/
    unsigned long ll9;  /* + ix+0F3h (ix+-13) h  \	*/
                        /* + ix+0F2h (ix+-14) l  |ll9 	*/
                        /* + ix+0F1h (ix+-15) h  | 	*/
                        /* + ix+0F0h (ix+-16) l _/ 	*/
    char lc10;          /*   ix+0EFh (ix+-17)  __lc10 	*/
    char lc11;          /*   ix+0EEh (ix+-18)  __lc11 	*/
    char *li12;         /*   ix+0EDh (ix+-19) h  \	*/
                        /*   ix+0ECh (ix+-20) l _/li12	*/
    unsigned long ll13; /* + ix+0EBh (ix+-21) h  \ \ 	*/
                        /* + ix+0EAh (ix+-22) l  |_/	*/
                        /* + ix+0E9h (ix+-23) h  | \ 	*/
                        /* + ix+0E8h (ix+-24) l _/_/ll13*/
    char lc15;          /* ; ix+0E7h (ix+-25)  __lc15 	*/

#ifdef DEBUG
    printf("\tsub_2D09(%x, %x, %d)\n", sa, p2, p3);
#endif

    li12 = p2;
    lc11 = lc15 = 0;
m1:
    lc7 = *(p2++);
    if (lc7 == 0)
        return;

    switch (lc7) {
    case '\n':
    case '\r':
        fputchar('\n'); /* m4	*/
        lc15 = 0;
        goto m1;

    case ' ':
        if (lc15 == 0) { /* l3:	*/
            fputchar('\t');
            lc15 = 1;
        } else {
            fputchar(lc7);
        }
        goto m1;

    case ';':
        return;

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
        if (((li8 = *p2) == '-') || (li8 == '+')) {
            if (isdigit(*(++p2)) != 0) {
                lc5 = atoi(p2);
                if (li8 == '-')
                    lc5 = -lc5;
                li8 = 0;
            } else {
                lc5 = 0;
            }
            while ((isdigit(*p2) != 0) || (*p2 == '+') || (*p2 == '-'))
                p2++;
        } else {
            if (li8 == '>') {
                for (lc5 = 0; *p2 == '>'; p2++, lc5++)
                    ;
            } else {
                li8 = 0;
                lc5 = 0;
            }
        }
        lc6 = *(p2++);
        break; /* goto m10; */

    case 'G':
    case 'X':
        if (isdigit(*p2) != 0) { /* m5:	*/
            li3 = p2;
            while (isdigit(*p2) != 0)
                p2++;
        } else {
            li3 = 0; /* m8:	*/
        }
        lc6 = *(p2++); /* m9:	*/
        li8 = 'G';
        break; /* goto m10; */

    case 'L':
    case 'R':
    case 'U':
        lc6 = lc7; /* m24: */
        lc7 = '~';
        li8 = 0; /* m25: */
        lc5 = 0;
        break; /* goto m10; */

    case 'D':
        lc6 = lc7; /* m26: */
        li8 = 0;
        lc5 = 0;
        break; /* goto m10; */

    default:
        fputchar(lc7); /* m2:	*/
        goto m1;      /* m3:	*/
    }
    /*
    m10:
    */
    switch (lc6) {
    case 'L':
        /*
        m27:	if(0 < (char)p3) {
              la2  = sa;
              lc10 = (char)p3 + (-1);
            } else {
        m29:	  la2  = sa->a_l19.wi[0];
        m30:	  lc10 = la2->a_c1 + (-1);
            }
        m28:	lz1  = &array_80EF[*(lc10 + (uchar*)&la2->a_c3)];
                break;
        */
        if (0 < (char)p3) { /* m27: */
            la2  = sa;
            lc10 = (char)p3 + (-1);
        m28:
            lz1 = &array_80EF[*(lc10 + (uchar *)&la2->a_c3)];
            break; /* goto m11; */
        }
        la2 = sa->a_l19.wi[0]; /* m29: */
    m30:
        lc10 = la2->a_c1 + (-1);
        goto m28;

    case 'N':
        la2  = sa; /* m32: */
        lc10 = (char)p3;
        break; /* goto m11; */

    case 'R':
        la2 = sa->a_l19.wi[1]; /* m31: */
        goto m30;
    }
    /*
    m11:
    */
    switch (lc7) {
    case 'A':
        sub_153A(la2); /* m51: */
        goto m1;

    case 'B':
        ll9 = sub_387A(la2); /* m45: */
    m46:
        if (li8 == '-') {
            if (lc11 == 0) {
                ll13      = ll9 + (long)word_AFF8;
                word_AFF8 = 0;
                lc11      = 1;
                goto m54;
            }
        }
        printf("%lu", ll9); /* m47: */
        goto m1;

    case 'C':
        if (la2->a_c0 == BFIELD) { /* m63:	*/
            printf("%d", la2->a_l19.wi[1]->a_c3[3]);
        } else {
            ll9 = la2->a_l19.l; /* m64: */
            if (sub_46F7(ll9) == 0)
                ll9 = (-1) - ll9;
            /*        word_AFF8 += ((sub_46F7(ll9) - 1)>>3); */ /* m65: */
            word_AFF8 += ((-1) + sub_46F7(ll9)) / 8;
        }
        goto m1;

    case 'D':
        if (word_AFF8 != 0) { /* m33: */
            printf("%d", word_AFF8);
            word_AFF8 = 0;
        }
        goto m1;

    case 'F': /* m43: */
        printf("%d", la2->a_l19.ii[1]);
        goto m39;

    case 'G':
    case 'X':
        lc4 = (lc7 == 'G') ? /* m69: */
                  *(lc10 + (uchar *)&la2->a_reg)
                           : *(lc10 + (uchar *)&la2->a_i6);
        if (li3 != 0) {
            while (isdigit(*li3) != 0) {                              /* m73: */
                lc4 = (char)array_AB24[lc4 * 2 + ((-48) + *(li3++))]; /* m72: */
            }
        }
        if (*p2 != '+') { /* m74: */
            lc4 += word_AFF8;
            word_AFF8 = 0;
        }
        printf("%s", regNames[lc4]); /* m75: */
        goto m1;

    case 'O':
        printf("%s", array_805F[la2->a_c0]); /* m49: */
        goto m1;

    case 'S':
        /**/
        if (la2->a_c0 == USEREG)
            printf("%s", regNames[la2->a_l19.ii[0]]);
        else if (la2->a_c0 == CONST)
            sub_2CE0(la2, la2->a_l19.l);
        else if (la2->a_c0 == FCONST)
            printf("%s", la2->a_l19.ci[0]);
        else
            printf("%s", la2->a_l19.vi[0]->b_name);
    /**/
    /*
            switch(la2->a_c0) {
              case 'E':
                printf("%s", regNames[la2->a_l19.ii[0]]);
                break;
              case 'C':
                sub_2CE0(la2, la2->a_l19.l);
                break;
              case 'D':
                printf("%s", la2->a_l19.ci[0]);
                break;
              default:
                printf("%s", la2->a_l19.vi[0]->b_name);
            }
    */
    m39:
        if (li8 == 0) {
            lc5 += word_AFF8;
            word_AFF8 = 0;
            if (word_AFF8 < lc5)
                printf("+%d", lc5);
            else if (lc5 < 0)
                printf("%d", lc5);
        }
        goto m1;

    case 'T':
        if (la2->a_c0 == BFIELD) { /* m66: */
            printf("%d", la2->a_l19.wi[1]->a_c3[2]);
        } else {
            ll9 = la2->a_l19.l; /* m67: */
            if (sub_46F7(ll9) == 0)
                ll9 = -1 - ll9;
            printf("%d", (-1) + sub_46F7(ll9));
        }
        goto m1;

    case 'V':
        if ((li8 == '-') || (li8 == '+')) { /* m52: */
            if (lc11 == 0) {                /* m53: */
                ll13      = la2->a_l19.l + word_AFF8;
                word_AFF8 = 0;
                lc11      = 1;
            }
        m54:
            ll13 += (li8 == '-') ? (long)(-1) : (long)1;
            if (sub_14F3(la2) == REG_L) {
                if (nodesize(la2) < 4) {
                    ll13 &= ((int)(1 << (nodesize(la2) * 8)) - 1);
                }
            }
            if (ll13 != 0) { /* m57: */
                for (; (li12 < p2 && *(p2 - 1) != '\n'); p2--)
                    ;          /* m59: */
                fputchar('\n'); /* m60: */
            } else {
                lc11 = 0; /* m61: */
            }
        } else {
            lc5 += word_AFF8; /* m62: */
            word_AFF8 = 0;
            sub_2CE0(la2, (la2->a_l19.l >> (lc5 << 3)));
        }
        goto m1;

    case 'Z':
        ll9 = nodesize(la2); /* m44: */
        goto m46;

    case '~':
        if (lc6 == 'U') { /* m76: */
            lc5 += word_AFFB;
            if (((unsigned)dopetab[sa->a_c0] & 0x200) != 0) {
                if ((char)p3 != 0)
                    lc5--;
            }
            printf("%d", lc5); /* m77: */
        } else {
            word_AFF8 += lc5; /* m78: */
            sub_2D09(la2, lz1->p_8, lc10);
        }
        /* goto m1; */
    }
    goto m1;
}

/* End of file sub_2D09.c */
#endif

/*
 * File - sub_3564.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 1

/*********************************************************
 * sub_3564 OK++			Used in: sub_35E6
 *********************************************************/
void sub_3564(register aaa_t *sa) {
    char l1;
    struct zzz *l2z;

    word_AFF8 = 0;
    for (l1 = 0; l1 != sa->a_c1; l1++) {
        if ((l2z = &array_80EF[sa->a_c3[l1]])->p_6) {
            sub_2D09(sa, l2z->p_6, l1);
            fputchar('\n');
        }
    }
}

/*********************************************************
 * sub_35E6 OK+				Used in: sub_2BD0
 *
 *********************************************************/
void sub_35E6(register aaa_t *sa) {
    int l1;

    if (dopetab[sa->a_c0] & 0x200)
        word_AFFB++;
    l1 = dopetab[sa->a_c0] & 0xC;
    if (8 == l1) {
        if (sa->a_c2 & 1) {
            sub_35E6(sa->a_l19.wi[0]);
            sub_35E6(sa->a_l19.wi[1]);
        } else {
            sub_35E6(sa->a_l19.wi[1]);
            if (sa->a_c2 & 2)
                prPush(sa->a_l19.wi[1]->a_reg[sa->a_l19.wi[1]->a_c1 - 1]);
            sub_35E6(sa->a_l19.wi[0]);
        }
    }
    if (l1 == 4)
        sub_35E6(sa->a_l19.wi[0]);
    if (sa->a_c2 & 2)
        prPop(sa->a_l19.wi[1]->a_reg[sa->a_l19.wi[1]->a_c1 - 1]);
    sub_3564(sa);
    if (dopetab[sa->a_c0] & 0x200)
        word_AFFB--;
}

/*********************************************************
 * sub_36E0 OK++   Used in: sub_E43,  sub_39CA, sub_3CDF,
 *			    sub_3DC9, sub_3EAA, sub_43EF,
 *			    sub_475C, sub_4C8B, sub_4FA8,
 *			    sub_508A, sub_53EE, sub_54B6,
 *			    sub_5DF6, sub_5F52
 *********************************************************/
void freeAaa(register aaa_t *sa) {

    byte_B013 = 1;
    if (sa->a_c0 == FCONST)
        free(sa->a_l19.wi[0]);
    sa->a_s17   = aaaFreeList;
    aaaFreeList = sa;
}

/*********************************************************
 * sub_3712 OK++    Used in: sub_E43,  sub_377A, sub_415E,
 *			     sub_4192, sub_43EF, sub_4DA3,
 *			     sub_54B6
 *********************************************************/
aaa_t *allocAaa(void) {
    register aaa_t *sa;

    byte_B013 = 1;
    if (aaaFreeList) {
        sa          = aaaFreeList;
        aaaFreeList = sa->a_s17;
        blkclr((char *)sa, sizeof(aaa_t));
    } else { /* create aaa_t */
        sa = allocmem(sizeof(aaa_t));
    }

    return sa;
}

/*********************************************************
 *  sub_374C OK++			Used in: allocmem
 *********************************************************/
bool releaseAaaFreelist(void) {
    register aaa_t *sa;

    if (aaaFreeList == 0)
        return false;
    while ((sa = aaaFreeList)) {
        aaaFreeList = sa->a_s17;
        free(sa);
    }
    return true;
}

/*********************************************************
 *  sub_377A OK++			Used in: sub_3CDF
 *********************************************************/
aaa_t *sub_377A(aaa_t *p1a) {
    register aaa_t *sa;

    sa  = allocAaa();
    *sa = *p1a;

    if (dopetab[sa->a_c0] & 0xC)
        sa->a_l19.wi[0] = sub_377A(sa->a_l19.wi[0]);
    if ((dopetab[sa->a_c0] & 0xC) == 8)
        sa->a_l19.wi[1] = sub_377A(sa->a_l19.wi[1]);
    return sa;
}

/* End of file sub_3564.c  */
#endif

/*
 * File - sub_37ED.c Created 09.03.2019 Last Modified 17.06.2020
 */
#if 1


/*********************************************************
 * sub_37ED v1 OK+	      Used in: sub_387A, sub_43EF
 *
 * Elegantly designed function leads to the generation of
 * less optimal code, unlike the second version
 *********************************************************/
void sub_37ED(register aaa_t * sa) {
    bbb_t * l1b;

    l1b = sa->a_s17;
    if(sa->a_i15 != 0)
      sa->a_i15 >>= 2;
    else {
      while(l1b->b_refl == 0)
          l1b = l1b->b_type;
      sa->a_s17 = l1b->b_type;
      sa->a_i15 = l1b->b_refl >> 2;
    }
}

/* End of file sub_37EDD.c  */
#endif

/*
 * File - sub_385B.c Created 09.03.2019 Last Modified 17.06.2020
 */
#if 1

/*********************************************************
 * sub_385B OK++    Used in: sub_387A, sub_43EF, sub_4DA3,
 *			     sub_4E8D
 *********************************************************/
void sub_385B(register aaa_t *sa) {
    sa->a_i15 = (sa->a_i15 * 4) | 1;
}

/*********************************************************
 * sub_387A OK++			Used in: sub_2D09
 *********************************************************/
uint16_t sub_387A(register aaa_t *sa) {
    uint8_t loc;

    if (sa->a_i15 == 0 && sa->a_s17->b_type == 0 && sa->a_s17->b_refl == 0)
        return 1;

    sub_37ED(sa);
    loc = nodesize(sa);
    sub_385B(sa);
    return loc;
}

/*********************************************************
 * sub_38CA OK++	      Used in: sub_393C, sub_3952
 *********************************************************/
bool sub_38CA(aaa_t *p1a, int p2) {
    register bbb_t *sb;

    if (p1a->a_i15 & p2)
        return true;
    if (p1a->a_i15 != 0)
        return false;
    sb = p1a->a_s17;
    do {
        if (sb->b_refl & p2)
            return true;
        if (sb->b_refl != 0)
            return false;
    } while ((sb = sb->b_type) != 0);
    return false;
}

/*********************************************************
 * sub_393C OK++			Used in: Not used
 *********************************************************/
bool sub_393C(aaa_t *sa) {
    return sub_38CA(sa, 1);
}

/*********************************************************
 * sub_3952 OK++			Used in: Not used
 *********************************************************/
bool sub_3952(aaa_t *sa) {
    return sub_38CA(sa, 2);
}

/*********************************************************
 * sub_3968 OK++			Used in: sub_47B2
 *********************************************************/
bool sub_3968(register aaa_t *sa) {
    return sa->a_s17->b_class == SDECL && (sa->a_i15 & 1) == 0;
}
#endif
#if 1

/*********************************************************
 * nodesize OK++    Used in: sub_808,  sub_E43,  sub_2C5E,
 *			     sub_2D09, sub_387A, sub_3A79,
 *			     sub_43EF, sub_47B2, sub_508A,
 *			     sub_54B6, sub_60A8, sub_6246,
 *			     sub_62BE
 *********************************************************/
unsigned nodesize(register aaa_t *sa) {

    if (sa->a_i15 & 2)
        prError("can\'t take sizeof func");

    if (sa->a_i15 & 1)
        return 2;
    return sa->a_s17->b_size;
}

/*********************************************************
 * sub_39CA OK++			Used in: sub_3EAA
 *********************************************************/
aaa_t *sub_39CA(register aaa_t *sa) {
    char buf[50];

    freeAaa(sa->a_l19.wi[1]);
    if (sub_14F3(sa) == 3) {
        sprintf(buf, "%ld.", sa->a_l19.wi[0]->a_l19.l);
        freeAaa(sa->a_l19.wi[0]);
        sa->a_l19.ci[0] = allocmem(strlen(buf) + 1); /* create string */
        strcpy(sa->a_l19.ci[0], buf);
        sa->a_l19.ii[1] = newSwTable(); /* swTableCnt++ */
        sa->a_c0        = FCONST;
        return sa;
    }
    sub_3A79(sa, sa->a_l19.wi[0]);
    freeAaa(sa);
    return sa->a_l19.wi[0];
}

/* End of file sub_385B.c  */
#endif

/*
 * File - sub_3A79.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 0

/*********************************************************
 * sub_3A79 OK+	              Used in: sub_3EAA, sub_39CA
 *
 * Compiler generates code that performs expected action,
 * but differs from original image
 *********************************************************/
void sub_3A79(register aaa_t *sa, aaa_t *p2a) {
    int l1;

#ifdef DEBUG
    printf("\tsub_3A79(%x, %x)\n", sa, p2a);
#endif

    l1 = nodesize(sa);
    if (l1 != 0) {
        if (l1 < 4) {
            l1 <<= 3;
            p2a->a_l19.l &= ((long)1 << l1) + (-1);
            if (sub_14F3(sa) == REG_A) {
                if ((p2a->a_l19.l & (1 << (l1 - 1))) != 0) {
                    p2a->a_l19.l |= ((-1) - (((long)1 << l1) - 1)); /* no code matching */
                }
            }
        }
    }
    p2a->a_s17 = sa->a_s17;
    p2a->a_i15 = sa->a_i15;
}

/* End of file sub_3A79.c  */
#endif

/*
 * File - sub_3B65.c Created 09.03.2019 Last Modified 29.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_3B65 OK++			Used in: sub_3EAA
 *********************************************************/
void sub_3B65(register unsigned long *ptr, long p2, int operator) {

#ifdef DEBUG
    printf("\tsub_3B65(%x, %lx, %d)\n", ptr, p2, operator);
#endif

    switch (operator) {
    case MOD:
        *ptr /= p2;
        break;
    case DIV:
        *ptr %= p2;
        break;
    case RSHIFT:
        *ptr >>= p2;
        break;
    }
    return;
}

/* End of file sub_3B65.c  */
#endif

/*
 * File - sub_3BC6.c Created 09.03.2019 Last Modified 29.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_3BC6 v1 OK+			Used in: sub_3EAA
 *
 * Compiler generates identical code from restored source
 * program in C, however, location of branches associated
 * with case constants is different from original.
 * This does not affect the function.
 *********************************************************/
void sub_3BC6(register long *ptr, long p2, int operator) {

#ifdef DEBUG
    printf("\tsub_3BC6(%x, %lx, %d)\n", ptr, p2, operator);
#endif

    switch (operator) {
    case MOD:
        *ptr %= p2;
        break;
    case BAND:
        *ptr &= p2;
        break;
    case MUL:
        *ptr *= p2;
        break;
    case ADD:
        *ptr += p2;
        break;
    case SUB:
        *ptr -= p2;
        break;
    case DIV:
        *ptr /= p2;
        break;
    case LSHIFT:
        *ptr <<= p2;
        break;
    case RSHIFT:
        *ptr >>= p2;
        break;
    case BXOR:
        *ptr ^= p2;
        break;
    case BOR:
        *ptr |= p2;
        break;
    }
    return;
}

/* End of file sub_3BC6.c  */
#endif

/*
 * File - sub_3CDF.c Created 09.03.2019 Last Modified 31.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_3CDF OK++			Used in: sub_3DC9
 *********************************************************/
aaa_t *sub_3CDF(register aaa_t *sa) {
    int loc;

#ifdef DEBUG
    printf("\tsub_3CDF(%x)\n", sa);
#endif

    if (sa->a_c0 == SCOLON) {
        sub_2BD0(sa->a_l19.wi[0]);
        freeAaa(sa);
        sa = sa->a_l19.wi[1];
    }
    if (byte_B014 != 0xA) {
        if ((dopetab[sa->a_c0] & 0x4000) != 0)
            return sa;
        switch (sa->a_c0) {
        case INCR:
        case DECR:
            if (sub_4C6D(sa) != 0) {
                array_AFFD[byte_B014++] = sa;
                sa->a_c0                = (sa->a_c0 == INCR) ? ASADD : ASSUB;
                sa                      = sub_377A(sa->a_l19.wi[0]);
            }
        }
        loc = dopetab[sa->a_c0] /*& 0xC */;
        if ((loc & 0xC) != 0)
            sa->a_l19.wi[0] = sub_3CDF(sa->a_l19.wi[0]);
        if ((loc & 0xC) == 8)
            sa->a_l19.wi[1] = sub_3CDF(sa->a_l19.wi[1]);
    }
    return sa;
}

/*********************************************************
 * sub_3DC9 OK++		Used in: sub_6D1, sub_D66
 *********************************************************/
void sub_3DC9(register aaa_t *sa) {
    unsigned loc;

#ifdef DEBUG
    printf("\tsub_3DC9(%x)\n", sa);
#endif

    sa = sub_600E(sa);
    if (sa->a_c0 == DOLLAR) {
        if (sa->a_l19.wi[0]->a_c0 == CONST) {
            warning("constant conditional branch");
            if (sa->a_l19.wi[0]->a_l19.l != 0) {
                sa->a_c0 = DOLLAR_U;
                freeAaa(sa->a_l19.wi[0]);
                sa->a_l19.wi[0] = sa->a_l19.wi[1];
            } else {
                sub_475C(sa);
                return;
            }
        }
    }
    byte_B014 = 0;
    if (sa->a_c0 == INCR) {
        sa->a_c0 = ASADD;
    } else {
        if (sa->a_c0 == DECR) {
            sa->a_c0 = ASSUB;
        }
    }
    sa = sub_3CDF(sa);
    if (byte_B014 != 0)
        sa = sub_600E(sa);
    sub_2BD0(sa);
    loc = 0;
    while (loc < byte_B014) {
        sub_2BD0(array_AFFD[loc]);
        loc++;
    }
}

/* End of file sub_3CDF.c */
#endif

/*
 * File - sub_3EAA.c Created 09.03.2019 Last Modified 29.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"
#include <stdlib.h>

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_3EAA OK+				Used in: sub_600E
 *********************************************************/
#if 1
/*vvvvvvvvvvvvvvvvvvvvvvvvvvv*/

aaa_t *sub_3EAA(register aaa_t *sa) {
    aaa_t *l1a;
    int l2;

#ifdef DEBUG
    aaa_t *tmp;
    printf("\tsub_3EAA(%x)\n", sa);
#endif

    if ((l2 = dopetab[sa->a_c0] & 0xC) != 0)
        sa->a_l19.wi[0] = sub_3EAA(sa->a_l19.wi[0]);
    if (l2 == 8)
        sa->a_l19.wi[1] = sub_3EAA(sa->a_l19.wi[1]);
    if (sa->a_c0 == CONV) {
        if ((sa->a_l19.wi[0])->a_c0 == FCONST) {
            if (sub_14F3(sa) == REG_F) {
                l1a        = sa->a_l19.wi[0];
                l1a->a_s17 = sa->a_s17;
                freeAaa(sa->a_l19.wi[1]);
                freeAaa(sa);
#ifdef DEBUG
                tmp = l1a;
                goto d2;
#else
                return l1a;
#endif
            }
        }
    }
    if ((l2 == 0) || ((sa->a_l19.wi[0])->a_c0 != CONST)) { /* m3: */
#ifdef DEBUG
        goto d1;
#else
        return sa;
#endif
    }
    if (sa->a_c0 == CONV) { /* m6: */

#ifdef DEBUG
        tmp = sub_39CA(sa);
        goto d2;
#else
        return sub_39CA(sa);
#endif
    }
    if ((l2 != 8) || ((sa->a_l19.wi[1])->a_c0 != CONST))
        goto m8; /* m7: */

#ifdef DEBUG
d1:
    tmp = sa;
d2:
    printf("\tsub_3EAA\t\tReturn %x\n", tmp);
    return tmp;
#else
    return sa;
#endif
m8:
    if (sub_14F3(sa) == REG_L) { /* m8:  */
        switch (sa->a_c0) {
        case MOD:
        case DIV:
        case RSHIFT:
            goto m14;
        case LT:
        case LEQ:
        case GT:
        case GEQ:
            goto m12;
        }
    }
    switch (sa->a_c0) { /* m10: */
    case BNOT:
        goto m23;
    case NOT:
        goto m21;
    case MINUS_U:
        goto m19;
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
        goto m18;
    case NEQL:
    case LT:
    case LEQ:
    case EQL:
    case GT:
    case GEQ:
        goto m17;
    default:
        {
#ifdef DEBUG
            goto d1;
#else
            return sa;
#endif
        }
    }
    /*    return sa; */

m12:
    word_B015 = "constant relational expression";
#ifdef DEBUG
    goto d1;
#else
    return sa;
#endif

m14:
    sub_3B65(&sa->a_l19.wi[0]->a_l19.ul, sa->a_l19.wi[1]->a_l19.l, sa->a_c0);
m15:
    if (l2 == 8) {
        sub_475C(sa->a_l19.wi[1]);
    }
    sub_3A79(sa, sa->a_l19.wi[0]); /* m16: */
    freeAaa(sa);
#ifdef DEBUG
    tmp = sa->a_l19.wi[0];
    goto d2;
#else
    return sa->a_l19.wi[0];
#endif

    /* Two identical code fragments could be intended for different messages */

m17:
    word_B015 = "constant relational expression";
#ifdef DEBUG
    goto d1;
#else
    return sa;
#endif

m18:
    sub_3BC6(&sa->a_l19.wi[0]->a_l19.l, sa->a_l19.wi[1]->a_l19.l, sa->a_c0);
    goto m15;

m19:
    sa->a_l19.wi[0]->a_l19.l = (long)0 - sa->a_l19.wi[0]->a_l19.l;
    goto m15;

m21:
    sa->a_l19.wi[0]->a_l19.l =
        sa->a_l19.wi[0]->a_l19.l == 0 ? (long)1 : (long)0; /* minor differences in the generated code */
    goto m15;

m23:
    sa->a_l19.wi[0]->a_l19.l = (long)(-1) - sa->a_l19.wi[0]->a_l19.l; /* minor differences in the generated code */
    goto m15;
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#else
/*vvvvvvvvvvvvvvvvvvvvvvvvvvv*/
aaa_t *sub_3EAA(register aaa_t *sa) {
    aaa_t *l1a;
    int l2;

#ifdef DEBUG
    printf("\tsub_3EAA(%x)\n", sa);
#endif

    if ((l2 = dopetab[sa->a_c0] & 0xC) != 0)
        sa->a_l19.wi[0] = sub_3EAA(sa->a_l19.wi[0]);
    if (l2 == 8)
        sa->a_l19.wi[1] = sub_3EAA(sa->a_l19.wi[1]);
    if (sa->a_c0 == CONV) {
        if ((sa->a_l19.wi[0])->a_c0 == FCONST) {
            if (sub_14F3(sa) == REG_F) {
                l1a = sa->a_l19.wi[0];
                l1a->a_s17 = sa->a_s17;
                freeAaa(sa->a_l19.wi[1]);
                freeAaa(sa);
                return l1a;
            }
        }
    }
m3:
    if ((l2 == 0) || ((sa->a_l19.wi[0])->a_c0 != CONST))
        return sa;
m6:
    if (sa->a_c0 == CONV)
        return sub_39CA(sa);
m7:
    if ((l2 != 8) || ((sa->a_l19.wi[1])->a_c0 != CONST))
        goto m8;
    return sa;

m8:
    if (sub_14F3(sa) == REG_L) { /* m8:  */
        switch (sa->a_c0) {
        case MOD:
        case DIV:
        case RSHIFT:
            goto m14;
        case LT:
        case LEQ:
        case GT:
        case GEQ:
            goto m12;
        }
    }
m10:
    switch (sa->a_c0) { /* m10: */
    case BNOT:
        goto m23;
    case NOT:
        goto m21;
    case MINUS_U:
        goto m19;
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
        goto m18;
    case NEQL:
    case LT:
    case LEQ:
    case EQL:
    case GT:
    case GEQ:
        goto m17;
    default:
        return sa;
    }
    /*    return sa; */

m12:
    word_B015 = "constant relational expression";
    return sa;

m14:
    sub_3B65(&sa->a_l19.wi[0]->a_l19.ul, sa->a_l19.wi[1]->a_l19.l, sa->a_c0);
m15:
    if (l2 == 8) {
        sub_475C(sa->a_l19.wi[1]);
    }
    sub_3A79(sa, sa->a_l19.wi[0]); /* m16: */
    freeAaa(sa);
    return sa->a_l19.wi[0];

    /* Two identical code fragments could be intended for different messages */

m17:
    word_B015 = "constant relational expression";
    return sa;

m18:
    sub_3BC6(&sa->a_l19.wi[0]->a_l19.l, sa->a_l19.wi[1]->a_l19.l, sa->a_c0);
    goto m15;

m19:
    sa->a_l19.wi[0]->a_l19.l = (long)0 - sa->a_l19.wi[0]->a_l19.l;
    goto m15;

m21:
    sa->a_l19.wi[0]->a_l19.l =
        sa->a_l19.wi[0]->a_l19.l == 0 ? (long)1 : (long)0; /* minor differences in the generated code */
    goto m15;

m23:
    sa->a_l19.wi[0]->a_l19.l = (long)(-1) - sa->a_l19.wi[0]->a_l19.l; /* minor differences in the generated code */
    goto m15;
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#endif
/* End of file sub_3EAA.c  */
#endif

/*
 * File - sub_415E.c  Created 09.03.2019 Last Modified 26.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_415E OK++   Used in: sub_808,  sub_E43,  sub_4192,
 *			    sub_4DA3, sub_54B6
 *********************************************************/
aaa_t *sub_415E(long number) {
    register aaa_t *sa;

#ifdef DEBUG
    printf("\tsub_415E(%ld)\n", number);
#endif
    sa          = allocAaa();
    sa->a_c0    = CONST;
    sa->a_s17   = word_AE11; /* "l" - long	  */
    sa->a_l19.l = number;
#ifdef DEBUG
    printf("\tsub_415E\t\tReturn %x\n", sa);
#endif
    return sa;
}

/* End of file sub_415E.c  */
#endif

/*
 * File - ssub_4192.c Created 09.03.2019 Last Modified 17.06.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*********************************************************
 * sub_4192 OK+     Used in: sub_6D1,  sub_793,  sub_808,
 *			     sub_B19,  sub_E43,  sub_17E0,
 *			     sub_19C1, sub_1B0C
 *
 * Generated code is completely identical to binary image
 * executable file, with exception location some branches
 * switch statements
 *********************************************************/
aaa_t *sub_4192(void) {
    aaa_t *l1a;
    char *l2;
    int l3;
    int l4;
    register aaa_t *sa;

#ifdef DEBUG
    printf("\tsub_4192()\n");
#endif

m1:
    l2 = getToken();
    if (isdigit(*l2) != 0)
        goto m2;
    if ((*l2 != '-') || (isdigit(*(l2 + 1)) == 0))
        goto m7;
m2:
    if (*l2 == '-') {
        l4 = 1;
        l2++;
    } else {
        l4 = 0; /* m4:  */
    }

#ifdef DEBUG
    printf("\tsub_4192\t\tatol(\"%s\") = %ld l4 = %d\n", l2, atol(l2), l4);
#endif

    sa = sub_415E(atol(l2));
    if (l4 != 0)
        sa->a_l19.l = 0 - sa->a_l19.l;
m5:
#ifdef DEBUG
    printf("\tsub_4192\t\tReturn %x\n", sa);
#endif
    return sa;

m7:
    if ((*l2 == '_') || (isalpha(*l2) != 0)) { /* m7:  */
        (sa = allocAaa())->a_c0 = IDOP;        /* m8:  */
        sa->a_l19.vi[0]         = sub_265(l2);
        sa->a_s17               = sa->a_l19.vi[0]->b_type;
        sa->a_i15               = sa->a_l19.vi[0]->b_refl;
        if (sa->a_l19.vi[0]->b_c13 != 3)
            goto m5;
        if (((sa->a_l19.vi[0]->b_c3) & 2) != 0)
            goto m5;
        prGlobalDef(sa->a_l19.vi[0]); /* Emit "global name" */
        goto m5;
    }
    if (*l2 == '`') { /* m9:  */
        sa        = allocAaa();
        sa->a_s17 = sub_627(l2, &sa->a_i15);
        sa->a_c0  = TYPEOP;
        goto m5;
    }
    if (*l2 == '.') { /* m10: */
        if (*(l2 + 1) != 0) {
            if (*(l2 + 1) != '.') {
                sa              = allocAaa();
                sa->a_s17       = word_AED7;                    /* "d" - double */
                sa->a_l19.ci[0] = (char *)allocmem(strlen(l2)); /* create string */
                strcpy(sa->a_l19.ci[0], l2 + 1);
                sa->a_l19.ii[1] = newSwTable(); /* swTableCnt++ */
                sa->a_c0        = FCONST;
                goto m5;
            }
        }
    }
    l4 = sub_1B2(l2); /* Token search */ /* m12: */
    l3 = dopetab[l4] & 0xC;
    switch (l3) {
    case 0xC: /* parsing operations	    */
        switch (l4) {
        case '4':
            sub_1B0C();
            goto m1;
        case '7':
        case '8':
            sub_19C1(l4);
            goto m1;
        case '9':
            sub_17E0();
            goto m1;
        }
        fatalErr("Expression error");
    case 0: /*  			    */
        return sub_43EF(l4, 0, 0);
    case 4: /*  			    */
        return sub_43EF(l4, sub_4192(), 0);
    case 8: /* computational operations */
        l1a = sub_4192();
        return sub_43EF(l4, l1a, sub_4192());
    }
    goto m1;
}

/* End of file sub_4192.c  */
#endif

/*
 * File - sub_43EF.c Created 09.03.2019 Last Modified 17.06.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_43EF OK+      Used in: sub_793,  sub_808,  sub_E43,
 *                            sub_4192, sub_4C8B, sub_4DA3,
 *                            sub_4E8D, sub_508A, sub_54B6,
 *                            sub_5DF6
 *
 * Generated code is completely identical, except for
 * location of code of branches of "switch" operator.
 *********************************************************/
aaa_t *sub_43EF(int p1, aaa_t *p2a, aaa_t *p3a) {
    bbb_t *l1b;
    long l2;
    register aaa_t *sa;

#ifdef DEBUG
    printf("\tsub_43EF(%d, %x, %x)\n", p1, p2a, p3a);
#endif

    sa              = allocAaa();
    sa->a_c0        = (char)p1;
    sa->a_l19.wi[0] = p2a;
    sa->a_l19.wi[1] = p3a;
    switch (dopetab[sa->a_c0] & 0x30) {
    case 0x10:
        sa->a_s17 = word_AE11; /* long	  */
        break;

    case 0x20:
        sa->a_s17 = word_AF1B; /* b	  */
        break;

    case 0x30:
        sa->a_s17 = word_AFE9; /* variable */
        break;

    default:
        sa->a_s17 = p2a->a_s17;
        sa->a_i15 = p2a->a_i15;
    }
    switch (sa->a_c0) {
    case HASHSIGN:
        if (sa->a_l19.wi[0]->a_c0 == IDOP)
            l2 = (unsigned)sa->a_l19.wi[0]->a_l19.wi[0]->a_i6;
        else
            l2 = (unsigned)nodesize(sa->a_l19.wi[0]); /* ?? */
        if (l2 == 0)
            warning("Sizeof yields 0");
        sub_475C(sa->a_l19.wi[0]);
        sa->a_c0    = CONST;
        sa->a_s17   = word_AE11; /* long	  */
        sa->a_i15   = 0;
        sa->a_l19.l = l2;
        break;

    case GADDR:
        if (sa->a_i15 == 0) {
            if (1 < (unsigned)sa->a_s17->b_nelem) {
                sa->a_i15 = sa->a_s17->b_refl;
                sa->a_s17 = sa->a_s17->b_type;
            }
        }
        sub_385B(sa);
        break;

    case LPAREN:
    case MUL_U:
        sub_37ED(sa);
        break;

    case DOT:
        if (p2a->a_c0 == TYPEOP) { /* m9: */
            l1b = p2a->a_s17;
            freeAaa(sa);
            freeAaa(p2a);
            sa           = p3a;
            sa->a_s17    = l1b;
            p3a->a_l19.l = *((int)sa->a_l19.wi[0] + l1b->b_memb + 1);
            break;
        }
        l1b          = *(p3a->a_l19.ii[0] + sa->a_s17->b_memb + 1); /* assigning to "aaa_t *" from "int" */
        sa->a_s17    = l1b->b_type;
        sa->a_i15    = l1b->b_refl;
        p3a->a_l19.l = l1b->b_i11;
        p3a->a_s17   = word_AF1D; /* x      */
        if ((l1b->b_c3 & 0x10) == 0)
            break;
        p2a              = allocAaa();
        *p2a             = *sa;
        p2a->a_l19.wi[0] = sa;
        sa               = p2a;
        sa->a_c0         = BFIELD;
        sa->a_l19.vi[1]  = l1b;
        break;

    case COLON_S:
        sa->a_s17 = word_AED9; /* char   */
        sa->a_i15 = 1;
        break;

    case CONV:
    case SCOLON:
    case QUEST:
        sa->a_s17 = sa->a_l19.wi[1]->a_s17;
        sa->a_i15 = sa->a_l19.wi[1]->a_i15;
        break;
    }
#ifdef DEBUG
    printf("\tsub_43EF\t\tReturn %x\n", sa);
#endif
    return sa;
}

/* End of file sub_43EF.c  */
#endif

/*
 * File - sub_46F7.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_46F7 OK++     Used in: sub_2D09, sub_47B2, sub_4FCE
 *			      sub_54B6
 *********************************************************/
uchar sub_46F7(long p1) {
    uchar l1;

#ifdef DEBUG
    printf("\tsub_46F7(%lu)\n", p1);
#endif

    if (((p1 & ((-1) + p1)) != 0) || (p1 < 1))
        return 0;
    l1 = 0;
    while ((p1 >>= 1) != 0)
        l1++;
    return (l1 + 1);
}

/* End of file sub_46F7.c  */
#endif

/*
 * File - sub_475C.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_475C OK++    Used in: sub_808,  sub_E43,  sub_17E0,
 *			     sub_19C1, sub_1B0C, sub_2BD0,
 *			     sub_3DC9, sub_3EAA, sub_43EF,
 *			     sub_475C, sub_4DA3, sub_4FA8,
 *			     sub_508A, sub_54B6
 *********************************************************/
void sub_475C(register aaa_t *sa) {
    int loc;

#ifdef DEBUG
    printf("\tsub_475C(%x)\n", sa);
#endif

    if ((loc = dopetab[sa->a_c0] & 0xC) != 0) {
        sub_475C(sa->a_l19.wi[0]);
        if (loc == 8) {
            sub_475C(sa->a_l19.wi[1]);
        }
    }
    freeAaa(sa);
#ifdef DEBUG
    printf("\tsub_475C\t\tReturn\n");
#endif
}

/* End of file sub_475C.c  */
#endif

/*
 * File - sub_47B2.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_47B2 OK+				Used in: sub_1F4B
 *********************************************************/
char sub_47B2(register aaa_t *sa, int p2) {
    long l1;

#ifdef DEBUG
    printf("\tsub_47B2(%x, %d)\n", sa, p2);
#endif

    switch (p2 - 1) { /* m1:  */
    case MUL_U - 1:
        sa = sa->a_l19.wi[1]; /* m2:  loc_47DE */
    case T_SCOLON - 1:
        if (sa->a_l19.l >= 1) { /* m3:  loc_47E7 */
            if (sa->a_l19.l < 3)
                return 1;
        }
        return 0;
    case RPAREN - 1:
        sa = sa->a_l19.wi[0]; /* m5:  loc_4821 */
    case MOD - 1:
        if (nodesize(sa) == 2) { /* m6:  loc_482A */
        m7:
            if ((char)sub_3968(sa) == 0)
                return 1;
        }
        return 0;
    case BAND - 1:
        if (sub_14F3(sa) != REG_F)
            goto m12; /* m9:  loc_4846 */
        return 0;
    case MUL - 1:
        sa = sa->a_l19.wi[0]; /* m11: loc_4856 */
    case DOLLAR_U - 1:
    m12:
        if (nodesize(sa) == 4)
            return 0; /* m12: loc_485F */
        goto m7;
    case SCOLON - 1:
        sa = sa->a_l19.wi[0]; /* m13: loc_486A */
    case DOLLAR - 1:
        return sub_3968(sa); /* m14: loc_4873 */
    case ADD - 1:
        if (sa->a_l19.bc[0] == 8)
            return 1; /* m16: loc_487C */
        if (sa->a_l19.bc[0] == 9)
            return 1;
        return 0;
    case INCR - 1:
        l1 = sub_2C5E(sa, sa->a_l19.l); /* m17: loc_4887 */
        if (l1 < (long)0xffffff80)
            return 0;
        if (l1 < 0x7d)
            return 1;
        return 0;
    case COLON_U - 1:
        if (sa->a_l19.l < 1)
            return 0; /* m19: loc_48E0 */
        if (sa->a_l19.l < 5)
            return 1;
        return 0;
    case COLON_S - 1:
        l1 = sa->a_l19.l; /* m20: loc_4910 */
        if (sub_14F3(sa) != REG_L)
            goto m21;
        if ((l1 & 1 << (nodesize(sa) << 3)) == 0)
            goto m21;
        l1 |= ((-1) - (unsigned)((int)(1 << (nodesize(sa) << 3)) - 1));
    m21:
        if (((uchar)l1 & 0x80) == 0)
            return 0;
        if (l1 >= (long)0xFFFFFFFC)
            return 1;
        return 0;
    case LPAREN - 1:
        sa = sa->a_l19.wi[1]; /* m22: loc_49AA */
    case HASHSIGN - 1:
        if (nodesize(sa) != 1)
            return 0; /* m23: loc_49B3 */
        if ((char)sub_3968(sa) != 0)
            return 0;
        return 1;
    case MINUS_U - 1:
        if (nodesize(sa) != 4)
            return 0; /* m24: loc_49CD */
    m25:
        if (sub_14F3(sa) != REG_F)
            goto m27;
        return 0;
    case COMMA - 1:
        if (nodesize(sa) == 2)
            goto m25; /* m26: loc_49EA */
        return 0;
    m27:
        if (sub_14F3(sa->a_l19.wi[0]) == REG_F)
            return 0; /* loc_49FB */
        if (sub_14F3(sa) != REG_L) {
        m28:
            if (sub_14F3(sa->a_l19.wi[0]) != REG_L)
                return 0; /* loc_4A15 */
        }
        return 1;
    case LT - 1:
        if (sa->a_l19.l == 0)
            return 1; /* m29: loc_4A29 */
        return 0;
    case CONV - 1: /* m31: loc_4A3F */
        if (nodesize(sa) == 4) {
        m32:
            if (sub_14F3(sa) == REG_A) {
                if (sub_14F3(sa->a_l19.wi[0]) == REG_A)
                    return 1;
            }
        }
        return 0;
    case SUB - 1:
        if (nodesize(sa) == 2)
            goto m32; /* m34: loc_4A5F */
        return 0;
    case PLUS_U - 1:
        if (1 == sa->a_l19.l)
            return 1; /* m36: loc_4A7B */
        return 0;
    case NOT - 1:
        return (uchar)sub_46F7(sa->a_l19.wi[1]->a_l19.l); /* m38: loc_4A9C */
    case NEQL - 1:
        return (uchar)sub_46F7(-1 - sa->a_l19.wi[1]->a_l19.l); /* m40: loc_4AB7 */
    case COLON - 1:
        if (nodesize(sa) == 4)
            goto m45; /* m41: loc_4ADB */
        return 0;
    case DECR - 1:
        if (nodesize(sa) == 2)
            goto m45; /* m43: loc_4AEC */
        return 0;
    case GADDR - 1:
        if (nodesize(sa) != 1)
            return 0; /* m44: loc_4AF7 */
    m45:
        if (sub_14F3(sa) != REG_A) {
            if (sub_14F3(sa) != REG_L)
                return 0;
        }
        if (sub_14F3(sa->a_l19.wi[0]) != REG_F)
            return 0; /* m46: loc_4B19 */
        return 1;
    case DIV - 1:
        if (nodesize(sa->a_l19.wi[0]) == 1)
            goto m51; /* m47: loc_4B2A */
        return 0;
    case DOT_DOT - 1:
        if (nodesize(sa->a_l19.wi[0]) == 2)
            goto m51; /* m49: loc_4B40 */
        return 0;
    case DOT - 1:
        if (nodesize(sa->a_l19.wi[0]) != 4)
            return 0; /* m50: loc_4B50 */
    m51:
        if (sub_14F3(sa) != REG_F)
            return 0;
        if (sub_14F3(sa->a_l19.wi[0]) == REG_A)
            return 1;
        goto m28;
    case LAND - 1:
        if (sub_14F3(sa) == REG_F)
            return 1; /* m52: loc_4B7D */
    }
    return 0;
}

/* End of file sub_47B2.c  */
#endif

/*
 * File - sub_4B89.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_4B89 OK+		      Used in: sub_4C12, sub_54B6
 *
 * Minor differences in the generated code.
 * Function is assigned the uchar type to avoid casting
 * type when it is called in other functions and generating
 * code corresponding to binary image.
 * Function is logically correct.
 *********************************************************/
uchar sub_4B89(register aaa_t *sa) {

#ifdef DEBUG
    printf("\tsub_4B89(%x)\n", sa);
#endif

    if ((dopetab[sa->a_c0] & 0x10) == 0) { /* Any operator except "#", "..", "CONST" */
        if ((sa->a_c0 != GADDR) || (sa->a_l19.wi[0]->a_c0 != IDOP)) {
            if (sa->a_c0 == ADD) {
                if (sa->a_l19.wi[1]->a_c0 == CONST) {
                    if (sub_4B89(sa->a_l19.wi[0]) != 0) {
                        return 1;
                    }
                }
            }
            return 0; /* m2: */
        }
    }
    return 1; /* m3: */
}

/* End of file sub_4B89.c  */
#endif

/*
 * File - sub_4BE5.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_4BE5 OK++			Used in: sub_54B6
 *********************************************************/
int sub_4BE5(register aaa_t *sa) {

#ifdef DEBUG
    printf("\tsub_4BE5(%x)\n", sa);
#endif

    if (sa->a_c0 != CONST)
        goto m1;
    if (sa->a_l19.l != 0)
        goto m1;
    return 1;
m1:
    return 0;
}

/*********************************************************
 * sub_4C12 OK++			Used in: sub_54B6
 *********************************************************/
int sub_4C12(register aaa_t *sa) {

#ifdef DEBUG
    printf("\tsub_4C12(%x)\n", sa);
#endif

    if (sa->a_c0 == GADDR) {
        if (sa->a_l19.wi[0]->a_c0 == IDOP)
            return 1;
    }
    if ((dopetab[sa->a_c0] & 0x10) != 0)
        return 0; /* if "#", "..", "CONST"  */
    if (sub_4B89(sa) != 0)
        return 1;
    return dopetab[sa->a_c0] & 0xF;
}

/* End of file sub_4BE5.c  */
#endif

/*
 * File - sub_4C6D.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_4C6D OK+				Used in: sub_3CDF
 *********************************************************/
char sub_4C6D(aaa_t *p1a) {

#ifdef DEBUG
    printf("\tsub_4C6D(%x)\n", p1a);
#endif

    if (p1a->a_l19.wi[0]->a_c0 == USEREG)
        return 1;
    return 0;
}

/* End of file sub_4C6D.c  */
#endif

/*
 * File - sub_4C8B.c Created 09.03.2019 Last Modified 31.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_4C8B OK++			Used in: sub_54B6
 *********************************************************/
aaa_t *sub_4C8B(register aaa_t *sa) {
    aaa_t *l1;

#ifdef DEBUG
    printf("\tsub_4C8B(%x)\n", sa);
#endif

    l1 = sa->a_l19.wi[0];
    if (sa->a_l19.wi[0]->a_c0 == NOT) {
        l1 = l1->a_l19.wi[0];
        freeAaa(sa->a_l19.wi[0]);
        freeAaa(sa);
        return l1;
    }
    if ((dopetab[l1->a_c0] & 0x12C) == '(') {
        freeAaa(sa);
        l1->a_c0 = sub_605E(l1->a_c0);
        return l1;
    }
    if ((dopetab[l1->a_c0] & 0x20) != 0) {
        l1->a_l19.wi[0] = sub_43EF(NOT, l1->a_l19.wi[0], (aaa_t *)0);
        l1->a_l19.wi[1] = sub_43EF(NOT, l1->a_l19.wi[1], (aaa_t *)0);
        freeAaa(sa);
        l1->a_c0 = (l1->a_c0 == LAND) ? LOR : LAND;
        return l1;
    }
    return sa;
}

/*********************************************************
 * sub_4DA3 OK++			Used in: sub_54B6
 *********************************************************/
aaa_t *sub_4DA3(register aaa_t *sa) {
    aaa_t *l1a;

#ifdef DEBUG
    printf("\tsub_4DA3(%x)\n", sa);
#endif

    if ((char)sa->a_l19.wi[0]->a_i15 == 1) {
        l1a        = sub_415E(sa->a_l19.wi[0]->a_i10);
        l1a->a_s17 = sa->a_s17;
        l1a->a_i15 = sa->a_i15;
        sub_475C(sa);
        sub_385B(l1a);
        sa          = allocAaa();
        *sa         = *l1a;
        sa->a_c0    = USEREG;
        sa->a_l19.l = 8;
        sa          = sub_43EF(ADD, sa, l1a);
        return sub_43EF(INCR, sa, 0);
    }
    if ((char)sa->a_l19.wi[0]->a_i15 == 2) {
        sa->a_c0    = USEREG;
        sa->a_l19.l = (int)sa->a_l19.wi[0]->a_i11;
    }
    return sa;
}

/*********************************************************
 * sub_4E8D OK++ 			Used in: sub_54B6
 *********************************************************/
aaa_t *sub_4E8D(register aaa_t *sa) {
    aaa_t *l1a;

#ifdef DEBUG
    printf("\tsub_4E8D(%x)\n", sa);
#endif

    if ((dopetab[(l1a = sa->a_l19.wi[0])->a_c0] & 0x1000) != 0) {
        l1a->a_s17      = sa->a_s17;
        l1a->a_i15      = sa->a_i15;
        sa->a_l19.wi[0] = l1a = sub_43EF(GADDR, l1a, 0);
    } else {
        l1a       = allocAaa();
        *l1a      = *sa;
        l1a->a_c0 = TYPEOP;
        sub_385B(l1a);
        sa->a_l19.wi[0] = sub_43EF(CONV, sub_43EF(GADDR, sa->a_l19.wi[0], 0), l1a);
    }
    sa->a_s17              = l1a->a_s17;
    sa->a_i15              = l1a->a_i15;
    sa->a_l19.wi[1]->a_i15 = sa->a_i15;
    sa->a_l19.wi[1]->a_s17 = sa->a_s17;
    sa->a_c0               = ADD;
    return sub_43EF(MUL_U, sa, 0);
}

/*********************************************************
 * sub_4FA8 OK++			Used in: sub_54B6
 *********************************************************/
aaa_t *sub_4FA8(register aaa_t *sa) {

#ifdef DEBUG
    printf("\tsub_4FA8(%x)\n", sa);
#endif

    sub_475C(sa->a_l19.wi[1]);
    freeAaa(sa);
    return sa->a_l19.wi[0];
}

/* End of file sub_4C8B.c  */
#endif

/*
 * File - sub_4FCE.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_4FCE OK+				Used in: sub_54B6
 *
 * Compiler generates identical code from restored source
 * program in C, however, location of branches associated
 * with case constants is different from original.
 * This does not affect the function.
 *********************************************************/
aaa_t *sub_4FCE(register aaa_t *sa) {

#ifdef DEBUG
    printf("\tsub_4FCE(%x)\n", sa);
#endif

    switch (sa->a_c0) {
    case MOD:
        sa->a_c0 = BAND;
        sa->a_l19.wi[1]->a_l19.l--;
        return sa;
    case MUL:
        sa->a_c0 = LSHIFT;
        break;
    case DIV:
        if (sub_14F3(sa) != REG_L)
            return sa;
        sa->a_c0 = RSHIFT;
        break;
    case ASMOD:
        sa->a_c0 = ASAND;
        sa->a_l19.wi[1]->a_l19.l--;
        return sa;
    case ASMUL:
        sa->a_c0 = ASLSHIFT;
        break;
    case ASDIV:
        if (sub_14F3(sa) != REG_L)
            return sa;
        sa->a_c0 = ASRSHIFT;
        break;
    }
    byte_B013                = 1;
    sa->a_l19.wi[1]->a_l19.l = sub_46F7(sa->a_l19.wi[1]->a_l19.l) - 1;
    return sa;
}

/* End of file sub_4FCE.c  */
#endif

/*
 * File - sub_508A.c Created 09.03.2019 Last Modified 31.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"
#include <string.h>

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_508A OK++			Used in: sub_54B6
 *********************************************************/
aaa_t *sub_508A(register aaa_t *sa) {
    aaa_t *l1a;
    aaa_t *l2a;
    char buf[15];
    long l3;

#ifdef DEBUG
    printf("\tsub_508A(%x)\n", sa);
#endif

    if (sub_14F3(sa) == REG_F) {
        if (sa->a_l19.wi[0]->a_c0 == CONST) {
            l3 = sa->a_l19.wi[0]->a_l19.l;
            freeAaa(sa->a_l19.wi[0]);
            freeAaa(sa->a_l19.wi[1]);
            sprintf(buf, "%ld", l3);
            sa->a_l19.ci[0] = (char *)allocmem(strlen(buf) + 1); /* create string */
            strcpy(sa->a_l19.ci[0], buf);
            sa->a_l19.ii[1] = newSwTable(); /* swTableCnt++ */
            sa->a_c0        = FCONST;
            return sa; /* m1:  */
        }
    }
    if ((dopetab[(l1a = sa->a_l19.wi[0])->a_c0] & 0x1000) != 0) { /* m2:  */
        if (nodesize(l1a) >= nodesize(sa)) {
            if (sub_14F3(sa) != REG_F) {
                if (sub_14F3(l1a) != REG_F) {
                    l1a->a_s17 = sa->a_s17;
                    l1a->a_i15 = sa->a_i15;
                    freeAaa(sa->a_l19.wi[1]);
                    freeAaa(sa); /* m3:  */
                    return l1a;
                }
            }
        }
    }
    if ((char)sub_6246(sa, l1a) != 0) { /* m5:  */
        sub_475C(sa->a_l19.wi[1]);
        l1a->a_s17 = sa->a_s17;
        l1a->a_i15 = sa->a_i15;
        freeAaa(sa);
        return l1a;
    }
    if (nodesize(l1a) < nodesize(sa))
        return sa; /* m6:  */
    if (l1a->a_c0 == CONV) {
        if (nodesize(l1a->a_l19.wi[0]) >= nodesize(sa)) {
            if (sub_6246(sa, l1a->a_l19.wi[0]) != 0)
                goto m7;
            if (sub_14F3(sa) == sub_14F3(l1a)) {
                if (sub_14F3(sa) == sub_14F3(l1a->a_l19.wi[0])) {
                m7:
                    sa->a_l19.wi[0] = l1a->a_l19.wi[0];
                    freeAaa(l1a->a_l19.wi[1]);
                    freeAaa(l1a);
                    return sa;
                }
            }
        }
    }
    if ((dopetab[l1a->a_c0] & 0xC00) == 0)
        return sa; /* m8:  */
    if (sub_14F3(l1a) == REG_F)
        return sa;
    if ((dopetab[l1a->a_c0] & 0x400) != 0) {
        if (l1a->a_l19.wi[0]->a_c0 != CONV)
            return sa;
        if (nodesize(l1a->a_l19.wi[0]->a_l19.wi[0]) >= nodesize(l1a))
            return sa;
    }
    l2a = sub_43EF(CONV, l1a->a_l19.wi[0], sa->a_l19.wi[1]); /* m9:  */
    *sa = *sa->a_l19.wi[1];
    if ((dopetab[l1a->a_c0] & 8) != 0) {
        sa = sub_43EF(CONV, l1a->a_l19.wi[1], sa);
    } else {
        freeAaa(sa); /* m10: */
        sa = 0;
    }
    l2a = sub_43EF((uchar)l1a->a_c0, l2a, sa); /* m11: */
    freeAaa(l1a);
    return l2a;
}

/*********************************************************
 * sub_53EE  OK++			Used in: sub_54B6
 *********************************************************/
aaa_t *sub_53EE(register aaa_t *sa) {
    aaa_t *l1a;

#ifdef DEBUG
    printf("\tsub_53EE(%x)\n", sa);
#endif

    if ((dopetab[(l1a = sa->a_l19.wi[0])->a_l19.wi[0]->a_c0] & 0x1000) != 0) {
        l1a        = l1a->a_l19.wi[0];
        l1a->a_s17 = sa->a_s17;
        l1a->a_i15 = sa->a_i15;
        freeAaa(sa->a_l19.wi[0]);
        freeAaa(sa);
        return l1a;
    }
    sa->a_c0        = CONV;
    sa->a_l19.wi[1] = l1a;
    sa->a_l19.wi[0] = l1a->a_l19.wi[0];
    l1a->a_c0       = TYPEOP;
    l1a->a_s17      = sa->a_s17;
    l1a->a_i15      = sa->a_i15;
    byte_B013       = 1;
    return sa;
}

/* End of file sub_508A.c  */
#endif

/*
 * File - sub_54B6.c Created 09.03.2019 Last Modified 31.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"
#include <ctype.h>
#include <stdarg.h>
#include <string.h>

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_54B6 - optim: Out of memory	Used in: sub_600E
 *********************************************************/
aaa_t *sub_54B6(register aaa_t *sa) {
    aaa_t *l1a;
    aaa_t *l2a;
    int l3;
    unsigned long l4;

#ifdef DEBUG
    printf("\tsub_54B6(%x)\n", sa);
#endif

    l3 = dopetab[sa->a_c0] & 0xC;
    if (l3 != 0) {
        sa->a_l19.wi[0] = sub_54B6(sa->a_l19.wi[0]);
    }
    if (l3 == 8)
        sa->a_l19.wi[1] = sub_54B6(sa->a_l19.wi[1]); /* m1: */
    if ((dopetab[sa->a_c0] & 0x40) != 0) {           /* m2: */
        if (sub_4C12(sa->a_l19.wi[0]) < sub_4C12(sa->a_l19.wi[1])) {
            byte_B013       = 1;
            l1a             = sa->a_l19.wi[0];
            sa->a_l19.wi[0] = sa->a_l19.wi[1];
            sa->a_l19.wi[1] = l1a;
        }
        if ((dopetab[sa->a_c0] & 0x2000) != 0) { /* m3: */
            if (sa->a_c0 == sa->a_l19.wi[0]->a_c0) {
                if (sub_4B89(sa->a_l19.wi[1]) != 0) {
                    if (sub_4B89((l1a = sa->a_l19.wi[0])->a_l19.wi[1]) != 0) {
                        byte_B013        = 1;
                        sa->a_l19.wi[0]  = l1a->a_l19.wi[1];
                        l1a->a_l19.wi[1] = sa;
                        sa               = l1a;
                        goto m5;
                    }
                }
                if (sub_4C12(sa->a_l19.wi[0]->a_l19.wi[1]) < sub_4C12(sa->a_l19.wi[1])) { /* m4: */
                    byte_B013                    = 1;
                    l1a                          = sa->a_l19.wi[1];
                    sa->a_l19.wi[1]              = sa->a_l19.wi[0]->a_l19.wi[1];
                    sa->a_l19.wi[0]->a_l19.wi[1] = l1a;
                }
            }
        }
    }
m5:
    if ((dopetab[sa->a_c0] & 0xC00) == 0x800) {
        if (sa->a_l19.wi[0]->a_c0 == CONV) {
            if (nodesize(sa->a_l19.wi[0]->a_l19.wi[0]) < nodesize(sa)) {
                if (sub_60A8(sa->a_l19.wi[1], sa->a_l19.wi[0]->a_l19.wi[0]) != 0) {
                    l2a                    = sa->a_l19.wi[0];
                    sa->a_l19.wi[0]        = l2a->a_l19.wi[0];
                    sa->a_s17              = sa->a_l19.wi[0]->a_s17;
                    sa->a_i15              = sa->a_l19.wi[0]->a_i15;
                    sa->a_l19.wi[1]->a_s17 = sa->a_s17;
                    sa->a_l19.wi[1]->a_i15 = sa->a_i15;
                    l2a->a_l19.wi[0]       = sa;
                    sa                     = l2a;
                }
            }
        }
    }
    if ((dopetab[sa->a_c0] & 0x420) == 0x420) { /* m6: */
        l1a = sa->a_l19.wi[0];
        if (sa->a_l19.wi[0]->a_c0 == CONV) {
            if (nodesize(l1a->a_l19.wi[0]) != 0) {
                if (nodesize(l1a->a_l19.wi[0]) < nodesize(l1a)) {
                    if (sa->a_l19.wi[1]->a_c0 == CONST) {
                        if ((sub_14F3(l1a) == REG_A) || (sub_14F3(l1a->a_l19.wi[0]) == REG_L)) {
                            if (sub_62BE(sa->a_l19.wi[0], sa->a_l19.wi[1]) != 0) { /* m7: */
                                freeAaa(sa->a_l19.wi[0]);
                                freeAaa(sa->a_l19.wi[0]->a_l19.wi[1]);
                                sa->a_l19.wi[0]        = sa->a_l19.wi[0]->a_l19.wi[0];
                                sa->a_l19.wi[1]->a_s17 = sa->a_l19.wi[0]->a_s17;
                                sa->a_l19.wi[1]->a_i15 = sa->a_l19.wi[0]->a_i15;
                                goto m10;
                            }
                            word_B015 = "mismatched comparision"; /* m8: */
                            goto m10;
                        }
                    }
                    if (sa->a_l19.wi[1]->a_c0 == CONV) { /* m9: */
                        if (sub_6246(sa->a_l19.wi[0]->a_l19.wi[0], sa->a_l19.wi[1]->a_l19.wi[0]) != 0) {
                            l1a             = sa->a_l19.wi[0];
                            sa->a_l19.wi[0] = l1a->a_l19.wi[0];
                            freeAaa(l1a->a_l19.wi[1]);
                            freeAaa(l1a);
                            l1a             = sa->a_l19.wi[1];
                            sa->a_l19.wi[1] = l1a->a_l19.wi[0];
                            freeAaa(l1a->a_l19.wi[1]);
                            freeAaa(l1a);
                        }
                    }
                }
            }
        }
    } /* Ok */
m10:
    switch (sa->a_c0) {
    case NOT:
        return sub_4C8B(sa); /* goto m11; */ /* m13 */
    case GADDR:
        if (sa->a_l19.wi[0]->a_c0 != MUL_U)
            return sa; /* m47 */
    m48:
        return sub_53EE(sa); /* goto m11; */
    case MUL:
    case DIV:
    case ASMUL:
    case ASDIV:
        if (sa->a_l19.wi[1]->a_c0 == CONST) { /* m34 */
            if (sa->a_l19.wi[1]->a_l19.l == 1)
                goto m30;
        }
    case MOD:
    case ASMOD:
        if (sa->a_l19.wi[1]->a_c0 == CONST) { /* m35 */
            if (sub_46F7(sa->a_l19.wi[1]->a_l19.l) != 0) {
                return sub_4FCE(sa); /* goto m11; */
            }
        }
    case BAND:
    case ASAND:
        if (sa->a_l19.wi[1]->a_c0 != CONST)
            goto m41; /* m36 */
        if (sa->a_l19.wi[1]->a_l19.l != 0)
            goto m41;
        switch (sa->a_c0) {
        case MOD:
        case DIV:
        case ASMOD:
            warning("Division by zero");
            return sa; /* goto m18; */
        case BAND:
        case MUL:
            sub_475C(sa->a_l19.wi[0]);
            sub_475C(sa->a_l19.wi[1]);
            sa->a_c0    = CONST;
            sa->a_l19.l = 0;
            return sa; /* goto m18; */
        case ASAND:
        case ASMUL:
            sa->a_c0 = ASSIGN;
            return sa; /* goto m18; */
        case ASDIV:
        m41:
            l4 = (nodesize(sa) >= 4) ? (long)(-1) : ((long)1 << (nodesize(sa) * 8)) + 0xffffffff;
            if (sa->a_c0 != BAND) {
                if (sa->a_c0 != ASAND)
                    return sa; /* goto m18; */
            }
            if (sa->a_l19.wi[1]->a_c0 != CONST)
                return sa; /* m44: */
            if (l4 != (sa->a_l19.wi[1]->a_l19.l & l4))
                return sa;
            goto m30;
        }
    case CONV:
        return sub_508A(sa); /* m45 */
                             /* goto m11; */
    case MUL_U:
        if (sa->a_l19.wi[0]->a_c0 != GADDR)
            return sa; /* m49 */
        switch ((l1a = sa->a_l19.wi[0]->a_l19.wi[0])->a_c0) {
        case LPAREN:
        case ASSIGN:
        case QUEST:
            return sa; /* goto m18; */
        }
        goto m48;
    case PLUS_U:
        freeAaa(sa); /* m46 */
        sa = sa->a_l19.wi[0];
        return sa; /* goto m18; */
    case DOT:
        return sub_4E8D(sa); /* goto m11; */ /* m12 */
    case LT:
    case GEQ:
        if (sub_14F3(sa->a_l19.wi[0]) == REG_L) { /* m14 */
            if (sub_4BE5(sa->a_l19.wi[0]) != 0) {
                word_B015 = "degenerate unsigned comparision";
                sub_475C(sa);
                sa = sub_415E((sa->a_c0 == GEQ) ? (long)1 : (long)0);
            }
        }
        return sa; /* goto m18: */
    case LEQ:
    case GT:
        if (sub_14F3(sa->a_l19.wi[0]) == REG_L) { /* m19: */
            if (sub_4BE5(sa->a_l19.wi[1]) != 0) {
                sa->a_c0 = (sa->a_c0 == GT) ? (char)NEQL : (char)EQL;
                return sa; /* goto m18; */
            }
        }
        if (sa->a_c0 == CONST) { /* m23: */
            sa->a_l19.wi[1]->a_l19.l += 1;
            sa->a_c0 = (sa->a_c0 == GT) ? (char)GEQ : (char)LT;
        } else {
            l1a             = sa->a_l19.wi[0]; /* m25: */
            sa->a_l19.wi[0] = sa->a_l19.wi[1];
            sa->a_l19.wi[1] = l1a;
            sa->a_c0        = (sa->a_c0 != GT) ? (char)GEQ : (char)LT;
        }
        return sa; /* goto m18; */
    case ASEOR:
    case BOR:
        if (sa->a_l19.wi[1]->a_c0 == CONST) { /* m27 */
            if (sa->a_l19.wi[1]->a_l19.l == (-1)) {
                sub_475C(sa->a_l19.wi[0]);
                freeAaa(sa);
                return sa->a_l19.wi[1];
            }
        }
    case ADD:
    case SUB:
    case LSHIFT:
    case ASADD:
    case ASSUB:
    case ASLSHIFT:
    case ASRSHIFT:
    case RSHIFT:
        if (sa->a_l19.wi[1]->a_c0 == CONST) { /* m28: */
            if (sa->a_l19.wi[1]->a_l19.l == 0) {
            m30:
                return sub_4FA8(sa); /* goto m11; */
            }
        }
        if ((dopetab[sa->a_c0] & 0x80) != 0) { /* m31: */
            if (nodesize(sa->a_l19.wi[1]) != 1) {
                l1a = allocAaa();
                /*          asdf = 1;	*/
                *((sub_14F3(sa->a_l19.wi[1]) == REG_L) ? (int *)word_AE53 : /* Pointers "int*" are not  */ /* uchar  */
                      (int *)word_AED9) = /* true, but generated code */                                   /* char   */
                    &(l1a->a_s17); /* is logically correct     */
                l1a->a_c0       = TYPEOP;
                sa->a_l19.wi[1] = sub_43EF(CONV, sa->a_l19.wi[1], l1a);
            }
        }
        return sa; /* goto m18; */
    }
    if (sa->a_c0 != IDOP)
        return sa; /* goto m18; */
    return sub_4DA3(sa);
}

/* End of file sub_54B6.c  */
#endif

/*
 * File - sub_5CF5.c Created 09.03.2019 Last Modified 17.06.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_5CF5 OK+			Used in: leaveBlock, sub_17E0
 *
 * Compiler generates identical code, however, location
 * of branches associated with case constants is different
 * from original. This does not affect the function.
 *********************************************************/
void sub_5CF5(register bbb_t *sb, int p2) {

#ifdef DEBUG
    printf("\tsub_5CF5(%x, %d)\n", sb, p2);
#endif

    switch (sb->b_c15) {
    case 1:
        if (sub_61AA(sb, p2) == 0) {
            array_AE13[lvlidx] -= sb->b_size;
            if ((sb->b_i11 = array_AE13[lvlidx]) < -128 && sb->b_size >= 4) {
                warning("%s: large offset", sb->b_name);
            }
        }
        break;
    case 5:
        sb->b_i11 = array_AE97[lvlidx];
        array_AE97[lvlidx] += sb->b_size;
        if (sb->b_size == 1) {
            switch (sb->b_type->b_class) {
            case SDECL:
            case UDECL:
                break;
            default:
                array_AE97[lvlidx]++;
            }
        }
        if ((char)sub_61AA(sb, p2) == 0)
            sb->b_c15 = 1;
        break;
    case 3:
    case 4:
        sub_C57(sb);
        break;
    }
}

/* End of file sub_5CF5.c  */
#endif
/*
 * File - sub_5DF6.c Created 09.03.2019 Last Modified 31.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"
#include <string.h>

/*********************************************************
 * sub_5DF6 OK++			Used in: sub_600E
 *********************************************************/
aaa_t *sub_5DF6(register aaa_t *sa) {
    char l1;
    char *l2;

#ifdef DEBUG
    printf("\tsub_5DF6(%x)\n", sa);
#endif

    l1 = dopetab[sa->a_c0] & 0xC;
    if (l1 == 8)
        sa->a_l19.wi[1] = sub_5DF6(sa->a_l19.wi[1]);
    if (l1 != 0)
        sa->a_l19.wi[0] = sub_5DF6(sa->a_l19.wi[0]);

    switch (sa->a_c0) {
    case SUB:
    case ASSUB:
        if (sa->a_l19.wi[1]->a_c0 == CONST) {
            sa->a_l19.wi[1]->a_l19.l = 0 - sa->a_l19.wi[1]->a_l19.l;
        } else {
            sa->a_l19.wi[1] = sub_43EF(MINUS_U, sa->a_l19.wi[1], 0);
        }
        sa->a_c0 = (sa->a_c0 == SUB) ? ADD : ASADD;
        break;
    case MINUS_U:
        if (sa->a_l19.wi[0]->a_c0 == MINUS_U) {
            freeAaa(sa);
            sa = sa->a_l19.wi[0];
            freeAaa(sa);
            sa = sa->a_l19.wi[0];
        }
        if (sa->a_l19.wi[0]->a_c0 == FCONST) {
            freeAaa(sa);
            sa = sa->a_l19.wi[0];
            l2 = (char *)allocmem(strlen(sa->a_l19.ci[0]) + 2);
            strcat(strcpy(l2, "-"), sa->a_l19.ci[0]);
            free((struct ptr *)sa->a_l19.wi[0]);
            sa->a_l19.ci[0] = l2;
        }
    }
#ifdef DEBUG
    printf("\tsub_5DF6\t\tReturn %x\n", sa);
#endif
    return sa;
}

/* End of file sub_5DF6.c  */
#endif

/*
 * File - sub_5F52.c Created 09.03.2019 Last Modified 27.06.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_5F52 OK++			Used in: sub_600E
 *********************************************************/
aaa_t *sub_5F52(register aaa_t *sa) {
    char l1;
    aaa_t *l2;

#ifdef DEBUG
    printf("\tsub_5F52(%x)\n", sa);
#endif

    l1 = dopetab[sa->a_c0] & 0xC;
    if (l1 == 8)
        sa->a_l19.wi[1] = sub_5F52(sa->a_l19.wi[1]);
    if (l1 != 0)
        sa->a_l19.wi[0] = sub_5F52(sa->a_l19.wi[0]);

    switch (sa->a_c0) {
    case ADD:
        if (sa->a_l19.wi[0]->a_c0 == MINUS_U) { /* m4: */
            l2              = sa->a_l19.wi[0];
            sa->a_l19.wi[0] = sa->a_l19.wi[1];
            sa->a_l19.wi[1] = l2;
        }
    case ASADD:
        if (sa->a_l19.wi[1]->a_c0 == MINUS_U) { /* m5 */
            freeAaa(sa->a_l19.wi[1]);
            sa->a_l19.wi[1] = sa->a_l19.wi[1]->a_l19.wi[0];
            sa->a_c0        = (sa->a_c0 == ASADD) ? ASSUB : SUB;
        }
    }
#ifdef DEBUG
    printf("\tsub_5F52\t\tReturn %x\n", sa);
#endif
    return sa;
}

/* End of file sub_5F52.c  */
#endif

/*
 * File - sub_600E.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_600E OK++     Used in: sub_793,  sub_808,  sub_E43,
 *                            sub_17E0, sub_19C1, sub_1B0C,
 *			      sub_3DC9
 *********************************************************/
aaa_t *sub_600E(register aaa_t *sa) {
#if 0
    int l1; /* Not used */
#endif

#ifdef DEBUG
    aaa_t *tmp;
    printf("\tsub_600E(%x)\n", sa);
#endif

    word_B015 = 0;
    sa        = sub_5DF6(sa);
#if 0
    l1 = 0; 		/* Not used, forgot to exclude */
#endif
    do {
        byte_B013 = 0;
        /*
              Excluded part optimization code
              present in the DOS version (3.06)
        */
        sa = sub_3EAA(sub_54B6(sa));
    } while (byte_B013 != 0);

    if (word_B015 != 0) {
        warning(word_B015);
    }
#ifdef DEBUG
    tmp = sub_5F52(sa);
    printf("\tsub_600E\t\t Return %x\n", tmp);
    return tmp;
#else
    return sub_5F52(sa);
#endif
}

/* End of file sub_600E.c  */
#endif

/*
 * File - sub_605E.c Created 09.03.2019 Last Modified 26.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_605E OK+				Used in: sub_4C8B
 *
 * Compiler generates identical code, however, location
 * of branches associated with case constants is different
 * from original. This does not affect the function.
 *********************************************************/

int sub_605E(int op) {

#ifdef DEBUG
    printf("\tsub_605E(%d)\n", op);
#endif

    switch (op) {
    case NEQL:
        break;
    case LT:
        return GEQ;
    case LEQ:
        return GT;
    case EQL:
        return NEQL;
    case GT:
        return LEQ;
    case GEQ:
        return LT;
    }
    return EQL;
}

/* End of file sub_605E.c  */
#endif

/*
 * File - sub_60A8.c Created 09.03.2019 Last Modified 31.01.2021
 */
#if 0

#include "cgen.h"
#include "stdio.h"

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_60A8 OK+				Used in: sub_54B6
 *
 * Added the r_bc variable to preserve the logical
 * behavior of the function. This function was optimized
 * manually in assembly language. In places with forced
 * type casting in the original binary program image, the
 * value is returned in the HL register pair.
 *
 * Generated code is different, but does not affect the
 * program logic. This function is boolean and only returns
 * 0 or 1.
 *********************************************************/
char sub_60A8(register aaa_t *sa, aaa_t *p2a) {
    long l1;
    char r_bc; /* Original code uses BC register pair */

    if (sa->a_c0 != 'C')
        return 0;             /* m1: */
    if (nodesize(p2a) >= 4) { /* m2: */
        if (((uchar)sa->a_l19.bc[3] & 0x80) != 0) {
            if (sub_14F3(p2a) != REG_A)
                goto m4;
        }
        return (int)1; /* m3: */
    m4:
        return (int)0;
    }
    l1 = (unsigned)1 << (int)nodesize(p2a) * 8; /* m5: */
    if (sub_14F3(p2a) != REG_L)
        goto m8;
    if (((uchar)sa->a_l19.bc[3] & 0x80) != 0)
        return 0;
m6:
    r_bc = 1;
    if (sa->a_l19.l >= l1)
        r_bc--;
m7:
    return r_bc;

m8:
    l1 /= 2;
    if (((uchar)sa->a_l19.bc[3] & 0x80) == 0)
        goto m6;
    r_bc = 1;
    if (sa->a_l19.l >= 0 - l1)
        goto m7;
    r_bc--;
    goto m7;
}

/* End function sub_60A8 */
#endif

/*
 * File - sub_61AA.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 1

/*********************************************************
 * sub_61AA OK++			Used in: sub_5CF5
 *********************************************************/
bool sub_61AA(register bbb_t *sb, int p2) {

    if (!rflag && isupper(p2) && sb->b_refl == 1 && sb->b_nelem > 1) {
        if (sub_6589(word_B017, 9) == 0)
            return false;
        if (sb->b_c15 == 5)
            sb->b_c3 |= 4;
        sb->b_c15  = 2;
        sb->b_memb.i = sub_6589(word_B017, 9);
        word_B017 &= ~array_AAE8[sb->b_memb.i];
        return true;
    }

    return true;
}

/*********************************************************
 * sub_6246 OK++	      Used in: sub_508A, sub_54B6
 *********************************************************/
bool sub_6246(aaa_t *p1a, aaa_t *p2a) {

    return nodesize(p1a) == nodesize(p2a) && sub_14F3(p1a) == sub_14F3(p2a);
}

/*********************************************************
 * sub_628F v1 OK++
 *********************************************************/
bool sub_628F(aaa_t *p1a, aaa_t *p2a) {
    return sub_14F3(p1a) == REG_A && sub_14F3(p2a) == REG_A;
}

/*********************************************************
 * sub_62BE OK++			Used in: sub_54B6
 *********************************************************/
bool sub_62BE(register aaa_t *sa, aaa_t *p2a) {
    long l1, l2;
    char l3;


    l3 = nodesize(sa->a_l19.wi[0]) * 8;
    if (l3 >= 32)
        return true;
    l1 = 1L << l3;
    l2 = 0;
    if (sub_628F(sa, sa->a_l19.wi[0])) {
        l1 /= 2;
        l2 = -l1;
    }
    return l2 <= p2a->a_l19.l && p2a->a_l19.l < l1;
}

/* End of file sub_61AA.c  */
#endif

/*
 * File - sub_63B8.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * sub_63B8 OK+				Used in: sub_1F4B
 *
 * Location code snippets differs, but the program is
 * logically correct
 *********************************************************/
char sub_63B8(int p1, int p2, int p3) {
    uchar l1;
    uchar l0;
    int l2;
    register uchar *st;

#ifdef DEBUG
    printf("\tsub_63B8(%x, %x, %x)\n", p1, p2, p3);
#endif

    p3 &= ~(0x40); /* Clear bit 6 */
    l1 = 0;

    if (p2 == 0) {
        l1 = sub_6589(p1, p3);
    } else if ((p2 & 0x8000) != 0) { /* m2:  */
        l1 = sub_6589((((p2 & 0x8000) != 0) ? ((-1) - p2) : array_AAE8[p2]) & p1, p3);
    } else if (p3 < 24) { /* m5:  */
        if ((l1 = sub_6589(((p2 & 0x8000) ? ((-1) - p2) : array_AAE8[p2]) & p1, p3)) == 0) {
            if ((l2 = sub_6589(p1, p3)) != 0) {
                if ((char)sub_6589((l2 & 0x8000) ? ((-1) - l2) : array_AAE8[l2], p2) != 0) { /* m9:  */
                    l1 = l2;                                                                 /* m10: */
                }
            }
        }
    } else {
        l2 = 6; /* m11: */
        st = &array_AB54[((-24) + p3) * 6];
    m12:
        if ((*(st + 0) != 0) && (l2-- != 0)) {
            if ((l0 = sub_6589(p1, *(st++))) == 0)
                goto m12;
            if (sub_6589(array_AAE8[l0], p2) == 0) {
                if (sub_6589(array_AAE8[p2], l0) == 0)
                    goto m12;
            }
            l1 = l0;
        }
    }
    return l1; /* m16: */
}

/* End of file sub_63B8.c  */
#endif

/*
 * File - sub_6589.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 1

/*********************************************************
 * sub_6589 OK++    Used in: sub_1F4B, sub_2B79, sub_61AA,
 *			     sub_63B8, sub_66BC
 *********************************************************/
uint8_t sub_6589(int p1, int p2) {
    char l1;
    uint8_t *l2;

    p2 &= ~0x40; /* Clear bit 6 */
    if (p2 < 24)
        if ((p1 & array_AAE8[p2]) == array_AAE8[p2])
            return p2;
        else
            return 0;
    p2 -= 24;
    l1 = 6;
    l2 = &array_AB54[p2 * 6];
    do {
        if (*l2 != 0 && (p1 & array_AAE8[*l2]) == array_AAE8[*l2])
            return *l2;
    } while (*++l2 && --l1 != 0);
    return 0;
}

/*********************************************************
 * sub_665B OK++			Used in: sub_66BC
 *********************************************************/
unsigned sub_665B(unsigned int p1, uint8_t p2) {
    unsigned loc;

    if (p1 == 0)
        return 0;
    p2 -= 48;
    for (loc = 1; loc < 24; loc++)
        if (array_AB24[loc * 2 + p2] == p1)
            return loc;
    return 0;
}

/*********************************************************
 * sub_66BC v3 ??+			Used in: sub_1F4B
 *
 * This function generates code as close as possible to
 * binary image.
 * Initialization variable "l2" is not required, since in
 * subsequent it is always assigned some values.
 *********************************************************/

int sub_66BC(int p1, int p2, int p3, char *p4) {
    int16_t l1, retval;
    char *l3;

    retval = 0;
    if ((p2 & 0x8000) != 0) {
        if (p1 == 0)
            retval = p2;
        else if ((l1 = sub_6589(((p2 & 0x8000) ? ~p2 : array_AAE8[p2]) & p3, p1)) != 0)
            retval = l1;
        else
            retval = sub_6589(p3, p1);
    } else if (p1 == 0) {
        if (p2 == 0 || p4 == 0)
            retval = p2;
        else {
            for (l3 = p4; isdigit(l3[1]); l3++)
                ;
            if (p2 >= 24 && (p2 = sub_6589(p3, p2)) == 0)
                retval = 0;
            else {
                do {
                    p2 = sub_665B(p2, (uint8_t)*l3);
                } while (l3-- != p4);
                retval = p2;
            }
        }
    } else if (p2 == 0)
        retval = p1;
    else {
        l1 = ((p1 & 0x8000) ? ~p1 : array_AAE8[p1]) & ((p2 & 0x8000) ? ~p2 : array_AAE8[p2]);
        if (((p1 & 0x8000) ? ~p1 : array_AAE8[p1]) == l1)
            retval = p1;
        else if (((p2 & 0x8000) ? ~p2 : array_AAE8[p2]) == l1)
            retval = p2;
        else
            retval = sub_6589(l1, p1);
    }
    return retval;
}

/*********************************************************
 * main OK+
 *
 * Functions of opening and closing a file are replaced by
 * standard functions
 *********************************************************/
int main(int argc, char **argv) {

#ifdef DEBUG
    printf("\tmain()\n");
#endif

    baseHeap = sbrk(0);                                               /* Current highest memory */
    for (--argc, ++argv; argc > 0 && **argv == '-'; ++argv, --argc) { /* Parsing options */
        switch (argv[0][1]) {
        case 'P':
        case 'p':
            pflag = true;
            break; /* Not use */
        case 'W':
        case 'w':
            wflag = true;
            break; /* Displaying warnings */
        case 'R':
            rflag = true;
            break;
        case 'B':
            bflag = true;
            break; /* Not use */
        case 'E':
            eflag = true;
            break; /* Not use */
        case 'H':
            hflag = true;
            break; /* Not use */
        default:
            fatalErr("Illegal\tswitch %c", argv[0][1]);
            break;
        }
    }
    if (argc-- > 0) {
        if (freopen(*argv, "r", stdin) == NULL) /* Open input file */
            fatalErr("Can't open %s", *argv);
        else if (argc > 0 && freopen(argv[1], "w", stdout) == NULL) /* Open output file */
            fatalErr("Can't create %s", argv[1]);
    }
    sub_1680();                  /* First_init */
    sub_6D1();                   /* Compiling intermediate code */
    if (fclose(stdout) == EOF) { /* Close output file */
        prError("Error closing output file");
    }
    /* Exit with error code */
    exit(errcnt != 0); /* Generated code is not significantly different */

} /* End main */

/* End of file sub_6589.c  */
#endif

/*
 * File - sub_6AA2.c Created 09.03.2019 Last Modified 30.05.2020
 */
/*
 * To comply with C standard functions are replaced with similar
 * ones with a variable number of parameters
 */

/*********************************************************
 * sub_6AA2 OK++     Used in: badIntCode,  sub_17E0, sub_19C1,
 *			      sub_2BD0, sub_4192, sub_6B1D,
 * fatalErr error  	      sub_6B9B,
 *********************************************************/
void fatalErr(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    prMsg(fmt, args);
    va_end(args);
    fclose(stdout);
    exit(2);
}

/*********************************************************
 * warning v1 OK++   Used in: sub_E43,  sub_3DC9, sub_43EF,
 * Warning message	      sub_54B6, sub_5CF5, sub_600E
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

/* End of file sub_6AA2.c */

/*
 * File - sub_6B1D.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 1

/*********************************************************
 * prError v1 OK++
 * Nonfatal error
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
 * prMsg OK++	      	  Used in: ferror, prError
 *********************************************************/
void prMsg(char *fmt, va_list args) {
    fprintf(stderr, "%s:%d:\t", progname, lineno);
    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
}
/* End of file sub_6B1D.c  */
#endif

/*
 * File - sub_6B9B.c Created 09.03.2019 Last Modified 30.05.2020
 */
#if 0

#include "cgen.h"
#include "stdio.h"

/*********************************************************
 * allocmem OK++    Used in: sub_265,  sub_1754, sub_19C1,
 *			     sub_1B0C, allocAaa, sub_39CA,
 * alloc_mem & return ptr    sub_4192, sub_508A, sub_5DF6
 *********************************************************/
void *allocmem(unsigned int size) {
    register char *ptr;

#ifdef DEBUG
    printf("\tallocmem(%u)\n", size);
#endif

    do {
        if ((ptr = cmalloc(size)) != (void *)0)
            goto m1;
    } while (releaseAaaFreelist() != 0);
    fatalErr("No room");
m1:
    blkclr(ptr, size);
    return ptr;
}

/* End of file sub_6B9B.c  */
#endif

#ifdef CPM
static uint8_t *freeList; /* wB024 */

#define Len(p)     (unsigned)((p)[-1] & 0x80 ? *(uint16_t *)((p)-3) : (p)[-1])
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
                *curHi = Link(loblk);       /* move the next info to the hi block */
            else if (curHi == &Link(loblk)) /* free list order is low hi next */
                *curLo = Link(hiblk);       /* move the next info to the lo block */
            else {                          /* not adjacent in freelist */
                *curLo = Link(loblk);       /* move the lo -> next info */
                *curHi = Link(hiblk);       /* move the hi -> next info */
            }
            loblk = BlkAddr(loblk);                           /* make sure we also include the header */
            free(setSize(loblk, hiblk + Len(hiblk) - loblk)); /* join the blocks */
            packed = true;
            goto rescan;
        }
    }
    /* Bug? the original code unintentionally returned int(curHi) + 1 */
    return packed;
}

/*********************************************************
 * cmalloc v2 OK++			Used in: allocmem
 *********************************************************/
void *malloc(unsigned size) {
    uint8_t *l1;
    unsigned l2;
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
        for (sst = (uint8_t *)&freeList; l1 = Link(sst); sst = l1) {
            if (Len(l1) >= size) {
                Link(sst) = Link(l1);
                sst       = l1;
                /* if splitting the block would leave sufficient space
                 * for a new block i.e. header + data/pointer then split it */
                if ((l2 = Len(sst)) > size + 2 + sizeof(uint8_t *)) { /* ? +1 ok */
                    l1 = sst + size;
                    free(setSize(l1, l2 - size));
                    sst = BlkAddr(sst);
                    return setSize(sst, size);
                } else
                    return sst;
            }
        }
    } while (!done && (done = pack()));
    l2 = size < 128 ? 1 : 3; /* size of block header */
    if ((sst = sbrk(size + l2)) == (uint8_t *)-1)
        return 0;

    return setSize(sst, size + l2);
}

/*********************************************************
 * free v6 OK++  Used in: leaveBlock,  sub_36E0, releaseAaaFreelist
 *			      sub_5DF6, sub_6D61, cmalloc
 * free the given block inserting on free chain in size order
 *
 *********************************************************/
void free(void *p) {
    register uint8_t *st;

    for (st = (uint8_t *)&freeList; Link(st) && Len(Link(st)) < Len((uint8_t *)p); st = Link(st))
        ;
    Link(p)  = Link(st);
    Link(st) = (uint8_t *)p;
}
#endif

/*=========================================================
 * ctype
 *========================================================*/
#if 0
#include <ctype.h>

unsigned char _ctype_[] = {
    0,       _C,      _C,      _C,      _C, _C, _C, _C, _C, _C, _S, _S, _S, _S,      _S,      _C,      _C,
    _C,      _C,      _C,      _C,      _C, _C, _C, _C, _C, _C, _C, _C, _C, _C,      _C,      _C,      _S,
    _P,      _P,      _P,      _P,      _P, _P, _P, _P, _P, _P, _P, _P, _P, _P,      _P,      _N,      _N,
    _N,      _N,      _N,      _N,      _N, _N, _N, _N, _P, _P, _P, _P, _P, _P,      _P,      _U | _X, _U | _X,
    _U | _X, _U | _X, _U | _X, _U | _X, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U,      _U,      _U,      _U,
    _U,      _U,      _U,      _U,      _U, _U, _U, _P, _P, _P, _P, _P, _P, _L | _X, _L | _X, _L | _X, _L | _X,
    _L | _X, _L | _X, _L,      _L,      _L, _L, _L, _L, _L, _L, _L, _L, _L, _L,      _L,      _L,      _L,
    _L,      _L,      _L,      _L,      _L, _P, _P, _P, _P, _C
};

/* End of file ctype_.c */
#endif

#include "cgen.h"
/*
 * File - nularg.c Created 09.03.2019 Last Modified 31.01.2021
 */
#if 0

char nularg;

/* End file nularg.c */
#endif

/*
 * File - getchar.c
 * simple file used for function versions of getchar & putchar
 */
#ifdef CPM
int fgetchar() {
    return fgetc(stdin);
}
int fputchar(int c) {
    return fputc(c, stdout);
}
#endif
/*
 *	Initial setup for stdio
 */
#if 0
#include <stdio.h>

#define BUFSIZ  512
#define MAXFILE 5 /* max number of files open */

/*
#define	FILL	0, "        ", "   ", 0, {0}, 0, {0}, 0, {0}, 0
*/

#define FILL    0, "\t    ", "   ", 0, { 0 }, 0, { 0 }, 0, { 0 }, (long)4, 0

struct fcb {
    uchar dr;        /*   +0 drive code				*/
    char name[8];    /*   +1 file name				*/
    char ft[3];      /*   +9 file type				*/
    uchar ex;        /*  +12 file extent				*/
    char fil[2];     /*  +13 not used				*/
    char rc;         /*  +15 number of records in present extent	*/
    char dm[16];     /*  +16 CP/M disk map				*/
    char nr;         /*  +32 next record to read or write		*/
    uchar ranrec[3]; /*  +33 random record number (24 bit no. )	*/
    long rwp;        /*  +36 read/write pointer in bytes		*/
    uchar use;       /*  +40 use flag				*/
};

/*	 flag values in fcb.use */

#define U_READ  1 /* file open for reading   */
#define U_WRITE 2 /* file open for writing   */
#define U_RDWR  3 /* open for read and write */
#define U_CON   4 /* device is console 	   */
#define U_RDR   5 /* device is reader	   */
#define U_PUN   6 /* device is punch	   */
#define U_LST   7 /* list device		   */

extern char _sibuf[BUFSIZ];

FILE _iob[MAXFILE] = {
    {
        _sibuf, 0, _sibuf, _IOREAD | _IOMYBUF, 0 /* stdin */
    },
    {
        (char *)0, 0, (char *)0, _IOWRT | _IONBF, 1 /* stdout */
    },
    {
        (char *)0, 0, (char *)0, _IOWRT | _IONBF, 2 /* stderr */
    },
};

struct fcb _fcb[MAXFILE] = {
    { FILL }, /* stdin */
    { FILL }, /* stdout */
    { FILL }, /* stderr */
};

/* End of file setup.c */
#endif

/*
 * File - sprintf.c Created 01.07.2019 Last Modified 31.01.2021
 */
#if 0

#include <stdio.h>

static	FILE	spf;

#define MAXINT 32767 /* max for int (0x7fff)	*/

/*========================================================
 * sprintf OK++ From library		Used in: sub_6BF5
 * 
 * Unlike the standard library function, this one uses the 
 * _IOWRT|_IOBINARY flags instead of _IOWRT|_IOBINARY|_IOSTRG.
 *=======================================================*/
int sprintf(wh, f, a) char * wh; char * f; int a; {

    spf._cnt = MAXINT;
    spf._ptr = wh;
    spf._flag = _IOWRT|_IOBINARY;
    _doprnt(&spf, f, &a);
    *spf._ptr = 0;
    return spf._ptr - wh;
}

/* End function sprintf */

/*
 * vfprintf - formatted output without ellipsis
 */

#include <stdarg.h>
#include <stdio.h>

extern int	_doprnt();

int
vfprintf(FILE *	file, char * fmt, va_list args) {
    return _doprnt(file, fmt, args);
}

#endif
#endif /* end of non DATA */