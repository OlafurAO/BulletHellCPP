REM Building...
mingw32-make -f MakeFile

if %errorlevel% neq 0 (
  exit /b %errorlevel%
)

REM Running...
.\main.exe