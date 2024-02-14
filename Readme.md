# Hitech C 3.09 tools

This repository contains several decompiled Hitech C 3.09 tools, modified to work on Windows and Linux.

The initial work for some of the tools was done by Andrey Nikitin and my contribution was restructuring the code to make it more understandable, verifying against the original CP/M version to ensure equivalence and fixing some bugs in the original code. His GitHub site https://github.com/nikitinprior has many of these tools as standalone repositories.

I have also included the decompilations for Hitech v4.11 libr and zas, along with an enhanced dump utility hidump2, a C driver zc and a tool to make pattern files for IDA Pro's flirt  tool.

Unlike Andrey's repositories, this is a single repository for building all of the tools for Windows using Visual Studio and also for Linux using the gnu makefiles, in the Linux directory.

Each tool also has two additional options, -v and -V that display version information based on the git repository. In normal use the version number is in the format

```
yyyy.mm.dd.nn
```

where yyyy.mm.dd reflects the date of the commit for the tool, and the nn is a release sequence number. The documents in the Scripts directory provide more details.

The -v option shows limited information, the -V options shows more information including a description, the build time, contributors and support email.

I have done builds using Visual Studio and gcc under WSL,  and all build cleanly. The changes to remove all the warnings may have broken the ability to build the tools under CP/M, however the changes to repair this should be minimal. This noted, several of the tools require bespoke libraries to make the code small enough to run natively. For CREF I did create, a bespoke library to do this and also fix the problem in the original distributed which meant it didn't work because fopen append mode was broken.

```
Updated: 14-Feb-2024 Mark Ogden
```

