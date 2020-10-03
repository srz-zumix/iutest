@echo off

SET LANG=ja_JP.SJIS
bash -c "make --no-print-directory %*" 2> build_log.txt
if errorlevel 1 (
    sed -e "s/:\([0-9]*\):[0-9]*:/(\1):/g" build_log.txt | sed -e "s/\/cygdrive\/\([a-z]\)/\1:/g"
    del /F build_log.txt
    exit /b 1
) else (
    sed -e "s/:\([0-9]*\):[0-9]*:/(\1):/g" build_log.txt | sed -e "s/\/cygdrive\/\([a-z]\)/\1:/g"
    del /F build_log.txt
    exit /b 0
)
