REM setlocal
set CWD=%cd%
set PATH=%PATH%;%CWD%\winlibs\tup;%CWD%\src;%CWD%\winlibs

REM tup (on windows) cannot handle config dirs
rmdir /Q /S build-debug
rmdir /Q /S build-release
rmdir /Q /S build-clang
