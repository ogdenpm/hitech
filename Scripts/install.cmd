
@echo off
setlocal enabledelayedexpansion
rem locally install applications
if /I [%~1] == [-v] (echo %0: 2023.4.19.15 [6256cd3]) & goto :EOF
if [%1] == [] goto usage
if [%2] neq [] goto start
:usage
echo usage: %0 file installRoot [configFile]
echo        configFile defaults to installRoot\install.cfg
echo.
echo install.cfg contains lines of the form type,dir[,suffix]
echo   Where type is the first parent directory name of the file to copy
echo   which ends in Release or Debug. 
echo   dir is the directory to install to; a leading + is replaced by installRoot
echo   suffix is inserted into the installed filename just before the .exe extension
echo   In both dir ^& suffix a $d is replaced by the current local date string in format yyyymmdd
echo   and a $t is replaced by the current local time string in format hhmmss
echo   All lines where type matches the input file's directory name are processed
echo.
echo Example with install.cfg in the current directory containing the line
echo x86-Release,+prebuilt
echo x86-Release,d:\bin,_32
echo.
echo install . path\x86-Release\myfile.exe
echo copies myfile to .\prebuilt\myfile.exe and d:\bin\myfile_32.exe
echo.
echo Control lines are also supported and they change what files the control lines apply to
echo Each control line's impact continue until the next control line
echo A control line starting with a + enables processing only for the list of files after the +
echo One starting  with a - only enables processing for files not in the list
echo a file name of * matches all files so +* renables processing for all files
echo -* stops all processing until the next control line (of limited use)
exit /b 1

:start

:: basic filename
set FILE=%~nx1
:: find the path to the target file
set PATHTO=%~p1
:getType
:: get the directory as a filename by removing trailing \
for %%I in ("%PATHTO:~,-1%") do (
    set PARENT=%%~nxI
    set PATHTO=%%~pI
)
if /I [%PARENT:~-5,5%] == [Debug] goto gotparent
if /I [%PARENT:~-7,7%] == [Release] goto gotparent
if [%PARENT%] neq [\] goto getType
echo Cannot find Release or Debug component in "%~1"
goto usage

:gotparent

if [%3] == [] (
    set CONFIGFILE=%2\install.cfg
) else (
    set CONFIGFILE=%3
)
set CONFIGFILE=%CONFIGFILE:\\=\%

if not exist %CONFIGFILE% (
    echo cannot find %CONFIGFILE%
    echo.
    goto :eof
)
:: get the current time for date/time modified dir or suffix
for /f "tokens=2 delims==." %%A in ('wmic os get LocalDateTime /format:list') do set NOW=%%A
:: process the intall config file
set SKIP=N
for /f %%A in (%CONFIGFILE%) do (
    set LINE=[%%A]
    set CH=!LINE:~,2!]
    if !CH! == [+] (
        call :setSkip "!LINE!" %FILE% N Y
    ) else if !CH! == [-] (
        call :setSkip "!LINE!" %FILE% Y N
    ) else if [!SKIP!] == [N] (
        for /f "tokens=1,2,* delims=," %%B in ("%%A") do (
            if /I [%PARENT%] == [%%B] (
                call :copy "%1" "%2" "%%C" "%%D"
            )
        )
    )
)
goto :eof

:: the core code to copy the file to the desired location
:copy root src dir suffix
setlocal enabledelayedexpansion
:: work out install directory
:: replacing + with installRoot, replacing any \\ with \ and remove any trailing \
set DIR=%~3
:: substitute any date / time
call set DIR=!DIR:$d=%NOW:~,8%!
call set DIR=!DIR:$t=%NOW:~8,6%!

if [%DIR:~0,1%]==[+] set DIR=%~2\%DIR:~1%
set DIR=%DIR:\\=\%
if [%DIR:~-1%] == [\] set DIR=%DIR:~0,-1%
:: make sure we have a directory
if not exist %DIR%\NUL mkdir %DIR%
set SUFFIX=%~4
if [%SUFFIX%] neq [] (
:: map @ to local time in suffix
    call set SUFFIX=!SUFFIX:$d=%NOW:~,8%!
    call set SUFFIX=!SUFFIX:$t=%NOW:~8,6%!
)
:: finalise the filename to use, adding in any suffix
set FILE=%DIR%\%~n1%SUFFIX%%~x1
echo Installing %~1 to %FILE%
copy /b /y "%~1" "%FILE%"
goto :eof

:: check if file is present in list, if it is
:: set SKIP to the passed in trueval else the falseval
:: supports * as a wild card and if list is empty it is treated
:: as if a * was used
:setSkip list file trueval falseval
setlocal enabledelayedexpansion
:: convert list to allow check for [file]
set list=%~1
set list=%list:,=][%
:: also remove the leading +/-
set list=[%list:~2%
:: set a default if no file specified
if %list% == [] set list=[*]
call set removed=!list:[%~2]=.!
if %list% neq %removed%  (
    set result=%3
) else if %list% neq %list:[*]=.% (
    set result=%3
) else set result=%4
endlocal & set SKIP=%result%
goto :eof

