/*
 *
 * The kwd.c file is part of the restored ZAS.EXE program
 * from the Hi-Tech Z80 C cross compiler v4.11
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH Z80 C cross compiler V4.11 
 * (HI-TECH Software) and extend its life, outside of the MSDOS 16 bit environment
 * for full operation in windows 32/64 and Unix-like operating systems
 *
 * The HI-TECH Z80 C cross compiler V4.11 is provided free of charge for any use,
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
 * This work is an extension of earlier work on decompiling ZAS.COM from the
 * Hi-Tech CP/M based compiler v3.09
 *
 * See the readme.md file for additional commentary
 *
 * Mark Ogden
 * 06-Jun-2022
 */
#include "cclass.h"
#include "zas.h"

/* clang-format off */
kwd_t kwd[] = { /* 0734 */
    {"$",      T_DOLLAR,   0   },  /* 0   */
    {"&",      G_AND,      4   },  /* 1   */
    {"(",      T_LPAREN,   9   },  /* 2   */
    {")",      T_RPAREN,   1   },  /* 3   */
    {"*",      T_MULT,     6   },  /* 4   */
    {"+",      T_PLUS,     5   },  /* 5   */
    {"",       T_COMMA,    0   },  /* 6   */
    {"-",      T_MINUS,    5   },  /* 7   */
    {".and.",  G_AND,      4   },  /* 8   */
    {".eq.",   G_EQ,       2   },  /* 9   */
    {".gt.",   G_GT,       2   },  /* 10  */
    {".high.", T_HIGH,     8   },  /* 11  */
    {"high",   T_HIGH,     8   },  /* 12  */
    {".low.",  T_LOW,      8   },  /* 13  */
    {"low",    T_LOW,      8   },  /* 14  */
    {".lt.",   G_LT,       2   },  /* 15  */
    {".mod.",  T_MOD,      6   },  /* 16  */
    {".not.",  G_NOT,      8   },  /* 17  */
    {"not",    G_NOT,      8   },  /* 18  */
    {".or.",   G_OR,       3   },  /* 19  */
    {".res.",  T_RES,      7   },  /* 20  */
    {".shl.",  T_SHL,      6   },  /* 21  */
    {"shl",    T_SHL,      6   },  /* 22  */
    {".shr.",  T_SHR,      6   },  /* 23  */
    {"shr",    T_SHR,      6   },  /* 24  */
    {".ugt.",  T_UGT,      2   },  /* 25  */
    {".ult.",  T_ULT,      2   },  /* 26  */
    {".xor.",  T_XOR,      3   },  /* 27  */
    {"/",      T_DIV,      6   },  /* 28  */
    {":",      T_COLON,    0   },  /* 29  */
    {"<",      G_LT,       2   },  /* 30  */
    {"=",      G_EQ,       2   },  /* 31  */
    {">",      G_GT,       2   },  /* 32  */
    {"\\",     G_NOT,      8   },  /* 33  */
    {"^",      G_OR,       3   },  /* 34  */
    {"a",      G_REG,      7   },  /* 35  */
    {"adc",    G_ADCSBC,   0x88},  /* 36  */
    {"add",    T_ADD,      0x80},  /* 37  */
    {"af",     G_REG,      0x27},  /* 38  */
    {"af'",    G_REG,      0x28},  /* 39  */
    {"age",    G_CC,       6   },  /* 40  */
    {"alt",    G_CC,       7   },  /* 41  */
    {"and",    G_ARITH8,   0xA0},  /* 42  */
    {"anz",    G_CC,       0   },  /* 43  */
    {"az",     G_CC,       1   },  /* 44  */
    {"b",      G_REG,      0   },  /* 45  */
    {"bc",     G_REG,      0x20},  /* 46  */
    {"bit",    G_BIT,      0x40},  /* 47  */
    {"c",      G_REG,      1   },  /* 48  */
    {"call",   T_CALL,     0xCD},  /* 49  */
    {"ccf",    G_SIMPLE,   0x3F},  /* 50  */
    {"cond",   T_COND,     0   },  /* 51  */
    {"cp",     G_ARITH8,   0xB8},  /* 52  */
    {"cpd",    G_EDSIMPLE, 0xA9},  /* 53  */
    {"cpdr",   G_EDSIMPLE, 0xB9},  /* 54  */
    {"cpi",    G_EDSIMPLE, 0xA1},  /* 55  */
    {"cpir",   G_EDSIMPLE, 0xB1},  /* 56  */
    {"cpl",    G_SIMPLE,   0x2F},  /* 57  */
    {"d",      G_REG,      2   },  /* 58  */
    {"daa",    G_SIMPLE,   0x27},  /* 59  */
    {"de",     G_REG,      0x22},  /* 60  */
    {"dec",    G_INCDEC,   5   },  /* 61  */
    {"defb",   T_DEFB,     0   },  /* 62  */
    {"deff",   T_DEFF,     0   },  /* 63  */
    {"defl",   T_DEFL,     0   },  /* 64  */
    {"defm",   T_DEFM,     0   },  /* 65  */
    {"defs",   T_DEFS,     0   },  /* 66  */
    {"defw",   T_DEFW,     0   },  /* 67  */
    {"di",     G_SIMPLE,   0xF3},  /* 68  */
    {"djnz",   T_DJNZ,     0x10},  /* 69  */
    {"e",      G_REG,      3   },  /* 70  */
    {"ei",     G_SIMPLE,   0xFB},  /* 71  */
    {"else",   T_ELSE,     0   },  /* 72  */
    {"end",    T_END,      0   },  /* 73  */
    {"endc",   G_END,      0   },  /* 74  */
    {"endif",  G_END,      0   },  /* 75  */
    {"endm",   T_ENDM,     0   },  /* 76  */
    {"equ",    T_EQU,      0   },  /* 77  */
    {"ex",     T_EX,       0xEB},  /* 78  */
    {"exx",    G_SIMPLE,   0xD9},  /* 79  */
    {"file",   T_FILE,     0   },  /* 80  */
    {"fge",    G_CC,       6   },  /* 81  */
    {"flt",    G_CC,       7   },  /* 82  */
    {"fnz",    G_CC,       0   },  /* 83  */
    {"fz",     G_CC,       1   },  /* 84  */
    {"global", T_GLOBAL,   0   },  /* 85  */
    {"h",      G_REG,      4   },  /* 86  */
    {"halt",   G_SIMPLE,   0x76},  /* 87  */
    {"hl",     G_REG,      0x24},  /* 88  */
    {"i",      G_REG,      0x10},  /* 89  */
    {"if",     T_COND,     0   },  /* 90  */
    {"im",     T_IM,       0x46},  /* 91  */
    {"in",     T_IN,       0xDB},  /* 92  */
    {"in0",    T_IN0,      0   },  /* 93  */
    {"inc",    G_INCDEC,   4   },  /* 94  */
    {"ind",    G_EDSIMPLE, 0xAA},  /* 95  */
    {"indr",   G_EDSIMPLE, 0xBA},  /* 96  */
    {"ini",    G_EDSIMPLE, 0xA2},  /* 97  */
    {"inir",   G_EDSIMPLE, 0xB2},  /* 98  */
    {"irp",    T_IRP,      0   },  /* 99  */
    {"irpc",   T_IRPC,     0   },  /* 100 */
    {"ix",     G_REG,      0xDD},  /* 101 */
    {"iy",     G_REG,      0xFD},  /* 102 */
    {"jp",     T_JP,       0xC3},  /* 103 */
    {"jr",     T_JR,       0x18},  /* 104 */
    {"l",      G_REG,      5   },  /* 105 */
    {"ld",     T_LD,       0x40},  /* 106 */
    {"ldd",    G_EDSIMPLE, 0xA8},  /* 107 */
    {"lddr",   G_EDSIMPLE, 0xB8},  /* 108 */
    {"ldi",    G_EDSIMPLE, 0xA0},  /* 109 */
    {"ldir",   G_EDSIMPLE, 0xB0},  /* 110 */
    {"line",   T_LINE,     0   },  /* 111 */
    {"lge",    G_CC,       2   },  /* 112 */
    {"llt",    G_CC,       3   },  /* 113 */
    {"local",  T_LOCAL,    0   },  /* 114 */
    {"lnz",    G_CC,       0   },  /* 115 */
    {"lz",     G_CC,       1   },  /* 116 */
    {"m",      G_CC,       7   },  /* 117 */
    {"macro",  T_MACRO,    0   },  /* 118 */
    {"mlt",    T_MLT,      0x4C},  /* 119 */
    {"nc",     G_CC,       2   },  /* 120 */
    {"neg",    G_EDSIMPLE, 0x44},  /* 121 */
    {"no",     G_CC,       4   },  /* 122 */
    {"nop",    G_SIMPLE,   0   },  /* 123 */
    {"nz",     G_CC,       0   },  /* 124 */
    {"o",      G_CC,       5   },  /* 125 */
    {"or",     G_ARITH8,   0xB0},  /* 126 */
    {"org",    T_ORG,      0   },  /* 127 */
    {"otdm",   G_EDSIMPLE, 0x8B},  /* 128 */
    {"otdmr",  G_EDSIMPLE, 0x9B},  /* 129 */
    {"otdr",   G_EDSIMPLE, 0xBB},  /* 130 */
    {"otim",   G_EDSIMPLE, 0x83},  /* 131 */
    {"otimr",  G_EDSIMPLE, 0x93},  /* 132 */
    {"otir",   G_EDSIMPLE, 0xB3},  /* 133 */
    {"out",    T_OUT,      0xD3},  /* 134 */
    {"out0",   T_OUT0,     1   },  /* 135 */
    {"outd",   G_EDSIMPLE, 0xAB},  /* 136 */
    {"outi",   G_EDSIMPLE, 0xA3},  /* 137 */
    {"p",      G_CC,       6   },  /* 138 */
    {"pe",     G_CC,       5   },  /* 139 */
    {"po",     G_CC,       4   },  /* 140 */
    {"pop",    G_PUSHPOP,  0xC1},  /* 141 */
    {"psect",  T_PSECT,    0   },  /* 142 */
    {"push",   G_PUSHPOP,  0xC5},  /* 143 */
    {"r",      G_REG,      0x11},  /* 144 */
    {"rept",   T_REPT,     0   },  /* 145 */
    {"res",    G_BIT,      0x80},  /* 146 */
    {"ret",    T_RET,      0xC9},  /* 147 */
    {"reti",   G_EDSIMPLE, 0x4D},  /* 148 */
    {"retn",   G_EDSIMPLE, 0x45},  /* 149 */
    {"rl",     G_ROTATE,   0x10},  /* 150 */
    {"rla",    G_SIMPLE,   0x17},  /* 151 */
    {"rlc",    G_ROTATE,   0   },  /* 152 */
    {"rlca",   G_SIMPLE,   7   },  /* 153 */
    {"rld",    G_EDSIMPLE, 0x6F},  /* 154 */
    {"rr",     G_ROTATE,   0x18},  /* 155 */
    {"rra",    G_SIMPLE,   0x1F},  /* 156 */
    {"rrc",    G_ROTATE,   8   },  /* 157 */
    {"rrca",   G_SIMPLE,   0xF },  /* 158 */
    {"rrd",    G_EDSIMPLE, 0x67},  /* 159 */
    {"rst",    T_RST,      0xC7},  /* 160 */
    {"sbc",    G_ADCSBC,   0x98},  /* 161 */
    {"scf",    G_SIMPLE,   0x37},  /* 162 */
    {"set",    G_BIT,      0xC0},  /* 163 */
    {"sla",    G_ROTATE,   0x20},  /* 164 */
    {"sll",    G_ROTATE,   0x20},  /* 165 */
    {"slp",    G_EDSIMPLE, 0x76},  /* 166 */
    {"sp",     G_REG,      0x26},  /* 167 */
    {"sra",    G_ROTATE,   0x28},  /* 168 */
    {"srl",    G_ROTATE,   0x38},  /* 169 */
    {"sub",    G_ARITH8,   0x90},  /* 170 */
    {"tst",    T_TST,      4   },  /* 171 */
    {"tstio",  T_TSTIO,    0   },  /* 172 */
    {"xor",    G_ARITH8,   0xA8},  /* 173 */
    {"z",      G_CC,       1   },  /* 174 */
};


kwd_t *kwdHashtab[] = { /* 0b4e */
    &kwd[6],   NULL,      &kwd[169], NULL,     
    NULL,      &kwd[72],  &kwd[2],   &kwd[78], 
    NULL,      &kwd[30],  NULL,      &kwd[155],
    &kwd[95],  &kwd[13],  &kwd[168], &kwd[58], 
    NULL,      NULL,      &kwd[171], NULL,     
    &kwd[18],  NULL,      &kwd[173], NULL,     
    NULL,      &kwd[24],  NULL,      NULL,     
    NULL,      NULL,      NULL,      &kwd[111],
    &kwd[65],  &kwd[149], &kwd[117], NULL,     
    NULL,      NULL,      NULL,      NULL,     
    NULL,      &kwd[1],   &kwd[38],  NULL,     
    &kwd[29],  &kwd[46],  &kwd[104], &kwd[128],
    &kwd[62],  NULL,      &kwd[45],  NULL,     
    &kwd[87],  &kwd[154], NULL,      NULL,     
    NULL,      &kwd[50],  NULL,      NULL,     
    &kwd[16],  &kwd[26],  NULL,      NULL,     
    &kwd[28],  &kwd[124], NULL,      NULL,     
    NULL,      &kwd[133], NULL,      &kwd[15], 
    &kwd[106], NULL,      NULL,      &kwd[135],
    &kwd[0],   &kwd[43],  &kwd[112], &kwd[137],
    &kwd[14],  &kwd[80],  &kwd[103], NULL,     
    NULL,      &kwd[53],  &kwd[82],  NULL,     
    NULL,      NULL,      &kwd[122], &kwd[123],
    &kwd[115], &kwd[71],  NULL,      &kwd[7],  
    NULL,      NULL,      NULL,      NULL,     
    &kwd[84],  &kwd[97],  NULL,      NULL,     
    &kwd[89],  NULL,      &kwd[159], NULL,     
    &kwd[79],  &kwd[42],  NULL,      &kwd[100],
    NULL,      NULL,      &kwd[134], NULL,     
    &kwd[150], NULL,      &kwd[132], NULL,     
    &kwd[34],  &kwd[145], &kwd[39],  &kwd[144],
    NULL,      &kwd[146], NULL,      &kwd[76], 
    &kwd[90],  &kwd[114], &kwd[5],   &kwd[22], 
    NULL,      NULL,      &kwd[127], &kwd[130],
    &kwd[153], NULL,      NULL,      NULL,     
    NULL,      NULL,      NULL,      NULL,     
    NULL,      NULL,      NULL,      &kwd[77], 
    NULL,      NULL,      NULL,      NULL,     
    &kwd[49],  &kwd[143], &kwd[141], &kwd[107],
    &kwd[37],  NULL,      &kwd[138], &kwd[139],
    NULL,      &kwd[69],  &kwd[116], NULL,     
    NULL,      &kwd[3],   &kwd[44],  &kwd[101],
    &kwd[31],  &kwd[9],   &kwd[120], NULL,     
    &kwd[11],  NULL,      &kwd[55],  &kwd[70], 
    NULL,      NULL,      &kwd[167], NULL,     
    &kwd[74],  NULL,      &kwd[91],  &kwd[98], 
    &kwd[110], NULL,      NULL,      NULL,     
    NULL,      &kwd[172], NULL,      NULL,     
    NULL,      NULL,      NULL,      NULL,     
    NULL,      NULL,      &kwd[56],  NULL,     
    NULL,      NULL,      &kwd[21],  &kwd[121],
    &kwd[170], NULL,      &kwd[94],  NULL,     
    NULL,      &kwd[48],  &kwd[67],  NULL,     
    NULL,      NULL,      NULL,      NULL,     
    &kwd[93],  &kwd[162], NULL,      &kwd[166],
    NULL,      &kwd[61],  NULL,      &kwd[51], 
    NULL,      NULL,      &kwd[64],  NULL,     
    &kwd[105], NULL,      NULL,      NULL,     
    NULL,      NULL,      NULL,      NULL,     
    NULL,      &kwd[73],  &kwd[81],  &kwd[152],
    NULL,      &kwd[83],  NULL,      NULL,     
    &kwd[35],  &kwd[52],  NULL,      NULL,     
    &kwd[88],  &kwd[96],  &kwd[108], NULL,     
    NULL,      &kwd[25],  NULL,      NULL,     
    NULL,      NULL,      NULL,      NULL,     
    &kwd[109], NULL,      NULL,      NULL,     
    &kwd[10],  &kwd[19],  &kwd[60],  NULL,     
    &kwd[23],  NULL,      NULL,      NULL,     
    NULL,      &kwd[54],  &kwd[151], NULL,     
    NULL,      &kwd[27],  &kwd[113], &kwd[41], 
    &kwd[47],  &kwd[66],  &kwd[33],  NULL,     
    &kwd[147], &kwd[8],   &kwd[12],  NULL,     
    &kwd[20],  &kwd[57],  &kwd[165], NULL,     
    NULL,      NULL,      &kwd[75],  &kwd[85], 
    &kwd[148], NULL,      &kwd[86],  NULL,     
    &kwd[157], NULL,      NULL,      NULL,     
    NULL,      &kwd[164], &kwd[118], &kwd[160],
    NULL,      NULL,      &kwd[119], &kwd[129],
    &kwd[163], NULL,      &kwd[99],  NULL,     
    NULL,      &kwd[161], &kwd[68],  &kwd[158],
    NULL,      NULL,      NULL,      NULL,     
    &kwd[4],   &kwd[102], NULL,      &kwd[32], 
    &kwd[59],  NULL,      NULL,      &kwd[63], 
    NULL,      &kwd[126], &kwd[131], &kwd[156],
    &kwd[174], &kwd[140], NULL,      NULL,     
    NULL,      &kwd[92],  &kwd[136], NULL,     
    NULL,      NULL,      &kwd[40],  NULL,     
    NULL,      &kwd[142], &kwd[36],  &kwd[17], 
    &kwd[125],
};

#ifdef _MSC_VER
#pragma warning(disable: 4245)  /* avoid warnings re converting int to uint8_t */
#endif
uint8_t invalidChars[] = { /* 0e10 */
    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    /* 00-07 */
    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    /* 08-0F */
    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    /* 10-17 */
    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    /* 18-1F */
    ~0,    ~0,    ~0,    ~0,    ~1,    ~0,    ~1,    ~4,    /* 20-27 */
    ~1,    ~1,    ~1,    ~1,    ~0,    ~1,    ~0x39, ~1,    /* 28-2F */
    ~0xC,  ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    /* 30-37 */
    ~0,    ~0,    ~1,    ~0,    ~1,    ~1,    ~1,    ~0,    /* 38-3F */
    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    /* 40-47 */
    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    /* 48-4F */
    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    ~0,    /* 50-57 */
    ~0,    ~0,    ~0,    ~0,    ~3,    ~0,    ~1,    ~0,    /* 58-5F */
    ~0,    ~0x1F, ~0xF,  ~0xF,  ~0xF,  ~0xF,  ~0x1F, ~0xF,  /* 60-67 */
    ~0x1F, ~0xF,  ~3,    ~0,    ~0x3F, ~0xB,  ~0xF,  ~0x17, /* 68-6F */
    ~7,    ~6,    ~0x1F, ~0xF,  ~0x1F, ~6,    ~0,    ~0xC,  /* 70-77 */
    ~7,    ~2,    ~0xF,  ~0,    ~0,    ~0,    ~0,    ~0,    /* 78-7F */
};
#ifdef _MSC_VER
#pragma warning(default: 4245)
#endif


kwd_t psectKwd[] = { /* 0e90 */
    {"abs",    G_PSECT, F_ABS   },  /* 0 */
    {"global", G_PSECT, F_GLOBAL},  /* 1 */
    {"local",  G_PSECT, F_LOCAL },  /* 2 */
    {"ovrld",  G_PSECT, F_OVRLD },  /* 3 */
    {"pure",   G_PSECT, F_PURE  },  /* 4 */
    {"reloc",  G_PSECT, F_RELOC },  /* 5 */
    {"size",   G_PSECT, F_SIZE  },  /* 6 */
};



kwd_t *psectHashtab[] = { /* 0bea */
    NULL,         &psectKwd[2], &psectKwd[3], &psectKwd[4],
    &psectKwd[6], NULL,         NULL,         NULL,        
    NULL,         NULL,         NULL,         &psectKwd[1],
    &psectKwd[5], NULL,         NULL,         NULL,        
    &psectKwd[0],
};
/* clang-format on */

static kwd_t *findKwd(register char *s);                     /* 82 2FB6 */
static kwd_t *findPsect(register char *s);                   /* 83 304A */
static int16_t getTokenId(register char *s, kwdfptr funptr); /* 84 30BE */

/**************************************************************************
 82 2fb6 ++
 **************************************************************************/
/*
    for fast access a table (invalidChars) is used to determine whether a character
    of the passed in string is valid at the corresponding location. e.g.
    if valid in pos 1, the bit 0 is clear, if valid in pos 2, bit 1 is clear ...
    note this limits to 8 char keywords
*/
static kwd_t *findKwd(register char *s) {
    kwd_t **probe;
    uint16_t hashIndex;
    int16_t probeStep;
    char *name;
    char chBitMask;

    hashIndex = 0;
    probeStep = 1;
    name      = s;
    hashIndex = 0;
    chBitMask = 1; /* this is used as a */
    while (*s) {
        if ((invalidChars[*s & 0x7f] & chBitMask)) /* char not allowed here for valid kwd */
            return NULL;
        hashIndex >>= 2; /* update the hash with this char */
        hashIndex += (*s << 9);
        s++;
        chBitMask <<= 1;
    }
    probe = kwdHashtab + hashIndex % MAX_OPERATORS;
    while (*probe && strcmp(name, (*probe)->name) != 0) { /* done it no more or found */
        probe += probeStep;
        probeStep += 2;
        if (probe >= kwdHashtab + MAX_OPERATORS) /* wrap around */
            probe -= MAX_OPERATORS;
    }
    return *probe;
}

/**************************************************************************
 83 304a ++
 **************************************************************************/
/* similar hash model to findKwd, but doesn't do the valid char precheck */
static kwd_t *findPsect(register char *s) {
    kwd_t **probe;
    uint16_t hashIndex;
    int16_t probeStep;
    char *name;

    hashIndex = 0;
    probeStep = 1;
    name      = s;
    while (*s) {
        hashIndex >>= 2;
        hashIndex += (*s << 9);
        ++s;
    }
    probe = psectHashtab + hashIndex % MAX_PSECT;
    while (*probe && (strcmp(name, (*probe)->name) != 0)) {
        probe += probeStep;
        probeStep += 2;
        if (probe >= psectHashtab + MAX_PSECT)
            probe -= MAX_PSECT;
    }
    return *probe;
}

/**************************************************************************
 84 30be ++
 **************************************************************************/
static int16_t getTokenId(register char *s, kwdfptr funptr) {
    char *t;
    kwd_t *po;
    char buf[80];

    t = buf;
    while (*s) { /* ? optimise loop expression to *t++ = tolower(*s); s++ */
        if (Isupper(*s))
            *t++ = 0x20 + *s++;
        else
            *t++ = *s++;
    }
    *t = 0;
    po = funptr(buf);
    if (!po)
        return -1;
    yylval.yTok = po->flags;
    return po->id;
}

/**************************************************************************
 85 311a ++
 **************************************************************************/
int16_t getKwdId(char *p1) {
    return getTokenId(p1, findKwd);
}

/**************************************************************************
 86 312c ++
 **************************************************************************/
int16_t getPsectId(char *p1) {
    return getTokenId(p1, findPsect);
}
