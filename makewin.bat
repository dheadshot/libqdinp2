@echo off
set FULLLIB=0
if "%1"=="clean" goto clean
if "%1"=="tmp/qdinpm.o" goto qdinpm
if "%1"=="tmp\qdinpm.o" goto qdinpm
if "%1"=="qdinpm.o" goto qdinpm
if "%1"=="distrib/libqdinp2.a" goto libqdinp2
if "%1"=="distrib\libqdinp2.a" goto libqdinp2
if "%1"=="libqdinp2.a" goto libqdinp2
if "%1"=="" goto default
if "%1"=="all" goto default
if "%1"=="/?" goto help

:help
echo Use "%0 clean" to clean, otherwise use "%0 TargetFile CommandEnvironment" to make that target.
goto end

:clean
del tmp\qdinpm.o
goto end

:noenv
echo Error: specify a command environment in the second variable!
goto end

:default

:libqdinp2
set FULLLIB=1
if exist "tmp\qdinpm.o" goto buildlib

:qdinpm
if "%2"=="tcc" tcc -DWINDOWS -c source\qdinpm.c -o tmp\qdinpm.o
if "%2"=="MinGW32" gcc -DWIN32 -c source\qdinpm.c -o tmp\qdinpm.o -march=i486 -mtune=i686 -Os -pipe
if "%2"=="MinGW64" gcc -DWIN64 -c source\qdinpm.c -o tmp\qdinpm.o -mtune=generic -Os -pipe
if "%2"=="gcc" gcc -DWINDOWS -c source\qdinpm.c -o tmp\qdinpm.o -mtune=generic -Os -pipe
if "%2"=="MSVC" cl /DWINDOWS /c /EHsc source\qdinpm.c /Fo tmp\qdinpm.obj
if "%2"=="" goto noenv
if NOT "%FULLLIB%"=="1" goto end

:buildlib
copy source\qdinpm.h distrib\qdinp2.h
if "%2"=="MSVC" lib tmp\qdinpm.obj /OUT distrib\qdinp2.lib
if "%2"=="tcc" goto tcclink
if "%2"=="MinGW32" goto mingwlink
if "%2"=="gcc" goto mingwlink
if "%2"=="MinGW64" goto mingwlink
if "%2"=="" goto noenv
goto endlink

:mingwlink
ar rc distrib\libqdinp2.a tmp\qdinpm.o
ranlib distrib\libqdinp2.a
goto endlink

:tcclink
tinylibmaker distrib\libqdinp2.a tmp\qdinpm.o
goto endlink

rem CFLAGS="-mtune=generic -Os -pipe -DWINDOWS"
:endlink
copy "distrib\*.h" "predist\*"
if exist "distrib\libqdinp2.a" copy "distrib\libqdinp2.a" "predist\qdinp2win_libqdinp2.a"
if exist "distrib\qdinp2.lib" copy "distrib\qdinp2.lib" "predist\qdinp2win_qdinp2.lib"

:end