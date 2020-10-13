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
APPLE_CLANGVERSION:=$(shell $(CXX) --version | grep -o "version\s[0-9]*\.[0-9]*")

dot:=.
empty:=
space:=$(empty) $(empty)
APPLE_CLANGVERSION:=$(subst -,$(dot), $(APPLE_CLANGVERSION))
APPLE_CLANGVERSION:=$(subst $(dot),$(space), $(APPLE_CLANGVERSION))

# $(warning ${APPLE_CLANGVERSION})

ifeq ($(words $(APPLE_CLANGVERSION)), 3)
APPLE_CLANGMAJOR:=$(word 2, $(APPLE_CLANGVERSION))
APPLE_CLANGMINOR:=$(word 3, $(APPLE_CLANGVERSION))
ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 7 \)))

# https://en.wikipedia.org/wiki/Xcode#Toolchain_versions

ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 12 \)))
CLANGMAJOR:=10
CLANGMINOR:=0
else

ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 11 \)))

ifeq (1,$(shell expr \( $(APPLE_CLANGMINOR) \>= 4 \)))
CLANGMAJOR:=9
CLANGMINOR:=0
else
CLANGMAJOR:=8
CLANGMINOR:=0
endif

else

ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 10 \)))

ifeq (1,$(shell expr \( $(APPLE_CLANGMINOR) \>= 2 \)))
CLANGMAJOR:=7
CLANGMINOR:=0
else
CLANGMAJOR:=6
CLANGMINOR:=0
endif

else

ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 9 \)))

ifeq (1,$(shell expr \( $(APPLE_CLANGMINOR) \>= 3 \)))
CLANGMAJOR:=5
CLANGMINOR:=0
else
CLANGMAJOR:=4
CLANGMINOR:=0
endif

else

CLANGMAJOR:=3

ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 8 \)))
CLANGMINOR:=9
else
ifeq (1,$(shell expr \( $(APPLE_CLANGMINOR) \>= 3 \)))
CLANGMINOR:=8
else
CLANGMINOR:=7
endif	# >= 8
endif	# >= 9
endif	# >= 10
endif	# >= 11
endif	# >= 12
endif	# >= 7

else
CLANGMAJOR:=3
CLANGMINOR:=${APPLE_CLANGMAJOR}
endif
else
CLANGMAJOR:=0
CLANGMINOR:=0
endif

CXX_MAJOR=${CLANGMAJOR}
CXX_MINOR=${CLANGMINOR}
CXX_VERSION=${CXX_MAJOR}.${CXX_MINOR}

# 9.0 later
ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 9 \)))
IUTEST_CXX_STRICT_NOWARN_FLAGS+=-Wno-inconsistent-missing-destructor-override
endif


endif
