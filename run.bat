@echo off

REM Default flags
set MAKE_FLAGS=

REM Check for debug flag
if "%~1"=="--debug" (
  set MAKE_FLAGS=CXXFLAGS=-g
  echo Activating debug mode...
)

REM Building...
mingw32-make -f MakeFile %MAKE_FLAGS%

if %errorlevel% neq 0 (
  exit /b %errorlevel%
)

REM Running...
.\main.exe