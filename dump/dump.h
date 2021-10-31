#ifdef __STDC__
# define	P(s) s
#else
# define P(s) ()
#endif


/* dump.c */
/*     235 */ int main P((int argc , char **argv ));
/*     264 */ void prc_rec P((void ));
/*     279 */ int chk_rec P((void ));
/*     301 */ void cod_text P((void ));
/*     341 */ void cod_psect P((void ));
/*     363 */ void cod_reloc P((void ));
/*     380 */ void cod_sym P((void ));
/*     419 */ void cod_start P((void ));
/*     427 */ void cod_end P((void ));
/*     435 */ void cod_ident P((void ));
/*     453 */ void cod_xpsect P((void ));
/*     468 */ void err_handling P((char *p1 , int p2 , int p3 , int p4 , int p5 ));
/*     486 */ void error P((int p1 , int p2 , int p3 , int p4 , int p5 ));
/*     493 */ void err_handling P((char *fmt , va_list args ));
/*     507 */ void error P((char *fmt , ...));
/*     520 */ uint calc_val P((uchar *p1 ));
/*     526 */ ulong calc_long P((uchar *p1 ));

#undef P
