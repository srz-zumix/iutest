#
# xcode.mk
#
# detect xcode compiler
#
# Copyright (C) 2018-2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

APPLE_CXXVERSION:=$(shell $(CXX) --version | grep -o Apple)

ifeq ($(APPLE_CXXVERSION),Apple)

CXX_APPLE_CLANG=1
CXX_NAME=clang++
CLANGVERSION:=$(shell $(CXX) --version | grep -o "version\s[0-9]*\.[0-9]*")

dot:=.
empty:=
space:=$(empty) $(empty)
CLANGVERSION:=$(subst -,$(dot), $(CLANGVERSION))
CLANGVERSION:=$(subst $(dot),$(space), $(CLANGVERSION))

ifeq ($(words $(CLANGVERSION)), 3)
CLANGMAJOR:=3
CLANGMINOR:=$(word 2, $(CLANGVERSION))
else
CLANGMAJOR:=0
CLANGMINOR:=0
endif

endif
