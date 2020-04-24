@echo off

rem SET VCLIST= "%VS80COMNTOOLS%" %VCLIST%
SET VCLIST= "%VS90COMNTOOLS%" %VCLIST%
SET VCLIST= "%VS100COMNTOOLS%" %VCLIST%
SET VCLIST= "%VS110COMNTOOLS%" %VCLIST%
SET VCLIST= "%VS120COMNTOOLS%" %VCLIST%
SET VCLIST= "%VS140COMNTOOLS%" %VCLIST%

SET PATH=%CUDA_PATH%\bin;%PATH%

rem VC
for %%v in (%VCLIST%) do (
    if not %%v == "" (
        call :vcenv %%v
        if not errorlevel 1 goto build
    )
)

@echo visual studio not installed.
exit /b 1

:vcenv
call "%~1\vsvars32.bat"
goto :EOF

:build
call make.exe %* TARGET_X86=yes
