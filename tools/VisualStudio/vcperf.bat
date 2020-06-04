@echo off

which vcperf.exe > nul 2>&1
if errorlevel 1 (
	call %~dp0\vcvars.bat 16.0 x64
)
vcperf.exe %*
