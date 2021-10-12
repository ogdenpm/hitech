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
#include "dump.h"
#include <stdio.h>
#ifndef CPM
#include <stdarg.h>
#endif

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
/*    main();		    ok++ works good	*/
void prc_rec();    /*  ok++ works good	*/
int chk_rec();     /*  ok   works good	*/
void cod_text();   /*  ok++ works good	*/
void cod_psect();  /*  ok++ works with error */
void cod_reloc();  /*  ok++ works good	*/
void cod_sym();    /*  ok++ works good	*/
void cod_start();  /*  ok++ works good	*/
void cod_end();    /*  ok++ works good	*/
void cod_ident();  /*  ok++ works good	*/
void cod_xpsect(); /*  ok++ not verified	*/
#if CPM
void err_handling(); /*  ok++ works good	*/
void error();        /*  ok++ works good	*/
#else
void err_handling(char *fmt, va_list args);
_Noreturn void error(char *fmt, ...);
#endif
uint calc_val();   /*  ok++ works good	*/
ulong calc_long(); /*  ok   works good	*/

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
struct aaa {
    char *name;        /* Record type name  		*/
    void (*fun_ptr)(); /* Record processing function	*/
};

/*
 *	Descriptions of variables and arrays
 */
char *name;         /* File name		*/
int cur_rec;        /* current record	*/
uchar rec_typ;      /* Record type		*/
int rec_len;        /* Record length	*/
uchar buf_data[512]; /* Record data buffer	*/

char order32[] = { 0, 1, 2, 3 }; /* 32 bit order */
char order16[] = { 0, 1 };       /* 16 bit order */

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
char msg_text[]        = "TEXT";
char msg_psect[]       = "PSECT";
char msg_reloc[]       = "RELOC";
char msg_sym[]         = "SYM";
char msg_start[]       = "START";
char msg_end[]         = "END";
char msg_ident[]       = "IDENT";
char msg_xpsect[]      = "XPSECT";

struct aaa rec_types[] = {
    { "", 0 },                 /* 0 */
    { msg_text, cod_text },    /* 1 */
    { msg_psect, cod_psect },  /* 2 */
    { msg_reloc, cod_reloc },  /* 3 */
    { msg_sym, cod_sym },      /* 4 */
    { msg_start, cod_start },  /* 5 */
    { msg_end, cod_end },      /* 6 */
    { msg_ident, cod_ident },  /* 7 */
    { msg_xpsect, cod_xpsect } /* 8 */
};

/*
 *	Symbol types:
 *
char    msg_blank[] = ""; */
char st_stack[]   = "STACK";
char st_comm[]    = "COMM";
char st_reg[]     = "REG";
char st_lineno[]  = "LINENO";
char st_filnam[]  = "FILNAM";
char st_extern[]  = "EXTERN";

char *sym_types[] = {
    0,
    /* msg_blank; */ /* 0 */
    st_stack,        /* 1 */
    st_comm,         /* 2 */
    st_reg,          /* 3 */
    st_lineno,       /* 4 */
    st_filnam,       /* 5 */
    st_extern        /* 6 */
};

/*
 *	Psect flags:
 */
char pf_global[]    = "GLOBAL";
char pf_pure[]      = "PURE";
char pf_ovrld[]     = "OVRLD";
char pf_abs[]       = "ABS";

char *psect_flags[] = {
    pf_global, /* 0 */
    pf_pure,   /* 1 */
    pf_ovrld,  /* 2 */
    pf_abs     /* 3 */
};

/*
 *	Relocation types:
 */
char rt_rabs[]      = "RABS";
char rt_rpsect[]    = "RPSECT";
char rt_rname[]     = "RNAME";
char rt_unkn1[]     = "Unknown";
char rt_unkn2[]     = "Unknown";
char rt_rrpsect[]   = "RRPSECT";
char rt_rrname[]    = "RRNAME";

char *reloc_types[] = {
    rt_rabs,    /* 0 */
    rt_rpsect,  /* 1 */
    rt_rname,   /* 2 */
    rt_unkn1,   /* 3 */
    rt_unkn2,   /* 4 */
    rt_rrpsect, /* 5 */
    rt_rrname   /* 6 */
};

/*
 *	Main program (ok++, works good)
 */
main(argc, argv) int argc;
char **argv;
{
    char **next_arg;

    if (argc == 2 && strcasecmp(argv[1], "-v") == 0) {
        showVersion(stdout, argv[1][1] == 'V');
        exit(0);
    }

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
    register struct aaa *st;

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
    rec_len = (uint)buf_data[0] + ((uint)buf_data[1] << 8);
    rec_typ = buf_data[2];

    if (rec_typ == 0 || rec_typ > 9)
        error("unknown record type: %d", rec_typ);
    if (rec_len > 512) {
        rec_types[rec_typ] = rec_types[0];
        error("%s record too long: %d", &rec_types[0].name, rec_len);
    }
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
    data_bytes = rec_len - (5 + strlen(psect_name));

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

    printf("\t\t%s", buf_data[2] != 0 ? &buf_data[2] : "(abs)");
    l1 = calc_val(buf_data) >> 4;
    l2 = 0;
    while (l1 != 0) {
        if (BITTST(l1, 0) != 0) {
            if (l2 >= ARRAY_SIZE(psect_flags))
                error("unknown psect flag: 0X%x", 1 << l2);
            printf("\t%s", *(psect_flags + l2));
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
    char *l2;

    l2 = buf_data;
    while (l2 < &buf_data[rec_len]) {
        l1 = (*(l2 + 2) & 0xF0) >> 4;
        if (l1 >= 7)
            error("unknown relocation type: 0X%x0", l1);
        printf("\t\t%d\t%s\t%s\t%d\n", calc_val(l2), reloc_types[l1], l2 + 3, (*(l2 + 2) & 0xF));
        l2 += strlen(l2 + 3) + 4;
    }
}

/*
 *	cod_sym (ok++, works good)
 */
void cod_sym() {
    char *l1;
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
        printf("\t\t%s\t%s\t%ld", l3, (*l2 != 0) ? l2 : (((l4 & 6) != 0) ? "" : "(abs)"), calc_long(l1));

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

        l1 += strlen(l2) + strlen(l3) + 8;
    }
}

/*
 *	cod_start (ok++, works good)
 */
void cod_start() {

    printf("\t\t%s\t%lu\n", buf_data[4] != 0 ? buf_data + 4 : "(abs)", calc_long(buf_data));
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

    printf("\t\t%s", (buf_data[12] != 0) ? &buf_data[12] : "(abs)");
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

    fputc('\n', stdin);
    fflush(stdin);

    if (name != 0)
        fprintf(stdout, "%s: ", name);
    if (cur_rec != 0)
        fprintf(stdout, "%d: ", cur_rec);
    fprintf(stdout, p1, p2, p3, p4, p5);
    fputc('\n', stdout);
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

    fputc('\n', stdin);
    fflush(stdin);

    if (name != 0)
        fprintf(stdout, "%s: ", name);
    if (cur_rec != 0)
        fprintf(stdout, "%d: ", cur_rec);

    vfprintf(stdout, fmt, args);
    fputc('\n', stdout);
}

void error(char *fmt, ...) {
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
