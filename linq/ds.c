/*
 * File created 14.11.2021, last modified 01.01.2022
 *
 * The ds.c file is part of the restored LINK.COM program
 * from the Hi-Tech C compiler v3.09 package.
 *
 *	Andrey Nikitin	01.01.2022
 */

#include <stdio.h>
#include <string.h>

#if CPM
#include <sys.h>
#endif

#include "link.h"

/* link / load modes */
#define CALCULATE 1
#define EXPLICIT  2

/**************************************************************************
 60	finPass1	ok++ (PMO)
 One very minor code variance where the load order of a & hl is swapped.
 There is no impact on execution
 **************************************************************************/
void finPass1() {
    char buff[20];
    sym_t **pslot;
    psect_t *pinfo;
    psect_t *pp;
    char linkMode;
    char loadMode;
    char *psectSpec;
    char *s;
    char separator;
    register sym_t *ps = NULL; /* PMO: if not key_R then ps may be used uninitialised */

    loadAddress        = 0;
    linkAddress        = 0;
    maxLinkAddress     = 0;
    if (!key_R && psect_location) {
        psectSpec = psect_location;

        for (;;) {
            if (!*psectSpec) {
                simpl_err("bad '-p' format");
                break;
            }
            for (s = psectSpec; *s && *s != '=' && *s != ',' && *s != '/'; s++)
                ;

            separator = *s;
            *s        = '\0';
            if ((ps = getSymbol(psectSpec, SF_PSECT)) == 0 &&
                (ps = getSymbol(psectSpec, SF_CLASS)) == 0)
                fatal_err("unknown psect: %s", psectSpec);
            if (ps->flags & SF_ABS)
                simpl_err("psect is absolute: %s", psectSpec);

            pinfo = ps->p.pinfo;
            if (pinfo->originSet)
                fatal_err("psect origin multiply defined: %s", psectSpec);

            (psectSpec = s)[0] = separator; /* put back separator */

            if (pinfo->align != 0) {
                linkAddress += (pinfo->align - 1);
                linkAddress &= ~(pinfo->align - 1L);
                loadAddress += (pinfo->align - 1);
                loadAddress &= ~(pinfo->align - 1L);
            }
            linkMode = loadMode = CALCULATE;
            saveLoadAddress     = loadAddress;
            if (separator == '=') {
                ++psectSpec;
                if (parseLongVal(&psectSpec, &linkAddress) != 0) { /*  link address */
                    fatal_err("bad origin format in spec");
                    break;
                }
                loadAddress = linkAddress;
                linkMode    = EXPLICIT;
                if (*psectSpec != '/')
                    loadMode = EXPLICIT;
            }
            if (*psectSpec == '/') {
                loadMode = CALCULATE;
                ++psectSpec;
                if (parseLongVal(&psectSpec, &loadAddress) != 0) /*  load address */
                    loadAddress = saveLoadAddress;
                else
                    loadMode = EXPLICIT;
            }
            if (ps->flags & SF_PSECT) {
                pinfo->linkAddress = linkAddress;
                if (pinfo->align != 0 && (linkAddress & (pinfo->align - 1)))
                    fatal_err("Psect %s not relocated on 0x%x boundary", pinfo->psectSym->name,
                              pinfo->align);

                if (maxLinkAddress < (linkAddress += pinfo->blkStartAddress))
                    maxLinkAddress = linkAddress;

                pinfo->loadAddress = loadAddress;
                if (pinfo->align != 0 && (loadAddress & (pinfo->align - 1)))
                    fatal_err("Psect %s not loaded on 0x%x boundary ", pinfo->psectSym->name,
                              pinfo->align);

                loadAddress += pinfo->blkStartAddress;
                pinfo->originSet = true;
            } else {
                for (pp = psectInfo; pp != nextPsect; pp++) {
                    if (pp->classSym == ps && !pp->originSet) {
                        if (linkMode == CALCULATE && pp->align != 0) {
                            linkAddress += (pp->align - 1); /* align */
                            linkAddress &= ~(pp->align - 1L);
                        }

                        pp->linkAddress = linkAddress;
                        if (pp->align != 0 && (linkAddress & (pp->align - 1)))
                            fatal_err("Psect %s not relocated on 0x%x boundary", pp->psectSym->name,
                                      pp->align);

                        if (maxLinkAddress < pp->blkStartAddress + linkAddress)
                            maxLinkAddress = pp->blkStartAddress + linkAddress;

                        if (linkMode == CALCULATE)
                            linkAddress += pp->blkStartAddress;

                        if (loadMode == CALCULATE && pp->align != 0) {
                            loadAddress += (pp->align - 1); /* align */
                            loadAddress &= ~(pp->align - 1L);
                        }

                        pp->loadAddress = loadAddress;
                        if (pp->align != 0 && (loadAddress & (pp->align - 1)))
                            fatal_err("Psect %s not loaded on 0x%x boundary ", pp->psectSym->name,
                                      pp->align);

                        if (loadMode == CALCULATE)
                            loadAddress += pp->blkStartAddress;
                        pp->originSet = true;
                    }
                }
            }
            if (*psectSpec == ',')
                psectSpec++;
            else {
                if (*psectSpec)
                    fatal_err("bad '-p' format");
                break;
            }
        }
    }

    for (pinfo = psectInfo; pinfo != nextPsect; pinfo++) {
        if (pinfo->maxSize != 0 && pinfo->maxSize < pinfo->blkStartAddress)
            simpl_err("psect exceeds max size: %s", pinfo->psectSym->name);

        if (key_R) { /* write records to start each psect */
            if (!(pinfo->psectSym->flags & SF_CLASS)) {
                conv_u32tob(pinfo->blkStartAddress, (uint8_t *)textRecBuf);
                strcpy((char *)textRecBuf + TEXT_PNAME, pinfo->psectSym->name);
                writeRec(TEXT_RECORD, (int)strlen((char *)textRecBuf + TEXT_PNAME) + TEXT_PNAME + 1,
                         textRecBuf);
            }
        } else {
            if (pinfo->originSet == 0 && pinfo->classSym == 0) {
                if (pinfo->psectSym->flags & SF_CLASS) {
                    for (pp = psectInfo; pp != nextPsect; ++pp)
                        if (!pp->originSet && pp->classSym == ps) /* ps potentially uninitialised */
                            setPsectOrigin(pp);
                } else
                    setPsectOrigin(pinfo);
            }

            if ((ps = pinfo->psectSym) != absSym) {
                if ((ps->flags & (SF_CLASS | SF_GLOBAL)) == SF_GLOBAL) {
                    sprintf(buff, "__L%s", ps->name); /* base address */
                    defineIfNeeded(buff, ps, 0, SF_GLOBAL);
                    buff[2] = 'H'; /* highest used address */
                    defineIfNeeded(buff, ps, pinfo->blkStartAddress, SF_GLOBAL);
                    if (pinfo->loadAddress != pinfo->linkAddress) {
                        buff[2] = 'B'; /* bias load - link */
                        defineIfNeeded(buff, ps, pinfo->loadAddress - pinfo->linkAddress,
                                       SF_GLOBAL);
                    }
                }
            }
        }
        pinfo->blkStartAddress = 0; /* reset for pass 2 */
    }
    if (!key_R) {
        if (cntUnresolved != 0 && !key_I)
            simpl_err("undefined symbol%c:", (cntUnresolved == 1) ? '\0' : 's');

        /* update all of the symbol values to reflect final locations */
        for (pslot = symbol_table; &symbol_table[MAX_SYMBOLS] != pslot; ++pslot) {
            if ((ps = *pslot) && !(ps->flags & (SF_PSECT | SF_CLASS))) {
                if (LowFlags(ps->flags) == SF_EXTERN) {
                    if (!key_I)
                        simpl_err("%s", ps->name);
                } else if (!(ps->psectSym->flags & SF_ABS) && LowFlags(ps->flags) != SF_COMM)
                    ps->p.value += ps->psectSym->p.pinfo->linkAddress;
            }
        }
    }
    if (key_S)
        return;

    for (pslot = symbol_table; &symbol_table[MAX_SYMBOLS] != pslot; ++pslot) {
        if ((ps = *pslot)) {
            if (ps->flags & SF_PSECT) {
                if (!key_C) {
                    wrRecord();
                    nonTextRecBuf[RECORD_TYPE] = PSECT_RECORD;

                    conv_u16tob((ps->flags & 0x7fff) | (key_R ? 0 : SF_ABS), nonTextRecPtr);

                    strcpy((char *)nonTextRecPtr + PSECT_PNAME, ps->name);
                    nonTextRecPtr += (strlen(ps->name) + PSECT_PNAME + 1);
                };
            } else if (!(ps->flags & SF_CLASS) && (!key_X || (ps->flags & SF_GLOBAL)) &&
                       (!key_Z || !isLocalName(ps->name)))
                wrSymbol(ps);
        }
    }
    if (key_H)
        fprintf(symFp, "%%locals\n");
}
