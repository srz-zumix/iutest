#
# iccversion.mk
#
# Intel Compiler (ICC) version check
#
# Copyright (C) 2021, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

ifneq ($(CXX_NAME),icc)

ifeq ($(findstring icpc, $(CXX)), icpc)
CXX_NAME=icc
endif

endif

ifeq ($(CXX_NAME),icc)

ICCDUMPVERSION:=$(shell $(CXX) -dumpversion)
ICCVERSION_TEMP:=$(ICCDUMPVERSION) 0 0

dot:=.
empty:=
space:=$(empty) $(empty)
ICCVERSION_TEMP:=$(subst $(dot),$(space), $(ICCVERSION_TEMP))
ICCMAJOR:=$(word 1, $(ICCVERSION_TEMP))
ICCMINOR:=$(word 2, $(ICCVERSION_TEMP))

CXX_MAJOR=${ICCMAJOR}
CXX_MINOR=${ICCMINOR}
CXX_VERSION=${CXX_MAJOR}.${CXX_MINOR}

STD_CPP03=c++98
STD_GNU03=gnu++98

IUTEST_CXX_STRICT_FLAGS= \
	-Wformat=2 -Wcast-qual \
	-Wwrite-strings -Wpointer-arith -Wundef

endif
