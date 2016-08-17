#!/usr/bin/make 

LANG=ja_JP.SJIS
HTMLLINT_PATH=$(subst \,/, $(HTMLLINT_ROOT))

default: target

all: target lint

target: Doxyfile
	doxygen Doxyfile

lint:
	(find ../ -maxdepth 1 -type f -name "*.html" -print0 | xargs -0 perl $(HTMLLINT_PATH)/htmllint)

clean:
	$(RM) -rf html
