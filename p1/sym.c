#include "p1.h"


int16_t word_a291;  /* as91 */
s25_t *s25FreeList; /* a293 */
s25_t **hashtab;    /* a295 */
void *word_a297;    /* a297 */
uint8_t byte_a299;  /* a299 */
uint8_t byte_a29a;  /* a29a */
uint8_t byte_968b; /* 968b */
int16_t word_968c; /* 968c */
int16_t tmpLabelId; /* 968e */


/**************************************************
 * 103: 4D92 PMO
 **************************************************/
void sub_4d92() {

    s25FreeList = word_a291 = 0;
    hashtab                 = xalloc(271 * sizeof(hashtab[0]));
}


/**************************************************
 * 104: 4DA7 PMO (to check)
 **************************************************/
s25_t *lookup(char *buf) {
    uint8_t type;
    int16_t crc;
    char *s;
    s25_t *ps;
    register s25_t *cp;
    for (crc = 0, s = buf; *s; s++)
        crc = crc * 2 + *s;
    for (ps = hashtab[crc % 271]; cp = ps->n_chain; ps = &cp->nMemberList) {
        if (buf && strcmp(cp->nVName, buf) == 0) {
            type = cp->m20;
            if (byte_8f86 != (type == D_STRUCT || type == D_UNION ? 1 : 0) && byte_8f86 == (type != D_MEMBER ? 1 : 0) || type == 0)
                    break;
        }
    }
    return ps;

}


/**************************************************
 * 105: 4E90 PMO
 **************************************************/
s25_t *sub_4e90(register char *buf) {
    s25_t *ps = lookup(buf);
    if (ps->n_chain == 0)
        ps->n_chain = nodeAlloc(buf);
    if (crfFp && buf)
        fprintf(crfFp, "%s %d\n", buf, lineNo);
    return ps->n_chain;
}

/**************************************************
 * 106: 4EED
 **************************************************/

/**************************************************
 * 107: 516C
 **************************************************/

/**************************************************
 * 108: 51CF
 **************************************************/
void sub_51cf(s25_t *ps) {
}

/**************************************************
 * 109: 51E7
 **************************************************/

/**************************************************
 * 110: 5356 PMO
 **************************************************/
bool releaseNodeFreeList() {
    register s25_t *st;

    if (s25FreeList) {
        while ((st = s25FreeList)) {
            s25FreeList = st->nMemberList;
            free(st);
        }
        return true;
    }
    return false;
}

char blank[] = "";
/**************************************************
 * 111: 5384 PMO
 **************************************************/
s25_t *nodeAlloc(char *s) {
    register s25_t *pn;
    static int16_t nodeCnt;

    if (s25FreeList) {
        pn          = s25FreeList;
        s25FreeList = pn->nMemberList;
        blkclr(pn, sizeof(s25_t));
    } else {
        pn = xalloc(sizeof(s25_t));
    }
    pn->m21     = inFunc;
    pn->nRefCnt = 1;
    pn->nodeId  = ++nodeCnt;
    if (s) {
        pn->nVName = (char *)xalloc(strlen(s) + 1);
        strcpy(pn->nVName, s);
    } else
        pn->nVName = blank;
    return pn;
}

/**************************************************
 * 112: 540C PMO
 **************************************************/
void reduceNodeRef(register s25_t *pn) {

    if (--pn->nRefCnt == 0) {
        switch (pn->m20) {
        default:
            if (pn->n_c7 == 2)
                sub_583a(pn->n_i2);
            else if (pn->n_c7 == 1)
                sub_2569(pn->n_i2);
            if (pn->n_dataType == DT_POINTER)
                reduceNodeRef(pn->n_chain);
        case 0:
        case D_LABEL:
        case D_STRUCT:
        case D_UNION:
        case D_ENUM:
            if (pn->nVName != blank)
                free(pn->nVName);
            pn->nMemberList = s25FreeList;
            s25FreeList     = pn;
            break;
        }
    }
}

/**************************************************
 * 113: 549C PMO
 **************************************************/
void enterScope() {

    prFuncBrace(T_LBRACE);
    ++inFunc;
}

/**************************************************
 * 114: 54AC PMO
 **************************************************/
void exitScope() {

    checkScopeExit();
    --inFunc;
    prFuncBrace(T_RBRACE);
}

/**************************************************
 * 115: 54C0
 **************************************************/
void checkScopeExit() {
    char *ch;
    s25_t **l2;
    char l3;
    char *l4;
    register s25_t *st;

    ch = hashtab;
    while (ch < 542 + hashtab) { /* m21: */
        l2 = ch;                   /* m1:  */
        while ((st = *l2) != 0) {  /* m20: */
            if (st->m21 == inFunc) {
                l4 = 0;
                l3 = st->m20;
                if ((st->m18 & 3) == 2) {
                    switch (l3) {
                    case 7:
                        l4 = "label";
                        break; /* m4:  */
                    case 8:
                    case 9:
                    case 0x1f:
                        break;
                    default:
                        l4 = "variable";
                        break;
                    }
                    if (l4 != 0)
                        prError("undefined %s: %s", l4, st->nVName); /* m3:  */
                } else if ((inFunc == 0) && (l3 == 0x2a)) {          /* m5:  */
                    if (bittst(st->m18, 1) == 0) {                   /* m6:  */
                        switch (l3) {
                        case 0:
                            break;
                        case 6:
                            l4 = 0;
                            break; /* m17: */
                        case 7:
                            l4 = "label";
                            break; /* m8:  */
                        case 8:
                            l4 = "structure";
                            break; /* m11: */
                        case 9:
                            l4 = "union";
                            break; /* m12: */
                        case 10:
                            l4 = "member";
                            break; /* m13: */
                        case 11:
                            l4 = "enum";
                            break; /* m14: */
                        case 12:
                            l4 = "constant";
                            break; /* m15: */
                        case 45:
                            l4 = "typedef";
                            break; /* m16: */
                        default:
                            if (bittst(st->m18, 0) != 0) {
                                l4 = "variable definition";
                            } else {
                                l4 = "variable declaration"; /* m16: */
                            }
                            break;
                        }
                        if (l4 != 0)
                            prWarning("unused %s: %s", l4, st->nVName); /* m9:  */
                    }
                }
                *l2 = st->m8; /* m10: */
                reduceNodeRef(st);
            } else {
                l2 = st->m8; /* m19: */
            }
        }
        ch = ch + 2; /* l1 += 2; */
    }
    l2 = &word_a291;
    while ((st = *l2) != 0) {    /* m24: */
        if (st->m21 == inFunc) { /* m22: */
            *l2 = st->m8;
            reduceNodeRef(st);
        } else {
            l2 = &st->m8; /* m23: */
        }
    }
}

s25_t *word_a291;
/**************************************************
 * 116: 56A4 PMO
 **************************************************/
s25_t *sub_56a4() {
    register s25_t *st;

    st = nodeAlloc(0);
    st->m18 |= 0x83;
    st->m8    = word_a291;
    word_a291 = st;
    return st;
}

/**************************************************
 * 117: 56CD PMO
 **************************************************/
s25_t *findMember(s25_t *p1, char *p2) {
    register s25_t *st;

    st = p1->nMemberList;
    for (;;) {
        if (p1 == st) {
            prError("%s is not a member of the struct/union %s", p2, p1->nVName);
            return NULL;
        }
        if (strcmp(st->nVName, p2) == 0)
            return st;
        st = st->nMemberList;
    }
}

/**************************************************
 * 118: 573B PMO
 **************************************************/
void sub_573b(register s25_t *st, FILE *fp) {

    if (st) {
        if (st->m18 & 0x80)
            fprintf(fp, "F%d", st->nodeId);
        else
            fprintf(fp, "_%s", st->nVName);
    }
}

/**************************************************
 * 119: 5785 PMO
 **************************************************/
int16_t newTmpLabel() {

    return ++tmpLabelId;
}

/**************************************************
 * 120: 578D PMO
 **************************************************/
s10_t *sub_578d(register s10_t *p) {
    s10_t *var2;
    s8_t *var4;
    int16_t var6;
    if (!p)
        return p;
    var2 = xalloc((p->cnt - 1) * sizeof(s8_t) + sizeof(s10_t));
    var6 = var2->cnt = p->cnt;
    while (var6--) {
        var4  = &var2->s8array[var6];
        *var4 = p->s8array[var6];
        if (var4->dataType == DT_POINTER)
            var4->u1.chain->nRefCnt++;
    }
    return var2;
}

/**************************************************
 * 121: 583A
 **************************************************/
sub_583a() {
}

/**************************************************
 * 122: 58BD
 **************************************************/
void sub_588d() {
}

/**************************************************
 * 123: 591D
 **************************************************/
bool sub_591d(s8_t *p1, s8_t *p2) {
    // types same?
}

/**************************************************
 * 124: 5A4A PMO
 **************************************************/
bool sub_5a4a(register s8_t *st) {
    return st->dataType == DT_VOID && st->i4 == 1;
}

/**************************************************
 * 125: 5A76 PMO
 **************************************************/
bool sub_5a76(register s8_t *st, uint8_t p2) {

    return st->dataType == p2 && st->i4 == 0 && st->c7 == 0;
}

/**************************************************
 * 126: 5AA4 PMO
 **************************************************/
bool sub_5aa4(register s8_t *st) {
    return st->c7 == 0 && (((st->i4 & 1) && st->c7 == 0) || st->dataType < DT_VOID);
}

/**************************************************
 * 127: 5AD5 PMO
 **************************************************/
bool sub_5ad5(register s8_t *st) {
    return st->c7 == 0 && st->i4 == 0 && st->dataType < DT_ENUM;
}

/**************************************************
 * 128: 5B08 PMO
 **************************************************/
bool sub_5b08(register s8_t *st) {
    return (st->c7 == 0 && st->i4 == 0 && st->dataType < DT_FLOAT);
}

/**************************************************
 * 129: 5B38 PMO
 **************************************************/
bool sub_5b38(register s8_t *st) {
    return st->c7 == 0 && st->i4 == 0 && (st->dataType == DT_FLOAT || st->dataType == DT_DOUBLE);
}

/**************************************************
 * 130: 5B69 PMO
 **************************************************/
bool isValidDimType(register s8_t *st) {

    return sub_5b08(st) || sub_5a76(st, DT_ENUM);
}

/**************************************************
 * 131: 5B99 PMO
 **************************************************/
void sub_5b99(register s8_t *st) {
    if (st->c7 == 2)
        st->c7 = 0;
    else
        st->i4 >>= 1;

    if (sub_5a76(st, 0x16))
        *st = st->ps25->attr;
}
