/*
 *
 * The dirent.c file is part of the restored P1.COM program
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
 * 21-Aug-2022
 *
 */

/*

    Implementation of POSIX directory browsing functions and types for Win32.

    Author:  Kevlin Henney (kevlin@acm.org, kevlin@curbralan.com)
    History: Created March 1997. Updated June 2003 and July 2012.
    Rights:  See end of file.

*/
#pragma warning(disable : 4996)
#include "dirent.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

    DIR *opendir(const char *name) {
        DIR *dir = 0;

        if (name && name[0]) {
            size_t base_length = strlen(name);
            const char *all = /* search pattern must end with suitable wildcard */
                strchr("/\\", name[base_length - 1]) ? "*" : "/*";

            if ((dir = (DIR *)malloc(sizeof * dir)) != 0 &&
                (dir->name = (char *)malloc(base_length + strlen(all) + 1)) != 0) {
                strcat(strcpy(dir->name, name), all);

                if ((dir->handle =
                    (handle_type)_findfirst(dir->name, &dir->info)) != -1) {
                    dir->result.d_name = 0;
                } else /* rollback */
                {
                    free(dir->name);
                    free(dir);
                    dir = 0;
                }
            } else /* rollback */
            {
                free(dir);
                dir = 0;
                errno = ENOMEM;
            }
        } else {
            errno = EINVAL;
        }

        return dir;
    }

    int closedir(DIR *dir) {
        int result = -1;

        if (dir) {
            if (dir->handle != -1) {
                result = _findclose(dir->handle);
            }

            free(dir->name);
            free(dir);
        }

        if (result == -1) /* map all errors to EBADF */
        {
            errno = EBADF;
        }

        return result;
    }

    struct dirent *readdir(DIR *dir) {
        struct dirent *result = 0;

        if (dir && dir->handle != -1) {
            if (!dir->result.d_name || _findnext(dir->handle, &dir->info) != -1) {
                result = &dir->result;
                result->d_name = dir->info.name;
            }
        } else {
            errno = EBADF;
        }

        return result;
    }

    void rewinddir(DIR *dir) {
        if (dir && dir->handle != -1) {
            _findclose(dir->handle);
            dir->handle = (handle_type)_findfirst(dir->name, &dir->info);
            dir->result.d_name = 0;
        } else {
            errno = EBADF;
        }
    }

#ifdef __cplusplus
}
#endif

/*

    Copyright Kevlin Henney, 1997, 2003, 2012. All rights reserved.

    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose is hereby granted without fee, provided
    that this copyright and permissions notice appear in all copies and
    derivatives.

    This software is supplied "as is" without express or implied warranty.

    But that said, if there are any problems please get in touch.

*/
