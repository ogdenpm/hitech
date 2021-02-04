/*
 * File - sub_1680.c Created 09.03.2019 Last Modified 21.01.2021
 */

#include "stdio.h"
#include <string.h>
#include "cgen.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/*********************************************************
 * sub_1680 OK++			    Used in: main
 *
 * first_init
 *********************************************************/
void sub_1680(void) {
    struct bbb           * sb;
    unsigned               cnt;
    register struct type * tp;

/*
 *	Initializaion of type pointers
 */
    static struct type vars[14] = {  /* sub_1680 */
      {"i",  2, 0, 1}, {"s",  2, 0, 1}, {"c",  1, 0, 1},
      {"l",  4, 0, 1}, {"ui", 2, 0, 2}, {"us", 2, 0, 2},
      {"uc", 1, 0, 2}, {"ul", 4, 0, 2}, {"f",  4, 0, 3},
      {"d",  4, 0, 3}, {"x",  2, 0, 1}, {"ux", 2, 0, 2},
      {"b",  0, 0, 0}, {"v",  0, 0, 0}
    };

#ifdef DEBUG
    printf("\tsub_1680()\n");
#endif

    /* Clear hash table */

    blkclr((char *)hashtab, sizeof(hashtab));

    /* Create a hash table of templates for standard types */

    cnt = ARRAY_SIZE(vars);
    tp = vars;
    do {
      sb = sub_265(tp->t_str);
      sb->b_class  = TDECL;
      sb->b_i11    = tp->t_alig;
      sb->b_size   = tp->t_size;
      sb->b_c13    = tp->t_flag;
      tp++;
      cnt--;
    } while (cnt != 0);

    /* Additional patterns for types */

    word_AE11 = sub_265("l");	/* long	  	*/
    word_AED7 = sub_265("d");	/* double 	*/
    word_AF1B = sub_265("b");	/* b   	  	*/
    word_AFE9 = sub_265("v");	/* variable 	*/
    word_AED9 = sub_265("c");	/* char   	*/
    word_AE53 = sub_265("uc");	/* uchar  	*/
    word_AF1D = sub_265("x");	/* x      	*/
    lvlidx = -1;
}

/*********************************************************
 * sub_174C OK++    Used in: sub_E43,  sub_17E0, sub_39CA,
 *			     sub_4192, sub_508A
 *********************************************************/
int sub_174C(void) {

#ifdef DEBUG
    printf("\tsub_174C()\n");
#endif

    return ++word_AE0F;
}

/*********************************************************
 * sub_1754 OK++    Used in: sub_17E0, sub_19C1, sub_1B0C
 *********************************************************/
struct bbb * sub_1754(char * token, int p2) {
    struct          bbb **l1b;
    register struct bbb * sb;

#ifdef DEBUG
    printf("\tsub_1754(%s, %d)\n", token, p2);
#endif
	
    sb = sub_265(token);			/* Set pointer to struct associated with   */
						/* pointer to token.			   */
    if((uchar)sb->b_ndpth != nstdpth) {		/* If nesting depth not correspond current,*/
      l1b        = gethashptr(token);		/* Get pointer to pointer to struct from   */
      sb         = allocmem(sizeof(struct bbb));/* hash table. Create new struct and save  */
      sb->b_next = *l1b;			/* pointer to struct from hash table in    */
      						/* struct as associated with it. 	   */
      *l1b       = sb;				/* Save pointer to this struct in current  */
						/* position hash table.			   */
      sb->b_name = allocmem(strlen(token)+1);	/* Get memory address allocated for token  */ 
						/* and assign it to corresponding member.  */
      strcpy(sb->b_name, token);		/* Copy specified token to this address.   */
      sb->b_ndpth = nstdpth;			/* Save current nesting depth in struct    */
/*
      if(++symcnt > dynmem)   dynmem = symcnt;
*/
    }
    sb->b_class = p2;
#ifdef DEBUG
    printf("\tsub_1754\t\tReturn %x\n", sb);
#endif
    return sb;
}

/* End of file sub_1680.c  */


