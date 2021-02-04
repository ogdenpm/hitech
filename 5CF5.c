/*
 * File - sub_5CF5.c Created 09.03.2019 Last Modified 17.06.2020
 */

#include "stdio.h"
#include "cgen.h"

/*********************************************************
 * sub_5CF5 OK+			Used in: sub_406, sub_17E0
 *
 * Compiler generates identical code, however, location
 * of branches associated with case constants is different
 * from original. This does not affect the function.
 *********************************************************/
void sub_5CF5(register struct bbb * sb, int p2) {

#ifdef DEBUG
    printf("\tsub_5CF5(%x, %d)\n", sb, p2);
#endif

    switch(sb->b_c13) {
      case 1:
	if(sub_61AA(sb, p2) == 0) {
	  array_AE13[lvlidx] -= sb->b_size;
	  if((sb->b_i11 = array_AE13[lvlidx]) < 0xFF80) {
	    if(sb->b_size >= 4) {
	      warning("%s: large offset", sb->b_name);
	    }
	  }
	}
	break;
      case 3:
      case 4:
	sub_C57(sb);
	break;
      case 5:
	sb->b_i11 = array_AE97[lvlidx];
	array_AE97[lvlidx] += sb->b_size;
	if(sb->b_size == 1) {
	  switch(sb->b_type->b_class) {
	    case SDECL:
	    case UDECL:
	      break;
	    default:
	      array_AE97[lvlidx]++;
	  }
	}
	if((char)sub_61AA(sb, p2) == 0) sb->b_c13 = 1;
    }
}

/* End of file sub_5CF5.c  */


