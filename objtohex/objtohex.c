#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
#include <io.h>
#else
#include <fcntl.h>
#include <unistd.h>
#endif
#include "showVersion.h"

uint8_t order32[4] = { 0, 1, 2, 3 };
uint8_t order16[2] = { 0, 1 };

struct {
    char *name;
    long val;
} marker[]         = { { "__Htext", 0 },  { "__Hdata", 0 },  { "__Hbss", 0 },  { "__Ldata", 0 },
               { "__Hstack", 0 }, { "__Bstack", 0 }, { "__Bdata", 0 }, { "__H_TEXT", 0 } };

char *objFile      = "l.com";
char *hexFile      = "l.hex";
char *relocSegName = "__Lbss";
char relocTmp[]    = "reloc.$$$";
char sym1[]        = "sym1.$$$";
char sym2[]        = "sym2.$$$";
char swap[]        = "swap.$$$";
/* accessors for above */
#define Htext  marker[0].val
#define Hdata  marker[1].val
#define Hbss   marker[2].val
#define Ldata  marker[3].val
#define Hstack marker[4].val
#define Bstack marker[5].val
#define Bdata  marker[6].val
#define H_text marker[7].val

uint8_t b6039[9];
long dw6042;
bool blkLoaded[256];
bool sOpt;

struct {
    unsigned int addr1;
    unsigned int addr2;
    unsigned int where1;
    unsigned int where2;
    unsigned int offset;
} chkSumList[64];

bool b63C7;
long dw63C8;
bool mOpt;
uint32_t _Htext;
FILE *symFp;
bool lOpt;
bool b63D4;
char *progname;
bool aOpt;
int16_t w63D8;
FILE *relocFp;
uint8_t w63DC[28];
char *w63F8;
uint8_t *blkBuf[256];
uint16_t extSegment;
long imageOffset;
uint32_t _Ltext;
bool hOpt;
uint8_t b6605[128 - 9 - 9];
bool binaryImage;
int16_t w6674;
bool iOpt;
bool cOpt;
uint8_t r6678[10];
long startAddr;
bool hasOffset;
uint8_t recType;
uint16_t recLen;
long dw668A;
int16_t nreloc;
bool pOpt;
uint8_t b6691[9];
long wrPos;
long maxStack;
uint8_t recData[512 - 3];
int16_t chkIdx;
uint8_t b68A1[32];
int16_t swapFd;
bool hasReloc;
bool eOpt;
FILE *sym2Fp;
bool rOpt;
uint8_t exeHdr[512];

int main(int argc, char **argv);
void sub_DB2(void);
void doFile(void);
long sub_10DB(void);
void sub_1503(void);
void sub_1621(void);
void loadBlk(int16_t blkNum);
void u32tob(uint8_t *buf, long n);
void i16tob(uint8_t *buf, uint16_t n);
void outHex2(uint16_t n);
void outHex4(uint16_t n);
void doStart(void);
void doSym(void);
void doReloc(void);
void putMem(uint8_t *buf, uint32_t loc, uint16_t len);
void doIdent(void);
void doText(void);
void readRec(void);
int16_t btoi16(uint8_t *buf);
uint32_t btou32(uint8_t *buf);
void rmWorkFiles(void);
_Noreturn void fatalErr(const char *fmt, ...);
void parseChecksumList(void);
int sub_2636(const void *p1, const void *p2);
void sub_2692(void);
void sub_2AD1(void);
bool parseAddr(char *buf, long *pVal);
void *xalloc(size_t size);
int geti16le(FILE *);
int puti16le(int w, FILE *stream);

int main(int argc, char **argv) {
    int16_t offset;
    int16_t blkIdx;
    long remaining;
    uint16_t cnt;
    uint16_t crc;
    long curAddr;
    char *wrMode;

    CHK_SHOW_VERSION(argc, argv);

    progname = "objto";
    swapFd   = -1;
    wrMode   = "w";
    for (; argc > 1 && argv[1][0] == '-'; argc--, argv++) {
        switch (argv[1][1]) {
        case 'm':
        case 'M':
            mOpt = true;
            break;
        case 'e':
        case 'E':
            eOpt = true;
            if (argv[1][2]) {
                if (parseAddr(argv[1] + 2, &remaining))
                    fatalErr("Bad arg to -b");
                else
                    maxStack = remaining;
            }
            wrMode = "wb";
            break;
        case '8':
            b63D4 = true;
            eOpt  = true;
            if (argv[1][2]) {
                if (parseAddr(argv[1] + 2, &remaining))
                    fatalErr("Bad arg to -b");
                else
                    maxStack = remaining;
            }
            wrMode = "wb";
            break;
        case 'a':
        case 'A':
            aOpt   = true;
            wrMode = "wb";
            break;
        case 'b':
        case 'B':
            binaryImage = true;
            wrMode      = "wb";
            hexFile     = "l.com";
            if (argv[1][2]) {
                if (parseAddr(argv[1] + 2, &imageOffset))
                    fatalErr("Bad arg to -b");
                else
                    hasOffset = true;
            }
            break;
        case 'l':
        case 'L':
            lOpt = true;
            /* FALLTHRU */
        case 'r':
        case 'R':
            rOpt = true;
            if (argv[1][2])
                relocSegName = argv[1] + 2;
            break;
        case 's':
        case 'S':
            if (pOpt)
                sOpt = true;
            else if (!argv[1][2])
                fprintf(stderr, "Missing file name after %s\n", argv[1]);
            else
                w63F8 = argv[1] + 2;
            break;
        case 'i':
        case 'I':
            iOpt = true;
            break;
        case 'h':
        case 'H':
            hOpt = true;
            break;
        case 'c':
        case 'C':
            cOpt = true;
            break;
        case 'p':
        case 'P':
            pOpt = true;
            if (argv[1][2]) {
                if (parseAddr(argv[1] + 2, &remaining))
                    fatalErr("Bad arg to -b");
                else
                    maxStack = remaining;
            }
            wrMode = "wb";
            break;
        default:
            fprintf(stderr, "Unrecognized switch %c\n", argv[1][2]);
            fatalErr("Usage: objtohex [-ssymfile] [object-file [hex-file]]");
            break;
        }
    }

    if (argc > 1) {
        objFile = argv[1];
        if (argc > 2) {
            hexFile = argv[2];
            if (argc > 3)
                fatalErr("Usage: objtohex [-ssymfile] [object-file [hex-file]]");
        }
    }
    if (pOpt && rOpt)
        lOpt = true;

    if ((w63F8 && (iOpt || aOpt || pOpt)) || ((aOpt || pOpt) && (iOpt || hOpt || eOpt)) ||
        (aOpt && pOpt))
        fatalErr("Bad combination of flags");
    if (aOpt || (pOpt && sOpt)) {
        w63F8 = sym1;
        w63D8 = 2;
        if (!(sym2Fp = fopen(sym2, "wb")))
            fatalErr("cannot open %s", sym2);
    }
    if (pOpt)
        w63F8 = 0;
    if (cOpt)
        parseChecksumList();
    if (w63F8 && !(symFp = fopen(w63F8, "w")))
        fatalErr("cannot open %s", w63F8);
    if (!(freopen(objFile, "rb", stdin)))
        fatalErr("Cannot open %s", objFile);
    if (!freopen(hexFile, wrMode, stdout))
        fatalErr("Cannot open %s", hexFile);
    if (hOpt)
        printf("\"Z80\"\n");
    if (rOpt && !(relocFp = fopen(relocTmp, "wb")))
        fatalErr("Cannot open %s", relocTmp);
    startAddr = _Ltext = 0x3ffff;
    doFile();
    if (!pOpt)
        sub_2692();
    sub_2AD1();
    if (startAddr == 0x3ffff)
        startAddr = _Ltext;
    blkIdx    = _Ltext >> 10;
    offset    = _Ltext & 0x3ff;
    remaining = _Htext - _Ltext;
    curAddr   = _Ltext;
    if (Htext < H_text)
        Htext = H_text;
    if (aOpt) {
        if (curAddr != 0)
            fatalErr("Text does not start at 0");
        binaryImage = true;
        sub_1621();
        imageOffset = -32;
    } else if (eOpt) {
        binaryImage = true;
        if (curAddr != 0)
            fatalErr("Text does not start at 0");
        imageOffset = sub_10DB();
    } else if (pOpt) {
        if (curAddr != 0)
            fatalErr("Text does not start at 0");
        binaryImage = true;
        sub_1503();
        imageOffset = -28;
    } else if (binaryImage && !hasOffset)
        imageOffset = curAddr;
    if (mOpt) {
        cnt = (int16_t)strlen(objFile);
        printf("S0");
        outHex2(crc = cnt + 3);
        outHex4(0);
        wrMode = objFile;
        while (*wrMode) {
            crc += *wrMode;
            outHex2(*wrMode++);
        }
        outHex2(-1 - crc);
        fputc('\n', stdout);
    }
    while (remaining) {
        if (hOpt)
            cnt = 8;
        else if (binaryImage)
            cnt = 1024;
        else
            cnt = 32;

        if (cnt > remaining)
            cnt = (int16_t)remaining;

        if (offset + cnt > 0x400)
            cnt = 0x400 - offset;
        remaining -= cnt;
        if (blkBuf[blkIdx] == NULL) {
            curAddr += cnt;
            if ((offset += cnt) == 0x400) {
                blkIdx++;
                offset = 0;
            }
        } else {
            loadBlk(blkIdx);
            if (hOpt) {
                if (!b63C7) {
                    printf("\tORG\t0");
                    outHex4((uint16_t)curAddr);
                    printf("H\n");
                    b63C7 = true;
                }
                printf("\tHEX\t");
            } else if (binaryImage) {
                if (fseek(stdout, curAddr - imageOffset, 0) < 0 ||
                    fwrite(blkBuf[blkIdx] + offset, 1, cnt, stdout) != cnt) {
                    fprintf(stderr, "Seek value was %ld: ", curAddr - imageOffset);
                    fatalErr("write error on %s", hexFile);
                }
                if ((offset += cnt) == 0x400) {
                    offset = 0;
                    blkIdx++;
                }
                curAddr += cnt;
                continue;
            } else {
                if (mOpt) {
                    if (curAddr >= 0x10000) {
                        printf("S2");
                        outHex2(crc = cnt + 4); /* byte count */
                        outHex4(curAddr >> 16);
                        crc += curAddr >> 16;
                    } else {
                        printf("S1");
                        outHex2((crc = cnt + 3));
                    }
                } else {
                    if (dw63C8 != (curAddr & 0xf0000)) {
                        extSegment = (uint16_t)((dw63C8 = curAddr & 0xf0000) >> 4);
                        fputc(':', stdout);
                        outHex2(crc = 2);
                        outHex4(0);
                        outHex2(2);
                        outHex4(extSegment);
                        crc += ((extSegment >> 8) & 0xff) + (extSegment & 0xff) + 2;
                        outHex2(0 - crc);
                        fputc('\n', stdout);
                    }
                    fputc(':', stdout);
                    outHex2(crc = cnt);
                }
                outHex4((uint16_t)curAddr);
                crc += (uint8_t)(curAddr >> 8) + (uint8_t)curAddr;
                if (!mOpt)
                    printf("00");
            }
            curAddr += cnt;
            while (cnt--) {
                crc += blkBuf[blkIdx][offset];
                outHex2(blkBuf[blkIdx][offset]);
                if (hOpt)
                    fputc(',', stdout);
                if (++offset == 0x400) {
                    blkIdx++;
                    offset = 0;
                }
            }
            if (!hOpt) {
                if (mOpt)
                    outHex2(~crc);
                else
                    outHex2(0 - crc);
            }
            fputc('\n', stdout);
        }
    }
    if (hOpt) {
        printf("\tEND\t0");
        outHex4((uint16_t)startAddr);
        fputc('H', stdout);
    } else if (!binaryImage) {
        if (mOpt) {
            printf("S903");
            outHex4((uint16_t)startAddr);
            outHex2((uint8_t)(~((startAddr >> 8) + startAddr + 3)));
        } else {
            printf(":00");
            outHex4((uint16_t)startAddr);
            printf("01");
            outHex2((uint8_t)(0 - ((startAddr >> 8) + startAddr + 3)));
        }
    }

    for (blkIdx = 0; blkIdx != 0x100; blkIdx++)
        if (blkLoaded[blkIdx])
            free(blkBuf[blkIdx]);
    sub_DB2();
    if (pOpt && nreloc)
        sub_2692();
    if (!binaryImage)
        fputc('\n', stdout);

    rmWorkFiles();
    if (fclose(stdout) == EOF) {
        fprintf(stderr, "Error closing output file\n");
        exit(1);
    }
    exit(0);
}

void sub_DB2() {
    uint16_t remaining;
    uint16_t blkSize;
    char buf[512];

    if (aOpt) {
        fclose(sym2Fp);
        if (!freopen(sym2, "r", stdin))
            fatalErr("Cannot open %s");
        /* note original code cast the two addresses below to (long *)
         * to pick up the value. However had been written using
         * u32tob. For the same endian file format this ok but
         * here btou32 is used to ensure compatibility
         */
        fseek(stdout, btou32(b68A1 + 8) + btou32(b68A1 + 4) + 32, 0);
        for (remaining = w6674 * 10; remaining; remaining -= blkSize) {
            if ((blkSize = 512) > remaining)
                blkSize = remaining;
            if ((uint16_t)fread(buf, 1, blkSize, stdin) != blkSize)
                fatalErr("Read error on %s", sym2);
            if (fwrite(buf, 1, blkSize, stdout) != blkSize)
                fatalErr("Write error on %s", hexFile);
        }
        puti16le(w63D8, stdout);
        if (!freopen(sym1, "r", stdin))
            fatalErr("Cannot open %s", sym1);

        while ((blkSize = (uint16_t)fread(buf, 1, 512, stdin)) > 0)
            if (fwrite(buf, 1, blkSize, stdout) != blkSize)
                fatalErr("Write error on %s", hexFile);
        fclose(stdin);
    }
    if (!pOpt || w6674 == 0 || !sOpt)
        return;

    fclose(sym2Fp);
    if (!freopen(sym2, "rb", stdin))
        fatalErr("Cannot open %s", sym2);
    fseek(stdout, dw6042, 0);
    for (remaining = w6674 * 14; remaining; remaining -= blkSize) {
        blkSize = 512;
        if (blkSize > remaining)
            blkSize = remaining;
        if (fread(buf, 1, blkSize, stdin) != blkSize)
            fatalErr("Read error on %s", sym2);
        if (fwrite(buf, 1, blkSize, stdout) != blkSize)
            fatalErr("Write error on %s", hexFile);
    }
    fclose(stdin);
}

void doFile() {
    do {
        readRec();
        switch (recType) {
        case 1:
            doText();
            break;
        case 5:
            doStart();
            break;
        case 4:
            doSym();
            break;
        case 3:
            doReloc();
            break;
        case 7:
            doIdent();
            break;
        }
    } while (recType != 6);
}

#define O_SIG      0
#define O_LASTSIZE 2
#define O_NBLOCKS  4
#define O_NRELOC   6
#define O_HDRSIZE  8
#define O_MINALLOC 10
#define O_MAXALLOC 12
#define O_SS       14
#define O_SP       16
#define O_IP       20
#define O_RELOCPOS 24

long sub_10DB() {
    long totalSize;
    uint16_t maxa;
    uint16_t mina;
    uint16_t relocSize;
    uint16_t textPara;

    fseek(stdout, 0L, 0);
    i16tob(&exeHdr[O_SIG], 0x5a4d); /* MZ */
    i16tob(&exeHdr[O_NRELOC], hasReloc ? nreloc : 0);
    if (maxStack == 0)
        maxStack = 0x10000;
    else
        maxStack += Hbss;
    if (maxStack >= 0x100000)
        maxStack = 0xffff0;
    maxa = (uint16_t)(((maxStack - Hdata + 0xf) >> 4) + 2);
    i16tob(&exeHdr[O_MAXALLOC], maxa);
    mina = (uint16_t)(((Hbss - Hdata) + 0x1000) / 16);
    if (mina > maxa)
        mina = maxa;
    i16tob(&exeHdr[O_MINALLOC], mina);
    if (b63D4) {
        if (Bstack != 0) {
            b6691[0] = 1;
            textPara = (_Htext + 0xf) >> 4;
            i16tob(b6691 + 1, textPara);
            i16tob(b6691 + 5, textPara + mina);
            i16tob(b6691 + 7, textPara + maxa);
            b6039[0] = 2;
            i16tob(b6039 + 1, 16);
            i16tob(b6039 + 5, 16);
            i16tob(b6039 + 7, 16);
        } else {
            b6691[0] = 1;
            textPara = (uint16_t)((Bdata + 0xf) / 16);
            i16tob(b6691 + 1, textPara);
            i16tob(b6691 + 5, textPara);
            i16tob(b6691 + 7, textPara);
            b6039[0] = 2;
            textPara = (uint16_t)((_Htext - Bdata + 0xf) >> 4);
            i16tob(b6039 + 1, textPara);
            i16tob(b6039 + 5, textPara + mina);
            i16tob(b6039 + 7, textPara + maxa);
        }

        fwrite(b6691, 9, 1, stdout);
        fwrite(b6039, 9, 1, stdout);
        fwrite(b6605, 0x6e, 1, stdout);
        return -128L;
    }
    if (Bstack != 0) {
        i16tob(&exeHdr[O_SP], (uint16_t)Hstack); /* note original pushed a long */
        i16tob(&exeHdr[O_SS], (uint16_t)(Bstack >> 4));
    } else {
        i16tob(&exeHdr[O_SP], (int16_t)(Hbss + 0x800)); /* note original pushed a long */
        i16tob(&exeHdr[O_SS], (int16_t)(Bdata >> 4));
    }
    i16tob(&exeHdr[O_IP], (int16_t)startAddr);
    if (hasReloc)
        i16tob(&exeHdr[O_RELOCPOS], 32);
    if (hasReloc)
        relocSize = (((nreloc + 3L) >> 2) + 2) >> 4;
    else
        relocSize = 32;
    if (relocSize > 0x100)
        relocSize = 0x100;

    i16tob(&exeHdr[O_HDRSIZE], relocSize / 16);
    totalSize = Htext + relocSize;
    i16tob(&exeHdr[O_NBLOCKS], (int16_t)((totalSize + 0x1ff) >> 9));
    i16tob(&exeHdr[O_LASTSIZE], totalSize & 0x1ff);
    fwrite(&exeHdr, 1, 32, stdout);
    return -relocSize;
}

void sub_1503() {
    if (_Ltext != 0)
        fatalErr("Text does not start at 0");
    if (maxStack != 0) {
        loadBlk(0);
        u32tob(blkBuf[0] + 2, maxStack);
    }
    i16tob(w63DC, 0x601a);
    u32tob(w63DC + 2, Htext);
    u32tob(w63DC + 6, Hdata - Ldata);
    if (Hbss == 0 && Hdata != 0)
        Hbss = Hdata;
    u32tob(w63DC + 10, Hdata - Hbss);
    u32tob(w63DC + 14, w6674 * 14);
    fwrite(w63DC, 0x1c, 1, stdout);
    dw6042 = Hdata + 0x1c;
    wrPos = dw6042 + w6674 * 14;
}

void sub_1621() {
    i16tob(b68A1, 0x109);
    i16tob(b68A1 + 2,
           (int16_t)Ldata); /* note bug in original code, was u32tob but over written below */
                            /* also w5A7B was not passed as long */
    u32tob(b68A1 + 16, w6674 * 10L);
    u32tob(b68A1 + 20, startAddr);
    u32tob(b68A1 + 4, (Htext + 0xf) & ~0xf);
    u32tob(b68A1 + 8, (Hdata - Ldata + 0xf) & ~0xf);
    u32tob(b68A1 + 12, Hbss - Hdata);
    fwrite(b68A1, 32, 1, stdout);
}

void loadBlk(int16_t blkNum) {
    uint8_t *buf = NULL;
    int16_t i;

    if (blkBuf[blkNum] && blkLoaded[blkNum])
        return;

    if (blkBuf[blkNum] == 0 && (buf = calloc(1, 0x400)) == NULL) {
        i = 0;
        while ((buf = blkBuf[i]) == NULL || blkLoaded[i] == 0)
            if (++i == 0x100)
                fatalErr("Out of memory");
        if (swapFd == -1) {
            close(creat(swap, 0x180));
            if ((swapFd = open(swap, 2)) < 0)
                fatalErr("Cannot open %s", swap);
        }
        if (lseek(swapFd, (long)blkNum << 10, 0) == -1 || write(swapFd, buf, 0x400) != 0x400)
            fatalErr("Write error on %s", swap);

        blkLoaded[i] = 0;
        memset(buf, 0, 0x400); /* replaced bmove */
        if (blkBuf[blkNum])
            if (lseek(swapFd, (long)blkNum << 10, 0) == -1 || read(swapFd, buf, 0x400) != 0x400)
                fatalErr("Read error on %s", swap);
    }
    blkBuf[blkNum]    = buf;
    blkLoaded[blkNum] = 1;
}

void u32tob(uint8_t *buf, long n) {
    buf[order32[0]] = (uint8_t)n;
    buf[order32[1]] = (uint8_t)(n >> 8);
    buf[order32[2]] = (uint8_t)(n >> 16);
    buf[order32[3]] = (uint8_t)(n >> 24);
}

void i16tob(uint8_t *buf, uint16_t n) {
    buf[order16[0]] = n % 256;
    buf[order16[1]] = n / 256;
}

void i16tole(char *buf, uint16_t n) {
    buf[0] = (char)n;
    buf[1] = n >> 8;
}

int16_t letoi16(uint8_t *buf) {
    return buf[0] + buf[1] * 256;
}

void outHex2(uint16_t n) {
    static char digits[] = "0123456789ABCDEF";

    fputc(digits[(n >> 4) & 0xf], stdout);
    fputc(digits[n & 0xf], stdout);
}

void outHex4(uint16_t n) {
    outHex2(n >> 8);
    outHex2(n);
}

void doStart() {
    startAddr = btou32(recData);
}

void doSym() {
    uint8_t *pname;
    int16_t var4;
    uint16_t flags;
    uint32_t value;
    long varE;
    char ch;
    uint8_t *var11;
    int16_t crc;
    uint8_t symEntry[14];
    uint16_t var23;
    register uint8_t *p;

    if (!w63F8 && !rOpt && !iOpt && !aOpt && !eOpt && (!pOpt || !!sOpt))
        return;
    p = recData;
    while (recLen) {
        value = btou32(p);
        flags = btoi16(p + 4);
        varE  = value;
        if (w63F8 && !iOpt && !aOpt)
            fprintf(symFp, "%04lx", varE);
        p += 6;
        pname = p;
        recLen -= 6;
        do {
            recLen--;
        } while (*p++);
        if (rOpt && strcmp(relocSegName, (char *)p) == 0)
            wrPos = varE;
        for (var4 = 0; var4 < 8; var4++)
            if (strcmp(marker[var4].name, (char *)p) == 0)
                marker[var4].val = varE;
        if (iOpt) {
            if (hOpt) {
                printf("%s\tEQU\t0", p);
                do {
                    recLen--;
                } while (*p++);
                outHex4((int16_t)varE);
                printf("H\n");
            } else {
                var11 = p;
                do {
                    recLen--;
                } while ((ch = *p++));
                fputc(':', stdout);
                crc = (int16_t)(p - var11 - 1);
                outHex2(crc);
                crc += ((varE >> 8) & 0xff) + (varE & 0xff) + 2;
                outHex2(2);
                while (*var11) {
                    outHex2(*var11);
                    crc += *var11++;
                }
                outHex2(-crc);
                fputc('\n', stdout);
            }
        } else if (aOpt) {
            *(int16_t *)r6678 = w63D8;
            w63D8 += (int16_t)strlen((char *)p) + 1;
            fwrite(p, 1, strlen((char *)p), symFp);
            recLen -= (int16_t)strlen((char *)p) + 1;
            p += strlen((char *)p) + 1;
            *((uint32_t *)&r6678[6]) = value;
            switch (*pname) {
            case '_':
            case 't':
                r6678[2] = 4;
                break;
            case 'd':
                r6678[2] = 6;
                break;
            case 'b':
                r6678[2] = 8;
                break;
            case 0:
                r6678[2] = !(flags & 6) ? 2 : 0;
                break;
            default:
                r6678[2] = 0x12;
                break;
            }
            if (flags & 0x10)
                r6678[2] |= 1;
            w6674++;
            if (fwrite(r6678, 10, 1, sym2Fp) != 1)
                fatalErr("Write error on %s", sym2);

        } else if (pOpt && sOpt) {
            u32tob(symEntry + 10, varE);
            switch (*pname) {
            case '_':
            case 't':
                var23 = 0xa200;
                break;
            case 'd':
                var23 = 0xa400;
                break;
            case 'b':
                var23 = 0xa100;
                break;
            }
            i16tob(symEntry + 8, var23);
            memset(symEntry, 0, 8); /* replaced bmove */
            strncpy((char *)symEntry, (char *)p, 8);
            recLen -= (int16_t)strlen((char *)p) + 1;
            p += strlen((char *)p) + 1;
            w6674++;
            if (fwrite(symEntry, 14, 1, sym2Fp) != 1)
                fatalErr("Write error on %s", sym2);
        } else if (w63F8) {
            while ((ch = *p++)) {
                fputc(ch, symFp);
                recLen--;
            }
            recLen--;
            fputc('\n', symFp);
        } else {
            do {
                recLen--;
            } while (*p++);
        }
    }
}

void doReloc() {
    int16_t var2;
    register uint8_t *iy = recData;
    static char notAbs[] = "object file is not absolute";

    while (recLen) {
        var2 = btoi16(iy);
        if (!lOpt && dw668A + var2 > 0xfffe)
            fatalErr("Image too big");
        iy += 2;
        if (pOpt) {
            if (*iy++ != 4)
                fatalErr(notAbs);
        } else if (lOpt) {
            if (*iy++ != 0x82)
                fatalErr(notAbs);
        } else if (*iy++ != 2)
            fatalErr(notAbs);
        recLen -= 3;
        do {
            recLen--;
        } while (*iy++);
        if (rOpt)
            puti16le(var2 + dw668A, relocFp);

        if (lOpt || pOpt)
            puti16le((dw668A + var2) >> 0x16, relocFp);
        nreloc++;
        if (nreloc == 0)
            fatalErr("Too many relocaton items");
    }
}

void putMem(uint8_t *buf, uint32_t loc, uint16_t len) {
    uint16_t n;
    uint16_t blkNum;

    if (loc < _Ltext)
        _Ltext = loc;
    if (loc + len > 0x40000)
        fatalErr("Image too big");
    if (loc + len > _Htext)
        _Htext = loc + len;
    while (len) {
        blkNum = loc >> 10;
        if (((loc + len - 1) >> 10) == blkNum)
            n = len;
        else
            n = 0x400 - (loc & 0x3ff);
        loadBlk(blkNum);
        memcpy(blkBuf[blkNum] + (loc & 0x3ff), buf, n); /* modified from bmove */
        loc += n;
        buf += n;
        len -= n;
    }
}

void doIdent() {
    uint8_t i;
    for (i = 0; i < 4; i++)
        order32[i] = recData[i];
    for (i = 0; i < 2; i++)
        order16[i] = recData[i + 4];
}

void doText() {
    uint32_t offset;
    int16_t len;
    int16_t doffset;

    dw668A = offset = btou32(recData);
    if (offset < _Ltext)
        _Ltext = offset;
    doffset = (int16_t)strlen((char *)recData + 4) + 5;
    len     = recLen - doffset;
    if (len != 0) {
        if (offset + len > _Htext)
            _Htext = offset + len;
        if (offset + len > 0x40000)
            fatalErr("Image too big");
        if (len)
            putMem(recData + doffset, offset, len);
    }
}

void readRec() {
    uint8_t hdr[3];

    if (fread(hdr, 3, 1, stdin) != 1)
        fatalErr("No end record");

    recType = hdr[2];
    if (recType == 0 || recType >= 9)
        fatalErr("Illegal record type");
    recLen = (hdr[1] << 8) + hdr[0];
    if (fread(recData, 1, recLen, stdin) != recLen)
        fatalErr("incomplete record");
}

int16_t btoi16(uint8_t *buf) {
    return buf[order16[1]] * 256 + buf[order16[0]];
}

uint32_t btou32(uint8_t *buf) {
    uint32_t val;
    int16_t i;

    i   = 4;
    val = 0L;
    while (i--)
        val += buf[order32[i]] << (i * 8);
    return val;
}

void rmWorkFiles() {
    if (rOpt)
        unlink(relocTmp);
    if (swapFd >= 0) {
        close(swapFd);
        unlink(swap);
    }

    if (pOpt || aOpt) {
        unlink(sym2);
        unlink(sym1);
    }
}

void fatalErr(const char *fmt, ...) {
    fprintf(stderr, "%s: ", progname);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);
    rmWorkFiles();
    exit(1);
}

void parseChecksumList() {
    unsigned int addr1;
    unsigned int addr2;
    unsigned int where1;
    unsigned int where2;
    unsigned int offset;
    int c;

    for (;;) {
        offset = 0;
        for (;;) {
            do {
                c = fgetc(stdin);
            } while (isspace(c));

            if (c == '/' && fgetc(stdin) == '*') {
                for (;;) {
                    if (fgetc(stdin) == '*') {
                        if ((c = fgetc(stdin)) == '/')
                            break;
                        else
                            ungetc(c, stdin);
                    }
                }
            } else
                break;
        }
        if (c == EOF)
            break;
        else {
            ungetc(c, stdin);
            c = scanf("%x -%x%x -%x +%x", &addr1, &addr2, &where1, &where2, &offset);
            if (c < 3)
                break;
            if (c == 3)
                where2 = where1;
            chkSumList[chkIdx].addr1    = addr1;
            chkSumList[chkIdx].addr2    = addr2;
            chkSumList[chkIdx].where1   = where1;
            chkSumList[chkIdx].where2   = where2;
            chkSumList[chkIdx++].offset = offset;
        }
    }
    if (c != EOF)
        fatalErr("Syntax error in checksum list");
    return;
}

int sub_2636(const void *p1, const void *p2) {
    if (*(uint32_t *)p1 == *(uint32_t *)p2)
        return 0;
    if (*(uint32_t *)p1 < *(uint32_t *)p2)
        return -1;
    return 1;
}

void sub_2692() {
    uint8_t var4[4];
    uint16_t var6;
    int16_t var8;
    long varC;
    long var10;
    long *var12;
    int16_t var14;
    int16_t var16;

    if (!rOpt)
        return;
    hasReloc = wrPos == 0 && lOpt && strcmp(relocSegName, "Dos_hdr") == 0;
    if (hasReloc)
        wrPos = 32;

    if (freopen(relocTmp, "rb", relocFp) != relocFp)
        fatalErr("Cannot open %s", relocTmp);

    var8 = nreloc;
    if (hasReloc) {
        fseek(stdout, wrPos, 0);
        while (var8--) {
            var6  = geti16le(relocFp);
            var16 = var6 & 0xf;
            var14 = geti16le(relocFp);
            var14 <<= 12;
            var14 += var6 << 4;
            fwrite(&var16, 2, 1, stdout);
            fwrite(&var14, 2, 1, stdout);
        }
        fclose(relocFp);
    } else if (pOpt) {
        if ((var12 = malloc(nreloc * sizeof(uint32_t))) == NULL)
            fatalErr("Out of memory");
        while (var8--) {
            varC = (uint32_t)geti16le(relocFp);
            varC += geti16le(relocFp) << 16;
            var12[var8] = varC;
        }
        fclose(relocFp);
        qsort(var12, nreloc, sizeof(uint32_t), sub_2636);
        fseek(stdout, wrPos, 0);
        var6 = 4;
        varC = var12[0];
        u32tob(var4, varC);
        fwrite(var4, sizeof(uint32_t), 1, stdout);
        var8 = 1;
        for (var8 = 1; var8 != nreloc; var6++, var8++) {
            var10 = varC;
            varC  = var12[var8];
            while (varC - var10 > 0xfe) {
                fputc(1, stdout);
                var6++;
                var10 += 0xfe;
            }
            fputc(varC - var10, stdout);
        }
        fputc(0, stdout);
        if (++var6 & 1)
            fputc(0, stdout);
    } else {
        var4[0] = (uint8_t)nreloc; /* low byte */
        var4[1] = nreloc >> 8;
        putMem(var4, wrPos, 2);
        while (var8--) {
            var6    = geti16le(relocFp);
            var4[0] = (uint8_t)var6; /* low byte */
            var4[1] = var6 >> 8;
            putMem(var4, wrPos += 2, 2);
            if (lOpt) {
                var6    = geti16le(relocFp);
                var6    = geti16le(relocFp);
                var4[0] = (uint8_t)var6;
                var4[1] = var6 >> 8;
                putMem(var4, wrPos += 2, 2);
            }
        }
    }
    fclose(relocFp);
}

/* the original code here has a flaw which propogates from the parseCheckSumList
 * in the original code crc, loc and the addrX, whereX and offset are all 16 bit
 * whilest the address locations are ok for 8/16 bit targets the crc and ideally
 * offset should be 32bits otherwise writing a 32 bit CRC gives an incorrect
 * value
 * Additionally the code to calculate loc + order[crcSize] falls triggers a Hi-Tech
 * code generation bug leading to the order[crcSize] always being 0.
 */
void sub_2AD1() {
    uint16_t loc;
    uint16_t crc;
    int16_t i;
    uint16_t crcSize;
    uint16_t blkNum;
    uint8_t crc8;
    uint8_t *order;

    for (i = 0; i < chkIdx; i++) {
        loc = chkSumList[i].addr1;
        if (loc < _Ltext)
            _Ltext = loc;
        crc = chkSumList[i].offset; /* initialize crc */
        if (chkSumList[i].addr2 > _Htext)
            _Htext = chkSumList[i].addr2;

        while (loc <= chkSumList[i].addr2) {
            loadBlk((blkNum = loc >> 10));
            crc += blkBuf[blkNum][loc++ & 0x3ff];
        }
        fprintf(stderr, "Checksum %04x at %04x\n", crc, loc = chkSumList[i].where1);
        crcSize = 0;
        if ((crcSize = chkSumList[i].where2 - loc + 1) != 4 && crcSize != 2 && crcSize != 1)
            fatalErr("Bad checksum specification");
        order   = crcSize == 4 ? order32 : order16;
        crcSize = 0;
        do {
            crc8 = (uint8_t)crc;
            crc >>= 8;
            putMem(&crc8, (uint32_t)loc + order[crcSize], 1);
        } while ((unsigned int)(loc + ++crcSize) <= chkSumList[i].where2);
    }
}

bool parseAddr(char *buf, long *pVal) {
    char ch;
    char *s;
    char *first;
    uint8_t base;
    long val;

    first = s = buf;
    if (!isxdigit(*s))
        return true;
    s++;
    while (isxdigit(*s))
        s++;
    buf = s;
    switch (*s) {
    case 'O':
    case 'Q':
    case 'o':
    case 'q':
        base = 8;
        break;
    case 'H':
    case 'h':
        base = 16;
        break;
    default:
        buf--;
        if (s[-1] == 'D' || s[-1] == 'd') {
            base = 10;
            s--;
        } else
            base = 10;
        break;
    }
    val = 0;
    for (val = 0; s != first; first++) {
        ch = *first;
        if ((base == 8 && ch > '7') || (base == 10 && ch > '9'))
            return true;
        val = val * base + (uint8_t)ch;
        val -= isdigit(ch) ? '0' : islower(ch) ? 'a' - 10 : 'A' - 10;
    }
    *pVal = val;
    return false;
}

void *xalloc(size_t size) {
    register char *ptr;

    if ((ptr = malloc(size)) == NULL)
        fatalErr("Cannot get memory");
    memset(ptr, 0, size); /* replaced blkclr */
    return ptr;
}

int geti16le(FILE *fp) {
    uint8_t buf[2];
    if (fread(buf, sizeof(buf), 1, fp) != 1)
        return EOF;
    return buf[0] + buf[1] * 256;
}

int puti16le(int w, FILE *fp) {
    if (putc(w & 0xFF, fp) == EOF || putc((w >> 8) & 0xFF, fp) == EOF)
        return (EOF);
    return (w);
}