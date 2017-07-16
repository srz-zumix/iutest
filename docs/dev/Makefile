#!/usr/bin/make

LANG=ja_JP.SJIS
HTMLLINT_PATH=$(subst \,/, $(HTMLLINT_ROOT))

default: target

all: target lint

target: Doxyfile
	doxygen Doxyfile

lint: htmllint htmlhint

htmllint:
	@if [ -f "$(HTMLLINT_PATH)/htmllint" ]; then \
		(find ../ -maxdepth 1 -type f -name "*.html" -print0 | xargs -0 perl $(HTMLLINT_PATH)/htmllint) \
	fi

htmlhint:
ifneq (, $(shell which htmlhint))
	@(find ../ -maxdepth 1 -type f -name "*.html" -print0 | xargs -0 htmlhint --nocolor)
endif

clean:
	$(RM) -rf html

version-test:
	make -f ../../test/docs/VersionTest.mk --no-print-directory
