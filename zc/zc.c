/*
 *	Copyright (C) 1984-1988 HI-TECH SOFTWARE
 *
 *	This software remains the property of HI-TECH SOFTWARE and is
 *	supplied under licence only. The use of this software is
 *	permitted under the terms of that licence only. Copying of
 *	this software except for the purpose of making backup or
 *	working copies for the use of the licensee on a single
 *	processor is prohibited.
 */

/*
 *	C command - Z80 Cross compiler
 *	Windows/Unix version
 *
 *	C [-C] [-O] [-I] [-F] [-U] [-D] [-S] [-X] [-P] [-W] [-M] files {-Llib}
 */

/*
 behaviour differences compared to CP/M version
 1) internal path name buffers have been expanded to support up to PATH_MAX/PATH_MAX/260 characters
    Greater than this will break the driver, but as limits in the tools are much shorter, they are
    likely to break with long path names.
 2) if environment variable HITECH is defined this overrides the default hitech value.
    hitechBin and hitechLib are updated to reflect the change
 3) if environment variable LIBDIR80 is defined this overrides the default hitechLib value
 4) if environment variable INCDIR80 is defined this overrides the detault hitechInc value
 4) If a tool is found  in hitechBin it is used, else a search is done in the curdir followed by
 PATH
 */
#include "zc.h"
#include <stdarg.h>
#include "showVersion.h"
/* build configuration */
/* HPATH default hitech path if not specified in environment var HITECH */
/* DEFTMP if TMP / TEMP environments are to be checked, incase they are not defined */
/* ESUFFIX is added to base tool name, to map to a renamed file. For windows the value must end in
 * .exe
 */
#define LINEMAX 120
#ifdef _WIN32
#define HPATH   "D:\\local\\lib\\cpm\\"
//#define DEFTMP  ""
#define ESUFFIX ".exe"
#else
#define HPATH   "/usr/hitech/"
#define DEFTMP  "/tmp/"
#define ESUFFIX ""
#endif
/* the structure below manages the configuration for various target builds
   it is split into two sections, the first is for builds using __getargs.
   and is skipped if -R is not specified.
   The #define NWILD, indicates the number of items in this section.
   To support z280 and in the future z180 specific builds, the structure
   contains a processor value which if not 0 is checked against a global
   processor flag. This flag can be set via the command line. If no processor
   specific build is found the z80 build is used.
*/
static uint8_t processor; /* 0->z80, 1->z180, 2->z280 */
#define P_Z80  0
#define P_Z180 1
#define P_Z280 2
struct _target {
    /* all flag strings are terminated with \0 after each flag, including the last
       end of flags is detected as \0\0
    */
    char *name;
    uint8_t modifier;    /* 0->z80, 1->z180, 2->z280 */
    char *cppFlags;      /* flags to add to cpp pass */
    char *crt;           /* c runtime startup file */
    char *linkFlags;     /* flags to add to link pass */
    char *clib;          /* c library to use, note prepended with lib and suffixed with .lib */
    char *ext;           /* extent used if -oname is not specified */
    char *objtohexFlags; /* flags to add to objtohex pass */
} targets[] = {
    /* put z180 and z280 before the z80 option */
    /* clang-format off */
    { "CPM",  P_Z280, "-DCPM\0-DCPMEX\0-Dz280\0", "c280cpm.obj", "-Z\0-Ptext=0,data,bss\0-C100H\0",              "280c",  ".com", NULL },
    { "CPM",  P_Z80,  "-DCPM\0-DCPMEX\0",         "crtcpm.obj",  "-Z\0-Ptext=0,data,bss\0-C100H\0",              "c",     ".com", NULL },
    { "CPM2", P_Z80,  "-DCPM\0",         "zcrtcpm.obj", "-Z\0-Ptext=0,data,bss\0-C100H\0-U__getargs\0", "corig", ".com", NULL },
#define NWILD 3
    { "CPM",  P_Z280, "-DCPM\0-DCPMEX\0-Dz280\0", "n280cpm.obj", "-Z\0-Ptext=0,data,bss\0-C100H\0",              "280c",  ".com", NULL },
    { "CPM",  P_Z80,  "-DCPM\0-DCPMEX\0",         "nrtcpm.obj",  "-Z\0-Ptext=0,data,bss\0-C100H\0",              "c",     ".com", NULL },
    { "CPM2", P_Z80,  "-DCPM\0",         "zcrtcpm.obj", "-Z\0-Ptext=0,data,bss\0-C100H\0",              "corig", ".com", NULL },
    { "UZI",  P_Z80,  "-DUZI\0",         "crtuzi.obj",  "-Z\0-Ptext=0,data,bss\0-C100H\0",              "cuzi",  "",     NULL },
    { "TOP",  P_Z280, "-DCPM\0",         "r280cpm.obj", "-Z\0-L\0-Pcpm=0,text,data,bss,stack\0",        "280c",  ".com", "-R\0-B100H\0" },
    { "TOP",  P_Z80,  "-DCPM\0",         "rrtcpm.obj",  "-Z\0-L\0-Pcpm=0,text,data,bss,stack\0",        "c",     ".com", "-R\0-B100H\0" },
    /* clang-format on */
};

#define DEFTARGET "CPM"

#define VERS      "3.09x"

#define MAXLIST   60  /* max arg list */
#define BIGLIST   120 /* room for much more */

#define PROMPT    "zc"
#define HITECH    "HITECH"
#define LIBDIR    "LIBDIR80"
#define INCDIR    "INCDIR80"

#ifndef DEFPATH /* not defined using -DDEFPATH=... */
#define DEFPATH HPATH
#endif

#define BINSUBDIR "bin" DIRSEP
#define LIBSUBDIR "lib80" DIRSEP
#define INCSUBDIR "include80" DIRSEP

#define LIBSUFFIX ".lib" /* library suffix */
#define LIBPREFIX "lib"  /* library prefix */

static bool keep, /* retain .obj files, don't link */
    keepas,       /* retain .as files, don't assemble */
    keepi,        /* retain .i files, don't process with p1 */
    keepp1,       /* retain .p1 files, don't run cgen */
    verbose,      /* verbose - echo all commands */
    optimize,     /* invoke optimiser */
    speed,        /* speed optimiser option */
    asmlst,       /* produce asm listing file */
    usegetargs,   /* true if getargs expansion requested */
    genDeps,      /* true if -Em (make dependencies) requested */
    xref,         /* generate cross reference listing */
    dryRun,       /* true if just show commands to be run */
    nolocal;      /* strip local symbols */

static char *iuds[MAXLIST], /* -[IUD] args to preprocessor and -E flags */
    *objs[MAXLIST],         /* .obj files and others for linker */
    *flgs[BIGLIST],         /* flags etc for linker */
    *libs[MAXLIST],         /* .lib files for linker */
    *c_as[MAXLIST],         /* .c files to compile or .as to assemble */
    *otoh[MAXLIST];         /* objtohex flags */

static uint8_t iud_idx, /* index into iuds[] */
    obj_idx,            /*   "     "  objs[] */
    flg_idx,            /*   "     "  flgs[] */
    lib_idx,            /*   "     "  libs[] */
    c_as_idx,           /*   "     "  c_as[] */
    otoh_idx;           /*   "     "  otoh[] */

static char *paths[] = { "cpp" ESUFFIX, "p1" ESUFFIX,   "cgen" ESUFFIX,     "optim" ESUFFIX,
                         "zas" ESUFFIX, "link" ESUFFIX, "objtohex" ESUFFIX, "cref" ESUFFIX };

#define cpp    paths[0]
#define pass1  paths[1]
#define cgen   paths[2]
#define optim  paths[3]
#define assem  paths[4]
#define linker paths[5]
#define objto  paths[6]
#define cref   paths[7]

char *hitech         = DEFPATH;
char *hitechBin      = DEFPATH BINSUBDIR;
char *hitechLib      = DEFPATH LIBSUBDIR;

static char *temps[] = {
    "ct1", "ct2", "ct3", "obj", "xin",
};

#define tmpf1     temps[0]
#define tmpf2     temps[1]
#define tmpf3     temps[2]
#define l_dot_obj temps[3]
#define crtmp     temps[4]

static char *target;
static char *cpppath = "-I";

static char tmpbuf[PATH_MAX]; /* gen. purpose buffer */
static char *single;          /* single object file to be deleted */
static short nfiles;          /* number of source or object files seen */
static char *outfile;         /* output file name for link/objtohex */
static short nerrs;           /* errors from passes */
static char *xrname;
static char *targetExt; /* extent used for target */

static void doit(void);
static void rm(char *file);
static void addlib(char *s);
static bool doexec(char *name, char **vec);
static void assemble(char *s);
static void compile(char *s);

/* macros in  normal useage, functions in debug to allow simple intercept */
#ifndef _DEBUG
#define addobj(s)          objs[obj_idx++] = s
#define addCppFlag(s)      iuds[iud_idx++] = s
#define addLinkFlag(s)     flgs[flg_idx++] = s
#define addObjtohexFlag(s) otoh[otoh_idx++] = s
#else
static void addCppFlag(char *s) {
    iuds[iud_idx++] = s;
}
static void addobj(char *s) {
    objs[obj_idx++] = s;
}
static void addLinkFlag(char *s) {
    flgs[flg_idx++] = s;
}
static void addObjtohexFlag(char *s) {
    otoh[otoh_idx++] = s;
}
#endif

int main(int argc, char **argv) {
    register char *cp;

    CHK_SHOW_VERSION(argc, argv);

    if (strcmp(argv[1], "-q") == 0) {
        argv++;
        argc--;
    } else {
        fprintf(stderr, "HI-TECH C COMPILER (Z80) V%s\n", VERS);
        fprintf(stderr, "Copyright (C) 1984-1989 HI-TECH SOFTWARE\n");
    }
#if EDUC
    fprintf(stderr, "Licensed for Educational purposes only\n");
#endif // EDUC

    if (argc == 1)
        argv = _getargs((char *)0, PROMPT);
    setPaths();

    obj_idx = 1; /* slot 0 reserved for crt file */
    while (*++argv) {
        if (argv[0][0] == '-') {
            switch (toupper(argv[0][1])) {
            case '-':
                if (stricmp(argv[0], "--ASMLIST") == 0)
                    asmlst = true;
                else
                    fprintf(stderr, "Ignoring unknown option %s\n", argv[0]);
                break;
            case 'A':
                if (target)
                    fprintf(stderr, "Only single -A option allowed, ignoring %s\n", argv[0]);
                else if (argv[0][2])
                    target = &argv[0][2];
                else
                    target = "TOP";
                break;
            case '1':
                keepp1 = true;
                break;
            case 'Z':
                if (strcmp(argv[0] + 1, "Z80") == 0)
                    processor = P_Z80;
                else if (strcmp(argv[0] + 1, "Z180") == 0)
                    processor = P_Z180;
                else if (strcmp(argv[0] + 1, "Z280") == 0)
                    processor = P_Z280;
                else
                    error("Unknown option %s", argv[0]);
                break;
            case 'R':
                usegetargs = true;
                break;
            case 'E':
                keepi = true;
                for (cp = argv[0] + 2; *cp; cp++) {
                    char *s = "-C\0-P\0-H\0-M\0";
                    while (*s && s[1] != toupper(*cp))
                        s += 3;
                    if (*s) {
                        addCppFlag(s);
                        if (s[1] == 'M')
                            genDeps = true;
                    } else
                        fprintf(stderr, "Ignoring unknown option -E%c\n", *cp);
                }
                break;
            case 'K':
                dryRun = true;
                /* FALLTHRU */
            case 'V':
                verbose = 1;
                break;

            case 'S':
                keepas = 1;
                break;
            case 'C':
                if (argv[0][2] == 'r' || argv[0][2] == 'R') {
                    if (xref)
                        fprintf(stderr, "muiltiple -CR[name] options, ignoring %s\n", argv[0]);
                    else {
                        xref = true;
                        if (argv[0][3]) {
                            xrname    = &argv[0][1];
                            xrname[0] = '-';
                            xrname[1] = 'o';
                        } else
                            xrname = (char *)0;
                    }
                } else
                    keep = 1;
                break;

            case 'O':
                if (argv[0][2] && stricmp(argv[0] + 2, "f") != 0) {
                    if (outfile)
                        fprintf(stderr, "muiltiple -Oname options, ignoring %s\n", argv[0]);
                    else
                        outfile = argv[0] + 2;
                } else {
                    optimize = 1;
                    speed    = argv[0][2] != '\0';
                }
                break;
            case 'I':
            case 'U':
            case 'D':
                addCppFlag(argv[0]);
                break;

            case 'L':
                addlib(&argv[0][2]);
                break;
            case 'F':
                argv[0][1] = 'D';
                addLinkFlag(argv[0]);
                break;
            case 'H':
                usage();
                break;
            case 'X':
                nolocal = 1;
                break;
            case 'M':
                addLinkFlag(argv[0]);
                break;

            default:
                fprintf(stderr, "Ignoring unknown option %s\n", argv[0]);
            }
            continue;
        }
        nfiles++;
        cp = argv[0];

        cp = strrchr(argv[0], '.');
        if (cp && (stricmp(cp, ".c") == 0 || stricmp(cp, ".as") == 0)) {
            c_as[c_as_idx++] = argv[0];
            addobj(single = newStr(NULL, fname(argv[0]), ".obj"));
        } else
            addobj(argv[0]);
    }
    if (!target)
        target = DEFTARGET;
    setTarget();
    doit();
    exit(nerrs != 0);
}

void setPaths() {
    char *env;
    char tmp[PATH_MAX];
    char *s      = NULL;
    bool haveLib = false;
    bool haveInc = false;
    /* get environment overrides */
    if ((env = getenv(LIBDIR))) {
        strcpy(tmp, env);
        if (*(s = fname(tmp)))
            strcat(s, DIRSEP);
        hitechLib = xstrdup(tmp);
        haveLib   = true;
    }
    if ((env = getenv(INCDIR))) {
        strcat(strcpy(tmp, "-I"), env);
        s = fname(tmp);
        if (*(s = fname(tmp)))
            strcat(s, DIRSEP);
        cpppath = xstrdup(tmp);
        haveInc = true;
    }
    if ((env = getenv(HITECH))) {
        strcpy(tmp, env);
        if (*(s = fname(tmp)))
            strcat(s, DIRSEP);
        hitech    = xstrdup(tmp);
        hitechBin = newStr(NULL, hitech, BINSUBDIR);

        if (!haveLib)
            hitechLib = newStr(NULL, hitech, LIBSUBDIR);

        if (!haveInc)
            cpppath = newStr("-I", hitech, INCSUBDIR);
    }

    /* setup up the paths for executables */
    strcpy(tmp, hitechBin);
    s = strchr(tmp, '\0'); /* append point */
    for (int i = 0; i < sizeof(paths) / sizeof(paths[0]); i++) {
        strcpy(s, paths[i]);
        if (canExecute(tmp))
            paths[i] = xstrdup(tmp);
#ifndef _WIN32
        else if (canExecute(paths[i])) { /* check in curdir, note windows does this by default */
            strcpy(s, "." PATHSEP);      /* prefix with ./ */
            strcat(s, paths[i]);
            paths[i] = xstrdup(s);
        } /* default leave for PATH to find */
#endif
    }
    /* set up paths for temp files */
#ifdef DEFTMP
    if (!(env = getenv("TMP")))
#ifdef _WIN32
        if (!(env = getenv(TEMP)))
#endif
        env = DEFTMP;
    strcpy(tmp, env);
    if (*(s = fname(tmp)))
        strcat(s, DIRSEP);
    s = strchr(s, '\0'); /* append point */
#else
    s = tmp;
#endif
    int pid = getpid();
    for (int i = 0; i != sizeof temps / sizeof temps[0]; i++) {
        sprintf(s, "_%d_.%s", pid, temps[i]); /* create a unique name */
        temps[i] = xstrdup(tmp);
    }
}

void setTarget() {
    for (int i = usegetargs ? 0 : NWILD; i < sizeof(targets) / sizeof(targets[0]); i++)
        if ((targets[i].modifier == 0 || targets[i].modifier == processor) &&
            stricmp(target, targets[i].name) == 0) {

            objs[0] = newStr(hitechLib, targets[i].crt, NULL);
            addlib(targets[i].clib);
            for (char *s = targets[i].cppFlags; *s; s += strlen(s) + 1)
                addCppFlag(s);
            for (char *s = targets[i].linkFlags; *s; s += strlen(s) + 1)
                addLinkFlag(s);
            if (targets[i].objtohexFlags) {
                for (char *s = targets[i].objtohexFlags; *s; s += strlen(s) + 1)
                    addObjtohexFlag(s);
            }
            targetExt = targets[i].ext;
            return;
        }
    error("Unsupported target %s", target);
}

static void doit() {
    register char *cp;
    register uint8_t i;

    if (xref)
        close(creat(crtmp, 0600));
    iuds[iud_idx++] = cpppath;
    if (genDeps)
        mkDepsDir();
    for (i = 0; i < c_as_idx; i++) {
        cp = strrchr(c_as[i], '.');
        if (stricmp(cp, ".c") == 0)
            compile(c_as[i]);
        else if (keepi || keepp1)
            fprintf(stderr, "-%c option used: %s ignored\n", keepi ? 'E' : '1', c_as[i]);
        else if (keepas)
            fprintf(stderr, "-S option used: %s ignored\n", c_as[i]);
        else
            assemble(c_as[i]);
    }
    rm(tmpf1);
    rm(tmpf2);
    rm(tmpf3);
    if (keepi || keepas || keepp1)
        return;
    if (!(keep || nerrs)) {
        if (!outfile)
            outfile = newStr(NULL, objs[1], targetExt);
        flgs[flg_idx++] = newStr("-o", otoh_idx ? l_dot_obj : outfile, NULL);
        for (i = 0; i < obj_idx; i++)
            flgs[flg_idx++] = objs[i];

        for (i = 0; i < lib_idx; i++)
            flgs[flg_idx++] = libs[i];
        flgs[flg_idx] = 0;
        if (doexec(linker, flgs) && otoh_idx) {
            otoh[otoh_idx++] = l_dot_obj;
            otoh[otoh_idx++] = outfile;
            otoh[otoh_idx]   = 0;
            doexec(objto, otoh);
            rm(l_dot_obj);
        }
        if (c_as_idx == 1 && nfiles == 1)
            rm(single);
    }
    if (xref) {
        if (xrname) {
            flgs[0] = xrname;
            flgs[1] = newStr("-H", outfile, ".crf");
            flgs[2] = crtmp;
            flgs[3] = 0;
            doexec(cref, flgs);
            rm(crtmp);
        } else
            printf("Cross referenece info left in %s "
                   "; run CREF to produce listing\n",
                   crtmp);
    }
}

static void rm(char *file) {
    if (verbose)
        printf("rm %s\n", file);
    if (!dryRun)
        unlink(file);
}

static void addlib(char *s) {
    sprintf(tmpbuf, "%s" LIBPREFIX "%s" LIBSUFFIX, hitechLib, s);
    libs[lib_idx++] = xstrdup(tmpbuf);
}

_Noreturn void error(char *s, ...) {
    va_list args;
    va_start(args, s);

    vfprintf(stderr, s, args);
    fputc('\n', stderr);
    va_end(args);
    exit(1);
}

char *xstrdup(char *s) {
    char *cp;
    if (!(cp = malloc(strlen(s) + 1)))
        error("Out of memory");
    return strcpy(cp, s);
}

static bool doexec(char *name, char **vec) {
    short len;
    char **pvec;
    char *args[BIGLIST];
    int i     = 0;

    args[i++] = fname(name);
    while ((args[i++] = *vec++))
        ;

    if (verbose) {
        len = 0;
        for (pvec = args; *pvec; pvec++) {
            if (len + strlen(*pvec) > LINEMAX - 2) {
                fprintf(stderr, "\\\n  ");
                len = 2;
            }
            len += fprintf(stderr, "%s ", *pvec);
        }
        fputc('\n', stderr);
    }
    if (dryRun)
        return true;
#ifdef _WIN32
    // name fixed if needed
    int ok = (int)_spawnvp(_P_WAIT, name, args);
    if (ok == -1)
        error("could not run %s", name);
    if (ok != 0)
        nerrs++;
    return ok == 0;
#else
    register int pid;
    int status;
    if ((pid = fork()) == 0) {
        execvp(name, (char *const *)args);
        fprintf(stderr, "%s ", args[0]);
        error("exec fail", NULL);
    }
    if (pid == -1)
        perror("Fork failed");
    if (wait(&status) != pid)
        perror("Wait failed");
    return status == 0;
#endif
}

static void assemble(char *s) {
    char *vec[10];
    uint8_t i;

    if (c_as_idx > 1)
        fprintf(stderr, "%s\n", s);
    i = 0;
    if (optimize)
        vec[i++] = "-J";
    if (nolocal)
        vec[i++] = "-X";
    vec[i++] = newStr("-O", fname(s), ".obj");
    if (asmlst)
        vec[i++] = newStr("-L", fname(s), ".lst");
    vec[i++] = s;
    vec[i]   = (char *)0;
    doexec(assem, vec);
}

static void compile(char *s) {
    char *cp;
    char *vec[MAXLIST];
    uint8_t i, j;

    if (c_as_idx > 1)
        fprintf(stderr, "%s\n", s);
    for (j = 0; j < iud_idx; j++)
        vec[j] = iuds[j];
    if (genDeps) {
        vec[j++] = tmpbuf;
    }
    vec[j++] = s;
    if (keepi) {
        if (genDeps)
            vec[j++] = newStr(".deps/", fname(s), ".d");
        else
            vec[j++] = newStr(NULL, s, ".i");
    } else
        vec[j++] = tmpf1;
    vec[j] = (char *)0;
    if (!doexec(cpp, vec) || keepi)
        return;
    cp = fname(s);
    i  = 0;
    if (keepas && !optimize)
        vec[i++] = "-S";
    if (xref)
        vec[i++] = newStr("-C", crtmp, NULL);
    vec[i++] = tmpf1;
    vec[i++] = keepp1 ? newStr(NULL, fname(s), ".p1") : tmpf2;
    vec[i++] = tmpf3;
    vec[i++] = (char *)0;
    if (!doexec(pass1, vec) || keepp1)
        return;
    i        = 0;
    vec[i++] = tmpf2;
    vec[i++] = (asmlst || keepas) && !optimize ? newStr(NULL, fname(s), ".as") : tmpf1;
    vec[i++] = (char *)0;
    if (!doexec(cgen, vec) || (keepas && !optimize))
        return;
    cp = tmpf1;
    if (optimize) {
        i        = 0;
        vec[i++] = tmpf1;
        cp = vec[i++] = (asmlst || keepas) ? newStr(NULL, fname(s), ".as") : tmpf2;
        vec[i]        = (char *)0;
        if (!doexec(optim, vec))
            return;
        if (keepas)
            return;
    }
    i = 0;
    if (nolocal)
        vec[i++] = "-X";
    if (optimize)
        vec[i++] = "-J";
    if (asmlst)
        vec[i++] = newStr("-L", fname(s), ".lst");
    vec[i++] = "-N";
    vec[i++] = newStr("-O", fname(s), ".obj");
    vec[i++] = cp;
    vec[i]   = (char *)0;
    doexec(assem, vec);
    if (asmlst)
        rm(cp);
}
/* clang-format off */
/* the code below uses printf rather than extended length strings to allow processing by Hitech C for UZI builds */
_Noreturn void usage() {
    printf("\nUsage: zc [-q] options inputfile+\n");
    printf("Where:\n");
    printf("-q         - supresses the sign on message\n");
    printf("inputfiles of the form\n");
    printf("  file.c/file.as are compiled/assembled before linking\n");
    printf("  -Lname are expanded to {LIBDIR80}/libname.lib, where {LIBDIR80} is the default library path\n");
    printf("The case insensitive options supported are:\n");
    printf("--ASMLIST  - create a listing file for the assembler pass\n");
    printf("             Warning compiling file.c with this option will overwite an existing file.as\n");
    printf("-1         - for debugging stops after running P1\n");
    printf("-Atarget?  - sets alternative target build. If target is missing it defaults to TOP, see below\n");
    printf("-C         - stop before linking\n");
    printf("-CRname?   - create a cross reference file, using name if specified\n");
    printf("-Dvar(=val)? - adds var to the cpp define list, if val is omitted the default is 1\n");
    printf("-E[CPHM]*  - run only cpp. C,P,H are passed to cpp, M creates make depdendency file in .deps/file.d\n");
    printf("-Fname?    - creates a symbol file, if name is omitted it defaults to l.sym\n");
    printf("-H         - show this help\n");
    printf("-Ipath     - adds path to the cpp include search path\n");
    printf("-K         - does a dry run of the compilation\n");
    printf("-Lname     - adds {LIBDIR80}/libname.lib to the libraries to be searched\n");
    printf("-Mname?    - creates a map file, if name is omitted it defaults to l.map\n");
    printf("-O(F)?     - optimise code, F optimises for speed\n");
    printf("-Oname     - specifies the output filename\n");
    printf("-R         - add wildcard name specification on command line\n");
    printf("-S         - stop after code generation\n");
    printf("-Uvar?     - undefines the specified var, or if no var, undefines all predefined vars\n");
    printf("-V         - verbose mode; list commands executed\n");
    printf("-X         - purge local symbols\n");
    printf("-(Z80|Z180|Z280) - sets the target CPU, default is Z80. Currently Z180 is treated as Z80\n");
    printf("\ntarget determines the startup, defines and libraries and is one of\n");
    printf("CPM        - CPM build using latest library files, includes support for CPM3+ features\n");
    printf("CPM2       - CPM build excluding CP/M 3 features but smaller code\n");
    printf("UZI        - UZI180 build\n");
    printf("TOP        - creates self relocating build to load into top of the TPA\n");
    printf("if no target is specified via -A, then the default is " DEFTARGET "\n");
/* clang - format on */
    exit(1);
}