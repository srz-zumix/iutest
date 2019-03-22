#!/usr/bin/make

LANG=ja_JP.SJIS
HTMLLINT_PATH=$(subst \,/, $(HTMLLINT_ROOT))

default: target

all: target lint

upgrade:
	doxygen -u

target: html/index.html

html/index.html: Makefile Doxyfile doxygen_filter.py
	export PYTHONIOENCODING=utf-8
	doxygen Doxyfile
#	doxyindexer searchdata.xml -o html/
#	cp '$(DOXYGEN_ROOT)/bin/doxysearch.cgi' html/

gh-pages: target
	- mkdir gh-pages
	cp *.html gh-pages/
	cp -r css gh-pages/
	cp -r html gh-pages/
	cp -r images gh-pages/
	cp ../README.md gh-pages/
	cp -r dev/.circleci gh-pages/
	cp dev/*.yml gh-pages/

clean:
	rm -rf html
	rm -rf gh-pages

lint:
	(find ./ -maxdepth 1 -type f -name "*.html" -print0 | xargs -0 perl $(HTMLLINT_PATH)/htmllint)

open: target
ifeq ($(OS),Windows_NT)
	cmd /c start html/index.html
else
	open html/index.html
endif
