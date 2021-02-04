/*
 * File - sub_6D1.c Created 09.03.2019 Last Modified 26.05.2020
 */
 
#include "stdio.h"
#include "cgen.h"

enum psect {
  P_BSS = 1,
  P_TEXT,
  P_DATA
};

/*********************************************************
 * sub_6D1 OK+				    Used in: main
 *
 * Compiling intermediate code
 *
 * Note:
 * Compiler generates identical code from restored source
 * program in C, however, location of branches associated
 * with case constants is different from original.
 * This does not affect the function.
 *********************************************************/
void sub_6D1(void) {
    register char * ch;
    int tok;

#ifdef DEBUG
    printf("\n\tsub_6D1 - Compiling_intermediate_code()\n\n");
#endif

    word_B017 = 0x17F;
    while((ch = sub_306()) != (char *)EOF) { /* get_token    */

#ifdef DEBUG
      tok = sub_1B2(ch);
      printf("\tsub_6D1\t\t\ttok = %x tok-50 = %x\n", tok, tok-50);
      switch (tok-50) {
#else
      switch ((tok = sub_1B2(ch))-50) {	     /* search_token */
#endif
	case 0:		/* "[\\" - case		*/
	  sub_E43();
	  break;
	case 1:		/* "[a" 		*/
	  sub_793();
	  break;
	case 2:		/* "[c" enum		*/
	  sub_1B0C();
	  break;
	case 3:		/* "[e" expression	*/
	  selpsect(P_TEXT);
	  sub_3DC9(sub_4192());
	  sub_76F(']');
	  break;
	case 4:		/* "[i" initialization	*/
	  sub_B19();
	  break;
	case 5:		/* "[s" struct		*/
	case 6:		/* "[u" union		*/
	  sub_19C1(tok);
	  break;
	case 7:		/* "[v" variable	*/
	  sub_17E0();
	  break;
	case 9:		/* "{" opening block 	*/
	  nstdpth++;		/* Increase the current nesting depth */
	  break;
	case 12:	/* "}" end of block 	*/
	  sub_406();
	  break;
	case 8:		/* "^" 			*/
	case 10:	/* "|" 			*/
	case 11:	/* "||" 		*/
	default:
	  sub_6C8();		/* {faterror("Bad int. code");} */ 
      }
    }
    sub_406();
}	

/* End of file sub_6D1.c */


