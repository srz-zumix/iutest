#
# mingw.mk
#
# Copyright (C) 2019, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

ifeq ($(findstring mingw, $(CXX)),mingw)
IUTEST_MKFLAG_MINGW=1
else
ifeq ($(findstring MinGW, $(shell ${CXX} -v 2>&1)), MinGW)
IUTEST_MKFLAG_MINGW=1
endif
endif

ifndef IUTEST_MKFLAG_MINGW
IUTEST_MKFLAG_MINGW=0
endif

ifeq ($(IUTEST_MKFLAG_MINGW),1)
LIBS+=ws2_32
override CXXFLAGS += -static-libgcc -static-libstdc++
endif
