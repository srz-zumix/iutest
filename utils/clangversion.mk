#
# clangversion.mk
#
# Clang version check
#
# Copyright (C) 2017-2021, Takazumi Shirayanagi
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
ifeq (${CLANGMAJOR}${CLANGMINOR},)

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

CXX_MAJOR=${CLANGMAJOR}
CXX_MINOR=${CLANGMINOR}
CXX_VERSION=${CXX_MAJOR}.${CXX_MINOR}

endif
endif

ifeq ($(CXX_NAME),clang++)

STD_CPP03=c++98
STD_GNU03=gnu++98

NO_UNUSED_LOCAL_TYPEDEFS=-Wno-unused-local-typedefs

#
# c++11
#

STD_CPP0X=c++0x
STD_GNU0X=gnu++0x

# 3.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \> 3 \) ))
STD_CPP11=c++11
STD_GNU11=gnu++11
endif

#
# c++14
#

# 3.2 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 2 \)))
STD_CPP1Y=c++1y
STD_GNU1Y=gnu++1y
endif

# 3.5 later
ifeq (1,$(shell expr \( \( $(CLANGMAJOR) \> 3 \) \| \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 5 \) \)))
STD_CPP14=c++14
STD_GNU14=gnu++14
endif

#
# c++17
#

# 3.5 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \> 3 \) \| \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 5 \)))
STD_CPP1Z=c++1z
STD_GNU1Z=gnu++1z
endif

# 5.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 5 \)))
STD_CPP17=c++17
STD_GNU17=gnu++17
endif

#
# c++20
#

# 5.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 5 \)))
STD_CPP2A=c++2a
STD_GNU2A=gnu++2a
endif

# 11.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 11 \)))
STD_CPP20=c++20
STD_GNU20=gnu++20
endif

#
# stable/latest
#

STD_CPP=$(STD_CPP03)
STD_GNU=$(STD_GNU03)
STD_CPP_LATEST=$(STD_CPP03)
STD_GNU_LATEST=$(STD_GNU03)

ifdef STD_CPP11
STD_CPP_LATEST=$(STD_CPP0X)
STD_GNU_LATEST=$(STD_GNU0X)
endif

ifdef STD_CPP11
STD_CPP=$(STD_CPP11)
STD_GNU=$(STD_GNU11)
STD_CPP_LATEST=$(STD_CPP11)
STD_GNU_LATEST=$(STD_GNU11)
endif

ifdef STD_CPP1Y
STD_CPP_LATEST=$(STD_CPP1Y)
STD_GNU_LATEST=$(STD_GNU1Y)
endif

ifdef STD_CPP14
STD_CPP=$(STD_CPP14)
STD_GNU=$(STD_GNU14)
STD_CPP_LATEST=$(STD_CPP14)
STD_GNU_LATEST=$(STD_GNU14)
endif

ifdef STD_CPP1Z
STD_CPP_LATEST=$(STD_CPP1Z)
STD_GNU_LATEST=$(STD_GNU1Z)
endif

ifdef STD_CPP17
STD_CPP=$(STD_CPP17)
STD_GNU=$(STD_GNU17)
STD_CPP_LATEST=$(STD_CPP17)
STD_GNU_LATEST=$(STD_GNU17)
endif

ifdef STD_CPP2A
STD_CPP_LATEST=$(STD_CPP2A)
STD_GNU_LATEST=$(STD_GNU2A)
endif

ifdef STD_CPP20
STD_CPP=$(STD_CPP20)
STD_GNU=$(STD_GNU20)
STD_CPP_LATEST=$(STD_CPP20)
STD_GNU_LATEST=$(STD_GNU20)
endif

ifdef STDFLAG_USE_LATEST
STDFLAG_VALUE=$(STD_CPP_LATEST)
endif
ifndef STDFLAG_VALUE
STDFLAG_VALUE=$(STD_CPP)
endif
ifndef STDFLAG
STDFLAG=-std=$(STDFLAG_VALUE)
endif
#ifndef STDLIB
#STDLIB=-stdlib=libc++
#endif

UTILS_MAKEFILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
include $(UTILS_MAKEFILE_DIR)/stdcver.mk

#
# Warning Option
#

IUTEST_CXX_NOWARN_FLAGS+=-Wno-missing-field-initializers

# until 3.4
ifeq (1,$(shell expr \( $(CLANGMAJOR) \< 3 \) \| \( $(CLANGMAJOR) = 3 \& $(CLANGMINOR) \< 4 \)))
IUTEST_CXX_STRICT_NOWARN_FLAGS+=-Wno-gnu
endif

# until 3.2
ifeq (1,$(shell expr \( $(CLANGMAJOR) \< 3 \) \| \( $(CLANGMAJOR) = 3 \& $(CLANGMINOR) \< 2 \)))
IUTEST_CXX_STRICT_NOWARN_FLAGS+=-Wno-pedantic
endif

# 11.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 11 \)))
IUTEST_CXX_STRICT_NOWARN_FLAGS+=-Wno-suggest-override -Wno-suggest-destructor-override
endif


# 10.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 10 \)))
IUTEST_CXX_STRICT_FLAGS+=-Wimplicit-int-float-conversion
IUTEST_CXX_STRICT_NOWARN_FLAGS+=-Wno-poison-system-directories
endif

# 8.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 8 \)))
IUTEST_CXX_STRICT_FLAGS+=-Wextra-semi \
	-Wimplicit-float-conversion
endif

# ６.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 6 \)))
IUTEST_CXX_STRICT_NOWARN_FLAGS+=-Wno-redundant-parens
endif

# 5.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 5 \)))
IUTEST_CXX_STRICT_NOWARN_FLAGS+=-Wno-inconsistent-missing-destructor-override
endif

# 4.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 4 \)))
IUTEST_CXX_STRICT_FLAGS+=-Wshadow-uncaptured-local
endif

# 3.９ later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \> 3 \) \| \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= ９ \)))
IUTEST_CXX_STRICT_FLAGS+=-Wshadow-all -Wnonportable-system-include-path
endif

# 3.8 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \> 3 \) \| \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 8 \)))
IUTEST_CXX_STRICT_FLAGS+=-Wdouble-promotion
endif

# 3.6 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \> 3 \) \| \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 6 \)))
IUTEST_CXX_STRICT_NOWARN_FLAGS+=-Wno-reserved-id-macro
endif

# 3.5 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \> 3 \) \| \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 5 \)))
IUTEST_CXX_STRICT_FLAGS+=-Wfloat-conversion
endif

# 3.4 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \> 3 \) \| \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 4 \)))
IUTEST_CXX_STRICT_FLAGS+=-Wno-gnu-zero-variadic-macro-arguments
endif

# 3.3 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \> 3 \) \| \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 3 \)))
IUTEST_CXX_STRICT_FLAGS+=-fcomment-block-commands=private,internal,retval
endif

# 3.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 3 \)))
IUTEST_CXX_STRICT_NOWARN_FLAGS+=\
	-Wno-c++98-compat -Wno-c++98-compat-pedantic \
	-Wno-disabled-macro-expansion \
	-Wno-exit-time-destructors \
	-Wno-missing-variable-declarations \

endif

# c++11 later
ifeq (1,$(shell expr \( $(CPPVER_Y) \>= 2011 \) ))

# 11.0 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 11 \)))
IUTEST_CXX_STRICT_FLAGS+=-Wsuggest-override
endif

else

IUTEST_CXX_STRICT_NOWARN_FLAGS+=-Wno-c99-extensions \
	-Wno-variadic-macros \
	-Wno-c++11-long-long \
	-Wno-long-long

endif

IUTEST_CXX_STRICT_FLAGS+=-Wmissing-noreturn -Wswitch-enum

IUTEST_CXX_STRICT_NOWARN_FLAGS+= \
	-Wno-missing-prototypes \
	-Wno-used-but-marked-unused \
	-Wno-global-constructors -Wno-weak-vtables \
	-Wno-padded \
	-Wno-deprecated \

# 3.2 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \> 3 \) \| \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 2 \)))

ifeq ($(IUTEST_WARN_EVERYTHING),1)

IUTEST_CXX_STRICT_FLAGS+=-Weverything
IUTEST_CXX_NOWARN_FLAGS+=${IUTEST_CXX_STRICT_NOWARN_FLAGS}

endif

endif

IUTEST_CXX_NOWARN_FLAGS+=-Wno-sign-conversion

# IUTEST_CXX_NOWARN_FLAGS+=-Wno-error=unknown-warning-option

ifeq ($(CLANG_TATGET), x86_64-pc-windows-msvc)
override CXXFLAGS+= -Xclang -flto-visibility-public-std
endif

endif
