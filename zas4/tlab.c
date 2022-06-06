/*
 *
 * The tlab.c file is part of the restored ZAS.EXE program
 * from the Hi-Tech Z80 C cross compiler v4.11
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH Z80 C cross compiler V4.11
 * (HI-TECH Software) and extend its life, outside of the MSDOS 16 bit environment
 * for full operation in windows 32/64 and Unix-like operating systems
 *
 * The HI-TECH Z80 C cross compiler V4.11 is provided free of charge for any use,
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
 * This work is an extension of earlier work on decompiling ZAS.COM from the
 * Hi-Tech CP/M based compiler v3.09
 *
 * See the readme.md file for additional commentary
 *
 * Mark Ogden
 * 06-Jun-2022
 */
#include "zas.h"

tmpLabel_t *highLabel;           /* 3ad6 */
tmpLabel_t tmpLabelTab[MAX_TMP]; /* 3ad8 */
tmpLabel_t *tmpLabelPtr;         /* 4690 */
tmpLabel_t *lowLabel;            /* 4692 */

/**************************************************************************
 137 51d8 ++
 **************************************************************************/
void initLocalLabels() {
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
    lowLabel = tmpLabelTab - 1; /* deliberately before start, but always incremented before use */
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

    if (phase != 2)
        tmpLabelPtr = lowLabel;
    if (phase == 0)
        highLabel = lowLabel;
}

/**************************************************************************
 138 51fe ++
 **************************************************************************/
void defTmpLabel(int16_t tLabel) {
    lowLabel++;
    if (phase != 2) {
        if (++tmpLabelPtr == &tmpLabelTab[MAX_TMP])
            fatalErr("Too many temporary labels");
        tmpLabelPtr->tLabel = tLabel;
        tmpLabelPtr->tLoc   = curPsect->sProp.vCurLoc;
        tmpLabelPtr->tPsect = curPsect;

        if (phase == 0)
            highLabel = tmpLabelPtr;
    } else if (curPsect->sProp.vCurLoc != lowLabel->tLoc)
        error("Phase error on temporary label");
}

/**************************************************************************
 139 5270 ++
 **************************************************************************/
prop_t *findLocalLabel(int16_t nLabel, int16_t tok) {
    register tmpLabel_t *si = lowLabel;
    if (tok == G_FWD) {
        do {
            if (++si > highLabel)
                goto undef;
        } while (si->tLabel != nLabel);
    } else {
        while (si->tLabel != nLabel)
            if (--si < tmpLabelTab)
                goto undef;
    }
    retProp.vNum  = si->tLoc;
    retProp.rSym  = si->tPsect;
    retProp.rType = si->tPsect == 0 ? 0 : 0x10;
    return &retProp;
undef:
    error("Undefined temporary label");
    retProp.rFlags = 0;
    retProp.rType  = RT_ABS;
    retProp.rSym   = absPsect;
    retProp.vNum   = 0xffff;
    return &retProp;
}
