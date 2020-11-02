#
# zapcc.mk
#
# GCC version check
#
# Copyright (C) 2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

ifneq ($(CXX_NAME),zapcc++)

ifeq ($(findstring zapcc++, $(CXX)), zapcc++)
CXX_NAME=zapcc++
endif

endif

ifeq ($(CXX_NAME),zapcc++)

CXX_NAME=zapcc++
ZAPCCVERSION:=$(shell $(CXX) --version | grep version | sed "s/.*version[ ]*\([0-9]*\.[0-9]*\).*/\1/")
ZAPCC_TATGET:=$(shell $(CXX) --version | grep Target | sed "s/.*Target:[ ]*\(.*\)/\1/")

dot:=.
empty:=
space:=$(empty) $(empty)
ZAPCCVERSION:=$(subst -,$(dot), $(ZAPCCVERSION))
ZAPCCVERSION:=$(subst $(dot),$(space), $(ZAPCCVERSION))

ifeq ($(words $(ZAPCCVERSION)), 2)
ZAPCCMAJOR:=$(word 1, $(ZAPCCVERSION))
ZAPCCMINOR:=$(word 2, $(ZAPCCVERSION))
else
ZAPCCMAJOR:=0
ZAPCCMINOR:=0
endif

CXX_MAJOR=${ZAPCCMAJOR}
CXX_MINOR=${ZAPCCMINOR}
CXX_VERSION=${CXX_MAJOR}.${CXX_MINOR}

STD_CPP03=c++98
STD_GNU03=gnu++98

STD_CPP11=c++11
STD_GNU11=gnu++11

NO_UNUSED_LOCAL_TYPEDEFS=-Wno-unused-local-typedefs

#
# c++11
#

# 7.0 later
ifeq (1,$(shell expr \( $(ZAPCCMAJOR) \>= 7 \) ))
STD_CPP11=c++11
STD_GNU11=gnu++11
else
STD_CPP11=c++0x
STD_GNU11=gnu++0x
endif

#
# c++14
#

# 7.0 later
ifeq (1,$(shell expr \( $(ZAPCCMAJOR) \>= 7 \) ))
STD_CPP14=c++14
STD_GNU14=gnu++14
endif

#
# c++17
#

# 7.0 later
ifeq (1,$(shell expr \( $(ZAPCCMAJOR) \>= 7 \)))
STD_CPP17=c++17
STD_GNU17=gnu++17
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

ifndef STDFLAG_VALUE
STDFLAG_VALUE=$(STD_CPP)
endif
ifndef STDFLAG
STDFLAG=-std=$(STDFLAG_VALUE)
endif

endif
