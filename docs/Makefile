#!/usr/bin/make

LANG=ja_JP.SJIS
HTMLLINT_PATH=$(subst \,/, $(HTMLLINT_ROOT))
GHPAGES_DIR:=gh-pages

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
	- mkdir ${GHPAGES_DIR}
	cp *.html ${GHPAGES_DIR}/
	cp -r css ${GHPAGES_DIR}/
	cp -r html ${GHPAGES_DIR}/
	cp -r images ${GHPAGES_DIR}/
	cp ../README.md ${GHPAGES_DIR}/

gh-pages-for-master:
	cp -r dev/.circleci ${GHPAGES_DIR}/
	cp dev/*.yml ${GHPAGES_DIR}/
	cp ../README.md ${GHPAGES_DIR}/

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
