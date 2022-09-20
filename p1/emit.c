/*
 *
 * The emit.c file is part of the restored P1.COM program
 * from the Hi-Tech CP/M Z80 C v3.09
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH Z80 C compiler V3.09
 * (HI-TECH Software) and extend its life, outside of the CP/M environment
 * for full operation in windows 32/64 and Unix-like operating systems
 *
 * The HI-TECH Z80 C cross compiler V3.09 is provided free of charge for any use,
 * private or commercial, strictly as-is. No warranty or product support
 * is offered or implied including merchantability, fitness for a particular
 * purpose, or non-infringement. In no event will HI-TECH Software or its
 * corporate affiliates be liable for any direct or indirect damages.
 *
 * You may use this software for whatever you like, providing you acknowledge
 * that the copyright to this software remains with HI-TECH Software and its
 * corporate affiliates.
 *
 * All copyrights to the algorithms used, binary code, trademarks, etc.
 * belong to the legal owner - Microchip Technology Inc. and its subsidiaries.
 * Commercial use and distribution of recreated source codes without permission
 * from the copyright holderis strictly prohibited.
 *
 *
 * See the readme.md file for additional commentary
 *
 * Mark Ogden
 * 09-Jul-2022
 */
#include "p1.h"

int16_t lastLineNo; /*9caf */
char emittedSrcFile[64];   /* 9cb1 */
void emitWhere(register FILE *p);
void emitVarVal(register sym_t *p);
void sub_0470(expr_t *p);
void sub_05f1(register expr_t *st);

/**************************************************
 * 1: 013D PMO +++
 **************************************************/
void emitWhere(register FILE *p) {

    if (lastLineNo != lineNo || strcmp(emittedSrcFile, srcFile) != 0) {
        fprintf(p, "\"%d", lineNo);
        if (strcmp(srcFile, emittedSrcFile) != 0)
            fprintf(p, " %s", srcFile);
        fputc('\n', p);
    }
    lastLineNo = lineNo;
    strcpy(emittedSrcFile, srcFile);
    if (s_opt != 0)
        emitSrcInfo();
}

/**************************************************
 * 2: 01C1 PMO +++
 **************************************************/
void emitVarVal(register sym_t *p) {

    if (p->a_nodeType == EXPRNODE)
        sub_0470(p->a_expr);
    else
        putchar('1');
}

/**************************************************
 * 3: 01EC PMO +++
 **************************************************/
void emitDependentVar(register sym_t *p) {

    if (p->a_dataType == DT_COMPLEX && !p->a_indirection && p->a_nextSym->a_nodeType != FUNCNODE &&
        !(p->a_nextSym->flags & S_EMITTED))
        emitVar(p->a_nextSym);
}

/**************************************************
 * 4: 022E PMO +++
 * optimiser has basic blocks moved and eliminates
 * a ld a,(ix+6)
 **************************************************/
void prFuncBrace(uint8_t tok) {
    if (tok == T_RBRACE)
        putchar('}');
    else if (tok == T_LBRACE)
        putchar('{');
    putchar('\n');
}

/**************************************************
 * 5: 0258 PMO +++
 **************************************************/
void emitLocalLabelDef(int16_t p) {

    emitWhere(stdout);
    printf("[e :U %d ]\n", p); /* EXPR :U */
}

/**************************************************
 * 6: 0273 PMO +++
 **************************************************/
void emitLabelDef(register sym_t *st) {

    if (st) {
        emitWhere(stdout);
        printf("[e :U "); /* EXPR :U */
        emitSymName(st, stdout);
        printf(" ]\n");
    }
}

/**************************************************
 * 7: 02A6 PMO +++
 **************************************************/
void emitCase(case_t *p1) {
    int16_t caseCnt;
    register s4_t *st;

    if (p1) {
        emitWhere(stdout);
        printf("[\\ "); /* CASE */
        sub_0470(p1->switchExpr);
        putchar('\n');
        caseCnt = p1->caseCnt;
        for (st = p1->caseOptions; caseCnt--; st++) {
            putchar('\t');
            sub_0470(st->caseVal);
            printf(" %d\n", st->caseLabel);
        }
        putchar('\t');
        printf(".. %d\n", p1->defLabel);
        printf("]\n");
    }
}

/**************************************************
 * 8: 0353 PMO +++
 **************************************************/
void emitStructUnion(sym_t *p, char c) {
    register sym_t *st;

    if (p) {
        for (st = p->memberList; st != p; st = st->memberList)
            emitDependentVar(st);

        emitWhere(stdout);
        putchar('[');
        if (c == D_STRUCT)
            putchar('s'); /* STRUCT */
        else
            putchar('u'); /* UNION */
        printf(" S%d", p->a_labelId);
        for (st = p->memberList; st != p; st = st->memberList) {
            if ((st->flags & S_BITFIELD))
                printf(" :%d", st->bwidth);
            putchar(' ');
            emitAttr(&st->attr);
            putchar(' ');
            emitVarVal(st);
        }
        printf(" ]\n");
    }
}

/**************************************************
 * 9: 042D PMO +++
 **************************************************/
void emitCast(register expr_t *p) {

    emitWhere(stdout);
    printf("[e "); /* EXPR */
    while (p && p->tType == P1_CONVERT)
        p = p->t_lhs;
    sub_0470(p);
    printf(" ]\n");
}

/**************************************************
 * 10: 0470 PMO +++
 **************************************************/
void sub_0470(expr_t *p) {

    if (p)
        sub_05f1(p);
    else
        putchar('1');
}

/**************************************************
 * 11: 0493 PMO +++
 **************************************************/
void emitVar(register sym_t *st) {
    char c;

    if (st) {
        emitWhere(stdout);
        emitDependentVar(st);
        st->flags |= S_EMITTED;
        printf("[v "); /* VAR */
        emitSymName(st, stdout);
        putchar(' ');
        emitAttr(&st->attr);
        putchar(' ');
        if (st->flags & S_MEM)
            emitVarVal(st);
        else
            putchar('0');
        if (st->sclass == D_STACK)
            c = (st->flags & S_ARG) ? 'r' : 'p';
        else
            c = *keywords[(unsigned)st->sclass - T_ASM];
        if (st->flags & 4)
            c += 0xE0;
        printf(" %c ]\n", c);
    }
}

/**************************************************
 * 12: 053F PMO ++
 **************************************************/
void emitAscii(register expr_t *st, char *pc) {
    int16_t len;

    emitWhere(tmpFp);
    fprintf(tmpFp, "[a %d", st->t_id);
    len = st->t_chCnt;
    do {
        fprintf(tmpFp, " %d", *pc++);
    } while (len--);
    fprintf(tmpFp, " ]\n");
}

/**************************************************
 * 13: 05B5 PMO +++
 **************************************************/
void sub_05b5(expr_t *p1) {

    emitWhere(stdout);
    sub_0470(p1);
    putchar('\n');
}

/**************************************************
 * 14: 05D3 PMO +++
 **************************************************/
void sub_05d3(expr_t *p1) {

    emitWhere(stdout);
    sub_0470(p1);
    putchar('\n');
}

/**************************************************
 * 15: 05F1 PMO +++
 * Optimiser passes only uint8_t to sub_5a76 as it
 * has the function prototype
 **************************************************/
void sub_05f1(register expr_t *st) {
    op_t *po;
    sym_t *ps;
    expr_t *pe;

    po = &opTable[st->tType - T_EROOT];
    if (po->operandFlags & O_LEAF) {
        switch (st->tType) {
        case T_ID:
            ps = st->t_pSym;
            if (ps->sclass == D_CONST) {
                printf(". `");
                emitSymName(ps->memberList, stdout);
                printf(" %d", ps->memberId);
            } else
                emitSymName(ps, stdout);
            break;
        case T_ICONST:
            if (isVarOfType(&st->attr, DT_VOID) != 0) {
                printf("%ld", st->t_ul);
                break;
            } else
                printf("-> %ld ", st->t_ul);
        /* FALLTHRU */
        case S_TYPE:
            emitAttr(&st->attr);
            break;
        case T_FCONST:
            printf(".%s", st->t_s);
            break;
        case T_SCONST:
            printf(":s %d", st->t_id);
            break;
        case D_MEMBERID:
            printf("%d", st->t_id);
            break;
        }
    } else {
        if (st->tType == T_SIZEOF)
            printf("-> ");
        if (st->tType == T_SIZEOF && (pe = st->t_lhs)->tType == T_ID &&
            !(pe->t_pSym->flags & S_MEM)) {
            printf("* # ");
            emitAttr(&pe->attr);
            putchar(' ');
            emitVarVal(pe->t_pSym);
            putchar(' ');
            emitAttr(&st->attr);
        } else {
            printf("%.3s ", po->name);
            if (st->tType != T_120) {
                sub_05f1(st->t_lhs);
                if (po->operandFlags & O_BINARY) {
                    putchar(' ');
                    sub_05f1(st->t_rhs);
                } else if (st->tType == T_SIZEOF) {
                    putchar(' ');
                    emitAttr(&st->attr);
                }
            }
        }
    }
}

/**************************************************
 * 16: 07E3 PMO +++
 * optimiser removes call csv & jp cret
 **************************************************/
void resetExprStack(void) {
    exprSP       = &exprStk[20];
    exprFreeList = 0;
}