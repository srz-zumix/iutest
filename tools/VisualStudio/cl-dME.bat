@echo off

echo %MSC_CMD_FLAGS%
echo %MSC_IDE_FLAGS%

python --version
python %~dp0\cl-dME.py %*
