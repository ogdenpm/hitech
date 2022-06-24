#include "p1.h"

s13_t *p13List    = &s13_9d1b; /* 8bc7 */
int16_t strId     = 0;         /* 8bd7 */
uint8_t byte_8f85 = 0;         /* 8f85 */
uint8_t byte_8f86 = 0;         /* 8f86 */

int16_t word_968c;  /* 968c */
int16_t tmpLabelId; /* 968e */

s13_t **s13SP;   /* 9cf1 */
s13_t *s13_9cf3; /* 9cf3 */
char pad9d00[27];
s13_t s13_9d1b; /* 9d1b */
s13_t s13_9d28; /* 9d28 */

s13_t *s13FreeList; /* 9d35 */
uint8_t byte_9d37;  /* 9d37 */
s13_t *s13Stk[20];  /* 9d38 */

/**************************************************
 * 17: 07F5 PMO
 **************************************************/
s25_t *sub_07f5(char p1) {
    char l1;
    register s25_t *st;

    l1        = byte_9d37;
    byte_9d37 = p1;
    st        = sub_0bfc();
    byte_9d37 = l1;
    return st;
}

/**************************************************
 * 18: 0817 PMO
 **************************************************/
s13_t *sub_0817(register s8_t *st) {
    int16_t var2;
    int16_t var4;
    s13_t *var6;
    uint8_t tok;
    s13_t *arr[128];

    if (st && st->c7 != 2 && st->i4 == 1 && st->dataType == DT_POINTER && st->u1.chain8->c7 == 2)
        st = st->u1.chain8;
    else if (st->c7 != 2)
        prError("function or function pointer required");

    if (st && st->c7 == 2 && st->ps10) {
        var4 = st->ps10->cnt;
        st   = st->ps10->s8array;
    } else {
        st   = NULL;
        var4 = 0;
    }

    var2     = 0;
    ungetTok = tok = yylex();
    for (;;) {
        if (st && st->dataType == DT_24) {
            var4 = 0;
            st   = 0;
        }
        if (tok != T_RPAREN) {
            if (st && sub_5a76(st, DT_VOID)) {
                prError("function does not take arguments");
                var4 = 0;
                st   = NULL;
            }
            var6 = sub_1441(T_60, sub_07f5(3));
            if (var6) {
                if (st && var4-- == 0) {
                    prError("too many arguments");
                    st   = 0;
                    var4 = 0;
                }
                if (st)
                    var6 = sub_1f5d(var6, st++);
                else
                    var6 = sub_1d02(var6);
                arr[var2++] = var6;
                tok         = yylex();
                if (tok != T_COMMA)
                    continue;
                ungetTok = tok;
            }
        }
        break;
    }
    if ((var4 != 1 || var2 != 0 || !sub_5a76(st, DT_VOID)) && var4 && st->dataType != DT_24)
        prError("too few arguments");

    if (var2 == 0)
        return sub_23b4(T_120, NULL, NULL); /* dummy 2nd & 3rd args added */
    var4 = 0;
    while (var4 + 1 != var2) {
        arr[var4 + 1] = sub_23b4(T_COMMA, arr[var4], arr[var4 + 1]);
        ++var4;
    }
    return arr[var4];
}

/**************************************************
 * 19: 0A83 PMO
 **************************************************/
s13_t *sub_0a83(uint8_t n) {
    register s13_t *st;

    byte_9d37 = n;
    if ((st = sub_1441(T_60, sub_0bfc(), 0))) { /* PMO added dummy arg3 */
        if (!sub_0aed(st))
            prError("constant expression required");
        else if (byte_9d37 == 2) {
            if (isValidDimType(&st->attr))
                st = sub_1ccc(st, DT_CONST);
            else
                prError("illegal type for array dimension");
        }
    }
    byte_9d37 = 0;
    return st;
}

/**************************************************
 * 20: 0AED PMO
 **************************************************/
bool sub_0aed(register s13_t *st) {
    uint8_t type, flags;

    if (st == 0)
        return true;
    type = st->tType;
    if (type == T_ID)
        return sub_5a76(&st->attr, DT_ENUM);
    if (type == T_SIZEOF)
        return true;
    if (type == D_ADDRESSOF && sub_0b93(st->t_ps25))
        return true;
    flags = opTable[(type - 60)].uc4;
    if (!(flags & 0x10))
        return false;
    if (flags & 1)
        return true;
    return sub_0aed(st->t_next) && (flags & 2) && sub_0aed(st->t_alt);
}

/**************************************************
 * 21: 0B93 PMO
 **************************************************/
int16_t sub_0b93(register s13_t *st) {
    uint8_t type;

    type = st->tType;
    if (type == T_ID)
        return st->t_ps25->m20 == T_EXTERN || st->t_ps25->m20 == T_STATIC;
    if (type == T_DOT)
        return sub_0b93(st->t_next);
    if (type == T_69)
        return sub_0aed(st->t_next) != 0;
    return 0;
}

/**************************************************
 * 22: 0BFC
 **************************************************/
s13_t *sub_0bfc() {
}

/**************************************************
 * 23: 10A8 PMO
 **************************************************/
bool sub_10a8() {
    s13_t *l1;
    s13_t *l2;
    uint8_t tok;
    register s13_t *st;

    if ((tok = sub_255d()) == T_LPAREN)
        return false;

    l1 = NULL;
    if (tok != T_120 &&
        (((opTable[tok - T_60].uc4 & 2) && (l1 = popS13()) == NULL) || (st = popS13()) == NULL))
        return true;

    switch (tok) {
    case T_64:
        sub_2529(T_69);
        p13List[1] = T_EQ;
        tok        = T_PLUS;
        if (isValidDimType(&l1->attr))
            l1 = sub_1ccc(l1, DT_CONST);
        else
            prError("illegal type for index expression");
        break;
    case T_INC:
    case T_75:
    case T_DEC:
    case T_77:
        l1  = &s13_9d28;
        tok = tok == T_INC ? T_PLUSEQ : tok == T_DEC ? T_MINUSEQ : tok == T_75 ? T_102 : T_104;
        break;
    case T_POINTER:
        tok = T_DOT;
        st  = sub_1441(T_69, st, 0); /* added dummy 3rd arg */
        break;
    case T_SIZEOF:
        if (st->tType == T_SCONST) {
            l2 = sub_1b4b((long)st->t_i2 + 1, DT_UINT);
            sub_2569(st);
            pushS13(l2);
            return false;
        }
        if (st->tType != S_TYPE && st->tType != T_ID) {
            l2            = allocSType(&st->attr);
            l2->attr.ps25 = NULL; /* PMO to check one of several options */
            l2->attr.c7   = 0;
            if (st->attr.c7 == 1) {
                l2  = sub_1441(T_SIZEOF, l2, 0);
                l1  = sub_1ccc(sub_21c7(st->attr.ps13), DT_UINT);
                tok = T_STAR;
            }
            sub_2569(st);
            st = l2;
        } else if (st->tType == S_TYPE && st->attr.c7 == 1) {
            l1  = sub_1ccc(sub_21c7(st->attr.ps13), DT_UINT);
            st  = sub_1441(T_SIZEOF, st, 0);
            tok = T_STAR;
        }
        break;
    case T_COMMA:
        if (p13List->tType != T_LPAREN || p13List->t_ca[1] != T_61)
            tok = T_114;
        break;
    case T_79:
        pushS13(sub_1bf7(sub_1441(T_60, l1, 0), &st->attr));
        sub_2569(st);
        return 0;
    }
    if ((l1 && l1->tType == T_COLON) != (tok == T_QUEST))
        return true;
    pushS13(sub_1441(tok, st, l1));
    return false;
}

/**************************************************
 * 24: 1340 PMO
 **************************************************/
s13_t *sub_1340(register s13_t *st, s13_t *p2) {
    s25_t *var2;
    s25_t *var4;

    if (!sub_5a76(&st->attr, DT_STRUCT) && !sub_5a76(&st->attr, DT_UNION))
        prError("struct/union required");
    else if (p2->tType != T_ID)
        prError("struct/union member expected");
    else if ((var4 = st->attr.ps25) == 0)
        ;
    else if (var4->m18 & 1)
        prError("undefined struct/union: %s", var4->nVName);
    else if ((var2 = findMember(var4, p2->t_ps25->nVName))) {
        sub_51cf(var2);
        st       = s13Alloc(T_126);
        st->t_i0 = var2->m14;
        st->attr = var2->attr;
        sub_2569(p2);
        return st;
    }
    return p2;
}

/**************************************************
 * 25: 1441 PMO
 **************************************************/
s13_t *sub_1441(uint8_t p1, register s13_t *lhs, s13_t *rhs) {
    s8_t tmpExpr;
    s13_t *savedLhs;
    s13_t *minusLhs;
    bool hasRhs;
    bool minusLhsValid;
    int16_t opFlags;
    char *opStr;
    uint8_t var13;

    hasRhs = (opTable[p1 - 60].uc4 & 2) != 0;
    opStr  = opTable[p1 - 60].s0;
    if (!lhs || (hasRhs && rhs == 0)) {
        sub_2569(lhs);
        if (hasRhs)
            sub_2569(rhs);
        return NULL;
    }
    minusLhsValid = false;
    opFlags       = opTable[p1 - 60].i5;
    if (p1 == D_ADDRESSOF && lhs->tType == T_ID && (lhs->t_ps25->m18 & 4))
        prError("can't take address of register variable");

    if (!(opFlags & 0x100))
        lhs = sub_1e37(lhs);
    if (hasRhs && !(opFlags & 0x400))
        rhs = sub_1e37(rhs);

    if (p1 == T_61) {
        if ((lhs->attr.i4 & 1) && lhs->attr.c7 == 0)
            lhs = sub_1441(T_69, lhs, 0); /* dummy 3rd arg */
    } else
        lhs = sub_1df0(lhs);

    if (hasRhs)
        rhs = sub_1df0(rhs);
    if ((opFlags & 0x2000) && sub_1ef1(lhs) == 0) {
        if (p1 == D_ADDRESSOF) {
            if (lhs->tType == D_ADDRESSOF && lhs->t_next->attr.c7 == 1)
                return lhs;
            else
                prError("can't take this address");
        } else
            prError("only lvalues may be assigned to or modified");
    }
    if ((opFlags & 0x4000) && (lhs->attr.i4 & 1) && lhs->attr.c7)
        prError("pointer required");
    if (!(opFlags & 3)) {
        if (sub_5a76(&lhs->attr, DT_2))
            lhs = sub_1ccc(lhs, DT_INT);
        if (hasRhs && sub_5a76(&rhs->attr, DT_2))
            rhs = sub_1ccc(rhs, DT_INT);
    }
    switch (p1) {
    case T_60:
        return lhs;
    case T_DOT:
        rhs = sub_1340(lhs, rhs);
        break;
    case T_121:
        tmpExpr    = curFuncNode->attr;
        tmpExpr.c7 = 0;
        if (sub_5a76(&tmpExpr, DT_VOID))
            prError("void function cannot return value");
        else
            lhs = sub_1f5d(lhs, &tmpExpr, 1);
        break;
    }
    if ((opFlags & 3)) {
        if ((opFlags & 2))
            lhs = sub_1b94(lhs);
        if ((opFlags & 1))
            rhs = sub_1b94(rhs);
    } else if ((opFlags & 4) && (lhs->attr.i4 & 1) && lhs->attr.c7 == 0 &&
               sub_5b08(&rhs->attr)) // 16e1
        rhs = sub_1ccc(sub_1441(T_STAR, rhs, sub_1ebd(lhs)),
                       (rhs->attr.dataType & DT_UNSIGNED) ? DT_UCONST : DT_CONST);
    else if (p1 == T_PLUS && (rhs->attr.i4 & 1) && rhs->attr.c7 == 0 &&
             sub_5b08(&lhs->attr)) { // 1740
        savedLhs = lhs;
        lhs      = rhs;
        rhs      = sub_1ccc(sub_1441(T_STAR, savedLhs, sub_1ebd(lhs)),
                       (rhs->attr.dataType & DT_UNSIGNED) ? DT_UCONST : DT_CONST);
    } else if ((opFlags & 8) && (lhs->attr.i4 & 1) && lhs->attr.c7 == 0 &&
               (!hasRhs || ((rhs->attr.i4 & 1) && rhs->attr.c7 == 0))) { // 17ab
        if (!(opFlags & 0x8000) || (!sub_5a4a(&lhs->attr) && !sub_5a4a(&rhs->attr))) {
            if (hasRhs && !sub_591d(&lhs->attr, &rhs->attr))
                prWarning("operands of %.3s not same pointer type", opStr);
            else if (p1 == T_MINUS) {
                minusLhs      = lhs;
                minusLhsValid = true;
                rhs           = sub_1ccc(rhs, lhs->attr.c7, sub_1ccc(lhs, DT_CONST));
            }
        }
    } else if ((opFlags & 0x30) && sub_5ad5(&lhs->attr) &&
               (!hasRhs || sub_5ad5(&rhs->attr))) { // 187a
        if (opFlags & 0x40) {
            var13 = sub_1da5(&lhs->attr, &rhs->attr);
            lhs   = sub_1ccc(lhs, var13);
            rhs   = sub_1ccc(rhs, var13);
        } // 18fa
        if (!(opFlags & 0x10) && (!sub_5b08(&lhs->attr) || !sub_5b08(&rhs->attr)))
            prError("integral type required");
    } else if (opFlags & 0x80) { // 1937
        if (sub_5a76(&lhs->attr, DT_VOID) || sub_5a76(&rhs->attr, DT_VOID)) {
            if (p1 == T_124 && lhs->tType == T_61 && !sub_5a76(&rhs->attr, DT_VOID)) {
                lhs->attr = rhs->attr;
                sub_2569(rhs);
                return lhs;
            }
            prError("illegal use of void expression");
        } else if (!(opFlags & 0x200) &&
                   (!sub_5aa4(&lhs->attr) || (hasRhs && !sub_5aa4(&rhs->attr)))) // 19cc
            prError("simple type required for %.3s", opStr);
        else if (opFlags & 0x1000) { // 1a11
            if ((opFlags & 0x8000)) {
                if (sub_2105(lhs) && (rhs->attr.i4 & 1) || rhs->attr.c7 == 0)
                    lhs = sub_1bf7(lhs, &rhs->attr);
                else if (sub_2105(rhs) && (lhs->attr.i4 & 1) && lhs->attr.c7 == 0)
                    rhs = sub_1bf7(rhs, &lhs->attr);
            } // 1a95
            if (!sub_591d(&lhs->attr, &rhs->attr))
                prWarning("operands of %.3s not same type", opStr);
        }
    } else if (!(opFlags & 0x200)) // 1ac3
        prError("type conflict");
    // 1ad1
    if (opFlags & 0x400)
        rhs = sub_1f5d(rhs, &lhs->attr, (opFlags & 4) == 0);

    savedLhs = sub_225a(p1, lhs, rhs);
    if (minusLhsValid)
        savedLhs = sub_1441(T_DIV, savedLhs, sub_1ebd(minusLhs));
    return savedLhs;
}

/**************************************************
 * 26: 1B4B PMO
 **************************************************/
s13_t *sub_1b4b(long num, uint8_t p2) {
    register s13_t *st;

    st                = allocIConst(num);
    st->attr.dataType = p2;
    return st;
}

/**************************************************
 * 27: 1B70 PMO
 **************************************************/
s13_t *allocFConst(char *fltStr) {
    register s13_t *st;

    st                = s13Alloc(T_FCONST);
    st->t_s           = fltStr;
    st->attr.dataType = DT_DOUBLE;
    return st;
}

/**************************************************
 * 28: 1B94 PMO
 **************************************************/
s13_t *sub_1b94(register s13_t *st) {

    if (!sub_5aa4(&st->attr))
        prError("logical type required");
    else if (!sub_5a76(&st->attr, 2))
        st = sub_1441(T_NE, st, sub_1bf7(&s13_9d1b, &st->attr));

    return st;
}

/**************************************************
 * 29: 1BF7
 **************************************************/
s13_t *sub_1bf7(register s13_t *st, s8_t *p2) {
    s13_t *var2;

    if (st->tType == 0x3D) {
        if ((var2 = st->m1.s[0])->m0 == 0x73) {
            if (bittst(var2->m1.a[0]->m18, 6) != 0) {
                prWarning("%s() declared implicit int16_t", var2->m1.a[0]->nVName);

                var2->m1.a[0]->m18 &= 0xBF; /* Error */
            }
        }
    }
    if (sub_591d(&st->m5, p2) == 0) { /* m1:  */
        if ((st->m0 != 0x74) || (st < __Hbss)) {
            st = sub_23b4(0x7C, st, allocSType(p2)); /* m2:  */
        }
        st->m5 = *p2; /* m3:  */
    }
    return st; /* m4:  */
}

/**************************************************
 * 30: 1CCC PMO
 **************************************************/
s13_t *sub_1ccc(s13_t *p1, uint8_t p2) {
    s8_t st;

    st.dataType = p2;
    st.i4       = 0;
    st.i2       = 0;
    st.c7       = 0;
    return sub_1bf7(p1, &st);
}

/**************************************************
 * 31: 1D02 PMO
 **************************************************/
s13_t *sub_1d02(register s13_t *st) {

    if (st->tType == T_COMMA || st->tType == 120)
        return st;
    if (!st->attr.c7 && !st->attr.i4) {
        if (st->attr.dataType < DT_INT || st->attr.dataType == DT_ENUM)
            return sub_1ccc(st, DT_INT);
        if (st->attr.dataType == DT_FLOAT)
            return sub_1ccc(st, DT_DOUBLE);
    }
    return st;
}

/**************************************************
 * 32: 1D5A
 **************************************************/
char sub_1d5a(register struct xxx *st, struct xxx *p2) {
    uint8_t l1;
    uint8_t l2;

    l1 = (bittst(st->m7, 0) == 0) && (bittst(p2->m7, 0) == 0) ? 0 : 1;
    l2 = st->m7;
    if (l2 < p2->m7)
        l2 = p2->m7;
    if (l2 < 8)
        l2 = 8;
    if (l2 == 0xE || l2 == 0x10)
        return 0x10;
    if (l2 == 0x12)
        l2 = 8;
    if (l1 != 0) {
        return (char)l2 | 1;
    } else {
        return l2;
    }
}

/**************************************************
 * 33: 1DF0 ?PMO
 **************************************************/
s13_t *sub_1df0(register s13_t *st) {

    if (st->tType = T_ID && st->attr.c7 == 2) {
        st->attr.dataType = 0x16;
        st->attr.c7       = 0;
        st->t_ps25        = st->attr.ps25; /* TO CHECK one of several options */
        st->attr.i4       = 0;
        return sub_1e58(st);
    }
    return st;
}

/**************************************************
 * 34: 1E37 PMO
 **************************************************/
s13_t *sub_1e37(register s13_t *st) {

    if (st->attr.c7 == 1)
        st = sub_1e58(st);
    return st;
}

/**************************************************
 * 35: 1E58 PMO
 **************************************************/
s13_t *sub_1e58(register s13_t *st) {
    s13_t *pi;

    pi          = sub_23b4(0x46, st, 0); /* PMO missing 3rd arg. added 0 */
    pi->attr    = st->attr;
    pi->attr.i2 = 0;
    pi->attr.c7 = 0;
    sub_5be1(&pi->attr);
    return pi;
}

/**************************************************
 * 36: 1EBD PMO
 **************************************************/
s13_t *sub_1ebd(register s13_t *st) {
    st = allocSType(&st->attr);
    st->attr.i4 >>= 1;
    return sub_1441(T_SIZEOF, st, 0); /* PMO fixed missing 3rd arg */
}

/**************************************************
 * 37: 1EF1 PMO
 **************************************************/
bool sub_1ef1(register s13_t *st) {

    switch (st->tType) {
    case 0x45:
        return true;
    case T_ID:
        return (st->t_ps25->m18 & 0x10) && st->t_ps25->m20 != T_EXTERN && st->attr.c7 == 0;
    case T_DOT:
        return st->attr.c7 == 0 && sub_1ef1(st->t_next);
    }
    return false;
}

/**************************************************
 * 38: 1F5D PMO
 **************************************************/
s13_t *sub_1f5d(register s13_t *st, s8_t *p2, int16_t p3) {
    s8_t *pAttr;

    pAttr = &st->attr;
    if (sub_591d(pAttr, p2) == 0) {
        if (sub_5ad5(pAttr) && sub_5ad5(p2)) {
            if (sub_5b08(p2) && sub_5b38(pAttr))
                prWarning("implicit conversion of float to integer");
        } else if (!(p2->i4 & 1) && p2->c7 == 0 && sub_5b08(pAttr)) {
            if (p3 == 0 && (sub_5a76(pAttr, DT_CONST) || sub_5a76(pAttr, DT_UCONST)))
                return st;
            if (!sub_2105(st))
                prWarning("illegal conversion of integer to pointer");
        } else if ((pAttr->i4 & 1) && pAttr->c7 == 0 && sub_5b08(p2))
            prWarning("illegal conversion of pointer to integer");
        else if ((pAttr->i4 & 1) && pAttr->c7 == 0 && (p2->i4 & 1) && p2->c7 == 0) {
            if (!sub_5a4a(pAttr) && !sub_5a4a(p2))
                prWarning("illegal conversion between pointer types");
        } else
            prError("illegal conversion");
    }
    return sub_1bf7(st, p2);
}

/**************************************************
 * 39: 2105 PMO
 **************************************************/
bool sub_2105(register s13_t *st) {

    switch (st->tType) {
    case 0x74:
        return st->t_ul == 0; /* long */
    case 0x7c:
        return sub_5b08(&st->attr) && sub_2105(st->t_next);
    }
    return false;
}

/**************************************************
 * 40: 2157 PMO
 **************************************************/
bool s13ReleaseFreeList() {
    register s13_t *st;

    if (s13FreeList == 0)
        return false;
    while ((st = s13FreeList)) {
        s13FreeList = st->t_next;
        free(st);
    }
    return true;
}

/**************************************************
 * 41: 2186 PMO
 **************************************************/
s13_t *s13Alloc(uint8_t tok) {
    register s13_t *st;

    if (s13FreeList != 0) {
        st          = s13FreeList;
        s13FreeList = st->t_next;
        blkclr(st, sizeof(s13_t));
    } else
        st = xalloc(sizeof(s13_t));
    st->tType         = tok;
    st->attr.dataType = DT_VOID;
    return st;
}

/**************************************************
 * 42: 21C7 PMO
 **************************************************/
s13_t *sub_21c7(register s13_t *st) {
    s13_t *l1;
    uint16_t l2;

    l1  = s13Alloc(0);
    *l1 = *st;
    l2  = opTable[st->tType - 60].uc4;
    if (!(l2 & 1) && st->tType != T_120) {
        l1->t_next = sub_21c7(st->t_next);
        if (l2 & 2)
            l1->t_alt = sub_21c7(st->t_alt);
    }
    return l1;
}

/**************************************************
 * 43: 225A PMO
 **************************************************/
s13_t *sub_225a(uint8_t p1, register s13_t *st, s13_t *p3) {
    s13_t *l1;

    if (p1 == T_124 && st->tType == T_ICONST) {
        st->attr = p3->attr;
        sub_2569(p3);
        return st;
    }
    l1 = sub_23b4(p1, st, p3); /* m1:  */

    switch (opTable[p1 - 60].c7) {
    case 1:
        l1->attr = st->attr;
        break;
    case 2:
        l1->attr = p3->attr;
        break;
    case 4:
        l1->attr = st->attr;
        sub_5be1(&l1->attr);
        break;
    case 3:
        l1->attr = st->attr;
        sub_5b99(&l1->attr);
        break;
    case 5:
        l1->attr.dataType = DT_INT;
        break;
    case 6:
        l1->attr.dataType = DT_2;
        break;
    case 7:
        l1->attr.dataType = DT_ULONG;
        break;
    }
    return l1;
}

/**************************************************
 * 44: 23B4 PMO
 **************************************************/
s13_t *sub_23b4(uint8_t tok, register s13_t *st, s13_t *p3) {
    s13_t *pi;

    pi = s13Alloc(tok);
    if (tok != T_120) {
        pi->t_next = st;
        if (opTable[tok - 60].uc4 & 2)
            pi->t_alt = p3;
    }
    return pi;
}

/**************************************************
 * 45: 240E PMO
 **************************************************/
s13_t *allocId(register s25_t *st) {
    s13_t *pi;

    pi         = s13Alloc(T_ID);
    pi->t_ps25 = st;
    if ((st->m18 & 0x10) || st->m20 == D_MEMBER)
        pi->attr = st->attr;
    return pi;
}

/**************************************************
 * 46: 245D PMO
 **************************************************/
s13_t *allocSConst() {
    register s13_t *st;

    st                = s13Alloc(T_SCONST);
    st->attr.dataType = DT_CHAR;
    st->attr.i4       = 1;
    st->t_i0          = ++strId;
    return st;
}

/**************************************************
 * 47: 248A PMO
 **************************************************/
s13_t *allocIConst(long p1) {
    register s13_t *st;

    st      = s13Alloc(T_ICONST);
    st->t_l = p1;
    return st;
}

/**************************************************
 * 48: 24B6 PMO
 **************************************************/
s13_t *allocSType(s8_t *p1) {
    register s13_t *st;

    st       = s13Alloc(S_TYPE);
    st->attr = *p1;
    return st;
}

/**************************************************
 * 49: 24DE PMO
 **************************************************/
void complexErr() {

    fatalErr("expression too complex");
}

/**************************************************
 * 50: 24E7 PMO
 **************************************************/
void pushS13(s13_t *p1) {

    if (s13SP == s13Stk)
        complexErr();
    *--s13SP = p1;
}

/**************************************************
 * 51: 250A PMO
 **************************************************/
s13_t *popS13() {

    if (s13SP != s13Stk[20])
        return *(s13SP++);
    return NULL;
}

/**************************************************
 * 52: 2529 PMO
 **************************************************/
void sub_2529(uint8_t p1) {
    register s13_t *st;

    if (p13List == s13_9cf3)
        complexErr();
    (--p13List)->tType = p1;
    st                 = p13List;
    st->t_ca[0]        = opTable[p1 - 60].c3;
}

/**************************************************
 * 53: 255D PMO
 **************************************************/
uint8_t sub_255d() {

    return (p13List++)->tType;
}

/**************************************************
 * 54: 2569 PMO (to fix __Hbss)
 **************************************************/
void sub_2569(register s13_t *st) {
    uint8_t type;

    if (st) {
        type = st->tType;
        if (!(opTable[type - 60].uc4 & 1) && type != T_120) {
            sub_2569(st->t_next);
            if (!(opTable[type - 60].uc4 & 2))
                sub_2569(st->t_alt);
        }
        if (st >= __Hbss) {
            if (type == T_FCONST)
                free(st->t_s);
            st->t_next  = s13FreeList; /* m2: */
            s13FreeList = st;
        }
    }
}

/**************************************************
 * 55: 25F7 PMO (to fix __Hbss)
 **************************************************/
s13_t *sub_25f7(register s13_t *st) {

    if (st) {
        if (st >= __Hbss && st->tType == T_ICONST) {
            st->t_ul += 1;
        } else if (st->tType == T_PLUS)
            st->t_alt = sub_25f7(st->t_alt);
        else
            st = sub_1441(T_PLUS, st, sub_1b4b(1L, DT_INT)); /* m3: */
    }
    return st; /* m4: */
}
