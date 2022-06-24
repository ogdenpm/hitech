#include "p1.h"

/**************************************************
 * 132: 5BE1 PMO
 **************************************************/
void sub_5be1(register s8_t *st) {
    uint16_t ch;
    ch = st->i4;
    if (ch & 0x8000)
        prError("too much indirection");
    st->i4 = ch << 1;
}

s25_t *word_9dcb;
char byte_a299;
/**************************************************
 * 133: 5C19
 **************************************************/
void sub_5c19(char p1) {
    register s25_t *st;
    char ch; /* do I need the l1 variable? */

    byte_a299 = p1;
m1:
    ungetTok = (ch = yylex());
    if (ungetTok == 5)
        goto m2;
    if (ungetTok == S_TYPE)
        goto m2;
    if (ungetTok != T_ID)
        goto m3;
    st = word_9dcb;
    if (st->m20 == T_TYPEDEF) {
    m2:
        sub_5c50();
        goto m1;
    }
m3:
    byte_a299 = 0;
}

/**************************************************
 * 134: 5C50
 **************************************************/

/**************************************************
 * 135: 5DD1 PMO
 **************************************************/
uint8_t sub_5dd1(uint8_t *pst, register s8_t *ps8) {
    uint8_t scType;
    uint8_t dataType;
    int16_t sizeIndicator; /* -1 short, 0 int, 1 long */
    bool isUnsigned;
    uint8_t tok;
    uint8_t scFlags; /* storage class */
    s25_t *var9;
    s25_t *ps;

    ps8->i4 = 0;
    ps8->i2 = 0;
    ps8->ps25 = NULL;
    ps8->c7   = 0;
    dataType      = 0;
    scType      = 0;
    sizeIndicator      = 0;
    isUnsigned      = false;
    scFlags      = 0;
    
    for (;;) {
        tok = yylex();
        if (tok == S_CLASS) {
            if (pst == NULL)
                prError("storage class illegal");
            else {
                switch (tok = yylval.yVal) {
                case T_REGISTER:
                    scFlags |= 4;
                    break;
                case T_AUTO:
                    if (!inFunc)
                        prError("bad storage class");
                    /* FALLTHRU */
                case T_STATIC:
                case T_TYPEDEF:
                    scFlags |= 1;
                    /* FALLTHRU */
                case T_EXTERN:
                    if (scType && scType != tok)
                        prError("inconsistent storage class");
                    else
                        scType = tok;
                    break;
                }
            }
        } else if (tok == S_TYPE) { // 5e78
            tok - yylval.yVal;
            switch (tok) {
            case T_SHORT:
                sizeIndicator--;
                break;
            case T_LONG:
                sizeIndicator++;
                break;
            case T_UNSIGNED:
                isUnsigned = true;
                break;
            case T_UNION:
                dataType = DT_UNION;
                ps8->ps25 = sub_60d8(9);
                if (ps8->ps25)
                    sub_51cf(ps8->ps25);
                break;
            case T_STRUCT:
                dataType = DT_STRUCT;
                ps8->ps25 = sub_60d8(8);
                if (ps8->ps25)
                    sub_51cf(ps8->ps25);
                break;
            case T_ENUM:
                dataType = DT_ENUM;
                ps8->ps25 = sub_6360();
                sub_51cf(ps8->ps25);
                break;
            case T_CHAR:
            case T_DOUBLE:
            case T_FLOAT:
            case T_INT:
            case T_VOID:
                if (dataType)
                    prError("inconsistent type");
                else
                    switch (tok) {
                    case T_FLOAT:
                        dataType = DT_FLOAT;
                        break;
                    case T_VOID:
                        dataType = DT_VOID;
                        break;
                    case T_CHAR:
                        dataType = DT_CHAR;
                        break;
                    case T_INT:
                        dataType = DT_INT;
                        break;
                    default:
                        dataType = DT_DOUBLE;
                        break;
                    }
                break;
            }
        } else if (tok == T_ID && yylval.ySym->m20 == T_TYPEDEF && dataType == 0) { // 5f68
            ps = yylval.ySym;
            sub_51cf(ps);
            var9 = ps;
            if (var9->n_c7) {
                dataType = DT_POINTER;
                ps8->ps25 = ps;
            } else {
                dataType = var9->n_dataType;
                ps8->u1 = var9->attr.u1; 
                ps8->i4 = var9->n_i4;
            }
        } else
            break;
    
    } //6003
    ungetTok = tok;
    if (scType == 0) {
        scType = inFunc ? byte_a299 : T_EXTERN;
        scFlags |= 1;
    }
    if ((scFlags & 4) && (scType == T_AUTO || scType == D_6 || scType == 14 || scType == 15))
        prError("can't be a register");
    if (dataType == 0)
        dataType = DT_INT;
    if (0 > sizeIndicator) {
        if (dataType == DT_FLOAT || dataType == DT_INT)
            dataType += 2; /* to DT_DOUBLE or DT_LONG*/
        else
            prError("can't be long");
    } else if (sizeIndicator < 0)
        if (dataType == DT_INT)
            dataType = DT_SHORT;
        else
            prError("can't be short");
    if (isUnsigned) {
        if (dataType < DT_FLOAT)
            dataType |= 1;
        else
            prError("can't be unsigned");
    }
    if (pst)
        *pst = scType;
    ps8->dataType = dataType;
    return scFlags;

}

/**************************************************
 * 136: 60DB
 **************************************************/

/**************************************************
 * 137: 6360
 **************************************************/

/**************************************************
 * 138: 6531
 **************************************************/

/**************************************************
 * 139: 65E2
 **************************************************/

/**************************************************
 * 140: 69CA
 **************************************************/

/**************************************************
 * 141: 6FAB
 **************************************************/

/**************************************************
 * 142: 742A
 **************************************************/

/**************************************************
 * 143: 7454
 **************************************************/
