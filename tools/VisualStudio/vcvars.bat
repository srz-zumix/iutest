@echo off

if not exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" (
    goto from_envvar
)

if "%~1"=="" (
    echo %~nx0 "<vs version(e.g. 16.0)>" [vcvarsall options...]
    exit 1
)
SET VSVER=%1
SET ARGS=

:check
shift
if "%~1"=="" goto final
set ARGS=%ARGS% %1
goto check
:final

which vswhere > nul 2>&1
if errorlevel 1 SET PATH=%PATH%;%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\
vswhere -version %VSVER% -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -find **/vcvarsall.bat > tmp.txt
SET /p VCVARS=<tmp.txt
del /F tmp.txt
echo %VCVARS%
echo %ARGS%

call "%VCVARS%" %ARGS%

goto :EOF

:from_envvar
echo not impl

