/*
 * normally the version script generates Generated/version.h
 * if the scripts are not being used comment out the #include "Generated/version.h"
 */
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>


#include "appinfo.h"
#include "gitVer.h"


#ifdef _DEBUG
#define BUILD "debug "
#else
#define BUILD 
#endif


/* if common libraries are used then define APP_LIBS with a list
 * of the version strings exported by the libraries
 * these version strings are arrays of char
 */
#ifdef APP_LIBS
typedef char const verstr[];
extern verstr APP_LIBS;
char const *libvers[] = { APP_LIBS, NULL };
#endif

/* 
 * The "full" flag controls whether the build date/time information is shown
 * along with any library info and contributors
 */

void showVersion(FILE *fp, bool full) {

    fputs(APP_NAME
#ifdef APP_VER
          "-" APP_VER
#endif
          " (C) " APP_OWNER
#ifdef APP_PORT
          " <" APP_PORT ">"
#endif
          " " GIT_VERSION "\n",
          fp);
    if (full) {
#ifdef APP_DESCRIPTION
        fputs(APP_DESCRIPTION "\n", fp);
#endif

#ifdef APP_LIBS
        for (char **p = libvers; *p; p++) {
            fputs("Library: ", fp);
            fputs(*p, fp);
            fputc('\n', fp);
        }
#endif
#ifdef APP_CONTRIBUTOR
        fputs("Contributors: " APP_CONTRIBUTOR "\n", fp);
#endif
        fprintf(fp, "%d bit " BUILD "build: " __DATE__ " " __TIME__ "\n",
                (int)(sizeof(void *) * CHAR_BIT));
    }
#ifdef APP_EMAIL
    fputs("\nSupport email: " APP_EMAIL "\n", fp);
#endif
}
