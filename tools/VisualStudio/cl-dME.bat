@echo off

python --version

if defined MSC_CMD_FLAGS (
    echo MSC_CMD_FLAGS
    echo %MSC_CMD_FLAGS%
    python %~dp0\cl-dME.py %MSC_CMD_FLAGS%
)
if defined MSC_IDE_FLAGS (
    echo MSC_IDE_FLAGS
    echo %MSC_IDE_FLAGS%
    python %~dp0\cl-dME.py %MSC_IDE_FLAGS%
)

exit 1
