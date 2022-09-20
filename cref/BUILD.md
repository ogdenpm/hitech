# Building the Hi-Tech C cref utility

The instructions below provide details on how to build the Hi-Tech C cref utility, dependent on your target environment. It has currently been tested under CP/M, UZI-180, Windows, linux and MacOs, although it should also compile under unix systems.

As CP/M only supports a limited command line length, the original utility used the Hi-Tech supplied _getargs function to allow long command lines to be entered. For modern systems this is not likely to be needed and is no longer used by default. 

Providing that the target environment supports opendir, readdir and closedir, it is still possible to include the _getargs functionality. The build instructions include the appropriate instructions, where this is currently supported.

CP/M and UZI-180 builds assume you are using the zc3 C driver from Nikitin Andrey's github site.

## CP/M

```
zc3 -o -CPM cref.c
```

Note CP/M builds automatically include the _getargs functionality.

## UZI-180

    zc3 -o cref.c

## GCC - Linux, MacOs ...

    Normal build
      gcc -O3 -ocref cref.c
    Build with _getargs support
      gcc -O3 -ocref -DUSE_GETARGS cref.c getargs.c fname.c

## Windows - Using Visual Studio

The commands below assume that appropriate developer environment variables have been setup.

    Normal buld
      cl /O2 /MD /std:c17 cref.c
    Build with _getargs support
      cl /O2 /MD /std:c17 -DUSE_GETARGS cref.c getargs.c fname.c missing\dirent.c

```
Updated by Mark Ogden 25-Aug-2022
```