@echo off

if not exist exsample mkdir exsample
cd exsample
if errorlevel 1 goto end
if not exist vc10 mkdir vc10
cd vc10
if errorlevel 1 goto end

cmake -G "Visual Studio 10" ../../

:end
pause
