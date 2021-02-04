/*
 * File - sub_1B2.c Created 09.03.2019 Last Modified 21.01.2021
 */

#include "stdio.h"
#include <string.h>

#include "cgen.h"

/*********************************************************
 * char sub_1B2 OK++	       Used in: sub_6D1, sub_4192
 *
 * Token search		(Binary search algorithm is used)
 *********************************************************/
char sub_1B2(register char * target) {
    unsigned char hi, lo, mid;
    char midVal;

    static char * tnames[] = {
    "",    "!",  "!=",  "#",  "$",  "$U", "%",  "&",  "&&", "&U",		
    "(",   ")",  "*",   "*U", "+",  "++", "+U", ",",  "-",  "--",		
    "->",  "-U", ".",   "..", "/",  ":",  ":U", ":s", ";",  ";;",		
    "<",   "<<", "<=",  "=",  "=%", "=&", "=*", "=+", "=-", "=/",		
    "=<<", "==", "=>>", "=^", "=|", ">",  ">=", ">>", "?",  "@",		
    "[\\", "[a", "[c",  "[e", "[i", "[s", "[u", "[v", "^",  "{",		
    "|",   "||", "}",   "~", "RECIP", "TYPE", "ID", "CONST",	
    "FCONST", "REG", "INAREG", "BITFIELD" };

    static char byte_A46A = 65;

#ifdef DEBUG
        printf("\tsub_1B2(\"%s\")\t", target);
#endif

    lo = 0;
    hi = byte_A46A;
    do {
      mid = (hi + lo)/2;
      if((midVal = strcmp(target, tnames[mid])) == 0) {
#ifdef DEBUG
        printf("\tReturn = %d\n", mid);
#endif
        return mid; 
      }
      if(midVal < 0) hi = mid - 1;
      else           lo = mid + 1;
    } while(hi >= lo);
    return (-1); /* Search terminates as unsuccessful */
}

/*********************************************************
 * gethashptr OK++		Used in: sub_265, sub_1754
 *
 * Convert name to a hash table ptr (sub_21F)
 *
 * Returns pointer to pointer to structure associated with
 * pointer to token.  for example
 *
 * Input	Hash key  Destination
 * string  	dec hex
 *   "f"  	 1	- float
 *   "i"  	 4	- int
 *   "l"  	 7	- long
 *   "s"  	14 0eh	- short
 *   "v"  	17 11h	- void
 *   "x"  	19 13h	- x ?
 *   "uc" 	30 1eh	- unsigned char
 *   "ui" 	36 24h	- unsigned int
 *   "ul" 	39 27h	- unsigned long
 *   "us" 	46 2eh	- unsigned short
 *   "ux" 	51 33h	- unsigned ?
 *   "b"  	98 62h	- b ?
 *   "c"  	99 63h	- char
 **********************************************************/

#define HASHTABSIZE (unsigned)0x65

struct bbb ** gethashptr(register char * sname) {
    unsigned int key;

#ifdef DEBUG
    printf("\tgethashptr(%s)\n", sname);
#endif

    key = 0;
    while((uchar)*sname != 0) {
      key = key*2 + (uchar)*sname; /* Get numeric value of key */
      sname++;
    }
    /* Hash table index is determined by    */
    /* hash function using division method  */
    return &hashtab[key%HASHTABSIZE];
}

/*********************************************************
 * sub_265 OK++	     Used in: sub_627,  sub_B19,  sub_E43,
 *			      sub_1680, sub_1754, sub_4192
 *
 * Return pointer to struct associated with pointer to token
 *********************************************************/
struct bbb * sub_265(char * str) { 
    struct bbb		 ** l1b;
    register struct bbb   * sb;

#ifdef DEBUG
    printf("\tsub_265(%s)\n", str);
#endif
					  /* In hash table, we look for pointer to    */
    l1b = gethashptr(str);		  /* entry in symbol table associated with    */
    sb  = *l1b;				  /* specific name. 			      */
    while(sb != 0) {			  /* While record is not the last in list,    */
    					  /* we check whether its name is correlated  */
      if(strcmp(sb->b_name, str) == 0) {  /* with a specific one.		      */
#ifdef DEBUG
        printf("\tsub_265\t\t\tReturn %x\n", sb);
#endif
        return sb;			  /* If such entry exists, return pointer to  */
     }					  /* it. Otherwise,			      */
      sb = sb->b_next;			  /* we check record associated with it.      */
    }					  /* If record does not exist,		      */
    sb = allocmem(sizeof(struct bbb));	  /* create new record. As record associated  */
    sb->b_next = *l1b;			  /* with it, we save pointer found in hash   */
					  /* table.				      */
    sb->b_name = allocmem(strlen(str)+1); /* We allocate place under name and	      */
    strcpy(sb->b_name, str);		  /* give her a specific name; 		      */
    sb->b_ndpth = nstdpth;		  /* correlate it with current nesting depth; */
    *l1b     = sb;			  /* save pointer to it at current hash table */
/*
    if(++symcnt > dynmem) dynmem = symcnt;
*/
#ifdef DEBUG
    printf("\tsub_265\t\t\tReturn %x\n", sb);
#endif
    return sb;				  /* position and return pointer to record.   */
}

/* End of file -  sub_1B2.c */


