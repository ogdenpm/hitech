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
          " " GIT_VERSION,
          fp);
    if (full) {
#ifdef APP_DESCRIPTION
        fputs("\n" APP_DESCRIPTION, fp);
#endif

#ifdef APP_LIBS
        for (char **p = libvers; *p; p++) {
            fputs("\nLibrary: ", fp);
            fputs(*p, fp);
        }
#endif
#ifdef APP_CONTRIBUTOR
        fputs("\nContributors: " APP_CONTRIBUTOR, fp);
#endif
        fprintf(fp, "\n%d bit " BUILD "build: " __DATE__ " " __TIME__,
                (int)(sizeof(void *) * CHAR_BIT));
    }
#ifdef APP_EMAIL
        fputs("\n\nSupport email: " APP_EMAIL, fp);
#endif
    fputc('\n', fp);
}
