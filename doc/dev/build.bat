@echo off

SET PATH=c:\cygwin\bin;%PATH%
SET LANG=ja_JP.SJIS
bash -c "make --no-print-directory %*" > build_log.txt 2>&1
if errorlevel 1 (
	sed -e "s/: [0-9]*:/: error:/g" build_log.txt | sed -e "s/:\([0-9]*\):/(\1):/g" | sed -e "s/\/cygdrive\/\([a-z]\)/\1:/g"
	rem del /F build_log.txt
	exit /b 1
) else (
	sed -e "s/: [0-9]*:/: error:/g" build_log.txt | sed -e "s/:\([0-9]*\):/(\1):/g" | sed -e "s/\/cygdrive\/\([a-z]\)/\1:/g"
	del /F build_log.txt
	exit /b 0
)
