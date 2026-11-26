@echo off

SET RESO=1280x720
SET GOURCE_OPTIONS=-%RESO% -c 4.0 -s 1 -r 60

:git
call gource %GOURCE_OPTIONS% -o gource.ppm ../../
ffmpeg -y -r 60 -f image2pipe -vcodec ppm -i gource.ppm -vcodec libx264 -preset ultrafast -pix_fmt yuv420p -crf 1 -threads 0 -bf 0 iutest-gource.mp4
del /F gource.ppm
goto :EOF
