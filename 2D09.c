/*
 * File - sub_2D09.c	BIG size - problems compiling v3.09
 */

#include "stdio.h"
#include "ctype.h"
#include "cgen.h"

int     atoi(char *);

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*.......................................................*
 *  sub_2D09_v2 optim: Out of memory	Used in: sub_3564
 *.......................................................*/
void sub_2D09(register struct aaa * sa, char * p2, int p3) {

  struct zzz	* lz1;	/*   ix+0FFh (ix+-1)  h  \	*/
			/*   ix+0FEh (ix+-2)  l _/li1 	*/	
  struct aaa	* la2;	/*   ix+0FDh (ix+-3)  h  \	*/
			/*   ix+0FCh (ix+-4)  l _/li2 	*/	
  char 		* li3;	/* + ix+0FBh (ix+-5)  h  \	*/
			/* + ix+0FAh (ix+-6)  l _/li3 	*/	
  uchar 	  lc4;	/* + ix+0F9h (ix+-7)  h __lc4 	*/
  char 		  lc5;	/* + ix+0F8h (ix+-8)  l __lc5 	*/
  char 		  lc6;	/*   ix+0F7h (ix+-9)  __lc6	*/
  char 		  lc7;	/*   ix+0F6h (ix+-10) __lc7 	*/
  int  		  li8;	/*   ix+0F5h (ix+-11) h  \	*/
			/*   ix+0F4h (ix+-12) l _/li8 	*/	
  unsigned long   ll9;	/* + ix+0F3h (ix+-13) h  \	*/
			/* + ix+0F2h (ix+-14) l  |ll9 	*/	
			/* + ix+0F1h (ix+-15) h  | 	*/	
			/* + ix+0F0h (ix+-16) l _/ 	*/	
  char 		  lc10;	/*   ix+0EFh (ix+-17)  __lc10 	*/
  char 		  lc11;	/*   ix+0EEh (ix+-18)  __lc11 	*/
  char 		* li12;	/*   ix+0EDh (ix+-19) h  \	*/
			/*   ix+0ECh (ix+-20) l _/li12	*/	
  unsigned long   ll13;	/* + ix+0EBh (ix+-21) h  \ \ 	*/
			/* + ix+0EAh (ix+-22) l  |_/	*/	
		 	/* + ix+0E9h (ix+-23) h  | \ 	*/
			/* + ix+0E8h (ix+-24) l _/_/ll13*/	
  char 		  lc15;	/* ; ix+0E7h (ix+-25)  __lc15 	*/

#ifdef DEBUG
    printf("\tsub_2D09(%x, %x, %d)\n", sa, p2, p3);
#endif

    li12 = p2;
    lc11 = lc15 = 0;		
m1: lc7  = *(p2++);
    if(lc7 == 0) return;

    switch(lc7) {
      case '\n':
      case '\r':
        putchar('\n');					/* m4	*/
        lc15 = 0;
        goto m1;

      case ' ':
        if(lc15 == 0) {					/* l3:	*/
          putchar('\t');
          lc15 = 1;
        } else {
	  putchar(lc7);
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
	if( ((li8 = *p2) == '-') || (li8 == '+')) {
	  if(isdigit(*(++p2)) != 0) {
	    lc5 = atoi(p2);
	    if(li8 == '-') lc5 = -lc5;
	    li8 = 0;
	  } else {
	    lc5 = 0;
	  }
	  while((isdigit(*p2) != 0) || (*p2 == '+') || (*p2 == '-'))  p2++;
	} else {
	  if(li8 == '>') {
	    for(lc5 = 0; *p2 == '>'; p2++, lc5++) ;
	  } else {
	    li8 = 0;
	    lc5 = 0;
	  }
	}
	lc6 = *(p2++);
        break; /* goto m10; */

      case 'G':
      case 'X':
        if(isdigit(*p2) != 0) {				/* m5:	*/						
          li3 = p2;
          while(isdigit(*p2) != 0) p2++;
        } else {
          li3 = 0;					/* m8:	*/
        }
        lc6 = *(p2++);					/* m9:	*/
        li8 = 'G';
        break; /* goto m10; */

      case 'L':
      case 'R':
      case 'U':
        lc6 = lc7;					/* m24: */
        lc7 = '~';
        li8 = 0;					/* m25: */
        lc5 = 0;
        break; /* goto m10; */

      case 'D':
        lc6 = lc7;					/* m26: */
        li8 = 0;
        lc5 = 0;
        break; /* goto m10; */

      default:
        putchar(lc7);					/* m2:	*/
        goto m1;					/* m3:	*/
    }
/*
m10:
*/
    switch(lc6) {
      case 'L':
/*
m27:	if(0 < (char)p3) {
	  la2  = sa;
	  lc10 = (char)p3 + (-1);
	} else {
m29:	  la2  = sa->a_l15.wi[0];
m30:	  lc10 = la2->a_c1 + (-1);
	}
m28:	lz1  = &array_80EF[*(lc10 + (uchar*)&la2->a_c3)];
        break;
*/
        if(0 < (char)p3) {				/* m27: */
          la2  = sa;
          lc10 = (char)p3 + (-1);
m28:      lz1  = &array_80EF[*(lc10 + (uchar*)&la2->a_c3)];
	  break; /* goto m11; */
	}
	la2  = sa->a_l15.wi[0];				/* m29: */
m30:	lc10 = la2->a_c1 + (-1);
	goto m28;

      case 'N':
        la2  = sa;					/* m32: */
        lc10 = (char)p3;
        break; /* goto m11; */

      case 'R':
    	la2 = sa->a_l15.wi[1];				/* m31: */
        goto m30;
    }
/*
m11:
*/
    switch(lc7) {
      case 'A':
        sub_153A(la2);					/* m51: */
        goto m1;

      case 'B':
        ll9 = sub_387A(la2); 				/* m45: */
m46:    if(li8 == '-') {
          if(lc11 == 0) {
            ll13 = ll9 + (long)word_AFF8;
            word_AFF8 = 0;
            lc11 = 1;
            goto m54;
          }
        }	
        printf("%lu", ll9);				/* m47: */
        goto m1;

      case 'C':
        if(la2->a_c0 == BFIELD) {			/* m63:	*/
          printf("%d", la2->a_l15.wi[1]->a_c6);
        } else {
          ll9 = la2->a_l15.l;				/* m64: */
          if(sub_46F7(ll9) == 0) ll9 = (-1) - ll9;
/*        word_AFF8 += ((sub_46F7(ll9) - 1)>>3); */	/* m65: */
          word_AFF8 += ((-1) + sub_46F7(ll9))/8;
        }
        goto m1;

      case 'D':
        if(word_AFF8 != 0) {				/* m33: */
          printf("%d", word_AFF8);
          word_AFF8 = 0;
        }
        goto m1;

      case 'F':						/* m43: */
        printf("%d", la2->a_l15.ii[1]);
        goto m39;

      case 'G':
      case 'X':
        lc4 = (lc7 == 'G') ?				/* m69: */
        *(lc10 + (uchar*)&la2->a_i9) : 
        *(lc10 + (uchar*)&la2->a_i6);
        if(li3 != 0) {
          while(isdigit(*li3) != 0) {			/* m73: */
            lc4 = (char)array_AB24[lc4*2 +((-48) + *(li3++))]; 	/* m72: */
          }
        }
        if(*p2 != '+') {				/* m74: */   
          lc4 += word_AFF8;
          word_AFF8 = 0;
        }
        printf("%s", off_AACA[lc4]);			/* m75: */
        goto m1;

      case 'O':
        printf("%s", array_805F[la2->a_c0]);		/* m49: */
        goto m1;

      case 'S':
/**/
	if     (la2->a_c0 == USEREG) printf("%s", off_AACA[la2->a_l15.ii[0]]);
	else if(la2->a_c0 ==  CONST) sub_2CE0(la2, la2->a_l15.l);
	else if(la2->a_c0 == FCONST) printf("%s", la2->a_l15.ci[0]);
	else			     printf("%s", la2->a_l15.vi[0]->b_name);
/**/
/*
        switch(la2->a_c0) {				
          case 'E':
            printf("%s", off_AACA[la2->a_l15.ii[0]]);
            break;
          case 'C':					
            sub_2CE0(la2, la2->a_l15.l);
            break;
          case 'D':					
            printf("%s", la2->a_l15.ci[0]);
            break;
          default:					
            printf("%s", la2->a_l15.vi[0]->b_name);
        }
*/
m39:    if(li8 == 0) {
          lc5 += word_AFF8;
          word_AFF8 = 0;
          if(word_AFF8 < lc5) printf("+%d", lc5);
          else if(lc5 < 0)    printf("%d",  lc5);
        }
        goto m1;

      case 'T':
        if(la2->a_c0 == BFIELD) {			/* m66: */
          printf("%d", la2->a_l15.wi[1]->a_c5);
        } else {
          ll9 = la2->a_l15.l;				/* m67: */
          if(sub_46F7(ll9) == 0) ll9 = -1 - ll9;
          printf("%d", (-1) + sub_46F7(ll9));
        }
        goto m1;

      case 'V':
        if((li8 == '-') || (li8 == '+')) {		/* m52: */
          if(lc11 == 0) {				/* m53: */
            ll13 = la2->a_l15.l + word_AFF8;
            word_AFF8 = 0;
            lc11 = 1;
          }
m54:	  ll13 += (li8 == '-') ? (long)(-1) : (long)1;
          if(sub_14F3(la2) == REG_L) {
            if(nodesize(la2) < 4) {
              ll13 &= ((int)(1<<(nodesize(la2)*8)) - 1);
            }
          }
          if(ll13 != 0) {				/* m57: */
            for(;(li12 < p2 && *(p2-1) != '\n');p2--) ;	/* m59: */ 
            putchar('\n');				/* m60: */
          } else {
            lc11 = 0;					/* m61: */
          }
        } else {
          lc5 += word_AFF8;				/* m62: */
          word_AFF8 = 0;
          sub_2CE0(la2, (la2->a_l15.l >> (lc5<<3)));
        }
        goto m1;

      case 'Z':
        ll9 = nodesize(la2);				/* m44: */
        goto m46;

      case '~':
        if(lc6 == 'U') {				/* m76: */
          lc5 += word_AFFB;
          if(((unsigned)dopetab[sa->a_c0] & 0x200) != 0) {
            if((char)p3 != 0) lc5--;
          }
          printf("%d", lc5);				/* m77: */
        } else {
          word_AFF8 += lc5;				/* m78: */
          sub_2D09(la2, lz1->p_8, lc10);
        }
        /* goto m1; */
    }
    goto m1;
}

/* End of file sub_2D09.c */



