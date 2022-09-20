/*
 * File created 14.11.2021, last modified 01.01.2022
 *
 * The e.c file is part of the restored LINK.COM program
 * from the Hi-Tech C compiler v3.09 package.
 *
 *	Andrey Nikitin	01.01.2022
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "link.h"

uint32_t textBaseAddress; /* 7f00   */

/**************************************************************************
 68	textRecPass1	ok++ (PMO)
 **************************************************************************/
int textRecPass1() {
    uint32_t endAddr;
    char *psectName;
    int textLen;
    register sym_t *ps;

    readRecData(textRecBuf); /* Read TEXT record to textRecBuf */

    psectName = (char *)textRecBuf + TEXT_PNAME;                    /* ptr to name psectSym    */
    textLen   = recLen - (int)(TEXT_PNAME + strlen(psectName) + 1); /* number of data bytes */

    if (textLen < 0)
        badFormat("text record has bad length: %d-%d-(%d+1) < 0", recLen, TEXT_PNAME,
                  strlen(psectName));

    endAddr = btou32(textRecBuf) + textLen; /* Offset+number of data bytes */
    ps      = addSym(psectName, SF_PSECT);       /* find the psectSym symbol       */
    if (ps->p.pinfo->endAddr < endAddr)          /* update psectSym end if necessary */
        ps->p.pinfo->endAddr = endAddr;
    return textLen;
}

/**************************************************************************
 69	textRecPass2	ok++ (PMO)
 **************************************************************************/
void textRecPass2() {
    uint32_t offset;
    psect_t *pPsect;
    register sym_t *ps;

    flushText();
    wrRecord();

    alreadyWritten = 0;
    textLen        = textRecPass1();          /* number of data bytes    */
    textRecPtr     = textRecBuf + TEXT_PNAME; /* ptr to name psectSym       */

    while (*textRecPtr++ != 0) /* skip name psectSym */
        ;

    endAddr = textRecPtr; /* ptr to start data psectSym */
    curAddr = textRecPtr;

    ps      = addSym((char *)textRecBuf + TEXT_PNAME, SF_PSECT); /* ptr to symbol table     */
    offset      = btou32(textRecBuf + TEXT_OFFSET);             /* Offset                  */
    pPsect      = ps->p.pinfo;

    if (!(ps->flags & SF_OVRLD))
        offset += pPsect->blkStartAddress;

    textBaseAddress = offset;

    if (!optR) {
        offset += pPsect->loadPt;

        textBaseAddress += pPsect->linkPt;
    }
    u32tob(offset, textRecBuf + TEXT_OFFSET);
}

/**************************************************************************
 70	startRecPass2	ok++ (PMO)
 **************************************************************************/
void startRecPass2() {
    uint32_t addr;
    register psect_t *pp;

    if (haveEntryPt != 0)
        simpleErr("entry point multiply defined");

    haveEntryPt = true;

    readRecData(recbuf);

    if (optC)
        return;

    addr = btou32(recbuf);

    pp = addSym((char *)recbuf + START_PNAME, SF_PSECT)->p.pinfo;

    addr += pp->blkStartAddress;

    if (!optR)
        addr += pp->linkPt;

    u32tob(addr, recbuf);
    writeRec(START_RECORD, START_PNAME + (int)strlen((char *)recbuf + START_PNAME) + 1, recbuf);
}

/**************************************************************************

       #######                     #         ###   #     #  #    #
       #        #    #  #####      #          #    ##    #  #   #
       #        ##   #  #    #     #          #    # #   #  #  #
       #####    # #  #  #    #     #          #    #  #  #  ###
       #        #  # #  #    #     #          #    #   # #  #  #
       #        #   ##  #    #     #          #    #    ##  #   #
       #######  #    #  #####      #######   ###   #     #  #    */
