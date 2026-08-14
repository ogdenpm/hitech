#include "_version.h"
#include "appinfo.h"
#include "verInfo.h"

#ifdef APP_LIBS
typedef char const verStr[];
extern verStr APP_LIBS;
char const *const libs[] = { APP_LIBS, 0 };
#else
char const *const libs[] = { 0 };
#endif

appInfo_t appInfo = {
    APP_NAME,
    APP_PRODUCT,
    APP_OWNER,
#ifdef APP_MODS
    .mods = APP_MODS,
#endif
#ifdef APP_DESCRIPTION
    .description = APP_DESCRIPTION,
#endif
#ifdef APP_CONTRIBUTORS
    .contributors = APP_CONTRIBUTORS,
#endif
    .email   = APP_EMAIL,
    .version = GIT_VERSION,
    .build = __DATE__ " " __TIME__
};