/*
 * File - sub_6589.c Created 09.03.2019 Last Modified 30.05.2020
 */

#include "stdio.h"
#include <ctype.h>
#include "cgen.h"

extern FILE   *f_inp;
extern FILE   *f_out;

/*********************************************************
 * sub_6589 OK++    Used in: sub_1F4B, sub_2B79, sub_61AA,
 *			     sub_63B8, sub_66BC
 *********************************************************/
uchar sub_6589(int p1, int p2) {
    char    l1;
    uchar * l2;

#ifdef DEBUG
    printf("\tsub_6589(%d, %d)\n", p1, p2);
#endif

    p2 &= ~(0x40);	/* Clear bit 6 */
    if(p2 < 24) {
      if((p1 & array_AAE8[p2]) == array_AAE8[p2]) return p2;
      return 0;
    }
    p2 += (-24);		/* m1: */
    l1 = 6;
    l2 = &array_AB54[p2*6];
    do {
      if(*l2 != 0) {		/* m2: */
        if((p1 & array_AAE8[*l2]) ==  array_AAE8[*l2]) return *l2;
      }
      if(*(++l2) == 0) break;	/* m4: */
      l1 = l1 + (-1);
    } while (l1 != 0);
    return 0;			/* m5: */
}

/*********************************************************
 * sub_665B OK++			Used in: sub_66BC
 *********************************************************/
unsigned sub_665B(unsigned int p1, char p2) {
    unsigned loc;

#ifdef DEBUG
    printf("\tsub_665B(%u, %d)\n", p1, p2);
#endif
	
    if(p1 == 0) return 0;
    p2 += -48;
    loc = 1;
    while(loc < 24) {
      if((uchar)array_AB24[loc*2 + p2] == p1) return loc;
      loc++;
    }
    return 0;
}

/*********************************************************
 * sub_66BC v1 OK+			Used in: sub_1F4B
 * 
 * This function generates code as close as possible to
 * binary image.
 * Initialization variable "l2" is not required, since in
 * subsequent it is always assigned some values.
 *********************************************************/
/*
int sub_66BC(int p1, int p2, int p3, char * p4) {
    int     l1, l2; 
    char  * l3;

#ifdef DEBUG
    printf("\tsub_66BC(%x, %x, %x, %x)\n", p1, p2, p3, p4);
#endif

    l2 = 0;
    if((p2 & 0x8000) !=  0) {
      if(p1 == 0) {
        l2 = p2;
m2:     goto m25;
      }
m5:   l1 = sub_6589(((p2 & 0x8000) ? ((-1) - p2) : array_AAE8[p2])& p3, p1);
      if(l1 != 0) {
        l2 = l1;
        goto m2;
      }
m6:   l2 = sub_6589(p3, p1);
      goto m2;
    }
m7: if(p1 == 0) {
      if((p2 == 0) || (p4 == 0)) {
m9:     l2 = p2;
        goto m2;
      }
m10:  for(l3 = p4; isdigit(*(l3+1)) == 0; l3++) ;
      if(p2 >= 0x18) {
        p2 = sub_6589(p3, p2);
        if(p2 == 0) {
          l2 = p2;
          goto m2;
        }
      }
m13:  do { p2 = sub_665B(p2, (uchar)*l3); } while((l3--) != p4);
      goto m9;
    }
m14:if(p2 == 0) {
m15:  l2 = p1;
      goto m2;
    }
m16:l1=((p1 & 0x8000) ? ((-1) - p1) : array_AAE8[p1]) &	
       ((p2 & 0x8000) ? ((-1) - p2) : array_AAE8[p2]);
    if(((p1 & 0x8000) ? ((-1) - p1) : array_AAE8[p1]) == l1) goto m15;
    if(((p2 & 0x8000) ? ((-1) - p2) : array_AAE8[p2]) == l1) goto m9;
    l2 = sub_6589(l1, p1);
m25:return l2;
}
*/

/*********************************************************
 * sub_66BC v2 - OK+ Optimized version  Used in: sub_1F4B
 *
 * Excluded local variable l2, which was assigned return 
 * values.
 *********************************************************/

int sub_66BC(int p1, int p2, int p3, char * p4) {
    int     l1; 
    char  * l3;

#ifdef DEBUG
    printf("\tsub_66BC(%x, %x, %x, %x)\n", p1, p2, p3, p4);
#endif

    if((p2 & 0x8000) !=  0) {
      if(p1 == 0) return p2;
      l1 = sub_6589(((p2 & 0x8000) ?			/* m5:  */
      ((-1) - p2) : array_AAE8[p2])& p3, p1);
      if(l1 != 0) return l1;
      return sub_6589(p3, p1);				/* m6:  */
    }
    if(p1 == 0) {					/* m7:  */
      if((p2 == 0) || (p4 == 0)) return p2;
      for(l3 = p4; isdigit(*(l3+1)) == 0; l3++) ;	/* m10: */
      if(p2 >= 0x18) {
        p2 = sub_6589(p3, p2);
        if(p2 == 0) return p2;
      }
      do {
        p2 = sub_665B(p2, (uchar)*l3);			/* m13: */
      } while((l3--) != p4);
      return p2;
    }
    if(p2 == 0) return p1;				/* m14: */
    l1=((p1 & 0x8000) ? ((-1) - p1) : array_AAE8[p1]) &	/* m16: */
       ((p2 & 0x8000) ? ((-1) - p2) : array_AAE8[p2]);
    if(((p1 & 0x8000) ? ((-1) - p1) : array_AAE8[p1]) == l1) return p1;
    if(((p2 & 0x8000) ? ((-1) - p2) : array_AAE8[p2]) == l1) return p2;
    return sub_6589(l1, p1);
}

/*********************************************************
 * main OK+
 *
 * Functions of opening and closing a file are replaced by
 * standard functions
 *********************************************************/
int main(int argc, char ** argv) {

#ifdef DEBUG
    printf("\tmain()\n");
#endif

    beg_sbrk = sbrk(0);	/* Current highest memory */
    argc--;
    argv++;
    while(argc > 0 && **argv == '-') { 	/* Parsing options */
      switch(argv[0][1]) {
        case 'B': bflag = 1;	break;	/* Not use */
        case 'E': eflag = 1;	break;	/* Not use */
        case 'H': hflag = 1;	break;	/* Not use */
        case 'P':
        case 'p': pflag = 1;	break;	/* Not use */
        case 'R': rflag = 1;	break;
        case 'W':
        case 'w': wflag = 1;	break;	/* Displaying warnings */
        default:
          faterror("Illegal\tswitch %c", argv[0][1]);
          break;
      }
      argv++;
      argc--;
    }
    if(argc-- > 0) {
        if((f_inp = freopen(*argv, "r", stdin)) == 0) {		/* Open input file */
          faterror("Can't open %s", *argv);
        }
      else if(argc > 0) {
        if((f_out = freopen(argv[1], "w", stdout)) == 0) {	/* Open output file */
          faterror("Can't create %s", argv[1]);
        }
      }
    }
    sub_1680();	/* First_init */
    sub_6D1();	/* Compiling intermediate code */
    if(fclose(f_out) != 0) {					/* Close output file */
      uerror("Error closing output file");
    }
    /* Exit with error code */
    exit((errcnt ? 1 : 0));	/* Generated code is not significantly different */

}   /* End main */


/* End of file sub_6589.c  */


