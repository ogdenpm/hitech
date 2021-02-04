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

/*
 *	Constant declarations
 */

#define MAXFUN	 0x20  /* Maximum limit nested function */
#define MAXBUF	   60  /* Maximum buffer size 		*/
#define MAXNAME	   40  /* Maximum file name length	*/
#define MAXERR	   30  /* Maximum number nonfatal errors*/

#define MININT -32768	/* min for int (0x8000)	*/
#define MAXINT  32767	/* max for int (0x7fff)	*/


#if 1
#define NULSTR	    0  /*  0  ""	*/
#define NOT	    1  /*  1  "!"	*/
#define NEQL	    2  /*  2  "!="	*/
#define HASHSIGN    3  /*  3  "#"	*/
#define DOLLAR	    4  /*  4  "$"	*/
#define DOLLAR_U    5  /*  5  "$U"	*/
#define MOD	    6  /*  6  "%"	*/
#define BAND	    7  /*  7  "&"	*/
#define LAND	    8  /*  8  "&&"	*/
#define GADDR	    9  /*  9  "&U"	*/
#define LPAREN	  0xA  /* 10  "("	*/
#define RPAREN	  0xB  /* 11  ")"	*/
#define MUL	  0xC  /* 12  "*"	*/
#define MUL_U	  0xD  /* 13  "*U"	*/
#define ADD	  0xE  /* 14  "+"	*/
#define INCR	  0xF  /* 15  "++"	*/
#define PLUS_U	 0x10  /* 16  "+U"	*/
#define COMMA	 0x11  /* 17  ","	*/
#define SUB	 0x12  /* 18  "-"	*/
#define DECR	 0x13  /* 19  "--"	*/
#define CONV	 0x14  /* 20  "->"	*/
#define MINUS_U	 0x15  /* 21  "-U"	*/
#define DOT	 0x16  /* 22  "."	*/
#define DOT_DOT	 0x17  /* 23  ".."	*/
#define DIV	 0x18  /* 24  "/"	*/
#define COLON	 0x19  /* 25  ":"	*/
#define COLON_U	 0x1A  /* 26  ":U"	*/
#define COLON_S	 0x1B  /* 27  ":s"	*/
#define SCOLON	 0x1C  /* 28  ";"	*/
#define T_SCOLON 0x1D  /* 29  ";;"	*/
#define LT	 0x1E  /* 30  "<"	*/
#define LSHIFT	 0x1F  /* 31  "<<"	*/
#define LEQ	 0x20  /* 32  "<="	*/
#define ASSIGN	 0x21  /* 33  "="	*/
#define ASMOD	 0x22  /* 34  "=%"	*/
#define ASAND	 0x23  /* 35  "=&"	*/
#define ASMUL	 0x24  /* 36  "=*"	*/
#define ASADD	 0x25  /* 37  "=+"	*/
#define ASSUB	 0x26  /* 38  "=-"	*/
#define ASDIV	 0x27  /* 39  "=/"	*/
#define ASLSHIFT 0x28  /* 40  "=<<"	*/
#define EQL	 0x29  /* 41  "=="	*/
#define ASRSHIFT 0x2A  /* 42  "=>>"	*/
#define ASEXOR	 0x2B  /* 43  "=^"	*/
#define ASEOR	 0x2C  /* 44  "=|"	*/
#define GT	 0x2D  /* 45  ">"	*/
#define GEQ	 0x2E  /* 46  ">="	*/
#define RSHIFT	 0x2F  /* 47  ">>"	*/
#define QUEST	 0x30  /* 48  "?"	*/
#define ATGIGN	 0x31  /* 49  "@"	*/
#define CASE	 0x32  /* 50  "[\\"	*/
#define UNKNOWN	 0x33  /* 51  "[a"	*/
#define ENUM	 0x34  /* 52  "[c"	*/
#define EXPR	 0x35  /* 53  "[e"	*/
#define INIT	 0x36  /* 54  "[i"	*/
#define STRUCT	 0x37  /* 55  "[s"	*/
#define UNION	 0x38  /* 56  "[u"	*/
#define VAR	 0x39  /* 57  "[v"	*/
#define BXOR	 0x3A  /* 58  "^"	*/
#define LBRACE	 0x3B  /* 59  "{"	*/
#define BOR	 0x3C  /* 60  "|"	*/
#define LOR	 0x3D  /* 61  "||"	*/
#define RBRACE	 0x3E  /* 62  "}"	*/
#define BNOT	 0x3F  /* 63  "~"	*/
#define RECIP	 0x40  /* 64  "RECIP"   */
#define TYPEOP	 0x41  /* 65  "TYPE"    */
#define IDOP	 0x42  /* 66  "ID"	*/
#define CONST	 0x43  /* 67  "CONST"   */
#define FCONST	 0x44  /* 68  "FCONST"  */
#define USEREG	 0x45  /* 69  "REG"     */
#define INAREG	 0x46  /* 70  "INAREG"  */
#define BFIELD   0x47  /* 71  "BITFIELD"*/
#else
enum op {
  NULSTR,	/*  0  0  ""	*/
  NOT,		/*  1  1  "!"	*/
  NEQL,		/*  2  2  "!="	*/
  HASHSIGN,	/*  3  3  "#"	*/
  DOLLAR,	/*  4  4  "$"	*/
  DOLLAR_U,	/*  5  5  "$U"	*/
  MOD,		/*  6  6  "%"	*/
  BAND,		/*  7  7  "&"	*/
  LAND,		/*  8  8  "&&"	*/
  GADDR,	/*  9  9  "&U"	*/
  LPAREN,	/* 10  A  "("	*/
  RPAREN,	/* 11  B  ")"	*/
  MUL,		/* 12  C  "*"	*/
  MUL_U,	/* 13  D  "*U"	*/
  ADD,		/* 14  E  "+"	*/
  INCR,		/* 15  F  "++"	*/
  PLUS_U,	/* 16 10  "+U"	*/
  COMMA,	/* 17 11  ","	*/
  SUB,		/* 18 12  "-"	*/
  DECR,		/* 19 13  "--"	*/
  CONV,		/* 20 14  "->"	*/
  MINUS_U,	/* 21 15  "-U"	*/
  DOT,		/* 22 16  "."	*/
  DOT_DOT,	/* 23 17  ".."	*/
  DIV,		/* 24 18  "/"	*/
  COLON,	/* 25 19  ":"	*/
  COLON_U,	/* 26 1A  ":U"	*/
  COLON_S,	/* 27 1B  ":s"	*/
  SCOLON,	/* 28 1C  ";"	*/
  T_SCOLON,	/* 29 1D  ";;"	*/
  LT,		/* 30 1E  "<"	*/
  LSHIFT,	/* 31 1F  "<<"	*/
  LEQ,		/* 32 20  "<="	*/
  ASSIGN,	/* 33 21  "="	*/
  ASMOD,	/* 34 22  "=%"	*/
  ASAND,	/* 35 23  "=&"	*/
  ASMUL,	/* 36 24  "=*"	*/
  ASADD,	/* 37 25  "=+"	*/
  ASSUB,	/* 38 26  "=-"	*/
  ASDIV,	/* 39 27  "=/"	*/
  ASLSHIFT,	/* 40 28  "=<<"	*/
  EQL,		/* 41 29  "=="	*/
  ASRSHIFT,	/* 42 2A  "=>>"	*/
  ASEXOR,	/* 43 2B  "=^"	*/
  ASEOR,	/* 44 2C  "=|"	*/
  GT,		/* 45 2D  ">"	*/
  GEQ,		/* 46 2E  ">="	*/
  RSHIFT,	/* 47 2F  ">>"	*/
  QUEST,	/* 48 30  "?"	*/
  ATGIGN,	/* 49 31  "@"	*/
  CASE,		/* 50 32  "[\\"	*/
  UNKNOWN,	/* 51 33  "[a"	*/
  ENUM,		/* 52 34  "[c"	*/
  EXPR,		/* 53 35  "[e"	*/
  INIT,		/* 54 36  "[i"	*/
  STRUCT,	/* 55 37  "[s"	*/
  UNION,	/* 56 38  "[u"	*/
  VAR,		/* 57 39  "[v"	*/
  BXOR,		/* 58 3A  "^"	*/
  LBRACE,	/* 59 3B  "{"	*/
  BOR,		/* 60 3C  "|"	*/
  LOR,		/* 61 3D  "||"	*/
  RBRACE,	/* 62 3E  "}"	*/
  BNOT,		/* 63 3F  "~"	*/
  RECIP,	/* 64 40  "RECIP"   */
  TYPEOP,	/* 65 41  "TYPE"    */
  IDOP,		/* 66 42  "ID"	    */
  CONST,	/* 67 43  "CONST"   */
  FCONST,	/* 68 44  "FCONST"  */
  USEREG,	/* 69 45  "REG"     */
  INAREG,	/* 70 46  "INAREG"  */
  BFIELD	/* 71 47  "BITFIELD"*/
};
#endif

/*
 * Classes
 */
 
#define MEMBER   0x16  /*     */
#define EDECL    0x34  /* '4' */
#define SDECL    0x37  /* '7' */
#define UDECL    0x38  /* '8' */
#define DECL9    0x39  /* '9' */
#define TDECL    0x41  /* 'A' */

/*
 *	Used macros
 */

#define LO_CHAR(a)      *((unsigned char *)&a)
#define HI_CHAR(a)      *(((unsigned char *)&a) + 1)
#define LO_WORD(a)      *((unsigned int *)&a)
#define HI_WORD(a)      *(((unsigned int *)&a) + 1)

#define bittst(var,bitno) ((var) & 1 << (bitno))
#define bitset(var,bitno) ((var) |= 1 << (bitno))
#define bitclr(var,bitno) ((var) &= ~(1 << (bitno)))

#ifndef	uchar
#define	uchar	unsigned char
#endif

#define container_of(ptr, type, member) ((type *)((char *)(ptr)-(char *)(&((type *)0)->member)))

/*
 *	Structural declarations
 */

union pw {
  int		* pi;
  char		* pc;
  struct aaa	* pst;
  int		  i;
  unsigned int	  ui;
  char		  ch[2];
  uchar		  uch[2];
};

union lw {
  long		  l;
  unsigned long   ul;
  struct aaa	* wi[2];
  struct bbb	* vi[2];
  char		* ci[2];
  char		  bc[4];
  int		* pl[2];
  unsigned long	* lp[2];
  unsigned	  ii[2];
};

struct	aaa {		/* Offset  	Used values  &  Description	*/
  uchar		a_c0;	/* +0  0	0 - 0x47			*/
  uchar		a_c1;	/* +1  1					*/
  uchar		a_c2;	/* +2  2	0, 1, 2,			*/
  uchar		a_c3;	/* +3  3					*/
  uchar		a_c4;	/* +4  4					*/
  uchar		a_c5;	/* +5  5					*/
  uchar		a_c6;	/* +6  6					*/
  struct aaa  * a_i5;	/* +7  7					*/
			/* +8  8					*/
  unsigned int  a_i6;	/* +9  9					*/
			/* +A 10					*/
  int		a_i7;	/* +B 11					*/
			/* +C 12					*/
  unsigned int  a_i8;	/* +D 13					*/
			/* +E 14					*/
  struct aaa  * a_i9;	/* +F 15					*/
			/*+10 16					*/
  int		a_i10;	/*+11 17					*/
			/*+12 18					*/
  int	      * a_i11;	/*+13 19					*/
			/*+14 20					*/
  unsigned int 	a_i12;	/*+15 21					*/
			/*+16 22					*/
  struct bbb  * a_i14;	/*+17 23					*/
			/*+18 24					*/
  union lw	a_l15;	/*+19 25					*/
			/*+1A 26					*/
			/*+1B 27					*/
			/*+1C 28					*/
};

struct	bbb {		/* Offset Member Description			*/
  char	      * b_name;	/* +0   0 s_name Pointer to Name identifier 	*/
			/* +1   1					*/
  char		b_class;/* +2	2 s_class	    0x16 - MEMBER 	*/
  			/*			    '4' -  EDECL	*/
  			/*			    '7' -  SDECL 	*/
  			/*			    '8' -  UDECL	*/
  			/*			    '9' - 		*/
  			/*			    'A' -  TYPE		*/
  char		b_c3;	/* +3	3 s_strg Bits used: 0 0000001 -		*/
  			/*		            1 0000010 -	global?	*/
  			/*		            2 0000100 -		*/
  			/*		            3 0001000 -	register?*/
  			/*		            4 0010000 -		*/
  char		b_ndpth;/* +4	4 s_ndpth Nesting depth of block	*/
  int		b_i5;	/* +5   5					*/
			/* +6   6					*/
  struct bbb *  b_next; /* +7   7					*/
			/* +8   8					*/
  unsigned	b_size; /* +9   9 s_size Type size			*/
			/* +A  10					*/
  int		b_nelem;/* +B  11 s_nelem				*/
			/* +C  12					*/
  unsigned	b_refl;	/* +D  13 s_refl				*/
			/* +E  14					*/
  struct bbb  * b_type;	/* +F  15 s_type				*/
			/* +10 16					*/
  int		b_i11;	/* +11 17 s_alig Type alig  size stack frame	*/
			/* +12 18					*/
  int	      * b_memb;	/* +13 19 s_memb Struct store			*/
			/* +14 20					*/
  char		b_c13;  /* +15 21	 type flag 0, 1, 2, 3, 4, 5,	*/
};

struct zzz {
  char		c_0;
  char		c_1;
  char		c_2;
  char		c_3;
  char		c_4;
  char		c_5;
  char 	      * p_6;
  char	      * p_8;
};

struct ptr {
  struct ptr * next_ptr;
};

struct header1 {
  uchar size;
  struct ptr next;
};

struct header2 {
  unsigned size;
  char aaa; 
  struct ptr next;
};

struct type {
  char	* t_str;
  int	  t_size;
  int	  t_alig;
  char	  t_flag;
};

/*
 *	Descriptions of variables and arrays
 *
 * Declarations are located in sequence of being in
 * original binary image of CGEN.COM
 *					Purpose				Where it is used
 * ===== Start bss section ======= */
extern char         buffer[MAXBUF];					/* sub_306  */
extern int          lineno;						/* sub_306, sub_6AD0, sub_6B55*/
extern char         progname[MAXNAME];	/*			   */	/* sub_306  */
extern char         byte_AE0C;		/* First call ncsv	   */	/* sub_2BD0 */
extern int          cursect; 		/*  Current section	   */ 	/* selpsect  */
extern int          word_AE0F;		/*			   */ 	/* sub_174C */
extern struct bbb * word_AE11;		/* "l" - long		   */ 	/* sub_1680, sub_415E, sub_43EF */
extern int          array_AE13[MAXFUN]; /*			   */ 	/* sub_406,  sub_17E0, sub_5CF5 */
extern struct bbb * word_AE53;		/* "uc" - unsigned char	   */
extern unsigned     nstdpth;		/* Current nesting depth   */
extern int          array_AE57[MAXFUN]; /*			   */
extern int          array_AE97[MAXFUN]; /*			   */
extern struct bbb * word_AED7;		/* "d" - double 	   */
extern struct bbb * word_AED9;		/* "c" - char 		   */
extern struct bbb * array_AEDB[MAXFUN]; /*			   */
extern struct bbb * word_AF1B;		/* "b"			   */
extern struct bbb * word_AF1D;		/* "x"			   */
extern struct bbb * hashtab[101];	/* hash table (array_AF1F) */
extern struct bbb * word_AFE9;		/* "v" - variable  	   */
extern int          lvlidx;		/* Level nested function   */	/* sub_406, sub_1680 */

extern int          word_AFED;						/* sub_1F4B */
extern char       * word_AFEF;						/* sub_1F4B */
extern char       * word_AFF1;						/* sub_1F4B */
extern char         byte_AFF3;						/* sub_1F4B */
extern int          word_AFF4;						/* sub_1F4B */
extern int          word_AFF6;						/* sub_1F4B */

extern int          word_AFF8;						/* sub_2D09, sub_3564 */
extern char         byte_AFFA;						/* sub_283E, sub_2B79 */
extern int          word_AFFB;						/* sub_2D09, sub_35E6 */
extern struct aaa * array_AFFD[0x14];					/* sub_3CDF, sub_3DC9 */
extern void	  * word_B011;						/* sub_36E0, sub_3712, sub_374C */
extern char         byte_B013;						/* sub_36E0, sub_3712, ... */
extern uchar        byte_B014;						/* sub_3CDF, sub_3DC9 */
extern char       * word_B015;	/* msgptr  Pointer str printf       */
extern int          word_B017;						/* sub_406, sub_6D1, sub_283E, sub_2BD0, sub_61AA */
extern char         wflag;		/* Warning messages	    */	/* main, sub_6AD0 */
extern char         pflag;		/* Not used		    */	/* main */
extern char         hflag;		/* Not used		    */	/* main */
extern int          errcnt;		/* Number of errors	    */	/* main, uerror */
extern char         bflag;		/* Not used		    */	/* main */
extern char       * beg_sbrk;		/* Current highest memory   */	/* main */
extern char         eflag;		/* Not used		    */	/* main */
extern char         rflag;		/*			    */	/* main, sub_61AA */

extern struct header1 word_B023; 					/* sub_6D61, cmalloc, sub_7028 */

#if 0
extern int          word_B026;						/* sprintf */
extern int          word_B028;						/* sprintf */
extern char         byte_B02E;						/* pnum, doprnt */
extern int          word_B02F;						/* pputc */
extern char         byte_B031;						/* pnum, doprnt */
extern char         buf_B032[512];					/* pnum, doprnt */
extern int          __argc_;						/* startup */
extern int          memtop;
#endif						/* brk, sbrk */
/* ===== End of bss section ======= */


/* ===== Start data section ======= */

extern char       * array_805F[];					/*+sub_2D09 */
extern struct zzz   array_80EF[];					/* sub_1F4B, sub_283E, sub_2D09, sub_3564 */
extern int          array_987D[];					/*+sub_13D  */
extern char         array_990D[];					/*+sub_13D  */
extern int          array_9BD4[];					/*+sub_13D  */
extern int          array_A162[];					/*+sub_1F4B */
extern char       * tnames[];						/*+sub_1B2  */
				
extern char         byte_A46A;		/* Initial value middle  */	/*+sub_1B2  */
					/* element used in binary search */
extern char         array_A542[];					/*+sub_153A */
extern char       * off_A592[];						/*+selpsect  */
extern int          dopetab[72];					/*+sub_1F4B, sub_2B8A, sub_2D09, sub_35E6, sub_377A, ... */
extern char         array_A94A[];					/*+sub_1F4B */
extern int          array_AAE8[];					/*+sub_406,  sub_1F4B, sub_283E, sub_61AA, sub_63B8, sub_6589, sub_66BC */
extern uchar        array_AB24[];					/*+sub_283E, sub_2D09, sub_665B */
extern uchar        array_AB54[];					/*+sub_63B8, sub_6589 */


extern struct type  vars[14];  						/* sub_1680 */
extern char       * off_AACA[];

/*
 * Added dummy variable "empty" to eliminate sub_5CF5 function
 * call with different number of parameters
 */

/*
extern int	    empty;
extern FILE	   *f_out, *f_in;
*/

/* ===== End of data section ======= */

/*
 * Function prototype
 *
 * Missing Hi-Tech C header files
 */

/*
long	     atol(char *str);
*/
int	     atoi(char *);
void	     blkclr(char *, unsigned short size);
void	   * sbrk(int);
/****************************************************************
 * Prototype functions are located in sequence of being in
 * original binary image of CGEN.COM
 *
 * ok++ - Full binary compatibility with code in original file;
 * ok+  - Code generated during compilation differs slightly,
 *        but is logically correct;
 * ok   - C source code was compiled successfully, but not verified.
 ****************************************************************/
/* lex.c ----------------------------------------------------------------------*/
int	     sub_13D(int, int);				/*.ok+  sub_13D.c	*/
char         sub_1B2(char *);				/* ok++ sub_1B2.c	*/
struct bbb **gethashptr(char *);	/*sub_21F*/	/* ok++			*/
struct bbb * sub_265(char *);				/* ok++			*/
char 	   * sub_306(void);				/*.ok+  sub_306.c	*/
void         sub_406(void);				/*.ok+  sub_406.c	*/
struct bbb * sub_627(char *, unsigned *);		/* ok++ 		*/
void	     sub_6C8(void);				/* ok++ 		*/
void	     sub_6D1(void);				/*.ok+  sub_6D1.c	*/
void	     sub_76F(int);				/* ok++ sub_76F.c	*/
void         sub_793(void);				/* ok++ 		*/
/* code.c ----------------------------------------------------------------------*/
int	     sub_808(struct bbb *, struct aaa *); 	/*.ok+  sub_808.c	*/
void	     sub_B19(void);				/* ok++ sub_B19.c	*/
void	     sub_B96(int);				/* ok++ 		*/
void         sub_BCC(int, int);				/* ok++ 		*/
void         sub_BEE(int, int);				/* ok++ 		*/
void         sub_C36(struct bbb *);			/* ok++ 		*/
void	     sub_C57(struct bbb *);			/* ok++ 		*/
void	     sub_CAB(struct bbb *);			/* ok++ 		*/
void	     sub_CDF(int);				/* ok++ 		*/
void	     selpsect(int);		/*sub_D37*/	/* ok++ 		*/
void	     sub_D66(int *, int *, int);		/* ok++ 		*/
void	     sub_E43(void);				/* ok++ 		*/
void	     sub_1420(int);				/* ok++ 		*/
void	     sub_143F(uchar);				/* ok++ 		*/
void	     sub_1489(uchar);				/* ok++ 		*/
void	     sub_14D3(struct bbb *);			/* ok++ 		*/
char	     sub_14F3(struct aaa *);			/* ok++ 		*/
void	     sub_153A(struct aaa *);			/* ok++ 		*/
void	     sub_155D(char *, int);			/* ok++ 		*/
void	     sub_15D3(int);				/* ok++ 		*/
void	     sub_15E7(int);				/* ok++ 		*/
void	     sub_15FB(struct bbb *, int, int);		/* ok++ 		*/
int	     sub_1659(int, int);			/* ok++ sub_1659.c	*/
void	     sub_1680(void);				/* ok++ sub_1680.c	*/
int	     sub_174C(void);				/* ok++ 		*/
struct bbb * sub_1754(char *, int);			/* ok++ 		*/
/* sym.c -----------------------------------------------------------------------*/
void	     sub_17E0(void);				/*.ok+  sub_17E0.c	*/
void         sub_19C1(int);				/* ok++ sub_19C1.c	*/

void         sub_1B0C(void);	      /* missing pop bc	   ok+			*/
int	     sub_1C6D(int, int);			/* ok++ sub_1C6D.c	*/
int	     sub_1C8E(struct bbb *);			/* ok++ sub_1C8E.c	*/
int	     sub_1CC4(struct bbb *);			/* ok++ 		*/
void	     sub_1CEF(struct bbb *);			/* ok++ 		*/
void	     sub_1EDF(void);				/* ok++ 		*/
int	     sub_1F4B(struct aaa *,int,int,int,int *);	/*.ok+  optim: out of memory */
int          sub_283E(struct aaa *, int);		/*.ok+  sub_283E.c	*/
int          sub_2B2A(struct aaa *);			/*.ok+  sub_2B2A.c	*/
uchar	     sub_2B79(struct aaa *);			/* ok+  sub_2B79.c	*/
/* cgen.c ----------------------------------------------------------------------*/
void	     sub_2BD0(struct aaa *);			/* ok++			*/
long	     sub_2C5E(struct aaa *, long);		/*.ok+  sub_2C5E.c	*/
void	     sub_2CE0(struct aaa *, long);		/* ok++ sub_2CE0.c	*/
void	     sub_2D09(struct aaa *, char *, int);	/*.ok   optim: out of memory */
void	     sub_3564(struct aaa *);			/*.ok+  sub_3564.c	*/
void         sub_35E6(struct aaa *);			/*.ok+  		*/
void	     sub_36E0(struct aaa *);			/* ok++ 		*/
struct aaa * sub_3712(void);				/* ok++ 		*/
char	     sub_374C(void);				/* ok++ 		*/
struct aaa * sub_377A(struct aaa *);			/* ok++ 		*/
void	     sub_37ED(struct aaa *);			/* ok++ sub_37ED.c	*/
void	     sub_385B(struct aaa *);			/* ok++ sub_385B.c	*/
int	     sub_387A(struct aaa *);			/* ok++ 		*/
int	     sub_38CA(struct aaa *, int);		/* ok++ 		*/
int	     sub_393C(struct aaa *);			/* ok++ 		*/
int	     sub_3952(struct aaa *);			/* ok++ 		*/
int	     sub_3968(struct aaa *);			/* ok++ 		*/
unsigned     nodesize(struct aaa *);	/*sub_3993*/	/* ok++ 		*/
struct aaa * sub_39CA(struct aaa *);			/* ok++ 		*/
void	     sub_3A79(struct aaa *, struct aaa *);	/*.ok+  sub_3A79.c	*/
void	     sub_3B65(unsigned long *, long, int);	/* ok++ sub_3B65.c	*/
void	     sub_3BC6(long *, long, int);		/*.ok+  sub_3BC6.c	*/
struct aaa * sub_3CDF(struct aaa *);			/* ok++ sub_3CDF.c	*/
/* tree.c ----------------------------------------------------------------------*/
void	     sub_3DC9(struct aaa *);			/* ok++			*/
struct aaa * sub_3EAA(struct aaa *);			/*.ok+  sub_3EAA.c	*/
struct aaa * sub_415E(long);				/* ok++ sub_415E.c	*/
struct aaa * sub_4192(void);				/*.ok+  sub_4192.c	*/
struct aaa * sub_43EF(int, struct aaa *, struct aaa *); /*.ok+  sub_43EF.c	*/
uchar	     sub_46F7(long);				/* ok++ sub_46F7.c	*/
void	     sub_475C(struct aaa *);			/* ok++ sub_475C.c	*/
char	     sub_47B2(struct aaa *, int);		/*.ok+  sub_47B2.c	*/
/*
int	     sub_4B89(struct aaa *);			   ok+    
*/
uchar	     sub_4B89(struct aaa *);			/*.ok+  sub_4B89.c	*/
int	     sub_4BE5(struct aaa *);			/* ok++ sub_4BE5.c	*/
int	     sub_4C12(struct aaa *);			/* ok++ 		*/
char	     sub_4C6D(struct aaa *);			/*.ok+  sub_4C6D.c	*/
struct aaa * sub_4C8B(struct aaa *);			/* ok++ sub_4C8B.c	*/
struct aaa * sub_4DA3(struct aaa *);			/* ok++ 		*/
struct aaa * sub_4E8D(struct aaa *);			/* ok++ 		*/
struct aaa * sub_4FA8(struct aaa *);			/* ok++ 		*/
struct aaa * sub_4FCE(struct aaa *);			/*.ok+  sub_4FCE.c	*/
struct aaa * sub_508A(struct aaa *);			/* ok++ sub_508A.c	*/
struct aaa * sub_53EE(struct aaa *);			/* ok++ 		*/
/* local.c ---------------------------------------------------------------------*/
struct aaa * sub_54B6(struct aaa *); 			/*.ok   optim: out of memory */
void         sub_5CF5(struct bbb *, int);		/*.ok+  sub_5CF5.c	*/
struct aaa * sub_5DF6(struct aaa *);			/* ok++ sub_5DF6.c	*/
struct aaa * sub_5F52(struct aaa *);			/* ok++ sub_5F52.c	*/
struct aaa * sub_600E(struct aaa *);			/* ok++ sub_600E.c	*/
int	     sub_605E(int);				/*.ok+  sub_605E.c	*/
char	     sub_60A8(struct aaa *, struct aaa *);	/*.ok+  sub_60A8.c	*/
int	     sub_61AA(struct bbb *, int);		/* ok++ sub_61AA.c	*/
int	     sub_6246(struct aaa *, struct aaa *);	/* ok++ 		*/
char	     sub_628F(struct aaa *, struct aaa *);	/* ok++ 		*/
char	     sub_62BE(struct aaa *, struct aaa *);	/* ok++ 		*/
char	     sub_63B8(int, int, int);			/*.ok+  sub_63B8.c	*/
uchar	     sub_6589(int, int);			/*.ok+  sub_6589.c	*/
unsigned     sub_665B(unsigned, char);			/* ok++ 		*/
int	     sub_66BC(int, int, int, char *);		/* ok++ 		*/
/* main.c  ---------------------------------------------------------------------*/
/* int	     main(int, char **);		*/	/* ok++ 		*/

/*
 * To comply with C standard functions are replaced with
 * similar ones with a variable number of parameters
 */
/*void	     faterror(char * fmt, ...);*/	/*sub_6AA2*/	/* ok   sub_6AA2.c	*/
/*void	     warning(char * fmt, ...);*/	/*sub_6AD0*/	/* ok   		*/
/*void	     uerror(char * p1);*/		/*sub_6B1D*/	/* ok++ sub_6B1D.c	*/
/*
 * sub_6B55 excluded because it is unnecessary
 *
void	     sub_6B55(char *, int, char *);
*/
void	   * allocmem(unsigned int);	/*sub_6B9B*/	/* ok++ sub_6B9B.c	*/

/* int	     fprintf(FILE *, char *, int);	*/

int	     sub_6BF5(char *, char *, FILE *);

void 	   * sub_6D1C(char *, int);			/* ok++ sub_6D1C.c	*/
int	     sub_6D61(void);				/* ok++ 		*/
void 	   * cmalloc(unsigned);				/* ok++ 		*/
void	     sub_7028(struct ptr *);			/* ok++ 		*/

int	     sub_708D(char *, int);					/* printf */

int	     getchar(void);
int	     putchar(int);

/*
 * The following declarations may be required to recreate from a binary image
 */
char	     sub_70CB(char);						/* toupper */

/*char	     sub_70F8(struct fcb *, char *);	*/	/* ok++ */	/* def_fcb */

int	     sub_7247(char *, char *, int);				/* sprintf */

int	     sub_7288(int);						/* pputc   */
int	     sub_7325(FILE *, char *, int *);				/* doprnt  */
/* int	     fgetc(FILE *); */
int	     sub_770B(FILE *);						/* filbuf  */
char	     sub_77F5();						/* Test ^c */
/*	     exit(int); */
int	     sub_7855(FILE *);						/* fclose  */
int	     sub_78F0(FILE *);						/* fflush  */

/* End file cgen.h */

/*
 * Debug function declarations
 */
#ifdef DEBUG1
void pr_st_a(struct aaa * st);
void pr_st_b(struct bbb * st);
#endif



