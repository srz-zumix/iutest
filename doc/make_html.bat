@echo off

make
if errorlevel 1 goto error

goto :EOF

:error
pause
exit /b 1

