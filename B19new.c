/*
 * File - sub_B19.c Created 09.03.2019 Last Modified 21.01.2021
 */

#include "stdio.h"
#include <stdlib.h>
#include "cgen.h"

enum psect {
  P_BSS = 1,
  P_TEXT,
  P_DATA
};

#define REG_A 1
#define REG_L 2
#define REG_F 3

/*********************************************************
 * sub_B19 OK++				 Used in: sub_6D1
 *********************************************************/
void sub_B19(void) {
    register struct bbb * sb;
    int l1;
    int l2;

#ifdef DEBUG
    printf("\tsub_B19()\n");
#endif

    sb = sub_265(sub_306());
    selpsect(P_DATA);
    sub_CAB(sb);		/* Emit "symbolic_name:" (identifier label) */
    l1 = sub_808(sb, sub_4192());
    l2 = (sb->b_refl) ? 2 : sb->b_type->b_size; 
    if(sb->b_nelem == 0) {
      sb->b_nelem = l1/l2;
      sb->b_size  = sub_1C8E(sb);
    }
    sub_76F(']');
#ifdef DEBUG
    printf("\tsub_B19 Return\n");
#endif
}	

/*********************************************************
 * sub_B96 OK++				Used in: sub_2BD0
 * emit_call_ncsv
 *********************************************************/
void sub_B96(int size_stack_frame) {

#ifdef DEBUG
    printf("\tsub_B96(%x)\n", size_stack_frame);
#endif

    selpsect(P_TEXT);
    if(byte_AE0C == 0) {	/* if first call	*/
      printf("global\tncsv, cret, indir\n");
    }
    printf("call\tncsv\n");
    byte_AE0C = 1;		/* first call is done	*/
    printf("defw\tf%d\n", size_stack_frame);
}

/*********************************************************
 * sub_BCC OK++				 Used in: sub_406
 *********************************************************/
void sub_BCC(int p1, int p2) {

#ifdef DEBUG
    printf("\tsub_BCC(%d, %d)\n", p1, p2);
#endif

    selpsect(P_TEXT);
    printf("jp\tcret\n"
	   "f%d\tequ\t%d\n", p1, p2);
}

/*********************************************************
 * sub_BEE OK++				 Used in: sub_406
 *********************************************************/
void sub_BEE(int p1, int p2) {

#ifdef DEBUG
    printf("\tsub_BEE(%d, %d)\n", p1, p2);
#endif

    selpsect(P_TEXT);
    printf("ld\tde,k%d\n"
	   "ld\tbc,%d\n"
	   "ldir\n"
	   "ld\thl,k%d\n", p1, p2, p1);
    selpsect(P_BSS);
    printf("k%d:defs\t%d\n", p1, p2);
}

/*********************************************************
 * sub_C36 OK++       Used in: sub_C57, sub_CAB, sub_4192
 *********************************************************/
void sub_C36(register struct bbb * sb) {

#ifdef DEBUG
    printf("\tsub_C36(%x)\n", sb);
#endif

    printf("global\t%s\n", sb->b_name);
    sb->b_c3 |= 2;
}

/*********************************************************
 * sub_C57 OK++				Used in: sub_5CF5
 *********************************************************/
void sub_C57(register struct bbb * sb) {

#ifdef DEBUG
    printf("\tsub_C57(%x)\n", sb);
#endif

    if((sb->b_c3 & 1) == 0) {
      if(sb->b_nelem != 0) {
	if((LO_CHAR(sb->b_refl) & 2) == 0) {
	  selpsect(P_BSS);
	  if(sb->b_c13 == 3) {
	    if((sb->b_c3 & 2) == 0) {
	      sub_C36(sb);	/* Emit "global name" */
	    }
	  }
	  sub_CAB(sb);	/* Emit "symbolic_name:" (identifier label) */
	  printf("\tdefs\t%u\n", sb->b_size);
        }
      }
    }
}

/*********************************************************
 * sub_CAB OK++			Used in: sub_B19, sub_C57
 *
 * Emit "symbolic_name:" (identifier label)
 *********************************************************/
void sub_CAB(register struct bbb * sb) {

#ifdef DEBUG
    printf("\tsub_CAB(%x)\n", sb);
#endif

    if((sb->b_c3 & 2)  == 0) {
      if(sb->b_c13 == 3) {
	sub_C36(sb);		/* Emit "global name" */
      }	
    }
    sb->b_c3 |= 1;
    printf("%s:\n", sb->b_name);

}

/*********************************************************
 * sub_CDF OK++				 Used in: sub_808
 * Emit "defb 0, ..." (num bytes)
 *********************************************************/
void sub_CDF(int num) {
    char cnt;

#ifdef DEBUG
    printf("\tsub_CDF(%d)\n", num);
#endif

    cnt = 0;				/* Reset counter bytes printed	   */
    while (num-- != 0) {		/* While data is available	   */
      if(cnt == 0) printf("defb\t0");	/* Initially output "defb 0",	   */
      else	   printf(",0");	/* later ",0"			   */ 
      cnt++;				/* and update number bytes output  */
      if(cnt == 0x10) {			/* If number bytes in string is 16 */
	cnt = 0;			/* Reset counter and		   */
	putchar('\n');			/* continue output in next line	   */
      }
    }					/* continue processing		   */
    if(cnt != 0) putchar('\n');		/* If line is incomplete, new line */
}

/*********************************************************
 * selpsect OK++     Used in: sub_6D1,  sub_793,  sub_B19,
 * 			      sub_B96,  sub_BCC,  sub_BEE,
 * Select psect		      sub_C57,  sub_E43  
 *********************************************************/
void selpsect(int section) {

    static char *off_A592[] = {"", "bss", "text", "data"};

#ifdef DEBUG
    printf("\tselpsect(%d)\n", section);
#endif

    if(section != cursect)  /* Only when changing section */
      printf("psect\t%s\n", off_A592[cursect = section]);
}

/*********************************************************
 * sub_D66 OK+				 Used in: sub_E43
 *
 * Generated code from the C source is completely identical,
 * except for useless code in binary image located after
 * L2++ operator, which does not affect function.
 *********************************************************/
void sub_D66(int * v1, int * v2, int p3) {
    char           mark;
    int          * l2;
    int            l3;
    int            l4, l5;
    register int * s1;

#ifdef DEBUG
    printf("\tsub_D66(%d, %d, %d)\n", v1, v2, p3);
#endif

    do {
      mark = 0;						/* m1: */
      s1   = v1;
      l2   = v2;
      l3   = p3;
      while(0 < --l3) {					/* m4: */
	if((int)*(s1+1) >= (int)*(s1+0)) goto m5;	/* m2: */
	mark    = 1;
	l4      = *(s1+0);
	*(s1+0) = *(s1+1);
	*(s1+1) = l4;
	l5      = *l2;
	*(l2+0) = *(l2+1);
	*(l2+1) = l5;
m3:	s1 = s1 + 1;					/* m3: */
	l2++;		/* <--- CGEN binary image at this point contains useless */
      }			/*      code (see disassembled code in B19.as file)      */
    } while(mark != 0);
    return;

m5: if(*(s1+0) != *(s1+1)) goto m3;			/* m5: */
    uerror("Duplicate case label");
    return;
}

/*********************************************************
 * sub_E43 v2 OK++			 Used in: sub_6D1
 *********************************************************/
void sub_E43(void) {
    struct aaa * l1a;
    int  l2, l3, l5, l4, l6, l7, l8;
    char l9, l10;
    int  v1[255], v2[255];
    register struct aaa * sa;

#ifdef DEBUG
    printf("\tsub_E43()\n");
#endif

    l1a = sub_4192();
    l5 = 0;
    for(;;) {
      sa = sub_600E(sub_4192());			/* m1:  */
      l2 = atoi(sub_306());
      if(sa->a_c0 == DOT_DOT) {
	l6 = l2;
	sub_36E0(sa);
	sub_76F(']');
	if(l5 != 0) break;
	warning("No case\tlabels");
	sub_475C(l1a);
	printf("jp\tl%d\n", l6);
	return;
      }
      if(sa->a_c0 == CONST) {				/* m3:  */
	v1[l5]   = sa->a_l15.ii[0];
	v2[l5++] = l2;
      } else {
        uerror("Non-constant case label");		/* m4:  */
      }
      sub_475C(sa);					/* m5:  */
    }
    sub_D66(v1, v2, l5);				/* m6:  */
    l3 = v1[l5-1] - v1[0];
    if(l3 >= 0) {
      if(l3 < 0x3E80) {
	if((l4*2 + 0x14) < l5*5) {
	  sa        = sub_3712();
	  sa->a_c0  = TYPEOP;
	  sa->a_i14 = l1a->a_i14;
	  sa->a_i12 = l1a->a_i12;
	  sa = sub_43EF(CONV, sub_415E(v1[0]), sa);
	  sa = sub_43EF(SUB, l1a, sa);
	  if(nodesize(sa) != 2) {
	    l1a        = sub_3712();
	    l1a->a_c0  = TYPEOP;
	    l1a->a_i14 = sub_265("us");
	    sa         = sub_43EF(CONV, sa, l1a);
	  }
	  selpsect(P_TEXT);				/* m7:  */
	  sub_3DC9(sub_43EF(RPAREN, sa, 0));
	  l3 = sub_174C(); 	/* word_AE0F++ */
	  printf("ld\ta,%u\n"
		 "cp\th\n" 
		 "jp\tc,l%d\n"
		 "jp\tnz,1f\n" 
		 "ld\ta,%u\n"
		 "cp\tl\n"
		 "jp\tc,l%d\n"
		 "1:add\thl,hl\n"
		 "ld\tde,S%u\n"
		 "add\thl,de\n"
		 "ld\ta,(hl)\n"
		 "inc\thl\n"
		 "ld\th,(hl)\n"
		 "ld\tl,a\n" /* hi         lo	*/
		 "jp\t(hl)\n", l4>>8, l6, l4&~(0xFF00), l6, l3); 
	  selpsect(P_DATA);
	  printf("S%d:\n", l3);
	  l2 = 0;
	  l4 = v1[0];
	  do {
	    if(l4 == v1[l2]) {				/* m8:  */
	      printf("defw\tl%d\n", v2[l2]);
	      l2++;
	    } else {
	      printf("defw\tl%d\n", l6);		/* m9:  */
	    }
	    l4++;					/* m10: */
	  } while(l2 < l5);
	  return;
	}
      }
    }  
    if(nodesize(l1a) == 2) {				/* m11: */
      selpsect(P_TEXT);
      sub_3DC9(sub_43EF(RPAREN, l1a, 0));
      l7 = -1;
      l2 = l8 = l10 = l9 = 0;
      while (l2 < l5) {					/* m20: */
        l7 &= v1[l2];					/* m12: */
        l8 |= v1[l2];
        if(l7>>8 != l8>>8) {
	  if((l7&~(0xFF00)) != (l8&~(0xFF00))) {
	    if((l9 | l10 ) != 0) printf("1:\n");
	    l10 = l9 = 0;				/* m13: */
	    l7  = l8 = v1[l2];
	  }
        }
        if(l7>>8 == l8>>8) {				/* m14: */
	  if(l9 == 0) {
	    printf("ld\ta,h\n");
	    sub_1420(l7>>8);
	    printf("jp\tnz,1f\n"
		   "ld\ta,l\n");
	    l9 = 1;
	  }
	  v1[l2] &= ~(0xFF00);				/* m15: */
        } else {
	  if((char)l10 == 0) {				/* m16: */
	    if(l9 != 0) printf("1:\n");
	    printf("ld\ta,l\n");			/* m17: */
	    sub_1420(l7&~(0xFF00));
	    printf("jp\tnz,1f\n" 
	           "ld\ta,h\n");
	    l10 = 1;
          }
          v1[l2] >>= 8;		/* asar */ 		/* m18: */
          v1[l2] &= ~(0xFF00);
        }
        sub_1420(v1[l2]);				/* m19: */
        printf("jp\tz,l%d\n", v2[l2]);
        l2++;
      }
      if((l9 | l10) != 0) printf("1:\n");
      printf("jp\tl%d\n", l6);				/* m21: */
      return;
    }
    selpsect(P_TEXT);					/* m22: */
    sub_3DC9(sub_43EF(INAREG, l1a, 0));
    l2 = 0;
    while (l2 < l5) {
      if((int)v1[l2] < 0x100) {
	if((int)v1[l2] >= 0xFF80) {
	  sub_1420(v1[l2]);
	  printf("jp\tz,l%d\n", v2[l2]);
	}
      }
      l2++;
    }
    printf("jp\tl%d\n", l6);
}

/*********************************************************
 * sub_1420 OK++			 Used in: sub_E43
 *********************************************************/
void sub_1420(int par) {

#ifdef DEBUG
    printf("\tsub_1420(%d)\n", par);
#endif
	
    printf((unsigned)par ? "cp\t%d\n" : "or\ta\n", par);
}

/*********************************************************
 * sub_143F OK++			Used in: sub_35E6
 *********************************************************/
void sub_143F(uchar reg) {

#ifdef DEBUG
    printf("\tsub_143F(%d)\n", reg);
#endif

    if(reg == 0xF) {
      printf("push\thl\n"
	     "push\tde\n");
      return;
    }
    if(7 >= reg) reg = reg/2 + 0xB;
    printf("push\t%s\n", off_AACA[reg]);
}

/*********************************************************
 * sub_1489 OK++			Used in: sub_35E6
 *********************************************************/
void sub_1489(uchar reg) {

#ifdef DEBUG
    printf("\tsub_1489(%d)\n", reg);
#endif

    if(reg == 0xF) {
      printf("pop\tde\n"
	     "pop\thl\n");
      return;
    }
    if(7 >= reg) reg = reg/2 + 0xB;
    printf("pop\t%s\n", off_AACA[reg]);
}

/*********************************************************
 * sub_14D3 OK++			Used in: sub_1EDF
 *
 * Assigning register "IY" value formal parameter with
 * type register
 *********************************************************/
void sub_14D3(register struct bbb * sb) {

#ifdef DEBUG
    printf("\tsub_14D3(%x)\n", sb);
#endif

    printf("ld\tl,(ix+%d)\n"
	   "ld\th,(ix+%d)\n"
	   "push\thl\n"
	   "pop\tiy\n", sb->b_i11, sb->b_i11+1);
}

/*********************************************************
 * sub_14F3 OK++   Used in: sub_153A, sub_2D09, sub_39CA,
 *			    sub_3A79, sub_3EAA, sub_47B2,
 *			    sub_4FCE, sub_508A, sub_54B6,
 *			    sub_60A8, sub_6246, sub_628F
 *********************************************************/
char sub_14F3(register struct aaa * sa) {

#ifdef DEBUG
    printf("\tsub_14F3(%x)\n", sa);
#endif

    if(bittst(sa->a_i12,1) != 0) return 0;
    if(sa->a_i12 != 0) return REG_L;
    if(1 < (unsigned)sa->a_i14->b_nelem) return 0;
    return sa->a_i14->b_c13;
}

/*********************************************************
 * sub_153A OK++			Used in: sub_2D09
 *********************************************************/
void sub_153A(register struct aaa * sa) {

    static char array_A542[] = {0, 'a', 'l', 'f'};

#ifdef DEBUG
    printf("\tsub_153A(%x)\n", sa);
#endif

    putchar(array_A542[(uchar)sub_14F3(sa)]);
}

/*********************************************************
 * sub_155D OK++			 Used in: sub_793
 *
 * Emit "defb byte1, ..." (from ptr num bytes)
 *********************************************************/
void sub_155D(register char * ptr, int num) {
    char cnt;

#ifdef DEBUG
    printf("\tsub_155D(%x, %d)\n", ptr, num);
#endif

    cnt = 0;				/* Reset counter bytes printed	   */
    while (num-- != 0) {		/* While data is available	   */
      if(cnt == 0) printf("defb\t");	/* Initially output "defb",	   */
      else	   putchar(',');	/* later "," 			   */   
      printf("%d", (uchar)*(ptr++));	/* Output byte and advance pointer */
      cnt++;				/* update number bytes output 	   */
      if(cnt != 0x10) continue; 	/* If number bytes in string is 16 */
      putchar('\n');			/* continue output in next line    */
      cnt = 0;				/* Reset counter and		   */
    }					/* continue processing		   */
    if(cnt != 0) putchar('\n');		/* If line is incomplete, new line */
}

/*********************************************************
 * xx1	 OK++		Used in: Explicit calls are absent
 *********************************************************/
void sub_15D3(int p) {

#ifdef DEBUG
    printf("\tsub_15D3(%d)\n", p);
#endif

    printf("j%d:\n", p);
}

/*********************************************************
 * xx2	 OK++		Used in: Explicit calls are absent
 *********************************************************/
void sub_15E7(int p) {

#ifdef DEBUG
    printf("\tsub_15E7(%d)\n", p);
#endif

    printf("jp\tj%d\n", p);
}

/*********************************************************
 * sub_15FB OK++			Used in: sub_1B0C
 *********************************************************/
void sub_15FB(register struct bbb * sb, int p2, int p3) {

#ifdef DEBUG
    printf("\tsub_15FB(%x, %d, %d)\n", sb, p2, p3);
#endif

    if((HI_CHAR(p2) & 0x80) != 0) goto m3;
    sb->b_c13 = 2;
    if(0xFF < p3) goto m2;
    LO_CHAR(sb->b_size) = 1;
m1: HI_CHAR(sb->b_size) = 0;
    return;

m2: LO_CHAR(sb->b_size) = 2;
    goto m1;

m3: sb->b_c13 = 1;
    if(0x7F < p3)   goto m2;
    if(p2 < 0xFF80) goto m2;
    LO_CHAR(sb->b_size) = 1;
    goto m1;
}

/* End of file - sub_B19.c  */


