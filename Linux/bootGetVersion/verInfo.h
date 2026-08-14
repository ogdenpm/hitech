/* showVersion.h: 2023.5.3.2 [2e11528] */
#ifndef _VERINFO_H_
#define _VERINFO_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    char const *name;
    char const *product;
    char const *owner;
    char const *mods;
    char const *description;
    char const *contributors;
    char const *email;
    char const *version;
    char const *build;
} appInfo_t;
extern appInfo_t appInfo;






#ifdef __cplusplus
}
#endif
#endif

