/*
 * File - sub_6D1C.c Created 09.03.2019 Last Modified 26.05.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_6D1C v2 OK++	      Used in: sub_6D61, cmalloc
 *********************************************************/
void * sub_6D1C(register char * p1, int p2) {

#ifdef DEBUG
    printf("\tsub_6D1C(%x, %x)", p1, p2);
#endif

    if(0x80 < p2) {
      *((int *)p1) = p2-3;
      p1 += 3;
      *((char *)p1-1) = 0x80;	/* bug in compiler v3.09 */
    } else {
      *(char *)p1 = (char)p2-1;
      p1++;
    }
#ifdef DEBUG
    printf("\tReturn %x\n", p1);
#endif
    return p1;
}

/*********************************************************
 * sub_6D61 v4 OK++		 	  Used in: cmalloc
 *
 * Compiled code is not significantly different from binary
 * image	
 *********************************************************/
int sub_6D61(void) {
    struct ptr          * l1;
    struct ptr          * l2;
    struct ptr          * l3;
    struct ptr          * l4;
    char                  l5;	/* Senseless variable */
    register struct ptr * st;

#ifdef DEBUG
    printf("\tsub_6D61()\n");
#endif

    l5 = 0;
m1: l4 = &word_B023.next;
    while((st = l4->next_ptr) != 0) {				/* m17: */
      l2 = st;							/* m2:  */
      if(bittst(*((char*)st-1),7) != 0)
        l2 = (struct ptr *)((int)l2 - 3); 			/* m3:  */	/* cast to "struct ptr *" from smaller integer type "int" */
      else
        l2 = (struct ptr *)((int)l2 - 1); 
      l3 = &word_B023.next;					/* m4:  */	/* cast to "struct ptr *" from smaller integer type "int" */
      while((l1 = l3->next_ptr) != 0) {				/* m16: */  
        if(((bittst((unsigned)((uchar)*((char*)l1-1)),7) ?	/* m5:  */
        (unsigned)*((int *)((char *)l1-3)) :			/* m6:  */
        (uchar)*((char *)((char *)l1-1))) + (int)l1) == l2) {	/* m7:  */	/* comparison "unsigned int" and "struct ptr *" */
          if(l3 == st) {					/* m17: */
            l4->next_ptr = l1->next_ptr;
          } else {
            if(l4 == l1) {					/* m8:  */
              l3->next_ptr = st->next_ptr;
            } else {
              l3->next_ptr = l1->next_ptr;			/* m9:  */
              l4->next_ptr = st->next_ptr;
            }
          }
          if((bittst((char)(container_of(l1, struct header1, next))->size,7)) != 0 ) /* m10 */
            l1 = (struct ptr *)((int)l1 - 3);
          else
            l1 = (struct ptr *)((int)l1 - 1); 			/* m11: */
          sub_7028((void *)sub_6D1C((char *)l1, (0-(int)l1) +	/* m14: */
          ((bittst(*((uchar*)st-1),7)) != 0 ? 			/* m12: */
          *((int *)((char *)st-3)) :				/* m13: */
          *((uchar *)st-1)) + (int)st));
          l5 = 1;
          goto m1;
        }
        l3 = l1;						/* m15: */
      }
#ifdef DEBUG
      printf("\tsub_6D61\t\tReturn %x\n", st);
#endif
      l4 = st;
    }
}

/*********************************************************
 * cmalloc v2 OK++			Used in: allocmem
 *********************************************************/
void * cmalloc(unsigned p1) {
    char	  * l1;	
    unsigned 	    l2;	
    uchar	    l3;
    register char * sst;

#ifdef DEBUG
    printf("\tcmalloc(%u)\n", p1);
#endif

    if(p1 < 2) p1 = 2;
    l3 = 0;
    do {
      sst = (char *)&word_B023+1;
      while((l1 = (char *)(*((int *)sst))) != 0) {	/* cast to "char *" from smaller integer type "int" */
	if((bittst((unsigned)((uchar)*((char*)l1-1)),7) ?
	(unsigned)*((int *)((char *)l1-3)) :
	(uchar)*((char *)((char *)l1-1))) >= p1) {
	  *((int *)sst) = *((int *)l1);			/* sst->ptr = l1->ptr */
	  sst = l1;
	  if(p1+6 < (l2 = (bittst(*((uchar*)sst-1),7) != 0) ?
	  (unsigned)*((int *)((uchar*)sst-3)) : *((uchar*)sst-1))) {
	    l1 = p1 + sst;
	    sub_7028((void *)sub_6D1C(l1, l2-p1));
	    if(bittst(*((char*)sst-1),7) != 0)
	      sst += -3;
	    else
	      sst += -1;
	    return (void *)sub_6D1C(sst, p1);
	  }
	  return sst;
	}
	sst = l1;
      }
      if(((char)l3) != 0) break;
    } while ((l3 = sub_6D61()) != 0);

    l2 = ((p1 < 0x80)) ? (unsigned)1 : (unsigned)3;
    if((sst = sbrk(p1+l2)) == ((char *) -1)) return 0;
    return (void *)sub_6D1C(sst, p1+l2);
}

/*********************************************************
 * sub_7028 v6 OK++  Used in: sub_406,  sub_36E0, sub_374C
 *			      sub_5DF6, sub_6D61, cmalloc
 *
 * Function consisting only of macros generates code exactly
 * corresponding to original and does not generate any
 * diagnostic messages when compiled. Algorithm used to
 * allocate and manage memory by an ordinary person is
 * perceived with great difficulty.
 *********************************************************/
void sub_7028(struct ptr * p1) {
    register struct ptr * st;

#ifdef DEBUG
    printf("\tsub_7028(%x)\n", p1);
#endif

    st = &word_B023.next;
    while((st->next_ptr != 0) && 	/* m2: */
    (((bittst((container_of(st->next_ptr, struct header1, next))->size,7)) ?
    ((container_of(st->next_ptr, struct header2, next))->size) :
    ((container_of(st->next_ptr, struct header1, next))->size)
    ) < 
    ((bittst((container_of(p1, struct header1, next))->size,7)) ?
    ((container_of(p1, struct header2, next))->size) :
    ((container_of(p1, struct header1, next))->size)))) {
      st = st->next_ptr;		/* m1: */
    }
    p1->next_ptr = st->next_ptr;	/* m7: */
    st->next_ptr = p1;
}

/* End of file sub_6D1C.c  */


