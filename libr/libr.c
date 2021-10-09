
/*
 * Program to combine multiple object files into one file.
 *
 * File libr3.c Created 18.07.2021 Last Modified 03.08.2021
 *
 * The C source code was RESTORED by disassembling the original executable
 * file LIBR.COM from the Hi-Tech v3.09 compiler.
 *
 * This file with some warning messages is compiled by Hi-Tech C compiler
 * v3.09 and the resulting executable file performs all the functions
 * provided. To compile, use the following command:
 *
 *    cc -o libr3.c
 *
 * The created executable file almost completely matches the original image.
 *
 * Not a commercial goal of this laborious work is to popularize
 * among potential fans of 8-bit computers the old HI-TECH C compiler
 * V3.09 (HI-TECH Software) and extend its life, outside of the
 * CP/M environment (Digital Research, Inc), for full operation in a
 * Unix-like operating system UZI-180 without using the CP/M emulator.
 *
 *	Andrey Nikitin 03.08.2021
 */

#include "libr.h"
#if CPM
#include "stdio.h"
#include <sys.h>
#else
#include <stdio.h>
#define index   strchr
#endif

#include <ctype.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

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

/*
 *	These definitions are not present in the header files of the compiler.
 */
#if CPM
#define SEEK_SET 0 /* from beginning of file */
#define SEEK_CUR 1 /* from current position */
#define SEEK_END 2 /* from end of file */
#endif

/*
 *	Used macros
 */
#define bittst(var, bitno) ((var)&1 << (bitno))

/*
 *	Initialized variables
 */
char arry_4204[] = "D?C???U";
int width        = 80;      // Output width		word_4256
char arry_4258[] = "rdxms"; // Program Keys
char msg_425e[] =
    "Usage: libr [-w][-pwidth] key [subkeys symbol] file.lib [modules ...]";
char arry_42f0[] = { 0 };
char order32[]   = { 0, 1, 2, 3 }; // 4358
uchar order16[]  = { 0, 1 };       // 435c

/*
 *	Descriptions of uninitialized variables and arrays
 */
int num_ofiles;   // Number of object files		word_4745
char **word_4747; //
char *word_4749;  // Pointer to an area of size num_ofiles
int *word_474b;   // Pointer to an area of size num_ofiles * 2
int word_474d;
int num_modules; // Number of modules in library file	word_474f
char byte_4751;
int word_4752; //
long long_4754;
char *fname_4758; // filename
int word_475a;
int word_475c;
char byte_475e;
int word_475f;
FILE *fptr_4761; // file pointer
long long_4763;
char buff_4767[512];
FILE *fptr_4967; // file pointer
char buff_4969[512];
long long_4b69;
FILE *fptr_4b6d; // file pointer
int word_4b6f;
uchar byte_4b71;
uchar byte_4b72;
uchar byte_4b73;
char *word_4b74; //
char byte_4b76;
int word_4b77;
int word_4b79;
char ban_warn; // byte_4b7b
int err_num;   // word_4b7c
int word_4b7e;
char byte_4b80;
char buff_4b81[512];
uchar recd_type; // byte_4d81
int length;      // word_4d82

struct aaa {
    char *i1;
    uchar i2;
};

struct aaa *word_4d84; // ptr to struct aaa
long long_4d86;
char byte_4d8a;
FILE *fptr_4d8b; // file pointer
struct aaa word_4d8d[500];
char *fname_5369; // file name

/****************************************************************
 * Prototype functions are located in sequence of being in
 * original binary image of LIBR.COM
 *
 * ok++ - Full binary compatibility with code in original file;
 * ok   - Code generated during compilation differs slightly,
 *        but is logically correct;
 ****************************************************************/

int sub_013dh(char *, char *); //  1 ok++   |  sub_12d4h Delete, Extract and
                               //  List modules with symbols
void sub_01cch(int, char **);  //  2 ok++   |  sub_0a93h Replace modules
uchar sub_01fbh(char *);       //  3 ok++   |  sub_09cdh Replace modules
// void	sub_025bh( void (*fun)(char *, uint) );	//  4 ok++ <-+
void sub_02b3h(char *, long); //* 5 ok++
void sub_02cch(char *, long); //* 6 ok++
void sub_02e5h();             //  7 ok++ 		Delete modules
void sub_0317h(char *, long); //* 8 ok++
void sub_0337h();             //  9 ok++ 		Extract modules
void sub_034ah();             // 10 ok++   |  sub_02b3h Delete modules
int sub_0366h(char *, uint, uint,
              FILE *);  // 11 ok++   |  sub_02cch Delete modules
void sub_03c7h();       // 12 ok++   |  sub_0317h Extract modules
void sub_03dah(char *); // 13 ok++   |  sub_0d7ch List modules
void sub_0487h();       // 14 ok++   |  sub_0ec1h List modules with symbols
void sub_04d6h();       // 15 ok++   |  sub_16e8h Replace modules
void sub_053ch();       // 16 ok++   |  sub_1721h Replace modules
void sub_0621h(void (*funptr)(char *, long)); // 17 ok++ <-+
// void	sub_0727h(void (*funptr)(char *, int));	// 18 ok++ <-+  sub_0d22h
void sub_0789h();                      // 19 ok++   |  sub_0e48h
void sub_0874h();                      // 20 ok++
void sub_0912h(char *);                // 21 ok++
void sub_09cdh(char *, uint);          // 22 ok++
void sub_0a93h(char *, uint);          // 23 ok++
void conv_ltoa(unsigned long, char *); // 24 ok++ sub_0bd5h
void conv_itoa(uint, char *);          // 25 ok++ sub_0c31h
uint conv_atoi(uchar *);               // 26 ok++ sub_0c53h
long conv_atol(uchar *);               // 27 ok++ sub_0c73h
void sub_0cb3h(char *);                // 28 ok++
void sub_0ce7h(char *);                // 29 ok++
void unexp_eof();               // 30 ok++ sub_0d14h 	Unexpected end of file
void sub_0d22h(char *, int);    //%31 ok++
void sub_0d7ch(char *, long);   //*32 ok++
void sub_0df2h(char *, char *); // 33 ok++ 		List modules
void sub_0e48h(char *, int);    //%34 ok++
void sub_0ec1h(char *, long);   //*35 ok++
void sub_0f0dh();               // 36 ok++ 		List modules with symbols
//	main();					// 37 ok+- 		Main program
void fatal_err();             // 38 ok++ sub_117ch 	Fatal error
void err_open(char *);        // 39 ok++ sub_11c4h 	Error open file
void err_seek(char *);        // 40 ok++ sub_11e5h 	Seek error
void simpl_err();             // 41 ok++ sub_1206h 	Simple error
void warning();               // 42 ok++ sub_124dh 	Warning message
void bf_format();             // 43 ok++ sub_1294h 	Bad file format
void sub_12d4h(char *, uint); //*44 ok++ 		Module not found
void sub_12e8h(int);          // 45 ok++
void sub_12fbh(int);          // 46 ok++
char *allocmem(int);          // 47 ok++ sub_1304h
void sub_1351h();             // 48 ok
int calc_val(uchar *);        // 49 ok++ sub_1429h
void sub_1457h(uchar *, int); // 50 ok++
int sub_14aeh(char *);        // 51 ok
int conv_atoi1(char *);       // 52 ok++ sub_1548h
void sub_1568h();             // 53 ok++		Get type of record
void sub_15fbh();             // 54 ok++
void sub_162ah();             // 55 ok++
void sub_16e8h(char *, long); //*56 ok++
void sub_1721h(char *, long); //*57 ok++
void sub_175ah();             // 58 ok++ 		Replace modules

//	_getargs()				// 59			From library

int sub_2355h(char *, uint, uint, FILE *); //    ok++
int read1(char *, int, unsigned, FILE *);  //

#if CPM
char *strrchr(char *, int);
int fputc(int c, FILE *stream);
int fgetc(FILE *stream);
int fseek(FILE *stream, long offs, int wh);
int unlink(char *name);
char *index(char *s, char c);
#endif

void (*func_42e1[])() = {
    sub_175ah, // Replace modules
    sub_02e5h, // Delete modules
    sub_0337h, // Extract modules
    sub_0df2h, // List modules
    sub_0f0dh  // List modules with symbols
};

/**************************************************************************
 1	sub_013dh	ok++	String comparison
 **************************************************************************/
int sub_013dh(register char *st, char *p2) {
    char l1, l2;

    while (*st != 0) {
        l1 = isupper(*st) ? 0x20 + *st : *st;
        l2 = isupper(*p2) ? 0x20 + *p2 : *p2;
        if (l1 != l2)
            break;
        ++st;
        ++p2;
    }
    return *st - *p2;
}

/**************************************************************************
 2	sub_01cch	ok++
 **************************************************************************/
void sub_01cch(int p1, char **p2) {

    word_4747 = p2;
    if ((num_ofiles = p1) != 0) {
        word_4749 = allocmem(num_ofiles);
        word_474b = (int *)allocmem(num_ofiles * 2);
    }
}

/**************************************************************************
 3	sub_01fbh	ok++
 **************************************************************************/
uchar sub_01fbh(char *p1) {
    char l1;

    if (num_ofiles == 0)
        return 1;
    l1 = num_ofiles;
    do {
        if (l1-- == 0)
            return 0;
    } while (sub_013dh(word_4747[l1], p1) != 0);

    word_4749[l1] = 1;
    return l1 + 1;
}

/**************************************************************************
 4	sub_025bh	ok++
 **************************************************************************/
void sub_025bh(void (*fun)(char *, uint)) {
    int l1;

    l1 = 0;
    while (l1 != num_ofiles) {
        if (word_4749[l1] == 0)
            fun(word_4747[l1], l1);
        ++l1;
    }
}

/**************************************************************************
 5	sub_02b3h	ok++
 **************************************************************************/
void sub_02b3h(char *p1, long dummy) {

    if (sub_01fbh(p1) == 0)
        sub_0789h();
}

/**************************************************************************
 6	sub_02cch	ok++
 **************************************************************************/
void sub_02cch(char *p1, long dummy) {

    if (sub_01fbh(p1) == 0)
        sub_0874h();
}

/**************************************************************************
 7	sub_02e5h	Delete modules		ok++
 **************************************************************************/
void sub_02e5h() {

    if (num_ofiles == 0)
        fatal_err("delete what ?");
    sub_0487h();
    sub_034ah();
    sub_0621h(sub_02b3h);
    sub_025bh(sub_12d4h); // Module not found
    sub_04d6h();
    sub_0621h(sub_02cch);
    sub_053ch();
}

/**************************************************************************
 8	sub_0317h	ok++
 **************************************************************************/
void sub_0317h(char *p1, long dummy) {

    if (sub_01fbh(p1) != 0)
        sub_0912h(p1);
}

/**************************************************************************
 9	sub_0337h	Extract modules		ok++
 **************************************************************************/
void sub_0337h() {

    sub_0487h();
    sub_0621h(sub_0317h);
    sub_025bh(sub_12d4h); // Module not found
}

/**************************************************************************
 10	sub_034ah	ok++
 **************************************************************************/
void sub_034ah() {

    if ((fptr_4967 = fopen("libtmp.$$$", "wb")) == 0) {
        err_open("libtmp.$$$");
    }
}

/**************************************************************************
 11	sub_0366h	ok++
 **************************************************************************/
int sub_0366h(char *p1, uint p2, uint p3, FILE *p4) {

    if ((p2 = sub_2355h(p1, p2, p3, p4)) != p3) {
        fatal_err("Write error on %s file",
                  (p4 == fptr_4967) ? "temp" : "output");
    }
    return p2;
}

/**************************************************************************
 12	sub_03c7hh	ok++
 **************************************************************************/
void sub_03c7h() {

    if (fptr_4967 != 0) {
        fclose(fptr_4967);
        unlink("libtmp.$$$");
    }
}

/**************************************************************************
 13	sub_03dah	ok++
 **************************************************************************/
void sub_03dah(char *p1) {
    register char *st;

    fname_4758 = p1;
    fptr_4761  = fopen(fname_4758, "rb");

    if (fptr_4761 == 0) {
        if (word_4b7e != 0)
            err_open(fname_4758);

        st = strrchr(fname_4758, '.');

        if (st == 0 || (strcmp(st, ".lib") && strcmp(st, ".LIB")))
            warning("library file names should have .lib extension: %s",
                    fname_4758);

        word_4752   = 0;
        num_modules = 0;
        return;
    }

    if (read1(buff_4969, 4, 1, fptr_4761) != 1)
        unexp_eof();

    word_4752 = conv_atoi(buff_4969);

    //  Get the number of modules in a library file
    num_modules = conv_atoi(buff_4969 + 2);
}

/**************************************************************************
 14	sub_0487h	ok++
 **************************************************************************/
void sub_0487h() {

    if (fptr_4761 == 0)
        return;
    if ((fptr_4b6d = fopen(fname_4758, "rb")) != 0) {
        if (fseek(fptr_4b6d, ((long)word_4752 + 4), SEEK_SET) != -1)
            return;
    }
    err_open(fname_4758);
}

/**************************************************************************
 15	sub_04d6h	ok++
 **************************************************************************/
void sub_04d6h() {

    if (err_num != 0)
        sub_12e8h(5);
    if (fptr_4761 == 0)
        return;
    if (fseek(fptr_4761, 4, SEEK_SET) != -1) {
        if (fseek(fptr_4b6d, ((long)word_4752 + 4), SEEK_SET) != -1)
            return;
    }
    err_seek(fname_4758);
}

/**************************************************************************
 16	sub_053ch	ok++
 **************************************************************************/
void sub_053ch() {
    int l1, l2;

    fclose(fptr_4967);
    if (fptr_4761 != 0) {
        fclose(fptr_4761);
        fclose(fptr_4b6d);
    }
    if ((fptr_4967 = fopen("libtmp.$$$", "rb")) == 0)
        err_open("libtmp.$$$");
    if ((fptr_4761 = fopen(fname_4758, "wb")) == 0)
        err_open(fname_4758);

    conv_itoa(word_475c, buff_4969);
    conv_itoa(word_475a, buff_4969 + 2);

    sub_0366h(buff_4969, 1, 4, fptr_4761);

    l2 = 4;
    while ((l1 = read1(buff_4969, 1, 0x200, fptr_4967)) != 0) {
        sub_0366h(buff_4969, 1, l1, fptr_4761);
        l2 += l1;
    }
    fclose(fptr_4761);
}

/**************************************************************************
 17	sub_0621h	ok++
 **************************************************************************/
void sub_0621h(void (*funptr)(char *, long)) {
    int loc;

    loc = num_modules;
    while (loc != 0) {
        if (read1(buff_4969, 12, 1, fptr_4761) != 1)
            unexp_eof();

        word_4b6f = conv_atoi(buff_4969);     // +0 Offset in the read buffer
        word_475f = conv_atoi(buff_4969 + 2); // +2
        long_4763 = conv_atol(buff_4969 + 4); // +4
        long_4b69 = conv_atol(buff_4969 + 8); // +8

        sub_0cb3h(buff_4969 + 12);

        byte_475e = byte_4751 = 0;

        funptr(buff_4969 + 12, long_4b69);

        if (byte_475e == 0) {
            if (fseek(fptr_4761, word_4b6f, SEEK_CUR) == -1)
                err_seek(fname_4758);
        }

        if (fptr_4b6d != 0) {
            if (byte_4751 == 0) {
                if (fseek(fptr_4b6d, long_4763, SEEK_CUR) == -1)
                    err_seek(fname_4758);
            }
        }
        --loc;
    }
}

/**************************************************************************
 18	sub_0727	ok++
 **************************************************************************/
void sub_0727h(void (*funptr)(char *, int)) {
    int l1;
    int l2;

    l1 = word_475f;
    while (l1 != 0) {
        if ((l2 = fgetc(fptr_4761)) == -1)
            unexp_eof();
        sub_0cb3h(buff_4767);
        funptr(buff_4767, l2);
        --l1;
    }
    byte_475e = 1;
}

/**************************************************************************
 19	sub_0789h	ok++
 **************************************************************************/
void sub_0789h() {
    int l1, l2;

    sub_0366h(buff_4969, 1, (l1 = strlen(buff_4969 + 12) + 0xD), fptr_4967);
    word_474d += l1;
    word_475c += (l1 + word_4b6f);
    l1 = word_4b6f;
    while (l1 != 0) {
        l2 = (l1 < 0x200) ? l1 : 0x200;
        if (read1(buff_4767, 1, l2, fptr_4761) != l2)
            unexp_eof();
        sub_0366h(buff_4767, 1, l2, fptr_4967);
        word_474d += l2;
        l1 -= l2;
    }
    ++word_475a;
    byte_475e = 1;
}

/**************************************************************************
 20	sub_0874h	ok++
 **************************************************************************/
void sub_0874h() {
    int l1, l2;

    l1 = long_4763;
    while (l1 != 0) {
        l2 = (l1 < 0x200) ? l1 : 0x200;
        if (read1(buff_4767, 1, l2, fptr_4b6d) != l2)
            unexp_eof();
        sub_0366h(buff_4767, 1, l2, fptr_4967);
        word_474d += l2;
        l1 -= l2;
    }
    byte_4751 = 1;
}

/**************************************************************************
 21	sub_0912h	ok++
 **************************************************************************/
void sub_0912h(char *p1) {
    int l1, l2;
    register FILE *st;

    if ((st = fopen(p1, "wb")) == 0)
        err_open(p1);
    l1 = long_4763;
    while (l1 != 0) {
        l2 = (l1 < 0x200) ? l1 : 0x200;
        if (read1(buff_4767, 1, l2, fptr_4b6d) != l2)
            unexp_eof();
        sub_0366h(buff_4767, 1, l2, st);
        l1 -= l2;
    }
    fclose(st);
    byte_4751 = 1;
}

/**************************************************************************
 22	sub_09cdh	ok++	used when replacing modules
 **************************************************************************/
void sub_09cdh(char *p1, uint p2) {
    unsigned int l1, l2, l3;
    register FILE *st;

    if ((st = fopen(p1, "rb")) == 0)
        err_open(p1);
    l3 = 0;
    l1 = word_474b[p2];

    while ((l2 = read1(buff_4767, 1, (0x200 < l1) ? 0x200 : l1, st)) != 0) {
        sub_0366h(buff_4767, 1, l2, fptr_4967);
        l3 += l2;
        word_474d += l2;
        l1 -= l2;
    }
    fclose(st);
}

/**************************************************************************
 23	sub_0a93h	ok++	used when replacing modules
 **************************************************************************/
void sub_0a93h(char *p1, uint p2) {
    int l1, l2, l3;
    register struct aaa *st;

    word_474b[p2] = (l1 = sub_14aeh(p1));

    l3            = (word_4d84 - word_4d8d);
    l2            = l3 * 2;

    for (st = word_4d8d; st != word_4d84; ++st) {
        l2 += strlen(st->i1);
    }

    word_475c += (strlen(p1) + l2 + 0xD);
    conv_itoa(l2, buff_4969);
    conv_itoa(l3, buff_4969 + 2);
    conv_ltoa((unsigned long)l1, buff_4969 + 4);
    conv_ltoa(long_4754, buff_4969 + 8);
    sub_0366h(buff_4969, 1, 0xC, fptr_4967);
    word_474d += 0xC;
    sub_0ce7h(p1);

    for (st = word_4d8d; st != word_4d84; ++st) {
        fputc(st->i2, fptr_4967);
        ++word_474d;
        sub_0ce7h(st->i1);
    }
    ++word_475a;
}

/**************************************************************************
 24	conv_ltoa	sub_0bd5h	ok++
 **************************************************************************/
void conv_ltoa(unsigned long p1, char *p2) {

    *p2       = p1;
    *(p2 + 1) = p1 >> 8;
    *(p2 + 2) = p1 >> 0x10;
    *(p2 + 3) = p1 >> 0x18;
}

/**************************************************************************
 25	conv_itoa	sub_0c31h	ok++
 **************************************************************************/
void conv_itoa(uint p1, char *p2) {

    *p2       = p1;
    *(p2 + 1) = p1 >> 8;
}

/**************************************************************************
 26	conv_atoi	sub_0c53h	ok++
 **************************************************************************/
uint conv_atoi(register uchar *p1) {

    return *p1 + (*(p1 + 1) << 8);
}

/**************************************************************************
 27	conv_atol	sub_0c73h	ok++
 **************************************************************************/
long conv_atol(register uchar *p1) {

    return *p1 + (*(p1 + 1) << 8) + (*(p1 + 2) << 0x10) + (*(p1 + 3) << 0x18);
}

/**************************************************************************
 28	sub_0cb3h	ok++
 **************************************************************************/
void sub_0cb3h(register char *p1) {
    int l1;

    do {
        if ((l1 = fgetc(fptr_4761)) == -1)
            unexp_eof();
        *(p1++) = l1;
    } while (l1 != 0);
}

/**************************************************************************
 29	sub_0ce7h	ok++
 **************************************************************************/
void sub_0ce7h(register char *p1) {

    do {
        ++word_474d;
    } while (fputc(*(p1++), fptr_4967) != 0);
}

/**************************************************************************
 30	unexp_eof	sub_0d14h	ok++
 **************************************************************************/
void unexp_eof() {

    bf_format(fname_4758, "unexpected end of file");
}

/**************************************************************************
 31	sub_0d22h	ok++
 **************************************************************************/
void sub_0d22h(char *p1, int p2) {

    if ((((char)p2 == 0) ? byte_4b72 : byte_4b73) == 0)
        return;
    if (strcmp(word_4b74, p1) != 0) {
        if (*p1 != '_')
            return;
        if (strcmp(word_4b74, p1 + 1) != 0)
            return;
    }
    byte_4b76 = 1;
    byte_4b71 = p2;
}

/**************************************************************************
 32	sub_0d7ch	Print obj name from library	ok++
 **************************************************************************/
void sub_0d7ch(char *p1, long dummy) {

    if (sub_01fbh(p1) == 0)
        return;
    if (word_4b74 != 0) {
        byte_4b76 = 0;
        sub_0727h(sub_0d22h);
        if (byte_4b76 == 0)
            return;
    }
    printf("%-15.15s", p1);
    if (word_4b74 != 0)
        printf(" %c", (byte_4b71 >= 7) ? 0x3f : arry_4204[byte_4b71]);
    putchar('\n');
}

/**************************************************************************
 33	sub_0df2h	List modules	ok++
 **************************************************************************/
void sub_0df2h(char *p1, char *p2) {

    if (*p1 != 0) {
        word_4b74 = p2;
        do {
            switch (*p1) {
            case 'd':
                byte_4b72 = 1;
                break;
            case 'u':
                byte_4b73 = 1;
                break;
            default:
                fatal_err("Subkeys: d(defined) u(ndefined)");
            }
        } while (*(++p1) != 0);
    }
    sub_0621h(sub_0d7ch); // Print name obj name from library with the key m
}

/**************************************************************************
 34	sub_0e48h	ok++	Print symbol name with the key s
 **************************************************************************/
void sub_0e48h(char *p1, int p2) {

    if (word_4b79 >= word_4b77) {
        printf("\t\t");
        word_4b79 = 0;
    }
    printf("%c %-12.12s", ((p2 >= 7) ? '?' : arry_4204[p2]), p1);
    if (++word_4b79 >= word_4b77) {
        printf("\n");
        return;
    }
    printf("  ");
}

/**************************************************************************
 35	sub_0ec1h	ok+	Print obj name and symbol names
 **************************************************************************/
void sub_0ec1h(char *p1, long dummy) {

    if (sub_01fbh(p1) == 0)
        return;
    printf("%-16.15s", p1); // Print obj name from library with the key s
    word_4b79 = 0;
    sub_0727h(sub_0e48h); // Print symbol name with the key s
    if (word_4b79 == 0)
        return;
    if (word_4b79 >= word_4b77)
        return;
    putchar('\n');
}

/**************************************************************************
 36	sub_0f0dh	List modules with symbols	ok++
 **************************************************************************/
void sub_0f0dh() {

    if ((word_4b77 = (width - 16) / 16) == 0)
        word_4b77 = 1;
    sub_0621h(sub_0ec1h); // Print obj name and symbol names
    sub_025bh(sub_12d4h); // Module not found
}

/**************************************************************************
 37	main	sub_0f38h	ok+
 **************************************************************************/
int main(argc, argv) int argc;
char **argv;
{
    char *l1;
    char *l2;

    if (argc == 2 && strcasecmp(argv[1], "-v") == 0) {
        showVersion(stdout, argv[1][1] == 'V');
        exit(0);
    }

#if CPM
    if (signal(SIGINT, SIG_IGN) != SIG_IGN)
        signal(SIGINT, sub_12fbh);

    if (argc == 1) {
        argv = _getargs(0, "libr");
        argc = _argc_;
    }
#endif

    fclose(stdin);
    --argc;
    ++argv;
    goto m5; // The code above this line generates a binary code
//----------------------// that fully corresponds to the original image.
m3:
    l1 = *argv + 1; //

m4:
    if (*l1 != 0)
        goto m6;
    --argc;
    ++argv;

m5:
    if (argc == 0)
        goto m11;
    goto m10;

    //  Libr options

m6:
    switch (*l1++) {
    case 'W': // Suppress non-fatal errors
    case 'w':
        goto m8;
    case 'P': // Specify page width
    case 'p':
        goto m9;
    default:
        goto m7;
    }
m7:
    fatal_err(msg_425e); // "Usage: ...]"
    goto m4;

m8:
    ban_warn = 1; // Disable warning messages
    goto m4;

m9:
    if (isdigit(*l1) == 0)
        goto m7;
    width = atoi(l1);  // Assigning a new width value
    l1    = arry_42f0; // This is an empty string ("")
    goto m4;

m10:
    if (**argv == '-')
        goto m3;

    //----------------- The code below this line generates the correct binary
    // code.

m11:
    if (argc < 2)
        fatal_err(msg_425e); // "Usage: ...]"
    l2 = *argv;
    --argc;
    ++argv;
    if ((l1 = index(arry_4258, ((isupper(*l2) != 0) ? *l2 + ' ' : *l2))) == 0)
        fatal_err(
            "Keys: r(eplace), d(elete), (e)x(tract), m(odules), s(ymbols)");

    word_4b7e = l1 - arry_4258;

    if (*(l2 + 1) != 0) {
        l1 = *argv;
        --argc;
        ++argv;
    }
    if (argc == 0)
        fatal_err(msg_425e); // "Usage: ...]"

    sub_03dah(*argv);
    sub_01cch(argc - 1, argv + 1);

    (func_42e1[word_4b7e])(l2 + 1,
                           l1); // Execute a function depending on the key

    sub_12e8h(err_num !=
              0); // Terminate the program with the appropriate error code
}

/**************************************************************************
 38	fatal_err	sub_117ch	ok++
 **************************************************************************/
void fatal_err(p1, p2, p3, p4, p5) {

    fprintf(stderr, (char *)p1, p2, p3, p4, p5);
    fputc('\n', stderr);
    sub_12e8h(6);
}

/**************************************************************************
 39	err_open	sub_11c4h	ok++
 **************************************************************************/
void err_open(char *p1) {

    fprintf(stderr, "Can't open %s\n", p1);
    sub_12e8h(2);
}

/**************************************************************************
 40	err_seek	sub_11e5h	ok++
 **************************************************************************/
void err_seek(char *p1) {

    fprintf(stderr, "Seek error on %s\n", p1);
    sub_12e8h(3);
}

/**************************************************************************
 41	Simple error	sub_1206h	ok++
 **************************************************************************/
void simpl_err(p1, p2, p3, p4, p5) {

    fprintf(stderr, (char *)p1, p2, p3, p4, p5);
    fputc('\n', stderr);
    ++err_num;
}

/**************************************************************************
 42	warning		sub_124dh	ok++
 **************************************************************************/
void warning(p1, p2, p3, p4, p5) {

    if (ban_warn != 0)
        return;
    fprintf(stderr, (char *)p1, p2, p3, p4, p5);
    fprintf(stderr, " (warning)\n");
}

/**************************************************************************
 43	bf_format		sub_1294h	ok++
 **************************************************************************/
void bf_format(p1, p2, p3, p4, p5, p6) char *p1;
{

    fprintf(stderr, "bad file format: %s\n", p1);
    fatal_err(p2, p3, p4, p5, p6);
}

/**************************************************************************
 44	sub_12d4h	ok++	module not found
 **************************************************************************/
void sub_12d4h(char *p1, uint p2) {

    simpl_err("no such module: %s", p1);
}

/**************************************************************************
 45	sub_12e8h	ok++
 **************************************************************************/
void sub_12e8h(int p1) {

    sub_03c7h();
    exit(p1);
}

/**************************************************************************
 46	sub_12fbh	ok++
 **************************************************************************/
void sub_12fbh(int p1) {

    sub_12e8h(4);
}

/**************************************************************************
 47	allocmem	sub_1304h	ok
 **************************************************************************/
char *allocmem(int p1) {
    char *l1;
    register char *st;

    if ((l1 = malloc(p1)) == 0)
        fatal_err("Cannot get memory");

    st = l1;
    while (p1-- != 0) { // Clearing area
        *st = 0;
        ++st;
    }
    return l1;
}

/**************************************************************************
 48	sub_1351h	ok
 **************************************************************************/
void sub_1351h() {
    uchar l1;

    if (read1(buff_4b81, 1, length, fptr_4d8b) != length)
        bf_format(fname_5369, "incomplete ident record");

    l1 = 0;
    if (byte_4b80 != 0) {

        while (l1 < 4) {
            if (buff_4b81[l1] != order32[l1])
                bf_format("ident records do not match");
            l1++;
        }
        l1 = 0;
        while (l1 < 2) {
            if ((char)(buff_4b81 + 4)[l1] != (char)order16[l1])
                bf_format("ident records do not match");
            l1++;
        }
        return;
    }
    while (l1 < 4) {
        order32[l1] = buff_4b81[l1];
        l1++;
    }
    l1 = 0;
    while (l1 < 2) {
        order16[l1] = (buff_4b81 + 4)[l1];
        l1++;
    }
    byte_4b80 = 1;
}

/**************************************************************************
 49	calc_val	sub_1429h	ok++
 **************************************************************************/
int calc_val(uchar *p1) {

    return (uint)(*((uint)order16[1] + p1) << 8) +
           (uint) * ((uint)order16[0] + p1);
}

/**************************************************************************
 50	sub_1457h	ok+
 **************************************************************************/

void sub_1457h(uchar *p1, int p2) {
    register struct aaa *st;

    if (word_4d84 == word_4d8d + 501)
        fatal_err("Too many symbols in %s", fname_5369);
    st = word_4d84;
    if ((st->i2 = p2) != 6)
        byte_4d8a = 1;
    strcpy((word_4d84->i1 = allocmem(strlen((char *)p1) + 1)), (char *)p1);

    ++word_4d84;
}

// Object file record types: | Length (16 bits)     | Record type (8 bits) |
// Data (Length*8 bits) |
#define TEXT_RECORD  1
#define PSECT_RECORD 2
#define RELOC_RECORD 3
#define SYM_RECORD                                                             \
    4 // | Value (32 bits)      | flags (16 bits)      | psect name           |
      // symbol name |
#define START_RECORD 5
#define END_RECORD   6 // | flags (16 bits)      |
#define IDENT_RECORD                                                           \
    7 // | byte order (32 bits) | byte order (16 bits) | machine name         |
      // version number (16 bits) |
#define XPSECT_RECORD  8
#define SEGMENT_RECORD 9

/**************************************************************************
 51	sub_14aeh	ok+
 **************************************************************************/
int sub_14aeh(char *p1) {

    fptr_4d8b = fopen((fname_5369 = p1), "rb");
    if (fptr_4d8b == 0)
        err_open(fname_5369);
    byte_4d8a = 0;
    long_4d86 = 0;
    word_4d84 = &word_4d8d;

//    for(;;) {		Failed attempt to use switch
m2:
    sub_1568h(); // Get type of record

    if (recd_type == SYM_RECORD)
        goto m3;
    if (recd_type == END_RECORD)
        goto m5;
    if (recd_type == IDENT_RECORD)
        goto m4;
    sub_15fbh();
    goto m2;

m3:
    sub_162ah(); // SYM_RECORD
    goto m2;

m4:
    sub_1351h(); // IDENT_RECORD
    goto m2;

m5:
    fclose(fptr_4d8b); // END_RECORD

    if ((ulong)long_4d86 >= (ulong)0x00010000)
        fatal_err("file too big");
    if (byte_4d8a == 0)
        warning("module %s defines no symbols", fname_5369);
    return long_4d86;
    /*
        switch(recd_type) {
          case IDENT_RECORD:	sub_1351h(); break; //goto m2;
          case SYM_RECORD:	sub_162ah(); break; //goto m2;
          default:		sub_15fbh(); break; //goto m2;
          case END_RECORD:	fclose(fptr_4d8b);
                    if((ulong)long_4d86 >= (ulong)0x00010000) fatal_err("file
       too big"); if(byte_4d8a == 0) warning("module %s defines no symbols",
       fname_5369); return long_4d86;
        }
        }
    */
}

/**************************************************************************
 52	conv_atoi1	sub_1548h	ok++
 **************************************************************************/
int conv_atoi1(register char *st) {

    return (((uint)(*st)) + ((uint) * (st + 1) << 8));
}

/**************************************************************************
 53	sub_1568h	ok++	Get type of record
 **************************************************************************/
void sub_1568h() {

    if (read1(buff_4b81, 3, 1, fptr_4d8b) != 1)
        bf_format(fname_5369, "no end record found");

    recd_type = buff_4b81[2];

    if (recd_type == 0)
        goto m2;
    if (recd_type < 9)
        goto m3;

m2:
    bf_format(fname_5369, "unknown record type: %d", (uint)recd_type);
//	509 = 512-3
m3:
    if (0x01FD < (length = conv_atoi1(buff_4b81)))
        bf_format(fname_5369, "record too long: %d+%d", 3, length);

    long_4d86 += (length + 3);
}

/**************************************************************************
 54	sub_15fbh	ok++
 **************************************************************************/
void sub_15fbh() {

    if (fseek(fptr_4d8b, length, SEEK_CUR) != -1)
        return;
    bf_format(fname_5369, "incomplete record");
}

/**************************************************************************
 55	sub_162ah	ok++
 **************************************************************************/
void sub_162ah() {
    char *l1;
    int l2;
    char l3;
    register char *st;

    if (read1(buff_4b81, 1, length, fptr_4d8b) != length)
        bf_format(fname_5369, "incomplete symbol record");

    st = buff_4b81;

    while (st < (buff_4b81 + length)) { // m8:
        l2 = calc_val(st + 4);          // m2:
        l3 = l2 & 0xF;
        l1 = st + 6;

        while (*(l1++) != 0)
            ;

        if (bittst(l2, 4) != 0) {
            if (l3 == 0)
                goto m5;
        }
        if (l3 == 2)
            goto m5; // m4:
        if (l3 == 6) {
        m5:
            sub_1457h((uchar *)l1, (uchar)l3);
        }
        st = l1; // m6:

        while (*(st++) != 0)
            ;
    }
}

/**************************************************************************
 56	sub_16e8h	ok++
 **************************************************************************/
void sub_16e8h(char *p1, long dummy) {

    if (sub_01fbh(p1) != 0) {
        sub_0a93h(p1, sub_01fbh(p1) - 1);
        return;
    }
    sub_0789h();
}

/**************************************************************************
 57	sub_1721h	ok++
 **************************************************************************/
void sub_1721h(char *p1, long dummy) {

    if (sub_01fbh(p1) != 0) {
        sub_09cdh(p1, sub_01fbh(p1) - 1);
        return;
    }
    sub_0874h();
}

/**************************************************************************
 58	sub_175ah	Replace modules		ok++
 **************************************************************************/
void sub_175ah() {

    if (num_ofiles == 0)
        fatal_err("replace what ?");
    sub_0487h();
    sub_034ah();
    sub_0621h(sub_16e8h);
    sub_025bh(sub_0a93h);
    sub_04d6h();
    sub_0621h(sub_1721h);
    sub_025bh(sub_09cdh);
    sub_053ch();
}

/**************************************************************************
 *	sub_2355h	ok++
 **************************************************************************/
int sub_2355h(char *p1, uint p2, uint p3, FILE *p4) {
    int l1;
    char *l2;
    register FILE *st;

    st = p4;
    l1 = p2 * p3;
    l2 = p1;

    while (l1 != 0) {
        if (fputc(*(l2++), st) == -1)
            break;
        l1 += -1;
    }
    return p3 - (l1 + p2 - 1) / p2;
}

void sub_23e4() { // Not used function
    fgetc(stdin);
}

/**************************************************************************
    read1	ok++
 **************************************************************************/
int read1(char *buf, int p2, unsigned count, register FILE *st) {
    char *ptr_buf;
    unsigned int tot_count;
    unsigned int next_char;

    tot_count = p2 * count;
    ptr_buf   = buf;

    while (tot_count != 0) {
        if ((next_char = fgetc(st)) == EOF)
            break;
        --tot_count;
        *ptr_buf++ = (char)next_char;
    }
    return count - (tot_count + p2 - 1) / p2;
}
