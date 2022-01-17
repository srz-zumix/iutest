#
# gccversion.mk
#
# GCC version check
#
# Copyright (C) 2017-2021, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

ifneq ($(CXX_NAME),g++)

ifeq ($(findstring g++, $(CXX)), g++)
ifneq ($(findstring clang++, $(CXX)), clang++)
CXX_NAME=g++
endif
endif

endif

ifeq ($(CXX_NAME),g++)

GCCDUMPVERSION:=$(shell $(CXX) -dumpversion)
GCCVERSION_TEMP:=$(GCCDUMPVERSION) 0 0

dot:=.
empty:=
space:=$(empty) $(empty)
GCCVERSION_TEMP:=$(subst $(dot),$(space), $(GCCVERSION_TEMP))
GCCMAJOR:=$(word 1, $(GCCVERSION_TEMP))
GCCMINOR:=$(word 2, $(GCCVERSION_TEMP))

CXX_MAJOR=${GCCMAJOR}
CXX_MINOR=${GCCMINOR}
CXX_VERSION=${CXX_MAJOR}.${CXX_MINOR}

STD_CPP03=c++98
STD_GNU03=gnu++98

# $(warning ${GCCMAJOR})

#
# c++11
#

# 4.3 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \> 4 \) \| \( $(GCCMAJOR) \>= 4 \& $(GCCMINOR) \>= 3 \)))
STD_CPP0X=c++0x
STD_GNU0X=gnu++0x
endif

# 4.7 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \> 4 \) \| \( $(GCCMAJOR) \>= 4 \& $(GCCMINOR) \>= 7 \)))
STD_CPP11=c++11
STD_GNU11=gnu++11

NO_UNUSED_LOCAL_TYPEDEFS=-Wno-unused-local-typedefs
endif

#
# c++14
#

# 4.8 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \>= 4 \& $(GCCMINOR) \>= 8 \)))
STD_CPP1Y=c++1y
STD_GNU1Y=gnu++1y
endif

# 5.0 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \>= 5 \) ))
STD_CPP14=c++14
STD_GNU14=gnu++14
endif

#
# c++17
#

# 5.0 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \>= 5 \) ))
#STD_CPP17=c++1z
#STD_GNU17=gnu++1z
STD_CPP17=c++17
STD_GNU17=gnu++17
endif


#
# c++20
#

# 8.0 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \>= 8 \) ))
STD_CPP2A=c++2a
STD_GNU2A=gnu++2a
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

UTILS_MAKEFILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
include $(UTILS_MAKEFILE_DIR)/stdcver.mk

#
# Warning Option
#

# until 4.6
ifeq (1,$(shell expr \( $(GCCMAJOR) \< 4 \) \| \( $(GCCMAJOR) = 4 \& $(GCCMINOR) \< 6 \)))
IUTEST_CXX_NOWARN_FLAGS+=-Wno-sign-compare -Wno-conversion-null
endif

# arm
ifeq ($(findstring arm, $(CXX)), arm)
IUTEST_CXX_NOWARN_FLAGS+=-Wno-psabi
endif

# 7.0 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \> 6 \) ))
IUTEST_CXX_STRICT_FLAGS+=-Wshadow-compatible-local
endif

# 6.0 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \> 5 \) ))
IUTEST_CXX_NOWARN_FLAGS+=-Wduplicated-cond
endif

# 5.0 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \> 4 \) ))
IUTEST_CXX_STRICT_FLAGS+=-Wfloat-conversion -Wformat-signedness
IUTEST_CXX_NOWARN_FLAGS+=-Wno-missing-field-initializers
endif

# 4.8 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \> 4 \) \| \( $(GCCMAJOR) \>= 4 \& $(GCCMINOR) \>= 8 \)))
# IUTEST_CXX_STRICT_FLAGS+=-Wsuggest-attribute=format
endif

# 4.0 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \> 3 \) ))
IUTEST_CXX_STRICT_FLAGS+=-Wunreachable-code -Wdouble-promotion \
	-Wmissing-noreturn -Wswitch-enum \
	-Wlogical-op -Woverlength-strings \
	-Wvariadic-macros
endif

# c++11 later
ifeq (1,$(shell expr \( $(CPPVER_Y) \>= 2011 \) ))

# 5.1 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \> 5 \) \| \( $(GCCMAJOR) = 5 \& $(GCCMINOR) \> 0 \)))
IUTEST_CXX_STRICT_FLAGS+=-Wsuggest-override
endif

endif

IUTEST_CXX_STRICT_FLAGS+=-Wformat-nonliteral -Winit-self

ifdef CI
# 4.9 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \> 4 \) \| \( $(GCCMAJOR) \>= 4 \& $(GCCMINOR) \>= 9 \)))
IUTEST_CXX_DIAGNOSTICS_FLAGS+=-fno-diagnostics-color
endif
endif

## for __float128 Q literal
# -fext-numeric-literals

endif
