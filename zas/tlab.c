/*
 *
 * The tlab.c file is part of the restored ZAS.COM program
 * from the Hi-Tech C compiler v3.09
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH C compiler V3.09
 * (HI-TECH Software) and extend its life, outside of the CP/M environment
 * (Digital Research, Inc), for full operation in a  Unix-like operating
 * system UZI-180 without using the CP/M emulator.
 *
 * The HI-TECH C compiler V3.09 is provided free of charge for any use,
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
 * Early work on the decompilation was done by Andrey Nikitin
 * Completion of the work and porting to work under modern compilers done by Mark Ogden
 * 19-May-2022
 */
#include "zas.h"

tmpLabel_t *highLabel;           /* a75a */
tmpLabel_t tmpLabelTab[MAX_TMP]; /* a756 */
tmpLabel_t *tmpLabelPtr;         /* af90 */
tmpLabel_t *lowLabel;            /* af92 */

/**************************************************************************
 112	sub_53e5h +++
 **************************************************************************/
void initLocalLabels() {
    lowLabel = tmpLabelTab - 1; /* deliberately before start, technically undefined behaviour */

    if (phase != 2)
        tmpLabelPtr = lowLabel;
    if (phase == 0)
        highLabel = lowLabel;
}

/**************************************************************************
 113	sub_5404h +++
 **************************************************************************/
void defTmpLabel(int16_t tLabel) {
    if (phase != 2) {
        if (++tmpLabelPtr == &tmpLabelTab[MAX_TMP])
            fatalErr("Too many temporary labels");
        tmpLabelPtr->tLabel = tLabel;
        tmpLabelPtr->tLoc   = curPsect->sProp.vNum;
        tmpLabelPtr->tPsect = curPsect;
        if (phase == 0)
            highLabel = tmpLabelPtr;
    }

    lowLabel++;
}

/**************************************************************************
 114 546a +++
 **************************************************************************/
prop_t *findLocalLabel(int16_t nLabel, int tok) {
    register tmpLabel_t *iy = lowLabel;
    if (tok == G_FWD) {
        do {
            if (++iy > highLabel)
                goto undef;
        } while (iy->tLabel != nLabel);
    } else {
        while (iy->tLabel != nLabel)
            if (--iy < tmpLabelTab)
                goto undef;
    }
    retProp.vNum      = iy->tLoc;
    retProp.cPsectSym = iy->tPsect;
    return &retProp;
undef:
    error("Undefined temporary label");
    retProp.cPsectSym = absPsect;
    retProp.vNum      = 0;
    return &retProp;
}
