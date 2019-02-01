#!/usr/bin/make

NOOP=sh -c true
FPS=60

FFMPEG_PRESET=-preset ultrafast
FFMPEG_PIXEL_FORMAT=-pix_fmt yuv420p

FFMPEG_OPTIONS=$(FFMPEG_PRESET) $(FFMPEG_PIXEL_FORMAT)

.PHONY: high low long short

default: low short git

high: default_scm
	@$(NOOP)
low: default_scm
	@$(NOOP)
long: default_scm
	@$(NOOP)
short: default_scm
	@$(NOOP)

ifeq ($(MAKECMDGOALS),)
GOURCE_OPTIONS=-640x480 -s 1 -r 25
else
GOURCE_OPTIONS=
endif

ifeq ($(filter long,$(MAKECMDGOALS)),long)
GOURCE_OPTIONS+=-s 30
else
ifeq ($(filter short,$(MAKECMDGOALS)),short)
GOURCE_OPTIONS+=-s 1 -c 4.0
endif
endif

ifeq ($(filter high,$(MAKECMDGOALS)),high)
FPS=60
GOURCE_OPTIONS+=-1280x720 -r $(FPS)
else
ifeq ($(filter low,$(MAKECMDGOALS)),low)
FPS=25
GOURCE_OPTIONS+=-640x480 -r $(FPS)
endif
endif

default_scm: git

git:
	gource $(GOURCE_OPTIONS) -o gource.ppm ../../
	ffmpeg -y -r $(FPS) -f image2pipe -vcodec ppm -i gource.ppm -vcodec libx264 $(FFMPEG_OPTIONS) -crf 1 -threads 0 -bf 0 iutest-gource.mp4

svn:
	svn log http://svn.osdn.jp/svnroot/iutest/ -r 1:HEAD --xml --verbose --quiet > log.xml
	gource $(GOURCE_OPTIONS) -o gource.ppm log.xml
	ffmpeg -y -r $(FPS) -f image2pipe -vcodec ppm -i gource.ppm -vcodec libx264 $(FFMPEG_OPTIONS) -crf 1 -threads 0 -bf 0 iutest-gource.mp4
