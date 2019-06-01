#
# cygwin.mk
#
# Copyright (C) 2017-2019, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

ifeq ($(findstring cygwin, $(shell ${CXX} -v 2>&1)), cygwin)
IUTEST_MKFLAG_CYGWIN=1
else

ifeq ($(findstring windows-cygnus, $(shell ${CXX} -v 2>&1)), windows-cygnus)
IUTEST_MKFLAG_CYGWIN=1
else
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
IUTEST_MKFLAG_CYGWIN=1
endif
endif

endif

ifndef IUTEST_MKFLAG_CYGWIN
IUTEST_MKFLAG_CYGWIN=0
endif

ifeq ($(IUTEST_MKFLAG_CYGWIN),1)
CYGWIN_OPTION:=${CYGWIN} error_start=dumper.exe
export CYGWIN=${CYGWIN_OPTION}
endif
