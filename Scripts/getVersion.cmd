@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
REM  Script for generation of version info suitable for windows VERSION_INFO and application use
REM  This is a much simplified version that takes the latest commit for files in a given directory
REM  If a version file is being generated then the following #defines is included
REM  #define GIT_VERSION "[branch-]yyyy.mm.dd.(release | sha1)[+][?]"
REM     yyyy.mm.dd  is the date in UTC of the last commit, leading zeros omitted
REM     release     is the numeric component of the release tag if the commit has a tag associated
REM     sha1        is the start of the git SHA1
REM     +           added if uncommitted files
REM     ?           added if no git, the question mark represents untracked
REM     branch      present if not non main or master. A detached branch is shown as (detached)
REM  if git information cannot be found and an output file is specified then
REM     if the output file already exists the existing version is used with a ? appended unless it has one already
REM     else #define GIT_VERSION "xxxx.xx.xx.xx ?" is written to the file
REM
REM  Unless surpressed by the -q flag, the generated version is shown on the console
REM  -w writes to the VER_FILE currently gitVer.h
REM
REM  Note when commits are made, without using the gitrel command then the commited gitVer.h
REM  will contain the most recent version prior to the commit. If copied to an environment
REM  without git installed this version will not be auto corrected, although a ? will be appended
REM  It is recommended for sharing the gitrel command is used. This will generate a tag of the form
REM  rnnn, with the gitVer.h set appropriately.
REM  In the repo, the generated tags are of the form dirname-rnnn, where dirname is the directory
REM  containing the relevant files and nnn is a decimal number without leading zeros.
REM
REM in case of previous abnormal exit from script clear vars
set GIT_VERSION=
set VER_FILE=
set WMODE=
set fQUIET=
set TEMPLATE=

set DEF_VER_FILE=_version.h
set CFG_FILE=version.in

::
:: --------------------
:CHECK_ARGS
:: --------------------
set SCRIPTNAME=%~n0

:: Console output only
IF [%1] == [] GOTO START

if /I [%~1] == [-v] (echo %~n0: Ver 2023.10.10.3 [dc1acfc]) & goto :eof
IF "%~1" == "-h" GOTO USAGE
:optloop
set OPT=%~1
IF "%OPT%" == "-q" set fQUIET=1& SHIFT& goto optloop
IF "%OPT%" == "-w" if not defined WMODE set WMODE=1& SHIFT& goto optloop
IF "%OPT%" == "-W" if not defined WMODE set WMODE=2& SHIFT& goto optloop
if "%OPT%" neq "" goto USAGE

if not defined WMODE set fQUIET=
goto START

:: --------------------
:USAGE
:: --------------------
ECHO usage: %SCRIPTNAME% -v ^| -h ^| [-q] [-w^|-W] 
ECHO.
ECHO  When called without arguments version information writes to console
ECHO.
ECHO  -v          - displays script version information
ECHO  -h          - displays this output
ECHO.
ECHO  -q          - Suppress console output, ignored if not writing to file
ECHO  -w          - write file if version changed
ECHO  -W          - write file even if version unchanged
ECHO.
ECHO  The default generated file is %DEF_VER_FILE% as a C/C++ header file
ECHO  An optional %CFG_FILE% can be used to override these, see documentation
ECHO.
ECHO  Example pre-build event:
ECHO  CALL $(SolutionDir)scripts\%SCRIPTNAME%.cmd -W
ECHO.
ECHO.
GOTO :EOF


REM ===================
REM Entry Point
REM ===================
:START
rem check for configuration file
if exist %CFG_FILE% (
    set /p firstLine=<%CFG_FILE%
    if "!firstLine:~0,1!" == "[" for /f "delims=[]" %%A in ("!firstLine!") do set VER_FILE=%%A&set SKIP=skip=1
    for /f %%A in ('findstr /r /i /c:"git_version.*[\"']@@[\"']" /c:"[\"']@@[\"'].*git_version" %CFG_FILE%') do set TEMPLATE=1
)
if not defined VER_FILE set VER_FILE=%DEF_VER_FILE%
set VER_FILE=%VER_FILE:/=\%
set TAG_PREFIX=
for /f %%A in ("%CD%") do set TAG_PREFIX=%%~nxA
call :getOldVersion
CALL :GET_VERSION_ID
if defined GIT_SHA1 (
    call :GET_VERSION_STRING
) else (
    echo No Git information found
rem get existing release and append ? for untracked (unless already marked)
    set GIT_VERSION=%OLD_GIT_VERSION%
    if "!GIT_VERSION:~-1!" neq "?" set GIT_VERSION=!GIT_VERSION!?
)
if defined WMODE call :WRITE_OUT
if not defined fQUIET ECHO %TAG_PREFIX% - %GIT_VERSION%
exit /b 0



REM ====================
REM FUNCTIONS
REM ====================
:getOldVersion
set OLD_GIT_VERSION=

if exist "%VER_FILE%" (
    for /f tokens^=2^ delims^='^" %%A in ('findstr /R /I "\<GIT_VERSION\>" %VER_FILE%') do set OLD_GIT_VERSION=%%A
)
if not defined OLD_GIT_VERSION set OLD_GIT_VERSION=xxxx.xx.xx.xx?
goto :eof


:: --------------------
:GET_VERSION_ID
:: --------------------
:: Get which branch we are on and whether any outstanding commits in current tree
set GIT_BRANCH=
set GIT_QUALIFIER=
set GIT_SHA1=
for /f "tokens=1-3 delims=. " %%A in ('"git status -s -b -uno -- . 2>&1"') do (
    if [%%A] == [fatal] goto :EOF
    if [%%A] == [##] (
        if "%%B" neq "HEAD" (
            set GIT_BRANCH=%%B
        ) else (
            set GIT_BRANCH=^(detached^)
        )
    ) else if "%%B.%%C" neq "%VER_FILE%" if "%%A%%B" neq "" (
            set GIT_QUALIFIER=+
            goto :gotQualifier
    )
)
:gotQualifier
:: error then no git or not in a repo (ERRORLEVEL not reliable)
IF not defined GIT_BRANCH goto :EOF

:: get the current SHA1 and commit time for items in this directory
for /f "tokens=1-3 delims=," %%A in ('git log -1 "--decorate-refs=tags/%TAG_PREFIX%-r*" "--format=%%h,%%ct,%%D" -- .') do (
    if [%%C] neq [] (
        set GIT_SHA1=%%C
        set GIT_SHA1=!GIT_SHA1:tag: %TAG_PREFIX%-r=!
    ) else (
        set GIT_SHA1=%%A
    )
    set GIT_CTIME=%%B
)
goto :EOF


:GET_VERSION_STRING
call :time2Ver GIT_VERSION GIT_CTIME

set GIT_VERSION=%GIT_VERSION%.%GIT_SHA1%%GIT_QUALIFIER%

if "%GIT_BRANCH%" neq "master" if "%GIT_BRANCH%" neq "main" set GIT_VERSION=%GIT_BRANCH%-%GIT_VERSION%

goto :EOF

:WRITE_OUT
:: -------
SETLOCAL ENABLEDELAYEDEXPANSION
if %WMODE% == 1 if "!OLD_GIT_VERSION!" == "%GIT_VERSION%" goto :EOF
:: create header file

if not defined TEMPLATE (
    ECHO // Autogenerated version file>"%VER_FILE%"
    ECHO #define GIT_VERSION     "%GIT_VERSION%">>"%VER_FILE%"
) else (
    if exist %VER_FILE% del %VER_FILE% >NUL
    for /f "%SKIP% delims=" %%L in (%CFG_FILE%) do (
        set LINE=%%L
        echo !LINE:@@=%GIT_VERSION%!>>%VER_FILE%
    )
)

goto :EOF

:: convert unix time to gmt yyyy.mm.dd  (note leading 0s are supressed)
:time2Ver gmtstr utime
setlocal
set /a z=%2/86400+719468,d=z%%146097,y=^(d-d/1460+d/36525-d/146096^)/365,d-=365*y+y/4-y/100,m=^(5*d+2^)/153
set /a d-=^(153*m+2^)/5-1,y+=z/146097*400+m/11,m=^(m+2^)%%12+1
endlocal & set %1=%y%.%m%.%d%
goto :EOF
