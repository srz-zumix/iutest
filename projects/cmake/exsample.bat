@echo off

SET VCVERSION=14
SET DIRNAME=vc%VCVERSION%

if not exist tmp mkdir tmp
cd tmp
if errorlevel 1 goto end
if not exist %DIRNAME% mkdir %DIRNAME%
cd %DIRNAME%
if errorlevel 1 goto end

cmake -G "Visual Studio %VCVERSION%" ../../

:end
pause
