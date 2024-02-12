/*
 * Program for displaying information about object files HI-TECH C compiler
 *
 * File dump.c Created 31.05.2021 Last Modified 06.06.2021
 *
 * The C source code was RESTORED by disassembling the original executable
 * file DUMP.COM from the Hi-Tech v1.3 compiler delivery package.
 *
 * Not a commercial goal of this laborious work is to popularize
 * among potential fans of 8-bit computers the old HI-TECH C compiler
 * V3.09 (HI-TECH Software) and extend its life, outside of the
 * CP/M environment (Digital Research, Inc), for full operation in a
 * Unix-like operating system UZI-180 without using the CP/M emulator.
 *
 *	Andrey Nikitin 06.06.2021
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#if !defined(_STDC_VERSION__) || __STDC_VERSION < 201112L
#define _Noreturn
#endif
#if defined(_MSC_VER) && !defined(__STDC__)
#define __STDC__ 1
#endif

#ifdef __STDC__
#include <stdarg.h>
#endif

#include "showVersion.h"

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
 *	Used macros
 */
#define BITTST(var, bitno) ((var)&1 << (bitno))
#define ARRAY_SIZE(x)      (sizeof(x) / sizeof((x)[0]))

/****************************************************************
 * Prototype functions are located in sequence of being in
 * original binary image of DUMP.COM
 *
 * ok++ - Full binary compatibility with code in original file;
 * ok   - Code generated during compilation differs slightly,
 *        but is logically correct;
 ****************************************************************/
#ifdef __STDC__
#define P(s) s
#else
#define P(s) ()
#endif
int main P((int argc, char **argv)); /* ok++ works good */
void cod_xpsect P((void));           /* ok++ not verified */
void prc_rec P((void));              /* ok++ works good */
int chk_rec P((void));               /* ok   works good */
void cod_text P((void));             /* ok++ works good */
void cod_psect P((void));            /* ok++ works with error */
void cod_reloc P((void));            /* ok++ works good */
void cod_sym P((void));              /* ok++ works good */
void cod_start P((void));            /* ok++ works good */
void cod_end P((void));              /* ok++ works good */
void cod_ident P((void));            /* ok++ works good */
#ifndef __STDC__
void err_handling(); /*  ok++ works good	*/
void error();        /*  ok++ works good	*/
#else
void err_handling(char *fmt, va_list args); /* safer version */
_Noreturn void error(char *fmt, ...);       /* safer version */
#endif
uint calc_val P((uchar * p1));   /*  ok++ works good	*/
ulong calc_long P((uchar * p1)); /*  ok   works good	*/
/*
 * To comply with C standard functions are replaced with
 * similar ones with a variable number of parameters
 */

#if CPM
int strlen();
int fread();
#endif

/*
 *	Structural declarations
 */
struct node {
    char *name;        /* Record type name  		*/
    void (*fun_ptr)(); /* Record processing function	*/
};

/*
 *	Descriptions of variables and arrays
 */
char *name;          /* File name		*/
int cur_rec;         /* current record	*/
uchar rec_typ;       /* Record type		*/
int rec_len;         /* Record length	*/
uchar buf_data[512]; /* Record data buffer	*/

uint8_t order32[] = { 0, 1, 2, 3 }; /* 32 bit order */
uint8_t order16[] = { 0, 1 };       /* 16 bit order */

/*	This version of the program implements the features marked CP/M:

TEXT	  0 "TEXT"		Record types:
PSECT	  1 "PSECT"
RELOC	  2 "RELOC"
SYM	  3 "SYM";
START	  4 "START"
END	  5 "END"	^
IDENT	  6 "IDENT"	|
XPSECT	  7 "XPSECT"	+-- CP/M
SEGMENT   8
XSYM	  9
SIGNAT   10

GLOBAL	  0 "GLOBAL"		Psect flags:
PURE	  1 "PURE"	^
OVRLD	  2 "OVRLD"	|
ABS	  3 "ABS"	+-- CP/M
BIGSEG    4
BASEPAGE  5
BITSEG    6

RABS	  0 "RABS"		Relocation types:
RPSECT	  1 "RPSECT"
RNAME	  2 "RNAME"
Unknown	  3 "Unknown"
RRABS	  4 "Unknown"	^
RRPSECT	  5 "RRPSECT"	|
RRNAME	  6 "RRNAME"	+-- CP/M
Unknown	  7
RSABS	  8
RSPSECT	  9
RSNAME	 10
Unknown	 11
RRSABS	 12
RRSPSECT 13
RRSNAME	 14
Unknown	 15

STACK	  0 "STACK";		Symbol types:
COMM	  1 "COMM";
REG	  2 "REG";
LINENO	  3 "LINENO";	^
FILNAM	  4 "FILNAM";	|
EXTERN	  5 "EXTERN";	+-- CP/M
*/

/*
 *	The sequence of the following variables
 *	does not match the original program
 *
 *	Record types:
 */

struct node rec_types[] = {
    { "", 0 },               /* 0 */
    { "TEXT", cod_text },    /* 1 */
    { "PSECT", cod_psect },  /* 2 */
    { "RELOC", cod_reloc },  /* 3 */
    { "SYM", cod_sym },      /* 4 */
    { "START", cod_start },  /* 5 */
    { "END", cod_end },      /* 6 */
    { "IDENT", cod_ident },  /* 7 */
    { "XPSECT", cod_xpsect } /* 8 */
};

/*
 *	Symbol types:
 */
char *sym_types[] = {
    "",       /* 0 */
    "STACK",  /* 1 */
    "COMM",   /* 2 */
    "REG",    /* 3 */
    "LINENO", /* 4 */
    "FILNAM", /* 5 */
    "EXTERN"  /* 6 */
};

/*
 *	Psect flags:
 */
char *psect_flags[] = {
    "GLOBAL", /* 0 */
    "PURE",   /* 1 */
    "OVRLD",  /* 2 */
    "ABS"     /* 3 */
};

/*
 *	Relocation types:
 */
char *reloc_types[] = {
    "RABS",    /* 0 */
    "RPSECT",  /* 1 */
    "RNAME",   /* 2 */
    "Unknown", /* 3 */
    "Unknown", /* 4 */
    "RRPSECT", /* 5 */
    "RRNAME"   /* 6 */
};

/*
 *	Main program (ok++, works good)
 */
int main(argc, argv) int argc;
char **argv;
{
    char **next_arg;

    CHK_SHOW_VERSION(argc, argv);

    if (argc == 1) {           /* When starting the program without     */
        *(argv + 1) = "l.obj"; /* parameters, process the file "l.obj"  */
        ++argc;
    }
    next_arg = argv + 1;
    while (next_arg < argv + argc) {
        cur_rec = 0;
        if (freopen((name = *next_arg), "rb", stdin) == 0)
            error("cannot open");
        printf("%s\n", name);
        prc_rec(); /* Record processing  */
        ++next_arg;
    }
    exit(0);
}

/*
 *	Processing of records (ok++, works good)
 */
void prc_rec() {
    register struct node *st;

    do {
        if (chk_rec() == 0)
            return;
        st = &rec_types[(uchar)rec_typ];
        printf("\t%d\t%s\n", cur_rec, st->name); /* display number, name and */
        (*st->fun_ptr)();                        /* content of the record    */
    } while (rec_typ != 6);
}

/*
 *	Check record (ok, works good)
 */
int chk_rec() {

    if ((fread(buf_data, 1, 3, stdin)) != 3)
        return (0);
    ++cur_rec;
    rec_len = buf_data[0] + (buf_data[1] << 8);
    rec_typ = buf_data[2];

    if (rec_typ == 0 || rec_typ >= 9) /* original had rec_typ > 9, but this misses 9 as an invalid value */
        error("unknown record type: %d", rec_typ);
    /*
        note the hitech compiler generates bizzare code for the call to error below
        I suspect the original was coded in error as
        error("%s record too long: %d", rec_types[rec_typ], rec_len);
        unfortunately the compiler generates two push bc on the stack for the string
        argument, and instead of generating the code to copy the structure onto the stack
        if actually generates
        rec_types[0] = rec_types[rec_typ];
    */
    if (rec_len > 512)
        error("%s record too long: %d", rec_types[rec_typ].name, rec_len);
    if (fread(buf_data, 1, rec_len, stdin) != rec_len)
        error("incomplete record: type = %d, length = %d", (uchar)rec_typ, rec_len);
    return (1);
}

/*
 *	cod_text (ok++, works good)
 */
void cod_text() {
    long offset;       /* Offset in psect	*/
    int data_bytes;    /* Number of data bytes	*/
    char byte_count;   /* Byte count on line 	*/
    uchar *ptr;        /* Pointer		*/
    uchar *psect_name; /* Psect name		*/

    offset = calc_long(buf_data);
    ptr = psect_name = &buf_data[4];
    while (*ptr != 0)
        ++ptr;
    ptr++;
    data_bytes = rec_len - (5 + (int)strlen((char *)psect_name));

    if (BITTST(data_bytes, 15) != 0)
        error("text record has length too small: %d", data_bytes);
#if CPM
    printf("\t\t%s\t%D\t%d\n", psect_name, offset, data_bytes);
#else
    printf("\t\t%s\t%ld\t%d\n", psect_name, offset, data_bytes);

#endif

    /*
     * Display of contained bytes
     */
    while (data_bytes != 0) {
        printf("\t\t");
        byte_count = 0x15; /* 21 */
        while ((byte_count != 0) && (data_bytes != 0)) {
            printf("%02x ", *(ptr++));
            --byte_count;
            --data_bytes;
        }
        fputc('\n', stdout);
    }
}
/**************************************************************************
 *	cod_psect (ok++)
 **************************************************************************/
void cod_psect() {
    uint l1;
    uchar l2;

    printf("\t\t%s", buf_data[2] != 0 ? (char *)&buf_data[2] : "(abs)");
    l1 = calc_val(buf_data) >> 4;
    l2 = 0;
    while (l1 != 0) {
        if (BITTST(l1, 0) != 0) {
            if (l2 >= ARRAY_SIZE(psect_flags))
                error("unknown psect flag: 0X%x", 1 << l2);
            printf("\t%s", psect_flags[l2]);
        }
        l1 <<= 1;
        ++l2;
    }
    fputc('\n', stdout);
}

/*
 *	cod_reloc (ok++, works good)
 */
void cod_reloc() {
    uchar l1; /* Relocation type */
    uchar *l2;

    l2 = buf_data;
    while (l2 < &buf_data[rec_len]) {
        l1 = (*(l2 + 2) & 0xF0) >> 4;
        if (l1 >= 7)
            error("unknown relocation type: 0X%x0", l1);
        printf("\t\t%d\t%s\t%s\t%d\n", calc_val(l2), reloc_types[l1], l2 + 3, (*(l2 + 2) & 0xF));
        l2 += strlen((char *)l2 + 3) + 4;
    }
}

/*
 *	cod_sym (ok++, works good)
 */
void cod_sym() {
    uchar *l1;
    uchar *l2; /* Psect  name */
    uchar *l3; /* Symbol name */
    uint l4;

    l1 = buf_data;
    while (l1 < &buf_data[rec_len]) {
        l3 = (l2 = l1 + 6);
        while (*l3 != 0)
            ++l3;
        l3++;
        l4 = calc_val(l1 + 4);
#if CPM
        printf("\t\t%s\t%s\t%D", l3, (*l2 != 0) ? l2 : (((l4 & 6) != 0) ? "" : "(abs)"), calc_long(l1));
#else
        printf("\t\t%s\t%s\t%ld", l3, (*l2 != 0) ? (char *)l2 : (((l4 & 6) != 0) ? "" : "(abs)"), calc_long(l1));

#endif

        if (BITTST(l4, 4) != 0)
            printf("\tGLOBAL");

        if ((l4 = l4 & 0xF) >= ARRAY_SIZE(sym_types))
            error("unknown symbol type %d", l4);

        if (*(sym_types + l4) != 0)              /* Added comparison with 0 to	*/
            printf("\t%s\n", *(sym_types + l4)); /* suppress output "(null)"
                                                  */
        else                                     /* when linking with unmodified */
            printf("\n");                        /* standard library		*/

        l1 += strlen((char *)l2) + strlen((char *)l3) + 8;
    }
}

/*
 *	cod_start (ok++, works good)
 */
void cod_start() {

    printf("\t\t%s\t%lu\n", buf_data[4] != 0 ? (char *)&buf_data[4] : "(abs)", calc_long(buf_data));
}

/*
 *	cod_end (ok++, works good)
 */
void cod_end() {

    fputc('\n', stdin);
}

/*
 *	cod_ident (ok++, works good)
 */
void cod_ident() {
    uchar l1;

    printf("\t\tMachine\t\t= %s\n", &buf_data[6]);
    printf("\t\t32 bit order\t= %d %d %d %d\n", buf_data[0], buf_data[1], buf_data[2], buf_data[3]);
    l1 = 0;
    while (l1 < 4) {
        order32[l1] = buf_data[l1];
        ++l1;
    }
    printf("\t\t16 bit order\t= %d %d\n", buf_data[4], buf_data[5]);
    order16[0] = buf_data[4];
    order16[1] = buf_data[5];
}

/*
 *	cod_xpsect (ok++, not verified)
 */
void cod_xpsect() {

    printf("\t\t%s", (buf_data[12] != 0) ? (char *)&buf_data[12] : "(abs)");
    if (calc_long(buf_data) != 0)
        printf("\tsize=%lu", calc_long(buf_data));
    if (calc_val(&buf_data[4]) != 0)
        printf("\treloc=%u", calc_val(&buf_data[4]));
    fputc('\n', stdin);
}

/*
 *	Error handling (ok++, works good)
 *
 */
#if CPM
void err_handling(p1, p2, p3, p4, p5) char *p1;
{

    fputc('\n', stdout);
    fflush(stdout);

    if (name != 0)
        fprintf(stderr, "%s: ", name);
    if (cur_rec != 0)
        fprintf(stderr, "%d: ", cur_rec);
    fprintf(stderr, p1, p2, p3, p4, p5);
    fputc('\n', stderr);
}

/*
 *	Print error (ok++, works good)
 */

void error(p1, p2, p3, p4, p5) {

    err_handling(p1, p2, p3, p4, p5);
    exit(1);
}

#else
void err_handling(char *fmt, va_list args) {

    fputc('\n', stdout);
    fflush(stdout);

    if (name != 0)
        fprintf(stderr, "%s: ", name);
    if (cur_rec != 0)
        fprintf(stderr, "%d: ", cur_rec);

    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
}

_Noreturn void error(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    err_handling(fmt, args);
    va_end(args);
    exit(1);
}

#endif

/*
 *	Calculate the value (ok++, works good)
 */
uint calc_val(p1) uchar *p1;
{ return ((uint) * ((uchar)order16[1] + p1) << 8) + *((uchar)order16[0] + p1); }

/*
 *	Calculate long value (ok, works good)
 */
ulong calc_long(p1) uchar *p1;
{
    long l1;
    uchar l2;

    l2 = 4;
    l1 = 0;
    while (l2-- != 0)
        l1 += p1[order32[l2]] << l2 * 8;
    return l1;
}

/*-------------------------------+
 |	End DUMP program	 |
 +-------------------------------*/
