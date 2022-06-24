#include "p1.h"

bool inFunc;        /* a288 */
uint8_t byte_a289;  /* a289 */
bool unreachable;  /* a28a */
int16_t word_a28b;  /* a28b */
s25_t *curFuncNode; /* a28d */
s25_t *pn_a28f;     /* ad8f */

/**************************************************
 * 81: 3ADF
 **************************************************/
void sub_3adf() {
    char tok; /* (ix+-1)    */ /* local variables are some structure  */
    uint8_t var2;              /* (ix+-2)    */
    int16_t var6;              /* (ix+-3)    */
    /* (ix+-4)    */
    int16_t var7; /* (ix+-5)    */
    /* (ix+-6)    */
    int16_t l5; /* (ix+-7)    */
    /* (ix+-8)    */
    int16_t *l6; /* (ix+-9)    */
    s8_t varA;
    /* (ix+-10) A */
    uint8_t varB; /* (ix+-11) B */
    uint8_t varC; /* (ix+-12) C */

    register s25_t *st; /* possibly a different structure */

    varC = sub_5dd1(&var2, &varA);
    if ((tok = yylex()) == T_SEMI)
        return;
    ungetTok = tok;
    varB     = 1;

    for (;;) {
        pn_a28f = 0;
        st      = sub_69ca(var2, &varA, varC & 0xFE);
        tok     = yylex();

        if (st && (st->m18 & 0x10) && st->n_c7 == 2) {
            if (varB && tok != T_COMMA && tok != T_SEMI && var2 != T_TYPEDEF) {
                byte_a289 = st->n_c7 == 2 && st->n_i4 == 0 && (st->n_dataType == DT_VOID || st->n_dataType == DT_INT);
                ungetTok  = tok;
                sub_516c(st);
                sub_0493(st);
                curFuncNode = st;
                sub_409b();
                return;
            }
            if (pn_a28f && !(pn_a28f->m18 & 0x10))
                expectedErr("function body");

            ++inFunc;
            checkScopeExit();
            --inFunc;
            ??PMO
            sub_0493(st);
            goto m13;
        }
        if (tok == 0x64) { /* m8: */
            if (var2 == 0x2D) {
                prError("illegal initialisation");
            }
            sub_516c(st); /* m9: */
            sub_0493(st);
            sub_3c7e(st);
            tok = yylex();
            goto m13;
        }
        if (st != 0) { /* m10: */
            if (bittst(varC, 0) != 0 && st->m20 != T_EXTERN) {
                sub_516c(st); /* m11: */
                sub_0493(st);
            } else {
                sub_01ec(st); /* m12: */
            }
        }
    m13:
        if (tok == 0x73)
            goto m14;
        if (tok == 0x50)
            goto m14;
        goto m16;

    m14:
        expectedErr(",");
        ungetTok = tok;

    m15:
        varC = 0;
    }

m16:
    if (tok == 0x71)
        goto m15;
    if (tok == 2)
        return;
    expectedErr(";");
    while (3 < tok) {  /* m18: */
        tok = yylex(); /* m17: */
    }
    /*#endif*/
}

/**************************************************
 * 82: 3C7E
 **************************************************/
void sub_3c7e(s25_t *p1) {
    struct xxx *ch;

    if (p1 != 0) {
        printf("[i ");
        sub_573b(p1, stdout);
        putchar('\n');
        st = p1;
        ch = sub_3d24(st, 1);
        if (bittst(ch, 7) != 0) {
            prError("initialisation syntax");
            skipToSemi();
            /* goto m2; */
        } else if (st->m7 == 1) { /* m1: */
            if (st->m2 != 0) {
                if (sub_2105(st->m2) != 0) {
                    sub_2569(st->m2);
                    st->m2 = allocIConst(ch);
                }
            }
        }
        printf("]\n"); /* m2: */
        return;
    }
    skipToSemi(); /* m3: */
}

/**************************************************
 * 83: 3D24
 **************************************************/
int16_t sub_3d24(register struct xxx *st, char p2) {
    int16_t ch;
    char l2;
    s13_t *l3;
    char l4;
    s13_t *l5;
    int16_t l6;
    char l7;
    s13_t *l8;
    char l9;

    ch = -1;
    if (p2 != 0) {
        if (st->m8 == 1) {
            if (st->m4 != 0) {
                printf(":U ..\n");
                /*
                        l2 = sub_2671();
                        l4 = (l2 == 4);
                        if(l4 != 0) l2 = sub_2671();
                */
                if ((l4 = ((l2 = yylex()) == 4)) != 0)
                    l2 = yylex();
                if (l2 == 0x76) { /* m2: */
                    if (st->m6 == 0) {
                        if (((int16_t)(st->m7) & 0xFE) == 4) {
                            ch = st->m7 & 0xFE; /* ERROR */
                            l3 = word_9dcb;
                            while (ch < strChCnt) {                  /* m4: */
                                printf("-> %d `c\n", (char)*(l3++)); /* m3: */
                                ++ch;
                            }
                            free(word_9dcb);
                            if (sub_2105(st->m4) != 0) {
                                printf("-> %d `c\n", 0);
                                ++ch;
                            }
                            if (l4 != 0)
                                l2 = yylex(); /* m5: */
                        m6:
                            if (l4 != 0) {
                                if (l2 != 3) {
                                    expectedErr("}");
                                    ch = -1;
                                }
                            }
                            printf("..\n"); /* m7: */
                            goto m34;
                        }
                    }
                }
                if (l4 == 0) { /* m8: */
                    expectedErr("{");
                    goto m6;
                }
                ungetTok = l2; /* m9: */
                if (st->m6 != 0 && st->m7 != 0x16) {
                    p2 = 0; /* m10: */
                } else {
                    st = st->m1;
                }
                ch = 0; /* m11: */
                for (;;) {
                    if (bittst(sub_3d24(st, p2), 7) != 0)
                        goto m6; /* m12: */
                    ++ch;
                    l2 = yylex();
                    if (l2 == 3)
                        goto m6;
                    if (l2 != 0x71)
                        goto m6;
                    l2 = yylex();
                    if (l2 == 3)
                        goto m6;
                    ungetTok = l2;
                } /* goto m12; */
            }
        }
    }
    if (p2 == 0)
        goto m14; /* m13: */
    if (st->m8 == 1)
        goto m25;

m14:
    if (st->m6 != 0)
        goto m25;
    if (st->m7 != 0x1A)
        goto m25;
    if (p2 != 0)
        printf(str_U);
    printf(str_U); /* m15: */
    l5 = st->m1;
    if (l5 == 0)
        goto m24;
    l2 = yylex();
    l7 = (l2 == 4); /* m16: */
    if (l7 == 0)
        ungetTok = l2;
    l6 = l5->m5.m6; /* l6 = l5->m10; */ /* m17: */

m18:
    if (bittst(sub_3d24(l6, 1), 7) != 0)
        goto m19;
    l6 = 0; /* l6 = l6->m5.m6; l6 = l6->m10; */ /* ERROR */
    if (l6 == l5)
        goto m19;
    l2 = yylex();
    if (l2 == 0x71)
        goto m21;
    ungetTok = l2;

m19:
    if (l7 == 0)
        goto nVName;
    l2 = yylex();
    if (l2 == 0x71)
        l2 = yylex();
    if (l2 == 3)
        goto nRefCnt; /* m20: */
    expectedErr("}");
    goto m24;

m21:
    if (l7 == 0)
        goto m18;
    l2       = yylex();
    ungetTok = l2;
    if (ungetTok != 3)
        goto m18;
    goto m19;

nRefCnt:
    ch = 1;
    goto m24;

nVName:
    ch = 1;
    goto m24;

m24:
    printf("..\n");
    if (p2 != 0)
        printf("..\n");
    goto m34;

m25:
    if (p2 == 0)
        goto m27;
    if (p2 == 1)
        goto m33;

m27:
    if (p2 == 2)
        goto m33;
    if (bittst(st->m6, 0) != 0)
        goto m28;
    if (st->m7 < 0x14)
        goto m28;
    goto m33;

m28:
    if ((l9 = ((l2 = yylex()) == 4)) == 0)
        ungetTok = l2;                /* m29: */
    (l8 = allocSType(st))->m5.m7 = 0; /* m30: */
    l8                           = sub_1441(0x7d, l8, sub_0a83(3));
    if (l8 != 0)
        sub_05b5(l8->m1.s[1]);
    if (l9 != 0 && yylex() != 3)
        expectedErr("}"); /* m31: */
    sub_2569(l8);        /* m32: */
    ch = 1;
    goto m34;

m33:
    prError("illegal initialisation");

m34:
    return ch;
}
