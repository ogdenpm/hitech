/****************************************************************************
 *  appinfo.h: part of the C port of Intel's ISIS-II ixref             *
 *  The original ISIS-II application is Copyright Intel                     *
 *                                                                          *
 *  Re-engineered to C by Mark Ogden <mark.pm.ogden@btinternet.com>         *
 *                                                                          *
 *  It is released for academic interest and personal use only              *
 ****************************************************************************/

// static version information
// provides opportunity to set common APP_xxx
#ifndef _APPINFO_H_
#define _APPINFO_H_
#include "_appinfo.h"

// common defaults if not specified
#ifndef APP_PRODUCT
#define APP_PRODUCT APP_NAME
#endif
#ifndef APP_OWNER
#define APP_OWNER "Mark Ogden"
#endif
#ifndef APP_EMAIL
#define APP_EMAIL "mark@mark-ogden.uk"
#endif
#endif
