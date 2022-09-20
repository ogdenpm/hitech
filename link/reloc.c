/*
 * File created 14.11.2021, last modified 01.01.2022
 *
 * The c.c file is part of the restored LINK.COM program
 * from the Hi-Tech C compiler v3.09 package.
 *
 *	Andrey Nikitin	01.01.2022
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if CPM
#include <sys.h>
#endif

#include "link.h"
/*
 *	Relocation type
 */
#define RelocType(n)  ((n)&0xf0)
#define RelocSize(n)  ((n)&0xf)

#define RELOCBASEMASK 0x30

#define RABS          0x00          /* Absolute - no relocation (i.e. no change)     */
#define RPSECT        0x10          /* Relocation within named psect                 */
#define RNAME         0x20          /* Relocation by value of name                   */
#define RR            0x40          /* psect relative */
#define RRPSECT       (RR | RPSECT) /* Relocation within psect, less the current pc  */
#define RRNAME        (RR | RNAME) /* As for RRPSECT, but relative to a symbol rather than a psect */
#define RS            0x80         /* segment relative */
#define RSPSECT       (RS | RPSECT) /* Relocation by the segment value for the psect  */
#define RSNAME        (RS | RNAME)  /* Relocation by the segment value for the symbol */

static void fixup(int offset, uint16_t relocType, uint32_t delta);

static char *fixupName;          /* 7ccc   */

/**************************************************************************
 42	sub_12d2	relocRecPass1	ok++ (PMO)
 **************************************************************************/
void relocRecPass1() {
    char *name; /* Psect or external name      */
    register uint8_t *s;

    readRecData(recbuf); /* Read RELOC record to recbuf */

    for (s = recbuf; s < recbuf + recLen; s += strlen(name) + RELOC_NAME + 1) {
        name = (char *)s + RELOC_NAME;
        if (RelocType(s[RELOC_TYPE]) == RNAME || RelocType(s[RELOC_TYPE]) == RRNAME)
            addSym(name, SF_GLOBAL);
    }
}

/**************************************************************************
 43	relocRecPass2	ok++ (PMO)
 3 minor differences as chkAddRecordItem 1st param is uint8_t and compiler
 doesn't load high byte
 1 instance of benign code differences
 original ex de,hl | ld (ix-4),e | ld (ix-3),d | ld hl,8
 new      ld (ix-4),l | ld (ix-3),h | ex de,hl | ld hl,8
 **************************************************************************/
void relocRecPass2() {
    uint8_t *rp;      /* Pointer relocation information field */
    sym_t *ps = NULL; /* PMO Force init */
    char *name;       /* Psect or external name              */
    size_t len;       /* Length relocation information field */
    uint16_t offset;
    uint32_t relocatability;
    uint8_t type; /* Relocation type */
    register psect_t *pp;

    readRecData(recbuf); /* Read RELOC record to recbuf */

    for (rp = recbuf; rp < (recbuf + recLen);
         rp += strlen((char *)rp + RELOC_NAME) + RELOC_NAME + 1) {
        name      = (char *)rp + RELOC_NAME;
        fixupName = name;
        offset    = (uint16_t)btoi16(rp);

        if (offset >= textLen)
            badFormat("relocation offset %d out of range 0..%d-%d-1", offset, textLen,
                      textRecPtr - textRecBuf);

        type = rp[RELOC_TYPE];

        if (optR) {
            if ((type & RELOCBASEMASK) == RNAME) {
                ps = addSym(name, 0);
                if (LowFlags(ps->flags) != SF_EXTERN) {
                    /* convert to PSECT relative */
                    type      = (type & ~RELOCBASEMASK) | RPSECT;
                    fixupName = name = ps->psectSym->name;
                    /* calc length of psect reloc record */
                    len = RELOC_NAME + strlen(name) + 1;
                    chkAddRecordItem(RELOC_RECORD, len);

                    /* adjust offset for data already written from this block
                     * and convert delta account for the psect start. This is
                     * written to the reloc file for final fixup
                     * the adjustment for to account for psect relative is done
                     * below
                     */
                    fixup(offset - alreadyWritten, type,
                          ps->p.value - addSym(name, SF_PSECT)->p.pinfo->blkStartAddress);
                }
            }

            len = RELOC_NAME + strlen(name) + 1;
            chkAddRecordItem(RELOC_RECORD, len);

            offset -= alreadyWritten;      /* ajust for already written text */
            u16tob(offset, nonTextRecPtr); /* save offset in record */

            nonTextRecPtr[RELOC_TYPE] = type;
            strcpy((char *)nonTextRecPtr + RELOC_NAME, name);
            nonTextRecPtr += len;

            switch (RelocType(type)) { /* type */
            default:
                badFormat("illegal relocation type: %02x", type);
                break;

            case RABS:
            case RNAME:
            case RRNAME:
            case RS:
            case RSPSECT:
            case RSNAME:
                fixup(offset, type, 0); /* doesn't change but updates end marker */
                break;

            case RPSECT:
            case RR:
            case RRPSECT:
                fixup(offset, type, addSym(name, SF_PSECT)->p.pinfo->blkStartAddress);
                break;
            }
        } else {

            if (optL || optLM)
                chkAddRecordItem(RELOC_RECORD, RELOC_NAME + 1); /* item with name set to "" */

            offset -= alreadyWritten;

            switch (RelocType(type)) {

            default:
                badFormat("illegal relocation type: %02x", type);
                break;

            case RABS:
            case RS:
                ps = 0; /* no name */
                fixup(offset, type, 0);
                break;

            case RR:
            case RRPSECT:
                pp = (ps = addSym(name, SF_PSECT))->p.pinfo;
                fixup(offset, type,
                      0 - textBaseAddress - (uint32_t)offset + pp->linkPt +
                          pp->blkStartAddress);
                break;

            case RPSECT:
                pp = (ps = addSym(name, SF_PSECT))->p.pinfo;
                fixup(offset, type, pp->linkPt + pp->blkStartAddress);
                break;

            case RSPSECT:
                pp             = (ps = addSym(name, SF_PSECT))->p.pinfo;
                relocatability = pp->align;
                if (relocatability == 0)
                    relocatability = 1;
                if (ps->flags & SF_BIGSEG)
                    relocatability <<= 16;
                fixup(offset, type, (pp->loadPt - pp->linkPt) / relocatability);
                break;

            case RRNAME:
                fixup(offset, type,
                      0 - textBaseAddress - (uint32_t)offset + (ps = addSym(name, 0))->p.value);
                ps = ps->psectSym;
                break;

            case RNAME:
                ps = addSym(name, 0);
                fixup(offset, type, ps->p.value);
                ps = ps->psectSym;
                break;

            case RSNAME:
                pp             = (ps = addSym(name, 0)->psectSym)->p.pinfo;
                relocatability = pp->align;
                if (relocatability == 0)
                    relocatability = 1;
                if (ps->flags & SF_BIGSEG)
                    relocatability <<= 0x10;
                fixup(offset, type, (pp->loadPt - pp->linkPt) / relocatability);
                break;
            }
            if ((optL && !(type & RS)) || (optLM && (type & RS)))
                if (ps && !(ps->flags & SF_ABS)) {
                    u16tob(offset, nonTextRecPtr); /* reloc item offset */
                    nonTextRecPtr[RELOC_TYPE] = type & (SF_ABS | SF_LOWMASK);
                    strcpy((char *)nonTextRecPtr + RELOC_NAME, ps->name);
                    nonTextRecPtr += (strlen(ps->name) + RELOC_NAME + 1);
                }
        }
    }
}

/**************************************************************************
 44	fixup	ok++ (PMO)
 code same except that the BB block after the switch is moved to earlier
 in the code image
 **************************************************************************/
static void fixup(int offset, uint16_t relocType, uint32_t delta) {
    uint32_t nval;
    uint32_t nmask;
    uint8_t *fixloc;

    fixloc  = offset + curAddr;
    endAddr = fixloc + RelocSize(relocType);

    switch (RelocSize(relocType)) {
    case 1:
        nval  = delta + *fixloc;
        nmask = 0xff;
        *fixloc += (uint8_t)delta;
        break;
    case 2:
        nval  = delta + (long)btoi16(fixloc);
        nmask = 0xffff;
        u16tob((uint16_t)nval, fixloc);
        break;
    case 3:
        nval = delta + btou24(fixloc);
        u24tob(nval, fixloc);
        nmask = 0xffffff;
        break;

    case 4:
        u32tob(delta + btou32(fixloc), fixloc);
        return;
    default:
        badFormat("illegal relocation size: %02x", relocType);
        return;
    }
    if ((~nmask & nval) == 0 || (nval | nmask) == -1L) /* check overflow */
        return;
    simpleErr("Fixup overflow referencing %s %s", (relocType & RNAME) ? "symbol" : "psect",
              fixupName);
}
