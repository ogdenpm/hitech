/*
 *
 * The kwd.c file is part of the restored ZAS.COM program
 * from the Hi-Tech C compiler v3.09
 *
 * Not a commercial goal of this laborious work is to popularize among
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
 * Early work on the decompilation was done by Andrey Nikitin
 * Completion of the work and porting to work under modern compilers done by Mark Ogden
 * 19-May-2022
 */
#include "cclass.h"
#include "zas.h"

/* clang-format off */
kwd_t kwd[] = {
    {"$",      T_DOLLAR,   0   },  /* 0   */
    {"&",      G_AND,      4   },  /* 1   */
    {"(",      T_LPAREN,   9   },  /* 2   */
    {")",      T_RPAREN,   1   },  /* 3   */
    {"*",      T_MULT,     6   },  /* 4   */
    {"+",      T_PLUS,     5   },  /* 5   */
    {"",       T_COMMA,  0   },  /* 6   */
    {"-",      T_MINUS,    5   },  /* 7   */
    {".and.",  G_AND,      4   },  /* 8   */
    {".eq.",   G_EQ,       2   },  /* 9   */
    {".gt.",   G_GT,       2   },  /* 10  */
    {".high.", T_HIGH,     8   },  /* 11  */
    {".low.",  T_LOW,      8   },  /* 12  */
    {".lt.",   G_LT,       2   },  /* 13  */
    {".mod.",  T_MOD,      6   },  /* 14  */
    {".not.",  G_NOT,      8   },  /* 15  */
    {".or.",   G_OR,       3   },  /* 16  */
    {".res.",  T_RES,      7   },  /* 17  */
    {".shl.",  T_SHL,      6   },  /* 18  */
    {".shr.",  T_SHR,      6   },  /* 19  */
    {".ugt.",  T_UGT,      2   },  /* 20  */
    {".ult.",  T_ULT,      2   },  /* 21  */
    {".xor.",  T_XOR,      3   },  /* 22  */
    {"/",      T_DIV,      6   },  /* 23  */
    {":",      T_COLON,    0   },  /* 24  */
    {"<",      G_LT,       2   },  /* 25  */
    {"=",      G_EQ,       2   },  /* 26  */
    {">",      G_GT,       2   },  /* 27  */
    {"\\",     G_NOT,      8   },  /* 28  */
    {"^",      G_OR,       3   },  /* 29  */
    {"a",      G_REG,      7   },  /* 30  */
    {"adc",    G_ADCSBC,   0x88},  /* 31  */
    {"add",    T_ADD,      0x80},  /* 32  */
    {"af",     G_REG,      0x27},  /* 33  */
    {"af'",    G_REG,      0x28},  /* 34  */
    {"age",    G_CC,       6   },  /* 35  */
    {"alt",    G_CC,       7   },  /* 36  */
    {"and",    G_ARITH8,   0xA0},  /* 37  */
    {"anz",    G_CC,       0   },  /* 38  */
    {"az",     G_CC,       1   },  /* 39  */
    {"b",      G_REG,      0   },  /* 40  */
    {"bc",     G_REG,      0x20},  /* 41  */
    {"bit",    G_BIT,      0x40},  /* 42  */
    {"c",      G_REG,      1   },  /* 43  */
    {"call",   T_CALL,     0xCD},  /* 44  */
    {"ccf",    G_SIMPLE,   0x3F},  /* 45  */
    {"cond",   T_COND,     0   },  /* 46  */
    {"cp",     G_ARITH8,   0xB8},  /* 47  */
    {"cpd",    G_EDSIMPLE, 0xA9},  /* 48  */
    {"cpdr",   G_EDSIMPLE, 0xB9},  /* 49  */
    {"cpi",    G_EDSIMPLE, 0xA1},  /* 50  */
    {"cpir",   G_EDSIMPLE, 0xB1},  /* 51  */
    {"cpl",    G_SIMPLE,   0x2F},  /* 52  */
    {"d",      G_REG,      2   },  /* 53  */
    {"daa",    G_SIMPLE,   0x27},  /* 54  */
    {"de",     G_REG,      0x22},  /* 55  */
    {"dec",    G_INCDEC,   5   },  /* 56  */
    {"defb",   T_DEFB,     0   },  /* 57  */
    {"deff",   T_DEFF,     0   },  /* 58  */
    {"defl",   T_DEFL,     0   },  /* 59  */
    {"defm",   T_DEFM,     0   },  /* 60  */
    {"defs",   T_DEFS,     0   },  /* 61  */
    {"defw",   T_DEFW,     0   },  /* 62  */
    {"di",     G_SIMPLE,   I_DI},  /* 63  */
    {"djnz",   T_DJNZ,     0x10},  /* 64  */
    {"e",      G_REG,      3   },  /* 65  */
    {"ei",     G_SIMPLE,   I_EI},  /* 66  */
    {"end",    T_END,      0   },  /* 67  */
    {"endc",   T_ENDC,     0   },  /* 68  */
    {"endm",   T_ENDM,     0   },  /* 69  */
    {"equ",    T_EQU,      0   },  /* 70  */
    {"ex",     T_EX,       0xEB},  /* 71  */
    {"exx",    G_SIMPLE,   0xD9},  /* 72  */
    {"fge",    G_CC,       6   },  /* 73  */
    {"flt",    G_CC,       7   },  /* 74  */
    {"fnz",    G_CC,       0   },  /* 75  */
    {"fz",     G_CC,       1   },  /* 76  */
    {"global", T_GLOBAL,   0   },  /* 77  */
    {"h",      G_REG,      4   },  /* 78  */
    {"halt",   G_SIMPLE,   0x76},  /* 79  */
    {"hl",     G_REG,      0x24},  /* 80  */
    {"i",      G_REG,      0x10},  /* 81  */
    {"im",     T_IM,       0x46},  /* 82  */
    {"in",     T_IN,       0xDB},  /* 83  */
    {"in0",    T_IN0,      0   },  /* 84  */
    {"inc",    G_INCDEC,   4   },  /* 85  */
    {"ind",    G_EDSIMPLE, 0xAA},  /* 86  */
    {"indr",   G_EDSIMPLE, 0xBA},  /* 87  */
    {"ini",    G_EDSIMPLE, 0xA2},  /* 88  */
    {"inir",   G_EDSIMPLE, 0xB2},  /* 89  */
    {"ix",     G_REG,      0xDD},  /* 90  */
    {"iy",     G_REG,      0xFD},  /* 91  */
    {"jp",     T_JP,       0xC3},  /* 92  */
    {"jr",     T_JR,       0x18},  /* 93  */
    {"l",      G_REG,      5   },  /* 94  */
    {"ld",     T_LD,       0x40},  /* 95  */
    {"ldd",    G_EDSIMPLE, 0xA8},  /* 96  */
    {"lddr",   G_EDSIMPLE, 0xB8},  /* 97  */
    {"ldi",    G_EDSIMPLE, 0xA0},  /* 98  */
    {"ldir",   G_EDSIMPLE, 0xB0},  /* 99  */
    {"lge",    G_CC,       2   },  /* 100 */
    {"llt",    G_CC,       3   },  /* 101 */
    {"lnz",    G_CC,       0   },  /* 102 */
    {"lz",     G_CC,       1   },  /* 103 */
    {"m",      G_CC,       7   },  /* 104 */
    {"macro",  T_MACRO,    0   },  /* 105 */
    {"mlt",    T_MLT,      0x4C},  /* 106 */
    {"nc",     G_CC,       2   },  /* 107 */
    {"neg",    G_EDSIMPLE, 0x44},  /* 108 */
    {"no",     G_CC,       4   },  /* 109 */
    {"nop",    G_SIMPLE,   0   },  /* 110 */
    {"nz",     G_CC,       0   },  /* 111 */
    {"o",      G_CC,       5   },  /* 112 */
    {"or",     G_ARITH8,   0xB0},  /* 113 */
    {"org",    T_ORG,      0   },  /* 114 */
    {"otdm",   G_EDSIMPLE, 0x8B},  /* 115 */
    {"otdmr",  G_EDSIMPLE, 0x9B},  /* 116 */
    {"otdr",   G_EDSIMPLE, 0xBB},  /* 117 */
    {"otim",   G_EDSIMPLE, 0x83},  /* 118 */
    {"otimr",  G_EDSIMPLE, 0x93},  /* 119 */
    {"otir",   G_EDSIMPLE, 0xB3},  /* 120 */
    {"out",    T_OUT,      0xD3},  /* 121 */
    {"out0",   T_OUT0,     1   },  /* 122 */
    {"outd",   G_EDSIMPLE, 0xAB},  /* 123 */
    {"outi",   G_EDSIMPLE, 0xA3},  /* 124 */
    {"p",      G_CC,       6   },  /* 125 */
    {"pe",     G_CC,       5   },  /* 126 */
    {"po",     G_CC,       4   },  /* 127 */
    {"pop",    G_PUSHPOP,  0xC1},  /* 128 */
    {"psect",  T_PSECT,    0   },  /* 129 */
    {"push",   G_PUSHPOP,  0xC5},  /* 130 */
    {"r",      G_REG,      0x11},  /* 131 */
    {"res",    G_BIT,      0x80},  /* 132 */
    {"ret",    T_RET,      0xC9},  /* 133 */
    {"reti",   G_EDSIMPLE, 0x4D},  /* 134 */
    {"retn",   G_EDSIMPLE, 0x45},  /* 135 */
    {"rl",     G_ROTATE,   0x10},  /* 136 */
    {"rla",    G_SIMPLE,   0x17},  /* 137 */
    {"rlc",    G_ROTATE,   0   },  /* 138 */
    {"rlca",   G_SIMPLE,   7   },  /* 139 */
    {"rld",    G_EDSIMPLE, 0x6F},  /* 140 */
    {"rr",     G_ROTATE,   0x18},  /* 141 */
    {"rra",    G_SIMPLE,   0x1F},  /* 142 */
    {"rrc",    G_ROTATE,   8   },  /* 143 */
    {"rrca",   G_SIMPLE,   0xF },  /* 144 */
    {"rrd",    G_EDSIMPLE, 0x67},  /* 145 */
    {"rst",    T_RST,      0xC7},  /* 146 */
    {"sbc",    G_ADCSBC,   0x98},  /* 147 */
    {"scf",    G_SIMPLE,   0x37},  /* 148 */
    {"set",    G_BIT,      0xC0},  /* 149 */
    {"sla",    G_ROTATE,   0x20},  /* 150 */
    {"sll",    G_ROTATE,   0x20},  /* 151 */
    {"slp",    G_EDSIMPLE, 0x76},  /* 152 */
    {"sp",     G_REG,      0x26},  /* 153 */
    {"sra",    G_ROTATE,   0x28},  /* 154 */
    {"srl",    G_ROTATE,   0x38},  /* 155 */
    {"sub",    G_ARITH8,   0x90},  /* 156 */
    {"tst",    T_TST,      4   },  /* 157 */
    {"tstio",  T_TSTIO,    0   },  /* 158 */
    {"xor",    G_ARITH8,   0xA8},  /* 159 */
    {"z",      G_CC,       1   },  /* 160 */
};


kwd_t *kwdHashtab[] = {
    &kwd[6],   &kwd[100], NULL,      NULL,     
    &kwd[42],  &kwd[61],  &kwd[127], NULL,     
    &kwd[133], NULL,      NULL,      &kwd[41], 
    NULL,      &kwd[116], &kwd[30],  NULL,     
    &kwd[17],  NULL,      NULL,      &kwd[94], 
    NULL,      NULL,      &kwd[13],  &kwd[48], 
    NULL,      &kwd[36],  NULL,      NULL,     
    NULL,      NULL,      NULL,      &kwd[14], 
    &kwd[44],  &kwd[37],  NULL,      &kwd[63], 
    &kwd[149], NULL,      NULL,      NULL,     
    NULL,      NULL,      NULL,      &kwd[38], 
    NULL,      &kwd[43],  &kwd[101], NULL,     
    NULL,      &kwd[34],  &kwd[136], NULL,     
    &kwd[147], &kwd[135], &kwd[76],  &kwd[123],
    NULL,      NULL,      &kwd[139], NULL,     
    NULL,      &kwd[59],  &kwd[148], &kwd[31], 
    &kwd[102], NULL,      &kwd[62],  NULL,     
    NULL,      NULL,      NULL,      &kwd[82], 
    NULL,      &kwd[54],  NULL,      NULL,     
    &kwd[9],   &kwd[39],  &kwd[106], NULL,     
    &kwd[65],  &kwd[92],  &kwd[125], NULL,     
    &kwd[109], &kwd[90],  &kwd[77],  NULL,     
    NULL,      &kwd[111], &kwd[113], NULL,     
    NULL,      &kwd[80],  NULL,      &kwd[33], 
    &kwd[72],  &kwd[145], NULL,      NULL,     
    NULL,      &kwd[15],  &kwd[110], NULL,     
    NULL,      NULL,      NULL,      NULL,     
    &kwd[85],  &kwd[137], NULL,      &kwd[93], 
    &kwd[131], NULL,      NULL,      NULL,     
    NULL,      NULL,      &kwd[26],  NULL,     
    NULL,      &kwd[159], NULL,      NULL,     
    NULL,      NULL,      NULL,      NULL,     
    NULL,      NULL,      NULL,      NULL,     
    NULL,      &kwd[29],  &kwd[158], NULL,     
    NULL,      NULL,      &kwd[12],  &kwd[3],  
    &kwd[73],  &kwd[134], &kwd[81],  &kwd[141],
    &kwd[138], &kwd[84],  &kwd[52],  &kwd[35], 
    &kwd[95],  NULL,      &kwd[146], &kwd[156],
    NULL,      NULL,      &kwd[132], &kwd[151],
    &kwd[120], &kwd[150], NULL,      &kwd[66], 
    &kwd[20],  &kwd[67],  NULL,      NULL,     
    &kwd[103], &kwd[128], NULL,      NULL,     
    &kwd[68],  NULL,      &kwd[5],   &kwd[108],
    NULL,      &kwd[119], NULL,      NULL,     
    NULL,      &kwd[47],  &kwd[98],  &kwd[117],
    NULL,      &kwd[64],  &kwd[126], NULL,     
    &kwd[22],  &kwd[74],  NULL,      NULL,     
    NULL,      NULL,      NULL,      NULL,     
    NULL,      &kwd[10],  &kwd[16],  &kwd[40], 
    &kwd[79],  NULL,      NULL,      NULL,     
    &kwd[104], &kwd[7],   &kwd[88],  &kwd[75], 
    NULL,      &kwd[157], NULL,      NULL,     
    &kwd[152], NULL,      NULL,      &kwd[45], 
    &kwd[114], NULL,      NULL,      &kwd[142],
    NULL,      &kwd[18],  NULL,      NULL,     
    NULL,      NULL,      NULL,      &kwd[107],
    NULL,      NULL,      &kwd[53],  &kwd[0],  
    NULL,      NULL,      &kwd[71],  &kwd[112],
    &kwd[23],  NULL,      &kwd[8],   NULL,     
    &kwd[160], &kwd[24],  &kwd[57],  &kwd[99], 
    &kwd[122], &kwd[144], &kwd[60],  &kwd[153],
    &kwd[32],  &kwd[118], &kwd[143], &kwd[89], 
    &kwd[154], NULL,      NULL,      NULL,     
    &kwd[83],  &kwd[155], NULL,      NULL,     
    NULL,      &kwd[91],  &kwd[1],   NULL,     
    NULL,      &kwd[97],  NULL,      &kwd[51], 
    NULL,      &kwd[50],  &kwd[96],  &kwd[115],
    &kwd[25],  &kwd[87],  NULL,      NULL,     
    NULL,      NULL,      NULL,      NULL,     
    NULL,      NULL,      NULL,      NULL,     
    NULL,      &kwd[129], NULL,      NULL,     
    NULL,      &kwd[49],  NULL,      &kwd[56], 
    &kwd[78],  &kwd[2],   &kwd[86],  NULL,     
    NULL,      &kwd[28],  NULL,      NULL,     
    NULL,      NULL,      &kwd[55],  &kwd[27], 
    &kwd[58],  &kwd[121], &kwd[124], NULL,     
    NULL,      NULL,      NULL,      NULL,     
    NULL,      NULL,      NULL,      NULL,     
    &kwd[70],  NULL,      NULL,      NULL,     
    NULL,      NULL,      NULL,      NULL,     
    &kwd[4],   &kwd[21],  &kwd[11],  &kwd[19], 
    NULL,      &kwd[46],  &kwd[69],  &kwd[105],
    &kwd[130], NULL,      &kwd[140],
};


uint8_t invalidChars[] = {
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
    ~0,    ~0x1F, ~0xF,  ~0xF,  ~0xF,  ~7,    ~0xF,  ~0xF,  /* 60-67 */
    ~0x1F, ~0xF,  ~3,    ~0,    ~0x2F, ~0xB,  ~0xF,  ~0x17, /* 68-6F */
    ~7,    ~6,    ~0x1F, ~0xF,  ~0x1F, ~6,    ~0,    ~8,    /* 70-77 */
    ~7,    ~2,    ~0xF,  ~0,    ~0,    ~0,    ~0,    ~0,    /* 78-7F */
};


kwd_t psectKwd[] = {
    {"abs",    G_PSECT, F_ABS   },  /* 0 */
    {"global", G_PSECT, F_GLOBAL},  /* 1 */
    {"local",  G_PSECT, F_LOCAL },  /* 2 */
    {"ovrld",  G_PSECT, F_OVRLD },  /* 3 */
    {"pure",   G_PSECT, F_PURE  },  /* 4 */
    {"reloc",  G_PSECT, F_RELOC },  /* 5 */
    {"size",   G_PSECT, F_SIZE  },  /* 6 */
};


kwd_t *psectHashtab[] = {
    NULL,         &psectKwd[2], &psectKwd[3], &psectKwd[4],
    &psectKwd[6], NULL,         NULL,         NULL,   
    NULL,         NULL,         NULL,         &psectKwd[1],
    &psectKwd[5], NULL,         NULL,         NULL,   
    &psectKwd[0],
};
/* clang-format on */

/**************************************************************************
 64	findKwd	ok++
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
    int probeStep;
    char *name;
    char chBitMask;

    hashIndex = 0;
    probeStep = 1;
    name      = s;
    hashIndex = 0;
    chBitMask = 1; /* this is used as a */
    while (*s) {
        if ((invalidChars[*s & 0x7f] & chBitMask) != 0) /* char not allowed here for valid kwd */
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
 65	findPsect +++
 **************************************************************************/
/* similar hash model to findKwd, but doesn't do the valid char precheck */
static kwd_t *findPsect(register char *s) {
    kwd_t **probe;
    uint16_t hashIndex;
    int probeStep;
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
 66	getTokenId	+++
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
    if (!(po = funptr(buf)))
        return -1;
    yylval.yVal = po->flags;
    return po->id;
}

/**************************************************************************
 67	getKwdId	+++
 **************************************************************************/
int16_t getKwdId(char *p1) {
    return getTokenId(p1, findKwd);
}

/**************************************************************************
 68	getPsectId	+++
 **************************************************************************/
int16_t getPsectId(char *p1) {
    return getTokenId(p1, findPsect);
}
