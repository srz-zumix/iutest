#
# clangversion.mk
#
# Clang version check
#
# Copyright (C) 2017-2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

# scan-build
ifeq ($(findstring clang++, $(CXX)), clang++)
IUTEST_CLANG_CXX=$(CXX)
endif

ifeq ($(findstring clang++, $(CCC_CXX)), clang++)
IUTEST_CLANG_CXX=$(CCC_CXX)
endif

ifndef CXX_APPLE_CLANG
ifeq ($(CXX_NAME),clang++)
IUTEST_CLANG_CXX=$(CXX)
endif
endif

ifdef IUTEST_CLANG_CXX

CXX_NAME=clang++
CLANGVERSION:=$(shell $(IUTEST_CLANG_CXX) --version | grep version | sed "s/.*version[ ]*\([0-9]*\.[0-9]*\).*/\1/")
CLANG_TATGET:=$(shell $(IUTEST_CLANG_CXX) --version | grep Target | sed "s/.*Target:[ ]*\(.*\)/\1/")

dot:=.
empty:=
space:=$(empty) $(empty)
CLANGVERSION:=$(subst -,$(dot), $(CLANGVERSION))
CLANGVERSION:=$(subst $(dot),$(space), $(CLANGVERSION))

ifeq ($(words $(CLANGVERSION)), 2)
CLANGMAJOR:=$(word 1, $(CLANGVERSION))
CLANGMINOR:=$(word 2, $(CLANGVERSION))
else
CLANGMAJOR:=0
CLANGMINOR:=0
endif

endif

ifeq ($(CXX_NAME),clang++)

STD_CPP03=c++98
STD_GNU03=gnu++98

STD_CPP11=c++11
STD_GNU11=gnu++11

NO_UNUSED_LOCAL_TYPEDEFS=-Wno-unused-local-typedefs

#
# c++14
#

# 3.5 later
ifeq (1,$(shell expr \( \( $(CLANGMAJOR) \> 3 \) \| \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 5 \) \)))
STD_CPP14=c++14
STD_GNU14=gnu++14
else

# 3.2 later
#ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 2 \)))
#STD_CPP14=c++1y
#STD_GNU14=gnu++1y
#endif

endif

#
# c++17
#

# 4.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 4 \)))
STD_CPP17=c++17
STD_GNU17=gnu++17
else

# 3.5 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \> 3 \) \| \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 5 \)))
STD_CPP17=c++1z
STD_GNU17=gnu++1z
endif

endif

#
# latest
#

STD_CPP=$(STD_CPP11)
STD_GNU=$(STD_GNU11)

ifdef STD_CPP14
STD_CPP=$(STD_CPP14)
STD_GNU=$(STD_GNU14)
endif

ifdef STD_CPP17
STD_CPP=$(STD_CPP17)
STD_GNU=$(STD_GNU17)
endif

ifndef STDFLAG
STDFLAG=-std=$(STD_CPP)
endif
#ifndef STDLIB
#STDLIB=-stdlib=libc++
#endif

#
# Warning Option
#

IUTEST_CXX_WARN_FLAGS+=-Wno-missing-field-initializers

# 8.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 8 \)))
IUTEST_CXX_WARN_FLAGS+=-Wextra-semi
endif

ifeq ($(CLANG_TATGET), x86_64-pc-windows-msvc)
CXXFLAGS+= -Xclang -flto-visibility-public-std
endif

endif

CXX_MAJOR=${CLANGMAJOR}
CXX_MINOR=${CLANGMINOR}
CXX_VERSION=${CXX_MAJOR}.${CXX_MINOR}
