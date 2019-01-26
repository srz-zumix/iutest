#!/usr/bin/make

default: version-test doxygen-command-typo-check

version-test:
	make -f VersionTest.mk --no-print-directory

doxygen-test:
	make -f DoxygenCommandCheck.mk --no-print-directory ROOT=../../include
