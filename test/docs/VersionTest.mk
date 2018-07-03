IUTEST_MAJORVER:=$(shell grep 'IUTEST_MAJORVER' ../../include/iutest_ver.hpp | head -1 | sed -e 's/.*define.*0x\([0-9]*\).*/\1/' -e 's/0\+\([0-9]\+\)/\1/')
IUTEST_MINORVER:=$(shell grep 'IUTEST_MINORVER' ../../include/iutest_ver.hpp | head -1 | sed -e 's/.*define.*0x\([0-9]*\).*/\1/' -e 's/0\+\([0-9]\+\)/\1/')
IUTEST_MICROVER:=$(shell grep 'IUTEST_MICROVER' ../../include/iutest_ver.hpp | head -1 | sed -e 's/.*define.*0x\([0-9]*\).*/\1/' -e 's/0\+\([0-9]\+\)/\1/')
IUTEST_REVISION:=$(shell grep 'IUTEST_REVISION' ../../include/iutest_ver.hpp | head -1 | sed -e 's/.*define.*0x\([0-9]*\).*/\1/' -e 's/0\+\([0-9]\+\)/\1/')
IUTEST_VERSION:=$(IUTEST_MAJORVER).$(IUTEST_MINORVER).$(IUTEST_MICROVER).$(IUTEST_REVISION)

DOXYGEN_VERSION:=$(word 3, $(shell grep 'PROJECT_NUMBER' ../../docs/Doxyfile | tail -n 1))
CHANGES_FILE:=../../CHANGES.md

default: dump-version doxygen-version nuget-version changes

dump-version:
	@echo iutest version $(IUTEST_VERSION)

doxygen-version:
	@echo Doxygen PROJECT_NUMBER $(DOXYGEN_VERSION)
	@if [ "$(IUTEST_VERSION)" != "$(DOXYGEN_VERSION)" ]; then exit 1; fi

nuget-version:
	@grep '<version>' ../../projects/nuget/iutest.nuspec | sed -e 's/.*>\(.*\)<.*/NuGet Version: \1/'
ifeq (0, $(IUTEST_REVISION))
	@grep '$(IUTEST_MAJORVER).$(IUTEST_MINORVER).$(IUTEST_MICROVER)' ../../projects/nuget/iutest.nuspec > /dev/null
else
	@grep '<version>' ../../projects/nuget/iutest.nuspec | sed -e 's/.*>\(.*\)<.*/NuGet Version: \1/'
	@echo test skipped...
endif


changes:
	@grep 'Changes for ' $(CHANGES_FILE) | head -1
	@if [ ! -e "$(CHANGES_FILE)" ]; then exit 1; fi
ifeq (0, $(IUTEST_REVISION))
	@grep 'Changes for ' $(CHANGES_FILE) | head -1 | grep '$(IUTEST_MAJORVER).$(IUTEST_MINORVER).$(IUTEST_MICROVER)' > /dev/null
else
	@echo test skipped...
endif
