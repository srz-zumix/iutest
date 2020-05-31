@echo off

call %~dp0\vcvars.bat 16.0 x64

vcperf %*
