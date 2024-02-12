/* showVersion.h: 2023.5.3.2 [2e11528] */
#ifndef _SHOWVERSION_H_
#define _SHOWVERSION_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CPM  /* don't add overhead to CP/M builds */
#define CHK_SHOW_VERSION(argc, argv)

#else

#include <stdbool.h>
#include <stdio.h>

typedef char const verstr[];
#ifdef _MSC_VER
#ifndef strcasecmp
#define strcasecmp  _stricmp
#endif
#endif

void showVersion(bool full);

#define CHK_SHOW_VERSION(argc, argv)                  \
    if (argc == 2 && strcasecmp(argv[1], "-v") == 0)  \
        do {                                          \
            showVersion(argv[1][1] == 'V');           \
            exit(0);                                  \
    } while (0)
#endif

#ifdef __cplusplus
}
#endif

#endif
