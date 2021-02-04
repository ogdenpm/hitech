/*
 * File 1.c Created 17.05.2019 Last Modified 03.02.2021
 */

#include "stdio.h"
#include "cgen.h"

#define	offsetof(ty, mem)	((int)&(((ty *)0)->mem))

/* ===== start bss section ======= */
char         buffer[MAXBUF];					/* sub_306 */
int          lineno;						/* sub_306, sub_6AD0, sub_6B55*/
char         progname[MAXNAME];					/* sub_306 */
char         byte_AE0C;		/* First call ncsv	   */	/* sub_2BD0 */
int          cursect;		/* Current section	   */ 	/* sub_D37  */
int          word_AE0F;		/*			   */ 	/* sub_174C */
struct bbb * word_AE11;		/* "l" - long		   */ 	/* sub_1680, sub_415E, sub_43EF */
int          array_AE13[MAXFUN];/*			   */ 	/* sub_406,  sub_17E0, sub_5CF5 */
struct bbb * word_AE53;		/* "uc" - unsigned char	   */
unsigned     nstdpth;		/* Current nesting depth   */
int          array_AE57[MAXFUN];/*			   */
int          array_AE97[MAXFUN];/*			   */
struct bbb * word_AED7;		/* "d" - double 	   */
struct bbb * word_AED9;		/* "c" - char 		   */
struct bbb * array_AEDB[MAXFUN];/*			   */
struct bbb * word_AF1B;		/* "b"			   */
struct bbb * word_AF1D;		/* "x"			   */
struct bbb * hashtab[101];	/* hash table (array_AF1F) */
struct bbb * word_AFE9;		/* "v" - variable  	   */
int          lvlidx;		/* Level nested function   */	/* sub_406, sub_1680 */

int          word_AFED;						/* sub_1F4B */
char       * word_AFEF;						/* sub_1F4B */
char       * word_AFF1;						/* sub_1F4B */
char         byte_AFF3;						/* sub_1F4B */
int          word_AFF4;						/* sub_1F4B */
int          word_AFF6;						/* sub_1F4B */

int          word_AFF8;						/* sub_2D09, sub_3564 */
char         byte_AFFA;						/* sub_283E, sub_2B79 */
int          word_AFFB;						/* sub_2D09, sub_35E6 */
struct aaa * array_AFFD[0x14];					/* sub_3CDF, sub_3DC9 */
void	   * word_B011;						/* sub_36E0, sub_3712, sub_374C */
char         byte_B013;						/* sub_36E0, sub_3712, ... */
uchar        byte_B014;						/* sub_3CDF, sub_3DC9 */
char       * word_B015;		/* Pointer for printf      */
int          word_B017;						/* sub_406, sub_6D1, sub_283E, sub_2BD0, sub_61AA */
char         wflag;		/* Warning messages	   */	/* main, sub_6AD0 */
char         pflag;		/* Not used		   */	/* main */
char         hflag;		/* Not used		   */	/* main */
int          errcnt;		/* Number of errors	   */	/* main, sub_6B1D */
char         bflag;		/* Not used		   */	/* main */
char       * beg_sbrk;		/* Current highest memory  */	/* main */
char         eflag;		/* Not used		   */	/* main */
char         rflag;		/* Not used		   */	/* main, sub_61AA */

struct header1 word_B023; 					/* sub_6D61, cmalloc, sub_7028 */

char 	 ** word_B024;

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

/*
 *	Variables for new functions for working with files (from the standard library) 
 */
FILE   *f_inp;
FILE   *f_out;

/*
 * Added dummy variable "empty" to eliminate sub_5CF5 function
 * call with different number of parameters
 */

int     empty;

/* End file 1.c */


